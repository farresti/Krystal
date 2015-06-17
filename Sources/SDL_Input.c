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
                    pInput->bKey[sEvent.key.keysym.scancode] = SDL_TRUE;
                }
                break;
            }
            case SDL_KEYUP:
            {
                pInput->bKey[sEvent.key.keysym.scancode] = SDL_FALSE;
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

/* ========================================================================= */
