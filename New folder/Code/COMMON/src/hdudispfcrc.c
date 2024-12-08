/*
 ******************************************************************************
 * License Information  :  Howell Instruments, Inc.                           *
 *                         "Licensed Software" and "All rights reserved".     *
 ******************************************************************************
 *  File                : hdudispfcrc.c
 *
 *  Description         : This file contains routines for CRC calculations.
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
 *
 * <Version No.>     <Author>          <Date>         <Problem Report No.>
 *
 *      1.1          Rona B.S        11-Sep-2017             100064
 *      1.2          Rona B.S        10-Oct-2017             100064
 *      1.3          Shilpa A R      09-Nov-2017             100164
 *
 * Additional References : None
 *
 *****************************************************************************
 */

#include "hdudispfcrc.h" /* contains the common defines and functions prototypes for CRC*/
#include "hdulibstm32f7xxhalrcc.h"  /* Header files for RCC HAL driver*/
#include "hdulibstm32f7xxhalcrc.h"  /* Header files for CRC EX HAL module */

static T_CRC_HANDLE   Crc_handle = {0};

/*
 * Function                :  CrcInit
 *
 * Description             :  This function initializes the CRC unit.
 *
 * Formal parameter(s)     :  None
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */

static void CrcInit(void)
{
   /*hdudispfcrc-CrcInit-DB-LLR-001*/
   Crc_handle.Instance = CRC;

   /* The default polynomial is used */
   Crc_handle.Init.DefaultPolynomialUse    = DEFAULT_POLYNOMIAL_ENABLE;

   /* The default init value is used */
   Crc_handle.Init.DefaultInitValueUse     = DEFAULT_INIT_VALUE_ENABLE;

   /* The input data are not inverted */
   Crc_handle.Init.InputDataInversionMode  = CRC_INPUTDATA_INVERSION_NONE;

   /* The output data are not inverted */
   Crc_handle.Init.OutputDataInversionMode = CRC_OUTPUTDATA_INVERSION_DISABLE;

   /* The input data are 32 bits lenght */
   Crc_handle.InputDataFormat              = CRC_INPUTDATA_FORMAT_WORDS;

   HalCrcInit(&Crc_handle);
}

/*
 * Function                :  CrcCalculate
 *
 * Description             :  This function is used to calculate the CRC.
 *
 * Formal parameter(s)     :  T_UINT32 *u32_buffer - IN  pointer to the input data buffer
 *                            T_UINT32 u32_buffer_length -IN input data buffer length
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */

T_UINT32 CrcCalculate(T_UINT32 *u32_buffer, T_UINT32 u32_buffer_length)
{
   T_UINT32 u32_crc_value = ZERO;

   /* Updated as per PR 100164 */
   /*hdudispfcrc- CrcCalculate-DB-LLR-001*/
   /*Initializes the CRC unit */
   CrcInit();

   /*hdudispfcrc- CrcCalculate-DB-LLR-002*/
   /*Calculates the CRC value */
   u32_crc_value = HalCrcAccumulate(&Crc_handle, u32_buffer, u32_buffer_length);

   /*Returns the CRC value obatined */
   return(u32_crc_value);
}
