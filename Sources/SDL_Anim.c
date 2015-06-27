/* ========================================================================= */
/*!
 * \file    SDL_Anim.c
 * \brief   File to handle the animations.
 * \author  Nyuu / Orlyn / Red
 * \version 1.0
 * \date    15 June 2015
 */
/* ========================================================================= */
/* Author  | Date     | Comments                                             */
/* --------+----------+----------------------------------------------------- */
/* Nyuu    | 15/06/15 | Creation.                                            */
/* ========================================================================= */

#include "SDL_Util.h"
#include "SDL_Anim.h"

/* ========================================================================= */

/*!
 * \brief  Function to init an animation.
 *
 * \param  pAnim   Pointer to the animation.
 * \param  pSprite Pointer to a sprite allocated.
 * \return None.
 */
void SDL_Anim_Init(SDL_Anim *pAnim, SDL_Sprite *pSprite)
{
    pAnim->pSprite   = pSprite;
    pAnim->iAnimType = SDL_ANIM_NONE;

    pAnim->iFrameMax       = SDL_Sprite_GetFrameMax(pSprite);
    pAnim->iFrameCurr      = 0;
    pAnim->iTimeBeforeNext = 0;
    pAnim->iFrameRate      = 0;
}

/*!
 * \brief  Function to set a frame of an animation.
 *
 * \param  pAnim  Pointer to the animation.
 * \param  iFrame Frame to set.
 * \return None.
 */
void SDL_Anim_SetFrame(SDL_Anim *pAnim, Uint32 iFrame)
{
    if(iFrame < pAnim->iFrameMax)
    {
        pAnim->iFrameCurr = iFrame;
    }
}

/*!
 * \brief  Function to start an animation.
 *
 * \param  pAnim      Pointer to the animation.
 * \param  iAnimType  Type of the animation (looped..).
 * \param  iFrameRate Frame rate of the animation.
 * \return None.
 */
void SDL_Anim_Start(SDL_Anim *pAnim, SDL_AnimType iAnimType, Uint32 iFrameRate)
{
    pAnim->iAnimType       = iAnimType;
    pAnim->iTimeBeforeNext = iFrameRate + SDL_GetTicks( );
    pAnim->iFrameRate      = iFrameRate;
}

/*!
 * \brief  Function to stop an animation.
 *
 * \param  pAnim Pointer to the animation.
 * \return None.
 */
void SDL_Anim_Stop(SDL_Anim *pAnim)
{
    pAnim->iAnimType       = SDL_ANIM_NONE;
    pAnim->iTimeBeforeNext = 0;
    pAnim->iFrameRate      = 0;
}

/*!
 * \brief  Function to update an animation.
 *
 * \param  pAnim Pointer to the animation.
 * \return None.
 */
void SDL_Anim_Update(SDL_Anim *pAnim)
{
    Uint32 iTime;

    if ((pAnim->iAnimType != SDL_ANIM_NONE) &&
        (pAnim->iTimeBeforeNext) &&
        (pAnim->iFrameRate) &&
        (pAnim->iFrameMax > 1))
    {
        iTime = SDL_GetTicks( );

        if (pAnim->iTimeBeforeNext <= iTime)
        {
            if ((pAnim->iAnimType == SDL_ANIM_LOOP) ||
                (pAnim->iFrameCurr < pAnim->iFrameMax - 1))
            {
                pAnim->iTimeBeforeNext = iTime + pAnim->iFrameRate;
                pAnim->iFrameCurr      = pAnim->iFrameCurr + 1;
                pAnim->iFrameCurr      = pAnim->iFrameCurr % pAnim->iFrameMax;
            }
            else // SDL_ANIM_ONCE && LAST_FRAME
            {
                pAnim->iTimeBeforeNext = 0;
                pAnim->iFrameRate      = 0;
            }
        }
    }
}

/*!
 * \brief  Function to draw an animation.
 *
 * \param  pAnim Pointer to the animation.
 * \param  pPos  Pointer to a point to position the animation.
 * \return None.
 */
void SDL_Anim_Draw(SDL_Anim *pAnim, const SDL_Point *pPos)
{
    SDL_Sprite_Draw(pAnim->pSprite, pPos, pAnim->iFrameCurr);
}

/*!
 * \brief  Function to draw an animation.
 *
 * \param  pAnim  Pointer to the animation.
 * \param  pPos   Pointer to a point to position the animation.
 * \param  dAngle Angle to rotate the animation.
 * \param  iFlip  Flag to flip the animation.
 * \return None.
 */
void SDL_Anim_DrawEx(SDL_Anim *pAnim, const SDL_Point *pPos, double dAngle, SDL_RendererFlip iFlip)
{
    SDL_Sprite_DrawEx(pAnim->pSprite, pPos, pAnim->iFrameCurr, dAngle, iFlip);
}

/* ========================================================================= */
