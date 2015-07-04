/* ========================================================================= */
/*!
 * \file    ENG_Linker.h
 * \brief   File to interface with the linker.
 * \author  Nyuu / Orlyn / Red
 * \version 1.0
 * \date    04 July 2015
 */
/* ========================================================================= */
/* Author  | Date     | Comments                                             */
/* --------+----------+----------------------------------------------------- */
/* Nyuu    | 04/07/15 | Creation.                                            */
/* ========================================================================= */

#ifndef __ENG_LINKER_H__
#define __ENG_LINKER_H__

    #include "ENG_Decal.h"
    #include "ENG_Effect.h"
    
    void        ENG_Linker_Init          (void);
    void        ENG_Linker_RegisterDecal (const char *szName, const char *szSprName, const Uint32 iFrame);
    void        ENG_Linker_RegisterEffect(const char *szName, const Uint32 iDataSize, const ENG_EffectTable *pTable);
    ENG_Decal  *ENG_Linker_SpawnDecal    (Uint32 iDclIdx, const SDL_Point *pOrigin, const Uint32 iLayer);
    ENG_Effect *ENG_Linker_SpawnEffect   (Uint32 iEffIdx, const SDL_Point *pOrigin, const Uint32 iLayer, ...);
    void        ENG_Linker_Free          (void);

#endif // __ENG_LINKER_H__

/* ========================================================================= */
