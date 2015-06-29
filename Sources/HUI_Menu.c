/* ========================================================================= */
/*!
* \file    HUI_Menu.c
* \brief   File to handle the menu.
* \author  Nyuu / Orlyn / Red
* \version 1.0
* \date    28 June 2015
*/
/* ========================================================================= */
/* Author  | Date     | Comments                                             */
/* --------+----------+----------------------------------------------------- */
/* Orlyn   | 28/06/15 | Creation.                                            */
/* ========================================================================= */

#include "HUI_Menu.h"

typedef struct
{
    SDL_bool bIsEmpty;
    HUI_ID   *pID;
    Uint32    iSize;
    Uint32    iIndex;
}HUI_MenuStack;

static HUI_MenuStack HUI_Stack;
static HUI_Menu *pMenuPause;
static HUI_Menu *pMenuStats;
static HUI_Menu *pMenuMap;
static TTF_Font *pFont;
/* ========================================================================= */

/*!
* \brief Function to get a menu.
*
* \param iID ID of the menu to draw.
* \return Pointer to the corresponding menu, NULL if error.
*/
static HUI_Menu *HUI_Menu_GetMenu(HUI_ID iID)
{
    switch (iID)
    {
    case HUI_MENU_PAUSE:
        return pMenuPause;
    case HUI_MENU_STATS:
        return pMenuStats;
    case HUI_MENU_MAP:
        return pMenuMap;
    }
    return NULL;
}

/*!
* \brief Function to init the array of sprite of a menu.
*
* \param pMenu    Pointer to menu.
* \param iNbLinks Number of links to init.
* \remarks extra parameters format per sprite:
*          char*, Sint32, Sint32
* \return None.
*/
static void HUI_Menu_InitSprites(HUI_Menu *pMenu, Uint32 iNbSprites, ...)
{
    Uint32 i = 0;
    va_list list;
    va_start(list, iNbSprites);
    pMenu->ppSprite = UTIL_Malloc((iNbSprites + 1)*sizeof(HUI_Sprite));
    if (pMenu->ppSprite)
    {
        for (i = 0; i < iNbSprites; ++i)
        {
            pMenu->ppSprite[i].pSprite = SDL_Precache_Sprite(va_arg(list, char*));
            pMenu->ppSprite[i].sPos.x  = va_arg(list, Sint32);
            pMenu->ppSprite[i].sPos.y  = va_arg(list, Sint32);
        }
        pMenu->ppSprite[i].pSprite = NULL;
        pMenu->ppSprite[i].sPos.x = 0;
        pMenu->ppSprite[i].sPos.y = 0;
    }
    va_end(list);
}

/*!
* \brief Function to init the array of text of a menu.
*
* \param pMenu    Pointer to menu.
* \param iNbLinks Number of links to init.
* \remarks extra parameters format per text:
*          TTF_Font*,SDL_Color*,Sint32, Sint32, char*
* \return None.
*/
static void HUI_Menu_InitText(HUI_Menu *pMenu, Uint32 iNbText, ...)
{
    Uint32 i = 0;
    SDL_Point sPos;
    TTF_Font *pFontText = NULL;
    SDL_Color *pColor = NULL;
    va_list list;
    va_start(list, iNbText);
    pMenu->ppText = UTIL_Malloc((iNbText + 1)*sizeof(HUI_Text*));
    if (pMenu->ppText)
    {
        for (i = 0; i < iNbText; ++i)
        {
            pMenu->ppText[i] = UTIL_Malloc(sizeof(HUI_Text));
            if (pMenu->ppText[i])
            {
                pFontText = va_arg(list, TTF_Font*);
                pColor = va_arg(list, SDL_Color*);
                sPos.x = va_arg(list, Sint32);
                sPos.y = va_arg(list, Sint32);
                HUI_Text_Init(pMenu->ppText[i],
                    pFontText,
                    pColor,
                    &sPos);
                HUI_Text_SetText(pMenu->ppText[i], va_arg(list, char*), 0);
            }
        }
        pMenu->ppText[i] = NULL;
    }
    va_end(list);
}

