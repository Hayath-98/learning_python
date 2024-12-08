/*
 ******************************************************************************
 * License Information  :  Howell Instruments, Inc.                           *
 *                         "Licensed Software" and "All rights reserved".     *
 ******************************************************************************
 *  File                : hdudispfmenu.c
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
 *      1.1          Rona B.S         13-Sep-2017             100064
 *      1.2          Rajalakshmi S    10-Oct-2017             100064
 *      1.3          Shruthi M N      13-Oct-2017             100083,100087
 *      1.4          Shruthi M N      30-Oct-2017             100104
 *      1.5          Shruthi M N,
 *                   Divya G P        04-Nov-2017             100156
 *      1.6          Divya G P        08-Nov-2017             100164
 *      1.7          Dhanalakshmi D   21-Jun-2020             100259
 *      1.8          Rona B S  		  30-Jun-2020             100259
 *      1.9          Rona B S  		  24-Jul-2020             100259
 *      1.10         Dhanalakshmi     05-Aug-2020             100270
 *      1.11         Dhanalakshmi     12-Sep-2020             100276
 *      1.12         Dhanalakshmi     20-Mar-2021             100331
 *      1.13         Dhanalakshmi     20-Mar-2021             100331
 *      1.14         Dhanalakshmi     03-Apr-2021             100330
 *      1.15         Dhanalakshmi     16-Apr-2021             100339
 *      1.16         Dhanalakshmi     24-Apr-2021             100344
 *      1.17         Dhanalakshmi     13-May-2021             100350
 *
 * Additional References : None
 *
 ******************************************************************************
 */

#include "hdudispfglobalsettings.h"  /* Routines to read and write data to NVRAM  */
#include "hdudispfgrapp.h"           /* routines for all graph */
#include "hdudispfmenu.h"            /* contains prototype for menu module*/
#include "hdudispfoffside.h"         /* contains prototype for offside modules*/
#include "hdudispfpbs.h"             /* Contains functions prototypes of pbs.*/
#include "hdudispfpdidata.h"         /* contains routines for PDI data */
#include "hdudispfpwm.h"             /* Contains functions prototypes of pwm.*/
#include "hdudispfrterror.h"           /* Provides sub routine for run time errors.*/
#include "hdudispftextbox.h"         /* routines for text box draw and updates */
#include "hdudispftimer.h"           /* increment a set of user installed timers. */

#include "hdudispfpanel.h"           /* Contains functions prototypes of panel.*/
#include "hdudispfconfig.h"          /* contains page and color config information */
#include "hdudispfpara.h"  /* prototype for builds faults, message and system information */
#include "hdulibbasictypes.h"      /* Contains basic header definations */
#include "hdudispfa429.h"          /* provides a429 functionalities */
#include "hdudispfucos.h"          /* provides ucos functionalities */
#include "hdudispfoffside.h"  /* Screen, message and timer configuration */
#include "hdudispfpdicheck.h" /*contains pdi check*/
#include "hdudispfforeground.h"  /* contains the routines for foreground layer of the display */
#include "hdudispfpbit.h" /*contains Pbit check*/

#define DEC_EIGHT         8U
#define DEC_NINE          9U
#define DEC_ELEVEN        11U
#define DEC_TWELVE        12U
#define DEC_THIRTEEN      13U
#define DEC_FOURTEEN      14U
#define MASK_VAL          0x7F

/*
 * Variables to suppress compiler warning for option -Wcast-qual.
 */

T_CHAR Menu_text[5] = "MENU";
T_CHAR Page_text[5] = "PAGE";
T_CHAR Msgs_text[9] = "MESSAGES";
T_CHAR Cool_down_timer_text[14] = "COOL DOWN TMR";
T_CHAR Fuel_flow_text[9] = "FUEL FLOW";
T_CHAR Sys_info_text[9] = "SYS INFO";
T_CHAR Exit_text[5] = "EXIT";
T_CHAR Back_text[5] = "BACK";
T_CHAR Scroll_text[6] = "SCROLL";
T_CHAR On_text[3] = "ON";
T_CHAR Off_text[4] = "OFF";
T_CHAR Stop_text[5] = "STOP";
T_CHAR Strt_text[5] = "STRT";
T_CHAR Rst_text[4] = "RST";
T_CHAR Err_text[4] = "ERR";
T_CHAR Rev_text[4] = "REV";
T_CHAR Msg_text[4] = "MSG";
T_CHAR Eiu1_text[5] = "EIU1";
T_CHAR Eiu2_text[5] = "EIU2";
T_CHAR Tmr_text[4] = "TMR";
T_CHAR Min_text[4] = "MIN";
T_CHAR Max_text[4] = "MAX";
T_CHAR Brt_aut_text[8] = "BRT:AUT";
T_CHAR Brt_man_text[8] = "BRT:MAN";
T_CHAR Brt_minus_text[2] = "-";
T_CHAR Brt_plus_text[2] = "+";
T_CHAR Menu_up[2] = "UP";
T_CHAR Menu_down[5] = "DOWN";
T_CHAR Brt_set_text[4] = "SET";
T_CHAR Set_text[8] = "ENT/SET";
T_CHAR Engine_text[7] = "ENGINE";
T_CHAR Engine_calibration_text[8] = "ENGINE";
T_CHAR Offset_text[6] = "MIN Q";
T_CHAR Gain_text[13] = "SHAFT FACTOR";
T_CHAR Invalid_screen_number_text[22] = "Invalid Screen Number";
T_CHAR Next_text[5] = "NEXT";

/* added for 20 page bitmap check  */
T_BOOL Bitmap_crc_check_bit[20] = {FALSE, FALSE, FALSE, FALSE,
		   FALSE, FALSE, FALSE, FALSE,
		   FALSE, FALSE, FALSE, FALSE,
		   FALSE, FALSE, FALSE, FALSE,
		   FALSE, FALSE};
T_STEXTBOXDATA Encoder_menu_select =
{
	0, 0, 0, 0, 0,
	0, 0, 0, 0,
	0, 0, 0, (T_CHAR *)0,(T_PSTEXTBOX)0
};

T_STEXTBOXDATA Menu_select_10inch =
{
	0, 0, 0, 0, 0,
	0, 0, 0, 0,
	0, 0, 0, (T_CHAR *)0,(T_PSTEXTBOX)0
};

T_CHAR Ff_text[12] = "FF     PPH ";
static T_TIMER Manual_timer_mirror = 0;
static T_TIMER Menu_timer = 0;
static T_TIMER Cool_timer_mirror = 0;
/* Updated for PR 100083 */
static T_INT16 Message_cnt = 0;

typedef enum
{
   MAN_TIMER_OFF,
   MAN_TIMER_ON
} T_MAN_TIMER_STATE;

static T_MAN_TIMER_STATE Man_timer_state = MAN_TIMER_OFF;

static T_STEXTBOXDATA **Pps_menu_stack[MAX_MENU_DEPTH+1] = {ZERO};

static T_INT16 S16_menu_stack_pointer = MAX_MENU_DEPTH;

static T_INT16 S16_sys_info_index = ZERO;

static T_UINT8 U8_selected_menu_item = ZERO;

static T_UINT8 U8_selected_menu_item_10inch = ZERO;

static T_UINT8 U8_selected_engine_item_10inch = ZERO;

static T_UINT8 U8_selected_engine_offset_gain = ZERO;

/* static T_UINT8 U8_selected_engine_parameter = ZERO; */

static T_UINT8 U8_selected_page_item = 0;

static T_INT16 S16_message_index = 0;

T_CHAR  Encoder_cool_down_text[] = "TIMER ON\r\nTIMER OFF";
T_CHAR  Encoder_fuel_flow_text[] = "FUEL FLOW ON\r\nFUEL FLOW OFF";

T_TIMER Manual_timer = 0;

T_TIMER Cool_timer = 0;

T_CHAR  Encoder_menu_text[] = "COOL DOWN TIMER\r\nSYS INFORMATION";
T_CHAR  Encoder_menu_text_ff[] = "COOL DOWN TIMER\r\nSYS INFORMATION\r\nFUEL FLOW";
T_CHAR  Menu_text_10inch[] = "CALIBRATION\r\nSYS INFORMATION";
T_CHAR  Calibration_text_10inch[] = "ENG 1\r\nENG 2\r\nENG 3\r\nENG 4";
T_CHAR  Parameter_text[] = "EOT\r\nFAT";
T_CHAR  Offsetgain_text[] = "MIN Q\r\nSHAFT FACTOR";
/* MIN Q - Offset SHAFT FACTOR - Gain */

T_UINT8 Engine_count = ZERO;

T_UINT16 Offset_value[NUMBEROFENGINES][OFFSET_LENGTH] = {0};
T_UINT16 Gain_value[NUMBEROFENGINES][GAIN_LENGTH]= {0};

    /* Offset/gain value array of string to display */
T_CHAR Offset_value_string[NUMBEROFENGINES][OFFSET_LENGTH+1] = {0};
T_CHAR Gain_value_string[NUMBEROFENGINES][GAIN_LENGTH+1] = {0};

    /*offset/gain value int used for transmit*/
T_UINT32 Offset_value_cal[NUMBEROFENGINES] = {0};
T_UINT32 Gain_value_cal[NUMBEROFENGINES] = {0};

    /* Digit of offset/gain to be changed*/
T_UINT8 Offset_digit[NUMBEROFENGINES] = {0};
T_UINT8 Gain_digit[NUMBEROFENGINES] = {0};

/* CMU “FUEL FLOW” is enable/disable status */
T_UINT8 Cmu_fuel_flow =0;

/* updated as PR 100083 */
T_CHAR  Encoder_page_text[360] = "";

T_STEXTBOXDATA Encoder_page_select =
{
   0, 0, 0, 0, 0,
   0, 0, 0, 0,
   0, 0, 0, (T_CHAR *)0,(T_PSTEXTBOX)0
};

T_STEXTBOXDATA Button_page_select =
{
   0, 0, 0, 0, 0,
   0, 0, 0, 0,
   0, 0, 0, (T_CHAR *)0,(T_PSTEXTBOX)0
};
/* Updated for PR 100083 */
T_STEXTBOXDATA Message_text_box =
{
	0, 0, 0, 0, 0,
	0, 0, 0, 0,
	0, 0, 0, (T_CHAR *)0,(T_PSTEXTBOX)0
};

T_STEXTBOXDATA Exit_button =
{
	0, 0, 0, 0, 0,
	0, 0, 0, 0,
	0, 0, 0, (T_CHAR *)0,(T_PSTEXTBOX)0
};

T_STEXTBOXDATA Back_button =
{
	0, 0, 0, 0, 0,
	0, 0, 0, 0,
	0, 0, 0, (T_CHAR *)0,(T_PSTEXTBOX)0
};

/* Updated for PR 100083 */
T_STEXTBOXDATA Scroll_button =
{
	0, 0, 0, 0, 0,
	0, 0, 0, 0,
	0, 0, 0, (T_CHAR *)0,(T_PSTEXTBOX)0
};

T_STEXTBOXDATA Cool_down_on_off_btn =
{
	0, 0, 0, 0, 0,
	0, 0, 0, 0,
	0, 0, 0, (T_CHAR *)0,(T_PSTEXTBOX)0
};

T_STEXTBOXDATA Man_timer_on_off_btn =
{
	0, 0, 0, 0, 0,
	0, 0, 0, 0,
	0, 0, 0, (T_CHAR *)0,(T_PSTEXTBOX)0
};

/* Updated for PR 100083 */
T_STEXTBOXDATA Manual_timer_reset_btn =
{
	0, 0, 0, 0, 0,
	0, 0, 0, 0,
	0, 0, 0, (T_CHAR *)0,(T_PSTEXTBOX)0
};

T_STEXTBOXDATA Dummy_button =
{
	0, 0, 0, 0, 0,
	0, 0, 0, 0,
	0, 0, 0, (T_CHAR *)0,(T_PSTEXTBOX)0
};


T_STEXTBOXDATA Set_button =
{
	0, 0, 0, 0, 0,
	0, 0, 0, 0,
	0, 0, 0, (T_CHAR *)0,(T_PSTEXTBOX)0
};
T_STEXTBOXDATA Top_button_1 =
{
	0, 0, 0, 0, 0,
	0, 0, 0, 0,
	0, 0, 0, (T_CHAR *)0,(T_PSTEXTBOX)0
};

T_STEXTBOXDATA Top_button_2 =
{
	0, 0, 0, 0, 0,
	0, 0, 0, 0,
	0, 0, 0, (T_CHAR *)0,(T_PSTEXTBOX)0
};

T_STEXTBOXDATA Top_button_3 =
{
	0, 0, 0, 0, 0,
	0, 0, 0, 0,
	0, 0, 0, (T_CHAR *)0,(T_PSTEXTBOX)0
};
T_STEXTBOXDATA Top_button_4 =
{
	0, 0, 0, 0, 0,
	0, 0, 0, 0,
	0, 0, 0, (T_CHAR *)0,(T_PSTEXTBOX)0
};

T_STEXTBOXDATA Top_button_5 =
{
	0, 0, 0, 0, 0,
	0, 0, 0, 0,
	0, 0, 0, (T_CHAR *)0,(T_PSTEXTBOX)0
};

T_STEXTBOXDATA Top_button_6 =
{
	0, 0, 0, 0, 0,
	0, 0, 0, 0,
	0, 0, 0, (T_CHAR *)0,(T_PSTEXTBOX)0
};
T_STEXTBOXDATA Timer_button =
{
	0, 0, 0, 0, 0,
	0, 0, 0, 0,
	0, 0, 0, (T_CHAR *)0,(T_PSTEXTBOX)0
};

/* Updated for PR 100083 */
T_STEXTBOXDATA Page_button =
{
	0, 0, 0, 0, 0,
	0, 0, 0, 0,
	0, 0, 0, (T_CHAR *)0,(T_PSTEXTBOX)0
};

T_STEXTBOXDATA Top_button_minus =
{
	0, 0, 0, 0, 0,
	0, 0, 0, 0,
	0, 0, 0, (T_CHAR *)0,(T_PSTEXTBOX)0
};

T_STEXTBOXDATA Top_button_plus =
{
	0, 0, 0, 0, 0,
	0, 0, 0, 0,
	0, 0, 0, (T_CHAR *)0,(T_PSTEXTBOX)0
};
/* Updated for PR 100083 */
T_STEXTBOXDATA Brightness_button =
{
	0, 0, 0, 0, 0,
	0, 0, 0, 0,
	0, 0, 0, (T_CHAR *)0,(T_PSTEXTBOX)0
};

T_STEXTBOXDATA Fuel_flow_message =
{
	0, 0, 0, 0, 0,
	0, 0, 0, 0,
	0, 0, 0, (T_CHAR *)0,(T_PSTEXTBOX)0
};

