/*
 ******************************************************************************
 * License Information  :  Howell Instruments, Inc.                           *
 *                         "Licensed Software" and "All rights reserved".     *
 ******************************************************************************
 *  File                : hdudispfpanel.c
 *
 *  Description         : The file defines the LCD configurations.
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
 *      1.3           Shruthi M N   13-Oct-2017             100083
 *      1.4           Shruthi M N   30-Oct-2017             100104
 *      1.5           Vinay H   	08-Nov-2017             100164
 *      1.6          Dhanalakshmi D 21-Jun-2020             100259
 *      1.7          Rona B S       29-Jun-2020             100259
 *      1.8          Dhanalakshmi   12-Sep-2020             100276
 *      1.9         Dhanalakshmi    20-Mar-2021             100331 
 *
 * Additional References : None
 *
 ******************************************************************************
 */

#include "hdudispfpanel.h"   /* Contains functions prototypes of panel.*/
#include "hdulibstm32f7xxhalltdc.h"  /* Header file of LTDC HAL module.*/
#include "hdulibstm32f7xxhal.h"  /* Header files for HAL driver*/
#include "hdudispfconfig.h" /* contains page and color config information */
#include "hdulibbasictypes.h"  /* Standard basic data type definitions */
#include "hdulibstm32f746xx.h" /* CMSIS Cortex-M7 Device Peripheral Access Layer */
/* Updated as per PR 100083 */
#include "hdudispfpdidata.h" /* Extract the data from NOR flash */
#include "hdudispfresource.h" /* provides central location to use On Chip Peripherals*/
#include "hdudispfmenu.h"            /* contains prototype for menu module*/
#include "hdudispfgrapp.h"           /* routines for all graph */

#define CONFIG_DATA_ADDRESS   0x63280000UL
#define PIXELS_480    480U
#define PIXELS_272    272U
#define PIXELS_640    640U
#define PIXELS_800    800U
#define PIXELS_320    320U
#define PIXELS_600    600U
#define PIXELS_1024   1024U
#define PIXELS_768    768U


/*Extract parameters for panel from Maintenance configuration*/

T_APPDATA_PANELSTRUCT *Appdata_appdata = (T_APPDATA_PANELSTRUCT*) 0x08010014;
void  *Vp_fgfb2 = (void *)(FG_FB_ONE_ADDR);     /* Pointer to frame buffer for Drawing. */

T_DISPLAYSIZE Display_size = E_NO_SIZE;

/* GLOBALS  */

/* Handle to the LCD.  Built during initialization. */
T_LTDC_HANDLE Ltdc_handle = {0};
/* Handle to the FG layer built during initialization */
T_LTDC_LAYERCFG P_layer_cfg1 = {0};

T_LTDC_LAYERCFG P_layer_cfg = {0};

static T_INT8  S8_forground_off = 0;

T_UINT16 Panel_width = 0;
T_UINT16 Panel_height = 0;
T_UINT16 Panel_hsync = 0;
T_UINT16 Panel_hbp = 0;
T_UINT16 Panel_hfp = 0;
T_UINT16 Panel_vsync = 0;
T_UINT16 Panel_vbp = 0;
T_UINT16 Panel_vfp = 0;

T_UINT8 Back_light = 1;

#define HEX_TEN 0x10U
#define MAX_VAL 255U
/*
 * Function                :  ErrorHandler
 *
 * Description             :  This function handles the error
 *
 * Formal parameter(s)     :  None
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */

static void ErrorHandler(void)
{
    /*hdudispfpanel-ErrorHandler-DB-LLR-001*/
    while(TRUE)
    {
       /*Loop infinitely*/
    }
}
/*
 * Function                :  DisplaySize
 *
 * Description             :  This function selects the display size
 *
 * Formal parameter(s)     :  None
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */

void DisplaySize()
{
   /* hdudispfpanel-DisplaySize-DB-LLR-001 */
    if (( PIXELS_480 == PANEL_WIDTH ) && ( PIXELS_272 == PANEL_HEIGHT ))
    {
    	Display_size = E_3_INCH;
    }
    else if ((PIXELS_640 == PANEL_WIDTH) && (PIXELS_480 == PANEL_HEIGHT))
    {
    	Display_size = E_3_INCH;
    }
    else if ((PIXELS_800 == PANEL_WIDTH ) && (PIXELS_480 ==  PANEL_HEIGHT))
    {
    	Display_size = E_7_INCH;
    }
    else if ((PIXELS_320 == PANEL_WIDTH ) && (PIXELS_480 == PANEL_HEIGHT ))
    {
    	Display_size = E_3_INCH;
    }
    else if (( PIXELS_800 == PANEL_WIDTH ) && ( PIXELS_600 == PANEL_HEIGHT))
    {
    	Display_size = E_7_INCH;
    }
    else if ((PIXELS_1024 == PANEL_WIDTH ) &&
    		( PIXELS_768 == PANEL_HEIGHT ))
    {
    	Display_size = E_10_INCH;
    }
	else 
	{
	 ; /* Do nothing */
	}
}
/*
 * Function                :  LCDConfig
 *
 * Description             :  This function Configures the LTDC peripheral :
 *                                        1) Configure the Pixel Clock for the LCD
 *                                  2) Configure the LTDC Timing and Polarity
 *                                  3) Configure the LTDC Layer 1 :
 *                                   - indirect color (L8) as pixel format
 *                                   - The frame buffer is located at FLASH memory
 *                                   - The Layer size configuration : 320x240
 *                                  4) Configure the LTDC Layer 2 :
 *                                   - The frame buffer is located at FLASH memory
 *                                   - The Layer size configuration : 320x240
 *                                     5) Load 256 colors in CLUT address for Layer 1
 *
 * Formal parameter(s)     :  None
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */

void LCDConfig(void)
{
	/*hdudispfpanel-LCDConfig-DB-LLR-008*/
   ConfigExtract((T_UINT8 *)CONFIG_DATA_ADDRESS);
   DisplaySize();
   if ((E_10_INCH == Display_size) || (E_3_INCH == Display_size))
   {
      ConfigSetConfig(E_LAND_SCAPE,(T_INT16)PANEL_WIDTH,
                         (T_INT16)PANEL_HEIGHT);
   }
   else if (E_7_INCH == Display_size)
   {
      ConfigSetConfig(E_PORTRAIT,(T_INT16)PANEL_WIDTH,
                         (T_INT16)PANEL_HEIGHT);
   }
   else
   {
    ; /* Do nothing */
   }
   /* LTDC Initialization -------------------------------------------------------*/

   /*hdudispfpanel-LCDConfig-DB-LLR-001*/
   /* Polarity configuration */
   /* Initialize the horizontal synchronization polarity as active low */
   Ltdc_handle.Init.HSPolarity = LTDC_HSPOLARITY_AL;
   /* Initialize the vertical synchronization polarity as active low */
   Ltdc_handle.Init.VSPolarity = LTDC_VSPOLARITY_AL;
   /* Initialize the data enable polarity as active low */
   Ltdc_handle.Init.DEPolarity = LTDC_DEPOLARITY_AL;
   /* Initialize the pixel clock polarity as input pixel clock */
   Ltdc_handle.Init.PCPolarity = LTDC_PCPOLARITY_IPC;

   /* Timing Configuration */
   Ltdc_handle.Init.HorizontalSync = (PANEL_HSYNC - ONE);
   Ltdc_handle.Init.VerticalSync = (PANEL_VSYNC - ONE);
   Ltdc_handle.Init.AccumulatedHBP = ((T_UINT16)(PANEL_HSYNC + PANEL_HBP - (T_UINT8)ONE));
   Ltdc_handle.Init.AccumulatedVBP = ((T_UINT16)(PANEL_VSYNC + PANEL_VBP - (T_UINT8)ONE));
   Ltdc_handle.Init.AccumulatedActiveH = ((T_UINT32)(PANEL_HEIGHT + \
								PANEL_VSYNC + PANEL_VBP - (T_UINT8)ONE));
   Ltdc_handle.Init.AccumulatedActiveW = ((T_UINT16)(PANEL_WIDTH + PANEL_HSYNC + \
								PANEL_HBP - (T_UINT8)ONE));
   Ltdc_handle.Init.TotalHeigh = ((T_UINT16)(PANEL_HEIGHT + PANEL_VSYNC + PANEL_VBP + \
								PANEL_VFP -(T_UINT8) ONE));
   Ltdc_handle.Init.TotalWidth = ((T_UINT16)(PANEL_WIDTH + PANEL_HSYNC + PANEL_HBP + \
								PANEL_HFP - (T_UINT8)ONE));

   /* Configure R,G,B component values for LCD background color */
   Ltdc_handle.Init.Backcolor.Blue = ZERO;
   Ltdc_handle.Init.Backcolor.Green = ZERO;
   Ltdc_handle.Init.Backcolor.Red = ZERO;

  Ltdc_handle.Instance = LTDC;

/* Background (static) Layer Configuration -----------------------------------------*/

   /*hdudispfpanel-LCDConfig-DB-LLR-002*/
   P_layer_cfg.WindowX0 = ZERO;
   P_layer_cfg.WindowX1 = PANEL_WIDTH;
   P_layer_cfg.WindowY0 = ZERO;
   P_layer_cfg.WindowY1 = PANEL_HEIGHT;

  /* Pixel Format configuration*/
  P_layer_cfg.PixelFormat = BACKGROUND_PIXEL_FORMAT1;

   /* Splash screen address. */
   P_layer_cfg.FBStartAdress = BG_FB_ADDR;
   /* Alpha constant (255 totally opaque) */
   P_layer_cfg.Alpha = MAX_VAL;

   /* Default Color configuration (configure A,R,G,B component values) */
   P_layer_cfg.Alpha0 = MAX_VAL;
   P_layer_cfg.Backcolor.Blue = ZERO;
   P_layer_cfg.Backcolor.Green = ZERO;
   P_layer_cfg.Backcolor.Red = ZERO;

  /* Configure blending factors */
  P_layer_cfg.BlendingFactor1 = LTDC_BLENDING_FACTOR1_PAXCA;
  P_layer_cfg.BlendingFactor2 = LTDC_BLENDING_FACTOR2_PAXCA;

  /* Configure the number of lines and number of pixels per line */
  P_layer_cfg.ImageWidth = PANEL_WIDTH;
  P_layer_cfg.ImageHeight = PANEL_HEIGHT;

  /* Foreground (Draw Layer) Configuration  */

   /*hdudispfpanel-LCDConfig-DB-LLR-003*/
   /* Windowing configuration */
   P_layer_cfg1.WindowX0 = ZERO;
   P_layer_cfg1.WindowX1 = PANEL_WIDTH;
   P_layer_cfg1.WindowY0 = ZERO;
   P_layer_cfg1.WindowY1 = PANEL_HEIGHT;

  /* Pixel Format configuration*/
  P_layer_cfg1.PixelFormat = FOREGROUND_PIXEL_FORMAT1;

  /*  Point to frame buffer. */
  P_layer_cfg1.FBStartAdress = FG_FB_ONE_ADDR;

   /* Alpha constant (255 totally opaque) */
   P_layer_cfg1.Alpha = MAX_VAL;

   /* Default Color configuration (configure A,R,G,B component values) */
   P_layer_cfg1.Alpha0 = MAX_VAL;
   P_layer_cfg1.Backcolor.Blue = HEX_TEN;
   P_layer_cfg1.Backcolor.Green = HEX_TEN;
   P_layer_cfg1.Backcolor.Red = HEX_TEN;

  /* Configure blending factors */
  P_layer_cfg1.BlendingFactor1 = LTDC_BLENDING_FACTOR1_PAXCA;
  P_layer_cfg1.BlendingFactor2 = LTDC_BLENDING_FACTOR2_PAXCA;

  /* Configure the number of lines and number of pixels per line */
  P_layer_cfg1.ImageWidth = PANEL_WIDTH;
  P_layer_cfg1.ImageHeight = PANEL_HEIGHT;

   /*hdudispfpanel-LCDConfig-DB-LLR-004*/
   if(HalLtdcInit(&Ltdc_handle) != HAL_OK)
   {
      /* Initialization Error */
      ErrorHandler();
   }
   else
   {
   /* Does nothing */
   }

   /*hdudispfpanel-LCDConfig-DB-LLR-005*/
   /* Configure the LTDC */
   __HAL_LTDC_ENABLE_IT(&Ltdc_handle,  LTDC_IT_LI);

   /*hdudispfpanel-LCDConfig-DB-LLR-006*/
   if(HalLtdcConfigLayer(&Ltdc_handle, &P_layer_cfg, ZERO) != HAL_OK)
   {
       /* Initialization Error */
       ErrorHandler();
   }
   else
   {
      /* Does nothing */
   }

   /*hdudispfpanel-LCDConfig-DB-LLR-007*/
   /* Configure the Foreground Layer*/
   if(HalLtdcConfigLayer(&Ltdc_handle, &P_layer_cfg1, ONE) != HAL_OK)
   {
      /* Initialization Error */
      ErrorHandler();
   }
   else
   {
      /* Does nothing */
   }
}

/*
 * Function                :  LCDBackgroundOff
 *
 * Description             :  The function turns the background off
 *
 * Formal parameter(s)     :  None
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */

void LCDBackgroundOff(void)
{
     /*hdudispfpanel-LCDBackgroundOff-DB-LLR-001*/
	/*Turns off backlight when switching pages*/
	if(FALSE == Bitmap_crc_check_bit[Page_num])
	{
		Back_light = 0;
	}



	/* Foreground (Draw Layer) Configuration  */
	
	/* Windowing configuration */
	P_layer_cfg1.WindowX0 = ZERO;
	P_layer_cfg1.WindowX1 = ZERO;
	P_layer_cfg1.WindowY0 = ZERO;
	P_layer_cfg1.WindowY1 = ZERO;

	/* Pixel Format configuration*/
	P_layer_cfg1.PixelFormat = ZERO;

	/*  Point to frame buffer. */
	P_layer_cfg1.FBStartAdress = ZERO;

	/* Alpha constant (255 totally opaque) */
	P_layer_cfg1.Alpha = ZERO;

	/* Default Color configuration (configure A,R,G,B component values) */
	P_layer_cfg1.Alpha0 = ZERO;
	P_layer_cfg1.Backcolor.Blue = ZERO;
	P_layer_cfg1.Backcolor.Green = ZERO;
	P_layer_cfg1.Backcolor.Red = ZERO;

	/* Configure blending factors */
	P_layer_cfg1.BlendingFactor1 = ZERO;
	P_layer_cfg1.BlendingFactor2 = ZERO;

	/* Configure the number of lines and number of pixels per line */
	P_layer_cfg1.ImageWidth = ZERO;
    P_layer_cfg1.ImageHeight = ZERO;

   /*hdudispfpanel-LCDBackgroundOff-DB-LLR-002*/
   if(HalLtdcConfigLayer(&Ltdc_handle, &P_layer_cfg1, ONE) != HAL_OK)
   {
      /* Initialization Error */
      ErrorHandler();
   }
   else
   {
      /* Does nothing */
   }

   /*hdudispfpanel-LCDBackgroundOff-DB-LLR-003*/
   S8_forground_off = ONE;

   Ltdc_handle.Instance->SRCR = LTDC_SRCR_IMR;
   LTDC_LAYER(&Ltdc_handle, ZERO)->CR &= ~((T_UINT32)LTDC_LXCR_LEN);
   Ltdc_handle.Instance->SRCR = LTDC_SRCR_IMR;
}

/*
 * Function                :  LCDBackgroundOn
 *
 * Description             :  The function turns the background on.
 *
 * Formal parameter(s)     :  None
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */
void LCDBackgroundOn(void)
{
	/*hdudispfpanel-LCDBackgroundOn-DB-LLR-001*/
	Back_light =1;

    Ltdc_handle.Instance->SRCR = LTDC_SRCR_IMR;
    LTDC_LAYER(&Ltdc_handle, ZERO)->CR |= (T_UINT32)LTDC_LXCR_LEN;
    Ltdc_handle.Instance->SRCR = LTDC_SRCR_IMR;

   /*hdudispfpanel-LCDBackgroundOn-DB-LLR-002*/
   if(((T_INT8)ONE) == S8_forground_off)
   {
	   /* Windowing configuration */
	   /* Foreground (Draw Layer) Configuration  */


	   /* Windowing configuration */
	   P_layer_cfg1.WindowX0 = ZERO;
	   P_layer_cfg1.WindowX1 = PANEL_WIDTH;
	   P_layer_cfg1.WindowY0 = ZERO;
	   P_layer_cfg1.WindowY1 = PANEL_HEIGHT;

	   /* Pixel Format configuration*/
	   P_layer_cfg1.PixelFormat = FOREGROUND_PIXEL_FORMAT1;

	   /*  Point to frame buffer. */
	   P_layer_cfg1.FBStartAdress = FG_FB_ONE_ADDR;

	   /* Alpha constant (255 totally opaque) */
	   P_layer_cfg1.Alpha = MAX_VAL;

	   /* Default Color configuration (configure A,R,G,B component values) */
	   P_layer_cfg1.Alpha0 = MAX_VAL;
	   P_layer_cfg1.Backcolor.Blue = HEX_TEN;
	   P_layer_cfg1.Backcolor.Green = HEX_TEN;
	   P_layer_cfg1.Backcolor.Red = HEX_TEN;

	   /* Configure blending factors */
	   P_layer_cfg1.BlendingFactor1 = LTDC_BLENDING_FACTOR1_PAXCA;
	   P_layer_cfg1.BlendingFactor2 = LTDC_BLENDING_FACTOR2_PAXCA;

	   /* Configure the number of lines and number of pixels per line */
	   P_layer_cfg1.ImageWidth = PANEL_WIDTH;
	   P_layer_cfg1.ImageHeight = PANEL_HEIGHT;

      /*hdudispfpanel-LCDBackgroundOn-DB-LLR-003*/
      if(HalLtdcConfigLayer(&Ltdc_handle, &P_layer_cfg1, ONE) != HAL_OK)
      {
         /* Initialization Error */
         ErrorHandler();
      }
      else
      {
         /* Does nothing */
      }
      /*hdudispfpanel-LCDBackgroundOn-DB-LLR-004*/
      S8_forground_off = ((T_INT8)ZERO);
   }
}
