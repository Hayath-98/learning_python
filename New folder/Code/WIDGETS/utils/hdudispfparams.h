/*
 ******************************************************************************
 * License Information  :  Howell Instruments, Inc.                           *
 *                         "Licensed Software" and "All rights reserved".     *
 ******************************************************************************
 *  File                : hdudispfparams.h
 *
 *  Description         : This file provides the tags for various parameters and parameter units.
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
 *      1.2           Shilpa A R         09-Oct-2017             100064
 *      1.3           Shruthi M N        15-Oct-2017             100083
 *      1.4           Shruthi M N        30-Oct-2017             100104
 *
 * Additional References : None
 *
 ******************************************************************************
 */

#ifndef _HDUDISPFPARAMS_H_
#define _HDUDISPFPARAMS_H_

#include  "hdulibbasictypes.h"   /*provides user defined types for basic types.*/

typedef enum
{
   PARAM_OK,         /* No problem.*/
   PARAM_ADVISORY,   /* Parameter is in the advisory region.*/
   PARAM_CAUTION,    /* Parameter is in the caution region.*/
   PARAM_WARNING,    /* Parameter is in the warning region.*/
   PARAM_BAD,        /* Anything >= PARAM_BAD will trigger gauge failure etc. */
   RANGE_ERROR,      /* The parameter is outside accepted range Sensor Fault? */
   CHANNEL_ERROR,    /* Hardware error detected.*/
   MISSING,          /* Networked LRU not reporting.*/
   NCD               /* No data from EECU.*/
}  T_PARAM_STAT;

/* All channel readings have this form.*/
typedef struct
{
    /* Updated as per PR100083*/
   T_INT32        r;      /* This is the number to use in normal op.*/
   T_PARAM_STAT   stat;   /* Status of channel.*/
   /* Updated as per PR100083*/
   T_FLOAT fread;
}  T_PARAM_READING;

 /* Updated as per PR100083*/
 /* Divide the number by this power of 10 to scale. */
typedef enum
{
   TIMES_100 = -2,
   TIMES_10,
   TIMES_ONE,
   ONE_DECIMAL,
   TWO_DECIMALS,
   THREE_DECIMALS,
   FOUR_DECIMALS,
   MAX_DECIMALS
}  T_P10;


#endif