T_STEXTBOXDATA Sys_info_message_box =
{
	0, 0, 0, 0, 0,
	0, 0, 0, 0,
	0, 0, 0, (T_CHAR *)0,(T_PSTEXTBOX)0
};

T_STEXTBOXDATA Encoder_cool_down_select =
{
	0, 0, 0, 0, 0,
	0, 0, 0, 0,
	0, 0, 0, (T_CHAR *)0,(T_PSTEXTBOX)0
};

T_STEXTBOXDATA Calibration_box =
{
	0, 0, 0, 0, 0,
	0, 0, 0, 0,
	0, 0, 0, (T_CHAR *)0,(T_PSTEXTBOX)0
};

T_STEXTBOXDATA Engine_calibration_box =
{
	0, 0, 0, 0, 0,
	0, 0, 0, 0,
	0, 0, 0, (T_CHAR *)0,(T_PSTEXTBOX)0
};

T_STEXTBOXDATA Parameter_calibration_box =
{
	0, 0, 0, 0, 0,
	0, 0, 0, 0,
	0, 0, 0, (T_CHAR *)0,(T_PSTEXTBOX)0
};


T_STEXTBOXDATA Next_box =
{
	0, 0, 0, 0, 0,
	0, 0, 0, 0,
	0, 0, 0, (T_CHAR *)0,(T_PSTEXTBOX)0
};

T_STEXTBOXDATA Offset_box =
{
	0, 0, 0, 0, 0,
	0, 0, 0, 0,
	0, 0, 0, (T_CHAR *)0,(T_PSTEXTBOX)0
};

T_STEXTBOXDATA Gain_box =
{
    0, 0, 0, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, (T_CHAR *)0,(T_PSTEXTBOX)0
};

T_STEXTBOXDATA *All_menu_items[] =
{
   &Dummy_button,
   &Exit_button,
   &Back_button,
   &Scroll_button,
   &Cool_down_on_off_btn,
   &Man_timer_on_off_btn,
   &Manual_timer_reset_btn,
   &Top_button_1,
   &Dummy_button,
   &Top_button_4,
   &Top_button_5,
   &Top_button_6,
   &Timer_button,
   &Page_button,
   &Brightness_button,
   &Fuel_flow_message,
   &Encoder_menu_select,
   &Encoder_page_select,
   &Button_page_select,
   &Dummy_button,
   &Message_text_box,
   &Encoder_cool_down_select,
   /* Updated for PR 100083 */
   &Prim_cool_down_pop_up_box,
   &Sys_info_message_box,
   &Top_button_2,
   &Top_button_3,
   &Top_button_minus,
   &Top_button_plus,
   &Menu_select_10inch,
   &Set_button,
   &Calibration_box,
   &Engine_calibration_box,
   &Parameter_calibration_box,
   &Next_box,
   &Offset_box,
   &Gain_box,
   ZERO
};

T_STEXTBOXDATA *Top_menu[] =
{
   ZERO,
   ZERO,
   ZERO,
   ZERO,
   ZERO,
   ZERO,
   ZERO,
   ZERO,
   ZERO,
   ZERO,
   ZERO,
   ZERO,
   ZERO,
   ZERO
};

/* Updated for PR 100083 */
T_STEXTBOXDATA *Timer_menu[] =
{
   &Top_button_1,
   &Exit_button,
   &Top_button_4,
   &Top_button_5,
   &Manual_timer_reset_btn,
   &Man_timer_on_off_btn,
   &Page_button,
   &Brightness_button,
   ZERO
};

T_STEXTBOXDATA *Page_menu[] =
{
   &Top_button_1,
   &Brightness_button,
   &Exit_button,
   &Encoder_page_select,
   ZERO
};

T_STEXTBOXDATA *Page_menu_1[] =
{
   &Brightness_button,
   &Exit_button,
   &Encoder_page_select,
   ZERO
};

T_STEXTBOXDATA *Page_menu_10inch[] =
{
   &Top_button_1,
   &Scroll_button,
   &Set_button,
   &Brightness_button,
   &Exit_button,
   &Button_page_select,
   ZERO
};

T_STEXTBOXDATA *Page_menu_10inch_1[] =
{
   &Scroll_button,
   &Set_button,
   &Brightness_button,
   &Exit_button,
   &Button_page_select,
   ZERO
};

T_STEXTBOXDATA  *Menu_menu[] =
{
   &Top_button_1,
   &Brightness_button,
   &Exit_button,
   &Encoder_menu_select,
   ZERO
};


T_STEXTBOXDATA  *Menu_menu_10inch[] =
{
   &Top_button_1,
   &Scroll_button,
   &Set_button,
   &Brightness_button,
   &Exit_button,
   &Menu_select_10inch,
   ZERO
};

T_STEXTBOXDATA *Msg_menu[] =
{
   &Top_button_1,
   &Brightness_button,
   &Exit_button,
   &Message_text_box,
   &Scroll_button,
   ZERO
};

T_STEXTBOXDATA *Cool_down_menu[] =
{
   &Top_button_1,
   &Brightness_button,
   &Exit_button,
   &Back_button,
   &Encoder_cool_down_select,
   ZERO
};

T_STEXTBOXDATA *Calibration_menu[] =
{
   &Top_button_1,
   &Scroll_button,
   &Set_button,
   &Calibration_box,
   &Brightness_button,
   &Exit_button,
   &Back_button,
   ZERO
};

T_STEXTBOXDATA *Engine_calibration[] =
{
   &Top_button_1,
   &Scroll_button,
   &Set_button,
   &Engine_calibration_box,
   &Brightness_button,
   &Exit_button,
   &Back_button,
   ZERO
};

T_STEXTBOXDATA *Parameter_calibration[] =
{
   &Top_button_1,
   &Scroll_button,
   &Set_button,
   &Parameter_calibration_box,
   &Brightness_button,
   &Exit_button,
   &Back_button,
   ZERO
};

T_STEXTBOXDATA *Offset_value_menu[] =
{
   &Top_button_1,
   &Scroll_button,
   &Set_button,
   &Next_box,
   &Offset_box,
   &Brightness_button,
   &Exit_button,
   &Back_button,
   ZERO
};


T_STEXTBOXDATA *Gain_value_menu[] =
{
   &Top_button_1,
   &Scroll_button,
   &Set_button,
   &Next_box,
   &Gain_box,
   &Brightness_button,
   &Exit_button,
   &Back_button,
   ZERO
};

T_STEXTBOXDATA *Fuel_flow[] =
{
   &Top_button_1,
   &Brightness_button,
   &Exit_button,
   &Back_button,
   &Scroll_button,
   &Fuel_flow_message,
   ZERO
};

/* Updated for PR 100083 */
T_STEXTBOXDATA *Sys_info_menu[] =
{
   &Top_button_1,
   &Brightness_button,
   &Exit_button,
   &Back_button,
   &Sys_info_message_box,
   &Scroll_button,
   ZERO
};


T_STEXTBOXDATA *Sys_info_menu_10inch[] =
{
   &Top_button_1,
   &Top_button_2,
   &Top_button_3,
   &Brightness_button,
   &Exit_button,
   &Back_button,
   &Sys_info_message_box,
   ZERO
};

T_STEXTBOXDATA *Brightness_menu[] =
{
   &Top_button_1,
   &Exit_button,
   &Top_button_minus,
   &Top_button_plus,
   &Brightness_button,
   ZERO
};

/* Updated for PR 100083 */
T_EPAGE_NUM Toggle_screen = EPAGE1;
T_UINT8 Page_number=EPAGEINVALID;
T_BOOL Cool_down_select=0;
T_BOOL Fuel_flow_select=0;
T_FLOAT Fuel_flow_data =0;
T_UINT8 Ff_a429_tag =0;
T_RTD_STATUS Ff_status =RTD_MISSING;

static void ManualTimerMaint(void);
static void ManualTimerStart(void);
static void MenuPush(T_STEXTBOXDATA **pps_items);
static void MenuCheckTimeOut(void);
static T_INT8 MenuSelectText(T_CHAR*   pc_menu_text
,T_INT8  s8_Present_Selection,T_INT8  s8_step,T_INT8  s8_max_selection);
static T_INT8 MenuSelectText10Inch(T_CHAR*   pc_menu_text
,T_INT8  s8_Present_Selection,T_INT8  s8_step_down,T_INT8  s8_max_selection);

/*
 * Function                : CoolTimerInit
 *
 * Description             : The function initializes the cooldown timer.
 *
 * Formal parameter(s)     : None
 *
 * Return Value            : None
 *
 * Assumption              : None
 *
 */
/* Updated for PR 100083 */
void CoolTimerInit(void)
{
   /* hdudispfmenu-CoolTimerInit-DB-LLR-001 */
   TimerInstall(&Cool_timer_mirror);
   Cool_timer = ZERO;
}

/*
 * Function                : CoolTimerReset
 *
 * Description             : The function reset the cooldown timer.
 *
 * Formal parameter(s)     : None
 *
 * Return Value            : None
 *
 * Assumption              : None
 *
 */

void CoolTimerReset(void)
{
   /* hdudispfmenu-CoolTimerReset-DB-LLR-001 */
   TimerReset(&Cool_timer_mirror);
   Cool_timer = ZERO;
}

/*
 * Function                : CoolTimerStart
 *
 * Description             : The function starts the cooldown timer.
 *
 * Formal parameter(s)     : None
 *
 * Return Value            : None
 *
 * Assumption              : None
 *
 */

void CoolTimerStart(void)
{
   /* hdudispfmenu-CoolTimerStart-DB-LLR-001 */
   TimerPreset(&Cool_timer_mirror, (T_INT32)Cool_timer);
}

/*
 * Function                : ManualTimerInit
 *
 * Description             : The function initializes the manual timer.
 *
 * Formal parameter(s)     : None
 *
 * Return Value            : None
 *
 * Assumption              : None
 *
 */

void ManualTimerInit(void)
{
   /* hdudispfmenu-ManualTimerInit-DB-LLR-001 */
   TimerInstall(&Manual_timer_mirror);
   Man_timer_state = MAN_TIMER_OFF;
   Manual_timer = ZERO;
}

/*
 * Function                : ManualTimerMaint
 *
 * Description             : This function function the Manual timer when the
 *                            state of timer is on.
 *
 * Formal parameter(s)     : None
 *
 * Return Value            : None
 *
 * Assumption              : None
 *
 */

static void ManualTimerMaint(void)
{
   if(MAN_TIMER_ON == Man_timer_state)
   {
      /* hdudispfmenu-ManualTimerMaint-DB-LLR-001 */
      Manual_timer = Manual_timer_mirror;
   }
   else
   {
      ;  /* Do nothing */
   }
}

/*
 * Function                : ManualTimerReset
 *
 * Description             : The function resets the manual timer.
 *
 * Formal parameter(s)     : None
 *
 * Return Value            : None
 *
 * Assumption              : None
 *
 */
static void ManualTimerReset(void)
{
   /* hdudispfmenu-ManualTimerReset-DB-LLR-001 */
   TimerReset(&Manual_timer_mirror);
   Manual_timer = ZERO;
}

/*
 * Function                : OffsideManualTimerReset
 *
 * Description             : The function resets the offside manual timer.
 *
 * Formal parameter(s)     : None
 *
 * Return Value            : None
 *
 * Assumption              : None
 *
 */
void OffsideManualTimerReset(void)
{
   /* hdudispfmenu-OffsideManualTimerReset-DB-LLR-001 */
   TimerReset(&Manual_timer_mirror);
   Manual_timer = ZERO;
}

/*
 * Function                : ManualTimerStart
 *
 * Description             : The function starts the manual timer.
 *
 * Formal parameter(s)     : None
 *
 * Return Value            : None
 *
 * Assumption              : None
 *
 */
static void ManualTimerStart(void)
{
   /* hdudispfmenu-ManualTimerStart-DB-LLR-001 */
   TimerPreset(&Manual_timer_mirror, (T_INT32)Manual_timer);
   Man_timer_state = MAN_TIMER_ON;
}

/*
 * Function                : OffsideManualTimerStart
 *
 * Description             : The function starts the offside manual timer.
 *
 * Formal parameter(s)     : T_UINT32 u32_start_val - IN Holds the stop value
 *
 * Return Value            : None
 *
 * Assumption              : None
 *
 */
void OffsideManualTimerStart(T_UINT32 u32_start_val)
{
   /* hdudispfmenu-OffsideManualTimerStart-DB-LLR-001 */
   TimerPreset(&Manual_timer_mirror, (T_INT32)u32_start_val);
   Man_timer_state = MAN_TIMER_ON;
}

/*
 * Function                : ManualTimerStop
 *
 * Description             : The function stops the manual timer.
 *
 * Formal parameter(s)     : None
 *
 * Return Value            : None
 *
 * Assumption              : None
 *
 */
static void ManualTimerStop(void)
{
   /* hdudispfmenu-ManualTimerStop-DB-LLR-001 */
   Man_timer_state = MAN_TIMER_OFF;
}

/*
 * Function                : OffsideManualTimerStop
 *
 * Description             : The function stops the offside manual timer.
 *
 * Formal parameter(s)     : T_UINT32 u32_stop_val - IN Holds the stop value
 *
 * Return Value            : None
 *
 * Assumption              : None
 *
 */
void OffsideManualTimerStop(T_UINT32 u32_stop_val)
{
   /* hdudispfmenu-OffsideManualTimerStop-DB-LLR-001 */
   Man_timer_state = MAN_TIMER_OFF;
   Manual_timer = u32_stop_val;
}

/*
 * Function                : MenuOff
 *
 * Description             : The function closes the menu option.
 *
 * Formal parameter(s)     : T_STEXTBOXDATA **ptr_next_item - INOUT Points to next item
 *
 * Return Value            : None
 *
 * Assumption              : None
 *
 */
static void MenuOff(T_STEXTBOXDATA **ptr_next_item)
{
   while((*ptr_next_item) != ((T_STEXTBOXDATA *)ZERO))
   {
      /* hdudispfmenu-MenuOff-DB-LLR-001 */
      TextBoxOff(*ptr_next_item);
      ptr_next_item++;
   }
}

/*
 * Function                : MenuOn
 *
 * Description             : The function displays the menu option.
 *
 * Formal parameter(s)     : T_STEXTBOXDATA **ptr_next_item -IN Points to next item
 *
 * Return Value            : None
 *
 * Assumption              : None
 *
 */
static void MenuOn(T_STEXTBOXDATA **ptr_next_item)
{
   while((*ptr_next_item) != ((T_STEXTBOXDATA *)ZERO))
   {
      /* hdudispfmenu-MenuOn-DB-LLR-001 */
      TextBoxOn(*ptr_next_item);
      ptr_next_item++;
   }
}

