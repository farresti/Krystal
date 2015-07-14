/* ========================================================================= */
/*!
* \file    HUI_Switch.c
* \brief   File to handle the switch.
* \author  Nyuu / Orlyn / Red
* \version 1.0
* \date    13 July 2015
*/
/* ========================================================================= */
/* Author  | Date     | Comments                                             */
/* --------+----------+----------------------------------------------------- */
/* Orlyn   | 13/07/15 | Creation.                                            */
/* ========================================================================= */

#include "HUI_Switch.h"

/* ========================================================================= */

/*!
* \brief  Function to change sprite while sliding a switch.
*
* \param  pSwitch Pointer to the switch.
* \return None.
*/
static void HUI_Switch_ChangeSprite(HUI_Switch *pSwitch)
{
    SDL_Point sPoint;

    HUI_Button_GetPosition(&pSwitch->sButton, &sPoint);
    if (sPoint.x + (pSwitch->rHitboxDis.w >> 1) > pSwitch->sPosition.x + (pSwitch->rSwitch.w >> 1))
    {
        pSwitch->sButton.pSprite = pSwitch->pSpriteEnable;
        pSwitch->iState = HUI_SWITCH_PENDINGEN;
    }
    else if (sPoint.x + (pSwitch->rHitboxDis.w >> 1) < pSwitch->sPosition.x + (pSwitch->rSwitch.w >> 1))
    {
        pSwitch->sButton.pSprite = pSwitch->pSpriteDisable;
        pSwitch->iState = HUI_SWITCH_PENDINGDIS;
    }
}

/*!
* \brief  Function to keep a switch in the box.
*
* \param  pSwitch Pointer to the switch.
* \return None.
*/
static void HUI_Switch_LimitPosition(HUI_Switch *pSwitch)
{
    SDL_Point sPoint;

    HUI_Button_GetPosition(&pSwitch->sButton, &sPoint);
    if (sPoint.x < pSwitch->sPosition.x)
    {
        HUI_Button_SetPosition(&pSwitch->sButton, pSwitch->sPosition.x, pSwitch->sPosition.y);
    }
    else if (sPoint.x + pSwitch->rHitboxDis.w > pSwitch->sPosition.x + pSwitch->rSwitch.w)
    {
        HUI_Button_SetPosition(&pSwitch->sButton, pSwitch->rHitboxEn.x, pSwitch->sPosition.y);
    }
}

/*!
* \brief  Function to set a switch to enabled state.
*
* \param  pSwitch Pointer to the switch.
* \return None.
*/
static void HUI_Switch_SetEnabled(HUI_Switch *pSwitch)
{
    HUI_Button_SetPosition(&pSwitch->sButton, pSwitch->rHitboxEn.x, pSwitch->rHitboxEn.y);
    pSwitch->iState = HUI_SWITCH_ENABLED;
    pSwitch->sButton.pSprite = pSwitch->pSpriteEnable;
}

/*!
* \brief  Function to set a switch to disabled state.
*
* \param  pSwitch Pointer to the switch.
* \return None.
*/
static void HUI_Switch_SetDisabled(HUI_Switch *pSwitch)
{
    HUI_Button_SetPosition(&pSwitch->sButton, pSwitch->rHitboxDis.x, pSwitch->rHitboxDis.y);
    pSwitch->iState = HUI_SWITCH_DISABLED;
    pSwitch->sButton.pSprite = pSwitch->pSpriteDisable;
}
/* ========================================================================= */

/*!
* \brief  Function to init a switch.
*
* \param  pSwitch        Pointer to the switch.
* \param  x              Position on X.
* \param  y              Position on Y.
* \param  bState         Initial state of the switch.
* \param  bIsTransparent Flag to set the background of the switch transparent.
* \param  pBackColor     Color of the background.
* \return None.
*/
void HUI_Switch_Init(HUI_Switch *pSwitch, Sint32 x, Sint32 y, HUI_SwitchState iState, SDL_bool bIsTransparent, SDL_Color *pBackColor)
{
    pSwitch->sPosition.x  = x;
    pSwitch->sPosition.y  = y;

    pSwitch->iState       = iState;
    pSwitch->bTransparent = bIsTransparent;

    pSwitch->pSpriteEnable = SDL_Precache_Sprite("swOn"); 
    pSwitch->pSpriteDisable = SDL_Precache_Sprite("swOff");

    SDL_Sprite_GetFrameSize(pSwitch->pSpriteEnable, &pSwitch->rHitboxEn);
    SDL_Sprite_GetFrameSize(pSwitch->pSpriteDisable, &pSwitch->rHitboxDis);

    pSwitch->rSwitch.x = x;
    pSwitch->rSwitch.y = y;
    pSwitch->rSwitch.w = (Sint32)((double)pSwitch->rHitboxEn.w * 1.67);
    pSwitch->rSwitch.h = pSwitch->rHitboxDis.h;

    pSwitch->rHitboxDis.x = x;
    pSwitch->rHitboxDis.y = y;

    pSwitch->rHitboxEn.x = x + pSwitch->rSwitch.w - pSwitch->rHitboxEn.w;
    pSwitch->rHitboxEn.y = y;

    if (iState == HUI_SWITCH_ENABLED)
    {
        HUI_Button_Init(&pSwitch->sButton, pSwitch->pSpriteEnable, pSwitch->rHitboxEn.x, pSwitch->rHitboxEn.y);
    }
    else
    {
        HUI_Button_Init(&pSwitch->sButton, pSwitch->pSpriteDisable, pSwitch->rHitboxDis.x, pSwitch->rHitboxDis.y);
    }

    if (!bIsTransparent)
    {
        pSwitch->sColor = *pBackColor;
    }
}

