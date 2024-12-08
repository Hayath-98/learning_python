/*
 ******************************************************************************
 * License Information  :  Howell Instruments, Inc.                           *
 *                         "Licensed Software" and "All rights reserved".     *
 ******************************************************************************
 *  File                : hdudispfmenu2.c
 *
 *  Description         : Defines all the menu options in the display
 *
 *  Compiler            : GNU gcc(GNU Tools for ARM Embedded Processors) version 5.4.1 20160919
 *
 *  Compiler options    : As per section 10.3.1 of Software Development Plan (HDU-001-002).
 *
 *  Pragma              : None
 *
 *  H/W platform        : ARM Cortex-M7 (STM32F767)
 *
 *  Portability         : None
 *
 *  Author(s)           : Rona B.S
 *
 *  Version History     :
 * <Version No.>     <Author>          <Date>         <Problem Report No.>
 *
 *      1.1          Dhanalakshmi D   21-Jun-2020             100259
 *      1.2          Rona B.S	      30-Jun-2020             100259
 *      1.3          Dhanalakshmi     05-Aug-2020             100270
 *      1.4          Dhanalakshmi     12-Sep-2020             100276
 *      1.5          Dhanalakshmi     20-Mar-2021             100331
 *      1.6          Dhanalakshmi     20-Mar-2021             100331
 *      1.7          Dhanalakshmi     03-Apr-2021             100330
 *      1.8          Dhanalakshmi     13-May-2021             100350
 *
 * Additional References : None
 *
 ******************************************************************************
 */

#include <hdudispfpanel.h>           /* Contains functions prototypes of panel.*/
#include "hdudispfglobalsettings.h"  /* Routines to read and write data to NVRAM  */
#include "hdudispfgrapp.h"           /* routines for all graph */
#include "hdudispfmenu.h"            /* contains prototype for menu module*/
#include "hdudispfoffside.h"         /* contains prototype for offside modules*/
#include "hdudispfpbs.h"             /* Contains functions prototypes of pbs.*/
#include "hdudispfpdidata.h"         /* contains routines for PDI data */
#include "hdudispfpdicheck.h"    /* contains routines for PDI data check*/
#include "hdudispfpwm.h"             /* Contains functions prototypes of pwm.*/
#include "hdudispfrterror.h"           /* Provides sub routine for run time errors.*/
#include "hdudispftextbox.h"         /* routines for text box draw and updates */
#include "hdudispftimer.h"           /* increment a set of user installed timers. */

#include "hdudispfconfig.h"          /* contains page and color config information */
#include "hdudispfpara.h"  /* prototype for builds faults, message and system information */
#include "hdulibbasictypes.h"      /* Contains basic header definations */
#include "hdudispfa429.h"          /* provides a429 functionalities */
#include "hdudispfucos.h"          /* provides ucos functionalities */
#include "hdudispfoffside.h"  /* Screen, message and timer configuration */

T_UINT16 Display_width = 0;
T_UINT16 Display_height = 0;

#define M_THREE_EIGHTY_FIVE 385
#define M_THREE_HUNDRED 300
#define M_NINETY_FIVE 95
#define M_ONE_TWENTY 120
#define M_ONE_FIFTY 150
#define M_SEVENTY 70
#define M_EIGHTY 80
#define M_TWENTY_TWO 22
#define M_EIGHTY_SEVEN 87
#define M_FIFTY 50
#define M_TWENTY_TWO 22

/*
 * Function                : MenuInitialize7inch
 *
 * Description             : Initialize the 7 inch menu Items
 *
 * Formal parameter(s)     : None
 *
 * Return Value            : None
 *
 * Assumption              : None
 *
 */

