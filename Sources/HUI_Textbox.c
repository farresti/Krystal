/* ========================================================================= */
/*!
 * \file    HUI_Textbox.c
 * \brief   File to handle the text boxes.
 * \author  Nyuu / Orlyn / Red
 * \version 1.0
 * \date    09 June 2015
 */
/* ========================================================================= */
/* Author  | Date     | Comments                                             */
/* --------+----------+----------------------------------------------------- */
/* Nyuu    | 09/06/15 | Creation.                                            */
/* Orlyn   | 15/06/15 | Add HUI_Textbox functions.                           */
/* Orlyn   | 16/06/15 | Add HUI_Textbox functions.                           */
/* Orlyn   | 17/06/15 | Add Cursor functions                                 */
/* Orlyn   | 18/06/15 | Clean and add repeat key support                     */
/* Orlyn   | 19/06/15 | Clean                                                */
/* ========================================================================= */

#include "HUI_Textbox.h"

/* ========================================================================= */

/*!
* \brief Function to return the current key in the text box.
*
* \param pTextBox       A pointer to the SDL_Textbox structure.
* \return an SDL_Keycode value of the current key
*/
static SDL_Keycode HUI_Textbox_GetCurrent(const HUI_Textbox *pTextBox)
{
    return pTextBox->iCurrentKey;
}

/*!
* \brief Function to return the x position of the cursor.
*
* \param pTextBox       A pointer to the SDL_Textbox structure.
* \return X position for the cursor
*/
static Sint32 HUI_Textbox_GetCursorX(const HUI_Textbox *pTextBox)
{
    Sint32 iX = pTextBox->sPointCursor.x;
    Sint32 iW = HUI_Textbox_GetTextLength(pTextBox);

    if (iW)
    {
        iX = pTextBox->rDest.x + iW;
    }
    return iX;
}

/*!
* \brief Function to return the y position of the cursor.
*
* \param pTextBox       A pointer to the SDL_Textbox structure.
* \return Y position for the cursor
*/
static Sint32 HUI_Textbox_GetCursorY(const HUI_Textbox *pTextBox)
{
    return pTextBox->sPointCursor.y;
}

/*!
* \brief Function to set text in the text box.
*
* \param pTextBox       A pointer to the SDL_Textbox structure.
* \param szText         The text to set.
* \return None
*/
static void HUI_Textbox_SetText(HUI_Textbox *pTextBox, const char *szText)
{
    Uint16 iLengthTextbox = HUI_Textbox_GetMaxTextLength(pTextBox);
    size_t iLengthText = strlen(szText);
    Uint32 i = 0;
    if (iLengthText > 0 && iLengthText <= iLengthTextbox)
    {
        memcpy(pTextBox->szText, szText, iLengthText + 1);
        pTextBox->iTextIndex = (Sint32)iLengthText;
    }
    else if (iLengthText > iLengthTextbox)
    {
        for (i = 0; i < iLengthTextbox; ++i)
        {
            *(pTextBox->szText + i) = szText[i];
        }
        *(pTextBox->szText + iLengthTextbox) = '\0';
        pTextBox->iTextIndex                     = iLengthTextbox;
    }
    else
    {
        *(pTextBox->szText)  = '\0';
        pTextBox->iTextIndex = 0;
    }
}

/*!
* \brief Function to add a letter.
*
* \param pTextBox       A pointer to the SDL_Textbox structure.
* \return None
*/
static void HUI_Textbox_Add(HUI_Textbox *pTextBox)
{
    SDL_Keymod   keyMod   = SDL_GetModState();
    SDL_Keycode  currKey  = HUI_Textbox_GetCurrent(pTextBox);
    char        *key      = (char*)SDL_GetKeyName(currKey);
    size_t       iLen     = strlen(key);
    if (currKey != '\0')
    {
        if ((pTextBox->iTextIndex + 1) <= HUI_Textbox_GetMaxTextLength(pTextBox))
        {
            if (iLen == 1)      /*Normal keys*/
            {
                if (!(keyMod & KMOD_SHIFT))  /*Maj key*/
                {
                    key = strlwr(key);
                }
                *(pTextBox->szText + pTextBox->iTextIndex) = key[0];
            }
            else                /*Keypad keys*/
            {
                *(pTextBox->szText + pTextBox->iTextIndex) = key[iLen - 1];
            }
            *(pTextBox->szText + pTextBox->iTextIndex + 1) = '\0';
            pTextBox->iTextIndex++;
        }
    }

}

