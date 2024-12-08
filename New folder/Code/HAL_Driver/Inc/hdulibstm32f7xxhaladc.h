/*
 ******************************************************************************
 * License Information  :  Howell Instruments, Inc.                           *
 *                         "Licensed Software" and "All rights reserved".     *
 ******************************************************************************
 *  File                : hdulibstm32f7xxhaladc.h
 *
 *  Description         : Header file of ADC HAL module.
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
 *      1.1          Shilpa A R       12-Sep-2017            100064
 *      1.2          Divya G P        09-Oct-2017            100064
 *
 * Additional References : None
 *
 ******************************************************************************
 */

/* Define to prevent recursive inclusion */
#ifndef _HDULIBSTM32F7XXHALADC_H_
#define _HDULIBSTM32F7XXHALADC_H_

/* Includes */
#include "hdulibstm32f746xx.h" /* CMSIS STM32F7xx Device Peripheral Access Layer file*/
#include "hdulibbasictypes.h" /* Define standard data types */
#include "hdulibstm32f7xxhaldma.h"  /* Header files for DMA HAL driver*/
#include "hdulibstm32f7xxhaldef.h" /*Contains the HAL defination module */
typedef struct
{
   T_UINT32 ClockPrescaler;        /* Select ADC clock prescaler */

   T_UINT32 Resolution;            /* Configures the ADC resolution.*/

   /*
    * Specifies ADC data alignment to right (MSB on register bit 11 and LSB on register bit 0)
    * (default setting) or to left (if regular group: MSB on register bit 15 and LSB on register
    * bit 4, if injected group (MSB kept as signed value due to potential negative value after
    * offset application): MSB on register bit 14 and LSB on register bit 3).
    */

   T_UINT32 DataAlign;

   /*
    * Configures the sequencer of regular and injected groups.
    * This parameter can be set to ENABLE or DISABLE
    */

   T_UINT32 ScanConvMode;

   /*
    * Specifies what EOC(End Of Conversion) flag is used for conversion
    * by polling and interruption: end of conversion of each rank or complete sequence.
    */
   T_UINT32 EOCSelection;

   /*
    * Specifies whether the conversion is performed in single mode (one conversion) or continuous
    * mode for regular group,after the selected trigger occurred
    * (software start or external trigger)
    * This parameter can be set to ENABLE or DISABLE.
    */
   T_UINT32 ContinuousConvMode;

   /* Specifies the number of ranks that will be converted within the regular group sequencer.*/
   T_UINT32 NbrOfConversion;

   /*
    * Specifies whether the conversions sequence of regular group is performed in
    * Complete-sequence/Discontinuous-sequence (main sequence subdivided in successive parts).
    */
   T_UINT32 DiscontinuousConvMode;

   /*
    * Specifies the number of discontinuous conversions in which the  main sequence of regular
    * group (parameter NbrOfConversion) will be subdivided.
    */
   T_UINT32 NbrOfDiscConversion;

   /* Selects the external event used to trigger the conversion start of regular group.*/
   T_UINT32 ExternalTrigConv;

   T_UINT32 ExternalTrigConvEdge;  /* Selects the external trigger edge of regular group. */

   /*
    * Specifies whether the DMA requests are performed in one shot mode (DMA transfer
    * stop when number of conversions is reached)
    */
   T_UINT32 DMAContinuousRequests;

}T_ADC_INIT;


typedef struct
{
  T_UINT32 Channel;      /* Specifies the channel to configure into ADC regular group. */

  T_UINT32 Rank;         /* Specifies the rank in the regular group sequencer. */

  T_UINT32 SamplingTime; /* Sampling time value to be set for the selected channel. */

  T_UINT32 Offset;       /* Reserved for future use, can be set to 0 */
}T_ADC_CHANNEL_CONF;

/* States of ADC global scope */
/* ADC not yet initialized or disabled */
#define HAL_ADC_STATE_RESET             ((T_UINT32)0x00000000U)
/* ADC peripheral ready for use */
#define HAL_ADC_STATE_READY             ((T_UINT32)0x00000001U)
/* ADC is busy to internal process (initialization, calibration) */
#define HAL_ADC_STATE_BUSY_INTERNAL     ((T_UINT32)0x00000002U)
 /* TimeOut occurrence */
