/*
 ******************************************************************************
 * License Information  :  Howell Instruments, Inc.                           *
 *                         "Licensed Software" and "All rights reserved".     *
 ******************************************************************************
 *  File                : hdulibstm32f7xxhalrcc.h
 *
 *  Description         : Header file of RCC HAL module.
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
 *      1.2          Shilpa A R      02-Sep-2017          100028
 *      1.3          Shilpa A R      02-Oct-2017          100064
 *      1.4          Divya G P       09-Oct-2017          100064
 *
 * Additional References : None
 *
 ******************************************************************************
 */

/* Define to prevent recursive inclusion */
#ifndef _HDULIBSTM32F7XXHALRCC_H_
#define _HDULIBSTM32F7XXHALRCC_H_

/* Includes */
#include "hdulibstm32f7xxhalrccex.h"   /* Header files for RCC EX HAL module*/
#include "hdulibbasictypes.h"          /* Define standard data types */
#include "hdulibstm32f7xxhaldef.h"     /* Header file of CORTEX HAL module */
#include "hdulibstm32f7xxhalconf.h"    /* provides HAL configurations. */

/* Exported types */

typedef struct
{
   /* The oscillators to be configured.This parameter can be a value of @ref RCC_Oscillator_Type*/
   T_UINT32 OscillatorType;

   /* The new state of the HSE.This parameter can be a value of @ref RCC_HSE_Config */
   T_UINT32 HSEState;

   /* The new state of the LSE.This parameter can be a value of @ref RCC_LSE_Config */
   T_UINT32 LSEState;

   /* The new state of the HSI.This parameter can be a value of @ref RCC_HSI_Config */
   T_UINT32 HSIState;

   /*
    * The HSI calibration trimming value (default is RCC_HSICALIBRATION_DEFAULT).
    * This parameter must be a number between Min_Data = 0x00 and Max_Data = 0x1F
    */
   T_UINT32 HSICalibrationValue;

   /* The new state of the LSI. This parameter can be a value of @ref RCC_LSI_Config */
   T_UINT32 LSIState;

   T_RCC_PLL_INIT PLL;        /* PLL structure parameters */

}T_RCC_OSC_INIT;

typedef struct
{
   /* The clock to be configured. This parameter can be a value of @ref RCC_System_Clock_Type */
   T_UINT32 ClockType;

   /*
    * The clock source (SYSCLKS) used as system clock.
    * This parameter can be a value of @ref RCC_System_Clock_Source
    */
   T_UINT32 SYSCLKSource;

   /*
    * The AHB clock (HCLK) divider. This clock is derived from the system clock (SYSCLK).
    * This parameter can be a value of @ref RCC_AHB_Clock_Source
    */
   T_UINT32 AHBCLKDivider;

   /*
    * The APB1 clock (PCLK1) divider. This clock is derived from the AHB clock (HCLK).
    * This parameter can be a value of @ref RCC_APB1_APB2_Clock_Source
    */
   T_UINT32 APB1CLKDivider;

   /*
    * The APB2 clock (PCLK2) divider. This clock is derived from the AHB clock (HCLK).
    * This parameter can be a value of @ref RCC_APB1_APB2_Clock_Source
    */
   T_UINT32 APB2CLKDivider;

}T_RCC_CLK_INIT;

#define RCC_OSCILLATORTYPE_NONE            ((T_UINT32)0x00000000U)
#define RCC_OSCILLATORTYPE_HSE             ((T_UINT32)0x00000001U)
#define RCC_OSCILLATORTYPE_HSI             ((T_UINT32)0x00000002U)
#define RCC_OSCILLATORTYPE_LSE             ((T_UINT32)0x00000004U)
#define RCC_OSCILLATORTYPE_LSI             ((T_UINT32)0x00000008U)

#define RCC_HSE_OFF                      ((T_UINT32)0x00000000U)
#define RCC_HSE_ON                       RCC_CR_HSEON
#define RCC_HSE_BYPASS                   ((T_UINT32)(RCC_CR_HSEBYP | RCC_CR_HSEON))

#define RCC_LSE_OFF                    ((T_UINT32)0x00000000U)
#define RCC_LSE_ON                     RCC_BDCR_LSEON
#define RCC_LSE_BYPASS                 ((T_UINT32)(RCC_BDCR_LSEBYP | RCC_BDCR_LSEON))

#define RCC_HSI_OFF                    ((T_UINT32)0x00000000U)
#define RCC_HSI_ON                     RCC_CR_HSION

/* Default HSI calibration trimming value */
#define RCC_HSICALIBRATION_DEFAULT     ((T_UINT32)0x10U)

#define RCC_LSI_OFF                    ((T_UINT32)0x00000000U)
#define RCC_LSI_ON                     RCC_CSR_LSION

