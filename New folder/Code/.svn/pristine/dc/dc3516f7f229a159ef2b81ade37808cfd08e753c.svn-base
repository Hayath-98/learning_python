/*
 ******************************************************************************
 * License Information  :  Howell Instruments, Inc.                           *
 *                         "Licensed Software" and "All rights reserved".     *
 ******************************************************************************
 *  File                : hdudispfpolygon2.c
 *
 *  Description         : The file contains polygons configuration
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
 *      1.1           Shilpa A R          18-Jul-2017             100064
 *      1.2           Shilpa A R          09-Oct-2017             100064
 *      1.3           Rona B S            11-Oct-2017             100064
 *      1.4           Shruthi M N         15-Oct-2017             100083, 100087
 *      1.5           Shruthi M N         30-Oct-2017             100104
 *      1.6           Shilpa A R          07-Nov-2017             100161
 *      1.7           Shruthi M N         08-Nov-2017             100164
 *      1.8           Vinay H             23-Mar-2018             100196
 *      1.9           Vinay H             28-Mar-2018             100196
 *      1.10          Dhanalakshmi D      21-Jun-2020             100259
 *      1.11          Rona B S            02-Jul-2020             100259
 *      1.12          Dhanalakshmi        05-Aug-2020             100270 
 *      1.13          Dhanalakshmi        12-Sep-2020             100276  
 *
 * Additional References : None
 *
 ******************************************************************************
 */

#include "hdudispfarmmath.h"  /* header file for CMSIS DSP Library */
#include "hdudispfrterror.h"     /* Provides stub routine for run time errors.*/
#include "hdudispfconfig.h"    /* contains page and color config information */
#include "hdudispfpolygon2.h"  /* contains routines for polygons configuration */
#include "hdudispfwidgets.h"   /* Contains routines for widget params */
#include "hdulibbasictypes.h"  /* Contains basic data types.*/
#include "hdudispfgrapp.h"   /* defines graphical applications */
#include "hdudispfresource.h"  /* provides central location to use On Chip Peripherals*/
#include "hdudispfpdidata.h" /* provides pdi declarations */

#define PI_VAL 3.14159265358979f
#define POINT_FIVE  0.5f
#define SIXTEEN_POINT_ZERO  16.0f
#define FLOAT_ONE 1.0f
#define FLOAT_TWO 2.0f
#define NUMBER_OF_BITS 32
#define DEC_TWO 2
/* constant used in tangent calculation */
#define TAN_PI         (T_FLOAT32) 3.1415926535897932384f
#define HALF_PI     (T_FLOAT32) 3.1415926535897932384f / 2.0f
#define SIXTH_PI    (T_FLOAT32) 3.1415926535897932384f / 6.0f
#define TWELFTH_PI  (T_FLOAT32) 3.1415926535897932384f / 12.0f
#define TAN_CONST1     -3.6112171f
#define TAN_CONST2      -4.6133253f
#define INV_TAN_CONST1  1.6867629106f
#define INV_TAN_CONST2  0.4378497304f
#define INV_TAN_CONST3  1.6867633134f
#define MAX_POLYGON_GRAPH           50U
#define OCTANT_VAL_0  0U
#define OCTANT_VAL_1  1U
#define OCTANT_VAL_2  2U
#define OCTANT_VAL_3  3U
#define OCTANT_VAL_4  4U
#define OCTANT_VAL_5  5U
#define OCTANT_VAL_6  6U
#define OCTANT_VAL_7  7U

/* Pool for "dynamic allocation" of polygon points. */
static T_UPOLYELEMENT   Upoint_pool[POLY_POINTS_AVAILABLE] = {0};
static T_UPOLYELEMENT   *Pu_next_element = Upoint_pool;
static T_UINT32            U32_elements_allocated = 0;

/* These are used to lock the first of the available elements after initialization. */
static T_UPOLYELEMENT   *Pu_element_lock = Upoint_pool;
static T_UINT32   U32_element_lock = 0;

/* Pool for "dynamic allocation" of polygons. */
static T_SPOLY S_poly_pool[POLYS_AVAILABLE] = {0};
static T_SPOLY *Ps_next_poly = S_poly_pool;
static T_UINT32   U32_polys_allocated = 0;

/* These are used to lock the first of the available polygons after initialization. */
static T_SPOLY *Ps_poly_lock = S_poly_pool;
static T_UINT32   U32_poly_lock = 0;

static T_SFLOATPOLY *PsGetShape(T_ESTOCKSHAPE e_shape);
static void VInitPolar(T_SPOLY *ps_poly, T_INT16 s16_rot);

/*This function determines the Angle for each point in the polygon*/
static T_UINT32 PolygonsAngle(T_INT32 end_rot, T_INT32 start_rot,T_BOOL rd_state,
                                 T_UINT16 pt_ctr, T_INT16 noOfPts);

static T_FLOAT32 Tan32Func(T_FLOAT32 val);
static T_FLOAT32 TangentFunc(T_FLOAT32 val);
static T_FLOAT32 InverseTangent(T_FLOAT32 val);
static T_FLOAT32 ModulusFunc(T_FLOAT32 numerator,T_FLOAT32 denominator);
static T_FLOAT32 SquareRoot(T_FLOAT32 square);

