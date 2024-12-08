/*
 ******************************************************************************
 * License Information  :  Howell Instruments, Inc.                           *
 *                         "Licensed Software" and "All rights reserved".     *
 ******************************************************************************
 *  File                : hdulibstm32f7xxhalpwr.h
 *
 *  Description         : Header file of PWR HAL module.
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
 *      1.2          Akshatha H      01-Sep-2017         100028
 *      1.3          Shilpa A R      02-Oct-2017         100064
 *
 * Additional References : None
 *
 ******************************************************************************
 */


/* Define to prevent recursive inclusion*/
#ifndef _HDULIBSTM32F7XXHALPWR_H_
#define _HDULIBSTM32F7XXHALPWR_H_

/* Includes */
#include "hdulibstm32f7xxhaldef.h"     /* Header file of CORTEX HAL module */
#include "hdulibstm32f7xxhalpwrex.h"   /* Header file of PWR HAL Extension module. */

typedef struct
{
   /*
    * PVDLevel: Specifies the PVD detection level.
    * This parameter can be a value of @ref PWR_PVD_detection_level
    */
   T_UINT32 PVDLevel;

   /*
    * Mode: Specifies the operating mode for the selected pins.
    * This parameter can be a value of @ref PWR_PVD_Mode
    */
   T_UINT32 Mode;
}T_PWR_PVD;


#define PWR_PVDLEVEL_0                  PWR_CR1_PLS_LEV0
#define PWR_PVDLEVEL_1                  PWR_CR1_PLS_LEV1
#define PWR_PVDLEVEL_2                  PWR_CR1_PLS_LEV2
#define PWR_PVDLEVEL_3                  PWR_CR1_PLS_LEV3
#define PWR_PVDLEVEL_4                  PWR_CR1_PLS_LEV4
#define PWR_PVDLEVEL_5                  PWR_CR1_PLS_LEV5
#define PWR_PVDLEVEL_6                  PWR_CR1_PLS_LEV6
/* External input analog voltage (Compare internally to VREFINT) */
#define PWR_PVDLEVEL_7                  PWR_CR1_PLS_LEV7

#define PWR_PVD_MODE_NORMAL                 ((T_UINT32)0x00000000U)   /* basic mode is used */
/* External Interrupt Mode with Rising edge trigger detection */
#define PWR_PVD_MODE_IT_RISING              ((T_UINT32)0x00010001U)
/* External Interrupt Mode with Falling edge trigger detection */
#define PWR_PVD_MODE_IT_FALLING             ((T_UINT32)0x00010002U)
/* External Interrupt Mode with Rising/Falling edge trigger detection */
#define PWR_PVD_MODE_IT_RISING_FALLING      ((T_UINT32)0x00010003U)
/* Event Mode with Rising edge trigger detection */
#define PWR_PVD_MODE_EVENT_RISING           ((T_UINT32)0x00020001U)
/* Event Mode with Falling edge trigger detection */
#define PWR_PVD_MODE_EVENT_FALLING          ((T_UINT32)0x00020002U)
/* Event Mode with Rising/Falling edge trigger detection */
#define PWR_PVD_MODE_EVENT_RISING_FALL   ((T_UINT32)0x00020003U)
#define PWR_MAINREGULATOR_ON                        ((T_UINT32)0x00000000U)
#define PWR_LOWPOWERREGULATOR_ON                    PWR_CR1_LPDS
#define PWR_SLEEPENTRY_WFI              ((T_UINT8)0x01U)
#define PWR_SLEEPENTRY_WFE              ((T_UINT8)0x02U)
#define PWR_STOPENTRY_WFI               ((T_UINT8)0x01U)
#define PWR_STOPENTRY_WFE               ((T_UINT8)0x02U)
#define PWR_REGULATOR_VOLTAGE_SCALE1         PWR_CR1_VOS
#define PWR_REGULATOR_VOLTAGE_SCALE2         PWR_CR1_VOS_1
#define PWR_REGULATOR_VOLTAGE_SCALE3         PWR_CR1_VOS_0
#define PWR_FLAG_WU                     PWR_CSR1_WUIF
#define PWR_FLAG_SB                     PWR_CSR1_SBF
#define PWR_FLAG_PVDO                   PWR_CSR1_PVDO
#define PWR_FLAG_BRR                    PWR_CSR1_BRR
#define PWR_FLAG_VOSRDY                 PWR_CSR1_VOSRDY

#define __HAL_PWR_VOLTAGESCALING_CONFIG(__REGULATOR__) do { \
                                             __IO T_UINT32 tmpreg; \
                                             MODIFY_REG(PWR->CR1, PWR_CR1_VOS, (__REGULATOR__)); \
                                             /* Delay after an RCC peripheral clock enabling */  \
                                             tmpreg = READ_BIT(PWR->CR1, PWR_CR1_VOS); \
                                             UNUSED(tmpreg); \
                                                } while(0)

#define __HAL_PWR_GET_FLAG(__FLAG__) ((PWR->CSR1 & (__FLAG__)) == (__FLAG__))

#define __HAL_PWR_CLEAR_FLAG(__FLAG__) (PWR->CR1 |=  (__FLAG__) << 2)

#define __HAL_PWR_PVD_EXTI_ENABLE_IT()   (EXTI->IMR |= (PWR_EXTI_LINE_PVD))

#define __HAL_PWR_PVD_EXTI_DISABLE_IT()  (EXTI->IMR &= ~(PWR_EXTI_LINE_PVD))

#define __HAL_PWR_PVD_EXTI_ENABLE_EVENT()   (EXTI->EMR |= (PWR_EXTI_LINE_PVD))

