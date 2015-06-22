/* ========================================================================= */
/*!
 * \file    COM_Util.c
 * \brief   File to handle the 'COM' util functions.
 * \author  Nyuu / Orlyn / Red
 * \version 1.0
 * \date    09 June 2015
 */
/* ========================================================================= */
/* Author  | Date     | Comments                                             */
/* --------+----------+----------------------------------------------------- */
/* Nyuu    | 09/06/15 | Creation.                                            */
/* Orlyn   | 10/06/15 | Add new functions UTIL_*                             */
/* Orlyn   | 11/06/15 | Add UTIL_StrCopy                                     */
/* ========================================================================= */

#include "COM_Log.h"
#include "COM_Util.h"

/* ========================================================================= */

#ifdef _DEBUG

/*! Global variable to count the allocations */
static unsigned int COM_iMallocCounter;

/*!
 * \brief Function to allocate a memory block (Debug).
 *
 * \param iSize  Size of the block to allocate.
 * \param szFct  Name of the function calling malloc.
 * \param iLine  Line of the call to malloc.
 * \param szFile Name of the file where the function is located.
 * \return A pointer to the allocated block, or NULL if error
 */
void *UTIL_MallocEx(size_t iSize, const char *szFct, size_t iLine, const char *szFile)
{
    void *pAllocatedMemory = malloc(iSize);

    if (pAllocatedMemory != NULL)
    {
        COM_Log_Print(COM_LOG_DEBUG,
                      "\nIn file : l%d %s\n"
                      "Function : %s\n"
                      "Allocated %u blocks @ %p\n",
                      iLine, szFile, szFct, iSize, pAllocatedMemory);

        COM_iMallocCounter++;
    }
    else
    {
        COM_Log_Print(COM_LOG_CRITICAL,
                      "\nIn file : l%d %s\n"
                      "Function : %s\n"
                      "Tried to allocate %u blocks, Insuffisient memory.\n",
                      iLine, szFile, szFct, iSize);
    }

    return pAllocatedMemory;
}

/*!
 * \brief Function to (re)allocate a memory block (Debug).
 *
 * \param pOldMemoryBlock Pointer to a memory block (Can be NULL).
 * \param iNewSize        New size of the memory block.
 * \param szFct           Name of the function calling malloc.
 * \param iLine           Line of the call to malloc.
 * \param szFile          Name of the file where the function is located.
 * \return A pointer to the (re)allocated block, or NULL if error
*/
void *UTIL_ReallocEx(void *pOldMemoryBlock, size_t iNewSize, const char *szFct, size_t iLine, const char *szFile)
{
    void *pNewMemoryBlock;

    pNewMemoryBlock = realloc(pOldMemoryBlock, iNewSize);

    if (pNewMemoryBlock != NULL)
    {
        if(pOldMemoryBlock == NULL)
        {
            COM_iMallocCounter++;
        }

        COM_Log_Print(COM_LOG_DEBUG,
                      "\nIn file : l%d %s\n"
                      "Function : %s\n"
                      "Reallocated %u blocks from @ %p\n",
                      iLine, szFile, szFct, iNewSize, pOldMemoryBlock);
    }
    else
    {
        if(pOldMemoryBlock == NULL)
        {
            COM_iMallocCounter--;
        }

        COM_Log_Print(COM_LOG_CRITICAL,
                      "\nIn file : l%d %s\n"
                      "Function : %s\n"
                      "Failed to reallocated %u blocks @ %p\n",
                      iLine, szFile, szFct, iNewSize, pOldMemoryBlock);
    }

    return pNewMemoryBlock;
}

/*!
 * \brief Function to free a memory block (Debug).
 *
 * \param ppMemory Pointer to pointer to the memory block to free.
 * \param szFct    Name of the function calling free.
 * \param iLine    Line of the call to free.
 * \param szFile   Name of the file where the function is located.
 * \return None
 */
void UTIL_FreeEx(void** ppMemory, const char *szFct, size_t iLine, const char *szFile)
{
    if (*ppMemory != NULL)
    {
      free(*ppMemory);
      COM_iMallocCounter--;
    }

    COM_Log_Print(COM_LOG_DEBUG,
                  "\nIn file : l%d %s\n"
                  "Function : %s\n"
                  "Freed @ %p\n"
                  "Blocks remaining : %d\n",
                  iLine, szFile, szFct, *ppMemory, COM_iMallocCounter);
    *ppMemory = NULL;
}

#else

/*!
 * \brief Function to allocate a memory block.
 *
 * \param iSize Size of the block to allocate.
 * \return A pointer to the allocated block, or NULL if error
 */
