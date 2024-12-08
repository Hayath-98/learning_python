/*
 ******************************************************************************
 * License Information  :  Howell Instruments, Inc.                           *
 *                         "Licensed Software" and "All rights reserved".     *
 ******************************************************************************
 *  File                : hdulibstmcorecomm.h
 *
 *  Description         : This file holds the members of irqn type.
 *
 *  Compiler            : GNU gcc(GNU Tools for ARM Embedded Processors) version 5.4.1 20160919
 *
 *
 *  Compiler options    : As per section 10.3.1 of Software Development Plan (HDU-001-002).
 *
 *
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
 *
 * <Version No.>     <Author>          <Date>         <Problem Report No.>
 *
 *      1.1          Shilpa A R        03-Sep-2017          -
 *
 * Additional References : None
 *
 ******************************************************************************
 */


#ifndef _HDULIBSTMCORECOMM_H_
#define _HDULIBSTMCORECOMM_H_


#define __CM7_REV            0x0001U  /* Cortex-M7 revision r0p1 */
#define __MPU_PRESENT             1       /* CM7 provides an MPU */
#define __NVIC_PRIO_BITS          4       /* CM7 uses 4 Bits for the Priority Levels */
#define __VENDOR_SYSTICKCONFIG    0       /* Set to 1 if different SysTick Config is used */
#define __FPU_PRESENT             1       /* FPU present*/
#define __ICACHE_PRESENT          1       /* CM7 instruction cache present */
#define __DCACHE_PRESENT          1       /* CM7 data cache present */

