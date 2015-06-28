/* ========================================================================= */
/*!
 * \file    HUI_Scrollbar.c
 * \brief   File to handle the scrollbar.
 * \author  Nyuu / Orlyn / Red
 * \version 1.0
 * \date    27 June 2015
 */
/* ========================================================================= */
/* Author  | Date     | Comments                                             */
/* --------+----------+----------------------------------------------------- */
/* Red     | 27/06/15 | Creation.                                            */
/* ========================================================================= */

#include "HUI_Scrollbar.h"

/* ========================================================================= */

/*!
 * \brief  Function to init a scrollbar.
 *
 * \param  pScrollbar       Pointer to the scrollbar.
 * \param  pSpriteScrollbar Pointer to the sprite used for the scrollbar.
 * \param  pSpriteSlider    Pointer to the sprite used for the slider.
 * \param  rHitboxScrollbar Hitbox of the scrollbar
 * \param  iMin             The minimum value of the scrollbar.
 * \param  iMax             The maximum value of the scrollbar (!= 0).
 * \return None.
 */
void HUI_Scrollbar_Init(HUI_Scrollbar *pScrollbar, SDL_Sprite *pSpriteScrollbar, SDL_Sprite *pSpriteSlider, SDL_Rect rHitboxScrollbar, Sint32 iMin, Sint32 iMax)
{
    pScrollbar->iCurrent = 0;
    pScrollbar->iMin     = iMin;
    pScrollbar->iMax     = iMax;


    SDL_Anim_Init(&pScrollbar->sAnimScrollbar, pSpriteScrollbar);
    SDL_Anim_SetFrame(&pScrollbar->sAnimScrollbar, 0);

    HUI_Button_Init(&pScrollbar->sButtonSlider, pSpriteSlider, 0, 0);

    pScrollbar->rHitboxScrollbar.x = rHitboxScrollbar.x;
    pScrollbar->rHitboxScrollbar.y = rHitboxScrollbar.y;
    pScrollbar->rHitboxScrollbar.h = rHitboxScrollbar.h;
    pScrollbar->rHitboxScrollbar.w = rHitboxScrollbar.w;

    pScrollbar->sPointScrollbar.x = rHitboxScrollbar.x;
    pScrollbar->sPointScrollbar.y = rHitboxScrollbar.y;
}


/*!
* \brief  Function to set the position of the scrollbar.
*
* \param  pScrollbar Pointer to the scrollbar.
* \param  x          Scrollbar position on x.
* \param  y          Scrollbar position on y.
* \return None.
*/
void HUI_Scrollbar_SetPosition(HUI_Scrollbar *pScrollbar, Sint32 x, Sint32 y)
{
    Uint32 iEcart = 0;

    iEcart = pScrollbar->sButtonSlider.sPointButton.x - pScrollbar->sPointScrollbar.x;
    SDL_Anim_SetPosition(&pScrollbar->sAnimScrollbar, x, y); // ca va virer normalement

    pScrollbar->sPointScrollbar.x = x;
    pScrollbar->sPointScrollbar.y = y;

    pScrollbar->rHitboxScrollbar.x = x;
    pScrollbar->rHitboxScrollbar.y = y;

    // TODO
    // Update the slider position also without overwritting the current value 
    HUI_Button_SetPosition(&pScrollbar->sButtonSlider, x +iEcart, y);
}
/*!
* \brief  Function to draw a scrollbar.
*
* \param  pScrollbar Pointer to the scrollbar.
* \return None.
*/
void HUI_Scrollbar_Draw(HUI_Scrollbar *pScrollbar)
{
    SDL_Anim_Draw(&pScrollbar->sAnimScrollbar);
    HUI_Button_Draw(&pScrollbar->sButtonSlider);
}

