/*
 ******************************************************************************
 * License Information  :  Howell Instruments, Inc.                           *
 *                         "Licensed Software" and "All rights reserved".     *
 ******************************************************************************
 *  File                : hdulibstm32f7xxhalpwrex.c
 *
 *  Description         : This file provides firmware functions to manage functionalities
 *                        of PWR extension peripheral and Peripheral Extended features functions
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
 * <Version No.>      <Author>          <Date>         <Problem Report No.>
 *
 *      1.1           Shilpa A R      28-Jul-2017           -
 *      1.2           Divya G P       02-Sep-2017      100028
 *
 * Additional References : None
 *
 ******************************************************************************
 */

/* Includes */
#include "hdulibstm32f7xxhal.h"        /* Header files for HAL driver*/
#include "hdulibbasictypes.h"          /* Contains basic data types*/
#include "hdulibstm32f7xxhalpwr.h"     /* Header files for PWR HAL  driver*/
#include "hdulibstm32f7xxhalrcc.h"     /* Header files for RCC HAL driver*/
#include "hdulibstm32f7xxhalpwrex.h"   /* Header file of PWR HAL Extension module. */
#include "hdulibstm32f7xxhaldef.h"     /*Contains the HAL defination module */
#include "hdulibstm32f746xx.h"         /* CMSIS Cortex-M7 Device Peripheral Access Layer */

#define PWR_OVERDRIVE_TIMEOUT_VALUE  1000U

/*
 * Function                :  HalPwrExEnableOverDrive
 *
 * Description             :  This function Activates the Over-Drive mode.
 *
 * Formal parameter(s)     :  None
 *
 * Return Value            :  T_HAL_STATUS - HAL status
 *
 * Assumption              :  None
 *
 */
T_HAL_STATUS HalPwrExEnableOverDrive(void)
{
   T_UINT32 tick_start = ZERO;

   /*hdulibstm32f7xxhalpwrex-HalPwrExEnableOverDrive-DB-LLR-001*/
   /* enable the RCC peripheral clock */
   __HAL_RCC_PWR_CLK_ENABLE();

   /*hdulibstm32f7xxhalpwrex-HalPwrExEnableOverDrive-DB-LLR-002*/
   /* Enable the Over-drive to extend the clock frequency to 216 MHz */
   __HAL_PWR_OVERDRIVE_ENABLE();

   /*hdulibstm32f7xxhalpwrex-HalPwrExEnableOverDrive-DB-LLR-003*/
   /* Get tick */
   tick_start = HALGetTick();

   /*hdulibstm32f7xxhalpwrex-HalPwrExEnableOverDrive-DB-LLR-004*/
   while(ZERO == __HAL_PWR_GET_FLAG(PWR_FLAG_ODRDY))
   {
      if((HALGetTick() - tick_start ) > PWR_OVERDRIVE_TIMEOUT_VALUE)
      {
         /* Return HAL_TIMEOUT */
         return HAL_TIMEOUT;
      }
      else
      {
         ;/* does nothing */
      }
   }

   /*hdulibstm32f7xxhalpwrex-HalPwrExEnableOverDrive-DB-LLR-005*/
   /* Enable the Over-drive switch */
   __HAL_PWR_OVERDRIVESWITCH_ENABLE();

   /*hdulibstm32f7xxhalpwrex-HalPwrExEnableOverDrive-DB-LLR-006*/
   /* Get tick */
   tick_start = HALGetTick();

   /*hdulibstm32f7xxhalpwrex-HalPwrExEnableOverDrive-DB-LLR-007*/
   while(ZERO == __HAL_PWR_GET_FLAG(PWR_FLAG_ODSWRDY))
   {
      if((HALGetTick() - tick_start ) > PWR_OVERDRIVE_TIMEOUT_VALUE)
      {
         /* Return HAL_TIMEOUT */
         return HAL_TIMEOUT;
      }
      else
      {
         ;/* does nothing */
      }
   }
   /*hdulibstm32f7xxhalpwrex-HalPwrExEnableOverDrive-DB-LLR-008*/
   /* Return HAL_OK */
   return HAL_OK;
}
