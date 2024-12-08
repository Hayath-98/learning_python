/*
 ******************************************************************************
 * License Information  :  Howell Instruments, Inc.                           *
 *                         "Licensed Software" and "All rights reserved".     *
 ******************************************************************************
 *  File                : hdudispfforeground.c
 *
 *  Description         : This file contains the routines which maintain the
 *                         "Real Time" foreground layer of the display.
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
 *  Author(s)           : Shilpa A R
 *
 *  Version History     :
 * <Version No.>      <Author>          <Date>         <Problem Report No.>
 *
 *      1.1           Shilpa A R    24-Jul-2017             100064
 *      1.2           Vinay H       09-Oct-2017             100064
 *      1.3           Shruthi M N   13-Oct-2017             100083,100087
 *      1.4           Shruthi M N   30-Oct-2017             100104
 *      1.5           Vinay H       23-Mar-2018             100196
 *      1.6           Vinay H       09-Apr-2018             100205
 *      1.7           Chaithra J    21-Jun-2020             100259
 *      1.8           Rona B S      29-Jun-2020             100259
 *      1.9           Dhanalakshmi  05-Aug-2020             100270
 *      1.10          Dhanalakshmi  12-Sep-2020             100276
 *      1.11          Rona B S      28-Sep-2020             100284
 *      1.12          Dhanalakshmi  20-Mar-2021             100331
 *      1.13          Dhanalakshmi  20-Mar-2021             100331
 *
 * Additional References : None
 *
 ******************************************************************************
 */

#include "hdudispfcas.h"   /* defines and functions prototypes for CAS */
#include "hdudispfdma2.h"  /* contains the common defines and functions prototypes for dma */
#include "hdudispfdma2d.h"   /* contains the common defines and functions prototypes for dma2d */
#include "hdudispfgrapp.h"  /* routines for all graph */
#include "hdudispfpbs.h"  /* Contains functions prototypes of pbs.*/
#include "hdudispfpwm.h"  /* Contains functions prototypes of pwm.*/
#include "hdudispftext.h"     /*  Routines which maintain text display and updates */
#include "hdudispftextbox.h" /* routines for text box draw and updtaes */
#include "hdudispftimer.h"   /* increment a set of user installed timers. */
#include "hdulibbasictypes.h"  /* Standard basic data type definitions */
#include "hdudispfforeground.h"  /* contains the routines for foreground layer of the display */
#include "hdudispfwidgets.h" /* Contains routines for widget params */
#include "hdudispfpanel.h"   /* Contains functions prototypes of panel.*/
#include "hdudispfrounddial.h" /* routines which draws and updates the round dial */
#include "hdudispfbargraphs.h" /* Routines which maintain the "Real Time" bar-graphs */
#include "hdudispfnumbox.h"  /*Numbox routines*/
#include "hdudispfcarrotgraph.h" /* routines which draws and updates the carrot graph */
#include "hdulibstm32f7xxhal.h" /* Header files for HAL driver*/
#include "hdudispfglobalsettings.h" /* Routines to read and write data to NVRAM  */
#include "hdudispfpdicheck.h" /*contains pdi check*/

/* updated as per PR 100083 */
#include "hdudispfa429.h"  /* Routines for arinc 429 */
#include "hdudispfmenu.h"  /* contains prototype for menu module*/
#include "hdudispfpbit.h"  /* contains prototypes for PBIT test. */
#include "hdudispfpdidata.h" /* Extract the data from NOR flash */
#include "hdudispfrtd.h"  /* Provide mapping for all A825 incoming parameters */

#include"hdudispfmdff.h" /*  Description contains Fuel flow functionalities */

#define MAX_TEXT_BOX 28U

#define FLASH_ON_TIME      500
#define FLASH_OFF_TIME  500

/* Initialize the display redX parameters*/
T_BOOL Distex_init = FALSE;

/* Optional functions.  */
__attribute__((weak)) void AppDraw(void)
{}
__attribute__((weak)) void AppDraw2(void)
{}

