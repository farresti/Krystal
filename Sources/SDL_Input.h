/* ========================================================================= */
/*!
 * \file    SDL_Input.h
 * \brief   File to interface with the inputs (Keyboard, mouse..).
 * \author  Nyuu / Orlyn / Red
 * \version 1.0
 * \date    09 June 2015
 */
/* ========================================================================= */
/* Author  | Date     | Comments                                             */
/* --------+----------+----------------------------------------------------- */
/* Nyuu    | 09/06/15 | Creation.                                            */
/* Red     | 10/06/15 | Creation of the SDL_Input structure.                 */
/* Orlyn   | 17/06/15 | Add some functions + cursors to the structure        */
/* ========================================================================= */

#ifndef __SDL_INPUT_H__
#define __SDL_INPUT_H__

    #include "SDL_Shared.h"

    /*!
     * \struct SDL_Input
     * \brief  Structure to handle the inputs.
     */
    typedef struct
    {
        SDL_bool    bKey[SDL_NUM_SCANCODES]; /*!< Status of each key of the keyboard*/
        SDL_bool    bMotionEvent;            /*!< Flag to indicate if the mouse has moved since the last time */
        SDL_Point   iMouse;                  /*!< Absolute position of the mouse. */
        SDL_Point   iMouseRel;               /*!< Relative position of the mouse. */
        Sint32      iScrollVertical;         /*!< Amount scrolled vertically, positive away from the user and negative toward the user. */
        SDL_bool    bMouseButtons[8];        /*!< Status of each buttons of the mouse */
        SDL_bool    bQuit;                   /*!< Flag to indicate if the cross has been pressed. */
        SDL_Keycode lastKey;                 /*!< Last key pressed*/
        SDL_Cursor *pTxtCursor;              /*!< Pointer to the text cursor*/
        SDL_Cursor *pStdCursor;              /*!< Pointer to the standard cursor*/
        SDL_bool    bRepeatKey;              /*!< Flag to enable or disable keyboard repeat*/
    } SDL_Input;

    void        SDL_Input_Init(SDL_Input *pInput);
    void        SDL_Input_Update(SDL_Input *pInput);
    SDL_bool    SDL_Input_IsKeyPressed(const SDL_Input *pInput, SDL_Keycode iKey);
    void        SDL_Input_ResetKey(SDL_Input *pInput, SDL_Keycode iKey);
    SDL_Keycode SDL_Input_GetLastKey(const SDL_Input *pInput);
    void        SDL_Input_GetMousePosition(const SDL_Input *pInput, SDL_Point *pMouse);
    void        SDL_Input_EnableKeyRepeat(SDL_Input *pInput);
    void        SDL_Input_DisableKeyRepeat(SDL_Input *pInput);
    SDL_bool    SDL_Input_IsKeyRepeatEnabled(SDL_Input *pInput);
    void        SDL_Input_Free(SDL_Input *pInput);

#endif // __SDL_INPUT_H__

/* ========================================================================= */