/*
 * Function                : MenuPush
 *
 * Description             : The function displays the menu items
 *
 * Formal parameter(s)     : T_STEXTBOXDATA **pps_items -IN Points to menu items
 *
 * Return Value            : None
 *
 * Assumption              : None
 *
 */
static void MenuPush(T_STEXTBOXDATA **pps_items)
{
   /* hdudispfmenu-MenuPush-DB-LLR-001 */
   PbsClear();

   /* Prevent stack overflow. */
   /* Updated for PR 100083 */
   if((T_INT16)ZERO == S16_menu_stack_pointer)
   {
      /* hdudispfmenu-MenuPush-DB-LLR-002 */
      return;
   }
   else
   {
    ; /* Do nothing */
   }

   /* If the stack is not empty. */
   if(ZERO != Pps_menu_stack[S16_menu_stack_pointer])
   {
      /* hdudispfmenu-MenuPush-DB-LLR-003 */
      MenuOff(Pps_menu_stack[S16_menu_stack_pointer]);
   }
   else
   {
    ; /* Do nothing */
   }

   /* hdudispfmenu-MenuPush-DB-LLR-004 */
   MenuOn(pps_items);

   S16_menu_stack_pointer = (T_INT16)(S16_menu_stack_pointer - (T_INT16)ONE);
   Pps_menu_stack[S16_menu_stack_pointer] = pps_items;
}

/*
 * Function                : MenuReset
 *
 * Description             : The function resets present menu.
 *
 * Formal parameter(s)     : T_STEXTBOXDATA **pps_items - IN Points to menu items
 *                           T_EPAGE_NUM page_num - IN Contains current page number.
 *
 * Return Value            : None
 *
 * Assumption              : None
 *
 */
/* Updated for PR 100083 */
void MenuReset(T_STEXTBOXDATA **pps_items, T_EPAGE_NUM page_num)
{
   /* hdudispfmenu-MenuReset-DB-LLR-001 */
   PbsClear();

   /* Turn off present menu. */
   if(S16_menu_stack_pointer != MAX_MENU_DEPTH)
   {
      /* hdudispfmenu-MenuReset-DB-LLR-002 */
      MenuOff(Pps_menu_stack[S16_menu_stack_pointer]);
   }
   else
   {
    ; /* Do nothing */
   }

   /* hdudispfmenu-MenuReset-DB-LLR-003 */
   ParaConfigTopMenu(pps_items, page_num);
   S16_menu_stack_pointer = (T_INT16)(MAX_MENU_DEPTH-(T_INT16)ONE);
   Pps_menu_stack[S16_menu_stack_pointer] = pps_items;
}

/*
 * Function                : MenuPop
 *
 * Description             : The function makes the menu appears ("pops up") in the foreground
 *                            of the visual interface
 *
 * Formal parameter(s)     : None
 *
 * Return Value            : None
 *
 * Assumption              : None
 *
 */
static void MenuPop(void)
{
   /* hdudispfmenu-MenuPop-DB-LLR-001 */
   PbsClear();

   /* Prevent stack underflow. */
   if(MAX_MENU_DEPTH == S16_menu_stack_pointer)
   {
      /* hdudispfmenu-MenuPop-DB-LLR-002 */
      return;
   }
   else
   {
    ; /* Do nothing */
   }

   /* hdudispfmenu-MenuPop-DB-LLR-003 */
   MenuOff(Pps_menu_stack[S16_menu_stack_pointer]);

   /* Updated for PR 100083 */
   S16_menu_stack_pointer = (T_INT16)(S16_menu_stack_pointer + (T_INT16)ONE);

   /* hdudispfmenu-MenuPop-DB-LLR-004 */
   if(S16_menu_stack_pointer >=(T_INT16)(MAX_MENU_DEPTH-(T_INT16)ONE))
   {
      MenuReset(Top_menu, Page_number);
   }
   else
   {
      MenuOn(Pps_menu_stack[S16_menu_stack_pointer]);
   }
}

/*
 * Function                : MenuCheckTimeOut
 *
 * Description             : The function check the timer and closes the current menu
 *                            when timer elapses.
 *
 * Formal parameter(s)     : None
 *
 * Return Value            : None
 *
 * Assumption              : None
 *
 */
static void MenuCheckTimeOut(void)
{
   if(Menu_timer>=MENU_TIME)
   {
      /* hdudispfmenu-MenuCheckTimeOut-DB-LLR-001 */
      TimerPreset(&Menu_timer, MENU_TIME);

      /* Updated for PR 100083 */
     if(S16_menu_stack_pointer != (T_INT16)(MAX_MENU_DEPTH-(T_INT16)ONE))
      {
         /* hdudispfmenu-MenuCheckTimeOut-DB-LLR-002 */
         MenuReset(Top_menu, Page_number);
      }
      else
      {
       ; /* Do nothing */
      }
   }
   else
   {
    ; /* Do nothing */
   }
}

/*
 * Function                : MenuSwitchPage
 *
 * Description             : The function configures the menu page switch.
 *
 * Formal parameter(s)     : T_EPAGE_NUM new_page_num - IN Holds the new page number
 *
 * Return Value            : None
 *
 * Assumption              : None
 *
 */
static void MenuSwitchPage(T_EPAGE_NUM new_page_num)
{
   if(new_page_num != Page_number)
   {
      /* hdudispfmenu-MenuSwitchPage-DB-LLR-001 */
      GrappSwithcScreens(new_page_num);

      if(EPAGE0 == new_page_num)
      {
         /* hdudispfmenu-MenuSwitchPage-DB-LLR-002 */
         /* Updated as per PR 100083 */
         if(Page_number <= (Max_num_of_pages-ONE))
         {
            Toggle_screen = Page_number;
         }
         else
         {
            ;/* Does nothing */
         }

         if(Toggle_screen>(Max_num_of_pages-ONE))
         {
            Toggle_screen = EPAGE1;
         }
         else
         {
            ;/* Does nothing */
         }

      }
      else
      {
       ; /* Do nothing */
      }

      /* hdudispfmenu-MenuSwitchPage-DB-LLR-003 */
      MenuReset(Top_menu, new_page_num);

      Page_number = new_page_num;

   }
   else
   {
    ; /* Do nothing */
   }
}

/*
 * Function                : ScanOne
 *
 * Description             : The function scans the text
 *
 * Formal parameter(s)     : T_CHAR* pc_text -IN  pointer to the text
 *
 * Return Value            : T_CHAR* - Address of pc_text
 *
 * Assumption              : None
 *
 */
static T_CHAR *ScanOne(T_CHAR* pc_text)
{
   /* hdudispfmenu-ScanOne-DB-LLR-001 */
   while(*pc_text != ZERO)
   {
      if(('\r' == *pc_text)||('\n' == *pc_text))
      {
         while(('\r' == *pc_text)||('\n' == *pc_text))
         {
            pc_text += ONE;
         }
         break;
      }
      else
      {
        ; /* Do nothing */
      }
      pc_text += ONE;
   }

   /* hdudispfmenu-ScanOne-DB-LLR-002 */
   return(pc_text);
}

/*
 * Function                : MenuSelectText
 *
 * Description             : The function helps in selecting the menu options.
 *
 * Formal parameter(s)     : T_CHAR* pc_menu_text –INOUT Pointer for menu text
 *                           T_INT8 s8_Present_Selection –INOUT holds present menu selected
 *                           T_INT8 s8_step –INOUT holds the next step
 *                           T_INT8 s8_max_selection - IN holds nth menu
 *
 * Return Value            : T_INT8 - returns present selected menu
 *
 * Assumption              : None
 *
 */
static T_INT8 MenuSelectText(T_CHAR*   pc_menu_text
                              ,T_INT8  s8_Present_Selection
                              ,T_INT8  s8_step
                              ,T_INT8  s8_max_selection
                              )
{
   T_INT8 s8_ctr = 0;

   T_CHAR *pc_temp = (T_CHAR *)NULL;

   /* Limit change to one step per display update. */
   if(s8_step < ((T_INT8)ZERO))
   {
      /* hdudispfmenu-MenuSelectText-DB-LLR-001 */
      s8_step = MINUS_ONE ;
   }
   else if(s8_step > (T_INT8)ZERO)
   {
      /* hdudispfmenu-MenuSelectText-DB-LLR-002 */
      s8_step = (T_INT8)ONE;
   }
   else
   {
     ; /* Do nothing */
   }

   /* hdudispfmenu-MenuSelectText-DB-LLR-003 */
   s8_Present_Selection = (T_INT8)(s8_Present_Selection+s8_step);

   /* Once first item of menu is reached, if scroll button is pressed */
   /* control goes to last item of the menu */
   /* Modulo on the number of selections. */
   while(s8_Present_Selection<(T_INT8)ZERO)
   {
      /* hdudispfmenu-MenuSelectText-DB-LLR-004 */
      s8_Present_Selection = (T_INT8)(s8_Present_Selection+s8_max_selection);
   }

   /* once end of menu is reached, if scroll button is pressed */
   /* control goes to 1st item of the menu */
   while(s8_Present_Selection>=s8_max_selection)
   {
      /* hdudispfmenu-MenuSelectText-DB-LLR-005 */
      s8_Present_Selection = (T_INT8)(s8_Present_Selection-s8_max_selection);
   }

   /* hdudispfmenu-MenuSelectText-DB-LLR-006 */
   /* Clear Previous Selection */
   pc_temp = pc_menu_text;
   while(*pc_temp != ZERO)
   {
      if((*pc_temp != '\r')&&(*pc_temp != '\n'))
      {
         *pc_temp &= MASK_VAL;
      }
      else
      {
        ; /* Do nothing */
      }

      pc_temp += ONE;
   }

   /* hdudispfmenu-MenuSelectText-DB-LLR-007 */
   /* Scan to the new selection */
   s8_ctr = s8_Present_Selection;

   while(s8_ctr)
   {
      pc_menu_text= ScanOne(pc_menu_text);
      s8_ctr = (T_INT8)(s8_ctr-(T_INT8)ONE);
   }

   /* hdudispfmenu-MenuSelectText-DB-LLR-008 */
   /* Reverse video the selection. */
   while((*pc_menu_text != ZERO)&&(*pc_menu_text != '\r')&&(*pc_menu_text != '\n'))
   {
      *pc_menu_text |= ONEHUNDRED_TWENTY_EIGHT;
      pc_menu_text += (T_INT8)ONE;
   }

   /* hdudispfmenu-MenuSelectText-DB-LLR-009 */
   return(s8_Present_Selection);
}


/*
 * Function                : MenuSelectText_10Inch
 *
 * Description             : The function helps in selecting the menu options.
 *
 * Formal parameter(s)     : T_CHAR* pc_menu_text –INOUT Pointer for menu text
 *                           T_INT8 s8_Present_Selection –INOUT holds present menu selected
 *                           T_INT8 s8_step –INOUT holds the next step
 *                           T_INT8 s8_max_selection - IN holds nth menu
 *
 * Return Value            : T_INT8 - returns present selected menu
 *
 * Assumption              : None
 *
 */
static T_INT8 MenuSelectText10Inch(T_CHAR*   pc_menu_text
                              ,T_INT8  s8_Present_Selection
                              ,T_INT8  s8_step_down
                              ,T_INT8  s8_max_selection
                              )
{
   T_INT8 s8_ctr = 0;
   T_INT8 s8_step = 0;

   T_CHAR *pc_temp = (T_CHAR *)NULL;

   /* Limit change to one step per display update. */
   if((T_INT8)ONE == s8_step_down)
   {
  /* hdudispfmenu-MenuSelectText10Inch-DB-LLR-001 */
     s8_step = (T_INT8)ONE;
   }
   else
   {
     ; /* Do nothing */
   }


   /* hdudispfmenu-MenuSelectText10Inch-DB-LLR-002 */
   s8_Present_Selection = (T_INT8)(s8_Present_Selection+s8_step);
   while(s8_Present_Selection>=s8_max_selection)
   {
      /* hdudispfmenu-MenuSelectText10Inch-DB-LLR-004*/
      s8_Present_Selection = (T_INT8)(s8_Present_Selection-s8_max_selection);
   }

   /* hdudispfmenu-MenuSelectText10Inch-DB-LLR-005 */
   /* Clear Previous Selection */
   pc_temp = pc_menu_text;
   while(*pc_temp != ZERO)
   {
      if((*pc_temp != '\r')&&(*pc_temp != '\n'))
      {
         *pc_temp &= MASK_VAL;
      }
      else
      {
        ; /* Do nothing */
      }

      pc_temp += ONE;
   }

   /* hdudispfmenu-MenuSelectText10Inch-DB-LLR-006 */
   /* Scan to the new selection */
   s8_ctr = s8_Present_Selection;

   while(s8_ctr)
   {
      pc_menu_text= ScanOne(pc_menu_text);
      s8_ctr = (T_INT8)(s8_ctr-(T_INT8)ONE);
   }

   /* hdudispfmenu-MenuSelectText10Inch-DB-LLR-007 */
   /* Reverse video the selection. */
   while((*pc_menu_text != ZERO)&&(*pc_menu_text != '\r')&&(*pc_menu_text != '\n'))
   {
      *pc_menu_text |= ONEHUNDRED_TWENTY_EIGHT;
      pc_menu_text += (T_INT8)ONE;
   }

   /* hdudispfmenu-MenuSelectText10Inch-DB-LLR-008 */
   return(s8_Present_Selection);
}


/*
 * Function                : EncoderCoolDownItemSelectText
 *
 * Description             : This function selects the required item in the cooldown menu
 *                            using the encoder.
 *
 * Formal parameter(s)     : None
 *
 * Return Value            : T_CHAR * - encoder cool down text
 *
 * Assumption              : None
 *
 */
T_CHAR *EncoderCoolDownItemSelectText(void)
{
   /* hdudispfmenu-EncoderCoolDownItemSelectText-DB-LLR-001 */
   Cool_down_state = (T_COOLDOWN_STATE) MenuSelectText(Encoder_cool_down_text
                                    ,(T_INT8) Cool_down_state
                                    ,Switches.sRE.twist
                                    ,COOL_DOWN_LIST_ITEMS
                                    );
   Switches.sRE.twist = (T_INT8)ZERO;

   if((T_INT8)ZERO != Switches.sRE.pressed)
   {
      /* hdudispfmenu-EncoderCoolDownItemSelectText-DB-LLR-002 */
      MenuPop();

      /* hdudispfmenu-EncoderCoolDownItemSelectText-DB-LLR-003 */
      if (ECOOLDOWN_ON == Cool_down_state)
      {
         /* updated as per PR 100083 */
          Cool_down_select = TRUE;
          OffsideCoolTimer(Cool_down_select);
      }
      else if (ECOOLDOWN_OFF == Cool_down_state)
      {
         /* updated as per PR 100083 */
         Cool_down_select = FALSE;
         OffsideCoolTimer(Cool_down_select);
      }
      else
      {
         ; /* Do nothing */
      }
   }
   else
   {
    ; /* Do nothing*/
   }

   /* hdudispfmenu-EncoderCoolDownItemSelectText-DB-LLR-004 */
   return(Encoder_cool_down_text);
}

