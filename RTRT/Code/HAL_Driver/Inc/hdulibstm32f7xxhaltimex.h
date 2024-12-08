/*
 ******************************************************************************
 * License Information  :  Howell Instruments, Inc.                           *
 *                         "Licensed Software" and "All rights reserved".     *
 ******************************************************************************
 *  File                : hdulibstm32f7xxhaltimex.h
 *
 *  Description         : Header file of TIM HAL Extension module.
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
 *
 * Additional References : None
 *
 ******************************************************************************
 */


/* Define to prevent recursive inclusion */
#ifndef _HDULIBSTM32F7XXHALTIMEX_H_
#define _HDULIBSTM32F7XXHALTIMEX_H_

/* Includes */
#include "hdulibstm32f7xxhaldef.h"       /*Contains the HAL defination module */
#include "hdulibstm32f746xx.h"           /* CMSIS Cortex-M7 Device Peripheral Access Layer */


/* Exported types */

typedef struct
{

  T_UINT32 IC1Polarity;     /*
                             * Specifies the active edge of the input signal.
                             * This parameter can be a value of @ref TIM_Input_Capture_Polarity
                             */

  T_UINT32 IC1Prescaler;    /*
                             * Specifies the Input Capture Prescaler.
                             * This parameter can be a value of @ref TIM_Input_Capture_Prescaler
                             */

  T_UINT32 IC1Filter;       /*
                             * Specifies the input capture filter.
                             * This parameter can be a number between Min_Data = 0x0
                             * and Max_Data = 0xF
                             */
  T_UINT32 Commutation_Delay;  /*
                                * Specifies the pulse value to be loaded into the Capture
                                * Compare Register.  This parameter can be a number
                                *  between Min_Data = 0x0000 and Max_Data = 0xFFFF
                                */
} T_TIM_HALLSENSOR_INIT;


typedef struct
{
/*
 * Trigger output (TRGO) selection.
 * This parameter can be a value of @ref TIM_Master_Mode_Selection
 */
  T_UINT32  MasterOutputTrigger;

/*
 * Trigger output2 (TRGO2) selection
 * This parameter can be a value of @ref TIMEx_Master_Mode_Selection_2
 */
  T_UINT32  MasterOutputTrigger2;
/*
 * Master/slave mode selection.
 * This parameter can be a value of @ref TIM_Master_Slave_Mode
 */
  T_UINT32  MasterSlaveMode;

}T_TIM_MASTERCONFIG;


typedef struct
{
 /*
  * TIM off state in run mode.
  * This parameter can be a value of @ref TIM_OSSR_Off_State_Selection_for_Run_mode_state
  */

  T_UINT32 OffStateRunMode;

  /*
   * TIM off state in IDLE mode.
   * This parameter can be a value of @ref TIM_OSSI_Off_State_Selection_for_Idle_mode_state
   */

  T_UINT32 OffStateIDLEMode;

  /*
   * TIM Lock level.
   * This parameter can be a value of @ref TIM_Lock_level
   */

  T_UINT32 LockLevel;

   /*
    * TIM dead Time.
    * This parameter can be a number between Min_Data = 0x00 and Max_Data = 0xFF
    */

  T_UINT32 DeadTime;

  /*
   * TIM Break State.
   * This parameter can be a value of @ref TIM_Break_Input_enable_disable
   */

  T_UINT32 BreakState;

  /*
   * TIM Break input polarity.
   * This parameter can be a value of @ref TIM_Break_Polarity
   */

  T_UINT32 BreakPolarity;

  /*
   * Specifies the break input filter.
   * This parameter can be a number between Min_Data = 0x0 and Max_Data = 0xF
   */

  T_UINT32 BreakFilter;

   /*
    * TIM Break2 State
    * This parameter can be a value of @ref TIMEx_Break2_Input_enable_disable
    */

  T_UINT32 Break2State;

 /*
  * TIM Break2 input polarity
  *  This parameter can be a value of @ref TIMEx_Break2_Polarity
  */

  T_UINT32 Break2Polarity;

 /*
  * TIM break2 input filter.
  * This parameter can be a number between Min_Data = 0x0 and Max_Data = 0xF
  */

  T_UINT32 Break2Filter;

  /*
   * TIM Automatic Output Enable state
   * This parameter can be a value of @ref TIM_AOE_Bit_Set_Reset
   */

  T_UINT32 AutomaticOutput;
} T_TIM_BREAD_DEAD_TIME;

