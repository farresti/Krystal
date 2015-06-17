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
 * \param pRectSrc A pointer to the source rectangle (Can be NULL).
 * \param pRectDst A pointer to the destination rectangle (Can be NULL).
 * \return 0 on success, else -1 if error.
 */
int SDL_Ctx_RenderCopy(SDL_Texture *pTexture, SDL_Rect *pRectSrc, SDL_Rect *pRectDst)
{
    return SDL_RenderCopy(SDL_context.pRenderer, pTexture, pRectSrc, pRectDst);
}

/*!
 * \brief Function to copy a texture to the renderer.
 *
 * \param pTexture The texture to copy.
 * \param pRectSrc A pointer to the source rectangle (Can be NULL).
 * \param pRectDst A pointer to the destination rectangle (Can be NULL).
 * \param dAngle   An angle in degrees to rotate the texture.
 * \param pCenter  Point to rotate the texture (Can be NULL).
 * \param iFlip    Flag to flip the texture.
 * \return 0 on success, -1 if error
 */
int SDL_Ctx_RenderCopyEx(SDL_Texture      *pTexture, 
                         SDL_Rect         *pRectSrc, 
                         SDL_Rect         *pRectDst, 
                         double            dAngle, 
                         const SDL_Point  *pCenter, 
                         SDL_RendererFlip  iFlip)
{
    return SDL_RenderCopyEx(SDL_context.pRenderer, 
                            pTexture, 
                            pRectSrc, 
                            pRectDst, 
                            dAngle, 
                            pCenter, 
                            iFlip);
}

/*!
* \brief Function to draw shape of a rect.
*
* \param pRectDest Pointer to the rect to draw, NULL to outline the entire rendering target.
* \return 0 on success, -1 if error.
*/
int SDL_Ctx_RenderDrawRect(SDL_Rect *pRectDest)
{
   return SDL_RenderDrawRect(SDL_context.pRenderer, pRectDest);
}

/*!
* \brief Function to draw a rect filled with color.
*
* \param pRectDest Pointer to the rect to draw, NULL for the entire rendering target.
* \param pColor    Pointer to the color.
* \return 0 on success, -1 if error.
*/
int SDL_Ctx_RenderFillRect(SDL_Rect *pRectDest, SDL_Color *pColor)
{
    SDL_SetRenderDrawColor(SDL_context.pRenderer, pColor->r, pColor->r, pColor->b, pColor->a);
    return SDL_RenderFillRect(SDL_context.pRenderer, pRectDest);
}

/*!
 * \brief Function to draw the renderer context.
 *
 * \return None
 */
void SDL_Ctx_RenderPresent(void)
{
    SDL_SetRenderDrawColor(SDL_context.pRenderer, 0, 0, 0, 255);
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
