/* ========================================================================= */
/*!
 * \file    SDL_Render.c
 * \brief   File to handle the render.
 * \author  Nyuu / Orlyn / Red
 * \version 1.0
 * \date    26 June 2015
 */
/* ========================================================================= */
/* Author  | Date     | Comments                                             */
/* --------+----------+----------------------------------------------------- */
/* Nyuu    | 26/06/15 | Creation.                                            */
/* ========================================================================= */

#include "SDL_Render.h"

/* ========================================================================= */

/*!
 * \struct SDL_Render
 * \brief  Structure to handle the render.
 */
typedef struct
{
    SDL_Renderer *pRenderer;  /*!< Pointer to the renderer. */ 
    SDL_Color     sColor;     /*!< Color of the renderer. */
} SDL_Render;

/*! Global variable to handle the render. */
static SDL_Render SDL_render;

/* ========================================================================= */

/*!
 * \brief Function to init the renderer.
 *
 * \param pRenderer Pointer to the renderer.
 * \param pColor    Pointer to the background color.
 * \return None.
 */
void SDL_Render_Init(SDL_Renderer *pRenderer, const SDL_Color *pColor)
{
    SDL_render.pRenderer = pRenderer;
    SDL_render.sColor.r  = pColor->r;
    SDL_render.sColor.g  = pColor->g;
    SDL_render.sColor.b  = pColor->b;
    SDL_render.sColor.a  = pColor->a;
}

/*!
 * \brief Function to create a texture from a surface.
 *
 * \param pSurface Pointer to the surface.
 * \return A pointer to the texture created, or NULL if error.
 */
SDL_Texture *SDL_Render_CreateTextureFromSurface(SDL_Surface *pSurface)
{
    return SDL_CreateTextureFromSurface(SDL_render.pRenderer, pSurface);
}

/*!
 * \brief Function to clear the renderer.
 *
 * \return None
 */
void SDL_Render_Clear(void)
{
    SDL_SetRenderDrawColor(SDL_render.pRenderer, SDL_render.sColor.r, SDL_render.sColor.g, SDL_render.sColor.b, SDL_render.sColor.a);
    SDL_RenderClear(SDL_render.pRenderer);
}

/*!
 * \brief Function to set the viewport of the renderer.
 *
 * \param pViewport Pointer to a rectangle to set the viewport (Can be NULL).
 * \return None
 */
void SDL_Render_SetViewport(const SDL_Rect *pViewport)
{
    SDL_RenderSetViewport(SDL_render.pRenderer, pViewport);
}

/*!
 * \brief Function to draw a texture to the renderer.
 *
 * \param pTexture The texture to draw.
 * \param pClip    Pointer to a rectangle to clip the texture (Can be NULL).
 * \param pPos     Pointer to a rectangle to position the texture (Can be NULL).
 * \return 0 on success, else -1 if error.
 */
int SDL_Render_DrawTexture(SDL_Texture *pTexture, const SDL_Rect *pClip, const SDL_Rect *pPos)
{
    return SDL_RenderCopy(SDL_render.pRenderer, pTexture, pClip, pPos);
}

/*!
 * \brief Function to draw a texture on the renderer.
 *
 * \param pTexture The texture to draw.
 * \param pClip    Pointer to a rectangle to clip the texture (Can be NULL).
 * \param pPos     Pointer to a rectangle to position the texture (Can be NULL).
 * \param dAngle   Angle to rotate the texture.
 * \param pCenter  Pointer to the center of the rotation.
 * \param iFlip    Flag to flip the texture.
 * \return 0 on success, else -1 if error.
 */
int SDL_Render_DrawTextureEx(SDL_Texture *pTexture, const SDL_Rect *pClip, const SDL_Rect *pPos, double dAngle, const SDL_Point *pCenter, SDL_RendererFlip iFlip)
{
    return SDL_RenderCopyEx(SDL_render.pRenderer, pTexture, pClip, pPos, dAngle, pCenter, iFlip);
}

/*!
 * \brief Function to draw a line on the renderer.
 *
 * \param x1     Position on x to start.
 * \param y1     Position on y to start.
 * \param x2     Position on x to end.
 * \param y2     Position on y to end.
 * \param pColor Pointer to the color to use.
 * \return None.
 */
void SDL_Render_DrawLine(Sint32 x1, Sint32 y1, Sint32 x2, Sint32 y2, const SDL_Color *pColor)
{
    SDL_SetRenderDrawColor(SDL_render.pRenderer, pColor->r, pColor->g, pColor->b, pColor->a);
    SDL_RenderDrawLine(SDL_render.pRenderer, x1, y1, x2, y2);
    SDL_SetRenderDrawColor(SDL_render.pRenderer, SDL_render.sColor.r, SDL_render.sColor.g, SDL_render.sColor.b, SDL_render.sColor.a);
}

/*!
 * \brief Function to draw a full rectangle on the renderer.
 *
 * \param pRect    Pointer to the rectangle to draw.
 * \param pColor   Pointer to the color to use.
 * \return None.
 */
void SDL_Render_DrawFullRect(const SDL_Rect *pRect, const SDL_Color *pColor)
{
    SDL_SetRenderDrawColor(SDL_render.pRenderer, pColor->r, pColor->g, pColor->b, pColor->a);
    SDL_RenderFillRect(SDL_render.pRenderer, pRect);
    SDL_SetRenderDrawColor(SDL_render.pRenderer, SDL_render.sColor.r, SDL_render.sColor.g, SDL_render.sColor.b, SDL_render.sColor.a);
}

/*!
 * \brief Function to draw a empty rectangle on the renderer.
 *
 * \param pRect    Pointer to the rectangle to draw.
 * \param pColor   Pointer to the color to use.
 * \return None.
 */
void SDL_Render_DrawEmptyRect(const SDL_Rect *pRect, const SDL_Color *pColor)
{
    SDL_SetRenderDrawColor(SDL_render.pRenderer, pColor->r, pColor->g, pColor->b, pColor->a);
    SDL_RenderDrawRect(SDL_render.pRenderer, pRect);
    SDL_SetRenderDrawColor(SDL_render.pRenderer, SDL_render.sColor.r, SDL_render.sColor.g, SDL_render.sColor.b, SDL_render.sColor.a);
}

/*!
 * \brief Function to present the renderer.
 *
 * \return None
 */
void SDL_Render_Present(void)
{
    SDL_RenderPresent(SDL_render.pRenderer);
}

/* ========================================================================= */
