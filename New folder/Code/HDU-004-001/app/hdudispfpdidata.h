/*
 ******************************************************************************
 * License Information  :  Howell Instruments, Inc.                           *
 *                         "Licensed Software" and "All rights reserved".     *
 ******************************************************************************
 *  File                : hdudispfpdidata.h
 *
 *  Description         : This file provides definitions for all the required data from the PDI
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
 *  Author(s)           : Shruthi MN
 *
 *  Version History     :
 * <Version No.>     <Author>          <Date>         <Problem Report No.>
 *
 *      1.1          Shruthi MN       26-Sep-2017             100064
 *      1.2          Rona B.S         11-Oct-2017             100064
 *      1.3          Divya G P,
 *                   Shruthi M N      12-Oct-2017             100073, 100083, 100087
 *      1.4          Shruthi M N      30-Oct-2017             100104
 *      1.5          Rona B.S         09-Nov-2017             100164
 *      1.6          Rona B S         23-Mar-2018             100196
 *      1.7          Rona B S         28-Mar-2018             100196
 *      1.8          Vinay H          05-Apr-2018             100205
 *      1.9         Chaithra J        21-Jun-2020             100259
 *      1.10         Rona B S         29-Jun-2020             100259
 *      1.11         Dhanalakshmi     05-Aug-2020             100270
 *      1.12         Dhanalakshmi     12-Sep-2020             100276
 *      1.13         Dhanalakshmi     28-Sep-2020             100284
 *      1.14         Dhanalakshmi     20-Mar-2021             100331
 *      1.15         Dhanalakshmi     20-Mar-2021             100331
 *      1.16         Dhanalakshmi     13-May-2021             100350
 *
 * Additional References : None
 *
 ******************************************************************************
 */

#ifndef _HDUDISPFPDIDATA_H_
#define _HDUDISPFPDIDATA_H_

#include "hdudispfnumbox.h"   /*Numbox routines*/
#include "hdulibbasictypes.h" /* Contains basic header definations */
#include "hdudispfpara.h"     /* Contains message and system information list */
#include "hdudispfgrapp.h"           /* routines for all graph */
#include "hdudispftimers.h"  /* Contains functions for exceedance timers */

/* Updtaed as per 100073 */

#define FOREGROUND_SETTING_ADDRESS 0x632A0000UL
#define SECTOR_SIZE                 0x20000U
#define CAS_MESSAGE_ADDRESS         0x63260000UL
#define A429_MESSAGE_ADDRESS        0x63220000
#define ACDT_ADDRESS                0x63520000
#define PAGE_NUM_BASE_ADDR          0x632A0000UL
#define GLOBAL_SETTING_ADDRESS      0x63580000UL
#define INVALID_PAGE_NUM                  0xFF
#define  MAG_BG(x) ((T_UINT32)x*MAG_FACTOR)
/* Updated as per PR100196 */
/* Updated per ECM 38, 39, 41 */
#define ELOG_TRIG_ADDRESS           0x63560000UL
#define ELOG_PARAM_ADDRESS          0x635601F4UL

/* updated as per PR 100073*/

#define CAS_SETTING_ADDRESS         0x63260708UL
#define MAX_NUM_A429                256
#define MAX_LEN_A429                100
#define MAX_NUM_CAS                 36
#define MAX_LEN_CAS                 50
#define MAX_NUM_EXCE                66
#define CAS_LOC_MAX                 75
#define CAS_TICKS                   1000
#define FIFTY_BYTES                 50
#define PARA_MAX_SIZE               50
#define MAX_CAS_TEXT_LEN            28
#define MAX_16_BITS                 0xFFFF
#define MAX_LEN_ACDT                48
#define MAX_NUM_CHAR                20
#define MAX_CONFIG                  20
#define MAX_LEN_EXCE                20
#define REDX_STRING_MAX             31
#define MAX_ELOG_PARAM              18
#define MAX_LEN_TIMER               64

#define MAX_CAS_STRING_TXT 			29
/* Updtaed as per 100073 */

#define PDI_PART_NUM_ADDR                 0x63FFFFEC
#define PDI_PART_NUM_SIZE           16
#define PAGE_SET_LEN                60
#define PAGE_NUM_BASE_OFFSET        0x20000
#define FRGRND_ADDR_60              60

#define MAX_NUM_PAGE_DIALS           30
#define MAX_POLYGON_GRAPHS           30
#define PARAMTR_MAX_VAL              50
#define PARAMTR_MAX_VAL_FG            30
#define ASSOCIALTED_LABEL            5
#define POWER_23                     -23
#define EXPONENT_127                 127

