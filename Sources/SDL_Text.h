/* ========================================================================= */
/*!
 * \file    SDL_Text.h
 * \brief   File to interface with the texts.
 * \author  Nyuu / Orlyn / Red
 * \version 1.0
 * \date    09 June 2015
 */
/* ========================================================================= */
/* Author  | Date     | Comments                                             */
/* --------+----------+----------------------------------------------------- */
/* Nyuu    | 09/06/15 | Creation.                                            */
/* Orlyn   | 13/06/15 | Add SDL_Text functions.                              */
/* ========================================================================= */

#ifndef __SDL_TEXT_H__
#define __SDL_TEXT_H__

    #include "SDL_Shared.h"
    
    /*!
     * \struct SDL_Text
     * \brief  Structure to handle a text.
     */
    typedef struct
    {
        TTF_Font    *pFont;    /*!< Pointer to the text font. */
        SDL_Texture *pTexture; /*!< Pointer to the text texture. */
        SDL_Rect     rDest;    /*!< Rectangle to position the text. */
    } SDL_Text;

    void SDL_Text_Init(SDL_Text *pText, TTF_Font *pFont, Sint32 x, Sint32 y);
    void SDL_Text_Set(SDL_Text *pText, const char *szText, SDL_Color *pColorFont, Sint32 iMaxW);
    void SDL_Text_Draw(SDL_Text* pText);
    void SDL_Text_Move(SDL_Text *pText, Sint32 x, Sint32 y);
    void SDL_Text_Center(SDL_Text *pText, Sint32 cx, Sint32 cy);
    void SDL_Text_Free(SDL_Text *pText);

#endif // __SDL_TEXT_H__

/* ========================================================================= */
