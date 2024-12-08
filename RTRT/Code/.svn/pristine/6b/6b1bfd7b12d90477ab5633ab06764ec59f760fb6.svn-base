/*
 ******************************************************************************
 * License Information  :  Howell Instruments, Inc.                           *
 *                         "Licensed Software" and "All rights reserved".     *
 ******************************************************************************
 *  File                : hdulibstm32f7xxhaltim.h
 *
 *  Description         : Header file of TIM HAL module.
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
 *      1.2          Rona.B.S        02-Sep-2017            100028
 *
 * Additional References : None
 *
 ******************************************************************************
 */

/* Define to prevent recursive inclusion */
#ifndef _HDULIBSTM32F7XXHALTIM_H_
#define _HDULIBSTM32F7XXHALTIM_H_

/* Includes */
#include "hdulibbasictypes.h"                  /* Contains the basic data types */
#include "hdulibstm32f7xxhaltimex.h"      /* Header files for TIM EX HAL driver*/
#include "hdulibstm32f7xxhaldma.h"        /* Header files for DMA HAL driver*/
#include "hdulibstm32f7xxhaldef.h"        /* Header files for HAL definayion driver*/
#include "hdulibstm32f746xx.h"            /* CMSIS Cortex-M7 Device Peripheral Access Layer */
#include "hdulibcorecm7.h"                /* Cortex-M7 processor and core peripherals */

typedef struct
{
  T_UINT32 Prescaler;         /*
                               * Specifies the prescaler value used to divide the TIM clock.
                               * This parameter can be a number between Min_Data = 0x0000 and
                               * Max_Data = 0xFFFF
                               */

  T_UINT32 CounterMode;       /*
                               * Specifies the counter mode.
                               * This parameter can be a value of @ref TIM_Counter_Mode
                               */

  T_UINT32 Period;            /*
                               *Specifies the period value to be loaded into the active
                               * Auto-Reload Register at the next update event.
                               * This parameter can be a number between Min_Data = 0x0000 and
                               * Max_Data = 0xFFFF.
                               */

  T_UINT32 ClockDivision;     /*
                               * Specifies the clock division.
                               * This parameter can be a value of @ref TIM_ClockDivision
                               */

  T_UINT32 RepetitionCounter;  /*
                                * Specifies the repetition counter value. Each time the
                                * RCR down-counter reaches zero, an update event is generated
                                *  and counting restarts from  the RCR value (N).
                                * This means in PWM mode that (N+1) corresponds to:
                                * - the number of PWM periods in edge-aligned mode
                                * - the number of half PWM period in center-aligned mode
                                * This parameter must be a number between Min_Data = 0x00
                                * and Max_Data = 0xFF.    @note This parameter is valid only
                                * for TIM1 and TIM8.
                                */
} T_TIM_BASE_INIT;


typedef struct
{
  T_UINT32 OCMode;        /*
                           * Specifies the TIM mode.
                           * This parameter can be a value of @ref
                           * TIMEx_Output_Compare_and_PWM_modes
                           */

  T_UINT32 Pulse;         /*
                           * Specifies the pulse value to be loaded into
                           *  the Capture Compare Register.
                           * This parameter can be a number between Min_Data = 0x0000
                           * and Max_Data = 0xFFFF
                           */

  T_UINT32 OCPolarity;    /*
                           * Specifies the output polarity.
                           * This parameter can be a value of @ref TIM_Output_Compare_Polarity
                           */

  T_UINT32 OCNPolarity;   /*
                           * Specifies the complementary output polarity.
                           * This parameter can be a value of @ref TIM_Output_Compare_N_Polarity
                           * @note This parameter is valid only for TIM1 and TIM8.
                           */

  T_UINT32 OCFastMode;   /*
                          * Specifies the Fast mode state.
                          * This parameter can be a value of @ref TIM_Output_Fast_State
                          * @note This parameter is valid only in PWM1 and PWM2 mode.
                          */


  T_UINT32 OCIdleState;   /*
                           * Specifies the TIM Output Compare pin state during Idle state.
                           * This parameter can be a value of @ref TIM_Output_Compare_Idle_State
                           * @note This parameter is valid only for TIM1 and TIM8.
                           */

  T_UINT32 OCNIdleState;  /*
                           * Specifies the TIM Output Compare pin state during Idle state.
                           * This parameter can be a value of @ref TIM_Output_Compare_N_Idle_State
                           * @note This parameter is valid only for TIM1 and TIM8.
                           */
} T_TIM_OC_INIT;


typedef struct
{
  T_UINT32 OCMode;        /*
                           * Specifies the TIM mode.This parameter can be a
                           * value of @ref TIMEx_Output_Compare_and_PWM_modes
                           */

  T_UINT32 Pulse;         /*
                           * Specifies the pulse value to be loaded into the
                           * Capture Compare Register.
                           * This parameter can be a number between Min_Data = 0x0000
                           * and Max_Data = 0xFFFF
                           */

  T_UINT32 OCPolarity;    /* Specifies the output polarity.*/

  T_UINT32 OCNPolarity;   /* Specifies the complementary output polarity.*/

  T_UINT32 OCIdleState;   /* Specifies the TIM Output Compare pin state during Idle state.*/

  T_UINT32 OCNIdleState;  /* Specifies the TIM Output Compare pin state during Idle state.*/

  T_UINT32 ICPolarity;    /* Specifies the active edge of the input signal.*/

  T_UINT32 ICSelection;   /* Specifies the input.*/

  T_UINT32 ICFilter;      /* Specifies the input capture filter.*/

} T_TIM_ONEPULSE_INIT;


typedef struct
{
  T_UINT32  ICPolarity;   /* Specifies the active edge of the input signal.*/

  T_UINT32 ICSelection;  /* Specifies the input.*/

  T_UINT32 ICPrescaler;  /* Specifies the Input Capture Prescaler.*/

  T_UINT32 ICFilter;     /* Specifies the input capture filter.*/
} T_TIM_IC_INIT;


typedef struct
{
  T_UINT32 EncoderMode;   /* Specifies the active edge of the input signal.*/

  T_UINT32 IC1Polarity;   /* Specifies the active edge of the input signal.*/

  T_UINT32 IC1Selection;  /* Specifies the input.*/

  T_UINT32 IC1Prescaler;  /* Specifies the Input Capture Prescaler.*/

  T_UINT32 IC1Filter;     /* Specifies the input capture filter.*/

  T_UINT32 IC2Polarity;   /* Specifies the active edge of the input signal.*/

  T_UINT32 IC2Selection;  /* Specifies the input.*/

  T_UINT32 IC2Prescaler;  /* Specifies the Input Capture Prescaler.*/

  T_UINT32 IC2Filter;     /* Specifies the input capture filter.*/
} T_TIM_ENCODER_INIT;


typedef struct
{
  T_UINT32 ClockSource;     /* TIM clock sources.*/

  T_UINT32 ClockPolarity;   /* TIM clock polarity.*/

  T_UINT32 ClockPrescaler;  /* TIM clock prescaler.*/

  T_UINT32 ClockFilter;    /* TIM clock filter.*/

}T_TIM_CLOCKCONFIG;


