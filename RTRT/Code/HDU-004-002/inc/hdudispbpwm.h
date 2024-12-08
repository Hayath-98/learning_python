/*
 ******************************************************************************
 * License Information  :  Howell Instruments, Inc.                           *
 *                         "Licensed Software" and "All rights reserved".     *
 ******************************************************************************
 *  File                : hdudispbpwm.h
 *
 *  Description         : This file contains the common defines and functions prototypes for
 *                        hdudispbpwm.c.
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
 *  Author(s)           : Ajay J G
 *
 *  Version History     :
 *
 * <Version No.>     <Author>          <Date>         <Problem Report No.>
 *
 *      1.1          Ajay J G        02-Aug-2017             -
 *      1.2          Divya G P       02-Sep-2017       100028
 *
 * Additional References : None
 *
 ******************************************************************************
 */

#ifndef _HDUDISPBPWM_H_
#define _HDUDISPBPWM_H_

extern void PwmInit(void);
extern void PwmLcdBackLightPcnt(T_UINT32 u32_pcnt_onx1000);

#endif /*_HDUDISPBPWM_H_*/
