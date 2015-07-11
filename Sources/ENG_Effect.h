/* ========================================================================= */
/*!
 * \file    ENG_Effect.h
 * \brief   File to interface with the engine effects.
 * \author  Nyuu / Orlyn / Red
 * \version 1.0
 * \date    15 June 2015
 */
/* ========================================================================= */
/* Author  | Date     | Comments                                             */
/* --------+----------+----------------------------------------------------- */
/* Nyuu    | 15/06/15 | Creation.                                            */
/* ========================================================================= */

#ifndef __ENG_EFFECT_H__
#define __ENG_EFFECT_H__

    #include "ENG_Shared.h"
    
    /*! Typedef to handle an effect. */
    typedef struct ENG_Effect ENG_Effect;

    /*!
     * \struct ENG_EffectTable
     * \brief  Structure to handle the effect functions table.
     */
    typedef struct
    {
        void (*pftSpawn)(ENG_Effect *, const SDL_Point *); /*!< Function pointer 'Spawn'. */
        void (*pftThink)(ENG_Effect *);                    /*!< Function pointer 'Think'. */
        void (*pftDraw) (ENG_Effect *);                    /*!< Function pointer 'Draw'. */
        void (*pftDie)  (ENG_Effect *);                    /*!< Function pointer 'Die'. */
    } ENG_EffectTable;

    /*!
     * \struct ENG_Effect
     * \brief  Structure to handle an effect.
     */
    struct ENG_Effect
    {
        Uint32                 iLayer;     /*!< Layer to draw the decal. */
        Uint32                 iNextThink; /*!< Time before the next think must occur. */
        SDL_bool               bKillMe;    /*!< Flag to kill the effect. */

        void                  *pPrivData;  /*!< Pointer to the private data. */
        const ENG_EffectTable *pTable;     /*!< Pointer to the functions table. */
        ENG_Effect            *pNext;      /*!< Pointer to the next effect. */
    };

    void        ENG_Effect_SetLayer    (ENG_Effect *pEffect, const Uint32 iLayer);
    void        ENG_Effect_SetNextThink(ENG_Effect *pEffect, const Uint32 iNextThink);
    void        ENG_Effect_Kill        (ENG_Effect *pEffect);
    void       *ENG_Effect_GetPrivData (ENG_Effect *pEffect);

    /* ----- Use ONLY by the scheduler / linker ----- */
    ENG_Effect *ENG_Effect_Alloc       (Uint32 iPrivDataSize);
    void        ENG_Effect_SetTable    (ENG_Effect *pEffect, const ENG_EffectTable *pTable);
    void        ENG_Effect_Spawn       (ENG_Effect *pEffect, const SDL_Point *pOrigin);
    void        ENG_Effect_Think       (ENG_Effect *pEffect, const Uint32 iTime);
    void        ENG_Effect_Draw        (ENG_Effect *pEffect, const Uint32 iLayer);
    void        ENG_Effect_Die         (ENG_Effect *pEffect);
    void        ENG_Effect_Free        (ENG_Effect **ppEffect);
    /* ---------------------------------------------- */

#endif // __ENG_EFFECT_H__

/* ========================================================================= */