typedef struct
{
  T_UINT32 ClearInputState;      /* TIM clear Input state.*/

  T_UINT32 ClearInputSource;     /* TIM clear Input sources.*/

  T_UINT32 ClearInputPolarity;   /* TIM Clear Input polarity.*/

  T_UINT32 ClearInputPrescaler;  /* TIM Clear Input prescaler.*/

  T_UINT32 ClearInputFilter;    /* TIM Clear Input filter.*/

}T_TIM_CLEARINPUTCONFIG;


typedef struct {
  T_UINT32  SlaveMode;         /*
                                * Slave mode selection
                                * This parameter can be a value of @ref TIMEx_Slave_Mode
                                */
  T_UINT32  InputTrigger;      /*
                                * Input Trigger source
                                *  This parameter can be a value of @ref TIM_Trigger_Selection
                                */
  T_UINT32  TriggerPolarity;   /*
                                *Input Trigger polarity
                                *  This parameter can be a value of @ref TIM_Trigger_Polarity
                                */
  T_UINT32  TriggerPrescaler;  /*
                                *Input trigger prescaler
                                *This parameter can be a value of @ref TIM_Trigger_Prescaler
                                */
  T_UINT32  TriggerFilter;     /*
                                *Input trigger filter
                                *This parameter can be a number between Min_Data =
                                * 0x0 and Max_Data = 0xF
                                */

}T_TIM_SLAVE_CONFIG;


typedef enum
{
  HAL_TIM_STATE_RESET             = 0x00U,    /* Peripheral not yet initialized or disabled  */
  HAL_TIM_STATE_READY             = 0x01U,    /* Peripheral Initialized and ready for use    */
  HAL_TIM_STATE_BUSY              = 0x02U,    /* An internal process is ongoing              */
  HAL_TIM_STATE_TIMEOUT           = 0x03U,    /* Timeout state                               */
  HAL_TIM_STATE_ERROR             = 0x04U     /* Reception process is ongoing                */
}T_HAL_TIM_STATE;


typedef enum
{
  HAL_TIM_ACTIVE_CHANNEL_1        = 0x01U,    /* The active channel is 1     */
  HAL_TIM_ACTIVE_CHANNEL_2        = 0x02U,    /* The active channel is 2     */
  HAL_TIM_ACTIVE_CHANNEL_3        = 0x04U,    /* The active channel is 3     */
  HAL_TIM_ACTIVE_CHANNEL_4        = 0x08U,    /* The active channel is 4     */
  HAL_TIM_ACTIVE_CHANNEL_CLEARED  = 0x00U     /* All active channels cleared */
}T_HAL_TIM_ACTIVE_CHANNEL;


typedef struct
{
   T_TIM                 *Instance;          /* Register base address             */
   T_TIM_BASE_INIT        Init;              /* TIM Time Base required parameters */
   T_HAL_TIM_ACTIVE_CHANNEL       Channel;   /* Active channel                    */
   T_DMA_HANDLE                *hdma[7];      /* DMA Handlers array                */
   T_HAL_LOCK             Lock;               /* Locking object                    */
   __IO T_HAL_TIM_STATE   State;            /* TIM operation state               */
}T_TIM_HANDLE;

/* Exported constants */

#define  TIM_INPUTCHANNELPOLARITY_RISING      ((T_UINT32)0x00000000U)
#define  TIM_INPUTCHANNELPOLARITY_FALLING     (TIM_CCER_CC1P)
#define  TIM_INPUTCHANLPOLARITY_BOTHEDGE    (TIM_CCER_CC1P | TIM_CCER_CC1NP)
#define TIM_ETRPOLARITY_INVERTED              (TIM_SMCR_ETP)
#define TIM_ETRPOLARITY_NONINVERTED           ((T_UINT32)0x0000U)

#define TIM_ETRPRESCALER_DIV1                 ((T_UINT32)0x0000U)
#define TIM_ETRPRESCALER_DIV2                 (TIM_SMCR_ETPS_0)
#define TIM_ETRPRESCALER_DIV4                 (TIM_SMCR_ETPS_1)
#define TIM_ETRPRESCALER_DIV8                 (TIM_SMCR_ETPS)

#define TIM_COUNTERMODE_UP                 ((T_UINT32)0x0000U)
#define TIM_COUNTERMODE_DOWN               TIM_CR1_DIR
#define TIM_COUNTERMODE_CENTERALIGNED1     TIM_CR1_CMS_0
#define TIM_COUNTERMODE_CENTERALIGNED2     TIM_CR1_CMS_1
#define TIM_COUNTERMODE_CENTERALIGNED3     TIM_CR1_CMS

#define TIM_CLOCKDIVISION_DIV1            ((T_UINT32)0x0000U)
#define TIM_CLOCKDIVISION_DIV2            (TIM_CR1_CKD_0)
#define TIM_CLOCKDIVISION_DIV4            (TIM_CR1_CKD_1)

#define TIM_OUTPUTSTATE_DISABLE            ((T_UINT32)0x0000U)
#define TIM_OUTPUTSTATE_ENABLE             (TIM_CCER_CC1E)

#define TIM_OCFAST_DISABLE                ((T_UINT32)0x0000U)
#define TIM_OCFAST_ENABLE                 (TIM_CCMR1_OC1FE)

#define TIM_OUTPUTNSTATE_DISABLE            ((T_UINT32)0x0000U)
#define TIM_OUTPUTNSTATE_ENABLE             (TIM_CCER_CC1NE)

#define TIM_OCPOLARITY_HIGH                ((T_UINT32)0x0000U)
#define TIM_OCPOLARITY_LOW                 (TIM_CCER_CC1P)

#define TIM_OCNPOLARITY_HIGH               ((T_UINT32)0x0000U)
#define TIM_OCNPOLARITY_LOW                (TIM_CCER_CC1NP)

#define TIM_OCIDLESTATE_SET                (TIM_CR2_OIS1)
#define TIM_OCIDLESTATE_RESET              ((T_UINT32)0x0000U)

#define TIM_OCNIDLESTATE_SET               (TIM_CR2_OIS1N)
#define TIM_OCNIDLESTATE_RESET             ((T_UINT32)0x0000U)

#define  TIM_ICPOLARITY_RISING             TIM_INPUTCHANNELPOLARITY_RISING
#define  TIM_ICPOLARITY_FALLING            TIM_INPUTCHANNELPOLARITY_FALLING
#define  TIM_ICPOLARITY_BOTHEDGE           TIM_INPUTCHANLPOLARITY_BOTHEDGE

#define TIM_ICSELECTION_DIRECTTI           (TIM_CCMR1_CC1S_0)

#define TIM_ICSELECTION_INDIRECTTI         (TIM_CCMR1_CC1S_1)

#define TIM_ICSELECTION_TRC                (TIM_CCMR1_CC1S)

#define TIM_ICPSC_DIV1                     ((T_UINT32)0x0000U)
#define TIM_ICPSC_DIV2                     (TIM_CCMR1_IC1PSC_0)
#define TIM_ICPSC_DIV4                     (TIM_CCMR1_IC1PSC_1)
#define TIM_ICPSC_DIV8                     (TIM_CCMR1_IC1PSC)

#define TIM_OPMODE_SINGLE                  (TIM_CR1_OPM)
#define TIM_OPMODE_REPETITIVE              ((T_UINT32)0x0000U)

