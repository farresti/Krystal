/* ========================================================================= */
/*!
 * \file    EFF_Test.c
 * \brief   File to do some effect tests.
 * \author  Nyuu / Orlyn / Red
 * \version 1.0
 * \date    11 July 2015
 */
/* ========================================================================= */
/* Author  | Date     | Comments                                             */
/* --------+----------+----------------------------------------------------- */
/* Nyuu    | 11/07/15 | Creation.                                            */
/* ========================================================================= */

#include "EFF_Test.h"

/* ========================================================================= */

static void EFF_Test_Spawn(ENG_Effect *pTest, const SDL_Point *pOrigin)
{
    (void) pOrigin;
    ENG_Effect_Kill(pTest);
}

/* ========================================================================= */

static const ENG_EffectTable Eff_TestTable = 
{
    EFF_Test_Spawn,
    NULL,
    NULL,
    NULL
};

static const ENG_EffectInfo Eff_TestInfo = 
{
    "eff_test",
    0,
    &Eff_TestTable
};

/* ========================================================================= */

void EFF_Test_Register(void)
{
    ENG_Linker_RegisterEffect(&Eff_TestInfo);
}

/* ========================================================================= */
