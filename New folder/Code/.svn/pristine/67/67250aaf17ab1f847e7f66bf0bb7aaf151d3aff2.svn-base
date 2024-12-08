/*
 ******************************************************************************
 * License Information  :  Howell Instruments, Inc.                           *
 *                         "Licensed Software" and "All rights reserved".     *
 ******************************************************************************
 *  File                : hdudispfgrapp.c
 *
 *  Description         : Contains routines for displaying exceedences,cool down timer ,
 *                        bar graphs, rounddails and timers.
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
 *      1.1          Shruthi MN        26-Sep-2017             100064
 *      1.2          Divya G P         10-Oct-2017             100064
 *      1.3          Rona B.S          11-Oct-2017             100064
 *      1.4          Shruthi M N       13-Oct-2017             100083, 100087
 *      1.5          Shruthi M N       30-Oct-2017             100104
 *      1.6          Shruthi M N,
 *                   Divya G P         04-Nov-2017             100133,100156
 *      1.7          Divya G P         08-Nov-2017             100164
 *      1.8          Shilpa A R        23-Mar-2018             100196
 *      1.9          Shruthi M N       05-Apr-2018             100205
 *      1.10         Chaithra J        21-Jun-2020             100259
 *      1.11         Rona  B S         29-Jun-2020             100259
 *      1.12         Dhanalakshmi      05-Aug-2020             100270
 *      1.13         Dhanalakshmi      12-Sep-2020             100276
 *      1.14         Dhanalakshmi      28-Sep-2020             100284
 *      1.15         Dhanalakshmi      20-Mar-2021             100331
 *      1.16         Dhanalakshmi      20-Mar-2021             100331
 *      1.17         Dhanalakshmi      03-Apr-2021             100330
 *
 * Additional References : None
 *
 ******************************************************************************
 */

#include "hdudispfdemo.h"   /* contains functions for demo */
#include "hdudispfcas.h"             /* common defines and functions prototypes for CAS */
#include "hdudispfdma2d.h"  /* contains the common defines and functions prototypes for dma2d */
#include "hdudispffonts.h"        /* Contains different font information*/
#include "hdudispfglobalsettings.h"  /* Routines to read and write data to NVRAM  */
#include "hdudispfgrapp.h"           /* routines for all graph */
#include "hdudispfmenu.h"            /* contains prototype for menu module*/
#include "hdudispfpbs.h"          /* Contains functions prototypes of pbs.*/
#include "hdudispfpdidata.h"         /* contains routines for PDI data */
#include "hdudispfpolygon1.h"         /* provides routines for "scan line" method polygon fill.*/
#include "hdudispfpolygon2.h"         /*  Contains routines for polygons configuration.*/
#include "hdudispfresource.h"  /* provides central location to use On Chip Peripherals*/
#include "hdudispfrterror.h"           /* Provides sub routine for run time errors.*/
#include "hdudispfstmadc.h"       /* contains routines for STM ADC modules.*/
#include "hdudispftext.h"         /* Routines which maintain text display and updates */
#include "hdudispftextbox.h"         /* routines for text box draw and updtaes */
#include "hdudispftextbox.h"      /* routines for text box draw and updtaes */
#include "hdudispftimer.h"           /* Need timer for debounce. */
#include "hdudispfrtd.h"             /* Provide mapping for all A825 incoming parameters */
#include "hdudispfconfig.h"          /* contains page and color config information */
#include "hdudispfrounddial.h"    /* routines which draws and updates the round dial */
#include "hdudispfbargraphs.h"    /* Routines which maintain the "Real Time" bar-graphs */
#include "hdudispfnumbox.h"       /* Number box routines*/
#include "hdudispfcarrotgraph.h"       /* Carrot Graph routines*/
#include "hdudispfbinascii.h"     /*Utility routines to convert binary to ascii base 10.*/
#include "hdudispfpara.h"         /* prototype for builds faults, message and system information */
#include "hdudispfucos.h"            /* uC/OS routines for the real-time kernel */
#include "hdudispfforeground.h"      /* contains the routines for foreground layer of the display */
#include "hdulibbasictypes.h"      /* Contains basic header definations */
/* updated as per PR 100083 */
#include "hdudispfa429.h"     /* Routines for arinc 429 */
#include "hdudispfoffside.h"  /* Screen, message and timer configuration */
#include "hdudispfpwm.h" /*maintains the pulse width modulation channels*/
#include "hdudispfpanel.h"   /* Contains functions prototypes of panel.*/
#include "hdudispfpbit.h"   /* Contains functions prototypes of panel.*/
#include "hdudispfpdicheck.h"  /* Contains functions prototypes of Pdicheck.*/
#include "hdudispflmsscu.h"  /* SCU rtd processing and error codes  */
#include "hdudispftimers.h"  /* Contains functions for exceedance timers */

#define SPLASH_TIME     500U   /* Hold the splash timer for 3 seconds. */
#define DAU_CONNECTED   1U
#define DEC_50          50U
#define DEC_60          60U
#define MAX_TIME        35999999UL
#define TICKS_PER_SECOND 1000U
#define COOLDOWN_AXIS_CALIBRATION 45U
/* Updated as per PR 100083 */
#define A429_DATA_SIZE   20U
#define MAX_A429_DATA    66U
#define BG_IMAGE_ADDR  0x60000000
/* updated as per PR 100083 */
#define PAGE_BITMAP_NUM_OF_SECTOR 20U
#define FP_100  100.0f