/*!
* \brief  Function to update a switch.
*
* \param  pSwitch Pointer to the switch.
* \param  pInput  Pointer to the inputs.
* \return None.
*/
void HUI_Switch_Update(HUI_Switch *pSwitch, const HUI_Input *pInput)
{
    SDL_Point sPoint;
    HUI_ButtonState iState = HUI_Button_GetState(&pSwitch->sButton);
    HUI_Button_Update(&pSwitch->sButton, pInput); 
    if (HUI_Button_GetState(&pSwitch->sButton) == HUI_BUTTON_ACTIVE)
    {
        HUI_Button_SetPosition(&pSwitch->sButton, pInput->iMouse.x + pInput->iMouseRel.x - (pSwitch->rHitboxEn.w >> 1), pSwitch->sPosition.y);
        HUI_Switch_ChangeSprite(pSwitch);        
        HUI_Switch_LimitPosition(pSwitch);
    }
    if (HUI_Button_GetState(&pSwitch->sButton) != iState &&
        iState == HUI_BUTTON_ACTIVE)
    { 
        if (pSwitch->iState == HUI_SWITCH_PENDINGEN)
        {
            HUI_Switch_SetEnabled(pSwitch);
        }
        else if (pSwitch->iState == HUI_SWITCH_PENDINGDIS)
        {
            HUI_Switch_SetDisabled(pSwitch);
        }
    }
    if (HUI_Button_GetState(&pSwitch->sButton) == HUI_BUTTON_INACTIVE && pInput->bMouseButtons[SDL_BUTTON_LEFT])
    {
        HUI_Input_GetMousePosition(pInput, &sPoint);
        if (UTIL_ContainPoint(&pSwitch->rHitboxDis, &sPoint))
        {
            HUI_Switch_SetDisabled(pSwitch);
        }
        else if (UTIL_ContainPoint(&pSwitch->rHitboxEn, &sPoint))
        {
            HUI_Switch_SetEnabled(pSwitch);
        }
    }
}

/*!
* \brief  Function to draw a switch.
*
* \param  pSwitch Pointer to the switch.
* \return None.
*/
void HUI_Switch_Draw(HUI_Switch *pSwitch)
{
    SDL_Color sColor;
    sColor.r = 175;
    sColor.g = 171;
    sColor.b = 171;
    sColor.a = 255;
    if (!pSwitch->bTransparent)
    {
        SDL_Render_DrawFullRect(&pSwitch->rSwitch, &pSwitch->sColor);
    }
    SDL_Render_DrawEmptyRect(&pSwitch->rSwitch, &sColor);
    HUI_Button_Draw(&pSwitch->sButton);
}

/*!
* \brief  Function to set the position of a switch.
*
* \param  pSwitch Pointer to the switch.
* \param  x       Position on X to set.
* \param  y       Position on Y to set.
* \return None.
*/
void HUI_Switch_SetPosition(HUI_Switch *pSwitch, Sint32 x, Sint32 y)
{
    pSwitch->sPosition.x  = x;
    pSwitch->sPosition.y  = y;

    pSwitch->rSwitch.x    = x;
    pSwitch->rSwitch.y    = y;

    pSwitch->rHitboxDis.x = x;
    pSwitch->rHitboxDis.y = y;

    pSwitch->rHitboxEn.x  = x + pSwitch->rSwitch.w - pSwitch->rHitboxEn.w;
    pSwitch->rHitboxEn.y  = y;

    if (pSwitch->iState == HUI_SWITCH_DISABLED)
    {
        HUI_Button_SetPosition(&pSwitch->sButton, pSwitch->rHitboxDis.x, pSwitch->rHitboxDis.y);
    }
    else if (pSwitch->iState == HUI_SWITCH_ENABLED)
    {
        HUI_Button_SetPosition(&pSwitch->sButton, pSwitch->rHitboxEn.x, pSwitch->rHitboxEn.y);
    }    
}

/*!
* \brief  Function to get the position of a switch.
*
* \param  pSwitch Pointer to the switch.
* \param  pPos    Pointer to to be filled with the position.
* \return None.
*/
void HUI_Switch_GetPosition(const HUI_Switch *pSwitch, SDL_Point *pPos)
{
    *pPos = pSwitch->sPosition;
}

/*!
* \brief  Function to get the state of a switch.
*
* \param  pSwitch Pointer to the switch.
* \return SDL_TRUE if active, SDL_FALSE else.
*/
HUI_SwitchState HUI_Switch_GetState(const HUI_Switch *pSwitch)
{
    return pSwitch->iState;
}
/* ========================================================================= */