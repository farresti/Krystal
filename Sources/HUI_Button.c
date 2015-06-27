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
    SDL_Anim_Init(&pButton->sAnim, pSprite);

    SDL_Anim_SetPosition(&pButton->sAnim, x, y);
    SDL_Anim_SetFrame(&pButton->sAnim, 0);

    SDL_Sprite_GetFrameSize(pSprite, &pButton->rHitbox);
    pButton->rHitbox.x = x;
    pButton->rHitbox.y = y;

    pButton->bIsRolledOver = SDL_FALSE;
    pButton->bIsClicked    = SDL_FALSE;
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
    /* ~~~ Check the position of the mouse.. ~~~ */
    if (pInput->bMotionEvent)
    {
        if (UTIL_ContainPoint(&pButton->rHitbox, &pInput->iMouse))
        {
            pButton->bIsRolledOver = SDL_TRUE;
        }
        else
        {
            pButton->bIsRolledOver = SDL_FALSE;
        }
    }

    /* ~~~ Check left click.. ~~~ */
    if( pButton->bIsRolledOver == SDL_TRUE )
	{
        if (pInput->bMouseButtons[SDL_BUTTON_LEFT])
        {
            pButton->bIsClicked = SDL_TRUE;
        }
        else
        {
            pButton->bIsClicked = SDL_FALSE;
        }
    }

    /* ~~~ Update the frame of the sprite.. ~~~ */
	if( pButton->bIsRolledOver == SDL_TRUE )
	{
		if( pButton->bIsClicked == SDL_TRUE )
		{
            SDL_Anim_SetFrame(&pButton->sAnim, 2);
		}
		else
		{
			SDL_Anim_SetFrame(&pButton->sAnim, 1);
		}
	}
	else
	{
		SDL_Anim_SetFrame(&pButton->sAnim, 0);
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
    SDL_Anim_Draw(&pButton->sAnim);
}

/*!
 * \brief  Function to get if a button is rolled over.
 *
 * \param  pButton Pointer to the button.
 * \return SDL_TRUE if the button is rolled over, else SDL_FALSE.
 */
SDL_bool HUI_Button_IsRolledOver(const HUI_Button *pButton)
{
	return pButton->bIsRolledOver;
}

/*!
 * \brief  Function to get if a button is clicked.
 *
 * \param  pButton Pointer to the button.
 * \return SDL_TRUE if the button is clicked, else SDL_FALSE.
 */
SDL_bool HUI_Button_IsClicked(const HUI_Button *pButton)
{
	return pButton->bIsClicked;
}

/* ========================================================================= */
