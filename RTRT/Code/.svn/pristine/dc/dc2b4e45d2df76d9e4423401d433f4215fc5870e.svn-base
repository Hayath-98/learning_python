/*
 ******************************************************************************
 * License Information  :  Howell Instruments, Inc.                           *
 *                         "Licensed Software" and "All rights reserved".     *
 ******************************************************************************
 *  File                : hdudispfconfig.c
 *
 *  Description         : This file initializes the increments all installed Timers
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
 *      1.1          Vinay H         19-Jul-2017             100064
 *      1.2          Rona B S        02-Jul-2020             100259
 *
 * Additional References : None
 *
 ******************************************************************************
 */

#include "hdudispftimer.h"        /* increment a set of user installed timers. */
#include "hdudispfconfig.h"       /* contains page and color config information */
#include "hdudispfwidgets.h"      /* Contains routines for widget params */

T_ELANDSCAPEORPORTRIAT E_orientation = E_LAND_SCAPE_PORTRAIT_UNKNOWN;
T_INT16     S16_panel_height = ZERO;
T_INT16     S16_panel_width = 0;

/*
 * Function                : ConfigSetConfig
 *
 * Description             : Increments all installed Timers.
 *
 * Formal parameter(s)     : T_ELANDSCAPEORPORTRIAT e_land_scape_or_portriat IN Orientation
 *                            of the display.(Horizonatal or Vertical)
 *                           T_INT16 panel_width -IN Width of the panel.
 *                           T_INT16 panel_height -IN Height of the panel
 *
 * Return Value            : None
 *
 * Assumption              : None
 *
 */
void ConfigSetConfig(T_ELANDSCAPEORPORTRIAT e_land_scape_or_portriat, T_INT16 panel_width,
                                                                      T_INT16 panel_height)
{
   /*hdudispfconfig-ConfigSetConfig-DB-LLR-001*/
   E_orientation = e_land_scape_or_portriat;
   S16_panel_height = panel_height;
   S16_panel_width = panel_width;
   TimerInstall(&U32_digital_timer);
}
