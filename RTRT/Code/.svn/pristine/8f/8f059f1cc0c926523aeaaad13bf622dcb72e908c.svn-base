/*
 ******************************************************************************
 * License Information  :  Howell Instruments, Inc.                           *
 *                         "Licensed Software" and "All rights reserved".     *
 ******************************************************************************
 *  File                : hdudispfoffside.h
 *
 *  Description         : contains prototype for transmissions and processing of
 *                        user defined node service codes and heart beat NOC
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
 *      1.1           Shilpa A R       11-Sep-2017             100064
 *      1.2           Rona B S         10-Oct-2017             100064
 *      1.3          Shruthi M N       30-Oct-2017             100104
 *      1.4          Dhanalakshmi D    21-Jun-2020             100259
 *      1.5          Rona B S          29-Jun-2020             100259
 *      1.6          Dhanalakshmi      20-Mar-2021             100331
 *      1.7          Dhanalakshmi      20-Mar-2021             100331
 *
 * Additional References : None
 *
 ******************************************************************************
 */

#ifndef _HDUDISPFOFFSIDE_H_
#define _HDUDISPFOFFSIDE_H_

#include "hdudispfarinc825.h"   /* Define the structure for an ARINC 825 Message. */
#include "hdulibbasictypes.h" /* Standard basic data type definitions */

extern void OffsideSwitchScreen(T_UINT8 u8_page_num);

extern void OffsideCalibration(T_UINT8 loop_i);
extern void OffsideCalibrationA825(T_UINT8 engine_count, T_UINT8 parameter_label);

extern void OffsideTimerStart(T_UINT32 U32_initial_value);
extern void OffsideTimerStop(T_UINT32 u32_stop_value);
extern void OffsideTimerReset(void);

extern void OffsideProcessA825NOC(T_A825_MESSAGE *s_mess);
extern void OffsideProcessA825NSC(T_A825_MESSAGE *s_mess);

extern void OffsideHeartBeat(void);
extern void OffsideCoolTimer(T_UINT8 cool_timer_state);
extern void OffsideFuelFlow(T_UINT8 Fuel_flow_state);

/* From other files*/
extern void GrappSetPage(T_UINT8   u8MyPage);

#endif /* _HDUDISPFOFFSIDE_H_ */
