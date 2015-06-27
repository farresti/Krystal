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

                    pSprite->iFrameWidth  = iFrameWidth;
                    pSprite->iFrameHeight = iFrameHeight;
                    pSprite->iNbFrameL    = rTextureSize.w / iFrameWidth;
                    pSprite->iNbFrameH    = rTextureSize.h / iFrameHeight;
                    pSprite->iFrameMax    = pSprite->iNbFrameL * pSprite->iNbFrameH;
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
    pSize->w = pSprite->iFrameWidth;
    pSize->h = pSprite->iFrameHeight;
}

/*!
 * \brief  Function to get the position of a frame.
 *
 * \param  pSprite Pointer to the sprite.
 * \param  iFrame  Index of the frame to get the position.
 * \param  pPos    Pointer to a rectangle to get the frame position.
 * \return None.
 */
void SDL_Sprite_GetFramePosition(const SDL_Sprite *pSprite, Uint32 iFrame, SDL_Rect *pPos)
{
    pPos->x = (iFrame % pSprite->iNbFrameL) * pSprite->iFrameWidth;
    pPos->y = (iFrame / pSprite->iNbFrameL) * pSprite->iFrameHeight;
}

/*!
 * \brief  Function to draw a sprite.
 *
 * \param  pSprite Pointer to the sprite.
 * \param  pClip   Pointer to a rectangle to clip the sprite.
 * \param  pPos    Pointer to a rectangle to position the sprite.
 * \return None.
 */
void SDL_Sprite_Draw(SDL_Sprite *pSprite, const SDL_Rect *pClip, const SDL_Rect *pPos)
{
    SDL_Render_DrawTexture(pSprite->pTexture, pClip, pPos);
}

/*!
 * \brief Function to draw a sprite.
 *
 * \param pSprite Pointer to the sprite.
 * \param pClip   Pointer to a rectangle to clip the sprite.
 * \param pPos    Pointer to a rectangle to position the sprite.
 * \param dAngle  Angle to rotate the sprite.
 * \param pCenter Pointer to the center of the rotation.
 * \param iFlip   Flag to flip the sprite.
 * \return None.
 */
void SDL_Sprite_DrawEx(SDL_Sprite *pSprite, const SDL_Rect *pClip, const SDL_Rect *pPos, double dAngle, const SDL_Point *pCenter, SDL_RendererFlip iFlip)
{
    SDL_Render_DrawTextureEx(pSprite->pTexture, pClip, pPos, dAngle, pCenter, iFlip);
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
