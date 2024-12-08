/*
 ******************************************************************************
 * License Information  :  Howell Instruments, Inc.                           *
 *                         "Licensed Software" and "All rights reserved".     *
 ******************************************************************************
 *  File                : hdudispfpbs.h
 *
 *  Description         : Interface definitions push button Switches.
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
 *      1.1          Shilpa A R       13-Sep-2017             100064
 *      1.2          Shruthi M N      15-Oct-2017             100083
 *      1.3          Dhanalakshmi D   21-Jun-2020             100259
 *      1.4          Rona B S	      29-Jun-2020             100259
 *
 * Additional References : None
 *
 ******************************************************************************
 */

#ifndef  _HDUDISPFPBS_H_
#define  _HDUDISPFPBS_H_

#include "hdulibbasictypes.h"  /* Standard basic data type definitions */

/* CONSTS      */

#define DELAY_UNTIL_REPEAT       1000  /* Delay from 1st press to repeat mS.  */
#define REP_RATE                 300   /* Delay between repeats (mS). */

#define PBS1_M       0x01     /* Mask for PBS1.    */
#define PBS2_M       0x02     /* Mask for PBS2.    */
#define PBS3_M       0x04     /* Mask for PBS3.    */
#define PBS4_M       0x08     /* Mask for PBS4.    */
#define PBS5_M       0x10     /* Mask for PBS5.    */
#define PBS6_M       0x20     /* Mask for PBS6.    */
#define PBS7_M       0x40     /* Mask for PBS7.    */
#define PBS8_M       0x80     /* Mask for PBS8.    */
#define PBS9_M       0x100    /* Mask for PBS9.    */
#define PBS10_M      0x200    /* Mask for PBS10.      */
#define PBS11_M      0x400    /* Mask for PBS11.      */
#define PBS12_M      0x800    /* Mask for PBS12.      */
#define PBS13_M      0x1000   /* Mask for PBS13.      */

/* TYPES       */

typedef struct
{
   T_INT8   pressed;
   T_INT8   twist;
}  T_ENCODER;


typedef struct
{
   T_INT8   activity;   /* Any button depressed or encoder action.*/
   T_INT8   pressed;    /* Any valid de-bounced presses or encoder change.*/
   T_UINT16 raw;        /* Direct port read of PBS.*/
   T_INT8   b1;
   T_INT8   b2;
   T_INT8   b3;
   T_INT8   b4;
   T_INT8   b5;
   T_INT8   b6;
   T_INT8   b7;
   T_INT8   b8;
   T_INT8   b10;   
   T_INT8   b11;
   T_INT8   b12;
   T_INT8   b13;  
   T_INT8   c1;
   T_INT8   c2;
   T_INT8   c3;
   T_ENCODER  sLE;
   T_ENCODER  sRE;
}T_PBS;

/* GLOBALS     */
extern T_PBS Switches;           /* Results of pbs get. */
/* Updated as per PR100083*/
extern T_BOOL Long_press;
/* FUNCTIONS   */
extern void PbsDriver(void);
extern void PbsGet(void);
extern void PbsInit (void);
extern void PbsClear(void);


#endif
