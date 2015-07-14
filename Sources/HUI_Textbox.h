/* ========================================================================= */
/*!
 * \file    HUI_Textbox.h
 * \brief   File to interface with the text boxes.
 * \author  Nyuu / Orlyn / Red
 * \version 1.0
 * \date    09 June 2015
 */
/* ========================================================================= */
/* Author  | Date     | Comments                                             */
/* --------+----------+----------------------------------------------------- */
/* Nyuu    | 09/06/15 | Creation.                                            */
/* Orlyn   | 15/06/15 | Add HUI_Textbox functions.                           */
/* Orlyn   | 16/06/15 | Add HUI_Textbox functions.                           */
/* Orlyn   | 17/06/15 | Add Cursor functions                                 */
/* Orlyn   | 18/06/15 | Clean and add repeat key support                     */
/* Orlyn   | 19/06/15 | Clean                                                */
/* Red     | 27/06/15 | Remove the param pColorFont from the structure       */
/* ========================================================================= */

#ifndef __HUI_TEXTBOX_H__
#define __HUI_TEXTBOX_H__

    #include "HUI_Text.h"
    #include "HUI_Input.h"

    /*!
     * \struct HUI_Textbox
     * \brief  Structure to handle a text box.
     */
    typedef struct HUI_Textbox
    {
        char        *szText;              /*!< String of the text inside the text box. */

        SDL_bool     bIsActive;           /*!< Flag to indicate if the text box is active. */
        SDL_bool     bIsFull;             /*!< Flag to indicate if the text box is full. */
        SDL_bool     bIsLocked;           /*!< Flag to indicate if a key is locked in the text box. */

        Uint32       iBoxLength;          /*!< Maximum length of the text within the text box in pixels. */
        Uint16       iTextLength;         /*!< Maximum length of the text within the text box in caracters. */
        Sint32       iTextIndex;          /*!< Index in the text string. */

        Uint32       iLastTime;           /*!< Time of the last action. */
        Uint32       iCursorTime;         /*!< Time for the blink of the cursor. */

        SDL_Keycode  iCurrentKey;         /*!< The current key being pressed. */
        SDL_Keycode  iLastKey;            /*!< The last key that has been pressed. */

        SDL_Point    sPointCursor;        /*!< Offset for the cursor. */

        HUI_Text    *pText;               /*!< Pointer to the text structure. */
        TTF_Font    *pFont;               /*!< Pointer to the text font. */
        SDL_Rect     rDest;               /*!< Rect of the text box. */
    } HUI_Textbox;
    
    void     HUI_Textbox_Init(HUI_Textbox *pTextBox, TTF_Font *pFont, SDL_Color *pColor, SDL_Rect *pDest, Uint16 iLength, char* szText);
    void     HUI_Textbox_Update(HUI_Textbox *pTextBox, HUI_Input *pInput);
    void     HUI_Textbox_Draw(HUI_Textbox *pTextbox);
    Sint32   HUI_Textbox_GetTextLength(const HUI_Textbox *pTextBox);
    Uint32   HUI_Textbox_GetMaxBoxLength(const HUI_Textbox *pTextBox);
    Uint16   HUI_Textbox_GetMaxTextLength(const HUI_Textbox *pTextBox);
    SDL_bool HUI_Textbox_IsActive(const HUI_Textbox *pTextBox);
    SDL_bool HUI_Textbox_IsFull(const HUI_Textbox *pTextBox);
    void     HUI_Textbox_SetColor(HUI_Textbox *pTextBox, SDL_Color *pColor);
    char    *HUI_Textbox_GetText(HUI_Textbox *pTextBox);
    void     HUI_Textbox_Free(HUI_Textbox *pTextBox);

#endif // __HUI_TEXTBOX_H__

/* ========================================================================= */
