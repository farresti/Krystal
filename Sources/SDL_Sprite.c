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
    FILE       *pSprFile  = NULL;
    SDL_RWops  *pSprRwPng = NULL;
    SDL_Sprite *pSprite   = NULL;
    char       *szSprPath = NULL;
    size_t      iFileSize = 0;
    size_t      iPngSize  = 0;
    Uint8      *pSprPng   = NULL;

    SDL_Rect    sFrameSize;
    SDL_Point   sFrameCenter;

    szSprPath = UTIL_StrBuild("sprites/", szSprName, ".spr", NULL);

    if (szSprPath)
    {
        pSprFile = UTIL_Fopen(szSprPath, "rb");

        if (pSprFile)
        {
            /* ~~~ Get the file size... ~~~ */
            fseek(pSprFile, 0, SEEK_END);
            iFileSize = ftell(pSprFile);
            rewind(pSprFile);

            /* ~~~ Read the data... ~~~ */
            fread(&sFrameSize.w,   sizeof( Sint32 ), 1, pSprFile);
            fread(&sFrameSize.h,   sizeof( Sint32 ), 1, pSprFile);
            fread(&sFrameCenter.x, sizeof( Sint32 ), 1, pSprFile);
            fread(&sFrameCenter.y, sizeof( Sint32 ), 1, pSprFile);

            /* ~~~ Read the PNG... ~~~ */
            iPngSize = iFileSize - ( sizeof( Sint32 ) * 4 );
            pSprPng  = ( Uint8 * ) UTIL_Malloc( iPngSize );

            if (pSprPng)
            {
                fread(pSprPng, sizeof( Uint8 ), iPngSize, pSprFile);
                pSprRwPng = SDL_RWFromMem(pSprPng, iPngSize);

                if (pSprRwPng)
                {
                    pSprite = (SDL_Sprite *) UTIL_Malloc( sizeof( SDL_Sprite ));

                    if (pSprite)
                    {
                        pSprite->pTexture = UTIL_TextureLoadRW(szSprPath, pSprRwPng, &pSprite->rTexture);
                        pSprite->szName   = UTIL_StrCopy(szSprName);

                        if (!pSprite->pTexture || !pSprite->szName) // Error: must free...
                        {
                            UTIL_Free( &pSprite->szName );
                            UTIL_TextureFree( &pSprite->pTexture );
                            UTIL_Free( &pSprite );
                        }
                        else
                        {
                            pSprite->rSrc.x = 0;
                            pSprite->rSrc.y = 0;
                            pSprite->rSrc.w = sFrameSize.w;
                            pSprite->rSrc.h = sFrameSize.h;

                            pSprite->rDest.x = 0;
                            pSprite->rDest.y = 0;
                            pSprite->rDest.w = sFrameSize.w;
                            pSprite->rDest.h = sFrameSize.h;

                            pSprite->sFrameCenter.x = sFrameCenter.x;
                            pSprite->sFrameCenter.y = sFrameCenter.y;

                            pSprite->iNbFrameL = pSprite->rTexture.w / sFrameSize.w;
                            pSprite->iNbFrameH = pSprite->rTexture.h / sFrameSize.h;

                            pSprite->iMaxFrame = pSprite->iNbFrameL * pSprite->iNbFrameH;
                        }
                    }

                    SDL_FreeRW(pSprRwPng);
                }

                UTIL_Free(&pSprPng);
            }

            UTIL_Fclose(&pSprFile);
        }

        UTIL_Free(&szSprPath);
    }

    return pSprite;
}

/*!
 * \brief  Function to set a frame for a sprite.
 *
 * \param  pSprite Pointer to a sprite.
 * \param  iFrame  Number of the frame to set.
 * \return None.
 */
void SDL_Sprite_SetFrame(SDL_Sprite *pSprite, Uint32 iFrame)
{
    if (iFrame < pSprite->iMaxFrame)
    {
        pSprite->rSrc.x = ( iFrame % pSprite->iNbFrameL ) * pSprite->rSrc.w;
        pSprite->rSrc.y = ( iFrame / pSprite->iNbFrameL ) * pSprite->rSrc.h;
    }
}

/*!
 * \brief  Function to get the maximum frame of a sprite.
 *
 * \param  pSprite Pointer to a sprite.
 * \return The maximum frame of a sprite.
 */
Uint32 SDL_Sprite_GetMaxFrame(SDL_Sprite *pSprite)
{
    return pSprite->iMaxFrame;
}

/*!
 * \brief  Function to get the frame size of a sprite.
 *
 * \param  pSprite    Pointer to a sprite.
 * \param  pFrameSize Rectangle to retrieve the frame size.
 * \return None.
 */
void SDL_Sprite_GetFrameSize(SDL_Sprite *pSprite, SDL_Rect *pFrameSize)
{
    pFrameSize->w = pSprite->rSrc.w;
    pFrameSize->h = pSprite->rSrc.h;
}

/*!
 * \brief  Function to draw a sprite.
 *
 * \param  pSprite Pointer to a sprite.
 * \param  pDest   Rectangle to position the sprite.
 * \param  dAngle  Angle to rotate the sprite.
 * \param  iFlip   Flag to flip the sprite.
 * \return None.
 */
void SDL_Sprite_Draw(SDL_Sprite *pSprite, SDL_Rect *pDest, double dAngle, SDL_RendererFlip iFlip)
{
    pSprite->rDest.x = pDest->x;
    pSprite->rDest.y = pDest->y;
    
    SDL_Ctx_RenderCopyEx(pSprite->pTexture, &pSprite->rSrc, &pSprite->rDest, dAngle, &pSprite->sFrameCenter, iFlip);
}

/*!
 * \brief  Function to free a sprite.
 *
 * \param  ppSprite Pointer to pointer to a sprite.
 * \return None.
 */
void SDL_Sprite_Free(SDL_Sprite **ppSprite)
{
    UTIL_Free( &( *ppSprite )->szName );
    UTIL_TextureFree( &( *ppSprite )->pTexture );
    UTIL_Free( ppSprite );
}

/* ========================================================================= */
