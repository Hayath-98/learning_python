/*
 ******************************************************************************
 * License Information  :  Howell Instruments, Inc.                           *
 *                         "Licensed Software" and "All rights reserved".     *
 ******************************************************************************
 *  File                : hdulibstm32f7xxhalgpioex.h
 *
 *  Description         : Header file of GPIO HAL Extension module.
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
 *      1.3          Shilpa A R      02-Oct-2017            100064
 *
 * Additional References : None
 *
 ******************************************************************************
 */

/* Define to prevent recursive inclusion */
#ifndef _HDULIBSTM32F7XXHALGPIOEX_H_
#define _HDULIBSTM32F7XXHALGPIOEX_H_

/* Includes */
#include "hdulibstm32f7xxhaldef.h"     /* Header file of CORTEX HAL module */
#include "hdulibstm32f746xx.h"         /* CMSIS Cortex-M7 Device Peripheral Access Layer */
#include "hdulibstm32f7xxhalgpio.h"       /* Header file of HAL GPIO module */


#if defined (STM32F745xx) || defined (STM32F746xx) || defined (STM32F756xx) || \
   defined (STM32F765xx) || defined (STM32F767xx) ||\
   defined (STM32F769xx) || defined (STM32F777xx) || defined (STM32F779xx)

#define GPIO_AF0_RTC_50HZ      ((T_UINT8)0x00U)  /* RTC_50Hz Alternate Function mapping */
/* MCO (MCO1 and MCO2) Alternate Function mapping */
#define GPIO_AF0_MCO           ((T_UINT8)0x00U)
#define GPIO_AF0_SWJ           ((T_UINT8)0x00U)  /* SWJ (SWD and JTAG) Alternate Function mapping*/
#define GPIO_AF0_TRACE         ((T_UINT8)0x00U)  /* TRACE Alternate Function mapping */

#define GPIO_AF1_TIM1          ((T_UINT8)0x01U)  /* TIM1 Alternate Function mapping */
#define GPIO_AF1_TIM2          ((T_UINT8)0x01U)  /* TIM2 Alternate Function mapping */

#define GPIO_AF2_TIM3          ((T_UINT8)0x02U)  /* TIM3 Alternate Function mapping */
#define GPIO_AF2_TIM4          ((T_UINT8)0x02U)  /* TIM4 Alternate Function mapping */
#define GPIO_AF2_TIM5          ((T_UINT8)0x02U)  /* TIM5 Alternate Function mapping */

#define GPIO_AF3_TIM8          ((T_UINT8)0x03U)  /* TIM8 Alternate Function mapping */
#define GPIO_AF3_TIM9          ((T_UINT8)0x03U)  /* TIM9 Alternate Function mapping */
#define GPIO_AF3_TIM10         ((T_UINT8)0x03U)  /* TIM10 Alternate Function mapping */
#define GPIO_AF3_TIM11         ((T_UINT8)0x03U)  /* TIM11 Alternate Function mapping */
#define GPIO_AF3_LPTIM1        ((T_UINT8)0x03U)  /* LPTIM1 Alternate Function mapping */
#define GPIO_AF3_CEC           ((T_UINT8)0x03U)  /* CEC Alternate Function mapping */

#define GPIO_AF4_I2C1          ((T_UINT8)0x04U)  /* I2C1 Alternate Function mapping */
#define GPIO_AF4_I2C2          ((T_UINT8)0x04U)  /* I2C2 Alternate Function mapping */
#define GPIO_AF4_I2C3          ((T_UINT8)0x04U)  /* I2C3 Alternate Function mapping */
#define GPIO_AF4_I2C4          ((T_UINT8)0x04U)  /* I2C4 Alternate Function mapping */
#define GPIO_AF4_CEC           ((T_UINT8)0x04U)  /* CEC Alternate Function mapping */