#define HAL_ADC_STATE_TIMEOUT           ((T_UINT32)0x00000004U)

/* States of ADC errors */
#define HAL_ADC_STATE_ERROR_INTERNAL    ((T_UINT32)0x00000010U) /* Internal error occurrence */
/* Configuration error occurrence */
#define HAL_ADC_STATE_ERROR_CONFIG      ((T_UINT32)0x00000020U)
#define ADC_CHANNEL_TEMPSENSOR  ((T_UINT32)ADC_CHANNEL_18 | 0x10000000U)

/* States of ADC group regular */
/*
 * A conversion on group regular is ongoing or can occur (either by continuous mode,
 * external trigger, low power auto power-on (if feature available),
 * multimode ADC master control (if feature available))
 */
#define HAL_ADC_STATE_REG_BUSY          ((T_UINT32)0x00000100U)
/* Conversion data available on group regular */
#define HAL_ADC_STATE_REG_EOC           ((T_UINT32)0x00000200U)
#define HAL_ADC_STATE_REG_OVR           ((T_UINT32)0x00000400U) /* Overrun occurrence */

/* States of ADC group injected */
/*
 * A conversion on group injected is ongoing or can occur (either by auto-injection mode,
 * external trigger, low power auto power-on (if feature available), multimode ADC master
 * control (if feature available))
 */
#define HAL_ADC_STATE_INJ_BUSY          ((T_UINT32)0x00001000U)
/* Conversion data available on group injected */
#define HAL_ADC_STATE_INJ_EOC           ((T_UINT32)0x00002000U)

typedef struct
{
  T_ADC                *Instance;                   /* Register base address */

  T_ADC_INIT           Init;                        /* ADC required parameters */

  __IO T_UINT32        NbrOfCurrentConversionRank;  /* ADC number of current conversion rank */

  T_DMA_HANDLE         *DMA_Handle;                 /* Pointer DMA Handler */

  T_HAL_LOCK           Lock;                        /* ADC locking object */

  __IO T_UINT32        State;                       /* ADC communication state */

  __IO T_UINT32        ErrorCode;                   /* ADC Error code */
}T_ADC_HANDLE;

#define HAL_ADC_ERROR_NONE        ((T_UINT32)0x00U)   /* No error            */

#define HAL_ADC_ERROR_OVR         ((T_UINT32)0x02U)   /* Overrun error       */
#define HAL_ADC_ERROR_DMA         ((T_UINT32)0x04U)   /* DMA transfer error  */

#define ADC_CLOCK_SYNC_PCLK_DIV4    ((T_UINT32)ADC_CCR_ADCPRE_0)

#define ADC_RESOLUTION_12B          ((T_UINT32)0x00000000U)
#define ADC_EXTERNALTRIGCONVEDGE_NONE           ((T_UINT32)0x00000000U)

#define ADC_EXTERNALTRIGCONV_T1_CC1    ((T_UINT32)0x00000000U)

#define ADC_SOFTWARE_START             ((T_UINT32)ADC_CR2_EXTSEL + 1)

#define ADC_DATAALIGN_RIGHT      ((T_UINT32)0x00000000U)
#define ADC_CHANNEL_9           ((T_UINT32)(ADC_CR1_AWDCH_3 | ADC_CR1_AWDCH_0))
#define ADC_CHANNEL_10          ((T_UINT32)(ADC_CR1_AWDCH_3 | ADC_CR1_AWDCH_1))
#define ADC_CHANNEL_11          ((T_UINT32)(ADC_CR1_AWDCH_3 | ADC_CR1_AWDCH_1 | ADC_CR1_AWDCH_0))
#define ADC_CHANNEL_17          ((T_UINT32)(ADC_CR1_AWDCH_4 | ADC_CR1_AWDCH_0))
#define ADC_CHANNEL_18          ((T_UINT32)(ADC_CR1_AWDCH_4 | ADC_CR1_AWDCH_1))

#define ADC_CHANNEL_VREFINT     ((T_UINT32)ADC_CHANNEL_17)
#define ADC_CHANNEL_VBAT        ((T_UINT32)ADC_CHANNEL_18)
#define ADC_SAMPLETIME_3CYCLES    ((T_UINT32)0x00000000U)
#define ADC_FLAG_EOC    ((T_UINT32)ADC_SR_EOC)
#define ADC_FLAG_STRT   ((T_UINT32)ADC_SR_STRT)
#define ADC_FLAG_OVR    ((T_UINT32)ADC_SR_OVR)

