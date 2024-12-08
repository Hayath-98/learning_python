/*
 ******************************************************************************
 * License Information  :  Howell Instruments, Inc.                           *
 *                         "Licensed Software" and "All rights reserved".     *
 ******************************************************************************
 *  File                : hdulibstm32f7xxhalcortex.h
 *
 *  Description         : Header file of CORTEX HAL module.
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
 *      1.2          Shilpa A R      02-Aug-2017          100028
 *
 * Additional References : None
 *
 ******************************************************************************
 */

/* Define to prevent recursive inclusion */
#ifndef _HDULIBSTM32F7XXHALCORTEX_H_
#define _HDULIBSTM32F7XXHALCORTEX_H_

/* Includes */
#include "hdulibstm32f7xxhaldef.h"    /*Contains the HAL defination module */

#if (__MPU_PRESENT == 1)

typedef struct
{
   /*
    * Specifies the status of the region.
    * This parameter can be a value of @ref CORTEX_MPU_Region_Enable
    */
   T_UINT8   Enable;
   /*
    * Specifies the number of the region to protect.
    * This parameter can be a value of @ref CORTEX_MPU_Region_Number
    */
   T_UINT8   Number;
   T_UINT32  BaseAddress;           /* Specifies the base address of the region to protect.*/
   /*
    * Specifies the size of the region to protect.
    * This parameter can be a value of @ref CORTEX_MPU_Region_Size
    */
   T_UINT8   Size;
   /*
    * Specifies the number of the subregion protection to disable.
    * This parameter must be a number between Min_Data = 0x00 and Max_Data = 0xFF
    */
   T_UINT8   SubRegionDisable;

   /* Specifies the TEX field level.This parameter can be a value of @ref CORTEX_MPU_TEX_Levels */
   T_UINT8   TypeExtField;
   /*
    * Specifies the region access permission type.
    * This parameter can be a value of @ref CORTEX_MPU_Region_Permission_Attributes
    */
   T_UINT8   AccessPermission;
   /*
    * Specifies the instruction access status.
    * This parameter can be a value of @ref CORTEX_MPU_Instruction_Access
    */
   T_UINT8   DisableExec;
   /*
    * Specifies the shareability status of the protected region.
    * This parameter can be a value of @ref CORTEX_MPU_Access_Shareable
    */
   T_UINT8   IsShareable;
   /*
    * Specifies the cacheable status of the region protected.
    * This parameter can be a value of @ref CORTEX_MPU_Access_Cacheable
    */
   T_UINT8   IsCacheable;
   /*
    * Specifies the bufferable status of the protected region.
    * This parameter can be a value of @ref CORTEX_MPU_Access_Bufferable
    */
   T_UINT8   IsBufferable;
}T_MPU_REGION_INIT;

#endif /* __MPU_PRESENT */

/* 0 bits for pre-emption priority 4 bits for subpriority */
#define NVIC_PRIORITYGROUP_0         ((T_UINT32)0x00000007U)
/* 1 bits for pre-emption priority 3 bits for subpriority */
#define NVIC_PRIORITYGROUP_1         ((T_UINT32)0x00000006U)
/* 2 bits for pre-emption priority 2 bits for subpriority */
#define NVIC_PRIORITYGROUP_2         ((T_UINT32)0x00000005U)
/* 3 bits for pre-emption priority 1 bits for subpriority */
#define NVIC_PRIORITYGROUP_3         ((T_UINT32)0x00000004U)
/* 4 bits for pre-emption priority 0 bits for subpriority */
#define NVIC_PRIORITYGROUP_4         ((T_UINT32)0x00000003U)

#define SYSTICK_CLKSOURCE_HCLK_DIV8    ((T_UINT32)0x00000000U)
#define SYSTICK_CLKSOURCE_HCLK         ((T_UINT32)0x00000004U)

