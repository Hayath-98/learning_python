/*
 ******************************************************************************
 * License Information  :  Howell Instruments, Inc.                           *
 *                         "Licensed Software" and "All rights reserved".     *
 ******************************************************************************
 *  File                : hdudispfmenu.h
 *
 *  Description         : Contains routines for all the menu options in the display
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
 *      1.1          Rona B.S         13-Sep-2017             100064
 *      1.2          Shruthi M N      12-Oct-2017             100073,100083,100087
 *      1.3          Shruthi M N      30-Oct-2017             100104
 *      1.4          Divya G P        03-Nov-2017             100156
 *      1.5          Rona B S         01-Jul-2020             100259
 *      1.6         Dhanalakshmi      05-Aug-2020             100270
 *      1.7         Dhanalakshmi      12-Sep-2020             100276
 *      1.8         Rona B S          28-Sep-2020             100284
 *      1.9         Dhanalakshmi     20-Mar-2021             100331
 *      1.10        Dhanalakshmi     20-Mar-2021             100331
 *
 * Additional References : None
 *
 ******************************************************************************
 */

#ifndef _HDUDISPFMENU_H_
#define _HDUDISPFMENU_H_

#include "hdudispftextbox.h"      /* routines for text box draw and updtaes */
#include "hdudispftimer.h"        /* increment a set of user installed timers. */
#include "hdudispfpara.h"         /* prototype for builds faults, message and system information */

#define NUMBEROFENGINES           4U
#define OFFSET_LENGTH             3U
#define GAIN_LENGTH               5U

extern void CoolTimerReset(void);
extern void CoolTimerStart(void);
extern void ManualTimerInit(void);
extern void OffsideManualTimerReset(void);
extern void OffsideManualTimerStart(T_UINT32 u32_start_val) ;
extern void OffsideManualTimerStop(T_UINT32 u32_stop_val);
extern void MenuInitialize();
extern T_CHAR *EncoderCoolDownItemSelectText(void);
extern T_CHAR *FuelFlowOnOffButtonText(void);
extern T_CHAR* SysInfoBoxText(void);
extern T_CHAR *EncoderMenuItemSelectText(void);
extern T_CHAR *MenuItemSelectText10Inch(void);
extern T_CHAR *CalibrationSelectText10Inch(void);
extern T_CHAR *EngCalibrationSelectTxt10Inch(void);
extern T_CHAR *ParamCalibriSlctTxt10Inch(void);
extern T_CHAR *OffsetValueText(void);
extern T_CHAR *GainValueText(void);
extern T_CHAR* EncoderPageItemSelectText(void);
extern T_CHAR* ButtonPageItemSelectText(void);
extern T_CHAR *MessageBoxText(void);
extern T_CHAR *ExitButtonText(void);
extern T_CHAR *BackButtonText(void);
extern T_CHAR *ScrollButtonText(void);
extern T_CHAR *CoolDownOnOffButtonText(void);
extern T_CHAR *ManTimerOnOffText(void);
extern T_CHAR *ManualTimerResetButtonText(void);
extern T_CHAR *DummyButtonText(void);
extern T_CHAR *SetButtonText(void);
extern T_CHAR *TopButton1Text(void);
extern T_CHAR *TopButton2Text10Inch(void);
extern T_CHAR *TopButton3Text10Inch(void);
extern T_CHAR *TopButton4Text(void);
extern T_CHAR *TopButton4Text10Inch(void);
extern T_CHAR *TopButton5Text(void);
extern T_CHAR *TopButton6Text(void);
extern T_CHAR *TopButton7Text(void);
extern T_CHAR *TopButton8Text(void);
extern T_CHAR *PageButtonText(void);
extern T_CHAR *TopButton10Text(void);
extern T_CHAR *TopButton6Text10Inch(void);
extern T_CHAR *TopButton7Text10Inch(void);
extern T_CHAR *TopButton13Text(void);
extern T_CHAR *TopButton8Text10Inch(void);
extern T_CHAR *NextBoxText(void);
/* updated for PR 100083 */
extern void MenuReset(T_STEXTBOXDATA **pps_items, T_EPAGE_NUM page_num);

extern void MenuInit();
extern void PageMenu(T_EPAGE_NUM back_grnd_page_num);
/* updated for PR 100083 */
extern void CoolTimerMaint(void);

extern void OffsetInttoIntArray(T_UINT8 sdi);
extern void GainInttoIntArray(T_UINT8 sdi);

extern void FloatToString ( T_FLOAT value, T_CHAR *str,T_UINT8 bit_size);

