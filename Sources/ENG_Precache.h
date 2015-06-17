/* ========================================================================= */
/*!
 * \file    ENG_Precache.h
 * \brief   File to interface with the precache.
 * \author  Nyuu / Orlyn / Red
 * \version 1.0
 * \date    15 June 2015
 */
/* ========================================================================= */
/* Author  | Date     | Comments                                             */
/* --------+----------+----------------------------------------------------- */
/* Nyuu    | 15/06/15 | Creation.                                            */
/* Red     | 16/06/15 | Dev basics functions                                 */
/* ========================================================================= */
 
#ifndef __ENG_PRECACHE_H__
#define __ENG_PRECACHE_H__
 
    #include "ENG_Shared.h"
    
    void        ENG_Precache_Init(void);
    SDL_Sprite *ENG_Precache_LoadSprite(const char *szSprName);
    SDL_Sound  *ENG_Precache_LoadSound(const char *szSndName);
    void        ENG_Precache_Free(void);

#endif // __ENG_PRECACHE_H__

/* ========================================================================= */