void MenuInitialize7inch()
{
       /*Encoder_menu_select Initialization*/
       /* hdudispfmenu2-MenuInitialize7inch-DB-LLR-001 */
        Encoder_menu_select.eTBoxType = SELECT_BOX;
        Encoder_menu_select.s16ULX = MENU_LIST_ULX;
        Encoder_menu_select.s16ULY = MENU_LIST_ULY-SIXTEEN;
        Encoder_menu_select.s16PixWidth = MENU_LIST_WIDTH;
        Encoder_menu_select.s16PixHeight = MENU_LIST_HEIGHT+TWENTY;
        Encoder_menu_select.eTXFont = E_SMALL_FONT;
        Encoder_menu_select.eFontColor = WHITE;
        Encoder_menu_select.eBackGroundColor = MENU_LIST_COLOR;
        Encoder_menu_select.s16Margin = MENU_LIST_MARGIN;
        Encoder_menu_select.fill = EncoderMenuItemSelectText;
        Encoder_menu_select.s16FrameWidth = MENU_LIST_FRAME_WIDTH;
        Encoder_menu_select.eFrameColor = WHITE;
        Encoder_menu_select.pcTitle = &Menu_text[0];

        /*Encoder_page_select Initialization*/
        /* hdudispfmenu2-MenuInitialize7inch-DB-LLR-002 */
        Encoder_page_select.eTBoxType = SELECT_BOX;
        Encoder_page_select.s16ULX = PAGE_LIST_ULX;
        Encoder_page_select.s16ULY = PAGE_LIST_ULY;
        Encoder_page_select.s16PixWidth = PAGE_LIST_WIDTH;
        Encoder_page_select.s16PixHeight = PAGE_LIST_HEIGHT;
        Encoder_page_select.eTXFont = E_SMALL_FONT;
        Encoder_page_select.eFontColor = WHITE;
        Encoder_page_select.eBackGroundColor = PAGE_LIST_COLOR;
        Encoder_page_select.s16Margin = PAGE_LIST_MARGIN;
        Encoder_page_select.fill = EncoderPageItemSelectText;
        Encoder_page_select.s16FrameWidth = PAGE_LIST_FRAME_WIDTH;
        Encoder_page_select.eFrameColor = WHITE;
        Encoder_page_select.pcTitle = &Page_text[0];

        /*Message_text_box Initialization*/
        /* hdudispfmenu2-MenuInitialize7inch-DB-LLR-003 */
        Message_text_box.eTBoxType = LIST_BOX;
        Message_text_box.s16ULX = MESSAGE_BOX_ULX;
        Message_text_box.s16ULY = MESSAGE_BOX_ULY;
        Message_text_box.s16PixWidth = MESSAGE_BOX_WIDTH;
        Message_text_box.s16PixHeight = MESSAGE_BOX_HEIGHT;
        Message_text_box.eTXFont = E_SMALL_FONT;
        Message_text_box.eFontColor = LISTBOX_TEXT_COLOR;
        Message_text_box.eBackGroundColor = LISTBOX_BKGND_COLOR;
        Message_text_box.s16Margin = TEN;
        Message_text_box.fill = MessageBoxText;
        Message_text_box.s16FrameWidth = LISTBOX_FRAME_WIDTH;
        Message_text_box.eFrameColor = LISTBOX_FRAME_COLOR;
        Message_text_box.pcTitle = &Msgs_text[0];

        /*Exit_button Initialization*/
        /* hdudispfmenu2-MenuInitialize7inch-DB-LLR-004 */
        Exit_button.eTBoxType = BB_RIGHT;
        Exit_button.s16ULX = (T_INT16)(Display_width-SIDE_BB_WIDTH);
        Exit_button.s16ULY = SIDE_BB_ULY2;
        Exit_button.s16PixWidth = SIDE_BB_WIDTH;
        Exit_button.s16PixHeight = SIDE_BB_HEIGHT;
        Exit_button.eTXFont = SIDE_BB_FONT;
        Exit_button.eFontColor = BUTT_TEXT_COLOR;
        Exit_button.eBackGroundColor = ACTION_COLOR;
        Exit_button.s16Margin = SIDE_BB_INSIDE_BORDER;
        Exit_button.fill = ExitButtonText;
        Exit_button.s16FrameWidth = ZERO;
        Exit_button.eFrameColor = BLACK;

        /*Back_button Initialization*/
        /* hdudispfmenu2-MenuInitialize7inch-DB-LLR-005 */
        Back_button.eTBoxType = BB_RIGHT;
        Back_button.s16ULX = (T_INT16)(Display_width-SIDE_BB_WIDTH);
        Back_button.s16ULY = SIDE_BB_ULY3;
        Back_button.s16PixWidth = SIDE_BB_WIDTH;
        Back_button.s16PixHeight = SIDE_BB_HEIGHT;
        Back_button.eTXFont = SIDE_BB_FONT;
        Back_button.eFontColor = BUTT_TEXT_COLOR;
        Back_button.eBackGroundColor = ACTION_COLOR;
        Back_button.s16Margin = SIDE_BB_INSIDE_BORDER;
        Back_button.fill = BackButtonText;
        Back_button.s16FrameWidth = ZERO;
        Back_button.eFrameColor = BLACK;

        /*Scroll_button Initialization*/
        /* hdudispfmenu2-MenuInitialize7inch-DB-LLR-006 */
        Scroll_button.eTBoxType = BB_BOTTOM;
        Scroll_button.s16ULX = M_THREE_EIGHTY_FIVE;
        Scroll_button.s16ULY = (T_INT16)(Display_height-BOTTOM_BB_HEIGHT);
        Scroll_button.s16PixWidth =  (T_INT16)((Display_width/FIVE)-ONE);
        Scroll_button.s16PixHeight = BOTTOM_BB_HEIGHT;
        Scroll_button.eTXFont = BOTTOM_BB_FONT;
        Scroll_button.eFontColor = BUTT_TEXT_COLOR;
        Scroll_button.eBackGroundColor = ACTION_COLOR;
        Scroll_button.s16Margin = BOTTOM_BB_INSIDE_BORDER;
        Scroll_button.fill = ScrollButtonText;
        Scroll_button.s16FrameWidth = ZERO;
        Scroll_button.eFrameColor = BLACK;

        /*Cool_down_on_off_btn Initialization*/
        /* hdudispfmenu2-MenuInitialize7inch-DB-LLR-007 */
        Cool_down_on_off_btn.eTBoxType = BB_RIGHT;
        Cool_down_on_off_btn.s16ULX = (T_INT16)(Display_width-SIDE_BB_WIDTH);
        Cool_down_on_off_btn.s16ULY = SIDE_BB_ULY4;
        Cool_down_on_off_btn.s16PixWidth = SIDE_BB_WIDTH;
        Cool_down_on_off_btn.s16PixHeight = SIDE_BB_HEIGHT;
        Cool_down_on_off_btn.eTXFont = SIDE_BB_FONT;
        Cool_down_on_off_btn.eFontColor = BUTT_TEXT_COLOR;
        Cool_down_on_off_btn.eBackGroundColor = ACTION_COLOR;
        Cool_down_on_off_btn.s16Margin = SIDE_BB_INSIDE_BORDER;
        Cool_down_on_off_btn.fill = CoolDownOnOffButtonText;
        Cool_down_on_off_btn.s16FrameWidth = ZERO;
        Cool_down_on_off_btn.eFrameColor = BLACK;

        /*Man_timer_on_off_btn Initialization*/
        /* hdudispfmenu2-MenuInitialize7inch-DB-LLR-008 */
        Man_timer_on_off_btn.eTBoxType = BB_RIGHT;
        Man_timer_on_off_btn.s16ULX = (T_INT16)(Display_width-SIDE_BB_WIDTH);
        Man_timer_on_off_btn.s16ULY = SIDE_BB_ULY6;
        Man_timer_on_off_btn.s16PixWidth = SIDE_BB_WIDTH;
        Man_timer_on_off_btn.s16PixHeight = SIDE_BB_HEIGHT;
        Man_timer_on_off_btn.eTXFont = SIDE_BB_FONT;
        Man_timer_on_off_btn.eFontColor = BUTT_TEXT_COLOR;
        Man_timer_on_off_btn.eBackGroundColor = ACTION_COLOR;
        Man_timer_on_off_btn.s16Margin = SIDE_BB_INSIDE_BORDER;
        Man_timer_on_off_btn.fill = ManTimerOnOffText;
        Man_timer_on_off_btn.s16FrameWidth = ZERO;
        Man_timer_on_off_btn.eFrameColor = BLACK;

        /*Manual_timer_reset_btn Initialization*/
        /* hdudispfmenu2-MenuInitialize7inch-DB-LLR-009 */
        Manual_timer_reset_btn.eTBoxType = BB_RIGHT;
        Manual_timer_reset_btn.s16ULX = (T_INT16)(Display_width-SIDE_BB_WIDTH);
        Manual_timer_reset_btn.s16ULY = SIDE_BB_ULY7;
        Manual_timer_reset_btn.s16PixWidth = SIDE_BB_WIDTH;
        Manual_timer_reset_btn.s16PixHeight = SIDE_BB_HEIGHT_SM;
        Manual_timer_reset_btn.eTXFont = SIDE_BB_FONT;
        Manual_timer_reset_btn.eFontColor = BUTT_TEXT_COLOR;
        Manual_timer_reset_btn.eBackGroundColor = ACTION_COLOR;
        Manual_timer_reset_btn.s16Margin = SIDE_BB_INSIDE_BORDER;
        Manual_timer_reset_btn.fill = ManualTimerResetButtonText;
        Manual_timer_reset_btn.s16FrameWidth = ZERO;
        Manual_timer_reset_btn.eFrameColor = BLACK;

        /*Dummy_button Initialization*/
        /* hdudispfmenu2-MenuInitialize7inch-DB-LLR-010 */
        Dummy_button.eTBoxType = BB_RIGHT;
        Dummy_button.s16ULX = (T_INT16)((Display_width-SIDE_BB_WIDTH)
                -SIDE_BB_WIDTH-SIDE_BB_INSIDE_BORDER);
        Dummy_button.s16ULY = SIDE_BB_ULY1;
        Dummy_button.s16PixWidth = SIDE_BB_WIDTH;
        Dummy_button.s16PixHeight = SIDE_BB_HEIGHT;
        Dummy_button.eTXFont = SIDE_BB_FONT;
        Dummy_button.eFontColor = WHITE;
        Dummy_button.eBackGroundColor = BLACK;
        Dummy_button.s16Margin = SIDE_BB_INSIDE_BORDER;
        Dummy_button.fill = DummyButtonText;
        Dummy_button.s16FrameWidth = ZERO;
        Dummy_button.eFrameColor = BLACK;

        /*Top_button_1 Initialization*/
        /* hdudispfmenu2-MenuInitialize7inch-DB-LLR-011 */
		Top_button_1.eTBoxType = BB_RIGHT;
		Top_button_1.s16ULX = (T_INT16)(Display_width-SIDE_BB_WIDTH);
		Top_button_1.s16ULY = SIDE_BB_ULY1;
		Top_button_1.s16PixWidth = SIDE_BB_WIDTH;
		Top_button_1.s16PixHeight = SIDE_BB_HEIGHT;
		Top_button_1.eTXFont = SIDE_BB_FONT;
		Top_button_1.eFontColor = BUTT_TEXT_COLOR;
		Top_button_1.eBackGroundColor = ACTION_COLOR;
		Top_button_1.s16Margin = SIDE_BB_INSIDE_BORDER;
		Top_button_1.fill = TopButton1Text;
		Top_button_1.s16FrameWidth = ZERO;
		Top_button_1.eFrameColor = BLACK;

        /*Top_button_4 Initialization*/
        /* hdudispfmenu2-MenuInitialize7inch-DB-LLR-012 */
        Top_button_4.eTBoxType = BB_RIGHT;
        Top_button_4.s16ULX = (T_INT16)(Display_width-SIDE_BB_WIDTH);
        Top_button_4.s16ULY = SIDE_BB_ULY4;
        Top_button_4.s16PixWidth = SIDE_BB_WIDTH;
        Top_button_4.s16PixHeight = SIDE_BB_HEIGHT;
        Top_button_4.eTXFont = SIDE_BB_FONT;
        Top_button_4.eFontColor = BUTT_TEXT_COLOR;
        Top_button_4.eBackGroundColor = MENU_COLOR;
        Top_button_4.s16Margin = SIDE_BB_INSIDE_BORDER;
        Top_button_4.fill = TopButton4Text;
        Top_button_4.s16FrameWidth = ZERO;
        Top_button_4.eFrameColor = BLACK;

        /*Top_button_5 Initialization*/
        /* hdudispfmenu2-MenuInitialize7inch-DB-LLR-013 */
        Top_button_5.eTBoxType = BB_RIGHT;
        Top_button_5.s16ULX = (T_INT16)(Display_width-SIDE_BB_WIDTH);
        Top_button_5.s16ULY = SIDE_BB_ULY5;
        Top_button_5.s16PixWidth = SIDE_BB_WIDTH;
        Top_button_5.s16PixHeight = SIDE_BB_HEIGHT;
        Top_button_5.eTXFont = SIDE_BB_FONT;
        Top_button_5.eFontColor = BUTT_TEXT_COLOR;
        Top_button_5.eBackGroundColor = ACTION_COLOR;
        Top_button_5.s16Margin = SIDE_BB_INSIDE_BORDER;
        Top_button_5.fill = TopButton5Text;
        Top_button_5.s16FrameWidth = ZERO;
        Top_button_5.eFrameColor = BLACK;

        /*Top_button_6 Initialization*/
        /* hdudispfmenu2-MenuInitialize7inch-DB-LLR-014 */
        Top_button_6.eTBoxType = BB_RIGHT;
        Top_button_6.s16ULX = (T_INT16)(Display_width-SIDE_BB_WIDTH);
        Top_button_6.s16ULY = SIDE_BB_ULY6;
        Top_button_6.s16PixWidth = SIDE_BB_WIDTH;
        Top_button_6.s16PixHeight = SIDE_BB_HEIGHT;
        Top_button_6.eTXFont = SIDE_BB_FONT;
        Top_button_6.eFontColor = BUTT_TEXT_COLOR;
        Top_button_6.eBackGroundColor = MENU_COLOR;
        Top_button_6.s16Margin = SIDE_BB_INSIDE_BORDER;
        Top_button_6.fill = TopButton6Text;
        Top_button_6.s16FrameWidth = ZERO;
        Top_button_6.eFrameColor = BLACK;

        /*Top_button_7 Initialization*/
        /* hdudispfmenu2-MenuInitialize7inch-DB-LLR-015 */
        Timer_button.eTBoxType = BB_RIGHT;
        Timer_button.s16ULX = (T_INT16)(Display_width-SIDE_BB_WIDTH);
        Timer_button.s16ULY = SIDE_BB_ULY7;
        Timer_button.s16PixWidth = SIDE_BB_WIDTH;
        Timer_button.s16PixHeight = SIDE_BB_HEIGHT;
        Timer_button.eTXFont = SIDE_BB_FONT;
        Timer_button.eFontColor = BUTT_TEXT_COLOR;
        Timer_button.eBackGroundColor = MENU_COLOR;
        Timer_button.s16Margin = SIDE_BB_INSIDE_BORDER;
        Timer_button.fill = TopButton7Text;
        Timer_button.s16FrameWidth = ZERO;
        Timer_button.eFrameColor = BLACK;

        /*Page Button Initialization*/
        /* hdudispfmenu2-MenuInitialize7inch-DB-LLR-016 */
        Page_button.eTBoxType = BB_BOTTOM;
        Page_button.s16ULX = M_THREE_EIGHTY_FIVE;
        Page_button.s16ULY = (T_INT16)(Display_height-BOTTOM_BB_HEIGHT);
        Page_button.s16PixWidth = M_NINETY_FIVE;
        Page_button.s16PixHeight = M_TWENTY_TWO;
        Page_button.eTXFont = BOTTOM_BB_FONT;
        Page_button.eFontColor = BUTT_TEXT_COLOR;
        Page_button.eBackGroundColor = ACTION_COLOR;
        Page_button.s16Margin = BOTTOM_BB_INSIDE_BORDER;
        Page_button.fill = PageButtonText;
        Page_button.s16FrameWidth = ZERO;
        Page_button.eFrameColor = BLACK;

        /*Brightness_button Initialization*/
        /* hdudispfmenu2-MenuInitialize7inch-DB-LLR-017 */
        Brightness_button.eTBoxType = BB_BOTTOM;
        Brightness_button.s16ULX = BOTTOM_BB_ULX1;
        Brightness_button.s16ULY = (T_INT16)(Display_height-BOTTOM_BB_HEIGHT);
        Brightness_button.s16PixWidth = M_NINETY_FIVE;
        Brightness_button.s16PixHeight = M_TWENTY_TWO;
        Brightness_button.eTXFont = BOTTOM_BB_FONT;
        Brightness_button.eFontColor = BUTT_TEXT_COLOR;
        Brightness_button.eBackGroundColor = MENU_COLOR;
        Brightness_button.s16Margin = BOTTOM_BB_INSIDE_BORDER;
        Brightness_button.fill = TopButton13Text;
        Brightness_button.s16FrameWidth = ZERO;
        Brightness_button.eFrameColor = BLACK;

        Fuel_flow_message.eTBoxType = SELECT_BOX;
        Fuel_flow_message.s16ULX = PAGE_LIST_ULX-40;
        Fuel_flow_message.s16ULY = PAGE_LIST_ULY;
        Fuel_flow_message.s16PixWidth = PAGE_LIST_WIDTH+30;
        Fuel_flow_message.s16PixHeight = PAGE_LIST_HEIGHT+30;
        Fuel_flow_message.eTXFont = E_SMALL_FONT;
        Fuel_flow_message.eFontColor = WHITE;
        Fuel_flow_message.eBackGroundColor = PAGE_LIST_COLOR;
        Fuel_flow_message.s16Margin = PAGE_LIST_MARGIN;
        Fuel_flow_message.fill = FuelFlowOnOffButtonText;
        Fuel_flow_message.s16FrameWidth = PAGE_LIST_FRAME_WIDTH;
        Fuel_flow_message.eFrameColor = WHITE;
        Fuel_flow_message.pcTitle = &Fuel_flow_text[0];

        /*Sys_info_message_box Initialization*/
        /* hdudispfmenu2-MenuInitialize7inch-DB-LLR-018 */
        Sys_info_message_box.eTBoxType = LIST_BOX;
        Sys_info_message_box.s16ULX = SYSINFO_BOX_ULX;
        Sys_info_message_box.s16ULY = SYSINFO_BOX_ULY;
        Sys_info_message_box.s16PixWidth = SYSINFO_BOX_WIDTH;
        Sys_info_message_box.s16PixHeight = SYSINFO_BOX_HEIGHT;
        Sys_info_message_box.eTXFont = SYSINFO_FONT;
        Sys_info_message_box.eFontColor = WHITE;
        Sys_info_message_box.eBackGroundColor = SYSINFO_BKGND_COLOR;
        Sys_info_message_box.s16Margin = TEN;
        Sys_info_message_box.fill = SysInfoBoxText;
        Sys_info_message_box.s16FrameWidth = SYSINFO_FRAME_WIDTH;
        Sys_info_message_box.eFrameColor = SYSINFO_FRAME_COLOR;
        Sys_info_message_box.pcTitle = &Sys_info_text[0];

        /*Encoder_cool_down_select Initialization*/
        /* hdudispfmenu2-MenuInitialize7inch-DB-LLR-019 */
        Encoder_cool_down_select.eTBoxType = SELECT_BOX;
        Encoder_cool_down_select.s16ULX = COOL_DOWN_LIST_ULX;
        Encoder_cool_down_select.s16ULY = COOL_DOWN_LIST_ULY;
        Encoder_cool_down_select.s16PixWidth = COOL_DOWN_LIST_WIDTH;
        Encoder_cool_down_select.s16PixHeight = COOL_DOWN_LIST_HEIGHT;
        Encoder_cool_down_select.eTXFont = E_SMALL_FONT;
        Encoder_cool_down_select.eFontColor = WHITE;
        Encoder_cool_down_select.eBackGroundColor = DARK_BLUE;
        Encoder_cool_down_select.s16Margin = COOL_DOWN_LIST_MARGIN;
        Encoder_cool_down_select.fill = EncoderCoolDownItemSelectText;
        Encoder_cool_down_select.s16FrameWidth = COOL_DOWN_LIST_FRAME_WIDTH;
        Encoder_cool_down_select.eFrameColor = WHITE;
        Encoder_cool_down_select.pcTitle = &Cool_down_timer_text[0];

}