/*
 * Function                : FloatToString
 *
 * Description             : converts floating point fuel flow data received from DAU to string
 *
 * Formal parameter(s)     : T_FLOAT value - IN contains the value to be converted to string
 *                           T_CHAR *str - OUT destination string
 *                           T_UINT8 bit_size - IN contains the number of digits in fuel flow value.
 *
 * Return Value            : None
 *
 * Assumption              : None
 *
 */

void FloatToString ( T_FLOAT value, T_CHAR *str, T_UINT8 bit_size)
{
 T_UINT32 u32_int_value =0;
 T_UINT32 u32_temp =0;
 T_UINT8 var_i=ZERO;   /* Loop variable */

 u32_int_value = (T_UINT32)value;
 /*hdudispfmenu-FloatToString-DB-LLR-001*/
 if(M_FP_COMPARE > (value - ZERO) && M_FP_COMPARE > (ZERO - value))
 {
	for (var_i = ONE; var_i <= bit_size; var_i++)
	{
		str[bit_size-var_i] = '0';
	}
	 return;
 }
  /*hdudispfmenu-FloatToString-DB-LLR-002*/
  if ((T_FLOAT)(value - (T_FLOAT)u32_int_value) < (T_FLOAT)0.499999f)
  {
   u32_temp = u32_int_value;
   for (var_i = ONE; var_i <= bit_size; var_i++)
   {
      str[bit_size-var_i] = (T_CHAR)((u32_temp%10) + '0');
	  u32_temp =u32_temp /10;
   }
  }
  /*hdudispfmenu-FloatToString-DB-LLR-003*/
  else
    {
   u32_temp = u32_int_value + 1;
   for (var_i = ONE; var_i <= bit_size; var_i++)
   {
      str[bit_size-var_i] = (T_CHAR)((u32_temp%10) + '0');
	  u32_temp = u32_temp /10;
   }
  }

}

/*
 * Function                : FuelFlowOnOffButtonText
 *
 * Description             : This function selects the required item in the fuel flow menu
 *                            using the encoder.
 *
 * Formal parameter(s)     : None
 *
 * Return Value            : T_CHAR * - encoder fuel flow text
 *
 * Assumption              : None
 *
 */
T_CHAR *FuelFlowOnOffButtonText(void)
{
	/*hdudispfmenu-FuelFlowOnOffButtonText-DB-LLR-001*/
	Fuel_flow_state = (T_COOLDOWN_STATE) MenuSelectText(Encoder_fuel_flow_text
                                    ,(T_INT8) Fuel_flow_state
                                    ,Switches.sRE.twist
                                    ,FUEL_FLOW_LIST_ITEMS
                                    );
   Switches.sRE.twist = (T_INT8)ZERO;
   /*hdudispfmenu-FuelFlowOnOffButtonText-DB-LLR-002*/
   if((T_INT8)ZERO != Switches.sRE.pressed)
   {
      MenuPop();
	  /*hdudispfmenu-FuelFlowOnOffButtonText-DB-LLR-004*/
      if (FUEL_FLOW_ON == Fuel_flow_state)
      {
            Fuel_flow_select = TRUE;
    	    OffsideFuelFlow(Fuel_flow_select);
	  }
       /*hdudispfmenu-FuelFlowOnOffButtonText-DB-LLR-003*/
      else
      {
	       	Fuel_flow_select = FALSE;
	       	OffsideFuelFlow(Fuel_flow_select);
      }
   }
   /*hdudispfmenu-FuelFlowOnOffButtonText-DB-LLR-005*/
   else
   {
      ; /*Do Nothing */
   }
  /*hdudispfmenu-FuelFlowOnOffButtonText-DB-LLR-006*/
   return(Encoder_fuel_flow_text);
}

/*
 * Function                : SysInfoBoxText
 *
 * Description             : This function shows the system info(binaries loaded)
 *                            when selected using the encoder.
 *
 * Formal parameter(s)     : None
 *
 * Return Value            : T_CHAR * - returns system information
 *
 * Assumption              : None
 *
 */
T_CHAR* SysInfoBoxText(void)
{
   /* Updated for PR 100083 */
   T_INT16 sys_info_cnt=0;
   T_INT16 scroll = 0;
   if (E_7_INCH == Display_size)
   {
	   if((T_INT8)ZERO != Switches.sRE.twist)
	   {
          /* hdudispfmenu-SysInfoBoxText-DB-LLR-001*/
	     /* Updated as per PR 100083 */
	      S16_sys_info_index = (T_INT16)(S16_sys_info_index + Switches.sRE.twist);
	      if(S16_sys_info_index < ((T_INT16)ZERO))
	      {
	          S16_sys_info_index = (T_INT16)ZERO;
	      }
	      else
	      {
	         ;/* Does noting */
	      }
	      Switches.sRE.twist = (T_INT8)ZERO;
	   }
	   else
	   {
	     ; /* Do nothing */
	   }
   }
   else if (E_10_INCH == Display_size)
   {
       /* hdudispfmenu-SysInfoBoxText-DB-LLR-006 */
       if(((T_INT8)ZERO != Switches.b2) || ((T_INT8)ZERO != Switches.b3))
       {
          if ((T_INT8)ONE ==  Switches.b2)
          {
            scroll = MINUS_ONE;
          }

          if ((T_INT8)ONE == Switches.b3)
          {
            scroll = ONE;
          }

          S16_sys_info_index = (T_INT16)(S16_sys_info_index + scroll);
          if(S16_sys_info_index < ((T_INT16)ZERO))
          {
              S16_sys_info_index = (T_INT16)ZERO;
          }
          else
          {
             ;/* Does noting */
          }

	   }
	   else
	   {
	  	 ; /* Do nothing */
	   }

   }
   else
   {
	   ; /* Do nothing */
   }


   /* hdudispfmenu-SysInfoBoxText-DB-LLR-002 */
   S16_sys_info_index = ParaGetSysInfoCount(S16_sys_info_index);

   /* Updated for PR 100083 */
   sys_info_cnt = BuildSysInfoList();

   /* hdudispfmenu-SysInfoBoxText-DB-LLR-004 */
   if(sys_info_cnt> (T_INT16)(SIXTEEN))
   {
      if((sys_info_cnt-S16_sys_info_index)<  (T_INT16)SIXTEEN)
      {
         S16_sys_info_index= (T_INT16)(sys_info_cnt-(T_INT16)SIXTEEN);
      }
      else
      {
         ;/* Does nothing */
      }
   }
   else
   {
       /* hdudispfmenu-SysInfoBoxText-DB-LLR-005 */
       Sys_info_message_box.s16PixHeight=  (T_INT16)((sys_info_cnt+1)*(LISTBOX_CHAR_HEIGHT+5));
       S16_sys_info_index=0;
   }

   /* hdudispfmenu-SysInfoBoxText-DB-LLR-003*/
   if(S16_sys_info_index>=0)
   {

      return((T_CHAR *)&Pc_sys_info_list[S16_sys_info_index]);
   }
   else
   {
      S16_sys_info_index = (T_INT16)ZERO;
      return((T_CHAR *)Empty_sys_info_list);
   }
}

/*
 * Function                : EncoderMenuItemSelectText
 *
 * Description             : This function selects the required item in the menu (cool down,
 *                           system info or fuel flow for MD engines and cool down or
 *                           system info for other engines) using the encoder.
 *
 * Formal parameter(s)     : None
 *
 * Return Value            : T_CHAR* - encoder page text
 *
 * Assumption              : None
 *
 */
T_CHAR *EncoderMenuItemSelectText(void)
{
   /*hdudispfmenu-EncoderMenuItemSelectText-DB-LLR-005*/
	if(TRUE == Md_engine_flag)
	{
	/* If the CMU “Fuel Flow” is enabled, the E2 Right Encoder SHALL display “Fuel Flow” */
	 if(ONE == Cmu_fuel_flow)
	 {
	   U8_selected_menu_item = (T_UINT8)MenuSelectText(Encoder_menu_text_ff
	                        ,(T_INT8) U8_selected_menu_item
	                        ,Switches.sRE.twist
	                        ,MENU_LIST_ITEMS_FF
	                        );

	   Switches.sRE.twist = (T_INT8)ZERO;
       /*hdudispfmenu-EncoderMenuItemSelectText-DB-LLR-006*/
	   if((T_INT8)ZERO != Switches.sRE.pressed)
	   {
	      switch(U8_selected_menu_item)
	      {
	         case ZERO:
	         {
	            MenuPush(Cool_down_menu);
	            break;
	         }
			 /*hdudispfmenu-EncoderMenuItemSelectText-DB-LLR-007*/
	         case ONE:
	         {
	            S16_sys_info_index = (T_INT16)ZERO;
	            /* Updated as per PR 100083 */
	            GlobalSettingsSetSysInfo();
	            OsTimeDly(ONE_HUNDRED);
	            ProcessSysInfoWords();

	            MenuPush(Sys_info_menu);
	            break;
	         }
			 /*hdudispfmenu-EncoderMenuItemSelectText-DB-LLR-008*/
			 case TWO:
	         {
			  MenuPush(Fuel_flow);
			  break;
			 }
	         default:
	         break;
	      }
	   }
	   /*hdudispfmenu-EncoderMenuItemSelectText-DB-LLR-009*/
	   else
	   {
	    ; /* Do nothing */
	   }
	   /*hdudispfmenu-EncoderMenuItemSelectText-DB-LLR-010*/
	   return(Encoder_menu_text_ff);
	   }
   else
	{
	     /* hdudispfmenu-EncoderMenuItemSelectText-DB-LLR-001 */
	   U8_selected_menu_item = (T_UINT8)MenuSelectText(Encoder_menu_text
	                        ,(T_INT8) U8_selected_menu_item
	                        ,Switches.sRE.twist
	                        ,MENU_LIST_ITEMS
	                        );

	   Switches.sRE.twist = (T_INT8)ZERO;

	   if((T_INT8)ZERO != Switches.sRE.pressed)
	   {
	      switch(U8_selected_menu_item)
	      {
	         case ZERO:
	         {
	            /* hdudispfmenu-EncoderMenuItemSelectText-DB-LLR-002 */
	            MenuPush(Cool_down_menu);
	            break;
	         }
	         case ONE:
	         {
	            /* hdudispfmenu-EncoderMenuItemSelectText-DB-LLR-003 */
	            S16_sys_info_index = (T_INT16)ZERO;
	            /* Updated as per PR 100083 */
	            GlobalSettingsSetSysInfo();
	            OsTimeDly(ONE_HUNDRED);
	            ProcessSysInfoWords();

	            MenuPush(Sys_info_menu);
	            break;
	         }
	         default:
	         break;
	      }
	   }
	   /* hdudispfmenu-EncoderMenuItemSelectText-DB-LLR-011 */
	   else
	   {
	    ; /* Do nothing */
	   }

	   /* hdudispfmenu-EncoderMenuItemSelectText-DB-LLR-004 */
	   return(Encoder_menu_text);
	 }
	}
	else
	{
			   /* hdudispfmenu-EncoderMenuItemSelectText-DB-LLR-012 */
			   U8_selected_menu_item = (T_UINT8)MenuSelectText(Encoder_menu_text
			                        ,(T_INT8) U8_selected_menu_item
			                        ,Switches.sRE.twist
			                        ,MENU_LIST_ITEMS
			                        );

			   Switches.sRE.twist = (T_INT8)ZERO;

			   if((T_INT8)ZERO != Switches.sRE.pressed)
			   {
			      switch(U8_selected_menu_item)
			      {
			         case ZERO:
			         {
			            /* hdudispfmenu-EncoderMenuItemSelectText-DB-LLR-013 */
			            MenuPush(Cool_down_menu);
			            break;
			         }
			         case ONE:
			         {
			            /* hdudispfmenu-EncoderMenuItemSelectText-DB-LLR-014 */
			            S16_sys_info_index = (T_INT16)ZERO;
			            /* Updated as per PR 100083 */
			            GlobalSettingsSetSysInfo();
			            OsTimeDly(ONE_HUNDRED);
			            ProcessSysInfoWords();

			            MenuPush(Sys_info_menu);
			            break;
			         }
			         default:
			         break;
			      }
			   }
			   /*hdudispfmenu-EncoderMenuItemSelectText-DB-LLR-011*/
			   else
			   {
			    ; /* Do nothing */
			   }

			   /* hdudispfmenu-EncoderMenuItemSelectText-DB-LLR-015 */
			   return(Encoder_menu_text);
			 }
}

/*
 * Function                : MenuItemSelectText10Inch
 *
 * Description             : This function selects the required item in the menu (CALIBRATION or
 *                           SYS INFORMATION) using the encoder.
 *
 * Formal parameter(s)     : None
 *
 * Return Value            : T_CHAR* - encoder page text
 *
 * Assumption              : None
 *
 */
T_CHAR *MenuItemSelectText10Inch(void)
{
   /* hdudispfmenu-MenuItemSelectText10Inch-DB-LLR-001 */
	U8_selected_menu_item_10inch = (T_UINT8)MenuSelectText10Inch(Menu_text_10inch
                        ,(T_INT8) U8_selected_menu_item_10inch
                        ,Switches.b3
                        ,MENU_LIST_ITEMS
                        );

   if((T_INT8)ZERO != Switches.b4)
   {
      switch(U8_selected_menu_item_10inch)
      {
         case ZERO:
         {
        	if (Bool_menu_cal!= TRUE)
        	{
			 /* hdudispfmenu-MenuItemSelectText10Inch-DB-LLR-002 */
        		MenuPush(Calibration_menu);
        	}
        	else
        	{
        		;/*do nothing*/
        	}
            break;
         }
         case ONE:
         {
		  /* hdudispfmenu-MenuItemSelectText10Inch-DB-LLR-003 */
            S16_sys_info_index = (T_INT16)ZERO;
            GlobalSettingsSetSysInfo();
            OsTimeDly(ONE_HUNDRED);
            ProcessSysInfoWords();

            MenuPush(Sys_info_menu_10inch);
            break;
         }
         default:
         break;
      }
   }
   else
   {
    ; /* Do nothing */
   }

   /* hdudispfmenu-EncoderMenuItemSelectText-DB-LLR-004 */
   return(Menu_text_10inch);
}


/*
 * Function                : CalibrationSelectText10Inch
 *
 * Description             : This function selects the required item in the menu (ENG 1 or ENG 2
 *                           or ENG 3 or ENG 4) using the encoder.
 *
 * Formal parameter(s)     : None
 *
 * Return Value            : T_CHAR* - encoder page text
 *
 * Assumption              : None
 *
 */