/*!
* \brief Function to init the array of text of a menu.
*
* \param pMenu    Pointer to menu.
* \return None.
*/
static void HUI_Menu_FreeText(HUI_Menu *pMenu)
{
    Uint32 i = 0;
    if (pMenu->ppText)
    {
        while (pMenu->ppText[i])
        {
            HUI_Text_Free(pMenu->ppText[i]);
            UTIL_Free(pMenu->ppText[i]);
            ++i;
        }
        UTIL_Free(pMenu->ppText[i]);
        UTIL_Free(pMenu->ppText);
    }
}

/*!
* \brief Function to init the array of textbox of a menu.
*
* \param pMenu      Pointer to menu.
* \param iNbTextbox Number of links to init.
* \remarks extra parameters format per text box:
*          TTF_Font*,SDL_Color*, SDL_Rect *,Uint16,char*
* \return None.
*/
static void HUI_Menu_InitTextbox(HUI_Menu *pMenu, Uint32 iNbTextbox, ...)
{
    Uint32 i = 0;
    TTF_Font  *pFontTextbox = NULL;
    SDL_Color *pColor       = NULL;
    SDL_Rect  *pRect        = NULL;
    Uint16     iLenght      = 0;
    char      *szText       = NULL;
    va_list list;
    va_start(list, iNbTextbox);
    pMenu->ppTextBox = UTIL_Malloc((iNbTextbox + 1)*sizeof(HUI_Textbox*));
    if (pMenu->ppTextBox)
    {
        for (i = 0; i < iNbTextbox; ++i)
        {
            pMenu->ppTextBox[i] = UTIL_Malloc(sizeof(HUI_Textbox));
            if (pMenu->ppTextBox[i])
            {
                pFontTextbox = va_arg(list, TTF_Font*);
                pColor       = va_arg(list, SDL_Color*);
                pRect        = va_arg(list, SDL_Rect*);
                iLenght      = va_arg(list, Uint16);
                szText       = va_arg(list, char*);
                HUI_Textbox_Init(pMenu->ppTextBox[i],
                    pFontTextbox,
                    pColor,
                    pRect,
                    iLenght,
                    szText);
            }
        }
        pMenu->ppTextBox[i] = NULL;
    }
    va_end(list);
}

/*!
* \brief Function to free the array of textbox of a menu.
*
* \param pMenu    Pointer to menu.
* \return None.
*/
static void HUI_Menu_FreeTextbox(HUI_Menu *pMenu)
{
    Uint32 i = 0;
    if (pMenu->ppTextBox)
    {
        while (pMenu->ppTextBox[i])
        {
            HUI_Textbox_Free(pMenu->ppTextBox[i]);
            UTIL_Free(pMenu->ppTextBox[i]);
            ++i;
        }
        UTIL_Free(pMenu->ppTextBox[i]);
        UTIL_Free(pMenu->ppTextBox);
    }
}

/*!
* \brief Function to init the array of links of a menu.
*
* \param pMenu    Pointer to menu.
* \param iNbLinks Number of links to init.
* \remarks extra parameters format :
*          HUI_ID,char*, Sint32, Sint32,pLinkFct
* \return None.
*/
static void HUI_Menu_InitLinks(HUI_Menu *pMenu, Uint32 iNbLinks, ...)
{
    Uint32 i = 0;
    Sint32 x = 0;
    Sint32 y = 0;
    va_list list;
    va_start(list, iNbLinks);
    pMenu->ppLink = UTIL_Malloc((iNbLinks + 1)*sizeof(HUI_Link*));
    if (pMenu->ppLink)
    {
        for (i = 0; i < iNbLinks; ++i)
        {
            pMenu->ppLink[i] = UTIL_Malloc(sizeof(HUI_Link));
            if (pMenu->ppLink[i])
            {
                pMenu->ppLink[i]->iIDLink = va_arg(list, HUI_ID);
                pMenu->ppLink[i]->pSprite = SDL_Precache_Sprite(va_arg(list, char*));
                x = va_arg(list, Sint32);
                y = va_arg(list, Sint32);
                HUI_Button_Init(&pMenu->ppLink[i]->sButton, pMenu->ppLink[i]->pSprite, 
                    x, y);
                pMenu->ppLink[i]->pLink = va_arg(list, pLinkFct);
            }
        }
        pMenu->ppLink[i] = NULL;
    }
    va_end(list);
}

