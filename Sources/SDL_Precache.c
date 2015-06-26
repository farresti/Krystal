/* ========================================================================= */
/*!
 * \file    SDL_Precache.c
 * \brief   File to handle the precache.
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
 
#include "SDL_Precache.h"

/* ========================================================================= */

/*!
 * \struct SDL_Precache
 * \brief  Structure to handle the precache.
 */
typedef struct
{
    SDL_Sprite **pArrSprites; /*!< Array of sprites precached. */
    SDL_Sound  **pArrSounds;  /*!< Array of sounds precached. */
 
    Uint32       iNbSprites;  /*!< Number of sprites precached. */
    Uint32       iNbSounds;   /*!< Number of sounds precached. */
} SDL_Precache;
 
/*! Global variable to handle the precache. */
static SDL_Precache SDL_precache;
 
/* ========================================================================= */
 
/*!
 * \brief  Function to initialize the precache.
 *
 * \return None.
 */
void SDL_Precache_Init(void)
{
    SDL_precache.iNbSprites  = 0;
    SDL_precache.iNbSounds   = 0;
    SDL_precache.pArrSprites = NULL;
    SDL_precache.pArrSounds  = NULL;
}

/*!
 * \brief Function to precache a sprite.
 *
 * \param  szSprName Name of the sprite.
 * \return A pointer to the loaded sprite, or NULL if error.
 */
SDL_Sprite *SDL_Precache_Sprite(const char *szSprName)
{
    const char *pSprName = NULL;
    SDL_Sprite *pSprite  = NULL;
    Uint32      iNumSprite;
    Uint32      iNewSize;
 
    /* Check if the sprite has already been precached */
    for (iNumSprite = 0 ; iNumSprite < SDL_precache.iNbSprites ; ++iNumSprite)
    {
        pSprName = SDL_Sprite_GetName(SDL_precache.pArrSprites[iNumSprite]);

        if (strcmp(pSprName, szSprName) == 0)
        {
            pSprite = SDL_precache.pArrSprites[iNumSprite];
        }        
    }
    
    /* If the sprite is not in the precache */
    if (pSprite == NULL)
    {
        pSprite = SDL_Sprite_Alloc(szSprName);
        
        if (pSprite)
        {
            iNewSize                 = sizeof(SDL_Sprite *) * (SDL_precache.iNbSprites + 1);
            SDL_precache.pArrSprites = (SDL_Sprite **) UTIL_Realloc(SDL_precache.pArrSprites, iNewSize);
            
            if (SDL_precache.pArrSprites)
            {
                SDL_precache.pArrSprites[SDL_precache.iNbSprites] = pSprite;
                SDL_precache.iNbSprites++;

                COM_Log_Print(COM_LOG_INFO, "Precache sprite: \"%s\".", szSprName);
            }
        }
    }
    
    return pSprite;
}
 
/*!
 * \brief  Function to precache a sound.
 *
 * \param  szSndName Name of the sound.
 * \return A pointer to the loaded sound, or NULL if error.
 */
SDL_Sound *SDL_Precache_Sound(const char *szSndName)
{
    const char *pSndName = NULL;
    SDL_Sound  *pSound   = NULL;
    Uint32      iNumSound;
    Uint32      iNewSize;
 
    /* Check if the sound has already been precached */
    for (iNumSound = 0 ; iNumSound < SDL_precache.iNbSounds ; ++iNumSound)
    {
        pSndName = SDL_Sound_GetName(SDL_precache.pArrSounds[iNumSound]);

        if (strcmp(pSndName, szSndName) == 0)
        {
            pSound = SDL_precache.pArrSounds[iNumSound];
        }
    }
    
    /* If the sound is not in the precache */
    if (pSound == NULL)
    {
        pSound = SDL_Sound_Alloc(szSndName);
 
        if (pSound)
        {
            iNewSize                = sizeof(SDL_Sound *) * (SDL_precache.iNbSounds + 1);
            SDL_precache.pArrSounds = (SDL_Sound **) UTIL_Realloc(SDL_precache.pArrSounds, iNewSize);
            
            if (SDL_precache.pArrSounds)
            {
                SDL_precache.pArrSounds[SDL_precache.iNbSounds] = pSound;
                SDL_precache.iNbSounds++;
                
                COM_Log_Print(COM_LOG_INFO, "Precache sound: \"%s\".", szSndName);
            }
        }
    }
 
    return pSound;
}
 
/*!
 * \brief  Function to free the precache
 *
 * \return None.
 */
void SDL_Precache_Free(void)
{
    Uint32 iNumSprite;
    Uint32 iNumSound;
    
    if (SDL_precache.pArrSprites)
    {
        for (iNumSprite = 0 ; iNumSprite < SDL_precache.iNbSprites ; ++iNumSprite)
        {
            SDL_Sprite_Free(&SDL_precache.pArrSprites[iNumSprite]);
        }
        
        SDL_precache.iNbSprites = 0;
        UTIL_Free(SDL_precache.pArrSprites);
    }
 
    if (SDL_precache.pArrSounds)
    {
        for (iNumSound = 0 ; iNumSound < SDL_precache.iNbSounds ; ++iNumSound)
        {
            SDL_Sound_Free(&SDL_precache.pArrSounds[iNumSound]);
        }
 
        SDL_precache.iNbSounds = 0;
        UTIL_Free(SDL_precache.pArrSounds);
    }
}

/* ========================================================================= */
