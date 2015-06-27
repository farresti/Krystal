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
/* Red     | 27/06/15 | Add new parameter sPointButton                       */
/*         |          | Add SetPosition, GetPosition, GetHitbox              */
/* ========================================================================= */

#ifndef __HUI_BUTTON_H__
#define __HUI_BUTTON_H__

    #include "HUI_Input.h"

    /*!
     * \enum HUI_ButtonState
     * \brief Enumeration to handle the states of a graphic button.
     */
    typedef enum
    {
        HUI_BUTTON_INACTIVE    = 0, /*!< Value 'inactive' button. */
        HUI_BUTTON_ROLLED_OVER = 1, /*!< Value 'rolled over' button. */
        HUI_BUTTON_ACTIVE      = 2  /*!< Value 'active' button. */
    } HUI_ButtonState;

    /*!
     * \struct HUI_Button
     * \brief  Structure to handle a graphic button.
     */
    typedef struct
    {
        SDL_Sprite *pSprite;    /*!< Pointer to a sprite. */

        SDL_Point sPosition;    /*!< Position of the button. */
        SDL_Rect  rHitbox;      /*!< Hitbox of the button. */

        HUI_ButtonState iState; /*!< State of the button. */
    } HUI_Button;

    void HUI_Button_Init(HUI_Button *pButton, SDL_Sprite *pSprite, Sint32 x, Sint32 y);
    void HUI_Button_Update(HUI_Button *pButton, const HUI_Input *pInput);
    void HUI_Button_Draw(HUI_Button *pButton);

    void HUI_Button_SetPosition(HUI_Button *pButton, Sint32 x, Sint32 y);
    void HUI_Button_GetPosition(const HUI_Button *pButton, SDL_Point *pPos);
    void HUI_Button_GetHitbox(const HUI_Button *pButton, SDL_Rect *pHitbox);

    HUI_ButtonState HUI_Button_GetState(const HUI_Button *pButton);

#endif // __HUI_BUTTON_H__

/* ========================================================================= */