/*!
* \brief Function to free the array of links of a menu.
*
* \param pMenu    Pointer to menu.
* \return None.
*/
static void HUI_Menu_FreeLinks(HUI_Menu *pMenu)
{
    Uint32 i = 0;
    if (pMenu->ppLink)
    {
        while (pMenu->ppLink[i])
        {
            UTIL_Free(pMenu->ppLink[i]);
            ++i;
        }
        UTIL_Free(pMenu->ppLink[i]);
        UTIL_Free(pMenu->ppLink);
    }
}

/*!
* \brief Function to update a menu.
*
* \param pID    Pointer to the current ID menu.
* \param pInput Pointer to the input structure.
* \return None.
*/
static void HUI_Menu_Update(HUI_ID iID, HUI_Input *pInput)
{
    HUI_Menu *pMenu = NULL;
    Uint32 i = 0;
    pMenu = HUI_Menu_GetMenu(iID);
    if (pMenu->ppTextBox)
    {
        while (pMenu->ppTextBox[i])
        {
            HUI_Textbox_Update(pMenu->ppTextBox[i], pInput);
            ++i;
        }
        i = 0;
    }
    if (pMenu->ppLink)
    {
        while (pMenu->ppLink[i])
        {
            HUI_Button_Update(&pMenu->ppLink[i]->sButton, pInput);
            if (HUI_Button_GetState(&pMenu->ppLink[i]->sButton) == HUI_BUTTON_ACTIVE)
            {
                (*pMenu->ppLink[i]->pLink)(pMenu, pMenu->ppLink[i]->iIDLink, pInput);
                pMenu->ppLink[i]->sButton.iState = HUI_BUTTON_INACTIVE;
            }
            ++i;
        }
        i = 0;
    }
}

/*!
* \brief Function to know if we have to quit the menu.
*
* \param iID    ID of the menu.
* \param pInput Pointer to the input structure.
* \return True if succes, false else.
*/
static SDL_bool HUI_Menu_Quit(HUI_ID iID, HUI_Input *pInput)
{
    HUI_Menu *pMenu = NULL;
    if (HUI_Input_IsKeyPressed(pInput, SDLK_ESCAPE) || 
        pInput->bQuit)
    {
        HUI_Menu_EmptyStack();
        HUI_Input_ResetKey(pInput, SDLK_ESCAPE);
        return SDL_TRUE;
    }
    pMenu = HUI_Menu_GetMenu(iID);
    if (pMenu)
    {
        if (pMenu->bQuit)
        {
            return SDL_TRUE;
        }
    }
    return SDL_FALSE;
}

/*!
* \brief Function to draw a menu.
*
* \param iID ID of the menu to draw.
* \return None.
*/
static void HUI_Menu_Draw(HUI_ID iID)
{
    HUI_Menu *pMenu = NULL;
    Uint32 i = 0;
    pMenu = HUI_Menu_GetMenu(iID);
    if (pMenu)
    {
        if (pMenu->ppSprite)
        {
            while (pMenu->ppSprite[i].pSprite)
            {
                SDL_Sprite_Draw(pMenu->ppSprite[i].pSprite, &pMenu->ppSprite[i].sPos, 0);
                ++i;
            }
        }
        i = 0;
        if (pMenu->ppText)
        {
            while (pMenu->ppText[i])
            {
                HUI_Text_Draw(pMenu->ppText[i]);
                ++i;
            }
        }
        i = 0;
        if (pMenu->ppTextBox)
        {
            while (pMenu->ppTextBox[i])
            {
                HUI_Textbox_Draw(pMenu->ppTextBox[i]);
                ++i;
            }
            i = 0;
        }
        if (pMenu->ppLink)
        {
            while (pMenu->ppLink[i])
            {
                HUI_Button_Draw(&pMenu->ppLink[i]->sButton);
                ++i;
            }
            i = 0;
        }
    }
}

/*!
* \brief Function to go into a sub menu.
*
* \param pMenu      Pointer to menu.
* \param iIDLink    ID of the menu linked by the button.
* \param pInput     Pointer to the input structure.
* \return None.
*/
void HUI_Menu_GoForward(HUI_Menu *pMenu, HUI_ID iIDLink, HUI_Input *pInput)
{
    (void)pMenu;
    HUI_Menu_Load(iIDLink, pInput);
}