/* Updated as per PR100196*/
/* Updated per ECM 38, 39, 41 */
#define MAX_LEN_ELOG_TRIG            100
#define MAX_ELOG_EVENT               5
#define MAX_ELOG_PARAM_SIZE          6
#define MAX_LEN_ELOG_EVENT           400
#define MAX_ELOG_TRIG_COND           5

typedef struct
{
   T_UINT16 u16_x;
   T_UINT16 u16_y;
}T_COORDINATES;

typedef enum
{
NUM_ONEW=0x1,
NUM_TWOW=0x2,
NUM_THREEW=0x4,
NUM_FOURW=0x8,
NUM_FIVEW=0x10,
NUM_SIXW=0x20,
NUM_SEVENW=0x40,
NUM_EIGHTW=0x80,
NUM_ONED=0x400,
NUM_TWOD=0x800,
NUM_THREED=0x1000,
NUM_FOURD=0x2000,
NUM_FIVED=0x4000,
NUM_SIXD=0x8000,
NUM_SEVEND=0x10000,
NUM_ONEB=0x100000,
NUM_TWOB=0x200000,
NUM_THREEB=0x400000,
NUM_FOURB=0x800000
}T_FORMAT;

typedef enum
{
   COLOR_BLACK=320,
   COLOR_DARK_RED,
   COLOR_RED=322,
   COLOR_LIGHT_RED=323,
   COLOR_PINK,
   COLOR_TEAL=325,
   COLOR_GREEN=326,
   COLOR_BRIGHT_GREEN,
   COLOR_TURQUOISE,
   COLOR_DARK_BLUE=329,
   COLOR_VIOLET,
   COLOR_BLUE=331,
   COLOR_LIGHT_GRAY=332,
   COLOR_GRAY,
   COLOR_DARK_GRAY,
   COLOR_DARK_YELLOW,
   COLOR_YELLOW=336,
   COLOR_ORANGE,
   COLOR_WHITE=338,
   COLOR_MAX
}T_COLOR;

/* Updtaed as per 100073 */
typedef enum
{
   ADVISORY = 1118,
   CAUTION=1119,
   WARNING=1120
}T_TYPE;


typedef enum
{
	/* Timer Display Formats */
	SECONDS = 1520,
	MIN_SEC = 1521,
	HOUR_MIN_SEC = 1522
}T_TIMER_FORMATS;

typedef struct
{
   T_UINT16 element;
   T_UINT8 label;
   T_UINT8 sdi;
   T_COORDINATES bg_axis;
   T_UINT8 bg_no_lin;
   /* Updtaed as per 100073 */
   T_INT32 bg_lin_range[21];
   T_INT32 bg_lin_length[21];

   T_UINT16 bg_width;
   /*OPTIONAL*/
   T_UINT16 bg_orien;
   T_COORDINATES bg_nb_axis ;
   T_UINT32 bg_nb_format  ;
   T_UINT16 bg_nb_font;
   T_UINT8 bg_no_lim  ;
   T_FLOAT bg_lim_val[10]  ;
   T_UINT8 bg_lim_val_type[10]  ;
   T_UINT16 bg_lim_color[10] ;
   T_UINT16 bg_lim_type[10]  ;
   T_COORDINATES bg_redx_axis ;
   T_UINT16 bg_redx_width  ;
   T_UINT16 bg_redx_height;
   T_COORDINATES bg_redx_offset_axis  ;
   T_UINT16 bg_redx_font   ;
   T_UINT8 bg_redx_txt[32] ;
}T_BARGRAPH;

typedef struct
{
   /*ROUND DIAL*/
   T_UINT16 element;
   T_UINT8 label;
   T_UINT8 sdi;
   /* Updtaed as per 100073 */
   T_UINT16 assc_labels[5]; /*associated labels*/

   T_COORDINATES rd_axis ;
   T_UINT8 rd_no_lin ;
   /* Updtaed as per 100073 */
   T_INT32 rd_lin_range[21]  ;
   T_INT32 rd_lin_angle[21];

   T_UINT8 rd_no_ptr;
   T_UINT16 rd_ptr_color[5];
   T_UINT16 rd_ptr_shape[5];
   T_INT16 rd_ptr_scale[5][2] ;
   T_INT16 rd_ptr_scale_offset[5][2];
   T_INT16 rd_ptr_rot[5];
   T_UINT16 rd_length  ;
   T_UINT8 rd_vern;
   T_FLOAT rd_vern_pos;
   /*OPTIONAL*/
   T_COORDINATES rd_nb_axis ;
   T_UINT32 rd_nb_format ;
   T_UINT16 rd_nb_font  ;
   T_UINT8 rd_no_lim   ;
   T_FLOAT rd_lim_val[10] ;
   T_UINT8 rd_lim_val_type[10] ;
   T_UINT16 rd_lim_color[10]  ;
   T_UINT16 rd_lim_type[10]  ;
   T_COORDINATES rd_redx_axis  ;
   T_UINT16 rd_redx_width   ;
   T_UINT16 rd_redx_height  ;
   T_COORDINATES rd_redx_offset_axis  ;
   T_UINT16 rd_redx_font  ;
   T_UINT8 rd_redx_txt[32] ;
}T_ROUND_DIAL;

