/*
 ******************************************************************************
 * License Information  :  Howell Instruments, Inc.                           *
 *                         "Licensed Software" and "All rights reserved".     *
 ******************************************************************************
 *  File                : hdulibstm32f7xxhaldef.h
 *
 *  Description         : This file contains HAL common defines, enumeration, macros and
 *                        structures definitions.
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
 *      1.2          Rona B.S        02-Sep-2017            100028 
 *
 * Additional References : None
 *
 ******************************************************************************
 */

/* Define to prevent recursive inclusion */
#ifndef _HDULIBSTM32F7XXHALDEF_H_
#define _HDULIBSTM32F7XXHALDEF_H_

/* Includes */
#include "hdulibstm32hallegacy.h"   /* defines the STM32Cube HAL constants, function */
#include "hdulibstm32f7xx.h"        /* CMSIS STM32F7xx Peripheral Access Layer Header File.*/
#include "hdulibbasictypes.h"       /* Define standard data types */
#include "hdulibstm32f7xxhalconf.h" /* provides HAL configurations. */

typedef enum
{
  HAL_OK       = 0x00U,
  HAL_ERROR    = 0x01U,
  HAL_BUSY     = 0x02U,
  HAL_TIMEOUT  = 0x03U
} T_HAL_STATUS;


typedef enum
{
  HAL_UNLOCKED = 0x00,
  HAL_LOCKED   = 0x01
} T_HAL_LOCK;

#define HAL_MAX_DELAY      0xFFFFFFFFU

#define HAL_IS_BIT_SET(REG, BIT)         (((REG) & (BIT)) != RESET)
#define HAL_IS_BIT_CLR(REG, BIT)         (((REG) & (BIT)) == RESET)

#define __HAL_LINKDMA(__HANDLE__, __PPP_DMA_FIELD__, __DMA_HANDLE__)           \
                        do{                                                    \
                           (__HANDLE__)->__PPP_DMA_FIELD__ = &(__DMA_HANDLE__);\
                           (__DMA_HANDLE__).Parent = (__HANDLE__);             \
                          } while(ZERO)

#define UNUSED(x) ((void)(x))

#define __HAL_RESET_HANDLE_STATE(__HANDLE__) ((__HANDLE__)->State = ZERO)

#define __HAL_LOCK(__HANDLE__)                                         \
                               do{                                     \
                                  if(HAL_LOCKED == (__HANDLE__)->Lock ) \
                                  {                                     \
                                     return HAL_BUSY;                   \
                                  }                                     \
                                  else                                  \
                                  {                                     \
                                     (__HANDLE__)->Lock = HAL_LOCKED;   \
                                  }                                     \
                                }while (ZERO)

#define __HAL_UNLOCK(__HANDLE__)                                      \
                                do{                                    \
                                    (__HANDLE__)->Lock = HAL_UNLOCKED;  \
                                  }while (ZERO)

#define __RAM_FUNC T_HAL_STATUS  __attribute__((section(".RamFunc")))

/* ARM & GNUCompiler */
#define __NOINLINE __attribute__ ( (noinline) )

#endif /* _HDULIBSTM32F7XXHALDEF_H_*/

