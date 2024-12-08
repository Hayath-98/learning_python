/*
 ******************************************************************************
 * License Information  :  Howell Instruments, Inc.                           *
 *                         "Licensed Software" and "All rights reserved".     *
 ******************************************************************************
 *  File                : hdulibstm32756gevalsdram.h
 *
 *  Description         : This file contains the common defines for sdram
 *
 *  Compiler            : GNU gcc(GNU Tools for ARM Embedded Processors) version 5.4.1 20160919
 *
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
 *      1.2          Shilpa A R      01-Sep-2017         100028
 *
 * Additional References : None
 *
 ******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _HDULIBSTM32756GEVALSDRAM_H_
#define _HDULIBSTM32756GEVALSDRAM_H_

#include "hdulibstm32f7xxhal.h"        /* Header files for HAL driver*/
#include "hdulibstm32f7xxhalsdram.h"   /* Header file of SDRAM HAL module. */
#include "hdulibstm32f7xxhaldef.h"     /*Contains the HAL defination module */
#include "hdulibstm32f746xx.h"         /* CMSIS Cortex-M7 Device Peripheral Access Layer */

/* @brief  SDRAM status structure definition*/
#define   SDRAM_OK         ((T_UINT8)0x00)
#define   SDRAM_ERROR      ((T_UINT8)0x01)

/* @defgroup STM32756G_EVAL_SDRAM_Exported_Constants */
#define SDRAM_DEVICE_ADDR  ((T_UINT32)0xC0000000)
#define SDRAM_DEVICE_SIZE  ((T_UINT32)0x800000)  /* SDRAM device size in MBytes */

/* SDRAM memory width */
#define SDRAM_MEMORY_WIDTH               FMC_SDRAM_MEM_BUS_WIDTH_32

#define SDCLOCK_PERIOD                FMC_SDRAM_CLOCK_PERIOD_3

/* SDRAM refresh counter (100Mhz SD clock) */
#define REFRESH_COUNT                    ((T_UINT32)0x0603)

#define SDRAM_TIMEOUT                    ((T_UINT32)0xFFFF)

/* DMA definitions for SDRAM DMA transfer */
#define __DMAX_CLK_ENABLE                 __HAL_RCC_DMA2_CLK_ENABLE
#define __DMAX_CLK_DISABLE                __HAL_RCC_DMA2_CLK_DISABLE
#define SDRAM_DMAX_CHANNEL                DMA_CHANNEL_0
#define SDRAM_DMAX_STREAM                 DMA2_STREAM0
#define SDRAM_DMAX_IRQN                   DMA2_STREAM0_IRQN


/* @brief  FMC SDRAM Mode definition register defines */
#define SDRAM_MODEREG_BURST_LENGTH_1             ((T_UINT16)0x0000)
#define SDRAM_MODEREG_BURST_LENGTH_2             ((T_UINT16)0x0001)
#define SDRAM_MODEREG_BURST_LENGTH_4             ((T_UINT16)0x0002)
#define SDRAM_MODEREG_BURST_LENGTH_8             ((T_UINT16)0x0004)
#define SDRAM_MODEREG_BURST_TYPE_SEQUEN      ((T_UINT16)0x0000)
#define SDRAM_MODREG_BURST_TYP_INTERLEAV     ((T_UINT16)0x0008)
#define SDRAM_MODEREG_CAS_LATENCY_2              ((T_UINT16)0x0020)
#define SDRAM_MODEREG_CAS_LATENCY_3              ((T_UINT16)0x0030)
#define SDRAM_MODEREG_OPERATING_MODE_STD    ((T_UINT16)0x0000)
#define SDRAM_MODEREG_WRBURST_MODE_PRG ((T_UINT16)0x0000)
#define SDRAM_MODEREG_WRBURST_MOD_SINGLE     ((T_UINT16)0x0200)

/* @defgroup STM32756G_EVAL_SDRAM_Exported_Functions */
T_UINT8 BspSdramInit(void);
void    BspSdramInitializationSequence(T_UINT32 refresh_count);

/*
 * These functions can be modified in case the current settings (e.g. DMA stream)
 * need to be changed for specific application needs
 */
void    BspSdramMspInit(T_SDRAM_HANDLE  *h_sdram);

#endif /* _STM32756G_EVAL_SDRAM_H_ */
