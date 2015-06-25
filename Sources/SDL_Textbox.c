/* ========================================================================= */
/*!
 * \file    SDL_Textbox.c
 * \brief   File to handle the text boxes.
 * \author  Nyuu / Orlyn / Red
 * \version 1.0
 * \date    09 June 2015
 */
/* ========================================================================= */
/* Author  | Date     | Comments                                             */
/* --------+----------+----------------------------------------------------- */
/* Nyuu    | 09/06/15 | Creation.                                            */
/* Orlyn   | 15/06/15 | Add SDL_Textbox functions.                           */
/* Orlyn   | 16/06/15 | Add SDL_Textbox functions.                           */
/* Orlyn   | 17/06/15 | Add Cursor functions                                 */
/* Orlyn   | 18/06/15 | Clean and add repeat key support                     */
/* Orlyn   | 19/06/15 | Clean                                                */
/* ========================================================================= */

#include "SDL_Textbox.h"

/* ========================================================================= */

/*!
* \brief Function to init a SDL_Textbox structure.
*
* \param pTextBox       A pointer to the SDL_Textbox structure.
* \param pFont          A pointer to the font to set.
* \param pColorFont     A pointer to the font color of the text.
* \param pRectDest      A pointer to a rect filled with position and size of the text box.
* \param iLength        The maximum length of the string allowed in the text box, != 0.
* \param szText         A string to inialise the text box, if none, value "" must be passed.
* \return None
* \remarks if the length of szText is greater than iLength, the string will be cut to match iLength.
*/
void SDL_Textbox_Init(SDL_Textbox *pTextBox, TTF_Font *pFont, SDL_Color *pColorFont, SDL_Rect *pRectDest, Uint16 iLength, char* szText)
{
    Sint32 iW = 0;
    Sint32 iH = 0;
    TTF_SizeText(pFont, " ", &iW, NULL);
    TTF_SizeText(pFont, "|", NULL, &iH);
    if (iH > pRectDest->h || iW > pRectDest->w)
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
    if (SDL_Textbox_GetMaxBoxLength(pTextBox) >= (Uint32)pRectDest->w)
    {
        pTextBox->iBoxLength = pRectDest->w - iW;
    }
    pTextBox->iTextLength    = iLength;
    /*Init text input*/
    pTextBox->szText         = (char*)UTIL_Malloc((iLength + 1)* sizeof(char));
    pTextBox->iCurrentKey    = pTextBox->iLastKey = '\0';
    pTextBox->iTextIndex     = 0;
    SDL_Textbox_SetText(pTextBox, szText);
    /*Init for cursor*/
    pTextBox->pFont          = pFont;
    pTextBox->sPointCursor.x = pRectDest->x + iW / 2;
    pTextBox->sPointCursor.y = pRectDest->y + pRectDest->h / 2 - iH / 2;
    /*Init structure SDL_Text*/
    pTextBox->pText          = (SDL_Text*)UTIL_Malloc(sizeof(SDL_Text));
    SDL_Text_Init(pTextBox->pText, pTextBox->pFont, pTextBox->sPointCursor.x, pTextBox->sPointCursor.y);
    SDL_Text_Set(pTextBox->pText, pTextBox->szText, pColorFont, 0);
    /*Init time*/
    pTextBox->iLastTime      = SDL_GetTicks();
    pTextBox->iCursorTime    = SDL_GetTicks();
    /*Init rect*/
    pTextBox->rDest.x        = pRectDest->x;
    pTextBox->rDest.y        = pRectDest->y;
    pTextBox->rDest.w        = pRectDest->w;
    pTextBox->rDest.h        = pRectDest->h;
    /*Init colors*/
    pTextBox->pColorFont     = pColorFont;
}