T_CHAR *CalibrationSelectText10Inch(void)
{
    /* hdudispfmenu-CalibrationSelectText10Inch-DB-LLR-001 */
    U8_selected_engine_item_10inch = (T_UINT8)MenuSelectText10Inch(Calibration_text_10inch
                        ,(T_INT8) U8_selected_engine_item_10inch
                        ,Switches.b3
                        ,4
                        );


   if((T_INT8)ZERO != Switches.b4)
   {
      MenuPush(Engine_calibration);
      switch(U8_selected_engine_item_10inch)
      {
         case ZERO:
         {
             /* ENG1 */
             /* hdudispfmenu-CalibrationSelectText10Inch-DB-LLR-002 */
            Engine_count = 0;
            break;
         }
         case ONE:
         {
             /* ENG2 */
             /* hdudispfmenu-CalibrationSelectText10Inch-DB-LLR-003 */
            Engine_count = 1;
            break;
         }
         case TWO:
         {
             /* ENG3 */
             /* hdudispfmenu-CalibrationSelectText_10Inch-DB-LLR-004 */
            Engine_count = 2;
            break;
         }
         case THREE:
         {
             /* ENG4 */
              /* hdudispfmenu-CalibrationSelectText_10Inch-DB-LLR-005 */
            Engine_count = 3;
            break;
        }
         default:
         break;
      }
   }
   else
   {
    ; /* Do nothing */
   }

   /* hdudispfmenu-CalibrationSelectText10Inch-DB-LLR-006 */
   return(Calibration_text_10inch);
}

/*
 * Function                : EngCalibrationSelectTxt10Inch
 *
 * Description             : This function selects the required item in the menu (MIN Q or
 *                           SHAFT FACTOR) using the encoder.
 *
 * Formal parameter(s)     : None
 *
 * Return Value            : T_CHAR* - encoder page text
 *
 * Assumption              : None
 *
 */
T_CHAR *EngCalibrationSelectTxt10Inch(void)
{
       /*  hdudispfmenu-EngCalibrationSelectTxt10Inch-DB-LLR-001 */
	U8_selected_engine_offset_gain = (T_UINT8)MenuSelectText10Inch(Offsetgain_text
	                        ,(T_INT8) U8_selected_engine_offset_gain
	                        ,Switches.b3
	                        ,2
	                        );


	if((T_INT8)ZERO != Switches.b4)
	{
	   switch(U8_selected_engine_offset_gain)
	   {
	      case ZERO:
	      {
		   /*  hdudispfmenu-EngCalibrationSelectTxt10Inch-DB-LLR-002 */
	         MenuPush(Offset_value_menu);
	         break;
	      }
	      case ONE:
	      {
		   /*  hdudispfmenu-EngCalibrationSelectTxt10Inch-DB-LLR-003 */
	         MenuPush(Gain_value_menu);
	         break;
	      }
	      default:
	      break;
	    }
	}
	else
    {
	   ; /* Do nothing */
	}
 /*  hdudispfmenu-EngCalibrationSelectTxt10Inch-DB-LLR-004 */
  return(Offsetgain_text);
}


/*
 * Function                : ParamCalibriSlctTxt10Inch
 *
 * Description             : This function selects the required item in the menu (cooldown or
 *                           system info) using the encoder.
 *
 * Formal parameter(s)     : None
 *
 * Return Value            : T_CHAR* - encoder page text
 *
 * Assumption              : None
 *
 */
T_CHAR *ParamCalibriSlctTxt10Inch(void)
{
        /*hdudispfmenu-ParamCalibrationSelectTxt10Inch-DB-LLR-001 */
	U8_selected_engine_offset_gain = (T_UINT8)MenuSelectText10Inch(Offsetgain_text
                        ,(T_INT8) U8_selected_engine_offset_gain
                        ,Switches.b3
                        ,2
                        );


   if((T_INT8)ZERO != Switches.b4)
   {
      switch(U8_selected_engine_offset_gain)
      {
         case ZERO:
         {
         /* hdudispfmenu-ParamCalibrationSelectTxt10Inch-DB-LLR-002 */
            /*MenuPush(offset_value); */
            break;
         }
         case ONE:
         {
         /* hdudispfmenu-ParamCalibrationSelectTxt10Inch-DB-LLR-003 */
           /* MenuPush(gain_value); */
            break;
         }
         default:
         break;
      }
   }
   else
   {
    ; /* Do nothing */
   }
      /* hdudispfmenu-ParamCalibrationSelectTxt10Inch-DB-LLR-004 */
   return(Offsetgain_text);
}


/*
 * Function                : OffsetInttoIntArray
 *
 * Description             : This function converts offset integer to array
 *
 * Formal parameter(s)     : T_UINT8 sdi - IN Identifier Value
 *
 * Return Value            : None
 *
 * Assumption              : None
 *
 */

void OffsetInttoIntArray(T_UINT8 sdi)
{
    T_UINT8 loop_i = 0;
    T_UINT32 temp_value[NUMBEROFENGINES] = {0};
    T_UINT32 power = 0;

    /* hdudispfmenu-OffsetInttoIntArray-DB-LLR-001 */
    temp_value[sdi] = Offset_value_cal[sdi];

    for (loop_i = 0; loop_i < OFFSET_LENGTH; loop_i++)
    {
        /* hdudispfmenu-OffsetInttoIntArray-DB-LLR-002 */
        power = (T_UINT32)(CalculatePower(TEN,(T_INT32)(OFFSET_LENGTH - (loop_i  + ONE))));
        Offset_value[sdi][loop_i] = (T_UINT16)(temp_value[sdi] / power);
        temp_value[sdi] %= power;
    }
}


/*
 * Function                : GainInttoIntArray
 *
 * Description             : This function converts Gain integer to array
 *
 * Formal parameter(s)     : T_UINT8 sdi- IN-Identifier Value
 *
 * Return Value            : None
 *
 * Assumption              : None
 *
 */

void GainInttoIntArray(T_UINT8 sdi)
{
    T_UINT8 loop_i = 0;
    T_UINT32 temp_value[NUMBEROFENGINES] = {0};
    T_UINT32 power = 0;

      /* hdudispfmenu-GainInttoIntArray-DB-LLR-001 */
    temp_value[sdi] = Gain_value_cal[sdi];

    for (loop_i = 0; loop_i < GAIN_LENGTH; loop_i++)
    {
        /* hdudispfmenu-GainInttoIntArray-DB-LLR-002 */
        power = (T_UINT32)(CalculatePower(TEN,(T_INT32)(GAIN_LENGTH - (loop_i  + ONE))));
        Gain_value[sdi][loop_i] = (T_UINT16)(temp_value[sdi] / power);
        temp_value[sdi] %= power;
    }
}


/*
 * Function                : OffsetValueText
 *
 * Description             : This function selects the required item in the menu (cooldown or
 *                           system info) using the encoder.
 *
 * Formal parameter(s)     : None
 *
 * Return Value            : T_CHAR* - encoder page text
 *
 * Assumption              : None
 *
 */
T_CHAR *OffsetValueText(void)
{
    T_CHAR string_temp[1] = "";
	T_UINT8 loop_i = 0;
	T_UINT8 loop_k = 0;

     /* Move to the position of the digit to be changed*/
 	if ((T_INT8)ZERO != Switches.b2)
	{

 		Offset_digit[Engine_count] =(T_UINT8) (Offset_digit[Engine_count] +ONE);
 		/*if digit count is greater than length, then loop to first digit*/
 		if (Offset_digit[Engine_count] >= OFFSET_LENGTH)
 		{
		/* hdudispfmenu-OffsetValueText-DB-LLR-001 */
 			Offset_digit[Engine_count] = 0;
 		}
	}
    /* Increment the digit when scroll button is pressed*/
	if((T_INT8)ZERO != Switches.b3)
    {
   	   ++Offset_value[Engine_count][Offset_digit[Engine_count]];
         /*if digit is greater than NINE loop to zero*/
   	   if (Offset_value[Engine_count][Offset_digit[Engine_count]] > NINE)
   	   {
	   /* hdudispfmenu-OffsetValueText-DB-LLR-002 */
   		Offset_value[Engine_count][Offset_digit[Engine_count]] = 0;
   	   }
    }
     /* Conversion of array of int to string for displaying*/
    for (loop_i = 0; loop_i<OFFSET_LENGTH; loop_i++)
    {
        /* hdudispfmenu-OffsetValueText-DB-LLR-003 */
        IntToStringTrim((T_UINT8)Offset_value[Engine_count][loop_i], 1, string_temp);
       Offset_value_string[Engine_count][loop_i] = *string_temp;
       /*   Reverse the selected digit*/
       Offset_value_string[Engine_count][Offset_digit[Engine_count]] |= ONEHUNDRED_TWENTY_EIGHT;
    }

    /* Set the value*/
    if((T_INT8)ZERO != Switches.b4)
    {
    /* hdudispfmenu-OffsetValueText-DB-LLR-004 */
        /* convert array of int to int*/
        Offset_value_cal[Engine_count] = 0;
        for (loop_k=0 ; loop_k < OFFSET_LENGTH ; loop_k++)
        {
            /* hdudispfmenu-OffsetValueText-DB-LLR-005 */
            Offset_value_cal[Engine_count] *= TEN;
            Offset_value_cal[Engine_count] +=
                     Offset_value[Engine_count][loop_k];
        }
            /* hdudispfmenu-OffsetValueText-DB-LLR-006 */
        OffsideCalibrationA825(Engine_count, LABEL_051);
        /* Return to previous screen once set*/
         MenuPop();
    }
    else
    {
        ; /* Do nothing */
    }
         /* hdudispfmenu-OffsetValueText-DB-LLR-007 */
   return(Offset_value_string[Engine_count]);
}


/*
 * Function                : GainValueText
 *
 * Description             : This function selects the required item in the menu (cooldown or
 *                           system info) using the encoder.
 *
 * Formal parameter(s)     : None
 *
 * Return Value            : T_CHAR* - encoder page text
 *
 * Assumption              : None
 *
 */
T_CHAR *GainValueText(void)
{
    T_CHAR string_temp[1] = "";
    T_UINT8 loop_i = 0;
    T_UINT8 loop_k = 0;

    if ((T_INT8)ZERO != Switches.b2)
	{
	  /* hdudispfmenu-GainValueText-DB-LLR-001 */
    	Gain_digit[Engine_count] =(T_UINT8) (Gain_digit[Engine_count] + ONE);
 		if (Gain_digit[Engine_count] >= GAIN_LENGTH)
 		{
 			Gain_digit[Engine_count] = 0;
 		}
	}

	if((T_INT8)ZERO != Switches.b3)
    {
	  /* hdudispfmenu-GainValueText-DB-LLR-002 */
   	   ++Gain_value[Engine_count][Gain_digit[Engine_count]];
   	   if (Gain_value[Engine_count][Gain_digit[Engine_count]] > NINE)
   	   {
   		   Gain_value[Engine_count][Gain_digit[Engine_count]] = 0;
   	   }
    }
	/* hdudispfmenu-GainValueText-DB-LLR-003 */
    for (loop_i = 0; loop_i<GAIN_LENGTH; loop_i++)
    {
        IntToStringTrim((T_UINT8)Gain_value[Engine_count][loop_i],ONE, string_temp);
       Gain_value_string[Engine_count][loop_i] = *string_temp;

       /*   Reverse the selected digit */
       Gain_value_string[Engine_count][Gain_digit[Engine_count]] |= ONEHUNDRED_TWENTY_EIGHT;
    }

    if((T_INT8)ZERO != Switches.b4)
    {
        /* hdudispfmenu-GainValueText-DB-LLR-004 */
        Gain_value_cal[Engine_count] = 0;
        /* hdudispfmenu-GainValueText-DB-LLR-005 */
        for (loop_k=0 ; loop_k < GAIN_LENGTH ; loop_k++)
        {
            Gain_value_cal[Engine_count] *= TEN;
            Gain_value_cal[Engine_count] += Gain_value[Engine_count][loop_k];
        }
        /* hdudispfmenu-GainValueText-DB-LLR-006 */
        OffsideCalibrationA825(Engine_count, LABEL_052);
        MenuPop();
    }
    else
    {
        ; /* Do nothing */
    }
		/* hdudispfmenu-GainValueText-DB-LLR-007 */
   return(Gain_value_string[Engine_count]);
}


/*
 * Function                : EncoderPageItemSelectText
 *
 * Description             : This function selects the required page(primary, secondary and so on)
 *                            using the encoder.
 *
 * Formal parameter(s)     : None
 *
 * Return Value            : T_CHAR* - encoder page text
 *
 * Assumption              : None
 *
 */
T_CHAR* EncoderPageItemSelectText(void)
{
 /* updated for PR 100083 */
   T_UINT8 u8_ctr=0;
   T_CHAR *pc_text=0;

   /* hdudispfmenu-EncoderPageItemSelectText-DB-LLR-001 */
   U8_selected_page_item = (T_UINT8)MenuSelectText(Encoder_page_text
                                 ,(T_INT8) U8_selected_page_item
                                 ,Switches.sRE.twist
                                 ,(T_INT8)(Max_num_of_pages-ONE)
                                 );

   Switches.sRE.twist = ZERO;

   /* Updated for PR 100083 */
   /* hdudispfmenu-EncoderPageItemSelectText-DB-LLR-008 */
   Encoder_page_select.s16PixWidth= (T_INT16)(Page_name_char_cnt*SMALL_FONT_WIDTH);
   Encoder_page_select.s16ULX= (T_INT16)(USABLE_LRX-Encoder_page_select.s16PixWidth-
                            PAGE_LIST_FRAME_WIDTH-PAGE_LIST_MARGIN);
   if(Max_num_of_pages<=SIX)
   {
       /* hdudispfmenu-EncoderPageItemSelectText-DB-LLR-009 */
       Encoder_page_select.s16PixHeight= (T_INT16)(Max_num_of_pages*NORMAL_FONT_HEIGHT);
       u8_ctr=0;
       Encoder_page_select.s16ULY= (T_INT16)(USABLE_LRY-Encoder_page_select.s16PixHeight-
                            PAGE_LIST_FRAME_WIDTH-PAGE_LIST_MARGIN);
   }
   else
   {
     /* hdudispfmenu-EncoderPageItemSelectText-DB-LLR-010 */
     if(U8_selected_page_item >= FOUR)
     {
       u8_ctr= (T_UINT8)(U8_selected_page_item-FOUR);
     }
     else
     {
        ;/* Does nothing */
     }
     Encoder_page_select.s16PixHeight= (T_INT16)(SEVEN*(NORMAL_FONT_HEIGHT-SEVEN));
     Encoder_page_select.s16ULY= (T_INT16)(USABLE_LRY-Encoder_page_select.s16PixHeight -
                              PAGE_LIST_FRAME_WIDTH-PAGE_LIST_MARGIN);
   }

   /* hdudispfmenu-EncoderPageItemSelectText-DB-LLR-005 */
   if((T_INT8)ZERO != Switches.sRE.pressed)
   {
    /* updated for PR 100083 */
      MenuSwitchPage(U8_selected_page_item+1);
      MenuReset(Top_menu, U8_selected_page_item+1);
      OffsideSwitchScreen((T_UINT8)(U8_selected_page_item+1));
   }
   else
   {
    ; /* Do nothing */
   }

   /* hdudispfmenu-EncoderPageItemSelectText-DB-LLR-006 */
   pc_text= Encoder_page_text;

   /* hdudispfmenu-EncoderPageItemSelectText-DB-LLR-007 */
   while(ZERO != u8_ctr)
   {
    while(*pc_text != ZERO)
       {
          if(('\r' == *pc_text)||('\n' == *pc_text ))
          {
             while(('\r' == *pc_text)||('\n' == *pc_text))
             {
                pc_text += ONE;
             }
             break;
          }
          else
          {
            ; /* Do nothing */
          }
          pc_text += ONE;
       }
      u8_ctr = (T_UINT8)(u8_ctr - ONE);
   }

   /* hdudispfmenu-EncoderPageItemSelectText-DB-LLR-004 */
   return (pc_text);
}

