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

#include "ENG_Effect.h"
#include "ENG_Scheduler.h"

/* ========================================================================= */

/*!
 * \struct ENG_Scheduler
 * \brief  Structure to handle the scheduler.
 */
typedef struct
{
    ENG_Effect *pFirst; /*!< Pointer to the first effect. */
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
    ENG_scheduler.pFirst = NULL;
}

/*!
 * \brief  Function to add an effect to the scheduler.
 *
 * \param  pEffect Pointer to an allocated effect.
 * \return None.
 */
void ENG_Scheduler_AddEffect(ENG_Effect *pEffect)
{
    pEffect->pNext       = ENG_scheduler.pFirst;
    ENG_scheduler.pFirst = pEffect;
}

/*!
 * \brief  Function to update the scheduler.
 *
 * \return None.
 */
void ENG_Scheduler_Update(void)
{
    ENG_Effect *pLast    = NULL;
    ENG_Effect *pCurrent = ENG_scheduler.pFirst;
    Uint32      iTime    = SDL_GetTicks( );

    while (pCurrent)
    {
        /* Think ? */
        if (pCurrent->iNextThink && pCurrent->iNextThink < iTime)
        {
            pCurrent->iNextThink = 0;

            if (pCurrent->pftThink)
            {
                pCurrent->pftThink(pCurrent);
            }
        }

        /* Die ? */
        if (pCurrent->bKillMe)
        {
            if (pLast)
            {
                pLast->pNext = pCurrent->pNext;

                UTIL_Free(pCurrent->pData);
                UTIL_Free(pCurrent);

                pCurrent = pLast->pNext;
            }
            else
            {
                ENG_scheduler.pFirst = ENG_scheduler.pFirst->pNext;

                UTIL_Free(pCurrent->pData);
                UTIL_Free(pCurrent);

                pCurrent = ENG_scheduler.pFirst;
            }
        }
        else
        {
            pLast    = pCurrent;
            pCurrent = pCurrent->pNext;
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
    ENG_Effect *pCurrent = ENG_scheduler.pFirst;

    while (pCurrent)
    {
        if (pCurrent->pftDraw)
        {
            pCurrent->pftDraw(pCurrent);
        }

        pCurrent = pCurrent->pNext;
    }
}

/*!
 * \brief  Function to free the scheduler.
 *
 * \return None.
 */
void ENG_Scheduler_Free(void)
{
    ENG_Effect *pCurrent = ENG_scheduler.pFirst;

    while (pCurrent)
    {
        ENG_scheduler.pFirst = ENG_scheduler.pFirst->pNext;

        UTIL_Free(pCurrent->pData);
        UTIL_Free(pCurrent);

        pCurrent = ENG_scheduler.pFirst;
    }
}

/* ========================================================================= */
