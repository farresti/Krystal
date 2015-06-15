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
/* ========================================================================= */

#include "SDL_Textbox.h"

/* ========================================================================= */

void SDL_Textbox_Init(SDL_Textbox *pTextBox, TTF_Font *pFont, SDL_Color *pColorFont, Sint32 x, Sint32 y)
{
    pTextBox->szText = NULL;
    pTextBox->bIsActive = SDL_FALSE;
    pTextBox->bIsFull = SDL_FALSE;
    pTextBox->currentLetter = pTextBox->precedentLetter = '\0';
    SDL_Textbox_SetText(pTextBox, "");
    pTextBox->pText = (SDL_Text*)malloc(sizeof(SDL_Text));
    SDL_Text_Init(pTextBox->pText, pFont, x, y);
    SDL_Text_Set(pTextBox->pText, pTextBox->szText, pColorFont);
    pTextBox->iLastTime = SDL_GetTicks();
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
    TTF_SizeText(pTextBox->pText->pFont, szText, &iW, NULL);
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
/*void SDL_Textbox_UpdateBox(SDL_Textbox *pTextBox)
{

}*/

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
    return pTextBox->bIsFull;
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
