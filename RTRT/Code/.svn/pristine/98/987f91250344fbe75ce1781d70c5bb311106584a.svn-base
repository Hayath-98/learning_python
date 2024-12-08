/*
 ******************************************************************************
 * License Information  :  Howell Instruments, Inc.                           *
 *                         "Licensed Software" and "All rights reserved".     *
 ******************************************************************************
 *  File                : hdulibstm32f7xxhalgpio.h
 *
 *  Description         : Header file of GPIO HAL module.
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
 *      1.2          Shilpa A R      02-Sep-2017           100028
 *
 * Additional References : None
 *
 ******************************************************************************
 */

/* Define to prevent recursive inclusion */
#ifndef _HDULIBSTM32F7XXHALGPIO_H_
#define _HDULIBSTM32F7XXHALGPIO_H_

/* Includes */
#include "hdulibstm32f746xx.h"         /* CMSIS Cortex-M7 Device Peripheral Access Layer */
#include "hdulibstm32f7xxhaldef.h"     /* Header file of CORTEX HAL module */
#include "hdulibstm32f7xxhalgpioex.h"  /* Header file of GPIO HAL Extension module.*/

typedef struct
{
   /*
    * Specifies the GPIO pins to be configured.
    * This parameter can be any value of @ref GPIO_pins_define
    */
   T_UINT32 Pin;

   /*
    * Specifies the operating mode for the selected pins.
    * This parameter can be a value of @ref GPIO_mode_define
    */
   T_UINT32 Mode;

   /*
    * Specifies the Pull-up or Pull-Down activation for the selected pins.
    * This parameter can be a value of @ref GPIO_pull_define
    */
   T_UINT32 Pull;

   /*
    * Specifies the speed for the selected pins.
    * This parameter can be a value of @ref GPIO_speed_define
    */
   T_UINT32 Speed;

   /*
    * Peripheral to be connected to the selected pins.
    * This parameter can be a value of @ref GPIO_Alternate_function_selection
    */
   T_UINT32 Alternate;
}T_GPIO_INIT;

typedef enum
{
   GPIO_PIN_RESET = 0,
   GPIO_PIN_SET
}T_GPIO_PIN_STATE;

#define GPIO_PIN_0                 ((T_UINT16)0x0001U)  /* Pin 0 selected */
#define GPIO_PIN_1                 ((T_UINT16)0x0002U)  /* Pin 1 selected */
#define GPIO_PIN_2                 ((T_UINT16)0x0004U)  /* Pin 2 selected */
#define GPIO_PIN_3                 ((T_UINT16)0x0008U)  /* Pin 3 selected */
#define GPIO_PIN_4                 ((T_UINT16)0x0010U)  /* Pin 4 selected */
#define GPIO_PIN_5                 ((T_UINT16)0x0020U)  /* Pin 5 selected */
#define GPIO_PIN_6                 ((T_UINT16)0x0040U)  /* Pin 6 selected */
#define GPIO_PIN_7                 ((T_UINT16)0x0080U)  /* Pin 7 selected */
#define GPIO_PIN_8                 ((T_UINT16)0x0100U)  /* Pin 8 selected */
#define GPIO_PIN_9                 ((T_UINT16)0x0200U)  /* Pin 9 selected */
#define GPIO_PIN_10                ((T_UINT16)0x0400U)  /* Pin 10 selected */
#define GPIO_PIN_11                ((T_UINT16)0x0800U)  /* Pin 11 selected */
#define GPIO_PIN_12                ((T_UINT16)0x1000U)  /* Pin 12 selected */
#define GPIO_PIN_13                ((T_UINT16)0x2000U)  /* Pin 13 selected */
#define GPIO_PIN_14                ((T_UINT16)0x4000U)  /* Pin 14 selected */
#define GPIO_PIN_15                ((T_UINT16)0x8000U)  /* Pin 15 selected */
#define GPIO_PIN_ALL               ((T_UINT16)0xFFFFU)  /* All pins selected */

#define GPIO_PIN_MASK              ((T_UINT32)0x0000FFFFU) /* PIN mask for assert test */

#define  GPIO_MODE_INPUT         ((T_UINT32)0x00000000U)   /* Input Floating Mode */
#define  GPIO_MODE_OUTPUT_PP     ((T_UINT32)0x00000001U)   /* Output Push Pull Mode */
#define  GPIO_MODE_OUTPUT_OD     ((T_UINT32)0x00000011U)   /* Output Open Drain Mode */
#define  GPIO_MODE_AF_PP         ((T_UINT32)0x00000002U)   /* Alternate Function Push Pull Mode */
#define  GPIO_MODE_AF_OD         ((T_UINT32)0x00000012U)   /* Alternate Function Open Drain Mode */

#define  GPIO_MODE_ANALOG        ((T_UINT32)0x00000003U)   /* Analog Mode */

