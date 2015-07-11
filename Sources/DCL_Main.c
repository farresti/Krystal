/* ========================================================================= */
/*!
 * \file    DCL_Main.c
 * \brief   File to handle the main 'DCL' functions.
 * \author  Nyuu / Orlyn / Red
 * \version 1.0
 * \date    04 July 2015
 */
/* ========================================================================= */
/* Author  | Date     | Comments                                             */
/* --------+----------+----------------------------------------------------- */
/* Nyuu    | 04/07/15 | Creation.                                            */
/* ========================================================================= */

#include "DCL_Main.h"

/* ========================================================================= */

static const ENG_DecalInfo ENG_decalInfo[ ] = 
{
    { "dcl_blood1",  "blood25",  0 },
    { "dcl_blood2",  "blood25",  1 },
    { "dcl_blood3",  "blood25",  2 },
    { "dcl_blood4",  "blood25",  3 },
    { "dcl_blood5",  "blood25",  4 },
    { "dcl_blood6",  "blood25",  5 },
    { "dcl_blood7",  "blood25",  6 },
    { "dcl_blood8",  "blood25",  7 },
    { "dcl_blood9",  "blood25",  8 },
    { "dcl_blood10", "blood25",  9 },
    { "dcl_blood11", "blood25", 10 },
    { "dcl_blood12", "blood25", 11 },
    { "dcl_blood13", "blood25", 12 },
    { "dcl_blood14", "blood25", 13 },
    { "dcl_blood15", "blood25", 14 },
    { "dcl_blood16", "blood25", 15 }
};

/* ========================================================================= */

/*!
 * \brief  Function to init the 'DCL' module.
 *
 * \return None.
 */
void DCL_Main_Init(void)
{
    Uint32 i;

    for (i = 0 ; i < UTIL_ArraySize(ENG_decalInfo) ; ++i)
    {
        ENG_Linker_RegisterDecal(&ENG_decalInfo[i]);
    }
}

/* ========================================================================= */