extern T_TIMER Manual_timer;
extern T_TIMER Cool_timer;
extern T_STEXTBOXDATA *Top_menu[];
extern T_STEXTBOXDATA *Timer_menu[];
extern T_STEXTBOXDATA *Menu_menu[];
extern T_STEXTBOXDATA *Menu_menu_10inch[];
extern T_STEXTBOXDATA *Page_menu[];
extern T_STEXTBOXDATA *Page_menu_1[];
extern T_STEXTBOXDATA *Page_menu_10inch[];
extern T_STEXTBOXDATA *Page_menu_10inch_1[];
extern T_STEXTBOXDATA *Msg_menu[];
extern T_STEXTBOXDATA *Cool_down_menu[];
extern T_STEXTBOXDATA *Fuel_flow[];
extern T_STEXTBOXDATA *Sys_info_menu[];
extern T_STEXTBOXDATA *Sys_info_menu_10inch[];
extern T_STEXTBOXDATA *Brightness_menu[];
extern T_STEXTBOXDATA *All_menu_items[];
extern T_STEXTBOXDATA Encoder_menu_select;
extern T_STEXTBOXDATA Menu_select_10inch;
extern T_STEXTBOXDATA Encoder_page_select;
extern T_STEXTBOXDATA Button_page_select;
extern T_STEXTBOXDATA Message_text_box;
extern T_STEXTBOXDATA Exit_button;
extern T_STEXTBOXDATA Back_button;
extern T_STEXTBOXDATA Scroll_button;
extern T_STEXTBOXDATA Cool_down_on_off_btn;
extern T_STEXTBOXDATA Man_timer_on_off_btn;
extern T_STEXTBOXDATA Manual_timer_reset_btn;
extern T_STEXTBOXDATA Dummy_button;
extern T_STEXTBOXDATA Set_button;
extern T_STEXTBOXDATA Top_button_1;
extern T_STEXTBOXDATA Top_button_2;
extern T_STEXTBOXDATA Top_button_3;
extern T_STEXTBOXDATA Top_button_4;
extern T_STEXTBOXDATA Top_button_5;
extern T_STEXTBOXDATA Top_button_6;
extern T_STEXTBOXDATA Timer_button;
extern T_STEXTBOXDATA Page_button;
extern T_STEXTBOXDATA Top_button_10;
extern T_STEXTBOXDATA Top_button_minus;
extern T_STEXTBOXDATA Top_button_plus;
extern T_STEXTBOXDATA Brightness_button;
extern T_STEXTBOXDATA Fuel_flow_message;
extern T_STEXTBOXDATA Sys_info_message_box;
extern T_STEXTBOXDATA Encoder_cool_down_select;
extern T_STEXTBOXDATA Calibration_box;
extern T_STEXTBOXDATA Engine_calibration_box;
extern T_STEXTBOXDATA Parameter_calibration_box;
extern T_STEXTBOXDATA Next_box;
extern T_STEXTBOXDATA Offset_box;
extern T_STEXTBOXDATA Gain_box;

extern T_CHAR Menu_text[5];
extern T_CHAR Page_text[5];
extern T_CHAR Msgs_text[9];
extern T_CHAR Cool_down_timer_text[14];
extern T_CHAR Fuel_flow_text[9];
extern T_CHAR Sys_info_text[9];
extern T_CHAR Exit_text[5];
extern T_CHAR Back_text[5];
extern T_CHAR Scroll_text[6];
extern T_CHAR On_text[3];
extern T_CHAR Off_text[4];
extern T_CHAR Stop_text[5];
extern T_CHAR Strt_text[5];
extern T_CHAR Rst_text[4];
extern T_CHAR Err_text[4];
extern T_CHAR Rev_text[4];
extern T_CHAR Msg_text[4];
extern T_CHAR Eiu1_text[5];
extern T_CHAR Eiu2_text[5];
extern T_CHAR Tmr_text[4];
extern T_CHAR Min_text[4];
extern T_CHAR Max_text[4];
extern T_CHAR Brt_aut_text[8];
extern T_CHAR Brt_man_text[8];
extern T_CHAR Brt_minus_text[2];
extern T_CHAR Brt_plus_text[2];
extern T_CHAR Brt_set_text[4];
extern T_CHAR Set_text[8];
extern T_CHAR Menu_up[2];
extern T_CHAR Menu_down[5];
extern T_CHAR Engine_text[7];
extern T_CHAR Engine_calibration_text[8];
extern T_CHAR Invalid_screen_number_text[22];
extern T_CHAR Next_text[5];
extern T_CHAR Offset_text[6];
extern T_CHAR Gain_text[13];