/* External Interrupt Mode with Rising edge trigger detection */
#define  GPIO_MODE_IT_RISING         ((T_UINT32)0x10110000U)
/* External Interrupt Mode with Falling edge trigger detection */
#define  GPIO_MODE_IT_FALLING        ((T_UINT32)0x10210000U)
/* External Interrupt Mode with Rising/Falling edge trigger detection */
#define  GPIO_MODE_IT_RISING_FALLING ((T_UINT32)0x10310000U)

/* External Event Mode with Rising edge trigger detection */
#define  GPIO_MODE_EVT_RISING        ((T_UINT32)0x10120000U)
/* External Event Mode with Falling edge trigger detection */
#define  GPIO_MODE_EVT_FALLING       ((T_UINT32)0x10220000U)
/* External Event Mode with Rising/Falling edge trigger detection */
#define  GPIO_MODE_EVT_RISING_FALLING  ((T_UINT32)0x10320000U)

#define  GPIO_SPEED_FREQ_LOW         ((T_UINT32)0x00000000U)  /* Low speed */
#define  GPIO_SPEED_FREQ_MEDIUM      ((T_UINT32)0x00000001U)  /* Medium speed */
#define  GPIO_SPEED_FREQ_HIGH        ((T_UINT32)0x00000002U)  /* Fast speed */
#define  GPIO_SPEED_FREQ_VERY_HIGH   ((T_UINT32)0x00000003U)  /* High speed */

#define  GPIO_NOPULL        ((T_UINT32)0x00000000U)   /* No Pull-up or Pull-down activation */
#define  GPIO_PULLUP        ((T_UINT32)0x00000001U)   /* Pull-up activation */
#define  GPIO_PULLDOWN      ((T_UINT32)0x00000002U)   /* Pull-down activation */

#define __HAL_GPIO_EXTI_GET_FLAG(__EXTI_LINE__) (EXTI->PR & (__EXTI_LINE__))


#define __HAL_GPIO_EXTI_CLEAR_FLAG(__EXTI_LINE__) (EXTI->PR = (__EXTI_LINE__))


#define __HAL_GPIO_EXTI_GET_IT(__EXTI_LINE__) (EXTI->PR & (__EXTI_LINE__))


#define __HAL_GPIO_EXTI_CLEAR_IT(__EXTI_LINE__) (EXTI->PR = (__EXTI_LINE__))

#define __HAL_GPIO_EXTI_GENERATE_SWIT(__EXTI_LINE__) (EXTI->SWIER |= (__EXTI_LINE__))

void  HalGpioInit(T_GPIO  *GPIOx, T_GPIO_INIT *GPIO_Init);

T_GPIO_PIN_STATE HalGpioReadPin(T_GPIO* GPIOx, T_UINT16 GPIO_Pin);
void HALGpioWritePin(T_GPIO* GPIOx, T_UINT16 GPIO_Pin, T_GPIO_PIN_STATE PinState);
void HALGpioTogglePin(T_GPIO* GPIOx, T_UINT16 GPIO_Pin);

#define IS_GPIO_PIN_ACTION(ACTION) (((ACTION) == GPIO_PIN_RESET) || ((ACTION) == GPIO_PIN_SET))
#define IS_GPIO_PIN(__PIN__)        ((((__PIN__) & GPIO_PIN_MASK) != (T_UINT32)0x00))
#define IS_GPIO_MODE(MODE) (((MODE) == GPIO_MODE_INPUT)              ||\
                            ((MODE) == GPIO_MODE_OUTPUT_PP)          ||\
                            ((MODE) == GPIO_MODE_OUTPUT_OD)          ||\
                            ((MODE) == GPIO_MODE_AF_PP)              ||\
                            ((MODE) == GPIO_MODE_AF_OD)              ||\
                            ((MODE) == GPIO_MODE_IT_RISING)          ||\
                            ((MODE) == GPIO_MODE_IT_FALLING)         ||\
                            ((MODE) == GPIO_MODE_IT_RISING_FALLING)  ||\
                            ((MODE) == GPIO_MODE_EVT_RISING)         ||\
                            ((MODE) == GPIO_MODE_EVT_FALLING)        ||\
                            ((MODE) == GPIO_MODE_EVT_RISING_FALLING) ||\
                            ((MODE) == GPIO_MODE_ANALOG))
#define IS_GPIO_SPEED(SPEED) (((SPEED) == GPIO_SPEED_LOW)  || ((SPEED) == GPIO_SPEED_MEDIUM) || \
                              ((SPEED) == GPIO_SPEED_FAST) || ((SPEED) == GPIO_SPEED_HIGH))
#define IS_GPIO_PULL(PULL) (((PULL) == GPIO_NOPULL) || ((PULL) == GPIO_PULLUP) || \
                            ((PULL) == GPIO_PULLDOWN))

#endif