/*
 * Function                :  ModulusFunc
 *
 * Description             :  This function returns the reminder value.
 *
 * Formal parameter(s)     :  T_FLOAT32 numerator - IN contains numerator value
 *                     T_FLOAT32 denominator - IN contains denominator value
 *
 * Return Value            :  T_FLOAT32 - Returns the remider value
 *
 * Assumption              :  None
 *
 */

static T_FLOAT32 ModulusFunc(T_FLOAT32 numerator,T_FLOAT32 denominator)
{
   T_FLOAT32 ret_val=0.0f;
   T_INT32 quotient =0;

   /* hdudispfpolygon2-ModulusFunc-DB-LLR-001 */
   quotient=(T_INT32)(numerator/denominator);
   ret_val=numerator - (T_FLOAT32)((T_FLOAT32)quotient * denominator);
   return ret_val;
}

/*
 * Function                :  Tan32Func
 *
 * Description             :  This function is used to obtain the tan theta value of a number.
 *
 * Formal parameter(s)     :  T_FLOAT32 val - IN  Input value
 *
 * Return Value            :  T_FLOAT32 - Tan theta value of a number
 *
 * Assumption              :  None
 *
 */

static T_FLOAT32 Tan32Func(T_FLOAT32 val)
{
    T_FLOAT32 x_mul_x = 0.0f;

    /* hdudispfpolygon2-Tan32Func-DB-LLR-001 */
    x_mul_x = val * val;
    return (val * TAN_CONST1 / (TAN_CONST2 + x_mul_x));
}

/*
 * Function                :  TangentFunc
 *
 * Description             :  This function is used to obtain the tangent value of a number.
 *
 * Formal parameter(s)     :  T_FLOAT32 val - IN  Input value
 *
 * Return Value            :  T_FLOAT32 - Tangent value of a number
 *
 * Assumption              :  None
 *
 */

static T_FLOAT32 TangentFunc(T_FLOAT32 val)
{
    T_INT32 octant = 0;
    T_FLOAT32 rem_val = 0.0f;
    T_FLOAT32 ret_val = 0.0f;

    /*   hdudispfpolygon2-TangentFunc-DB-LLR-001 */
    rem_val = ModulusFunc(val , (2.0f * TAN_PI));
    octant = (T_INT32)(val / (TAN_PI / FOUR));

    switch (octant)
    {
        case OCTANT_VAL_0 :
         /* hdudispfpolygon2-TangentFunc-DB-LLR-002 */
         ret_val =  Tan32Func((T_FLOAT32)(rem_val * (FOUR/TAN_PI)));
         break;
        case OCTANT_VAL_1 :
         /* hdudispfpolygon2-TangentFunc-DB-LLR-003 */
         ret_val = 1.0f / Tan32Func((T_FLOAT32)((HALF_PI - rem_val) * (FOUR / TAN_PI)));
         break;
        case OCTANT_VAL_2 :
         /* hdudispfpolygon2-TangentFunc-DB-LLR-004 */
         ret_val = -1.0f / Tan32Func((T_FLOAT32)((rem_val - HALF_PI) * (FOUR / TAN_PI)));
         break;
        case OCTANT_VAL_3 :
         /* hdudispfpolygon2-TangentFunc-DB-LLR-005 */
         ret_val = -Tan32Func((T_FLOAT32)((TAN_PI - rem_val) * (FOUR / TAN_PI)));
         break;
        case OCTANT_VAL_4 :
         /* hdudispfpolygon2-TangentFunc-DB-LLR-006 */
         ret_val = Tan32Func((T_FLOAT32)((rem_val - TAN_PI) * (FOUR / TAN_PI)));
         break;
        case OCTANT_VAL_5 :
         /* hdudispfpolygon2-TangentFunc-DB-LLR-007 */
         ret_val = 1.0f / Tan32Func((T_FLOAT32)(((THREE * HALF_PI) - rem_val) * (FOUR / TAN_PI)));
         break;
        case OCTANT_VAL_6 :
         /* hdudispfpolygon2-TangentFunc-DB-LLR-008 */
         ret_val = -1.0f / Tan32Func((T_FLOAT32)((rem_val - (THREE * HALF_PI)) * (FOUR / TAN_PI)));
         break;
        case OCTANT_VAL_7 :
         /* hdudispfpolygon2-TangentFunc-DB-LLR-009 */
         ret_val = -Tan32Func((T_FLOAT32)((TWO * TAN_PI - rem_val) * (FOUR / TAN_PI)));
         break;
        default:
         /* hdudispfpolygon2-TangentFunc-DB-LLR-010 */
         ret_val = 0.0f;
         break;
    }
    return ret_val;
}

/*
 * Function                :  InverseTangent
 *
 * Description             :  This function is used to obtain the inverse tangent
 *                         value of a number.
 *
 * Formal parameter(s)     :  T_FLOAT32 val - IN  Input value.
 *
 * Return Value            :  T_FLOAT32 - Inverse Tangent value of a number.
 *
 * Assumption              :  None
 *
 */
