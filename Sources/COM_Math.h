/* ========================================================================= */
/*!
 * \file    COM_Math.h
 * \brief   File to interface with mathematical functions.
 * \author  Nyuu / Orlyn / Red
 * \version 1.0
 * \date    23 June 2015
 */
/* ========================================================================= */
/* Author  | Date     | Comments                                             */
/* --------+----------+----------------------------------------------------- */
/* Nyuu    | 23/06/15 | Creation.                                            */
/* ========================================================================= */

#ifndef __COM_MATH_H__
#define __COM_MATH_H__

    #include "COM_Shared.h"
    
    /*! Macro to get the min of two values. */
    #define COM_Math_Min(x,y) ((x) > (y) ? (y) : (x))
    /*! Macro to get the max of two values. */
    #define COM_Math_Max(x,y) ((x) > (y) ? (x) : (y))
    
    void         COM_Math_Init(void);
    int          COM_Math_Rand(int iMin, int iMax);
    unsigned int COM_Math_Sqrt32(unsigned int iValue);

#endif // __COM_MATH_H__

/* ========================================================================= */
