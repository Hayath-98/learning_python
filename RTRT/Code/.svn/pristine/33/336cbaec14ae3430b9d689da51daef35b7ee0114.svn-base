/*
 ******************************************************************************
 * License Information  :  Howell Instruments, Inc.                           *
 *                         "Licensed Software" and "All rights reserved".     *
 ******************************************************************************
 *  File                : hdulibstm32f7xxhalflash.h
 *
 *  Description         : Header file of FLASH HAL module.
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

/* Define to prevent recursive inclusion*/
#ifndef _HDULIBSTM32F7XXHALFLASH_H_
#define _HDULIBSTM32F7XXHALFLASH_H_

/* Includes */
#include "hdulibstm32f7xxhalflashex.h" /* Header file of FLASH HAL Extension module. */
#include "hdulibstm32f7xxhaldef.h"     /* Header file of CORTEX HAL module */
#include "hdulibstm32f746xx.h"         /* CMSIS Cortex-M7 Device Peripheral Access Layer */
#include "hdulibstm32f7xx.h"           /* CMSIS STM32F7xx Peripheral Access Layer Header File.*/
#include "hdulibbasictypes.h"          /* Contains all the basic data types.*/

typedef enum
{
  FLASH_PROC_NONE = 0U,
  FLASH_PROC_SECTERASE,
  FLASH_PROC_MASSERASE,
  FLASH_PROC_PROGRAM
} T_FLASH_PROCEDURE;

typedef struct
{
   /* Internal variable to indicate which procedure is ongoing or not in IT context */
   __IO T_FLASH_PROCEDURE ProcedureOnGoing;

   /* Internal variable to save the remaining sectors to erase in IT context        */
   __IO T_UINT32               NbSectorsToErase;

   /* Internal variable to provide voltage range selected by user in IT context     */
   __IO T_UINT8                VoltageForErase;

   /* Internal variable to define the current sector which is erasing               */
   __IO T_UINT32               Sector;

   /* Internal variable to save address selected for program */
   __IO T_UINT32               Address;

  T_HAL_LOCK                   Lock;         /* FLASH locking object */

   __IO T_UINT32               ErrorCode;   /* FLASH error code */

}T_FLASH_PROCESS;

#define HAL_FLASH_ERROR_NONE         ((T_UINT32)0x00000000U)    /* No error */
#define HAL_FLASH_ERROR_ERS          ((T_UINT32)0x00000002U)    /* Programming Sequence error */
#define HAL_FLASH_ERROR_PGP          ((T_UINT32)0x00000004U)    /* Programming Parallelism error */
#define HAL_FLASH_ERROR_PGA          ((T_UINT32)0x00000008U)    /* Programming Alignment error */
#define HAL_FLASH_ERROR_WRP          ((T_UINT32)0x00000010U)    /* Write protection error */
#define HAL_FLASH_ERROR_OPERATION    ((T_UINT32)0x00000020U)    /* Operation Error */

/* Program byte (8-bit) at a specified address */
#define FLASH_TYPEPROGRAM_BYTE        ((T_UINT32)0x00U)
/* Program a half-word (16-bit) at a specified address   */
#define FLASH_TYPEPROGRAM_HALFWORD    ((T_UINT32)0x01U)
/* Program a word (32-bit) at a specified address */
#define FLASH_TYPEPROGRAM_WORD        ((T_UINT32)0x02U)
/* Program a double word (64-bit) at a specified address */
#define FLASH_TYPEPROGRAM_DOUBLEWORD  ((T_UINT32)0x03U)

#define FLASH_FLAG_EOP         FLASH_SR_EOP       /* FLASH End of Operation flag */
#define FLASH_FLAG_OPERR       FLASH_SR_OPERR     /* FLASH operation Error flag */
#define FLASH_FLAG_WRPERR      FLASH_SR_WRPERR    /* FLASH Write protected error flag */
#define FLASH_FLAG_PGAERR      FLASH_SR_PGAERR    /* FLASH Programming Alignment error flag */
#define FLASH_FLAG_PGPERR      FLASH_SR_PGPERR    /* FLASH Programming Parallelism error flag  */
#define FLASH_FLAG_ERSERR      FLASH_SR_ERSERR    /* FLASH Erasing Sequence error flag */
#define FLASH_FLAG_BSY         FLASH_SR_BSY       /* FLASH Busy flag */