#if (__MPU_PRESENT == 1)
#define  MPU_HFNMI_PRIVDEF_NONE      ((T_UINT32)0x00000000U)
#define  MPU_HARDFAULT_NMI           ((T_UINT32)0x00000002U)
#define  MPU_PRIVILEGED_DEFAULT      ((T_UINT32)0x00000004U)
#define  MPU_HFNMI_PRIVDEF           ((T_UINT32)0x00000006U)

#define  MPU_REGION_ENABLE     ((T_UINT8)0x01U)
#define  MPU_REGION_DISABLE    ((T_UINT8)0x00U)

#define  MPU_INSTRUCTION_ACCESS_ENABLE      ((T_UINT8)0x00U)
#define  MPU_INSTRUCTION_ACCESS_DISABLE     ((T_UINT8)0x01U)

#define  MPU_ACCESS_SHAREABLE        ((T_UINT8)0x01U)
#define  MPU_ACCESS_NOT_SHAREABLE    ((T_UINT8)0x00U)

#define  MPU_ACCESS_CACHEABLE         ((T_UINT8)0x01U)
#define  MPU_ACCESS_NOT_CACHEABLE     ((T_UINT8)0x00U)

#define  MPU_ACCESS_BUFFERABLE         ((T_UINT8)0x01U)
#define  MPU_ACCESS_NOT_BUFFERABLE     ((T_UINT8)0x00U)

#define  MPU_TEX_LEVEL0    ((T_UINT8)0x00U)
#define  MPU_TEX_LEVEL1    ((T_UINT8)0x01U)
#define  MPU_TEX_LEVEL2    ((T_UINT8)0x02U)

#define   MPU_REGION_SIZE_32B      ((T_UINT8)0x04U)
#define   MPU_REGION_SIZE_64B      ((T_UINT8)0x05U)
#define   MPU_REGION_SIZE_128B     ((T_UINT8)0x06U)
#define   MPU_REGION_SIZE_256B     ((T_UINT8)0x07U)
#define   MPU_REGION_SIZE_512B     ((T_UINT8)0x08U)
#define   MPU_REGION_SIZE_1KB      ((T_UINT8)0x09U)
#define   MPU_REGION_SIZE_2KB      ((T_UINT8)0x0AU)
#define   MPU_REGION_SIZE_4KB      ((T_UINT8)0x0BU)
#define   MPU_REGION_SIZE_8KB      ((T_UINT8)0x0CU)
#define   MPU_REGION_SIZE_16KB     ((T_UINT8)0x0DU)
#define   MPU_REGION_SIZE_32KB     ((T_UINT8)0x0EU)
#define   MPU_REGION_SIZE_64KB     ((T_UINT8)0x0FU)
#define   MPU_REGION_SIZE_128KB    ((T_UINT8)0x10U)
#define   MPU_REGION_SIZE_256KB    ((T_UINT8)0x11U)
#define   MPU_REGION_SIZE_512KB    ((T_UINT8)0x12U)
#define   MPU_REGION_SIZE_1MB      ((T_UINT8)0x13U)
#define   MPU_REGION_SIZE_2MB      ((T_UINT8)0x14U)
#define   MPU_REGION_SIZE_4MB      ((T_UINT8)0x15U)
#define   MPU_REGION_SIZE_8MB      ((T_UINT8)0x16U)
#define   MPU_REGION_SIZE_16MB     ((T_UINT8)0x17U)
#define   MPU_REGION_SIZE_32MB     ((T_UINT8)0x18U)
#define   MPU_REGION_SIZE_64MB     ((T_UINT8)0x19U)
#define   MPU_REGION_SIZE_128MB    ((T_UINT8)0x1AU)
#define   MPU_REGION_SIZE_256MB    ((T_UINT8)0x1BU)
#define   MPU_REGION_SIZE_512MB    ((T_UINT8)0x1CU)
#define   MPU_REGION_SIZE_1GB      ((T_UINT8)0x1DU)
#define   MPU_REGION_SIZE_2GB      ((T_UINT8)0x1EU)
#define   MPU_REGION_SIZE_4GB      ((T_UINT8)0x1FU)

