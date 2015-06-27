/* ========================================================================= */
/*!
 * \file    SDL_Sprite.c
 * \brief   File to handle the sprites.
 * \author  Nyuu / Orlyn / Red
 * \version 1.0
 * \date    09 June 2015
 */
/* ========================================================================= */
/* Author  | Date     | Comments                                             */
/* --------+----------+----------------------------------------------------- */
/* Nyuu    | 09/06/15 | Creation.                                            */
/* ========================================================================= */

#include "SDL_Util.h"
#include "SDL_Render.h"
#include "SDL_Sprite.h"

/* ========================================================================= */

/*!
 * \brief  Function to load a sprite.
 *
 * \param  szSprName Name of the sprite.
 * \return A pointer to the loaded sprite, or NULL if error.
 */
SDL_Sprite *SDL_Sprite_Alloc(const char *szSprName)
{
    SDL_RWops  *pSprRw    = NULL;
    SDL_Sprite *pSprite   = NULL;
    char       *szSprPath = NULL;
    SDL_Rect    rTextureSize;
    Uint32      iFrameWidth;
    Uint32      iFrameHeight;

    szSprPath = UTIL_StrBuild("sprites/", szSprName, ".spr", NULL);

    if (szSprPath)
    {
        pSprRw = UTIL_RWOpen(szSprPath, "rb");

        if (pSprRw)
        {
            pSprite = (SDL_Sprite *) UTIL_Malloc(sizeof(SDL_Sprite));

            if (pSprite)
            {
                /* ~~~ Read the data... ~~~ */
                SDL_RWread(pSprRw, &iFrameWidth,  sizeof( Sint32 ), 1);
                SDL_RWread(pSprRw, &iFrameHeight, sizeof( Sint32 ), 1);

                /* ~~~ Read the PNG... ~~~ */
                pSprite->pTexture = UTIL_TextureLoadRW(szSprPath, pSprRw, &rTextureSize);
                pSprite->szName   = UTIL_StrCopy(szSprName);

                if (!pSprite->pTexture || !pSprite->szName) // Error: must free...
                {
                    UTIL_Free(pSprite->szName);
                    UTIL_TextureFree(&pSprite->pTexture);
                    UTIL_Free(pSprite);
                }
                else
                {
                    if ((!iFrameWidth) || (!iFrameHeight))
                    {
                        iFrameWidth  = rTextureSize.w;
                        iFrameHeight = rTextureSize.h;
                    }

                    pSprite->iNbFrameW = rTextureSize.w / iFrameWidth;
                    pSprite->iNbFrameH = rTextureSize.h / iFrameHeight;
                    pSprite->iFrameMax = pSprite->iNbFrameW * pSprite->iNbFrameH;

                    pSprite->sFrameClip.x     = 0;
                    pSprite->sFrameClip.y     = 0;
                    pSprite->sFrameClip.w     = iFrameWidth;
                    pSprite->sFrameClip.h     = iFrameHeight;
                    pSprite->sFramePosition.x = 0;
                    pSprite->sFramePosition.y = 0;
                    pSprite->sFramePosition.w = iFrameWidth;
                    pSprite->sFramePosition.h = iFrameHeight;
                    pSprite->sFrameCenter.x   = (iFrameWidth >> 1);
                    pSprite->sFrameCenter.y   = (iFrameHeight >> 1);
                }
            }

            UTIL_RWClose(&pSprRw);
        }

        UTIL_Free(szSprPath);
    }

    return pSprite;
}

/*!
 * \brief  Function to get the name of a sprite.
 *
 * \param  pSprite Pointer to the sprite.
 * \return The name of the sprite.
 */
const char *SDL_Sprite_GetName(const SDL_Sprite *pSprite)
{
    return pSprite->szName;
}

/*!
 * \brief  Function to get the maximum frame of a sprite.
 *
 * \param  pSprite Pointer to the sprite.
 * \return The maximum frame of the sprite.
 */
Uint32 SDL_Sprite_GetFrameMax(const SDL_Sprite *pSprite)
{
    return pSprite->iFrameMax;
}

/*!
 * \brief  Function to get the frame size of a sprite.
 *
 * \param  pSprite Pointer to the sprite.
 * \param  pSize   Rectangle to retrieve the frame size.
 * \return None.
 */
void SDL_Sprite_GetFrameSize(const SDL_Sprite *pSprite, SDL_Rect *pSize)
{
    pSize->w = pSprite->sFrameClip.w;
    pSize->h = pSprite->sFrameClip.h;
}

/*!
 * \brief  Function to draw a sprite.
 *
 * \param  pSprite Pointer to the sprite.
 * \param  pPos    Pointer to a point to position the sprite.
 * \param  iFrame  Index of the frame of the sprite to draw.
 * \return None.
 */
void SDL_Sprite_Draw(SDL_Sprite *pSprite, const SDL_Point *pPos, Uint32 iFrame)
{
    if(iFrame < pSprite->iFrameMax)
    {
        pSprite->sFrameClip.x     = ((iFrame % pSprite->iNbFrameW) * pSprite->sFrameClip.w);
        pSprite->sFrameClip.y     = ((iFrame / pSprite->iNbFrameW) * pSprite->sFrameClip.h);
        pSprite->sFramePosition.x = pPos->x;
        pSprite->sFramePosition.y = pPos->y;

        SDL_Render_DrawTexture(pSprite->pTexture, &pSprite->sFrameClip, &pSprite->sFramePosition);
    }
}

/*!
 * \brief Function to draw a sprite.
 *
 * \param pSprite Pointer to the sprite.
 * \param pPos    Pointer to a point to position the sprite.
 * \param iFrame  Index of the frame of the sprite to draw.
 * \param dAngle  Angle to rotate the sprite.
 * \param iFlip   Flag to flip the sprite.
 * \return None.
 */
void SDL_Sprite_DrawEx(SDL_Sprite *pSprite, const SDL_Point *pPos, Uint32 iFrame, double dAngle, SDL_RendererFlip iFlip)
{
    if(iFrame < pSprite->iFrameMax)
    {
        pSprite->sFrameClip.x     = ((iFrame % pSprite->iNbFrameW) * pSprite->sFrameClip.w);
        pSprite->sFrameClip.y     = ((iFrame / pSprite->iNbFrameW) * pSprite->sFrameClip.h);
        pSprite->sFramePosition.x = pPos->x;
        pSprite->sFramePosition.y = pPos->y;

        SDL_Render_DrawTextureEx(pSprite->pTexture, &pSprite->sFrameClip, &pSprite->sFramePosition, dAngle, &pSprite->sFrameCenter, iFlip);
    }
}

/*!
 * \brief  Function to free the sprite.
 *
 * \param  ppSprite Pointer to pointer to a sprite.
 * \return None.
 */
void SDL_Sprite_Free(SDL_Sprite **ppSprite)
{
    UTIL_Free((*ppSprite)->szName);
    UTIL_TextureFree(&(*ppSprite)->pTexture);
    UTIL_Free(*ppSprite);
}

/* ========================================================================= */
