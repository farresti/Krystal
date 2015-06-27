/* ========================================================================= */
/*!
 * \file    HUI_Text.h
 * \brief   File to interface with the texts.
 * \author  Nyuu / Orlyn / Red
 * \version 1.0
 * \date    09 June 2015
 */
/* ========================================================================= */
/* Author  | Date     | Comments                                             */
/* --------+----------+----------------------------------------------------- */
/* Nyuu    | 09/06/15 | Creation.                                            */
/* Orlyn   | 13/06/15 | Add HUI_Text functions.                              */
/* Red     | 27/06/15 | Add sColor as a parameter                            */
/*         |          | New argument in Init, SDL_Color                      */
/*         |          | Remove argument in Set, SDL_Color                    */
/*         |          | New function SetColor                                */
/*         |          | Rename Set in SetText                                */
/*         |          | Rename Move in SetPosition                           */
/* ========================================================================= */

#ifndef __HUI_TEXT_H__
#define __HUI_TEXT_H__

    #include "HUI_Shared.h"
    
    /*!
     * \struct HUI_Text
     * \brief  Structure to handle a text.
     */
    typedef struct
    {
        TTF_Font    *pFont;    /*!< Pointer to the text font. */
        SDL_Texture *pTexture; /*!< Pointer to the text texture. */
        SDL_Rect     rDest;    /*!< Rectangle to position the text. */
        SDL_Color    sColor;   /*!< Color of the text. */
    } HUI_Text;

    void HUI_Text_Init(HUI_Text *pText, TTF_Font *pFont, const SDL_Color *pColor, Sint32 x, Sint32 y);
    void HUI_Text_SetText(HUI_Text *pText, const char *szText, Sint32 iMaxW);
    void HUI_Text_SetColor(HUI_Text *pText, const SDL_Color *pColor);
    void HUI_Text_Draw(HUI_Text* pText);
    void HUI_Text_SetPosition(HUI_Text *pText, Sint32 x, Sint32 y);
    void HUI_Text_Center(HUI_Text *pText, Sint32 cx, Sint32 cy);
    void HUI_Text_Free(HUI_Text *pText);

#endif // __HUI_TEXT_H__

/* ========================================================================= */
