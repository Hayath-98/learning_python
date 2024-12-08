/*
 ******************************************************************************
 * License Information  :  Howell Instruments, Inc.                           *
 *                         "Licensed Software" and "All rights reserved".     *
 ******************************************************************************
 *  File                : hdulibstm32f7xxhal.h
 *
 *  Description         : This file contains all the functions prototypes for the HAL module driver.
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
 *      1.2          Divya G P       01-Sep-2017      100028
 *      1.3          Divya G P       08-Nov-2017      100164
 *      1.4          Rona B S        12-Sep-2020      100276
 *
 * Additional References : None
 *
 ******************************************************************************
 */

/* Define to prevent recursive inclusion */
#ifndef _HDULIBSTM32F7XXHAL_H_
#define _HDULIBSTM32F7XXHAL_H_

#include "hdulibbasictypes.h"        /* Define standard data types */
#include "hdulibstm32f7xxhaldma.h"   /* contains HAL common defines,enum,macro and structures */
#include "hdulibstm32f7xxhaldef.h"   /* contains HAL common defines,enum,macro and structures */
#include "hdulibcorecm7.h"           /* Cortex-M7 processor and core peripherals */
#include "hdulibstm32f7xxhalconf.h"  /* provides HAL configurations. */

/* SYSCFG_BootMode Boot Mode */

#define SYSCFG_MEM_BOOT_ADD0          ((T_UINT32)0x00000000U)
#define SYSCFG_MEM_BOOT_ADD1          SYSCFG_MEMRMP_MEM_BOOT

/* Freeze/Unfreeze Peripherals in Debug mode */
#define __HAL_DBGMCU_FREEZE_TIM2()           (DBGMCU->APB1FZ |= (DBGMCU_APB1_FZ_DBG_TIM2_STOP))
#define __HAL_DBGMCU_FREEZE_TIM3()           (DBGMCU->APB1FZ |= (DBGMCU_APB1_FZ_DBG_TIM3_STOP))
#define __HAL_DBGMCU_FREEZE_TIM4()           (DBGMCU->APB1FZ |= (DBGMCU_APB1_FZ_DBG_TIM4_STOP))
#define __HAL_DBGMCU_FREEZE_TIM5()           (DBGMCU->APB1FZ |= (DBGMCU_APB1_FZ_DBG_TIM5_STOP))
#define __HAL_DBGMCU_FREEZE_TIM6()           (DBGMCU->APB1FZ |= (DBGMCU_APB1_FZ_DBG_TIM6_STOP))
#define __HAL_DBGMCU_FREEZE_TIM7()           (DBGMCU->APB1FZ |= (DBGMCU_APB1_FZ_DBG_TIM7_STOP))
#define __HAL_DBGMCU_FREEZE_TIM12()          (DBGMCU->APB1FZ |= (DBGMCU_APB1_FZ_DBG_TIM12_STOP))
#define __HAL_DBGMCU_FREEZE_TIM13()          (DBGMCU->APB1FZ |= (DBGMCU_APB1_FZ_DBG_TIM13_STOP))
#define __HAL_DBGMCU_FREEZE_TIM14()          (DBGMCU->APB1FZ |= (DBGMCU_APB1_FZ_DBG_TIM14_STOP))
#define __HAL_DBGMCU_FREEZE_LPTIM1()         (DBGMCU->APB1FZ |= (DBGMCU_APB1_FZ_DBG_LPTIM1_STOP))
#define __HAL_DBGMCU_FREEZE_RTC()            (DBGMCU->APB1FZ |= (DBGMCU_APB1_FZ_DBG_RTC_STOP))
#define __HAL_DBGMCU_FREEZE_WWDG()           (DBGMCU->APB1FZ |= (DBGMCU_APB1_FZ_DBG_WWDG_STOP))
#define __HAL_DBGMCU_FREEZE_IWDG()           (DBGMCU->APB1FZ |= (DBGMCU_APB1_FZ_DBG_IWDG_STOP))
#define __HAL_DBGMCU_FREEZE_I2C1_TIMEOUT()   (DBGMCU->APB1FZ |= \
                                             (DBGMCU_APB1_FZ_I2C1_SMBUS_TMOUT))
