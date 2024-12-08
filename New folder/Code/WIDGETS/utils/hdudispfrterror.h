/*
 ******************************************************************************
 * License Information  :  Howell Instruments, Inc.                           *
 *                         "Licensed Software" and "All rights reserved".     *
 ******************************************************************************
 *  File                : hdudispfrterror.h
 *
 *  Description         : Stub routine for run time errors.
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
 *      1.1          Vinay H         14-Sep-2017             100064
 *      1.2          Shruthi M N     19-Oct-2017             100083
 *
 * Additional References : None
 *
 ******************************************************************************
 */
#ifndef  _HDUDISPFRTERROR_H_
#define  _HDUDISPFRTERROR_H_

#include "hdulibbasictypes.h" /* Standard basic data type definitions */

/*FUNCTION*/
extern void RterrWidget(T_CHAR *pc_file, T_INT32 s32_line_number, T_CHAR *pc_message);

#endif
