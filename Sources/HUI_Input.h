/* ========================================================================= */
/*!
 * \file    HUI_Input.h
 * \brief   File to interface with the inputs (Keyboard, mouse..).
 * \author  Nyuu / Orlyn / Red
 * \version 1.0
 * \date    09 June 2015
 */
/* ========================================================================= */
/* Author  | Date     | Comments                                             */
/* --------+----------+----------------------------------------------------- */
/* Nyuu    | 09/06/15 | Creation.                                            */
/* Red     | 10/06/15 | Creation of the HUI_Input structure.                 */
/* Orlyn   | 17/06/15 | Add some functions + cursors to the structure        */
/* ========================================================================= */

#ifndef __HUI_INPUT_H__
#define __HUI_INPUT_H__

    #include "HUI_Shared.h"

    /*!
     * \struct HUI_Input
     * \brief  Structure to handle the inputs.
     */
    typedef struct
    {
        SDL_Event   sEvent;                  /*!< Status of the events. */

        SDL_bool    bKey[SDL_NUM_SCANCODES]; /*!< Status of each key of the keyboard. */
        SDL_Keycode iLastKey;                /*!< Last key pressed. */
        SDL_bool    bRepeatKey;              /*!< Flag to enable or disable keyboard repeat. */

        SDL_Point   iMouse;                  /*!< Absolute position of the mouse. */
        SDL_Point   iMouseRel;               /*!< Relative position of the mouse. */
        SDL_bool    bMouseButtons[8];        /*!< Status of each buttons of the mouse */
        SDL_bool    bMotionEvent;            /*!< Flag to indicate if the mouse has moved since the last time. */
        Sint32      iScrollVertical;         /*!< Amount scrolled vertically (Up = Positive). */
        
        SDL_bool    bQuit;                   /*!< Flag to indicate if the cross has been pressed. */
        
        SDL_Cursor *pTxtCursor;              /*!< Pointer to the text cursor. */
        SDL_Cursor *pStdCursor;              /*!< Pointer to the standard cursor. */
    } HUI_Input;

    void        HUI_Input_Init(HUI_Input *pInput);
    void        HUI_Input_Update(HUI_Input *pInput);
    SDL_bool    HUI_Input_IsKeyPressed(const HUI_Input *pInput, SDL_Keycode iKey);
    void        HUI_Input_ResetKey(HUI_Input *pInput, SDL_Keycode iKey);
    SDL_Keycode HUI_Input_GetLastKey(const HUI_Input *pInput);
    void        HUI_Input_GetMousePosition(const HUI_Input *pInput, SDL_Point *pMouse);
    void        HUI_Input_SetKeyRepeat(HUI_Input *pInput, SDL_bool bEnabled);
    SDL_bool    HUI_Input_IsKeyRepeatEnabled(const HUI_Input *pInput);
    void        HUI_Input_Free(HUI_Input *pInput);

#endif // __HUI_INPUT_H__

/* ========================================================================= */
