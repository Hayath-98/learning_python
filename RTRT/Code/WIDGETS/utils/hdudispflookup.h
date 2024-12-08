/*
 ******************************************************************************
 * License Information  :  Howell Instruments, Inc.                           *
 *                         "Licensed Software" and "All rights reserved".     *
 ******************************************************************************
 *  File                : hdudispflookup.h
 *
 *  Description         : This file provide the table lookup routines.
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
 *      1.1           Shilpa A R         14-Sep-2017             100064
 *      1.2           Shruthi M N        15-Oct-2017             100083
 *
 * Additional References : None
 *
 ******************************************************************************
 */

#ifndef  _HDUDISPFLOOKUP_H_
#define  _HDUDISPFLOOKUP_H_

#include "hdudispfparams.h"    /* provides the tags for various parameters and parameter units */

 /* Updated as per PR100083*/
typedef  struct
{
   T_INT32  *x;
   T_INT32  *y;
}  T_LOOKUP_TABLE;

 /* Updated as per PR100083*/
extern T_INT32 LookupTableLookup (const T_LOOKUP_TABLE *table, T_INT32 ind_var, T_PARAM_STAT *stat);

#endif