/* Updtaed as per 100073 */
extern T_CHAR  Encoder_page_text[360];
/* updated for PR 100083 */
extern T_BOOL Cool_down_select;
extern T_BOOL Fuel_flow_select;
extern T_FLOAT Fuel_flow_data;
extern T_UINT8 Ff_a429_tag;
extern T_RTD_STATUS Ff_status;

extern T_EPAGE_NUM Toggle_screen;
extern T_UINT8 Page_number;

extern T_UINT16 Display_width;
extern T_UINT16 Display_height;

extern T_UINT32 Offset_value_cal[NUMBEROFENGINES];
extern T_UINT32 Gain_value_cal[NUMBEROFENGINES];

extern T_UINT16 Offset_value[NUMBEROFENGINES][OFFSET_LENGTH];
extern T_UINT16 Gain_value[NUMBEROFENGINES][GAIN_LENGTH];

/* added for 20 page bitmap check  */
extern T_BOOL Bitmap_crc_check_bit[20];

extern T_UINT8 Cmu_fuel_flow;

/*#define DISPLAY_WIDTH               480 */

/*#define DISPLAY_HEIGHT              800 */

#define DIVIDER_WIDTH               2

#define SMALL_FONT_WIDTH            13
#define SMALL_FONT_HEIGHT           22

#define NORMAL_FONT_WIDTH           16
#define NORMAL_FONT_HEIGHT          30
#define USABLE_LRX                  480
#define USABLE_LRY                  770
#define USABLE_LRX_10INCH           768
#define USABLE_LRY_10INCH           1014

#define SIDE_BB_FONT                E_SMALL_FONT
#define SIDE_BB_CHAR_WIDTH          SMALL_FONT_WIDTH
#define  SIDE_BB_CHAR_HEIGHT           SMALL_FONT_HEIGHT
#define SIDE_BB_OUTSIDE_BORDER      8
#define SIDE_BB_INSIDE_BORDER       5

/* updated for PR 100083 */
#define SIDE_BB_HEIGHT              90        /*was 94 */
#define SIDE_BB_HEIGHT_SM           90       /* Only for timer_reset button */

#define SIDE_BB_WIDTH               (SIDE_BB_OUTSIDE_BORDER+SIDE_BB_CHAR_WIDTH)
/*#define SIDE_BB_ULX                 (DISPLAY_WIDTH-SIDE_BB_WIDTH) */


#define SIDE_BB_DELTAY              (SIDE_BB_HEIGHT+DIVIDER_WIDTH)

/* updated for PR 100083 */
#define SIDE_BB_OFFSET                 44
#define SIDE_BB_ULY1                SIDE_BB_OFFSET      /*was 0 */
#define SIDE_BB_ULY2                SIDE_BB_DELTAY+SIDE_BB_OFFSET
#define SIDE_BB_ULY3                (2*SIDE_BB_DELTAY)+SIDE_BB_OFFSET
#define SIDE_BB_ULY4                (3*SIDE_BB_DELTAY)+SIDE_BB_OFFSET
#define SIDE_BB_ULY5                (4*SIDE_BB_DELTAY)+SIDE_BB_OFFSET
#define SIDE_BB_ULY6                (5*SIDE_BB_DELTAY)+SIDE_BB_OFFSET
#define SIDE_BB_ULY7                (6*SIDE_BB_DELTAY)+SIDE_BB_OFFSET


#define BOTTOM_BB_FONT              E_BEZEL_FONT
#define BOTTOM_BB_CHAR_HEIGHT       18

#define BOTTOM_BB_OUTSIDE_BORDER    4
#define BOTTOM_BB_INSIDE_BORDER     4

#define BOTTOM_BB_HEIGHT            (BOTTOM_BB_CHAR_HEIGHT+BOTTOM_BB_OUTSIDE_BORDER)
/*#define BOTTOM_BB_WIDTH             ((DISPLAY_WIDTH/5)-1) */

/*#define BOTTOM_BB_ULY               (DISPLAY_HEIGHT-BOTTOM_BB_HEIGHT)*/

#define BOTTOM_BB_OUTSIDE_BORDER_10  2
#define BOTTOM_BB_INSIDE_BORDER_10   2

#define BOTTOM_BB_HEIGHT_10INCH     24
#define BOTTOM_BB_WIDTH_10INCH      109

#define BOTTOM_BB_EDGE_OFFSET       10

