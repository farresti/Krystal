/* ========================================================================= */
/*!
 * \file    SDL_Textbox.h
 * \brief   File to interface with the text boxes.
 * \author  Nyuu / Orlyn / Red
 * \version 1.0
 * \date    09 June 2015
 */
/* ========================================================================= */
/* Author  | Date     | Comments                                             */
/* --------+----------+----------------------------------------------------- */
/* Nyuu    | 09/06/15 | Creation.                                            */
/* ========================================================================= */

#ifndef __SDL_TEXTBOX_H__
#define __SDL_TEXTBOX_H__

    #include "SDL_Shared.h"
    #include "SDL_Text.h"

    /*!
     * \struct SDL_Textbox
     * \brief  Structure to handle a text box.
     */
    typedef struct
    {
        char *szText;
        SDL_bool bIsActive;
        SDL_bool bIsFull;
        Uint32 iMaxLength;
        Uint32 iLastTime;
        SDL_Keycode currentLetter;
        SDL_Keycode precedentLetter;
        SDL_Text *pText;
    } SDL_Textbox;

    /* Textbox functions */
    void      SDL_Textbox_Init(SDL_Textbox *pTextBox, TTF_Font *pFont, SDL_Color *pColorFont, Sint32 x, Sint32 y);
    void      SDL_Textbox_SetText(SDL_Textbox *pTextBox, const char *szText);
    void      SDL_Textbox_UpdateBox(SDL_Textbox *pTextBox);
    Sint32    SDL_Textbox_GetLength(SDL_Textbox *pTextBox);
    Uint32    SDL_Textbox_GetMaxLength(SDL_Textbox *pTextBox);
    SDL_bool  SDL_Textbox_IsFull(SDL_Textbox *pTextBox);
    SDL_bool  SDL_Textbox_IsActive(SDL_Textbox *pTextBox);
    void      SDL_Textbox_Free(SDL_Textbox *pTextBox);

#endif // __SDL_TEXTBOX_H__

/* ========================================================================= */
