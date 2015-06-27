/* ========================================================================= */
/*!
 * \file    HUI_Text.c
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

#include "HUI_Text.h"

/* ========================================================================= */

/*!
 * \brief Function to initialize a text.
 *
 * \param pText  Pointer to the text.
 * \param pFont  Pointer to the font to use.
 * \param pColor Pointer to the desired color of the text.
 * \param x      Text position on x.
 * \param y      Text position on y.
 * \return None.
 */
void HUI_Text_Init(HUI_Text *pText, TTF_Font *pFont, const SDL_Color *pColor, Sint32 x, Sint32 y)
{
    pText->pFont    = pFont;
    pText->pTexture = NULL;
    pText->rDest.x  = x;
    pText->rDest.y  = y;
    pText->rDest.w  = 0;
    pText->rDest.h = 0;
    pText->sColor.r = pColor->r;
    pText->sColor.g = pColor->g;
    pText->sColor.b = pColor->b;
    pText->sColor.a = pColor->a;
}

/*!
 * \brief Function to set a text.
 *
 * \param pText  Pointer to the text.
 * \param szText String to use for the text.
 * \param iMaxW  Maximum width for a line of the text, 0 will do return every '\n'.
 * \return None.
 */
void HUI_Text_SetText(HUI_Text *pText, const char *szText, Sint32 iMaxW)
{
    SDL_Surface *pSurface = NULL;
    Sint32       iW       = 0;

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
            pSurface = TTF_RenderText_Blended_Wrapped(pText->pFont, " ", pText->sColor, iW);
        }
        else
        {
            pSurface = TTF_RenderText_Blended_Wrapped(pText->pFont, szText, pText->sColor, iW);
        }

        if (pSurface == NULL)
        {
            COM_Log_Print(COM_LOG_CRITICAL, "Unable to create a surface for the text \"%s\" !", szText);
        }
        else
        {
            UTIL_TextureFree(&pText->pTexture);
            pText->pTexture = SDL_Render_CreateTextureFromSurface(pSurface);

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
void HUI_Text_Draw(HUI_Text* pText)
{
    SDL_Render_DrawTexture(pText->pTexture, NULL, &pText->rDest);
}

/*!
 * \brief Function to move a text to a new location.
 *
 * \param pText Pointer to the text.
 * \param x     New position on x.
 * \param y     New position on y.
 * \return None.
 */
void HUI_Text_SetPosition(HUI_Text *pText, Sint32 x, Sint32 y)
{
    pText->rDest.x = x;
    pText->rDest.y = y;
}

/*!
 * \brief Function to center a text around a point.
 *
 * \param pText Pointer to the text.
 * \param cx    Center position on x.
 * \param cy    Center position on y.
 * \return None.
 */
void HUI_Text_Center(HUI_Text *pText, Sint32 cx, Sint32 cy)
{
    pText->rDest.x = (cx - (pText->rDest.w >> 1));
    pText->rDest.y = (cy - (pText->rDest.h >> 1));
}

/*!
 * \brief Function to free a text.
 *
 * \param pText Pointer to the text.
 * \return None.
 */
void HUI_Text_Free(HUI_Text *pText)
{
    UTIL_TextureFree(&pText->pTexture);
}

/*!
* \brief Function to set the color of the text
*
* \param pText  Pointer to the text.
* \param pColor Pointer to the desired color of the text.
* \return None.
*/
void HUI_Text_SetColor(HUI_Text *pText, const SDL_Color *pColor)
{
    pText->sColor.r = pColor->r;
    pText->sColor.g = pColor->g;
    pText->sColor.b = pColor->b;
    pText->sColor.a = pColor->a;
}
/* ========================================================================= */
