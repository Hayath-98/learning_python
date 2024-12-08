/*
 ******************************************************************************
 * License Information  :  Howell Instruments, Inc.                           *
 *                         "Licensed Software" and "All rights reserved".     *
 ******************************************************************************
 *  File                : hdulibstm32f7xxhalcrc.h
 *
 *  Description         : Header file of CORTEX HAL module.
 *
 *  Compiler            : GNU gcc(GNU Tools for ARM Embedded Processors) version 5.4.1 20160919
 *
 *  Compiler options    : As per section 10.3.1 of Software Development Plan (HDU-001-002).
 *
 *  Pragma              : None
 *
 * H/W platform         : ARM Cortex-M7 (STM32F767)
 *
 *  Portability         : None
 *
 *  Author(s)           : Vinay H
 *
 *  Version History     :
 * <Version No.>     <Author>          <Date>         <Problem Report No.>
 *
 *      1.1          Vinay H         26-Jul-2017             -
 *      1.2          Divya G P       01-Sep-2017        100028
 *
 * Additional References : None
 *
 ******************************************************************************
 */

/* Define to prevent recursive inclusion */
#ifndef _HDULIBSTM32F7XXHALCRC_H_
#define _HDULIBSTM32F7XXHALCRC_H_

/* Includes*/
#include "hdulibstm32f7xxhaldma.h"     /* Header file of CORTEX HAL module */
#include "hdulibstm32f746xx.h"         /* CMSIS Cortex-M7 Device Peripheral Access Layer */
#include "hdulibstm32f7xxhaldef.h"     /*Contains the HAL definition module */

typedef enum
{
   HAL_CRC_STATE_RESET     = 0x00U,  /* CRC not yet initialized or disabled */
   HAL_CRC_STATE_READY     = 0x01U,  /* CRC initialized and ready for use   */
   HAL_CRC_STATE_BUSY      = 0x02U,  /* CRC internal process is ongoing     */
   HAL_CRC_STATE_TIMEOUT   = 0x03U,  /* CRC timeout state                   */
   HAL_CRC_STATE_ERROR     = 0x04U   /* CRC error state                     */
}T_HAL_CRC_STATE;

typedef struct
{
   /*
    * This parameter is a value of @ref CRC_Default_Polynomial and indicates if default
    * polynomial is used.
    * If set to DEFAULT_POLYNOMIAL_ENABLE, resort to default
    * X^32 + X^26 + X^23 + X^22 + X^16 + X^12 + X^11 + X^10 +X^8 + X^7 + X^5 + X^4 + X^2+ X +1.
    * In that case, there is no need to set GeneratingPolynomial field.
    * If otherwise set to DEFAULT_POLYNOMIAL_DISABLE, GeneratingPolynomial and CRCLength
    * fields must be set
    */
   T_UINT8 DefaultPolynomialUse;

   /*
    * This parameter is a value of @ref CRC_Default_InitValue_Use and indicates if default
    * init value is used.
    * If set to DEFAULT_INIT_VALUE_ENABLE, resort to default
    * 0xFFFFFFFF value. In that case, there is no need to set InitValue field.
    * If otherwise set to DEFAULT_INIT_VALUE_DISABLE,  InitValue field must be set
    */
   T_UINT8 DefaultInitValueUse;

   /*
    * Set CRC generating polynomial. 7, 8, 16 or 32-bit long value for a polynomial degree
    * respectively equal to 7, 8, 16 or 32. This field is written in normal representation,
    * e.g., for a polynomial of degree 7, X^7 + X^6 + X^5 + X^2 + 1 is written 0x65.
    * No need to specify it if DefaultPolynomialUse is set to DEFAULT_POLYNOMIAL_ENABLE
    */
   T_UINT32 GeneratingPolynomial;

   /*
    * This parameter is a value of @ref CRC_Polynomial_Sizes and indicates CRC length.
    * Value can be either one of
    * CRC_POLYLENGTH_32B                  (32-bit CRC)
    * CRC_POLYLENGTH_16B                  (16-bit CRC)
    * CRC_POLYLENGTH_8B                   (8-bit CRC)
    * CRC_POLYLENGTH_7B                   (7-bit CRC)
    */
   T_UINT32 CRCLength;

   /*
    * Init value to initiate CRC computation. No need to specify it if DefaultInitValueUse
    * is set to DEFAULT_INIT_VALUE_ENABLE
    */
   T_UINT32 InitValue;

   /*
    * This parameter is a value of @ref CRCEx_Input_Data_Inversion and specifies input
    * data inversion mode.
    * Can be either one of the following values
    * CRC_INPUTDATA_INVERSION_NONE      no input data inversion
    * CRC_INPUTDATA_INVERSION_BYTE      byte-wise inversion, 0x1A2B3C4D becomes 0x58D43CB2
    * CRC_INPUTDATA_INVERSION_HALFWORD  halfword-wise inversion, 0x1A2B3C4D becomes 0xD458B23C
    * CRC_INPUTDATA_INVERSION_WORD      word-wise inversion, 0x1A2B3C4D becomes 0xB23CD458
    */
   T_UINT32 InputDataInversionMode;

   /*
    * This parameter is a value of @ref CRCEx_Output_Data_Inversion and specifies output data
    * (i.e. CRC) inversion mode.
    * Can be either
    * CRC_OUTPUTDATA_INVERSION_DISABLE   no CRC inversion, or
    * CRC_OUTPUTDATA_INVERSION_ENABLE    CRC 0x11223344 is converted into 0x22CC4488
    */
   T_UINT32 OutputDataInversionMode;
}T_CRC_INIT;