__attribute__((weak)) void AppDraw4(void)
{}
__attribute__((weak)) void AppDraw5(void)
{}

/*CAS redx */
static T_CAS_REDX Cas_red_x =  {{E_REGION_TYPE_GAUGE,{0,0},0,0,{0,0},E_NO_FONT,0},
		 (T_SPOLY *)0};

static T_DIS_REDX Dis_red_x =  {{E_REGION_TYPE_GAUGE,{0,0},0,0,{0,0},E_NO_FONT,0},
		 (T_SPOLY *)0};

/* Updated as per PR 100083 */
/* Null or Address of Background Image to load. */
static T_UINT16   *Pu16_back_ground = 0;

/* Holds the flash value */
T_INT8   S8_had_flash = 0;

/* Holds the flash timer value */
static T_TIMER     Flash_timer = 0;

/* Holds the digital timer */
static T_TIMER     Digital_timer = 0;

/* Holds the updated digital timer value */
T_UINT8  U8_update_digital = 0;

/* Holds the Flash state */
T_ETXFS  Flash_state = FLASH_STATE_OFF;

/* contains the currect foreground frame buffer value */
static T_UINT8  U8_which_fgfb = 0;

/* holds the text flash value */
static T_EFLASHSTATE E_txt_flash = FLASH_ON;

/* Holds the digital timer value */
T_TIMER  U32_digital_timer = 0;

/* Calibraion option is available only when DAU is sending signals*/
T_BOOL Bool_menu_cal = FALSE;

/*
 * Function                :  ForegroundClear
 *
 * Description             :  This function clears the foreground
 *
 * Formal parameter(s)     :  None
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */

void ForegroundClear(void)
{
   /*hdudispfforeground-ForegroundClear-DB-LLR-001*/
   BargraphClear();
   RoundDialClear();
   CarrotGraphClear();
   NumboxClear();
   TextClear();
   TextBoxClear(Ap_page_tbs);
   PolygonsClear();

   /*hdudispfforeground-ForegroundClear-DB-LLR-002*/
   /*Clear Page settings during page switch*/
   MemSet(&Page_settings,0,sizeof(T_PAGE));
   /*Clear Page exceedance settings*/
   if(Exceed_cnt > 0)
   {
       MemSet(&Exceed_data[0],0,sizeof(T_EXCEED_STRUCT) * Exceed_cnt);
       Exceed_cnt = 0;
   }
   else
   {
	   ;
   }
   if(Rd_cnt > 0)
   {
         MemSet(&Ap_page0_dials[0],0,(sizeof(T_ROUNDDIALDEF) *Rd_cnt));
         MemSet(&Rd_parameter_occurrence[0],0,(sizeof(T_UINT16) *Rd_cnt));
         Rd_cnt=0;
   }
   else
   {
	   ;
   }
   if(Cg_cnt > 0)
   {
	   MemSet(&Ap_page2_carrot[0],0,(sizeof(T_CARROTGRAPHDEF)*Cg_cnt));
	   MemSet(&Cg_parameter_occurrence[0],0,(sizeof(T_UINT16)*Cg_cnt));
	   Cg_cnt=0;
   }
   else
   {
	   ;
   }
   if(Bg_cnt > 0)
   {
	   MemSet(&Ap_page1_bar_graphs[0],0,(sizeof(T_SBARGRAPHDEF)*Bg_cnt));
	   MemSet(&Bg_parameter_occurrence[0],0,(sizeof(T_UINT16)*Bg_cnt));
	   Bg_cnt=0;
   }
   else
   {
	   ;
   }

   /*hdudispfforeground-ForegroundClear-DB-LLR-003*/
   if(Nb_cnt > 0)
   {
	   MemSet(&Page_num_boxes[0],0,(sizeof(T_SNUMBOXDEF)*Nb_cnt));
	   MemSet(&Nb_parameter_occurrence[0],0,(sizeof(T_UINT16)*Nb_cnt));
	   Nb_cnt=0;
   }
   else
   {
	   ;
   }
   if(Tb_cnt > 0)
   {
	   MemSet(&Ap_page_tbs[0],0,(sizeof(T_STEXTBOXPDIDATA)*Tb_cnt));
	   MemSet(&Tb_parameter_occurrence[0],0,(sizeof(T_UINT16)*Tb_cnt));
	   Tb_cnt=0;
   }
   else
   {
	   ;
   }
   if(Text_cnt > 0)
   {
	   MemSet(&Page_txt[0],0,(sizeof(T_TEXT)*Text_cnt));
	   MemSet(&Text_parameter_occurrence[0],0,(sizeof(T_UINT16)*Text_cnt));
	   Text_cnt = 0;
   }
   else
   {
	   ;
   }
   Timer_flag = FALSE;
   Caslocationset_parameters = FALSE;

   /*Clear red_x points when page switch */
   Dis_red_x.poly_red_x=(T_SPOLY *)0;
}

