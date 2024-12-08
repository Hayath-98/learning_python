/*
 ******************************************************************************
 * License Information  :  Howell Instruments, Inc.                           *
 *                         "Licensed Software" and "All rights reserved".     *
 ******************************************************************************
 *  File                : hdulibstm32f7xxhaladc.c
 *
 *  Description         : This file provides firmware functions to manage the following
 *                         functionalities of the Analog to Digital Convertor (ADC) peripheral:
 *                         - Initialization and de-initialization functions
 *                         - IO operation functions
 *                         - State and errors functions
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
 *  Author(s)           : Shilpa A R
 *
 *  Version History     :
 * <Version No.>     <Author>          <Date>         <Problem Report No.>
 *
 *      1.1          Shilpa A R       12-Sep-2017           100064
 *      1.2          Divya G P        09-Oct-2017           100064
 *
 * Additional References : None
 *
 ******************************************************************************
 */

/* Includes */
#include "hdulibcmsisgcc.h"/*CMSIS Cortex-M7 Core Function/Instruction Header File*/
#include "hdulibstm32f7xxhaladc.h" /* Defines ADC specification */
#include "hdulibstm32f7xxhalconf.h" /* contains HAL common defines,enum,macro and structures */
#include "hdulibbasictypes.h" /* Define standard data types */
#include "hdulibstm32f7xxhal.h" /* Header files for HAL driver*/
#include "hdulibsystemstm32f7xx.h"/* Cortex-M7 Device System Source File for STM32F7xx devices.*/
#include "hdulibstm32f7xx.h"  /* CMSIS STM32F7xx Device Peripheral Access Layer file*/
#include "hdulibstm32f7xxhaldef.h" /*Contains the HAL defination module */

#define VAL_1000K    1000000U

static void AdcInit(T_ADC_HANDLE* h_adc);

/*
 * Function                :  HalAdcInit
 *
 * Description             :  This function Initializes the ADCx peripheral according to the
 *                             specified parameters in the ADC_InitStruct and initializes
 *                             the ADC MSP.
 *
 * Formal parameter(s)     :  T_ADC_HANDLE* h_adc - IN pointer to a T_ADC_HANDLE structure that
 *                             contains the configuration information for the specified ADC
 *
 * Return Value            :  T_HAL_STATUS - HAL status
 *
 * Assumption              :  None
 *
 */

T_HAL_STATUS HalAdcInit(T_ADC_HANDLE* h_adc)
{
   T_HAL_STATUS tmp_hal_status = HAL_OK;

   /* Check ADC handle */
   /*hdulibstm32f7xxhaladc-HalAdcInit-DB-LLR-001*/
   if(NULL == h_adc )
   {
      return HAL_ERROR;
   }
   else
   {
      ;/* Does nothing */
   }
   /*hdulibstm32f7xxhaladc-HalAdcInit-DB-LLR-002*/
   if(HAL_ADC_STATE_RESET == h_adc->State)
   {
      /* Initialize ADC error code */
      ADC_CLEAR_ERRORCODE(h_adc);

      /* Allocate lock resource and initialize it */
      h_adc->Lock = HAL_UNLOCKED;
      /* Init the low level hardware */
      HalAdcMspInit(h_adc);
   }
   else
   {
      ;/* Does nothing */
   }

   /* Configuration of ADC parameters if previous preliminary actions are */
   /* correctly completed.                                                */
   if (ZERO != HAL_IS_BIT_CLR(h_adc->State, HAL_ADC_STATE_ERROR_INTERNAL))
   {
      /*hdulibstm32f7xxhaladc-HalAdcInit-DB-LLR-003*/
      /* Set ADC state */
      ADC_STATE_CLR_SET(h_adc->State,HAL_ADC_STATE_REG_BUSY | HAL_ADC_STATE_INJ_BUSY,
                   HAL_ADC_STATE_BUSY_INTERNAL);

      /* Set ADC parameters */
      AdcInit(h_adc);

      /* Set ADC error code to none */
      ADC_CLEAR_ERRORCODE(h_adc);

      /* Set the ADC state */
      ADC_STATE_CLR_SET(h_adc->State,HAL_ADC_STATE_BUSY_INTERNAL,HAL_ADC_STATE_READY);
   }
   else
   {
      /*hdulibstm32f7xxhaladc-HalAdcInit-DB-LLR-004*/
      tmp_hal_status = HAL_ERROR;
   }

   /*hdulibstm32f7xxhaladc-HalAdcInit-DB-LLR-005*/
   /* Release Lock */
   __HAL_UNLOCK(h_adc);

   /* Return function status */
   return tmp_hal_status;
}

