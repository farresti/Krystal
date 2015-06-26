/* ========================================================================= */
/*!
 * \file    COM_Shared.h
 * \brief   File to interface with the 'COM' includes & constants.
 * \author  Nyuu / Orlyn / Red
 * \version 1.0
 * \date    09 June 2015
 */
/* ========================================================================= */
/* Author  | Date     | Comments                                             */
/* --------+----------+----------------------------------------------------- */
/* Nyuu    | 09/06/15 | Creation.                                            */
/* Red     | 09/06/15 | __FUNCTION => __FUNCTION__                           */
/* ========================================================================= */

#ifndef __COM_SHARED_H__
#define __COM_SHARED_H__
    
    #ifdef _MSC_VER
        /*! Constant to remove some useless warnings with MSVC++. */
        #define _CRT_SECURE_NO_WARNINGS
        #define _CRT_NONSTDC_NO_DEPRECATE
    #else 
        /*! Constant to add for other IDE. */
        #define __FUNCTION__ __func__
    #endif
    
    /*! Constant to retrieve the filename. */
    #define __FILENAME__ (strrchr(__FILE__,'\\') ? (strrchr(__FILE__,'\\') + 1) : __FILE__)
    
    #include <stdio.h>
    #include <stdlib.h>
    #include <stdarg.h>
    #include <string.h>
    #include <time.h>
    
#endif // __COM_SHARED_H__

/* ========================================================================= */