#define GPIO_AF5_SPI1          ((T_UINT8)0x05U)  /* SPI1 Alternate Function mapping */
#define GPIO_AF5_SPI2          ((T_UINT8)0x05U)  /* SPI2/I2S2 Alternate Function mapping */
#define GPIO_AF5_SPI3          ((T_UINT8)0x05U)  /* SPI3/I2S3 Alternate Function mapping */
#define GPIO_AF5_SPI4          ((T_UINT8)0x05U)  /* SPI4 Alternate Function mapping */
#define GPIO_AF5_SPI5          ((T_UINT8)0x05U)  /* SPI5 Alternate Function mapping */
#define GPIO_AF5_SPI6          ((T_UINT8)0x05U)  /* SPI6 Alternate Function mapping */

#define GPIO_AF6_SPI3          ((T_UINT8)0x06U)  /* SPI3/I2S3 Alternate Function mapping  */
#define GPIO_AF6_SAI1          ((T_UINT8)0x06U)  /* SAI1 Alternate Function mapping       */

#define GPIO_AF7_USART1        ((T_UINT8)0x07U)  /* USART1 Alternate Function mapping     */
#define GPIO_AF7_USART2        ((T_UINT8)0x07U)  /* USART2 Alternate Function mapping     */
#define GPIO_AF7_USART3        ((T_UINT8)0x07U)  /* USART3 Alternate Function mapping     */
#define GPIO_AF7_UART5         ((T_UINT8)0x07U)  /* UART5 Alternate Function mapping      */
#define GPIO_AF7_SPDIFRX       ((T_UINT8)0x07U)  /* SPDIF-RX Alternate Function mapping   */
#define GPIO_AF7_SPI2          ((T_UINT8)0x07U)  /* SPI2 Alternate Function mapping       */
#define GPIO_AF7_SPI3          ((T_UINT8)0x07U)  /* SPI3 Alternate Function mapping       */

#define GPIO_AF8_UART4         ((T_UINT8)0x08U)  /* UART4 Alternate Function mapping  */
#define GPIO_AF8_UART5         ((T_UINT8)0x08U)  /* UART5 Alternate Function mapping  */
#define GPIO_AF8_USART6        ((T_UINT8)0x08U)  /* USART6 Alternate Function mapping */
#define GPIO_AF8_UART7         ((T_UINT8)0x08U)  /* UART7 Alternate Function mapping  */
#define GPIO_AF8_UART8         ((T_UINT8)0x08U)  /* UART8 Alternate Function mapping  */
#define GPIO_AF8_SPDIFRX       ((T_UINT8)0x08U)  /* SPIDIF-RX Alternate Function mapping */
#define GPIO_AF8_SAI2          ((T_UINT8)0x08U)  /* SAI2 Alternate Function mapping   */

#define GPIO_AF9_CAN1          ((T_UINT8)0x09U)  /* CAN1 Alternate Function mapping    */
#define GPIO_AF9_CAN2          ((T_UINT8)0x09U)  /* CAN2 Alternate Function mapping    */
#define GPIO_AF9_TIM12         ((T_UINT8)0x09U)  /* TIM12 Alternate Function mapping   */
#define GPIO_AF9_TIM13         ((T_UINT8)0x09U)  /* TIM13 Alternate Function mapping   */
#define GPIO_AF9_TIM14         ((T_UINT8)0x09U)  /* TIM14 Alternate Function mapping   */
#define GPIO_AF9_QUADSPI       ((T_UINT8)0x09U)  /* QUADSPI Alternate Function mapping */
#if defined(STM32F746xx) || defined(STM32F756xx) || defined(STM32F767xx) || defined(STM32F769xx) \
            || defined(STM32F777xx) || defined(STM32F779xx)
#define GPIO_AF9_LTDC          ((T_UINT8)0x09U)  /* LCD-TFT Alternate Function mapping */
#endif /* STM32F746xx || STM32F756xx || STM32F767xx || STM32F769xx || STM32F777xx || STM32F779xx */

