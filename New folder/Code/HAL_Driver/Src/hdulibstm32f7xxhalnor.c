/*
 ******************************************************************************
 * License Information  :  Howell Instruments, Inc.                           *
 *                         "Licensed Software" and "All rights reserved".     *
 ******************************************************************************
 *  File                : hdulibstm32f7xxhalnor.c
 *
 *  Description         : This file provides a generic firmware to drive NOR memories mounted
 *                        as external device.
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
 *  Author(s)           : Rona B.S
 *
 *  Version History     :
 * <Version No.>     <Author>          <Date>         <Problem Report No.>
 *
 *      1.1          Rona B.S          12-Sep-2017            100064
 *
 * Additional References : None
 *
 ******************************************************************************
 */

/* Includes */
#include "hdulibstm32f7xxhalfmc.h" /* Defines FMC specification */
#include "hdulibstm32f7xxhalnor.h" /* Defines NOR specification */
#include "hdulibstm32f7xxhalconf.h" /* contains HAL common defines,enum,macro and structures */
#include "hdulibstm32f7xxhal.h"/* Header files for HAL driver*/

static T_UINT32 Nor_memory_data_width  = NOR_MEMORY_8B;

/*
 * Function                :  HalNorInit
 *
 * Description             :  This function performs the NOR memory
 *                            Initialization sequence.
 *
 * Formal parameter(s)     :  T_NOR_HANDLE_TYPE *h_nor - IN/OUT pointer to a
 *                            NOR_HandleTypeDef structure that contains the
 *                            configuration information for NOR module.
 *                            T_FMC_NORSRAM_TIMING *timing - IN pointer to NOR
 *                            control timing structure.
 *                            T_FMC_NORSRAM_TIMING *ext_timing - IN pointer to
 *                            NOR extended mode timing structure
 *
 * Return Value            :  T_HAL_STATUS - returns HAL status
 *
 * Assumption              :  None
 *
 */

T_HAL_STATUS HalNorInit(T_NOR_HANDLE_TYPE *h_nor, T_FMC_NORSRAM_TIMING *timing,
      T_FMC_NORSRAM_TIMING *ext_timing)
{
   /* hdulibstm32f7xxhalnor-HalNorInit-DB-LLR-001 */
   /* Check the NOR handle parameter */
   if(NULL == h_nor)
   {
      return HAL_ERROR;
   }
   else
   {
      ; /* Do nothing */
   }

   /* hdulibstm32f7xxhalnor-HalNorInit-DB-LLR-002 */
   if(HAL_NOR_STATE_RESET == h_nor->State)
   {
      /* Allocate lock resource and initialize it */
      h_nor->Lock = HAL_UNLOCKED;

      /* Initialize the low level hardware (MSP) */
      HalNorMspInit(h_nor);

   }
   else
   {
      ; /* Do nothing */
   }

   /* hdulibstm32f7xxhalnor-HalNorInit-DB-LLR-003 */
   /* Initialize NOR control Interface */
   FmcNorSramInit(h_nor->Instance, &(h_nor->Init));

   /* Initialize NOR timing Interface */
   FmcNorSramTimingInit(h_nor->Instance, timing, h_nor->Init.NSBank);

   /* Initialize NOR extended mode timing Interface */
   FmcNorSramExtendedTimingInit(h_nor->Extended, ext_timing, h_nor->Init.NSBank,
            h_nor->Init.ExtendedMode);

   /* Enable the NORSRAM device */
   __FMC_NORSRAM_ENABLE(h_nor->Instance, h_nor->Init.NSBank);

   /* Set NOR Memory Data Width*/
   if (FMC_NORSRAM_MEM_BUS_WIDTH_8 == h_nor->Init.MemoryDataWidth)
   {
      /* hdulibstm32f7xxhalnor-HalNorInit-DB-LLR-004 */
      Nor_memory_data_width = NOR_MEMORY_8B;
   }
   else
   {
      /* hdulibstm32f7xxhalnor-HalNorInit-DB-LLR-005 */
      Nor_memory_data_width = NOR_MEMORY_16B;
   }

   /* hdulibstm32f7xxhalnor-HalNorInit-DB-LLR-006 */
   /* Set the NOR controller state */
   h_nor->State = HAL_NOR_STATE_READY;

   /* hdulibstm32f7xxhalnor-HalNorInit-DB-LLR-007 */
   return HAL_OK;
}

/*
 * Function                :  HalNorMspInit
 *
 * Description             :  This function is used to initialize the NOR MSP.
 *
 * Formal parameter(s)     :  T_NOR_HANDLE_TYPE *h_nor: IN pointer to a
 *                            NOR_HandleTypeDef structure that contains
 *                            the configuration information for NOR module.
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */

void HalNorMspInit(T_NOR_HANDLE_TYPE *h_nor)
{
   /* hdulibstm32f7xxhalnor-HalNorMspInit-DB-LLR-001 */
   /* Prevent unused argument(s) compilation warning */
   UNUSED(h_nor);
}

