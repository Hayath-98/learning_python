/*
 ******************************************************************************
 * License Information  :  Howell Instruments, Inc.                           *
 *                         "Licensed software and All rights reserved".       *
 ******************************************************************************
 *  File                : hdudispfmain.h
 *
 *  Description         : This file contains prototypes for Main module.
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
 *  Author(s)           : Shilpa A R
 *
 *  Version History     :
 * <Version No.>      <Author>        <Date>         <Problem Report No.>
 *     1.1            Shilpa A R     28-Sep-2017             100064
 *     1.2            Divya G P      09-Oct-2017             100064
 *
 * Additional References : None
 *
 ******************************************************************************
 */
#ifndef _HDUDISPFMAIN_H_
#define _HDUDISPFMAIN_H_

#include "hdulibbasictypes.h"            /* Contains basic header definitions */

extern T_INT32 DisplayMain(void);
extern void SysTickHandler(void);

#endif
