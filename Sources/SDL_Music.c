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
 * \param  pMusic Pointer to a loaded music.
 * \param  iLoops Number of times the music must be looped.
 * \return None.
 */
void SDL_Music_Play(SDL_Music *pMusic, Sint32 iLoops)
{
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
* \brief  Function to set the volume of the music.
*
* \param  iVolume the value of the volume (0 - 100%)
* \return None.
*/
void SDL_Music_SetVolume(Uint32 iVolume)
{
    if (iVolume > 100) iVolume = 100;

    SDL_Music_Volume = (Uint32)(iVolume * MIX_MAX_VOLUME / 100.0);
    Mix_VolumeMusic(SDL_Music_Volume);
    COM_Log_Print(COM_LOG_INFO, "Music Volume is set to %d %%", iVolume);
}

/*!
* \brief  Function to get the volume of the music
*
* \return the value of the volume (0 - 100%).
*/
Uint32 SDL_Music_GetVolume(void)
{
    return SDL_Music_Volume;
}
/* ========================================================================= */