#define TIM_ENCODERMODE_TI1                (TIM_SMCR_SMS_0)
#define TIM_ENCODERMODE_TI2                (TIM_SMCR_SMS_1)
#define TIM_ENCODERMODE_TI12               (TIM_SMCR_SMS_1 | TIM_SMCR_SMS_0)

#define TIM_IT_UPDATE           (TIM_DIER_UIE)
#define TIM_IT_CC1              (TIM_DIER_CC1IE)
#define TIM_IT_CC2              (TIM_DIER_CC2IE)
#define TIM_IT_CC3              (TIM_DIER_CC3IE)
#define TIM_IT_CC4              (TIM_DIER_CC4IE)
#define TIM_IT_COM              (TIM_DIER_COMIE)
#define TIM_IT_TRIGGER          (TIM_DIER_TIE)
#define TIM_IT_BREAK            (TIM_DIER_BIE)

#define TIM_COMMUTATION_TRGI              (TIM_CR2_CCUS)
#define TIM_COMMUTATION_SOFTWARE          ((T_UINT32)0x0000U)

#define TIM_DMA_UPDATE                     (TIM_DIER_UDE)
#define TIM_DMA_CC1                        (TIM_DIER_CC1DE)
#define TIM_DMA_CC2                        (TIM_DIER_CC2DE)
#define TIM_DMA_CC3                        (TIM_DIER_CC3DE)
#define TIM_DMA_CC4                        (TIM_DIER_CC4DE)
#define TIM_DMA_COM                        (TIM_DIER_COMDE)
#define TIM_DMA_TRIGGER                    (TIM_DIER_TDE)

#define TIM_EVENTSOURCE_UPDATE              TIM_EGR_UG
#define TIM_EVENTSOURCE_CC1                 TIM_EGR_CC1G
#define TIM_EVENTSOURCE_CC2                 TIM_EGR_CC2G
#define TIM_EVENTSOURCE_CC3                 TIM_EGR_CC3G
#define TIM_EVENTSOURCE_CC4                 TIM_EGR_CC4G
#define TIM_EVENTSOURCE_COM                 TIM_EGR_COMG
#define TIM_EVENTSOURCE_TRIGGER             TIM_EGR_TG
#define TIM_EVENTSOURCE_BREAK               TIM_EGR_BG
#define TIM_EVENTSOURCE_BREAK2              TIM_EGR_B2G

#define TIM_FLAG_UPDATE                    (TIM_SR_UIF)
#define TIM_FLAG_CC1                       (TIM_SR_CC1IF)
#define TIM_FLAG_CC2                       (TIM_SR_CC2IF)
#define TIM_FLAG_CC3                       (TIM_SR_CC3IF)
#define TIM_FLAG_CC4                       (TIM_SR_CC4IF)
#define TIM_FLAG_COM                       (TIM_SR_COMIF)
#define TIM_FLAG_TRIGGER                   (TIM_SR_TIF)
#define TIM_FLAG_BREAK                     (TIM_SR_BIF)
#define TIM_FLAG_BREAK2                    (TIM_SR_B2IF)
#define TIM_FLAG_CC1OF                     (TIM_SR_CC1OF)
#define TIM_FLAG_CC2OF                     (TIM_SR_CC2OF)
#define TIM_FLAG_CC3OF                     (TIM_SR_CC3OF)
#define TIM_FLAG_CC4OF                     (TIM_SR_CC4OF)

#define  TIM_CLOCKSOURCE_ETRMODE2    (TIM_SMCR_ETPS_1)
#define  TIM_CLOCKSOURCE_INTERNAL    (TIM_SMCR_ETPS_0)
#define  TIM_CLOCKSOURCE_ITR0        ((T_UINT32)0x0000U)
#define  TIM_CLOCKSOURCE_ITR1        (TIM_SMCR_TS_0)
#define  TIM_CLOCKSOURCE_ITR2        (TIM_SMCR_TS_1)
#define  TIM_CLOCKSOURCE_ITR3        (TIM_SMCR_TS_0 | TIM_SMCR_TS_1)
#define  TIM_CLOCKSOURCE_TI1ED       (TIM_SMCR_TS_2)
#define  TIM_CLOCKSOURCE_TI1         (TIM_SMCR_TS_0 | TIM_SMCR_TS_2)
#define  TIM_CLOCKSOURCE_TI2         (TIM_SMCR_TS_1 | TIM_SMCR_TS_2)
#define  TIM_CLOCKSOURCE_ETRMODE1    (TIM_SMCR_TS)

#define TIM_CLOCKPOLARITY_INVERTED           TIM_ETRPOLARITY_INVERTED
#define TIM_CLOCKPOLARITY_NONINVERTED        TIM_ETRPOLARITY_NONINVERTED
#define TIM_CLOCKPOLARITY_RISING             TIM_INPUTCHANNELPOLARITY_RISING
#define TIM_CLOCKPOLARITY_FALLING            TIM_INPUTCHANNELPOLARITY_FALLING
#define TIM_CLOCKPOLARITY_BOTHEDGE           TIM_INPUTCHANLPOLARITY_BOTHEDGE

#define TIM_CLOCKPRESCALER_DIV1              TIM_ETRPRESCALER_DIV1
#define TIM_CLOCKPRESCALER_DIV2              TIM_ETRPRESCALER_DIV2
#define TIM_CLOCKPRESCALER_DIV4              TIM_ETRPRESCALER_DIV4
#define TIM_CLOCKPRESCALER_DIV8              TIM_ETRPRESCALER_DIV8

#define TIM_CLEARINPUTPOLARITY_INVERTED           TIM_ETRPOLARITY_INVERTED
#define TIM_CLR_INPUTPOLARTY_NONINVERTED        TIM_ETRPOLARITY_NONINVERTED

#define TIM_CLEARINPUTPRESCALER_DIV1                    TIM_ETRPRESCALER_DIV1
#define TIM_CLEARINPUTPRESCALER_DIV2                    TIM_ETRPRESCALER_DIV2
#define TIM_CLEARINPUTPRESCALER_DIV4                    TIM_ETRPRESCALER_DIV4
#define TIM_CLEARINPUTPRESCALER_DIV8                    TIM_ETRPRESCALER_DIV8

#define TIM_OSSR_ENABLE          (TIM_BDTR_OSSR)
#define TIM_OSSR_DISABLE          ((T_UINT32)0x0000U)

#define TIM_OSSI_ENABLE        (TIM_BDTR_OSSI)
#define TIM_OSSI_DISABLE            ((T_UINT32)0x0000U)

#define TIM_LOCKLEVEL_OFF     ((T_UINT32)0x0000U)
#define TIM_LOCKLEVEL_1            (TIM_BDTR_LOCK_0)
#define TIM_LOCKLEVEL_2            (TIM_BDTR_LOCK_1)
#define TIM_LOCKLEVEL_3            (TIM_BDTR_LOCK)

#define TIM_BREAK_ENABLE          (TIM_BDTR_BKE)
#define TIM_BREAK_DISABLE         ((T_UINT32)0x0000U)

#define TIM_BREAKPOLARITY_LOW        ((T_UINT32)0x0000U)
#define TIM_BREAKPOLARITY_HIGH       (TIM_BDTR_BKP)

#define TIM_AUTOMATICOUTPUT_ENABLE           (TIM_BDTR_AOE)
#define  TIM_AUTOMATICOUTPUT_DISABLE          ((T_UINT32)0x0000U)