#define RCC_PLL_NONE                   ((T_UINT32)0x00000000U)
#define RCC_PLL_OFF                    ((T_UINT32)0x00000001U)
#define RCC_PLL_ON                     ((T_UINT32)0x00000002U)
#define RCC_PLLP_DIV2                  ((T_UINT32)0x00000002U)
#define RCC_PLLP_DIV4                  ((T_UINT32)0x00000004U)
#define RCC_PLLP_DIV6                  ((T_UINT32)0x00000006U)
#define RCC_PLLP_DIV8                  ((T_UINT32)0x00000008U)
#define RCC_PLLSOURCE_HSI                RCC_PLLCFGR_PLLSRC_HSI
#define RCC_PLLSOURCE_HSE                RCC_PLLCFGR_PLLSRC_HSE
#define RCC_CLOCKTYPE_SYSCLK             ((T_UINT32)0x00000001U)
#define RCC_CLOCKTYPE_HCLK               ((T_UINT32)0x00000002U)
#define RCC_CLOCKTYPE_PCLK1              ((T_UINT32)0x00000004U)
#define RCC_CLOCKTYPE_PCLK2              ((T_UINT32)0x00000008U)
#define RCC_SYSCLKSOURCE_HSI             RCC_CFGR_SW_HSI
#define RCC_SYSCLKSOURCE_HSE             RCC_CFGR_SW_HSE
#define RCC_SYSCLKSOURCE_PLLCLK          RCC_CFGR_SW_PLL
#define RCC_SYSCLKSOURCE_STATUS_HSI      RCC_CFGR_SWS_HSI   /* HSI used as system clock */
#define RCC_SYSCLKSOURCE_STATUS_HSE      RCC_CFGR_SWS_HSE   /* HSE used as system clock */
#define RCC_SYSCLKSOURCE_STATUS_PLLCLK   RCC_CFGR_SWS_PLL   /* PLL used as system clock */
#define RCC_SYSCLK_DIV1                  RCC_CFGR_HPRE_DIV1
#define RCC_SYSCLK_DIV2                  RCC_CFGR_HPRE_DIV2
#define RCC_SYSCLK_DIV4                  RCC_CFGR_HPRE_DIV4
#define RCC_SYSCLK_DIV8                  RCC_CFGR_HPRE_DIV8
#define RCC_SYSCLK_DIV16                 RCC_CFGR_HPRE_DIV16
#define RCC_SYSCLK_DIV64                 RCC_CFGR_HPRE_DIV64
#define RCC_SYSCLK_DIV128                RCC_CFGR_HPRE_DIV128
#define RCC_SYSCLK_DIV256                RCC_CFGR_HPRE_DIV256
#define RCC_SYSCLK_DIV512                RCC_CFGR_HPRE_DIV512
#define RCC_HCLK_DIV1                    RCC_CFGR_PPRE1_DIV1
#define RCC_HCLK_DIV2                    RCC_CFGR_PPRE1_DIV2
#define RCC_HCLK_DIV4                    RCC_CFGR_PPRE1_DIV4
#define RCC_HCLK_DIV8                    RCC_CFGR_PPRE1_DIV8
#define RCC_HCLK_DIV16                   RCC_CFGR_PPRE1_DIV16
#define RCC_RTCCLKSOURCE_LSE             ((T_UINT32)0x00000100U)
#define RCC_RTCCLKSOURCE_LSI             ((T_UINT32)0x00000200U)
#define RCC_RTCCLKSOURCE_HSE_DIV2        ((T_UINT32)0x00020300U)
#define RCC_RTCCLKSOURCE_HSE_DIV3        ((T_UINT32)0x00030300U)
#define RCC_RTCCLKSOURCE_HSE_DIV4        ((T_UINT32)0x00040300U)
#define RCC_RTCCLKSOURCE_HSE_DIV5        ((T_UINT32)0x00050300U)
#define RCC_RTCCLKSOURCE_HSE_DIV6        ((T_UINT32)0x00060300U)
#define RCC_RTCCLKSOURCE_HSE_DIV7        ((T_UINT32)0x00070300U)
#define RCC_RTCCLKSOURCE_HSE_DIV8        ((T_UINT32)0x00080300U)
#define RCC_RTCCLKSOURCE_HSE_DIV9        ((T_UINT32)0x00090300U)
#define RCC_RTCCLKSOURCE_HSE_DIV10       ((T_UINT32)0x000A0300U)
#define RCC_RTCCLKSOURCE_HSE_DIV11       ((T_UINT32)0x000B0300U)
#define RCC_RTCCLKSOURCE_HSE_DIV12       ((T_UINT32)0x000C0300U)
#define RCC_RTCCLKSOURCE_HSE_DIV13       ((T_UINT32)0x000D0300U)
#define RCC_RTCCLKSOURCE_HSE_DIV14       ((T_UINT32)0x000E0300U)
#define RCC_RTCCLKSOURCE_HSE_DIV15       ((T_UINT32)0x000F0300U)
#define RCC_RTCCLKSOURCE_HSE_DIV16       ((T_UINT32)0x00100300U)
#define RCC_RTCCLKSOURCE_HSE_DIV17       ((T_UINT32)0x00110300U)
#define RCC_RTCCLKSOURCE_HSE_DIV18       ((T_UINT32)0x00120300U)
#define RCC_RTCCLKSOURCE_HSE_DIV19       ((T_UINT32)0x00130300U)
#define RCC_RTCCLKSOURCE_HSE_DIV20       ((T_UINT32)0x00140300U)
#define RCC_RTCCLKSOURCE_HSE_DIV21       ((T_UINT32)0x00150300U)
#define RCC_RTCCLKSOURCE_HSE_DIV22       ((T_UINT32)0x00160300U)
#define RCC_RTCCLKSOURCE_HSE_DIV23       ((T_UINT32)0x00170300U)
#define RCC_RTCCLKSOURCE_HSE_DIV24       ((T_UINT32)0x00180300U)
#define RCC_RTCCLKSOURCE_HSE_DIV25       ((T_UINT32)0x00190300U)
#define RCC_RTCCLKSOURCE_HSE_DIV26       ((T_UINT32)0x001A0300U)
#define RCC_RTCCLKSOURCE_HSE_DIV27       ((T_UINT32)0x001B0300U)
#define RCC_RTCCLKSOURCE_HSE_DIV28       ((T_UINT32)0x001C0300U)
#define RCC_RTCCLKSOURCE_HSE_DIV29       ((T_UINT32)0x001D0300U)
#define RCC_RTCCLKSOURCE_HSE_DIV30       ((T_UINT32)0x001E0300U)
#define RCC_RTCCLKSOURCE_HSE_DIV31       ((T_UINT32)0x001F0300U)
#define RCC_MCO1                         ((T_UINT32)0x00000000U)
#define RCC_MCO2                         ((T_UINT32)0x00000001U)
#define RCC_MCO1SOURCE_HSI               ((T_UINT32)0x00000000U)
#define RCC_MCO1SOURCE_LSE               RCC_CFGR_MCO1_0
#define RCC_MCO1SOURCE_HSE               RCC_CFGR_MCO1_1
#define RCC_MCO1SOURCE_PLLCLK            RCC_CFGR_MCO1
#define RCC_MCO2SOURCE_SYSCLK            ((T_UINT32)0x00000000U)
#define RCC_MCO2SOURCE_PLLI2SCLK         RCC_CFGR_MCO2_0
#define RCC_MCO2SOURCE_HSE               RCC_CFGR_MCO2_1
#define RCC_MCO2SOURCE_PLLCLK            RCC_CFGR_MCO2
#define RCC_MCODIV_1                    ((T_UINT32)0x00000000U)
#define RCC_MCODIV_2                    RCC_CFGR_MCO1PRE_2
#define RCC_MCODIV_3                    ((T_UINT32)RCC_CFGR_MCO1PRE_0 | RCC_CFGR_MCO1PRE_2)
#define RCC_MCODIV_4                    ((T_UINT32)RCC_CFGR_MCO1PRE_1 | RCC_CFGR_MCO1PRE_2)
#define RCC_MCODIV_5                    RCC_CFGR_MCO1PRE
#define RCC_IT_LSIRDY                    ((T_UINT8)0x01U)
#define RCC_IT_LSERDY                    ((T_UINT8)0x02U)
#define RCC_IT_HSIRDY                    ((T_UINT8)0x04U)
#define RCC_IT_HSERDY                    ((T_UINT8)0x08U)
#define RCC_IT_PLLRDY                    ((T_UINT8)0x10U)
#define RCC_IT_PLLI2SRDY                 ((T_UINT8)0x20U)
#define RCC_IT_PLLSAIRDY                 ((T_UINT8)0x40U)
#define RCC_IT_CSS                       ((T_UINT8)0x80U)