/* End of FLASH Operation Interrupt source */
#define FLASH_FLAG_ALL_ERRORS     (FLASH_FLAG_OPERR   | FLASH_FLAG_WRPERR | FLASH_FLAG_PGAERR | \
                                   FLASH_FLAG_PGPERR  | FLASH_FLAG_ERSERR)
#define FLASH_IT_EOP               FLASH_CR_EOPIE
#define FLASH_IT_ERR               ((T_UINT32)0x02000000U)  /* Error Interrupt source */
#define FLASH_PSIZE_BYTE           ((T_UINT32)0x00000000U)
#define FLASH_PSIZE_HALF_WORD      ((T_UINT32)FLASH_CR_PSIZE_0)
#define FLASH_PSIZE_WORD           ((T_UINT32)FLASH_CR_PSIZE_1)
#define FLASH_PSIZE_DOUBLE_WORD    ((T_UINT32)FLASH_CR_PSIZE)
#define CR_PSIZE_MASK              ((T_UINT32)0xFFFFFCFFU)

#define FLASH_KEY1               ((T_UINT32)0x45670123U)
#define FLASH_KEY2               ((T_UINT32)0xCDEF89ABU)
#define FLASH_OPT_KEY1           ((T_UINT32)0x08192A3BU)
#define FLASH_OPT_KEY2           ((T_UINT32)0x4C5D6E7FU)

#define FLASH_SECTOR_0           ((T_UINT32)0U) /*!< Sector Number 0   */
#define FLASH_SECTOR_1           ((T_UINT32)1U) /*!< Sector Number 1   */
#define FLASH_SECTOR_2           ((T_UINT32)2U) /*!< Sector Number 2   */
#define FLASH_SECTOR_3           ((T_UINT32)3U) /*!< Sector Number 3   */
#define FLASH_SECTOR_4           ((T_UINT32)4U) /*!< Sector Number 4   */
#define FLASH_SECTOR_5           ((T_UINT32)5U) /*!< Sector Number 5   */
#define FLASH_SECTOR_6           ((T_UINT32)6U) /*!< Sector Number 6   */
#define FLASH_SECTOR_7           ((T_UINT32)7U) /*!< Sector Number 7   */

#define __HAL_FLASH_SET_LATENCY(__LATENCY__) \
                  (MODIFY_REG(FLASH->ACR, FLASH_ACR_LATENCY, (T_UINT32)(__LATENCY__)))

#define __HAL_FLASH_GET_LATENCY()     (READ_BIT((FLASH->ACR), FLASH_ACR_LATENCY))


#define __HAL_FLASH_PREFETCH_BUFFER_EN()  (FLASH->ACR |= FLASH_ACR_PRFTEN)


#define __HAL_FLASH_PREFETCH_BUFFER_DIS()   (FLASH->ACR &= (~FLASH_ACR_PRFTEN))


#define __HAL_FLASH_ART_ENABLE()  (SET_BIT(FLASH->ACR, FLASH_ACR_ARTEN))


#define __HAL_FLASH_ART_DISABLE()   (CLEAR_BIT(FLASH->ACR, FLASH_ACR_ARTEN))


#define __HAL_FLASH_ART_RESET()  (FLASH->ACR |= FLASH_ACR_ARTRST)


#define __HAL_FLASH_ENABLE_IT(__INTERRUPT__)  (FLASH->CR |= (__INTERRUPT__))


#define __HAL_FLASH_DISABLE_IT(__INTERRUPT__)  (FLASH->CR &= ~(T_UINT32)(__INTERRUPT__))

#define __HAL_FLASH_GET_FLAG(__FLAG__)   ((FLASH->SR & (__FLAG__)))


#define __HAL_FLASH_CLEAR_FLAG(__FLAG__)   (FLASH->SR = (__FLAG__))


#define OPTCR_BYTE1_ADDRESS         ((T_UINT32)0x40023C15)

#define IS_FLASH_TYPEPROGRAM(VALUE)(((VALUE) == FLASH_TYPEPROGRAM_BYTE) || \
                                    ((VALUE) == FLASH_TYPEPROGRAM_HALFWORD) || \
                                    ((VALUE) == FLASH_TYPEPROGRAM_WORD) || \
                                    ((VALUE) == FLASH_TYPEPROGRAM_DOUBLEWORD))

#endif