static T_FLOAT32 InverseTangent(T_FLOAT32 val)
{
    T_FLOAT32 y_val = 0;
    T_BOOL complement_val = FALSE;
    T_BOOL region_val = FALSE;
    T_BOOL sign_val = FALSE;
    T_FLOAT32 x2_val = 0;

    if (val < ZERO)
    {
        /* hdudispfpolygon2-InverseTangent-DB-LLR-001 */
        val = -val;
        sign_val = TRUE;
    }
    else
    {
      /* Does nothing */
    }

    if (val > FLOAT_ONE)
    {
      /* hdudispfpolygon2-InverseTangent-DB-LLR-002 */
        val = FLOAT_ONE / val;
        complement_val = TRUE;
    }
    else
    {
      /* Does nothing */
    }

    if (val > TangentFunc((T_FLOAT32)TWELFTH_PI))
    {
      /* hdudispfpolygon2-InverseTangent-DB-LLR-003 */
        val = (val - TangentFunc((T_FLOAT32)SIXTH_PI)) / (ONE + TangentFunc((T_FLOAT32)SIXTH_PI)
                                             * val);
        region_val = TRUE;
    }
    else
    {
      /* Does nothing */
    }

    /*   hdudispfpolygon2-InverseTangent-DB-LLR-004 */
    x2_val = val * val;
    y_val = (val * (INV_TAN_CONST1 + x2_val * INV_TAN_CONST2) / (INV_TAN_CONST3 + x2_val));

    if (TRUE == region_val)
    {
      /* hdudispfpolygon2-InverseTangent-DB-LLR-005 */
        y_val += SIXTH_PI;
    }
    else
    {
      /* Does nothing */
    }

    if (TRUE == complement_val)
    {
      /* hdudispfpolygon2-InverseTangent-DB-LLR-006 */
        y_val = HALF_PI - y_val;
    }
    else
    {
      /* Does nothing */
    }

    if (TRUE == sign_val)
    {
      /* hdudispfpolygon2-InverseTangent-DB-LLR-007 */
        y_val = -y_val;
    }
    else
    {
      /* Does nothing */
    }

    /*   hdudispfpolygon2-InverseTangent-DB-LLR-008 */
    return (T_FLOAT32)y_val;
}

/*
 * Function                :  SquareRoot
 *
 * Description             :  This function is used to find the square root of a number.
 *
 * Formal parameter(s)     :  T_FLOAT32 square - IN  Input value.
 *
 * Return Value            :  T_FLOAT32 - Square root of a number.
 *
 * Assumption              :  None
 *
 */
static T_FLOAT32 SquareRoot(T_FLOAT32 square)
{
    T_FLOAT32 root = square / 3.0f;
    T_INT32 loop_counter = 0;

    if (square <= ZERO)
    {
      /* hdudispfpolygon2-SquareRoot-DB-LLR-001 */
        return ZERO;
    }
    else
    {
      /* Does nothing */
    }

    for (loop_counter = ZERO; loop_counter < NUMBER_OF_BITS; loop_counter++)
    {
      /* hdudispfpolygon2-SquareRoot-DB-LLR-002 */
        root = (root + square / root) / FLOAT_TWO;
    }

    /* hdudispfpolygon2-SquareRoot-DB-LLR-003 */
    return root;
}

/*
 * Function                :  ClearElements
 *
 * Description             :  This function release the pool of PolyElements.
 *
 * Formal parameter(s)     :  None
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */
static void ClearElements(void)
{
   /*hdudispfpolygon2-ClearElements-DB-LLR-001*/
   Pu_next_element = Pu_element_lock;
   U32_elements_allocated = U32_element_lock;
}

/*
 * Function                :  AllocateElements
 *
 * Description             :  The function allocates points to the polygon.
 *
 * Formal parameter(s)     :  T_UINT32 u32_num_elements - IN Number of points to be allocated
 *
 * Return Value            :  T_UPOLYELEMENT - Returns the allocated points
 *
 * Assumption              :  None
 *
 */
static T_UPOLYELEMENT *AllocateElements(T_UINT32 u32_num_elements)
{
   T_UPOLYELEMENT *pu_ret_val = NULL;

   /*hdudispfpolygon2-AllocateElements-DB-LLR-001*/
   if(u32_num_elements > POLY_POINTS_AVAILABLE)
   {
      return((T_UPOLYELEMENT *)NULL);
   }
   else
   {
      /* Does nothing */
   }

   /*hdudispfpolygon2-AllocateElements-DB-LLR-002*/
   if((U32_elements_allocated + u32_num_elements) > POLY_POINTS_AVAILABLE)
   {
      return((T_UPOLYELEMENT *)NULL);
   }
   else
   {
      /* Does nothing */
   }

   /*hdudispfpolygon2-AllocateElements-DB-LLR-003*/
   pu_ret_val = Pu_next_element;
   Pu_next_element += u32_num_elements;
   U32_elements_allocated += u32_num_elements;
   return(pu_ret_val);
}

