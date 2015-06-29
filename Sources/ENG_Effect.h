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
     * \struct ENG_Effect
     * \brief  Structure to handle an effect.
     */
    struct ENG_Effect
    {
        SDL_Point sOrigin;              /*!< Origin of the effect. */
        SDL_Point sPosition;            /*!< Position of the effect. */
        Uint32    iLayer;               /*!< Layer to draw the effect. */
        Uint32    iNextThink;           /*!< Time before the next think must occur. */
        SDL_bool  bKillMe;              /*!< Flag to kill the effect. */

        void *pData;                    /*!< Pointer to the private data. */

        void (*pftThink)(ENG_Effect *); /*!< Function pointer 'Think'. */
        void (*pftDraw)(ENG_Effect *);  /*!< Function pointer 'Draw'. */

        ENG_Effect *pNext;              /*!< Pointer to the next effect. */
    };

    ENG_Effect *ENG_Effect_Alloc(Uint32 iDataSize);
    void        ENG_Effect_SetOrigin(ENG_Effect *pEffect, const SDL_Point *pOrigin);
    void        ENG_Effect_Kill(ENG_Effect *pEffect);

#endif // __ENG_EFFECT_H__

/* ========================================================================= */