/*!
* \brief Function to draw the cursor in the textbox.
*
* \param pTextBox       A pointer to the SDL_Textbox structure.
* \return None
*/
static void HUI_Textbox_DrawCursor(HUI_Textbox *pTextBox)
{
    SDL_Color colorCursor = { 0, 0, 0, 255 };
    HUI_Text cursor;
    if (HUI_Textbox_IsActive(pTextBox))
    {
        if (SDL_GetTicks() - pTextBox->iCursorTime >= 500)
        {
            HUI_Text_Init(&cursor, pTextBox->pFont, HUI_Textbox_GetCursorX(pTextBox), HUI_Textbox_GetCursorY(pTextBox));
            HUI_Text_Set (&cursor, "|", &colorCursor, 0);
            HUI_Text_Draw(&cursor);
            HUI_Text_Free(&cursor);

            if (SDL_GetTicks() - pTextBox->iCursorTime >= 1000)
            {
                pTextBox->iCursorTime = SDL_GetTicks();
            }
        }
    }
    else
    {
        pTextBox->iCursorTime = SDL_GetTicks();
    }
}

/*!
* \brief Function to add a space.
*
* \param pTextBox       A pointer to the SDL_Textbox structure.
* \return None
*/
static void HUI_Textbox_AddSpace(HUI_Textbox *pTextBox)
{
    if ((pTextBox->iTextIndex + 1) <= HUI_Textbox_GetMaxTextLength(pTextBox))
    {
        *(pTextBox->szText + pTextBox->iTextIndex)     = ' ';
        *(pTextBox->szText + pTextBox->iTextIndex + 1) = '\0';
        pTextBox->iTextIndex++;
    }
}

/*!
* \brief Function to delete a letter.
*
* \param pTextBox       A pointer to the SDL_Textbox structure.
* \return None
*/
static void HUI_Textbox_Delete(HUI_Textbox *pTextBox)
{
    pTextBox->iTextIndex--;
    if (pTextBox->iTextIndex < 0)
    {
        pTextBox->iTextIndex = 0;
    }
    *(pTextBox->szText + pTextBox->iTextIndex) = '\0';
}

/*!
* \brief Function to test if a Textbox is full.
*
* \param pTextBox       A pointer to the SDL_Textbox structure.
* \return None.
*/
static void HUI_Textbox_CheckSize(HUI_Textbox *pTextBox)
{
    if (pTextBox->iTextIndex == HUI_Textbox_GetMaxTextLength(pTextBox) ||
        (Uint32)HUI_Textbox_GetTextLength(pTextBox) >= HUI_Textbox_GetMaxBoxLength(pTextBox))
    {
        pTextBox->bIsFull = SDL_TRUE;
    }
    else
    {
        pTextBox->bIsFull = SDL_FALSE;
    }
}

/*!
* \brief Function to return if a key is locked.
*
* \param pTextBox       A pointer to the SDL_Textbox structure.
* \return true if a key is locked, false else
*/
static SDL_bool HUI_Textbox_IsKeyLocked(const HUI_Textbox *pTextBox)
{
    return pTextBox->bIsLocked;
}

/*!
* \brief Function to test if key is locked.
*
* \param pTextBox       A pointer to the SDL_Textbox structure.
* \return None.
*/
static void HUI_Textbox_CheckLock(HUI_Textbox *pTextBox)
{
    if (pTextBox->iCurrentKey == pTextBox->iLastKey)
    {
        if (SDL_GetTicks() - pTextBox->iLastTime >= 150)
        {
            pTextBox->bIsLocked = SDL_TRUE;
        }
        else
        {
            pTextBox->bIsLocked = SDL_FALSE;
        }
    }
    else
    {
        pTextBox->bIsLocked = SDL_FALSE;
    }
}

/*!
* \brief Function to set the active flag of the text box.
*
* \param pTextBox Pointer to the textbox.
* \param pInput   Pointer to the inputs.
* \return None.
*/
static void HUI_Textbox_CheckActive(HUI_Textbox *pTextBox, const HUI_Input *pInput)
{
    if (UTIL_ContainPoint(&pTextBox->rDest, &pInput->iMouse))
    {
        SDL_SetCursor(pInput->pTxtCursor);

        if (!HUI_Textbox_IsActive(pTextBox))
        {
            if (pInput->bMouseButtons[SDL_BUTTON_LEFT])
            {
                pTextBox->bIsActive = SDL_TRUE;
            }
        }
    }
    else
    {
        SDL_SetCursor(pInput->pStdCursor);

        if (pInput->bMouseButtons[SDL_BUTTON_LEFT])
        {
            pTextBox->bIsActive = SDL_FALSE;
        }
    }
}

