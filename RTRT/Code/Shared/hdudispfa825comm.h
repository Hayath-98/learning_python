/*
 ******************************************************************************
 * License Information  :  Howell Instruments, Inc.                           *
 *                         "Licensed Software" and "All rights reserved".     *
 ******************************************************************************
 *  File                : hdudispfa825comm.h
 *
 *  Description         : prototype for arinc 825 communications
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
 * <Version No.>      <Author>          <Date>         <Problem Report No.>
 *
 *      1.1           Vinay H       24-Jul-2017             100064
 *      1.2           Vinay H       09-Oct-2017             100064
 *      1.3           Shruthi M N   13-Oct-2017             100083
 *
 * Additional References : None
 *
 ******************************************************************************
 */

#ifndef _HDUDISPFA825COMM_H_
#define _HDUDISPFA825COMM_H_

#include "hdudispfoscpu.h"    /* defines the OS configurations  */
#include "hdudispfresource.h"  /* provides central location to use of On Chip Peripherals*/

extern T_OS_STK A825_comm1_task_stk[A825COMM_TASK_STK_SIZE];
extern T_OS_STK A825_comm2_task_stk[A825COMM_TASK_STK_SIZE];

/*Updated as per PR100083*/
extern T_UINT32 Can1_msg_cntr;

extern void A825CommInit1(void);
extern void A825CommInit2(void);

#endif