#define  TIM_TRGO_RESET            ((T_UINT32)0x0000U)
#define  TIM_TRGO_ENABLE           (TIM_CR2_MMS_0)
#define  TIM_TRGO_UPDATE           (TIM_CR2_MMS_1)
#define  TIM_TRGO_OC1              ((TIM_CR2_MMS_1 | TIM_CR2_MMS_0))
#define  TIM_TRGO_OC1REF           (TIM_CR2_MMS_2)
#define  TIM_TRGO_OC2REF           ((TIM_CR2_MMS_2 | TIM_CR2_MMS_0))
#define  TIM_TRGO_OC3REF           ((TIM_CR2_MMS_2 | TIM_CR2_MMS_1))
#define  TIM_TRGO_OC4REF           ((TIM_CR2_MMS_2 | TIM_CR2_MMS_1 | TIM_CR2_MMS_0))

#define TIM_MASTERSLAVEMODE_ENABLE          ((T_UINT32)0x0080)
#define TIM_MASTERSLAVEMODE_DISABLE         ((T_UINT32)0x0000U)

#define TIM_TS_ITR0                        ((T_UINT32)0x0000U)
#define TIM_TS_ITR1                        ((T_UINT32)0x0010U)
#define TIM_TS_ITR2                        ((T_UINT32)0x0020U)
#define TIM_TS_ITR3                        ((T_UINT32)0x0030U)
#define TIM_TS_TI1F_ED                     ((T_UINT32)0x0040U)
#define TIM_TS_TI1FP1                      ((T_UINT32)0x0050U)
#define TIM_TS_TI2FP2                      ((T_UINT32)0x0060U)
#define TIM_TS_ETRF                        ((T_UINT32)0x0070U)
#define TIM_TS_NONE                        ((T_UINT32)0xFFFFU)

#define TIM_TRIGGERPOLARITY_INVERTED           TIM_ETRPOLARITY_INVERTED
#define TIM_TRIGGERPOLARITY_NONINVERTED        TIM_ETRPOLARITY_NONINVERTED
#define TIM_TRIGGERPOLARITY_RISING             TIM_INPUTCHANNELPOLARITY_RISING
#define TIM_TRIGGERPOLARITY_FALLING            TIM_INPUTCHANNELPOLARITY_FALLING
#define TIM_TRIGGERPOLARITY_BOTHEDGE           TIM_INPUTCHANLPOLARITY_BOTHEDGE

#define TIM_TRIGGERPRESCALER_DIV1             TIM_ETRPRESCALER_DIV1
#define TIM_TRIGGERPRESCALER_DIV2             TIM_ETRPRESCALER_DIV2
#define TIM_TRIGGERPRESCALER_DIV4             TIM_ETRPRESCALER_DIV4
#define TIM_TRIGGERPRESCALER_DIV8             TIM_ETRPRESCALER_DIV8

#define TIM_TI1SELECTION_CH1                ((T_UINT32)0x0000U)
#define TIM_TI1SELECTION_XORCOMBINATION     (TIM_CR2_TI1S)

#define TIM_DMABASE_CR1                    (0x00000000U)
#define TIM_DMABASE_CR2                    (0x00000001U)
#define TIM_DMABASE_SMCR                   (0x00000002U)
#define TIM_DMABASE_DIER                   (0x00000003U)
#define TIM_DMABASE_SR                     (0x00000004U)
#define TIM_DMABASE_EGR                    (0x00000005U)
#define TIM_DMABASE_CCMR1                  (0x00000006U)
#define TIM_DMABASE_CCMR2                  (0x00000007U)
#define TIM_DMABASE_CCER                   (0x00000008U)
#define TIM_DMABASE_CNT                    (0x00000009U)
#define TIM_DMABASE_PSC                    (0x0000000AU)
#define TIM_DMABASE_ARR                    (0x0000000BU)
#define TIM_DMABASE_RCR                    (0x0000000CU)
#define TIM_DMABASE_CCR1                   (0x0000000DU)
#define TIM_DMABASE_CCR2                   (0x0000000EU)
#define TIM_DMABASE_CCR3                   (0x0000000FU)
#define TIM_DMABASE_CCR4                   (0x00000010U)
#define TIM_DMABASE_BDTR                   (0x00000011U)
#define TIM_DMABASE_DCR                    (0x00000012U)
#define TIM_DMABASE_OR                     (0x00000013U)

#define TIM_DMABURSTLENGTH_1TRANSFER           (0x00000000U)
#define TIM_DMABURSTLENGTH_2TRANSFERS          (0x00000100U)
#define TIM_DMABURSTLENGTH_3TRANSFERS          (0x00000200U)
#define TIM_DMABURSTLENGTH_4TRANSFERS          (0x00000300U)
#define TIM_DMABURSTLENGTH_5TRANSFERS          (0x00000400U)
#define TIM_DMABURSTLENGTH_6TRANSFERS          (0x00000500U)
#define TIM_DMABURSTLENGTH_7TRANSFERS          (0x00000600U)
#define TIM_DMABURSTLENGTH_8TRANSFERS          (0x00000700U)
#define TIM_DMABURSTLENGTH_9TRANSFERS          (0x00000800U)
#define TIM_DMABURSTLENGTH_10TRANSFERS         (0x00000900U)
#define TIM_DMABURSTLENGTH_11TRANSFERS         (0x00000A00U)
#define TIM_DMABURSTLENGTH_12TRANSFERS         (0x00000B00U)
#define TIM_DMABURSTLENGTH_13TRANSFERS         (0x00000C00U)
#define TIM_DMABURSTLENGTH_14TRANSFERS         (0x00000D00U)
#define TIM_DMABURSTLENGTH_15TRANSFERS         (0x00000E00U)
#define TIM_DMABURSTLENGTH_16TRANSFERS         (0x00000F00U)
#define TIM_DMABURSTLENGTH_17TRANSFERS         (0x00001000U)
#define TIM_DMABURSTLENGTH_18TRANSFERS         (0x00001100U)

#define TIM_DMA_ID_UPDATE                ((T_UINT16) 0x0U)
#define TIM_DMA_ID_CC1                   ((T_UINT16) 0x1U)
#define TIM_DMA_ID_CC2                   ((T_UINT16) 0x2U)
#define TIM_DMA_ID_CC3                   ((T_UINT16) 0x3U)
#define TIM_DMA_ID_CC4                   ((T_UINT16) 0x4U)
#define TIM_DMA_ID_COMMUTATION           ((T_UINT16) 0x5U)
#define TIM_DMA_ID_TRIGGER               ((T_UINT16) 0x6U)

#define TIM_CCX_ENABLE                   ((T_UINT32)0x0001U)
#define TIM_CCX_DISABLE                  ((T_UINT32)0x0000U)
#define TIM_CCXN_ENABLE                  ((T_UINT32)0x0004U)
#define TIM_CCXN_DISABLE                 ((T_UINT32)0x0000U)


/* Exported macro */

#define __HAL_TIM_RESET_HANDLE_STATE(__HANDLE__) ((__HANDLE__)->State = HAL_TIM_STATE_RESET)

#define __HAL_TIM_ENABLE(__HANDLE__)                 ((__HANDLE__)->Instance->CR1|=(TIM_CR1_CEN))

