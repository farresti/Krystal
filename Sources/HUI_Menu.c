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

static HUI_MenuStack HUI_stack;
static HUI_ID iNextID;
static TTF_Font *pFont;


static HUI_Menu *pMenuPause;
static HUI_Menu *pMenuStats;
static HUI_Menu *pMenuMap;
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
* \brief Function to get the link ID.
*
* \return ID for the link of a button.
*/
static HUI_ID HUI_Menu_GetNextID(void)
{
    return iNextID;
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
static void HUI_MenuSprites_Init(HUI_Menu *pMenu, Uint32 iNbSprites, ...)
{
    Uint32 i = 0;
    va_list list;
    va_start(list, iNbSprites);
    pMenu->arrSprite = UTIL_Malloc((iNbSprites + 1)*sizeof(HUI_Sprite));
    if (pMenu->arrSprite)
    {
        for (i = 0; i < iNbSprites; ++i)
        {
            pMenu->arrSprite[i].pSprite = SDL_Precache_Sprite(va_arg(list, char*));
            pMenu->arrSprite[i].sPos.x  = va_arg(list, Sint32);
            pMenu->arrSprite[i].sPos.y  = va_arg(list, Sint32);
        }
        pMenu->arrSprite[i].pSprite = NULL;
        pMenu->arrSprite[i].sPos.x = 0;
        pMenu->arrSprite[i].sPos.y = 0;
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
static void HUI_MenuText_Init(HUI_Menu *pMenu, Uint32 iNbText, ...)
{
    Uint32 i = 0;
    SDL_Point sPos;
    TTF_Font *pFontText = NULL;
    SDL_Color *pColor = NULL;
    va_list list;
    va_start(list, iNbText);
    pMenu->pArrText = UTIL_Malloc((iNbText + 1)*sizeof(HUI_Text*));
    if (pMenu->pArrText)
    {
        for (i = 0; i < iNbText; ++i)
        {
            pMenu->pArrText[i] = UTIL_Malloc(sizeof(HUI_Text));
            if (pMenu->pArrText[i])
            {
                pFontText = va_arg(list, TTF_Font*);
                pColor = va_arg(list, SDL_Color*);
                sPos.x = va_arg(list, Sint32);
                sPos.y = va_arg(list, Sint32);
                HUI_Text_Init(pMenu->pArrText[i],
                    pFontText,
                    pColor,
                    &sPos);
                HUI_Text_SetText(pMenu->pArrText[i], va_arg(list, char*), 0);
            }
        }
        pMenu->pArrText[i] = NULL;
    }
    va_end(list);
}

/*!
* \brief Function to init the array of text of a menu.
*
* \param pMenu    Pointer to menu.
* \return None.
*/
static void HUI_MenuText_Free(HUI_Menu *pMenu)
{
    Uint32 i = 0;
    if (pMenu->pArrText)
    {
        while (pMenu->pArrText[i])
        {
            HUI_Text_Free(pMenu->pArrText[i]);
            UTIL_Free(pMenu->pArrText[i]);
            ++i;
        }
        UTIL_Free(pMenu->pArrText);
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
static void HUI_MenuTextBox_Init(HUI_Menu *pMenu, Uint32 iNbTextbox, ...)
{
    Uint32 i = 0;
    TTF_Font  *pFontTextbox = NULL;
    SDL_Color *pColor       = NULL;
    SDL_Rect  *pRect        = NULL;
    Uint16     iLenght      = 0;
    char      *szText       = NULL;
    va_list list;
    va_start(list, iNbTextbox);
    pMenu->pArrTextBox = UTIL_Malloc((iNbTextbox + 1)*sizeof(HUI_Textbox*));
    if (pMenu->pArrTextBox)
    {
        for (i = 0; i < iNbTextbox; ++i)
        {
            pMenu->pArrTextBox[i] = UTIL_Malloc(sizeof(HUI_Textbox));
            if (pMenu->pArrTextBox[i])
            {
                pFontTextbox = va_arg(list, TTF_Font*);
                pColor       = va_arg(list, SDL_Color*);
                pRect        = va_arg(list, SDL_Rect*);
                iLenght      = va_arg(list, Uint16);
                szText       = va_arg(list, char*);
                HUI_Textbox_Init(pMenu->pArrTextBox[i],
                    pFontTextbox,
                    pColor,
                    pRect,
                    iLenght,
                    szText);
            }
        }
        pMenu->pArrTextBox[i] = NULL;
    }
    va_end(list);
}

/*!
* \brief Function to free the array of textbox of a menu.
*
* \param pMenu    Pointer to menu.
* \return None.
*/
static void HUI_MenuTextBox_Free(HUI_Menu *pMenu)
{
    Uint32 i = 0;
    if (pMenu->pArrTextBox)
    {
        while (pMenu->pArrTextBox[i])
        {
            HUI_Textbox_Free(pMenu->pArrTextBox[i]);
            UTIL_Free(pMenu->pArrTextBox[i]);
            ++i;
        }
        UTIL_Free(pMenu->pArrTextBox);
    }
}

/*!
* \brief Function to init the array of links of a menu.
*
* \param pMenu    Pointer to menu.
* \param iNbLinks Number of links to init.
* \remarks extra parameters format :
*     -common to both switch and button : 
*          HUI_Type          eType   Type of button 
*          Sint32            x       position along X
*          Sint32            y       position along Y
*     -switch only :
*          HUI_SwitchState   iState  initial state of the switch
*          SDL_bool          bTrans  flag to indicate if the background is transparent
*          SDL_Color         *pColor Pointer to the color of the back, NULL if none
*          pActionFct        Function to call when the switch is enabled
*          pActionFct        Function to call when the switch is disabled
*     -button only :
*          char*             szName  Name of the sprite to load for the button
*          HUI_ID            iIDLink ID of the menu to link
*          pActionFct        Function to call when the button is clicked
* \return None.
*/
static void HUI_MenuButton_Init(HUI_Menu *pMenu, Uint32 iNbLinks, ...)
{
    Uint32 i = 0;
    Sint32 x = 0;
    Sint32 y = 0;
    SDL_bool  bTrans;
    HUI_SwitchState  iState;
    SDL_Color *pColor;
    va_list list;
    va_start(list, iNbLinks);
    pMenu->pArrButtons = UTIL_Malloc((iNbLinks + 1)*sizeof(HUI_MenuButton*));
    if (pMenu->pArrButtons)
    {
        for (i = 0; i < iNbLinks; ++i)
        {
            pMenu->pArrButtons[i] = UTIL_Malloc(sizeof(HUI_MenuButton));
            if (pMenu->pArrButtons[i])
            {
                pMenu->pArrButtons[i]->eType = va_arg(list, HUI_Type);
                x = va_arg(list, Sint32);
                y = va_arg(list, Sint32);
                if (pMenu->pArrButtons[i]->eType == HUI_MENU_BUTTON)
                {
                    pMenu->pArrButtons[i]->pSprite    = SDL_Precache_Sprite(va_arg(list, char*));
                    pMenu->pArrButtons[i]->iIDLink    = va_arg(list, HUI_ID);
                    pMenu->pArrButtons[i]->pLink      = va_arg(list, pActionFct);
                    pMenu->pArrButtons[i]->pActionEn  = NULL;
                    pMenu->pArrButtons[i]->pActionDis = NULL;
                    HUI_Button_Init(&pMenu->pArrButtons[i]->sButton, pMenu->pArrButtons[i]->pSprite,
                        x, y);
                    pMenu->pArrButtons[i]->iLastButtonState = HUI_Button_GetState(&pMenu->pArrButtons[i]->sButton);
                }
                else if (pMenu->pArrButtons[i]->eType == HUI_MENU_SWITCH)
                {
                    iState                            = va_arg(list, HUI_SwitchState);
                    bTrans                            = va_arg(list, SDL_bool);
                    pColor                            = va_arg(list, SDL_Color*);
                    pMenu->pArrButtons[i]->pActionEn  = va_arg(list, pActionFct);
                    pMenu->pArrButtons[i]->pActionDis = va_arg(list, pActionFct);

                    pMenu->pArrButtons[i]->pSprite    = NULL;
                    pMenu->pArrButtons[i]->iIDLink    = 0;
                    pMenu->pArrButtons[i]->pLink      = NULL;
                    HUI_Switch_Init(&pMenu->pArrButtons[i]->sSwitch, x, y, iState, bTrans, pColor);
                    pMenu->pArrButtons[i]->iLastSwitchState = HUI_Switch_GetState(&pMenu->pArrButtons[i]->sSwitch);
                }
            }
        }
        pMenu->pArrButtons[i] = NULL;
    }
    va_end(list);
}

/*!
* \brief Function to free the array of links of a menu.
*
* \param pMenu    Pointer to menu.
* \return None.
*/
static void HUI_MenuButton_Free(HUI_Menu *pMenu)
{
    Uint32 i = 0;
    if (pMenu->pArrButtons)
    {
        while (pMenu->pArrButtons[i])
        {
            UTIL_Free(pMenu->pArrButtons[i]);
            ++i;
        }
        UTIL_Free(pMenu->pArrButtons);
    }
}

/*!
* \brief Function to update a menu button.
*
* \param pButton    Pointer to the menu button.
* \param pInput     Pointer to the input structure.
* \return None.
*/
static void HUI_MenuButton_Update(HUI_MenuButton *pButton, HUI_Input *pInput)
{
    HUI_SwitchState iState;
    switch (pButton->eType)
    {
    case HUI_MENU_BUTTON:
        pButton->iLastButtonState = HUI_Button_GetState(&pButton->sButton);
        HUI_Button_Update(&pButton->sButton, pInput);

        if (HUI_Button_GetState(&pButton->sButton) != pButton->iLastButtonState &&
            pButton->iLastButtonState == HUI_BUTTON_ACTIVE)
        {
            if (pButton->pLink)
            {
                iNextID = pButton->iIDLink;
                (*pButton->pLink)();
            }
            pButton->sButton.iState = HUI_BUTTON_INACTIVE;
        }
        break;
    case HUI_MENU_SWITCH :
        HUI_Switch_Update(&pButton->sSwitch, pInput);
        iState = HUI_Switch_GetState(&pButton->sSwitch);

        if (iState != pButton->iLastSwitchState)
        {
            if (iState == HUI_SWITCH_ENABLED)
            {
                if (pButton->pActionEn)
                {
                    (*pButton->pActionEn)();
                }
                pButton->iLastSwitchState = iState;
            } 
            else if (iState == HUI_SWITCH_DISABLED)
            { 
                if (pButton->pActionDis)
                {
                    (*pButton->pActionDis)();
                }
                pButton->iLastSwitchState = iState;
            }
        }
        break;
    }
}

/*!
* \brief Function to draw a menu button.
*
* \param pButton    Pointer to the menu button.
* \return None.
*/
static void HUI_MenuButton_Draw(HUI_MenuButton *pButton)
{
    switch (pButton->eType)
    {
    case HUI_MENU_BUTTON:
        HUI_Button_Draw(&pButton->sButton);
        break;
    case HUI_MENU_SWITCH:
        HUI_Switch_Draw(&pButton->sSwitch);
        break;
    }
}

/* ========================================================================= */
/*!
* \brief Function to go into a sub menu.
*
* \param iIDLink    ID of the menu linked by the button.
* \return None.
*/
void HUI_Menu_GoForward(void)
{
    HUI_Menu_Load(HUI_Menu_GetNextID());
}

/*!
* \brief Function to quit a sub menu.
*
* \param iIDLink    ID of the menu linked by the button.
* \return None.
*/
void HUI_Menu_GoBack(void)
{
    HUI_Menu *pMenu  = HUI_Menu_GetMenu(HUI_Menu_GetID());
    if (pMenu)
    {
        pMenu->bQuit = SDL_TRUE;
    }
   
}

/* ========================================================================= */

/*!
* \brief Function to init the menu stack.
*
* \return None.
*/
static void HUI_Menu_InitStack(void)
{
    HUI_stack.iIndex   = 0;
    HUI_stack.iSize    = 1;
    HUI_stack.pID      = UTIL_Malloc(sizeof(HUI_ID));
    HUI_stack.bIsEmpty = SDL_TRUE;
    if (HUI_stack.pID == NULL)
    {
        COM_Log_Print(COM_LOG_CRITICAL, ">> Not enough memory for the menu stack holder");
    }
}

/*!
* \brief Function to add an ID to the menu stack.
*
* \param iID    ID of the menu to add.
* \return None.
*/
static void HUI_Menu_AddToStack(HUI_ID iID)
{
    if (HUI_stack.iIndex >= HUI_stack.iSize)
    {
        HUI_stack.iSize += 1;
        HUI_stack.pID = UTIL_Realloc(HUI_stack.pID, HUI_stack.iSize * sizeof(HUI_ID));
    }
    HUI_stack.pID[HUI_stack.iIndex] = iID;
    HUI_stack.iIndex += 1;
    HUI_stack.bIsEmpty = SDL_FALSE;
}

/*!
* \brief Function to remove last ID of the menu stack.
*
* \return None.
*/
static void HUI_Menu_RemoveFromStack(void)
{
    if (HUI_stack.iIndex)
    {
        HUI_stack.iIndex -= 1;
        HUI_stack.pID[HUI_stack.iIndex] = HUI_MENU_ERROR;
    }
    else
    {
        HUI_stack.bIsEmpty = SDL_TRUE;
    }
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
    SDL_Rect  rect  = { 100, 600, 400, 40 };
    pMenuPause      = UTIL_Malloc(sizeof(HUI_Menu));
    pMenuPause->iID = HUI_MENU_PAUSE;

    pMenuPause->pArrButtons = NULL;
    pMenuPause->arrSprite   = NULL;
    pMenuPause->pArrText    = NULL;
    pMenuPause->pArrTextBox = NULL;

    HUI_MenuSprites_Init(pMenuPause, 1, 
        "menuPause", 0, 0);
    HUI_MenuButton_Init(pMenuPause, 2,
        HUI_MENU_BUTTON, 150, 200, "button", HUI_MENU_STATS, HUI_Menu_GoForward,
        HUI_MENU_BUTTON, 400, 200, "button", HUI_MENU_ERROR, HUI_Menu_GoBack);
    HUI_MenuText_Init(pMenuPause, 2,
        pFont, &color, 300, 350, "Ceci est un menu",
        pFont, &color, 200, 10,  "Menu Pause");
    HUI_MenuTextBox_Init(pMenuPause, 1,
        pFont, &color, &rect, 18, "Enter Text");

    pMenuPause->bQuit     = SDL_FALSE;
    pMenuPause->bIsOpaque = SDL_TRUE;
}

/*!
* \brief Function to init the stats menu.
*
* \return None.
*/
static void HUI_Menu_InitStats(void)
{
    SDL_Color color = { 255, 120, 0, 255 };
    pMenuStats      = UTIL_Malloc(sizeof(HUI_Menu));
    pMenuStats->iID = HUI_MENU_STATS;

    pMenuStats->pArrButtons = NULL;
    pMenuStats->arrSprite = NULL;
    pMenuStats->pArrText = NULL;
    pMenuStats->pArrTextBox = NULL;

    HUI_MenuSprites_Init(pMenuStats, 2, 
        "menuStats", 0, 0,
        "steam", 70, 150);
    HUI_MenuButton_Init(pMenuStats, 2,
        HUI_MENU_BUTTON, 150, 200, "button",  HUI_MENU_PAUSE, HUI_Menu_GoBack,
        HUI_MENU_BUTTON, 700, 200, "button2", HUI_MENU_MAP, HUI_Menu_GoForward);
    HUI_MenuText_Init(pMenuStats, 6,
        pFont, &color, 200, 10, "Menu Stats",
        pFont, &color, 200, 10, "",
        pFont, &color, 200, 10, "",
        pFont, &color, 200, 10, "",
        pFont, &color, 200, 10, "",
        pFont, &color, 200, 10, "");

    pMenuStats->bQuit     = SDL_FALSE;
    pMenuStats->bIsOpaque = SDL_TRUE;
}
    
/*!
* \brief Function to init the map menu.
*
* \return None.
*/
static void HUI_Menu_InitMap(void)
{
    SDL_Color color = { 255, 120, 0, 255 };
    pMenuMap        = UTIL_Malloc(sizeof(HUI_Menu));
    pMenuMap->iID   = HUI_MENU_MAP;

    pMenuMap->pArrButtons  = NULL;
    pMenuMap->arrSprite    = NULL;
    pMenuMap->pArrText     = NULL;
    pMenuMap->pArrTextBox  = NULL;

    HUI_MenuSprites_Init(pMenuMap, 1,
        "steam", 70, 150);
    HUI_MenuButton_Init(pMenuMap, 2,
        HUI_MENU_BUTTON, 300, 200, "button", HUI_MENU_STATS, HUI_Menu_GoBack,
        HUI_MENU_SWITCH, 150, 400, HUI_SWITCH_DISABLED, SDL_TRUE, NULL, NULL, NULL);
    HUI_MenuText_Init(pMenuMap, 1,
        pFont, &color, 200, 10, "Menu Map");

    pMenuMap->bQuit     = SDL_FALSE;
    pMenuMap->bIsOpaque = SDL_FALSE;
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
* \brief Function to get the last ID of the menu stack.
*
* \return ID of the menu, 404 if the stack is empty.
*/
HUI_ID HUI_Menu_GetID(void)
{
    if (!HUI_stack.bIsEmpty)
    {
        return HUI_stack.pID[HUI_stack.iIndex - 1];
    }
    return HUI_MENU_ERROR;
}


/*!
* \brief Function to know if the menu stack is empty.
*
* \return SDL_TRUE if empty, SDL_FALSE else.
*/
SDL_bool HUI_Menu_IsStackEmpty(void)
{
    return HUI_stack.bIsEmpty;
}

/*!
* \brief Function to load and update a menu.
*
* \param iID    ID of the menu to load.
* \param pInput Pointer to the input structure.
* \return None.
*/
void HUI_Menu_Load(HUI_ID iID)
{
    HUI_Menu *pMenu = HUI_Menu_GetMenu(iID);
    HUI_Menu_AddToStack(iID);
    if (pMenu)
    {
        pMenu->bQuit = SDL_FALSE;
    }
}

/*!
* \brief Function to update a menu.
*
* \param pID    Pointer to the current ID menu.
* \param pInput Pointer to the input structure.
* \return None.
*/
void HUI_Menu_Update(HUI_Input *pInput)
{
    HUI_Menu *pMenu = NULL;
    Uint32 i = 0;
    pMenu = HUI_Menu_GetMenu(HUI_Menu_GetID());
    if (pMenu)
    {
        if (pMenu->pArrTextBox)
        {
            while (pMenu->pArrTextBox[i])
            {
                HUI_Textbox_Update(pMenu->pArrTextBox[i], pInput);
                ++i;
            }
            i = 0;
        }
        if (pMenu->pArrButtons)
        {
            while (pMenu->pArrButtons[i])
            {
                HUI_MenuButton_Update(pMenu->pArrButtons[i], pInput);
                ++i;
            }
            i = 0;
        }
        HUI_Menu_Quit(pInput);
    }
}

/*!
* \brief Function to draw a menu.
*
* \param iID ID of the menu to draw.
* \return None.
*/
void HUI_Menu_Draw(void)
{
    HUI_Menu *pMenu = NULL;
    Uint32 i = 0;
    pMenu = HUI_Menu_GetMenu(HUI_Menu_GetID());
    if (pMenu)
    {
        if (!pMenu->bQuit)
        {
            if (pMenu->bIsOpaque)
            {
                SDL_Render_Clear();
            }
            if (pMenu->arrSprite)
            {
                while (pMenu->arrSprite[i].pSprite)
                {
                    SDL_Sprite_Draw(pMenu->arrSprite[i].pSprite, &pMenu->arrSprite[i].sPos, 0);
                    ++i;
                }
            }
            i = 0;
            if (pMenu->pArrText)
            {
                while (pMenu->pArrText[i])
                {
                    HUI_Text_Draw(pMenu->pArrText[i]);
                    ++i;
                }
            }
            i = 0;
            if (pMenu->pArrTextBox)
            {
                while (pMenu->pArrTextBox[i])
                {
                    HUI_Textbox_Draw(pMenu->pArrTextBox[i]);
                    ++i;
                }
                i = 0;
            }
            if (pMenu->pArrButtons)
            {
                while (pMenu->pArrButtons[i])
                {
                    HUI_MenuButton_Draw(pMenu->pArrButtons[i]);
                    ++i;
                }
                i = 0;
            }
        }
    }
}

/*!
* \brief Function to know if we have to quit the menu.
*
* \param iID    ID of the menu.
* \param pInput Pointer to the input structure.
* \return True if succes, false else.
*/
void HUI_Menu_Quit(HUI_Input *pInput)
{
    HUI_Menu *pMenu = NULL;
    if (HUI_Input_IsKeyPressed(pInput, SDLK_ESCAPE) ||
        pInput->bQuit)
    {
        HUI_Menu_EmptyStack();
        HUI_Input_ResetKey(pInput, SDLK_ESCAPE);
    }
    pMenu = HUI_Menu_GetMenu(HUI_Menu_GetID());
    if (pMenu)
    {
        if (pMenu->bQuit)
        {
            HUI_Menu_RemoveFromStack();
        }
    }
}

/*!
* \brief Function to empty the stack and quit all menus.
*
* \return None.
*/
void HUI_Menu_EmptyStack(void)
{
    Uint32    i = 0;
    Uint32    iSize = HUI_stack.iSize;
    HUI_Menu *pMenu = NULL;
    for (i = 0; i < iSize; ++i)
    {
        pMenu = HUI_Menu_GetMenu(HUI_stack.pID[i]);
        if (pMenu)
        {
            pMenu->bQuit = SDL_TRUE;
        }        
        HUI_Menu_RemoveFromStack();
    }
    HUI_stack.bIsEmpty = SDL_TRUE;
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
            HUI_MenuText_Free(pMenu);
            HUI_MenuTextBox_Free(pMenu);
            HUI_MenuButton_Free(pMenu);
            UTIL_Free(pMenu->arrSprite);
            UTIL_Free(pMenu);
        }
    }
    UTIL_Free(HUI_stack.pID);
    TTF_CloseFont(pFont);
}

/* ========================================================================= */