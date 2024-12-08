/*
 ******************************************************************************
 * License Information  :  Howell Instruments, Inc.                           *
 *                         "Licensed Software" and "All rights reserved".     *
 ******************************************************************************
 *  File                : hdulibstm32f7xxhalpwrex.h
 *
 *  Description         : Header file of PWR HAL Extension module.
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

/* Define to prevent recursive inclusion*/
#ifndef _HDULIBSTM32F7XXHALPWREX_H_
#define _HDULIBSTM32F7XXHALPWREX_H_

/* Includes */
#include "hdulibstm32f7xxhaldma.h"     /*Header files for DMA HAL driver  */
#include "hdulibstm32f7xxhaldef.h"     /* Header file of CORTEX HAL module */
#include "hdulibstm32f746xx.h"         /* Header files for HAL driver*/

#define PWR_WAKEUP_PIN1                PWR_CSR2_EWUP1
#define PWR_WAKEUP_PIN2                PWR_CSR2_EWUP2
#define PWR_WAKEUP_PIN3                PWR_CSR2_EWUP3
#define PWR_WAKEUP_PIN4                PWR_CSR2_EWUP4
#define PWR_WAKEUP_PIN5                PWR_CSR2_EWUP5
#define PWR_WAKEUP_PIN6                PWR_CSR2_EWUP6
#define PWR_WAKEUP_PIN1_HIGH           PWR_CSR2_EWUP1
#define PWR_WAKEUP_PIN2_HIGH           PWR_CSR2_EWUP2
#define PWR_WAKEUP_PIN3_HIGH           PWR_CSR2_EWUP3
#define PWR_WAKEUP_PIN4_HIGH           PWR_CSR2_EWUP4
#define PWR_WAKEUP_PIN5_HIGH           PWR_CSR2_EWUP5
#define PWR_WAKEUP_PIN6_HIGH           PWR_CSR2_EWUP6
#define PWR_WAKEUP_PIN1_LOW            (T_UINT32)((PWR_CR2_WUPP1<<6) | PWR_CSR2_EWUP1)
#define PWR_WAKEUP_PIN2_LOW            (T_UINT32)((PWR_CR2_WUPP2<<6) | PWR_CSR2_EWUP2)
#define PWR_WAKEUP_PIN3_LOW            (T_UINT32)((PWR_CR2_WUPP3<<6) | PWR_CSR2_EWUP3)
#define PWR_WAKEUP_PIN4_LOW            (T_UINT32)((PWR_CR2_WUPP4<<6) | PWR_CSR2_EWUP4)
#define PWR_WAKEUP_PIN5_LOW            (T_UINT32)((PWR_CR2_WUPP5<<6) | PWR_CSR2_EWUP5)
#define PWR_WAKEUP_PIN6_LOW            (T_UINT32)((PWR_CR2_WUPP6<<6) | PWR_CSR2_EWUP6)
#define PWR_MAINREGULATOR_UNDERDRIVE_ON                       PWR_CR1_MRUDS
/* LOWPOWERREGULATOR */
#define PWR_LOWPWRREGULATOR_UNDERDRIV_ON            ((T_UINT32)(PWR_CR1_LPDS | PWR_CR1_LPUDS))
#define PWR_FLAG_ODRDY                  PWR_CSR1_ODRDY
#define PWR_FLAG_ODSWRDY                PWR_CSR1_ODSWRDY
#define PWR_FLAG_UDRDY                  PWR_CSR1_UDRDY
#define PWR_WAKEUP_PIN_FLAG1            PWR_CSR2_WUPF1
#define PWR_WAKEUP_PIN_FLAG2            PWR_CSR2_WUPF2
#define PWR_WAKEUP_PIN_FLAG3            PWR_CSR2_WUPF3
#define PWR_WAKEUP_PIN_FLAG4            PWR_CSR2_WUPF4
#define PWR_WAKEUP_PIN_FLAG5            PWR_CSR2_WUPF5
#define PWR_WAKEUP_PIN_FLAG6            PWR_CSR2_WUPF6
#define __HAL_PWR_OVERDRIVE_ENABLE() (PWR->CR1 |= (T_UINT32)PWR_CR1_ODEN)
#define __HAL_PWR_OVERDRIVE_DISABLE() (PWR->CR1 &= (T_UINT32)(~PWR_CR1_ODEN))
#define __HAL_PWR_OVERDRIVESWITCH_ENABLE() (PWR->CR1 |= (T_UINT32)PWR_CR1_ODSWEN)
#define __HAL_PWR_OVERDRIVSWITCH_DISABLE() (PWR->CR1 &= (T_UINT32)(~PWR_CR1_ODSWEN))
#define __HAL_PWR_UNDERDRIVE_ENABLE() (PWR->CR1 |= (T_UINT32)PWR_CR1_UDEN)
#define __HAL_PWR_UNDERDRIVE_DISABLE() (PWR->CR1 &= (T_UINT32)(~PWR_CR1_UDEN))
#define __HAL_PWR_GET_ODRUDR_FLAG(__FLAG__) ((PWR->CSR1 & (__FLAG__)) == (__FLAG__))

#define __HAL_PWR_CLEAR_ODRUDR_FLAG() (PWR->CSR1 |= PWR_FLAG_UDRDY)
#define __HAL_PWR_GET_WAKEUP_FLAG(__WUFLAG__) (PWR->CSR2 & (__WUFLAG__))
#define __HAL_PWR_CLEAR_WAKEUP_FLAG(__WUFLAG__) (PWR->CR2 |=  (__WUFLAG__))

T_HAL_STATUS HalPwrExEnableOverDrive(void);

#define IS_PWR_REGULATOR_UNDERDRIVE(REGULATOR) (((REGULATOR)==PWR_MAINREGULATOR_UNDERDRIVE_ON) || \
                                              ((REGULATOR) == PWR_LOWPWRREGULATOR_UNDERDRIV_ON))
#define IS_PWR_WAKEUP_PIN(__PIN__)         (((__PIN__) == PWR_WAKEUP_PIN1)       || \
                                            ((__PIN__) == PWR_WAKEUP_PIN2)       || \
                                            ((__PIN__) == PWR_WAKEUP_PIN3)       || \
                                            ((__PIN__) == PWR_WAKEUP_PIN4)       || \
                                            ((__PIN__) == PWR_WAKEUP_PIN5)       || \
                                            ((__PIN__) == PWR_WAKEUP_PIN6)        || \
                                            ((__PIN__) == PWR_WAKEUP_PIN1_HIGH)  || \
                                            ((__PIN__) == PWR_WAKEUP_PIN2_HIGH)  || \
                                            ((__PIN__) == PWR_WAKEUP_PIN3_HIGH)  || \
                                            ((__PIN__) == PWR_WAKEUP_PIN4_HIGH)  || \
                                            ((__PIN__) == PWR_WAKEUP_PIN5_HIGH)  || \
                                            ((__PIN__) == PWR_WAKEUP_PIN6_HIGH)  || \
                                            ((__PIN__) == PWR_WAKEUP_PIN1_LOW)   || \
                                            ((__PIN__) == PWR_WAKEUP_PIN2_LOW)   || \
                                            ((__PIN__) == PWR_WAKEUP_PIN3_LOW)   || \
                                            ((__PIN__) == PWR_WAKEUP_PIN4_LOW)   || \
                                            ((__PIN__) == PWR_WAKEUP_PIN5_LOW)    || \
                                            ((__PIN__) == PWR_WAKEUP_PIN6_LOW))

#endif