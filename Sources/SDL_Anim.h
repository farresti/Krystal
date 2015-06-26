/* ========================================================================= */
/*!
 * \file    SDL_Anim.h
 * \brief   File to interface with the animations.
 * \author  Nyuu / Orlyn / Red
 * \version 1.0
 * \date    15 June 2015
 */
/* ========================================================================= */
/* Author  | Date     | Comments                                             */
/* --------+----------+----------------------------------------------------- */
/* Nyuu    | 15/06/15 | Creation.                                            */
/* ========================================================================= */
    
#ifndef __SDL_ANIM_H__
#define __SDL_ANIM_H__
    
    #include "SDL_Sprite.h"
    
    /*!
     * \enum  SDL_AnimType
     * \brief Enumeration of the possible type of animations.
     */
    typedef enum
    {
        SDL_ANIM_NONE = 0, /*!< Value no animation. */
        SDL_ANIM_ONCE = 1, /*!< Value one animation. */
        SDL_ANIM_LOOP = 2  /*!< Value looped animation. */
    } SDL_AnimType;

    /*!
     * \struct SDL_Anim
     * \brief  Structure to handle an animation.
     */
    typedef struct
    {
        SDL_Sprite      *pSprite;         /*!< Pointer to a sprite. */
        SDL_AnimType     iAnimType;       /*!< Type of the animation (looped..). */

        SDL_Rect         rFrameClip;      /*!< Rectangle to clip a frame. */
        SDL_Rect         rFramePos;       /*!< Rectangle to position a frame. */
        SDL_Point        sFrameCenter;    /*!< Center of the frame. */

        Uint32           iFrameMax;       /*!< Maximum frame of the sprite. */
        Uint32           iFrameCurr;      /*!< Current frame of the sprite. */
        Uint32           iTimeBeforeNext; /*!< Time before the next frame. */
        Uint32           iFrameRate;      /*!< Frame rate of the sprite. */

        double           dAngle;          /*!< Angle to rotate the frame. */
        SDL_RendererFlip iFlip;           /*!< Flag to flip the sprite. */
    } SDL_Anim;

    void SDL_Anim_Init(SDL_Anim *pAnim, SDL_Sprite *pSprite);

    void SDL_Anim_SetPosition(SDL_Anim *pAnim, Sint32 x, Sint32 y);
    void SDL_Anim_SetAngle   (SDL_Anim *pAnim, double dAngle);
    void SDL_Anim_SetFlip    (SDL_Anim *pAnim, SDL_RendererFlip iFlip);
    void SDL_Anim_SetFrame   (SDL_Anim *pAnim, Uint32 iFrame);

    void SDL_Anim_Start(SDL_Anim *pAnim, SDL_AnimType iAnimType, Uint32 iFrameRate);
    void SDL_Anim_Stop(SDL_Anim *pAnim);

    void SDL_Anim_Update(SDL_Anim *pAnim);
    void SDL_Anim_Draw(SDL_Anim *pAnim);
    void SDL_Anim_DrawEx(SDL_Anim *pAnim);

#endif // __SDL_ANIM_H__

/* ========================================================================= */
