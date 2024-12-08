/*
 ******************************************************************************
 * License Information  :  Howell Instruments, Inc.                           *
 *                         "Licensed Software" and "All rights reserved".     *
 ******************************************************************************
 *  File                : hdulibstm32f7xxhalconf.h
 *
 *  Description         : This file provides HAL configurations.
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
 *      1.2          Rona B.S        02-Sep-2017            100028 
 *
 * Additional References : None
 *
 ******************************************************************************
 */

/* Define to prevent recursive inclusion*/
#ifndef _HDULIBSTM32F7XXHALCONF_H_
#define _HDULIBSTM32F7XXHALCONF_H_

/*Module Selection*/

#define HAL_MODULE_ENABLED
#define HAL_ADC_MODULE_ENABLED
#define HAL_CAN_MODULE_ENABLED
#define HAL_CRC_MODULE_ENABLED
#define HAL_DMA_MODULE_ENABLED
#define HAL_DMA2D_MODULE_ENABLED
#define HAL_FLASH_MODULE_ENABLED
#define HAL_NOR_MODULE_ENABLED
#define HAL_SRAM_MODULE_ENABLED
#define HAL_SDRAM_MODULE_ENABLED
#define HAL_GPIO_MODULE_ENABLED
#define HAL_I2C_MODULE_ENABLED
#define HAL_IWDG_MODULE_ENABLED
#define HAL_LTDC_MODULE_ENABLED
#define HAL_PWR_MODULE_ENABLED
#define HAL_RCC_MODULE_ENABLED
#define HAL_SD_MODULE_ENABLED
#define HAL_SPI_MODULE_ENABLED
#define HAL_TIM_MODULE_ENABLED
#define HAL_SMARTCARD_MODULE_ENABLED
#define HAL_WWDG_MODULE_ENABLED
#define HAL_CORTEX_MODULE_ENABLED

/*HSE/HSI Values adaptation*/

 /*
  * value of rciAdjust the value of External High Speed oscillator (HSE) used in your application.
  *        This value is used by the RCC HAL module to compute the system frequency
  *        (when HSE is used as system clock source, directly or through the PLL).
  */
#if !defined  (HSE_VALUE)
  #define HSE_VALUE    ((T_UINT32)25000000) /* Value of the External oscillator in Hz */
#endif /* HSE_VALUE */

#if !defined  (HSE_STARTUP_TIMEOUT)
  #define HSE_STARTUP_TIMEOUT    ((T_UINT32)100U)   /* Time out for HSE start up, in ms */
#endif /* HSE_STARTUP_TIMEOUT */

 /*
  * value of rciInternal High Speed oscillator (HSI) value.
  *        This value is used by the RCC HAL module to compute the system frequency
  *        (when HSI is used as system clock source, directly or through the PLL).
  */
#if !defined  (HSI_VALUE)
  #define HSI_VALUE    ((T_UINT32)16000000) /* Value of the Internal oscillator in Hz*/
#endif /* HSI_VALUE */

 /*
  * value of rciInternal Low Speed oscillator (LSI) value.
  */
#if !defined  (LSI_VALUE)
 #define LSI_VALUE  ((T_UINT32)32000)       /* LSI Typical Value in Hz*/
#endif /* LSI_VALUE */

/*
 * Value of the Internal Low Speed oscillator in Hz
 * The real value may vary depending on the variations
 * in voltage and temperature.
 */

 /*
  * value of rciExternal Low Speed oscillator (LSE) value.
  */
#if !defined  (LSE_VALUE)
 #define LSE_VALUE  ((T_UINT32)32768)    /* Value of the External Low Speed oscillator in Hz */
#endif /* LSE_VALUE */
#if !defined  (LSE_STARTUP_TIMEOUT)
  #define LSE_STARTUP_TIMEOUT    ((T_UINT32)5000U)   /* Time out for LSE start up, in ms */
#endif /* LSE_STARTUP_TIMEOUT */

 /*
  * value of rciExternal clock source for I2S peripheral
  *        This value is used by the I2S HAL module to compute the I2S clock source
  *        frequency, this source is inserted directly through I2S_CKIN pad.
  */
#if !defined  (EXTERNAL_CLOCK_VALUE)
  #define EXTERNAL_CLOCK_VALUE    ((T_UINT32)12288000) /* Value of the Internal oscillator in Hz*/
#endif /* EXTERNAL_CLOCK_VALUE */

/* System Configuration */
 /*
  * value of rciThis is the HAL system configuration section
  */
#define  VDD_VALUE                    ((T_UINT32)3300U) /* Value of VDD in mv */
#define  TICK_INT_PRIORITY            ((T_UINT32)0x0FU) /* tick interrupt priority */
#define  USE_RTOS                     0U
#define  PREFETCH_ENABLE              1U
#define  ART_ACCLERATOR_ENABLE        1U /* To enable instruction cache and prefetch */