/*
 * Function                :  ClearPolys
 *
 * Description             :  This function release the pool of PolyElements.
 *
 * Formal parameter(s)     :  None
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */
static void ClearPolys(void)
{
   /* hdudispfpolygon2-ClearPolys-DB-LLR-001 */
   Ps_next_poly = Ps_poly_lock;
   U32_polys_allocated = U32_poly_lock;
}

/*
 * Function                :  PolygonsClear
 *
 * Description             :  This function Clear all post initialization polygon allocations.
 *
 * Formal parameter(s)     :  None
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */
void PolygonsClear(void)
{
   /* hdudispfpolygon2-PolygonsClear-DB-LLR-001 */
   ClearElements();
   ClearPolys();
}

/*
 * Function                :  PsAllocatePoly
 *
 * Description             :  This function allocate a polygon with a specific number of elements.
 *
 * Formal parameter(s)     :  T_INT16 s16_num_elements - IN Number of elements in polygon.
 *
 * Return Value            :  T_SPOLY* - returns polygon.
 *
 * Assumption              :  None
 *
 */
static T_SPOLY *PsAllocatePoly(T_INT16 s16_num_elements)
{
   T_SPOLY           *ps_ret_val = (T_SPOLY *)NULL;
   T_SRECTPOINT   *ps_rec_points = NULL;
   T_SPOLARPOINT *ps_pol_points = NULL;

   T_CHAR parm_pc_message1[] ="Too few points in Polygon.";
   T_CHAR parm_pc_message2[] ="Too few polygons available.";
   T_CHAR parm_pc_message3[] ="Out of poly points.";
   T_CHAR file_name[] = __FILE__;

   /*hdudispfpolygon2-PsAllocatePoly-DB-LLR-001*/
   /* Polygon must have at least three points. */
   if(s16_num_elements < ((T_INT16)THREE))
  {
      RterrWidget((T_CHAR *)file_name, __LINE__, (T_CHAR *)&parm_pc_message1);       
      return(ps_ret_val);
  }
   else
   {
      /* Does nothing */
   }

   /*hdudispfpolygon2-PsAllocatePoly-DB-LLR-002*/
   /* Allocate a polygon to hold the shape. */
   if(U32_polys_allocated >= POLYS_AVAILABLE)
   {
      RterrWidget((T_CHAR *)file_name, __LINE__, (T_CHAR *)&parm_pc_message2);
      return(ps_ret_val);
   }
   else
   {
      /* Does nothing */
   }

   /*hdudispfpolygon2-PsAllocatePoly-DB-LLR-003*/
   ps_ret_val = Ps_next_poly;
   Ps_next_poly += 1;
   U32_polys_allocated += 1;

   /*hdudispfpolygon2-PsAllocatePoly-DB-LLR-004*/
   /* Allocate storage for the rectangular representation. */
   ps_rec_points = (T_SRECTPOINT *)AllocateElements((T_UINT32)s16_num_elements);
   if(NULL == ps_rec_points)
   {
      RterrWidget((T_CHAR *)file_name, __LINE__, (T_CHAR *)&parm_pc_message3);
   }
   else
   {
      /* Does nothing */
   }
   /*hdudispfpolygon2-PsAllocatePoly-DB-LLR-005*/
   /* Allocate storage for the polar representation. */
   ps_pol_points = (T_SPOLARPOINT *)AllocateElements((T_UINT32)s16_num_elements);
   if(NULL == ps_pol_points)
   {
      RterrWidget((T_CHAR *)file_name, __LINE__, (T_CHAR *)&parm_pc_message3);
   }
   else
   {
      /* Does nothing */
   }
   /*hdudispfpolygon2-PsAllocatePoly-DB-LLR-006*/
   ps_ret_val->s16Pts = s16_num_elements;
   ps_ret_val->psRP = ps_rec_points;
   ps_ret_val->psPP = ps_pol_points;
   ps_ret_val->psNext = (T_SPOLY*)NULL;

   return(ps_ret_val);
}

/*
 * Function                :  PolygonsPsDuplicate
 *
 * Description             :  This function  duplicates a polygon
 *
 * Formal parameter(s)     :  T_SPOLY *ps_poly_src - INOUT composite polar/rectangular polygon
 *
 * Return Value            :  T_SPOLY* - returns composite polar/rectangular polygon
 *
 * Assumption              :  None
 *
 */
