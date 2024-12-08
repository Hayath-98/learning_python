/*
 ******************************************************************************
 * License Information  :  Howell Instruments, Inc.                           *
 *                         "Licensed Software" and "All rights reserved".     *
 ******************************************************************************
 *  File                : hdulibstm32f7xxhaltim.c
 *
 *  Description         : TIM HAL module driver.
 *                        This file provides firmware functions to manage the
 *                        functionalities of the Timer (TIM) peripheral
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
 *      1.2          Rona.B.S        02-Sep-2017            100028
 *
 * Additional References : None
 *
 ******************************************************************************
 */

/* Includes*/
#include "hdulibstm32f7xxhal.h"     /* Header files for HAL driver*/
#include "hdulibbasictypes.h"       /* Contains the basic data types*/
#include "hdulibstm32f7xxhaltim.h"  /* Header file of TIM HAL module*/
#include "hdulibstm32f7xxhaldef.h"  /*Contains the HAL defination module */
#include "hdulibstm32f746xx.h"      /* CMSIS Cortex-M7 Device Peripheral Access Layer */
#include "hdulibstm32f7xxhaltimex.h"/* Header files for TIM EX HAL driver*/
#include "hdulibbasictypes.h"       /* Define standard types */

/*
 * Function                :  HalTimPwmInit
 *
 * Description             :  Initializes the TIM PWM Time Base according to the specified
 *                            parameters in the T_TIM_HANDLE and create the associated handle.
 *
 * Formal parameter(s)     :  T_TIM_HANDLE h_tim - INOUT pointer to a T_TIM_HANDLE structure
 *                            that contains the configuration information for TIM module.
 *
 * Return Value            :  HAL status
 *
 * Assumption              :  None
 *
 */

T_HAL_STATUS HalTimPwmInit(T_TIM_HANDLE *h_tim)
{
  /*hdulibstm32f7xxhaltim-HalTimPwmInit-DB-LLR-001*/
  /* Check the TIM handle allocation */
  if(NULL == h_tim)
  {
    return HAL_ERROR;
  }
  else
  {
   ;
  }

   /*hdulibstm32f7xxhaltim-HalTimPwmInit-DB-LLR-002*/
  if( HAL_TIM_STATE_RESET == h_tim->State)
  {
    /* Allocate lock resource and initialize it */
    h_tim->Lock = HAL_UNLOCKED;
    /* Init the low level hardware : GPIO, CLOCK, NVIC and DMA */
    HalTimPwmMspInit(h_tim);
  }
  else
  {
   ;
  }

  /*hdulibstm32f7xxhaltim-HalTimPwmInit-DB-LLR-003*/
  /* Set the TIM state */
  h_tim->State= HAL_TIM_STATE_BUSY;

  /* Init the base time for the PWM */
  TimBaseSetConfig(h_tim->Instance, &h_tim->Init);

  /* Initialize the TIM state*/
  h_tim->State= HAL_TIM_STATE_READY;

  return HAL_OK;
}

/*
 * Function                :  HalTimPwmMspInit
 *
 * Description             :  Initializes the TIM PWM MSP.
 *
 * Formal parameter(s)     :  T_TIM_HANDLE h_tim - IN pointer to a TIM_HANDLE structure
 *                            that contains the configuration information for TIM module.
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */

void HalTimPwmMspInit(T_TIM_HANDLE *h_tim)
{
   /*hdulibstm32f7xxhaltim-HalTimPwmMspInit-DB-LLR-001*/
  /* Prevent unused argument(s) compilation warning */
  UNUSED(h_tim);

}

/*
 * Function                :  HalTimPwmStart
 *
 * Description             :  Starts the PWM signal generation.
 *
 * Formal parameter(s)     :  T_TIM_HANDLE h_tim - IN pointer to a TIM_HANDLE structure
 *                            that contains the configuration information for TIM module.
 *                            T_UINT32 channel - IN TIM Channels to be enabled.
 *                            This parameter can be one of the following values:
 *                            TIM_CHANNEL_1 - TIM Channel 1 selected
 *                            TIM_CHANNEL_2 - TIM Channel 2 selected
 *                            TIM_CHANNEL_3 - TIM Channel 3 selected
 *                            TIM_CHANNEL_4 - TIM Channel 4 selected
 *
 * Return Value            :  HAL status
 *
 * Assumption              :  None
 *
 */

