/*
 ******************************************************************************
 * License Information  :  Howell Instruments, Inc.                           *
 *                         "Licensed Software" and "All rights reserved".     *
 ******************************************************************************
 *  File                : hdulibstm32f7xxhalcrcex.h
 *
 *  Description         : Header file of CORTEX HAL module.
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
 *      1.2          Divya G P     01-Sep-2017        100028
 *      1.3          Shilpa A R    04-Nov-2017        100156
 *
 * Additional References : None
 *
 ******************************************************************************
 */

/* Define to prevent recursive inclusion*/
#ifndef _HDULIBSTM32F7XXHALCRCEX_H_
#define _HDULIBSTM32F7XXHALCRCEX_H_

/* Includes*/
#include "hdulibstm32f7xxhaldma.h"     /* Header file of CORTEX HAL module */
#include "hdulibstm32f7xxhaldef.h"     /* Header file of CORTEX HAL module */
#include "hdulibstm32f7xxhalcrc.h"     /* Header files for CRC EX HAL module */
#include "hdulibstm32f746xx.h"         /* CMSIS Cortex-M7 Device Peripheral Access Layer */

#define CRC_INPUTDATA_INVERSION_NONE              ((T_UINT32)0x00000000U)
#define CRC_INPUTDATA_INVERSION_BYTE              ((T_UINT32)CRC_CR_REV_IN_0)
#define CRC_INPUTDATA_INVERSION_HALFWORD          ((T_UINT32)CRC_CR_REV_IN_1)
#define CRC_INPUTDATA_INVERSION_WORD              ((T_UINT32)CRC_CR_REV_IN)

#define IS_CRC_INPUTDATA_INVERSION_MODE(__MODE__) (((__MODE__) == CRC_INPUTDATA_INVERSION_NONE) ||\
                                         ((__MODE__) == CRC_INPUTDATA_INVERSION_BYTE) || \
                                         ((__MODE__) == CRC_INPUTDATA_INVERSION_HALFWORD) || \
                                         ((__MODE__) == CRC_INPUTDATA_INVERSION_WORD))

#define CRC_OUTPUTDATA_INVERSION_DISABLE         ((T_UINT32)0x00000000U)
#define CRC_OUTPUTDATA_INVERSION_ENABLE          ((T_UINT32)CRC_CR_REV_OUT)

#define IS_CRC_OUTPUTDATA_INVERSION_MODE(__MODE__)   \
                                       (((__MODE__) == CRC_OUTPUTDATA_INVERSION_DISABLE) || \
                                       ((__MODE__) == CRC_OUTPUTDATA_INVERSION_ENABLE))

#define  __HAL_CRC_OUTPUTREVERSAL_ENABLE(__HANDLE__) ((__HANDLE__)->Instance->CR |= CRC_CR_REV_OUT)

#define __HAL_CRC_OUTPUTREVERSAL_DISABLE(__HANDLE__) \
                                    ((__HANDLE__)->Instance->CR &= ~(CRC_CR_REV_OUT))

#define __HAL_CRC_POLYNOMIAL_CONFIG(__HANDLE__, __POLYNOMIAL__) \
                                    ((__HANDLE__)->Instance->POL = (__POLYNOMIAL__))

/* Updated as per PR 100156 */
extern T_HAL_STATUS HalCrcExPolynomialSet(T_CRC_HANDLE *h_crc, T_UINT32 pol, T_UINT32 poly_length);

#endif