#define __HAL_TIM_URS_ENABLE(__HANDLE__)             ((__HANDLE__)->Instance->CR1|=(TIM_CR1_URS))

#define __HAL_TIM_MOE_ENABLE(__HANDLE__)             ((__HANDLE__)->Instance->BDTR|=(TIM_BDTR_MOE))

#define TIM_CCER_CCXE_MASK ((T_UINT32)(TIM_CCER_CC1E | TIM_CCER_CC2E | \
                                       TIM_CCER_CC3E | TIM_CCER_CC4E))
#define TIM_CCER_CCXNE_MASK ((T_UINT32)(TIM_CCER_CC1NE | TIM_CCER_CC2NE | TIM_CCER_CC3NE))

#define __HAL_TIM_DISABLE(__HANDLE__) \
                        do { \
                          if (((__HANDLE__)->Instance->CCER & TIM_CCER_CCXE_MASK) == 0) \
                          { \
                            if(((__HANDLE__)->Instance->CCER & TIM_CCER_CCXNE_MASK) == 0) \
                            { \
                              (__HANDLE__)->Instance->CR1 &= ~(TIM_CR1_CEN); \
                            } \
                          } \
                        } while(0)

#define __HAL_TIM_URS_DISABLE(__HANDLE__)            ((__HANDLE__)->Instance->CR1&=~(TIM_CR1_URS))


#define __HAL_TIM_MOE_DISABLE(__HANDLE__) \
                        do { \
                          if (((__HANDLE__)->Instance->CCER & TIM_CCER_CCXE_MASK) == 0) \
                          { \
                            if(((__HANDLE__)->Instance->CCER & TIM_CCER_CCXNE_MASK) == 0) \
                            { \
                              (__HANDLE__)->Instance->BDTR &= ~(TIM_BDTR_MOE); \
                            } \
                          } \
                        } while(0)

#define __HAL_TIM_ENABLE_IT(__HANDLE__, __INTERRUPT__) \
                                       ((__HANDLE__)->Instance->DIER |= (__INTERRUPT__))
#define __HAL_TIM_ENABLE_DMA(__HANDLE__, __DMA__)    \
                                             ((__HANDLE__)->Instance->DIER |= (__DMA__))
#define __HAL_TIM_DISABLE_IT(__HANDLE__, __INTERRUPT__) \
                                       ((__HANDLE__)->Instance->DIER &= ~(__INTERRUPT__))
#define __HAL_TIM_DISABLE_DMA(__HANDLE__, __DMA__)   \
                                       ((__HANDLE__)->Instance->DIER &= ~(__DMA__))
#define __HAL_TIM_GET_FLAG(__HANDLE__, __FLAG__)     \
                                 (((__HANDLE__)->Instance->SR &(__FLAG__)) == (__FLAG__))
#define __HAL_TIM_CLEAR_FLAG(__HANDLE__, __FLAG__)  \
                                             ((__HANDLE__)->Instance->SR = ~(__FLAG__))

#define __HAL_TIM_GET_IT_SOURCE(__HANDLE__, __INTERRUPT__) \
                        ((((__HANDLE__)->Instance->DIER & (__INTERRUPT__)) == \
                        (__INTERRUPT__)) ? SET : RESET)

#define __HAL_TIM_CLEAR_IT(__HANDLE__, __INTERRUPT__)  \
                           ((__HANDLE__)->Instance->SR = ~(__INTERRUPT__))

#define __HAL_TIM_IS_TIM_COUNTING_DOWN(__HANDLE__)         \
                              (((__HANDLE__)->Instance->CR1 &(TIM_CR1_DIR)) == (TIM_CR1_DIR))
#define __HAL_TIM_SET_PRESCALER (__HANDLE__, __PRESC__)      \
                              ((__HANDLE__)->Instance->PSC = (__PRESC__))

#define TIM_SET_ICPRESCALERVALUE(__HANDLE__, __CHANNEL__, __ICPSC__) \
(((__CHANNEL__) == TIM_CHANNEL_1) ? ((__HANDLE__)->Instance->CCMR1 |= (__ICPSC__)) :\
 ((__CHANNEL__) == TIM_CHANNEL_2) ? ((__HANDLE__)->Instance->CCMR1 |= ((__ICPSC__) << 8)) :\
 ((__CHANNEL__) == TIM_CHANNEL_3) ? ((__HANDLE__)->Instance->CCMR2 |= (__ICPSC__)) :\
 ((__HANDLE__)->Instance->CCMR2 |= ((__ICPSC__) << 8)))

#define TIM_RESET_ICPRESCALERVALUE(__HANDLE__, __CHANNEL__) \
(((__CHANNEL__) == TIM_CHANNEL_1) ? ((__HANDLE__)->Instance->CCMR1\
                                 &= (T_UINT16)~TIM_CCMR1_IC1PSC) :\
 ((__CHANNEL__) == TIM_CHANNEL_2) ? ((__HANDLE__)->Instance->CCMR1 \
                                  &= (T_UINT16)~TIM_CCMR1_IC2PSC) :\
 ((__CHANNEL__) == TIM_CHANNEL_3) ? ((__HANDLE__)->Instance->CCMR2 \
                                   &= (T_UINT16)~TIM_CCMR2_IC3PSC) :\
 ((__HANDLE__)->Instance->CCMR2 &= (T_UINT16)~TIM_CCMR2_IC4PSC))

#define TIM_SET_CAPTUREPOLARITY(__HANDLE__, __CHANNEL__, __POLARITY__) \
(((__CHANNEL__) == TIM_CHANNEL_1) ? ((__HANDLE__)->Instance->CCER |= (__POLARITY__)) :\
 ((__CHANNEL__) == TIM_CHANNEL_2) ? ((__HANDLE__)->Instance->CCER |= ((__POLARITY__) << 4)) :\
 ((__CHANNEL__) == TIM_CHANNEL_3) ? ((__HANDLE__)->Instance->CCER |= ((__POLARITY__) << 8)) :\
 ((__HANDLE__)->Instance->CCER |= (((__POLARITY__) << 12) & TIM_CCER_CC4P)))

#define TIM_RESET_CAPTUREPOLARITY(__HANDLE__, __CHANNEL__) \
      (((__CHANNEL__) == TIM_CHANNEL_1) ? ((__HANDLE__)->Instance->CCER &=\
      (T_UINT16)~(TIM_CCER_CC1P | TIM_CCER_CC1NP)) :\
      ((__CHANNEL__) == TIM_CHANNEL_2) ? ((__HANDLE__)->Instance->CCER &= \
      (T_UINT16)~(TIM_CCER_CC2P | TIM_CCER_CC2NP)) :\
      ((__CHANNEL__) == TIM_CHANNEL_3) ? ((__HANDLE__)->Instance->CCER &= \
      (T_UINT16)~(TIM_CCER_CC3P | TIM_CCER_CC3NP)) :\
      ((__HANDLE__)->Instance->CCER &= (T_UINT16)~TIM_CCER_CC4P))


#define __HAL_TIM_SET_COUNTER(__HANDLE__, __COUNTER__)\
               ((__HANDLE__)->Instance->CNT = (__COUNTER__))


#define __HAL_TIM_GET_COUNTER(__HANDLE__) ((__HANDLE__)->Instance->CNT)