/*
 * Function                :  VHadFlash
 *
 * Description             :  The function sets flash to one.
 *
 * Formal parameter(s)     :  None
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */

void VHadFlash(void)
{
   /*hdudispfforeground-VHadFlash-DB-LLR-001*/
   S8_had_flash = ((T_INT8)ONE);
}

/*
 * Function                :  EGetFlashState
 *
 * Description             :  The function returns flash state
 *
 * Formal parameter(s)     :  None
 *
 * Return Value            :  T_EFLASHSTATE - returns flash state
 *
 * Assumption              :  None
 *
 */

T_EFLASHSTATE EGetFlashState(void)
{
   /*hdudispfforeground-EGetFlashState-DB-LLR-001*/
   return(E_txt_flash);
}

/*
 * Function                :  ForegroundReDraw1
 *
 * Description             :  This functions toggles active frame buffer.
 *
 * Formal parameter(s)     :  None
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */

void ForegroundReDraw1(void)
{
   /* Toggle active frame buffer.  */
   if(ZERO == U8_which_fgfb )
   {
      /*hdudispfforeground-ForegroundReDraw1-DB-LLR-001*/
      HalLtdcSetAddress(&Ltdc_handle, FG_FB_ONE_ADDR, ONE);
      Vp_fgfb2 = (void *)FG_FB_TWO_ADDR;
      Dma2ClearForeground((void *)FG_FB_THREE_ADDR, FG_FB_SIZE);
      U8_which_fgfb = ONE;
   }
   else if(ONE == U8_which_fgfb)
   {
      /*hdudispfforeground-ForegroundReDraw1-DB-LLR-002*/
      HalLtdcSetAddress(&Ltdc_handle, FG_FB_TWO_ADDR, ONE);
      Vp_fgfb2 = (void *)FG_FB_THREE_ADDR;
      Dma2ClearForeground((void *)FG_FB_ONE_ADDR, FG_FB_SIZE);
      U8_which_fgfb = TWO;
   }
   else
   {
      /*hdudispfforeground-ForegroundReDraw1-DB-LLR-003*/
      HalLtdcSetAddress(&Ltdc_handle, FG_FB_THREE_ADDR, ONE);
      Vp_fgfb2 = (void *)FG_FB_ONE_ADDR;
      Dma2ClearForeground((void *)FG_FB_TWO_ADDR, FG_FB_SIZE);
      U8_which_fgfb = ZERO;
   }
}

/*
 * Function                :  ForegroundReDraw2
 *
 * Description             :  This function Updates the installed widgets.
 *
 * Formal parameter(s)     :  None
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */
void ForegroundReDraw2(void)
{
   /*hdudispfforeground-ForegroundReDraw2-DB-LLR-001*/
   S8_had_flash = FALSE;

   /*hdudispfforeground-ForegroundReDraw2-DB-LLR-002*/
   if(U32_digital_timer >= DIGITAL_DELAY)
   {
      U8_update_digital = ONE;
      TimerReset(&U32_digital_timer);
   }
   else
   {
      U8_update_digital = ZERO;
   }

   /*hdudispfforeground-ForegroundReDraw2-DB-LLR-003*/
   RoundDialUpdate();
   BargraphUpdate();
   NumboxUpdate();
   CarrotGraphUpdate();
   if(1 == Page_cas)
   {
      CasUpdate();
   }
   else
   {
      ;/* Does nothing */
   }
}