/*
 * Function                : MenuInitialize10inch
 *
 * Description             : Initialize the 10 inch menu Items
 *
 * Formal parameter(s)     : None
 *
 * Return Value            : None
 *
 * Assumption              : None
 *
 */


void MenuInitialize10inch()
{
        /* Menu_select_10Inch Initialization */
        /* hdudispfmenu2-MenuInitialize10inch-DB-LLR-002 */
        Menu_select_10inch.eTBoxType = SELECT_BOX;
        Menu_select_10inch.s16ULX = MENU_LIST_ULX-M_ONE_TWENTY;
        Menu_select_10inch.s16ULY = MENU_LIST_ULY-M_SEVENTY;
        Menu_select_10inch.s16PixWidth = MENU_LIST_WIDTH;
        Menu_select_10inch.s16PixHeight = MENU_LIST_HEIGHT+ TWENTY;
        Menu_select_10inch.eTXFont = E_SMALL_FONT;
        Menu_select_10inch.eFontColor = WHITE;
        Menu_select_10inch.eBackGroundColor = ACTION_COLOR;
        Menu_select_10inch.s16Margin = MENU_LIST_MARGIN;
        Menu_select_10inch.fill = MenuItemSelectText10Inch;
        Menu_select_10inch.s16FrameWidth = MENU_LIST_FRAME_WIDTH;
        Menu_select_10inch.eFrameColor = WHITE;
        Menu_select_10inch.pcTitle = &Menu_text[0];

		/*Encoder_page_select Initialization*/
		/* hdudispfmenu2-MenuInitialize10inch-DB-LLR-003 */
		Encoder_page_select.eTBoxType = SELECT_BOX;
		Encoder_page_select.s16ULX = PAGE_LIST_ULX_10INCH;
		Encoder_page_select.s16ULY = PAGE_LIST_ULY_10INCH;
		Encoder_page_select.s16PixWidth = PAGE_LIST_WIDTH;
		Encoder_page_select.s16PixHeight = PAGE_LIST_HEIGHT;
		Encoder_page_select.eTXFont = E_SMALL_FONT;
		Encoder_page_select.eFontColor = WHITE;
		Encoder_page_select.eBackGroundColor = PAGE_LIST_COLOR;
		Encoder_page_select.s16Margin = PAGE_LIST_MARGIN;
		Encoder_page_select.fill = EncoderPageItemSelectText;
		Encoder_page_select.s16FrameWidth = PAGE_LIST_FRAME_WIDTH;
		Encoder_page_select.eFrameColor = WHITE;
		Encoder_page_select.pcTitle = &Page_text[0];

        /* hdudispfmenu2-MenuInitialize10inch-DB-LLR-004 */
		/*Message_text_box Initialization*/
        Message_text_box.eTBoxType = LIST_BOX;
        Message_text_box.s16ULX = M_THREE_HUNDRED;
        Message_text_box.s16ULY = MESSAGE_BOX_ULY;
        Message_text_box.s16PixWidth = MESSAGE_BOX_WIDTH;
        Message_text_box.s16PixHeight = MESSAGE_BOX_HEIGHT;
        Message_text_box.eTXFont = E_SMALL_FONT;
        Message_text_box.eFontColor = LISTBOX_TEXT_COLOR;
        Message_text_box.eBackGroundColor = LISTBOX_BKGND_COLOR;
        Message_text_box.s16Margin = TEN;
        Message_text_box.fill = MessageBoxText;
        Message_text_box.s16FrameWidth = LISTBOX_FRAME_WIDTH;
        Message_text_box.eFrameColor = LISTBOX_FRAME_COLOR;
        Message_text_box.pcTitle = &Msgs_text[0];

        /*Exit_button Initialization*/
        /* hdudispfmenu2-MenuInitialize10inch-DB-LLR-005 */
        Exit_button.eTBoxType = BB_BOTTOM;
        Exit_button.s16ULX = BOTTOM_BB_ULX5_10INCH;
        Exit_button.s16ULY = (T_INT16)(Display_height-BOTTOM_BB_HEIGHT_10INCH);
        Exit_button.s16PixWidth = BOTTOM_BB_WIDTH_10INCH;
        Exit_button.s16PixHeight = BOTTOM_BB_HEIGHT_10INCH;
        Exit_button.eTXFont = BOTTOM_BB_FONT;
        Exit_button.eFontColor = BUTT_TEXT_COLOR;
        Exit_button.eBackGroundColor = ACTION_COLOR;
        Exit_button.s16Margin = BOTTOM_BB_INSIDE_BORDER_10;
        Exit_button.fill = ExitButtonText;
        Exit_button.s16FrameWidth = ZERO;
        Exit_button.eFrameColor = BLACK;

        /*Back_button Initialization*/
        /* hdudispfmenu2-MenuInitialize10inch-DB-LLR-006 */
        Back_button.eTBoxType = BB_BOTTOM;
        Back_button.s16ULX = BOTTOM_BB_ULX7_10INCH;
        Back_button.s16ULY = (T_INT16)(Display_height-BOTTOM_BB_HEIGHT_10INCH);
        Back_button.s16PixWidth = BOTTOM_BB_WIDTH_10INCH;
        Back_button.s16PixHeight = BOTTOM_BB_HEIGHT_10INCH;
        Back_button.eTXFont = BOTTOM_BB_FONT;
        Back_button.eFontColor = BUTT_TEXT_COLOR;
        Back_button.eBackGroundColor = ACTION_COLOR;
        Back_button.s16Margin = BOTTOM_BB_INSIDE_BORDER_10;
        Back_button.fill = BackButtonText;
        Back_button.s16FrameWidth = ZERO;
        Back_button.eFrameColor = BLACK;

        /*Scroll_button Initialization*/
        /* hdudispfmenu2-MenuInitialize10inch-DB-LLR-007 */
        Scroll_button.eTBoxType = BB_BOTTOM;
        Scroll_button.s16ULX = BOTTOM_BB_ULX3_10INCH;
        Scroll_button.s16ULY = (T_INT16)(Display_height-BOTTOM_BB_HEIGHT_10INCH);
        Scroll_button.s16PixWidth = BOTTOM_BB_WIDTH_10INCH;
        Scroll_button.s16PixHeight = BOTTOM_BB_HEIGHT_10INCH;
        Scroll_button.eTXFont = BOTTOM_BB_FONT;
        Scroll_button.eFontColor = BUTT_TEXT_COLOR;
        Scroll_button.eBackGroundColor = MENU_COLOR;
        Scroll_button.s16Margin = BOTTOM_BB_INSIDE_BORDER_10;
        Scroll_button.fill = ScrollButtonText;
        Scroll_button.s16FrameWidth = ZERO;
        Scroll_button.eFrameColor = BLACK;

        /*Dummy_button Initialization*/
        /* hdudispfmenu2-MenuInitialize10inch-DB-LLR-011 */
        Dummy_button.eTBoxType = BB_RIGHT;
        Dummy_button.s16ULX = (T_INT16)((Display_width-SIDE_BB_WIDTH)
                -SIDE_BB_WIDTH-SIDE_BB_INSIDE_BORDER);
        Dummy_button.s16ULY = SIDE_BB_ULY1;
        Dummy_button.s16PixWidth = SIDE_BB_WIDTH;
        Dummy_button.s16PixHeight = SIDE_BB_HEIGHT;
        Dummy_button.eTXFont = SIDE_BB_FONT;
        Dummy_button.eFontColor = WHITE;
        Dummy_button.eBackGroundColor = BLACK;
        Dummy_button.s16Margin = SIDE_BB_INSIDE_BORDER;
        Dummy_button.fill = DummyButtonText;
        Dummy_button.s16FrameWidth = ZERO;
        Dummy_button.eFrameColor = BLACK;

        /* hdudispfmenu2-MenuInitialize10inch-DB-LLR-012 */
        Set_button.eTBoxType = BB_BOTTOM;
        Set_button.s16ULX = BOTTOM_BB_ULX4_10INCH;
        Set_button.s16ULY = (T_INT16)(Display_height-BOTTOM_BB_HEIGHT_10INCH);
        Set_button.s16PixWidth = BOTTOM_BB_WIDTH_10INCH;
        Set_button.s16PixHeight = BOTTOM_BB_HEIGHT_10INCH;
        Set_button.eTXFont = BOTTOM_BB_FONT;
        Set_button.eFontColor = BUTT_TEXT_COLOR;
        Set_button.eBackGroundColor = MENU_COLOR;
        Set_button.s16Margin = BOTTOM_BB_INSIDE_BORDER_10;
        Set_button.fill = SetButtonText;
        Set_button.s16FrameWidth = ZERO;
        Set_button.eFrameColor = BLACK;

        /*Top_button_1 Initialization*/
        /* hdudispfmenu2-MenuInitialize10inch-DB-LLR-013 */
		Top_button_1.eTBoxType = BB_BOTTOM;
		Top_button_1.s16ULX = BOTTOM_BB_ULX1_10INCH;
		Top_button_1.s16ULY = (T_INT16)(Display_height-BOTTOM_BB_HEIGHT_10INCH);
		Top_button_1.s16PixWidth = BOTTOM_BB_WIDTH_10INCH;
		Top_button_1.s16PixHeight = BOTTOM_BB_HEIGHT_10INCH;
		Top_button_1.eTXFont = BOTTOM_BB_FONT;
		Top_button_1.eFontColor = BUTT_TEXT_COLOR;
		Top_button_1.eBackGroundColor = ACTION_COLOR;
		Top_button_1.s16Margin = BOTTOM_BB_INSIDE_BORDER_10;
		Top_button_1.fill = TopButton1Text;
		Top_button_1.s16FrameWidth = ZERO;
		Top_button_1.eFrameColor = BLACK;

        /*Top_button_2 Initialization*/
        /* hdudispfmenu2-MenuInitialize10inch-DB-LLR-014 */
        Top_button_2.eTBoxType = BB_BOTTOM;
        Top_button_2.s16ULX = BOTTOM_BB_ULX2_10INCH;
        Top_button_2.s16ULY = (T_INT16)(Display_height-BOTTOM_BB_HEIGHT_10INCH);
        Top_button_2.s16PixWidth = BOTTOM_BB_WIDTH_10INCH;
        Top_button_2.s16PixHeight = BOTTOM_BB_HEIGHT_10INCH;
        Top_button_2.eTXFont = BOTTOM_BB_FONT;
        Top_button_2.eFontColor = BUTT_TEXT_COLOR;
        Top_button_2.eBackGroundColor = MENU_COLOR;
        Top_button_2.s16Margin = BOTTOM_BB_INSIDE_BORDER_10;
        Top_button_2.fill = TopButton2Text10Inch;
        Top_button_2.s16FrameWidth = ZERO;
        Top_button_2.eFrameColor = BLACK;

        /*Top_button_3 Initialization*/
        /* hdudispfmenu2-MenuInitialize10inch-DB-LLR-015 */
        Top_button_3.eTBoxType = BB_BOTTOM;
        Top_button_3.s16ULX = BOTTOM_BB_ULX3_10INCH;
        Top_button_3.s16ULY = (T_INT16)(Display_height-BOTTOM_BB_HEIGHT_10INCH);
        Top_button_3.s16PixWidth = BOTTOM_BB_WIDTH_10INCH;
        Top_button_3.s16PixHeight = BOTTOM_BB_HEIGHT_10INCH;
        Top_button_3.eTXFont = BOTTOM_BB_FONT;
        Top_button_3.eFontColor = BUTT_TEXT_COLOR;
        Top_button_3.eBackGroundColor = MENU_COLOR;
        Top_button_3.s16Margin = BOTTOM_BB_INSIDE_BORDER_10;
        Top_button_3.fill = TopButton3Text10Inch;
        Top_button_3.s16FrameWidth = ZERO;
        Top_button_3.eFrameColor = BLACK;

        /*Top_button_4 Initialization*/
        /* hdudispfmenu2-MenuInitialize10inch-DB-LLR-016 */
        Top_button_4.eTBoxType = BB_BOTTOM;
        Top_button_4.s16ULX = BOTTOM_BB_ULX4_10INCH;
        Top_button_4.s16ULY = (T_INT16)(Display_height-BOTTOM_BB_HEIGHT_10INCH);
        Top_button_4.s16PixWidth = BOTTOM_BB_WIDTH_10INCH;
        Top_button_4.s16PixHeight = BOTTOM_BB_HEIGHT_10INCH;
        Top_button_4.eTXFont = BOTTOM_BB_FONT;
        Top_button_4.eFontColor = BUTT_TEXT_COLOR;
        Top_button_4.eBackGroundColor = MENU_COLOR;
        Top_button_4.s16Margin = BOTTOM_BB_INSIDE_BORDER_10;
        Top_button_4.fill = TopButton4Text10Inch;
        Top_button_4.s16FrameWidth = ZERO;
        Top_button_4.eFrameColor = BLACK;

        /*Top_button_5 Initialization*/
        /* hdudispfmenu2-MenuInitialize10inch-DB-LLR-017 */
        Top_button_5.eTBoxType = BB_BOTTOM;
        Top_button_5.s16ULX = BOTTOM_BB_ULX5_10INCH;
        Top_button_5.s16ULY = (T_INT16)(Display_height-BOTTOM_BB_HEIGHT_10INCH);
        Top_button_5.s16PixWidth = BOTTOM_BB_WIDTH_10INCH;
        Top_button_5.s16PixHeight = BOTTOM_BB_HEIGHT_10INCH;
        Top_button_5.eTXFont = BOTTOM_BB_FONT;
        Top_button_5.eFontColor = BUTT_TEXT_COLOR;
        Top_button_5.eBackGroundColor = ACTION_COLOR;
        Top_button_5.s16Margin = BOTTOM_BB_INSIDE_BORDER_10;
        Top_button_5.fill = TopButton5Text;
        Top_button_5.s16FrameWidth = ZERO;
        Top_button_5.eFrameColor = BLACK;

        /*Top_button_6 Initialization*/
        /* hdudispfmenu2-MenuInitialize10inch-DB-LLR-018 */
        Top_button_6.eTBoxType = BB_BOTTOM;
        Top_button_6.s16ULX = BOTTOM_BB_ULX6_10INCH;
        Top_button_6.s16ULY = (T_INT16)(Display_height-BOTTOM_BB_HEIGHT_10INCH);
        Top_button_6.s16PixWidth = BOTTOM_BB_WIDTH_10INCH;
        Top_button_6.s16PixHeight = BOTTOM_BB_HEIGHT_10INCH;
        Top_button_6.eTXFont = BOTTOM_BB_FONT;
        Top_button_6.eFontColor = BUTT_TEXT_COLOR;
        Top_button_6.eBackGroundColor = MENU_COLOR;
        Top_button_6.s16Margin = BOTTOM_BB_INSIDE_BORDER_10;
        Top_button_6.fill = TopButton6Text;
        Top_button_6.s16FrameWidth = ZERO;
        Top_button_6.eFrameColor = BLACK;

        /*Man_timer_on_off_btn Initialization*/
        /* hdudispfmenu2-MenuInitialize10inch-DB-LLR-019 */
        Man_timer_on_off_btn.eTBoxType = BB_BOTTOM;
        Man_timer_on_off_btn.s16ULX = BOTTOM_BB_ULX6_10INCH;
        Man_timer_on_off_btn.s16ULY = (T_INT16)(Display_height-BOTTOM_BB_HEIGHT_10INCH);
        Man_timer_on_off_btn.s16PixWidth = BOTTOM_BB_WIDTH_10INCH;
        Man_timer_on_off_btn.s16PixHeight = BOTTOM_BB_HEIGHT_10INCH;
        Man_timer_on_off_btn.eTXFont = BOTTOM_BB_FONT;
        Man_timer_on_off_btn.eFontColor = BUTT_TEXT_COLOR;
        Man_timer_on_off_btn.eBackGroundColor = ACTION_COLOR;
        Man_timer_on_off_btn.s16Margin = BOTTOM_BB_INSIDE_BORDER_10;
        Man_timer_on_off_btn.fill = ManTimerOnOffText;
        Man_timer_on_off_btn.s16FrameWidth = ZERO;
        Man_timer_on_off_btn.eFrameColor = BLACK;

        /*Manual_timer_reset_btn Initialization*/

        Manual_timer_reset_btn.eTBoxType = BB_BOTTOM;
        Manual_timer_reset_btn.s16ULX = BOTTOM_BB_ULX7_10INCH;
        Manual_timer_reset_btn.s16ULY = (T_INT16)(Display_height-BOTTOM_BB_HEIGHT_10INCH);
        Manual_timer_reset_btn.s16PixWidth = BOTTOM_BB_WIDTH_10INCH;
        Manual_timer_reset_btn.s16PixHeight = BOTTOM_BB_HEIGHT_10INCH;
        Manual_timer_reset_btn.eTXFont = BOTTOM_BB_FONT;
        Manual_timer_reset_btn.eFontColor = BUTT_TEXT_COLOR;
        Manual_timer_reset_btn.eBackGroundColor = ACTION_COLOR;
        Manual_timer_reset_btn.s16Margin = BOTTOM_BB_INSIDE_BORDER_10;
        Manual_timer_reset_btn.fill = ManualTimerResetButtonText;
        Manual_timer_reset_btn.s16FrameWidth = ZERO;
        Manual_timer_reset_btn.eFrameColor = BLACK;

		/*Top_button9 Initialization*/
		/* hdudispfmenu2-MenuInitialize10inch-DB-LLR-020 */
		Timer_button.eTBoxType = BB_BOTTOM;
		Timer_button.s16ULX = BOTTOM_BB_ULX7_10INCH;
		Timer_button.s16ULY = (T_INT16)(Display_height-BOTTOM_BB_HEIGHT_10INCH);
		Timer_button.s16PixWidth = BOTTOM_BB_WIDTH_10INCH;
		Timer_button.s16PixHeight = BOTTOM_BB_HEIGHT_10INCH;
		Timer_button.eTXFont = BOTTOM_BB_FONT;
		Timer_button.eFontColor = BUTT_TEXT_COLOR;
		Timer_button.eBackGroundColor = MENU_COLOR;
		Timer_button.s16Margin = BOTTOM_BB_INSIDE_BORDER_10;
		Timer_button.fill = TopButton7Text;
		Timer_button.s16FrameWidth = ZERO;
		Timer_button.eFrameColor = BLACK;

		/*Top_button_11 Initialization*/
		/* hdudispfmenu2-MenuInitialize10inch-DB-LLR-021 */
		Top_button_minus.eTBoxType = BB_BOTTOM;
		Top_button_minus.s16ULX = BOTTOM_BB_ULX6_10INCH;
		Top_button_minus.s16ULY = (T_INT16)(Display_height-BOTTOM_BB_HEIGHT_10INCH);
		Top_button_minus.s16PixWidth = BOTTOM_BB_WIDTH_10INCH;
		Top_button_minus.s16PixHeight = BOTTOM_BB_HEIGHT_10INCH;
		Top_button_minus.eTXFont = BOTTOM_BB_FONT;
		Top_button_minus.eFontColor = BUTT_TEXT_COLOR;
		Top_button_minus.eBackGroundColor = MENU_COLOR;
		Top_button_minus.s16Margin = BOTTOM_BB_INSIDE_BORDER_10;
		Top_button_minus.fill = TopButton6Text10Inch;
		Top_button_minus.s16FrameWidth = ZERO;
		Top_button_minus.eFrameColor = BLACK;

		/*Top_button_12 Initialization*/
		/* hdudispfmenu2-MenuInitialize10inch-DB-LLR-022 */
		Top_button_plus.eTBoxType = BB_BOTTOM;
		Top_button_plus.s16ULX = BOTTOM_BB_ULX7_10INCH;
		Top_button_plus.s16ULY = (T_INT16)(Display_height-BOTTOM_BB_HEIGHT_10INCH);
		Top_button_plus.s16PixWidth = BOTTOM_BB_WIDTH_10INCH;
		Top_button_plus.s16PixHeight = BOTTOM_BB_HEIGHT_10INCH;
		Top_button_plus.eTXFont = BOTTOM_BB_FONT;
		Top_button_plus.eFontColor = BUTT_TEXT_COLOR;
		Top_button_plus.eBackGroundColor = MENU_COLOR;
		Top_button_plus.s16Margin = BOTTOM_BB_INSIDE_BORDER_10;
		Top_button_plus.fill = TopButton7Text10Inch;
		Top_button_plus.s16FrameWidth = ZERO;
		Top_button_plus.eFrameColor = BLACK;
        /*Brightness_button Initialization*/
        /* hdudispfmenu2-MenuInitialize10inch-DB-LLR-023 */
		Brightness_button.eTBoxType = BB_BOTTOM;
		Brightness_button.s16ULX = BOTTOM_BB_ULX8_10INCH;
		Brightness_button.s16ULY = (T_INT16)(Display_height-BOTTOM_BB_HEIGHT_10INCH);
		Brightness_button.s16PixWidth = BOTTOM_BB_WIDTH_10INCH;
		Brightness_button.s16PixHeight = BOTTOM_BB_HEIGHT_10INCH;
		Brightness_button.eTXFont = BOTTOM_BB_FONT;
		Brightness_button.eFontColor = BUTT_TEXT_COLOR;
		Brightness_button.eBackGroundColor = MENU_COLOR;
		Brightness_button.s16Margin = BOTTOM_BB_INSIDE_BORDER_10;
		Brightness_button.fill = TopButton8Text10Inch;
		Brightness_button.s16FrameWidth = ZERO;
		Brightness_button.eFrameColor = BLACK;

        /*Sys_info_message_box Initialization*/
        /* hdudispfmenu2-MenuInitialize10inch-DB-LLR-024 */
        Sys_info_message_box.eTBoxType = LIST_BOX;
        Sys_info_message_box.s16ULX = M_THREE_HUNDRED;
        Sys_info_message_box.s16ULY = SYSINFO_BOX_ULY;
        Sys_info_message_box.s16PixWidth = SYSINFO_BOX_WIDTH;
        Sys_info_message_box.s16PixHeight = SYSINFO_BOX_HEIGHT;
        Sys_info_message_box.eTXFont = SYSINFO_FONT;
        Sys_info_message_box.eFontColor = WHITE;
        Sys_info_message_box.eBackGroundColor = SYSINFO_BKGND_COLOR;
        Sys_info_message_box.s16Margin = TEN;
        Sys_info_message_box.fill = SysInfoBoxText;
        Sys_info_message_box.s16FrameWidth = SYSINFO_FRAME_WIDTH;
        Sys_info_message_box.eFrameColor = SYSINFO_FRAME_COLOR;
        Sys_info_message_box.pcTitle = &Sys_info_text[0];

        /*Encoder_cool_down_select Initialization*/
        /* hdudispfmenu2-MenuInitialize10inch-DB-LLR-025 */
        Encoder_cool_down_select.eTBoxType = SELECT_BOX;
        Encoder_cool_down_select.s16ULX = COOL_DOWN_LIST_ULX_10INCH;
        Encoder_cool_down_select.s16ULY = COOL_DOWN_LIST_ULY_10INCH;
        Encoder_cool_down_select.s16PixWidth = COOL_DOWN_LIST_WIDTH;
        Encoder_cool_down_select.s16PixHeight = COOL_DOWN_LIST_HEIGHT;
        Encoder_cool_down_select.eTXFont = E_SMALL_FONT;
        Encoder_cool_down_select.eFontColor = WHITE;
        Encoder_cool_down_select.eBackGroundColor = DARK_BLUE;
        Encoder_cool_down_select.s16Margin = COOL_DOWN_LIST_MARGIN;
        Encoder_cool_down_select.fill = EncoderCoolDownItemSelectText;
        Encoder_cool_down_select.s16FrameWidth = COOL_DOWN_LIST_FRAME_WIDTH;
        Encoder_cool_down_select.eFrameColor = WHITE;
        Encoder_cool_down_select.pcTitle = &Cool_down_timer_text[0];

        /* hdudispfmenu2-MenuInitialize10inch-DB-LLR-026 */
        Calibration_box.eTBoxType = SELECT_BOX;
        Calibration_box.s16ULX = MENU_LIST_ULX-M_ONE_TWENTY;
        Calibration_box.s16ULY = MENU_LIST_ULY-M_ONE_FIFTY;
        Calibration_box.s16PixWidth = MENU_LIST_WIDTH;
        Calibration_box.s16PixHeight = MENU_LIST_HEIGHT+M_EIGHTY;
        Calibration_box.eTXFont = E_SMALL_FONT;
        Calibration_box.eFontColor = WHITE;
        Calibration_box.eBackGroundColor = MENU_LIST_COLOR;
        Calibration_box.s16Margin = MENU_LIST_MARGIN;
        Calibration_box.fill = CalibrationSelectText10Inch;
        Calibration_box.s16FrameWidth = MENU_LIST_FRAME_WIDTH;
        Calibration_box.eFrameColor = WHITE;
        Calibration_box.pcTitle = &Engine_text[0];

        /* hdudispfmenu2-MenuInitialize10inch-DB-LLR-027 */
        Engine_calibration_box.eTBoxType = SELECT_BOX;
        Engine_calibration_box.s16ULX = MENU_LIST_ULX-M_ONE_TWENTY;
        Engine_calibration_box.s16ULY = MENU_LIST_ULY-M_ONE_FIFTY;
        Engine_calibration_box.s16PixWidth = MENU_LIST_WIDTH;
        Engine_calibration_box.s16PixHeight = MENU_LIST_HEIGHT+M_EIGHTY;
        Engine_calibration_box.eTXFont = E_SMALL_FONT;
        Engine_calibration_box.eFontColor = WHITE;
        Engine_calibration_box.eBackGroundColor = MENU_LIST_COLOR;
        Engine_calibration_box.s16Margin = MENU_LIST_MARGIN;
        Engine_calibration_box.fill = EngCalibrationSelectTxt10Inch;
        Engine_calibration_box.s16FrameWidth = MENU_LIST_FRAME_WIDTH;
        Engine_calibration_box.eFrameColor = WHITE;
        Engine_calibration_box.pcTitle = &Engine_calibration_text[0];

        /* hdudispfmenu2-MenuInitialize10inch-DB-LLR-028 */
        Parameter_calibration_box.eTBoxType = SELECT_BOX;
        Parameter_calibration_box.s16ULX = MENU_LIST_ULX-M_ONE_TWENTY;
        Parameter_calibration_box.s16ULY = MENU_LIST_ULY-M_ONE_FIFTY;
        Parameter_calibration_box.s16PixWidth = MENU_LIST_WIDTH;
        Parameter_calibration_box.s16PixHeight = MENU_LIST_HEIGHT+M_EIGHTY;
        Parameter_calibration_box.eTXFont = E_SMALL_FONT;
        Parameter_calibration_box.eFontColor = WHITE;
        Parameter_calibration_box.eBackGroundColor = MENU_LIST_COLOR;
        Parameter_calibration_box.s16Margin = MENU_LIST_MARGIN;
        Parameter_calibration_box.fill = ParamCalibriSlctTxt10Inch;
        Parameter_calibration_box.s16FrameWidth = MENU_LIST_FRAME_WIDTH;
        Parameter_calibration_box.eFrameColor = WHITE;
        Parameter_calibration_box.pcTitle = &Engine_calibration_text[0];

        /* hdudispfmenu2-MenuInitialize10inch-DB-LLR-029 */
        Next_box.eTBoxType = BB_BOTTOM;
        Next_box.s16ULX = BOTTOM_BB_ULX2_10INCH;
        Next_box.s16ULY = (T_INT16)(Display_height-BOTTOM_BB_HEIGHT_10INCH);
        Next_box.s16PixWidth = BOTTOM_BB_WIDTH_10INCH;
        Next_box.s16PixHeight = BOTTOM_BB_HEIGHT_10INCH;
        Next_box.eTXFont = BOTTOM_BB_FONT;
        Next_box.eFontColor = BUTT_TEXT_COLOR;
        Next_box.eBackGroundColor = MENU_COLOR;
        Next_box.s16Margin = BOTTOM_BB_INSIDE_BORDER_10;
        Next_box.fill = NextBoxText;
        Next_box.s16FrameWidth = ZERO;
        Next_box.eFrameColor = BLACK;

        /* hdudispfmenu2-MenuInitialize10inch-DB-LLR-030 */
        Offset_box.eTBoxType = SELECT_BOX;
        Offset_box.s16ULX = MENU_LIST_ULX-M_ONE_TWENTY;
        Offset_box.s16ULY = MENU_LIST_ULY-M_ONE_FIFTY;
        Offset_box.s16PixWidth = MENU_LIST_WIDTH;
        Offset_box.s16PixHeight = MENU_LIST_HEIGHT+M_EIGHTY;
        Offset_box.eTXFont = E_SMALL_FONT;
        Offset_box.eFontColor = WHITE;
        Offset_box.eBackGroundColor = MENU_LIST_COLOR;
        Offset_box.s16Margin = MENU_LIST_MARGIN;
        Offset_box.fill = OffsetValueText;
        Offset_box.s16FrameWidth = MENU_LIST_FRAME_WIDTH;
        Offset_box.eFrameColor = WHITE;
        Offset_box.pcTitle = &Offset_text[0];

        /* hdudispfmenu2-MenuInitialize10inch-DB-LLR-031 */
        Gain_box.eTBoxType = SELECT_BOX;
        Gain_box.s16ULX = MENU_LIST_ULX-M_ONE_TWENTY;
        Gain_box.s16ULY = MENU_LIST_ULY-M_ONE_FIFTY;
        Gain_box.s16PixWidth = MENU_LIST_WIDTH;
        Gain_box.s16PixHeight = MENU_LIST_HEIGHT+M_EIGHTY;
        Gain_box.eTXFont = E_SMALL_FONT;
        Gain_box.eFontColor = WHITE;
        Gain_box.eBackGroundColor = MENU_LIST_COLOR;
        Gain_box.s16Margin = MENU_LIST_MARGIN;
        Gain_box.fill = GainValueText;
        Gain_box.s16FrameWidth = MENU_LIST_FRAME_WIDTH;
        Gain_box.eFrameColor = WHITE;
        Gain_box.pcTitle = &Gain_text[0];

        /* hdudispfmenu2-MenuInitialize10inch-DB-LLR-032 */
        Button_page_select.eTBoxType = SELECT_BOX;
        Button_page_select.s16ULX = MENU_LIST_ULX-M_ONE_TWENTY;
        Button_page_select.s16ULY = MENU_LIST_ULY-M_EIGHTY_SEVEN;
        Button_page_select.s16PixWidth = M_ONE_TWENTY;
        Button_page_select.s16PixHeight = MENU_LIST_HEIGHT+M_FIFTY;
        Button_page_select.eTXFont = E_SMALL_FONT;
        Button_page_select.eFontColor = WHITE;
        Button_page_select.eBackGroundColor = PAGE_LIST_COLOR;
        Button_page_select.s16Margin = MENU_LIST_COLOR;
        Button_page_select.fill =  ButtonPageItemSelectText;
        Button_page_select.s16FrameWidth = PAGE_LIST_FRAME_WIDTH;
        Button_page_select.eFrameColor = WHITE;
        Button_page_select.pcTitle = &Page_text[0];

        /* hdudispfmenu2-MenuInitialize10inch-DB-LLR-033 */
        Page_button.eTBoxType = BB_BOTTOM;
        Page_button.s16ULX = BOTTOM_BB_ULX2_10INCH;
        Page_button.s16ULY = (T_INT16)(Display_height-BOTTOM_BB_HEIGHT_10INCH);
        Page_button.s16PixWidth = BOTTOM_BB_WIDTH_10INCH;
        Page_button.s16PixHeight = BOTTOM_BB_HEIGHT_10INCH;
        Page_button.eTXFont = BOTTOM_BB_FONT;
        Page_button.eFontColor = BUTT_TEXT_COLOR;
        Page_button.eBackGroundColor = MENU_COLOR;
        Page_button.s16Margin = BOTTOM_BB_INSIDE_BORDER_10;
        Page_button.fill = PageButtonText;
        Page_button.s16FrameWidth = ZERO;
        Page_button.eFrameColor = BLACK;


}