#define  MPU_REGION_NO_ACCESS      ((T_UINT8)0x00U)
#define  MPU_REGION_PRIV_RW        ((T_UINT8)0x01U)
#define  MPU_REGION_PRIV_RW_URO    ((T_UINT8)0x02U)
#define  MPU_REGION_FULL_ACCESS    ((T_UINT8)0x03U)
#define  MPU_REGION_PRIV_RO        ((T_UINT8)0x05U)
#define  MPU_REGION_PRIV_RO_URO    ((T_UINT8)0x06U)

#define  MPU_REGION_NUMBER0    ((T_UINT8)0x00U)
#define  MPU_REGION_NUMBER1    ((T_UINT8)0x01U)
#define  MPU_REGION_NUMBER2    ((T_UINT8)0x02U)
#define  MPU_REGION_NUMBER3    ((T_UINT8)0x03U)
#define  MPU_REGION_NUMBER4    ((T_UINT8)0x04U)
#define  MPU_REGION_NUMBER5    ((T_UINT8)0x05U)
#define  MPU_REGION_NUMBER6    ((T_UINT8)0x06U)
#define  MPU_REGION_NUMBER7    ((T_UINT8)0x07U)

#endif

/* Initialization and de-initialization functions*/
void HALNvicSetPriorityGrouping(T_UINT32 PriorityGroup);
void HalNvicSetPriority(T_IRQN_TYPE IRQn, T_UINT32 PreemptPriority, T_UINT32 SubPriority);
void HalNvicEnableIrq(T_IRQN_TYPE IRQn);
T_UINT32 HALSysTickConfig(T_UINT32 TicksNumb);

/* Peripheral Control functions */
#if (__MPU_PRESENT == 1)
void HalMpuEnable(T_UINT32 MPU_Control);
extern void HalMpuDisable(void);
void HalMpuConfigRegion(T_MPU_REGION_INIT *MPU_Init);
#endif /* __MPU_PRESENT */
void HAL_SYSTICK_IRQHandler(void);

#define IS_NVIC_PRIORITY_GROUP(GROUP) (((GROUP) == NVIC_PRIORITYGROUP_0) || \
                                       ((GROUP) == NVIC_PRIORITYGROUP_1) || \
                                       ((GROUP) == NVIC_PRIORITYGROUP_2) || \
                                       ((GROUP) == NVIC_PRIORITYGROUP_3) || \
                                       ((GROUP) == NVIC_PRIORITYGROUP_4))

#define IS_NVIC_PREEMPTION_PRIORITY(PRIORITY)  ((PRIORITY) < 0x10U)

#define IS_NVIC_SUB_PRIORITY(PRIORITY)         ((PRIORITY) < 0x10U)

#define IS_NVIC_DEVICE_IRQ(IRQ)                ((IRQ) >= 0x00)

#define IS_SYSTICK_CLK_SOURCE(SOURCE) (((SOURCE) == SYSTICK_CLKSOURCE_HCLK) || \
                                       ((SOURCE) == SYSTICK_CLKSOURCE_HCLK_DIV8))

#if (__MPU_PRESENT == 1)
#define IS_MPU_REGION_ENABLE(STATE) (((STATE) == MPU_REGION_ENABLE) || \
                                     ((STATE) == MPU_REGION_DISABLE))

#define IS_MPU_INSTRUCTION_ACCESS(STATE) (((STATE) == MPU_INSTRUCTION_ACCESS_ENABLE) || \
                                          ((STATE) == MPU_INSTRUCTION_ACCESS_DISABLE))

#define IS_MPU_ACCESS_SHAREABLE(STATE)   (((STATE) == MPU_ACCESS_SHAREABLE) || \
                                          ((STATE) == MPU_ACCESS_NOT_SHAREABLE))

#define IS_MPU_ACCESS_CACHEABLE(STATE)   (((STATE) == MPU_ACCESS_CACHEABLE) || \
                                          ((STATE) == MPU_ACCESS_NOT_CACHEABLE))

#define IS_MPU_ACCESS_BUFFERABLE(STATE)   (((STATE) == MPU_ACCESS_BUFFERABLE) || \
                                          ((STATE) == MPU_ACCESS_NOT_BUFFERABLE))

