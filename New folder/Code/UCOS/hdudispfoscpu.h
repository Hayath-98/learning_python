/*
 ******************************************************************************
 * License Information  :  Howell Instruments, Inc.                           *
 *                         "Licensed Software" and "All rights reserved".     *
 ******************************************************************************
 *  File                : hdudispfoscpu.h
 *
 *  Description         : This file declares the functions used by the OS.
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
 *      1.1           Vinay H       14-Sep-2017             100064
 *
 * Additional References : None
 *
 ******************************************************************************
 */
#ifndef _HDUDISPFOSCPU_H_
#define _HDUDISPFOSCPU_H_

#include "hdulibbasictypes.h"            /* Contains basic data types */

typedef T_UINT32    T_OS_STK;        /* Each stack entry is 32-bit wide*/

extern T_UINT32 U32_critical_sr;

extern T_UINT32 SaveStatusReg(void);
extern void RestoreStatusReg(T_UINT32 U32_critical_sr);

#define OS_ENTER_CRITICAL()     {U32_critical_sr = SaveStatusReg();}
#define OS_EXIT_CRITICAL()      {RestoreStatusReg(U32_critical_sr);}
#define OS_TASK_SW()            (OsCtxSw())

#endif /*_HDUDISPFOSCPU_H_*/
