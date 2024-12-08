/*
 ******************************************************************************
 * License Information  :  Howell Instruments, Inc.                           *
 *                         "Licensed Software" and "All rights reserved".     *
 ******************************************************************************
 *  File                : hdulibstm32f7xxhalcortex.c
 *
 *  Description         : This file provides firmware functions to manage the following
 *                        functionalities of the CORTEX:
 *                        - Initialization and de-initialization functions
 *                        - Peripheral Control functions
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
 *      1.1          Vinay H         25-Jul-2017             -
 *      1.2          Shilpa A R      02-Sep-2017          100028
 *
 * Additional References : None
 *
 ******************************************************************************
 */

/* Includes */
#include "hdulibstm32f746xx.h"            /* CMSIS STM32F7xx Device Peripheral Access Layer file*/
#include "hdulibstm32f7xxhal.h"           /* Header files for HAL driver*/
#include "hdulibbasictypes.h"             /* Conatins the basic data types*/
#include "hdulibstm32f7xxhalcortex.h"     /* Header files for CORTEX HAL driver*/
#include "hdulibcorecm7.h"                /* CMSIS Cortex-M7 Core Peripheral Access Layer File*/
#include "hdulibstm32f7xxhalconf.h"       /* Header files for HAL Configuration driver*/
#include "hdulibstm32f7xx.h"              /* CMSIS STM32F7xx Device Peripheral Access Layer File*/
#include "hdulibcmsisgcc.h"               /* CMSIS Cortex-M Core Function/Instruction */
/*
 * Function                :  HALNvicSetPriorityGrouping
 *
 * Description             :  Sets the priority grouping field (preemption priority
 *                            and sub priority) using the required unlock sequence.
 *
 * Formal parameter(s)     :  T_UINT32 priority_group - OUT The priority grouping bits length.
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */
void HALNvicSetPriorityGrouping(T_UINT32 priority_group)
{
  /*hdulibstm32f7xxhalcortex-HALNvicSetPriorityGrouping-DB-LLR-001*/
  /* Set the PRIGROUP[10:8] bits according to the priority_group parameter value */
  NVICSetPriorityGrouping(priority_group);
}


/*
 * Function                :  HalNvicSetPriority
 *
 * Description             :  Sets the priority of an interrupt.
 *
 * Formal parameter(s)     :  T_IRQN_TYPE irq_n - IN External interrupt number.
 *                            T_UINT32 preempt_priority - IN The preemption priority
 *                            for the IRQn channel.
 *                            T_UINT32 sub_priority - IN the sub priority level for
 *                            the IRQ channel.
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */
void HalNvicSetPriority(T_IRQN_TYPE irq_n, T_UINT32 preempt_priority, T_UINT32 sub_priority)
{
  T_UINT32 priority_group = ZERO;

  /*hdulibstm32f7xxhalcortex-HalNvicSetPriority-DB-LLR-001*/
  priority_group = NVICGetPriorityGrouping();

  /*hdulibstm32f7xxhalcortex-HalNvicSetPriority-DB-LLR-002*/
  NVICSetPriority(irq_n, NVICEncodePriority(priority_group, preempt_priority, sub_priority));
}

/*
 * Function                :  HalNvicEnableIrq
 *
 * Description             :  Enables a device specific interrupt in the NVIC interrupt
 *                            controller.
 *
 * Formal parameter(s)     :  IRQn_Type irq_n - IN  External interrupt number.
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */
void HalNvicEnableIrq(T_IRQN_TYPE irq_n)
{
  /*hdulibstm32f7xxhalcortex-HalNvicEnableIrq-DB-LLR-001*/
  /* Enable interrupt */
   NVICEnableIRQ(irq_n);
}

