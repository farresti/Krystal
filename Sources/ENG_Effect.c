/* ========================================================================= */
/*!
 * \file    ENG_Effect.c
 * \brief   File to handle the engine effects.
 * \author  Nyuu / Orlyn / Red
 * \version 1.0
 * \date    15 June 2015
 */
/* ========================================================================= */
/* Author  | Date     | Comments                                             */
/* --------+----------+----------------------------------------------------- */
/* Nyuu    | 15/06/15 | Creation.                                            */
/* ========================================================================= */

#include "ENG_View.h"
#include "ENG_Effect.h"

/* ========================================================================= */

/*!
 * \brief  Function to allocate an effect.
 *
 * \param  iDataSize Size of the data (Can be 0).
 * \return A pointer to the allocated effect, or NULL if error.
 */
ENG_Effect *ENG_Effect_Alloc(Uint32 iDataSize)
{
    ENG_Effect *pEffect = (ENG_Effect *) UTIL_Malloc(sizeof(ENG_Effect));

    if (pEffect)
    {
        memset(pEffect, 0, sizeof(ENG_Effect));

        if (iDataSize)
        {
            pEffect->pData = UTIL_Malloc(iDataSize);

            if (pEffect->pData == NULL)
            {
                UTIL_Free(pEffect);
            }
        }
    }

    return pEffect;
}

/*!
 * \brief  Function to set the origin of an effect.
 *
 * \param  pEffect Pointer to the effect.
 * \param  pOrigin Pointer to the origin.
 * \return None.
 */
void ENG_Effect_SetOrigin(ENG_Effect *pEffect, const SDL_Point *pOrigin)
{
    pEffect->sOrigin.x = pOrigin->x;
    pEffect->sOrigin.y = pOrigin->y;

    ENG_View_ConvOrigin(pOrigin, &pEffect->sPosition);
}

/*!
 * \brief  Function to kill an effect.
 *
 * \param  pEffect Pointer to the effect.
 * \return None.
 */
void ENG_Effect_Kill(ENG_Effect *pEffect)
{
    pEffect->bKillMe = SDL_TRUE;
}

/* ========================================================================= */