#define __HAL_ADC_RESET_HANDLE_STATE(__HANDLE__) ((__HANDLE__)->State = HAL_ADC_STATE_RESET)

#define __HAL_ADC_ENABLE(__HANDLE__) ((__HANDLE__)->Instance->CR2 |=  ADC_CR2_ADON)

#define __HAL_ADC_CLEAR_FLAG(__HANDLE__, __FLAG__) (((__HANDLE__)->Instance->SR) = ~(__FLAG__))

#define __HAL_ADC_GET_FLAG(__HANDLE__, __FLAG__) ((((__HANDLE__)->Instance->SR) &  \
                                                         (__FLAG__)) == (__FLAG__))

#define ADC_STAB_DELAY_US               ((T_UINT32) 3U)

#define ADC_TEMPSENSOR_DELAY_US         ((T_UINT32) 10U)

#define ADC_IS_SOFTWARE_START_REGULAR(__HANDLE__)                              \
  (((__HANDLE__)->Instance->CR2 & ADC_CR2_EXTEN) == RESET)

#define ADC_STATE_CLR_SET MODIFY_REG

#define ADC_CLEAR_ERRORCODE(__HANDLE__)    \
  ((__HANDLE__)->ErrorCode = HAL_ADC_ERROR_NONE)

#define ADC_SQR1(_NbrOfConversion_) (((_NbrOfConversion_) - (T_UINT8)1) << 20)

#define ADC_SMPR1(_SAMPLETIME_, _CHANNELNB_) ((_SAMPLETIME_) << (3 * \
(((T_UINT32)((T_UINT16)(_CHANNELNB_))) - 10)))

#define ADC_SMPR2(_SAMPLETIME_, _CHANNELNB_) ((_SAMPLETIME_) << (3 * \
((T_UINT32)((T_UINT16)(_CHANNELNB_)))))


#define ADC_SQR3_RK(_CHANNELNB_, _RANKNB_) (((T_UINT32)((T_UINT16)(_CHANNELNB_))) \
<< (5 * ((_RANKNB_) - 1)))


#define ADC_SQR2_RK(_CHANNELNB_, _RANKNB_) (((T_UINT32)((T_UINT16)(_CHANNELNB_))) \
<< (5 * ((_RANKNB_) - 7)))


#define ADC_SQR1_RK(_CHANNELNB_, _RANKNB_) (((T_UINT32)((T_UINT16)(_CHANNELNB_))) \
<< (5 * ((_RANKNB_) - 13)))


#define ADC_CR2_CONTINUOUS(_CONTINUOUS_MODE_) ((_CONTINUOUS_MODE_) << 1)


#define ADC_CR1_DISCONTINUOUS(_NBR_DISCONTINUOUSCONV_) (((_NBR_DISCONTINUOUSCONV_) - 1) \
<< POSITION_VAL(ADC_CR1_DISCNUM))


#define ADC_CR1_SCANCONV(_SCANCONV_MODE_) ((_SCANCONV_MODE_) << 8)


#define ADC_CR2_EOCSELECTION(_EOCSelection_MODE_) ((_EOCSelection_MODE_) << 10)


#define ADC_CR2_DMACONTREQ(_DMAContReq_MODE_) ((_DMAContReq_MODE_) << 9)

extern T_HAL_STATUS HalAdcInit(T_ADC_HANDLE* h_adc);
extern void   HalAdcMspInit(T_ADC_HANDLE* h_adc);

/* I/O operation functions */
extern T_HAL_STATUS HalAdcStart(T_ADC_HANDLE* h_adc);
extern T_HAL_STATUS HalAdcPollForConversion(T_ADC_HANDLE* h_adc, T_UINT32 timeout);

extern T_UINT32          HalAdcGetValue(T_ADC_HANDLE* h_adc);
/* Peripheral Control functions */
extern T_HAL_STATUS HalAdcConfigChannel(T_ADC_HANDLE* h_adc, T_ADC_CHANNEL_CONF* sConfig);


#endif /*_HDULIBSTM32F7XXHALADC_H_ */

