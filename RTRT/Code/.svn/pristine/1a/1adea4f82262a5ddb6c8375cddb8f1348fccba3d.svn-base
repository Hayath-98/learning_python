/*
 ******************************************************************************
 * License Information  :  Howell Instruments, Inc.                           *
 *                         "Licensed Software" and "All rights reserved".     *
 ******************************************************************************
 *  File                : hdulibstm32f7xxhalgpio.c
 *
 *  Description         : GPIO HAL module driver.
 *                        This file provides firmware functions to manage the following
 *                        functionalities of the General Purpose Input/Output (GPIO) peripheral:
 *                        -Initialization and de-initialization functions
 *                        -IO operation functions
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
 *      1.2          Shilpa A R      02-Sep-2017           100028
 *
 * Additional References : None
 *
 ******************************************************************************
 */

/* Includes */

#include "hdulibstm32f7xxhal.h"         /* Header files for HAL driver*/
#include "hdulibbasictypes.h"           /* Contains the basic data types */
#include "hdulibstm32f7xxhalgpio.h"     /* Header files for GPIO HAL driver*/
#include "hdulibstm32f7xxhalrcc.h"      /* Header files for RCC HAL driver*/
#include "hdulibstm32f746xx.h"         /* CMSIS Cortex-M7 Device Peripheral Access Layer */

#define GPIO_MODE             ((T_UINT32)0x00000003U)
#define EXTI_MODE             ((T_UINT32)0x10000000U)
#define GPIO_MODE_IT          ((T_UINT32)0x00010000U)
#define GPIO_MODE_EVT         ((T_UINT32)0x00020000U)
#define RISING_EDGE           ((T_UINT32)0x00100000U)
#define FALLING_EDGE          ((T_UINT32)0x00200000U)
#define GPIO_OUTPUT_TYPE      ((T_UINT32)0x00000010U)
#define GPIO_NUMBER           ((T_UINT32)16U)

/*
 * Function                :  HalGpioInit
 *
 * Description             :  This function initializes the GPIO peripheral.
 *
 * Formal parameter(s)     :  T_GPIO gpio_x - INOOUT where x can be (A..K) to select the
 *                            GPIO peripheral specified parameters in the gpio_init.
 *                            T_GPIO_INIT gpio_init - IN pointer to a GPIO_InitTypeDef structure
 *                            that contains the configuration information for the specified GPIO
 *                            peripheral.
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */

void HalGpioInit(T_GPIO  *gpio_x, T_GPIO_INIT *gpio_init)
{
  T_UINT32 position = 0x00;
  T_UINT32 io_position = 0x00;
  T_UINT32 io_current = 0x00;
  T_UINT32 temp = 0x00;

  /* Configure the port pins */
  for(position = ZERO; position < GPIO_NUMBER; position++)
  {
     /*hdulibstm32f7xxhalgpio-HalGpioInit-DB-LLR-002*/
    /* Get the IO position */
    io_position = ((T_UINT32)ONE) << position;

    /* Get the current IO position */
    io_current = (T_UINT32)(gpio_init->Pin) & io_position;

    if(io_current == io_position)
    {
      /* In case of Alternate function mode selection */
      if((GPIO_MODE_AF_PP == gpio_init->Mode) || (GPIO_MODE_AF_OD == gpio_init->Mode))
      {
        /*hdulibstm32f7xxhalgpio-HalGpioInit-DB-LLR-003*/
        /* Configure Alternate function mapped with the current IO */
        temp = gpio_x->AFR[position >> THREE];
        temp &= ~((T_UINT32)FIFTEEN << ((T_UINT32)(position & (T_UINT32)SEVEN) * FOUR)) ;
        temp |= ((T_UINT32)(gpio_init->Alternate) << (((T_UINT32)position &
                (T_UINT32)SEVEN) * FOUR));
        gpio_x->AFR[position >> THREE] = temp;
      }
      else
      {
       ;
      }

      /*hdulibstm32f7xxhalgpio-HalGpioInit-DB-LLR-004*/
      /* Configure IO Direction mode (Input, Output, Alternate or Analog) */
      temp = gpio_x->MODER;
      temp &= ~(GPIO_MODER_MODER0 << (position * TWO));
      temp |= ((gpio_init->Mode & GPIO_MODE) << (position * TWO));
      gpio_x->MODER = temp;

      /* In case of Output or Alternate function mode selection */
      if(( GPIO_MODE_OUTPUT_PP == gpio_init->Mode) || (GPIO_MODE_AF_PP == gpio_init->Mode) ||
         (GPIO_MODE_OUTPUT_OD == gpio_init->Mode) || (GPIO_MODE_AF_OD == gpio_init->Mode))
      {
        /*hdulibstm32f7xxhalgpio-HalGpioInit-DB-LLR-005*/
        /* Configure the IO Speed */
        temp = gpio_x->OSPEEDR;
        temp &= ~(GPIO_OSPEEDER_OSPEEDR0 << (position * TWO));
        temp |= (gpio_init->Speed << (position * TWO));
        gpio_x->OSPEEDR = temp;

        /* Configure the IO Output Type */
        temp = gpio_x->OTYPER;
        temp &= ~(GPIO_OTYPER_OT_0 << position) ;
        temp |= (((gpio_init->Mode & GPIO_OUTPUT_TYPE) >> FOUR) << position);
        gpio_x->OTYPER = temp;
      }
      else
      {
       ;
      }

      /*hdulibstm32f7xxhalgpio-HalGpioInit-DB-LLR-006*/
      /* Activate the Pull-up or Pull down resistor for the current IO */
      temp = gpio_x->PUPDR;
      temp &= ~(GPIO_PUPDR_PUPDR0 << (position * TWO));
      temp |= ((gpio_init->Pull) << (position * TWO));
      gpio_x->PUPDR = temp;

      /* Configure the External Interrupt or event for the current IO */
      if(EXTI_MODE == (gpio_init->Mode & EXTI_MODE))
      {
        /*hdulibstm32f7xxhalgpio-HalGpioInit-DB-LLR-007*/
        /* Enable SYSCFG Clock */
        __HAL_RCC_SYSCFG_CLK_ENABLE();

        temp = SYSCFG->EXTICR[position >> TWO];
        temp &= ~(((T_UINT32)0x0F) << (FOUR * (position & THREE)));
        temp |= ((T_UINT32)(GPIO_GET_INDEX(gpio_x)) << (FOUR * (position & THREE)));
        SYSCFG->EXTICR[position >> TWO] = temp;

        /* Clear EXTI line configuration */
        temp = EXTI->IMR;
        temp &= ~((T_UINT32)io_current);

        if(GPIO_MODE_IT == (gpio_init->Mode & GPIO_MODE_IT))
        {
          temp |= io_current;
        }
        else
        {
         ;
        }

        EXTI->IMR = temp;

        /*hdulibstm32f7xxhalgpio-HalGpioInit-DB-LLR-009*/
        temp = EXTI->EMR;
        temp &= ~((T_UINT32)io_current);

        if(GPIO_MODE_EVT == (gpio_init->Mode & GPIO_MODE_EVT))
        {
          temp |= io_current;
        }
        else
        {
         ;
        }

        EXTI->EMR = temp;

        /*hdulibstm32f7xxhalgpio-HalGpioInit-DB-LLR-010*/
        /* Clear Rising Falling edge configuration */
        temp = EXTI->RTSR;
        temp &= ~((T_UINT32)io_current);

        if(RISING_EDGE == (gpio_init->Mode & RISING_EDGE))
        {
          temp |= io_current;
        }
        else
        {
         ;
        }

        EXTI->RTSR = temp;

        /*hdulibstm32f7xxhalgpio-HalGpioInit-DB-LLR-011*/
        temp = EXTI->FTSR;
        temp &= ~((T_UINT32)io_current);

        if(FALLING_EDGE == (gpio_init->Mode & FALLING_EDGE))
        {
          temp |= io_current;
        }
        else
        {
         ;
        }

        EXTI->FTSR = temp;
      }
      else
      {
        ;
      }
    }
    else
    {
      ;
    }
  }
}