T_SPOLY *PolygonsPsDuplicate(T_SPOLY *ps_poly_src)
{
   T_SPOLY *ps_poly_dest = NULL;
   T_SPOLY *ps_poly_ret = NULL;
   T_INT16  s16_pt_ctr = 0;

   /*hdudispfpolygon2-PolygonsPsDuplicate-DB-LLR-001*/
   /* Null Pointer Check. */
   if((T_SPOLY *)NULL == ps_poly_src)
   {
      return((T_SPOLY *)NULL);
   }
   else
   {
      /* Does nothing */
   }
   /*hdudispfpolygon2-PolygonsPsDuplicate-DB-LLR-002*/
   ps_poly_ret = PsAllocatePoly(ps_poly_src->s16Pts);
   ps_poly_dest = ps_poly_ret;

   do
   {
      /*hdudispfpolygon2-PolygonsPsDuplicate-DB-LLR-003*/
      for(s16_pt_ctr=0; s16_pt_ctr<ps_poly_src->s16Pts; s16_pt_ctr++)
      {
         ps_poly_dest->psPP[s16_pt_ctr] = ps_poly_src->psPP[s16_pt_ctr];
         ps_poly_dest->psRP[s16_pt_ctr] = ps_poly_src->psRP[s16_pt_ctr];
      }

      /*hdudispfpolygon2-PolygonsPsDuplicate-DB-LLR-004*/
      ps_poly_src = ps_poly_src->psNext;
      if((T_SPOLY *)NULL != ps_poly_src)
      {
         ps_poly_dest->psNext = PsAllocatePoly(ps_poly_src->s16Pts);
         ps_poly_dest = ps_poly_dest->psNext;
      }
      else
      {
         /* Does nothing */
      }

   } while(ps_poly_src);

   /*hdudispfpolygon2-PolygonsPsDuplicate-DB-LLR-005*/
   return(ps_poly_ret);
}

/*
 * Function                :  PolygonsAngle
 *
 * Description             :  This function determines the Angle for each point in the polygon
 *
 * Formal parameter(s)     :  T_INT32 end_rot   - IN  end angle,
 *                            T_INT32 start_rot - IN start angle,
 *                            T_BOOL rd_state   - IN indicates round dial state,
 *                            T_UINT16 pt_ctr   - INOUT pointer counter,
 *                            T_INT16 noOfPts   - IN number of pointers.
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */

static T_UINT32 PolygonsAngle(T_INT32 end_rot, T_INT32 start_rot,T_BOOL rd_state,
                                 T_UINT16 pt_ctr, T_INT16 noOfPts)
{
    T_INT32 angular_diff = 0; /* Angular difference between two points in the moving round dial*/
    T_INT32 updated_angle = 0; /* Angle for each point */
    T_UINT32 rd_angle = 0; /* Angle for each point returned as Unsigned*/

    /*Check whether its a moving round dial or not*/
    if (TRUE == rd_state)
    {
        /*hdudispfpolygon2-PolygonsAngle-DB-LLR-001*/
        /* To ensure first two points are in same Angle  */
        if (pt_ctr > ZERO)
        {
            pt_ctr = (T_UINT16)(pt_ctr - ONE);
        }
		else
        {
            ; /*Do nothing*/
        }
        /* pointer moves in anti-clockwise*/
        /*hdudispfpolygon2-PolygonsAngle-DB-LLR-002*/
        if(end_rot >= start_rot)
        {
            /* Angular difference between two points in the moving round dial*/
            /*  Calculated from subtracting StartAngle from End Angle */
            /*  and dividing it with number of points */

            angular_diff = (end_rot - start_rot)/(noOfPts-DEC_TWO);

            /* updated Angle for each point in the polygon*/
            updated_angle = start_rot + ((pt_ctr) * angular_diff);

            
            /*if updated Angle is greater than end Angle, make it equals to end Angle*/
            /*hdudispfpolygon2-PolygonsAngle-DB-LLR-003*/
            if (updated_angle > end_rot)
            {
                updated_angle = end_rot;
            }
			else
            {
                ; /*Do nothing*/
            }
        }
        /* pointer moves in clockwise */
        /*hdudispfpolygon2-PolygonsAngle-DB-LLR-004*/
        else
        {
            angular_diff = (start_rot - end_rot)/(noOfPts-DEC_TWO);

            updated_angle = start_rot - ((pt_ctr) * angular_diff);

            if (updated_angle < end_rot)
            {
                updated_angle = end_rot;
            }
			else
            {
                ; /*Do nothing*/
            }
        }
    }
    /*hdudispfpolygon2-PolygonsAngle-DB-LLR-005*/
    else
    {
        updated_angle = end_rot;
    }

    rd_angle = (T_UINT32)updated_angle;

    /*hdudispfpolygon2-PolygonsAngle-DB-LLR-006*/
    /* Angle must be between 0 and 2 * Pi. */
    rd_angle &= ANGLE_MASK;

    /*hdudispfpolygon2-PolygonsAngle-DB-LLR-007*/
    /* Adjust 90 Deg.if portrait. */
    if(E_PORTRAIT == E_orientation)
    {
        rd_angle = (T_UINT32) (rd_angle - ANGLE_SUBT);
        rd_angle &= ANGLE_MASK;
    }
    else
    {
        /* Does nothing */
    }
    /*hdudispfpolygon2-PolygonsAngle-DB-LLR-008*/
    return(rd_angle);
}


