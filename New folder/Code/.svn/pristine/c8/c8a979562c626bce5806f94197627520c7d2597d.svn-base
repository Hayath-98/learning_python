/*
 ******************************************************************************
 * License Information  :  Howell Instruments, Inc.                           *
 *                         "Licensed Software" and "All rights reserved".     *
 ******************************************************************************
 *  File                : hdulibstm32f7xxhalflashex.h
 *
 *  Description         : Header file of FLASH HAL Extension module.
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

#ifndef _HDULIBSTM32F7XXHALFLASHEX_H_
#define _HDULIBSTM32F7XXHALFLASHEX_H_


/* Includes */
#include "hdulibstm32f7xxhaldef.h"     /* Header file of CORTEX HAL module */
#include "hdulibstm32f746xx.h"         /* CMSIS Cortex-M7 Device Peripheral Access Layer */
#include "hdulibstm32f7xxhalflash.h"   /* Header file of HAL FLASH module */ 

typedef struct
{
   /*
    * Mass erase or sector Erase.
    * This parameter can be a value of @ref FLASHEx_Type_Erase
    */
   T_UINT32 TypeErase;

   /*
    * Initial FLASH sector to erase when Mass erase is disabled
    * This parameter must be a value of @ref FLASHEx_Sectors
    */
   T_UINT32 Sector;

   /*
    * Number of sectors to be erased.
    * This parameter must be a value between 1 and(max number of sectors - value of Initial sector)
    */
   T_UINT32 NbSectors;

   /*
    * The device voltage range which defines the erase parallelism
    * This parameter must be a value of @ref FLASHEx_Voltage_Range
    */
   T_UINT32 VoltageRange;

} T_FLASH_ERASEINIT;

typedef struct
{
   /*
    * Option byte to be configured.
    * This parameter can be a value of @ref FLASHEx_Option_Type
    */
   T_UINT32 OptionType;

   /*
    * Write protection activation or deactivation.
    * This parameter can be a value of @ref FLASHEx_WRP_State
    */
   T_UINT32 WRPState;

   /*
    * Specifies the sector(s) to be write protected.
    * The value of this parameter depend on device used within the same series
    */
   T_UINT32 WRPSector;

   /*
    * Set the read protection level.
    * This parameter can be a value of @ref FLASHEx_Option_Bytes_Read_Protection
    */
   T_UINT32 RDPLevel;

   /*
    * Set the BOR Level.
    * This parameter can be a value of @ref FLASHEx_BOR_Reset_Level
    */
   T_UINT32 BORLevel;

   /*
    * Program the FLASH User Option Byte: WWDG_SW / IWDG_SW / RST_STOP / RST_STDBY /
    * IWDG_FREEZE_STOP / IWDG_FREEZE_SANDBY / nDBANK / nDBOOT.
    * nDBANK / nDBOOT are only available for STM32F76xxx/STM32F77xxx devices
    */
   T_UINT32 USERConfig;

   /*
    * Boot base address when Boot pin = 0.
    * This parameter can be a value of @ref FLASHEx_Boot_Address
    */
   T_UINT32 BootAddr0;

   /*
    * Boot base address when Boot pin = 1.
    * This parameter can be a value of @ref FLASHEx_Boot_Address
    */
   T_UINT32 BootAddr1;

} T_FLASH_OBPROGRAMINIT;


#define FLASH_TYPEERASE_SECTORS         ((T_UINT32)0x00U)  /* Sectors erase only */
#define FLASH_TYPEERASE_MASSERASE       ((T_UINT32)0x01U)  /* Flash Mass erase activation */
#define FLASH_VOLTAGE_RANGE_1        ((T_UINT32)0x00U)  /* Device operating range: 1.8V to 2.1V */
#define FLASH_VOLTAGE_RANGE_2        ((T_UINT32)0x01U)  /* Device operating range: 2.1V to 2.7V */
#define FLASH_VOLTAGE_RANGE_3        ((T_UINT32)0x02U)  /* Device operating range: 2.7V to 3.6V */
/* Device operating range: 2.7V to 3.6V + External Vpp */
#define FLASH_VOLTAGE_RANGE_4        ((T_UINT32)0x03U)
/* Disable the write protection of the desired bank 1 sectors */
#define OB_WRPSTATE_DISABLE       ((T_UINT32)0x00U)
/* Enable the write protection of the desired bank 1 sectors */
#define OB_WRPSTATE_ENABLE        ((T_UINT32)0x01U)
#define OPTIONBYTE_WRP         ((T_UINT32)0x01U)  /* WRP option byte configuration */
#define OPTIONBYTE_RDP         ((T_UINT32)0x02U)  /* RDP option byte configuration */
#define OPTIONBYTE_USER        ((T_UINT32)0x04U)  /* USER option byte configuration */
#define OPTIONBYTE_BOR         ((T_UINT32)0x08U)  /* BOR option byte configuration */
#define OPTIONBYTE_BOOTADDR_0  ((T_UINT32)0x10U)  /* Boot 0 Address configuration */
#define OPTIONBYTE_BOOTADDR_1  ((T_UINT32)0x20U)  /* Boot 1 Address configuration */
#define OB_RDP_LEVEL_0       ((T_UINT8)0xAAU)
#define OB_RDP_LEVEL_1       ((T_UINT8)0x55U)
/*
 * Warning: When enabling read protection level 2
 * it s no more possible to go back to level 1 or 0
 */