static T_CHAR Cool_text[9] = "CoolDown";

T_STEXTBOXDATA Prim_cool_down_pop_up_box =
{
   LIST_BOX, 0, 0, 90, 58, E_TINY_FONT,
   WHITE, DARK_BLUE, 2, CoolxBoxText, 0, WHITE, &Cool_text[0],(T_PSTEXTBOX)0
};
static T_CHAR Empty_str[1]="";
T_ROUNDDIALDEF Ap_page0_dials[30] = {0};

T_CARROTGRAPHDEF Ap_page2_carrot[30] = {0};

T_POLYGRAPHDEF Ap_poly_graph[30] = {{0,0, (T_SFLOATPOLY *)0 }};

/* updated as per PR 100083 */
T_STEXTBOXPDIDATA Ap_page_tbs[50] ={0};
T_PARAM_TABLE Parameters[256]=
{
   {0,0,BNR,{0,PARAM_OK,0.0f}}
};

T_PARAM_TABLE Parameters_numbox[256]=
{
   {0,0,BNR ,{0,PARAM_OK,0.0f}}
};

T_PARAM_TABLE Scu_parameters[3]=
{
   {0,0,BNR,{0,PARAM_OK,0.0f}}
};

T_CHAR  U8_circle[2] = {CIRCLE_E, 0x00};
T_INT8 U8_time_string[15] = {0};
T_EPAGE_NUM Page_num = EPAGE1;
T_ACDT_STRUCT Auto_cool_down_tmr = {0};
T_SNUMBOXDEF Page_num_boxes[50]={{0}};

static T_BOOL Set_new_page = FALSE;
static T_EPAGE_NUM New_page_num = EPAGE0;
static T_TIMER Splash_timer = ZERO;
static T_BOOL Inside_n1 = FALSE;
/* updated as per PR 100083 */
T_UINT8 Splash_done = ZERO;
T_UINT8 Splash_b1_press=2;

/*Updated per ECM 38,39, 41*/
T_ELOG_TRIG_STRUCT Elog_trig[MAX_ELOG_EVENT] = {0};
T_ELOG_LABEL_STRUCT Elog_label[MAX_ELOG_EVENT]={{0}};

/* updated as per PR100270 */
T_PARAM_TABLE Parameters_reading[256] =
 {
   {0,0,BNR,{0,PARAM_OK,0.0f}}
 };
T_CHAR Timer_message[13] = "";
/*********************  BAR GRAPHS  **************************/
T_SBARGRAPHDEF Ap_page1_bar_graphs[30] =
		{
		      0
		};

/*Airframe Info is checked after 1min of Power On */
#define AIFRAME_CHECK_SEC 1500U
T_TEXT Page_txt[30]={0};

/*
 *
 * Function                : ScaleRead
 *
 * Description             : The function reads data from stored a825 messages
 *
 * Formal parameter(s)     : None
 *
 * Return Value            : None
 *
 * Assumption              : None
 *
 */
void ScaleRead(void)
{
   T_UINT16 u16_i=ZERO;
   T_UINT16 u16_j=ZERO;

   /* updated as per PR 100083 */
   /* hdudispfgrapp-ScaleRead-DB-LLR-001 */
   for(u16_i=1;u16_i<=Port1_label_count;u16_i++)
   {
 	  if (TRUE == Config_data.scu_enable)
 	  {
 		   for(u16_j=0;u16_j<=TWO;u16_j++)
 		   {
 		      ScuRTDGetParam(u16_j, &Scu_parameters[u16_j].reading, Scu_parameters[u16_j].type);
 		   }
 	  }
 	  else
 	  {
 		  ;
 	  }
      if(BNR == Parameters[u16_i].type)
      {

         RTDGetParam(u16_i, &Parameters[u16_i].reading);
         RTDGetParam(u16_i, &Parameters_numbox[u16_i].reading);
      }
      else
      {
         RTDGetParamDdw(u16_i, &Parameters[u16_i].reading);
      }
      Parameters_reading[u16_i] = Parameters[u16_i];
   }
}

/*
 *
 * Function                : CompareLimit
 *
 * Description             : The function compares value with the range values.
 *
 * Formal parameter(s)     : T_INT16 val -IN Value to be compared
 *                           T_UINT16 range -IN Range to be compared
 *                           T_UINT8 operator  -IN Operator value
 *
 * Return Value            : T_UINT8 - returns the status to be true or false
 *
 * Assumption              : None
 *
 */