#define __HAL_TIM_SET_AUTORELOAD(__HANDLE__, __AUTORELOAD__)                  \
                        do{                                                  \
                            (__HANDLE__)->Instance->ARR = (__AUTORELOAD__);  \
                            (__HANDLE__)->Init.Period = (__AUTORELOAD__);    \
                          } while(0)

#define __HAL_TIM_GET_AUTORELOAD(__HANDLE__) ((__HANDLE__)->Instance->ARR)


#define __HAL_TIM_SET_CLOCKDIVISION(__HANDLE__, __CKD__) \
                        do{                                                             \
                              (__HANDLE__)->Instance->CR1 &= (T_UINT16)(~TIM_CR1_CKD);  \
                              (__HANDLE__)->Instance->CR1 |= (__CKD__);                 \
                              (__HANDLE__)->Init.ClockDivision = (__CKD__);             \
                          } while(0)

#define __HAL_TIM_GET_CLOCKDIVISION(__HANDLE__) ((__HANDLE__)->Instance->CR1 & TIM_CR1_CKD)


#define __HAL_TIM_SET_ICPRESCALER(__HANDLE__, __CHANNEL__, __ICPSC__) \
                        do{                                                    \
                              TIM_RESET_ICPRESCALERVALUE((__HANDLE__), (__CHANNEL__));  \
                              TIM_SET_ICPRESCALERVALUE((__HANDLE__), (__CHANNEL__), (__ICPSC__)); \
                          } while(0)

#define __HAL_TIM_GET_ICPRESCALER(__HANDLE__, __CHANNEL__)  \
  (((__CHANNEL__) == TIM_CHANNEL_1) ? ((__HANDLE__)->Instance->CCMR1 & TIM_CCMR1_IC1PSC) :\
   ((__CHANNEL__) == TIM_CHANNEL_2) ? (((__HANDLE__)->Instance->CCMR1 & TIM_CCMR1_IC2PSC) >> 8) :\
   ((__CHANNEL__) == TIM_CHANNEL_3) ? ((__HANDLE__)->Instance->CCMR2 & TIM_CCMR2_IC3PSC) :\
   (((__HANDLE__)->Instance->CCMR2 & TIM_CCMR2_IC4PSC)) >> 8)


#define __HAL_TIM_SET_CAPTUREPOLARITY(__HANDLE__, __CHANNEL__, __POLARITY__)\
                       do{\
                           TIM_RESET_CAPTUREPOLARITY((__HANDLE__), (__CHANNEL__));\
                           TIM_SET_CAPTUREPOLARITY((__HANDLE__), (__CHANNEL__), (__POLARITY__)); \
                         }while(0)


/* Exported functions */

/* Timer PWM functions */

T_HAL_STATUS HalTimPwmInit(T_TIM_HANDLE *htim);
void HalTimPwmMspInit(T_TIM_HANDLE *htim);

/* Blocking mode: Polling */

T_HAL_STATUS HalTimPwmStart(T_TIM_HANDLE *htim, T_UINT32 Channel);
T_HAL_STATUS HalTimPwmConfigChannel(T_TIM_HANDLE *htim, T_TIM_OC_INIT* sConfig, T_UINT32 Channel);

#define IS_TIM_COUNTER_MODE(__MODE__) (((__MODE__) == TIM_COUNTERMODE_UP)              || \
                                       ((__MODE__) == TIM_COUNTERMODE_DOWN)            || \
                                       ((__MODE__) == TIM_COUNTERMODE_CENTERALIGNED1)  || \
                                       ((__MODE__) == TIM_COUNTERMODE_CENTERALIGNED2)  || \
                                       ((__MODE__) == TIM_COUNTERMODE_CENTERALIGNED3))

#define IS_TIM_CLOCKDIVISION_DIV(__DIV__) (((__DIV__) == TIM_CLOCKDIVISION_DIV1) || \
                                           ((__DIV__) == TIM_CLOCKDIVISION_DIV2) || \
                                           ((__DIV__) == TIM_CLOCKDIVISION_DIV4))

#define IS_TIM_FAST_STATE(__STATE__) (((__STATE__) == TIM_OCFAST_DISABLE) || \
                                      ((__STATE__) == TIM_OCFAST_ENABLE))

#define IS_TIM_OUTPUT_STATE(STATE) (((STATE) == TIM_OUTPUTSTATE_DISABLE) || \
                                    ((STATE) == TIM_OUTPUTSTATE_ENABLE))

#define IS_TIM_OUTPUTN_STATE(STATE) (((STATE) == TIM_OUTPUTNSTATE_DISABLE) || \
                                     ((STATE) == TIM_OUTPUTNSTATE_ENABLE))

#define IS_TIM_OC_POLARITY(__POLARITY__) (((__POLARITY__) == TIM_OCPOLARITY_HIGH) || \
                                          ((__POLARITY__) == TIM_OCPOLARITY_LOW))

#define IS_TIM_OCN_POLARITY(__POLARITY__) (((__POLARITY__) == TIM_OCNPOLARITY_HIGH) || \
                                           ((__POLARITY__) == TIM_OCNPOLARITY_LOW))

#define IS_TIM_OCIDLE_STATE(__STATE__) (((__STATE__) == TIM_OCIDLESTATE_SET) || \
                                        ((__STATE__) == TIM_OCIDLESTATE_RESET))

#define IS_TIM_OCNIDLE_STATE(__STATE__) (((__STATE__) == TIM_OCNIDLESTATE_SET) || \
                                         ((__STATE__) == TIM_OCNIDLESTATE_RESET))

#define IS_TIM_IC_POLARITY(__POLARITY__) (((__POLARITY__) == TIM_ICPOLARITY_RISING)   || \
                                          ((__POLARITY__) == TIM_ICPOLARITY_FALLING)  || \
                                          ((__POLARITY__) == TIM_ICPOLARITY_BOTHEDGE))

#define IS_TIM_IC_SELECTION(__SELECTION__) (((__SELECTION__) == TIM_ICSELECTION_DIRECTTI) || \
                                            ((__SELECTION__) == TIM_ICSELECTION_INDIRECTTI) || \
                                            ((__SELECTION__) == TIM_ICSELECTION_TRC))

#define IS_TIM_IC_PRESCALER(__PRESCALER__) (((__PRESCALER__) == TIM_ICPSC_DIV1) || \
                                            ((__PRESCALER__) == TIM_ICPSC_DIV2) || \
                                            ((__PRESCALER__) == TIM_ICPSC_DIV4) || \
                                            ((__PRESCALER__) == TIM_ICPSC_DIV8))

#define IS_TIM_OPM_MODE(__MODE__) (((__MODE__) == TIM_OPMODE_SINGLE) || \
                                   ((__MODE__) == TIM_OPMODE_REPETITIVE))

#define IS_TIM_ENCODER_MODE(__MODE__) (((__MODE__) == TIM_ENCODERMODE_TI1) || \
                                       ((__MODE__) == TIM_ENCODERMODE_TI2) || \
                                       ((__MODE__) == TIM_ENCODERMODE_TI12))

#define IS_TIM_IT(__IT__) ((((__IT__) & 0xFFFFFF00U) == 0x00000000U) && ((__IT__) != 0x00000000U))