/*
 * Function                :  HALSysTickConfig
 *
 * Description             :  Initializes the System Timer and its interrupt, and starts
 *                            the System Tick Timer.Counter is in free running mode to
 *                            generate periodic interrupts.
 *
 * Formal parameter(s)     :  T_UINT32 ticks_numb - IN Specifies the ticks Number of ticks between
 *                            two interrupts.
 *
 * Return Value            :  T_UINT32 - completion status
 *
 * Assumption              :  None
 *
 */
T_UINT32 HALSysTickConfig(T_UINT32 ticks_numb)
{
  /*hdulibstm32f7xxhalcortex-HALSysTickConfig-DB-LLR-001*/
   return SysTickConfig(ticks_numb);
}

/*
 * Function                :  HalMpuDisable
 *
 * Description             : Disable fault exceptions and clear the control register.
 *
 * Formal parameter(s)     :  None
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */

void HalMpuDisable(void)
{
  /*hdulibstm32f7xxhalcortex-HalMpuDisable-DB-LLR-001*/
  /* Make sure outstanding transfers are done */
  __DMB();

  /* Disable fault exceptions */
  SCB->SHCSR &= ~SCB_SHCSR_MEMFAULTENA_MSK;

  /*hdulibstm32f7xxhalcortex-HalMpuDisable-DB-LLR-002*/
  /* Disable the MPU and clear the control register*/
  MPU->CTRL = ZERO;
}

/*
 * Function                :  HalMpuEnable
 *
 * Description             :  Enable fault exceptions
 *
 * Formal parameter(s)     :  T_UINT32 mpu_control - IN Specifies the control
 *                            mode of the MPU during hard fault
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */
void HalMpuEnable(T_UINT32 mpu_control)
{
  /*hdulibstm32f7xxhalcortex-HalMpuEnable-DB-LLR-001*/
  /* Enable the MPU */
  MPU->CTRL = mpu_control | MPU_CTRL_ENABLE_MSK;

  /*hdulibstm32f7xxhalcortex-HalMpuEnable-DB-LLR-002*/
  /* Enable fault exceptions */
  SCB->SHCSR |= SCB_SHCSR_MEMFAULTENA_MSK;

  /* Ensure MPU setting take effects */
  __DSB();
  __ISB();
}

/*
 * Function                :  HalMpuConfigRegion
 *
 * Description             : Initializes and configures the Region and the memory to be protected.
 *
 * Formal parameter(s)     :  T_MPU_REGION_INIT * mpu_init- IN Pointer to a MPU_Region_InitTypeDef
 *                            structure that contains the initialization and
 *                            configuration information
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */
void HalMpuConfigRegion(T_MPU_REGION_INIT *mpu_init)
{

  /*hdulibstm32f7xxhalcortex-HalMpuConfigRegion-DB-LLR-001*/
  /* Set the Region number */
  MPU->RNR = mpu_init->Number;

  /*hdulibstm32f7xxhalcortex-HalMpuConfigRegion-DB-LLR-002*/
  if ((mpu_init->Enable) != RESET)
  {
    MPU->RBAR = mpu_init->BaseAddress;
    MPU->RASR = ((T_UINT32)mpu_init->DisableExec             << MPU_RASR_XN_POS)   |
                ((T_UINT32)mpu_init->AccessPermission        << MPU_RASR_AP_POS)   |
                ((T_UINT32)mpu_init->TypeExtField            << MPU_RASR_TEX_POS)  |
                ((T_UINT32)mpu_init->IsShareable             << MPU_RASR_S_POS)    |
                ((T_UINT32)mpu_init->IsCacheable             << MPU_RASR_C_POS)    |
                ((T_UINT32)mpu_init->IsBufferable            << MPU_RASR_B_POS)    |
                ((T_UINT32)mpu_init->SubRegionDisable        << MPU_RASR_SRD_POS)  |
                ((T_UINT32)mpu_init->Size                    << MPU_RASR_SIZE_POS) |
                ((T_UINT32)mpu_init->Enable                  << MPU_RASR_ENABLE_POS);
  }
  else
  {
    MPU->RBAR = ZERO;
    MPU->RASR = ZERO;
  }
}
