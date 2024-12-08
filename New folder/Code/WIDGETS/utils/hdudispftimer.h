/*
 ******************************************************************************
 * License Information  :  Howell Instruments, Inc.                           *
 *                         "Licensed Software" and "All rights reserved".     *
 ******************************************************************************
 *  File                : hdudispftimer.h
 *
 *  Description         : Used to increment a set of user installed timers.
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
 *      1.1          Vinay H         14-Sep-2017             100064
 *
 * Additional References : None
 *
 ******************************************************************************
 */

#ifndef _HDUDISPFTIMER_H_
#define _HDUDISPFTIMER_H_

#include "hdulibbasictypes.h" /* Contains basic header definations */

/* TYPES       */
typedef  T_UINT32 T_TIMER;

/* FUNCTIONS   */
extern void TimerInstall(volatile T_TIMER *timer);
extern void TimerDriver(void);
extern void TimerReset(volatile T_TIMER *timer);
extern void TimerPreset(volatile T_TIMER *timer, T_INT32 s32_set_val);

#endif /*_HDUDISPFTIMER_H_*/
