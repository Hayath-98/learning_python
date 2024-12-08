/*
 ******************************************************************************
 * License Information  :  Howell Instruments, Inc.                           *
 *                         "Licensed Software" and "All rights reserved".     *
 ******************************************************************************
 *  File                : hdudispfpanel.h
 *
 *  Description         : prototype to defines the LCD configurations.
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
 *      1.1           Shilpa A R       24-Jul-2017             100064
 *      1.2           Vinay H          09-Oct-2017             100064
 *      1.3          Shruthi M N       30-Oct-2017             100104
 *      1.4          Dhanalakshmi D    21-Jun-2020             100259
 *      1.5          Rona B S		   29-Jun-2020			   100259
 *      1.6          Dhanalakshmi      12-Sep-2020             100276
 *      1.7          Rona B.S          15-Sep-2020             100276
 *
 * Additional References : None
 *
 ******************************************************************************
 */

#ifndef _HDUDISPFPANEL_H_
#define _HDUDISPFPANEL_H_

#include "hdudispfresource.h"  /* provides central location to use On Chip Peripherals*/
#include "hdulibstm32f7xxhalltdc.h"  /* Header file of LTDC HAL module.*/
#include "hdulibstm32f7xxhal.h"  /* Header files for HAL driver*/
#include "hdudispfconfig.h"  /* contains page and color config information */
#include "hdulibbasictypes.h"  /* Standard basic data type definitions */

extern void LCDConfig(void);
extern void LCDBackgroundOff(void);
extern void LCDBackgroundOn(void);

/* Handle to the LCD.  Built during initialization. */
extern T_LTDC_HANDLE Ltdc_handle;
/* Handle to the FG layer built during initialization. */
extern T_LTDC_LAYERCFG P_layer_cfg1;

/* Location of Video RAM */
#define VIDEO_RAM       0xc0000000
#define PACK_THIS __attribute__ ((packed))
extern T_UINT8 Back_light;

typedef struct TagAPP_DATA

{

                T_UINT16 panelWidth;

                T_UINT16 panelHeight;

                T_UINT16 panelHSync;

                T_UINT16 panelHBP;

                T_UINT16 panelHFP;

                T_UINT16 panelVSync;

                T_UINT16 panelVbp;

                T_UINT16 panelVfp;





}PACK_THIS T_APPDATA_PANELSTRUCT;


typedef enum
{
   E_NO_SIZE,
   E_3_INCH,
   E_5_INCH,
   E_7_INCH,
   E_10_INCH

}  T_DISPLAYSIZE;

typedef enum
{
    /** No Active Switches */
    LAND_SCAPE = 0,
    /** Display on Top */
    PORTRAIT = 1

} T_PANEL_ORIENTATION;

extern T_APPDATA_PANELSTRUCT *Appdata_appdata;
# define ORIENTATION *((T_UINT8*)(0x801002C))
extern T_DISPLAYSIZE Display_size;

/* Timing  and size for selected panel */
#if (PANEL == RK043FN48H)

#define  PANEL_WIDTH               ((T_UINT16)480)          /* LCD PIXEL WIDTH            */
#define  PANEL_HEIGHT               ((T_UINT16)272)            /* LCD PIXEL HEIGHT           */

#define  PANEL_HSYNC            ((T_UINT16)41)           /* Horizontal synchronization */
#define  PANEL_HBP              ((T_UINT16)13)           /* Horizontal back porch      */
#define  PANEL_HFP              ((T_UINT16)32)           /* Horizontal front porch     */
#define  PANEL_VSYNC            ((T_UINT16)10)           /* Vertical synchronization   */
#define  PANEL_VBP              ((T_UINT16)2)               /* Vertical back porch        */
#define  PANEL_VFP              ((T_UINT16)272)          /* Vertical front porch       */

#elif  (PANEL == AA065VD51)

#define  PANEL_WIDTH                ((T_UINT16)640)          /* LCD PIXEL WIDTH            */
#define  PANEL_HEIGHT               ((T_UINT16)480)          /* LCD PIXEL HEIGHT           */

#define  PANEL_HSYNC             ((T_UINT16)10)   /* Horizontal synchronization */
#define  PANEL_HBP               ((T_UINT16)30)   /* Horizontal back porch      */
#define  PANEL_HFP               ((T_UINT16)10)   /* Horizontal front porch     */

#define  PANEL_VSYNC             ((T_UINT16)10)   /* Vertical synchronization   */
#define  PANEL_VBP               ((T_UINT16)2)    /* Vertical back porch        */
#define  PANEL_VFP               ((T_UINT16)200)  /* Vertical front porch       */

#elif  (PANEL == AA07MC52)

#define  PANEL_WIDTH                ((T_UINT16)800)          /* LCD PIXEL WIDTH            */
#define  PANEL_HEIGHT               ((T_UINT16)480)          /* LCD PIXEL HEIGHT           */