typedef struct
{
   T_UINT16 element;
   T_UINT8 label;
   T_UINT8 sdi;
   T_COORDINATES nb_axis ;
   /*OPTIONAL*/
   T_UINT32 nb_format;
   T_UINT16 nb_font ;
   T_UINT8 nb_no_lim;
   T_FLOAT nb_lim_val[10];
   T_UINT8 nb_lim_val_type[10] ;
   T_UINT16 nb_lim_color[10] ;
   T_UINT16 nb_lim_type[10] ;
   T_COORDINATES nb_redx_axis ;
   T_UINT16 nb_redx_width   ;
   T_UINT16 nb_redx_height ;
   T_COORDINATES nb_redx_offset_axis ;
   T_UINT16 nb_redx_font     ;
   T_UINT8 nb_redx_txt[32]   ;
}T_NUMBERBOX;


typedef struct
{
   /*CARROT GRAPH*/
   T_UINT16 element;
   T_UINT8 label;
   T_UINT8 sdi;
   /* Updtaed as per 100073 */
  /* T_UINT16 assc_labels[5];*/ /*associated labels*/

   T_COORDINATES cg_axis ;
   T_UINT8 cg_no_lin ;
   /* Updtaed as per 100073 */
   T_INT32 cg_lin_range[21]  ;
   T_INT32 cg_lin_offset[21];

   T_UINT8 cg_no_ptr;
   T_UINT16 cg_ptr_color[5];
   T_UINT16 cg_ptr_shape[5];
   T_INT16 cg_ptr_scale[5][2] ;
   T_INT16 cg_ptr_scale_offset[5][2];
   T_INT16 cg_ptr_rot[5];
   T_UINT16 cg_orien  ;
   /*OPTIONAL*/
   T_COORDINATES cg_nb_axis ;
   T_UINT32 cg_nb_format ;
   T_UINT16 cg_nb_font  ;
   T_UINT8 cg_no_lim   ;
   T_FLOAT cg_lim_val[10] ;
   T_UINT8 cg_lim_val_type[10] ;
   T_UINT16 cg_lim_color[10]  ;
   T_UINT16 cg_lim_type[10]  ;
   T_COORDINATES cg_redx_axis  ;
   T_UINT16 cg_redx_width   ;
   T_UINT16 cg_redx_height  ;
   T_COORDINATES cg_redx_offset_axis  ;
   T_UINT16 cg_redx_font  ;
   T_UINT8 cg_redx_txt[32] ;
}T_CARROTGRAPH;


typedef struct
{
   T_UINT16 element;
   T_UINT8 label;
   T_UINT8 sdi;
   T_UINT8 tb_string[32] ;
   T_COORDINATES tb_axis ;
   T_UINT16 tb_width ;
   T_UINT16 tb_height  ;
   T_UINT16 tb_margin;
   T_UINT16 tb_frame_width  ;
   T_UINT16 tb_frame_color;
   T_UINT16 tb_bg_color   ;
   T_UINT16 tb_bit;
   T_UINT8 tb_cross_val_type ;
   T_FLOAT  tb_cross_val ;
   T_UINT16 tb_align  ;
   T_UINT16 tb_font ;
   T_UINT16 tb_color;
   T_UINT16 tb_state;
   T_UINT16 tb_flash ;
   T_UINT16 tb_flash_color;
   T_COORDINATES tb_redx_axis ;
   T_UINT16 tb_redx_width  ;
   T_UINT16 tb_redx_height   ;
   T_COORDINATES tb_redx_offset_axis  ;
   T_UINT16 tb_redx_font   ;
T_UINT8 tb_redx_txt[32] ;
}T_TEXTBOX;