#define TIM_CHANNEL_1                      ((T_UINT32)0x0000U)
#define TIM_CHANNEL_2                      ((T_UINT32)0x0004U)
#define TIM_CHANNEL_3                      ((T_UINT32)0x0008U)
#define TIM_CHANNEL_4                      ((T_UINT32)0x000CU)
#define TIM_CHANNEL_5                      ((T_UINT32)0x0010U)
#define TIM_CHANNEL_6                      ((T_UINT32)0x0014U)
#define TIM_CHANNEL_ALL                    ((T_UINT32)0x003CU)

#define TIM_OCMODE_TIMING                   ((T_UINT32)0x0000U)
#define TIM_OCMODE_ACTIVE                   ((T_UINT32)TIM_CCMR1_OC1M_0)
#define TIM_OCMODE_INACTIVE                 ((T_UINT32)TIM_CCMR1_OC1M_1)
#define TIM_OCMODE_TOGGLE                   ((T_UINT32)TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_0)
#define TIM_OCMODE_PWM1                     ((T_UINT32)TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1)
#define TIM_OCMODE_PWM2                     ((T_UINT32)TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1 |\
                                             TIM_CCMR1_OC1M_0)
#define TIM_OCMODE_FORCED_ACTIVE            ((T_UINT32)TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_0)
#define TIM_OCMODE_FORCED_INACTIVE          ((T_UINT32)TIM_CCMR1_OC1M_2)

#define TIM_OCMODE_RETRIGERRABLE_OPM1      ((T_UINT32)TIM_CCMR1_OC1M_3)
#define TIM_OCMODE_RETRIGERRABLE_OPM2      ((T_UINT32)TIM_CCMR1_OC1M_3 | TIM_CCMR1_OC1M_0)
#define TIM_OCMODE_COMBINED_PWM1           ((T_UINT32)TIM_CCMR1_OC1M_3 | TIM_CCMR1_OC1M_2)
#define TIM_OCMODE_COMBINED_PWM2           ((T_UINT32)TIM_CCMR1_OC1M_3 | TIM_CCMR1_OC1M_0 |\
                                             TIM_CCMR1_OC1M_2)
#define TIM_OCMODE_ASSYMETRIC_PWM1         ((T_UINT32)TIM_CCMR1_OC1M_3 | TIM_CCMR1_OC1M_1 | \
                                             TIM_CCMR1_OC1M_2)
#define TIM_OCMODE_ASSYMETRIC_PWM2         ((T_UINT32)TIM_CCMR1_OC1M_3 | TIM_CCMR1_OC1M)

#define TIM_TIM2_TIM8_TRGO                     (0x00000000U)
#define TIM_TIM2_ETH_PTP                       (0x00000400U)
#define TIM_TIM2_USBFS_SOF                     (0x00000800U)
#define TIM_TIM2_USBHS_SOF                     (0x00000C00U)
#define TIM_TIM5_GPIO                          (0x00000000U)
#define TIM_TIM5_LSI                           (0x00000040U)
#define TIM_TIM5_LSE                           (0x00000080U)
#define TIM_TIM5_RTC                           (0x000000C0U)
#define TIM_TIM11_GPIO                         (0x00000000U)
#define TIM_TIM11_SPDIFRX                      (0x00000001U)
#define TIM_TIM11_HSE                          (0x00000002U)
#define TIM_TIM11_MCO1                         (0x00000003U)

#define TIM_CLEARINPUTSOURCE_ETR            ((T_UINT32)0x0001U)
#define TIM_CLEARINPUTSOURCE_OCREFCLR       ((T_UINT32)0x0002U)
#define TIM_CLEARINPUTSOURCE_NONE           ((T_UINT32)0x0000U)

#define TIM_BREAK2_DISABLE         ((T_UINT32)0x00000000U)
#define TIM_BREAK2_ENABLE          ((T_UINT32)TIM_BDTR_BK2E)

#define TIM_BREAK2POLARITY_LOW        ((T_UINT32)0x00000000U)
#define TIM_BREAK2POLARITY_HIGH       (TIM_BDTR_BK2P)