#define  PANEL_HSYNC             ((T_UINT16)130)  /* Horizontal synchronization */
#define  PANEL_HBP               ((T_UINT16)30)   /* Horizontal back porch      */
#define  PANEL_HFP               ((T_UINT16)10)   /* Horizontal front porch     */

#define  PANEL_VSYNC             ((T_UINT16)10)   /* Vertical synchronization   */
#define  PANEL_VBP               ((T_UINT16)10)   /* Vertical back porch        */
#define  PANEL_VFP               ((T_UINT16)20)   /* Vertical front porch       */

#elif  (PANEL == KD035HVFMA035)

#define  PANEL_WIDTH                ((T_UINT16)320)          /* LCD PIXEL WIDTH            */
#define  PANEL_HEIGHT               ((T_UINT16)480)          /* LCD PIXEL HEIGHT           */

#define  PANEL_HSYNC             ((T_UINT16)130)   /* Horizontal synchronization */
#define  PANEL_HBP               ((T_UINT16)30)   /* Horizontal back porch      */
#define  PANEL_HFP               ((T_UINT16)10)   /* Horizontal front porch     */

#define  PANEL_VSYNC             ((T_UINT16)10)   /* Vertical synchronization   */
#define  PANEL_VBP               ((T_UINT16)10)    /* Vertical back porch        */
#define  PANEL_VFP               ((T_UINT16)20)   /* Vertical front porch       */


#elif  (PANEL == AA104SL12)

#define  PANEL_WIDTH                ((T_UINT16)800)          /* LCD PIXEL WIDTH            */
#define  PANEL_HEIGHT               ((T_UINT16)600)          /* LCD PIXEL HEIGHT           */

#define  PANEL_HSYNC            ((T_UINT16)10)   /* Horizontal synchronization */
#define  PANEL_HBP              ((T_UINT16)30)   /* Horizontal back porch      */
#define  PANEL_HFP              ((T_UINT16)10)   /* Horizontal front porch     */

#define  PANEL_VSYNC            ((T_UINT16)10)   /* Vertical synchronization   */
#define  PANEL_VBP              ((T_UINT16)10)    /* Vertical back porch        */
#define  PANEL_VFP              ((T_UINT16)20)  /* Vertical front porch       */

#elif  (PANEL == AA104XD12)

#define  PANEL_WIDTH            ((T_UINT16)Appdata_appdata->panelWidth)
/* ((T_UINT16)1024)*/     /* LCD PIXEL WIDTH  */
#define  PANEL_HEIGHT           ((T_UINT16)Appdata_appdata->panelHeight)
/*((T_UINT16)768)*/         /* LCD PIXEL HEIGHT           */

#define  PANEL_HSYNC            ((T_UINT16)Appdata_appdata->panelHSync)
/*((T_UINT16)10) */  /* Horizontal synchronization */
#define  PANEL_HBP             ((T_UINT16)Appdata_appdata->panelHBP)
/*((T_UINT16)30) */  /* Horizontal back porch      */
#define  PANEL_HFP              ((T_UINT16)Appdata_appdata->panelHFP)
/*((T_UINT16)10)*/   /* Horizontal front porch     */

#define  PANEL_VSYNC            ((T_UINT16)Appdata_appdata->panelVSync)
/* ((T_UINT16)10)*/   /* Vertical synchronization   */
#define  PANEL_VBP               ((T_UINT16)Appdata_appdata->panelVbp)
/*((T_UINT16)10)*/    /* Vertical back porch        */
#define  PANEL_VFP              ((T_UINT16)Appdata_appdata->panelVfp)
/*((T_UINT16)20)*/  /* Vertical front porch       */

/* ((T_UINT16)1024)*/     /* LCD PIXEL WIDTH  */

#endif

/********************************/
/* Orientation of panel.*/
/********************************/
#define LAND_SCAPE      0
#define PORTRAIT        1

/* Pixel Formats. */
#define PIXEL_FORMAT_ARGB4444    4
#define PIXEL_FORMAT_AL88       7

/* Select Pixel Format */
#define  FOREGROUND_PIXEL_FORMAT1      PIXEL_FORMAT_ARGB4444
#define  BACKGROUND_PIXEL_FORMAT1      PIXEL_FORMAT_ARGB4444

/* Panel/Pixel Format dependent definitions. */
#define FG_FB_SIZE (T_UINT32)(PANEL_WIDTH*PANEL_HEIGHT*2)

#define FG_FB_SIZE1 0x800000

/* Frame buffer locations. */
#define FG_FB_ONE_ADDR     VIDEO_RAM
#define FG_FB_TWO_ADDR     (VIDEO_RAM+((T_UINT32)FG_FB_SIZE))
#define FG_FB_THREE_ADDR   (FG_FB_TWO_ADDR+((T_UINT32)FG_FB_SIZE))
#define BG_FB_ADDR            (FG_FB_THREE_ADDR+((T_UINT32)FG_FB_SIZE))


#endif /* _HDUDISPFPANEL_H_ */