/*
 * Function                :  PolygonsvPolarToRect
 *
 * Description             :  This function Rotates, translates and projects a polygon
 *
 * Formal parameter(s)     :  T_SPOLY *ps_poly - INOUT composite polar/rectangular polygon
 *                            T_INT32 s32_xoff - INOUT X-axis co-ordinate
 *                            T_INT32 s32_yoff - INOUT Y-axis co-ordinate
 *                            T_UINT16 u16_len - IN  Length
 *                            T_UINT32 u32_rot - INOUT Angle
 *                            T_INT32 u32_rot_rd - IN Round dial Angle
 *							  T_BOOL moving_rd - IN  Moving Round dial State
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */
void PolygonsvPolarToRect(T_SPOLY *ps_poly, T_INT32 s32_xoff, T_INT32 s32_yoff,
                           T_UINT16 u16_len, T_INT32 u32_rot, T_INT32 u32_rot_rd,T_BOOL moving_rd)
{
   T_UINT16 u16_pt_ctr = 0;
   T_INT32 s32_temp = 0;
   T_INT32 s32_theta = 0;
   T_INT32 s32_cos_theta = 0;
   T_INT32 s32_sin_theta = 0;
   T_INT32 s32_lenx = 0;
   T_INT32 s32_leny = 0;
   T_UINT32 angle_rot = 0;


   T_CHAR parm_pc_message1[] ="Null pointer pointer.";
   T_CHAR file_name[] = __FILE__;

   /*hdudispfpolygon2-PolygonsvPolarToRect-DB-LLR-001*/
   if(NULL == ps_poly)
   {
      RterrWidget((T_CHAR *)file_name, __LINE__, (T_CHAR *)&parm_pc_message1);
      return;
   }
   else
   {
      /* Does nothing */
   }

   /*hdudispfpolygon2-PolygonsvPolarToRect-DB-LLR-002*/
   /* Translate XY coordinates if Portrait mode. */
   if(E_PORTRAIT == E_orientation)
   {
      s32_temp = s32_xoff;
      s32_xoff = s32_yoff;
      s32_yoff = (T_INT32)(S16_panel_height* (T_INT32)MAG_FACTOR) - s32_temp;
   }
   else
   {
      /* Does nothing */
   }


   do
   {
      /* Update the (X,Y) coordinates of each point in the polygon. */
      for(u16_pt_ctr=0; u16_pt_ctr < ps_poly->s16Pts; u16_pt_ctr++)
      {
          /*hdudispfpolygon2-PolygonsvPolarToRect-DB-LLR-006*/		  
          /*Function returns the Angle for the points*/
    	  angle_rot = PolygonsAngle(u32_rot, u32_rot_rd, moving_rd, u16_pt_ctr, ps_poly->s16Pts);

          /* Calc coor offset due to pointer length. */
          s32_lenx = (ArmCosQ15((T_Q15)angle_rot)  * u16_len);
          s32_leny = (ArmSinQ15((T_Q15)angle_rot) * u16_len);

          /* Calculate and limit the absolute angle */
          s32_theta = (T_INT32)ps_poly->psPP[u16_pt_ctr].s32A;
          s32_theta = (T_INT32)(s32_theta + (T_INT32)angle_rot);
          s32_theta  = s32_theta & (T_INT32)ANGLE_MASK;

          /* Get sin and cos of absolute angle. */
          s32_cos_theta =(T_INT32) ArmCosQ15((T_INT16)s32_theta);
          s32_sin_theta =(T_INT32) ArmSinQ15((T_INT16)s32_theta);

          /*hdudispfpolygon2-PolygonsvPolarToRect-DB-LLR-007*/
          /* Calculate the X coor. */
          s32_temp =  ps_poly->psPP[u16_pt_ctr].s32R;
          s32_temp *= (T_INT32)s32_cos_theta;
          s32_temp >>= TWO;
          s32_temp += s32_lenx;
          s32_temp >>= FORTEEN;
          s32_temp = s32_temp + (T_INT32)ONE;
          s32_temp >>= ONE;

          ps_poly->psRP[u16_pt_ctr].s32X = s32_temp;
          ps_poly->psRP[u16_pt_ctr].s32X += s32_xoff;

          /*hdudispfpolygon2-PolygonsvPolarToRect-DB-LLR-008*/
          /* Calculate the Y coor. */
          s32_temp =  ps_poly->psPP[u16_pt_ctr].s32R;
          s32_temp *= (T_INT32)s32_sin_theta;
          s32_temp >>= TWO;
          s32_temp += s32_leny;
          s32_temp >>= FORTEEN;
          s32_temp = s32_temp + (T_INT32)ONE;
          s32_temp >>= ONE;

          ps_poly->psRP[u16_pt_ctr].s32Y = s32_temp;
          ps_poly->psRP[u16_pt_ctr].s32Y += s32_yoff;
      }
      /*hdudispfpolygon2-PolygonsvPolarToRect-DB-LLR-009*/
      ps_poly = ps_poly->psNext;
   }while(ps_poly);
}

/*
 * Function                :  PsGetShape
 *
 * Description             :  The function returns points to draw a polygon based on
 *                            the input shape.
 *
 * Formal parameter(s)     :  T_ESTOCKSHAPE e_shape - IN Input shape
 *
 * Return Value            :  T_SFLOATPOLY* - Pointer to structure containing the points
 *                                            to draw polygon
 *
 * Assumption              :  None
 *
 */
