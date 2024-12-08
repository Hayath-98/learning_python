/*
 ******************************************************************************
 * License Information  :  Howell Instruments, Inc.                           *
 *                         "Licensed Software" and "All rights reserved".     *
 ******************************************************************************
 *  File                : hdudispfpoller.h
 *
 *  Description         : This file provides declarations for engine information system poller.
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
 *      1.1          Vinay H         24-Jul-2017             100064
 *      1.2          Divya G P       09-Oct-2017             100064
 *
 * Additional References : None
 *
 ******************************************************************************
 */

#ifndef _HDUDISPFPOLLER_H_
#define _HDUDISPFPOLLER_H_

#include "hdudispfresource.h"/* provides resources */
#include "hdudispfucos.h" /* provides ucos functionalities */
#include "hdudispfoscpu.h"    /* OS function declarations */

extern T_OS_EVENT *Sem_poller_task;
extern T_OS_STK Poller_task_stk[POLLER_TASK_STK_SIZE];

extern void PollerInit(void);
extern void PollerSignalTask(void);

#endif   /* POLLER_H */