T_UINT8 CompareLimit(T_FLOAT val, T_FLOAT range, T_UINT8 operator)
{
   T_UINT8 ret_val=0;

   switch(operator)
   {
   /*hdudispfgrapp-CompareLimit-DB-LLR-001*/
   case LESS_THAN:
      if(val<range)
      {
         ret_val=1;
      }
      break;
   /*hdudispfgrapp-CompareLimit-DB-LLR-002*/
   case LESS_THAN_EQUAL:
      if(val<=range)
      {
         ret_val=1;
      }
      break;
   /*hdudispfgrapp-CompareLimit-DB-LLR-003*/
   case EQUAL:
      if((T_UINT32)(val*FP_100)==(T_UINT32)(range*FP_100))
      {
         ret_val=1;
      }
      break;
   /*hdudispfgrapp-CompareLimit-DB-LLR-004*/
   case GREATER_THAN_EQUAL:
      if(val>=range)
      {
         ret_val=1;
      }
      break;
   /*hdudispfgrapp-CompareLimit-DB-LLR-005*/
   case GREATER_THAN:
      if(val>range)
      {
         ret_val=1;
      }
      break;
   /*hdudispfgrapp-CompareLimit-DB-LLR-006*/
   case NOT_EQUAL:
      if((T_UINT32)(val*FP_100)!=(T_UINT32)(range*FP_100))
      {
         ret_val=1;
      }
      break;
   /*hdudispfgrapp-CompareLimit-DB-LLR-007*/
   default:
      ret_val=0;
      break;
   }
   return ret_val;
}

/*
 *
 * Function                : ExmonCheck
 *
 * Description             : The function checks the range and sets the status and color
 *
 * Formal parameter(s)     : None
 *
 * Return Value            : None
 *
 * Assumption              : None
 *
 */
void ExmonCheck(void)
{
   T_UINT8 u8_j=0;
   T_UINT8 u8_i=0;
   T_UINT8 compare=0;

   /*hdudispfgrapp-ExmonCheck-DB-LLR-001*/
   for(u8_i=0;u8_i<Bg_cnt;u8_i++)
   {
      if(Ap_page1_bar_graphs[u8_i].psParam->stat < PARAM_BAD)
      {
         for(u8_j=0;u8_j<Ap_page1_bar_graphs[u8_i].numLimit;u8_j++)
         {
          /* Updated as per PR 100083 */
            compare=CompareLimit((T_FLOAT)(Ap_page1_bar_graphs[u8_i].psParam->fread),
                                 Ap_page1_bar_graphs[u8_i].limVal[u8_j],
                                 Ap_page1_bar_graphs[u8_i].limValtype[u8_j]);
            if(ONE == compare)
            {
               Ap_page1_bar_graphs[u8_i].ePenColor=Ap_page1_bar_graphs[u8_i].limColor[u8_j];
               Ap_page1_bar_graphs[u8_i].psParam->stat = Ap_page1_bar_graphs[u8_i].limType[u8_j];
               break;
            }
            else
            {
               ;/*Do nothing*/
            }
         }
      }
      else
      {
         ; /*Do nothing*/
      }
   }

   /*hdudispfgrapp-ExmonCheck-DB-LLR-002*/
   for(u8_i=0;u8_i<Nb_cnt;u8_i++)
   {
      if(Page_num_boxes[u8_i].psParam->stat < PARAM_BAD)
      {
         for(u8_j=0;u8_j<Page_num_boxes[u8_i].numLimit;u8_j++)
         {
          /* Updated as per PR 100083 */
            compare=CompareLimit((T_FLOAT)(Page_num_boxes[u8_i].psParam->fread),\
                                 Page_num_boxes[u8_i].limVal[u8_j],\
                                 Page_num_boxes[u8_i].limValtype[u8_j]);
            if(ONE == compare)
            {
               Page_num_boxes[u8_i].ePenColor=Page_num_boxes[u8_i].limColor[u8_j];
               Page_num_boxes[u8_i].psParam->stat=Page_num_boxes[u8_i].limType[u8_j];
               break;
            }
            else
            {
               ; /*Do nothing*/
            }
         }
      }
      else
      {
         ; /*Do nothing*/
      }
   }
}

/*
 *
 * Function                : CoolxBoxText
 *
 * Description             : The function displays the Cool Down pop up box text in primary
 *                           page of the display.
 *
 * Formal parameter(s)     : None
 *
 * Return Value            : T_CHAR * - Returns the Cool down timer text
 *
 * Assumption              : None
 *
 */
T_CHAR *CoolxBoxText(void)
{
   T_UINT32 u32_seconds = 0;
   T_UINT32 u32_minutes = 0;
   T_CHAR *pc_string = NULL;
   T_CHAR time_string[15] = {0};

   /* hdudispfgrapp-CoolxBoxText-DB-LLR-001 */
   T_UINT32 u32_cool_down = Auto_cool_down_tmr.acdt_time * DEC_1000;

   if (Cool_timer > u32_cool_down)
   {
      Cool_timer = u32_cool_down;
   }
   else
   {
      ;/* Do nothing */
   }

   /* hdudispfgrapp-CoolxBoxText-DB-LLR-002 */
   u32_seconds = (u32_cool_down - Cool_timer) / DEC_1000;
   u32_minutes = u32_seconds / DEC_60;
   u32_seconds %= DEC_60;
   u32_minutes %= DEC_60;

   /* hdudispfgrapp-CoolxBoxText-DB-LLR-003 */
   pc_string = (T_CHAR *)BinasByteFormatInfo (&u32_minutes, FOURB+TWOW+UNSIGNED+NOLZB,
         (T_INT8 *)time_string);

   *(pc_string++) = ':';

   pc_string = (T_CHAR *)BinasByteFormatInfo (&u32_seconds, FOURB+TWOW+UNSIGNED+NOLZB,
                             (T_INT8 *)pc_string);

   /* hdudispfgrapp-CoolxBoxText-DB-LLR-004 */
   TextDispString((T_INT8 *)time_string, Page_settings.acdt_axis.u16_x, Page_settings.
         acdt_axis.u16_y, E_SMALL_FONT, WHITE, TX_NO_FLASH, V_NORMAL, ALIGN_CENTER);

   return (&Empty_str[0]);
}