typedef struct
{
   /* POLY GRAPH*/
   T_UINT16 element;
   T_UINT16 poly_shape;
   T_UINT8 poly_no_pts;
   T_FLOAT poly_pts[45][2];
   T_UINT8 poly_inc_no_pts;
   T_FLOAT poly_inc_pts[45][2];
}T_POLYGRAPH;
typedef struct
{
   T_UINT16 element;
   T_UINT8 label ;
   T_UINT8 sdi ;
   T_UINT8 txt_string[32];
   T_COORDINATES txt_axis;
   T_UINT8 txt_cross_val_type ;
   T_FLOAT  txt_cross_val ;
   T_UINT16 txt_bit ;
   T_UINT16 txt_align ;
   T_UINT16 txt_font;
   T_UINT16 txt_color;
   T_UINT16 txt_state;
   T_UINT16 txt_flash ;
   T_COORDINATES txt_redx_axis;
   T_UINT16 txt_redx_width ;
   T_UINT16 txt_redx_height ;
   T_COORDINATES txt_redx_offset_axis ;
   T_UINT16 txt_redx_font;
   T_UINT8 txt_redx_txt[32];
}T_TEXT_SETT;

typedef struct
{
   T_COORDINATES cas_axis;
   T_UINT16 cas_num_rows;
   T_UINT16 cas_num_column;
   T_UINT16 cas_row_height;
   T_UINT16 cas_col_width;
   T_UINT16 cas_font;
   /* Updtaed as per 100073 */
   T_UINT16 cas_adv_flash_timer;
   T_UINT16 cas_caut_flash_timer;
   T_UINT16 cas_warn_flash_timer;

   T_UINT8 cas_redx_txt[32] ;
}T_CAS_LOCATION_STRUCT;

typedef struct
{
	/* Exceedance timer settings */
   T_UINT16 element;
   T_UINT8 timer_label;
   T_COORDINATES timer_axis;
   T_UINT8 timer_sdi;
   T_UINT16 timer_font;
   T_UINT16 timer_format;
}T_TIMER_STRUCT;

typedef struct
{
   T_UINT8 page_num ;
   T_UINT8 page_name[22];
   T_UINT32 page_menu;
   T_UINT16 menu_color;
   T_UINT16 action_color;
   T_UINT16 menu_txt_color;
   T_COORDINATES timer_axis   ;
   T_UINT16 timer_font;
   T_COORDINATES acdt_axis;
   T_UINT8 acdt_flag;
   T_BARGRAPH Bg_settings[30];
   T_ROUND_DIAL Rd_settings[30];
   T_NUMBERBOX Nb_settings[50];
   T_TEXTBOX Tb_settings[50];
   T_TEXT_SETT Text_settings[30];
   T_CARROTGRAPH Cg_settings[30];
   T_TIMER_STRUCT Timer_settings[MAX_EXCEED_TIMERS+ONE];
   T_CAS_LOCATION_STRUCT Cas_loc_settings;
}T_PAGE;

typedef struct
{
  T_UINT32 A429_bnr_bits;
  T_UINT32 A429_bnr_start_bit;
  /* Updtaed as per 100073 */
  T_FLOAT A429_bnr_max;
  T_FLOAT A429_bnr_min;
  T_UINT32 A429_bnr_offset;

  T_UINT32 A429_bnr_timeout;
  /* Updtaed as per PR 100073 */
  T_FLOAT A429_bnr_scale_fact;
}T_BNR_STRUCT;


typedef struct
{
   T_UINT8 A429_port;
   T_UINT8 A429_label;
   T_UINT8 A429_sdi;
   T_UINT16 A429_type;
   /* Updtaed as per 100073 */
   union
   {
      T_BNR_STRUCT A429_bnr_data;
      T_UINT32 A429_ddw_timeout;
   }label_data;
}T_A429_PARAMS;

typedef struct
{
   T_COORDINATES exceed_axis;
   T_UINT8 label;
   T_UINT8 sdi;
   T_UINT16 exceed_bit;
   T_UINT16 exceed_font;
   /* Updtaed as per 100073 */
   T_PARAM_READING *exceed_reading;
}T_EXCEED_STRUCT;

typedef struct
{
   T_UINT32 acdt_page;
   T_UINT8 label;
   T_UINT16 acdt_time;
   /* Updtaed as per 100073 */
   T_UINT8 wog_label;
   T_UINT16 wog_start_bit;
   T_PARAM_READING *wog_data;

   T_COORDINATES acdt_axis;
   T_UINT8 acdt_on_trigger;
   T_FLOAT acdt_on_trigger_value;
   T_UINT8 acdt_on_cond;
   T_FLOAT acdt_on_cond_value;
   T_UINT8 acdt_off_condition;
   T_FLOAT acdt_off_condition_value;
   T_PARAM_READING *acdt_reading;
}T_ACDT_STRUCT;