/* Flags in the CR register */
#define RCC_FLAG_HSIRDY                  ((T_UINT8)0x21U)
#define RCC_FLAG_HSERDY                  ((T_UINT8)0x31U)
#define RCC_FLAG_PLLRDY                  ((T_UINT8)0x39U)
#define RCC_FLAG_PLLI2SRDY               ((T_UINT8)0x3BU)
#define RCC_FLAG_PLLSAIRDY               ((T_UINT8)0x3CU)

/* Flags in the BDCR register */
#define RCC_FLAG_LSERDY                  ((T_UINT8)0x41U)

/* Flags in the CSR register */
#define RCC_FLAG_LSIRDY                  ((T_UINT8)0x61U)
#define RCC_FLAG_BORRST                  ((T_UINT8)0x79U)
#define RCC_FLAG_PINRST                  ((T_UINT8)0x7AU)
#define RCC_FLAG_PORRST                  ((T_UINT8)0x7BU)
#define RCC_FLAG_SFTRST                  ((T_UINT8)0x7CU)
#define RCC_FLAG_IWDGRST                 ((T_UINT8)0x7DU)
#define RCC_FLAG_WWDGRST                 ((T_UINT8)0x7EU)
#define RCC_FLAG_LPWRRST                 ((T_UINT8)0x7FU)
#define RCC_LSEDRIVE_LOW                 ((T_UINT32)0x00000000U)
#define RCC_LSEDRIVE_MEDIUMLOW           RCC_BDCR_LSEDRV_1
#define RCC_LSEDRIVE_MEDIUMHIGH          RCC_BDCR_LSEDRV_0
#define RCC_LSEDRIVE_HIGH                RCC_BDCR_LSEDRV

#define __HAL_RCC_CRC_CLK_ENABLE()   do { \
                                        __IO T_UINT32 tmpreg; \
                                        SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_CRCEN);\
                                        /* Delay after an RCC peripheral clock enabling */ \
                                        tmpreg = READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_CRCEN);\
                                        UNUSED(tmpreg); \
                                      } while(0)

#define __HAL_RCC_DMA1_CLK_ENABLE()   do { \
                                        __IO T_UINT32 tmpreg; \
                                        SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_DMA1EN);\
                                        /* Delay after an RCC peripheral clock enabling */ \
                                        tmpreg = READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_DMA1EN);\
                                        UNUSED(tmpreg); \
                                      } while(0)

#define __HAL_RCC_CRC_CLK_DISABLE()          (RCC->AHB1ENR &= ~(RCC_AHB1ENR_CRCEN))
#define __HAL_RCC_DMA1_CLK_DISABLE()         (RCC->AHB1ENR &= ~(RCC_AHB1ENR_DMA1EN))


#define __HAL_RCC_WWDG_CLK_ENABLE()   do { \
                                        __IO T_UINT32 tmpreg; \
                                        SET_BIT(RCC->APB1ENR, RCC_APB1ENR_WWDGEN);\
                                        /* Delay after an RCC peripheral clock enabling */ \
                                        tmpreg = READ_BIT(RCC->APB1ENR, RCC_APB1ENR_WWDGEN);\
                                        UNUSED(tmpreg); \
                                      } while(0)

