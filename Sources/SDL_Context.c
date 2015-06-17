/* ========================================================================= */
/*!
 * \file    SDL_Context.c
 * \brief   File to handle the context.
 * \author  Nyuu / Orlyn / Red
 * \version 1.0
 * \date    09 June 2015
 */
/* ========================================================================= */
/* Author  | Date     | Comments                                             */
/* --------+----------+----------------------------------------------------- */
/* Nyuu    | 09/06/15 | Creation.                                            */
/* Orlyn   | 10/06/15 | Add new functions SDL_CONTEXT_*                      */
/* ========================================================================= */

#include "SDL_Context.h"

/* ========================================================================= */

/*!
 * \struct SDL_Context
 * \brief  Structure to handle the context.
 */
typedef struct
{
    SDL_Renderer *pRenderer; /*!< Pointer to the renderer. */
    SDL_Window   *pWindow;   /*!< Pointer to the window. */
} SDL_Context;

/*! Global variable to handle the context. */
static SDL_Context SDL_context;

/* ========================================================================= */

/*!
 * \brief Function to init the context.
 *
 * \param szWindowName Name of the window
 * \param iWidth       Width of the window
 * \param iHeight      Height of the window
 * \return SDL_TRUE is success, else SDL_FALSE.
 */
SDL_bool SDL_Ctx_Init(const char *szWindowName, int iWidth, int iHeight)
{
    SDL_Renderer *pRenderer = NULL;
    SDL_Window   *pWindow   = NULL;

    pWindow = SDL_CreateWindow(szWindowName,
                               SDL_WINDOWPOS_UNDEFINED,
                               SDL_WINDOWPOS_UNDEFINED,
                               iWidth,
                               iHeight,
                               SDL_WINDOW_SHOWN);

    if (pWindow != NULL)
    {
        pRenderer = SDL_CreateRenderer(pWindow, 
                                       -1, 
                                       SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        
        if (pRenderer != NULL)
        {
            SDL_context.pRenderer = pRenderer;
            SDL_context.pWindow   = pWindow;

            return SDL_TRUE;
        }

        SDL_DestroyWindow(pWindow);
    }

    return SDL_FALSE;
}

/*!
 * \brief Function to create a texture from a surface.
 *
 * \param pSurface Pointer to the surface.
 * \return A pointer to the texture created, or NULL if error.
 */
SDL_Texture *SDL_Ctx_CreateTextureFromSurface(SDL_Surface *pSurface)
{
    return SDL_CreateTextureFromSurface(SDL_context.pRenderer, pSurface);
}

/*!
 * \brief Function to clear the renderer context.
 *
 * \return None
 */
void SDL_Ctx_RenderClear(void)
{
    SDL_RenderClear(SDL_context.pRenderer);
}

/*!
 * \brief Function to copy a texture to the renderer.
 *
 * \param pTexture The texture to copy.
 * \param pSrc     Rectangle to clip the texture (Can be NULL).
 * \param pDest    Rectangle to position the texture (Can be NULL).
 * \return 0 on success, else -1 if error.
 */
int SDL_Ctx_RenderCopy(SDL_Texture *pTexture, SDL_Rect *pSrc, SDL_Rect *pDest)
{
    return SDL_RenderCopy(SDL_context.pRenderer, pTexture, pSrc, pDest);
}

/*!
 * \brief Function to copy a texture to the renderer.
 *
 * \param pTexture The texture to copy.
 * \param pSrc     Rectangle to clip the texture (Can be NULL).
 * \param pDest    Rectangle to position the texture (Can be NULL).
 * \param iFlip    Flag to flip the texture.
 * \return 0 on success, else -1 if error.
 */
int SDL_Ctx_RenderCopyEx(SDL_Texture *pTexture, SDL_Rect *pSrc, SDL_Rect *pDest, SDL_RendererFlip iFlip)
{
    return SDL_RenderCopyEx(SDL_context.pRenderer, pTexture, pSrc, pDest, 0.0, NULL, iFlip );
}

/*!
 * \brief Function to draw the renderer context.
 *
 * \return None
 */
void SDL_Ctx_RenderPresent(void)
{
    SDL_RenderPresent(SDL_context.pRenderer);
}

/*!
 * \brief Function to free the context.
 *
 * \return None
 */
void SDL_Ctx_Quit(void)
{
    SDL_DestroyWindow(SDL_context.pWindow);
    SDL_DestroyRenderer(SDL_context.pRenderer);

    SDL_context.pWindow   = NULL;
    SDL_context.pRenderer = NULL;
}

/* ========================================================================= */