/*
 * Function                :  HalAdcMspInit
 *
 * Description             :  This function Initializes the ADC MSP.
 *
 * Formal parameter(s)     :  T_ADC_HANDLE* h_adc - IN pointer to a T_ADC_HANDLE structure that
 *                             contains the configuration information for the specified ADC.
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */

void HalAdcMspInit(T_ADC_HANDLE* h_adc)
{
   /* Prevent unused argument(s) compilation warning */
   /*hdulibstm32f7xxhaladc-HalAdcMspInit-DB-LLR-001*/
   UNUSED(h_adc);
   /*
    * NOTE : This function Should not be modified, when the callback is needed,
    * the HalAdcMspInit could be implemented in the user file
    */
}

/*
 * Function                :  HalAdcStart
 *
 * Description             :  This function Enables ADC and starts conversion of the
 *                             regular channels.
 *
 * Formal parameter(s)     :  T_ADC_HANDLE* h_adc - IN pointer to a T_ADC_HANDLE structure that
 *                             contains the configuration information for the specified ADC.
 *
 * Return Value            :  T_HAL_STATUS - HAL status
 *
 * Assumption              :  None
 *
 */

T_HAL_STATUS HalAdcStart(T_ADC_HANDLE* h_adc)
{
   __IO T_UINT32 counter = ZERO;

   /*hdulibstm32f7xxhaladc-HalAdcStart-DB-LLR-001*/
   /* Process locked */
   __HAL_LOCK(h_adc);

   /* Enable the ADC peripheral */
   /*
    * Check if ADC peripheral is disabled in order to enable it and wait during
    * Tstab time the ADC's stabilization
    */
   /*hdulibstm32f7xxhaladc-HalAdcStart-DB-LLR-002*/
   if((h_adc->Instance->CR2 & ADC_CR2_ADON) != ADC_CR2_ADON)
   {
      /* Enable the Peripheral */
      __HAL_ADC_ENABLE(h_adc);

      /* Delay for ADC stabilization time */
      /* Compute number of CPU cycles to wait for */
      counter = (ADC_STAB_DELAY_US * (System_core_clock / VAL_1000K));
      while(ZERO != counter)
      {
         counter--;
      }
   }
   else
   {
      ;/* Does nothing */
   }

   /* Start conversion if ADC is effectively enabled */
   if(ZERO != HAL_IS_BIT_SET(h_adc->Instance->CR2, ADC_CR2_ADON))
   {
      /* Set ADC state                                                          */
      /* - Clear state bitfield related to regular group conversion results     */
      /* - Set state bitfield related to regular group operation                */
      /*hdulibstm32f7xxhaladc-HalAdcStart-DB-LLR-003*/
      ADC_STATE_CLR_SET(h_adc->State,
                      HAL_ADC_STATE_READY | HAL_ADC_STATE_REG_EOC | HAL_ADC_STATE_REG_OVR,
                      HAL_ADC_STATE_REG_BUSY);

      /* If conversions on group regular are also triggering group injected,    */
      /* update ADC state. */
      if (RESET != READ_BIT(h_adc->Instance->CR1, ADC_CR1_JAUTO))
      {
         /*hdulibstm32f7xxhaladc-HalAdcStart-DB-LLR-004*/
         ADC_STATE_CLR_SET(h_adc->State, HAL_ADC_STATE_INJ_EOC, HAL_ADC_STATE_INJ_BUSY);
      }
      else
      {
         ;/* Does nothing */
      }

      /* State machine update: Check if an injected conversion is ongoing */
      if (ZERO != HAL_IS_BIT_SET(h_adc->State, HAL_ADC_STATE_INJ_BUSY))
      {
         /*hdulibstm32f7xxhaladc-HalAdcStart-DB-LLR-005*/
         /* Reset ADC error code fields related to conversions on group regular */
         CLEAR_BIT(h_adc->ErrorCode, (HAL_ADC_ERROR_OVR | HAL_ADC_ERROR_DMA));
      }
      else
      {
         /*hdulibstm32f7xxhaladc-HalAdcStart-DB-LLR-006*/
         /* Reset ADC all error code fields */
         ADC_CLEAR_ERRORCODE(h_adc);
      }

      /* Process unlocked */
      /* Unlock before starting ADC conversions: in case of potential      */
      /* interruption, to let the process to ADC IRQ Handler.    */
      /*hdulibstm32f7xxhaladc-HalAdcStart-DB-LLR-007*/
      __HAL_UNLOCK(h_adc);

      /* Clear regular group conversion flag and overrun flag */
      /* (To ensure of no unknown state from potential previous ADC operations) */
      /*hdulibstm32f7xxhaladc-HalAdcStart-DB-LLR-008*/
      __HAL_ADC_CLEAR_FLAG(h_adc, ADC_FLAG_EOC | ADC_FLAG_OVR);

      /* Check if Multimode enabled */
      if(ZERO != HAL_IS_BIT_CLR(ADC->CCR, ADC_CCR_MULTI))
      {
         /* if no external trigger present enable software conversion of regular channels */
         if(RESET == (h_adc->Instance->CR2 & ADC_CR2_EXTEN))
         {
            /*hdulibstm32f7xxhaladc-HalAdcStart-DB-LLR-009*/
            /* Enable the selected ADC software conversion for regular group */
            h_adc->Instance->CR2 |= (T_UINT32)ADC_CR2_SWSTART;
         }
         else
         {
            ;/* Does nothing */
         }

      }
      else
      {
         /*
          * if instance of handle correspond to ADC1 and  no external trigger present enable
          * software conversion of regular channels
          */
         if((ADC1 == h_adc->Instance) && (RESET == (h_adc->Instance->CR2 & ADC_CR2_EXTEN)))
         {
            /*hdulibstm32f7xxhaladc-HalAdcStart-DB-LLR-010*/
            /* Enable the selected ADC software conversion for regular group */
            h_adc->Instance->CR2 |= (T_UINT32)ADC_CR2_SWSTART;
         }
         else
         {
            ;/* Does nothing */
         }

      }
   }

   /*hdulibstm32f7xxhaladc-HalAdcStart-DB-LLR-011*/
   /* Return function status */
   return HAL_OK;
}