T_HAL_STATUS HalTimPwmStart(T_TIM_HANDLE *h_tim, T_UINT32 channel)
{
   /*hdulibstm32f7xxhaltim-HalTimPwmStart-DB-LLR-001*/
  /* Enable the Capture compare channel */
  TimCcxChannelCmd(h_tim->Instance, channel, TIM_CCX_ENABLE);

   /*hdulibstm32f7xxhaltim-HalTimPwmStart-DB-LLR-002*/
  if(IS_TIM_ADVANCED_INSTANCE(h_tim->Instance) != RESET)
  {
    /* Enable the main output */
    __HAL_TIM_MOE_ENABLE(h_tim);
  }
  else
  {
   ;
  }

   /*hdulibstm32f7xxhaltim-HalTimPwmStart-DB-LLR-003*/
  /* Enable the Peripheral */
  __HAL_TIM_ENABLE(h_tim);

   /*hdulibstm32f7xxhaltim-HalTimPwmStart-DB-LLR-004*/
  /* Return function status */
  return HAL_OK;
}

/*
 * Function                :  HalTimPwmConfigChannel
 *
 * Description             :  Initializes the TIM PWM  channels according to the specified
 *                            parameters in the T_TIM_OC_INIT.
 *
 * Formal parameter(s)     :  T_TIM_HANDLE h_tim - INOUT pointer to a T_TIM_HANDLE structure
 *                            that containsthe configuration information for TIM module.
 *                            T_TIM_OC_INIT s_config - IN Pointer to T_TIM_OC_INIT structure.
 *                            T_UINT32 channel - IN TIM Channels to be enabled.
 *                            This parameter can be one of the following values:
 *                            TIM_CHANNEL_1 - TIM Channel 1 selected
 *                            TIM_CHANNEL_2 - TIM Channel 2 selected
 *                            TIM_CHANNEL_3 - TIM Channel 3 selected
 *                            TIM_CHANNEL_4 - TIM Channel 4 selected
 *
 * Return Value            :  T_HAL_STATUS : HAL status
 *
 * Assumption              :  None
 *
 */

T_HAL_STATUS HalTimPwmConfigChannel(T_TIM_HANDLE *h_tim, T_TIM_OC_INIT* s_config,
                                           T_UINT32 channel)
{
   /*hdulibstm32f7xxhaltim-HalTimPwmConfigChannel-DB-LLR-001*/
  __HAL_LOCK(h_tim);

   /*hdulibstm32f7xxhaltim-HalTimPwmConfigChannel-DB-LLR-002*/
     h_tim->State = HAL_TIM_STATE_BUSY;

  switch (channel)
  {
   /*hdulibstm32f7xxhaltim-HalTimPwmConfigChannel-DB-LLR-003*/
    case TIM_CHANNEL_1:
    {
      /* Configure the Channel 1 in PWM mode */
      TimOc1SetConfig(h_tim->Instance, s_config);

      /* Set the Preload enable bit for channel1 */
      h_tim->Instance->CCMR1 |= TIM_CCMR1_OC1PE;

      /* Configure the Output Fast mode */
      h_tim->Instance->CCMR1 &= ~TIM_CCMR1_OC1FE;
      h_tim->Instance->CCMR1 |= s_config->OCFastMode;
    }
    break;

   /*hdulibstm32f7xxhaltim-HalTimPwmConfigChannel-DB-LLR-004*/
    case TIM_CHANNEL_2:
    {
      /* Configure the Channel 2 in PWM mode */
      TimOc2SetConfig(h_tim->Instance, s_config);

      /* Set the Preload enable bit for channel2 */
      h_tim->Instance->CCMR1 |= TIM_CCMR1_OC2PE;

      /* Configure the Output Fast mode */
      h_tim->Instance->CCMR1 &= ~TIM_CCMR1_OC2FE;
      h_tim->Instance->CCMR1 |= s_config->OCFastMode << EIGHT;
    }
    break;

   /*hdulibstm32f7xxhaltim-HalTimPwmConfigChannel-DB-LLR-005*/
    case TIM_CHANNEL_3:
    {
      /* Configure the Channel 3 in PWM mode */
      TimOc3SetConfig(h_tim->Instance, s_config);

      /* Set the Preload enable bit for channel3 */
      h_tim->Instance->CCMR2 |= TIM_CCMR2_OC3PE;

     /* Configure the Output Fast mode */
      h_tim->Instance->CCMR2 &= ~TIM_CCMR2_OC3FE;
      h_tim->Instance->CCMR2 |= s_config->OCFastMode;
    }
    break;

   /*hdulibstm32f7xxhaltim-HalTimPwmConfigChannel-DB-LLR-006*/
    case TIM_CHANNEL_4:
    {
      /* Configure the Channel 4 in PWM mode */
      TimOc4SetConfig(h_tim->Instance, s_config);

      /* Set the Preload enable bit for channel4 */
      h_tim->Instance->CCMR2 |= TIM_CCMR2_OC4PE;

     /* Configure the Output Fast mode */
      h_tim->Instance->CCMR2 &= ~TIM_CCMR2_OC4FE;
      h_tim->Instance->CCMR2 |= s_config->OCFastMode << EIGHT;
    }
    break;

   /*hdulibstm32f7xxhaltim-HalTimPwmConfigChannel-DB-LLR-007*/
    default:
    break;
  }

  /*hdulibstm32f7xxhaltim-HalTimPwmConfigChannel-DB-LLR-008*/
  h_tim->State = HAL_TIM_STATE_READY;

  /*hdulibstm32f7xxhaltim-HalTimPwmConfigChannel-DB-LLR-009*/
  __HAL_UNLOCK(h_tim);

  return HAL_OK;
}