/*No effect of OC5REF on OC1REFC, OC2REFC and OC3REFC */
#define TIM_GROUPCH5_NONE       ((T_UINT32)0x00000000U)
 /*OC1REFC is the logical AND of OC1REFC and OC5REF */
#define TIM_GROUPCH5_OC1REFC    (TIM_CCR5_GC5C1)
/*OC2REFC is the logical AND of OC2REFC and OC5REF */
#define TIM_GROUPCH5_OC2REFC    (TIM_CCR5_GC5C2)
 /*OC3REFC is the logical AND of OC3REFC and OC5REF */
#define TIM_GROUPCH5_OC3REFC    (TIM_CCR5_GC5C3)

#define  TIM_TRGO2_RESET                          ((T_UINT32)0x00000000U)
#define  TIM_TRGO2_ENABLE                         ((T_UINT32)(TIM_CR2_MMS2_0))
#define  TIM_TRGO2_UPDATE                         ((T_UINT32)(TIM_CR2_MMS2_1))
#define  TIM_TRGO2_OC1                            ((T_UINT32)(TIM_CR2_MMS2_1 | TIM_CR2_MMS2_0))
#define  TIM_TRGO2_OC1REF                         ((T_UINT32)(TIM_CR2_MMS2_2))
#define  TIM_TRGO2_OC2REF                         ((T_UINT32)(TIM_CR2_MMS2_2 | TIM_CR2_MMS2_0))
#define  TIM_TRGO2_OC3REF                         ((T_UINT32)(TIM_CR2_MMS2_2 | TIM_CR2_MMS2_1))
#define  TIM_TRGO2_OC4REF                         ((T_UINT32)(TIM_CR2_MMS2_2 | TIM_CR2_MMS2_1 |\
                                                   TIM_CR2_MMS2_0))
#define  TIM_TRGO2_OC5REF                         ((T_UINT32)(TIM_CR2_MMS2_3))
#define  TIM_TRGO2_OC6REF                         ((T_UINT32)(TIM_CR2_MMS2_3 | TIM_CR2_MMS2_0))
#define  TIM_TRGO2_OC4REF_RISINGFALLING           ((T_UINT32)(TIM_CR2_MMS2_3 | TIM_CR2_MMS2_1))
#define  TIM_TRGO2_OC6REF_RISINGFALLING           ((T_UINT32)(TIM_CR2_MMS2_3 | TIM_CR2_MMS2_1 | \
                                                   TIM_CR2_MMS2_0))
#define  TIM_TRG2_OC4_OC6_RISNG                    ((T_UINT32)(TIM_CR2_MMS2_3 | TIM_CR2_MMS2_2))
#define  TIM_TRG2_OC4_OC6_FALLING                  ((T_UINT32)(TIM_CR2_MMS2_3 | TIM_CR2_MMS2_2 |\
                                                   TIM_CR2_MMS2_0))
#define  TIM_TRG2_OC5_OC6_RISING                   ((T_UINT32)(TIM_CR2_MMS2_3 | TIM_CR2_MMS2_2 |\
                                                   TIM_CR2_MMS2_1))
#define  TIM_TRG2_OC5_OC6_FALLING                  ((T_UINT32)(TIM_CR2_MMS2_3 | TIM_CR2_MMS2_2 |\
                                                   TIM_CR2_MMS2_1 | TIM_CR2_MMS2_0))

#define TIM_SLAVEMODE_DISABLE                ((T_UINT32)0x0000U)
#define TIM_SLAVEMODE_RESET                  ((T_UINT32)(TIM_SMCR_SMS_2))
#define TIM_SLAVEMODE_GATED                  ((T_UINT32)(TIM_SMCR_SMS_2 | TIM_SMCR_SMS_0))
#define TIM_SLAVEMODE_TRIGGER                ((T_UINT32)(TIM_SMCR_SMS_2 | TIM_SMCR_SMS_1))
#define TIM_SLAVEMODE_EXTERNAL1              ((T_UINT32)(TIM_SMCR_SMS_2 | TIM_SMCR_SMS_1 |\
                                             TIM_SMCR_SMS_0))
#define TIM_SLAVE_COMBINED_RESET  ((T_UINT32)(TIM_SMCR_SMS_3))

/* Exported macro */