/*!
* \brief Function to set text in the text box.
*
* \param pTextBox       A pointer to the SDL_Textbox structure.
* \param szText         The text to set.
* \return None
*/
static void SDL_Textbox_SetText(SDL_Textbox *pTextBox, const char *szText)
{
    Uint16 iLengthTextbox = SDL_Textbox_GetMaxTextLength(pTextBox);
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
* \brief Function to update text from user input.
*
* \param pTextBox       A pointer to the SDL_Textbox structure.
* \return None
*/
void SDL_Textbox_Update(SDL_Textbox *pTextBox, SDL_Input *pInput)
{
    SDL_Keycode iLastKey = SDL_Input_GetLastKey(pInput);
    if (SDL_Textbox_IsActive(pTextBox))
    {
        if (SDL_Input_IsKeyPressed(pInput, iLastKey))
        {
            pTextBox->iCurrentKey = iLastKey;
            if ((iLastKey >= SDLK_SPACE && iLastKey <= SDLK_z) ||
                (iLastKey >= SDLK_KP_DIVIDE && iLastKey <= SDLK_KP_PERIOD))
            {
                if (!SDL_Textbox_IsFull(pTextBox))
                {
                    if (iLastKey == SDLK_SPACE)
                    {
                        SDL_Textbox_AddSpace(pTextBox);
                    }
                    else if (pTextBox->iCurrentKey != pTextBox->iLastKey ||
                        SDL_Textbox_IsKeyLocked(pTextBox))
                    {
                        SDL_Textbox_Add(pTextBox);
                    }
                    if (!SDL_Textbox_IsKeyLocked(pTextBox))
                    {
                        pTextBox->iLastTime = SDL_GetTicks();
                    }
                }
            }
            else if (iLastKey == SDLK_BACKSPACE)
            {
                SDL_Textbox_Delete(pTextBox);
            }
            else if (iLastKey == SDLK_RETURN)
            {
                pTextBox->bIsActive = SDL_FALSE;
            }
            SDL_Input_ResetKey(pInput, iLastKey);
        }
        SDL_Textbox_CheckSize(pTextBox);
        SDL_Textbox_CheckLock(pTextBox);
        if (SDL_Textbox_IsKeyLocked(pTextBox))
        {
            SDL_Input_SetKeyRepeat(pInput, SDL_TRUE);
        }
        else
        {
            SDL_Input_SetKeyRepeat(pInput, SDL_FALSE);
        }
        pTextBox->iLastKey = pTextBox->iCurrentKey;
    }
    else
    {
        SDL_Input_SetKeyRepeat(pInput, SDL_FALSE);
    }
    SDL_Textbox_CheckActive(pTextBox, pInput);
}

/*!
* \brief Function to add a letter.
*
* \param pTextBox       A pointer to the SDL_Textbox structure.
* \return None
*/
static void SDL_Textbox_Add(SDL_Textbox *pTextBox)
{
    SDL_Keymod   keyMod   = SDL_GetModState();
    SDL_Keycode  currKey  = SDL_Textbox_GetCurrent(pTextBox);
    char        *key      = (char*)SDL_GetKeyName(currKey);
    size_t       iLen     = strlen(key);
    if (currKey != '\0')
    {
        if ((pTextBox->iTextIndex + 1) <= SDL_Textbox_GetMaxTextLength(pTextBox))
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
* \brief Function to add a space.
*
* \param pTextBox       A pointer to the SDL_Textbox structure.
* \return None
*/
static void SDL_Textbox_AddSpace(SDL_Textbox *pTextBox)
{
    if ((pTextBox->iTextIndex + 1) <= SDL_Textbox_GetMaxTextLength(pTextBox))
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
static void SDL_Textbox_Delete(SDL_Textbox *pTextBox)
{
    pTextBox->iTextIndex--;
    if (pTextBox->iTextIndex < 0)
    {
        pTextBox->iTextIndex = 0;
    }
    *(pTextBox->szText + pTextBox->iTextIndex) = '\0';
}

/*!
* \brief Function to draw the textbox.
*
* \param pTextBox       A pointer to the SDL_Textbox structure.
* \return None
*/
void SDL_Textbox_Draw(SDL_Textbox *pTextBox)
{
    SDL_Color colorBox = { 255, 255, 255, 255 };

    SDL_Ctx_RenderFillRect(&pTextBox->rDest, &colorBox);
    SDL_Text_Set(pTextBox->pText, pTextBox->szText, pTextBox->pColorFont, 0);
    SDL_Text_Draw(pTextBox->pText);
    SDL_Textbox_DrawCursor(pTextBox);
}

/*!
* \brief Function to draw the cursor in the textbox.
*
* \param pTextBox       A pointer to the SDL_Textbox structure.
* \return None
*/
static void SDL_Textbox_DrawCursor(SDL_Textbox *pTextBox)
{
    SDL_Color colorCursor = { 0, 0, 0, 255 };
    SDL_Text cursor;
    if (SDL_Textbox_IsActive(pTextBox))
    {
        if (SDL_GetTicks() - pTextBox->iCursorTime >= 500)
        {
            SDL_Text_Init(&cursor, pTextBox->pFont, SDL_Textbox_GetCursorX(pTextBox), SDL_Textbox_GetCursorY(pTextBox));
            SDL_Text_Set (&cursor, "|", &colorCursor, 0);
            SDL_Text_Draw(&cursor);
            SDL_Text_Free(&cursor);
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
* \brief Function to return the length in pixel of the text.
*
* \param pTextBox       A pointer to the SDL_Textbox structure.
* \return size of the text as it is displayed.
*/
Sint32 SDL_Textbox_GetTextLength(const SDL_Textbox *pTextBox)
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
* \param pTextBox       A pointer to the SDL_Textbox structure.
* \return number of caracters allowed in the textbox.
*/
Uint16 SDL_Textbox_GetMaxTextLength(const SDL_Textbox *pTextBox)
{
    return pTextBox->iTextLength;
}

/*!
* \brief Function to return the max length of a text of a Textbox.
*
* \param pTextBox       A pointer to the SDL_Textbox structure.
* \return maximum size text in the text box for the choosen font.
*/
Uint32 SDL_Textbox_GetMaxBoxLength(const SDL_Textbox *pTextBox)
{
    return pTextBox->iBoxLength;
}

/*!
* \brief Function to set the active flag of the text box.
*
* \param pTextBox       A pointer to the SDL_Textbox structure.
* \return true if the box is active, false else
*/
static void SDL_Textbox_CheckActive(SDL_Textbox *pTextBox, const SDL_Input *pInput)
{
    if (UTIL_ContainPoint(&pInput->iMouse, &pTextBox->rDest))
    {
        SDL_SetCursor(pInput->pTxtCursor);
        if (!SDL_Textbox_IsActive(pTextBox))
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

/*!
* \brief Function to return the state of a Textbox.
*
* \param pTextBox       A pointer to the SDL_Textbox structure.
* \return true if the box is active, false else
*/
SDL_bool SDL_Textbox_IsActive(const SDL_Textbox *pTextBox)
{
    return pTextBox->bIsActive;
}

/*!
* \brief Function to return if a Textbox is full.
*
* \param pTextBox       A pointer to the SDL_Textbox structure.
* \return true if the box is full, false else
*/
SDL_bool SDL_Textbox_IsFull(const SDL_Textbox *pTextBox)
{
    return pTextBox->bIsFull;
}

/*!
* \brief Function to test if a Textbox is full.
*
* \param pTextBox       A pointer to the SDL_Textbox structure.
* \return None.
*/
static void SDL_Textbox_CheckSize(SDL_Textbox *pTextBox)
{
    if (pTextBox->iTextIndex == SDL_Textbox_GetMaxTextLength(pTextBox) ||
        (Uint32)SDL_Textbox_GetTextLength(pTextBox) >= SDL_Textbox_GetMaxBoxLength(pTextBox))
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
static SDL_bool SDL_Textbox_IsKeyLocked(const SDL_Textbox *pTextBox)
{
    return pTextBox->bIsLocked;
}

/*!
* \brief Function to test if key is locked.
*
* \param pTextBox       A pointer to the SDL_Textbox structure.
* \return None.
*/
static void SDL_Textbox_CheckLock(SDL_Textbox *pTextBox)
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
* \brief Function to return the x position of the cursor.
*
* \param pTextBox       A pointer to the SDL_Textbox structure.
* \return X position for the cursor
*/
static Sint32 SDL_Textbox_GetCursorX(const SDL_Textbox *pTextBox)
{
    Sint32 iX = pTextBox->sPointCursor.x;
    Sint32 iW = SDL_Textbox_GetTextLength(pTextBox);

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
static Sint32 SDL_Textbox_GetCursorY(const SDL_Textbox *pTextBox)
{
    return pTextBox->sPointCursor.y;
}

/*!
* \brief Function to return the current key in the text box.
*
* \param pTextBox       A pointer to the SDL_Textbox structure.
* \return an SDL_Keycode value of the current key
*/
static SDL_Keycode  SDL_Textbox_GetCurrent(const SDL_Textbox *pTextBox)
{
    return pTextBox->iCurrentKey;
}

/*!
* \brief Function to set the color of the text in the text box.
*
* \param pTextBox       A pointer to the SDL_Textbox structure.
* \param pColor         The pointer to the new color structure.
* \return None
*/
void SDL_Textbox_SetColor(SDL_Textbox *pTextBox, SDL_Color *pColor)
{
    pTextBox->pColorFont = pColor;
}

/*!
* \brief Function to free an SDL_Textbox.
*
* \param pTextBox       A pointer to the SDL_Textbox structure.
* \return None
*/
void SDL_Textbox_Free(SDL_Textbox *pTextBox)
{
    SDL_Text_Free(pTextBox->pText);
    UTIL_Free(pTextBox->pText);
    UTIL_Free(pTextBox->szText);
}
/* ========================================================================= */