#define __HAL_RCC_PWR_CLK_ENABLE()   do { \
                                        __IO T_UINT32 tmpreg; \
                                        SET_BIT(RCC->APB1ENR, RCC_APB1ENR_PWREN);\
                                        /* Delay after an RCC peripheral clock enabling */ \
                                        tmpreg = READ_BIT(RCC->APB1ENR, RCC_APB1ENR_PWREN);\
                                        UNUSED(tmpreg); \
                                      } while(0)

#define __HAL_RCC_WWDG_CLK_DISABLE()   (RCC->APB1ENR &= ~(RCC_APB1ENR_WWDGEN))
#define __HAL_RCC_PWR_CLK_DISABLE()    (RCC->APB1ENR &= ~(RCC_APB1ENR_PWREN))

#define __HAL_RCC_SYSCFG_CLK_ENABLE()   do { \
                                        __IO T_UINT32 tmpreg; \
                                        SET_BIT(RCC->APB2ENR, RCC_APB2ENR_SYSCFGEN);\
                                        /* Delay after an RCC peripheral clock enabling */ \
                                        tmpreg = READ_BIT(RCC->APB2ENR, RCC_APB2ENR_SYSCFGEN);\
                                        UNUSED(tmpreg); \
                                      } while(0)

#define __HAL_RCC_SYSCFG_CLK_DISABLE() (RCC->APB2ENR &= ~(RCC_APB2ENR_SYSCFGEN))


#define __HAL_RCC_CRC_IS_CLK_ENABLED()         ((RCC->AHB1ENR & (RCC_AHB1ENR_CRCEN)) != RESET)
#define __HAL_RCC_DMA1_IS_CLK_ENABLED()        ((RCC->AHB1ENR & (RCC_AHB1ENR_DMA1EN)) != RESET)

#define __HAL_RCC_CRC_IS_CLK_DISABLED()        ((RCC->AHB1ENR & (RCC_AHB1ENR_CRCEN)) == RESET)
#define __HAL_RCC_DMA1_IS_CLK_DISABLED()       ((RCC->AHB1ENR & (RCC_AHB1ENR_DMA1EN)) == RESET)

#define __HAL_RCC_WWDG_IS_CLK_ENABLED()        ((RCC->APB1ENR & (RCC_APB1ENR_WWDGEN)) != RESET)
#define __HAL_RCC_PWR_IS_CLK_ENABLED()         ((RCC->APB1ENR & (RCC_APB1ENR_PWREN)) != RESET)

#define __HAL_RCC_WWDG_IS_CLK_DISABLED()       ((RCC->APB1ENR & (RCC_APB1ENR_WWDGEN)) == RESET)
#define __HAL_RCC_PWR_IS_CLK_DISABLED()        ((RCC->APB1ENR & (RCC_APB1ENR_PWREN)) == RESET)

#define __HAL_RCC_SYSCFG_IS_CLK_ENABLED()      ((RCC->APB2ENR & (RCC_APB2ENR_SYSCFGEN)) != RESET)
#define __HAL_RCC_SYSCFG_IS_CLK_DISABLED()     ((RCC->APB2ENR & (RCC_APB2ENR_SYSCFGEN)) == RESET)

#define __HAL_RCC_AHB1_FORCE_RESET()    (RCC->AHB1RSTR = 0xFFFFFFFFU)
#define __HAL_RCC_CRC_FORCE_RESET()     (RCC->AHB1RSTR |= (RCC_AHB1RSTR_CRCRST))
#define __HAL_RCC_DMA1_FORCE_RESET()    (RCC->AHB1RSTR |= (RCC_AHB1RSTR_DMA1RST))

#define __HAL_RCC_AHB1_RELEASE_RESET()  (RCC->AHB1RSTR = 0x00U)
#define __HAL_RCC_CRC_RELEASE_RESET()   (RCC->AHB1RSTR &= ~(RCC_AHB1RSTR_CRCRST))
#define __HAL_RCC_DMA1_RELEASE_RESET()  (RCC->AHB1RSTR &= ~(RCC_AHB1RSTR_DMA1RST))

#define __HAL_RCC_APB1_FORCE_RESET()     (RCC->APB1RSTR = 0xFFFFFFFFU)
#define __HAL_RCC_WWDG_FORCE_RESET()     (RCC->APB1RSTR |= (RCC_APB1RSTR_WWDGRST))
#define __HAL_RCC_PWR_FORCE_RESET()      (RCC->APB1RSTR |= (RCC_APB1RSTR_PWRRST))

#define __HAL_RCC_APB1_RELEASE_RESET()   (RCC->APB1RSTR = 0x00U)
#define __HAL_RCC_WWDG_RELEASE_RESET()   (RCC->APB1RSTR &= ~(RCC_APB1RSTR_WWDGRST))
#define __HAL_RCC_PWR_RELEASE_RESET()    (RCC->APB1RSTR &= ~(RCC_APB1RSTR_PWRRST))

#define __HAL_RCC_APB2_FORCE_RESET()     (RCC->APB2RSTR = 0xFFFFFFFFU)
#define __HAL_RCC_SYSCFG_FORCE_RESET()   (RCC->APB2RSTR |= (RCC_APB2RSTR_SYSCFGRST))