typedef struct
{
   T_UINT8 cas_string[31];
   T_UINT8 label;
   T_UINT16 cas_start_bit;
   T_UINT16 cas_priority;
   T_UINT16 cas_type;
   T_UINT16 cas_id;
}T_CAS_MESSAGE_STRUCT;

/* Updated as per PR 100073 */
typedef struct
{
   T_UINT8 config_name[21];
   T_UINT8 config_version[18];
   T_UINT32 config_CRC;
   T_UINT8 config_engine[34];
   T_COORDINATES du_resolution;
   T_COORDINATES channels;
   T_UINT8 eng_sdi;
   T_UINT8 scu_enable;
}T_CONFIG_STRUCT;

/* Updated per PR100196 */
/* Updated per ECM 38, 39, 41 */
typedef struct
{
/* Ex Log Trigger settings */
   T_UINT8 elog_trig_label[5];
   T_UINT8 elog_trig_sdi[5];
   T_UINT8 elog_trig_start_type[5];
   T_FLOAT elog_trig_start_val[5];
   T_UINT8 elog_trig_cross_type[5];
   T_FLOAT elog_trig_cross_val[5];
   T_UINT16 elog_trig_time[5];
}T_ELOG_TRIG_STRUCT;

/* Updated per PR100196 */
typedef struct
{
/* Ex Log Event settings */
   T_UINT8 elog_label;
   T_UINT8 elog_sdi;
   T_UINT8 elog_bit_label[18];
   T_UINT8 elog_bit_param[18][8];
}T_ELOG_LABEL_STRUCT;