#define IS_MPU_TEX_LEVEL(TYPE) (((TYPE) == MPU_TEX_LEVEL0)  || \
                                ((TYPE) == MPU_TEX_LEVEL1)  || \
                                ((TYPE) == MPU_TEX_LEVEL2))

#define IS_MPU_REGION_PERMIT_ATTRIBUTE(TYPE) (((TYPE) == MPU_REGION_NO_ACCESS)   || \
                                                  ((TYPE) == MPU_REGION_PRIV_RW)     || \
                                                  ((TYPE) == MPU_REGION_PRIV_RW_URO) || \
                                                  ((TYPE) == MPU_REGION_FULL_ACCESS) || \
                                                  ((TYPE) == MPU_REGION_PRIV_RO)     || \
                                                  ((TYPE) == MPU_REGION_PRIV_RO_URO))

#define IS_MPU_REGION_NUMBER(NUMBER)    (((NUMBER) == MPU_REGION_NUMBER0) || \
                                         ((NUMBER) == MPU_REGION_NUMBER1) || \
                                         ((NUMBER) == MPU_REGION_NUMBER2) || \
                                         ((NUMBER) == MPU_REGION_NUMBER3) || \
                                         ((NUMBER) == MPU_REGION_NUMBER4) || \
                                         ((NUMBER) == MPU_REGION_NUMBER5) || \
                                         ((NUMBER) == MPU_REGION_NUMBER6) || \
                                         ((NUMBER) == MPU_REGION_NUMBER7))

#define IS_MPU_REGION_SIZE(SIZE)    (((SIZE) == MPU_REGION_SIZE_32B)   || \
                                     ((SIZE) == MPU_REGION_SIZE_64B)   || \
                                     ((SIZE) == MPU_REGION_SIZE_128B)  || \
                                     ((SIZE) == MPU_REGION_SIZE_256B)  || \
                                     ((SIZE) == MPU_REGION_SIZE_512B)  || \
                                     ((SIZE) == MPU_REGION_SIZE_1KB)   || \
                                     ((SIZE) == MPU_REGION_SIZE_2KB)   || \
                                     ((SIZE) == MPU_REGION_SIZE_4KB)   || \
                                     ((SIZE) == MPU_REGION_SIZE_8KB)   || \
                                     ((SIZE) == MPU_REGION_SIZE_16KB)  || \
                                     ((SIZE) == MPU_REGION_SIZE_32KB)  || \
                                     ((SIZE) == MPU_REGION_SIZE_64KB)  || \
                                     ((SIZE) == MPU_REGION_SIZE_128KB) || \
                                     ((SIZE) == MPU_REGION_SIZE_256KB) || \
                                     ((SIZE) == MPU_REGION_SIZE_512KB) || \
                                     ((SIZE) == MPU_REGION_SIZE_1MB)   || \
                                     ((SIZE) == MPU_REGION_SIZE_2MB)   || \
                                     ((SIZE) == MPU_REGION_SIZE_4MB)   || \
                                     ((SIZE) == MPU_REGION_SIZE_8MB)   || \
                                     ((SIZE) == MPU_REGION_SIZE_16MB)  || \
                                     ((SIZE) == MPU_REGION_SIZE_32MB)  || \
                                     ((SIZE) == MPU_REGION_SIZE_64MB)  || \
                                     ((SIZE) == MPU_REGION_SIZE_128MB) || \
                                     ((SIZE) == MPU_REGION_SIZE_256MB) || \
                                     ((SIZE) == MPU_REGION_SIZE_512MB) || \
                                     ((SIZE) == MPU_REGION_SIZE_1GB)   || \
                                     ((SIZE) == MPU_REGION_SIZE_2GB)   || \
                                     ((SIZE) == MPU_REGION_SIZE_4GB))

#define IS_MPU_SUB_REGION_DISABLE(SUBREGION)  ((SUBREGION) < (T_UINT16)0x00FFU)
#endif

#endif