#define __HAL_DBGMCU_FREEZE_I2C2_TIMEOUT()   (DBGMCU->APB1FZ |= \
                                             (DBGMCU_APB1_FZ_I2C2_SMBUS_TMOUT))
#define __HAL_DBGMCU_FREEZE_I2C3_TIMEOUT()   (DBGMCU->APB1FZ |= \
                                             (DBGMCU_APB1_FZ_I2C3_SMBUS_TMOUT))

#define __HAL_DBGMCU_FREEZE_CAN1()           (DBGMCU->APB1FZ |= (DBGMCU_APB1_FZ_DBG_CAN1_STOP))
#define __HAL_DBGMCU_FREEZE_CAN2()           (DBGMCU->APB1FZ |= (DBGMCU_APB1_FZ_DBG_CAN2_STOP))
#define __HAL_DBGMCU_FREEZE_TIM1()           (DBGMCU->APB2FZ |= (DBGMCU_APB2_FZ_DBG_TIM1_STOP))
#define __HAL_DBGMCU_FREEZE_TIM8()           (DBGMCU->APB2FZ |= (DBGMCU_APB2_FZ_DBG_TIM8_STOP))
#define __HAL_DBGMCU_FREEZE_TIM9()           (DBGMCU->APB2FZ |= (DBGMCU_APB2_FZ_DBG_TIM9_STOP))
#define __HAL_DBGMCU_FREEZE_TIM10()          (DBGMCU->APB2FZ |= (DBGMCU_APB2_FZ_DBG_TIM10_STOP))
#define __HAL_DBGMCU_FREEZE_TIM11()          (DBGMCU->APB2FZ |= (DBGMCU_APB2_FZ_DBG_TIM11_STOP))

#define __HAL_DBGMCU_UNFREEZE_TIM2()           (DBGMCU->APB1FZ &= ~(DBGMCU_APB1_FZ_DBG_TIM2_STOP))
#define __HAL_DBGMCU_UNFREEZE_TIM3()           (DBGMCU->APB1FZ &= ~(DBGMCU_APB1_FZ_DBG_TIM3_STOP))
#define __HAL_DBGMCU_UNFREEZE_TIM4()           (DBGMCU->APB1FZ &= ~(DBGMCU_APB1_FZ_DBG_TIM4_STOP))
#define __HAL_DBGMCU_UNFREEZE_TIM5()           (DBGMCU->APB1FZ &= ~(DBGMCU_APB1_FZ_DBG_TIM5_STOP))
#define __HAL_DBGMCU_UNFREEZE_TIM6()           (DBGMCU->APB1FZ &= ~(DBGMCU_APB1_FZ_DBG_TIM6_STOP))
#define __HAL_DBGMCU_UNFREEZE_TIM7()           (DBGMCU->APB1FZ &= ~(DBGMCU_APB1_FZ_DBG_TIM7_STOP))
#define __HAL_DBGMCU_UNFREEZE_TIM12()          (DBGMCU->APB1FZ &= ~(DBGMCU_APB1_FZ_DBG_TIM12_STOP))
#define __HAL_DBGMCU_UNFREEZE_TIM13()          (DBGMCU->APB1FZ &= ~(DBGMCU_APB1_FZ_DBG_TIM13_STOP))
#define __HAL_DBGMCU_UNFREEZE_TIM14()          (DBGMCU->APB1FZ &= ~(DBGMCU_APB1_FZ_DBG_TIM14_STOP))
#define __HAL_DBGMCU_UNFREEZE_LPTIM1()         (DBGMCU->APB1FZ &= ~(DBGMCU_APB1_FZ_DBG_LPTIM1_STOP))
#define __HAL_DBGMCU_UNFREEZE_RTC()            (DBGMCU->APB1FZ &= ~(DBGMCU_APB1_FZ_DBG_RTC_STOP))
#define __HAL_DBGMCU_UNFREEZE_WWDG()           (DBGMCU->APB1FZ &= ~(DBGMCU_APB1_FZ_DBG_WWDG_STOP))
#define __HAL_DBGMCU_UNFREEZE_IWDG()           (DBGMCU->APB1FZ &= ~(DBGMCU_APB1_FZ_DBG_IWDG_STOP))

