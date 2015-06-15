/* ========================================================================= */
/*!
 * \file    SDL_Button.c
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

#include "SDL_Util.h"
#include "SDL_Button.h"

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
void SDL_Button_Init(SDL_Button *pButton, SDL_Sprite *pSprite, Sint32 x, Sint32 y)
{
    pButton->pSprite = pSprite;

    SDL_Sprite_GetFrameSize(pSprite, &pButton->rDest);
    pButton->rDest.x = x;
    pButton->rDest.y = y;
    pButton->dAngle  = 0.0;

    pButton->bIsRolledOver = SDL_FALSE;
    pButton->bIsClicked    = SDL_FALSE;
}

/*!
 * \brief Function to set the angle of a button.
 *
 * \param pButton Pointer to the button.
 * \param dAngle  Angle to rotate the button.
 * \return None.
 */
void SDL_Button_SetAngle(SDL_Button *pButton, double dAngle)
{
    pButton->dAngle = dAngle;
}

/*!
 * \brief  Function to get the angle of a button.
 *
 * \param  pButton Pointer to the button.
 * \return The angle of the button.
 */
double SDL_Button_GetAngle(SDL_Button *pButton)
{
    return pButton->dAngle;
}

/*!
 * \brief  Function to update a button.
 *
 * \param  pButton Pointer to the button.
 * \param  pInput  Pointer to the inputs.
 * \return None.
 */
void SDL_Button_Update(SDL_Button *pButton, SDL_Input *pInput)
{
    /* ~~~ Check the position of the mouse.. ~~~ */
    if (pInput->bMotionEvent)
    {
        if (UTIL_ContainPoint(pInput->iMouseX, pInput->iMouseY, &pButton->rDest))
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
			SDL_Sprite_SetFrame(pButton->pSprite, 2);
		}
		else
		{
			SDL_Sprite_SetFrame(pButton->pSprite, 1);
		}
	}
	else
	{
		SDL_Sprite_SetFrame(pButton->pSprite, 0);
	}
}

/*!
 * \brief  Function to draw a button.
 *
 * \param  pButton Pointer to the button.
 * \return None.
 */
void SDL_Button_Draw(SDL_Button *pButton)
{
    SDL_Sprite_Draw(pButton->pSprite, &pButton->rDest, pButton->dAngle, SDL_FLIP_NONE);
}

/*!
 * \brief  Function to get if a button is rolled over.
 *
 * \param  pButton Pointer to the button.
 * \return SDL_TRUE if the button is rolled over, else SDL_FALSE.
 */
SDL_bool SDL_Button_IsRolledOver(SDL_Button *pButton)
{
	return pButton->bIsRolledOver;
}

/*!
 * \brief  Function to get if a button is clicked.
 *
 * \param  pButton Pointer to the button.
 * \return SDL_TRUE if the button is clicked, else SDL_FALSE.
 */
SDL_bool SDL_Button_IsClicked(SDL_Button *pButton)
{
	return pButton->bIsClicked;
}

/* ========================================================================= */