/*
 * Function                : MenuInitialize
 *
 * Description             : Initialize the menu Items
 *
 * Formal parameter(s)     : None
 *
 * Return Value            : None
 *
 * Assumption              : None
 *
 */

void MenuInitialize()
{
    if (E_7_INCH == Display_size)
    {
        /* hdudispfmenu2-MenuInitialize-DB-LLR-001 */
        Display_width = PANEL_HEIGHT;
        Display_height = PANEL_WIDTH;
        MenuInitialize7inch();
        /*Initialize Top Menu*/
        Top_menu[0] = &Top_button_1;
        Top_menu[1] = &Dummy_button;
        Top_menu[2] = &Dummy_button;
        Top_menu[3] = &Top_button_4;
        Top_menu[4] = &Top_button_5;
        Top_menu[5] = &Top_button_6;
        Top_menu[6] = &Timer_button;
        Top_menu[7] = &Dummy_button;
        Top_menu[8] = &Page_button;
        Top_menu[9] = &Dummy_button;
        Top_menu[10] = &Dummy_button;
        Top_menu[11] = &Dummy_button;
        Top_menu[12] = &Brightness_button;
        Top_menu[13] = ZERO;

    }
    else if (E_10_INCH == Display_size)
    {
        /* hdudispfmenu2-MenuInitialize-DB-LLR-002 */
        Display_width = PANEL_WIDTH;
        Display_height = PANEL_HEIGHT;
        MenuInitialize10inch();
        /*Initialize Top Menu*/
        Top_menu[0] = &Top_button_1;
        Top_menu[1] = &Page_button;
        Top_menu[2] = &Dummy_button;
        Top_menu[3] = &Top_button_4;
        Top_menu[4] = &Top_button_5;
        Top_menu[5] = &Top_button_6;
        Top_menu[6] = &Timer_button;
        Top_menu[7] = &Brightness_button;
        Top_menu[8] = ZERO;
    }
    else if (E_3_INCH == Display_size)
    {
        /* hdudispfmenu2-MenuInitialize-DB-LLR-003 */
        Display_width = PANEL_WIDTH;
        Display_height = PANEL_HEIGHT;

    }
    else
    {
    	; /* Do Nothing */
    }
}