#define OB_RDP_LEVEL_2       ((T_UINT8)0xCCU)

#define OB_WWDG_SW           ((T_UINT32)0x10U)  /* Software WWDG selected */
#define OB_WWDG_HW           ((T_UINT32)0x00U)  /* Hardware WWDG selected */
#define OB_IWDG_SW           ((T_UINT32)0x20U)  /* Software IWDG selected */
#define OB_IWDG_HW           ((T_UINT32)0x00U)  /* Hardware IWDG selected */
#define OB_STOP_NO_RST       ((T_UINT32)0x40U) /* No reset generated when entering in STOP */
#define OB_STOP_RST          ((T_UINT32)0x00U) /* Reset generated when entering in STOP */
#define OB_STDBY_NO_RST      ((T_UINT32)0x80U) /* No reset generated when entering in STANDBY */
#define OB_STDBY_RST         ((T_UINT32)0x00U) /* Reset generated when entering in STANDBY */
#define OB_IWDG_STOP_FREEZE  ((T_UINT32)0x00000000U) /* Freeze IWDG counter in STOP mode */
#define OB_IWDG_STOP_ACTIVE  ((T_UINT32)0x80000000U) /* IWDG counter active in STOP mode */
#define OB_IWDG_STDBY_FREEZE  ((T_UINT32)0x00000000U) /* Freeze IWDG counter in STANDBY mode */
#define OB_IWDG_STDBY_ACTIVE   ((T_UINT32)0x40000000U) /* IWDG counter active in STANDBY mode */
#define OB_BOR_LEVEL3          ((T_UINT32)0x00U)  /* Supply voltage ranges from 2.70 to 3.60 V */
#define OB_BOR_LEVEL2          ((T_UINT32)0x04U)  /* Supply voltage ranges from 2.40 to 2.70 V */
#define OB_BOR_LEVEL1          ((T_UINT32)0x08U)  /* Supply voltage ranges from 2.10 to 2.40 V */
#define OB_BOR_OFF             ((T_UINT32)0x0CU)  /* Supply voltage ranges from 1.62 to 2.10 V */

