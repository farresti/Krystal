/* ========================================================================= */
/*!
 * \file    COM_Log.h
 * \brief   File to interface with the logs.
 * \author  Nyuu / Orlyn / Red
 * \version 1.0
 * \date    09 June 2015
 */
/* ========================================================================= */
/* Author  | Date     | Comments                                             */
/* --------+----------+----------------------------------------------------- */
/* Nyuu    | 09/06/15 | Creation.                                            */
/* Red     | 10/06/15 | Add COM_LogType and COM_Log structure with basic     */
/*         |          | functions                                            */
/* ========================================================================= */

#ifndef __COM_LOG_H__
#define __COM_LOG_H__

    #include "COM_Shared.h"
    
    /*!
     * \enum  COM_LogType
     * \brief Enumeration of the possible type of logs.
     */
    typedef enum 
    {
        COM_LOG_DEBUG    = 0, /*!< Value 'debug' log. */
        COM_LOG_INFO     = 1, /*!< Value 'info' log. */
        COM_LOG_WARNING  = 2, /*!< Value 'warning' log. */
        COM_LOG_ERROR    = 3, /*!< Value 'error' log. */
        COM_LOG_CRITICAL = 4, /*!< Value 'critical' log. */
    } COM_LogType;

    void COM_Log_Init(COM_LogType iPrintLevel, const char *szPath);
    void COM_Log_Print(COM_LogType iPrintLevel, const char *szFormat, ...);
    void COM_Log_Quit(void);

#endif // __COM_LOG_H__

/* ========================================================================= */