#define BOTTOM_BB_DELTAX            (BOTTOM_BB_WIDTH+DIVIDER_WIDTH)

#define BOTTOM_BB_DELTAX_10INCH     (BOTTOM_BB_WIDTH_10INCH+DIVIDER_WIDTH)

#define BOTTOM_BB_ULX1              0
#define BOTTOM_BB_ULX5              (4*BOTTOM_BB_DELTAX)

#define BOTTOM_BB_ULX1_10INCH      (BOTTOM_BB_EDGE_OFFSET+BOTTOM_BB_OUTSIDE_BORDER_10)

#define BOTTOM_BB_ULX2_10INCH       (BOTTOM_BB_EDGE_OFFSET+BOTTOM_BB_WIDTH_10INCH+\
									(2*BOTTOM_BB_OUTSIDE_BORDER_10))
#define BOTTOM_BB_ULX3_10INCH       (BOTTOM_BB_EDGE_OFFSET+(2*BOTTOM_BB_WIDTH_10INCH)+\
									(3*BOTTOM_BB_OUTSIDE_BORDER_10))
#define BOTTOM_BB_ULX4_10INCH       (BOTTOM_BB_EDGE_OFFSET+(3*BOTTOM_BB_WIDTH_10INCH)+\
									(3*BOTTOM_BB_OUTSIDE_BORDER_10))+1
#define BOTTOM_BB_ULX5_10INCH       (BOTTOM_BB_EDGE_OFFSET+(5*BOTTOM_BB_WIDTH_10INCH)+\
									(8*BOTTOM_BB_OUTSIDE_BORDER_10))+1
#define BOTTOM_BB_ULX6_10INCH       (BOTTOM_BB_EDGE_OFFSET+(6*BOTTOM_BB_WIDTH_10INCH)+\
									(9*BOTTOM_BB_OUTSIDE_BORDER_10))+1
#define BOTTOM_BB_ULX7_10INCH       (BOTTOM_BB_EDGE_OFFSET+(7*BOTTOM_BB_WIDTH_10INCH)+\
									(10*BOTTOM_BB_OUTSIDE_BORDER_10))+1
#define BOTTOM_BB_ULX8_10INCH       (BOTTOM_BB_EDGE_OFFSET+(8*BOTTOM_BB_WIDTH_10INCH)+\
									(11*BOTTOM_BB_OUTSIDE_BORDER_10))


#define BUTT_TEXT_COLOR             WHITE

#define LISTBOX_FONT                E_TINY_FONT
#define LISTBOX_CHAR_WIDTH          11
#define LISTBOX_CHAR_HEIGHT         18
#define LISTBOX_BKGND_COLOR         DARK_BLUE
#define LISTBOX_TEXT_COLOR          WHITE
#define LISTBOX_FRAME_COLOR         WHITE
#define LISTBOX_FRAME_WIDTH         2

#define ACTION_COLOR                BLUE
#define MENU_COLOR                  DARK_BLUE
#define MAX_MENU_DEPTH              7
/* updated for PR 100083*/
#define MENU_TIME                   10000
#define MIN_MAX_ITTR                25

#define COOL_DOWN_LIST_CHARS           13
#define COOL_DOWN_LIST_ITEMS           2
#define COOL_DOWN_LIST_WIDTH           (COOL_DOWN_LIST_CHARS*NORMAL_FONT_WIDTH)
#define COOL_DOWN_LIST_HEIGHT          (COOL_DOWN_LIST_ITEMS+2)*(NORMAL_FONT_HEIGHT-5)
#define COOL_DOWN_LIST_FRAME_WIDTH     3
#define COOL_DOWN_LIST_MARGIN          10
#define COOL_DOWN_LIST_ULX             \
        (USABLE_LRX-COOL_DOWN_LIST_WIDTH-COOL_DOWN_LIST_FRAME_WIDTH-COOL_DOWN_LIST_MARGIN)
#define COOL_DOWN_LIST_ULY             \
        (USABLE_LRY-COOL_DOWN_LIST_HEIGHT-COOL_DOWN_LIST_FRAME_WIDTH-COOL_DOWN_LIST_MARGIN)


#define COOL_DOWN_LIST_ULX_10INCH             \
        (USABLE_LRX_10INCH-COOL_DOWN_LIST_WIDTH-COOL_DOWN_LIST_FRAME_WIDTH-COOL_DOWN_LIST_MARGIN)

#define COOL_DOWN_LIST_ULY_10INCH             \
        (USABLE_LRY_10INCH-COOL_DOWN_LIST_HEIGHT-COOL_DOWN_LIST_FRAME_WIDTH-COOL_DOWN_LIST_MARGIN)