/* ========================================================================= */

/*!
 * \brief Function to init a SDL_Textbox structure.
 *
 * \param pTextBox Pointer to the textbox.
 * \param pFont    Pointer to the font to set.
 * \param pColor   Pointer to the font color of the text.
 * \param pDest    Pointer to a rect filled with position and size of the text box.
 * \param iLength  The maximum length of the string allowed in the text box, != 0.
 * \param szText   String to inialise the text box, if none, value "" must be passed.
 * \return None
 *
 * \remark if the length of szText is greater than iLength, the string will be cut to match iLength.
 */
void HUI_Textbox_Init(HUI_Textbox *pTextBox, TTF_Font *pFont, SDL_Color *pColor, SDL_Rect *pDest, Uint16 iLength, char* szText)
{
    Sint32 iW = 0;
    Sint32 iH = 0;

    TTF_SizeText(pFont, " ", &iW, NULL);
    TTF_SizeText(pFont, "|", NULL, &iH);

    if (iH > pDest->h || iW > pDest->w)
    {
        COM_Log_Print(COM_LOG_ERROR, "Not enough space for text in the texbox.");
        return;
    }

    /*Init flags*/
    pTextBox->bIsActive      = SDL_FALSE;
    pTextBox->bIsFull        = SDL_FALSE;
    pTextBox->bIsLocked      = SDL_FALSE;
    /*Init max length*/
    pTextBox->iBoxLength     = iLength*iW;

    if (HUI_Textbox_GetMaxBoxLength(pTextBox) >= (Uint32) pDest->w)
    {
        pTextBox->iBoxLength = pDest->w - iW;
    }

    pTextBox->iTextLength    = iLength;
    /*Init text input*/
    pTextBox->szText         = (char*)UTIL_Malloc((iLength + 1)* sizeof(char));
    pTextBox->iCurrentKey    = pTextBox->iLastKey = '\0';
    pTextBox->iTextIndex     = 0;
    HUI_Textbox_SetText(pTextBox, szText);
    /*Init for cursor*/
    pTextBox->pFont          = pFont;
    pTextBox->sPointCursor.x = pDest->x + iW / 2;
    pTextBox->sPointCursor.y = pDest->y + pDest->h / 2 - iH / 2;
    /*Init structure SDL_Text*/
    pTextBox->pText          = (HUI_Text*) UTIL_Malloc(sizeof(HUI_Text));
    HUI_Text_Init(pTextBox->pText, pTextBox->pFont, pTextBox->sPointCursor.x, pTextBox->sPointCursor.y);
    HUI_Text_Set(pTextBox->pText, pTextBox->szText, pColor, 0);
    /*Init time*/
    pTextBox->iLastTime      = SDL_GetTicks();
    pTextBox->iCursorTime    = SDL_GetTicks();
    /*Init rect*/
    pTextBox->rDest.x        = pDest->x;
    pTextBox->rDest.y        = pDest->y;
    pTextBox->rDest.w        = pDest->w;
    pTextBox->rDest.h        = pDest->h;
    /*Init colors*/
    pTextBox->pColorFont     = pColor;
}

/*!
 * \brief Function to update text from user input.
 *
 * \param pTextBox Pointer to the textbox.
 * \param pInput   Pointer to the inputs.
 * \return None
 */