#define IS_TIM_GET_IT(__IT__) (((__IT__) == TIM_IT_UPDATE)  || \
                               ((__IT__) == TIM_IT_CC1)     || \
                               ((__IT__) == TIM_IT_CC2)     || \
                               ((__IT__) == TIM_IT_CC3)     || \
                               ((__IT__) == TIM_IT_CC4)     || \
                               ((__IT__) == TIM_IT_COM)     || \
                               ((__IT__) == TIM_IT_TRIGGER) || \
                               ((__IT__) == TIM_IT_BREAK))

#define IS_TIM_DMA_SOURCE(__SOURCE__) ((((__SOURCE__) & 0xFFFF80FFU) == 0x00000000U) \
                                       && ((__SOURCE__) != 0x00000000U))

#define IS_TIM_EVENT_SOURCE(__SOURCE__) ((((__SOURCE__) & 0xFFFFFE00U) == 0x00000000U)\
                                       && ((__SOURCE__) != 0x00000000U))

#define IS_TIM_FLAG(__FLAG__) (((__FLAG__) == TIM_FLAG_UPDATE) || \
                               ((__FLAG__) == TIM_FLAG_CC1)     || \
                               ((__FLAG__) == TIM_FLAG_CC2)     || \
                               ((__FLAG__) == TIM_FLAG_CC3)     || \
                               ((__FLAG__) == TIM_FLAG_CC4)     || \
                               ((__FLAG__) == TIM_FLAG_COM)     || \
                               ((__FLAG__) == TIM_FLAG_TRIGGER) || \
                               ((__FLAG__) == TIM_FLAG_BREAK)   || \
                               ((__FLAG__) == TIM_FLAG_BREAK2)  || \
                               ((__FLAG__) == TIM_FLAG_CC1OF)   || \
                               ((__FLAG__) == TIM_FLAG_CC2OF)   || \
                               ((__FLAG__) == TIM_FLAG_CC3OF)   || \
                               ((__FLAG__) == TIM_FLAG_CC4OF))

#define IS_TIM_CLOCKSOURCE(__CLOCK__) (((__CLOCK__) == TIM_CLOCKSOURCE_INTERNAL) || \
                                       ((__CLOCK__) == TIM_CLOCKSOURCE_ETRMODE2) || \
                                       ((__CLOCK__) == TIM_CLOCKSOURCE_ITR0)     || \
                                       ((__CLOCK__) == TIM_CLOCKSOURCE_ITR1)     || \
                                       ((__CLOCK__) == TIM_CLOCKSOURCE_ITR2)     || \
                                       ((__CLOCK__) == TIM_CLOCKSOURCE_ITR3)     || \
                                       ((__CLOCK__) == TIM_CLOCKSOURCE_TI1ED)    || \
                                       ((__CLOCK__) == TIM_CLOCKSOURCE_TI1)      || \
                                       ((__CLOCK__) == TIM_CLOCKSOURCE_TI2)      || \
                                       ((__CLOCK__) == TIM_CLOCKSOURCE_ETRMODE1))

#define IS_TIM_CLOCKPOLARITY(__POLARITY__) (((__POLARITY__) == TIM_CLOCKPOLARITY_INVERTED)    || \
                                        ((__POLARITY__) == TIM_CLOCKPOLARITY_NONINVERTED) || \
                                        ((__POLARITY__) == TIM_CLOCKPOLARITY_RISING)      || \
                                        ((__POLARITY__) == TIM_CLOCKPOLARITY_FALLING)     || \
                                        ((__POLARITY__) == TIM_CLOCKPOLARITY_BOTHEDGE))

#define IS_TIM_CLOCKPRESCALER(__PRESCALER__) (((__PRESCALER__) == TIM_CLOCKPRESCALER_DIV1) || \
                                              ((__PRESCALER__) == TIM_CLOCKPRESCALER_DIV2) || \
                                              ((__PRESCALER__) == TIM_CLOCKPRESCALER_DIV4) || \
                                              ((__PRESCALER__) == TIM_CLOCKPRESCALER_DIV8))

#define IS_TIM_CLOCKFILTER(__ICFILTER__)      ((__ICFILTER__) <= 0xF)

#define IS_TIM_CLEARINPUT_POLARITY(__POLARITY__)  \
                                         (((__POLARITY__) == TIM_CLEARINPUTPOLARITY_INVERTED) || \
                                        ((__POLARITY__) == TIM_CLR_INPUTPOLARTY_NONINVERTED))

#define IS_TIM_CLEARINPUT_PRESCALER(__PRESCALER__) \
                                       (((__PRESCALER__) == TIM_CLEARINPUTPRESCALER_DIV1) || \
                                       ((__PRESCALER__) == TIM_CLEARINPUTPRESCALER_DIV2) || \
                                       ((__PRESCALER__) == TIM_CLEARINPUTPRESCALER_DIV4) || \
                                       ((__PRESCALER__) == TIM_CLEARINPUTPRESCALER_DIV8))

#define IS_TIM_CLEARINPUT_FILTER(__ICFILTER__) ((__ICFILTER__) <= 0xF)

#define IS_TIM_OSSR_STATE(__STATE__) (((__STATE__) == TIM_OSSR_ENABLE) || \
                                      ((__STATE__) == TIM_OSSR_DISABLE))

#define IS_TIM_OSSI_STATE(__STATE__) (((__STATE__) == TIM_OSSI_ENABLE) || \
                                      ((__STATE__) == TIM_OSSI_DISABLE))

#define IS_TIM_LOCK_LEVEL(__LEVEL__) (((__LEVEL__) == TIM_LOCKLEVEL_OFF) || \
                                      ((__LEVEL__) == TIM_LOCKLEVEL_1) || \
                                      ((__LEVEL__) == TIM_LOCKLEVEL_2) || \
                                      ((__LEVEL__) == TIM_LOCKLEVEL_3))

#define IS_TIM_BREAK_STATE(__STATE__) (((__STATE__) == TIM_BREAK_ENABLE) || \
                                       ((__STATE__) == TIM_BREAK_DISABLE))

#define IS_TIM_BREAK_POLARITY(__POLARITY__) (((__POLARITY__) == TIM_BREAKPOLARITY_LOW) || \
                                             ((__POLARITY__) == TIM_BREAKPOLARITY_HIGH))

#define IS_TIM_AUTOMATIC_OUTPUT_STATE(__STATE__) (((__STATE__) == TIM_AUTOMATICOUTPUT_ENABLE) || \
                                                  ((__STATE__) == TIM_AUTOMATICOUTPUT_DISABLE))

#define IS_TIM_TRGO_SOURCE(__SOURCE__) (((__SOURCE__) == TIM_TRGO_RESET) || \
                                        ((__SOURCE__) == TIM_TRGO_ENABLE) || \
                                        ((__SOURCE__) == TIM_TRGO_UPDATE) || \
                                        ((__SOURCE__) == TIM_TRGO_OC1) || \
                                        ((__SOURCE__) == TIM_TRGO_OC1REF) || \
                                        ((__SOURCE__) == TIM_TRGO_OC2REF) || \
                                        ((__SOURCE__) == TIM_TRGO_OC3REF) || \
                                        ((__SOURCE__) == TIM_TRGO_OC4REF))

#define IS_TIM_MSM_STATE(__STATE__) (((__STATE__) == TIM_MASTERSLAVEMODE_ENABLE) || \
                                     ((__STATE__) == TIM_MASTERSLAVEMODE_DISABLE))

