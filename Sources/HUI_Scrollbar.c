/* ========================================================================= */
/*!
 * \file    HUI_Scrollbar.c
 * \brief   File to handle the scrollbar.
 * \author  Nyuu / Orlyn / Red
 * \version 1.0
 * \date    27 June 2015
 */
/* ========================================================================= */
/* Author  | Date     | Comments                                             */
/* --------+----------+----------------------------------------------------- */
/* Red     | 27/06/15 | Creation.                                            */
/* ========================================================================= */

#include "HUI_Scrollbar.h"

/* ========================================================================= */

/*!
 * \brief  Function to init a scrollbar.
 *
 * \param  pScrollbar       Pointer to the scrollbar.
 * \param  pSpriteScrollbar Pointer to the sprite used for the scrollbar.
 * \param  pSpriteSlider    Pointer to the sprite used for the slider.
 * \param  rHitboxScrollbar Hitbox of the scrollbar
 * \param  iMin             The minimum value of the scrollbar ( < iMax).
 * \param  iMax             The maximum value of the scrollbar ( > iMin).
 * \return None.
 */
void HUI_Scrollbar_Init(HUI_Scrollbar *pScrollbar, SDL_Sprite *pSpriteScrollbar, SDL_Sprite *pSpriteSlider, SDL_Rect rHitboxScrollbar, Sint32 iMin, Sint32 iMax)
{
    pScrollbar->iCurrent = iMin;
    pScrollbar->iMin     = iMin;
    pScrollbar->iMax     = iMax;


    SDL_Anim_Init(&pScrollbar->sAnimScrollbar, pSpriteScrollbar);
    SDL_Anim_SetFrame(&pScrollbar->sAnimScrollbar, 0);

    HUI_Button_Init(&pScrollbar->sButtonSlider, pSpriteSlider, rHitboxScrollbar.x, rHitboxScrollbar.y);

    pScrollbar->rHitboxScrollbar.x = rHitboxScrollbar.x;
    pScrollbar->rHitboxScrollbar.y = rHitboxScrollbar.y;
    pScrollbar->rHitboxScrollbar.h = rHitboxScrollbar.h;
    pScrollbar->rHitboxScrollbar.w = rHitboxScrollbar.w;

    pScrollbar->sPointScrollbar.x = rHitboxScrollbar.x;
    pScrollbar->sPointScrollbar.y = rHitboxScrollbar.y;
}


/*!
* \brief  Function to set the position of the scrollbar.
*
* \param  pScrollbar Pointer to the scrollbar.
* \param  x          Scrollbar position on x.
* \param  y          Scrollbar position on y.
* \return None.
*/
void HUI_Scrollbar_SetPosition(HUI_Scrollbar *pScrollbar, Sint32 x, Sint32 y)
{
    SDL_Point sShift;
    SDL_Rect  rRectSlider;

    HUI_Button_GetHitbox(&pScrollbar->sButtonSlider, &rRectSlider);

    sShift.x = pScrollbar->sButtonSlider.sPosition.x - pScrollbar->sPointScrollbar.x;
 
    pScrollbar->sPointScrollbar.x = x;
    pScrollbar->sPointScrollbar.y = y;

    pScrollbar->rHitboxScrollbar.x = x;
    pScrollbar->rHitboxScrollbar.y = y;

    sShift.y = pScrollbar->sPointScrollbar.y + (pScrollbar->rHitboxScrollbar.h / 2) - (rRectSlider.h / 2);

    HUI_Button_SetPosition(&pScrollbar->sButtonSlider, x + sShift.x, sShift.y);
}


/*!
* \brief  Function to draw a scrollbar.
*
* \param  pScrollbar Pointer to the scrollbar.
* \return None.
*/
void HUI_Scrollbar_Draw(HUI_Scrollbar *pScrollbar)
{
    SDL_Anim_Draw(&pScrollbar->sAnimScrollbar, &pScrollbar->sPointScrollbar);
    HUI_Button_Draw(&pScrollbar->sButtonSlider);
}

