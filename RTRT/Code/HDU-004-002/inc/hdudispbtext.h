/*
 ******************************************************************************
 * License Information  :  Howell Instruments, Inc.                           *
 *                         "Licensed Software" and "All rights reserved".     *
 ******************************************************************************
 *  File                : hdudispbtext.h
 *
 *  Description         :This file contains the common defines and functions prototypes for
 *                       hdudispbtext.c.
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
 *  Author(s)           : Ajay J G
 *
 *  Version History     :
 *
 * <Version No.>     <Author>          <Date>         <Problem Report No.>
 *
 *      1.1          Ajay J G        02-Aug-2017             -
 *      1.2          Divya G P       02-Sep-2017          100028
 *      1.3          Rona B.S        04-Nov-2017          100156
 *      1.4          Vinay H         08-Nov-2017          100164
 *
 * Additional References : None
 *
 ******************************************************************************
 */

#ifndef _HDUDISPBTEXT_H_
#define _HDUDISPBTEXT_H_

#include "hdudispbfonts.h"    /* Contains functions prototypes of hdudispbfonts*/

extern void TextPrintChar(T_UINT8   u8_char);
extern void TextInit(void);
extern void TextPrintString(T_UINT8 *pu8_string);
extern void TextClearEOL(void);

#endif /* _HDUDISPBTEXT_H_ */
