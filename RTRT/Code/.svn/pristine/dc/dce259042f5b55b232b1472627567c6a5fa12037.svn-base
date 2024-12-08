/*
 ******************************************************************************
 * License Information  :  Howell Instruments, Inc.                           *
 *                         "Licensed Software" and "All rights reserved".     *
 ******************************************************************************
 *  File                : hdudispfstmadc.c
 *
 *  Description         : This file initializes the internal ADC and polls for conversion
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
 *  Author(s)           : Rona B.S
 *
 *  Version History     :
 * <Version No.>     <Author>          <Date>         <Problem Report No.>
 *
 *      1.1          Rona B.S         13-Sep-2017             100064
 *      1.2          Divya G P        09-Oct-2017             100064
 *      1.3          Shruthi M N      30-Oct-2017             100104
 *      1.4          Divya G P        09-Nov-2017             100164
 *
 * Additional References : None
 *
 ******************************************************************************
 */

#include "hdudispfstmadc.h" /*declares the internal ADC and polls for conversion*/
#include "hdulibstm32f7xxhaladc.h"/* Defines ADC configurations */
#include "hdulibstm32f7xxhalrccex.h" /* Defines RCC configurations */
#include "hdulibstm32f7xxhalgpio.h" /* Defines GPIO configurations */
#include "hdulibstm32f7xxhal.h" /* Header files for HAL driver*/
#include "hdulibbasictypes.h" /* Define standard data types */
#include "hdulibstm32hallegacy.h"/*definition for the STM32Cube HAL constants*/
#include "hdulibstm32f7xx.h"/* CMSIS STM32F7xx Device Peripheral Access Layer file*/

/* Definition for ADCX clock resources */
#define ADCX                            ADC3
#define ADCX_CLK_ENABLE()              __HAL_RCC_ADC3_CLK_ENABLE()
#define ADCX_CHANNEL_GPIO_CLK_ENABLE()  __HAL_RCC_GPIOC_CLK_ENABLE()

/* Definition for ADCX Channel Pin */
#define ADCX_CHANNEL_PIN                (GPIO_PIN_0|GPIO_PIN_1)
#define ADCX_CHANNEL_GPIO_PORT          GPIOC

/*Static*/
static T_ADC_HANDLE  Adc_handle = {ZERO};
static T_ADC_CHANNEL_CONF S_config1 = {ZERO};
static T_ADC_CHANNEL_CONF S_config2 = {ZERO};

static void ErrorHandler(void);

/*Global*/
T_INT16  S16_adc_reading[NUM_CHAN] = {ZERO};


/*
 *
 * Function                : ErrorHandler
 *
 * Description             : This function Handles the error.
 *
 * Formal parameter(s)     : None
 *
 * Return Value            : None
 *
 * Assumption              : None
 *
 */

static void ErrorHandler(void)
{
  /*hdudispfstmadc-ErrorHandler-DB-LLR-001*/
   while(TRUE)
   {
      ; /*Do nothing*/
   }
}

/*
 *
 * Function                : StmadcInit
 *
 * Description             : This function initializes the internal ADC.
 *
 * Formal parameter(s)     : None
 *
 * Return Value            : None
 *
 * Assumption              : None
 *
 */