/*
 *
 * Function                : RoundDialsInit
 *
 * Description             : Initializes the round dail.
 *
 * Formal parameter(s)     : T_ROUNDDIALDEF *rd_list - INOUT Pointer to round dial structure.
 *
 * Return Value            : None
 *
 * Assumption              : None
 *
 */

void RoundDialsInit(T_ROUNDDIALDEF *rd_list)
{
   T_UINT8 cntr=0;
   /*hdudispfgrapp-RoundDialsInit-DB-LLR-001*/
   while(cntr++<Rd_cnt)
   {
      RoundDialAllocat(rd_list);
      rd_list += 1;
   }
}


/*
 *
 * Function                : CarrotGraphInit
 *
 * Description             : Initializes the carrotgraphs.
 *
 * Formal parameter(s)     : T_CARROTGRAPHDEF *cg_list - INOUT Pointer to carro graph structure.
 *
 * Return Value            : None
 *
 * Assumption              : None
 *
 */
void CarrotGraphInit(T_CARROTGRAPHDEF *cg_list)
{
   T_UINT8 cntr=0;
   /*hdudispfgrapp-CarrotGraphInit-DB-LLR-001*/
   while(cntr++<Cg_cnt)
   {
      CarrotGraphAllocat(cg_list);
      cg_list += 1;
   }
}

/*
 *
 * Function                : BarGraphInit
 *
 * Description             : Initializes the Bar graphs.
 *
 * Formal parameter(s)     : T_SBARGRAPHDEF *bg_list - INOUT Pointer to bar graph structure.
 *
 * Return Value            : None
 *
 * Assumption              : None
 *
 */

void BarGraphInit(T_SBARGRAPHDEF *bg_list)
{
   T_UINT8 cntr=0;
   /*hdudispfgrapp-BarGraphInit-DB-LLR-001*/
   while(cntr++<Bg_cnt)
   {
      /* Install pointers. */
      BargraphAllocat(bg_list);
      bg_list += 1;
   }
}

/*
 *
 * Function                : NumberBoxInit
 *
 * Description             : Initializes the Number Box.
 *
 * Formal parameter(s)     : T_SNUMBOXDEF  *nb_list - INOUT Pointer to number box structure
 *
 * Return Value            : None
 *
 * Assumption              : None
 *
 */

void NumberBoxInit(T_SNUMBOXDEF  *nb_list)
{
   T_UINT8 cntr=0;
   /*hdudispfgrapp-NumberBoxInit-DB-LLR-001*/
   while(cntr++<Nb_cnt)
   {
	  /* Install pointers. */
	   NumboxAllocat(nb_list);
       nb_list += 1;
   }
}
/*
 *
 * Function                : TextInit
 *
 * Description             : Initializes the TEXT.
 *
 * Formal parameter(s)     : T_TEXT  *text_list - INOUT Pointer to TEXT structure
 *
 * Return Value            : None
 *
 * Assumption              : None
 *
 */

void TextInit(T_TEXT  *text_list)
{
   T_UINT8 cntr=0;
   /*hdudispfgrapp-TextInit-DB-LLR-001*/
   while(cntr++<Text_cnt)
   {
	      /* Install pointers. */
		   TextAllocatPdi( (T_PTEXT *)text_list,(T_UINT8 *) text_list->pu8String,
		   (T_UINT16)text_list->u16X0,(T_UINT16)text_list->u16Y0,
	           text_list->eTXAlign,text_list->eTXFont,text_list->ePenColor,text_list->eTXV,
	           text_list->eTXFlash);
	      text_list += 1;
   }
}

/*
 *
 * Function                : TextBoxPdiInit
 *
 * Description             : Initializes the TEXT Box.
 *
 * Formal parameter(s)     : T_STEXTBOXDATA *tb_list - INOUT Pointer to TEXT box structure
 *
 * Return Value            : None
 *
 * Assumption              : None
 *
 */

void TextBoxPdiInit(T_STEXTBOXPDIDATA *tb_list)
{
   T_UINT8 cntr=0;
   /*hdudispfgrapp-TextBoxPdiInit-DB-LLR-001*/
   while(cntr++<Tb_cnt)
   {
      /* Install pointers. */
      TextBoxPdiAllocate(tb_list);
      tb_list += 1;
   }
}
/*
 * Function                : GrappSwithcScreens
 *
 * Description             : The function switches from existing page to the input page.
 *
 * Formal parameter(s)     : T_EPAGE_NUM e_new_page_num - IN Input page number.
 *
 * Return Value            : None
 *
 * Assumption              : None
 *
 */

