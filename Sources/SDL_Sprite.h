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
        char        *szName;       /*!< Name of the sprite. */
        SDL_Texture *pTexture;     /*!< Pointer to the texture. */

        Uint32       iNbFrameW;    /*!< Number of frame (Width). */
        Uint32       iNbFrameH;    /*!< Number of frame (Height). */
        Uint32       iFrameMax;    /*!< Maximum frame. */

        SDL_Rect     sFrameClip;     /*!< Frame clip. */
        SDL_Rect     sFramePosition; /*!< Frame position. */
        SDL_Point    sFrameCenter;   /*!< Frame center. */
    } SDL_Sprite;

    SDL_Sprite *SDL_Sprite_Alloc(const char *szSprName);

    const char *SDL_Sprite_GetName(const SDL_Sprite *pSprite);
    Uint32      SDL_Sprite_GetFrameMax(const SDL_Sprite *pSprite);
    void        SDL_Sprite_GetFrameSize(const SDL_Sprite *pSprite, SDL_Rect *pSize);

    void        SDL_Sprite_Draw(SDL_Sprite *pSprite, const SDL_Point *pPos, Uint32 iFrame);
    void        SDL_Sprite_DrawEx(SDL_Sprite *pSprite, const SDL_Point *pPos, Uint32 iFrame, double dAngle, SDL_RendererFlip iFlip);

    void        SDL_Sprite_Free(SDL_Sprite **ppSprite);

#endif // __SDL_SPRITE_H__

/* ========================================================================= */