void StmadcInit(void)
{

   T_GPIO_INIT gpio_init_struct = {ZERO};

   /*hdudispfstmadc-StmadcInit-DB-LLR-001*/
   ADCX_CLK_ENABLE();

   /*hdudispfstmadc-StmadcInit-DB-LLR-002*/
   ADCX_CHANNEL_GPIO_CLK_ENABLE();

   /*hdudispfstmadc-StmadcInit-DB-LLR-003*/
   /*Configure the ADC peripheral*/
   Adc_handle.Instance          = ADCX;

   /*hdudispfstmadc-StmadcInit-DB-LLR-003*/
   Adc_handle.Init.ClockPrescaler        = ADC_CLOCKPRESCALER_PCLK_DIV4;
   Adc_handle.Init.Resolution            = ADC_RESOLUTION_12B;
   /* Sequencer disabled (ADC conversion on only 1 channel: channel set on rank 1) */
   Adc_handle.Init.ScanConvMode          = DISABLE;
   /* Continuous mode disabled to have only 1 conversion at each conversion trig */
   Adc_handle.Init.ContinuousConvMode    = DISABLE;
   /* Parameter discarded because sequencer is disabled */
   Adc_handle.Init.DiscontinuousConvMode = DISABLE;
   Adc_handle.Init.NbrOfDiscConversion   = HAL_OK;
   /* Conversion start trigged at each external event */
   Adc_handle.Init.ExternalTrigConvEdge  = ADC_EXTERNALTRIGCONVEDGE_NONE;
   Adc_handle.Init.ExternalTrigConv      = ADC_EXTERNALTRIGCONV_T1_CC1;
   Adc_handle.Init.DataAlign             = ADC_DATAALIGN_RIGHT;
   Adc_handle.Init.NbrOfConversion       = ONE;
   Adc_handle.Init.DMAContinuousRequests = DISABLE;
   Adc_handle.Init.EOCSelection          = DISABLE;

   /*hdudispfstmadc-StmadcInit-DB-LLR-004*/
   if (HAL_OK != HalAdcInit(&Adc_handle))
   {
      /* ADC initialization Error */
      ErrorHandler();
   }
   else
   {
      ;/*Do nothing*/
   }

   /*hdudispfstmadc-StmadcInit-DB-LLR-005*/
   /*Configure peripheral GPIO*/

   /* ADC Channel GPIO pin configuration */
   gpio_init_struct.Pin  = ADCX_CHANNEL_PIN;
   gpio_init_struct.Mode = GPIO_MODE_ANALOG;
   gpio_init_struct.Pull = GPIO_NOPULL;
   HalGpioInit(ADCX_CHANNEL_GPIO_PORT, &gpio_init_struct);

   /*hdudispfstmadc-StmadcInit-DB-LLR-006*/
   /*Configure ADC regular channel */
   S_config1.Channel      = ADC_CHANNEL_10;
   S_config1.Rank         = ONE;
   S_config1.SamplingTime = ADC_SAMPLETIME_3CYCLES;
   S_config1.Offset       = ZERO;

   /*hdudispfstmadc-StmadcInit-DB-LLR-007*/
   /*Configure ADC regular channel */
   S_config2.Channel      = ADC_CHANNEL_11;
   S_config2.Rank         = ONE;
   S_config2.SamplingTime = ADC_SAMPLETIME_3CYCLES;
   S_config2.Offset       = ZERO;

   /*hdudispfstmadc-StmadcInit-DB-LLR-008*/
   if (HAL_OK != HalAdcConfigChannel(&Adc_handle, &S_config1))
   {
      /* Channel Configuration Error */
      ErrorHandler();
   }
   else
   {
      ;/*Do nothing*/
   }

   /*hdudispfstmadc-StmadcInit-DB-LLR-009*/
   /*Start the conversion process */
   if (HAL_OK != HalAdcStart(&Adc_handle))
   {
      /* Start Conversation Error */
      ErrorHandler();
   }
   else
   {
      ;/*Do nothing*/
   }
}


/*
 *
 * Function                : StmadcDriver
 *
 * Description             : StmadcDriver function polls for conversion and configures
 *                            ADC configuration Channel.
 *
 * Formal parameter(s)     : None
 *
 * Return Value            : None
 *
 * Assumption              : None
 *
 */

void StmadcDriver(void)
{
   static T_UINT16 u16_chan_num = ZERO;

  /*hdudispfstmadc-StmadcDriver-DB-LLR-001*/
   HalAdcPollForConversion(&Adc_handle, ZERO);

   /*hdudispfstmadc-StmadcDriver-DB-LLR-002*/
   S16_adc_reading[u16_chan_num] = (T_INT16)HalAdcGetValue(&Adc_handle);

   /*hdudispfstmadc-StmadcDriver-DB-LLR-003*/
   u16_chan_num = (T_UINT16)(u16_chan_num + ONE);

   if(NUM_CHAN == u16_chan_num)
   {
      u16_chan_num = ZERO;
   }
   else
   {
    ;/*Do nothing*/
   }

   switch(u16_chan_num)
   {
      /*hdudispfstmadc-StmadcDriver-DB-LLR-004*/
      case 0:
         HalAdcConfigChannel(&Adc_handle, &S_config1);
         HalAdcStart(&Adc_handle);
         break;
      /*hdudispfstmadc-StmadcDriver-DB-LLR-005*/
      case 1:
         HalAdcConfigChannel(&Adc_handle, &S_config2);
         HalAdcStart(&Adc_handle);
         break;
      /*hdudispfstmadc-StmadcDriver-DB-LLR-006*/
      default:
         u16_chan_num = ZERO;
         break;
   }
}


