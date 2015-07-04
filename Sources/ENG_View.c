/* ========================================================================= */
/*!
 * \file    ENG_View.c
 * \brief   File to handle the view.
 * \author  Nyuu / Orlyn / Red
 * \version 1.0
 * \date    28 June 2015
 */
/* ========================================================================= */
/* Author  | Date     | Comments                                             */
/* --------+----------+----------------------------------------------------- */
/* Nyuu    | 28/06/15 | Creation.                                            */
/* ========================================================================= */

#include "ENG_View.h"

/* ========================================================================= */

/*! Global variable to handle the view. */
static SDL_Rect ENG_view;

/* ========================================================================= */

/*!
 * \brief  Function to init the view.
 *
 * \param  w Width of the view.
 * \param  h Height of the view.
 * \return None.
 */
void ENG_View_Init(Sint32 w, Sint32 h)
{
    ENG_view.x = 0;
    ENG_view.y = 0;
    ENG_view.w = w;
    ENG_view.h = h;
}

/*!
 * \brief  Function to set the view origin.
 *
 * \param  pOrigin Pointer to an origin.
 * \return None.
 */
void ENG_View_SetOrigin(const SDL_Point *pOrigin)
{
    ENG_view.x = pOrigin->x;
    ENG_view.y = pOrigin->y;
}

/*!
 * \brief  Function to center the view origin.
 *
 * \param  pOrigin Pointer to an origin.
 * \return None.
 */
void ENG_View_CenterOrigin(const SDL_Point *pOrigin)
{
    ENG_view.x = (pOrigin->x - (ENG_view.w >> 1));
    ENG_view.y = (pOrigin->y - (ENG_view.h >> 1));
}

/*!
 * \brief  Function to convert an origin to a position.
 *
 * \param  pOrigin Pointer to an origin.
 * \param  pPos    Pointer to a position.
 * \return None.
 */
void ENG_View_ConvOrigin(const SDL_Point *pOrigin, SDL_Point *pPos)
{
    pPos->x = (pOrigin->x - ENG_view.x);
    pPos->y = (pOrigin->y - ENG_view.y);
}

/* ========================================================================= */
