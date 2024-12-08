/*
 ******************************************************************************
 * License Information  :  Howell Instruments, Inc.                           *
 *                         "Licensed Software" and "All rights reserved".     *
 ******************************************************************************
 *  File                : hdudispbcrc.c
 *
 *  Description         :The hdudispbcrc CSC contains routines for CRC calculations.
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
 *      1.1          Rona B.S        02-Aug-2017             -
 *      1.2          Divya G P       01-Sep-2017           100028
 *      1.3          Rona B.S        04-Nov-2017           100156
 *      1.4          Rona B.S        05-Jul-2020           100259
 *
 * Additional References : None
 *
 *****************************************************************************
 */

/* Includes*/
#include "hdulibstm32f7xxhalcrcex.h"   /* Header files for CRC EX HAL module */
#include "hdudispbcrc.h"             /* Contains functions prototypes of hdudispbcrc*/
#include "hdulibbasictypes.h"           /* Basic data types.*/
#include "hdudispbboot.h"            /* Contains functions prototypes of hdudispbfonts*/
#include "hdulibstm32f7xxhalcrc.h"   /* Header files for CRC HAL module */
#include "hdulibstm32f7xxhaldef.h"   /*Contains the HAL definition module */

static T_CRC_HANDLE   Crc_handle = {ZERO};

/*
 * Function                :  VCRCInit
 *
 * Description             :  This function initializes the CRC unit.
 *
 *
 * Formal parameter(s)     :  None
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */

static void VCRCInit(void)
{

   /*hdudispbcrc-VCRCInit-DB-LLR-001*/
   Crc_handle.Instance = CRC;

   /* The default polynomial is used */
   Crc_handle.Init.DefaultPolynomialUse    = DEFAULT_POLYNOMIAL_ENABLE;

   /* The default init value is used */
   Crc_handle.Init.DefaultInitValueUse     = DEFAULT_INIT_VALUE_ENABLE;

   /* The input data are not inverted */
   Crc_handle.Init.InputDataInversionMode  = CRC_INPUTDATA_INVERSION_NONE;

   /* The output data are not inverted */
   Crc_handle.Init.OutputDataInversionMode = CRC_OUTPUTDATA_INVERSION_DISABLE;

   /* The input data are 32 bits length */
   Crc_handle.InputDataFormat              = CRC_INPUTDATA_FORMAT_WORDS;

   /*hdudispbcrc-VCRCInit-DB-LLR-002*/
   if (HalCrcInit(&Crc_handle) != HAL_OK)
   {
      while(ONE);
   }
   else
   {
      ;/*Do nothing*/
   }
}


/*
 * Function                :  CRCRom
 *
 * Description             :  This function is used to calculate the CRC
 *
 * Formal parameter(s)     :  T_SBOOTFILE *ps_boot_file - IN Where the file will be loaded.
 *
 * Return Value            :  T_UINT8 - returns CRC calculation status
 *
 * Assumption              :  None
 *
 */

T_UINT8 CRCRom(T_SBOOTFILE *ps_boot_file)
{
   T_UINT32             u32_flash_crc = ZERO;
   volatile T_UINT32    u32_crc_value = ZERO;
   T_UINT32             *pu32_flash_crc = ZERO;
   T_UINT8              result = ZERO;

   /* Initialize the CRC unit. */
   /*hdudispbcrc-CRCRom-DB-LLR-001*/
   VCRCInit();

   /*hdudispbcrc-CRCRom-DB-LLR-002*/
    u32_crc_value = HalCrcAccumulate(&Crc_handle, (T_UINT32 *)(ps_boot_file->u32LoadAddr),
                    ((ps_boot_file->u32LoadSize)/FOUR)-ONE);
   /*hdudispbcrc-CRCRom-DB-LLR-003*/
   pu32_flash_crc = (T_UINT32 *)((ps_boot_file->u32LoadAddr) + ((ps_boot_file->u32LoadSize))
                    - FOUR);

   u32_flash_crc = *pu32_flash_crc;

   if(u32_crc_value == u32_flash_crc)
   {
    /*hdudispbcrc-CRCRom-DB-LLR-004*/
      result = ONE;
   }
   else
   {
    /*hdudispbcrc-CRCRom-DB-LLR-004*/
     result = ZERO;
   }
     /*hdudispbcrc-CRCRom-DB-LLR-005*/
   return result;
}