#define __HAL_PWR_PVD_EXTI_DISABLE_EVENT()  (EXTI->EMR &= ~(PWR_EXTI_LINE_PVD))

#define __HAL_PWR_PVD_EXTI_EN_RISING_EDG()   (SET_BIT(EXTI->RTSR, PWR_EXTI_LINE_PVD))

#define __HAL_PWR_PVD_EXI_DIS_RISE_EDG()  (CLEAR_BIT(EXTI->RTSR, PWR_EXTI_LINE_PVD))

#define __HAL_PWR_PVD_EXI_EN_FALLING_EDG()   (SET_BIT(EXTI->FTSR, PWR_EXTI_LINE_PVD))

#define __HAL_PWR_PVD_EXTI_DIS_FALL_EDG()  (CLEAR_BIT(EXTI->FTSR, PWR_EXTI_LINE_PVD))


#define __HAL_PWR_PVD_ENBLE_RSN_FLLG_EDG()   __HAL_PWR_PVD_EXTI_ENABLE_RISING_EDGE();\
                                             __HAL_PWR_PVD_EXTI_ENABLE_FALLING_EDGE();


#define __HAL_PWR_PVD_DSBLE_RSN_FLLG_EDG()  __HAL_PWR_PVD_EXTI_DISABLE_RISING_EDGE();\
                                            __HAL_PWR_PVD_EXTI_DISABLE_FALLING_EDGE();


#define __HAL_PWR_PVD_EXTI_GET_FLAG()  (EXTI->PR & (PWR_EXTI_LINE_PVD))

#define __HAL_PWR_PVD_EXTI_CLEAR_FLAG()  (EXTI->PR = (PWR_EXTI_LINE_PVD))

#define __HAL_PWR_PVD_EXTI_GENERATE_SWIT() (EXTI->SWIER |= (PWR_EXTI_LINE_PVD))

/* Initialization and de-initialization functions */
void HAL_PWR_DeInit(void);
void HAL_PWR_EnableBkUpAccess(void);
void HAL_PWR_DisableBkUpAccess(void);

/* PVD configuration */
void HAL_PWR_ConfigPVD(T_PWR_PVD *sConfigPVD);
void HAL_PWR_EnablePVD(void);
void HAL_PWR_DisablePVD(void);

/* WakeUp pins configuration */
void HAL_PWR_EnableWakeUpPin(T_UINT32 WakeUpPinPolarity);
void HAL_PWR_DisableWakeUpPin(T_UINT32 WakeUpPinx);

/* Low Power modes entry */
void HAL_PWR_EnterSTOPMode(T_UINT32 Regulator, T_UINT8 STOPEntry);
void HAL_PWR_EnterSLEEPMode(T_UINT32 Regulator, T_UINT8 SLEEPEntry);
void HAL_PWR_EnterSTANDBYMode(void);

/* Power PVD IRQ Handler */
void HAL_PWR_PVD_IRQHandler(void);
void HAL_PWR_PVDCallback(void);

/* Cortex System Control functions */
void HAL_PWR_EnableSleepOnExit(void);
void HAL_PWR_DisableSleepOnExit(void);
void HAL_PWR_EnableSEVOnPend(void);
void HAL_PWR_DisableSEVOnPend(void);

/* External interrupt line 16 Connected to the PVD EXTI Line */
#define PWR_EXTI_LINE_PVD  ((T_UINT32)EXTI_IMR_IM16)

#define IS_PWR_PVD_LEVEL(LEVEL) (((LEVEL) == PWR_PVDLEVEL_0) || ((LEVEL) == PWR_PVDLEVEL_1)|| \
                                 ((LEVEL) == PWR_PVDLEVEL_2) || ((LEVEL) == PWR_PVDLEVEL_3)|| \
                                 ((LEVEL) == PWR_PVDLEVEL_4) || ((LEVEL) == PWR_PVDLEVEL_5)|| \
                                 ((LEVEL) == PWR_PVDLEVEL_6) || ((LEVEL) == PWR_PVDLEVEL_7))
#define IS_PWR_PVD_MODE(MODE) (((MODE) == PWR_PVD_MODE_IT_RISING)|| \
                              ((MODE) == PWR_PVD_MODE_IT_FALLING) || \
                              ((MODE) == PWR_PVD_MODE_IT_RISING_FALLING) || \
                              ((MODE) == PWR_PVD_MODE_EVENT_RISING) || \
                              ((MODE) == PWR_PVD_MODE_EVENT_FALLING) || \
                              ((MODE) == PWR_PVD_MODE_EVENT_RISING_FALL) || \
                              ((MODE) == PWR_PVD_MODE_NORMAL))
#define IS_PWR_REGULATOR(REGULATOR) (((REGULATOR) == PWR_MAINREGULATOR_ON) || \
                                     ((REGULATOR) == PWR_LOWPOWERREGULATOR_ON))
#define IS_PWR_SLEEP_ENTRY(ENTRY) (((ENTRY) == PWR_SLEEPENTRY_WFI) ||\
                                 ((ENTRY) == PWR_SLEEPENTRY_WFE))
#define IS_PWR_STOP_ENTRY(ENTRY) (((ENTRY) == PWR_STOPENTRY_WFI) || ((ENTRY) == PWR_STOPENTRY_WFE))
#define IS_PWR_REGULATOR_VOLTAGE(VOLTAGE) (((VOLTAGE) == PWR_REGULATOR_VOLTAGE_SCALE1) || \
                                           ((VOLTAGE) == PWR_REGULATOR_VOLTAGE_SCALE2) || \
                                           ((VOLTAGE) == PWR_REGULATOR_VOLTAGE_SCALE3))
#endif
