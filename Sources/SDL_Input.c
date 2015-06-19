/* ========================================================================= */
/*!
 * \file    SDL_Input.c
 * \brief   File to handle the inputs (Keyboard, mouse..).
 * \author  Nyuu / Orlyn / Red
 * \version 1.0
 * \date    09 June 2015
 */
/* ========================================================================= */
/* Author  | Date     | Comments                                             */
/* --------+----------+----------------------------------------------------- */
/* Nyuu    | 09/06/15 | Creation.                                            */
/* Red     | 10/06/15 | Add SDL_Input_ Update and Init                       */
/* Orlyn   | 17/06/15 | Add some functions                                   */
/* ========================================================================= */

#include "SDL_Input.h"

/* ========================================================================= */

/*!
 * \brief Function to init the inputs.
 *
 * \param pInput Pointer to the input.
 * \return None.
 */
void SDL_Input_Init(SDL_Input *pInput)
{
    memset(pInput, 0, sizeof(*pInput));

    pInput->pStdCursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW);
    pInput->pTxtCursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_IBEAM);
    SDL_Input_SetKeyRepeat(pInput, SDL_FALSE);
}

/*!
 * \brief Function to update the inputs.
 *
 * \param pInput Pointer to the input.
 * \return None.
 */
void SDL_Input_Update(SDL_Input *pInput)
{
    SDL_Event sEvent;

    pInput->bMotionEvent = SDL_FALSE;

    while (SDL_PollEvent(&sEvent))
    {
        switch (sEvent.type)
        {
            case SDL_KEYDOWN:
            {
                if (sEvent.key.repeat == 0 || pInput->bRepeatKey) 
                {
                    pInput->bKey[sEvent.key.keysym.sym] = SDL_TRUE;
                    pInput->iLastKey = sEvent.key.keysym.sym;
                }
                break;
            }
            case SDL_KEYUP:
            {
                pInput->bKey[sEvent.key.keysym.sym] = SDL_FALSE;
                break;
            }
            case SDL_MOUSEMOTION:
            {
                pInput->bMotionEvent = SDL_TRUE;
                pInput->iMouse.x     = sEvent.motion.x;
                pInput->iMouse.y     = sEvent.motion.y;
                pInput->iMouseRel.x  = sEvent.motion.xrel;
                pInput->iMouseRel.y  = sEvent.motion.yrel;
                break;
            }
            case SDL_MOUSEBUTTONDOWN:
            {
                pInput->bMouseButtons[sEvent.button.button] = SDL_TRUE;
                break;
            }
            case SDL_MOUSEBUTTONUP:
            {
                pInput->bMouseButtons[sEvent.button.button] = SDL_FALSE;
                break;
            }
            case SDL_QUIT:
            {
                pInput->bQuit = SDL_TRUE;
                break;
            }
            case SDL_MOUSEWHEEL:
            {
                pInput->iScrollVertical = sEvent.wheel.y;
                break;
            }
            default:
            {
                break;
            }
        }
    }
}

/*!
 * \brief Function to test if a key is pressed.
 *
 * \param pInput Pointer to the input.
 * \return SDL_TRUE if the key is pressed, else SDL_FALSE.
 */
SDL_bool SDL_Input_IsKeyPressed(const SDL_Input *pInput, SDL_Keycode iKey)
{
    return pInput->bKey[iKey];
}

/*!
 * \brief Function to reset a specified key.
 *
 * \param pInput Pointer to the input.
 * \return None.
 */
void SDL_Input_ResetKey(SDL_Input *pInput, SDL_Keycode iKey)
{
    pInput->bKey[iKey] = SDL_FALSE;
}

/*!
 * \brief Function to get the last pressed key.
 *
 * \param pInput Pointer to the input.
 * \return The key code of the last key pressed.
 */
SDL_Keycode SDL_Input_GetLastKey(const SDL_Input *pInput)
{
    return pInput->iLastKey;
}

/*!
* \brief Function to get the position of the mouse.
*
* \param pInput Pointer to the input.
* \param pMouse Pointer to retrieve the mouse position.
* \return None.
*/
void SDL_Input_GetMousePosition(const SDL_Input *pInput, SDL_Point *pMouse)
{
    pMouse->x = pInput->iMouse.x;
    pMouse->y = pInput->iMouse.y;
}

/*!
* \brief Function to set keyboard repeatition.
*
* \param pInput     Pointer to the input.
* \param bENabled   Boolean to set key repeat.
* \return None.
*/
void SDL_Input_SetKeyRepeat(SDL_Input *pInput, SDL_bool bENabled)
{
    pInput->bRepeatKey = bENabled;
}

/*!
* \brief Function to return the flag of key repeat.
*
* \param pInput Pointer to the input.
* \return True if key repeat is enabled, false else.
*/
SDL_bool SDL_Input_IsKeyRepeatEnabled(SDL_Input *pInput)
{
    return pInput->bRepeatKey;
}

/*!
 * \brief Function to free the input structure.
 *
 * \param pInput Pointer to the input.
 * \return None.
 */
void SDL_Input_Free(SDL_Input *pInput)
{
    SDL_FreeCursor(pInput->pTxtCursor);
    SDL_FreeCursor(pInput->pStdCursor);
}

/* ========================================================================= */
