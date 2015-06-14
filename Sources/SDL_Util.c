/* ========================================================================= */
/*!
 * \file    SDL_Util.c
 * \brief   File to handle the 'SDL' util functions.
 * \author  Nyuu / Orlyn / Red
 * \version 1.0
 * \date    13 June 2015
 */
/* ========================================================================= */
/* Author  | Date     | Comments                                             */
/* --------+----------+----------------------------------------------------- */
/* Nyuu    | 13/06/15 | Creation.                                            */
/* ========================================================================= */

#include "SDL_Context.h"
#include "SDL_Util.h"

/* ========================================================================= */

/*!
 * \brief  Function to load a texture from a RWops.
 * \param  szPath       Path of the texture (Only useful for logs).
 * \param  pRWops       Pointer to a RWops.
 * \param  pTextureSize Size of the texture (Can be NULL)
 * \return A pointer to the loaded texture, or NULL if error.
 */
SDL_Texture *UTIL_TextureLoadRW(const char *szPath, SDL_RWops *pRWops, SDL_Rect *pTextureSize)
{
    SDL_Surface *pSurface = IMG_LoadPNG_RW(pRWops); // Only PNG are allowed.
    SDL_Texture *pTexture = NULL;

    if (pSurface == NULL)
    {
        COM_Log_Print(COM_LOG_ERROR, "Can't load the image ( Corrupted data ? ) !");
        COM_Log_Print(COM_LOG_ERROR, ">> Path \"%s\".\n", szPath);
    }
    else
    {
        if (pTextureSize)
        {
            pTextureSize->w = pSurface->w;
            pTextureSize->h = pSurface->h;
        }

        pTexture = SDL_Ctx_CreateTextureFromSurface(pSurface);

        if (pTexture == NULL)
        {
            COM_Log_Print(COM_LOG_CRITICAL, "Can't create a texture from the image !");
            COM_Log_Print(COM_LOG_CRITICAL, ">> Path \"%s\".\n", szPath);
        }

        SDL_FreeSurface(pSurface);
    }

    return pTexture;
}

/*!
 * \brief  Function to load a texture.
 * \param  szPath       Path of the texture to open.
 * \param  pTextureSize Size of the texture (Can be NULL)
 * \return A pointer to the loaded texture, or NULL if error.
 */
SDL_Texture *UTIL_TextureLoad(const char *szPath, SDL_Rect *pTextureSize)
{
    SDL_RWops   *pRWops   = SDL_RWFromFile(szPath, "rb");
    SDL_Texture *pTexture = NULL;

    if (pRWops == NULL)
    {
        COM_Log_Print(COM_LOG_ERROR, "Can't open an image !");
        COM_Log_Print(COM_LOG_ERROR, ">> Path \"%s\".\n", szPath);
    }
    else
    {
        pTexture = UTIL_TextureLoadRW(szPath, pRWops, pTextureSize);
        SDL_FreeRW(pRWops);
    }

    return pTexture;
}

/*!
 * \brief  Function to free a texture.
 * \param  ppTexture Pointer to pointer to the texture to free.
 * \return None.
 */
void UTIL_TextureFree(SDL_Texture **ppTexture)
{
    if (*ppTexture != NULL)
    {
        SDL_DestroyTexture(*ppTexture);
        *ppTexture = NULL;
    }
}

/*!
 * \brief  Function to load a music.
 * \param  szPath Path of the music to open.
 * \return A pointer to the loaded music, or NULL if error.
 */
Mix_Music *UTIL_MusicLoad(const char *szPath)
{
    Mix_Music *pMusic = Mix_LoadMUS(szPath);

    if (pMusic == NULL)
    {
        COM_Log_Print(COM_LOG_ERROR, "Can't load a music !");
        COM_Log_Print(COM_LOG_ERROR, ">> Path \"%s\".\n", szPath);
    }

    return pMusic;
}

/*!
 * \brief  Function to free a music.
 * \param  ppMusic Pointer to pointer to the music to free.
 * \return None.
 */
void UTIL_MusicFree(Mix_Music **ppMusic)
{
    if (*ppMusic != NULL)
    {
        Mix_FreeMusic(*ppMusic);
        *ppMusic = NULL;
    }
}

/*!
 * \brief  Function to load a chunk.
 * \param  szPath Path of the chunk to open.
 * \return A pointer to the loaded chunk, or NULL if error.
*/
Mix_Chunk *UTIL_ChunkLoad(const char *szPath)
{
    Mix_Chunk *pChunk = Mix_LoadWAV(szPath);

    if (pChunk == NULL)
    {
        COM_Log_Print(COM_LOG_ERROR, "Can't load a sound !");
        COM_Log_Print(COM_LOG_ERROR, ">> Path \"%s\".\n", szPath);
    }

    return pChunk;
}

/*!
 * \brief  Function to free a chunk.
 * \param  ppChunk Pointer to pointer to the chunk to free.
 * \return None.
 */
void UTIL_ChunkFree(Mix_Chunk **ppChunk)
{
    if (*ppChunk != NULL)
    {
        Mix_FreeChunk(*ppChunk);
        *ppChunk = NULL;
    }
}

/*!
 * \brief  Function to check if a point is inside a rectangle.
 * \param  x     Position on x.
 * \param  y     Position on y.
 * \param  pRect Pointer to the rectangle to check.
 * \return 1 is success, else 0.
 */
int UTIL_ContainPoint(Sint32 x, Sint32 y, SDL_Rect *pRect)
{
    return (( x >= pRect->x ) && 
            ( x < pRect->x + pRect->w ) && 
            ( y >= pRect->y ) && 
            ( y < pRect->y + pRect->h ));
}

/* ========================================================================= */