/* Updated as per 100073 */
typedef enum /* UINT 16 */
{
    BLANK_ITEM = 0xFFFF,
    INVALID_ITEM = 0xFFFE,

    CONFIG_NAME = 100,
    DU_RESOLUTION = 101,
    CONFIG_PN_VN = 102,

    /*  A429*/
    A429_PORT = 200,
    A429_TYPE = 201,

    A429_BNR_BITS = 221,
    A429_BNR_START_BIT = 222,
    /* Updtaed for PR 100083 */
    A429_BNR_SCALE_FACTOR = 223, /* float*/
    A429_BNR_MAX = 224,
    A429_BNR_MIN = 225,
    A429_BNR_OFFSET =1405,
    A429_BNR_TIMEOUT = 226,

    A429_DDW_TIMEOUT = 260,

    A429_BNR = 280,
    A429_DDW = 282,

    /* PAGE*/
    PAGE_NUM = 300,
    PAGE_NAME = 301,
    /*OPTIONAL*/
    PAGE_MENU = 302,
    PAGE_MENU_COLOR = 303,
    PAGE_ACTION_COLOR = 304,
    MENU_TXT_COLOR = 305,
    TIMER_AXIS = 306,
    TIMER_FONT = 307,
    /*ACDT_TIMER = 308,*/
    ACDT_AXIS = 308,

    ELEMENT = 315,
    LABEL = 316,
	SDI = 318,
	ELEMENT_GLOBAL = 317,

    /*FONTS*/
    FONT_TINY = 350,
    FONT_SMALL = 351,
    FONT_NORMAL = 352,
    FONT_LARGE = 353,

    /*FOREGROUND ELEMENTS*/
    FG_CAPITAL_R_POINTER = 360,
    FG_EQUILATERAL_TRIANGLE = 361,
    FG_RED_X_SHAPE = 362,
    FG_STANDARD_POINTER = 363,
    FG_STANDARD_TIP_POINTER = 364,
    FG_DIAMOND_POINT_SHAPE = 365,
    FG_DIAMOND_POINT_TIP_SHAPE = 366,
    FG_CAPITAL_T_POINTER = 367,
    FG_SQUARE = 368,
    FG_CAPITAL_E_POINTER = 369,
    FG_LOWER_BOX_POINTER_SHAPE = 370,
    FG_CAPITAL_G_POINTER = 371,
    FG_MIDDLE_BOX_POINTER_SHAPE = 372,
   /*Updated as per PR100196*/
    FG_DIAMOND_FINE_POINT_SHAPE = 373,
    FG_DIAMOND_FINE_POINT_TIP_SHAPE = 374,
	/* Triangle Shapes */
	FG_RIGHT_TRIANGLE = 375,
	FG_RIGHT2_TRIANGLE = 376,
	FG_MOVING_ROUND_DIAL = 377,
    FG_POINTER_SHAPE1 = 378,
    FG_POINTER_SHAPE2 = 379,
    FG_POINTER_SHAPE3 = 380,
    FG_POINTER_SHAPE4 = 381,
    FG_POINTER_SHAPE5 = 382,
    FG_POINTER_SHAPE6 = 383,
    FG_POINTER_SHAPE7 = 384,
    FG_POINTER_SHAPE8 = 385,
    FG_POINTER_SHAPE9 = 386,
    FG_POINTER_SHAPE10 = 387,
    FG_POINTER_SHAPE11 = 388,
	FG_POINTER_SHAPE12 = 389,

    TXT_STATE_NORMAL = 390,
    TXT_STATE_REVERSE = 391,

    TEXT_FLASH_ON = 395,
    TEXT_FLASH_OFF = 396,

    ORIENT_HORIZONTAL = 397,
    ORIENT_VERTICAL = 398,

    BAR_GRAPH = 400,
    ROUND_DIAL = 500,
    POLY_GRAPH = 580,
    NUMBER_BOX = 700,
    CARROT_GRAPH = 600,
    TEXT_BOX_PDI = 800,
    TEXT_ONLY = 900,
	EXCEED_TIMER = 1000,

    /*BAR GRAPH      400*/
    BG_AXIS = 401,
    BG_NO_LIN = 402,
    BG_LIN_RANGE = 403,
    BG_LIN_LENGTH = 404,
    BG_WIDTH = 405,
    /*OPTIONAL*/
    BG_ORIEN = 425,
    BG_NB_AXIS = 426,
    BG_NB_FORMAT = 427,
    BG_NB_FONT = 428,
    BG_NO_LIM = 429,
    BG_LIM_VAL = 430,
    BG_LIM_COLOR = 431,
    BG_NB_LIM_COLOR = 432,
    BG_REDX_AXIS = 433,
    BG_REDX_WIDTH = 434,
    BG_REDX_HEIGHT = 435,
    BG_REDX_OFFSET_AXIS = 436,
    BG_REDX_FONT = 437,
    BG_REDX_TXT = 438,
	BG_LIM_TYPE = 439,

    /*ROUND DIAL     500*/
    RD_ASSOCIATED_LABELS =1406,
    RD_AXIS = 501,
    RD_NO_LIN = 502,
    RD_LIN_RANGE = 503,
    RD_LIN_ANGLE = 504,
    RD_NO_PTR = 505,
    RD_PTR_COLOR = 506,
    RD_PTR_SHAPE = 507,
    RD_PTR_SCALE = 508,
    RD_PTR_SCALE_OFFSET = 509,
    RD_PTR_ROT = 510,
    RD_LENGTH = 511,
    RD_VERN = 512,
    RD_VERN_POS = 513,
    /*OPTIONAL*/
    RD_NB_AXIS = 525,
    RD_NB_FORMAT = 526,
    RD_NB_FONT = 527,
    RD_NO_LIM = 528,
    RD_LIM_VAL = 529,
    RD_LIM_COLOR = 530,
    RD_REDX_AXIS = 531,
    RD_REDX_WIDTH = 532,
    RD_REDX_HEIGHT = 533,
    RD_REDX_OFFSET_AXIS = 534,
    RD_REDX_FONT = 535,
    RD_REDX_TXT = 536,
	RD_LIM_TYPE = 537,

	/* POLY GRAPH */
	POLY_SHAPE = 585,
	POLY_NO_PTS = 586,
	POLY_PTS = 587,
    POLY_INC_NO_PTS = 588,
    POLY_INC_PTS = 589,

    /*NUMBER BOX     700*/
    NB_AXIS = 701,
    /*OPTIONAL*/
    NB_FORMAT = 725,
    NB_FONT = 726,
    NB_NO_LIM = 727,
    NB_LIM_VAL = 728,
    NB_LIM_COLOR = 729,
    NB_REDX_AXIS = 730,
    NB_REDX_WIDTH = 731,
    NB_REDX_HEIGHT = 732,
    NB_REDX_OFFSET_AXIS = 733,
    NB_REDX_FONT = 734,
    NB_REDX_TXT = 735,
	NB_LIM_TYPE = 736,

    /*CARROT GRAPH     900*/
    /*CG_ASSOCIATED_LABELS =1407,*/
    CG_AXIS = 601,
    CG_NO_LIN = 602,
    CG_LIN_RANGE = 603,
    CG_LIN_OFFSET = 604,
    CG_NO_PTR = 605,
    CG_PTR_COLOR = 606,
    CG_PTR_SHAPE = 607,
    CG_PTR_SCALE = 608,
    CG_PTR_SCALE_OFFSET = 609,
    CG_PTR_ROT = 610,
    CG_ORIEN = 611,
    /*OPTIONAL*/
    CG_NB_AXIS = 625,
    CG_NB_FORMAT = 626,
    CG_NB_FONT = 627,
    CG_NO_LIM = 628,
    CG_LIM_VAL = 629,
    CG_LIM_COLOR = 630,
    CG_REDX_AXIS = 631,
    CG_REDX_WIDTH = 632,
    CG_REDX_HEIGHT = 633,
    CG_REDX_OFFSET_AXIS = 634,
    CG_REDX_FONT = 635,
    CG_REDX_TXT = 636,
	CG_LIM_TYPE = 637,

    TB_STRING = 801,
    TB_AXIS = 802,
    TB_WIDTH = 803,
    TB_HEIGHT = 804,
    TB_MARGIN = 805,
    TB_FRAME_WIDTH = 806,
    TB_FRAME_COLOR = 807,
    TB_BG_COLOR = 808,

	TB_BIT =823,
	TB_CROSS_VAL =824,
    TB_ALIGN = 825,
    TB_FONT = 826,
    TB_COLOR = 827,
    TB_REDX_AXIS = 828,
    TB_REDX_WIDTH = 829,
    TB_REDX_HEIGHT = 830,
    TB_REDX_OFFSET_AXIS = 831,
    TB_REDX_FONT = 832,
    TB_REDX_TXT = 833,
    TB_STATE    = 834,
    TB_FLASH    = 835,
	TB_FLASH_COLOR = 836,

    TXT_STRING = 901,
    TXT_AXIS = 902,
	TXT_BIT = 923,
	TXT_CROSS_VAL=924,
    TXT_ALIGN = 925,
    TXT_FONT = 926,
    TXT_COLOR = 927,
    TXT_STATE = 928,
    TXT_FLASH = 929,
    TXT_REDX_AXIS = 930,
    TXT_REDX_WIDTH = 931,
    TXT_REDX_HEIGHT = 932,
    TXT_REDX_OFFSET_AXIS = 933,
    TXT_REDX_FONT = 934,
    TXT_REDX_TXT = 935,


    /*   CAS message settings*/
    CAS_STRING = 1100,
    CAS_START_BIT = 1101,
    CAS_PRIORITY = 1102,
    CAS_TYPE = 1103,
    /*OPTIONAL*/
    CAS_ID = 1104,

    /* CAS location settings*/
    CAS_AXIS = 1110,
    CAS_NUM_ROWS = 1111,
    CAS_NUM_COLUMN = 1112,
    CAS_ROW_HEIGHT = 1113,
    CAS_COL_WIDTH = 1114,
    CAS_FONT = 1115,
    CAS_ADV_FLASH_TIMER = 1116,
    CAS_CAUT_FLASH_TIMER=1403,
    CAS_WARN_FLASH_TIMER = 1404,

    CAS_REDX_TXT = 1117,

    /* PARAM TYPES */
    TYPE_NORMAL = 1150,
	TYPE_ADVISORY = 1151,
	TYPE_CAUTION = 1152,
	TYPE_WARNING  = 1153,

    /*NUMBER FORMAT (above)*/
    /*AUTO COOL DOWN TIMER*/
    ACDT_TIME = 1300,
    WOG_LABEL = 1301,   /* byte*/
    WOG_START_BIT = 1302,  /* uint16*/
    ACDT_ON_TRIGGER = 1303,
    ACDT_ON_COND = 1304,
    ACDT_OFF_CONDITION = 1305,

    /* Exceedance Location Settings*/
    EXCEED_BIT = 1400,
    EXCEED_AXIS = 1401,
    EXCEED_FONT = 1402,

    /* Ex Log Trigger Settings*/
    ELOG_TRIG_LABEL = 1411,
    ELOG_TRIG_SDI = 1412,
    ELOG_TRIG_STRT_VAL = 1413,
    ELOG_TRIG_CROSS_VAL = 1414,
    ELOG_TRIG_TIME = 1415,
    /* Ex Log Label Settings*/
    ELOG_LABEL = 1421,
    ELOG_SDI = 1422,
    ELOG_BIT_LABEL = 1423,
    ELOG_BIT_PARAM = 1424,

	/* Timer settings */
	EXCEED_TIMER_AXIS = 1500,
	EXCEED_TIMER_FONT = 1501,
	EXCEED_TIMER_FORMAT = 1502

}T_PDI_ENUM;

