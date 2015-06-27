/* ========================================================================= */
/*!
 * \file    HUI_Button.h
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

#ifndef __HUI_BUTTON_H__
#define __HUI_BUTTON_H__

    #include "HUI_Input.h"

    /*!
     * \struct HUI_Button
     * \brief  Structure to handle a graphic button.
     */
    typedef struct
    {
        SDL_Anim sAnim;         /*!< Structure to animate the button. */
        SDL_Rect rHitbox;       /*!< Hitbox of the button. */

        SDL_bool bIsRolledOver; /*!< Flag to indicate if the button is rolled over. */
        SDL_bool bIsClicked;    /*!< Flag to indicate if the button is clicked. */
    } HUI_Button;

    void     HUI_Button_Init(HUI_Button *pButton, SDL_Sprite *pSprite, Sint32 x, Sint32 y);
    void     HUI_Button_Update(HUI_Button *pButton, const HUI_Input *pInput);
    void     HUI_Button_Draw(HUI_Button *pButton);

    SDL_bool HUI_Button_IsRolledOver(const HUI_Button *pButton);
    SDL_bool HUI_Button_IsClicked(const HUI_Button *pButton);

#endif // __HUI_BUTTON_H__

/* ========================================================================= */