#define __HAL_TIM_SET_COMPARE(__HANDLE__, __CHANNEL__, __COMPARE__) \
(((__CHANNEL__) == TIM_CHANNEL_1) ? ((__HANDLE__)->Instance->CCR1 = (__COMPARE__)) :\
 ((__CHANNEL__) == TIM_CHANNEL_2) ? ((__HANDLE__)->Instance->CCR2 = (__COMPARE__)) :\
 ((__CHANNEL__) == TIM_CHANNEL_3) ? ((__HANDLE__)->Instance->CCR3 = (__COMPARE__)) :\
 ((__CHANNEL__) == TIM_CHANNEL_4) ? ((__HANDLE__)->Instance->CCR4 = (__COMPARE__)) :\
 ((__CHANNEL__) == TIM_CHANNEL_5) ? ((__HANDLE__)->Instance->CCR5 = (__COMPARE__)) :\
 ((__HANDLE__)->Instance->CCR6 = (__COMPARE__)))


#define __HAL_TIM_GET_COMPARE(__HANDLE__, __CHANNEL__) \
(((__CHANNEL__) == TIM_CHANNEL_1) ? ((__HANDLE__)->Instance->CCR1) :\
 ((__CHANNEL__) == TIM_CHANNEL_2) ? ((__HANDLE__)->Instance->CCR2) :\
 ((__CHANNEL__) == TIM_CHANNEL_3) ? ((__HANDLE__)->Instance->CCR3) :\
 ((__CHANNEL__) == TIM_CHANNEL_4) ? ((__HANDLE__)->Instance->CCR4) :\
 ((__CHANNEL__) == TIM_CHANNEL_5) ? ((__HANDLE__)->Instance->CCR5) :\
 ((__HANDLE__)->Instance->CCR6))

#define IS_TIM_CHANNELS(CHANNEL) (((CHANNEL) == TIM_CHANNEL_1) || \
                                  ((CHANNEL) == TIM_CHANNEL_2) || \
                                  ((CHANNEL) == TIM_CHANNEL_3) || \
                                  ((CHANNEL) == TIM_CHANNEL_4) || \
                                  ((CHANNEL) == TIM_CHANNEL_5) || \
                                  ((CHANNEL) == TIM_CHANNEL_6) || \
                                  ((CHANNEL) == TIM_CHANNEL_ALL))

#define IS_TIM_PWMI_CHANNELS(CHANNEL) (((CHANNEL) == TIM_CHANNEL_1) || \
                                       ((CHANNEL) == TIM_CHANNEL_2))

#define IS_TIM_OPM_CHANNELS(CHANNEL) (((CHANNEL) == TIM_CHANNEL_1) || \
                                      ((CHANNEL) == TIM_CHANNEL_2))

#define IS_TIM_COMPLEMENTARY_CHANNELS(CHANNEL) (((CHANNEL) == TIM_CHANNEL_1) || \
                                                ((CHANNEL) == TIM_CHANNEL_2) || \
                                                ((CHANNEL) == TIM_CHANNEL_3))
#define IS_TIM_PWM_MODE(MODE) (((MODE) == TIM_OCMODE_PWM1)               || \
                          ((MODE) == TIM_OCMODE_PWM2)               || \
                               ((MODE) == TIM_OCMODE_COMBINED_PWM1)      || \
                               ((MODE) == TIM_OCMODE_COMBINED_PWM2)      || \
                               ((MODE) == TIM_OCMODE_ASSYMETRIC_PWM1)    || \
                               ((MODE) == TIM_OCMODE_ASSYMETRIC_PWM2))

#define IS_TIM_OC_MODE(MODE) (((MODE) == TIM_OCMODE_TIMING)             || \
                             ((MODE) == TIM_OCMODE_ACTIVE)             || \
                             ((MODE) == TIM_OCMODE_INACTIVE)           || \
                             ((MODE) == TIM_OCMODE_TOGGLE)             || \
                             ((MODE) == TIM_OCMODE_FORCED_ACTIVE)      || \
                             ((MODE) == TIM_OCMODE_FORCED_INACTIVE)    || \
                             ((MODE) == TIM_OCMODE_RETRIGERRABLE_OPM1) || \
                             ((MODE) == TIM_OCMODE_RETRIGERRABLE_OPM2))