/*!
* \brief  Function to update a scrollbar.
*
* \param  pScrollbar Pointer to the scrollbar.
* \param  pInput  Pointer to the inputs.
* \return None.
*/
void HUI_Scrollbar_Update(HUI_Scrollbar *pScrollbar, const HUI_Input *pInput)
{
    SDL_Rect  rRectSlider;
    SDL_Point sPointSlider;
    SDL_Point sMidSlider;
    Uint32    iTmp = 0;
    rRectSlider  = HUI_Button_GetHitbox(&pScrollbar->sButtonSlider);
    sPointSlider = HUI_Button_GetPosition(&pScrollbar->sButtonSlider);
    sMidSlider.x = rRectSlider.w / 2;
    HUI_Button_Update(&pScrollbar->sButtonSlider,pInput);

    if(pScrollbar->sButtonSlider.bIsClicked) // Appuie
    { 
        if ((pInput->iMouse.x >= pScrollbar->sPointScrollbar.x) && (pInput->iMouse.x <= (pScrollbar->sPointScrollbar.x + pScrollbar->rHitboxScrollbar.w + sMidSlider.x)))  // Toujours dans la barre de scroll
        {
            //Petit problème d'accroche de la barre si on bouge trop vite mais bon ...
            

            if (pInput->iMouse.x - sMidSlider.x < 0) sMidSlider.x = 0; // empecher le curseur d'aller hors de la barre
            HUI_Button_SetPosition(&pScrollbar->sButtonSlider, pInput->iMouse.x - sMidSlider.x, pScrollbar->sPointScrollbar.y);

            //Update current value
            if ((sPointSlider.x == 0) || (sPointSlider.x - pScrollbar->sPointScrollbar.x) < 0)
            {
                pScrollbar->iCurrent = 0;
            }
            else
            {
                iTmp = pScrollbar->rHitboxScrollbar.w - (sPointSlider.x - pScrollbar->sPointScrollbar.x) - (1 / pScrollbar->rHitboxScrollbar.w);
                pScrollbar->iCurrent = pScrollbar->iMax - (iTmp *pScrollbar->iMax) / pScrollbar->rHitboxScrollbar.w;
            }
            
        } 
    }
}


/*!
* \brief Function to set the values of a scrollbar.
*
* \param  pScrollbar Pointer to the scrollbar.
* \param  iMax       The maximum value of the scrollbar.
* \param  iMin       The minimum value of the scrollbar.
* \param  iStep      The step value of the scrollbar.
* \return None.
*/
void HUI_Scrollbar_SetValue(HUI_Scrollbar *pScrollbar, Sint32 iMin, Sint32 iMax, Sint32 iStep)
{
    pScrollbar->iMin  = iMin;
    pScrollbar->iMax  = iMax;
    pScrollbar->iStep = iStep;
}

/*!
* \brief  Function to get the current value of a scrollbar.
*
* \param  pScrollbar Pointer to the scrollbar.
* \return The current value of the scrollbar.
*/
Sint32 HUI_Scrollbar_GetCurrent(const HUI_Scrollbar *pScrollbar)
{
    return pScrollbar->iCurrent;
}

/*!
* \brief  Function to get the maximum value of a scrollbar.
*
* \param  pScrollbar Pointer to the scrollbar.
* \return The maximum value of the scrollbar.
*/
Sint32 HUI_Scrollbar_GetMax(const HUI_Scrollbar *pScrollbar)
{
    return pScrollbar->iMax;
}

/*!
* \brief  Function to get the minimum value of a scrollbar.
*
* \param  pScrollbar  Pointer to the scrollbar.
* \return The minimum value of the scrollbar.
*/
Sint32 HUI_Scrollbar_GetMin(const HUI_Scrollbar *pScrollbar)
{
    return pScrollbar->iMin;
}

/*!
* \brief  Function to get the step value of a scrollbar.
*
* \param  pScrollbar  Pointer to the scrollbar.
* \return The step value of the scrollbar.
*/
Sint32 HUI_Scrollbar_GetStep(const HUI_Scrollbar *pScrollbar)
{
    return pScrollbar->iStep;
}

/* ========================================================================= */
