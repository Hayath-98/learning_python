/*
 ******************************************************************************
 * License Information  :  Howell Instruments, Inc.                           *
 *                         "Licensed Software" and "All rights reserved".     *
 ******************************************************************************
 *  File                : hdudispfwidgets.h
 *
 *  Description         : Contains routines for widget parameters.
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
 *  Portability         : None
 *
 *  Author(s)           : Vinay H
 *
 *  Version History     :
 * <Version No.>     <Author>          <Date>         <Problem Report No.>
 *
 *      1.1          Vinay H         19-Jul-2017             100064
 *      1.2          Rona B.S        10-Oct-2017             100064
 *      1.3          Shruthi M N     15-Oct-2017             100083
 *      1.4          Shruthi M N     30-Oct-2017             100104
 *      1.5          Sainath G N     21-Jun-2020             100259
 *      1.6          Rona B S        02-Jul-2020             100259
 *      1.7          Dhanalakshmi    12-Sep-2020             100276 
 *
 * Additional References : None
 *
 ******************************************************************************
 */

#ifndef _HDUDISPFWIDGETS_H_
#define _HDUDISPFWIDGETS_H_

#include "hdudispffonts.h"      /*Contains different font information*/
#include "hdudispftext.h"       /*  Routines which maintain text display and updates */
#include "hdudispfconfig.h"     /* contains page and color config information */
#include "hdudispfparams.h"     /* provides the tags for various parameters and parameter units */
#include "hdudispfpolygon2.h"   /* contains routines for polygons configuration */
#include "hdulibbasictypes.h"   /* Standard basic data type definitions */

#define MAX_DPD         13U   /* Maximum digits for digital readout + book ends + delimiter. */
#define BAR_WIDTH       3U    /* Width of the red x bars in pixels. */

/* Used to set pointer slew rate.         */
#define FRAME_MS        40U      /* Number of mSec per frame update. */
#define  DIG_MS         50U      /* Number of mSec per digital update. */

#define DIGITAL_DELAY   333U

/* ROUND DIAL SPECIFIC DEFINITIONS. */
#define MAX_ROUND_DIALS 30U   /* Maximum number of active round dials. */
#define MAX_PPD         5U    /* Maximum pointers per dial definition. */
#define EXTRACT_9_11_BIT 0x0f00U
#define EXTRACT_5_8_BIT  0x00f0U
#define EXTRACT_4_BYTE   0xff000000U

/* Carrot graph */
#define MAX_CARROT_GRAPH 30U

/* Type for a region of the display. */
typedef enum
{
   E_REGION_TYPE_GAUGE,
   E_REGION_TYPE_NUMBER
} T_EREGIONTYPE;

/* Type for On or Off of a Widget */
typedef enum
{
   E_WIDGET_OFF,
   E_WIDGET_ON
}  T_EWIDGETONOFF;

typedef enum
{
   FLASH_ON,
   FLASH_OFF
}  T_EFLASHSTATE;


typedef struct sWidgetParam
{
   /* Dynamic (Run Time) Data */
   /* Updated as per PR100083*/
   T_INT32        s32Dig;         /* Present digital reading. */
   T_INT32        s32DisDig;      /* Digital reading for display. */
   T_PARAM_STAT   eDIsDigStat;

   T_PTEXT     *pText;            /* Handle to the widget text. */
   /* Updated as per PR100083*/
   T_INT32     s32Scaler;         /* Scaler reading for angle/length/.... */
   T_INT32     s32ScalerStep;     /* Step size to Scaler. */
}  T_SWIDGETPARAM;

/* Factor of four magnification is used for anti-aliasing.  */
#define MAG_FACTOR   4U
#define  MAG(x) ((T_INT16)(x*(T_INT16)MAG_FACTOR))

/* Type for a point on the display. */
typedef struct
{
   T_INT16  u16X0;
   T_INT16  u16Y0;
}  T_SDISLOC;


typedef struct
{
   T_EREGIONTYPE  eRegionType;    /* What type of region is it? */
   T_SDISLOC      sDisLocCtr;     /* Center of the region. */
    /* Width of the region if Gauge type, Width of the line if Number type. */
   T_INT32           s32Width;
   T_INT32           s32Height;   /* Height of the region. */
   /* Offset from center to center of text if Gauge, offset to start of line if Number type.. */
   T_SDISLOC         sDisLocO;
   T_ETXFONT         eTXFont;     /* Which font to use. */
   T_UINT8           *pu8Text;    /* Region Text. */
}  T_SDISREGION;

extern T_UINT32   U32_digital_timer;
extern T_UINT8 U8_update_digital;

extern void WidgetsTranslate(T_SRECTPOINT *ppoint_1);

extern T_UINT32 WidgetsDotAddr(T_SDISLOC *ppoint_3);
extern void WidgetsRedX (T_SDISREGION *ps_dis_region, T_SPOLY **pps_poly_red_x);
extern T_UINT32 WidgetsRGB444ToRGB888(T_EPENCOLOR e_pen_color);
extern void WidgetsUpdateRT(T_PARAM_READING  *ps_param, T_SWIDGETPARAM *ps_widget_parm);
extern void WidgetsNumUpdate(T_PARAM_READING *param, T_SWIDGETPARAM *ps_widget_param,
             T_CHAR *ac_dig_text, T_UINT16 u16_format, T_EPENCOLOR e_pen_color);
   /* Updated as per PR100083*/
extern void RedXGauge(T_SDISREGION *ps_dis_region, T_SPOLY *ps_red_x);

#endif /* _HDUDISPFWIDGETS_H_ */