#define __HAL_RCC_APB2_RELEASE_RESET()   (RCC->APB2RSTR = 0x00U)
#define __HAL_RCC_SYSCFG_RELEASE_RESET() (RCC->APB2RSTR &= ~(RCC_APB2RSTR_SYSCFGRST))

#define __HAL_RCC_CRC_CLK_SLEEP_ENABLE()      (RCC->AHB1LPENR |= (RCC_AHB1LPENR_CRCLPEN))
#define __HAL_RCC_DMA1_CLK_SLEEP_ENABLE()     (RCC->AHB1LPENR |= (RCC_AHB1LPENR_DMA1LPEN))

#define __HAL_RCC_CRC_CLK_SLEEP_DISABLE()     (RCC->AHB1LPENR &= ~(RCC_AHB1LPENR_CRCLPEN))
#define __HAL_RCC_DMA1_CLK_SLEEP_DISABLE()    (RCC->AHB1LPENR &= ~(RCC_AHB1LPENR_DMA1LPEN))

#define __HAL_RCC_WWDG_CLK_SLEEP_ENABLE()    (RCC->APB1LPENR |= (RCC_APB1LPENR_WWDGLPEN))
#define __HAL_RCC_PWR_CLK_SLEEP_ENABLE()     (RCC->APB1LPENR |= (RCC_APB1LPENR_PWRLPEN))

#define __HAL_RCC_WWDG_CLK_SLEEP_DISABLE()   (RCC->APB1LPENR &= ~(RCC_APB1LPENR_WWDGLPEN))
#define __HAL_RCC_PWR_CLK_SLEEP_DISABLE()    (RCC->APB1LPENR &= ~(RCC_APB1LPENR_PWRLPEN))

#define __HAL_RCC_SYSCFG_CLK_SLEEP_EN()  (RCC->APB2LPENR |= (RCC_APB2LPENR_SYSCFGLPEN))
#define __HAL_RCC_SYSCFG_CLK_SLEEP_DIS() (RCC->APB2LPENR &= ~(RCC_APB2LPENR_SYSCFGLPEN))

#define __HAL_RCC_CRC_IS_CLK_SLEEP_EN() ((RCC->AHB1LPENR & (RCC_AHB1LPENR_CRCLPEN)) != RESET)
#define __HAL_RCC_DMA1_IS_CLK_SLEEP_EN() ((RCC->AHB1LPENR &(RCC_AHB1LPENR_DMA1LPEN)) != RESET)

#define __HAL_RCC_CRC_IS_CLK_SLEEP_DIS() ((RCC->AHB1LPENR & (RCC_AHB1LPENR_CRCLPEN)) == RESET)
#define __HAL_RCC_DMA1_IS_CLK_SLEEP_DIS() ((RCC->AHB1LPENR & \
                                                (RCC_AHB1LPENR_DMA1LPEN)) == RESET)

#define __HAL_RCC_WWDG_IS_CLK_SLEEP_EN() ((RCC->APB1LPENR &(RCC_APB1LPENR_WWDGLPEN)) != RESET)
#define __HAL_RCC_PWR_IS_CLK_SLEEP_EN() ((RCC->APB1LPENR & (RCC_APB1LPENR_PWRLPEN)) != RESET)

#define __HAL_RCC_WWDG_IS_CLK_SLEEP_DIS() ((RCC->APB1LPENR &   \
                                                (RCC_APB1LPENR_WWDGLPEN)) == RESET)
#define __HAL_RCC_PWR_IS_CLK_SLEEP_DIS() ((RCC->APB1LPENR & (RCC_APB1LPENR_PWRLPEN)) == RESET)

#define __HAL_RCC_SYSCFG_IS_CLK_SLEEP_EN() ((RCC->APB2LPENR & \
                                                (RCC_APB2LPENR_SYSCFGLPEN)) != RESET)
#define __HAL_RCC_SYSCFG_IS_CLK_SLEP_DIS() ((RCC->APB2LPENR &\
                                                   (RCC_APB2LPENR_SYSCFGLPEN)) == RESET)

#define __HAL_RCC_HSI_ENABLE() (RCC->CR |= (RCC_CR_HSION))
#define __HAL_RCC_HSI_DISABLE() (RCC->CR &= ~(RCC_CR_HSION))

#define __HAL_RCC_HSI_CALIBVALUE_ADJUST(__HSICALIBRATIONVALUE__) (MODIFY_REG(RCC->CR,\
        RCC_CR_HSITRIM, (T_UINT32)(__HSICALIBRATIONVALUE__) << POSITION_VAL(RCC_CR_HSITRIM)))

#define __HAL_RCC_LSI_ENABLE()  (RCC->CSR |= (RCC_CSR_LSION))
#define __HAL_RCC_LSI_DISABLE() (RCC->CSR &= ~(RCC_CSR_LSION))

#define __HAL_RCC_HSE_CONFIG(__STATE__)                         \
                    do {                                        \
                      if (RCC_HSE_ON == (__STATE__))            \
                      {                                         \
                        SET_BIT(RCC->CR, RCC_CR_HSEON);         \
                      }                                         \
                      else if (RCC_HSE_OFF == (__STATE__))      \
                      {                                         \
                        CLEAR_BIT(RCC->CR, RCC_CR_HSEON);       \
                        CLEAR_BIT(RCC->CR, RCC_CR_HSEBYP);      \
                      }                                         \
                      else if (RCC_HSE_BYPASS == (__STATE__))   \
                      {                                         \
                        SET_BIT(RCC->CR, RCC_CR_HSEBYP);        \
                        SET_BIT(RCC->CR, RCC_CR_HSEON);         \
                      }                                         \
                      else                                      \
                      {                                         \
                        CLEAR_BIT(RCC->CR, RCC_CR_HSEON);       \
                        CLEAR_BIT(RCC->CR, RCC_CR_HSEBYP);      \
                      }                                         \
                    } while(0)

