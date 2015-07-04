/* ========================================================================= */
/*!
 * \file    ENG_View.h
 * \brief   File to interface with the view.
 * \author  Nyuu / Orlyn / Red
 * \version 1.0
 * \date    28 June 2015
 */
/* ========================================================================= */
/* Author  | Date     | Comments                                             */
/* --------+----------+----------------------------------------------------- */
/* Nyuu    | 28/06/15 | Creation.                                            */
/* ========================================================================= */

#ifndef __ENG_VIEW_H__
#define __ENG_VIEW_H__

    #include "ENG_Shared.h"
    
    void ENG_View_Init(Sint32 w, Sint32 h);
    void ENG_View_SetOrigin(const SDL_Point *pOrigin);
    void ENG_View_CenterOrigin(const SDL_Point *pOrigin);
    void ENG_View_ConvOrigin(const SDL_Point *pOrigin, SDL_Point *pPos);

#endif // __ENG_VIEW_H__

/* ========================================================================= */
