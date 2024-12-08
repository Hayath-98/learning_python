/*
 ******************************************************************************
 * License Information  :  Howell Instruments, Inc.                           *
 *                         "Licensed Software" and "All rights reserved".     *
 ******************************************************************************
 *  File                : hdudispbrterr.h
 *
 *  Description         : This file contains the common defines and functions prototypes for
 *                        hdudispbrterr.c.
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
 *      1.2          Shilpa A R      05-Sep-2017              100028
 *      1.3          Shilpa A R      02-Oct-2017              100064
 *
 * Additional References : None
 *
 ******************************************************************************
 */
#ifndef _HDUDISPBRTERR_H_
#define _HDUDISPBRTERR_H_

#include "hdulibbasictypes.h"      /* Basic data types.*/

extern void RterrFunc(T_UINT8 *ptr_file, T_INT32 s32_line_number, T_UINT8 *ptr_message);

#endif /* _HDUDISPBRTERR_H_ */