/*
 * Function                :  HalGpioReadPin
 *
 * Description             :  Reads the specified input port pin.
 *
 * Formal parameter(s)     :  T_GPIO gpio_x - IN where x can be (A..K) to select the
 *                             GPIO peripheral.
 *                            T_UINT16 gpio_pin - IN  specifies the port bit to be written.
 *                             This parameter can be one of GPIO_PIN_x where x can be (0..15).
 *
 * Return Value            :  T_GPIO_PIN_STATE - The input port pin value.
 *
 * Assumption              :  None
 *
 */

T_GPIO_PIN_STATE HalGpioReadPin(T_GPIO* gpio_x, T_UINT16 gpio_pin)
{
 T_GPIO_PIN_STATE bitstatus = GPIO_PIN_RESET;

 if((gpio_x->IDR & gpio_pin) != (T_UINT32)GPIO_PIN_RESET)
 {
   /*hdulibstm32f7xxhalgpio-HalGpioReadPin-DB-LLR-002*/
   bitstatus = GPIO_PIN_SET;
 }
 else
 {
   /*hdulibstm32f7xxhalgpio-HalGpioReadPin-DB-LLR-003*/
   bitstatus = GPIO_PIN_RESET;
 }
 return bitstatus;
}

/*
 * Function                :  HALGpioWritePin
 *
 * Description             :  Sets or clears the selected data port bit.
 *
 * Formal parameter(s)     :  T_GPIO gpio_x - OUT where x can be (A..K) to select the
 *                             GPIO peripheral.
 *                            T_UINT16 gpio_pin - IN specifies the port bit to be written.
 *                             This parameter can be one of GPIO_PIN_x where x can be (0..15).
 *                            T_GPIO_PIN_STATE pin_state - IN specifies the value to be written
 *                             to the selected bit.
 *                             This parameter can be one of the T_GPIO_PIN_STATE enum values:
 *                            GPIO_PIN_RESET: to clear the port pin
 *                            GPIO_PIN_SET: to set the port pin
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */

void HALGpioWritePin(T_GPIO* gpio_x, T_UINT16 gpio_pin, T_GPIO_PIN_STATE pin_state)
{
  if(pin_state != GPIO_PIN_RESET)
  {
    /*hdulibstm32f7xxhalgpio-HalGpioWritePin-DB-LLR-002*/
    gpio_x->BSRR = gpio_pin;
  }
  else
  {
     /*hdulibstm32f7xxhalgpio-HalGpioWritePin-DB-LLR-003*/
    gpio_x->BSRR = (T_UINT32)gpio_pin << SIXTEEN;
  }
}

/*
 * Function                :  HALGpioTogglePin
 *
 * Description             :  Toggles the specified GPIO pins.
 *
 * Formal parameter(s)     :  T_GPIO gpio_x - INOUT Where x can be (A..I) to select the
 *                             GPIO peripheral.
 *                            T_UINT16 gpio_pin -IN  Specifies the pins to be toggled.
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */

void HALGpioTogglePin(T_GPIO* gpio_x, T_UINT16 gpio_pin)
{
  /*hdulibstm32f7xxhalgpio-HalGpioTogglePin-DB-LLR-002*/
  gpio_x->ODR ^= gpio_pin;
}


