/* ========================================================================= */
/*!
 * \file    SDL_Text.c
 * \brief   File to handle the texts.
 * \author  Nyuu / Orlyn / Red
 * \version 1.0
 * \date    09 June 2015
 */
/* ========================================================================= */
/* Author  | Date     | Comments                                             */
/* --------+----------+----------------------------------------------------- */
/* Nyuu    | 09/06/15 | Creation.                                            */
/* Orlyn   | 13/06/15 | Add SDL_Text functions.                              */
/* ========================================================================= */

#include "SDL_Text.h"

/* ========================================================================= */

/*!
* \brief Function to initialize position and font of an SDL_Text structure.
*
* \param pText       A pointer to the SDL_Text structure.
* \param pFont       A pointer to the font to use.
* \param x           X location to positionnate the text.
* \param y           Y location to positionnate the text.
* \return None
*/
void SDL_Text_Init(SDL_Text *pText, TTF_Font *pFont, Sint32 x, Sint32 y)
{
    pText->pFont = pFont;
    pText->pTexture = NULL;
    pText->rDestText.x = x;
    pText->rDestText.y = y;
    pText->rDestText.w = 0;
    pText->rDestText.h = 0;
}

/*!
* \brief Function to set the texture of an SDL_Text structure.
*
* \param pText       Pointer to the SDL_Text structure.
* \param szText      The text to fill the texture with.
* \param pColorFont  A pointer to the desired color of the text.
* \return None.
*/
void SDL_Text_Set(SDL_Text *pText, const char *szText, SDL_Color *pColorFont)
{
    SDL_Surface* textSurface = NULL;
    Sint32 iW = 0;
    if (szText)
    {
        TTF_SizeText(pText->pFont, szText, &iW, NULL);
        textSurface = TTF_RenderText_Blended_Wrapped(pText->pFont, szText, *pColorFont, iW);
        if (textSurface == NULL)
        {
            COM_Log_Print(COM_LOG_CRITICAL, "Unable to load surface for the text %s.", szText);
        }
        else
        {
            SDL_Text_Free(pText);
            pText->pTexture = SDL_Ctx_CreateTextureFromSurface(textSurface);
            if (pText->pTexture == NULL)
            {
                COM_Log_Print(COM_LOG_CRITICAL, "Unable to load texture for the text %s.", szText);
            }
            pText->rDestText.w = textSurface->w;
            pText->rDestText.h = textSurface->h;
            SDL_FreeSurface(textSurface);
            textSurface = NULL;
        }
    }
}

/*!
* \brief Function to draw a text.
*
* \param pText       Pointer to the SDL_Text structure.
* \return None.
*/
void SDL_Text_Draw(SDL_Text* pText)
{
    SDL_Ctx_RenderCopy(pText->pTexture, NULL, &pText->rDestText);
}

/*!
* \brief Function to move the text to new location.
*
* \param pText       Pointer to the SDL_Text structure.
* \param x           X location to move the text to.
* \param y           Y location to move the text to.
* \return None.
*/
void SDL_Text_Move(SDL_Text *pText, Sint32 x, Sint32 y)
{
    pText->rDestText.x = x;
    pText->rDestText.y = y;
}

/*!
* \brief Function to center the text around a point.
*
* \param pText       Pointer to the SDL_Text structure.
* \param cx          X location to center the text on.
* \param cy          Y location to center the text on.
* \return None.
*/
void SDL_Text_Center(SDL_Text *pText, Sint32 x, Sint32 y)
{
    pText->rDestText.x = x - pText->rDestText.w / 2;
    pText->rDestText.y = y - pText->rDestText.h / 2;
}

/*!
* \brief Function to free the texture of an SDL_Text.
*
* \param pText       Pointer to the SDL_Text structure.
* \return None.
*/
void SDL_Text_Free(SDL_Text *pText)
{
    if (pText->pTexture)
    {
        SDL_DestroyTexture(pText->pTexture);
        pText->pTexture = NULL;
    }
}
/* ========================================================================= */