void GrappSwithcScreens(T_EPAGE_NUM e_new_page_num)
{
   /*hdudispfgrapp-GrappSwithcScreens-DB-LLR-001*/
   if(e_new_page_num == Page_num)
   {
      return;
   }
   else
   {
      ; /* Do nothing */
   }

   /*hdudispfgrapp-GrappSwithcScreens-DB-LLR-002*/
   Page_num = e_new_page_num;
   /* Updated as per PR 100083 */
   PwmBlink();
   LCDBackgroundOff();

   /*hdudispfgrapp-GrappSwithcScreens-DB-LLR-003*/
   ForegroundClear();

   /* Updated as per PR 100083 */
   /*hdudispfgrapp-GrappSwithcScreens-DB-LLR-004*/
   ForegroundLoadBackground((T_UINT16 *)(BG_IMAGE_ADDR+
      (Page_num*PAGE_BITMAP_NUM_OF_SECTOR*SECTOR_SIZE)));

   /*hdudispfgrapp-GrappSwithcScreens-DB-LLR-005*/
   PdiPageDataInit(Page_num);

   /*hdudispfgrapp-GrappSwithcScreens-DB-LLR-006*/
   ExceedExtract((T_UINT8 *)(PAGE_EXCEEDANCE_ADDR+(Page_num*MAX_A429_DATA*A429_DATA_SIZE)));

   /*hdudispfgrapp-GrappSwithcScreens-DB-LLR-007*/
   RoundDialsInit(Ap_page0_dials);

   /*hdudispfgrapp-GrappSwithcScreens-DB-LLR-008*/
   NumberBoxInit(Page_num_boxes);

   /*hdudispfgrapp-GrappSwithcScreens-DB-LLR-009*/
   BarGraphInit(Ap_page1_bar_graphs);
   TextInit(Page_txt);
   TextBoxPdiInit(Ap_page_tbs);
   /*hdudispfgrapp-GrappSwithcScreens-DB-LLR-011 */
   CarrotGraphInit(Ap_page2_carrot);

   /*hdudispfgrapp-GrappSwithcScreens-DB-LLR-010*/
   TextBoxOff(&Prim_cool_down_pop_up_box);
   /* Updated as per PR 100083 */
   if(TRUE == Acdt_flag)
   {
      /*hdudispfgrapp-GrappSwithcScreens-DB-LLR-010*/
      Prim_cool_down_pop_up_box.s16ULX = (T_INT16)(Page_settings.acdt_axis.u16_x -
         COOLDOWN_AXIS_CALIBRATION);
      Prim_cool_down_pop_up_box.s16ULY = (T_INT16)(Page_settings.acdt_axis.u16_y -
         COOLDOWN_AXIS_CALIBRATION);
   }
   else
   {
      ;/* Do nothing */
   }
}

/*
 * Function                : GrappInit
 *
 * Description             : The function initializes timers and loads the Splash screen
 *
 * Formal parameter(s)     : None
 *
 * Return Value            : None
 *
 * Assumption              : None
 *
 */
void GrappInit(void)
{
   /*hdudispfgrapp-GrappInit-DB-LLR-001*/
   TimerInstall(&Splash_timer);

   /*hdudispfgrapp-GrappInit-DB-LLR-002*/
   TimerInstall(&Cool_timer);

   /* Added to make Polygons configurable */
    GlobalExtract((T_UINT8 *)GLOBAL_SETTING_ADDRESS);

   /*hdudispfgrapp-GrappInit-DB-LLR-003*/
   /* Updated as per PR 100083 */
    PageExtract((T_UINT8 *)(FOREGROUND_SETTING_ADDRESS+(19*SECTOR_SIZE)));

    if(Page_settings.page_num!=ZERO)
    {
      ForegroundLoadBackground((T_UINT16 *)(BG_IMAGE_ADDR+(Page_settings.page_num *
                                  PAGE_BITMAP_NUM_OF_SECTOR*SECTOR_SIZE)));
    }
    else
    {
       Splash_timer = SPLASH_TIME;
    }
}

/*
 *
 * Function                : GrappApp
 *
 * Description             : The function reads the data, performs range check, initializes the
 *                           foreground elements of the first page and initializes page Menu
 *
 * Formal parameter(s)     : None
 *
 * Return Value            : None
 *
 * Assumption              : None
 *
 */
