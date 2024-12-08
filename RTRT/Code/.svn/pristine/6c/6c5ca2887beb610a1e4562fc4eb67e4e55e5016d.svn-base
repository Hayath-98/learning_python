/*
 ******************************************************************************
 * License Information  :  Howell Instruments, Inc.                           *
 *                         "Licensed software and All rights reserved".       *
 ******************************************************************************
 *  File                : hdudispfcbit.h
 *
 *  Description         : This file contains prototypes for CBIT test.
 *
 *  Compiler            : GNU gcc(GNU Tools for ARM Embedded Processors) version 5.4.1 20160919
 *
 *  Compiler options    : As per section 10.3.1 of Software Development Plan (HDU-001-002).
 *
 *  Pragma              : None.
 *
 *  H/W platform        : ARM Cortex-M7 (STM32F767)
 *
 *  Portability         : None
 *
 *  Author(s)           : Rajalakshmi S
 *
 *  Version History     :
 * <Version No.>      <Author>        <Date>         <Problem Report No.>
 *     1.1            Rajalakshmi S    08-Sep-2017             100064
 *
 * Additional References : None
 *
 ******************************************************************************
 */
#ifndef _HDUDISPFCBIT_H_
#define _HDUDISPFCBIT_H_

#include "hdudispfresource.h"    /* provides central location to use On Chip Peripherals*/
#include "hdulibbasictypes.h"  /* Standard basic data type definitions */
#include "hdudispfucos.h"        /* uC/OS routines for the real-time kernel */

#define STK_VAL 0xDEADDEADU

extern T_OS_EVENT *Sem_cbit_task ;
extern T_OS_STK    Cbit_task_stack[CBIT_TASK_STK_SIZE];

extern void CbitSignalTask(void);
extern void CbitInit(void);

#endif
