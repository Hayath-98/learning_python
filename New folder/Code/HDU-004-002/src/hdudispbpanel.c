/*
 ******************************************************************************
 * License Information  :  Howell Instruments, Inc.                           *
 *                         "Licensed Software" and "All rights reserved".     *
 ******************************************************************************
 *  File                : hdudispbpanel.c
 *
 *  Description         : This file configures the display panel.
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
 *  Author(s)           : Ajay J G
 *
 *  Version History     :
 * <Version No.>     <Author>          <Date>         <Problem Report No.>
 *
 *      1.1          Ajay J G        28-Jul-2017             -
 *      1.2          Divya G P       01-Sep-2017           100028
 *      1.3          Rona B.S        04-Nov-2017           100156
 *      1.4          Vinay H         09-Nov-2017           100164
 *      1.5          Vinay H         23-Mar-2018           100196
 *      1.6          Rona B S        29-Jun-2020           100259
 *
 * Additional References : None
 *
 ******************************************************************************
 */

#include "hdulibstm32f7xxhal.h"            /* Header files for HAL driver*/
#include "hdudispbpanel.h"                 /* Contains functions prototypes of hdudispbpanel*/
#include "hdulibbasictypes.h"              /* Basic data types.*/
#include "hdulibstm32f7xxhalltdc.h"        /* Header file of LTDC HAL module.*/
#include "hdudispbboot.h"                  /* Contains functions prototypes of hdudispbboot.*/
#include "hdulibstm32f746xx.h"             /* CMSIS Cortex-M7 Device Peripheral Access Layer */
#include "hdulibstm32f7xxhaldef.h"         /*Contains the HAL defination module */
#include "hdudispbappdata.h"			   /* Contains appdata structure for configuration file*/

void  *Vp_fgfb = FB_ADDR;               /*    Pointer to foreground frame buffer for Drawing. */
T_EPEN_COLOR Pen_color = WHITE_BPC;         /*    Default pen color.*/

/* GLOBALS  */
/* Handle to the LCD.  Built during initialization. */
T_LTDC_HANDLE Ltdc_handle = {ZERO};
/* Handle to the Panel FG layer built during initialization. */
T_LTDC_LAYERCFG Player_cfg1 = {ZERO};

/* Standard 4 bit RGB palette */
#define LCD_COLOR_BLACK             ((T_UINT32)0x00000)
#define LCD_COLOR_DARK_RED       ((T_UINT32)0x800000)
#define LCD_COLOR_RED                  ((T_UINT32)0xff0000)
#define LCD_COLOR_PINK              ((T_UINT32)0xff00ff)
#define LCD_COLOR_TEAL              ((T_UINT32)0x00ffff)
#define LCD_COLOR_GREEN             ((T_UINT32)0x008000)
#define LCD_COLOR_BRIGHT_GREEN   ((T_UINT32)0x00ff00)
#define LCD_COLOR_TURQUOISE         ((T_UINT32)0x00ffff)
#define LCD_COLOR_DARK_BLUE         ((T_UINT32)0x000080)
#define LCD_COLOR_VIOLET            ((T_UINT32)0x800080)
#define LCD_COLOR_BLUE              ((T_UINT32)0x0000ff)
#define LCD_COLOR_LIGHT_GRAY     ((T_UINT32)0xc0c0c0)
#define LCD_COLOR_GRAY              ((T_UINT32)0x808080)
#define LCD_COLOR_DARK_YELLOW    ((T_UINT32)0x808000)
#define LCD_COLOR_YELLOW            ((T_UINT32)0xffff00)
#define LCD_COLOR_WHITE             ((T_UINT32)0xffffff)