void GrappApp(void)
{
   T_EPAGE_NUM e_page_temp = EPAGE0;
   static T_BOOL firstin_demo_mode = TRUE;
   static T_UINT16 counter_airframe = ZERO;
   T_UINT16 loop_i = 0;
   T_CHAR file_name[] = __FILE__;
   static T_CHAR param_message[] = "Too many Polygons.";
   static T_CHAR param_message1[] = "RedX not configured in PDI";
   T_BOOL redx_found = FALSE;

   /*hdudispfgrapp-GrappApp-DB-LLR-007*/
   if(Pg_cnt > MAX_POLYS)
     {
  	    RterrWidget((T_CHAR *)&file_name,__LINE__, (T_CHAR *) &param_message);
     }
     else
     {
        ;/*Do nothing*/
     }

   while((loop_i < Pg_cnt) && (redx_found !=TRUE))
   {
	   if(FG_RED_X_SHAPE == Ap_poly_graph[loop_i].polygon_shape)
	   {
		   redx_found = TRUE;
	   }
	   else
	   {
		   redx_found = FALSE;
	   }
	   loop_i++;
   }
   if(FALSE == redx_found)
   {
  	   RterrWidget((T_CHAR *)&file_name,__LINE__, (T_CHAR *) &param_message1);
   }
   else
   {
	 ;/*Do nothing*/
   }

   /*hdudispfgrapp-GrappApp-DB-LLR-001*/
   ScaleRead();

   /*hdudispfgrapp-GrappApp-DB-LLR-002*/
   ExmonCheck();

   /*hdudispfgrapp-GrappApp-DB-LLR-003*/
   if(ZERO == Splash_done)
   {
      /* Updated for PR 100083 */
     /* Updated for PR100133 */
      if((Splash_timer >= SPLASH_TIME) || ((ZERO==Splash_b1_press)&&(Switches.b1 || Switches.b2||
         Switches.b3||Switches.b4|| Switches.b5|| Switches.b6 || Switches.b7
         || Switches.b8||
         Switches.b10 || Switches.b11 || Switches.b12 || Switches.b13 ||
       Switches.c1 ||Switches.c2|| Switches.c3|| Switches.sLE.pressed||Switches.sRE.pressed))||
       (0 !=Switches.sLE.twist) || (0 !=Switches.sRE.twist)||(firstin_demo_mode & Demo_active
        &(Splash_timer >= SPLASH_TIME)))
      {
        if(TRUE == Demo_mode_activate)
        {
           firstin_demo_mode = FALSE;
        }
      else
      {
        ;
      }
         Splash_done = 1;
         if((TRUE==Nv_crc_fail) && (ONE==Du_position))
         {
          Page_num=EPAGE1;
          Cool_down_select=FALSE;
          Fuel_flow_select = FUEL_FLOW_ON;
          Active_eiu=EIU1;
         }
         else
         {
          ;
         }
         if(ONE==Du_position)
         {
          OffsideSwitchScreen(Page_num);
          OffsideCoolTimer(Cool_down_select);
          OffsideFuelFlow(Fuel_flow_select);
          GlobalSettingsSetEIU(Active_eiu);
         }
         else
         {
          ;
         }
         OsTimeDly(250);
         ForegroundLoadBackground((T_UINT16 *)(BG_IMAGE_ADDR+
            (Page_num*PAGE_BITMAP_NUM_OF_SECTOR*SECTOR_SIZE)));
         PdiPageDataInit(Page_num);
         if (FALSE == Page_parameter_error[Page_num])
         {
             RoundDialsInit(Ap_page0_dials);
             NumberBoxInit(Page_num_boxes);
             BarGraphInit(Ap_page1_bar_graphs);
             TextInit(Page_txt);
             TextBoxPdiInit(Ap_page_tbs);
             CarrotGraphInit(Ap_page2_carrot);
         }
		 else
		 {
		    ; /* Do nothing */
		 }
         TextBoxOff(&Prim_cool_down_pop_up_box);

         if(TRUE == Acdt_flag)
         {
            Prim_cool_down_pop_up_box.s16ULX = (T_INT16)(Page_settings.acdt_axis.u16_x -
                                                        COOLDOWN_AXIS_CALIBRATION);
            Prim_cool_down_pop_up_box.s16ULY = (T_INT16)(Page_settings.acdt_axis.u16_y -
                                                        COOLDOWN_AXIS_CALIBRATION);
         }
         else
         {
            ; /* Do nothing*/
         }
         MenuInit();
      }
      else
      {
         ; /* Do nothing*/
      }
      return;
   }
   else
   {
      ; /* Do nothing*/
   }

   /* Updated as per PR100196 */
   /* Check for Airframe Information after 1min of power On */
   /*hdudispfgrapp-GrappApp-DB-LLR-006*/
   counter_airframe = (T_UINT16)(counter_airframe + 1);

   if(counter_airframe >= AIFRAME_CHECK_SEC)
   {
      counter_airframe = AIFRAME_CHECK_SEC;

      ProcessAirframeInfoWords();

   }
   else
   {
         ;/*Do nothing*/
   }
   /*hdudispfgrapp-GrappApp-DB-LLR-004*/
   e_page_temp = Page_num;
   if(TRUE == Set_new_page)
   {
      OS_ENTER_CRITICAL();
      Set_new_page = FALSE;
      e_page_temp = New_page_num;
      OS_EXIT_CRITICAL();
   }
   else
   {
      ; /* Do nothing*/
   }

   /*hdudispfgrapp-GrappApp-DB-LLR-005*/
   PageMenu(e_page_temp);
}

/*
 * Function                : GrappSetPage
 *
 * Description             : Function updates the new page number.
 *
 * Formal parameter(s)     : T_UINT8 u8_set_page - IN Input page number
 *
 * Return Value            : None
 *
 * Assumption              : None
 *
 */
void GrappSetPage(T_UINT8 u8_set_page)
{
   /*hdudispfgrapp-GrappSetPage-DB-LLR-001*/
   OS_ENTER_CRITICAL();

   /*hdudispfgrapp-GrappSetPage-DB-LLR-002*/
   Set_new_page = TRUE;
   New_page_num = (T_EPAGE_NUM)u8_set_page;

   /*hdudispfgrapp-GrappSetPage-DB-LLR-003*/
   OS_EXIT_CRITICAL();
}

