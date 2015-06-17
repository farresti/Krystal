/* ========================================================================= */
/*!
 * \file    COM_Util.h
 * \brief   File to interface with the 'COM' util functions.
 * \author  Nyuu / Orlyn / Red
 * \version 1.0
 * \date    09 June 2015
 */
/* ========================================================================= */
/* Author  | Date     | Comments                                             */
/* --------+----------+----------------------------------------------------- */
/* Nyuu    | 09/06/15 | Creation.                                            */
/* Orlyn   | 10/06/15 | Add new functions COM_UTIL_*                         */
/* Orlyn   | 11/06/15 | Add COM_UTIL_StrCopy                                 */
/* ========================================================================= */

#ifndef __COM_UTIL_H__
#define __COM_UTIL_H__

    #include "COM_Shared.h"

    /* Memory leaks */
    #ifdef _DEBUG
        #define UTIL_Malloc(x)    UTIL_MallocEx(x, __FUNCTION__, __LINE__, __FILE__)
        #define UTIL_Realloc(x,y) UTIL_ReallocEx(x, y, __FUNCTION__, __LINE__, __FILE__)
        #define UTIL_Free(x)      UTIL_FreeEx((void**)&x, __FUNCTION__, __LINE__, __FILE__) 

        void *UTIL_MallocEx(size_t iSize, const char *szFct, size_t iLine, const char *szFile);
        void *UTIL_ReallocEx(void* pOldMemoryBlock, size_t iNewSize, const char *szFct, size_t iLine, const char *szFile);
        void  UTIL_FreeEx(void** ppMemory, const char *szFct, size_t iLine, const char *szFile);
    #else
        void *UTIL_Malloc(size_t iSize);
        void *UTIL_Realloc(void* pOldMemoryBlock, size_t iNewSize);
        #define UTIL_Free(x) \
                        do\
                        {\
                            if(x)\
                            {\
                                free(x);\
                                x = NULL;\
                            }\
                        }while(x)

    #endif // _DEBUG

    FILE *UTIL_Fopen(const char *szPath, const char *szMode);
    void  UTIL_Fclose(FILE **ppFile);

    char *UTIL_StrCopy(const char *szSrc);
    char *UTIL_StrBuild(const char *szStart, ...);

    void UTIL_RandInit(void);
    int  UTIL_Rand(int iMin, int iMax);

#endif // __COM_UTIL_H__

/* ========================================================================= */