void HUI_Textbox_Update(HUI_Textbox *pTextBox, HUI_Input *pInput)
{
    SDL_Keycode iLastKey = HUI_Input_GetLastKey(pInput);

    if (HUI_Textbox_IsActive(pTextBox))
    {
        if (HUI_Input_IsKeyPressed(pInput, iLastKey))
        {
            pTextBox->iCurrentKey = iLastKey;
            if ((iLastKey >= SDLK_SPACE && iLastKey <= SDLK_z) ||
                (iLastKey >= SDLK_KP_DIVIDE && iLastKey <= SDLK_KP_PERIOD))
            {
                if (!HUI_Textbox_IsFull(pTextBox))
                {
                    if (iLastKey == SDLK_SPACE)
                    {
                        HUI_Textbox_AddSpace(pTextBox);
                    }
                    else if (pTextBox->iCurrentKey != pTextBox->iLastKey ||
                        HUI_Textbox_IsKeyLocked(pTextBox))
                    {
                        HUI_Textbox_Add(pTextBox);
                    }
                    if (!HUI_Textbox_IsKeyLocked(pTextBox))
                    {
                        pTextBox->iLastTime = SDL_GetTicks();
                    }
                }
            }
            else if (iLastKey == SDLK_BACKSPACE)
            {
                HUI_Textbox_Delete(pTextBox);
            }
            else if (iLastKey == SDLK_RETURN)
            {
                pTextBox->bIsActive = SDL_FALSE;
            }
            HUI_Input_ResetKey(pInput, iLastKey);
        }
        HUI_Textbox_CheckSize(pTextBox);
        HUI_Textbox_CheckLock(pTextBox);
        if (HUI_Textbox_IsKeyLocked(pTextBox))
        {
            HUI_Input_SetKeyRepeat(pInput, SDL_TRUE);
        }
        else
        {
            HUI_Input_SetKeyRepeat(pInput, SDL_FALSE);
        }
        pTextBox->iLastKey = pTextBox->iCurrentKey;
    }
    else
    {
        HUI_Input_SetKeyRepeat(pInput, SDL_FALSE);
    }
    HUI_Textbox_CheckActive(pTextBox, pInput);
}

/*!
 * \brief Function to draw the textbox.
 *
 * \param pTextBox Pointer to the textbox.
 * \return None
 */
void HUI_Textbox_Draw(HUI_Textbox *pTextBox)
{
    HUI_Text_Set(pTextBox->pText, pTextBox->szText, pTextBox->pColorFont, 0);
    HUI_Text_Draw(pTextBox->pText);

    HUI_Textbox_DrawCursor(pTextBox);
}

/*!
 * \brief Function to return the length in pixel of the text.
 *
 * \param pTextBox Pointer to the textbox.
 * \return size of the text as it is displayed.
 */
Sint32 HUI_Textbox_GetTextLength(const HUI_Textbox *pTextBox)
{
    Sint32 iW = 0;
    if (pTextBox->szText)
    {
        TTF_SizeText(pTextBox->pText->pFont, pTextBox->szText, &iW, NULL);
    }
    return iW;
}

/*!
 * \brief Function to return the maximum length of the text.
 *
 * \param pTextBox Pointer to the textbox.
 * \return number of caracters allowed in the textbox.
 */
Uint16 HUI_Textbox_GetMaxTextLength(const HUI_Textbox *pTextBox)
{
    return pTextBox->iTextLength;
}

/*!
 * \brief Function to return the max length of a text of a textbox.
 *
 * \param pTextBox Pointer to the textbox.
 * \return maximum size text in the text box for the choosen font.
 */
Uint32 HUI_Textbox_GetMaxBoxLength(const HUI_Textbox *pTextBox)
{
    return pTextBox->iBoxLength;
}

/*!
 * \brief Function to return the state of a textbox.
 *
 * \param pTextBox Pointer to the textbox.
 * \return true if the box is active, false else
 */
SDL_bool HUI_Textbox_IsActive(const HUI_Textbox *pTextBox)
{
    return pTextBox->bIsActive;
}

/*!
 * \brief Function to return if a Textbox is full.
 *
 * \param pTextBox Pointer to the textbox.
 * \return true if the box is full, false else
 */
SDL_bool HUI_Textbox_IsFull(const HUI_Textbox *pTextBox)
{
    return pTextBox->bIsFull;
}

/*!
 * \brief Function to set the color of the text in the text box.
 *
 * \param pTextBox Pointer to the textbox.
 * \param pColor   Pointer to the new color.
 * \return None
 */
void SDL_Textbox_SetColor(HUI_Textbox *pTextBox, SDL_Color *pColor)
{
    pTextBox->pColorFont = pColor;
}

/*!
 * \brief Function to free an SDL_Textbox.
 *
 * \param pTextBox Pointer to the textbox.
 * \return None
 */
void HUI_Textbox_Free(HUI_Textbox *pTextBox)
{
    HUI_Text_Free(pTextBox->pText);
    UTIL_Free(pTextBox->pText);
    UTIL_Free(pTextBox->szText);
}

/* ========================================================================= */
