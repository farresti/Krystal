/* ========================================================================= */
/*!
 * \file    ENG_Scheduler.c
 * \brief   File to handle the scheduler.
 * \author  Nyuu / Orlyn / Red
 * \version 1.0
 * \date    28 June 2015
 */
/* ========================================================================= */
/* Author  | Date     | Comments                                             */
/* --------+----------+----------------------------------------------------- */
/* Nyuu    | 28/06/15 | Creation.                                            */
/* ========================================================================= */

#include "ENG_Layer.h"
#include "ENG_Scheduler.h"

/* ========================================================================= */

/*!
 * \struct ENG_Scheduler
 * \brief  Structure to handle the scheduler.
 */
typedef struct
{
    ENG_Decal  *pFirstDecal;  /*!< Pointer to the first decal. */
    ENG_Effect *pFirstEffect; /*!< Pointer to the first effect. */
} ENG_Scheduler;

/*! Global variable to handle the scheduler. */
static ENG_Scheduler ENG_scheduler;

/* ========================================================================= */

/*!
 * \brief  Function to init the scheduler.
 *
 * \return None.
 */
void ENG_Scheduler_Init(void)
{
    ENG_scheduler.pFirstDecal  = NULL;
    ENG_scheduler.pFirstEffect = NULL;
}

/*!
 * \brief  Function to add a decal to the scheduler.
 *
 * \param  pDecal Pointer to an allocated decal.
 * \return None.
 */
void ENG_Scheduler_AddDecal(ENG_Decal *pDecal)
{
    pDecal->pNext             = ENG_scheduler.pFirstDecal;
    ENG_scheduler.pFirstDecal = pDecal;
}

/*!
 * \brief  Function to add an effect to the scheduler.
 *
 * \param  pEffect Pointer to an allocated effect.
 * \return None.
 */
void ENG_Scheduler_AddEffect(ENG_Effect *pEffect)
{
    pEffect->pNext             = ENG_scheduler.pFirstEffect;
    ENG_scheduler.pFirstEffect = pEffect;
}

/*!
 * \brief  Function to update the scheduler.
 *
 * \return None.
 */
void ENG_Scheduler_Update(void)
{
    ENG_Effect *pLastEffect    = NULL;
    ENG_Effect *pCurrentEffect = ENG_scheduler.pFirstEffect;
    Uint32      iTime          = SDL_GetTicks( );

    /* ~~~ Update the effects ~~~ */
    while (pCurrentEffect)
    {
        ENG_Effect_Think(pCurrentEffect, iTime);

        /* ~~~ Should be removed ? ~~~ */
        if (pCurrentEffect->bKillMe)
        {
            ENG_Effect_Die(pCurrentEffect);

            if (pLastEffect)
            {
                pLastEffect->pNext = pCurrentEffect->pNext;
                ENG_Effect_Free(&pCurrentEffect);
                pCurrentEffect = pLastEffect->pNext;
            }
            else
            {
                ENG_scheduler.pFirstEffect = ENG_scheduler.pFirstEffect->pNext;
                ENG_Effect_Free(&pCurrentEffect);
                pCurrentEffect = ENG_scheduler.pFirstEffect;
            }
        }
        else
        {
            pLastEffect    = pCurrentEffect;
            pCurrentEffect = pCurrentEffect->pNext;
        }
    }
}

/*!
 * \brief  Function to draw the scheduler.
 *
 * \return None.
 */
void ENG_Scheduler_Draw(void)
{
    ENG_Decal  *pCurrentDecal  = NULL;
    ENG_Effect *pCurrentEffect = NULL;
    Uint32      iLayer         = 0;
    Uint32      iMaxLayer      = ENG_Layer_GetMax( );

    /* ~~~ Draw for each layer (0 => Ground ; MaxLayer => Sky) ~~~ */
    for (iLayer = 0 ; iLayer < iMaxLayer ; ++iLayer)
    {
        pCurrentDecal  = ENG_scheduler.pFirstDecal;
        pCurrentEffect = ENG_scheduler.pFirstEffect;

        /* ~~~ Draw the decals ~~~ */
        while (pCurrentDecal)
        {
            ENG_Decal_Draw(pCurrentDecal, iLayer);
            pCurrentDecal = pCurrentDecal->pNext;
        }

        /* ~~~ Draw the effects ~~~ */
        while (pCurrentEffect)
        {
            ENG_Effect_Draw(pCurrentEffect, iLayer);
            pCurrentEffect = pCurrentEffect->pNext;
        }
    }
}

/*!
 * \brief  Function to free the scheduler.
 *
 * \return None.
 */
void ENG_Scheduler_Free(void)
{
    ENG_Decal  *pCurrentDecal  = ENG_scheduler.pFirstDecal;
    ENG_Effect *pCurrentEffect = ENG_scheduler.pFirstEffect;

    /* ~~~ Free the decals ~~~ */
    while (pCurrentDecal)
    {
        ENG_scheduler.pFirstDecal = ENG_scheduler.pFirstDecal->pNext;
        ENG_Decal_Free(&pCurrentDecal);
        pCurrentDecal = ENG_scheduler.pFirstDecal;
    }

    /* ~~~ Free the effects ~~~ */
    while (pCurrentEffect)
    {
        ENG_scheduler.pFirstEffect = ENG_scheduler.pFirstEffect->pNext;
        ENG_Effect_Free(&pCurrentEffect);
        pCurrentEffect = ENG_scheduler.pFirstEffect;
    }
}

/* ========================================================================= */