/*
 *
 * Function                : ButtonPageItemSelectText
 *
 * Description             : This function selects the required page(primary, secondary and so on)
 *
 * Formal parameter(s)     : None
 *
 * Return Value            : T_CHAR* - button 7 page text
 *
 * Assumption              : None
 *
 */
T_CHAR* ButtonPageItemSelectText(void)
{
   T_UINT8 u8_ctr=0;
   T_CHAR *pc_text=0;

   /* hdudispfmenu-ButtonPageItemSelectText-DB-LLR-001 */
   U8_selected_page_item = (T_UINT8)MenuSelectText10Inch(Encoder_page_text
                                 ,(T_INT8) U8_selected_page_item
                                 ,Switches.b3
                                 ,(T_INT8)(Max_num_of_pages-ONE)
                                 );


   Button_page_select.s16PixWidth= (T_INT16)(Page_name_char_cnt*SMALL_FONT_WIDTH);
   Button_page_select.s16ULX= (T_INT16)(USABLE_LRX_10INCH-Button_page_select.s16PixWidth-
                            PAGE_LIST_FRAME_WIDTH-PAGE_LIST_MARGIN-PAGE_LIST_10INCH_WIDTH);
   if(Max_num_of_pages<=SIX)
   {
       /* hdudispfmenu-ButtonPageItemSelectText-DB-LLR-002 */
	   Button_page_select.s16PixHeight= (T_INT16)(Max_num_of_pages*NORMAL_FONT_HEIGHT);
       u8_ctr=0;
       Button_page_select.s16ULY= (T_INT16)(USABLE_LRY_10INCH-Button_page_select.s16PixHeight-
                            PAGE_LIST_FRAME_WIDTH-PAGE_LIST_MARGIN-PAGE_LIST_10INCH_HEIGHT);
   }
   else
   {
     /* hdudispfmenu-ButtonPageItemSelectText-DB-LLR-003 */
     if(U8_selected_page_item >= FOUR)
     {
       u8_ctr= (T_UINT8)(U8_selected_page_item-FOUR);
     }
     else
     {
        ;/* Does nothing */
     }
     Button_page_select.s16PixHeight= (T_INT16)(SEVEN*(NORMAL_FONT_HEIGHT-SEVEN));
     Button_page_select.s16ULY= (T_INT16)(USABLE_LRY_10INCH-Button_page_select.s16PixHeight -
                              PAGE_LIST_FRAME_WIDTH-PAGE_LIST_MARGIN-PAGE_LIST_10INCH_HEIGHT);
   }

   /* hdudispfmenu-ButtonPageItemSelectText-DB-LLR-004 */
   if((T_INT8)ZERO != Switches.b4)
   {
      MenuSwitchPage(U8_selected_page_item+DEC_ONE);
      MenuReset(Top_menu, U8_selected_page_item+DEC_ONE);
      OffsideSwitchScreen((T_UINT8)(U8_selected_page_item+DEC_ONE));
   }
   else
   {
    ; /* Do nothing */
   }

   /* hdudispfmenu-ButtonPageItemSelectText-DB-LLR-005 */
   pc_text= Encoder_page_text;

   /* hdudispfmenu-ButtonPageItemSelectText-DB-LLR-006 */
   while(ZERO != u8_ctr)
   {
    while(*pc_text != ZERO)
       {
          if(('\r' == *pc_text)||('\n' == *pc_text ))
          {
             while(('\r' == *pc_text)||('\n' == *pc_text))
             {
                pc_text += ONE;
             }
             break;
          }
          else
          {
            ; /* Do nothing */
          }
          pc_text += ONE;
       }
      u8_ctr = (T_UINT8)(u8_ctr - ONE);
   }

   /* hdudispfmenu-ButtonPageItemSelectText-DB-LLR-007 */
   return ((T_CHAR *)pc_text);
}

/*
 * Function                : MessageBoxText
 *
 * Description             : The function displays the messages.
 *
 * Formal parameter(s)     : None
 *
 * Return Value            : T_CHAR*  - returns messages
 *
 * Assumption              : None
 *
 */
T_CHAR *MessageBoxText(void)
{
   /* hdudispfmenu-MessageBoxText-DB-LLR-001 */
   New_message = FALSE;

   if((T_INT8)ZERO != Switches.sRE.twist)
   {
      /* hdudispfmenu-MessageBoxText-DB-LLR-002 */
      S16_message_index = (T_INT16)(S16_message_index + Switches.sRE.twist);

      /* hdudispfmenu-MessageBoxText-DB-LLR-003 */
      if(S16_message_index < (T_INT16)ZERO)
      {
         S16_message_index = (T_INT16)ZERO;
      }
      Switches.sRE.twist = (T_INT8)ZERO;
   }
   else
   {
    ; /* Do nothing */
   }

   /* hdudispfmenu-MessageBoxText-DB-LLR-004 */
   S16_message_index = ParaGetMessageCount(S16_message_index);
   /* Updated for PR 100083 */
   Message_cnt = BuildMessageList();
   if(Message_cnt > (T_INT16)TEN)
   {
      Message_text_box.s16PixHeight = (T_INT16)(MESSAGE_BOX_HEIGHT +
                                            ((LISTBOX_CHAR_HEIGHT+FIVE)*NINE));
      if((S16_message_index+(T_INT16)TEN) >= Message_cnt)
      {
         S16_message_index=(T_INT16)(Message_cnt-(T_INT16)TEN);
      }
      else
      {
         ;
      }
   }
   else
   {
      Message_text_box.s16PixHeight = (T_INT16)(MESSAGE_BOX_HEIGHT +
                                      ((LISTBOX_CHAR_HEIGHT+DEC_FIVE)*(Message_cnt-DEC_ONE)));
      TextBoxOff(&Scroll_button);
      S16_message_index=((T_INT16)ZERO);
   }

   if(S16_message_index >= ((T_INT16)ZERO))
   {
      return((T_CHAR *)&(Message_list[S16_message_index]));
   }
   else
   {
       /*hdudispfmenu-MessageBoxText-DB-LLR-005 */
      S16_message_index = (T_INT16)ZERO;
      return((T_CHAR *)Pc_empty_message_list);
   }
}

/*
 * Function                : ExitButtonText
 *
 * Description             : The function displays the exit button text.
 *
 * Formal parameter(s)     : None
 *
 * Return Value            : T_CHAR * - returns EXIT message
 *
 * Assumption              : None
 *
 */
T_CHAR *ExitButtonText(void)
{
   if (E_7_INCH == Display_size)
   {
	   if((T_INT8)ZERO != Switches.b2)
       {
          /* hdudispfmenu-ExitButtonText-DB-LLR-001 */
          MenuReset(Top_menu, Page_number);
       }
       else
       {
        ; /* Do nothing */
       }
   }
   else if (E_10_INCH == Display_size )
   {
   	   if((T_INT8)ZERO != Switches.b5)
       {
	   /* hdudispfmenu-ExitButtonText-DB-LLR-003 */
          MenuReset(Top_menu, Page_number);
       }
       else
       {
         ; /* Do nothing */
       }
    }

   /* hdudispfmenu-ExitButtonText-DB-LLR-002 */
   return(&Exit_text[0]);
}

/*
 * Function                : BackButtonText
 *
 * Description             : The function displays the back button text.
 *
 * Formal parameter(s)     : None
 *
 * Return Value            : T_CHAR * - returns BACK message
 *
 * Assumption              : None
 *
 */
T_CHAR *BackButtonText(void)
{
   if (E_7_INCH == Display_size)
   {
       if((T_INT8)ZERO != Switches.b3)
       {
          /* hdudispfmenu-BackButtonText-DB-LLR-001 */
          MenuPop();
       }
       else
       {
        ; /* Do nothing */
       }
   }
   else if (E_10_INCH == Display_size)
   {
       if((T_INT8)ZERO != Switches.b7)
       {
          /* hdudispfmenu-BackButtonText-DB-LLR-003 */
          MenuPop();
       }
       else
       {
        ; /* Do nothing */
       }
   }

   /* hdudispfmenu-BackButtonText-DB-LLR-002 */
   return(&Back_text[0]);
}

/*
 * Function                : ScrollButtonText
 *
 * Description             : The function displays the scroll button text.
 *
 * Formal parameter(s)     : None
 *
 * Return Value            : T_CHAR * - returns SCROLL message
 *
 * Assumption              : None
 *
 */
T_CHAR *ScrollButtonText(void)
{
   /* hdudispfmenu-ScrollButtonText-DB-LLR-001 */
   return(&Scroll_text[0]);
}

/*
 * Function                : CoolDownOnOffButtonText
 *
 * Description             : The function selects the cool down state(on/off) from the menu.
 *
 * Formal parameter(s)     : None
 *
 * Return Value            : T_CHAR * - returns ON or OFF state
 *
 * Assumption              : None
 *
 */

T_CHAR *CoolDownOnOffButtonText(void)
{
   if((T_INT8)ZERO != Switches.b4)
   {
      if(ECOOLDOWN_ON == Cool_down_state)
      {
         /* hdudispfmenu-CoolDownOnOffButtonText-DB-LLR-001 */
         Cool_down_state = ECOOLDOWN_OFF;
         /* Updated as per PR 100083 */
         Cool_down_select = FALSE;
      }
      else
      {
         /* hdudispfmenu-CoolDownOnOffButtonText-DB-LLR-002 */
         Cool_down_state = ECOOLDOWN_ON;
         /* Updated as per PR 100083 */
         Cool_down_select = TRUE;
      }

      /* hdudispfmenu-CoolDownOnOffButtonText-DB-LLR-003 */
      Switches.b4 = ZERO;
   }

   /* hdudispfmenu-CoolDownOnOffButtonText-DB-LLR-004 */
   if(ECOOLDOWN_ON == Cool_down_state)
   {
      return(&On_text[0]);
   }
   else
   {
      return(&Off_text[0]);
   }
}

/*
 *
 * Function                : ManTimerOnOffText
 *
 * Description             : The function selects the manual timer state(on/off) from the menu.
 *
 * Formal parameter(s)     : None
 *
 * Return Value            : T_CHAR * - returns STRT or STOP state
 *
 * Assumption              : None
 *
 */

T_CHAR *ManTimerOnOffText(void)
{
   if((T_INT8)ZERO != Switches.b6)
   {
      if(MAN_TIMER_OFF == Man_timer_state)
      {
         /* hdudispfmenu-ManTimerOnOffText-DB-LLR-001 */
         OffsideTimerStart(Manual_timer);
         ManualTimerStart();
      }
      else
      {
         /* hdudispfmenu-ManTimerOnOffText-DB-LLR-002 */
         OffsideTimerStop(Manual_timer);
         ManualTimerStop();
      }
      Switches.b6 = (T_INT8)ZERO;
   }

   /* hdudispfmenu-ManTimerOnOffText-DB-LLR-003 */
   if(MAN_TIMER_OFF == Man_timer_state)
   {
      return(&Strt_text[0]);
   }
   else
   {
      return(&Stop_text[0]);
   }
}

/*
 * Function                : ManualTimerResetButtonText
 *
 * Description             : The function resets the manual timer.
 *
 * Formal parameter(s)     : None
 *
 * Return Value            : T_CHAR * -  returns reset text
 *
 * Assumption              : None
 *
 */
T_CHAR *ManualTimerResetButtonText(void)
{
   if((T_INT8)ZERO != Switches.b7)
   {
      /* hdudispfmenu-ManualTimerResetButtonText-DB-LLR-001 */
      OffsideTimerReset();
      ManualTimerReset();
      Switches.b7 = (T_INT8)ZERO;
   }
   else
   {
    ; /* Do nothing */
   }

   /* hdudispfmenu-ManualTimerResetButtonText-DB-LLR-002 */
   /* updated as per PR 100083 */
   return(&Rst_text[0]);
}

/*
 * Function                : DummyButtonText
 *
 * Description             : The function returns dummy message.
 *
 * Formal parameter(s)     : None
 *
 * Return Value            : T_CHAR * -  returns dummy message
 *
 * Assumption              : None
 *
 */
T_CHAR *DummyButtonText(void)
{
   /* hdudispfmenu-DummyButtonText-DB-LLR-001 */
   return(&Err_text[0]);
}


/*
 * Function                : SetButtonText
 *
 * Description             : This function enables the  options
 *
 * Formal parameter(s)     : None
 *
 * Return Value            : T_CHAR * - Pointer to character
 *
 * Assumption              : None
 *
 */
T_CHAR *SetButtonText(void)
{
   if((T_INT8)ZERO != Switches.b2)
   {
      /* hdudispfmenu-SetButtonText-DB-LLR-001 */
      ;
   }
   else
   {
    ; /* Do nothing */
   }
     /* hdudispfmenu-SetButtonText-DB-LLR-002 */
  return(&Set_text[0]);
}

/*
 * Function                : TopButton1Text
 *
 * Description             : The function swaps to reversionary page,
 *                           if already present swaps to previously present page.
 *
 * Formal parameter(s)     : None
 *
 * Return Value            : T_CHAR * - Pointer to character
 *
 * Assumption              : None
 *
 */
