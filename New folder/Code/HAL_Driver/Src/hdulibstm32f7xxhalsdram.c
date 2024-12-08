/*
 ******************************************************************************
 * License Information  :  Howell Instruments, Inc.                           *
 *                         "Licensed Software" and "All rights reserved".     *
 ******************************************************************************
 *  File                : hdulibstm32f7xxhalsdram.c
 *
 *  Description         : This file provides a generic firmware to drive SDRAM memories mounted
 *                      as external device.
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
 *      1.1          Vinay H         27-Jul-2017             -
 *      1.2          Divya G P       02-Sep-2017          100028
 *
 * Additional References : None
 *
 ******************************************************************************
 */

/* Includes */
#include "hdulibstm32f7xxhal.h"        /* Header file of HAL module.*/
#include "hdulibstm32f7xxhalfmc.h"      /* Header file of FMC HAL module.*/
#include "hdulibstm32f7xxhalsdram.h"   /* Header file of SDRAM HAL module.*/
#include "hdulibstm32f7xxhaldef.h"     /*Contains the HAL definition module */

/*
 * Function                :  HALSdramInit
 *
 * Description             :  This function performs the SDRAM device initialization sequence.
 *
 * Formal parameter(s)     :  T_SDRAM_HANDLE *h_sdram - INOUT pointer to a T_SDRAM_HANDLE structure
 *                            that contains the configuration information for SDRAM module.
 *                            T_FMC_SDRAM_TIMING *timing - IN Pointer to SDRAM control
 *                            timing structure
 *
 * Return Value            :  T_HAL_STATUS - returns SDRAM initialization status
 *
 * Assumption              :  None
 *
 */
T_HAL_STATUS HALSdramInit(T_SDRAM_HANDLE *h_sdram, T_FMC_SDRAM_TIMING *timing)
{
   /*hdulibstm32f7xxhalsdram-HALSdramInit-DB-LLR-001*/
   /* Check the SDRAM handle parameter */
   if(NULL == h_sdram)
   {
      return HAL_ERROR;
   }
   else
   {
      ;/*Do nothing*/
   }

   /*hdulibstm32f7xxhalsdram-HALSdramInit-DB-LLR-002*/
   if(HAL_SDRAM_STATE_RESET == h_sdram->State)
   {
      /* Allocate lock resource and initialize it */
      h_sdram->Lock = HAL_UNLOCKED;

      /* Initialize the low level hardware (MSP) */
      HALSdramMspInit(h_sdram);
   }
   else
   {
      ;/*Do nothing*/
   }

   /*hdulibstm32f7xxhalsdram-HALSdramInit-DB-LLR-003*/
   /* Initialize the SDRAM controller state */
   h_sdram->State = HAL_SDRAM_STATE_BUSY;

   /*hdulibstm32f7xxhalsdram-HALSdramInit-DB-LLR-004*/
   /* Initialize SDRAM control Interface */
   FmcSdramInit(h_sdram->Instance, &(h_sdram->Init));

   /*hdulibstm32f7xxhalsdram-HALSdramInit-DB-LLR-005*/
   /* Initialize SDRAM timing Interface */
   FmcSdramTimingInit(h_sdram->Instance, timing, h_sdram->Init.SDBank);

   /*hdulibstm32f7xxhalsdram-HALSdramInit-DB-LLR-006*/
   /* Update the SDRAM controller state */
   h_sdram->State = HAL_SDRAM_STATE_READY;

   return HAL_OK;
}

/*
 * Function                :  HALSdramMspInit
 *
 * Description             :  This function performs SDRAM MSP Init.
 *
 * Formal parameter(s)     :  T_SDRAM_HANDLE *h_sdram - IN pointer to a T_SDRAM_HANDLE structure
 *                            that contains the configuration information for SDRAM module.
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */
void HALSdramMspInit(T_SDRAM_HANDLE *h_sdram)
{
   /*hdulibstm32f7xxhalsdram-HALSdramMspInit-DB-LLR-001*/
   /* Prevent unused argument(s) compilation warning */
   UNUSED(h_sdram);
}

