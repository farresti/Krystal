/* ========================================================================= */
/*!
 * \file    SDL_Precache.h
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
 
#ifndef __SDL_PRECACHE_H__
#define __SDL_PRECACHE_H__
 
    #include "SDL_Sprite.h"
    #include "SDL_Sound.h"
    
    void        SDL_Precache_Init(void);
    SDL_Sprite *SDL_Precache_Sprite(const char *szSprName);
    SDL_Sound  *SDL_Precache_Sound(const char *szSndName);
    void        SDL_Precache_Free(void);

#endif // __SDL_PRECACHE_H__

/* ========================================================================= */
