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
/* Orlyn   | 18/06/15 | Clean and add repeat key support                     */
/* Orlyn   | 19/06/15 | Clean                                                */
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
        char        *szText;              /*!< String of the text inside the text box. */

        SDL_bool     bIsActive;           /*!< Flag to indicate if the text box is active. */
        SDL_bool     bIsFull;             /*!< Flag to indicate if the text box is full. */
        SDL_bool     bIsLocked;           /*!< Flag to indicate if a key is locked in the text box. */

        Uint32       iMaxLength;          /*!< Maximum length of the text within the text box. */

        Uint32       iLastTime;           /*!< Time of the last action. */
        Uint32       iCursorTime;         /*!< Time for the blink of the cursor. */

        SDL_Keycode  iCurrentKey;          /*!< The current key being pressed. */
        SDL_Keycode  iLastKey;             /*!< The last key that has been pressed. */

        SDL_Point    sPointCursor;        /*!< Offset for the cursor. */

        SDL_Text    *pText;               /*!< Pointer to the text structure. */
        TTF_Font    *pFont;               /*!< Pointer to the text font. */
        SDL_Color   *pColorFont;          /*!< Pointer to the color of the font. */
        SDL_Rect     rDest;               /*!< Rect of the text box. */
    } SDL_Textbox;
        
    void                SDL_Textbox_Init(SDL_Textbox *pTextBox, TTF_Font *pFont, SDL_Color *pColorFont, SDL_Rect *pRectDest);
    static void         SDL_Textbox_SetText(SDL_Textbox *pTextBox, const char *szText);
    void                SDL_Textbox_Update(SDL_Textbox *pTextBox, SDL_Input *pInput);
    static void         SDL_Textbox_Add(SDL_Textbox *pTextbox);
    static void         SDL_Textbox_AddSpace(SDL_Textbox *pTextBox);
    static void         SDL_Textbox_Delete(SDL_Textbox *pTextBox);
    void                SDL_Textbox_Draw(SDL_Textbox *pTextbox);
    static void         SDL_Textbox_DrawCursor(SDL_Textbox *pTextbox);
    Sint32              SDL_Textbox_GetTextLength(const SDL_Textbox *pTextBox);
    Uint32              SDL_Textbox_GetMaxLength(const SDL_Textbox *pTextBox);
    static SDL_bool     SDL_Textbox_IsFull(const SDL_Textbox *pTextBox);
    static void         SDL_Textbox_CheckSize(SDL_Textbox *pTextBox);
    static void         SDL_Textbox_CheckActive(SDL_Textbox *pTextBox, const SDL_Input *pInput);
    SDL_bool            SDL_Textbox_IsActive(const SDL_Textbox *pTextBox);
    static SDL_bool     SDL_Textbox_IsKeyLocked(const SDL_Textbox *pTextBox);
    static void         SDL_Textbox_CheckLock(SDL_Textbox *pTextBox);
    static Sint32       SDL_Textbox_GetCursorX(const SDL_Textbox *pTextBox);
    static Sint32       SDL_Textbox_GetCursorY(const SDL_Textbox *pTextBox);
    static SDL_Keycode  SDL_Textbox_GetCurrent(const SDL_Textbox *pTextBox);
    void                SDL_Textbox_SetColor(SDL_Textbox *pTextBox, SDL_Color *pColor);
    void                SDL_Textbox_Free(SDL_Textbox *pTextBox);

#endif // __SDL_TEXTBOX_H__

/* ========================================================================= */
