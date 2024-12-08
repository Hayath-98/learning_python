/*
 ******************************************************************************
 * License Information  :  Howell Instruments, Inc.                           *
 *                         "Licensed Software" and "All rights reserved".     *
 ******************************************************************************
 *  File                : hdudispfdma2.h
 *
 *  Description         : This file contains the common defines and functions prototypes for
 *                        hdudispfdma2.c
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
 *  Author(s)           : Rona B.S
 *
 *  Version History     :
 *
 * <Version No.>     <Author>          <Date>         <Problem Report No.>
 *
 *      1.1          Rona B.S        11-Sep-2017             100064
 *
 * Additional References : None
 *
 *****************************************************************************
 */

#ifndef _HDUDISPFDMA2_H_
#define _HDUDISPFDMA2_H_

#include "hdulibstm32f7xxhaldmaex.h"  /*Contains the DMA EX HAL module */
#include "hdulibstmcorecomm.h"  /* Header files for Core Communication*/
#include "hdulibstm32f746xx.h"  /* CMSIS Cortex-M7 Device Peripheral Access Layer */
#include "hdulibstm32f7xxhal.h" /* Header files for HAL driver*/
#include "hdulibbasictypes.h" /* Standard basic data type definitions */


#define DMA_INSTANCE               DMA2_STREAM0
#define DMA_CHANNEL                DMA_CHANNEL_0
#define DMA_INSTANCE_IRQ           DMA2_STREAM0_IRQN
extern T_DMA_HANDLE Dma_handle;
extern void Dma2ClearForeground(void *frame_buffer, T_UINT32 u32_size);
extern void Dma2Init(void);


#endif /* _HDUDISPFDMA2_H_ */

