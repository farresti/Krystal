/* ========================================================================= */
/*!
 * \file    SDL_Context.h
 * \brief   File to interface with the context.
 * \author  Nyuu / Orlyn / Red
 * \version 1.0
 * \date    09 June 2015
 */
/* ========================================================================= */
/* Author  | Date     | Comments                                             */
/* --------+----------+----------------------------------------------------- */
/* Nyuu    | 09/06/15 | Creation.                                            */
/* Orlyn   | 10/06/15 | Add new functions SDL_Ctx_*                          */
/* ========================================================================= */

#ifndef __SDL_CONTEXT_H__
#define __SDL_CONTEXT_H__

    #include "SDL_Shared.h"
    
    SDL_bool SDL_Ctx_Init(const char *szWindowName, int iWidth, int iHeight);

    SDL_Texture *SDL_Ctx_CreateTextureFromSurface(SDL_Surface *pSurface);

    void SDL_Ctx_RenderClear(void);
    int  SDL_Ctx_RenderCopy(SDL_Texture *pTexture, SDL_Rect *pRectSrc, SDL_Rect *pRectDst);
    int  SDL_Ctx_RenderCopyEx(SDL_Texture      *pTexture, 
                              SDL_Rect         *pRectSrc, 
                              SDL_Rect         *pRectDst, 
                              double            dAngle, 
                              const SDL_Point  *pCenter, 
                              SDL_RendererFlip  iFlip);
    int  SDL_Ctx_RenderDrawRect(SDL_Rect *pRectDest);
    int  SDL_Ctx_RenderFillRect(SDL_Rect *pRectDest, SDL_Color *pColor);
    void SDL_Ctx_RenderPresent(void);

    void SDL_Ctx_Quit(void);

#endif // __SDL_CONTEXT_H__

/* ========================================================================= */