/* MAC ADDRESS: MAC_ADDR0:MAC_ADDR1:MAC_ADDR2:MAC_ADDR3:MAC_ADDR4:MAC_ADDR5 */
#define MAC_ADDR0   2U
#define MAC_ADDR1   0U
#define MAC_ADDR2   0U
#define MAC_ADDR3   0U
#define MAC_ADDR4   0U
#define MAC_ADDR5   0U

/* Definition of the Ethernet driver buffers size and count */
#define ETH_RXBUFNB           ((T_UINT32)4U)       /* 4 Rx buffers of size ETH_RX_BUF_SIZE  */
#define ETH_TXBUFNB           ((T_UINT32)4U)       /* 4 Tx buffers of size ETH_TX_BUF_SIZE  */

/* Section 2: PHY configuration section */

/* DP83848 PHY Address*/
#define DP83848_PHY_ADDRESS             0x01U
/* PHY Reset delay these values are based on a 1 ms Systick interrupt*/
#define PHY_RESET_DELAY                 ((T_UINT32)0x000000FFU)
/* PHY Configuration delay */
#define PHY_CONFIG_DELAY                ((T_UINT32)0x00000FFFU)

#define PHY_READ_TO                     ((T_UINT32)0x0000FFFFU)
#define PHY_WRITE_TO                    ((T_UINT32)0x0000FFFFU)

/* Section 3: Common PHY Registers */

#define PHY_BCR                      ((T_UINT16)0x00U)    /* Transceiver Basic Control Register   */
#define PHY_BSR                      ((T_UINT16)0x01U)    /* Transceiver Basic Status Register    */

#define PHY_RESET                    ((T_UINT16)0x8000U) /* PHY Reset */
#define PHY_LOOPBACK                 ((T_UINT16)0x4000U) /* Select loop-back mode */
#define PHY_FULLDUPLEX_100M          ((T_UINT16)0x2100U) /* Set the full-duplex mode at 100 Mb/s */
#define PHY_HALFDUPLEX_100M          ((T_UINT16)0x2000U) /* Set the half-duplex mode at 100 Mb/s */
#define PHY_FULLDUPLEX_10M           ((T_UINT16)0x0100U) /* Set the full-duplex mode at 10 Mb/s */
#define PHY_HALFDUPLEX_10M           ((T_UINT16)0x0000U) /* Set the half-duplex mode at 10 Mb/s */
#define PHY_AUTONEGOTIATION          ((T_UINT16)0x1000U) /* Enable auto-negotiation function */
#define PHY_RESTART_AUTONEGOTIATION  ((T_UINT16)0x0200U) /* Restart auto-negotiation function */
#define PHY_POWERDOWN                ((T_UINT16)0x0800U) /* Select the power down mode */
#define PHY_ISOLATE                  ((T_UINT16)0x0400U) /* Isolate PHY from MII */

#define PHY_AUTONEGO_COMPLETE        ((T_UINT16)0x0020U)  /* Auto-Negotiation process completed */
#define PHY_LINKED_STATUS            ((T_UINT16)0x0004U)  /* Valid link established */
#define PHY_JABBER_DETECTION         ((T_UINT16)0x0002U)  /* Jabber condition detected */

/* Section 4: Extended PHY Registers */

#define PHY_SR                  ((T_UINT16)0x10U)    /* PHY status register Offset */
#define PHY_MICR                ((T_UINT16)0x11U)    /* MII Interrupt Control Register */
/* MII Interrupt Status and Misc. Control Register */
#define PHY_MISR                ((T_UINT16)0x12U)

#define PHY_LINK_STATUS         ((T_UINT16)0x0001U)  /* PHY Link mask */
#define PHY_SPEED_STATUS        ((T_UINT16)0x0002U)  /* PHY Speed mask */
#define PHY_DUPLEX_STATUS       ((T_UINT16)0x0004U)  /* PHY Duplex mask */

#define PHY_MICR_INT_EN         ((T_UINT16)0x0002U)  /* PHY Enable interrupts */
#define PHY_MICR_INT_OE         ((T_UINT16)0x0001U)  /* PHY Enable output interrupt events */

#define PHY_MISR_LINK_INT_EN    ((T_UINT16)0x0020U)  /* Enable Interrupt on change of link status*/
#define PHY_LINK_INTERRUPT      ((T_UINT16)0x2000U)  /* PHY link status interrupt mask */

/*  SPI peripheral configuration */

/*
 * CRC FEATURE: Use to activate CRC feature inside HAL SPI Driver
 * Activated: CRC code is present inside driver
 * Deactivated: CRC code cleaned from driver
 */

#define USE_SPI_CRC                     1U

#endif /* __STM32F7xx_HAL_CONF_H */
