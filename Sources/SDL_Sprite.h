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

        Uint32       iFrameWidth;  /*!< Frame width */
        Uint32       iFrameHeight; /*!< Frame height */
        Uint32       iNbFrameL;    /*!< Number of frame (Width) */
        Uint32       iNbFrameH;    /*!< Number of frame (Height) */
        Uint32       iFrameMax;    /*!< Maximum frame */
    } SDL_Sprite;

    SDL_Sprite *SDL_Sprite_Alloc(const char *szSprName);

    const char *SDL_Sprite_GetName(const SDL_Sprite *pSprite);
    Uint32      SDL_Sprite_GetFrameMax(const SDL_Sprite *pSprite);
    void        SDL_Sprite_GetFrameSize(const SDL_Sprite *pSprite, SDL_Rect *pSize);
    void        SDL_Sprite_GetFramePosition(const SDL_Sprite *pSprite, Uint32 iFrame, SDL_Rect *pPos);

    void        SDL_Sprite_Draw(SDL_Sprite *pSprite, const SDL_Rect *pClip, const SDL_Rect *pPos);
    void        SDL_Sprite_DrawEx(SDL_Sprite *pSprite, const SDL_Rect *pClip, const SDL_Rect *pPos, double dAngle, const SDL_Point *pCenter, SDL_RendererFlip iFlip);

    void        SDL_Sprite_Free(SDL_Sprite **ppSprite);

#endif // __SDL_SPRITE_H__

/* ========================================================================= */