/*
 * Function                :  HalAdcPollForConversion
 *
 * Description             :  This function Poll for regular conversion complete.
 *
 * Formal parameter(s)     :  T_ADC_HANDLE* h_adc - IN pointer to a T_ADC_HANDLE structure that
 *                             contains the configuration information for the specified ADC
 *                            T_UINT32 timeout - IN timeout value in millisecond.
 *
 * Return Value            :  T_HAL_STATUS - HAL status
 *
 * Assumption              :  None
 *
 */

T_HAL_STATUS HalAdcPollForConversion(T_ADC_HANDLE* h_adc, T_UINT32 timeout)
{
   T_UINT32 tickstart = ZERO;

   /* Verification that ADC configuration is compliant with polling for      */
   /* each conversion:                                                       */
   /* Particular case is ADC configured in DMA mode and ADC sequencer with   */
   /* several ranks and polling for end of each conversion.                  */
   /* For code simplicity sake, this particular case is generalized to       */
   /* ADC configured in DMA mode and polling for end of each conversion.     */
   if (ZERO != HAL_IS_BIT_SET(h_adc->Instance->CR2, ADC_CR2_EOCS) &&
      ZERO != HAL_IS_BIT_SET(h_adc->Instance->CR2, ADC_CR2_DMA))
   {
      /*hdulibstm32f7xxhaladc-HalAdcPollForConversion-DB-LLR-001*/
      /* Update ADC state machine to error */
      SET_BIT(h_adc->State, HAL_ADC_STATE_ERROR_CONFIG);

      /* Process unlocked */
      __HAL_UNLOCK(h_adc);

      return HAL_ERROR;
   }
   else
   {
     ; /* Does nothing */
   }

   /*hdulibstm32f7xxhaladc-HalAdcPollForConversion-DB-LLR-002*/
   /* Get tick */
   tickstart = HALGetTick();

   /* Check End of conversion flag */
   while(ZERO == (__HAL_ADC_GET_FLAG(h_adc, ADC_FLAG_EOC)))
   {
      /* Check if timeout is disabled (set to infinite wait) */
      if(timeout != HAL_MAX_DELAY)
      {
         if((ZERO == timeout ) || ((HALGetTick() - tickstart ) > timeout))
         {
            /*hdulibstm32f7xxhaladc-HalAdcPollForConversion-DB-LLR-003*/
            /* Update ADC state machine to timeout */
            SET_BIT(h_adc->State, HAL_ADC_STATE_TIMEOUT);

            /* Process unlocked */
            __HAL_UNLOCK(h_adc);

            return HAL_TIMEOUT;
         }
         else
         {
            ; /* Does nothing */
         }
      }
   }

   /*hdulibstm32f7xxhaladc-HalAdcPollForConversion-DB-LLR-004*/
   /* Clear regular group conversion flag */
   __HAL_ADC_CLEAR_FLAG(h_adc, ADC_FLAG_STRT | ADC_FLAG_EOC);

   /*hdulibstm32f7xxhaladc-HalAdcPollForConversion-DB-LLR-005*/
   /* Update ADC state machine */
   SET_BIT(h_adc->State, HAL_ADC_STATE_REG_EOC);

   /* Determine whether any further conversion upcoming on group regular       */
   /* by external trigger, continuous mode or scan sequence on going.          */
   if(ZERO != ADC_IS_SOFTWARE_START_REGULAR(h_adc)           &&
     (DISABLE == h_adc->Init.ContinuousConvMode)            &&
     (ZERO != HAL_IS_BIT_CLR(h_adc->Instance->SQR1, ADC_SQR1_L) ||
      ZERO != HAL_IS_BIT_CLR(h_adc->Instance->CR2, ADC_CR2_EOCS)))
   {
      /*hdulibstm32f7xxhaladc-HalAdcPollForConversion-DB-LLR-006*/
      /* Set ADC state */
      CLEAR_BIT(h_adc->State, HAL_ADC_STATE_REG_BUSY);

      if (ZERO != HAL_IS_BIT_CLR(h_adc->State, HAL_ADC_STATE_INJ_BUSY))
      {
         /*hdulibstm32f7xxhaladc-HalAdcPollForConversion-DB-LLR-007*/
         SET_BIT(h_adc->State, HAL_ADC_STATE_READY);
      }
      else
      {
         ; /* Does nothing */
      }
   }
   else
   {
     ; /* Does nothing */
   }

   /*hdulibstm32f7xxhaladc-HalAdcPollForConversion-DB-LLR-008*/
   /* Return ADC state */
   return HAL_OK;
}


