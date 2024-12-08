/*
 ******************************************************************************
 * License Information  :  Howell Instruments, Inc.                           *
 *                         "Licensed Software" and "All rights reserved".     *
 ******************************************************************************
 *  File                : hdulibstm32f7xxhalsdram.h
 *
 *  Description         : Header file of SDRAM HAL module.
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
 *      1.1          Vinay H         26-Jul-2017             -
 *      1.2          Divya G P       02-Sep-2017      100028
 *
 * Additional References : None
 *
 ******************************************************************************
 */

/* Define to prevent recursive inclusion */
#ifndef _HDULIBSTM32F7XXHALSDRAM_H_
#define _HDULIBSTM32F7XXHALSDRAM_H_

/* Includes*/
#include "hdulibstm32f7xxhaldef.h"      /*Contains the HAL defination module */
#include "hdulibstm32f7xxhaldma.h"      /*Contains the DMA HAL defination module */
#include "hdulibstm32f7xxhalfmc.h"      /*Contains the FMC HAL defination module */

/* Exported typedef*/

typedef enum
{
   HAL_SDRAM_STATE_RESET             = 0x00U,  /* SDRAM not yet initialized or disabled */
   HAL_SDRAM_STATE_READY             = 0x01U,  /* SDRAM initialized and ready for use   */
   HAL_SDRAM_STATE_BUSY              = 0x02U,  /* SDRAM internal process is ongoing     */
   HAL_SDRAM_STATE_ERROR             = 0x03U,  /* SDRAM error state                     */
   HAL_SDRAM_STATE_WRITE_PROTECTED   = 0x04U,  /* SDRAM device write protected          */
   HAL_SDRAM_STATE_PRECHARGED        = 0x05U   /* SDRAM device precharged               */
}T_HAL_SDRAM_STATE;

typedef struct
{
   T_FMC_SDRAM             *Instance;  /* Register base address*/

   T_FMC_SDRAM_INIT         Init;       /* SDRAM device configuration parameters */

   __IO T_HAL_SDRAM_STATE   State;      /* SDRAM access state*/

   T_HAL_LOCK               Lock;       /* SDRAM locking object*/

   T_DMA_HANDLE             *hdma;     /* Pointer DMA handler*/
}T_SDRAM_HANDLE;

#define __HAL_SDRAM_RESET_HANDLE_STATE(__HANDLE__) ((__HANDLE__)->State = HAL_SDRAM_STATE_RESET)

T_HAL_STATUS HALSdramInit(T_SDRAM_HANDLE *hsdram, T_FMC_SDRAM_TIMING *Timing);
extern void HALSdramMspInit(T_SDRAM_HANDLE *hsdram);

/* SDRAM Control functions*/
T_HAL_STATUS HalSdramSendCommand(T_SDRAM_HANDLE *hsdram,
                                 T_FMC_SDRAM_COMMAND *Command, T_UINT32 Timeout);
T_HAL_STATUS HalSdramProgramRefreshRate(T_SDRAM_HANDLE *hsdram, T_UINT32 RefreshRate);

#endif /* __STM32F7xx_HAL_SDRAM_H */
