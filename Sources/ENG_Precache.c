/* ========================================================================= */
/*!
 * \file    ENG_Precache.c
 * \brief   File to handle the precache.
 * \author  Nyuu / Orlyn / Red
 * \version 1.0
 * \date    15 June 2015
 */
/* ========================================================================= */
/* Author  | Date     | Comments                                             */
/* --------+----------+----------------------------------------------------- */
/* Nyuu    | 15/06/15 | Creation.                                            */
/* ========================================================================= */

#include "ENG_Precache.h"

/* ========================================================================= */

/*!
 * \struct ENG_Precache
 * \brief  Structure to handle the precache.
 */
typedef struct
{
    SDL_Sprite **pArrSprites; /*!< Array of sprites precached. */
    SDL_Sound  **pArrSounds;  /*!< Array of sounds precached. */

    Uint32       iNbSprites;  /*!< Number of sprites precached. */
    Uint32       iNbSounds;   /*!< Number of sounds precached. */
} ENG_Precache;

/*! Global variable to handle the precache. */
static ENG_Precache ENG_precache;

/* ========================================================================= */

/* ========================================================================= */
