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
/* ========================================================================= */

#include "SDL_Textbox.h"

/* ========================================================================= */

void SDL_Textbox_Init(SDL_Textbox *pTextBox, TTF_Font *pFont, SDL_Color *pColorFont,
    Sint32 x, Sint32 y, Sint32 w, Sint32 h)
{
    Sint32 iW = 0, iH = 0;
    TTF_SizeText(pFont, " ", &iW, NULL);
    TTF_SizeText(pFont, "|", NULL, &iH);
    if (iH > h || iW > w)
    {
        COM_Log_Print(COM_LOG_ERROR, "Not enough space for text in the texbox.");
        return;
    }
    /*Init flags*/
    pTextBox->bIsActive = SDL_FALSE;
    pTextBox->bIsFull = SDL_FALSE;
    pTextBox->bIsLocked = SDL_FALSE;
    /*Init text input*/
    pTextBox->szText = NULL;
    pTextBox->currentLetter = pTextBox->precedentLetter = '\0';
    SDL_Textbox_SetText(pTextBox, "\0");
    /*Init for cursor*/
    pTextBox->pFont = pFont;
    pTextBox->offsetCursor.x = x + iW;
    pTextBox->offsetCursor.y = y + h / 2 - iH / 2;
    /*Init structure SDL_Text*/
    pTextBox->pText = (SDL_Text*)malloc(sizeof(SDL_Text));
    SDL_Text_Init(pTextBox->pText, pTextBox->pFont, pTextBox->offsetCursor.x, pTextBox->offsetCursor.y);
    SDL_Text_Set(pTextBox->pText, pTextBox->szText, pColorFont);
    /*Init time*/
    pTextBox->iLastTime = SDL_GetTicks();
    /*Init rect*/
    pTextBox->rDest.x = x;
    pTextBox->rDest.y = y;
    pTextBox->rDest.w = w;
    pTextBox->rDest.h = h;
    /*Init max length*/
    pTextBox->iMaxLength = w - 2 * iW;
    /*Init colors*/
    pTextBox->pColorFont = pColorFont;

    SDL_Textbox_Draw(pTextBox);
}