#define __HAL_RCC_LSE_CONFIG(__STATE__) \
                    do {                                       \
                      if((__STATE__) == RCC_LSE_ON )           \
                      {                                        \
                        SET_BIT(RCC->BDCR, RCC_BDCR_LSEON);    \
                      }                                        \
                      else if(RCC_LSE_OFF == (__STATE__))      \
                      {                                        \
                        CLEAR_BIT(RCC->BDCR, RCC_BDCR_LSEON);  \
                        CLEAR_BIT(RCC->BDCR, RCC_BDCR_LSEBYP); \
                      }                                        \
                      else if(RCC_LSE_BYPASS == (__STATE__))   \
                      {                                        \
                        SET_BIT(RCC->BDCR, RCC_BDCR_LSEBYP);   \
                        SET_BIT(RCC->BDCR, RCC_BDCR_LSEON);    \
                      }                                        \
                      else                                     \
                      {                                        \
                        CLEAR_BIT(RCC->BDCR, RCC_BDCR_LSEON);  \
                        CLEAR_BIT(RCC->BDCR, RCC_BDCR_LSEBYP); \
                      }                                        \
                    } while(0)

#define __HAL_RCC_RTC_ENABLE()  (RCC->BDCR |= (RCC_BDCR_RTCEN))
#define __HAL_RCC_RTC_DISABLE() (RCC->BDCR &= ~(RCC_BDCR_RTCEN))


#define __HAL_RCC_RTC_CLKPRESCALER(__RTCCLKSource__) ((((__RTCCLKSource__) &\
                                       RCC_BDCR_RTCSEL) == RCC_BDCR_RTCSEL) ?    \
                                       MODIFY_REG(RCC->CFGR, RCC_CFGR_RTCPRE, ((__RTCCLKSource__) \
                                       & 0xFFFFCFF)) : CLEAR_BIT(RCC->CFGR, RCC_CFGR_RTCPRE))

#define __HAL_RCC_RTC_CONFIG(__RTCCLKSource__) do { __HAL_RCC_RTC_CLKPRESCALER(__RTCCLKSource__);\
                                                   RCC->BDCR |= ((__RTCCLKSource__) & 0x00000FFF);\
                                                   } while (0)


#define __HAL_RCC_BACKUPRESET_FORCE()   (RCC->BDCR |= (RCC_BDCR_BDRST))
#define __HAL_RCC_BACKUPRESET_RELEASE() (RCC->BDCR &= ~(RCC_BDCR_BDRST))

#define __HAL_RCC_PLL_ENABLE() (SET_BIT(RCC->CR, RCC_CR_PLLON))
#define __HAL_RCC_PLL_DISABLE() (CLEAR_BIT(RCC->CR, RCC_CR_PLLON))

#define __HAL_RCC_PLL_PLLSOURCE_CONFIG(__PLLSOURCE__) (MODIFY_REG(RCC->PLLCFGR,\
                                 RCC_PLLCFGR_PLLSRC, (__PLLSOURCE__)))

#define __HAL_RCC_PLL_PLLM_CONFIG(__PLLM__) (MODIFY_REG(RCC->PLLCFGR, RCC_PLLCFGR_PLLM, (__PLLM__)))

#define __HAL_RCC_I2S_CONFIG(__SOURCE__) do {RCC->CFGR &= ~(RCC_CFGR_I2SSRC); \
                                             RCC->CFGR |= (__SOURCE__);       \
                                            }while(0)

#define __HAL_RCC_PLLI2S_ENABLE() (RCC->CR |= (RCC_CR_PLLI2SON))
#define __HAL_RCC_PLLI2S_DISABLE() (RCC->CR &= ~(RCC_CR_PLLI2SON))

#define __HAL_RCC_SYSCLK_CONFIG(__RCC_SYSCLKSOURCE__) (MODIFY_REG(RCC->CFGR, RCC_CFGR_SW,\
                                 (__RCC_SYSCLKSOURCE__)))

#define __HAL_RCC_GET_SYSCLK_SOURCE() ((T_UINT32)(RCC->CFGR & RCC_CFGR_SWS))


#define __HAL_RCC_LSEDRIVE_CONFIG(__RCC_LSEDRIVE__) \
                  (MODIFY_REG(RCC->BDCR, RCC_BDCR_LSEDRV, (T_UINT32)(__RCC_LSEDRIVE__) ))

#define __HAL_RCC_GET_PLL_OSCSOURCE() ((T_UINT32)(RCC->PLLCFGR & RCC_PLLCFGR_PLLSRC))


#define __HAL_RCC_MCO1_CONFIG(__MCOCLKSOURCE__, __MCODIV__) \
   (MODIFY_REG(RCC->CFGR, (RCC_CFGR_MCO1 | RCC_CFGR_MCO1PRE), ((__MCOCLKSOURCE__) | (__MCODIV__))))

#define __HAL_RCC_MCO2_CONFIG(__MCOCLKSOURCE__, __MCODIV__) \
        (MODIFY_REG(RCC->CFGR, (RCC_CFGR_MCO2 | RCC_CFGR_MCO2PRE), \
        ((__MCOCLKSOURCE__) | ((__MCODIV__) << 3)));)

#define __HAL_RCC_ENABLE_IT(__INTERRUPT__) (*(__IO T_UINT8 *) RCC_CIR_BYTE1_ADDRESS |= \
                                          (__INTERRUPT__))

