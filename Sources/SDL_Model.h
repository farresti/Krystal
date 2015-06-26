/* ========================================================================= */
/*!
 * \file    SDL_Model.h
 * \brief   File to interface with the models.
 * \author  Nyuu / Orlyn / Red
 * \version 1.0
 * \date    26 June 2015
 */
/* ========================================================================= */
/* Author  | Date     | Comments                                             */
/* --------+----------+----------------------------------------------------- */
/* Nyuu    | 26/06/15 | Creation.                                            */
/* ========================================================================= */

#ifndef __SDL_MODEL_H__
#define __SDL_MODEL_H__

    #include "SDL_Anim.h"

    /*!
     * \struct SDL_Model
     * \brief  Structure to handle a model.
     */
    typedef struct
    {
        char *szName; /*!< Name of the model. */
    } SDL_Model;

#endif // __SDL_MODEL_H__

/* ========================================================================= */