typedef enum
{
  NONMASKABLEINT_IRQN         = -14,    /* 2 Non Maskable Interrupt */
  MEMORYMANAGEMENT_IRQN       = -12,    /* 4 Cortex-M7 Memory Management Interrupt */
  BUSFAULT_IRQN               = -11,    /* 5 Cortex-M7 Bus Fault Interrupt */
  USAGEFAULT_IRQN             = -10,    /* 6 Cortex-M7 Usage Fault Interrupt */
  SVCALL_IRQN                 = -5,     /* 11 Cortex-M7 SV Call Interrupt */
  DEBUGMONITOR_IRQN           = -4,     /* 12 Cortex-M7 Debug Monitor Interrupt */
  PENDSV_IRQN                 = -2,     /* 14 Cortex-M7 Pend SV Interrupt */
  SYSTICK_IRQN                = -1,     /* 15 Cortex-M7 System Tick Interrupt */
  WWDG_IRQN                   = 0,      /* Window WatchDog Interrupt */
  PVD_IRQN                    = 1,      /* PVD through EXTI Line detection Interrupt */
  TAMP_STAMP_IRQN             = 2,      /* Tamper and TimeStamp interrupts through the EXTI line */
  RTC_WKUP_IRQN               = 3,      /* RTC Wakeup interrupt through the EXTI line */
  FLASH_IRQN                  = 4,      /* FLASH global Interrupt */
  RCC_IRQN                    = 5,      /* RCC global Interrupt */
  EXTI0_IRQN                  = 6,      /* EXTI Line0 Interrupt */
  EXTI1_IRQN                  = 7,      /* EXTI Line1 Interrupt */
  EXTI2_IRQN                  = 8,      /* EXTI Line2 Interrupt */
  EXTI3_IRQN                  = 9,      /* EXTI Line3 Interrupt */
  EXTI4_IRQN                  = 10,     /* EXTI Line4 Interrupt */
  DMA1_STREAM0_IRQN           = 11,     /* DMA1 Stream 0 global Interrupt */
  DMA1_STREAM1_IRQN           = 12,     /* DMA1 Stream 1 global Interrupt */
  DMA1_STREAM2_IRQN           = 13,     /* DMA1 Stream 2 global Interrupt */
  DMA1_STREAM3_IRQN           = 14,     /* DMA1 Stream 3 global Interrupt */
  DMA1_STREAM4_IRQN           = 15,     /* DMA1 Stream 4 global Interrupt */
  DMA1_STREAM5_IRQN           = 16,     /* DMA1 Stream 5 global Interrupt */
  DMA1_STREAM6_IRQN           = 17,     /* DMA1 Stream 6 global Interrupt */
  ADC_IRQN                    = 18,     /* ADC1, ADC2 and ADC3 global Interrupts */
  CAN1_TX_IRQN                = 19,     /* CAN1 TX Interrupt */
  CAN1_RX0_IRQN               = 20,     /* CAN1 RX0 Interrupt */
  CAN1_RX1_IRQN               = 21,     /* CAN1 RX1 Interrupt */
  CAN1_SCE_IRQN               = 22,     /* CAN1 SCE Interrupt */
  EXTI9_5_IRQN                = 23,     /* External Line[9:5] Interrupts */
  TIM1_BRK_TIM9_IRQN          = 24,     /* TIM1 Break interrupt and TIM9 global interrupt */
  TIM1_UP_TIM10_IRQN          = 25,     /* TIM1 Update Interrupt and TIM10 global interrupt */
  /* TIM1 Trigger and Commutation Interrupt and TIM11 global interrupt */
  TIM1_TRG_COM_TIM11_IRQN     = 26,
  TIM1_CC_IRQN                = 27,     /* TIM1 Capture Compare Interrupt */
  TIM2_IRQN                   = 28,     /* TIM2 global Interrupt */
  TIM3_IRQN                   = 29,     /* TIM3 global Interrupt */
  TIM4_IRQN                   = 30,     /* TIM4 global Interrupt */
  I2C1_EV_IRQN                = 31,     /* I2C1 Event Interrupt */
  I2C1_ER_IRQN                = 32,     /* I2C1 Error Interrupt */
  I2C2_EV_IRQN                = 33,     /* I2C2 Event Interrupt */
  I2C2_ER_IRQN                = 34,     /* I2C2 Error Interrupt */
  SPI1_IRQN                   = 35,     /* SPI1 global Interrupt */
  SPI2_IRQN                   = 36,     /* SPI2 global Interrupt */
  USART1_IRQN                 = 37,     /* USART1 global Interrupt */
  USART2_IRQN                 = 38,     /* USART2 global Interrupt */
  USART3_IRQN                 = 39,     /* USART3 global Interrupt */
  EXTI15_10_IRQN              = 40,     /* External Line[15:10] Interrupts */
  RTC_ALARM_IRQN              = 41,     /* RTC Alarm (A and B) through EXTI Line Interrupt */
  OTG_FS_WKUP_IRQN            = 42,     /* USB OTG FS Wakeup through EXTI line interrupt */
  TIM8_BRK_TIM12_IRQN         = 43,     /* TIM8 Break Interrupt and TIM12 global interrupt */
  TIM8_UP_TIM13_IRQN          = 44,     /* TIM8 Update Interrupt and TIM13 global interrupt */
  /* TIM8 Trigger and Commutation Interrupt and TIM14 global interrupt */
  TIM8_TRG_COM_TIM14_IRQN     = 45,
  TIM8_CC_IRQN                = 46,     /* TIM8 Capture Compare Interrupt */
  DMA1_STREAM7_IRQN           = 47,     /* DMA1 Stream7 Interrupt */
  FMC_IRQN                    = 48,     /* FMC global Interrupt */
  SDMMC1_IRQN                 = 49,     /* SDMMC1 global Interrupt */
  TIM5_IRQN                   = 50,     /* TIM5 global Interrupt */
  SPI3_IRQN                   = 51,     /* SPI3 global Interrupt */
  UART4_IRQN                  = 52,     /* UART4 global Interrupt */
  UART5_IRQN                  = 53,     /* UART5 global Interrupt */
  TIM6_DAC_IRQN               = 54,     /* TIM6 global and DAC1&2 underrun error  interrupts */
  TIM7_IRQN                   = 55,     /* TIM7 global interrupt */
  DMA2_STREAM0_IRQN           = 56,     /* DMA2 Stream 0 global Interrupt */
  DMA2_STREAM1_IRQN           = 57,     /* DMA2 Stream 1 global Interrupt */
  DMA2_STREAM2_IRQN           = 58,     /* DMA2 Stream 2 global Interrupt */
  DMA2_STREAM3_IRQN           = 59,     /* DMA2 Stream 3 global Interrupt */
  DMA2_STREAM4_IRQN           = 60,     /* DMA2 Stream 4 global Interrupt */
  ETH_IRQN                    = 61,     /* Ethernet global Interrupt */
  ETH_WKUP_IRQN               = 62,     /* Ethernet Wakeup through EXTI line Interrupt */
  CAN2_TX_IRQN                = 63,     /* CAN2 TX Interrupt */
  CAN2_RX0_IRQN               = 64,     /* CAN2 RX0 Interrupt   */
  CAN2_RX1_IRQN               = 65,     /* CAN2 RX1 Interrupt   */
  CAN2_SCE_IRQN               = 66,     /* CAN2 SCE Interrupt   */
  OTG_FS_IRQN                 = 67,     /* USB OTG FS global Interrupt */
  DMA2_STREAM5_IRQN           = 68,     /* DMA2 Stream 5 global interrupt */
  DMA2_STREAM6_IRQN           = 69,     /* DMA2 Stream 6 global interrupt */
  DMA2_STREAM7_IRQN           = 70,     /* DMA2 Stream 7 global interrupt */
  USART6_IRQN                 = 71,     /* USART6 global interrupt   */
  I2C3_EV_IRQN                = 72,     /* I2C3 event interrupt */
  I2C3_ER_IRQN                = 73,     /* I2C3 error interrupt */
  OTG_HS_EP1_OUT_IRQN         = 74,     /* USB OTG HS End Point 1 Out global interrupt */
  OTG_HS_EP1_IN_IRQN          = 75,     /* USB OTG HS End Point 1 In global interrupt */
  OTG_HS_WKUP_IRQN            = 76,     /* USB OTG HS Wakeup through EXTI interrupt */
  OTG_HS_IRQN                 = 77,     /* USB OTG HS global interrupt */
  DCMI_IRQN                   = 78,     /* DCMI global interrupt  */
  RNG_IRQN                    = 80,     /* RNG global interrupt */
  FPU_IRQN                    = 81,     /* FPU global interrupt */
  UART7_IRQN                  = 82,     /* UART7 global interrupt */
  UART8_IRQN                  = 83,     /* UART8 global interrupt */
  SPI4_IRQN                   = 84,     /* SPI4 global Interrupt  */
  SPI5_IRQN                   = 85,     /* SPI5 global Interrupt  */
  SPI6_IRQN                   = 86,     /* SPI6 global Interrupt  */
  SAI1_IRQN                   = 87,     /* SAI1 global Interrupt  */
  LTDC_IRQN                   = 88,     /* LTDC global Interrupt  */
  LTDC_ER_IRQN                = 89,     /* LTDC Error global Interrupt */
  DMA2D_IRQN                  = 90,     /* DMA2D global Interrupt */
  SAI2_IRQN                   = 91,     /* SAI2 global Interrupt  */
  QUADSPI_IRQN                = 92,     /* Quad SPI global interrupt */
  LPTIM1_IRQN                 = 93,     /* LP TIM1 interrupt */
  CEC_IRQN                    = 94,     /* HDMI-CEC global Interrupt */
  I2C4_EV_IRQN                = 95,     /* I2C4 Event Interrupt */
  I2C4_ER_IRQN                = 96,     /* I2C4 Error Interrupt */
  SPDIF_RX_IRQN               = 97     /* SPDIF-RX global Interrupt  */
} T_IRQN_TYPE;

#endif /* _HDULIBSTMCORECOMM_H_ */