#define __HAL_RCC_DISABLE_IT(__INTERRUPT__) (*(__IO T_UINT8 *) RCC_CIR_BYTE1_ADDRESS &= \
                                             (T_UINT8)(~(__INTERRUPT__)))

#define __HAL_RCC_CLEAR_IT(__INTERRUPT__) (*(__IO T_UINT8 *)RCC_CIR_BYTE2_ADDRESS =(__INTERRUPT__))

#define __HAL_RCC_GET_IT(__INTERRUPT__) ((RCC->CIR & (__INTERRUPT__)) == (__INTERRUPT__))


#define __HAL_RCC_CLEAR_RESET_FLAGS() (RCC->CSR |= RCC_CSR_RMVF)

#define RCC_FLAG_MASK  ((T_UINT8)0x1F)
#define __HAL_RCC_GET_FLAG(__FLAG__) (((((ONE == ((__FLAG__) >> 5))? RCC->CR :(( \
         TWO == ((__FLAG__) >> 5)) ? RCC->BDCR :((THREE == ((__FLAG__) >> 5))?  \
         RCC->CSR :RCC->CIR))) & ((T_UINT32)1 << ((__FLAG__) & RCC_FLAG_MASK)))!= 0)? 1 : 0)

/* Initialization and de-initialization functions */
T_HAL_STATUS HalRccOscConfig(T_RCC_OSC_INIT *RCC_OscInitStruct);
T_HAL_STATUS HalRccClockConfig(T_RCC_CLK_INIT *RCC_ClkInitStruct, T_UINT32 FLatency);

/* Peripheral Control functions */
T_UINT32 HalRccGetSysClockFreq(void);

#define HSE_TIMEOUT_VALUE          HSE_STARTUP_TIMEOUT
#define HSI_TIMEOUT_VALUE          ((T_UINT32)2)  /* 2 ms */
#define LSI_TIMEOUT_VALUE          ((T_UINT32)2)  /* 2 ms */
#define PLL_TIMEOUT_VALUE          ((T_UINT32)2)  /* 2 ms */
#define CLOCKSWITCH_TIMEOUT_VALUE  ((T_UINT32)5000) /* 5 s    */


#define RCC_CIR_BYTE1_ADDRESS         ((T_UINT32)(RCC_BASE + 0x0C + 0x01))

#define RCC_CIR_BYTE2_ADDRESS         ((T_UINT32)(RCC_BASE + 0x0C + 0x02))

#define RCC_DBP_TIMEOUT_VALUE      ((T_UINT32)100)
#define RCC_LSE_TIMEOUT_VALUE      LSE_STARTUP_TIMEOUT

#define IS_RCC_OSCILLATORTYPE(OSCILLATOR) ((OSCILLATOR) <= 15)

#define IS_RCC_HSE(HSE) (((HSE) == RCC_HSE_OFF) || ((HSE) == RCC_HSE_ON) || \
                         ((HSE) == RCC_HSE_BYPASS))

#define IS_RCC_LSE(LSE) (((LSE) == RCC_LSE_OFF) || ((LSE) == RCC_LSE_ON) || \
                         ((LSE) == RCC_LSE_BYPASS))

#define IS_RCC_HSI(HSI) (((HSI) == RCC_HSI_OFF) || ((HSI) == RCC_HSI_ON))

#define IS_RCC_LSI(LSI) (((LSI) == RCC_LSI_OFF) || ((LSI) == RCC_LSI_ON))

#define IS_RCC_PLL(PLL) (((PLL) == RCC_PLL_NONE) ||((PLL) == RCC_PLL_OFF) || ((PLL) == RCC_PLL_ON))

#define IS_RCC_PLLSOURCE(SOURCE) (((SOURCE) == RCC_PLLSOURCE_HSI) || \
                                  ((SOURCE) == RCC_PLLSOURCE_HSE))

#define IS_RCC_SYSCLKSOURCE(SOURCE) (((SOURCE) == RCC_SYSCLKSOURCE_HSI) || \
                                     ((SOURCE) == RCC_SYSCLKSOURCE_HSE) || \
                                     ((SOURCE) == RCC_SYSCLKSOURCE_PLLCLK))
#define IS_RCC_PLLM_VALUE(VALUE) ((2 <= (VALUE)) && ((VALUE) <= 63))

#define IS_RCC_PLLN_VALUE(VALUE) ((50 <= (VALUE)) && ((VALUE) <= 432))

#define IS_RCC_PLLP_VALUE(VALUE) (((VALUE) == RCC_PLLP_DIV2) || ((VALUE) == RCC_PLLP_DIV4) || \
                                  ((VALUE) == RCC_PLLP_DIV6) || ((VALUE) == RCC_PLLP_DIV8))
#define IS_RCC_PLLQ_VALUE(VALUE) ((2 <= (VALUE)) && ((VALUE) <= 15))

#define IS_RCC_HCLK(HCLK) (((HCLK) == RCC_SYSCLK_DIV1)   || ((HCLK) == RCC_SYSCLK_DIV2)   || \
                           ((HCLK) == RCC_SYSCLK_DIV4)   || ((HCLK) == RCC_SYSCLK_DIV8)   || \
                           ((HCLK) == RCC_SYSCLK_DIV16)  || ((HCLK) == RCC_SYSCLK_DIV64)  || \
                           ((HCLK) == RCC_SYSCLK_DIV128) || ((HCLK) == RCC_SYSCLK_DIV256) || \
                           ((HCLK) == RCC_SYSCLK_DIV512))