/*!
* \brief  Function to update a scrollbar.
*
* \param  pScrollbar Pointer to the scrollbar.
* \param  pInput     Pointer to the inputs.
* \return None.
*/
void HUI_Scrollbar_Update(HUI_Scrollbar *pScrollbar, const HUI_Input *pInput)
{
    SDL_Rect  rRectSlider;
    SDL_Point sPointSlider;
    SDL_Point sMidSlider;
    Sint32    iPercentage = 0;

    HUI_Button_GetHitbox(&pScrollbar->sButtonSlider, &rRectSlider);
    HUI_Button_GetPosition(&pScrollbar->sButtonSlider, &sPointSlider);

    sMidSlider.x = rRectSlider.w / 2;
    sMidSlider.y = rRectSlider.h / 2;

    HUI_Button_Update(&pScrollbar->sButtonSlider, pInput);

    if (HUI_Button_GetState(&pScrollbar->sButtonSlider) == HUI_BUTTON_ACTIVE)
    {
        if ((pInput->iMouse.x >= pScrollbar->sPointScrollbar.x + sMidSlider.x) && (pInput->iMouse.x <= (pScrollbar->sPointScrollbar.x + pScrollbar->rHitboxScrollbar.w - sMidSlider.x))) // Above the scrollbar ?
        {
            HUI_Button_SetPosition(&pScrollbar->sButtonSlider, pInput->iMouse.x - sMidSlider.x , sPointSlider.y);

            iPercentage = (sPointSlider.x - pScrollbar->sPointScrollbar.x) * 100 / (pScrollbar->rHitboxScrollbar.w - rRectSlider.w);
            pScrollbar->iCurrent = pScrollbar->iMin + (((pScrollbar->iMax - pScrollbar->iMin) * iPercentage) / 100);
         
        } 
    }
}

/*!
* \brief  Function to set the values of a scrollbar.
*
* \param  pScrollbar Pointer to the scrollbar.
* \param  iValue     The value of the slider.
* \return None.
*/
void HUI_Scrollbar_SetValue(HUI_Scrollbar *pScrollbar, Sint32 iValue)
{
    SDL_Point sPointSlider;
    SDL_Rect  rRectSlider;

    if (iValue >= pScrollbar->iMin && iValue <= pScrollbar->iMax)
    {
        HUI_Button_GetHitbox(&pScrollbar->sButtonSlider, &rRectSlider);

        sPointSlider.x = (((iValue - pScrollbar->iMin)) * (pScrollbar->rHitboxScrollbar.w - rRectSlider.w));
        sPointSlider.x = pScrollbar->sPointScrollbar.x +  sPointSlider.x / ((pScrollbar->iMax - pScrollbar->iMin));

        HUI_Button_SetPosition(&pScrollbar->sButtonSlider, sPointSlider.x, pScrollbar->sButtonSlider.sPosition.y);
        pScrollbar->iCurrent = iValue;
    }
}

/*!
* \brief  Function to set the parameter of a scrollbar.
*
* \param  pScrollbar Pointer to the scrollbar.
* \param  iMax       The maximum value of the scrollbar.
* \param  iMin       The minimum value of the scrollbar.
* \return None.
*/
void HUI_Scrollbar_SetParam(HUI_Scrollbar *pScrollbar, Sint32 iMin, Sint32 iMax)
{
    pScrollbar->iMin  = iMin;
    pScrollbar->iMax  = iMax;
}

/*!
* \brief  Function to get the current value of a scrollbar.
*
* \param  pScrollbar Pointer to the scrollbar.
* \return The current value of the scrollbar.
*/
Sint32 HUI_Scrollbar_GetCurrent(const HUI_Scrollbar *pScrollbar)
{
    return pScrollbar->iCurrent;
}

/*!
* \brief  Function to get the maximum value of a scrollbar.
*
* \param  pScrollbar Pointer to the scrollbar.
* \return The maximum value of the scrollbar.
*/
Sint32 HUI_Scrollbar_GetMax(const HUI_Scrollbar *pScrollbar)
{
    return pScrollbar->iMax;
}

/*!
* \brief  Function to get the minimum value of a scrollbar.
*
* \param  pScrollbar  Pointer to the scrollbar.
* \return The minimum value of the scrollbar.
*/
Sint32 HUI_Scrollbar_GetMin(const HUI_Scrollbar *pScrollbar)
{
    return pScrollbar->iMin;
}


/* ========================================================================= */
