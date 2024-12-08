/*
 ******************************************************************************
 * License Information  :  Howell Instruments, Inc.                           *
 *                         "Licensed Software" and "All rights reserved".     *
 ******************************************************************************
 *  File                : hdudispfwidgets.c
 *
 *  Description         : This file defines functions to draw RedX,to update the number Box and
 *                        to recalculate the polygon location.
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
 *      1.1          Vinay H         14-Sep-2017             100064
 *      1.2          Rona B.S        10-Oct-2017             100064
 *      1.3          Shruthi M N     15-Oct-2017             100083
 *      1.4          Shruthi M N     30-Oct-2017             100104
 *      1.5          Sainath G N     21-Jun-2020             100259
 *      1.6          Rona B S        02-Jul-2020             100259
 *      1.7          Dhanalakshmi    12-Sep-2020             100276 
 *
 *
 * Additional References : None
 *
 ******************************************************************************
 */

#include "hdudispffonts.h"      /*Contains different font information*/
#include "hdudispfpolygon1.h"    /*implements the "scan line" method polygon fill.*/
#include "hdudispftext.h"       /*  Routines which maintain text display and updates */
#include "hdudispfwidgets.h"    /* Contains routines for widget params */
#include "hdudispfconfig.h"     /* contains page and color config information */
#include "hdudispfbinascii.h"   /*Utility routines to convert binary to ascii base 10.*/
#include "hdulibbasictypes.h"   /* Standard basic data type definitions */
#include "hdudispfpanel.h"     /* Contains functions prototypes of panel.*/

/*Static function*/
 /* Updated as per PR100083*/
static void RedXNumber(T_SPOLY *ps_red_bar);

#define EXTRACT_1_4_BIT          0x000F
#define SCALING_VAL_RED          3.0F

/*
 * Function                : RedXGauge
 *
 * Description             : Displays RedX for Gauge and display the corressponding text.
 *
 * Formal parameter(s)     : T_SDISREGION *ps_dis_region - IN Pointer to RedX region parameters.
 *                           T_SPOLY *ps_red_x - IN Pointer to RedX polygon.
 *
 * Return Value            : None
 *
 * Assumption              : None
 *
 */
void RedXGauge(T_SDISREGION *ps_dis_region, T_SPOLY *ps_red_x)
{
   T_INT16  s16_text_loc_x = 0;
   T_INT16  s16_text_loc_y = 0;

   /*hdudispfwidgets-RedXGauge-DB-LLR-001*/
   PolygonFillRect( (T_INT16) (ps_dis_region->sDisLocCtr.u16X0 - (ps_dis_region->s32Width/2))
                      ,(T_INT16) (ps_dis_region->sDisLocCtr.u16Y0 - (ps_dis_region->s32Height/2))
                      ,(T_INT16) ps_dis_region->s32Width
                      ,(T_INT16) ps_dis_region->s32Height
                      ,BLACK);

   /*hdudispfwidgets-RedXGauge-DB-LLR-002*/
   PolygonDrawPoly(ps_red_x, RED);

   /*hdudispfwidgets-RedXGauge-DB-LLR-003*/
   /* Locate center of string display. */
   s16_text_loc_x = (T_INT16)(ps_dis_region->sDisLocCtr.u16X0 + ps_dis_region->sDisLocO.u16X0);
   s16_text_loc_y = (T_INT16)(ps_dis_region->sDisLocCtr.u16Y0 + ps_dis_region->sDisLocO.u16Y0);

   /* If the region text is defined. */
   if(ps_dis_region->pu8Text != ZERO)
   {
      /* If the region text is not an empty string. */
      if(ZERO != *(ps_dis_region->pu8Text))
      {
        /*hdudispfwidgets-RedXGauge-DB-LLR-004*/
         TextDispString((T_INT8 *)(ps_dis_region->pu8Text)
                                 ,(T_UINT16)s16_text_loc_x
                                 ,(T_UINT16)s16_text_loc_y
                                 ,ps_dis_region->eTXFont
                                 ,LIGHT_RED
                                 ,TX_NO_FLASH
                                 ,V_NORMAL
                                 ,ALIGN_CENTER);
      }
      else
      {
         ;/*Do nothing*/
      }
   }
   else
   {
      ; /*Do nothing*/
   }
}