/*
 * Function                :  AppExDraw
 *
 * Description             :  This function checks for exceedance condition and
 *                            displays exceedance
 *
 * Formal parameter(s)     :  None
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */
void AppExDraw( void)
{
   T_UINT8 loop_cntr = 0;
   T_CHAR file_name2[] = __FILE__;
   T_CHAR exceed_msg[] = "Too many exceedances";

   if((T_UINT16)SIXTY_FIVE < (T_UINT16)Exceed_cnt)
   {
      RterrWidget((T_CHAR *)&file_name2, __LINE__, &exceed_msg[0]);
   }

   /* for all exceedance */
   for(loop_cntr = 0; loop_cntr < Exceed_cnt; loop_cntr++)
   {
            /* Updated as per PR 100083 */
            /* Check with exceedance bit */
            if (((Exceed_data[loop_cntr].exceed_reading->r &
                  (T_INT32)(ONE << (Exceed_data[loop_cntr].exceed_bit-ONE)))&&
                  (PARAM_OK ==Exceed_data[loop_cntr].exceed_reading->stat)) || \
                  ((S32_data_exceed[Exceed_data[loop_cntr].sdi]) &
                          (T_INT32)(ONE << (Exceed_data[loop_cntr].exceed_bit-ONE))))
            {
               /* hdudispfgrapp-AppExDraw-DB-LLR-001 */
               TextDispString((T_INT8 *)U8_circle, Exceed_data[loop_cntr].exceed_axis.u16_x,
                              Exceed_data[loop_cntr].exceed_axis.u16_y,
                              Exceed_data[loop_cntr].exceed_font, YELLOW,
                              TX_NO_FLASH, V_NORMAL, ALIGN_CENTER);



               if(ZERO != (S32_data_exceed[Exceed_data[loop_cntr].sdi] & (T_INT32)(ONE <<
                    (Exceed_data[loop_cntr].exceed_bit-ONE))))
               {
                  ;/* Does nothing */
               }
               else
               {
                  /* hdudispfgrapp-AppExDraw-DB-LLR-002 */
                  S32_data_exceed[Exceed_data[loop_cntr].sdi] =
                          ((S32_data_exceed[Exceed_data[loop_cntr].sdi]) |
                       (T_INT32)(ONE << (Exceed_data[loop_cntr].exceed_bit-ONE)));
               }
            }
            else
            {
               ;/* Do nothing */
            }



      }
 /*  S32_data_exceed = S32_data_exceed|Exceed_data[0].exceed_reading->r ; */
}



/*
 * Function                : FlightTimer
 *
 * Description             : Displays the timer.
 *
 * Formal parameter(s)     : None
 *
 * Return Value            : None
 *
 * Assumption              : None
 *
 */
void FlightTimer(void)
{
   T_UINT32 u32_seconds = 0;
   T_UINT32 u32_minutes = 0;
   T_UINT32 u32_hours = 0;
   T_CHAR *pc_string = NULL;
   T_CHAR colon = ':';

   /*hdudispfgrapp-FlightTimer-DB-LLR-001*/
   if (Manual_timer > MAX_TIME)
   {
      Manual_timer = MAX_TIME;
   }
   else
   {
      ; /* Do nothing */
   }

   /*hdudispfgrapp-FlightTimer-DB-LLR-002*/
   u32_hours = Manual_timer / (SEC_PER_MIN * MIN_PER_HOUR * TICKS_PER_SECOND);
   u32_seconds = Manual_timer / TICKS_PER_SECOND;
   u32_minutes = u32_seconds / SEC_PER_MIN;

   u32_seconds %= SEC_PER_MIN;
   u32_minutes %= MIN_PER_HOUR;

   /*hdudispfgrapp-FlightTimer-DB-LLR-003*/
   pc_string =(T_CHAR *)BinasByteFormatInfo (&u32_hours, ONEB+ONEW+UNSIGNED+NOLZB, U8_time_string);

   *(pc_string++) = colon;

   /*hdudispfgrapp-FlightTimer-DB-LLR-004*/
   pc_string = (T_CHAR *)BinasByteFormatInfo (&u32_minutes, FOURB+TWOW+UNSIGNED+NOLZB,
                                    (T_INT8 *)pc_string);

   *(pc_string++) = colon;

   /*hdudispfgrapp-FlightTimer-DB-LLR-005*/
   pc_string = (T_CHAR *)BinasByteFormatInfo (&u32_seconds, FOURB+TWOW+UNSIGNED+NOLZB,
                                    (T_INT8 *)pc_string);

   /*hdudispfgrapp-FlightTimer-DB-LLR-006*/
   TextDispString(U8_time_string, Page_settings.timer_axis.u16_x, Page_settings.timer_axis.u16_y,
                  Page_settings.timer_font, WHITE, TX_NO_FLASH, V_NORMAL, ALIGN_CENTER);
}

/*
 * Function                : CoolDownTimer
 *
 * Description             : The function displays the cooldown timer in primary page
 *
 * Formal parameter(s)     : None
 *
 * Return Value            : None
 *
 * Assumption              : None
 *
 */
