/*
 ******************************************************************************
 * License Information  :  Howell Instruments, Inc.                           *
 *                         "Licensed Software" and "All rights reserved".     *
 ******************************************************************************
 *  File                : hdudispfcas.h
 *
 *  Description         : This file contains the common defines and functions prototypes for
 *                        hdudispfcas.c
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
 *      1.2          Shruthi M N     19-Oct-2017             100083
 *
 * Additional References : None
 *
 *****************************************************************************
 */

#ifndef _HDUDISPFCAS_H_
#define _HDUDISPFCAS_H_

#include "hdulibbasictypes.h" /* Standard basic data type definitions */
#include "hdudispfpara.h"  /* prototype for builds faults, message and system information  */

extern T_UINT16 U16_cas_words[MAX_FLAG_WORDS];
/*Install the flash timer for each possible CAS message.*/
extern void CasInit(void);
extern void CasSetCasWord(T_UINT8  u8_index, T_UINT16 u16_cas_word);
extern void CasUpdate(void);
extern void CasDisplay();
extern void CasSort (void);

#endif /* _HDUDISPFCAS_H_ */