/* Freeze/Unfreeze Peripherals in Debug mode for Time out (TMOUT) */

#define __HAL_DBGMCU_UNFREEZE_I2C1_TMOUT()   (DBGMCU->APB1FZ &= \
                                                ~(DBGMCU_APB1_FZ_I2C1_SMBUS_TMOUT))
#define __HAL_DBGMCU_UNFREEZE_I2C2_TMOUT()   (DBGMCU->APB1FZ &= \
                                                ~(DBGMCU_APB1_FZ_I2C2_SMBUS_TMOUT))
#define __HAL_DBGMCU_UNFREEZE_I2C3_TMOUT()   (DBGMCU->APB1FZ &= \
                                                ~(DBGMCU_APB1_FZ_I2C3_SMBUS_TMOUT))
#define __HAL_DBGMCU_UNFREEZE_I2C4_TMOUT()   (DBGMCU->APB1FZ &= \
                                                ~(DBGMCU_APB1_FZ_DBG_I2C4_SMBUS_TIMEOUT))
#define __HAL_DBGMCU_UNFREEZE_CAN1()           (DBGMCU->APB1FZ &= ~(DBGMCU_APB1_FZ_DBG_CAN1_STOP))
#define __HAL_DBGMCU_UNFREEZE_CAN2()           (DBGMCU->APB1FZ &= ~(DBGMCU_APB1_FZ_DBG_CAN2_STOP))
#define __HAL_DBGMCU_UNFREEZE_TIM1()           (DBGMCU->APB2FZ &= ~(DBGMCU_APB2_FZ_DBG_TIM1_STOP))
#define __HAL_DBGMCU_UNFREEZE_TIM8()           (DBGMCU->APB2FZ &= ~(DBGMCU_APB2_FZ_DBG_TIM8_STOP))
#define __HAL_DBGMCU_UNFREEZE_TIM9()           (DBGMCU->APB2FZ &= ~(DBGMCU_APB2_FZ_DBG_TIM9_STOP))
#define __HAL_DBGMCU_UNFREEZE_TIM10()          (DBGMCU->APB2FZ &= ~(DBGMCU_APB2_FZ_DBG_TIM10_STOP))
#define __HAL_DBGMCU_UNFREEZE_TIM11()          (DBGMCU->APB2FZ &= ~(DBGMCU_APB2_FZ_DBG_TIM11_STOP))

/* FMC (NOR/RAM) mapped at 0x60000000 and SDRAM mapped at 0xC0000000 */
#define __HAL_SYSCFG_REMAPMEMORY_FMC()          (SYSCFG->MEMRMP &= ~(SYSCFG_MEMRMP_SWP_FMC))

/* FMC/SDRAM  mapped at 0x60000000 (NOR/RAM) mapped at 0xC0000000 */
#define __HAL_SYSCFG_REMAPMEM_FMC_SDRAM() (do {SYSCFG->MEMRMP &= ~(SYSCFG_MEMRMP_SWP_FMC);\
                                          SYSCFG->MEMRMP |= (SYSCFG_MEMRMP_SWP_FMC_0);\
                                         }while(0);)

/* Return the memory boot mapping as configured by user. */
#define __HAL_SYSCFG_GET_BOOT_MODE()           (READ_BIT(SYSCFG->MEMRMP, SYSCFG_MEMRMP_MEM_BOOT))

/* Initialization and de-initialization functions */

extern T_HAL_STATUS HalInit(void);
extern T_HAL_STATUS HAL_DeInit(void);
extern void HAL_MspDeInit(void);
extern T_HAL_STATUS HALInitTick (T_UINT32 tick_priority);

/* Peripheral Control functions  */
extern void HalIncTick(void);
extern void HalDelay(__IO T_UINT32 Delay);
extern T_UINT32 HALGetTick(void);

#endif