#if defined(STM32F746xx) || defined(STM32F756xx) || defined(STM32F765xx) || defined(STM32F765xx) \
   || defined(STM32F767xx) || defined(STM32F769xx) || defined(STM32F777xx) || defined(STM32F779xx)

#define GPIO_AF9_FMC           ((T_UINT8)0x09U)   /* FMC Alternate Function mapping */
#endif /* STM32F746xx || STM32F756xx || STM32F767xx || STM32F769xx || STM32F777xx || STM32F779xx */

#define GPIO_AF10_OTG_FS        ((T_UINT8)0xAU)  /* OTG_FS Alternate Function mapping */
#define GPIO_AF10_OTG_HS        ((T_UINT8)0xAU)  /* OTG_HS Alternate Function mapping */
#define GPIO_AF10_QUADSPI       ((T_UINT8)0xAU)  /* QUADSPI Alternate Function mapping */
#define GPIO_AF10_SAI2          ((T_UINT8)0xAU)  /* SAI2 Alternate Function mapping */


#define GPIO_AF11_ETH           ((T_UINT8)0x0BU)  /* ETHERNET Alternate Function mapping */

#define GPIO_AF12_FMC           ((T_UINT8)0xCU)  /* FMC Alternate Function mapping */
/* OTG HS configured in FS, Alternate Function mapping */
#define GPIO_AF12_OTG_HS_FS     ((T_UINT8)0xCU)
#define GPIO_AF12_SDMMC1        ((T_UINT8)0xCU)  /* SDMMC1 Alternate Function mapping */


#define GPIO_AF13_DCMI          ((T_UINT8)0x0DU)  /* DCMI Alternate Function mapping */

#if defined(STM32F746xx) || defined(STM32F756xx) || defined(STM32F767xx) || defined(STM32F769xx) \
            || defined(STM32F777xx) || defined(STM32F779xx)
#define GPIO_AF13_LTDC          ((T_UINT8)0x0DU)  /* LTDC Alternate Function mapping */


#define GPIO_AF14_LTDC          ((T_UINT8)0x0EU)  /* LCD-TFT Alternate Function mapping */
#endif /* STM32F746xx || STM32F756xx || STM32F767xx || STM32F769xx || STM32F777xx || STM32F779xx */

#define GPIO_AF15_EVENTOUT      ((T_UINT8)0x0FU)  /* EVENTOUT Alternate Function mapping */

/*
 * STM32F745xx || STM32F746xx || STM32F756xx || STM32F765xx
 * || STM32F767xx || STM32F769xx || STM32F777xx || STM32F779xx
 */
#endif

#define GPIOA_PIN_AVAILABLE  GPIO_PIN_ALL
#define GPIOB_PIN_AVAILABLE  GPIO_PIN_ALL
#define GPIOC_PIN_AVAILABLE  GPIO_PIN_ALL
#define GPIOD_PIN_AVAILABLE  GPIO_PIN_ALL
#define GPIOE_PIN_AVAILABLE  GPIO_PIN_ALL
#define GPIOF_PIN_AVAILABLE  GPIO_PIN_ALL
#define GPIOG_PIN_AVAILABLE  GPIO_PIN_ALL
#define GPIOI_PIN_AVAILABLE  GPIO_PIN_ALL
#define GPIOJ_PIN_AVAILABLE  GPIO_PIN_ALL
#define GPIOH_PIN_AVAILABLE  GPIO_PIN_ALL
#define GPIOK_PIN_AVAILABLE  (GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_3 | GPIO_PIN_4 | \
                              GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7)

#if defined (STM32F745xx) || defined (STM32F746xx) || defined (STM32F756xx) || \
      defined (STM32F765xx) || defined (STM32F767xx) || defined (STM32F769xx) || \
      defined (STM32F777xx) || defined (STM32F779xx)
