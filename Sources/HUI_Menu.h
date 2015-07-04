/* ========================================================================= */
/*!
* \file    HUI_Menu.h
* \brief   File to interface with the menu.
* \author  Nyuu / Orlyn / Red
* \version 1.0
* \date    27 June 2015
*/
/* ========================================================================= */
/* Author  | Date     | Comments                                             */
/* --------+----------+----------------------------------------------------- */
/* Orlyn   | 28/06/15 | Creation.                                            */
/* ========================================================================= */

#ifndef __HUI_MENU_H__
#define __HUI_MENU_H__

    #include "HUI_Button.h"
    #include "HUI_Textbox.h"

#define __NBMENU__ 3

    /*!
    * \enum HUI_ID
    * \brief  List of all the menus.
    */
    typedef Uint32 HUI_ID;
    enum
    {
        HUI_MENU_PAUSE = 0,
        HUI_MENU_MAP   = 1,
        HUI_MENU_STATS = 2
    };

    typedef void(*pLinkFct)(void*, HUI_ID, HUI_Input*); /*!< Pointer to the function to call on action of the button. */

    /*!
    * \struct HUI_Link
    * \brief  Structure to handle the action of button in a menu.
    */
    typedef struct
    {
        SDL_Sprite *pSprite;  /*!< Sprite of the button. */
        HUI_Button  sButton;  /*!< Button associated to the link. */
        HUI_ID      iIDLink;  /*!< ID of the menu linked, if necessary. */
        pLinkFct    pLink;    /*!< Pointer to the function to call on action of the button. */
    }HUI_Link;

    /*!
    * \struct HUI_Sprite
    * \brief  Structure to handle a sprite with position.
    */
    typedef struct
    {
        SDL_Sprite *pSprite;
        SDL_Point   sPos;
    }HUI_Sprite;

    /*!
    * \struct HUI_Menu
    * \brief  Structure to handle the menus.
    */
    typedef struct
    {
        HUI_Text    **ppText;    /*!< Array of text inside the menu. */
        HUI_Textbox **ppTextBox; /*!< Array of text box inside the menu. */
        HUI_Link    **ppLink;    /*!< Array of links inside the menu. */
        HUI_Sprite  *ppSprite;  /*!< Array of sprites inside the menu. */
        HUI_ID       iID;        /*!< ID of the menu, is unique. */
        SDL_bool     bQuit;      /*!< Flag to quit a menu. */
    }HUI_Menu;

    /*Buttons functions*/
    void HUI_Menu_GoForward(HUI_Menu *pMenu, HUI_ID iIDLink, HUI_Input *pInput);
    void HUI_Menu_GoBack(HUI_Menu *pMenu, HUI_ID iIDLink, HUI_Input *pInput);
    void HUI_Menu_OpenTextBox(HUI_Menu *pMenu, HUI_ID iIDLink, HUI_Input *pInput);
    void HUI_Menu_SetOption(HUI_Menu *pMenu, HUI_ID iIDLink, HUI_Input *pInput);

    void HUI_Menu_Init(void);
    void HUI_Menu_Load(HUI_ID iID, HUI_Input *pInput);
    void HUI_Menu_Free(void);
    void HUI_Menu_EmptyStack(void);

#endif // __HUI_MENU_H__

/* ========================================================================= */