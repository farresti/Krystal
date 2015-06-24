/* ========================================================================= */
/*!
 * \file    SDL_Music.c
 * \brief   File to handle the musics.
 * \author  Nyuu / Orlyn / Red
 * \version 1.0
 * \date    13 June 2015
 */
/* ========================================================================= */
/* Author  | Date     | Comments                                             */
/* --------+----------+----------------------------------------------------- */
/* Nyuu    | 13/06/15 | Creation.                                            */
/* Red     | 13/06/15 | Add Alloc.                                           */
/* ========================================================================= */

#include "SDL_Util.h"
#include "SDL_Music.h"

/* ========================================================================= */

/*! Global variable to handle the volume of the music 0 - 100 */
static Uint32 SDL_Music_volume = 100;

/*!
 * \brief  Function to load a music.
 *
 * \param  szMscName Name of the music. 
 * \return A pointer to the loaded music, or NULL if error.
 */
SDL_Music *SDL_Music_Alloc(const char *szMscName)
{
    SDL_Music  *pMusic       = NULL;
    char       *szMusicPath = NULL;

    szMusicPath = UTIL_StrBuild("musics/", szMscName, ".mp3", NULL);

    if (szMusicPath)
    {
        pMusic = (SDL_Music *)UTIL_Malloc(sizeof(SDL_Music));

        if (pMusic)
        {
            pMusic->pMixData = UTIL_MusicLoad(szMusicPath);
            pMusic->szName   = UTIL_StrCopy(szMscName);

            if (!pMusic->pMixData || !pMusic->szName) // Error: must free...
            {
                UTIL_MusicFree(&pMusic->pMixData);
                UTIL_Free(pMusic->szName);
                UTIL_Free(pMusic);
            }
        }

        UTIL_Free(szMusicPath);
    }

    return pMusic;
}

/*!
 * \brief  Function to play a music.
 *
 * \param  pMusic  Pointer to a loaded music.
 * \param  iVolume Volume to play the sound (0 - 128).
 * \param  iLoops  Number of times the music must be looped.
 * \return None.
 */
void SDL_Music_Play(SDL_Music *pMusic, Uint32 iVolume, Sint32 iLoops)
{
    iVolume = ((iVolume * SDL_Music_volume) / 100);
    Mix_VolumeMusic(iVolume);
    Mix_PlayMusic(pMusic->pMixData, iLoops);
}

/*!
 * \brief  Function to free a music.
 *
 * \param  ppMusic Pointer to pointer to the music to free.
 * \return None.
 */
void SDL_Music_Free(SDL_Music **ppMusic)
{
    UTIL_Free((*ppMusic)->szName );
    UTIL_MusicFree( &( *ppMusic )->pMixData );
    UTIL_Free(*ppMusic);
}

/*!
* \brief  Function to set the global volume of the music.
*
* \param  iVolume the value of the global volume (0 - 100%).
* \return None.
*/
void SDL_Music_SetGlobalVolume(Uint32 iVolume)
{
    if (iVolume > 100) iVolume = 100;

    SDL_Music_volume = iVolume;

    COM_Log_Print(COM_LOG_INFO, "Music Volume is set to %d %%", SDL_Music_volume);
}

/*!
* \brief  Function to get the volume of the music.
*
* \return the value of the volume (0 - 100%).
*/
Uint32 SDL_Music_GetGlobalVolume(void)
{
    return SDL_Music_volume;
}

/*!
* \brief  Function to set the volume of the current music
*
* \param  iVolume the value of the volume (0 - 128)
* \return None.
*/
void SDL_Music_SetVolume(Uint32 iVolume)
{
    iVolume = ((iVolume * SDL_Music_volume) / 100);
    Mix_VolumeMusic(iVolume);
}
/* ========================================================================= */