#define GPIO_GET_INDEX(__GPIOx__)   ((T_UINT8)(((__GPIOx__) == (GPIOA))? 0U :\
                                              ((__GPIOx__) == (GPIOB))? 1U :\
                                              ((__GPIOx__) == (GPIOC))? 2U :\
                                              ((__GPIOx__) == (GPIOD))? 3U :\
                                              ((__GPIOx__) == (GPIOE))? 4U :\
                                              ((__GPIOx__) == (GPIOF))? 5U :\
                                              ((__GPIOx__) == (GPIOG))? 6U :\
                                              ((__GPIOx__) == (GPIOH))? 7U :\
                                              ((__GPIOx__) == (GPIOI))? 8U :\
                                              ((__GPIOx__) == (GPIOJ))? 9U : 10U))

/*
 * STM32F745xx || STM32F746xx || STM32F756xx || STM32F765xx || STM32F767xx ||
 * STM32F769xx || STM32F777xx || STM32F779xx
 */
#endif

#define IS_GPIO_PIN_AVAILABLE(__INSTANCE__,__PIN__)  \
           ((((__INSTANCE__) == GPIOA) && (((__PIN__) & (GPIOA_PIN_AVAILABLE)) != 0) \
           && (((__PIN__) | (GPIOA_PIN_AVAILABLE)) == (GPIOA_PIN_AVAILABLE))) || \
           (((__INSTANCE__) == GPIOB) && (((__PIN__) & (GPIOB_PIN_AVAILABLE)) != 0) && \
           (((__PIN__) | (GPIOB_PIN_AVAILABLE)) == (GPIOB_PIN_AVAILABLE))) || \
           (((__INSTANCE__) == GPIOC) && (((__PIN__) & (GPIOC_PIN_AVAILABLE)) != 0) && \
           (((__PIN__) | (GPIOC_PIN_AVAILABLE)) == (GPIOC_PIN_AVAILABLE))) || \
           (((__INSTANCE__) == GPIOD) && (((__PIN__) & (GPIOD_PIN_AVAILABLE)) != 0) && \
           (((__PIN__) | (GPIOD_PIN_AVAILABLE)) == (GPIOD_PIN_AVAILABLE))) || \
           (((__INSTANCE__) == GPIOE) && (((__PIN__) & (GPIOE_PIN_AVAILABLE)) != 0) && \
           (((__PIN__) | (GPIOE_PIN_AVAILABLE)) == (GPIOE_PIN_AVAILABLE))) || \
           (((__INSTANCE__) == GPIOF) && (((__PIN__) & (GPIOF_PIN_AVAILABLE)) != 0) && \
           (((__PIN__) | (GPIOF_PIN_AVAILABLE)) == (GPIOF_PIN_AVAILABLE))) || \
           (((__INSTANCE__) == GPIOG) && (((__PIN__) & (GPIOG_PIN_AVAILABLE)) != 0) && \
           (((__PIN__) | (GPIOG_PIN_AVAILABLE)) == (GPIOG_PIN_AVAILABLE))) || \
           (((__INSTANCE__) == GPIOI) && (((__PIN__) & (GPIOI_PIN_AVAILABLE)) != 0) && \
           (((__PIN__) | (GPIOI_PIN_AVAILABLE)) == (GPIOI_PIN_AVAILABLE))) || \
           (((__INSTANCE__) == GPIOJ) && (((__PIN__) & (GPIOJ_PIN_AVAILABLE)) != 0) && \
           (((__PIN__) | (GPIOJ_PIN_AVAILABLE)) == (GPIOJ_PIN_AVAILABLE))) || \
           (((__INSTANCE__) == GPIOK) && (((__PIN__) & (GPIOK_PIN_AVAILABLE)) != 0) && \
           (((__PIN__) | (GPIOK_PIN_AVAILABLE)) == (GPIOK_PIN_AVAILABLE))) || \
           (((__INSTANCE__) == GPIOH) && (((__PIN__) & (GPIOH_PIN_AVAILABLE)) != 0) && \
           (((__PIN__) | (GPIOH_PIN_AVAILABLE)) == (GPIOH_PIN_AVAILABLE))))

