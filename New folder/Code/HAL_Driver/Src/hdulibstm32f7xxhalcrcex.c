/*
 ******************************************************************************
 * License Information  :  Howell Instruments, Inc.                           *
 *                         "Licensed Software" and "All rights reserved".     *
 ******************************************************************************
 *  File                : hdulibstm32f7xxhalcrcex.c
 *
 *  Description         : This file provides firmware functions to manage the
 *                        functionalities of the CRC peripheral.
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
 *      1.1           Shilpa A R    28-Jul-2017          -
 *      1.2           Divya G P     01-Sep-2017        100028
 *
 * Additional References : None
 *
 ******************************************************************************
 */

/* Includes */
#include "hdulibstm32f7xxhal.h"           /* Header files for HAL driver*/
#include "hdulibstm32f7xxhalcrcex.h"      /* Header files for CRC EX HAL driver*/
#include "hdulibstm32f7xxhalcrc.h"        /* Header files for CRC HAL driver*/
#include "hdulibbasictypes.h"             /* Contains basic data types*/
#include "hdulibstm32f7xxhaldef.h"        /* Header file of CORTEX HAL module */
#include "hdulibstm32f7xx.h"              /* CMSIS Cortex-M7 Device Peripheral Access Layer */
#include "hdulibstm32f746xx.h"          /* CMSIS STM32F7xx Peripheral Access Layer Header File.*/

/*
 * Function                :  HalCrcExPolynomialSet
 *
 * Description             :  This function initializes the CRC polynomial if different
 *                            from default one.
 *
 * Formal parameter(s)     :  T_CRC_HANDLE *h_crc - IN CRC handle
 *                            T_UINT32 pol - IN CRC generating polynomial (7, 8, 16 or 32-bit long)
 *                            T_UINT32 poly_length - IN CRC polynomial length
 *
 * Return Value            :  T_HAL_STATUS - HAL status
 *
 * Assumption              :  None
 *
 */
T_HAL_STATUS HalCrcExPolynomialSet(T_CRC_HANDLE *h_crc, T_UINT32 pol, T_UINT32 poly_length)
{
   /*hdulibstm32f7xxhalcrcex-HalCrcExPolynomialSet-DB-LLR-001*/
   T_UINT32 msb_bits = THIRTY_ONE;

   /*hdulibstm32f7xxhalcrcex-HalCrcExPolynomialSet-DB-LLR-002*/
   while ((ZERO == (pol & ((T_UINT32)(ONE) << msb_bits))) && (msb_bits-- > ZERO))
   {
      ;
   }

   switch (poly_length)
   {
      /*hdulibstm32f7xxhalcrcex-HalCrcExPolynomialSet-DB-LLR-003*/
      case CRC_POLYLENGTH_7B:
         if (msb_bits >= HAL_CRC_LENGTH_7B)
         {
            return  HAL_ERROR;
         }
         break;

      /*hdulibstm32f7xxhalcrcex-HalCrcExPolynomialSet-DB-LLR-004*/
      case CRC_POLYLENGTH_8B:
         if (msb_bits >= HAL_CRC_LENGTH_8B)
         {
            return  HAL_ERROR;
         }
         break;

      /*hdulibstm32f7xxhalcrcex-HalCrcExPolynomialSet-DB-LLR-005*/
      case CRC_POLYLENGTH_16B:
         if (msb_bits >= HAL_CRC_LENGTH_16B)
         {
            return  HAL_ERROR;
         }
         break;

      /*hdulibstm32f7xxhalcrcex-HalCrcExPolynomialSet-DB-LLR-006*/
      case CRC_POLYLENGTH_32B:
         /* no polynomial definition vs. polynomial length issue possible */
         break;

      /*hdulibstm32f7xxhalcrcex-HalCrcExPolynomialSet-DB-LLR-007*/
      default:
         break;
   }

   /*hdulibstm32f7xxhalcrcex-HalCrcExPolynomialSet-DB-LLR-008*/
   /* set generating polynomial */
   WRITE_REG(h_crc->Instance->POL, pol);

   /*hdulibstm32f7xxhalcrcex-HalCrcExPolynomialSet-DB-LLR-009*/
   /* set generating polynomial size */
   MODIFY_REG(h_crc->Instance->CR, CRC_CR_POLYSIZE, poly_length);

   /*hdulibstm32f7xxhalcrcex-HalCrcExPolynomialSet-DB-LLR-010*/
   /* Return function status */
   return HAL_OK;
}
