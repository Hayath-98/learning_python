/*
 ******************************************************************************
 * License Information  :  Howell Instruments, Inc.                           *
 *                         "Licensed Software" and "All rights reserved".     *
 ******************************************************************************
 *  File                : hdudispfconfig.h
 *
 *  Description         : This file contain prototype to initializes the
 *                         increments all installed Timers
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
 *  Author(s)           : Vinay H
 *
 *  Version History     :
 * <Version No.>     <Author>          <Date>         <Problem Report No.>
 *
 *      1.1          Vinay H          19-Jul-2017             100064
 *      1.2          Shruthi M N      04-Nov-2017             100120
 *      1.3          Dhanalakshmi D   21-Jun-2020             100259
 *      1.4          Rona B S         02-Jul-2020             100259
 *      1.5          Dhanalakshmi     12-Sep-2020             100276 
 *      1.6          Dhanalakshmi     28-Sep-2020             100284 
 *
 * Additional References : None
 *
 ******************************************************************************
 */

#ifndef _HDUDISPFCONFIG_H_
#define _HDUDISPFCONFIG_H_

#include "hdulibbasictypes.h"  /* Standard basic data type definitions */

#define MAX_PANEL_WIDTH    1024U

/* Select orientation */
/* 4 bits per color for various hues (RGB 444).    */
/*Updated as per PR100120 */
typedef  enum
{
   BLACK = 0x000,
   DARK_RED = 0x400,
   RED = 0xf00,
   CAS_RED = 0xf44,
   CAS_REV_RED = 0xf44,
   LIGHT_RED = CAS_RED,
   PINK = 0xf0f,
   TEAL = 0x0ff,
   GREEN = 0x0b0,
   BRIGHT_GREEN = 0x0f0,
   TURQUOISE = 0x4ed,
   DARK_BLUE = 0x00a,
   VIOLET = 0x82e,
   BLUE = 0x00f,
   LIGHT_GRAY = 0xccc,
   GRAY = 0x888,
   DARK_GRAY = 0x444,
   DARK_YELLOW = 0x880,
   YELLOW = 0xff0,
   CAS_AMBER = YELLOW,
   WHITE = 0xfff,
   CAS_WHITE = WHITE,
   ORANGE = 0xd60,
   INVALID_COLOR = 0xffff
}  T_EPENCOLOR;

/* Is the MFD landscape or portrait? */
typedef  enum
{
   E_LAND_SCAPE_PORTRAIT_UNKNOWN = 0,
   E_LAND_SCAPE,
   E_PORTRAIT
}  T_ELANDSCAPEORPORTRIAT;

#define  POLY_POINTS_AVAILABLE   3200U
#define  POLYS_AVAILABLE          300U

extern void *Vp_fgfb2;
extern void ConfigSetConfig(T_ELANDSCAPEORPORTRIAT e_land_scape_or_portriat, T_INT16 panel_width,
                                                                  T_INT16 panel_height);
extern T_ELANDSCAPEORPORTRIAT E_orientation;
extern T_INT16 S16_panel_height;
extern T_INT16 S16_panel_width;

#endif /* _HDUDISPFCONFIG_H_ */