/*
 * Function                :  TimBaseSetConfig
 *
 * Description             :  Time Base configuration
 *
 * Formal parameter(s)     :  T_TIM tim_x - INOUT select the TIM peripheral
 *                            T_TIM_BASE_INIT structure - IN pointer on TIM Time Base
 *                            required parameters
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */

void TimBaseSetConfig(T_TIM *tim_x, T_TIM_BASE_INIT *structure)
{
  T_UINT32 tmp_cr1 = ZERO;

  /*hdulibstm32f7xxhaltim-TimBaseSetConfig-DB-LLR-001*/
  tmp_cr1 = tim_x->CR1;

  /*hdulibstm32f7xxhaltim-TimBaseSetConfig-DB-LLR-002*/
  /* Set TIM Time Base Unit parameters */
  if(IS_TIM_CC3_INSTANCE(tim_x) != RESET)
  {
    /* Select the Counter Mode */
    tmp_cr1 &= ~(TIM_CR1_DIR | TIM_CR1_CMS);
    tmp_cr1 |= structure->CounterMode;
  }
  else
  {
   ;
  }
  /*hdulibstm32f7xxhaltim-TimBaseSetConfig-DB-LLR-003*/
  if(IS_TIM_CC1_INSTANCE(tim_x) != RESET)
  {
    /* Set the clock division */
    tmp_cr1 &= ~TIM_CR1_CKD;
    tmp_cr1 |= (T_UINT32)structure->ClockDivision;
  }
  else
  {
   ;
  }
  /*hdulibstm32f7xxhaltim-TimBaseSetConfig-DB-LLR-004*/
  tim_x->CR1 = tmp_cr1;

  /*hdulibstm32f7xxhaltim-TimBaseSetConfig-DB-LLR-005*/
  /* Set the Auto-reload value */
  tim_x->ARR = (T_UINT32)structure->Period ;

  /*hdulibstm32f7xxhaltim-TimBaseSetConfig-DB-LLR-006*/
  /* Set the Prescaler value */
  tim_x->PSC = (T_UINT32)structure->Prescaler;

  /*hdulibstm32f7xxhaltim-TimBaseSetConfig-DB-LLR-007*/
  if(IS_TIM_ADVANCED_INSTANCE(tim_x) != RESET)
  {
    /* Set the Repetition Counter value */
    tim_x->RCR = structure->RepetitionCounter;
  }
  else
  {
   ;
  }

  /*hdulibstm32f7xxhaltim-TimBaseSetConfig-DB-LLR-008*/
  /*
   * Generate an update event to reload the Prescaler
   *  and the repetition counter(only for TIM1 and TIM8) value immediately
   */
  tim_x->EGR = TIM_EGR_UG;
}