extern T_UINT32 Rd_lin_angle_status[PARAMTR_MAX_VAL_FG];

/* Updtaed as per 100073 */
extern T_CONFIG_STRUCT Config_data;
extern T_UINT8 Max_num_of_pages;
extern void ConfigExtract(T_UINT8 *address);
extern T_POLYGRAPH Pg_settings[30];
extern T_A429_PARAMS A429_cfg_data[256];
extern T_CAS_MESSAGE_STRUCT Cas_messages[36];
extern T_ACDT_STRUCT Auto_cool_down_tmr;
extern T_EXCEED_STRUCT Exceed_data[MAX_NUM_EXCE];
extern T_UINT16 A429_settings_cnt;
extern T_UINT16 Cas_word_cnt;
extern T_UINT8 Bg_cnt;
extern T_UINT8 Rd_cnt;
extern T_UINT8 Nb_cnt;
extern T_UINT8 Pg_cnt;
extern T_UINT8 Text_cnt;
extern T_UINT8 Cg_cnt;
extern T_UINT8 Tb_cnt;
extern T_UINT8 Exceed_cnt;
extern T_UINT8 Timer_cnt;
extern T_UINT8 Page_cas;
extern T_TEXT Page_txt[30];
extern T_BOOL Bg_tracker[PARAMTR_MAX_VAL_FG][PARAMTR_MAX_VAL];
extern T_BOOL Rd_tracker[PARAMTR_MAX_VAL_FG][PARAMTR_MAX_VAL];
extern T_BOOL Cg_tracker[PARAMTR_MAX_VAL_FG][PARAMTR_MAX_VAL];
extern T_BOOL Nb_tracker[PARAMTR_MAX_VAL_FG][PARAMTR_MAX_VAL];
extern T_BOOL Elog_trig_bool;
extern T_BOOL Elog_param;
extern T_BOOL Acdt_parameters;
extern T_BOOL Caslocationset_parameters;
extern T_UINT8 Scu_label_flag;

