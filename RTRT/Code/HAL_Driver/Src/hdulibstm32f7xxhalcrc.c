/*
 ******************************************************************************
 * License Information  :  Howell Instruments, Inc.                           *
 *                         "Licensed Software" and "All rights reserved".     *
 ******************************************************************************
 *  File                : hdulibstm32f7xxhalcrc.c
 *
 *  Description         : This file provides firmware functions to manage the following
 *                        functionalities of the Cyclic Redundancy Check (CRC) peripheral:
 *                        - Initialization and de-initialization functions
 *                        - Peripheral Control functions
 *                        - Peripheral State functions
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
 * <Version No.>        <Author>          <Date>         <Problem Report No.>
 *
 *      1.1             Vinay H         26-Jul-2017             -
 *      1.2             Divya G P       01-Sep-2017        100028
 *      1.3             Shruthi M N     30-Oct-2017        100104
 *
 * Additional References : None
 *
 ******************************************************************************
 */

/* Includes */
#include "hdulibstm32f7xxhal.h"     /* Header files for HAL driver*/
#include "hdulibstm32f746xx.h"     /* CMSIS STM32F7xx Device Peripheral Access Layer file*/
#include "hdulibstm32f7xxhalcrc.h"  /* Header files for CRC HAL driver*/
#include "hdulibstm32f7xxhalmsp.h"  /* Header files for HAL MSP driver */
#include "hdulibbasictypes.h"       /* Contains basic data types*/
#include "hdulibstm32f7xxhaldef.h"  /* Header file of CORTEX HAL module */



static T_UINT32 CrcHandle8(T_CRC_HANDLE *h_crc, T_UINT8 p_buffer[], T_UINT32 buffer_length);
static T_UINT32 CrcHandle16(T_CRC_HANDLE *h_crc, T_UINT16 p_buffer[], T_UINT32 buffer_length);

/*
 * Function                :  HALCrcInit
 *
 * Description             :  This function initializes the CRC according to the specified
 *                            parameters in the T_CRC_INIT and create the associated handle.
 *
 * Formal parameter(s)     :  T_CRC_HANDLE* h_crc - INOUT pointer to T_CRC_HANDLE structure
 *                            that handles CRC.
 *
 * Return Value            :  T_HAL_STATUS - returns status of CRC handle
 *                            HAL_ERROR - when there is no CRC
 *                            HAL_OK - CRC handle is done succesfully
 *
 * Assumption              :  None
 *
 */
T_HAL_STATUS HalCrcInit(T_CRC_HANDLE *h_crc)
{
   /*hdulibstm32f7xxhalcrc-HalCrcInit-DB-LLR-001*/
   /* Check the CRC handle allocation */
   if(NULL == h_crc)
   {
      return HAL_ERROR;
   }
   else
   {
       ;/*Do nothing*/
   }

   /*hdulibstm32f7xxhalcrc-HalCrcInit-DB-LLR-002*/
   if(HAL_CRC_STATE_RESET == h_crc->State)
   {
      /* Allocate lock resource and initialize it */
      h_crc->Lock = HAL_UNLOCKED;

      /* Init the low level hardware */
      HalCRCMspInit();
   }
   else
   {
       ;/*Do nothing*/
   }

   /*hdulibstm32f7xxhalcrc-HalCrcInit-DB-LLR-003*/
   /* Change CRC peripheral state */
   h_crc->State = HAL_CRC_STATE_BUSY;

   /*hdulibstm32f7xxhalcrc-HalCrcInit-DB-LLR-004*/
   if(DEFAULT_POLYNOMIAL_ENABLE == h_crc->Init.DefaultPolynomialUse)
   {
      /* initialize IP with default generating polynomial */
      WRITE_REG(h_crc->Instance->POL, DEFAULT_CRC32_POLY);
      MODIFY_REG(h_crc->Instance->CR, CRC_CR_POLYSIZE, CRC_POLYLENGTH_32B);
   }
   else
   {
      /*hdulibstm32f7xxhalcrc-HalCrcInit-DB-LLR-005*/
      /* initialize CRC IP with generating polynomial defined by user */
     if(HalCrcExPolynomialSet(h_crc, h_crc->Init.GeneratingPolynomial,
                                    h_crc->Init.CRCLength) != HAL_OK)
     {
         return HAL_ERROR;
     }
     else
     {
         ;/*Do nothing*/
     }
   }

   /*
    * Check whether or not non-default CRC initial value has been
    * picked up by user
    */
   /*hdulibstm32f7xxhalcrc-HalCrcInit-DB-LLR-006*/
   if(DEFAULT_INIT_VALUE_ENABLE == h_crc->Init.DefaultInitValueUse)
   {
      WRITE_REG(h_crc->Instance->INIT, DEFAULT_CRC_INITVALUE);
   }
   else
   {
      WRITE_REG(h_crc->Instance->INIT, h_crc->Init.InitValue);
   }

   /*hdulibstm32f7xxhalcrc-HalCrcInit-DB-LLR-007*/
   /* set input data inversion mode */
   MODIFY_REG(h_crc->Instance->CR, CRC_CR_REV_IN, h_crc->Init.InputDataInversionMode);

   /*hdulibstm32f7xxhalcrc-HalCrcInit-DB-LLR-008*/
   /* set output data inversion mode */
   MODIFY_REG(h_crc->Instance->CR, CRC_CR_REV_OUT, h_crc->Init.OutputDataInversionMode);

   /*hdulibstm32f7xxhalcrc-HalCrcInit-DB-LLR-009*/
   /* Change CRC peripheral state */
   h_crc->State = HAL_CRC_STATE_READY;

   /* Return function status */
   return HAL_OK;
}

