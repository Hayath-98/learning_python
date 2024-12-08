/*
 ******************************************************************************
 * License Information  :  Howell Instruments, Inc.                           *
 *                         "Licensed Software" and "All rights reserved".     *
 ******************************************************************************
 *  File                : hdulibstm32f7xxhalnor.h
 *
 *  Description         : This file provides a generic firmware to drive NOR memories mounted
 *                        as external device.
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
 * <Version No.>     <Author>          <Date>         <Problem Report No.>
 *
 *      1.1          Rona B.S          12-Sep-2017          100064
 *
 * Additional References : None
 *
 ******************************************************************************
 */

/* Define to prevent recursive inclusion */
#ifndef _HDULIBSTM32F7XXHALNOR_H_
#define _HDULIBSTM32F7XXHALNOR_H_


/* Includes */
#include "hdulibstm32f7xxhalfmc.h" /* Defines FMC specification */

typedef enum
{
  HAL_NOR_STATE_RESET             = 0x00U,  /*NOR not yet initialized or disabled  */
  HAL_NOR_STATE_READY             = 0x01U,  /*NOR initialized and ready for use    */
  HAL_NOR_STATE_BUSY              = 0x02U,  /*NOR internal processing is ongoing   */
  HAL_NOR_STATE_ERROR             = 0x03U,  /*NOR error state                      */
  HAL_NOR_STATE_PROTECTED         = 0x04U   /*NOR NORSRAM device write protected   */
}T_HAL_NOR_STATE_TYPE;

typedef struct
{
  T_FMC_NORSRAM            *Instance;    /*Register base address*/

  T_FMC_NORSRAM_EXTENDED   *Extended;    /*Extended mode register base address*/

  T_FMC_NORSRAM_INIT       Init;         /*NOR device control configuration parameters*/

  T_HAL_LOCK               Lock;         /*NOR locking object*/

  T_HAL_NOR_STATE_TYPE        State;        /*NOR device access state*/

}T_NOR_HANDLE_TYPE;


/* Initialization functions */
T_HAL_STATUS HalNorInit(T_NOR_HANDLE_TYPE *h_nor, T_FMC_NORSRAM_TIMING *timing,
                        T_FMC_NORSRAM_TIMING *ext_timing);

void HalNorMspInit(T_NOR_HANDLE_TYPE *h_nor);


#define NOR_ADDR_SHIFT(__NOR_ADDRESS, __NOR_MEMORY_WIDTH_, __ADDRESS__)\
                      ((T_UINT32)(((__NOR_MEMORY_WIDTH_) == NOR_MEMORY_16B)?\
                      ((T_UINT32)((__NOR_ADDRESS) + (2 * (__ADDRESS__)))):\
                      ((T_UINT32)((__NOR_ADDRESS) + (__ADDRESS__)))))

#define NOR_WRITE(__ADDRESS__, __DATA__)   \
               (do{    \
                 (*(__IO T_UINT16 *)((T_UINT32)(__ADDRESS__)) = (__DATA__)); \
                 __DSB();                                                    \
               } while(ZERO))

/* NOR memory data width */
#define NOR_MEMORY_8B            ((T_UINT8)0x0U)
#define NOR_MEMORY_16B           ((T_UINT8)0x1U)

#endif /* _HDULIBSTM32F7XXHALNOR_H_ */

