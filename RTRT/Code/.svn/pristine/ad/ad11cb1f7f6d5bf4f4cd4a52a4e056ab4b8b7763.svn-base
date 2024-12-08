/*
 ******************************************************************************
 * License Information  :  Howell Instruments, Inc.                           *
 *                         "Licensed Software" and "All rights reserved".     *
 ******************************************************************************
 *  File                : hdulibstm32f7xxhal.c
 *
 *  Description         : This is the common part of the HAL initialization
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
 *      1.1          Vinay H           25-Jul-2017             -
 *      1.2          Divya G P         01-Sep-2017    100028
 *      1.3          Shilpa A R        06-Nov-2017    100156
 *      1.4          Rona B S          12-Sep-2020    100276 
 *
 * Additional References : None
 *
 ******************************************************************************
 */

#include "hdulibstm32f7xxhal.h"        /* Header files for HAL driver*/
#include "hdulibbasictypes.h"          /* Define standard data types */
#include "hdulibcorecm7.h"             /* CMSIS Cortex-M7 Core Peripheral Access Layer */
#include "hdulibstm32f7xxhalcortex.h"  /* Header file of CORTEX HAL module */
#include "hdulibstm32f7xxhaldef.h"     /* Header file of CORTEX HAL module */
#include "hdulibstm32f7xxhalflash.h"   /* Header file of FLASH HAL module. */
#include "hdulibstm32f7xxhalconf.h"    /* provides HAL configurations. */


/* HAL_Private_Variables */
static __IO T_UINT32 Uw_tick = ZERO;

/*
 * Function                :  HalInit
 *
 * Description             :  This function is used to initialize the HAL Library
 *
 * Formal parameter(s)     :  None
 *
 * Return Value            :  T_HAL_STATUS - returns HAL_OK when all HAL library module
 *                                           is initialized
 *
 * Assumption              :  None
 *
 */

T_HAL_STATUS HalInit(void)
{
   /*hdulibstm32f7xxhal-HalInit-DB-LLR-001*/
   /* Configure Flash pre-fetch and Instruction cache through ART accelerator */
   if (ART_ACCLERATOR_ENABLE != ZERO)
   {
      __HAL_FLASH_ART_ENABLE();  /* ART_ACCLERATOR_ENABLE */
   }
   else
   {
      ;/*Do nothing*/
   }

   /*hdulibstm32f7xxhal-HalInit-DB-LLR-002*/
   /* Set Interrupt Group Priority */
   HALNvicSetPriorityGrouping(NVIC_PRIORITYGROUP_4);

   /*hdulibstm32f7xxhal-HalInit-DB-LLR-003*/
   /* Use systick as time base source and configure 1ms tick (default clock after Reset is HSI) */
   HALInitTick(TICK_INT_PRIORITY);

   /*hdulibstm32f7xxhal-HalInit-DB-LLR-005*/
   /* Return function status */
   return HAL_OK;
}

/*
 * Function                :  HALInitTick
 *
 * Description             :  This function configures the source of the time base.
 *                            The time source is configured  to have 1ms time base with a dedicated
 *                            tick interrupt priority.
 *
 * Formal parameter(s)     :  T_UINT32 tick_priority - IN specifies the priority
 *
 * Return Value            :  T_HAL_STATUS - returns HAL_OK when all source time base is configured
 *
 * Assumption              :  None
 *
 */
T_HAL_STATUS HALInitTick(T_UINT32 tick_priority)
{
   /*hdulibstm32f7xxhal-HALInitTick-DB-LLR-001*/
   /*Configure the SysTick to have interrupt in 1ms time basis*/
   HALSysTickConfig(System_core_clock/1000);

   /*hdulibstm32f7xxhal-HALInitTick-DB-LLR-002*/
   /*Configure the SysTick IRQ priority */
   HalNvicSetPriority(SYSTICK_IRQN, tick_priority,ZERO);

   /*hdulibstm32f7xxhal-HALInitTick-DB-LLR-003*/
   /* Return function status */
   return HAL_OK;
}

/*
 * Function                :  HalIncTick
 *
 * Description             :  This function is called to increment  a global variable "Uw_tick"
 *                            used as application time base.
 *
 * Formal parameter(s)     :  None
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */
void HalIncTick(void)
{
   /*hdulibstm32f7xxhal-HalIncTick-DB-LLR-001*/
   Uw_tick++;
}

/*
 * Function                :  HALGetTick
 *
 * Description             :  This function provides a tick value in millisecond
 *
 * Formal parameter(s)     :  None
 *
 * Return Value            :  T_UINT32 - returns time tick value
 *
 * Assumption              :  None
 *
 */
T_UINT32 HALGetTick(void)
{
   /*hdulibstm32f7xxhal-HALGetTick-DB-LLR-001*/
   return Uw_tick;
}

/*
 * Function                :  HalDelay
 *
 * Description             :  This function provides delay based on the value
 *                            present in the function parameter.
 *
 * Formal parameter(s)     :  T_UINT32 delay - IN specifies the delay time length, in milliseconds.
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */
void HalDelay(__IO T_UINT32 delay)
{
   T_UINT32 tick_start = ZERO;

   /*hdulibstm32f7xxhal-HalDelay-DB-LLR-001*/
   tick_start = HALGetTick();

   /*hdulibstm32f7xxhal-HalDelay-DB-LLR-002*/
   while((HALGetTick() - tick_start) < delay)
   {
   }
}
