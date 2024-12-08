/*
 ******************************************************************************
 * License Information  :  Howell Instruments, Inc.                           *
 *                         "Licensed Software" and "All rights reserved".     *
 ******************************************************************************
 *  File                : hdudispfwdog.h
 *
 *  Description         : This file provides protoypes for accessing the watch dog timer.
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
 *  Author(s)           : Shruthi MN
 *
 *  Version History     :
 * <Version No.>     <Author>          <Date>         <Problem Report No.>
 *
 *      1.1          Shruthi MN       15-Oct-2017             100083
 *
 * Additional References : None
 *
 ******************************************************************************
 */

#ifndef _HDUDISPFWDOG_H_
#define _HDUDISPFWDOG_H_

#include "hdulibstm32f7xxhaldef.h"    /*Contains the HAL defination module */
#include "hdulibstm32f7xxhaliwdg.h"   /* IWDG interface declarations */


#define WDOG_TIMEOUT_MS             2000U    /* Refer to M_WDOG_PRESCALER */
#define WDOG_FREQ                   32000U   /* Watchdog freq = 32KHz */
#define MAX_RELOAD_VALUE            0x00000FFFUL

/* For this prescaler, max value of M_WDOG_TIMEOUT_mS = 6553 */
#define WDOG_PRESCALER              (IWDG_PRESCALER_64)

/* Initializes the watch dog timer*/
extern void WdogInit(void);

/* Resets watch dog timer.*/
extern void WdogKickWatchDog(void);

#endif /*_HDUDISPFWDOG_H_*/