static T_SFLOATPOLY *PsGetShape(T_ESTOCKSHAPE e_shape)
{
   T_CHAR parm_pc_message1[] ="Undefined Stock Shape.";
   T_CHAR file_name[] = __FILE__;
   T_SFLOATPOLY *ptr_points_draw = (T_SFLOATPOLY *)NULL;
   T_UINT16 loop_i = 0;

   typedef enum
   {
     VALID_SHAPE =1,
	 INVALID_SHAPE =2
   }T_ERROR_FLAG;
   T_ERROR_FLAG shape_valid = INVALID_SHAPE;

   /*hdudispfpolygon2-PsGetShape-DB-LLR-001*/
   if((ENOSHAPE == e_shape) || (e_shape >= EMAXSTOCKSHAPE))
   {
      return((T_SFLOATPOLY *)NULL);
   }
   else
   {
      ; /*Do nothing*/
   }
   
   /* Added to make Polygons configurable -future Change */
   /*hdudispfpolygon2-PsGetShape-DB-LLR-018*/
   for (loop_i = 0;loop_i< MAX_POLYGON_GRAPHS;loop_i++)
   {
	   if(e_shape == Ap_poly_graph[loop_i].polygon_shape)
	   {
		   shape_valid = VALID_SHAPE;
		   ptr_points_draw = Ap_poly_graph[loop_i].polystruct;
           break;
	   }
   }
   /*hdudispfpolygon2-PsGetShape-DB-LLR-019*/
   if (shape_valid != VALID_SHAPE)
   {
       RterrWidget((T_CHAR *)file_name, __LINE__, (T_CHAR *)&parm_pc_message1);
   }
   /*hdudispfpolygon2-PsGetShape-DB-LLR-020*/
   return ptr_points_draw;
}

/*
 * Function                :  VInitPolar
 *
 * Description             :  This function initialize a polygon by scaling a stock shape.
 *
 * Formal parameter(s)     :  T_SPOLY *ps_poly - IN composite polar/rectangular polygon
 *                            T_INT16 s16_rot - IN Angle
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */
static void VInitPolar(T_SPOLY *ps_poly, T_INT16 s16_rot)
{
   T_SRECTPOINT   *ps_rec_pt = NULL;
   T_SPOLARPOINT *ps_pol_pt = NULL;
   T_INT16           s16_pt_ctr = 0;
   T_INT32           s32_rsq = 0;
   T_FLOAT             f_temp = 0.0f;

   /*hdudispfpolygon2-VInitPolar-DB-LLR-001*/
   ps_rec_pt   =  ps_poly->psRP;
   ps_pol_pt = ps_poly->psPP;

   for(s16_pt_ctr=ZERO; s16_pt_ctr < ps_poly->s16Pts; s16_pt_ctr++)
   {
      /* Calculate and store the angle of the vector. */
      /* Check for 90 or 270 Degrees. */
      if(ZERO == ps_rec_pt[s16_pt_ctr].s32X )
      {
       /*hdudispfpolygon2-VInitPolar-DB-LLR-002*/
         if(ps_rec_pt[s16_pt_ctr].s32Y > ((T_INT32)ZERO))
         {
            /* Angle is Pi/2. */
            ps_pol_pt[s16_pt_ctr].s32A = ANGLE_PIBY2;
         }
         else
         {
            /* Angle is 3 Pi / 2 */
            ps_pol_pt[s16_pt_ctr].s32A = ANGLE_3PIBY2_1;
         }
      }

      /* Check for 0 or 180 Degrees. */
      else if( ((T_INT32)ZERO) == ps_rec_pt[s16_pt_ctr].s32Y)
      {
       /*hdudispfpolygon2-VInitPolar-DB-LLR-003*/
         if(ps_rec_pt[s16_pt_ctr].s32X > ((T_INT32)ZERO))
         {
            /* Angle is Pi/2. */
            ps_pol_pt[s16_pt_ctr].s32A = ((T_INT32)ZERO);
         }
         else
         {
            /* Angle is 3 Pi / 2 */
            ps_pol_pt[s16_pt_ctr].s32A = ANGLE_3PIBY2_2;
         }
      }
      else
      {
         /*hdudispfpolygon2-VInitPolar-DB-LLR-004*/
         f_temp  = (T_FLOAT32)InverseTangent((T_FLOAT32)(ps_rec_pt[s16_pt_ctr].s32Y)/
                                (T_FLOAT32)(ps_rec_pt[s16_pt_ctr].s32X));

         /*hdudispfpolygon2-VInitPolar-DB-LLR-005*/
         /* Test for quadrant shift. */
         if((ps_rec_pt[s16_pt_ctr].s32X < ((T_INT32)ZERO)) &&
                              (ps_rec_pt[s16_pt_ctr].s32Y > ((T_INT32)ZERO)))
         {
            f_temp += PI_VAL;
         }
         else if((ps_rec_pt[s16_pt_ctr].s32X < ((T_INT32)ZERO)) &&
                              (ps_rec_pt[s16_pt_ctr].s32Y < ((T_INT32)ZERO)))
         {
            f_temp += PI_VAL;
         }
         else if((ps_rec_pt[s16_pt_ctr].s32X > ((T_INT32)ZERO)) &&
                               (ps_rec_pt[s16_pt_ctr].s32Y < ((T_INT32)ZERO)))
         {
            f_temp += (FLOAT_TWO * PI_VAL);
         }
         else
         {
            ; /* Do nothing */
         }

         /*
          * The integer representation of the angle lies between
          * (0 = 0) and (0x8000 = 2 PI_VAL) radians.
          */
         f_temp *= (T_FLOAT)PI_2_RAD_MAX;
         f_temp /= FL2XPI;
         ps_pol_pt[s16_pt_ctr].s32A = (T_INT32)(f_temp+POINT_FIVE);
      }

      /*hdudispfpolygon2-VInitPolar-DB-LLR-006*/
      ps_pol_pt[s16_pt_ctr].s32A += (T_INT32)s16_rot;
      ps_pol_pt[s16_pt_ctr].s32A = ps_pol_pt[s16_pt_ctr].s32A & (T_INT32)ANGLE_MASK;

      /*hdudispfpolygon2-VInitPolar-DB-LLR-007*/
      /* Calculate and store the length of the vector * 16. */
      s32_rsq = (ps_rec_pt[s16_pt_ctr].s32X * ps_rec_pt[s16_pt_ctr].s32X) +
                       (ps_rec_pt[s16_pt_ctr].s32Y * ps_rec_pt[s16_pt_ctr].s32Y);

      f_temp = (T_FLOAT)s32_rsq * SIXTEEN_POINT_ZERO;
      f_temp = (T_FLOAT)SquareRoot((T_FLOAT32)f_temp);
      f_temp += POINT_FIVE;
      ps_pol_pt[s16_pt_ctr].s32R = (T_INT32)(f_temp);
   }
}