/*!
* \brief Function to quit a sub menu.
*
* \param pMenu      Pointer to menu.
* \param iIDLink    ID of the menu linked by the button.
* \param pInput     Pointer to the input structure.
* \return None.
*/
void HUI_Menu_GoBack(HUI_Menu *pMenu, HUI_ID iIDLink, HUI_Input *pInput)
{
    (void)iIDLink;
    (void)pInput;
    pMenu->bQuit = SDL_TRUE;
}

/* ========================================================================= */
/*!
* \brief Function to init the pause menu.
*
* \return None.
*/
static void HUI_Menu_InitPause(void)
{
    SDL_Color color = { 0, 0, 0, 255 };
    SDL_Rect  rect = { 100, 600, 400, 40 };
    pMenuPause = UTIL_Malloc(sizeof(HUI_Menu));
    pMenuPause->iID = HUI_MENU_PAUSE;

    pMenuPause->ppLink    = NULL;
    pMenuPause->ppSprite  = NULL;
    pMenuPause->ppText    = NULL;
    pMenuPause->ppTextBox = NULL;

    HUI_Menu_InitSprites(pMenuPause, 1, 
        "menuPause", 0, 0);
    HUI_Menu_InitLinks(pMenuPause, 1,
        HUI_MENU_STATS, "button", 150, 200, HUI_Menu_GoForward);
    HUI_Menu_InitText(pMenuPause, 2,
        pFont, &color, 300, 500, "Ceci est un menu",
        pFont, &color, 200, 10,  "Menu Pause");
    HUI_Menu_InitTextbox(pMenuPause, 1,
        pFont, &color, &rect, 18, "Enter Text");

    pMenuPause->bQuit = SDL_FALSE;
}

/*!
* \brief Function to init the stats menu.
*
* \return None.
*/
static void HUI_Menu_InitStats(void)
{
    SDL_Color color = { 255, 120, 0, 255 };
    pMenuStats = UTIL_Malloc(sizeof(HUI_Menu));
    pMenuStats->iID = HUI_MENU_STATS;

    pMenuStats->ppLink = NULL;
    pMenuStats->ppSprite = NULL;
    pMenuStats->ppText = NULL;
    pMenuStats->ppTextBox = NULL;

    HUI_Menu_InitSprites(pMenuStats, 2, 
        "menuStats", 0, 0,
        "steam", 70, 150);
    HUI_Menu_InitLinks(pMenuStats, 2,
        HUI_MENU_PAUSE, "button", 300, 50, HUI_Menu_GoBack,
        HUI_MENU_MAP, "Button2", 700, 200, HUI_Menu_GoForward);
    HUI_Menu_InitText(pMenuStats, 6,
        pFont, &color, 200, 10, "Menu Stats",
        pFont, &color, 200, 10, "",
        pFont, &color, 200, 10, "",
        pFont, &color, 200, 10, "",
        pFont, &color, 200, 10, "",
        pFont, &color, 200, 10, "");

    pMenuStats->bQuit = SDL_FALSE;
}
    
/*!
* \brief Function to init the map menu.
*
* \return None.
*/
static void HUI_Menu_InitMap(void)
{
    SDL_Color color = { 255, 120, 0, 255 };
    pMenuMap = UTIL_Malloc(sizeof(HUI_Menu));
    pMenuMap->iID = HUI_MENU_MAP;

    pMenuMap->ppLink    = NULL;
    pMenuMap->ppSprite  = NULL;
    pMenuMap->ppText    = NULL;
    pMenuMap->ppTextBox = NULL;

    HUI_Menu_InitSprites(pMenuMap, 1,
        "steam", 70, 150);
    HUI_Menu_InitLinks(pMenuMap, 1,
        HUI_MENU_STATS, "button", 300, 200, HUI_Menu_GoBack);
    HUI_Menu_InitText(pMenuMap, 1,
        pFont, &color, 200, 10, "Menu Map");

    pMenuMap->bQuit = SDL_FALSE;
}
/* ========================================================================= */

/*!
* \brief Function to init the menu stack.
*
* \return None.
*/
static void HUI_Menu_InitStack(void)
{
    HUI_Stack.iIndex = 0;
    HUI_Stack.iSize = 1;
    HUI_Stack.pID = UTIL_Malloc(sizeof(HUI_ID));
    HUI_Stack.bIsEmpty = SDL_TRUE;
}