/*
 * Function                : RedXNumber
 *
 * Description             : Draws RedX in numberbox place.
 *
 * Formal parameter(s)     : T_SDISREGION *ps_dis_region - IN Pointer to RedX region parameters.
 *                           T_SPOLY *ps_red_bar - IN Pointer to RedX polygon.
 *
 * Return Value            : None
 *
 * Assumption              : None
 *
 */
static void RedXNumber(T_SPOLY *ps_red_bar)
{

   /*hdudispfwidgets-RedXNumber-DB-LLR-001*/
   PolygonDrawPoly(ps_red_bar, RED);
}

/*
 * Function                : WidgetsRedX
 *
 * Description             : Displays RedX in Gauge and numberbox place.
 *
 * Formal parameter(s)     : T_SDISREGION *ps_dis_region - IN Pointer to RedX region parameters.
 *                           T_SPOLY **pps_poly_red_x- INOUT Pointer to RedX polygon.
 *
 * Return Value            : None
 *
 * Assumption              : None
 *
 */
void WidgetsRedX (T_SDISREGION *ps_dis_region, T_SPOLY **pps_poly_red_x)
{
   if(E_REGION_TYPE_GAUGE == ps_dis_region->eRegionType)
   {
      /* If the Red X poly has not been defined. */
      if((T_SPOLY*)ZERO == (*pps_poly_red_x))
      {


         /*hdudispfwidgets-WidgetsRedX-DB-LLR-001*/
        /* Updated as per PR100083*/
         *pps_poly_red_x =  PolygonsPsPolyInit(EREDXSHAPE
                            ,(T_FLOAT)(ps_dis_region->s32Width)
                            ,(T_INT16)((T_INT32)MAG(ps_dis_region->sDisLocCtr.u16X0) +
                                 (ps_dis_region->s32Width * ((T_INT32)TWO)))
                            ,(T_FLOAT)(ps_dis_region->s32Height)
                            ,MAG(ps_dis_region->sDisLocCtr.u16Y0)
                            ,ZERO
                            );
      }
      else
      {
         ;/*Do nothing*/
      }
      /*hdudispfwidgets-WidgetsRedX-DB-LLR-002*/
      RedXGauge(ps_dis_region, *pps_poly_red_x);
   }
   else if (E_REGION_TYPE_NUMBER == ps_dis_region->eRegionType)
   {
      /* If the Red X poly has not been defined. */
      if((T_SPOLY*)NULL == (*pps_poly_red_x))
      {
         /*hdudispfwidgets-WidgetsRedX-DB-LLR-003*/
         *pps_poly_red_x = PolygonsPsPolyInit(EREDXSHAPE
                           ,(T_FLOAT)(ps_dis_region->s32Width)
                           ,MAG(ps_dis_region->sDisLocCtr.u16X0 +
                               (ps_dis_region->s32Width))
                           ,SCALING_VAL_RED
                           ,MAG(ps_dis_region->sDisLocCtr.u16Y0)
                           ,ZERO
                           );
      }
      else
      {
         ;/*Do nothing*/
      }
      /*hdudispfwidgets-WidgetsRedX-DB-LLR-004*/
      RedXNumber(*pps_poly_red_x);
   }
   else
   {
      ;/*Do nothing*/
   }
}

/*
 * Function                : WidgetsRGB444ToRGB888
 *
 * Description             : Convert RGB444 to RGB888
 *
 * Formal parameter(s)     : T_EPENCOLOR e_pen_color - IN Input color to be converted.
 *
 * Return Value            : T_UINT32 - Output color
 *
 * Assumption              : None
 *
 */
