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
#include "SDL_Context.h"
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
    SDL_RWops  *pSprRw       = NULL;
    SDL_Sprite *pSprite      = NULL;
    char       *szSprPath    = NULL;
    Uint32      iFrameWidth  = 0;
    Uint32      iFrameHeight = 0;

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
                pSprite->pTexture = UTIL_TextureLoadRW(szSprPath, pSprRw, &pSprite->rTexture);
                pSprite->szName   = UTIL_StrCopy(szSprName);

                if (!pSprite->pTexture || !pSprite->szName) // Error: must free...
                {
                    UTIL_Free(pSprite->szName);
                    UTIL_TextureFree(&pSprite->pTexture);
                    UTIL_Free(pSprite);
                }
                else
                {
                    pSprite->rTexture.x = 0;
                    pSprite->rTexture.y = 0;

                    pSprite->iFrameWidth  = iFrameWidth;
                    pSprite->iFrameHeight = iFrameHeight;
                    pSprite->iNbFrameL    = pSprite->rTexture.w / iFrameWidth;
                    pSprite->iNbFrameH    = pSprite->rTexture.h / iFrameHeight;
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
 * \param  pSrc    Rectangle to retrieve the frame size.
 * \return None.
 */
void SDL_Sprite_GetFrameSize(const SDL_Sprite *pSprite, SDL_Rect *pSrc)
{
    pSrc->w = pSprite->iFrameWidth;
    pSrc->h = pSprite->iFrameHeight;
}

/*!
 * \brief  Function to get the origin of a frame.
 *
 * \param  pSprite Pointer to the sprite.
 * \param  iFrame  Frame to clip.
 * \param  pSrc    Rectangle to retrieve the frame clip.
 * \return None.
 */
void SDL_Sprite_GetFrameOrigin(const SDL_Sprite *pSprite, Uint32 iFrame, SDL_Rect *pSrc)
{
    pSrc->x = ( iFrame % pSprite->iNbFrameL ) * pSprite->iFrameWidth;
    pSrc->y = ( iFrame / pSprite->iNbFrameL ) * pSprite->iFrameHeight;
}

/*!
 * \brief  Function to draw a sprite.
 *
 * \param  pSprite Pointer to the sprite.
 * \param  pDest   Rectangle to position the sprite.
 * \param  pSrc    Rectangle to clip the sprite.
 * \param  iFlip   Flag to flip the sprite.
 * \return None.
 */
void SDL_Sprite_Draw(SDL_Sprite *pSprite, SDL_Rect *pSrc, SDL_Rect *pDest, SDL_RendererFlip iFlip)
{
    SDL_Ctx_RenderCopyEx(pSprite->pTexture, pSrc, pDest, iFlip);
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
    UTIL_TextureFree(&( *ppSprite )->pTexture);
    UTIL_Free(*ppSprite);
}

/* ========================================================================= */
