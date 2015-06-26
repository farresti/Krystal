/* ========================================================================= */
/*!
 * \file    SDL_Render.h
 * \brief   File to interface with the render.
 * \author  Nyuu / Orlyn / Red
 * \version 1.0
 * \date    26 June 2015
 */
/* ========================================================================= */
/* Author  | Date     | Comments                                             */
/* --------+----------+----------------------------------------------------- */
/* Nyuu    | 26/06/15 | Creation.                                            */
/* ========================================================================= */

#ifndef __SDL_RENDER_H__
#define __SDL_RENDER_H__

    #include "SDL_Shared.h"
    
    void         SDL_Render_Init(SDL_Renderer *pRenderer, const SDL_Color *pColor);

    SDL_Texture *SDL_Render_CreateTextureFromSurface(SDL_Surface *pSurface);

    void         SDL_Render_Clear(void);
    int          SDL_Render_DrawTexture(SDL_Texture *pTexture, const SDL_Rect *pClip, const SDL_Rect *pPos);
    int          SDL_Render_DrawTextureEx(SDL_Texture *pTexture, const SDL_Rect *pClip, const SDL_Rect *pPos, double dAngle, const SDL_Point *pCenter, SDL_RendererFlip iFlip);
    void         SDL_Render_DrawLine(Sint32 x1, Sint32 y1, Sint32 x2, Sint32 y2, const SDL_Color *pColor);
    void         SDL_Render_DrawFullRect(const SDL_Rect *pRect, const SDL_Color *pColor);
    void         SDL_Render_DrawEmptyRect(const SDL_Rect *pRect, const SDL_Color *pColor);
    void         SDL_Render_Present(void);

#endif // __SDL_RENDER_H__

/* ========================================================================= */
