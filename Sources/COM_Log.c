/* ========================================================================= */
/*!
 * \file    COM_Log.c
 * \brief   File to handle the logs.
 * \author  Nyuu / Orlyn / Red
 * \version 1.0
 * \date    09 June 2015
 */
/* ========================================================================= */
/* Author  | Date     | Comments                                             */
/* --------+----------+----------------------------------------------------- */
/* Nyuu    | 09/06/15 | Creation.                                            */
/* Red     | 10/06/15 | Add basics functions.                                */
/* Red     | 14/06/15 | Remove szLogName from the structure, useless         */
/*         |          | File is now created in logs/name.log                 */
/* ========================================================================= */

#include "COM_Util.h"
#include "COM_Log.h"

/* ========================================================================= */

/*!
 * \struct COM_Log
 * \brief  Structure to handle the logs.
 */
typedef struct
{
    FILE        *pLogFile;    /*!< Pointer to the logs file. */
    COM_LogType  iPrintLevel; /*!< Type of logs allowed. */
} COM_Log;

/*! Global variable to handle the logs. */
static COM_Log COM_log;

/* ========================================================================= */

/*!
 * \brief Function to initialize the logs.
 *
 * \param iPrintLevel Level of print.
 * \param szPath      Path of the logs file.
 * \return None.
 */
void COM_Log_Init(COM_LogType iPrintLevel, const char *szPath)
{
    char       szTimeBuffer[128];
    char      *szLogPath = NULL;
    time_t     sTime;
    struct tm *pTimeinfo = NULL;

    szLogPath = UTIL_StrBuild("logs/", szPath, ".log", NULL);

    if (szLogPath)
    {
        COM_log.pLogFile = fopen(szLogPath, "w+");

        if (COM_log.pLogFile)
        {
            time(&sTime);
            pTimeinfo = localtime(&sTime);
            strftime(szTimeBuffer, sizeof(szTimeBuffer), "%A %Y-%m-%d -- %H:%M:%S", pTimeinfo);

            fprintf(COM_log.pLogFile, "***********************************************************************\n");
            fprintf(COM_log.pLogFile, "                    %s\n", szTimeBuffer);
            fprintf(COM_log.pLogFile, "***********************************************************************\n\n");

            COM_log.iPrintLevel = iPrintLevel;
        }

        UTIL_Free(szLogPath);
    }
}

/*!
 * \brief Function to print a log message.
 *
 * \param iPrintLevel Prefix of log message to use ( cf COM_LogType ).
 * \param szFormat    The formatted message to write.
 * \return None.
 */
void COM_Log_Print(COM_LogType iPrintLevel, const char *szFormat, ...)
{
    static const char *szLogTxt[] = { "Debug   : ", 
                                      "Info    : ", 
                                      "Warning : ", 
                                      "Error   : ", 
                                      "Critical: " };
    va_list            ap;

    if (COM_log.pLogFile && COM_log.iPrintLevel <= iPrintLevel)
    {
        fputs(szLogTxt[iPrintLevel], COM_log.pLogFile);

        va_start(ap, szFormat);
        vfprintf(COM_log.pLogFile, szFormat, ap);
        va_end(ap);

        fputc('\n', COM_log.pLogFile);

        // If crash...
        fflush(COM_log.pLogFile);
    }
}

/*!
 * \brief Function to close the logs.
 *
 * \return None
 */
void COM_Log_Quit(void)
{
    UTIL_FileClose(&COM_log.pLogFile);
}

/* ========================================================================= */