static T_UINT32 Color_lookup_table[16] =
{
   LCD_COLOR_BLACK,
   LCD_COLOR_DARK_RED,
   LCD_COLOR_RED,
   LCD_COLOR_PINK,
   LCD_COLOR_TEAL,
   LCD_COLOR_GREEN,
   LCD_COLOR_BRIGHT_GREEN,
   LCD_COLOR_TURQUOISE,
   LCD_COLOR_DARK_BLUE,
   LCD_COLOR_VIOLET,
   LCD_COLOR_BLUE,
   LCD_COLOR_LIGHT_GRAY,
   LCD_COLOR_GRAY,
   LCD_COLOR_DARK_YELLOW,
   LCD_COLOR_YELLOW,
   LCD_COLOR_WHITE
};

static void ErrorHandler(void);

/*
 * Function                :  ErrorHandler
 *
 * Description             :  This function is used to perform error handling and
 *                            enters infinite loop.
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
   /*hdudispbpanel-ErrorHandler-DB-LLR-001*/
   while(ONE)
   {
      ; /* Do nothing */
   }
}

/*
 * Function                :  BspLcdSetPenColor
 *
 * Description             :  This function sets the color of the displayed text
 *
 * Formal parameter(s)     :  T_EPEN_COLOR color - IN Color to be set.
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */
void BspLcdSetPenColor(T_EPEN_COLOR color)
{
   /*hdudispbpanel-BspLcdSetPenColor-DB-LLR-001*/
   /* Set the CLUT index assuming 100% Alpha    */
   Pen_color = (Pen_color & MASK_MSB) | (T_UINT8)color;
}

/*
 * Function                :  LcdConfig
 *
 * Description             :  This function Configures the LTDC peripheral :
 *                            1) Configure the Pixel Clock for the LCD
 *                            2) Configure the LTDC Timing and Polarity
 *                            3) Configure the LTDC Layer 1 :
 *                               - indirect color (L8) as pixel format
 *                               - The frame buffer is located at FLASH memory
 *                               - The Layer size configuration : 320x240
 *                            4) Configure the LTDC Layer 2 :
 *                               - The frame buffer is located at FLASH memory
 *                               - The Layer size configuration : 320x240
 *                            5) Load 256 colors in CLUT address for Layer 1
 *
 * Formal parameter(s)     :  None
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */

void LcdConfig(void)
{
/* LTDC Initialization */

   /*hdudispbpanel-LcdConfig-DB-LLR-001*/
   /* Polarity configuration */
   /* Initialize the horizontal synchronization polarity as active low */
   Ltdc_handle.Init.HSPolarity = LTDC_HSPOLARITY_AL;
   /* Initialize the vertical synchronization polarity as active low */
   Ltdc_handle.Init.VSPolarity = LTDC_VSPOLARITY_AL;
   /* Initialize the data enable polarity as active low */
   Ltdc_handle.Init.DEPolarity = LTDC_DEPOLARITY_AL;
   /* Initialize the pixel clock polarity as input pixel clock */
   Ltdc_handle.Init.PCPolarity = LTDC_PCPOLARITY_IPC;

   /*hdudispbpanel-LcdConfig-DB-LLR-002*/
   /* Timing Configuration */
   Ltdc_handle.Init.HorizontalSync = (PANEL_HSYNC - ONE);
   Ltdc_handle.Init.VerticalSync = (PANEL_VSYNC - ONE);
   Ltdc_handle.Init.AccumulatedHBP = ((T_UINT16)(PANEL_HSYNC + PANEL_HBP - (T_UINT8)ONE));
   Ltdc_handle.Init.AccumulatedVBP = ((T_UINT16)(PANEL_VSYNC + PANEL_VBP - (T_UINT8)ONE));
   Ltdc_handle.Init.AccumulatedActiveH =
		   ((T_UINT32)(PANEL_HEIGHT + PANEL_VSYNC + PANEL_VBP - (T_UINT8)ONE));
   Ltdc_handle.Init.AccumulatedActiveW =
		   ((T_UINT16)(PANEL_WIDTH + PANEL_HSYNC + PANEL_HBP - (T_UINT8)ONE));
   Ltdc_handle.Init.TotalHeigh =
		   ((T_UINT16)(PANEL_HEIGHT + PANEL_VSYNC + PANEL_VBP + PANEL_VFP -(T_UINT8) ONE));
   Ltdc_handle.Init.TotalWidth =
		   ((T_UINT16)(PANEL_WIDTH + PANEL_HSYNC + PANEL_HBP + PANEL_HFP - (T_UINT8)ONE));

   /*hdudispbpanel-LcdConfig-DB-LLR-003*/
   /* Configure R,G,B component values for LCD background color */
   Ltdc_handle.Init.Backcolor.Blue = ZERO;
   Ltdc_handle.Init.Backcolor.Green = ZERO;
   Ltdc_handle.Init.Backcolor.Red = ZERO;

   Ltdc_handle.Instance = LTDC;

   /*hdudispbpanel-LcdConfig-DB-LLR-004*/
   /* Foreground (Draw Layer) Configuration*/

   /* Windowing configuration */
   Player_cfg1.WindowX0 = ZERO;
   Player_cfg1.WindowX1 = PANEL_WIDTH;
   Player_cfg1.WindowY0 = ZERO;
   Player_cfg1.WindowY1 = PANEL_HEIGHT;

   /*hdudispbpanel-LcdConfig-DB-LLR-005*/
   /* Pixel Format configuration*/
   Player_cfg1.PixelFormat = FOREGROUND_PIXEL_FORMAT;

   /*  Point to frame buffer.*/
   Player_cfg1.FBStartAdress = (T_UINT32)FB_ADDR;

   /* Alpha constant (255 totally opaque) */
   Player_cfg1.Alpha = TWOHUNDRED_FIFTY_FIVE;

   /* Default Color configuration (configure A,R,G,B component values) */
   Player_cfg1.Alpha0 = TWOHUNDRED_FIFTY_FIVE;
   Player_cfg1.Backcolor.Blue = ZERO;
   Player_cfg1.Backcolor.Green = ZERO;
   Player_cfg1.Backcolor.Red = TWOHUNDRED_FIFTY_FIVE;

   /*hdudispbpanel-LcdConfig-DB-LLR-006*/
   /* Configure blending factors */
   Player_cfg1.BlendingFactor1 = LTDC_BLENDING_FACTOR1_PAXCA;
   Player_cfg1.BlendingFactor2 = LTDC_BLENDING_FACTOR2_PAXCA;

   /*hdudispbpanel-LcdConfig-DB-LLR-007*/
   /* Configure the number of lines and number of pixels per line */
   Player_cfg1.ImageWidth = PANEL_WIDTH;
   Player_cfg1.ImageHeight = PANEL_HEIGHT;

   /*hdudispbpanel-LcdConfig-DB-LLR-008*/
   if(HalLtdcInit(&Ltdc_handle) != HAL_OK)
   {
      /* Initialization Error */
      ErrorHandler();
   }
   /*hdudispbpanel-LcdConfig-DB-LLR-009*/
   /* Configure the LTDC */
   __HAL_LTDC_ENABLE_IT(&Ltdc_handle,  LTDC_IT_LI);

   /*hdudispbpanel-LcdConfig-DB-LLR-010*/
   /* Configure the Foreground Layer*/
   if(HalLtdcConfigLayer(&Ltdc_handle, &Player_cfg1, ONE) != HAL_OK)
   {
      /* Initialization Error */
      ErrorHandler();
   }
   /*hdudispbpanel-LcdConfig-DB-LLR-011*/
   /*  Configure the CLUT for foreground layer.*/
   HalLtdcConfigClut(&Ltdc_handle, Color_lookup_table, SIXTEEN, ONE);

   /*hdudispbpanel-LcdConfig-DB-LLR-012*/
   /*  Enable CLUT for the foreground layer.*/
   HalLtdcEnableClut(&Ltdc_handle, ONE);
}