/*
 * Function                : HalAdcGetValue
 *
 * Description             : The function configures for the selected ADC regular channel
 *                           its corresponding rank in the sequencer and its sample time.
 *
 * Formal parameter(s)     : T_ADC_HANDLE* h_adc -IN pointer to a T_ADC_HANDLE structure
 *                           that contains the configuration information for the specified ADC.
 *
 * Return Value            : T_UINT32 - Converted value
 *
 * Assumption              : None
 *
 */

T_UINT32 HalAdcGetValue(T_ADC_HANDLE* h_adc)
{
   /*hdulibstm32f7xxhaladc-HalAdcGetValue-DB-LLR-001*/
   /* Return the selected ADC converted value */
   return h_adc->Instance->DR;
}


/*
 * Function                : HalAdcConfigChannel
 *
 * Description             : The function configures for the selected ADC regular channel
 *                           its corresponding rank in the sequencer and its sample time.
 *
 * Formal parameter(s)     : T_ADC_HANDLE* h_adc -INOUT pointer to a T_ADC_HANDLE structure
 *                           that contains the configuration information for the specified ADC.
 *                           T_ADC_CHANNEL_CONF* s_config - IN ADC configuration structure.
 *
 * Return Value            : T_HAL_STATUS - HAL status
 *
 * Assumption              : None
 *
 */


