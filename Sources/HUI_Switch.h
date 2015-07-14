/* ========================================================================= */
/*!
* \file    HUI_Switch.h
* \brief   File to interface with the switch.
* \author  Nyuu / Orlyn / Red
* \version 1.0
* \date    13 July 2015
*/
/* ========================================================================= */
/* Author  | Date     | Comments                                             */
/* --------+----------+----------------------------------------------------- */
/* Orlyn   | 13/07/15 | Creation.                                            */
/* ========================================================================= */

#ifndef __HUI_SWITCH_H__
#define __HUI_SWITCH_H__

    #include "HUI_Button.h"

    /*!
    * \enum HUI_SwitchState
    * \brief  enumeration of state for a switch.
    */
    typedef enum
    {
        HUI_SWITCH_DISABLED,
        HUI_SWITCH_ENABLED,
        HUI_SWITCH_PENDINGEN,
        HUI_SWITCH_PENDINGDIS
    }HUI_SwitchState;
     
    /*!
    * \struct HUI_Switch
    * \brief  Structure to handle a switch.
    */
    typedef struct HUI_Switch
    {
       
        HUI_SwitchState iState;               /*!< State of the switch. */

        HUI_Button      sButton;              /*!< Button associated with the switch. */
        SDL_Sprite     *pSpriteEnable;        /*!< Sprite for the enable state. */
        SDL_Sprite     *pSpriteDisable;       /*!< Sprite for the disable state. */

        SDL_Point       sPosition;            /*!< Position of the switch. */

        SDL_Rect        rHitboxEn;            /*!< Hitbox of the enable state. */
        SDL_Rect        rHitboxDis;           /*!< Hitbox of the disable state. */
        SDL_Rect        rSwitch;              /*!< Rect of the switch. */

        SDL_bool        bTransparent;         /*!< Flag to set the background of the switch transparent */
        SDL_Color       sColor;               /*!< Color of the background of the switch. */
    } HUI_Switch;

    void            HUI_Switch_Init(HUI_Switch *pSwitch, Sint32 x, Sint32 y, HUI_SwitchState iState, SDL_bool bIsTransparent, SDL_Color *pBackColor);
    void            HUI_Switch_Update(HUI_Switch *pSwitch, const HUI_Input *pInput);
    void            HUI_Switch_Draw(HUI_Switch *pSwitch);

    void            HUI_Switch_SetPosition(HUI_Switch *pSwitch, Sint32 x, Sint32 y);
    void            HUI_Switch_GetPosition(const HUI_Switch *pSwitch, SDL_Point *pPos);
    HUI_SwitchState HUI_Switch_GetState(const HUI_Switch *pSwitch);

#endif // __HUI_SWITCH_H__
/* ========================================================================= */
