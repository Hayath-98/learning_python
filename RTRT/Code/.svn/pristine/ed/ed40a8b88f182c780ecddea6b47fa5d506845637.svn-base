/*
 ******************************************************************************
 * License Information  :  Howell Instruments, Inc.                           *
 *                         "Licensed Software" and "All rights reserved".     *
 ******************************************************************************
 *  File                : hdudispfbfarmsinq15.c
 *
 *  Description         : This file contains sine calculation for Q15 values.
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
 *      1.1           Shilpa A R       20-Jul-2017             100064
 *      1.2           Shruthi M N      15-Oct-2017             100083
 *      1.3           Shruthi M N      30-Oct-2017             100104
 *      1.4           Rona B S         02-Jul-2020             100259
 *
 * Additional References : None
 *
 ******************************************************************************
 */
#include "hdudispfarmmath.h"           /* header file for CMSIS DSP Library */
#include "hdudispfbfarmcommontables.h"  /* contains extern declaration for common tables */
#include "hdulibbasictypes.h"         /* Standard basic data type definitions */

/*
 * Function                : ArmSinQ15
 *
 * Description             : This function provides approximation to the trigonometric sine
 *                           function for Q15 data . The Q15 input value is in the range
 *                           [0 +0.9999] and is mapped to a radian value in the range [0 - 2*pi).
 *
 * Formal parameter(s)     : T_Q15 x_val - IN  Scaled value in radians.
 *
 * Return Value            : T_Q15
 *
 * Assumption              : None
 */
T_Q15 ArmSinQ15(T_Q15 x_val)
{
  /* Updated as per PR100083*/
  T_Q31 sin_val = ZERO;                /* Temporary variables for input, output */
  T_INT32 arr_index = ZERO;            /* arr_index variables */
  T_Q15 sin_tab_a = ZERO;
  T_Q15 sin_tab_b = ZERO;              /* Four nearest output values */
  T_Q15 fract = ZERO;                  /* Temporary values for fractional values */

  /*hdudispfbfarmsinq15-ArmSinQ15-DB-LLR-001*/
  /* Calculate the nearest index */
  arr_index = (T_INT32) ((T_UINT32)x_val >> FAST_MATH_Q15_SHIFT);

   /*hdudispfbfarmsinq15-ArmSinQ15-DB-LLR-002*/
   /* Calculation of fractional value */
  fract = (T_Q15)((x_val - (arr_index << FAST_MATH_Q15_SHIFT)) << NINE);

  /* Read two nearest values of input value from the sin table */
  /*hdudispfbfarmsinq15-ArmSinQ15-DB-LLR-003*/
  sin_tab_a = Sin_table_q15[arr_index];
  /*hdudispfbfarmsinq15-ArmSinQ15-DB-LLR-004*/
  sin_tab_b = Sin_table_q15[arr_index+1];

  /*hdudispfbfarmsinq15-ArmSinQ15-DB-LLR-005*/
  /* Linear interpolation process */
  /* Updated as per PR100083*/
  sin_val = ((T_Q31)((T_Q31)HEX_8000-fract)*sin_tab_a >> SIXTEEN);
  /*hdudispfbfarmsinq15-ArmSinQ15-DB-LLR-006*/
  sin_val = ((((T_Q31)sin_val << SIXTEEN) + ((T_Q31)fract*sin_tab_b)) >> SIXTEEN);

  /*hdudispfbfarmsinq15-ArmSinQ15-DB-LLR-007*/
  /* Updated as per PR100083*/
  return (T_Q15)(sin_val << ONE);
}
