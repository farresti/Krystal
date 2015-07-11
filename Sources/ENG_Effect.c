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
 * \param  iPrivDataSize Size of the private data in bytes.
 * \return A pointer to the allocated effect, or NULL if error.
 */
ENG_Effect *ENG_Effect_Alloc(Uint32 iPrivDataSize)
{
    ENG_Effect *pEffect = (ENG_Effect *) UTIL_Malloc(sizeof(ENG_Effect));

    if (pEffect)
    {
        memset(pEffect, 0, sizeof(ENG_Effect));

        if (iPrivDataSize)
        {
            pEffect->pPrivData = UTIL_Malloc(iPrivDataSize);

            if (pEffect->pPrivData == NULL)
            {
                UTIL_Free(pEffect);
            }
        }
    }

    return pEffect;
}

/*!
 * \brief  Function to set an effect layer.
 *
 * \param  pEffect Pointer to the effect.
 * \param  iLayer  Index of the layer.
 * \return None.
 */
void ENG_Effect_SetLayer(ENG_Effect *pEffect, const Uint32 iLayer)
{
    pEffect->iLayer = iLayer;
}

/*!
 * \brief  Function to set an effect next think.
 *
 * \param  pEffect    Pointer to the effect.
 * \param  iNextThink Time value before the next think.
 * \return None.
 */
void ENG_Effect_SetNextThink(ENG_Effect *pEffect, const Uint32 iNextThink)
{
    pEffect->iNextThink = iNextThink;
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

/*!
 * \brief  Function to retrieve a pointer to an effect private data.
 *
 * \param  pEffect Pointer to the effect.
 * \return A pointer to the effect private data.
 */
void *ENG_Effect_GetPrivData(ENG_Effect *pEffect)
{
    return pEffect->pPrivData;
}

/*!
 * \brief  Function to set an effect functions table.
 *
 * \param  pEffect Pointer to the effect.
 * \param  pTable  Pointer to the effect functions table.
 * \return None.
 */
void ENG_Effect_SetTable(ENG_Effect *pEffect, const ENG_EffectTable *pTable)
{
    pEffect->pTable = pTable;
}

/*!
 * \brief  Function to execute the effect function 'Spawn'.
 *
 * \param  pEffect Pointer to the effect.
 * \return None.
 */
void ENG_Effect_Spawn(ENG_Effect *pEffect, const SDL_Point *pOrigin)
{
    if (pEffect->pTable->pftSpawn)
    {
        pEffect->pTable->pftSpawn(pEffect, pOrigin);
    }
}

/*!
 * \brief  Function to execute the effect function 'Think'.
 *
 * \param  pEffect Pointer to the effect.
 * \param  iTime   Value of the current time.
 * \return None.
 */
void ENG_Effect_Think(ENG_Effect *pEffect, const Uint32 iTime)
{
    if (pEffect->iNextThink && pEffect->iNextThink < iTime)
    {
        pEffect->iNextThink = 0;

        if (pEffect->pTable->pftThink)
        {
            pEffect->pTable->pftThink(pEffect);
        }
    }
}

/*!
 * \brief  Function to execute the effect function 'Draw'.
 *
 * \param  pEffect Pointer to the effect.
 * \param  iLayer  Index of the current layer.
 * \return None.
 */
void ENG_Effect_Draw(ENG_Effect *pEffect, const Uint32 iLayer)
{
    if (pEffect->pTable->pftDraw && pEffect->iLayer == iLayer)
    {
        pEffect->pTable->pftDraw(pEffect);
    }
}

/*!
 * \brief  Function to execute the effect function 'Die'.
 *
 * \param  pEffect Pointer to the effect.
 * \return None.
 */
void ENG_Effect_Die(ENG_Effect *pEffect)
{
    if (pEffect->pTable->pftDie)
    {
        pEffect->pTable->pftDie(pEffect);
    }
}

/*!
 * \brief  Function to free an effect.
 *
 * \param  ppEffect Pointer to pointer to the effect.
 * \return None.
 */
void ENG_Effect_Free(ENG_Effect **ppEffect)
{
    UTIL_Free((*ppEffect)->pPrivData);
    UTIL_Free(*ppEffect);
}

/* ========================================================================= */
