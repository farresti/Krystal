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

typedef struct
{
    int a;
    int b;
    int c;
} EFF_TestData;

/* ========================================================================= */

static void EFF_Test_Spawn(ENG_Effect *pTest)
{
    EFF_TestData *pTestData = (EFF_TestData *) ENG_Effect_GetData(pTest);
    pTestData->a = 0;
}

static void EFF_Test_Think(ENG_Effect *pTest)
{
    EFF_TestData *pTestData = (EFF_TestData *) ENG_Effect_GetData(pTest);
    pTestData->a = 0;
}

static void EFF_Test_Draw(ENG_Effect *pTest)
{
    EFF_TestData *pTestData = (EFF_TestData *) ENG_Effect_GetData(pTest);
    pTestData->a = 0;
}

static void EFF_Test_Die(ENG_Effect *pTest)
{
    EFF_TestData *pTestData = (EFF_TestData *) ENG_Effect_GetData(pTest);
    pTestData->a = 0;
}

/* ========================================================================= */

ENG_EffectTable Eff_TestTable = 
{
    EFF_Test_Spawn,
    EFF_Test_Think,
    EFF_Test_Draw,
    EFF_Test_Die
};

void EFF_Test_Register(void)
{
    ENG_Linker_RegisterEffect( "test", sizeof(EFF_TestData), &Eff_TestTable);
}

/* ========================================================================= */