/*Updated as per PR100083*/
/*
 * Function                :  CasRedxInit
 *
 * Description             :  This function initializes CAS red X region.
 *
 * Formal parameter(s)     :  T_CAS_REDX *cas_redx -OUT  CAS Red X region
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */

void CasRedxInit(T_CAS_REDX *cas_redx)
{

   /*hdudispfforeground-CasRedxInit-DB-LLR-001*/
   cas_redx->disRegion.eRegionType= E_REGION_TYPE_GAUGE;
   cas_redx->disRegion.sDisLocCtr.u16X0 = (T_INT16)((T_INT16)((Cas_messages_setting.columnWidth *
         Cas_messages_setting.column)/(T_INT16)TWO) + (Cas_messages_setting.sOrigin.u16X0
		          -(T_INT16)SIDE_BB_WIDTH));
   cas_redx->disRegion.sDisLocCtr.u16Y0 = (T_INT16)(((T_INT16)(Cas_messages_setting.rowHeight *
         Cas_messages_setting.row)/(T_INT16)TWO) + \
		 (T_INT16)(Cas_messages_setting.sOrigin.u16Y0- (T_INT16)TEN));
   cas_redx->disRegion.s32Width = (T_INT16)((Cas_messages_setting.columnWidth *
         Cas_messages_setting.column) -(SIDE_BB_WIDTH));
   cas_redx->disRegion.s32Height = (T_INT16)((Cas_messages_setting.rowHeight *
         Cas_messages_setting.row)-(BOTTOM_BB_HEIGHT));
   cas_redx->disRegion.sDisLocO.u16X0 = (T_INT16)((Cas_messages_setting.columnWidth -
         cas_redx->disRegion.sDisLocCtr.u16X0) + ((T_INT16)Cas_messages_setting.sOrigin.u16X0)
		    - (SIDE_BB_WIDTH));
   cas_redx->disRegion.sDisLocO.u16Y0 = (T_INT16)((T_UINT16)(Cas_messages_setting.rowHeight -
         cas_redx->disRegion.sDisLocCtr.u16Y0) + (T_INT16)(Cas_messages_setting.sOrigin.u16Y0
		      -(T_INT16)TEN));
   cas_redx->disRegion.eTXFont = Cas_messages_setting.eFont;
   cas_redx->disRegion.pu8Text = Cas_messages_setting.cas_redx_txt;

}

/*
 * Function                :  DisRedxInit
 *
 * Description             :  This function initializes Dis red X region.
 *
 * Formal parameter(s)     :  T_DIS_REDX *dis_redx -OUT  DIS Red X region
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */

void DisRedxInit(T_DIS_REDX *dis_redx)
{
	T_UINT16 x_axis_size = 0;
	T_UINT16 y_axis_size = 0;

        /* hdudispfforeground-DisRedxInit-DB-LLR-001 */
	if (E_LAND_SCAPE == E_orientation)
	{
		x_axis_size = PANEL_WIDTH;
		y_axis_size = PANEL_HEIGHT;
	}
	else
	{
		x_axis_size = PANEL_HEIGHT;
		y_axis_size = PANEL_WIDTH;
	}

   dis_redx->disRegion.eRegionType= E_REGION_TYPE_GAUGE;

   dis_redx->disRegion.sDisLocCtr.u16X0 = (T_INT16)(((x_axis_size)/2)-(SIDE_BB_WIDTH)+8);

   dis_redx->disRegion.sDisLocCtr.u16Y0 = (T_INT16)(((y_axis_size)/2)-(BOTTOM_BB_HEIGHT)+10);

   dis_redx->disRegion.s32Width = (x_axis_size) -(SIDE_BB_WIDTH*2)+8;

   dis_redx->disRegion.s32Height =  (y_axis_size)-(BOTTOM_BB_HEIGHT *2)-1;

}