T_CHAR *TopButton1Text(void)
{
   if((T_UINT8)ZERO != Switches.b1)
   {
      if(Page_number != EPAGE0)
      {
         /* hdudispfmenu-TopButton1Text-DB-LLR-001 */
         /* updated as per PR 100083 */
         if(Page_number <= (Max_num_of_pages-ONE))
         {
            Toggle_screen = Page_number;
         }
         else
         {
            ;/* Does nothing */
         }
         if(Toggle_screen > (Max_num_of_pages-ONE))
         {
            Toggle_screen = EPAGE1;
         }
         else
         {
            ;/* Does nothing */
         }

         MenuSwitchPage(EPAGE0);
      }
      else
      {
         /* hdudispfmenu-TopButton1Text-DB-LLR-002 */
         MenuSwitchPage(Toggle_screen);
         OffsideSwitchScreen((T_UINT8)Toggle_screen);
      }
   }
   else
   {
    ; /* Do nothing */
   }

   /* hdudispfmenu-TopButton1Text-DB-LLR-003 */
   return(&Rev_text[0]);
}

/*
 * Function                : TopButton2Text10Inch
 *
 * Description             : This function enables the  options
 *
 * Formal parameter(s)     : None
 *
 * Return Value            : T_CHAR * - Pointer to character
 *
 * Assumption              : None
 *
 */
T_CHAR *TopButton2Text10Inch(void)
{
   if((T_INT8)ZERO != Switches.b2)
   {
      /* hdudispfmenu-TopButton2Text10Inch-DB-LLR-001 */
      ;
   }
   else
   {
    ; /* Do nothing */
   }
    /* hdudispfmenu-TopButton2Text10Inch-DB-LLR-002 */
  return(&Menu_up[0]);
}


/*
 * Function                : TopButton3Text10Inch
 *
 * Description             : This function enables the  options
 *
 * Formal parameter(s)     : None
 *
 * Return Value            : T_CHAR * - Pointer to character
 *
 * Assumption              : None
 *
 */
T_CHAR *TopButton3Text10Inch(void)
{
	/* hdudispfmenu-TopButton3Text10Inch-DB-LLR-001 */
   if((T_INT8)ZERO != Switches.b3)
   {
      ;
   }
   else
   {
    ; /* Do nothing */
   }
   /* hdudispfmenu-TopButton3Text10Inch-DB-LLR-002 */
   return(&Menu_down[0]);
}


/*
 * Function                : TopButton4Text
 *
 * Description             : This function enables the Menu_menu options
 *
 * Formal parameter(s)     : None
 *
 * Return Value            : T_CHAR * - Pointer to character
 *
 * Assumption              : None
 *
 */
T_CHAR *TopButton4Text(void)
{
   if((T_INT8)ZERO != Switches.b4)
   {
      /* hdudispfmenu-TopButton4Text-DB-LLR-001 */
      MenuPush(Menu_menu);
      Switches.b4 = (T_INT8)ZERO;
   }
   else
   {
    ; /* Do nothing */
   }

   /* hdudispfmenu-TopButton4Text-DB-LLR-002 */
   return(&Menu_text[0]);
}

/*
 * Function                : TopButton4Text10Inch
 *
 * Description             : This function enables the Menu_menu options
 *
 * Formal parameter(s)     : None
 *
 * Return Value            : T_CHAR * - Pointer to character
 *
 * Assumption              : None
 *
 */
T_CHAR *TopButton4Text10Inch(void)
{
   if((T_INT8)ZERO != Switches.b4)
   {
      /* hdudispfmenu-TopButton4Text10Inch-DB-LLR-001 */
      MenuPush(Menu_menu_10inch);
      Switches.b4 = (T_INT8)ZERO;
   }
   else
   {
    ; /* Do nothing */
   }

   /* hdudispfmenu-TopButton4Text10Inch-DB-LLR-002 */
   return(&Menu_text[0]);
}

/*
 * Function                : TopButton5Text
 *
 * Description             : This function sets the active EIU to EIU1 or EIU2.
 *
 * Formal parameter(s)     : None
 *
 * Return Value            : T_CHAR * - Pointer to character
 *
 * Assumption              : None
 *
 */
T_CHAR *TopButton5Text(void)
{
   if((T_INT8)ZERO != Switches.b5)
   {
      if(EIU1 == Active_eiu)
      {
         /* hdudispfmenu-TopButton5Text-DB-LLR-001 */
         Active_eiu = EIU2;
      }
      else
      {
         /* hdudispfmenu-TopButton5Text-DB-LLR-002 */
         Active_eiu = EIU1;
      }

      /* hdudispfmenu-TopButton5Text-DB-LLR-003 */
      Switches.b5 =(T_INT8)ZERO;
      GlobalSettingsSetEIU(Active_eiu);
   }

   if(EIU1 == Active_eiu)
   {
      /* hdudispfmenu-TopButton5Text-DB-LLR-004 */
      return(&Eiu2_text[0]);
   }
   else
   {
      /* hdudispfmenu-TopButton5Text-DB-LLR-005 */
      return(&Eiu1_text[0]);
   }
}

/*
 * Function                : TopButton6Text
 *
 * Description             : This function enables the Top_button_6 options
 *
 * Formal parameter(s)     : None
 *
 * Return Value            : T_CHAR * - Pointer to character
 *
 * Assumption              : None
 *
 */
T_CHAR *TopButton6Text(void)
{
   T_INT16  s16_message_cnt = ZERO;

   /* hdudispfmenu-TopButton6Text-DB-LLR-001 */
   s16_message_cnt = ParaGetMessageCount(ZERO);

   if(s16_message_cnt >= (T_INT16)ZERO)
   {
      /* hdudispfmenu-TopButton6Text-DB-LLR-002 */
      Top_button_6.eBackGroundColor= Page_settings.menu_color;
      Top_button_6.eFontColor = Page_settings.menu_txt_color;

      if(ZERO != (New_message))
      {
         /* hdudispfmenu-TopButton6Text-DB-LLR-003 */
         TextBoxFlash(&Top_button_6);
      }
      else
      {
         /* hdudispfmenu-TopButton6Text-DB-LLR-004 */
         TextBoxNoFlash(&Top_button_6);
      }

      if((T_INT8)ZERO != Switches.b6)
      {
         /* hdudispfmenu-TopButton6Text-DB-LLR-005 */
         S16_message_index = (T_INT16)ZERO;
         MenuPush(Msg_menu);
      }
      else
      {
       ; /* Do nothing */
      }
   }
   else
   {
     /* hdudispfmenu-TopButton6Text-DB-LLR-006 */
     /* updated as per PR 100083 */
     TextBoxOff(Top_menu[5]);
      Top_button_6.eBackGroundColor=BLACK;
      Top_button_6.eFontColor = BLACK;
   }

   /* hdudispfmenu-TopButton6Text-DB-LLR-007 */
   return(&Msg_text[0]);
}

/*
 * Function                : TopButton7Text
 *
 * Description             : This function enables the Timer_menu options.
 *
 * Formal parameter(s)     : None
 *
 * Return Value            : T_CHAR * - Pointer to character
 *
 * Assumption              : None
 *
 */
T_CHAR *TopButton7Text(void)
{
   if((T_INT8)ZERO != Switches.b7)
   {
      /* hdudispfmenu-TopButton7Text-DB-LLR-001 */
      MenuPush(Timer_menu);
   }
   else
   {
    ; /* Do nothing */
   }

   /* hdudispfmenu–TopButton7Text-DB-LLR-003 */
   return(&Tmr_text[0]);
}

/*
 * Function                : PageButtonText
 *
 * Description             : This function enables the Page_menu options.
 *
 * Formal parameter(s)     : None
 *
 * Return Value            : T_CHAR * - Pointer to character
 *
 * Assumption              : None
 *
 */
T_CHAR *PageButtonText(void)
{
    /* hdudispfmenu-PageButtonText-DB-LLR-001 */
	if (E_7_INCH == Display_size)
	{
		if((T_INT8)ZERO != Switches.sRE.pressed)
		{
			   if(ZERO == ((Page_settings.page_menu >> 1) & 1))
			   {
				    MenuPush(Page_menu_1);
			   }
			   else
			   {
			        MenuPush(Page_menu);
			   }
		}
		else
		{
			;
		}
	}
	else if (E_10_INCH == Display_size)
	{
		if((T_INT8)ZERO != Switches.b2)
		{
			   if(ZERO == ((Page_settings.page_menu >> 1) & 1))
			   {
				   MenuPush(Page_menu_10inch_1);
			   }
			   else
			   {
				   MenuPush(Page_menu_10inch);
			   }
		}
	}

   /* hdudispfmenu-PageButtonText-DB-LLR-002 */
   return(&Page_text[0]);
}


/*
 * Function                : TopButton10Text
 *
 * Description             : This function enables the set brightness options.
 *
 * Formal parameter(s)     : None
 *
 * Return Value            : T_CHAR * - Pointer to character
 *
 * Assumption              : None
 *
 */
T_CHAR *TopButton10Text(void)
{
   if((T_INT8)ZERO != Switches.b10)
   {
   /* hdudispfmenu-TopButton10Text-DB-LLR-001 */
      MenuPush(Timer_menu);
   }
   else
   {
    ; /* Do nothing */
   }
     /* hdudispfmenu-TopButton10Text-DB-LLR-002 */
   return(&Brt_set_text[0]);
}


/*
 * Function                : TopButton6Text10Inch
 *
 * Description             : This function enables the the brightness minus options.
 *
 * Formal parameter(s)     : None
 *
 * Return Value            : T_CHAR * - Pointer to character
 *
 * Assumption              : None
 *
 */

T_CHAR *TopButton6Text10Inch(void)
{
   if((T_INT8)ZERO != Switches.b6)
   {
       /* hdudispfmenu-TopButton6Text10Inch-DB-LLR-001 */
	   ;
   }
   else
   {
	   ;/* Do nothing */
   }
    /* hdudispfmenu-TopButton6Text10Inch-DB-LLR-002 */
   return(&Brt_minus_text[0]);
}


/*
 * Function                : TopButton7Text10Inch
 *
 * Description             : This function enables the the brightness plus options.
 *
 * Formal parameter(s)     : None
 *
 * Return Value            : T_CHAR * - Pointer to character
 *
 * Assumption              : None
 *
 */


T_CHAR *TopButton7Text10Inch(void)
{
   if((T_INT8)ZERO != Switches.b7)
   {
   /* hdudispfmenu-TopButton7Text10Inch-DB-LLR-001 */
      ;
   }
   else
   {
    ; /* Do nothing */
   }
         /* hdudispfmenu-TopButton7Text10Inch-DB-LLR-002 */
   return(&Brt_plus_text[0]);

}




/*
 * Function                : TopButton13Text
 *
 * Description             : The function configures brightness factor.
 *
 * Formal parameter(s)     : None
 *
 * Return Value            : T_CHAR * - Pointer to character
 *
 * Assumption              : None
 *
 */
T_CHAR *TopButton13Text(void)
{
   static T_INT8  s8_had_max = ZERO;
   static T_INT8  s8_had_min = ZERO;
   static T_INT8  s8_max_min_timer = MIN_MAX_ITTR;

   T_INT16 s16_delta = ZERO;
   T_INT16 s16_auto_brightness_temp = ZERO;

   /* hdudispfmenu-TopButton13Text-DB-LLR-001 */
   s16_auto_brightness_temp = Auto_brightness;

   if(((s8_max_min_timer++) > (T_INT8)MIN_MAX_ITTR) || (Switches.sLE.pressed))
   {
      /* hdudispfmenu-TopButton13Text-DB-LLR-002 */
      s8_had_max = (T_INT8)ZERO;
      s8_had_min = (T_INT8)ZERO;
      s8_max_min_timer = (T_INT8)MIN_MAX_ITTR;
   }
   else
   {
    ; /* Do nothing */
   }

   if(s8_had_max && (Switches.sLE.twist < (T_INT8)ZERO))
   {
      /* hdudispfmenu-TopButton13Text-DB-LLR-003 */
      s8_max_min_timer = (T_INT8)MIN_MAX_ITTR;
   }
   else if (s8_had_min && (Switches.sLE.twist > (T_INT8)ZERO))
   {
      /* hdudispfmenu-TopButton13Text-DB-LLR-004 */
      s8_max_min_timer = (T_INT8)MIN_MAX_ITTR;
   }
   else
   {
    ; /* Do nothing */
   }

   if((T_INT8)ZERO != (Switches.sLE.twist))
   {
      if(EBRIGHTNESS_MANUAL == Brightness_mode)
      {
         /* hdudispfmenu-TopButton13Text-DB-LLR-005 */
         s16_delta = Manual_brightness/((T_INT16)TEN);

         if(((T_INT16)ZERO) == s16_delta)
         {
            /* hdudispfmenu-TopButton13Text-DB-LLR-006 */
            s16_delta = ONE;
         }
         else
         {
            ; /* Do nothing */
         }

         if(Switches.sLE.twist<((T_INT8)ZERO))
         {
            /* hdudispfmenu-TopButton13Text-DB-LLR-007 */
            s16_delta = (T_INT16)-s16_delta;
         }
         else
         {
          ; /* Do nothing */
         }

         /* hdudispfmenu-TopButton13Text-DB-LLR-008 */
         Manual_brightness =(T_INT16)(Manual_brightness+s16_delta);
      }
      else if(EBRIGHTNESS_AUTO == Brightness_mode)
      {
         /* hdudispfmenu-TopButton13Text-DB-LLR-009 */
         s16_delta = s16_auto_brightness_temp/((T_INT16)TEN);

         if((T_INT16)ZERO == s16_delta)
         {
            /* hdudispfmenu-TopButton13Text-DB-LLR-010 */
            s16_delta = ONE;
         }
         else
         {
          ; /* Do nothing */
         }

         if(Switches.sLE.twist< (T_INT8)ZERO)
         {
            /* hdudispfmenu-TopButton13Text-DB-LLR-011 */
            s16_delta = (T_INT16)-s16_delta;
         }
         else
         {
          ; /* Do nothing */
         }

         /* hdudispfmenu-TopButton13Text-DB-LLR-012 */
         s16_auto_brightness_temp = (T_INT16)(s16_auto_brightness_temp+s16_delta);
      }
   }
   else
   {
    ; /* Do nothing */
   }

   if(Manual_brightness > MAX_MANUAL_BRIGHTNESS)
   {
      /* hdudispfmenu-TopButton13Text-DB-LLR-013 */
      Manual_brightness = MAX_MANUAL_BRIGHTNESS;
      s8_max_min_timer = (T_INT8)ZERO;
      s8_had_max = (T_INT8)ONE;
   }
   else if(Manual_brightness < MIN_MANUAL_BRIGHTNESS)
   {
      /* hdudispfmenu-TopButton13Text-DB-LLR-014 */
      s8_max_min_timer = (T_INT8)ZERO;
      Manual_brightness = MIN_MANUAL_BRIGHTNESS;
      s8_had_min = (T_INT8)ONE;
   }
   else
   {
    ; /* Do nothing */
   }

   if(s16_auto_brightness_temp > MAX_AUTO_BRIGHTNESS)
   {
      /* hdudispfmenu-TopButton13Text-DB-LLR-015 */
      s16_auto_brightness_temp = MAX_AUTO_BRIGHTNESS;
      s8_max_min_timer = (T_INT8)ZERO;
      s8_had_max =(T_INT8)ONE;
   }
   else if(s16_auto_brightness_temp < MIN_AUTO_BRIGHTNESS)
   {
      /* hdudispfmenu-TopButton13Text-DB-LLR-016 */
      s16_auto_brightness_temp = MIN_AUTO_BRIGHTNESS;
      s8_max_min_timer = (T_INT8)ZERO;
      s8_had_min = (T_INT8)ONE;
   }
   else
   {
    ; /* Do nothing */
   }

   if(ZERO != Switches.sLE.pressed)
   {
      if(EBRIGHTNESS_MANUAL == Brightness_mode)
      {
         /* hdudispfmenu-TopButton13Text-DB-LLR-017 */
         Brightness_mode = EBRIGHTNESS_AUTO;
      }
      else
      {
         /* hdudispfmenu-TopButton13Text-DB-LLR-018 */
         Brightness_mode = EBRIGHTNESS_MANUAL;
      }

      /* hdudispfmenu-TopButton13Text-DB-LLR-019 */
      PwmBackLightNewMode(s16_auto_brightness_temp);
   }
   else
   {
    ; /* Do nothing */
   }

   if((T_INT8)ZERO != Switches.sLE.twist)
   {
      /* hdudispfmenu-TopButton13Text-DB-LLR-020 */
      PwmBackLightStepTo(s16_auto_brightness_temp);
   }
   else
   {
    ; /* Do nothing */
   }

   /* hdudispfmenu-TopButton13Text-DB-LLR-021 */
   Switches.sLE.pressed = (T_INT8)ZERO;
   Switches.sLE.twist = (T_INT8)ZERO;

   if(s8_max_min_timer < MIN_MAX_ITTR)
   {
      if(s8_had_min != (T_INT8)ZERO)
      {
         /* hdudispfmenu-TopButton13Text-DB-LLR-022 */
         return(&Min_text[0]);
      }
      else if (s8_had_max != (T_INT8)ZERO)
      {
         /* hdudispfmenu-TopButton13Text-DB-LLR-023 */
         return(&Max_text[0]);
      }
   }
   else
   {
    ; /* Do nothing */
   }

   if(EBRIGHTNESS_AUTO == Brightness_mode)
   {
      /* hdudispfmenu-TopButton13Text-DB-LLR-024 */
      return(&Brt_aut_text[0]);
   }
   else
   {
      /* hdudispfmenu-TopButton13Text-DB-LLR-025 */
      return(&Brt_man_text[0]);
   }
}


