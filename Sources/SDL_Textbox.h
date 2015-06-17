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
/* Orlyn   | 15/06/15 | Add SDL_Textbox functions.                           */
/* Orlyn   | 16/06/15 | Add SDL_Textbox functions.                           */
/* Orlyn   | 17/06/15 | Add Cursor functions                                 */
/* ========================================================================= */

#ifndef __SDL_TEXTBOX_H__
#define __SDL_TEXTBOX_H__

    #include "SDL_Shared.h"
    #include "SDL_Text.h"
    #include "SDL_Util.h"
    #include "SDL_Input.h"
    #include "SDL_Context.h"

    /*!
     * \struct SDL_Textbox
     * \brief  Structure to handle a text box.
     */
    typedef struct
    {
        char        *szText;
        SDL_bool     bIsActive;
        SDL_bool     bIsFull;
        SDL_bool     bIsLocked;
        Uint32       iMaxLength;
        Uint32       iLastTime;
        Uint32       iCursorTime;
        SDL_Keycode  currentLetter;
        SDL_Keycode  precedentLetter;
        SDL_Text    *pText;
        TTF_Font    *pFont;
        SDL_Rect     rDest;
        SDL_Color   *pColorFont;
        SDL_Point   offsetCursor;
    } SDL_Textbox;

    /* Textbox functions */
    void      SDL_Textbox_Init(SDL_Textbox *pTextBox, TTF_Font *pFont, SDL_Color *pColorFont, Sint32 x, Sint32 y, Sint32 w, Sint32 h);
    void      SDL_Textbox_SetText(SDL_Textbox *pTextBox, const char *szText);
    void      SDL_Textbox_Update(SDL_Textbox *pTextBox, SDL_Input *pInput);
    void      SDL_Textbox_AddLetter(SDL_Textbox *pTextbox);
    void      SDL_Textbox_AddSpace(SDL_Textbox *pTextBox);
    void      SDL_Textbox_DeleteLetter(SDL_Textbox *pTextBox);
    void      SDL_Textbox_Draw(SDL_Textbox *pTextbox); 
    void      SDL_Textbox_DrawCursor(SDL_Textbox *pTextbox);
    Sint32    SDL_Textbox_GetLength(SDL_Textbox *pTextBox);
    Uint32    SDL_Textbox_GetMaxLength(SDL_Textbox *pTextBox);
    SDL_bool  SDL_Textbox_IsFull(SDL_Textbox *pTextBox);
    void      SDL_Textbox_SetActive(SDL_Textbox *pTextBox, SDL_Input *pInput);
    SDL_bool  SDL_Textbox_IsActive(SDL_Textbox *pTextBox);
    SDL_bool  SDL_Textbox_IsLocked(SDL_Textbox *pTextBox);
    Sint32    SDL_Textbox_GetCursorX(SDL_Textbox *pTextBox);
    Sint32    SDL_Textbox_GetCursorY(SDL_Textbox *pTextBox);
    void      SDL_Textbox_Free(SDL_Textbox *pTextBox);

#endif // __SDL_TEXTBOX_H__

/* ========================================================================= */
