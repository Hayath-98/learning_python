/*
 ******************************************************************************
 * License Information  :  Howell Instruments, Inc.                           *
 *                         "Licensed Software" and "All rights reserved".     *
 ******************************************************************************
 *  File                : hdudispftimers.h
 *
 *  Description         : This file contains functions prototypes for
 *                        exceedance timers
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
 *  Author(s)           : Dhanalakshmi D
 *
 *  Version History     :
 *
 * <Version No.>     <Author>          <Date>         <Problem Report No.>
 *
 *      1.1           Dhanalakshmi     20-Mar-2021             100331
 *      1.2           Dhanalakshmi     20-Mar-2021             100331
 *      1.3           Dhanalakshmi     16-Apr-2021             100339
 *      1.4           Dhanalakshmi     13-May-2021             100350
 *
 * Additional References : None
 *
 *****************************************************************************
 */

#ifndef _HDUDISPFTIMERS_H_
#define _HDUDISPFTIMERS_H_

#include "hdulibbasictypes.h"      /* Standard basic data type definitions */

#define MAX_EXCEED_TIMERS 16


typedef struct
{
   T_UINT8 timer_a249_label;
   T_UINT8 timer_a429_sdi;
   T_BOOL timer_data_flag;
   T_BOOL timer_sec_flag;
	/* Exceedance timer parameters from DAU */
   T_UINT8 timer_id;
   T_UINT8 timer_param;
   T_UINT8 timer_color;
   T_UINT8 timer_flash;
   T_UINT32 timer_seconds;
}T_TIMER_PARAM_STRUCT;


extern T_TIMER_PARAM_STRUCT Exceed_timer_params[MAX_EXCEED_TIMERS];
extern T_UINT16 Timer_a429_tag[MAX_EXCEED_TIMERS];

extern void AppExTimerDraw( void);

#endif /* _HDUDISPFTIMERS_H_ */
