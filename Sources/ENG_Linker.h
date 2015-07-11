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
    
    /*!
     * \struct ENG_DecalInfo
     * \brief  Structure to handle the info of a decal.
     */
    typedef struct
    {
        const char   *szName;    /*!< Pointer to the decal name. */
        const char   *szSprName; /*!< Pointer to the sprite name. */
        const Uint32  iFrame;    /*!< Index of the sprite frame. */
    } ENG_DecalInfo;

    /*!
     * \struct ENG_EffectInfo
     * \brief  Structure to handle the info of a effect.
     */
    typedef struct
    {
        const char            *szName;        /*!< Pointer to the effect name. */
        const Uint32           iPrivDataSize; /*!< Size of the effect private data. */
        const ENG_EffectTable *pTable;        /*!< Pointer to the effect table. */
    } ENG_EffectInfo;

    void        ENG_Linker_Init          (void);
    void        ENG_Linker_RegisterDecal (const ENG_DecalInfo  * const pDclInfo);
    void        ENG_Linker_RegisterEffect(const ENG_EffectInfo * const pEffInfo);
    ENG_Decal  *ENG_Linker_SpawnDecal    (Uint32 iDclIdx, const SDL_Point *pOrigin, const Uint32 iLayer);
    ENG_Effect *ENG_Linker_SpawnEffect   (Uint32 iEffIdx, const SDL_Point *pOrigin, const Uint32 iLayer);
    void        ENG_Linker_Free          (void);

#endif // __ENG_LINKER_H__

/* ========================================================================= */