#define IS_RCC_CLOCKTYPE(CLK) ((1 <= (CLK)) && ((CLK) <= 15))

#define IS_RCC_PCLK(PCLK) (((PCLK) == RCC_HCLK_DIV1) || ((PCLK) == RCC_HCLK_DIV2) || \
                           ((PCLK) == RCC_HCLK_DIV4) || ((PCLK) == RCC_HCLK_DIV8) || \
                           ((PCLK) == RCC_HCLK_DIV16))

#define IS_RCC_MCO(MCOX) (((MCOX) == RCC_MCO1) || ((MCOX) == RCC_MCO2))


#define IS_RCC_MCO1SOURCE(SOURCE) (((SOURCE) == RCC_MCO1SOURCE_HSI) || \
                                    ((SOURCE) == RCC_MCO1SOURCE_LSE) || \
                                   ((SOURCE) == RCC_MCO1SOURCE_HSE) || \
                                   ((SOURCE) == RCC_MCO1SOURCE_PLLCLK))

#define IS_RCC_MCO2SOURCE(SOURCE) (((SOURCE) == RCC_MCO2SOURCE_SYSCLK) || \
                                   ((SOURCE) == RCC_MCO2SOURCE_PLLI2SCLK)|| \
                                   ((SOURCE) == RCC_MCO2SOURCE_HSE) || \
                                   ((SOURCE) == RCC_MCO2SOURCE_PLLCLK))

#define IS_RCC_MCODIV(DIV) (((DIV) == RCC_MCODIV_1)  || ((DIV) == RCC_MCODIV_2) || \
                             ((DIV) == RCC_MCODIV_3) || ((DIV) == RCC_MCODIV_4) || \
                             ((DIV) == RCC_MCODIV_5))
#define IS_RCC_CALIBRATION_VALUE(VALUE) ((VALUE) <= 0x1F)

#define IS_RCC_RTCCLKSOURCE(SOURCE) (((SOURCE) == RCC_RTCCLKSOURCE_LSE) || \
                                     ((SOURCE) == RCC_RTCCLKSOURCE_LSI) || \
                                     ((SOURCE) == RCC_RTCCLKSOURCE_HSE_DIV2) || \
                                     ((SOURCE) == RCC_RTCCLKSOURCE_HSE_DIV3) || \
                                     ((SOURCE) == RCC_RTCCLKSOURCE_HSE_DIV4) || \
                                     ((SOURCE) == RCC_RTCCLKSOURCE_HSE_DIV5) || \
                                     ((SOURCE) == RCC_RTCCLKSOURCE_HSE_DIV6) || \
                                     ((SOURCE) == RCC_RTCCLKSOURCE_HSE_DIV7) || \
                                     ((SOURCE) == RCC_RTCCLKSOURCE_HSE_DIV8) || \
                                     ((SOURCE) == RCC_RTCCLKSOURCE_HSE_DIV9) || \
                                     ((SOURCE) == RCC_RTCCLKSOURCE_HSE_DIV10) || \
                                     ((SOURCE) == RCC_RTCCLKSOURCE_HSE_DIV11) || \
                                     ((SOURCE) == RCC_RTCCLKSOURCE_HSE_DIV12) || \
                                     ((SOURCE) == RCC_RTCCLKSOURCE_HSE_DIV13) || \
                                     ((SOURCE) == RCC_RTCCLKSOURCE_HSE_DIV14) || \
                                     ((SOURCE) == RCC_RTCCLKSOURCE_HSE_DIV15) || \
                                     ((SOURCE) == RCC_RTCCLKSOURCE_HSE_DIV16) || \
                                     ((SOURCE) == RCC_RTCCLKSOURCE_HSE_DIV17) || \
                                     ((SOURCE) == RCC_RTCCLKSOURCE_HSE_DIV18) || \
                                     ((SOURCE) == RCC_RTCCLKSOURCE_HSE_DIV19) || \
                                     ((SOURCE) == RCC_RTCCLKSOURCE_HSE_DIV20) || \
                                     ((SOURCE) == RCC_RTCCLKSOURCE_HSE_DIV21) || \
                                     ((SOURCE) == RCC_RTCCLKSOURCE_HSE_DIV22) || \
                                     ((SOURCE) == RCC_RTCCLKSOURCE_HSE_DIV23) || \
                                     ((SOURCE) == RCC_RTCCLKSOURCE_HSE_DIV24) || \
                                     ((SOURCE) == RCC_RTCCLKSOURCE_HSE_DIV25) || \
                                     ((SOURCE) == RCC_RTCCLKSOURCE_HSE_DIV26) || \
                                     ((SOURCE) == RCC_RTCCLKSOURCE_HSE_DIV27) || \
                                     ((SOURCE) == RCC_RTCCLKSOURCE_HSE_DIV28) || \
                                     ((SOURCE) == RCC_RTCCLKSOURCE_HSE_DIV29) || \
                                     ((SOURCE) == RCC_RTCCLKSOURCE_HSE_DIV30) || \
                                     ((SOURCE) == RCC_RTCCLKSOURCE_HSE_DIV31))

#define IS_RCC_LSE_DRIVE(DRIVE) (((DRIVE) == RCC_LSEDRIVE_LOW)        || \
                                 ((DRIVE) == RCC_LSEDRIVE_MEDIUMLOW)  || \
                                 ((DRIVE) == RCC_LSEDRIVE_MEDIUMHIGH) || \
                                 ((DRIVE) == RCC_LSEDRIVE_HIGH))

#endif