T_HAL_STATUS HalAdcConfigChannel(T_ADC_HANDLE* h_adc, T_ADC_CHANNEL_CONF* s_config)
{
   T_UINT32 counter = ZERO;

   /*hdulibstm32f7xxhaladc-HalAdcConfigChannel-DB-LLR-001*/
   /* Process locked */
   __HAL_LOCK(h_adc);

   if (s_config->Channel > ADC_CHANNEL_9)
   {
      /*hdulibstm32f7xxhaladc-HalAdcConfigChannel-DB-LLR-002*/
      /* Clear the old sample time */
      h_adc->Instance->SMPR1 &= ~ADC_SMPR1(ADC_SMPR1_SMP10, s_config->Channel);

      if (ADC_CHANNEL_TEMPSENSOR == s_config->Channel)
      {
         /*hdulibstm32f7xxhaladc-HalAdcConfigChannel-DB-LLR-003*/
         /* Set the new sample time */
         h_adc->Instance->SMPR1 |= ADC_SMPR1(s_config->SamplingTime, ADC_CHANNEL_18);
      }
      else
      {
         /*hdulibstm32f7xxhaladc-HalAdcConfigChannel-DB-LLR-004*/
         /* Set the new sample time */
         h_adc->Instance->SMPR1 |= ADC_SMPR1(s_config->SamplingTime, s_config->Channel);
      }
   }
   else
   {
      /*hdulibstm32f7xxhaladc-HalAdcConfigChannel-DB-LLR-005*/
      /* Clear the old sample time */
      h_adc->Instance->SMPR2 &= ~ADC_SMPR2(ADC_SMPR2_SMP0, s_config->Channel);

      /* Set the new sample time */
      h_adc->Instance->SMPR2 |= ADC_SMPR2(s_config->SamplingTime, s_config->Channel);
   }


   if (s_config->Rank < SEVEN)
   {
      /*hdulibstm32f7xxhaladc-HalAdcConfigChannel-DB-LLR-006*/
      /* Clear the old SQx bits for the selected rank */
      h_adc->Instance->SQR3 &= ~ADC_SQR3_RK(ADC_SQR3_SQ1, s_config->Rank);

      /* Set the SQx bits for the selected rank */
      h_adc->Instance->SQR3 |= ADC_SQR3_RK(s_config->Channel, s_config->Rank);
   }
   else if (s_config->Rank < THIRTEEN)
   {
      /*hdulibstm32f7xxhaladc-HalAdcConfigChannel-DB-LLR-007*/
      /* Clear the old SQx bits for the selected rank */
      h_adc->Instance->SQR2 &= ~ADC_SQR2_RK(ADC_SQR2_SQ7, s_config->Rank);

      /* Set the SQx bits for the selected rank */
      h_adc->Instance->SQR2 |= ADC_SQR2_RK(s_config->Channel, s_config->Rank);
   }
   else
   {
      /*hdulibstm32f7xxhaladc-HalAdcConfigChannel-DB-LLR-008*/
      /* Clear the old SQx bits for the selected rank */
      h_adc->Instance->SQR1 &= ~ADC_SQR1_RK(ADC_SQR1_SQ13, s_config->Rank);

      /* Set the SQx bits for the selected rank */
      h_adc->Instance->SQR1 |= ADC_SQR1_RK(s_config->Channel, s_config->Rank);
   }

   /*hdulibstm32f7xxhaladc-HalAdcConfigChannel-DB-LLR-009*/
   /* if ADC1 Channel_18 is selected enable VBAT Channel */
   if ((ADC1 == h_adc->Instance) && (ADC_CHANNEL_VBAT == s_config->Channel))
   {
      /* Enable the VBAT channel*/
      ADC->CCR |= ADC_CCR_VBATE;
   }
   else
   {
      ;/*Do nothing*/
   }

   if ((ADC1 == h_adc->Instance) && ((ADC_CHANNEL_TEMPSENSOR == s_config->Channel) ||
      (ADC_CHANNEL_VREFINT == s_config->Channel)))
   {
      /*hdulibstm32f7xxhaladc-HalAdcConfigChannel-DB-LLR-010*/
      /* Enable the TSVREFE channel*/
      ADC->CCR |= ADC_CCR_TSVREFE;

      if(ADC_CHANNEL_TEMPSENSOR == s_config->Channel)
      {
      /* Delay for temperature sensor stabilization time */
         /* Compute number of CPU cycles to wait for */
         /*hdulibstm32f7xxhaladc-HalAdcConfigChannel-DB-LLR-011*/
         counter = (ADC_TEMPSENSOR_DELAY_US * (System_core_clock / VAL_1000K));

         while(ZERO != counter)
         {
         counter--;
         }
      }
      else
      {
         ;/*Do nothing*/
      }
   }
   else
   {
      ;/*Do nothing*/
   }

   /*hdulibstm32f7xxhaladc-HalAdcConfigChannel-DB-LLR-012*/
   /* Process unlocked */
   __HAL_UNLOCK(h_adc);

   /*hdulibstm32f7xxhaladc-HalAdcConfigChannel-DB-LLR-013*/
   /* Return function status */
   return HAL_OK;
}


/*
 * Function                : AdcInit
 *
 * Description             : The function configures for the selected ADC regular channel
 *                            its corresponding rank in the sequencer and its sample time.
 *
 * Formal parameter(s)     : T_ADC_HANDLE* h_adc -INOUT pointer to a T_ADC_HANDLE structure
 *                           that contains the configuration information for the specified ADC.
 *
 * Return Value            : T_HAL_STATUS - HAL status
 *
 * Assumption              : None
 *
 */

