/* ========================================================================= */
/*!
 * \file    SDL_Music.h
 * \brief   File to interface with the musics.
 * \author  Nyuu / Orlyn / Red
 * \version 1.0
 * \date    13 June 2015
 */
/* ========================================================================= */
/* Author  | Date     | Comments                                             */
/* --------+----------+----------------------------------------------------- */
/* Nyuu    | 13/06/15 | Creation.                                            */
/* ========================================================================= */

#ifndef __SDL_MUSIC_H__
#define __SDL_MUSIC_H__

    #include "SDL_Shared.h"

    /*!
     * \struct SDL_Music
     * \brief  Structure to handle a music.
     */
    typedef struct
    {
        char      *szName;   /*!< Name of the music */
        Mix_Music *pMixData; /*!< Pointer to the music data */
    } SDL_Music;

    SDL_Music *SDL_Music_Alloc(const char *szMscName);
    void       SDL_Music_Play(SDL_Music *pMusic, Uint32 iVolume, Sint32 iLoops);
    void       SDL_Music_Free(SDL_Music **ppMusic);
    void       SDL_Music_SetGlobalVolume(Uint32 iVolume);
    Uint32     SDL_Music_GetGlobalVolume(void);
    void       SDL_Music_SetVolume(Uint32 iVolume);
#endif // __SDL_MUSIC_H__

/* ========================================================================= */
