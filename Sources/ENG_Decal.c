/* ========================================================================= */
/*!
 * \file    ENG_Decal.c
 * \brief   File to handle the decals.
 * \author  Nyuu / Orlyn / Red
 * \version 1.0
 * \date    04 July 2015
 */
/* ========================================================================= */
/* Author  | Date     | Comments                                             */
/* --------+----------+----------------------------------------------------- */
/* Nyuu    | 04/07/15 | Creation.                                            */
/* ========================================================================= */

#include "ENG_View.h"
#include "ENG_Decal.h"

/* ========================================================================= */

/*!
 * \brief  Function to allocate a decal.
 *
 * \return A pointer to the allocated decal, or NULL if error.
 */
ENG_Decal *ENG_Decal_Alloc(void)
{
    ENG_Decal *pDecal = (ENG_Decal *) UTIL_Malloc(sizeof(ENG_Decal));

    if (pDecal)
    {
        memset(pDecal, 0, sizeof(ENG_Decal));
    }

    return pDecal;
}

/*!
 * \brief  Function to set a decal origin.
 *
 * \param  pDecal  Pointer to the decal.
 * \param  pOrigin Pointer to an origin.
 * \return None.
 */
void ENG_Decal_SetOrigin(ENG_Decal *pDecal, const SDL_Point *pOrigin)
{
    pDecal->sOrigin.x = pOrigin->x;
    pDecal->sOrigin.y = pOrigin->y;
}

/*!
 * \brief  Function to set a decal layer.
 *
 * \param  pDecal Pointer to the decal.
 * \param  iLayer Index of a layer.
 * \return None.
 */
void ENG_Decal_SetLayer(ENG_Decal *pDecal, const Uint32 iLayer)
{
    pDecal->iLayer = iLayer;
}

/*!
 * \brief  Function to set a decal sprite.
 *
 * \param  pDecal  Pointer to the decal.
 * \param  pSprite Pointer to an allocated sprite.
 * \return None.
 */
void ENG_Decal_SetSprite(ENG_Decal *pDecal, SDL_Sprite *pSprite)
{
    pDecal->pSprite = pSprite;
}

/*!
 * \brief  Function to set a decal frame.
 *
 * \param  pDecal Pointer to the decal.
 * \param  iFrame Index of a frame.
 * \return None.
 */
void ENG_Decal_SetFrame(ENG_Decal *pDecal, const Uint32 iFrame)
{
    pDecal->iFrame = iFrame;
}

/*!
 * \brief  Function to draw a decal.
 *
 * \param  pDecal Pointer to the decal.
 * \param  iLayer Index of the current layer.
 * \return None.
 */
void ENG_Decal_Draw(ENG_Decal *pDecal, const Uint32 iLayer)
{
    if (pDecal->iLayer == iLayer)
    {
        ENG_View_ConvOrigin(&pDecal->sOrigin, &pDecal->sPosition);

        SDL_Sprite_Draw(pDecal->pSprite, &pDecal->sPosition, pDecal->iFrame);
    }
}

/*!
 * \brief  Function to free a decal.
 *
 * \param  ppDecal Pointer to pointer to the decal.
 * \return None.
 */
void ENG_Decal_Free(ENG_Decal **ppDecal)
{
    UTIL_Free(*ppDecal);
}

/* ========================================================================= */
