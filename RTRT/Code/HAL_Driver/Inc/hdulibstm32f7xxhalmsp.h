/*
 ******************************************************************************
 * License Information  :  Howell Instruments, Inc.                           *
 *                         "Licensed Software" and "All rights reserved".     *
 ******************************************************************************
 *  File                : hdulibstm32f7xxhalmsp.h
 *
 *  Description         : Header file of HAL MSP module.
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
 * <Version No.>     <Author>          <Date>         <Problem Report No.>
 *
 *      1.1          Shilpa A R        23-Aug-2017             -
 *
 * Additional References : None
 *
 ******************************************************************************
 */

#ifndef _HDULIBSTM32F7XXHALMSP_H_
#define _HDULIBSTM32F7XXHALMSP_H_

#include "hdulibstm32f7xxhalcrc.h"           /*Contains the CRC HAL module */
#include "hdulibstm32f7xxhalltdc.h"          /*Contains the LTDC HAL module */

extern void HalLtdcMspInit();
extern void HalCRCMspInit();

#endif /* _HDULIBSTM32F7XXHALMSP_H_ */