extern T_UINT16 Bg_parameter_occurrence[PARAMTR_MAX_VAL_FG];
extern T_UINT16 Rd_parameter_occurrence[PARAMTR_MAX_VAL_FG];
extern T_UINT16 Nb_parameter_occurrence[PARAMTR_MAX_VAL];
extern T_UINT16 Cg_parameter_occurrence[PARAMTR_MAX_VAL_FG];
extern T_UINT16 Tb_parameter_occurrence[PARAMTR_MAX_VAL];
extern T_UINT16 Text_parameter_occurrence[PARAMTR_MAX_VAL_FG];

extern T_SFLOATPOLY Pg_dis_region[30];
extern T_SFLOATPOLY Pg_inc_dis_region[30];
extern T_BOOL Md_engine_flag;

/* Updated as per 100083 */
extern T_UINT8 Page_name_char_cnt;
extern T_PAGE Page_settings;
/* Updated as per 100073 */
extern T_BOOL Acdt_flag;
extern T_BOOL Timer_flag;
extern T_UINT8 Cas_cnt;
extern T_CAS_TYPE FindCasType(T_UINT16 type);
extern T_PARAM_STAT FindParamType(T_UINT16 type);
extern void CasExtract(T_UINT8 *address);
extern void A429Extract(T_UINT8 *address);
extern void PdiDataInit();
extern void PdiPageDataInit(T_UINT8 page_num);
extern void acdt_extract(T_UINT8 *address);
extern void ExceedExtract(T_UINT8 *address);
extern T_FLOAT CalculatePower (T_FLOAT value, T_INT32 mul);
extern void GlobalExtract(T_UINT8 *address);
extern void PageExtract(T_UINT8 *address);
/* Updated as per PR100196 */
/* Updated per ECM 38, 39, 41 */
extern T_ELOG_TRIG_STRUCT Elog_trig[MAX_ELOG_EVENT];
extern T_ELOG_LABEL_STRUCT Elog_label[MAX_ELOG_EVENT];
extern void ElogTrigExtract(T_UINT8 *address);
extern void ElogParamExtract(T_UINT8 *address);
extern T_UINT8 Cond_cnt[MAX_ELOG_EVENT];

#endif /* _HDUDISPFPDIDATA_H_ */