/*!
* \brief Function to add an ID to the menu stack.
*
* \param iID    ID of the menu to add.
* \return None.
*/
static void HUI_Menu_AddToStack(HUI_ID iID)
{
    if (HUI_Stack.iIndex >= HUI_Stack.iSize)
    {
        HUI_Stack.iSize += 1;
        HUI_Stack.pID = UTIL_Realloc(HUI_Stack.pID, HUI_Stack.iSize * sizeof(HUI_ID));
    }
    HUI_Stack.pID[HUI_Stack.iIndex] = iID;
    HUI_Stack.iIndex += 1;
    HUI_Stack.bIsEmpty = SDL_FALSE;
}

/*!
* \brief Function to add an ID to the menu stack.
*
* \param iID    ID of the menu to add.
* \return None.
*/
static void HUI_Menu_RemoveFromStack(void)
{
    if (HUI_Stack.iIndex)
    {
        HUI_Stack.iIndex -= 1;
    }
    else
    {
        HUI_Stack.bIsEmpty = SDL_TRUE;
    }
}

/*!
* \brief Function to know if the menu stack is empty.
*
* \return true if empty, false else.
*/
static SDL_bool HUI_Menu_IsStackEmpty(void)
{
    return HUI_Stack.bIsEmpty;
}

/*!
* \brief Function to empty the stack and quit all menus.
*
* \return None.
*/
void HUI_Menu_EmptyStack(void)
{
    Uint32 i = 0;
    Uint32 iSize = HUI_Stack.iSize;
    HUI_Menu *pMenu = NULL;
    for (i = 0; i < iSize; ++i)
    {
        pMenu = HUI_Menu_GetMenu(HUI_Stack.pID[i]);
        pMenu->bQuit = SDL_TRUE;
        HUI_Menu_RemoveFromStack();
    }
    HUI_Stack.bIsEmpty = SDL_TRUE;
}

/* ========================================================================= */

/*!
* \brief Function to init all the menus.
*
* \return None.
*/
void HUI_Menu_Init(void)
{
    HUI_Menu_InitStack();
    pFont = TTF_OpenFont("fonts/codenewroman.ttf", 30);
    if (pFont)
    {
        HUI_Menu_InitPause();
        HUI_Menu_InitStats();
        HUI_Menu_InitMap();
    }
}

/*!
* \brief Function to load and update a menu.
*
* \param iID    ID of the menu to load.
* \param pInput Pointer to the input structure.
* \return None.
*/
void HUI_Menu_Load(HUI_ID iID, HUI_Input *pInput)
{
    SDL_bool bMenuQuit = SDL_FALSE;
    HUI_Menu *pMenu = HUI_Menu_GetMenu(iID);
    HUI_Menu_AddToStack(iID);
    if (pMenu)
    {
        pMenu->bQuit = SDL_FALSE;
    }
    do
    {
        SDL_Render_Clear();
        HUI_Input_Update(pInput);
        HUI_Menu_Update(iID, pInput);
        if (!pMenu->bQuit)
        {
            HUI_Menu_Draw(iID);
        }
        bMenuQuit = HUI_Menu_Quit(iID, pInput);
        SDL_Render_Present();
    } while (!bMenuQuit);
    if (!HUI_Menu_IsStackEmpty())
    {
        HUI_Menu_RemoveFromStack();
    }
}

/*!
* \brief Function to free all the menus.
*
* \return None.
*/
void HUI_Menu_Free(void)
{
    HUI_ID i;
    HUI_Menu *pMenu = NULL;
    for (i = 0; i < __NBMENU__; ++i)
    {
        pMenu = HUI_Menu_GetMenu(i);
        if (pMenu)
        {
            HUI_Menu_FreeText(pMenu);
            HUI_Menu_FreeTextbox(pMenu);
            HUI_Menu_FreeLinks(pMenu);
            UTIL_Free(pMenu->ppSprite);
            UTIL_Free(pMenu);
        }
    }
    UTIL_Free(HUI_Stack.pID);
    TTF_CloseFont(pFont);
}



/* ========================================================================= */