/*
 * Function                :  TimOc1SetConfig
 *
 * Description             :  Time Output Compare 1 configuration
 *
 * Formal parameter(s)     :  T_TIM *tim_x  - INOUT to select the TIM peripheral
 *                            T_TIM_OC_INIT oc_onfig - IN The output configuration structure
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */

void TimOc1SetConfig(T_TIM *tim_x, T_TIM_OC_INIT *oc_onfig)
{
  T_UINT32 tmp_cc_mrx = ZERO;
  T_UINT32 tmp_ccer = ZERO;
  T_UINT32 tmp_cr2 = ZERO;

  /*hdulibstm32f7xxhaltim-TimOc1SetConfig-DB-LLR-001*/
  /* Disable the Channel 1: Reset the CC1E Bit */
  tim_x->CCER &= ~TIM_CCER_CC1E;

  /*hdulibstm32f7xxhaltim-TimOc1SetConfig-DB-LLR-002*/
  /* Get the tim_x CCER register value */
  tmp_ccer = tim_x->CCER;

  /*hdulibstm32f7xxhaltim-TimOc1SetConfig-DB-LLR-003*/
  /* Get the tim_x CR2 register value */
  tmp_cr2 = tim_x->CR2;

  /*hdulibstm32f7xxhaltim-TimOc1SetConfig-DB-LLR-004*/
  /* Get the tim_x CCMR1 register value */
  tmp_cc_mrx = tim_x->CCMR1;

  /*hdulibstm32f7xxhaltim-TimOc1SetConfig-DB-LLR-005*/
  /* Reset the Output Compare Mode Bits */
  tmp_cc_mrx &= ~TIM_CCMR1_OC1M;
  tmp_cc_mrx &= ~TIM_CCMR1_CC1S;
  /* Select the Output Compare Mode */
  tmp_cc_mrx |= oc_onfig->OCMode;

  /*hdulibstm32f7xxhaltim-TimOc1SetConfig-DB-LLR-006*/
  /* Reset the Output Polarity level */
  tmp_ccer &= ~TIM_CCER_CC1P;
  /* Set the Output Compare Polarity */
  tmp_ccer |= oc_onfig->OCPolarity;

  /*hdulibstm32f7xxhaltim-TimOc1SetConfig-DB-LLR-007*/
  if(RESET != IS_TIM_ADVANCED_INSTANCE(tim_x))
  {
    /* Reset the Output N Polarity level */
    tmp_ccer &= ~TIM_CCER_CC1NP;
    /* Set the Output N Polarity */
    tmp_ccer |= oc_onfig->OCNPolarity;
    /* Reset the Output N State */
    tmp_ccer &= ~TIM_CCER_CC1NE;

    /* Reset the Output Compare and Output Compare N IDLE State */
    tmp_cr2 &= ~TIM_CR2_OIS1;
    tmp_cr2 &= ~TIM_CR2_OIS1N;
    /* Set the Output Idle state */
    tmp_cr2 |= oc_onfig->OCIdleState;
    /* Set the Output N Idle state */
    tmp_cr2 |= oc_onfig->OCNIdleState;
  }
  else
  {
   ;
  }
  /*hdulibstm32f7xxhaltim-TimOc1SetConfig-DB-LLR-008*/
  /* Write to tim_x CR2 */
  tim_x->CR2 = tmp_cr2;

  /*hdulibstm32f7xxhaltim-TimOc1SetConfig-DB-LLR-009*/
  /* Write to tim_x CCMR1 */
  tim_x->CCMR1 = tmp_cc_mrx;

  /*hdulibstm32f7xxhaltim-TimOc1SetConfig-DB-LLR-010*/
  /* Set the Capture Compare Register value */
  tim_x->CCR1 = oc_onfig->Pulse;

  /*hdulibstm32f7xxhaltim-TimOc1SetConfig-DB-LLR-011*/
  /* Write to tim_x CCER */
  tim_x->CCER = tmp_ccer;
}

/*
 * Function                :  TimOc2SetConfig
 *
 * Description             :  Time Output Compare 2 configuration
 *
 * Formal parameter(s)     :  T_TIM *tim_x - INOUT to select the TIM peripheral
 *                            T_TIM_OC_INIT oc_onfig - IN The output configuration structure
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */

void TimOc2SetConfig(T_TIM *tim_x, T_TIM_OC_INIT *oc_onfig)
{
  T_UINT32 tmp_cc_mrx = ZERO;
  T_UINT32 tmp_ccer = ZERO;
  T_UINT32 tmp_cr2 = ZERO;

  /*hdulibstm32f7xxhaltim-TimOc2SetConfig-DB-LLR-001*/
  /* Disable the Channel 2: Reset the CC2E Bit */
  tim_x->CCER &= ~TIM_CCER_CC2E;

  /*hdulibstm32f7xxhaltim-TimOc2SetConfig-DB-LLR-002*/
  /* Get the tim_x CCER register value */
  tmp_ccer = tim_x->CCER;

  /*hdulibstm32f7xxhaltim-TimOc2SetConfig-DB-LLR-003*/
  /* Get the tim_x CR2 register value */
  tmp_cr2 = tim_x->CR2;

  /*hdulibstm32f7xxhaltim-TimOc2SetConfig-DB-LLR-004*/
  /* Get the tim_x CCMR1 register value */
  tmp_cc_mrx = tim_x->CCMR1;

  /*hdulibstm32f7xxhaltim-TimOc2SetConfig-DB-LLR-005*/
  /* Reset the Output Compare mode and Capture/Compare selection Bits */
  tmp_cc_mrx &= ~TIM_CCMR1_OC2M;
  tmp_cc_mrx &= ~TIM_CCMR1_CC2S;

  /* Select the Output Compare Mode */
  tmp_cc_mrx |= (oc_onfig->OCMode << EIGHT);

  /*hdulibstm32f7xxhaltim-TimOc2SetConfig-DB-LLR-006*/
  /* Reset the Output Polarity level */
  tmp_ccer &= ~TIM_CCER_CC2P;
  /* Set the Output Compare Polarity */
  tmp_ccer |= (oc_onfig->OCPolarity << FOUR);

  /*hdulibstm32f7xxhaltim-TimOc2SetConfig-DB-LLR-007*/
  if(RESET != IS_TIM_ADVANCED_INSTANCE(tim_x))
  {
    /* Reset the Output N Polarity level */
    tmp_ccer &= ~TIM_CCER_CC2NP;
    /* Set the Output N Polarity */
    tmp_ccer |= (oc_onfig->OCNPolarity << FOUR);
    /* Reset the Output N State */
    tmp_ccer &= ~TIM_CCER_CC2NE;

    /* Reset the Output Compare and Output Compare N IDLE State */
    tmp_cr2 &= ~TIM_CR2_OIS2;
    tmp_cr2 &= ~TIM_CR2_OIS2N;
    /* Set the Output Idle state */
    tmp_cr2 |= (oc_onfig->OCIdleState << TWO);
    /* Set the Output N Idle state */
    tmp_cr2 |= (oc_onfig->OCNIdleState << TWO);
  }
  else
  {
   ;
  }
  /*hdulibstm32f7xxhaltim-TimOc2SetConfig-DB-LLR-008*/
  /* Write to tim_x CR2 */
  tim_x->CR2 = tmp_cr2;

  /*hdulibstm32f7xxhaltim-TimOc2SetConfig-DB-LLR-009*/
  /* Write to tim_x CCMR1 */
  tim_x->CCMR1 = tmp_cc_mrx;

  /*hdulibstm32f7xxhaltim-TimOc2SetConfig-DB-LLR-010*/
  /* Set the Capture Compare Register value */
  tim_x->CCR2 = oc_onfig->Pulse;

  /*hdulibstm32f7xxhaltim-TimOc2SetConfig-DB-LLR-011*/
  /* Write to tim_x CCER */
  tim_x->CCER = tmp_ccer;
}

/*
 * Function                :  TimOc3SetConfig
 *
 * Description             :  Time Output Compare 3 configuration
 *
 * Formal parameter(s)     :  T_TIM *tim_x - INOUT To select the TIM peripheral
 *                            T_TIM_OC_INIT oc_onfig - IN The output configuration structure
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */

void TimOc3SetConfig(T_TIM *tim_x, T_TIM_OC_INIT *oc_onfig)
{
  T_UINT32 tmp_cc_mrx = ZERO;
  T_UINT32 tmp_ccer = ZERO;
  T_UINT32 tmp_cr2 = ZERO;

  /*hdulibstm32f7xxhaltim-TimOc3SetConfig-DB-LLR-001*/
  /* Disable the Channel 3: Reset the CC3E Bit */
  tim_x->CCER &= ~TIM_CCER_CC3E;

  /*hdulibstm32f7xxhaltim-TimOc3SetConfig-DB-LLR-002*/
  /* Get the tim_x CCER register value */
  tmp_ccer = tim_x->CCER;

  /*hdulibstm32f7xxhaltim-TimOc3SetConfig-DB-LLR-003*/
  /* Get the tim_x CR2 register value */
  tmp_cr2 = tim_x->CR2;

  /*hdulibstm32f7xxhaltim-TimOc3SetConfig-DB-LLR-004*/
  /* Get the tim_x CCMR2 register value */
  tmp_cc_mrx = tim_x->CCMR2;

  /*hdulibstm32f7xxhaltim-TimOc3SetConfig-DB-LLR-005*/
  /* Reset the Output Compare mode and Capture/Compare selection Bits */
  tmp_cc_mrx &= ~TIM_CCMR2_OC3M;
  tmp_cc_mrx &= ~TIM_CCMR2_CC3S;
  /* Select the Output Compare Mode */
  tmp_cc_mrx |= oc_onfig->OCMode;

  /*hdulibstm32f7xxhaltim-TimOc3SetConfig-DB-LLR-006*/
  /* Reset the Output Polarity level */
  tmp_ccer &= ~TIM_CCER_CC3P;
  /* Set the Output Compare Polarity */
  tmp_ccer |= (oc_onfig->OCPolarity << EIGHT);

  /*hdulibstm32f7xxhaltim-TimOc3SetConfig-DB-LLR-007*/
  if(RESET != IS_TIM_ADVANCED_INSTANCE(tim_x))
  {
    /* Reset the Output N Polarity level */
    tmp_ccer &= ~TIM_CCER_CC3NP;
    /* Set the Output N Polarity */
    tmp_ccer |= (oc_onfig->OCNPolarity << EIGHT);
    /* Reset the Output N State */
    tmp_ccer &= ~TIM_CCER_CC3NE;

    /* Reset the Output Compare and Output Compare N IDLE State */
    tmp_cr2 &= ~TIM_CR2_OIS3;
    tmp_cr2 &= ~TIM_CR2_OIS3N;
    /* Set the Output Idle state */
    tmp_cr2 |= (oc_onfig->OCIdleState << FOUR);
    /* Set the Output N Idle state */
    tmp_cr2 |= (oc_onfig->OCNIdleState << FOUR);
  }
  else
  {
  ;
  }
  /*hdulibstm32f7xxhaltim-TimOc3SetConfig-DB-LLR-008*/
  /* Write to tim_x CR2 */
  tim_x->CR2 = tmp_cr2;

  /*hdulibstm32f7xxhaltim-TimOc3SetConfig-DB-LLR-009*/
  /* Write to tim_x CCMR2 */
  tim_x->CCMR2 = tmp_cc_mrx;

  /*hdulibstm32f7xxhaltim-TimOc3SetConfig-DB-LLR-010*/
  /* Set the Capture Compare Register value */
  tim_x->CCR3 = oc_onfig->Pulse;

  /*hdulibstm32f7xxhaltim-TimOc3SetConfig-DB-LLR-011*/
  /* Write to tim_x CCER */
  tim_x->CCER = tmp_ccer;
}

/*
 * Function                :  TimOc4SetConfig
 *
 * Description             :  Time Output Compare 4 configuration
 *
 * Formal parameter(s)     :  T_TIM *tim_x  -INOUT To select the TIM peripheral
 *                            T_TIM_OC_INIT oc_onfig - IN The output configuration structure
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */

void TimOc4SetConfig(T_TIM *tim_x, T_TIM_OC_INIT *oc_onfig)
{
  T_UINT32 tmp_cc_mrx = ZERO;
  T_UINT32 tmp_ccer = ZERO;
  T_UINT32 tmp_cr2 = ZERO;

  /*hdulibstm32f7xxhaltim-TimOc4SetConfig-DB-LLR-001*/
  /* Disable the Channel 4: Reset the CC4E Bit */
  tim_x->CCER &= ~TIM_CCER_CC4E;

  /*hdulibstm32f7xxhaltim-TimOc4SetConfig-DB-LLR-002*/
  /* Get the tim_x CCER register value */
  tmp_ccer = tim_x->CCER;

  /*hdulibstm32f7xxhaltim-TimOc4SetConfig-DB-LLR-003*/
  /* Get the tim_x CR2 register value */
  tmp_cr2 = tim_x->CR2;

  /*hdulibstm32f7xxhaltim-TimOc4SetConfig-DB-LLR-004*/
  /* Get the tim_x CCMR2 register value */
  tmp_cc_mrx = tim_x->CCMR2;

  /*hdulibstm32f7xxhaltim-TimOc4SetConfig-DB-LLR-005*/
  /* Reset the Output Compare mode and Capture/Compare selection Bits */
  tmp_cc_mrx &= ~TIM_CCMR2_OC4M;
  tmp_cc_mrx &= ~TIM_CCMR2_CC4S;

  /* Select the Output Compare Mode */
  tmp_cc_mrx |= (oc_onfig->OCMode << EIGHT);

  /*hdulibstm32f7xxhaltim-TimOc4SetConfig-DB-LLR-006*/
  /* Reset the Output Polarity level */
  tmp_ccer &= ~TIM_CCER_CC4P;
  /* Set the Output Compare Polarity */
  tmp_ccer |= (oc_onfig->OCPolarity << TWELVE);

  /*hdulibstm32f7xxhaltim-TimOc4SetConfig-DB-LLR-007*/
  /*if((tim_x == TIM1) || (tim_x == TIM8))*/
  if(RESET != IS_TIM_ADVANCED_INSTANCE(tim_x))
  {
    /* Reset the Output Compare IDLE State */
    tmp_cr2 &= ~TIM_CR2_OIS4;

    /* Set the Output Idle state */
    tmp_cr2 |= (oc_onfig->OCIdleState << SIX);
  }
  else
  {
   ;
  }

  /*hdulibstm32f7xxhaltim-TimOc4SetConfig-DB-LLR-008*/
  /* Write to tim_x CR2 */
  tim_x->CR2 = tmp_cr2;

  /*hdulibstm32f7xxhaltim-TimOc4SetConfig-DB-LLR-009*/
  /* Write to tim_x CCMR2 */
  tim_x->CCMR2 = tmp_cc_mrx;

  /*hdulibstm32f7xxhaltim-TimOc4SetConfig-DB-LLR-010*/
  /* Set the Capture Compare Register value */
  tim_x->CCR4 = oc_onfig->Pulse;

  /*hdulibstm32f7xxhaltim-TimOc4SetConfig-DB-LLR-011*/
  /* Write to tim_x CCER */
  tim_x->CCER = tmp_ccer;
}

/*
 * Function                :  TimCcxChannelCmd
 *
 * Description             :  Enables or disables the TIM Capture Compare Channel x.
 *
 * Formal parameter(s)     :  T_TIM *tim_x - INOUT To select the TIM peripheral.
 *                            This parameter can be one of the following values:
 *                            TIM_Channel_1 - TIM Channel 1
 *                            TIM_Channel_2 - TIM Channel 2
 *                            TIM_Channel_3 - TIM Channel 3
 *                            TIM_Channel_4 - TIM Channel 4
 *                            T_UINT32 channel - IN Specifies the TIM Channel CCxE bit new state
 *                            T_UINT32 channel_state - IN Specifies the TIM Channel CCxE bit
 *                            new state.This parameter can be TIM_CCX_ENABLE or TIM_CCx_Disable.
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */

void TimCcxChannelCmd(T_TIM* tim_x, T_UINT32 channel, T_UINT32 channel_state)
{
  T_UINT32 temp = ZERO;

  /*hdulibstm32f7xxhaltim-TimCcxChannelCmd-DB-LLR-001*/
  temp = TIM_CCER_CC1E << channel;

  /* Reset the CCxE Bit */
  tim_x->CCER &= ~temp;

  /*hdulibstm32f7xxhaltim-TimCcxChannelCmd-DB-LLR-002*/
  /* Set or reset the CCxE Bit */
  tim_x->CCER |= (T_UINT32)(channel_state << channel);
}


