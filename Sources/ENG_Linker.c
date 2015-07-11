/* ========================================================================= */
/*!
 * \file    ENG_Linker.c
 * \brief   File to handle the linker.
 * \author  Nyuu / Orlyn / Red
 * \version 1.0
 * \date    04 July 2015
 */
/* ========================================================================= */
/* Author  | Date     | Comments                                             */
/* --------+----------+----------------------------------------------------- */
/* Nyuu    | 04/07/15 | Creation.                                            */
/* ========================================================================= */

#include "ENG_Scheduler.h"
#include "ENG_Linker.h"

/* ========================================================================= */

/*!
 * \struct ENG_DecalLink
 * \brief  Structure to handle a new decal.
 */
typedef struct
{
    const ENG_DecalInfo *pInfo;   /*!< Pointer to the decal info. */
    SDL_Sprite          *pSprite; /*!< Pointer to the decal sprite. */
} ENG_DecalLink;

/*!
 * \struct ENG_EffectLink
 * \brief  Structure to handle a new effect.
 */
typedef struct
{
    const ENG_EffectInfo *pInfo; /*!< Pointer to the effect info. */
} ENG_EffectLink;

/*!
 * \struct ENG_Linker
 * \brief  Structure to handle the linker.
 */
typedef struct
{
    ENG_DecalLink  *pArrDecals;  /*!< Array of decals registered. */
    ENG_EffectLink *pArrEffects; /*!< Array of effects registered. */

    Uint32          iNbDecals;   /*!< Number of decals registered. */
    Uint32          iNbEffects;  /*!< Number of effects registered. */
} ENG_Linker;

/*! Global variable to handle the linker. */
static ENG_Linker ENG_linker;

/* ========================================================================= */

/*!
 * \brief  Function to init the linker.
 *
 * \return None.
 */
void ENG_Linker_Init(void)
{
    ENG_linker.iNbDecals   = 0;
    ENG_linker.iNbEffects  = 0;

    ENG_linker.pArrDecals  = NULL;
    ENG_linker.pArrEffects = NULL;
}

/*!
 * \brief  Function to register a decal in the linker.
 *
 * \param  pDclInfo Pointer to the decal info.
 * \return None.
 */
void ENG_Linker_RegisterDecal(const ENG_DecalInfo * const pDclInfo)
{
    ENG_DecalLink *pDecalLink = NULL;
    SDL_Sprite    *pSprite    = NULL;
    Uint32         iNewSize   = 0;

    pSprite = SDL_Precache_Sprite(pDclInfo->szSprName);

    if (pSprite)
    {
        iNewSize = sizeof(ENG_DecalLink) * (ENG_linker.iNbDecals + 1);
        ENG_linker.pArrDecals = (ENG_DecalLink *) UTIL_Realloc(ENG_linker.pArrDecals, iNewSize);

        if (ENG_linker.pArrDecals)
        {
            pDecalLink          = &(ENG_linker.pArrDecals[ENG_linker.iNbDecals]);
            pDecalLink->pInfo   = pDclInfo;
            pDecalLink->pSprite = pSprite;

            COM_Log_Print(COM_LOG_INFO, "Register decal: \"%s\".", pDclInfo->szName);
            ENG_linker.iNbDecals++;
        }
    }
}

/*!
 * \brief  Function to register an effect in the linker.
 *
 * \param  pEffInfo Pointer to the effect info.
 * \return None.
 */
void ENG_Linker_RegisterEffect(const ENG_EffectInfo * const pEffInfo)
{
    ENG_EffectLink *pEffectLink = NULL;
    Uint32          iNewSize    = 0;

    iNewSize = sizeof(ENG_EffectLink) * (ENG_linker.iNbEffects + 1);
    ENG_linker.pArrEffects = (ENG_EffectLink *) UTIL_Realloc(ENG_linker.pArrEffects, iNewSize);

    if (ENG_linker.pArrDecals)
    {
        pEffectLink        = &(ENG_linker.pArrEffects[ENG_linker.iNbEffects]);
        pEffectLink->pInfo = pEffInfo;

        COM_Log_Print(COM_LOG_INFO, "Register effect: \"%s\".", pEffInfo->szName);
        ENG_linker.iNbEffects++;
    }
}

/*!
 * \brief  Function to spawn a decal.
 *
 * \param  iDclIdx Index of the decal.
 * \param  pOrigin Pointer to the decal origin.
 * \param  iLayer  Index of the decal layer.
 * \return A pointer to the allocated decal, or NULL if error.
 */
ENG_Decal *ENG_Linker_SpawnDecal(Uint32 iDclIdx, const SDL_Point *pOrigin, const Uint32 iLayer)
{
    ENG_DecalLink *pDecalLink = NULL;
    ENG_Decal     *pDecal     = NULL;

    if (iDclIdx < ENG_linker.iNbDecals)
    {
        pDecal = ENG_Decal_Alloc( );

        if (pDecal)
        {
            pDecalLink = &(ENG_linker.pArrDecals[iDclIdx]);

            ENG_Decal_SetOrigin(pDecal, pOrigin);
            ENG_Decal_SetLayer (pDecal, iLayer);
            ENG_Decal_SetSprite(pDecal, pDecalLink->pSprite);
            ENG_Decal_SetFrame (pDecal, pDecalLink->pInfo->iFrame);

            ENG_Scheduler_AddDecal(pDecal);
        }
    }
    else
    {
        COM_Log_Print(COM_LOG_WARNING, "Invalid decal index: %d ( Max: %d ) !", iDclIdx, ENG_linker.iNbDecals);
    }

    return pDecal;
}

/*!
 * \brief  Function to spawn an effect.
 *
 * \param  iEffIdx Index of the effect.
 * \param  pOrigin Pointer to the effect origin.
 * \param  iLayer  Index of the effect layer.
 * \return A pointer to the allocated effect, or NULL if error.
 */
ENG_Effect *ENG_Linker_SpawnEffect(Uint32 iEffIdx, const SDL_Point *pOrigin, const Uint32 iLayer)
{
    ENG_EffectLink *pEffectLink = NULL;
    ENG_Effect     *pEffect     = NULL;

    if (iEffIdx < ENG_linker.iNbEffects)
    {
        pEffectLink = &(ENG_linker.pArrEffects[iEffIdx]);
        pEffect     = ENG_Effect_Alloc(pEffectLink->pInfo->iPrivDataSize);

        if (pEffect)
        {
            ENG_Effect_SetLayer (pEffect, iLayer);
            ENG_Effect_SetTable (pEffect, pEffectLink->pInfo->pTable);
            ENG_Effect_Spawn    (pEffect, pOrigin);

            ENG_Scheduler_AddEffect(pEffect);
        }
    }
    else
    {
        COM_Log_Print(COM_LOG_WARNING, "Invalid effect index: %d ( Max: %d ) !", iEffIdx, ENG_linker.iNbEffects);
    }

    return pEffect;
}

/*!
 * \brief  Function to free the linker.
 *
 * \return None.
 */
void ENG_Linker_Free(void)
{
    ENG_linker.iNbDecals  = 0;
    ENG_linker.iNbEffects = 0;

    UTIL_Free(ENG_linker.pArrDecals);
    UTIL_Free(ENG_linker.pArrEffects);
}

/* ========================================================================= */