/*
 * Function                :  HalSdramSendCommand
 *
 * Description             :  This function Sends command to the SDRAM bank.
 *
 * Formal parameter(s)     :  T_SDRAM_HANDLE *h_sdram - INOUT pointer to a T_SDRAM_HANDLE structure
 *                            that containsthe configuration information for SDRAM module.
 *                            T_FMC_SDRAM_COMMAND *command - IN SDRAM command structure
 *                            T_UINT32 timeout - IN timeout duration
 *
 * Return Value            :  T_HAL_STATUS - returns status of SDRAM bank status
 *
 * Assumption              :  None
 *
 */
T_HAL_STATUS HalSdramSendCommand(T_SDRAM_HANDLE *h_sdram, T_FMC_SDRAM_COMMAND *command,
                                 T_UINT32 timeout)
{
   /*hdulibstm32f7xxhalsdram-HalSdramSendCommand-DB-LLR-001*/
   /* Check the SDRAM controller state */
   if(HAL_SDRAM_STATE_BUSY == h_sdram->State)
   {
      return HAL_BUSY;
   }
   else
   {
      ;/*Do nothing*/
   }

   /*hdulibstm32f7xxhalsdram-HalSdramSendCommand-DB-LLR-002*/
   /* Update the SDRAM state */
   h_sdram->State = HAL_SDRAM_STATE_BUSY;

   /*hdulibstm32f7xxhalsdram-HalSdramSendCommand-DB-LLR-003*/
   /* Send SDRAM command */
   FmcSdramSendCommand(h_sdram->Instance, command, timeout);

   /*hdulibstm32f7xxhalsdram-HalSdramSendCommand-DB-LLR-004*/
   /* Update the SDRAM controller state state */
   if(FMC_SDRAM_CMD_PALL == command->CommandMode)
   {
      h_sdram->State = HAL_SDRAM_STATE_PRECHARGED;
   }
   else
   {
      h_sdram->State = HAL_SDRAM_STATE_READY;
   }
   /*hdulibstm32f7xxhalsdram-HalSdramSendCommand-DB-LLR-005*/
   return HAL_OK;
}

/*
 * Function                :  HalSdramProgramRefreshRate
 *
 * Description             :  This function Programs the SDRAM Memory Refresh rate.
 *
 * Formal parameter(s)     :  T_SDRAM_HANDLE *h_sdram - INOUT pointer to a T_SDRAM_HANDLE structure
 *                            that containsthe configuration information for SDRAM module.
 *                            T_UINT32 refresh_rate - IN The SDRAM refresh rate value
 *
 * Return Value            :  T_HAL_STATUS - returns SDRAM memory availability
 *
 * Assumption              :  None
 *
 */
T_HAL_STATUS HalSdramProgramRefreshRate(T_SDRAM_HANDLE *h_sdram, T_UINT32 refresh_rate)
{
   /*hdulibstm32f7xxhalsdram-HalSdramProgramRefreshRate-DB-LLR-001*/
   /* Check the SDRAM controller state */
   if(HAL_SDRAM_STATE_BUSY == h_sdram->State)
   {
      return HAL_BUSY;
   }
   else
   {
      ;/*Do nothing*/
   }

   /*hdulibstm32f7xxhalsdram-HalSdramProgramRefreshRate-DB-LLR-002*/
   /* Update the SDRAM state */
   h_sdram->State = HAL_SDRAM_STATE_BUSY;

   /*hdulibstm32f7xxhalsdram-HalSdramProgramRefreshRate-DB-LLR-003*/
   /* Program the refresh rate */
   FmcSdramProgramRefreshRate(h_sdram->Instance ,refresh_rate);

   /*hdulibstm32f7xxhalsdram-HalSdramProgramRefreshRate-DB-LLR-004*/
   /* Update the SDRAM state */
   h_sdram->State = HAL_SDRAM_STATE_READY;

   return HAL_OK;
}
