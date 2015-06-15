/* ========================================================================= */
/*!
 * \file    SDL_Sprite.h
 * \brief   File to interface with the sprites.
 * \author  Nyuu / Orlyn / Red
 * \version 1.0
 * \date    09 June 2015
 */
/* ========================================================================= */
/* Author  | Date     | Comments                                             */
/* --------+----------+----------------------------------------------------- */
/* Nyuu    | 09/06/15 | Creation.                                            */
/* ========================================================================= */

#ifndef __SDL_SPRITE_H__
#define __SDL_SPRITE_H__

    #include "SDL_Shared.h"
    
    /*!
     * \struct SDL_Sprite
     * \brief  Structure to handle a sprite.
     */
    typedef struct
    {
        char        *szName;       /*!< Name of the sprite */

        SDL_Texture *pTexture;     /*!< Pointer to the texture */
        SDL_Rect     rTexture;     /*!< Size of the texture */

        SDL_Rect     rSrc;         /*!< Rectangle to clip the texture */
        SDL_Rect     rDest;        /*!< Rectangle to position the texture */

        SDL_Point    sFrameCenter; /*!< Center of each frame */
        Uint32       iNbFrameL;    /*!< Number of frame (Width) */
        Uint32       iNbFrameH;    /*!< Number of frame (Height) */
        Uint32       iMaxFrame;    /*!< Maximum frame */
    } SDL_Sprite;

    SDL_Sprite *SDL_Sprite_Alloc(const char *szSprName);
    void        SDL_Sprite_SetFrame(SDL_Sprite *pSprite, Uint32 iFrame);
    Uint32      SDL_Sprite_GetMaxFrame(SDL_Sprite *pSprite);
    void        SDL_Sprite_GetFrameSize(SDL_Sprite *pSprite, SDL_Rect *pFrameSize);
    void        SDL_Sprite_Draw(SDL_Sprite *pSprite, SDL_Rect *pDest, double dAngle, SDL_RendererFlip iFlip);
    void        SDL_Sprite_Free(SDL_Sprite **ppSprite);

#endif // __SDL_SPRITE_H__

/* ========================================================================= */