#define IS_TIM_TRIGGER_SELECTION(__SELECTION__) (((__SELECTION__) == TIM_TS_ITR0) || \
                                                 ((__SELECTION__) == TIM_TS_ITR1) || \
                                                 ((__SELECTION__) == TIM_TS_ITR2) || \
                                                 ((__SELECTION__) == TIM_TS_ITR3) || \
                                                 ((__SELECTION__) == TIM_TS_TI1F_ED) || \
                                                 ((__SELECTION__) == TIM_TS_TI1FP1) || \
                                                 ((__SELECTION__) == TIM_TS_TI2FP2) || \
                                                 ((__SELECTION__) == TIM_TS_ETRF))

#define IS_TIM_INTERNAL_TGR_SELECTION(SELECTION) (((SELECTION) == TIM_TS_ITR0) || \
                                                      ((SELECTION) == TIM_TS_ITR1) || \
                                                      ((SELECTION) == TIM_TS_ITR2) || \
                                                      ((SELECTION) == TIM_TS_ITR3))

#define IS_TIM_INTERNAL_TGREVENT_SLCTN(__SELECTION__) \
                                                          (((__SELECTION__) == TIM_TS_ITR0) || \
                                                          ((__SELECTION__) == TIM_TS_ITR1) || \
                                                          ((__SELECTION__) == TIM_TS_ITR2) || \
                                                          ((__SELECTION__) == TIM_TS_ITR3) || \
                                                          ((__SELECTION__) == TIM_TS_NONE))

#define IS_TIM_TRIGGERPOLARITY(__POLARITY__)  \
                                    (((__POLARITY__) == TIM_TRIGGERPOLARITY_INVERTED   ) || \
                                    ((__POLARITY__) == TIM_TRIGGERPOLARITY_NONINVERTED) || \
                                    ((__POLARITY__) == TIM_TRIGGERPOLARITY_RISING     ) || \
                                    ((__POLARITY__) == TIM_TRIGGERPOLARITY_FALLING    ) || \
                                    ((__POLARITY__) == TIM_TRIGGERPOLARITY_BOTHEDGE   ))

#define IS_TIM_TRIGGERPRESCALER(__PRESCALER__) (((__PRESCALER__) == TIM_TRIGGERPRESCALER_DIV1) || \
                                               ((__PRESCALER__) == TIM_TRIGGERPRESCALER_DIV2) || \
                                               ((__PRESCALER__) == TIM_TRIGGERPRESCALER_DIV4) || \
                                               ((__PRESCALER__) == TIM_TRIGGERPRESCALER_DIV8))

#define IS_TIM_TRIGGERFILTER(__ICFILTER__)     ((__ICFILTER__) <= 0xF)

#define IS_TIM_TI1SELECTION(__TI1SELECTION__)   (((__TI1SELECTION__) == TIM_TI1SELECTION_CH1) || \
                                      ((__TI1SELECTION__) == TIM_TI1SELECTION_XORCOMBINATION))

#define IS_TIM_DMA_BASE(__BASE__) (((__BASE__) == TIM_DMABASE_CR1) || \
                                   ((__BASE__) == TIM_DMABASE_CR2) || \
                                   ((__BASE__) == TIM_DMABASE_SMCR) || \
                                   ((__BASE__) == TIM_DMABASE_DIER) || \
                                   ((__BASE__) == TIM_DMABASE_SR) || \
                                   ((__BASE__) == TIM_DMABASE_EGR) || \
                                   ((__BASE__) == TIM_DMABASE_CCMR1) || \
                                   ((__BASE__) == TIM_DMABASE_CCMR2) || \
                                   ((__BASE__) == TIM_DMABASE_CCER) || \
                                   ((__BASE__) == TIM_DMABASE_CNT) || \
                                   ((__BASE__) == TIM_DMABASE_PSC) || \
                                   ((__BASE__) == TIM_DMABASE_ARR) || \
                                   ((__BASE__) == TIM_DMABASE_RCR) || \
                                   ((__BASE__) == TIM_DMABASE_CCR1) || \
                                   ((__BASE__) == TIM_DMABASE_CCR2) || \
                                   ((__BASE__) == TIM_DMABASE_CCR3) || \
                                   ((__BASE__) == TIM_DMABASE_CCR4) || \
                                   ((__BASE__) == TIM_DMABASE_BDTR) || \
                                   ((__BASE__) == TIM_DMABASE_DCR) || \
                                   ((__BASE__) == TIM_DMABASE_OR))

#define IS_TIM_DMA_LENGTH(__LENGTH__) (((__LENGTH__) == TIM_DMABURSTLENGTH_1TRANSFER) || \
                                       ((__LENGTH__) == TIM_DMABURSTLENGTH_2TRANSFERS) || \
                                       ((__LENGTH__) == TIM_DMABURSTLENGTH_3TRANSFERS) || \
                                       ((__LENGTH__) == TIM_DMABURSTLENGTH_4TRANSFERS) || \
                                       ((__LENGTH__) == TIM_DMABURSTLENGTH_5TRANSFERS) || \
                                       ((__LENGTH__) == TIM_DMABURSTLENGTH_6TRANSFERS) || \
                                       ((__LENGTH__) == TIM_DMABURSTLENGTH_7TRANSFERS) || \
                                       ((__LENGTH__) == TIM_DMABURSTLENGTH_8TRANSFERS) || \
                                       ((__LENGTH__) == TIM_DMABURSTLENGTH_9TRANSFERS) || \
                                       ((__LENGTH__) == TIM_DMABURSTLENGTH_10TRANSFERS) || \
                                       ((__LENGTH__) == TIM_DMABURSTLENGTH_11TRANSFERS) || \
                                       ((__LENGTH__) == TIM_DMABURSTLENGTH_12TRANSFERS) || \
                                       ((__LENGTH__) == TIM_DMABURSTLENGTH_13TRANSFERS) || \
                                       ((__LENGTH__) == TIM_DMABURSTLENGTH_14TRANSFERS) || \
                                       ((__LENGTH__) == TIM_DMABURSTLENGTH_15TRANSFERS) || \
                                       ((__LENGTH__) == TIM_DMABURSTLENGTH_16TRANSFERS) || \
                                       ((__LENGTH__) == TIM_DMABURSTLENGTH_17TRANSFERS) || \
                                       ((__LENGTH__) == TIM_DMABURSTLENGTH_18TRANSFERS))

#define IS_TIM_IC_FILTER(ICFILTER) ((ICFILTER) <= 0xF)

void TimBaseSetConfig(T_TIM *TIMx, T_TIM_BASE_INIT *Structure);

void TimOc1SetConfig(T_TIM *TIMx, T_TIM_OC_INIT *OC_Config);
void TimOc2SetConfig(T_TIM *TIMx, T_TIM_OC_INIT *OC_Config);
void TimOc3SetConfig(T_TIM *TIMx, T_TIM_OC_INIT *OC_Config);
void TimOc4SetConfig(T_TIM *TIMx, T_TIM_OC_INIT *OC_Config);
void TimCcxChannelCmd(T_TIM* TIMx, T_UINT32 Channel, T_UINT32 ChannelState);

#endif /* _HDULIBSTM32F7XXHALTIM_H_ */