/*
 * Function                :  ForegroundReDraw3
 *
 * Description             :  This function Redraws the installed widgets.
 *
 * Formal parameter(s)     :  None
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */
void ForegroundReDraw3(void)
{
   static T_UINT8 u8_delay = ZERO;
   static T_UINT8 u8_lcd_off = ZERO;
   static T_UINT8 u8_prev_x = ZERO;
   T_UINT8 sdi_cntr = 0;

   if(Flash_timer >= (FLASH_ON_TIME +FLASH_OFF_TIME))
   {
      /*hdudispfforeground-ForegroundReDraw3-DB-LLR-001*/
      TimerReset(&Flash_timer);
   }
   else
   {
      ;/*Do nothing*/
   }

   /*hdudispfforeground-ForegroundReDraw3-DB-LLR-002*/
   if(Flash_timer < FLASH_ON_TIME)
   {
      Flash_state =  FLASH_STATE_ON;
      E_txt_flash = FLASH_ON;
   }
   else
   {
      Flash_state =  FLASH_STATE_OFF;
      E_txt_flash = FLASH_OFF;
   }

   /* Initialize the display redX parameters once*/
   if (FALSE == Distex_init)
   {
	   Distex_init = TRUE;
       DisRedxInit(&Dis_red_x);
   }

   if (ZERO != Pu16_back_ground)
   {
      /*hdudispfforeground-ForegroundReDraw3-DB-LLR-003*/
      PwmBlink();
      LCDBackgroundOff();
      if((TRUE == Data_received )&&( FALSE == Bitmap_crc_check_bit[Page_num]))
      {
    	  CrcPages(Page_num);
    	  Bitmap_crc_check_bit[Page_num]=TRUE;
      }
      Dma2dRgbToArgb4444((void *)Pu16_back_ground, (void *)BG_FB_ADDR, (T_UINT32)PANEL_WIDTH,
                                                 (T_UINT32)PANEL_HEIGHT);
      Pu16_back_ground = ((T_UINT16)ZERO);
      /* Updated as per PR 100083 */
      u8_delay = FIVE;
      u8_lcd_off = ONE ;
      Cas_red_x.poly_red_x = (T_SPOLY *)ZERO;
   }

   else
   {
         /*hdudispfforeground-ForegroundReDraw3-DB-LLR-004*/
	   if (FALSE == Page_parameter_error[Page_num])
	   {
         TextDraw();
         AppDraw1();
	   }
	   else
	   {
	       ; /* Do nothing */
	   }
         AppDraw2();

         /* globalParameterError - On error in global parameter draw RedX on display*/
          /* Updated as per PR 100083 */
         if((((TRUE == Both_dau_fail|| ZERO != Pbit_test_result) &&
                 (ZERO != Splash_done)&&(ZERO == u8_lcd_off) )&&(TRUE != Demo_mode)) ||
        		 (TRUE == Global_parameter_error))
         {
            /*SHOW BIG RED X */
            WidgetsRedX(&Dis_red_x.disRegion, &Dis_red_x.poly_red_x);
            /* Updated as per PR100196 */
            TextBoxOff(&Prim_cool_down_pop_up_box);
            TextBoxOff(Top_menu[0]);
            TextBoxOff(Top_menu[1]);
            TextBoxOff(Top_menu[4]);
            TextBoxOff(Top_menu[6]);
            TextBoxOff(Top_menu[8]);
            u8_prev_x = ONE;
            /*Receive calibration labels after disconnecting and connecting DAU*/
            for (sdi_cntr= 0;sdi_cntr<NUMBEROFENGINES;sdi_cntr++)
            {
            	Offset_bool[sdi_cntr]  = FALSE;
            	Gain_bool[sdi_cntr]  = FALSE;
            }
            /*calibration option is disabled when RedX*/
            Bool_menu_cal =  TRUE;
         }
         /*
          *  when there is an error in page parameter draw RedX only on
          *  that particular page
          */
         else if (TRUE == Page_parameter_error[Page_num])
         {
        	 WidgetsRedX(&Dis_red_x.disRegion, &Dis_red_x.poly_red_x);
         }
         /*hdudispfforeground-ForegroundReDraw3-DB-LLR-007*/
         else
         {
        	 Bool_menu_cal = FALSE;
        /* Delete this line after verifying so that redX doesn't allocate points each time*/
            Dis_red_x.poly_red_x=(T_SPOLY *)0;
            if(u8_prev_x >= ONE)
            {
               u8_prev_x = ZERO;
               MenuReset(Top_menu, (T_EPAGE_NUM)Page_number);
            }
			/*hdudispfforeground-ForegroundReDraw3-DB-LLR-009*/
            if ((ONE == Splash_done) && (ONE == Cmu_fuel_flow) && (TRUE == Md_engine_flag)
                && (TWO == Page_num) && (ONE == Fuel_flow_select))
            {
            	AppFuelFlowDraw();
            }
            else
            {
            	;
            }
            RoundDialDraw();
            BargraphDraw();
            AppDraw4();
            AppDraw5();
            CarrotGraphDraw();
            NumboxDraw();
			TextBoxPdiDraw();
	        TextDrawPDI();
            AppDraw();
            if((1 == Page_cas) && (((FALSE == Cas_wog_data_recieved)
               && (FALSE == Cas_data_recieved))
               ||(Parameters[Cas_label_start_idx].reading.stat >= PARAM_BAD
               && Parameters[Cas_label_start_idx+1].reading.stat >= PARAM_BAD
               && Parameters[Cas_label_start_idx+2].reading.stat >= PARAM_BAD
               && Parameters[Cas_label_start_idx+3].reading.stat >= PARAM_BAD
               && Parameters[Cas_label_start_idx+4].reading.stat >= PARAM_BAD
               && Parameters[Cas_label_start_idx+5].reading.stat >= PARAM_BAD
               && Auto_cool_down_tmr.wog_data->stat >= PARAM_BAD)))
            {
               CasRedxInit(&Cas_red_x);
               WidgetsRedX(&Cas_red_x.disRegion, &Cas_red_x.poly_red_x);
            }
            else
            {
               Cas_red_x.poly_red_x = (T_SPOLY *)ZERO;
            }
         }
         /*hdudispfforeground-ForegroundReDraw3-DB-LLR-008*/
         TextBoxDraw();
         if (ZERO == Splash_done)
         {
        	 LCDBackgroundOn();
         }
         else
         {
        	 ;
         }

      if(ZERO == u8_delay)
      {
        if(u8_lcd_off > ZERO)
        {
           PwmBlink();
        }
        else
        {
        	LCDBackgroundOn();
        }
         u8_lcd_off = ZERO;
      }
      else
      {
         /*hdudispfforeground-ForegroundReDraw3-DB-LLR-005*/
         PwmBlink();
         u8_delay =(T_UINT8)(u8_delay - ONE);
      }
   }
   /*hdudispfforeground-ForegroundReDraw3-DB-LLR-006*/
   if(FALSE == S8_had_flash)
   {
      TimerReset(&Flash_timer);
   }
   else
   {
     ; /* Does nothing */
   }
}

/*
 * Function                :  ForegroundLoadBackground
 *
 * Description             :  The function loads the background
 *
 * Formal parameter(s)     :  T_UINT16 *pu16_src - IN source for the background.
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */
void ForegroundLoadBackground(T_UINT16 *pu16_src)
{
   /*hdudispfforeground-ForegroundLoadBackground-DB-LLR-001*/
   Pu16_back_ground = pu16_src;
}

/*
 * Function                :  ForegroundInit
 *
 * Description             :  The function intializes the foreground.
 *
 * Formal parameter(s)     :  None
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */

void ForegroundInit(void)
{
   /*hdudispfforeground-ForegroundInit-DB-LLR-001*/
   TimerInstall(&Flash_timer);
   TimerInstall(&Digital_timer);
}