/*!
* \brief Function to set text in the text box.
*
* \param pTextBox       A pointer to the SDL_Textbox structure.
* \param szText         The text to set.
* \return None
*/
void SDL_Textbox_SetText(SDL_Textbox *pTextBox, const char *szText)
{
    Sint32 iW = 0;
    if (strlen(szText) > 1)
    {
        TTF_SizeText(pTextBox->pText->pFont, szText, &iW, NULL);
    }
    if ((Uint32)(iW) <= SDL_Textbox_GetMaxLength(pTextBox))
    {
        if (pTextBox->szText)
        {
            UTIL_Free(&pTextBox->szText);
        }
        pTextBox->szText = UTIL_StrCopy(szText);
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
    SDL_Keycode lastKey = SDL_Input_GetLastKey(pInput);
    if (SDL_Textbox_IsActive(pTextBox))
    {
        if (SDL_Input_IsKeyPressed(pInput, lastKey))
        {
            if ((pInput->lastKey > SDLK_SPACE && pInput->lastKey <= SDLK_z) ||
                (pInput->lastKey >= SDLK_KP_DIVIDE && pInput->lastKey <= SDLK_KP_PERIOD))
            {
                pTextBox->currentLetter = lastKey;
                if (!SDL_Textbox_IsFull(pTextBox))
                {
                    if (pTextBox->currentLetter != pTextBox->precedentLetter ||
                        SDL_Textbox_IsLocked(pTextBox))
                    {
                        SDL_Textbox_AddLetter(pTextBox);
                        pTextBox->precedentLetter = pTextBox->currentLetter;
                        pTextBox->iLastTime = SDL_GetTicks();
                    }
                }
            }
            else if (pInput->lastKey == SDLK_BACKSPACE)
            {
                if (SDL_Textbox_GetLength(pTextBox) > 0)
                {
                    SDL_Textbox_DeleteLetter(pTextBox);
                }
            }
            else if (pInput->lastKey == SDLK_SPACE)
            {
                SDL_Textbox_AddSpace(pTextBox);
            }
            else if (pInput->lastKey == SDLK_RETURN)
            {
                pTextBox->bIsActive = SDL_FALSE;
            }
            SDL_Input_ResetKey(pInput, lastKey);
        }
    }
    SDL_Textbox_SetActive(pTextBox, pInput);
    SDL_Textbox_Draw(pTextBox);
}

/*!
* \brief Function to add a letter.
*
* \param pTextBox       A pointer to the SDL_Textbox structure.
* \return None
*/
void SDL_Textbox_AddLetter(SDL_Textbox *pTextBox)
{
    char *szTemp = NULL;
    char *key = (char*)SDL_GetKeyName(pTextBox->currentLetter);
    SDL_Keymod keyMod = SDL_GetModState();
    if (pTextBox->currentLetter != '\0')
    {
        if (strlen(key) == 1)
        {
            if (!(keyMod & KMOD_SHIFT))
            {
                key = strlwr(key);
            }
            szTemp = UTIL_StrBuild(pTextBox->szText, key, NULL);
        }
        else
        {
            szTemp = UTIL_StrBuild(pTextBox->szText, key + strlen(key) - 1, NULL);
        }
        if (szTemp)
        {
            SDL_Textbox_SetText(pTextBox, szTemp);
            UTIL_Free(&szTemp);
        }
    }

}

/*!
* \brief Function to add a space.
*
* \param pTextBox       A pointer to the SDL_Textbox structure.
* \return None
*/
void SDL_Textbox_AddSpace(SDL_Textbox *pTextBox)
{
    const char *space = " ";
    char       *szTemp = NULL;
    szTemp = UTIL_StrBuild(pTextBox->szText, space, NULL);
    if (szTemp)
    {
        SDL_Textbox_SetText(pTextBox, szTemp);
        UTIL_Free(&szTemp);
    }
}

/*!
* \brief Function to delete a letter.
*
* \param pTextBox       A pointer to the SDL_Textbox structure.
* \return None
*/
void SDL_Textbox_DeleteLetter(SDL_Textbox *pTextBox)
{
    Uint32 iLen = strlen(pTextBox->szText);
    char *szTemp = NULL;
    szTemp = UTIL_StrCopy(pTextBox->szText);
    if (szTemp)
    {
        szTemp[iLen - 1] = '\0';
        SDL_Textbox_SetText(pTextBox, szTemp);
        UTIL_Free(&szTemp);
    }
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
    SDL_Text_Set(pTextBox->pText, pTextBox->szText, pTextBox->pColorFont);
    SDL_Text_Draw(pTextBox->pText);
    SDL_Textbox_DrawCursor(pTextBox);
}

/*!
* \brief Function to draw the cursor in the textbox.
*
* \param pTextBox       A pointer to the SDL_Textbox structure.
* \return None
*/
void SDL_Textbox_DrawCursor(SDL_Textbox *pTextBox)
{
    SDL_Color colorCursor = { 0, 0, 0, 255 };
    SDL_Text text;
    if (SDL_Textbox_IsActive(pTextBox))
    {
        if (SDL_GetTicks() - pTextBox->iCursorTime >= 500)
        {
            SDL_Text_Init(&text, pTextBox->pFont, SDL_Textbox_GetCursorX(pTextBox), SDL_Textbox_GetCursorY(pTextBox));
            SDL_Text_Set(&text, "|", &colorCursor);
            SDL_Text_Draw(&text);
            SDL_Text_Free(&text);
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
* \brief Function to return the state of a Textbox.
*
* \param pTextBox       A pointer to the SDL_Textbox structure.
* \return size of the text as it is displayed.
*/
Sint32 SDL_Textbox_GetLength(SDL_Textbox *pTextBox)
{
    Sint32 iW = 0;
    TTF_SizeText(pTextBox->pText->pFont, pTextBox->szText, &iW, NULL);
    return iW;
}

/*!
* \brief Function to return the max length of a text of a Textbox.
*
* \param pTextBox       A pointer to the SDL_Textbox structure.
* \return maximum size text in the text box for the choosen font.
*/
Uint32 SDL_Textbox_GetMaxLength(SDL_Textbox *pTextBox)
{
    return pTextBox->iMaxLength;
}

/*!
* \brief Function to set the active flag of the text box.
*
* \param pTextBox       A pointer to the SDL_Textbox structure.
* \return true if the box is active, false else
*/
void SDL_Textbox_SetActive(SDL_Textbox *pTextBox, SDL_Input *pInput)
{
    if (UTIL_ContainPoint(pInput->iMouseX, pInput->iMouseY, &pTextBox->rDest))
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
SDL_bool SDL_Textbox_IsActive(SDL_Textbox *pTextBox)
{
    return pTextBox->bIsActive;
}

/*!
* \brief Function to return if a Textbox is full.
*
* \param pTextBox       A pointer to the SDL_Textbox structure.
* \return true if the box is full, false else
*/
SDL_bool SDL_Textbox_IsFull(SDL_Textbox *pTextBox)
{
    if ((Uint32)(SDL_Textbox_GetLength(pTextBox)) > pTextBox->iMaxLength)
    {
        pTextBox->bIsFull = SDL_TRUE;
    }
    else
    {
        pTextBox->bIsFull = SDL_FALSE;
    }
    return pTextBox->bIsFull;
}

/*!
* \brief Function to return if a key is locked.
*
* \param pTextBox       A pointer to the SDL_Textbox structure.
* \return true if a key is locked, false else
*/
SDL_bool SDL_Textbox_IsLocked(SDL_Textbox *pTextBox)
{
    if (pTextBox->currentLetter == pTextBox->precedentLetter)
    {
        if (SDL_GetTicks() - pTextBox->iLastTime >= 200)
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
    return pTextBox->bIsLocked;
}

/*!
* \brief Function to return the x position of the cursor.
*
* \param pTextBox       A pointer to the SDL_Textbox structure.
* \return true if a key is locked, false else
*/
Sint32 SDL_Textbox_GetCursorX(SDL_Textbox *pTextBox)
{
    Sint32 iX = pTextBox->offsetCursor.x, iW = 0;
    iW = SDL_Textbox_GetLength(pTextBox);
    if (iW != 0)
    {
        iX = pTextBox->rDest.x;
    }
    iX += iW;
    return iX;
}

/*!
* \brief Function to return the y position of the cursor.
*
* \param pTextBox       A pointer to the SDL_Textbox structure.
* \return true if a key is locked, false else
*/
Sint32 SDL_Textbox_GetCursorY(SDL_Textbox *pTextBox)
{
    return pTextBox->offsetCursor.y;
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
    UTIL_Free(&pTextBox->pText);
    UTIL_Free(&pTextBox->szText);
}
/* ========================================================================= */
