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
                if (sEvent.key.repeat == 0) 
                {
                    pInput->bKey[sEvent.key.keysym.sym] = SDL_TRUE;
                    pInput->lastKey = sEvent.key.keysym.sym;
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
                pInput->iMouseX      = sEvent.motion.x;
                pInput->iMouseY      = sEvent.motion.y;
                pInput->iMouseXRel   = sEvent.motion.xrel;
                pInput->iMouseYRel   = sEvent.motion.yrel;
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
* \return true if the key is pressed, false if not.
*/
SDL_bool SDL_Input_IsKeyPressed(SDL_Input *pInput, SDL_Keycode key)
{
    return pInput->bKey[key];
}

/*!
* \brief Function to reset the flag of a specified key².
*
* \param pInput Pointer to the input.
* \return None.
*/
void SDL_Input_ResetKey(SDL_Input *pInput, SDL_Keycode key)
{
    pInput->bKey[key] = SDL_FALSE;
}

/*!
* \brief Function to get the last pressed key.
*
* \param pInput Pointer to the input.
* \return The SDL_Keycode of the last key pressed.
*/
SDL_Keycode  SDL_Input_GetLastKey(SDL_Input *pInput)
{
    return pInput->lastKey;
}

/*!
* \brief Function to get the position of the mouse.
*
* \param pInput         Pointer to the input.
* \param pMousePosition Pointer to the SDL_Point structure to be filled with
*                       mouse positions.
* \return None.
*/
void SDL_Input_GetMousePosition(SDL_Input *pInput, SDL_Point *pMousePosition)
{
    pMousePosition->x = pInput->iMouseX;
    pMousePosition->y = pInput->iMouseY;
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
