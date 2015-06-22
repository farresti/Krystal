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
/* Red     | 16/06/15 | Dev basics functions                                 */
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
 
/*!
 * \brief  Function to initialize the precache.
 *
 * \return None.
 */
void ENG_Precache_Init(void)
{
    ENG_precache.iNbSprites  = 0;
    ENG_precache.iNbSounds   = 0;
    ENG_precache.pArrSprites = NULL;
    ENG_precache.pArrSounds  = NULL;
}
 
/*!
 * \brief  Function to precache a sprite.
 *
 * \param  szSprName Name of the sprite.
 * \return A pointer to the loaded sprite, or NULL if error.
 */
SDL_Sprite *ENG_Precache_LoadSprite(const char *szSprName)
{
    const char *pSprName = NULL;
    SDL_Sprite *pSprite  = NULL;
    Uint32      iNumSprite;
    Uint32      iNewSize;
 
    /* Check if the sprite has already been precached */
    for (iNumSprite = 0 ; iNumSprite < ENG_precache.iNbSprites ; ++iNumSprite)
    {
        pSprName = SDL_Sprite_GetName(ENG_precache.pArrSprites[iNumSprite]);

        if (strcmp(pSprName, szSprName) == 0)
        {
            pSprite = ENG_precache.pArrSprites[iNumSprite];
        }        
    }
    
    /* If the sprite is not in the precache */
    if (pSprite == NULL)
    {
        pSprite = SDL_Sprite_Alloc(szSprName);
        
        if (pSprite)
        {
            iNewSize                 = sizeof(SDL_Sprite *) * (ENG_precache.iNbSprites + 1);
            ENG_precache.pArrSprites = (SDL_Sprite **) UTIL_Realloc(ENG_precache.pArrSprites, iNewSize);
            
            if (ENG_precache.pArrSprites)
            {
                ENG_precache.pArrSprites[ENG_precache.iNbSprites] = pSprite;
                ENG_precache.iNbSprites++;

                COM_Log_Print(COM_LOG_INFO, "Precache: \"%s.spr\"", szSprName);
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
SDL_Sound *ENG_Precache_LoadSound(const char *szSndName)
{
    const char *pSndName = NULL;
    SDL_Sound  *pSound   = NULL;
    Uint32      iNumSound;
    Uint32      iNewSize;
 
    /* Check if the sound has already been precached */
    for (iNumSound = 0 ; iNumSound < ENG_precache.iNbSounds ; ++iNumSound)
    {
        pSndName = SDL_Sound_GetName(ENG_precache.pArrSounds[iNumSound]);

        if (strcmp(pSndName, szSndName) == 0)
        {
            pSound = ENG_precache.pArrSounds[iNumSound];
        }
    }
    
    /* If the sound is not in the precache */
    if (pSound == NULL)
    {
        pSound = SDL_Sound_Alloc(szSndName);
 
        if (pSound)
        {
            iNewSize                = sizeof(SDL_Sound *) * (ENG_precache.iNbSounds + 1);
            ENG_precache.pArrSounds = (SDL_Sound **) UTIL_Realloc(ENG_precache.pArrSounds, iNewSize);
            
            if (ENG_precache.pArrSounds)
            {
                ENG_precache.pArrSounds[ENG_precache.iNbSounds] = pSound;
                ENG_precache.iNbSounds++;
                
                COM_Log_Print(COM_LOG_INFO, "Precache: \"%s.wav\"", szSndName);
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
void ENG_Precache_Free(void)
{
    Uint32 iNumSprite = 0;
    Uint32 iNumSound  = 0;
    
    if (ENG_precache.pArrSprites)
    {
        for (iNumSprite = 0 ; iNumSprite < ENG_precache.iNbSprites ; ++iNumSprite)
        {
            SDL_Sprite_Free(&ENG_precache.pArrSprites[iNumSprite]);
        }
       
        ENG_precache.iNbSprites = 0;
        UTIL_Free((ENG_precache.pArrSprites));
    }
 
    if (ENG_precache.pArrSounds)
    {
        for (iNumSound = 0 ; iNumSound < ENG_precache.iNbSounds ; ++iNumSound)
        {
            SDL_Sound_Free(&ENG_precache.pArrSounds[iNumSound]);
        }
 
        ENG_precache.iNbSounds = 0;
        UTIL_Free((ENG_precache.pArrSounds));
    }
}

/* ========================================================================= */
