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

    /*!
     * \struct HUI_Scrollbar
     * \brief  Structure to handle a scrollbar.
     */
    typedef struct
    {
        Sint32 iMax; /*!< The maximum value of the scrollbar. */
        Sint32 iMin; /*!< The minimum value of the scrollbar. */
        Sint32 iStep;  /*!< The step of the scrollbar. */
        Sint32 iCurrent; /*!< The current value. */

        HUI_Button *pButtonSlider; /*!< Hitbox of the slider. */
        SDL_Rect sScrollbar; /*!< Hitbox of the scrollbar. */

    } HUI_Scrollbar;

    void   HUI_Scrollbar_Init();
    void   HUI_Scrollbar_Draw(HUI_Scrollbar *pScrollbar);
    void   HUI_Scrollbar_Free(HUI_Scrollbar *pScrollbar);

    void   HUI_Scrollbar_SetSlidePosition(HUI_Scrollbar *pScrollbar);
    void   HUI_Scrollbar_SetValue(HUI_Scrollbar *pScrollbar, Sint32 iMax, Sint32 iMin, Sint32 iStep);

    Sint32 HUI_Scrollbar_GetCurrent(HUI_Scrollbar *pScrollbar);
    Sint32 HUI_Scrollbar_GetMin(HUI_Scrollbar *pScrollbar);
    Sint32 HUI_Scrollbar_GetMax(HUI_Scrollbar *pScrollbar);
    Sint32 HUI_Scrollbar_GetStep(HUI_Scrollbar *pScrollbar);
    

#endif // __HUI_SCROLLBAR_H__

/* ========================================================================= */