/*
 * Function                :  HalCrcAccumulate
 *
 * Description             :  Compute the 7, 8, 16 or 32-bit CRC value of an 8, 16
 *                            or 32-bit data buffer starting with the previously
 *                            computed CRC as initialization value.
 *
 * Formal parameter(s)     :  T_CRC_HANDLE *h_crc - INOUT CRC handle
 *                            T_UINT32 p_buffer - IN pointer to the input data buffer, exact input
 *                                                data format is provided by h_crc->InputDataFormat
 *                            T_UINT32 buffer_length - IN input data buffer length
 *                            (number of bytes if p_buffer type is * T_UINT8,
 *                             number of half-words if p_buffer type is * T_UINT16,
 *                            number of words if p_buffer type is * T_UINT32).
 *
 * Return Value            :  T_UINT32 - returns CRC output(h_crc->Instance->DR register)
 *
 * Assumption              :  None
 *
 */

T_UINT32 HalCrcAccumulate(T_CRC_HANDLE *h_crc, T_UINT32 p_buffer[], T_UINT32 buffer_length)
{
   T_UINT32 index = ZERO; /* CRC input data buffer index */
   T_UINT32 temp = ZERO;   /* CRC output (read from h_crc->Instance->DR register) */

   /*hdulibstm32f7xxhalcrc-HalCrcAccumulate-DB-LLR-001*/
   /* Process locked */
   __HAL_LOCK(h_crc);

   /* Change CRC peripheral state */
   h_crc->State = HAL_CRC_STATE_BUSY;

   switch (h_crc->InputDataFormat)
   {
      /*hdulibstm32f7xxhalcrc-HalCrcAccumulate-DB-LLR-002*/
      case CRC_INPUTDATA_FORMAT_WORDS:
         /* Enter Data to the CRC calculator */
         for(index = ZERO; index < buffer_length; index++)
         {
             h_crc->Instance->DR = p_buffer[index];
         }
         temp = h_crc->Instance->DR;
         break;

      /*hdulibstm32f7xxhalcrc-HalCrcAccumulate-DB-LLR-002*/
      case CRC_INPUTDATA_FORMAT_BYTES:
         temp = CrcHandle8(h_crc, (T_UINT8*)p_buffer, buffer_length);
         break;

      /*hdulibstm32f7xxhalcrc-HalCrcAccumulate-DB-LLR-002*/
      case CRC_INPUTDATA_FORMAT_HALFWORDS:
         temp = CrcHandle16(h_crc, (T_UINT16*)p_buffer, buffer_length);
         break;

      default:
         break;
   }

   /*hdulibstm32f7xxhalcrc-HalCrcAccumulate-DB-LLR-003*/
   /* Change CRC peripheral state */
   h_crc->State = HAL_CRC_STATE_READY;

   /*hdulibstm32f7xxhalcrc-HalCrcAccumulate-DB-LLR-004*/
   /* Process unlocked */
   __HAL_UNLOCK(h_crc);

   /* Return the CRC computed value */
   return temp;
}

/*
 * Function                :  CrcHandle8
 *
 * Description             :  This function Specific data handling to optimize processing time.
 *                            Enter 8-bit input data to the CRC calculator.
 *
 * Formal parameter(s)     :  T_CRC_HANDLE* h_crc - OUT pointer to a T_CAN_HANDLE structure that
 *                            handles CRC.
 *                            T_UINT8 p_buffer[] - IN pointer to the input data buffer
 *                            T_UINT32 buffer_length - IN input data buffer length
 *
 * Return Value            :  T_UINT32 - returns h_crc->Instance->DR
 *
 * Assumption              :  None
 *
 */