/*
 * Function                : TopButton8Text10Inch
 *
 * Description             : The function configures brightness factor.
 *
 * Formal parameter(s)     : None
 *
 * Return Value            : T_CHAR * - Pointer to character
 *
 * Assumption              : None
 *
 */

T_CHAR *TopButton8Text10Inch(void)
{

   static T_INT8  s8_had_max = ZERO;
   static T_INT8  s8_had_min = ZERO;
   static T_INT8  s8_max_min_timer = MIN_MAX_ITTR;

   T_INT16 s16_delta = ZERO;
   T_INT16 s16_auto_brightness_temp = ZERO;

   /* hdudispfmenu-TopButton8Text10Inch-DB-LLR-001 */
   s16_auto_brightness_temp = Auto_brightness;


   if(((s8_max_min_timer++) > (T_INT8)MIN_MAX_ITTR) || (T_INT8)ZERO != Switches.b8)
   {
      /* hdudispfmenu-TopButton8Text10Inch-DB-LLR-002 */
      s8_had_max = (T_INT8)ZERO;
      s8_had_min = (T_INT8)ZERO;
      s8_max_min_timer = (T_INT8)MIN_MAX_ITTR;
   }
   else
   {
    ;  /*Do nothing*/
   }
   if(s8_had_max && (T_INT8)ZERO != Switches.b6 && EBRIGHTNESS_MANUAL == Brightness_mode)
   {
    /* hdudispfmenu-TopButton8Text10Inch-DB-LLR-003 */
      s8_max_min_timer = (T_INT8)MIN_MAX_ITTR;
   }
   if(s8_had_min && (T_INT8)ZERO != Switches.b7 && EBRIGHTNESS_MANUAL == Brightness_mode)
   {
       /* hdudispfmenu-TopButton8Text10Inch-DB-LLR-004 */
       s8_max_min_timer = (T_INT8)MIN_MAX_ITTR;
   }
   else
   {
    ;  /*Do nothing*/
   }

   if(((T_INT8)ZERO != Switches.b7 || (T_INT8)ZERO != Switches.b6))
   {
      if(EBRIGHTNESS_MANUAL == Brightness_mode)
      {
	  /* hdudispfmenu-TopButton8Text10Inch-DB-LLR-005 */
         s16_delta = Manual_brightness/((T_INT16)TEN);

         if(((T_INT16)ZERO) == s16_delta)
         {
		  /* hdudispfmenu-TopButton8Text10Inch-DB-LLR-006 */
            s16_delta = ONE;
         }
         else
         {
            ; /* Do nothing*/
         }

         if((T_INT8)ZERO != Switches.b6)
         {
		 /* hdudispfmenu-TopButton8Text10Inch-DB-LLR-007 */
            s16_delta = (T_INT16)-s16_delta;
         }
         else
         {
          ; /* Do nothing*/
         }
        /* hdudispfmenu-TopButton8Text10Inch-DB-LLR-008 */
         Manual_brightness =(T_INT16)(Manual_brightness+s16_delta);
      }
      else if(EBRIGHTNESS_AUTO == Brightness_mode)
      {
	  /* hdudispfmenu-TopButton8Text10Inch-DB-LLR-009 */
         s16_delta = s16_auto_brightness_temp/((T_INT16)TEN);

       	  if((T_INT16)ZERO == s16_delta)
         {
		 /* hdudispfmenu-TopButton8Text10Inch-DB-LLR-010 */
           s16_delta = ONE;
         }
         else
         {
          ; /* Do nothing*/
         }

         if((T_INT8)ZERO != Switches.b6)
         {
		 /* hdudispfmenu-TopButton8Text10Inch-DB-LLR-011 */
            s16_delta = (T_INT16)-s16_delta;
         }
         else
         {
          ;  /*Do nothing*/
         }
	    /* hdudispfmenu-TopButton8Text10Inch-DB-LLR-012 */
        s16_auto_brightness_temp = (T_INT16)(s16_auto_brightness_temp+s16_delta);
      }
   }
   else
   {
    ;  /*Do nothing*/
   }

   if(Manual_brightness > MAX_MANUAL_BRIGHTNESS)
   {
   	  /* hdudispfmenu-TopButton8Text10Inch-DB-LLR-013 */
      Manual_brightness = MAX_MANUAL_BRIGHTNESS;
      s8_max_min_timer = (T_INT8)ZERO;
      s8_had_max = (T_INT8)ONE;
   }
   else if(Manual_brightness < MIN_MANUAL_BRIGHTNESS)
   {
      /* hdudispfmenu-TopButton8Text10Inch-DB-LLR-014 */
      s8_max_min_timer = (T_INT8)ZERO;
      Manual_brightness = MIN_MANUAL_BRIGHTNESS;
      s8_had_min = (T_INT8)ONE;
   }
   else
   {
    ;  /*Do nothing*/
   }

   if(s16_auto_brightness_temp > MAX_AUTO_BRIGHTNESS)
   {
      /* hdudispfmenu-TopButton8Text10Inch-DB-LLR-015 */
      s16_auto_brightness_temp = MAX_AUTO_BRIGHTNESS;
      s8_max_min_timer = (T_INT8)ZERO;
      s8_had_max =(T_INT8)ONE;
   }
   else if(s16_auto_brightness_temp < MIN_AUTO_BRIGHTNESS)
   {
   	 /* hdudispfmenu-TopButton8Text10Inch-DB-LLR-016 */
     s16_auto_brightness_temp = MIN_AUTO_BRIGHTNESS;
      s8_max_min_timer = (T_INT8)ZERO;
      s8_had_min = (T_INT8)ONE;
   }
   else
   {
    ; /* Do nothing*/
   }

   if((T_INT8)ZERO != Switches.b8)
   {
      if(EBRIGHTNESS_MANUAL == Brightness_mode)
      {
	   	 /* hdudispfmenu-TopButton8Text10Inch-DB-LLR-017 */
         Brightness_mode = EBRIGHTNESS_AUTO;
      	MenuPush(Brightness_menu);
      }
      else
      {
	     /* hdudispfmenu-TopButton8Text10Inch-DB-LLR-018 */
         Brightness_mode = EBRIGHTNESS_MANUAL;
     	MenuPush(Brightness_menu);

      }
	  /* hdudispfmenu-TopButton8Text10Inch-DB-LLR-019 */
      PwmBackLightNewMode(s16_auto_brightness_temp);
   }
   else
   {
    ;  /*Do nothing*/
   }

   if((T_INT8)ZERO != Switches.b7 || (T_INT8)ZERO != Switches.b6)
   {
      /* hdudispfmenu-TopButton8Text10Inch-DB-LLR-020 */
      PwmBackLightStepTo(s16_auto_brightness_temp);
   }
   else
   {
    ; /* Do nothing*/
   }
   if(s8_max_min_timer < MIN_MAX_ITTR)
   {
      if(s8_had_min != (T_INT8)ZERO)
      {
	     /* hdudispfmenu-TopButton8Text10Inch-DB-LLR-022 */
         return(&Min_text[0]);
      }
      else if (s8_had_max != (T_INT8)ZERO)
      {
	     /* hdudispfmenu-TopButton8Text10Inch-DB-LLR-023 */
         return(&Max_text[0]);
      }
   }
   else
   {
    ;  /*Do nothing*/
   }

   if(EBRIGHTNESS_AUTO == Brightness_mode)
   {
      /* hdudispfmenu-TopButton8Text10Inch-DB-LLR-024 */
      return(&Brt_aut_text[0]);
   }
   else
   {
      /* hdudispfmenu-TopButton8Text10Inch-DB-LLR-025 */
      return(&Brt_man_text[0]);
   }
}

/*
 * Function                : NextBoxText
 *
 * Description             : The function enables the next text box.
 *
 * Formal parameter(s)     : None
 *
 * Return Value            : T_CHAR * - Pointer to character
 *
 * Assumption              : None
 *
 */
T_CHAR *NextBoxText(void)
{
   if((T_INT8)ZERO != Switches.b2)
   {
      /* hdudispfmenu-NextBoxText-DB-LLR-001 */
      ;
   }
   else
   {
    ; /* Do nothing */
   }
   /* hdudispfmenu-NextBoxText-DB-LLR-002 */
  return(&Next_text[0]);
}

/*
 * Function                : MenuInit
 *
 * Description             : The function configures the timer initializations
 *                           and all text boxes used by the menu system
 *
 * Formal parameter(s)     : None
 *
 * Return Value            : None
 *
 * Assumption              : None
 *
 */
void MenuInit()
{
   T_STEXTBOXDATA **ptr_next_item = NULL;

   /* hdudispfmenu–MenuInit-DB-LLR-001 */
   /* Init the manual timer. */
   ManualTimerInit();
   CoolTimerInit();

   TimerInstall(&Menu_timer);

   /* Initialize all text boxes used by the menu system. */
   for(ptr_next_item=All_menu_items; (*ptr_next_item) != ((T_STEXTBOXDATA *)ZERO); ptr_next_item++)
   {
      /* hdudispfmenu–MenuInit-DB-LLR-002 */
      TextBoxInit(*ptr_next_item);
   }
}


/*
 * Function                : PageMenu
 *
 * Description             : The function performs page menu operations.
 *
 * Formal parameter(s)     : T_EPAGE_NUM back_grnd_page_num - IN background
 *                                           page number
 *
 * Return Value            : None
 *
 * Assumption              : None
 *
 */
void PageMenu(T_EPAGE_NUM back_grnd_page_num)
{
   T_UINT8 indx=0;
   T_STEXTBOXDATA **ps_next_item = NULL;
   T_CHAR file_name[] = __FILE__;

   /* hdudispfmenu-PageMenu-DB-LLR-001 */
   /* Maintain the Manual Timer. */
   ManualTimerMaint();

   /* Switches not included in the application are used for menu hold. */
   if((Switches.pressed)||((Switches.raw&PBS9_M)||(Switches.raw&PBS10_M)||(Switches.raw&PBS11_M)))
   {
      /* hdudispfmenu-PageMenu-DB-LLR-002 */
      TimerReset(&Menu_timer);
   }
   else
   {
    ; /* Do nothing */
   }

   for(ps_next_item=All_menu_items; (*ps_next_item) != ((T_STEXTBOXDATA *)0); ps_next_item++)
   {
      if((DEC_EIGHT == indx)||(DEC_NINE == indx)||(DEC_ELEVEN == indx)||
         (DEC_TWELVE == indx)||(DEC_THIRTEEN == indx))
      {
         /* hdudispfmenu-PageMenu-DB-LLR-003 */
         (*ps_next_item)->eBackGroundColor=Page_settings.menu_color;
      }
      else if(indx<=DEC_FOURTEEN)
      {
         /* hdudispfmenu-PageMenu-DB-LLR-004 */
         (*ps_next_item)->eBackGroundColor=Page_settings.action_color;
      }
      /* Updated for PR 100083 */
      else if(indx<=TWENTY || (TWENTY_TWO == indx))
      {
         /* hdudispfmenu-PageMenu-DB-LLR-008 */
         (*ps_next_item)->eBackGroundColor=Page_settings.menu_color;
      }
      else
      {
         ;/* Does nothing */
      }
      /* hdudispfmenu-PageMenu-DB-LLR-005 */
      (*ps_next_item)->eFontColor=Page_settings.menu_txt_color;
      indx++;
   }

   /* hdudispfmenu-PageMenu-DB-LLR-006 */
   /* Check for Menu Time Out */
   MenuCheckTimeOut();

   MenuSwitchPage(back_grnd_page_num);

   /* hdudispfmenu-PageMenu-DB-LLR-007 */
   /* Hook for special action based on screen number */
   /* updated as per PR 100083 */
   if(Page_number >= Max_num_of_pages)
   {
      RterrWidget((T_CHAR *)&file_name, __LINE__, &Invalid_screen_number_text[0]);

   }
   else
   {
    ; /* Does nothing */
   }
}
