/*
 ******************************************************************************
 * License Information  :  Howell Instruments, Inc.                           *
 *                         "Licensed Software" and "All rights reserved".     *
 ******************************************************************************
 *  File                : hdudispfpointers.h
 *
 *  Description         : Contains ponters for polygon shapes.
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
 *      1.1          Vinay H         19-Jul-2017             100064
 *      1.2          Rona B.S        11-Oct-2017             100064
 *      1.3          Rona B.S        05-Jul-2020             100259
 *
 * Additional References : None
 *
 ******************************************************************************
 */

#ifndef _HDUDISPFPOINTERS_H_
#define _HDUDISPFPOINTERS_H_

#include "hdudispfpolygon2.h"  /* contains routines for ploygons configuration */
#include "hdudispfwidgets.h"  /* Contains routines for widget params */

typedef struct
{
   T_INT32     s32PtrShape; /* Which shape to use. */
   T_EPENCOLOR ePenColor;   /* Default color. */
   T_SPOLY     *psShape;    /* Poly of the Shape. */
}  T_SPTRSPEC;

#endif /* _HDUDISPFPOINTERS_H_ */
