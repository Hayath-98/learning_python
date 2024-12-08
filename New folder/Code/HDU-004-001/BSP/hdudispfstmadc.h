/*
 ******************************************************************************
 * License Information  :  Howell Instruments, Inc.                           *
 *                         "Licensed Software" and "All rights reserved".     *
 ******************************************************************************
 *  File                : hdudispfstmadc.h
 *
 *  Description         : This file declares the internal ADC and polls for conversion
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
 *      1.1          Vinay H         21-Jul-2017             100064
 *      1.2          Divya G P       09-Oct-2017             100064
 *
 * Additional References : None
 *
 ******************************************************************************
 */
#ifndef _HDUDISPFSTMADC_H_
#define _HDUDISPFSTMADC_H_

#include "hdulibbasictypes.h"  /* Standard basic data type definitions */

#define NUM_CHAN  2U

extern T_INT16 S16_adc_reading[NUM_CHAN];

/*Functions*/
extern void StmadcInit(void);
extern void StmadcDriver(void);

#endif
