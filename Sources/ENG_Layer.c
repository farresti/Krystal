/* ========================================================================= */
/*!
 * \file    ENG_Layer.c
 * \brief   File to handle the layers.
 * \author  Nyuu / Orlyn / Red
 * \version 1.0
 * \date    03 July 2015
 */
/* ========================================================================= */
/* Author  | Date     | Comments                                             */
/* --------+----------+----------------------------------------------------- */
/* Nyuu    | 03/07/15 | Creation.                                            */
/* ========================================================================= */

#include "ENG_Layer.h"

/* ========================================================================= */

/*! Global variable to handle the layers. */
static Uint32 ENG_maxLayer;

/* ========================================================================= */

/*!
 * \brief  Function to init the layers.
 *
 * \param  iMaxLayer Maximum layer.
 * \return None.
 */
void ENG_Layer_Init(Uint32 iMaxLayer)
{
    ENG_maxLayer = iMaxLayer;
}

/*!
 * \brief  Function to get the maximum layer.
 *
 * \return The maximum layer.
 */
Uint32 ENG_Layer_GetMax(void)
{
    return ENG_maxLayer;
}

/* ========================================================================= */
