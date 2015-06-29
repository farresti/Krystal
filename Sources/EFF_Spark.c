/* ========================================================================= */
/*!
 * \file    EFF_Spark.c
 * \brief   File to handle the effect 'Spark'.
 * \author  Nyuu / Orlyn / Red
 * \version 1.0
 * \date    28 June 2015
 */
/* ========================================================================= */
/* Author  | Date     | Comments                                             */
/* --------+----------+----------------------------------------------------- */
/* Nyuu    | 28/06/15 | Creation.                                            */
/* ========================================================================= */

#include "EFF_Spark.h"

/* ========================================================================= */

/*!
 * \struct ENG_Scheduler
 * \brief  Structure to handle the data of an effect 'Spark'.
 */
typedef struct
{
    Uint32    iNbSparks;       /*!< Number of sparks. */
    Uint32    iLifetime;       /*!< Lifetime of the effect. */

    SDL_Rect  arrRect[10];     /*!< Array of rectangles. */
    SDL_Point arrVelocity[10]; /*!< Array of rectangles. */
    SDL_Color arrColor[10];    /*!< Array of colors. */
} EFF_Spark;

/* ========================================================================= */

/*!
 * \brief  Function to update an effect 'Spark'.
 *
 * \param  pSpark Pointer to the effect.
 * \return None.
 */
static void EFF_Spark_Think(ENG_Effect *pSpark)
{
    EFF_Spark *pData = (EFF_Spark *)(pSpark->pData);
    Uint32 iTime     = SDL_GetTicks( );
    Uint32 i;

    if (iTime < pData->iLifetime)
    {
        for (i = 0 ; i < pData->iNbSparks ; ++i)
        {
            pData->arrRect[i].x += pData->arrVelocity[i].x;
            pData->arrRect[i].y += pData->arrVelocity[i].y;

            pData->arrColor[i].r -= (Uint8) COM_Math_Rand(0, 4);
            pData->arrColor[i].g -= (Uint8) COM_Math_Rand(0, 4);
            pData->arrColor[i].b -= (Uint8) COM_Math_Rand(0, 1);
        }

        pSpark->iNextThink = iTime + 25;
    }
    else
    {
        ENG_Effect_Kill(pSpark);
    }
}

/*!
 * \brief  Function to draw an effect 'Spark'.
 *
 * \param  pSpark Pointer to the effect.
 * \return None.
 */
static void EFF_Spark_Draw(ENG_Effect *pSpark)
{
    EFF_Spark *pData = (EFF_Spark *)(pSpark->pData);
    Uint32     i;

    for (i = 0 ; i < pData->iNbSparks ; ++i)
    {
        SDL_Render_DrawFullRect(&pData->arrRect[i], &pData->arrColor[i]);
    }
}

/* ========================================================================= */

/*!
 * \brief  Function to spawn an effect 'Spark'.
 *
 * \param  pOrigin Pointer to an origin.
 * \return None.
 */
void EFF_Spark_Spawn(const SDL_Point *pOrigin)
{
    ENG_Effect *pSpark = NULL;
    EFF_Spark  *pData  = NULL;
    Uint32      i;

    /* Allocate the effect. */
    pSpark = ENG_Effect_Alloc(sizeof(EFF_Spark));
    
    /* Init the basic data. */
    ENG_Effect_SetOrigin(pSpark, pOrigin);

    pSpark->iNextThink = SDL_GetTicks( ) + 25;
    pSpark->pftThink   = &(EFF_Spark_Think);
    pSpark->pftDraw    = &(EFF_Spark_Draw);

    /* Init the private data. */
    pData = (EFF_Spark *)(pSpark->pData); 

    pData->iNbSparks = COM_Math_Rand(7, 10);
    pData->iLifetime = SDL_GetTicks( ) + 1000;

    for (i = 0 ; i < pData->iNbSparks ; i++)
    {
        pData->arrRect[i].x = pOrigin->x + COM_Math_Rand(-2, 2);
        pData->arrRect[i].y = pOrigin->y + COM_Math_Rand(-2, 2);
        pData->arrRect[i].w = 2;
        pData->arrRect[i].h = 2;

        pData->arrVelocity[i].x = COM_Math_Rand(-3, 3);
        pData->arrVelocity[i].y = COM_Math_Rand(-3, 3);

        pData->arrColor[i].r = (Uint8) COM_Math_Rand(200, 240);
        pData->arrColor[i].g = (Uint8) COM_Math_Rand(200, 240);
        pData->arrColor[i].b = (Uint8) COM_Math_Rand(40, 80);
        pData->arrColor[i].a = 255;
    }

    /* Add to the scheduler. */
    ENG_Scheduler_AddEffect(pSpark);
}

/* ========================================================================= */
