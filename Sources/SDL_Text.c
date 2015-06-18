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

#include "SDL_Context.h"
#include "SDL_Util.h"
#include "SDL_Text.h"

/* ========================================================================= */

/*!
 * \brief Function to initialize a text.
 *
 * \param pText Pointer to the text.
 * \param pFont Pointer to the font to use.
 * \param x     Text position on x.
 * \param y     Text position on y.
 * \return None.
 */
void SDL_Text_Init(SDL_Text *pText, TTF_Font *pFont, Sint32 x, Sint32 y)
{
    pText->pFont = pFont;
    pText->pTexture = NULL;
    pText->rDest.x = x;
    pText->rDest.y = y;
    pText->rDest.w = 0;
    pText->rDest.h = 0;
}

/*!
 * \brief Function to set a text.
 *
 * \param pText      Pointer to the text.
 * \param szText     String to use for the text.
 * \param pColorFont Pointer to the desired color of the text.
 * \param iMaxW      Maximum width for a line of the text, 0 will do return every '\n'.
 * \return None.
 */
void SDL_Text_Set(SDL_Text *pText, const char *szText, SDL_Color *pColorFont, Sint32 iMaxW)
{
    SDL_Surface *pSurface = NULL;
    Sint32       iW = 0;

    if (szText)
    {
        if (!iMaxW)
        {
            TTF_SizeText(pText->pFont, szText, &iW, NULL);
        }
        else
        {
            iW = iMaxW;
        }
        if (iW == 0)
        {
            pSurface = TTF_RenderText_Blended_Wrapped(pText->pFont, " ", *pColorFont, iW);
        }
        else
        {
            pSurface = TTF_RenderText_Blended_Wrapped(pText->pFont, szText, *pColorFont, iW);
        }
        if (pSurface == NULL)
        {
            COM_Log_Print(COM_LOG_CRITICAL, "Unable to create a surface for the text \"%s\" !", szText);
        }
        else
        {
            UTIL_TextureFree(&pText->pTexture);
            pText->pTexture = SDL_Ctx_CreateTextureFromSurface(pSurface);

            if (pText->pTexture == NULL)
            {
                COM_Log_Print(COM_LOG_CRITICAL, "Unable to create a texture for the text \"%s\" !", szText);
            }

            pText->rDest.w = pSurface->w;
            pText->rDest.h = pSurface->h;

            SDL_FreeSurface(pSurface);
        }
    }
}

/*!
 * \brief Function to draw a text.
 *
 * \param pText Pointer to the text.
 * \return None.
 */
void SDL_Text_Draw(SDL_Text* pText)
{
    SDL_Ctx_RenderCopy(pText->pTexture, NULL, &pText->rDest);
}

/*!
 * \brief Function to move a text to a new location.
 *
 * \param pText Pointer to the text.
 * \param x     New text position on x.
 * \param y     New text position on y.
 * \return None.
 */
void SDL_Text_Move(SDL_Text *pText, Sint32 x, Sint32 y)
{
    pText->rDest.x = x;
    pText->rDest.y = y;
}

/*!
 * \brief Function to center a text around a point.
 *
 * \param pText Pointer to the text.
 * \param cx    Point position on x.
 * \param cy    Point position on y.
 * \return None.
 */
void SDL_Text_Center(SDL_Text *pText, Sint32 cx, Sint32 cy)
{
    pText->rDest.x = cx - pText->rDest.w / 2;
    pText->rDest.y = cy - pText->rDest.h / 2;
}

/*!
 * \brief Function to free a text.
 *
 * \param pText Pointer to the text.
 * \return None.
 */
void SDL_Text_Free(SDL_Text *pText)
{
    UTIL_TextureFree(&pText->pTexture);
}

/* ========================================================================= */
