/*
 ******************************************************************************
 * License Information  :  Howell Instruments, Inc.                           *
 *                         "Licensed Software" and "All rights reserved".     *
 ******************************************************************************
 *  File                : hdudispfpwm.h
 *
 *  Description         : This file declares the pulse width modulation channels which
 *                         control display and bezel backlight brightness.
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
 *      1.1           Shilpa A R          21-Jul-2017             100064
 *
 * Additional References : None
 *
 ******************************************************************************
 */

#ifndef _HDUDISPFPWM_H_
#define _HDUDISPFPWM_H_

extern void PwmInit(void);
extern void PwmBackLightDriver(void);
extern void PwmLcdBackLightPcnt(T_UINT32 u32_pcnt_onx1000);
extern void PwmBackLightStepTo(T_INT16 new_auto_brightness);
extern void PwmBackLightNewMode(T_INT16 new_auto_brightness);
extern void PwmBlink(void);

#endif /* _HDUDISPFPWM_H_ */
