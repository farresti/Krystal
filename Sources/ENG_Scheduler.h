/* ========================================================================= */
/*!
 * \file    ENG_Scheduler.h
 * \brief   File to interface with the scheduler.
 * \author  Nyuu / Orlyn / Red
 * \version 1.0
 * \date    28 June 2015
 */
/* ========================================================================= */
/* Author  | Date     | Comments                                             */
/* --------+----------+----------------------------------------------------- */
/* Nyuu    | 28/06/15 | Creation.                                            */
/* ========================================================================= */

#ifndef __ENG_SCHEDULER_H__
#define __ENG_SCHEDULER_H__

    #include "ENG_Shared.h"

    void ENG_Scheduler_Init(void);

    void ENG_Scheduler_AddEffect(ENG_Effect *pEffect);

    void ENG_Scheduler_Update(void);
    void ENG_Scheduler_Draw(void);
    void ENG_Scheduler_Free(void);

#endif // __ENG_SCHEDULER_H__

/* ========================================================================= */
