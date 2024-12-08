/*
 ******************************************************************************
 * License Information  :  Howell Instruments, Inc.                           *
 *                         "Licensed Software" and "All rights reserved".     *
 ******************************************************************************
 *  File                : hdudispbpanel.h
 *
 *  Description         : This file contains the common defines and functions prototypes for
 *                        hdudispbpanel.c.
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
 *
 * <Version No.>     <Author>          <Date>         <Problem Report No.>
 *
 *      1.1          Ajay J G        02-Aug-2017             -
 *      1.2          Divya G P       01-Sep-2017           100028
 *      1.3          Rona B.S        04-Nov-2017           100156
 *      1.4          Vinay H         23-Mar-2018           100196
 *      1.5          Rona B.S        21-Jun-2020           100259  
 *      1.6          Rona B.S        29-Jun-2020           100259
 *
 * Additional References : None
 *
 ******************************************************************************
 */

#ifndef _HDUDISPBPANEL_H_
#define _HDUDISPBPANEL_H_

#include "hdulibbasictypes.h"             /* Contains basic data types */

/* *** CAUTION!  Last 1 Meg of 8 Meg is reserved for frame buffer.  */

#define FB_SIZE (PANEL_WIDTH*PANEL_HEIGHT)

/* Panel on the F7 Discovery. */
#define RK043FN48H      0
/* Panel on the Prototype EIS. */
#define AA065VD51       1
/* Panel on the Prototype #2 EIS. */
#define AA07MC52        3
/* Panel on the Prototype DPI. */
#define KD035HVFMA035   4
/* Panel on C130 Prototype EIS. */
#define AA104SL12       5
/*  1024 x 768 Panel. */
#define AA104XD12       6

/*********************************/
/* Pixel Formats.*/
/*********************************/
#define PIXEL_FORMAT_ARGB8888    0
#define PIXEL_FORMAT_RGB888      1
#define PIXEL_FORMAT_RGB565         2
#define PIXEL_FORMAT_ARGB1555    3
#define PIXEL_FORMAT_ARGB4444    4
#define PIXEL_FORMAT_L8             5
#define PIXEL_FORMAT_AL44           6
#define PIXEL_FORMAT_AL88       7

#define  FOREGROUND_PIXEL_FORMAT    PIXEL_FORMAT_AL44

#define  BACKGROUND_PIXEL_FORMAT    PIXEL_FORMAT_RGB565

#define FG_FB_SIZE (PANEL_WIDTH*PANEL_HEIGHT)

#define BSP_LCD_DRAWPIXEL(Xpos,Ypos,Color)\
       (*(volatile T_UINT8*) (((T_UINT32)Vp_fgfb) + ((Ypos*PANEL_WIDTH) + Xpos)) = (uint8_t)Color;)

#define ISBLANK(Xpos,Ypos)\
      (*(volatile T_UINT8*) ((T_UINT32)Vp_fgfb + (Ypos*PANEL_WIDTH + Xpos)) == 0)

#define AA_SHIFT  4
#define AA_MASK      0xf0
extern void *Vp_fgfb;               /* Pointer to frame buffer for Drawing.*/

/* Index of colors in the CLUT*/
typedef  enum
{
   /*Boot pen color - BPC, used only in boot software.*/
   BLACK_BPC,
   DARK_RED_BPC,
   RED_BPC,
   PINK_BPC,
   TEAL_BPC,
   GREEN_BPC,
   BRIGHT_GREEN_BPC,
   TURQUOISE_BPC,
   DARK_BLUE_BPC,
   VIOLET_BPC,
   BLUE_BPC,
   LIGHT_GRAY_BPC,
   GRAY_BPC,
   DARK_YELLOW_BPC,
   YELLOW_BPC,
   WHITE_BPC
}  T_EPEN_COLOR;




extern T_EPEN_COLOR Pen_color;                  /* Present value of the pen color.*/

extern void BspLcdSetPenColor(T_EPEN_COLOR color);

extern void LcdConfig(void);

#endif /* _HDUDISPBPANEL_H_ */