static T_UINT32 CrcHandle8(T_CRC_HANDLE *h_crc, T_UINT8 p_buffer[], T_UINT32 buffer_length)
{
   T_UINT32 index = ZERO; /* input data buffer index */

    /*
     * Processing time optimization: 4 bytes are entered in a row with a single word write,
     * last bytes must be carefully fed to the CRC calculator to ensure a correct type
     * handling by the IP
     */

   /*hdulibstm32f7xxhalcrc-CrcHandle8-DB-LLR-001*/
   for(index = ZERO; index < (buffer_length/FOUR); index++)
   {
      h_crc->Instance->DR = (T_UINT32)(((T_UINT32)(p_buffer[FOUR *index])<<TWENTY_FOUR) |
                           ((T_UINT32)(p_buffer[FOUR*index+ONE])<<SIXTEEN) |
                           ((T_UINT32)(p_buffer[FOUR*index+TWO])<<EIGHT)
                           | (T_UINT32)(p_buffer[FOUR*index+THREE]));
   }
   /* last bytes specific handling */
   if((buffer_length%FOUR) != ZERO)
   {
      /*hdulibstm32f7xxhalcrc-CrcHandle8-DB-LLR-002*/
      if(ONE == (buffer_length % FOUR))
      {
         *(__IO T_UINT8*) (&h_crc->Instance->DR) = p_buffer[FOUR*index];
      }
      else
      {
         ;/*Do nothing*/
      }
      /*hdulibstm32f7xxhalcrc-CrcHandle8-DB-LLR-003*/
      if(TWO == (buffer_length % FOUR))
      {
         *(__IO T_UINT16*) (&h_crc->Instance->DR) =
                                (T_UINT16)((T_UINT16)((T_UINT16)(p_buffer[FOUR*index])
                                 <<EIGHT)|(T_UINT16)(p_buffer[FOUR*index+ONE]));
      }
      else
      {
         ;/*Do nothing*/
      }
      /*hdulibstm32f7xxhalcrc-CrcHandle8-DB-LLR-004*/
      if(THREE == (buffer_length % FOUR))
      {
         *(__IO T_UINT16*) (&h_crc->Instance->DR) =
                                 (T_UINT16)((T_UINT16)((T_UINT16)(p_buffer[FOUR*index])
                                  <<EIGHT) | (T_UINT16)(p_buffer[FOUR*index+ONE]));
         *(__IO T_UINT8*) (&h_crc->Instance->DR) = p_buffer[FOUR*index+TWO];
      }
     else
     {
        ;/*Do nothing*/
     }
   }
   else
   {
      ;/*Do nothing*/
   }

   /*hdulibstm32f7xxhalcrc-CrcHandle8-DB-LLR-005*/
   /* Return the CRC computed value */
   return h_crc->Instance->DR;
}

/*
 * Function                :  CrcHandle16
 *
 * Description             :  This function Specific data handling to optimize processing time.
 *                            Enter 16-bit input data to the CRC calculator.
 *
 * Formal parameter(s)     :  T_CRC_HANDLE* h_crc - OUT pointer to a T_CAN_HANDLE structure
 *                            that handles CRC.
 *                            T_UINT16 p_buffer[] - IN pointer to the input data buffer
 *                            T_UINT32 buffer_length - IN input data buffer length
 *
 * Return Value            :  T_UINT32 - returns h_crc->Instance->DR
 *
 * Assumption              :  None
 *
 */
static T_UINT32 CrcHandle16(T_CRC_HANDLE *h_crc, T_UINT16 p_buffer[], T_UINT32 buffer_length)
{
   T_UINT32 index = ZERO;   /* input data buffer index */

   /*
    * Processing time optimization: 2 HalfWords are entered in a row with a single word write,
    * in case of odd length, last HalfWord must be carefully fed to the CRC calculator to ensure
    * a correct type handling by the IP
    */

   /*hdulibstm32f7xxhalcrc-CrcHandle16-DB-LLR-001*/
   for(index = ZERO; index < (buffer_length/TWO); index++)
   {
      h_crc->Instance->DR = (((T_UINT32)(p_buffer[TWO*index])<<SIXTEEN)
                           | (T_UINT32)(p_buffer[TWO*index+ONE]));
   }
   /*hdulibstm32f7xxhalcrc-CrcHandle16-DB-LLR-002*/
   if((buffer_length%TWO) != ZERO)
   {
       *(__IO T_UINT16*) (&h_crc->Instance->DR) = p_buffer[TWO*index];
   }
   else
   {
       ;/*Do nothing*/
   }

   /*hdulibstm32f7xxhalcrc-CrcHandle16-DB-LLR-003*/
   /* Return the CRC computed value */
   return h_crc->Instance->DR;
}