T_UINT32 WidgetsRGB444ToRGB888(T_EPENCOLOR e_pen_color)
{
   T_UINT32 u32_color = 0;
   T_UINT32 u32_red = 0;
   T_UINT32 u32_green = 0;
   T_UINT32 u32_blue = 0;

   /*hdudispfwidgets-WidgetsRGB444ToRGB888-DB-LLR-001*/
   /* Convert RGB444 to RGB888 */
   u32_red = (e_pen_color & EXTRACT_9_11_BIT)>>EIGHT;
   u32_red |= u32_red<<FOUR;

   u32_green = (e_pen_color & EXTRACT_5_8_BIT)>>FOUR;
   u32_green |= u32_green<<FOUR;

   u32_blue = (e_pen_color & EXTRACT_1_4_BIT);
   u32_blue |= u32_blue<<FOUR;

   u32_color = EXTRACT_4_BYTE;
   u32_color |= u32_red<<SIXTEEN;
   u32_color |= u32_green<<EIGHT;
   u32_color |= u32_blue;

   return(u32_color);
}

/*
 * Function                : WidgetsDotAddr
 *
 * Description             : Return foreground buffer address.
 *
 * Formal parameter(s)     : T_SDISLOC *ptr_point - Pointer to the offset
 *
 * Return Value            : T_UINT32 - returns foreground buffer address
 *
 * Assumption              : None
 *
 */
T_UINT32 WidgetsDotAddr(T_SDISLOC *ptr_point)
{
   /*hdudispfwidgets-WidgetsDotAddr-DB-LLR-001*/
   return((T_UINT32)Vp_fgfb2
               +(T_UINT32)(ptr_point->u16Y0*S16_panel_width*DEC_TWO)
               +(T_UINT32)(ptr_point->u16X0 * (T_INT16)TWO)
               );
}

/*
 * Function                : WidgetsUpdateRT
 *
 * Description             : Calculates the polygon position based on updated input
 *
 * Formal parameter(s)     : T_PARAM_READING  *ps_param - IN Pointer to updated readings.
 *                           T_SWIDGETPARAM *ps_widget_parm - INOUT  Pointer to polygon
 *                           to be recalculated.
 *
 * Return Value            : None
 *
 * Assumption              : None
 *
 */
void WidgetsUpdateRT(T_PARAM_READING   *ps_param, T_SWIDGETPARAM *ps_widget_parm)
{
    /* Updated as per PR100083*/
   T_INT32 s32_scaler_step = ZERO;
   T_INT32 s32_temp = ZERO;

   /* If a new digital reading, re-calculate the step to next pointer position. */
   if(ps_widget_parm->s32Dig != ps_param->r)
   {
   /*hdudispfwidgets-WidgetsUpdateRT-DB-LLR-001*/
      ps_widget_parm->s32Dig = ps_param->r;
      s32_temp = ps_widget_parm->s32Dig - ps_widget_parm->s32Scaler;

      if(s32_temp!= ((T_INT32)ZERO))
      {
         s32_scaler_step =  (T_INT32)s32_temp;
         s32_scaler_step *= (T_INT32)(FRAME_MS);
         s32_scaler_step /= (T_INT32)(DIG_MS);

         if(((T_INT32)ZERO) == s32_scaler_step)
         {
            if(s32_temp > ((T_INT32)ZERO))
            {
               s32_scaler_step = ((T_INT32)ONE);
            }
            else
            {
               s32_scaler_step = MINUS_ONE;
            }
         }
         else
         {
            ;/*Do nothing*/
         }
         s32_temp = (T_INT32)s32_scaler_step;
      }
      else
      {
         ;/*Do nothing*/
      }
      ps_widget_parm->s32ScalerStep = s32_temp;
   }
   else
   {
      ;/*Do nothing*/
   }

   if(ps_widget_parm->s32ScalerStep > ((T_INT32)ZERO))
   {
      /*hdudispfwidgets-WidgetsUpdateRT-DB-LLR-002*/
      if((ps_widget_parm->s32Scaler + ps_widget_parm->s32ScalerStep) > ps_param->r)
      {
         ps_widget_parm->s32Scaler = ps_param->r;
         ps_widget_parm->s32ScalerStep = ((T_INT32)ZERO);
      }
      else
      {
         ;/*Do nothing*/
      }
   }
   else if (ps_widget_parm->s32ScalerStep < ((T_INT32)ZERO))
   {
      /*hdudispfwidgets-WidgetsUpdateRT-DB-LLR-003*/
      if((ps_widget_parm->s32Scaler + ps_widget_parm->s32ScalerStep) < ps_param->r)
      {
         ps_widget_parm->s32Scaler = ps_param->r;
         ps_widget_parm->s32ScalerStep = ((T_INT32)ZERO);
      }
      else
      {
         ;/*Do nothing*/
      }
   }
   else
   {
      ;/*Do nothing*/
   }
   /*hdudispfwidgets-WidgetsUpdateRT-DB-LLR-004*/
   ps_widget_parm->s32Scaler = (T_INT32)(ps_widget_parm->s32Scaler + ps_widget_parm->s32ScalerStep);

   if((U8_update_digital != ZERO) || (ps_widget_parm->eDIsDigStat != ps_param->stat))
   {
      /*hdudispfwidgets-WidgetsUpdateRT-DB-LLR-005*/
      ps_widget_parm->s32DisDig = ps_param->r;
      ps_widget_parm->eDIsDigStat = ps_param->stat;
   }
   else
   {
      ; /*Do nothing*/
   }
}