/*
 * Function                :  PolygonsPsPolyInit
 *
 * Description             :  The function release the pool of PolyElements
 *
 * Formal parameter(s)     :  T_ESTOCKSHAPE e_poly_shape - IN Shape of polygon
 *                            T_FLOAT fx_scale - IN X-axis scaling factor
 *                            T_INT16 s16_xoff - IN X-axis offset
 *                            T_FLOAT fy_scale - IN X-axis scaling factor
 *                            T_INT16 s16_yoff - IN Y-axis offset
 *                            T_INT16 s16_rot - IN Angle
 *
 * Return Value            :  T_SPOLY * -returns composite polar/rectangular polygon
 *
 * Assumption              :  None
 *
 */
T_SPOLY * PolygonsPsPolyInit(T_ESTOCKSHAPE e_poly_shape
                                             ,T_FLOAT fx_scale
                                             ,T_INT16 s16_xoff
                                             ,T_FLOAT fy_scale
                                             ,T_INT16 s16_yoff
                                             ,T_INT16 s16_rot
                                 )
{
   const T_SFLOATPOLY   *ps_float_poly = NULL;
   T_SPOLY *ps_poly = NULL;
   T_INT16 s16_point_ctr = 0;

   T_SRECTPOINT *ps_rect_point = NULL;
   const T_SFLOATPOINT *ps_float_point = NULL;
   T_SPOLY *ps_ret_val = NULL;

   /*hdudispfpolygon2-PolygonsPsPolyInit-DB-LLR-001*/
   ps_float_poly = PsGetShape(e_poly_shape);
   ps_poly =   PsAllocatePoly(ps_float_poly->s16Points);
   ps_ret_val  = ps_poly;

   do
   {
      /*hdudispfpolygon2-PolygonsPsPolyInit-DB-LLR-002*/
      ps_float_point = ps_float_poly->asFloatPoint;
      ps_rect_point  = ps_poly->psRP;
      s16_point_ctr = ps_float_poly->s16Points;

      /*hdudispfpolygon2-PolygonsPsPolyInit-DB-LLR-003*/
      /* Initialize the rectangular points of the polygon. */
      while(s16_point_ctr--)
      {
         ps_rect_point->s32X = (T_INT32)((ps_float_point->fX * fx_scale * MAG_FACTOR)) + s16_xoff;
         ps_rect_point->s32Y = (T_INT32)((ps_float_point->fY * fy_scale * MAG_FACTOR)) + s16_yoff;
         ps_float_point += ONE;
         ps_rect_point += ONE;
      }
      /*hdudispfpolygon2-PolygonsPsPolyInit-DB-LLR-004*/
      /* Init the polar points of the polygon. */
      VInitPolar(ps_poly, s16_rot);

      /*hdudispfpolygon2-PolygonsPsPolyInit-DB-LLR-005*/
      /* See if there is more to do. */
      ps_float_poly = ps_float_poly->psNext;
      if( (T_SFLOATPOLY *)NULL != ps_float_poly)
      {
         ps_poly->psNext = PsAllocatePoly(ps_float_poly->s16Points);
         ps_poly = ps_poly->psNext;
      }
	  else
      {
         ; /*Do nothing*/
      }
    }  while(ps_float_poly);

   /*hdudispfpolygon2-PolygonsPsPolyInit-DB-LLR-006*/
   PolygonsvPolarToRect(ps_ret_val, XOFF_ZERO, YOFF_ZERO, LEN_ZERO, ROT_ZERO, ROT_ZERO, FALSE);

   /*hdudispfpolygon2-PolygonsPsPolyInit-DB-LLR-007*/
   return (ps_ret_val);
}
