/* ========================================================================= */
/*!
 * \file    SDL_Sound.h
 * \brief   File to interface with the sounds.
 * \author  Nyuu / Orlyn / Red
 * \version 1.0
 * \date    13 June 2015
 */
/* ========================================================================= */
/* Author  | Date     | Comments                                             */
/* --------+----------+----------------------------------------------------- */
/* Nyuu    | 13/06/15 | Creation.                                            */
/* ========================================================================= */

#ifndef __SDL_SOUND_H__
#define __SDL_SOUND_H__

    #include "SDL_Shared.h"



    /*!
     * \struct SDL_Sound
     * \brief  Structure to handle a sound.
     */
    typedef struct
    {
        char      *szName;    /*!< Name of the sound */
        Mix_Chunk *pMixChunk; /*!< Pointer to the sound */
    } SDL_Sound;

    SDL_Sound  *SDL_Sound_Alloc(const char *szSndName);
    const char *SDL_Sound_GetName(const SDL_Sound *pSound);
    void        SDL_Sound_Play(SDL_Sound *pSound, Uint32 iChannel, Uint32 iVolume, Sint32 iLoops);
    void        SDL_Sound_Free(SDL_Sound **ppSound);
    void        SDL_Sound_SetGlobalVolume(Uint32 iVolume);
    Uint32      SDL_Sound_GetGlobalVolume(void);
#endif // __SDL_SOUND_H__

/* ========================================================================= */
