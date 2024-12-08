/*
 ******************************************************************************
 * License Information  :  Howell Instruments, Inc.                           *
 *                         "Licensed Software" and "All rights reserved".     *
 ******************************************************************************
 *  File                : hdudispflookup.c
 *
 *  Description         : This file implements the functions for value lookup from a table
 *                        of values.  The table must be monotonic.  The table represents
 *                        a piece wise linear representation of a function.
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

#include "hdudispflookup.h"      /* Provide the table lookup routines */
#include "hdulibbasictypes.h"  /* Standard basic data type definitions */

/*
 * Function                :  LookupTableLookup
 *
 * Description             :  The function Calculate the sensor unit value for the corresponding
 *                            ADC reading.
 *
 * Formal parameter(s)     :  const T_LOOKUP_TABLE *table - IN Pointer to look up table
 *                            T_INT32 ind_var - IN Value to be searched in Lookup table
 *                            T_PARAM_STAT *stat - INOUT Status parameter for lookup table
 *
 * Return Value            :  T_INT32 - Calculated Sensor unit value for the
 *                            corresponding ADC reading
 *
 * Assumption              :  None
 *
 */

T_INT32 LookupTableLookup (const T_LOOKUP_TABLE *table, T_INT32 ind_var, T_PARAM_STAT *stat)
{
   T_INT16        num_segs = 0;
    /* Updated as per PR100083*/
   const T_INT32  *x_array = NULL;
   const T_INT32  *y_array = NULL;
   T_BOOL         neg_val = FALSE;
   T_INT32        seg_delta_x = 0;
   T_INT32        seg_delta_y = 0;
   T_INT32        delta_x = 0;
   T_INT32        results = 0;

   /*hdudispflookup-LookupTableLookup-DB-LLR-001*/
  /*The function returns 0 if lookup table is empty or lookup status is empty */
  if ((NULL == table -> x) || (NULL == table -> y ) || (NULL == stat))
  {

     return ZERO; /* Defensive Code */
  }

  else
  {
      x_array = table -> x;
      y_array = table -> y;

      num_segs = (T_INT16)*(x_array++);
      y_array++;

      /* If the independent array is increasing. */
      if (*x_array <= *(x_array + num_segs - ONE))
      {
       /*hdudispflookup-LookupTableLookup-DB-LLR-002*/
         /* Independent var to low? */
         if (*x_array >= ind_var)
         {
            *stat = RANGE_ERROR;
            return (*y_array);
         }
         else
         {
            /* Does nothing */
         }
         /*hdudispflookup-LookupTableLookup-DB-LLR-003*/
         /* Independent to high? */
         if (*(x_array+num_segs-ONE) <= ind_var)
         {
            *stat = RANGE_ERROR;
            return (*(y_array+num_segs-ONE));
         }
         else
         {
            /* Does nothing */
         }

         /* Perform binary search for the correct segment.*/
         /* Do until just above the correct segment.*/
         do
         {
            /*hdudispflookup-LookupTableLookup-DB-LLR-004*/
            /* Reduce step of binary search.*/
            if(num_segs > (T_INT16)ONE)
            {
               num_segs >>= ONE;
            }
            else
            {
               /* Does nothing */
            }

            /* Adjust the array pointers.*/
            if (*x_array <= ind_var)
            {
               x_array += num_segs;
               y_array += num_segs;
            }
            else
            {
               x_array -= num_segs;
               y_array -= num_segs;
            }

         }
         while(!((*x_array > ind_var) &&  (*(x_array-ONE) <= ind_var)));
      }

      /* Else if independent array is decreasing.*/
      else
      {
       /*hdudispflookup-LookupTableLookup-DB-LLR-005*/
         /* Independent var to low*/
         if (*x_array <= ind_var)
         {
            return (*y_array);
         }
         else
         {
            /* Does nothing */
         }
         /*hdudispflookup-LookupTableLookup-DB-LLR-006*/
         /* Independent to high*/
         if (*(x_array+num_segs-ONE) >= ind_var)
         {
            return (*(y_array+num_segs-ONE));
         }
         else
         {
            /* Does nothing */
         }

         /* Perform binary search for the correct segment.*/
         /* Do until just above the correct segment.*/
         do
         {
         /*hdudispflookup-LookupTableLookup-DB-LLR-007*/
            /* Reduce step of binary search.*/
            if(num_segs > (T_INT16)ONE)
            {
               num_segs >>= ONE;
            }
            else
            {
               /* Does nothing */
            }

            if (*x_array >= ind_var)
            {
               x_array += num_segs;
               y_array += num_segs;
            }
            else
            {
               x_array -= num_segs;
               y_array -= num_segs;
            }

         }
         while(!((*x_array < ind_var) &&  (*(x_array-ONE) >= ind_var)));
      }
      /*hdudispflookup-LookupTableLookup-DB-LLR-008*/
      seg_delta_x = (T_INT32)*x_array;
      seg_delta_x -= (T_INT32)(*(--x_array));
      delta_x = (T_INT32)ind_var - (T_INT32)*x_array;
      seg_delta_y = (T_INT32)*y_array;
      seg_delta_y -= (T_INT32)(*(--y_array));
      /*hdudispflookup-LookupTableLookup-DB-LLR-009*/
      results =  ((delta_x * seg_delta_y) * (T_INT32)TWO);
      results = results / seg_delta_x;
      /*hdudispflookup-LookupTableLookup-DB-LLR-010*/
      if (results < (T_INT32)ZERO)
      {
         neg_val = TRUE;
         results = -results;
      }
      else
      {
         /* Does nothing */
      }
      /*hdudispflookup-LookupTableLookup-DB-LLR-011*/
      results =  results + (T_INT32)ONE;
      results >>= ONE;
      /*hdudispflookup-LookupTableLookup-DB-LLR-012*/
      if (TRUE == neg_val)
      {
         results = -results;
      }
      else
      {
         /* Does nothing */
      }
      /*hdudispflookup-LookupTableLookup-DB-LLR-013*/
      results = results + (T_INT32)(*y_array);
  }
   /*hdudispflookup-LookupTableLookup-DB-LLR-014*/
    /* Updated as per PR100083*/
   return ( results);
}



