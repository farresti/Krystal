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
 *
 * \param  szPath       Path of the texture (Only useful for logs).
 * \param  pRWops       Pointer to a RWops.
 * \param  pTextureSize Rectangle to retrieve the size of the texture (Can be NULL).
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
 *
 * \param  szPath       Path of the texture to open.
 * \param  pTextureSize Rectangle to retrieve the size of the texture (Can be NULL).
 * \return A pointer to the loaded texture, or NULL if error.
 */
SDL_Texture *UTIL_TextureLoad(const char *szPath, SDL_Rect *pTextureSize)
{
    SDL_RWops   *pRWops   = UTIL_RWOpen(szPath, "rb");
    SDL_Texture *pTexture = NULL;

    if (pRWops)
    {
        pTexture = UTIL_TextureLoadRW(szPath, pRWops, pTextureSize);
        UTIL_RWClose(&pRWops);
    }

    return pTexture;
}

/*!
 * \brief  Function to free a texture.
 *
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
 * \brief Function to open a file using a RWops.
 *
 * \param szPath Path of the file to open.
 * \param szMode Mode used to open the file.
 * \return A pointer to the opened file using a RWops, or NULL if error.
 */
SDL_RWops *UTIL_RWOpen(const char *szPath, const char *szMode)
{
    SDL_RWops *pRw = SDL_RWFromFile(szPath, szMode);

    if (pRw == NULL)
    {
        COM_Log_Print(COM_LOG_ERROR, "Can't open a file (Mode : %s) !",
                                     strchr(szMode, 'r') ? "Read" : "Write");
        COM_Log_Print(COM_LOG_ERROR, "Path: \"%s\"", szPath);
    }
    
    return pRw;
}

/*!
 * \brief Function to close a RWops.
 *
 * \param ppRw Pointer to pointer to the RWops to close.
 * \return None.
 */
void UTIL_RWClose(SDL_RWops **ppRw)
{
    if (*ppRw != NULL)
    {
        SDL_FreeRW(*ppRw);
        *ppRw = NULL;
    }
}

/*!
 * \brief  Function to load a music.
 *
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
 *
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
 *
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
 *
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
 *
 * \param  pPt   Pointer to the point.
 * \param  pRect Pointer to the rectangle.
 * \return 1 is success, else 0.
 */
int UTIL_ContainPoint(const SDL_Point *pPt, const SDL_Rect *pRect)
{
    return (( pPt->x >= pRect->x            ) && 
            ( pPt->x <  pRect->x + pRect->w ) && 
            ( pPt->y >= pRect->y            ) && 
            ( pPt->y <  pRect->y + pRect->h ));
}

/*!
 * \brief  Function to check if two rectangles collide.
 *
 * \param  pRect1 Pointer to a rectangle.
 * \param  pRect2 Pointer to another rectangle.
 * \return 1 is success, else 0.
 */
int UTIL_CollideRect(const SDL_Rect *pRect1, const SDL_Rect *pRect2)
{
    return (!(( pRect2->x             >= pRect1->x + pRect1->w ) || 
              ( pRect2->x + pRect2->w <= pRect1->x             ) || 
              ( pRect2->y             >= pRect1->y + pRect1->h ) || 
              ( pRect2->y + pRect2->h <= pRect1->y             )));
}

/* ========================================================================= */