/*
 * Function                : WidgetsNumUpdate
 *
 * Description             : The function updates number box with the lastest inputs.
 *
 * Formal parameter(s)     : T_PARAM_READING *param - IN Pointer to updated readings
 *                           T_SWIDGETPARAM *ps_widget_param -IN Pointer to numberbox
 *                           to be updated
 *                           T_CHAR *ac_dig_text - IN Text to displayed
 *                           T_UINT16 u16_format - IN Format of Text to displayed
 *
 * Return Value            : None
 *
 * Assumption              : None
 *
 */
void WidgetsNumUpdate(T_PARAM_READING *param, T_SWIDGETPARAM *ps_widget_param,
          T_CHAR *ac_dig_text, T_UINT16 u16_format, T_EPENCOLOR e_pen_color)
{
    /* Updated as per PR100083*/
   T_INT32  s32_dis_num = ZERO;

   if (PARAM_WARNING == param->stat)
   {
      /*hdudispfwidgets-WidgetsNumUpdate-DB-LLR-001*/
      TextUpdate((T_PTEXT)ps_widget_param->pText, e_pen_color, TX_FLASH, V_REVERSE);
      s32_dis_num = ps_widget_param->s32DisDig;
   }
   else if(PARAM_CAUTION == param->stat)
   {
      /*hdudispfwidgets-WidgetsNumUpdate-DB-LLR-002*/
      TextUpdate((T_PTEXT)ps_widget_param->pText, e_pen_color, TX_NO_FLASH, V_REVERSE);
      s32_dis_num = ps_widget_param->s32DisDig;
   }
   else if(PARAM_ADVISORY == param->stat)
   {
         /*hdudispfwidgets-WidgetsNumUpdate-DB-LLR-005*/
      TextUpdate((T_PTEXT)ps_widget_param->pText, e_pen_color, TX_FLASH, V_NORMAL);
      s32_dis_num = ps_widget_param->s32DisDig;
   }
   else
   {
      /*hdudispfwidgets-WidgetsNumUpdate-DB-LLR-003*/
      TextUpdate((T_PTEXT)ps_widget_param->pText, e_pen_color, TX_NO_FLASH, V_NORMAL);
      s32_dis_num = ps_widget_param->s32DisDig;
   }
   /*hdudispfwidgets-WidgetsNumUpdate-DB-LLR-004*/
   BinasByteFormatInfoBE(&(s32_dis_num), u16_format,(T_INT8*) ac_dig_text);
}
