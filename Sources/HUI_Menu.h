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

    #include "HUI_Switch.h"
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
        HUI_MENU_STATS = 2,
        HUI_MENU_ERROR = 404
    };

    typedef enum
    {
        HUI_MENU_SWITCH,
        HUI_MENU_BUTTON
    }HUI_Type;

    /*!
    * \struct HUI_Menu
    * \brief  Structure to handle the menus.
    */
    typedef struct HUI_Menu
    {
        HUI_Text                 **pArrText;        /*!< Array of text inside the menu. */
        HUI_Textbox              **pArrTextBox;     /*!< Array of text box inside the menu. */
        struct HUI_MenuButton    **pArrButtons;     /*!< Array of links inside the menu. */
        struct HUI_Sprite         *arrSprite;       /*!< Array of sprites inside the menu. */

        HUI_ID                     iID;             /*!< ID of the menu, is unique. */

        SDL_bool                   bQuit;           /*!< Flag to quit a menu. */
        SDL_bool                   bIsOpaque;       /*!< Flag to set the backgound transparent. */
    }HUI_Menu;

    typedef void(*pLinkFct)(HUI_ID); /*!< Pointer to the function to call on action of the button. */
    typedef void(*pActionFct)(void); /*!< Pointer to the function to call on action of the switch. */

    /*!
    * \struct HUI_MenuButton
    * \brief  Structure to handle the action of button in a menu.
    */
    typedef struct HUI_MenuButton
    {
        HUI_Type        eType;

        SDL_Sprite     *pSprite;     /*!< Sprite of the button. */
        HUI_Button      sButton;     /*!< Button associated to the link. */
        HUI_ID          iIDLink;     /*!< ID of the menu linked, if necessary. */
        pLinkFct        pLink;       /*!< Pointer to the function to call on action of the button. */

        HUI_Switch      sSwitch;     /*!< Switch associated to an option. */
        pActionFct      pActionEn;   /*!< Pointer to the function to call on action of the switch. */
        pActionFct      pActionDis;  /*!< Pointer to the function to call on action of the switch. */
        HUI_SwitchState iLastState;
    }HUI_MenuButton;

    /*!
    * \struct HUI_Sprite
    * \brief  Structure to handle a sprite with position.
    */
    typedef struct HUI_Sprite
    {
        SDL_Sprite *pSprite;
        SDL_Point   sPos;
    }HUI_Sprite;
    

    /*Buttons functions*/
    void HUI_Menu_GoForward(HUI_ID iIDLink);
    void HUI_Menu_GoBack(HUI_ID iIDLink);

    void     HUI_Menu_Init(void);
    HUI_ID   HUI_Menu_GetID(void);
    SDL_bool HUI_Menu_IsStackEmpty(void);

    void     HUI_Menu_Load(HUI_ID iID);
    void     HUI_Menu_Update(HUI_Input *pInput);
    void     HUI_Menu_Draw(void);
    void     HUI_Menu_Quit(HUI_Input *pInput);
    void     HUI_Menu_EmptyStack(void);
    void     HUI_Menu_Free(void);

#endif // __HUI_MENU_H__

/* ========================================================================= */