#define IS_TIM_REMAP(__TIM_REMAP__)  (((__TIM_REMAP__) == TIM_TIM2_TIM8_TRGO)||\
                                      ((__TIM_REMAP__) == TIM_TIM2_ETH_PTP)||\
                                      ((__TIM_REMAP__) == TIM_TIM2_USBFS_SOF)||\
                                      ((__TIM_REMAP__) == TIM_TIM2_USBHS_SOF)||\
                                      ((__TIM_REMAP__) == TIM_TIM5_GPIO)||\
                                      ((__TIM_REMAP__) == TIM_TIM5_LSI)||\
                                      ((__TIM_REMAP__) == TIM_TIM5_LSE)||\
                                      ((__TIM_REMAP__) == TIM_TIM5_RTC)||\
                                      ((__TIM_REMAP__) == TIM_TIM11_GPIO)||\
                                      ((__TIM_REMAP__) == TIM_TIM11_SPDIFRX)||\
                                      ((__TIM_REMAP__) == TIM_TIM11_HSE)||\
                                      ((__TIM_REMAP__) == TIM_TIM11_MCO1))
#define IS_TIM_DEADTIME(__DEADTIME__)      ((__DEADTIME__) <= 0xFF)
#define IS_TIM_BREAK_FILTER(__FILTER__) ((__FILTER__) <= 0xF)
#define IS_TIM_CLEARINPUT_SOURCE(MODE) (((MODE) == TIM_CLEARINPUTSOURCE_ETR)      || \
                                        ((MODE) == TIM_CLEARINPUTSOURCE_OCREFCLR)  || \
                                        ((MODE) == TIM_CLEARINPUTSOURCE_NONE))
#define IS_TIM_BREAK2_STATE(STATE) (((STATE) == TIM_BREAK2_ENABLE) || \
                                    ((STATE) == TIM_BREAK2_DISABLE))
#define IS_TIM_BREAK2_POLARITY(__POLARITY__) (((__POLARITY__) == TIM_BREAK2POLARITY_LOW) || \
                                              ((__POLARITY__) == TIM_BREAK2POLARITY_HIGH))
#define IS_TIM_GROUPCH5(OCREF) ((((OCREF) & 0x1FFFFFFF) == 0x00000000))
#define IS_TIM_TRGO2_SOURCE(SOURCE) (((SOURCE) == TIM_TRGO2_RESET)                        || \
                                     ((SOURCE) == TIM_TRGO2_ENABLE)                       || \
                                     ((SOURCE) == TIM_TRGO2_UPDATE)                       || \
                                     ((SOURCE) == TIM_TRGO2_OC1)                          || \
                                     ((SOURCE) == TIM_TRGO2_OC1REF)                       || \
                                     ((SOURCE) == TIM_TRGO2_OC2REF)                       || \
                                     ((SOURCE) == TIM_TRGO2_OC3REF)                       || \
                                     ((SOURCE) == TIM_TRGO2_OC3REF)                       || \
                                     ((SOURCE) == TIM_TRGO2_OC4REF)                       || \
                                     ((SOURCE) == TIM_TRGO2_OC5REF)                       || \
                                     ((SOURCE) == TIM_TRGO2_OC6REF)                       || \
                                     ((SOURCE) == TIM_TRGO2_OC4REF_RISINGFALLING)         || \
                                     ((SOURCE) == TIM_TRGO2_OC6REF_RISINGFALLING)         || \
                                     ((SOURCE) == TIM_TRG2_OC4_OC6_RISNG)  || \
                                     ((SOURCE) == TIM_TRG2_OC4_OC6_FALLING) || \
                                     ((SOURCE) == TIM_TRG2_OC5_OC6_RISING)  || \
                                     ((SOURCE) == TIM_TRG2_OC5_OC6_FALLING))
#define IS_TIM_SLAVE_MODE(MODE) (((MODE) == TIM_SLAVEMODE_DISABLE)   || \
                                 ((MODE) == TIM_SLAVEMODE_RESET)     || \
                                 ((MODE) == TIM_SLAVEMODE_GATED)     || \
                                 ((MODE) == TIM_SLAVEMODE_TRIGGER)   || \
                                 ((MODE) == TIM_SLAVEMODE_EXTERNAL1) || \
                                 ((MODE) == TIM_SLAVE_COMBINED_RESET))

#endif /* _HDULIBSTM32F7XXHALTIMEX_H_ */