static void AdcInit(T_ADC_HANDLE* h_adc)
{
   /* Set ADC parameters */
   /* Set the ADC clock prescaler */
   /*hdulibstm32f7xxhaladc-AdcInit-DB-LLR-001*/
   ADC->CCR &= ~(ADC_CCR_ADCPRE);
   ADC->CCR |=  h_adc->Init.ClockPrescaler;

   /*hdulibstm32f7xxhaladc-AdcInit-DB-LLR-002*/
   /* Set ADC scan mode */
   h_adc->Instance->CR1 &= ~(ADC_CR1_SCAN);
   h_adc->Instance->CR1 |=  ADC_CR1_SCANCONV(h_adc->Init.ScanConvMode);

   /*hdulibstm32f7xxhaladc-AdcInit-DB-LLR-003*/
   /* Set ADC resolution */
   h_adc->Instance->CR1 &= ~(ADC_CR1_RES);
   h_adc->Instance->CR1 |=  h_adc->Init.Resolution;

   /*hdulibstm32f7xxhaladc-AdcInit-DB-LLR-004*/
   /* Set ADC data alignment */
   h_adc->Instance->CR2 &= ~(ADC_CR2_ALIGN);
   h_adc->Instance->CR2 |= h_adc->Init.DataAlign;

   /* Enable external trigger if trigger selection is different of software  */

   if(ADC_SOFTWARE_START != h_adc->Init.ExternalTrigConv)
   {
      /*hdulibstm32f7xxhaladc-AdcInit-DB-LLR-005*/
      /* Select external trigger to start conversion */
      h_adc->Instance->CR2 &= ~(ADC_CR2_EXTSEL);
      h_adc->Instance->CR2 |= h_adc->Init.ExternalTrigConv;

      /*hdulibstm32f7xxhaladc-AdcInit-DB-LLR-006*/
      /* Select external trigger polarity */
      h_adc->Instance->CR2 &= ~(ADC_CR2_EXTEN);
      h_adc->Instance->CR2 |= h_adc->Init.ExternalTrigConvEdge;
   }
   else
   {
      /*hdulibstm32f7xxhaladc-AdcInit-DB-LLR-007*/
      /* Reset the external trigger */
      h_adc->Instance->CR2 &= ~(ADC_CR2_EXTSEL);
      h_adc->Instance->CR2 &= ~(ADC_CR2_EXTEN);
   }

   /*hdulibstm32f7xxhaladc-AdcInit-DB-LLR-008*/
   /* Enable or disable ADC continuous conversion mode */
   h_adc->Instance->CR2 &= ~(ADC_CR2_CONT);
   h_adc->Instance->CR2 |= ADC_CR2_CONTINUOUS(h_adc->Init.ContinuousConvMode);

   if(h_adc->Init.DiscontinuousConvMode != DISABLE)
   {
      /*hdulibstm32f7xxhaladc-AdcInit-DB-LLR-009*/
      /* Enable the selected ADC regular discontinuous mode */
      h_adc->Instance->CR1 |= (T_UINT32)ADC_CR1_DISCEN;

      /* Set the number of channels to be converted in discontinuous mode */
      h_adc->Instance->CR1 &= ~(ADC_CR1_DISCNUM);
      h_adc->Instance->CR1 |=  ADC_CR1_DISCONTINUOUS(h_adc->Init.NbrOfDiscConversion);
   }
   else
   {
      /*hdulibstm32f7xxhaladc-AdcInit-DB-LLR-010*/
      /* Disable the selected ADC regular discontinuous mode */
      h_adc->Instance->CR1 &= ~(ADC_CR1_DISCEN);
   }

   /*hdulibstm32f7xxhaladc-AdcInit-DB-LLR-011*/
   /* Set ADC number of conversion */
   h_adc->Instance->SQR1 &= ~(ADC_SQR1_L);
   h_adc->Instance->SQR1 |=  ADC_SQR1(h_adc->Init.NbrOfConversion);

   /*hdulibstm32f7xxhaladc-AdcInit-DB-LLR-012*/
   /* Enable or disable ADC DMA continuous request */
   h_adc->Instance->CR2 &= ~(ADC_CR2_DDS);
   h_adc->Instance->CR2 |= ADC_CR2_DMACONTREQ(h_adc->Init.DMAContinuousRequests);

   /*hdulibstm32f7xxhaladc-AdcInit-DB-LLR-013*/
   /* Enable or disable ADC end of conversion selection */
   h_adc->Instance->CR2 &= ~(ADC_CR2_EOCS);
   h_adc->Instance->CR2 |= ADC_CR2_EOCSELECTION(h_adc->Init.EOCSelection);
}