#define IS_GPIO_AF(AF)   (((AF) == GPIO_AF0_RTC_50Hz)   || ((AF) == GPIO_AF1_TIM1)        || \
                          ((AF) == GPIO_AF0_SWJ)        || ((AF) == GPIO_AF0_TRACE)      || \
                          ((AF) == GPIO_AF0_MCO)       || ((AF) == GPIO_AF1_TIM2)       || \
                          ((AF) == GPIO_AF2_TIM3)       || ((AF) == GPIO_AF2_TIM4)       || \
                          ((AF) == GPIO_AF2_TIM5)       || ((AF) == GPIO_AF3_TIM8)       || \
                          ((AF) == GPIO_AF3_TIM9)       || ((AF) == GPIO_AF3_TIM10)      || \
                          ((AF) == GPIO_AF3_TIM11)      || ((AF) == GPIO_AF3_LPTIM1)     || \
                          ((AF) == GPIO_AF3_CEC)        || ((AF) == GPIO_AF4_CEC)        || \
                          ((AF) == GPIO_AF4_I2C1)       || ((AF) == GPIO_AF4_I2C2)       || \
                          ((AF) == GPIO_AF4_I2C3)       || ((AF) == GPIO_AF4_I2C4)       || \
                          ((AF) == GPIO_AF5_SPI1)       || ((AF) == GPIO_AF5_SPI2)       || \
                          ((AF) == GPIO_AF5_SPI3)       || ((AF) == GPIO_AF5_SPI4)       || \
                          ((AF) == GPIO_AF5_SPI5)       || ((AF) == GPIO_AF5_SPI6)       || \
                          ((AF) == GPIO_AF6_SPI3)       || ((AF) == GPIO_AF6_SAI1)       || \
                          ((AF) == GPIO_AF7_SPI3)       || ((AF) == GPIO_AF7_SPI2)        || \
                          ((AF) == GPIO_AF7_USART1)     || ((AF) == GPIO_AF7_USART2)      || \
                          ((AF) == GPIO_AF7_USART3)     || ((AF) == GPIO_AF7_UART5)       || \
                          ((AF) == GPIO_AF7_SPDIFRX)    || ((AF) == GPIO_AF8_SPDIFRX)     || \
                          ((AF) == GPIO_AF8_SAI2)       || ((AF) == GPIO_AF8_USART6)      || \
                          ((AF) == GPIO_AF8_UART4)      || ((AF) == GPIO_AF8_UART5)       || \
                          ((AF) == GPIO_AF8_UART7)      || ((AF) == GPIO_AF8_UART8)       || \
                          ((AF) == GPIO_AF9_CAN1)       || ((AF) == GPIO_AF9_CAN2)        || \
                          ((AF) == GPIO_AF9_TIM12)      || ((AF) == GPIO_AF9_TIM12)      || \
                          ((AF) == GPIO_AF9_TIM14)      || ((AF) == GPIO_AF9_QUADSPI)    || \
                          ((AF) == GPIO_AF9_LTDC)       || ((AF) == GPIO_AF10_OTG_FS)    || \
                          ((AF) == GPIO_AF10_OTG_HS)    || ((AF) == GPIO_AF10_SAI2)      || \
                          ((AF) == GPIO_AF10_QUADSPI)   || ((AF) == GPIO_AF11_ETH)       || \
                          ((AF) == GPIO_AF12_OTG_HS_FS) || ((AF) == GPIO_AF12_SDMMC1)     || \
                          ((AF) == GPIO_AF12_FMC)       || ((AF) == GPIO_AF15_EVENTOUT)  || \
                          ((AF) == GPIO_AF13_DCMI)      || ((AF) == GPIO_AF14_LTDC))

#endif /* __STM32F7xx_HAL_GPIO_EX_H */