void *UTIL_Malloc(size_t iSize)
{
    void *pAllocatedMemory = malloc(iSize);

    if (pAllocatedMemory == NULL)
    {
        COM_Log_Print(COM_LOG_CRITICAL,
                      "Failed to allocated %u memory blocks, not enough memory !",
                      iSize);
    }

    return pAllocatedMemory;
}

/*!
 * \brief Function to (re)allocate a memory block.
 *
 * \param pOldMemoryBlock Pointer to a memory block (Can be NULL).
 * \param iNewSize        New size of the memory block.
 * \return A pointer to the (re)allocated block, or NULL if error
 */
void *UTIL_Realloc(void *pOldMemoryBlock, size_t iNewSize)
{
    void *pNewMemoryBlock = realloc(pOldMemoryBlock, iNewSize);

    if (pNewMemoryBlock == NULL)
    {
        COM_Log_Print(COM_LOG_CRITICAL,
                      "Failed to allocated %u memory blocks, not enough memory !",
                      iNewSize);
    }

    return pNewMemoryBlock;
}

/*!
 * \brief Function to free a memory block.
 *
 * \param ppMemory Pointer to pointer to a memory block.
 * \return None
 */
void UTIL_Free(void **ppMemory)
{
    if(*ppMemory != NULL)
    {
        free(*ppMemory);
        *ppMemory = NULL;
    }
}

#endif // _DEBUG

/* ========================================================================= */

/*!
 * \brief Function to open a file.
 *
 * \param szPath Path of the file to open.
 * \param szMode Mode used to open the file.
 * \return A pointer to the opened file, or NULL if error.
 */
FILE *UTIL_FileOpen(const char *szPath, const char *szMode)
{
    FILE *pFile = fopen(szPath, szMode);

    if (pFile == NULL)
    {
        COM_Log_Print(COM_LOG_ERROR, "Can't open a file (Mode : %s) !",
                                     strchr(szMode, 'r') ? "Read" : "Write");
        COM_Log_Print(COM_LOG_ERROR, "Path: \"%s\"", szPath);
    }

    return pFile;
}

/*!
 * \brief Function to close a file.
 *
 * \param ppFile Pointer to pointer to the file to close.
 * \return None.
 */
void UTIL_FileClose(FILE **ppFile)
{
    if (*ppFile != NULL)
    {
        fclose(*ppFile);
        *ppFile = NULL;
    }
}

/*!
 * \brief Function to allocate and copy a string.
 *
 * \param  szSrc Pointer to the string to copy.
 * \return A pointer to the allocated string, or NULL if error.
 */
char *UTIL_StrCopy(const char *szSrc)
{
    size_t iLen = strlen(szSrc);

    char *szCopy = ( char * ) UTIL_Malloc(iLen + 1);

    if (szCopy)
    {
        memcpy(szCopy, szSrc, iLen + 1);
    }

    return szCopy;
}

/*!
 * \brief Function to allocate and build a string.
 *
 * \param szStart Pointer to the first string.
 * \return A pointer to the allocated string, or NULL if error.
 *
 * \remark The last string must be NULL.
 */
char *UTIL_StrBuild(const char *szStart, ...)
{
    va_list     ap;
    size_t      iLen;
    size_t      iPos;
    const char *pSrc;
    char       *pDest;

    /* ~~~ Initialize... ~~~ */
    iLen = 0;
    pSrc = szStart;
    pDest = NULL;
    va_start(ap, szStart);

    /* ~~~ Reallocate and concatenate... ~~~ */
    do
    {
        iPos = iLen;
        iLen = iLen + strlen(pSrc);
        pDest = (char *) UTIL_Realloc(pDest, iLen + 1);

        if (pDest)
        {
            strcpy(pDest + iPos, pSrc);
        }
        else
        {
            iLen = 0;
        }
    } while ((pSrc = va_arg(ap, const char *)) != NULL);

    va_end(ap);

    return pDest;
}

/*!
 * \brief Function to initialize the random number generator.
 *
 * \return None.
 */
void UTIL_RandInit(void)
{
    srand(( unsigned int ) time( NULL ));
}

/*!
 * \brief Function to get a random number.
 *
 * \param iMin Minimum random number.
 * \param iMax Maximum random number.
 * \return A random number between a min and a max.
 */
int UTIL_Rand(int iMin, int iMax)
{
    return (( rand( ) % ( iMax - iMin + 1 )) + iMin );
}

/* ========================================================================= */