void CoolDownTimer(void)
{
   /* Updated as per PR 100083 */
   static T_BOOL state = FALSE;

   /* Updated as per PR 100083 */
   if ((CompareLimit((Auto_cool_down_tmr.acdt_reading->fread),
         Auto_cool_down_tmr.acdt_on_trigger_value,GREATER_THAN)) && !Inside_n1)
   {
      /* hdudispfgrapp-CoolDownTimer-DB-LLR-001 */
      Inside_n1 = TRUE;
   }
   else
   {
      ;/* Do nothing */
   }



   /* Updated as per PR 100083 */
   if(TRUE == Inside_n1)
   {
      /*If timer is less than 59*/
      if ((ONE == CompareLimit((Auto_cool_down_tmr.acdt_reading->fread),
            Auto_cool_down_tmr.acdt_on_cond_value,LESS_THAN)) &&
             (ONE == Auto_cool_down_tmr.wog_data->r))
      {
         /* hdudispfgrapp-CoolDownTimer-DB-LLR-002 */
         CoolTimerStart();
         if((TRUE == Acdt_flag) && (TRUE == Cool_down_select) &&
         (Auto_cool_down_tmr.acdt_reading->stat<PARAM_BAD)
             && (Auto_cool_down_tmr.wog_data->stat<PARAM_BAD))
         {
             TextBoxOn(&Prim_cool_down_pop_up_box);
         }
       else
       {
       ;
       }
         state=TRUE;
      }
      /*If timer is in between 59 and 65*/
      else if ((CompareLimit((Auto_cool_down_tmr.acdt_reading->fread),
               Auto_cool_down_tmr.acdt_on_cond_value,GREATER_THAN_EQUAL)) &&
               (TRUE==state) &&
               (CompareLimit((Auto_cool_down_tmr.acdt_reading->fread),
               Auto_cool_down_tmr.acdt_off_condition_value,LESS_THAN_EQUAL))&&
               (ONE == Auto_cool_down_tmr.wog_data->r))
      {
         /* hdudispfgrapp-CoolDownTimer-DB-LLR-003 */
         CoolTimerStart();
         if((TRUE == Acdt_flag) && (TRUE == Cool_down_select) &&
         (Auto_cool_down_tmr.acdt_reading->stat<PARAM_BAD)
             && (Auto_cool_down_tmr.wog_data->stat<PARAM_BAD))
         {
             TextBoxOn(&Prim_cool_down_pop_up_box);
         }
       else
       {
       ;
       }
      }
      /*If timer is greater than 65*/
      else if ((TRUE == CompareLimit((Auto_cool_down_tmr.acdt_reading->fread),
               Auto_cool_down_tmr.acdt_off_condition_value,GREATER_THAN))||
                  (ONE !=Auto_cool_down_tmr.wog_data->r))
      {
         /* hdudispfgrapp-CoolDownTimer-DB-LLR-004 */
         state=FALSE;
         CoolTimerReset();
         TextBoxOff(&Prim_cool_down_pop_up_box);
      }
      else
      {
         CoolTimerReset();
      }
   }
   else
   {
      ;/* Do nothing */
   }
}

/*
 * Function                : AppDraw1
 *
 * Description             : The function displays CAS messages, exceedences ,
 *                           Cool down timer and Manual timer
 *
 * Formal parameter(s)     : None
 *
 * Return Value            : None
 *
 * Assumption              : None
 *
 */
void AppDraw1(void)
{
   /*hdudispfgrapp-AppDraw1-DB-LLR-001*/
   if(ZERO==Splash_done)
   {
      return;
   }
   else
   {
      ;/* Do nothing*/
   }

   /*hdudispfgrapp-AppDraw1-DB-LLR-002*/
   TextBoxOff(&Prim_cool_down_pop_up_box);

   /*hdudispfgrapp-AppDraw1-DB-LLR-003*/
   /* Updated as per PR 100083 */
   if((1 == Page_cas && ((TRUE == Cas_wog_data_recieved) || (TRUE == Cas_data_recieved))
          &&(Parameters[Cas_label_start_idx].reading.stat < PARAM_BAD
          || Parameters[Cas_label_start_idx+1].reading.stat < PARAM_BAD
          || Parameters[Cas_label_start_idx+2].reading.stat < PARAM_BAD
          || Parameters[Cas_label_start_idx+3].reading.stat < PARAM_BAD
          || Parameters[Cas_label_start_idx+4].reading.stat < PARAM_BAD
          || Parameters[Cas_label_start_idx+5].reading.stat < PARAM_BAD
          || Auto_cool_down_tmr.wog_data->stat < PARAM_BAD))
		  && (ZERO == ((Cas_error >> Page_num) & ONE)))
   {
   CasDisplay();
   }
   else
   {
      ;/* Do nothing*/
   }

   /*hdudispfgrapp-AppDraw1-DB-LLR-004*/
   if(0x1 == ((Page_settings.page_menu>>7) & 0x1) &&
   ((ZERO == ((Timer_axis_error >> Page_num) & ONE))
	 && (TRUE == Timer_flag)))
   {
      FlightTimer();
   }
   else
   {
      ;/* Do nothing*/
   }
   /*hdudispfgrapp-AppDraw1-DB-LLR-005*/
   if(ZERO == ((Acdt_axis_error >> Page_num) & ONE))
   {
	   CoolDownTimer();
   }
   else
   {
	   ;
   }

   if(TRUE != Acdt_flag)
   {
      TextBoxOff(&Prim_cool_down_pop_up_box);
   }
   else
   {
       ;
   }
   /*hdudispfgrapp-AppDraw1-DB-LLR-006*/
   if(ZERO == ((Exceed_error >> Page_num ) & ONE))
   {
      AppExDraw();
   }
   else
   {
	   ;
   }
   /*hdudispfgrapp-AppDraw1-DB-LLR-007*/
   if(ZERO == ((ONE >> Page_num ) & Ex_timer_error))
   {
	   AppExTimerDraw();
   }
   else
   {
	   ;
   }
}
