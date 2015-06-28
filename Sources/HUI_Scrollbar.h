/* ========================================================================= */
/*!
 * \file    HUI_Scrollbar.h
 * \brief   File to interface with the scrollbar.
 * \author  Nyuu / Orlyn / Red
 * \version 1.0
 * \date    27 June 2015
 */
/* ========================================================================= */
/* Author  | Date     | Comments                                             */
/* --------+----------+----------------------------------------------------- */
/* Red     | 27/06/15 | Creation.                                            */
/* ========================================================================= */

#ifndef __HUI_SCROLLBAR_H__
#define __HUI_SCROLLBAR_H__

    #include "HUI_Button.h"
    #include "HUI_Input.h"

    /*!
     * \struct HUI_Scrollbar
     * \brief  Structure to handle a scrollbar.
     */
    typedef struct
    {
        Sint32      iMax;               /*!< The maximum value of the scrollbar. */
        Sint32      iMin;               /*!< The minimum value of the scrollbar. */
        Sint32      iCurrent;           /*!< The current value. */

        HUI_Button  sButtonSlider;      /*!< Hitbox of the slider. */

        SDL_Anim    sAnimScrollbar;     /*!< Structure to animate the scrollbar. */
        SDL_Rect    rHitboxScrollbar;   /*!< Hitbox of the scrollbar. */
        SDL_Point   sPointScrollbar;    /*!< Position of the scrollbar. */
    } HUI_Scrollbar;

    void   HUI_Scrollbar_Init(HUI_Scrollbar *pScrollbar, SDL_Sprite *pSpriteScrollbar, SDL_Sprite *pSpriteSlider, SDL_Rect rHitboxScrollbar, Sint32 iMin, Sint32 iMax);
    void   HUI_Scrollbar_SetPosition(HUI_Scrollbar *pScrollbar, Sint32 x, Sint32 y);
    void   HUI_Scrollbar_Draw(HUI_Scrollbar *pScrollbar);
    void   HUI_Scrollbar_Update(HUI_Scrollbar *pScrollbar, const HUI_Input *pInput);

    void   HUI_Scrollbar_SetParam(HUI_Scrollbar *pScrollbar, Sint32 iMin, Sint32 iMax);
    void   HUI_Scrollbar_SetValue(HUI_Scrollbar *pScrollbar, Sint32 iValue);

    Sint32 HUI_Scrollbar_GetCurrent(const HUI_Scrollbar *pScrollbar);
    Sint32 HUI_Scrollbar_GetMin(const HUI_Scrollbar *pScrollbar);
    Sint32 HUI_Scrollbar_GetMax(const HUI_Scrollbar *pScrollbar);

#endif // __HUI_SCROLLBAR_H__

/* ========================================================================= */