#define OB_BOOTADDR_ITCM_RAM         ((T_UINT32)0x0000U)  /* Boot from ITCM RAM (0x00000000) */
/* Boot from System memory bootloader (0x00100000) */
#define OB_BOOTADDR_SYSTEM           ((T_UINT32)0x0040U)
/* Boot from Flash on ITCM interface (0x00200000) */
#define OB_BOOTADDR_ITCM_FLASH       ((T_UINT32)0x0080U)
/* Boot from Flash on AXIM interface (0x08000000) */
#define OB_BOOTADDR_AXIM_FLASH       ((T_UINT32)0x2000U)
#define OB_BOOTADDR_DTCM_RAM         ((T_UINT32)0x8000U)  /* Boot from DTCM RAM (0x20000000) */
#define OB_BOOTADDR_SRAM1            ((T_UINT32)0x8004U)  /* Boot from SRAM1 (0x20010000) */
#define OB_BOOTADDR_SRAM2            ((T_UINT32)0x8013U)  /* Boot from SRAM2 (0x2004C000) */
#define FLASH_LATENCY_0                FLASH_ACR_LATENCY_0WS   /* FLASH Zero Latency cycle */
#define FLASH_LATENCY_1                FLASH_ACR_LATENCY_1WS   /* FLASH One Latency cycle */
#define FLASH_LATENCY_2                FLASH_ACR_LATENCY_2WS   /* FLASH Two Latency cycles */
#define FLASH_LATENCY_3                FLASH_ACR_LATENCY_3WS   /* FLASH Three Latency cycles */
#define FLASH_LATENCY_4                FLASH_ACR_LATENCY_4WS   /* FLASH Four Latency cycles */
#define FLASH_LATENCY_5                FLASH_ACR_LATENCY_5WS   /* FLASH Five Latency cycles */
#define FLASH_LATENCY_6                FLASH_ACR_LATENCY_6WS   /* FLASH Six Latency cycles */
#define FLASH_LATENCY_7                FLASH_ACR_LATENCY_7WS   /* FLASH Seven Latency cycles */
#define FLASH_LATENCY_8                FLASH_ACR_LATENCY_8WS   /* FLASH Eight Latency cycles */
#define FLASH_LATENCY_9                FLASH_ACR_LATENCY_9WS   /* FLASH Nine Latency cycles */
#define FLASH_LATENCY_10               FLASH_ACR_LATENCY_10WS  /* FLASH Ten Latency cycles */
#define FLASH_LATENCY_11               FLASH_ACR_LATENCY_11WS  /* FLASH Eleven Latency cycles */
#define FLASH_LATENCY_12               FLASH_ACR_LATENCY_12WS  /* FLASH Twelve Latency cycles */
#define FLASH_LATENCY_13               FLASH_ACR_LATENCY_13WS  /* FLASH Thirteen Latency cycles */
#define FLASH_LATENCY_14               FLASH_ACR_LATENCY_14WS  /* FLASH Fourteen Latency cycles */
#define FLASH_LATENCY_15               FLASH_ACR_LATENCY_15WS  /* FLASH Fifteen Latency cycles */

#define FLASH_MER_BIT     (FLASH_CR_MER) /*!< only 1 MER bit */

#if (FLASH_SECTOR_TOTAL == 8)

#define OB_WRP_SECTOR_0       ((T_UINT32)0x00010000U) /* Write protection of Sector0 */
#define OB_WRP_SECTOR_1       ((T_UINT32)0x00020000U) /* Write protection of Sector1 */
#define OB_WRP_SECTOR_2       ((T_UINT32)0x00040000U) /* Write protection of Sector2 */
#define OB_WRP_SECTOR_3       ((T_UINT32)0x00080000U) /* Write protection of Sector3 */
#define OB_WRP_SECTOR_4       ((T_UINT32)0x00100000U) /* Write protection of Sector4 */
#define OB_WRP_SECTOR_5       ((T_UINT32)0x00200000U) /* Write protection of Sector5 */
#define OB_WRP_SECTOR_6       ((T_UINT32)0x00400000U) /* Write protection of Sector6 */
#define OB_WRP_SECTOR_7       ((T_UINT32)0x00800000U) /* Write protection of Sector7 */
#define OB_WRP_SECTOR_ALL     ((T_UINT32)0x00FF0000U) /* Write protection of all Sectors */

#endif /* FLASH_SECTOR_TOTAL == 8 */

#define __HAL_FLASH_CALC_BOOT_BASE_ADR(__ADDRESS__) ((__ADDRESS__) >> 14)


#define IS_FLASH_TYPEERASE(VALUE)(((VALUE) == FLASH_TYPEERASE_SECTORS) || \
                                  ((VALUE) == FLASH_TYPEERASE_MASSERASE))

#define IS_VOLTAGERANGE(RANGE)(((RANGE) == FLASH_VOLTAGE_RANGE_1) || \
                               ((RANGE) == FLASH_VOLTAGE_RANGE_2) || \
                               ((RANGE) == FLASH_VOLTAGE_RANGE_3) || \
                               ((RANGE) == FLASH_VOLTAGE_RANGE_4))

#define IS_WRPSTATE(VALUE)(((VALUE) == OB_WRPSTATE_DISABLE) || \
                           ((VALUE) == OB_WRPSTATE_ENABLE))

#define IS_OPTIONBYTE(VALUE)(((VALUE) <= (OPTIONBYTE_WRP | OPTIONBYTE_RDP | OPTIONBYTE_USER |\
                                          OPTIONBYTE_BOR | OPTIONBYTE_BOOTADDR_0 | \
                                          OPTIONBYTE_BOOTADDR_1)))

