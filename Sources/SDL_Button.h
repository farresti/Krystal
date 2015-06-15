/* ========================================================================= */
/*!
 * \file    SDL_Button.h
 * \brief   File to interface with the graphic buttons.
 * \author  Nyuu / Orlyn / Red
 * \version 1.0
 * \date    09 June 2015
 */
/* ========================================================================= */
/* Author  | Date     | Comments                                             */
/* --------+----------+----------------------------------------------------- */
/* Nyuu    | 09/06/15 | Creation.                                            */
/* ========================================================================= */

#ifndef __SDL_BUTTON_H__
#define __SDL_BUTTON_H__

    #include "SDL_Sprite.h"
    #include "SDL_Input.h"

    /*!
     * \struct SDL_Button
     * \brief  Structure to handle a graphic button.
     */
    typedef struct
    {
        SDL_Sprite *pSprite;       /*!< Pointer to the sprite button. */

        SDL_Rect    rDest;         /*!< Rectangle to position the button. */
        double      dAngle;        /*!< Angle of the button. */

        SDL_bool    bIsRolledOver; /*!< Flag to indicate if the button is rolled over. */
        SDL_bool    bIsClicked;    /*!< Flag to indicate if the button is clicked. */
    } SDL_Button;

    void     SDL_Button_Init(SDL_Button *pButton, SDL_Sprite *pSprite, Sint32 x, Sint32 y);

    void     SDL_Button_SetAngle(SDL_Button *pButton, double dAngle);
    double   SDL_Button_GetAngle(SDL_Button *pButton);

    void     SDL_Button_Update(SDL_Button *pButton, SDL_Input *pInput);
    void     SDL_Button_Draw(SDL_Button *pButton);

    SDL_bool SDL_Button_IsRolledOver(SDL_Button *pButton);
    SDL_bool SDL_Button_IsClicked(SDL_Button *pButton);

#endif // __SDL_BUTTON_H__

/* ========================================================================= */
