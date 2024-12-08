/*
 ******************************************************************************
 * License Information  :  Howell Instruments, Inc.                           *
 *                         "Licensed Software" and "All rights reserved".     *
 ******************************************************************************
 *  File                : hdudispfdemo.h
 *
 *  Description         : : This file contains prototype and structure definations for
 *                        Demo mode.
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
 * <Version No.>     <Author>          <Date>         <Problem Report No.>
 *
 *      1.1          Shilpa A R      23-Mar-2018             100196
 *      1.2          Rona B S        05-Jul-2020             100259
 *
 * Additional References : None
 *
 ******************************************************************************
 */

#ifndef _HDUDISPFDEMO_H_
#define _HDUDISPFDEMO_H_

#include "hdudispfresource.h" /* provides central location to use On Chip Peripherals*/
#include "hdudispfucos.h"     /* defines the implementation of uC/OS routines  */
#include "hdudispfarinc825.h" /* Define the structure for an ARINC 825 Message. */
#include "hdudispfrtd.h"      /* Provide mapping for all A825 incoming parameters */
#include "hdudispfa429.h"     /* Provide mapping for all A429 parameters */

#define MAX_A429_LABELS  256U
#define MAX_A429_CHANNEL 2U
#define DEMO_DOC_ID      161U
#define MAX_CAS_DATA     0xFFFF
#define MAX_CAS_COUNT    5U
#define MAX_EXCEE_DATA   0x80
#define HEX_F0           0xF0
#define HEX_0F           0x0F
#define HEX_CC           0xCC
#define HEX_33           0x33
#define HEX_AA           0xAA
#define HEX_55           0x55
/* From bit 11 to 29 */
#define MAX_A429_DATA_VALUE    0x7FFFF

typedef struct
{
   T_A429_DATA_STRUCT A429_data;
   T_FLOAT    data;
   T_UINT32 localtimer;
   T_BOOL FWD;
}T_A429_DEMO_STRUCT;

extern T_OS_EVENT *Sem_demo_task;
extern T_OS_STK Demo_task_stk[DEMO_TASK_STK_SIZE];
extern T_BOOL Demo_active;

extern void DemoInit(void);
extern void DemoSignalTask(void);
#endif /* _HDUDISPFDEMO_H_ */