#define IS_OB_BOOT_ADDRESS(ADDRESS) ((ADDRESS) <= 0x8013)

#define IS_OB_RDP_LEVEL(LEVEL) (((LEVEL) == OB_RDP_LEVEL_0)   ||\
                                ((LEVEL) == OB_RDP_LEVEL_1)   ||\
                                ((LEVEL) == OB_RDP_LEVEL_2))

#define IS_OB_WWDG_SOURCE(SOURCE) (((SOURCE) == OB_WWDG_SW) || ((SOURCE) == OB_WWDG_HW))

#define IS_OB_IWDG_SOURCE(SOURCE) (((SOURCE) == OB_IWDG_SW) || ((SOURCE) == OB_IWDG_HW))

#define IS_OB_STOP_SOURCE(SOURCE) (((SOURCE) == OB_STOP_NO_RST) || ((SOURCE) == OB_STOP_RST))

#define IS_OB_STDBY_SOURCE(SOURCE) (((SOURCE) == OB_STDBY_NO_RST) || ((SOURCE) == OB_STDBY_RST))

#define IS_OB_IWDG_STOP_FREEZE(FREEZE) (((FREEZE) == OB_IWDG_STOP_FREEZE) || \
                                       ((FREEZE) == OB_IWDG_STOP_ACTIVE))

#define IS_OB_IWDG_STDBY_FREEZE(FREEZE) (((FREEZE) == OB_IWDG_STDBY_FREEZE) || \
                                       ((FREEZE) == OB_IWDG_STDBY_ACTIVE))

#define IS_OB_BOR_LEVEL(LEVEL) (((LEVEL) == OB_BOR_LEVEL1) || ((LEVEL) == OB_BOR_LEVEL2) ||\
                                ((LEVEL) == OB_BOR_LEVEL3) || ((LEVEL) == OB_BOR_OFF))

#define IS_FLASH_LATENCY(LATENCY) (((LATENCY) == FLASH_LATENCY_0)  || \
                                   ((LATENCY) == FLASH_LATENCY_1)  || \
                                   ((LATENCY) == FLASH_LATENCY_2)  || \
                                   ((LATENCY) == FLASH_LATENCY_3)  || \
                                   ((LATENCY) == FLASH_LATENCY_4)  || \
                                   ((LATENCY) == FLASH_LATENCY_5)  || \
                                   ((LATENCY) == FLASH_LATENCY_6)  || \
                                   ((LATENCY) == FLASH_LATENCY_7)  || \
                                   ((LATENCY) == FLASH_LATENCY_8)  || \
                                   ((LATENCY) == FLASH_LATENCY_9)  || \
                                   ((LATENCY) == FLASH_LATENCY_10) || \
                                   ((LATENCY) == FLASH_LATENCY_11) || \
                                   ((LATENCY) == FLASH_LATENCY_12) || \
                                   ((LATENCY) == FLASH_LATENCY_13) || \
                                   ((LATENCY) == FLASH_LATENCY_14) || \
                                   ((LATENCY) == FLASH_LATENCY_15))

#define IS_FLASH_ADDRESS(ADDRESS) (((ADDRESS) >= FLASH_BASE) && ((ADDRESS) <= FLASH_END))

#define IS_FLASH_NBSECTORS(NBSECTORS) (((NBSECTORS) != 0U) && ((NBSECTORS) <= FLASH_SECTOR_TOTAL))

#if (FLASH_SECTOR_TOTAL == 8)
#define IS_FLASH_SECTOR(SECTOR) (((SECTOR) == FLASH_SECTOR_0)   || ((SECTOR) == FLASH_SECTOR_1) ||\
                                 ((SECTOR) == FLASH_SECTOR_2)   || ((SECTOR) == FLASH_SECTOR_3) ||\
                                 ((SECTOR) == FLASH_SECTOR_4)   || ((SECTOR) == FLASH_SECTOR_5) ||\
                                 ((SECTOR) == FLASH_SECTOR_6)   || ((SECTOR) == FLASH_SECTOR_7))

#define IS_OB_WRP_SECTOR(SECTOR)  ((((SECTOR) & 0xFF00FFFFU) == 0x00000000U) && \
                                    ((SECTOR) != 0x00000000U))
#endif /* FLASH_SECTOR_TOTAL == 8 */

extern void FLASH_Erase_Sector(T_UINT32 Sector, T_UINT8 VoltageRange);

#endif