/* updated for PR 100083*/
#define SYSINFO_FONT                   E_SMALL_FONT
#define SYSINFO_CHAR_WIDTH             13
#define SYSINFO_CHAR_HEIGHT            22
#define SYSINFO_BKGND_COLOR            DARK_BLUE
#define SYSINFO_TEXT_COLOR             WHITE
#define SYSINFO_FRAME_COLOR            WHITE
#define SYSINFO_FRAME_WIDTH            2
#define SYSINFO_MARGIN                 5
#define SYSINFO_BOX_ULX                18
/* updated for PR 100083*/
#define SYSINFO_BOX_ULY                200
#define SYSINFO_BOX_WIDTH              32 *SYSINFO_CHAR_WIDTH
/* updated for PR 100083*/
#define SYSINFO_BOX_HEIGHT             22*(SYSINFO_CHAR_HEIGHT-3)
#define MENU_LIST_CHARS                15
#define MENU_LIST_ITEMS                2
#define MENU_LIST_ITEMS_FF             3
#define MENU_LIST_WIDTH                (MENU_LIST_CHARS*NORMAL_FONT_WIDTH)
/* Updated for PR 100083 */
#define MENU_LIST_HEIGHT               (MENU_LIST_ITEMS+1)*NORMAL_FONT_HEIGHT
#define MENU_LIST_FRAME_WIDTH 3
#define MENU_LIST_MARGIN               10
#define MENU_LIST_COLOR                DARK_BLUE
#define MENU_LIST_ULX                  (USABLE_LRX-MENU_LIST_WIDTH-MENU_LIST_FRAME_WIDTH- \
                                                 MENU_LIST_MARGIN)
#define MENU_LIST_ULY                  (USABLE_LRY-MENU_LIST_HEIGHT-MENU_LIST_FRAME_WIDTH- \
                                                 MENU_LIST_MARGIN)

#define MENU_LIST_ULX_10INCH           (USABLE_LRX_10INCH-MENU_LIST_WIDTH-MENU_LIST_FRAME_WIDTH- \
                                                 MENU_LIST_MARGIN)
#define MENU_LIST_ULY_10INCH           (USABLE_LRY_10INCH-MENU_LIST_HEIGHT-MENU_LIST_FRAME_WIDTH- \
                                                 MENU_LIST_MARGIN)

#define PAGE_LIST_CHARS                9
#define PAGE_LIST_ITEMS                2
#define PAGE_LIST_WIDTH                (PAGE_LIST_CHARS*NORMAL_FONT_WIDTH)
/* Updated for PR 100083 */
#define PAGE_LIST_HEIGHT               (PAGE_LIST_ITEMS+1)*(NORMAL_FONT_HEIGHT-5)
#define PAGE_LIST_FRAME_WIDTH 3
#define PAGE_LIST_MARGIN               10
#define PAGE_LIST_COLOR                DARK_BLUE /*0x444*/
#define PAGE_LIST_ULX                  (USABLE_LRX-PAGE_LIST_WIDTH-PAGE_LIST_FRAME_WIDTH-\
                                                     PAGE_LIST_MARGIN)
#define PAGE_LIST_ULY                  (USABLE_LRY-PAGE_LIST_HEIGHT-PAGE_LIST_FRAME_WIDTH- \
                                                     PAGE_LIST_MARGIN)

#define PAGE_LIST_ULX_10INCH           (USABLE_LRX_10INCH-PAGE_LIST_WIDTH-PAGE_LIST_FRAME_WIDTH-\
                                                     PAGE_LIST_MARGIN)
#define PAGE_LIST_ULY_10INCH           (USABLE_LRY_10INCH-PAGE_LIST_HEIGHT-PAGE_LIST_FRAME_WIDTH- \
                                                     PAGE_LIST_MARGIN)
#define PAGE_LIST_10INCH_WIDTH   465
#define PAGE_LIST_10INCH_HEIGHT  295

#define MESSAGE_BOX_ULX          23
#define MESSAGE_BOX_ULY          337
#define MESSAGE_BOX_WIDTH        37 *LISTBOX_CHAR_WIDTH
#define FUEL_FLOW_LIST_ITEMS           2
/* Updated for PR 100083 */
#define MESSAGE_BOX_HEIGHT       4*LISTBOX_CHAR_HEIGHT

extern T_UINT32 Loop_textbox;

extern T_CHAR Ff_text[12];

#endif /* _HDUDISPFMENU_H_ */