typedef struct
{
   T_CRC                 *Instance;     /* Register base address        */

   T_CRC_INIT             Init;          /* CRC configuration parameters */

   T_HAL_LOCK             Lock;         /* CRC Locking object           */

   __IO T_HAL_CRC_STATE   State;    /* CRC communication state      */

   /*
    * This parameter is a value of @ref CRC_Input_Buffer_Format and specifies input data format.
    * Can be either
    * CRC_INPUTDATA_FORMAT_BYTES       input data is a stream of bytes (8-bit data)
    * CRC_INPUTDATA_FORMAT_HALFWORDS   input data is a stream of half-words (16-bit data)
    * CRC_INPUTDATA_FORMAT_WORDS       input data is a stream of words (32-bits data)
    * Note that constant CRC_INPUT_FORMAT_UNDEFINED is defined but an initialization error
    * must occur if InputBufferFormat is not one of the three values listed above
    */
   T_UINT32 InputDataFormat;
}T_CRC_HANDLE;

#define DEFAULT_CRC32_POLY      0x04C11DB7U

#define DEFAULT_CRC_INITVALUE   0xFFFFFFFFU

#define DEFAULT_POLYNOMIAL_ENABLE       ((T_UINT8)0x00U)
#define DEFAULT_POLYNOMIAL_DISABLE      ((T_UINT8)0x01U)

#define DEFAULT_INIT_VALUE_ENABLE       ((T_UINT8)0x00U)
#define DEFAULT_INIT_VALUE_DISABLE      ((T_UINT8)0x01U)

#define CRC_POLYLENGTH_32B              ((T_UINT32)0x00000000U)
#define CRC_POLYLENGTH_16B              ((T_UINT32)CRC_CR_POLYSIZE_0)
#define CRC_POLYLENGTH_8B               ((T_UINT32)CRC_CR_POLYSIZE_1)
#define CRC_POLYLENGTH_7B               ((T_UINT32)CRC_CR_POLYSIZE)

#define HAL_CRC_LENGTH_32B     32U
#define HAL_CRC_LENGTH_16B     16U
#define HAL_CRC_LENGTH_8B       8U
#define HAL_CRC_LENGTH_7B       7U

#define CRC_INPUTDATA_FORMAT_UNDEFINED             ((T_UINT32)0x00000000U)
#define CRC_INPUTDATA_FORMAT_BYTES                 ((T_UINT32)0x00000001U)
#define CRC_INPUTDATA_FORMAT_HALFWORDS             ((T_UINT32)0x00000002U)
#define CRC_INPUTDATA_FORMAT_WORDS                 ((T_UINT32)0x00000003U)

#define __HAL_CRC_RESET_HANDLE_STATE(__HANDLE__) ((__HANDLE__)->State = HAL_CRC_STATE_RESET)

#define __HAL_CRC_DR_RESET(__HANDLE__) ((__HANDLE__)->Instance->CR |= CRC_CR_RESET)

#define __HAL_CRC_INITIALCRCVALUE_CONFIG(__HANDLE__, __INIT__) \
                        ((__HANDLE__)->Instance->INIT = (__INIT__))

#define __HAL_CRC_SET_IDR(__HANDLE__, __VALUE__)   \
                        (WRITE_REG((__HANDLE__)->Instance->IDR, CRC_IDR_IDR, (__VALUE__)))

#define __HAL_CRC_GET_IDR(__HANDLE__) (((__HANDLE__)->Instance->IDR) & CRC_IDR_IDR)

/* Include CRC HAL Extension module */
#include "hdulibstm32f7xxhalcrcex.h"      /* Header files for CRC EX HAL module */

/* Initialization and de-initialization functions */
extern T_HAL_STATUS HalCrcInit(T_CRC_HANDLE *hcrc);

/* Peripheral Control functions*/
T_UINT32 HalCrcAccumulate(T_CRC_HANDLE *hcrc, T_UINT32 pBuffer[], T_UINT32 BufferLength);
T_UINT32 HalCrcCalculate(T_CRC_HANDLE *hcrc, T_UINT32 pBuffer[], T_UINT32 BufferLength);

#define IS_DEFAULT_POLYNOMIAL(__DEFAULT__) (((__DEFAULT__) == DEFAULT_POLYNOMIAL_ENABLE) || \
                                            ((__DEFAULT__) == DEFAULT_POLYNOMIAL_DISABLE))
#define IS_DEFAULT_INIT_VALUE(__VALUE__)  (((__VALUE__) == DEFAULT_INIT_VALUE_ENABLE) || \
                                           ((__VALUE__) == DEFAULT_INIT_VALUE_DISABLE))
#define IS_CRC_POL_LENGTH(__LENGTH__)     (((__LENGTH__) == CRC_POLYLENGTH_32B) || \
                                           ((__LENGTH__) == CRC_POLYLENGTH_16B) || \
                                           ((__LENGTH__) == CRC_POLYLENGTH_8B)  || \
                                           ((__LENGTH__) == CRC_POLYLENGTH_7B))
#define IS_CRC_INPUTDATA_FORMAT(__FORMAT__)      (((__FORMAT__) == CRC_INPUTDATA_FORMAT_BYTES) || \
                                          ((__FORMAT__) == CRC_INPUTDATA_FORMAT_HALFWORDS) || \
                                          ((__FORMAT__) == CRC_INPUTDATA_FORMAT_WORDS))

#endif
