/*
 ******************************************************************************
 * License Information  :  Howell Instruments, Inc.                           *
 *                         "Licensed Software" and "All rights reserved".     *
 ******************************************************************************
 *  File                : hdudispfstandard.h
 *
 *  Description         : Standard definitions
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
 *  Portability         : None
 *
 *  Author(s)           : Vinay H
 *
 *  Version History     :
 * <Version No.>     <Author>          <Date>         <Problem Report No.>
 *
 *      1.1          Vinay H         19-Jul-2017             100064
 *      1.2          Shruthi M N     30-Oct-2017             100104
 *
 * Additional References : None
 *
 ******************************************************************************
 */

#ifndef _HDUDISPFSTANDARD_H_
#define _HDUDISPFSTANDARD_H_

#include "hdulibbasictypes.h"    /* Contains basic header definition */

#define EVER      ;;

#define NULL      ((void *)0)

#define STD_NUMBER_OF(x) (sizeof(x)/sizeof(x[0]))

#define STD_IS_IN_RANGE(val,minval,maxval) \
                     (((val)<(minval)) ? FALSE : (((val)>(maxval)) ? FALSE : TRUE))

#define MIN(x,y) ((x)<(y)?(x):(y))
#define MAX(x,y) ((x)>(y)?(x):(y))

#endif
