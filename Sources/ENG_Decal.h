/* ========================================================================= */
/*!
 * \file    ENG_Decal.h
 * \brief   File to interface with the decals.
 * \author  Nyuu / Orlyn / Red
 * \version 1.0
 * \date    04 July 2015
 */
/* ========================================================================= */
/* Author  | Date     | Comments                                             */
/* --------+----------+----------------------------------------------------- */
/* Nyuu    | 04/07/15 | Creation.                                            */
/* ========================================================================= */

#ifndef __ENG_DECAL_H__
#define __ENG_DECAL_H__

    #include "ENG_Shared.h"
    
    /*! Typedef to handle a decal. */
    typedef struct ENG_Decal ENG_Decal;

    /*!
     * \struct ENG_Decal
     * \brief  Structure to handle a decal.
     */
    struct ENG_Decal
    {
        SDL_Point   sOrigin;   /*!< Origin of the decal. */
        SDL_Point   sPosition; /*!< Position of the decal. */
        Uint32      iLayer;    /*!< Layer to draw the decal. */
        SDL_Sprite *pSprite;   /*!< Pointer to the sprite to draw. */
        Uint32      iFrame;    /*!< Frame of the sprite to draw. */

        ENG_Decal  *pNext;     /*!< Pointer to the next decal. */
    };
    
    /* ----- Use ONLY by the scheduler / linker ----- */
    ENG_Decal *ENG_Decal_Alloc    (void);
    void       ENG_Decal_SetOrigin(ENG_Decal *pDecal, const SDL_Point *pOrigin);
    void       ENG_Decal_SetLayer (ENG_Decal *pDecal, const Uint32 iLayer);
    void       ENG_Decal_SetSprite(ENG_Decal *pDecal, SDL_Sprite *pSprite);
    void       ENG_Decal_SetFrame (ENG_Decal *pDecal, const Uint32 iFrame);
    void       ENG_Decal_Draw     (ENG_Decal *pDecal, const Uint32 iLayer);
    void       ENG_Decal_Free     (ENG_Decal **ppDecal);
    /* ---------------------------------------------- */

#endif // __ENG_DECAL_H__

/* ========================================================================= */
