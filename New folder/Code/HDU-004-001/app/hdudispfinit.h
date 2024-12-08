/*
 ******************************************************************************
 * License Information  :  Howell Instruments, Inc.                           *
 *                         "Licensed Software" and "All rights reserved".     *
 ******************************************************************************
 *  File                : hdudispfinit.h
 *
 *  Description         : Creates and schedules the init task
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
 *      1.1          Vinay H         13-Sep-2017             100064
 *      1.2          Divya G P       10-Oct-2017             100064
 *
 * Additional References : None
 *
 ******************************************************************************
 */

#ifndef _HDUDISPFINIT_H_
#define _HDUDISPFINIT_H_

#include "hdudispfresource.h" /* provides central location to use On Chip Peripherals*/
#include "hdulibbasictypes.h" /* provides basic datatypes */
#include "hdudispfoscpu.h"  /* OS function declarations */

extern T_BOOL Init_b_done;
extern T_OS_STK Init_task_stk[INIT_TASK_STK_SIZE];
extern void InitInit(void);
extern void InitSignalTask(void);
extern void ITInterrupsInit(void);

#endif

