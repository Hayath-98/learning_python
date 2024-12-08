/*
 ******************************************************************************
 * License Information  :  Howell Instruments, Inc.                           *
 *                         "Licensed Software" and "All rights reserved".     *
 ******************************************************************************
 *  File                : hdudispfapp.h
 *
 *  Description         : This file contains Engine Information System application
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
 *      1.1           Shilpa A R        12-Sep-2017             100064
 *      1.2           Dhanalakshmi      20-Mar-2021             100331
 *      1.3           Dhanalakshmi      20-Mar-2021             100331
 *
 * Additional References : None
 *
 ******************************************************************************
 */

#ifndef _HDUDISPFAPP_H_
#define _HDUDISPFAPP_H_

#include "hdudispfresource.h" /* provides central location to use On Chip Peripherals*/
#include "hdudispfucos.h"     /* defines the implementation of uC/OS routines  */
#include "hdudispfarinc825.h" /* Define the structure for an ARINC 825 Message. */
#include "hdudispfrtd.h"      /* Provide mapping for all A825 incoming parameters */

extern T_OS_EVENT *Sem_app_task;
extern T_OS_STK App_task_stk[APP_TASK_STK_SIZE];
extern void AppInit(void);
extern T_UINT32 Time_in_sec;

extern T_UINT32 AppU32NOC(T_A825_MESSAGE *s_mess, T_EA825BUS a825_bus);
extern T_UINT32 AppU32NSC(T_A825_MESSAGE *s_mess, T_EA825BUS a825_bus);

#endif   /* _HDUDISPFAPP_H_   */
