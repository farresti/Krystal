/* ========================================================================= */
/*!
 * \file    HUI_Button.c
 * \brief   File to handle the graphic buttons.
 * \author  Nyuu / Orlyn / Red
 * \version 1.0
 * \date    09 June 2015
 */
/* ========================================================================= */
/* Author  | Date     | Comments                                             */
/* --------+----------+----------------------------------------------------- */
/* Nyuu    | 09/06/15 | Creation.                                            */
/* Red     | 27/06/15 | Add SetPosition                                      */
/*         |          | Fix the update function                              */
/*         |          | Update all function for the new param SDL_Point      */
/* ========================================================================= */

#include "HUI_Button.h"

/* ========================================================================= */

/*!
 * \brief Function to init a button.
 *
 * \param pButton Pointer to the button.
 * \param pSprite Pointer to a sprite allocated.
 * \param x       Position on x.
 * \param y       Position on y.
 * \return None.
 */
void HUI_Button_Init(HUI_Button *pButton, SDL_Sprite *pSprite, Sint32 x, Sint32 y)
{
    pButton->pSprite = pSprite;

    SDL_Sprite_GetFrameSize(pSprite, &pButton->rHitbox);
    pButton->sPosition.x = x;
    pButton->sPosition.y = y;
    pButton->rHitbox.x   = x;
    pButton->rHitbox.y   = y;

    pButton->iState = HUI_BUTTON_INACTIVE;
}

/*!
 * \brief  Function to update a button.
 *
 * \param  pButton Pointer to the button.
 * \param  pInput  Pointer to the inputs.
 * \return None.
 */
void HUI_Button_Update(HUI_Button *pButton, const HUI_Input *pInput)
{
    switch (pButton->iState)
    {
        case HUI_BUTTON_INACTIVE:
        {
            if ((pInput->bMotionEvent) && (UTIL_ContainPoint(&pButton->rHitbox, &pInput->iMouse)))
            {
                pButton->iState = HUI_BUTTON_ROLLED_OVER;
            }

            break;
        }
        case HUI_BUTTON_ROLLED_OVER:
        {
            if ((pInput->bMotionEvent) && (!UTIL_ContainPoint(&pButton->rHitbox, &pInput->iMouse)))
            {
                pButton->iState = HUI_BUTTON_INACTIVE;
            }
            else if (pInput->bMouseButtons[SDL_BUTTON_LEFT])
            {
                pButton->iState = HUI_BUTTON_ACTIVE;
            }

            break;
        }
        case HUI_BUTTON_ACTIVE:
        {
            if (!pInput->bMouseButtons[SDL_BUTTON_LEFT])
            {
                pButton->iState = HUI_BUTTON_ROLLED_OVER;
            }
            break;
        }
        default:
        {
            COM_Log_Print(COM_LOG_WARNING, "Wrong button state (%d) !", pButton->iState);
            break;
        }
    }
}

/*!
 * \brief  Function to draw a button.
 *
 * \param  pButton Pointer to the button.
 * \return None.
 */
void HUI_Button_Draw(HUI_Button *pButton)
{
    SDL_Sprite_Draw(pButton->pSprite, &pButton->sPosition, pButton->iState);
}

/*!
 * \brief  Function to set the position of a button.
 *
 * \param  pButton Pointer to the button.
 * \param  x       Button position on x.
 * \param  y       Button position on y.
 * \return None.
 */
void HUI_Button_SetPosition(HUI_Button *pButton, Sint32 x, Sint32 y)
{
    pButton->sPosition.x = x;
    pButton->sPosition.y = y;
    pButton->rHitbox.x   = x;
    pButton->rHitbox.y   = y;
}

/*!
 * \brief  Function to get the position of the button.
 *
 * \param  pButton Pointer to the button.
 * \param  pPos    Pointer to a point to retrieve the position of the button.
 * \return None.
 */
void HUI_Button_GetPosition(const HUI_Button *pButton, SDL_Point *pPos)
{
    pPos->x = pButton->sPosition.x;
    pPos->y = pButton->sPosition.y;
}

/*!
 * \brief  Function to get the hitbox of a button.
 *
 * \param  pButton Pointer to the button.
 * \param  pHitbox Pointer to a rectangle to retrieve the hitbox of the button.
 * \return None.
 */
void HUI_Button_GetHitbox(const HUI_Button *pButton, SDL_Rect *pHitbox)
{
    pHitbox->x = pButton->rHitbox.x;
    pHitbox->y = pButton->rHitbox.y;
    pHitbox->w = pButton->rHitbox.w;
    pHitbox->h = pButton->rHitbox.h;
}

/*!
 * \brief  Function to get the state of a button.
 *
 * \param  pButton Pointer to the button.
 * \return The state of the button.
 */
HUI_ButtonState HUI_Button_GetState(const HUI_Button *pButton)
{
    return pButton->iState;
}

/* ========================================================================= */
