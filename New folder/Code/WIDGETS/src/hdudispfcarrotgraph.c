/*
 ******************************************************************************
 * License Information  :  Howell Instruments, Inc.                           *
 *                         "Licensed Software" and "All rights reserved".     *
 ******************************************************************************
 *  File                : hdudispfcarrotgraph.c
 *
 *  Description         : The file contains routines to draw and update the carrot graphs
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
 *  Author(s)           : Gururaj C
 *
 *  Version History     :
 * <Version No.>     <Author>          <Date>         <Problem Report No.>
 *
 *      1.1          Gururaj C       21-Jun-2020             100259
 *      1.2          Rona B S        02-Jul-2020             100259
 *      1.3          Dhanalakshmi    12-Sep-2020             100276 
 *
 * Additional References : None
 *
 ******************************************************************************
 */

#include "hdudispffonts.h"        /*Contains different font configuration information*/
#include "hdudispfpolygon1.h"      /*implements the "scan line" method polygon fill.*/
#include "hdudispfrterror.h"        /* Provides stub routine for run time errors.*/
#include "hdudispftext.h"         /*  Routines which maintain text display and updates */
#include "hdudispfcarrotgraph.h"    /* routines which draws and updates the carrot graph */
#include "hdudispfbinascii.h"   /*Utility routines to convert binary to ascii base 10.*/
#include "hdudispfpdidata.h" /* provides pdi declarations */

/* Statically allocate pool of carrot graphs.  */
static T_SCARROTGRAPH A_carrot_graph[MAX_CARROT_GRAPH] = {0};
static T_UINT16   U16_carrot_graphs_installed = 0;
#define ASSC_LABEL_INDX 5U
#define THOUSAND     1000U
/*
 * Function                : CarrotGraphAllocat
 *
 * Description             : Allocate a single carrot graph.
 *
 * Formal parameter(s)     : T_CARROTGRAPHDEF *carrot_graph_def - OUT carrot graph definition.
 *
 * Return Value            : None
 *
 * Assumption              : None
 *
 */
void CarrotGraphAllocat(T_CARROTGRAPHDEF *carrot_graph_def)
{
   T_SPTRSPEC  *ps_ptr_src = {0};
   T_SPTRSPEC  *ps_ptr_dest = {0};
   T_PARAM_STAT   e_temp_stat = PARAM_OK;
    /* Updated as per PR100083*/
   T_UINT8 u8_i=0;
   T_UINT8 num_dec=0;
   T_INT32 reading=0;
   T_PCARROTGRAPH carrot_graph = &(A_carrot_graph[U16_carrot_graphs_installed]);

   static T_CHAR param_message[] = "Too many carrot graphs.";
   T_CHAR file_name[] = __FILE__;

   /* Check for over allocated. */
   if(MAX_CARROT_GRAPH < Cg_cnt)
   {
     /*hdudispfcarrotgraph-CarrotGraphAllocat-DB-LLR-001*/
      RterrWidget((T_CHAR *)&file_name,__LINE__, (T_CHAR *) &param_message);
      carrot_graph_def->pCarrotGraph = (T_PCARROTGRAPH)ZERO;
      return;
   }
   else
   {
     /*hdudispfcarrotgraph-CarrotGraphAllocat-DB-LLR-002*/
      /* Link the owner to object. */
      carrot_graph_def->pCarrotGraph = carrot_graph;
   }
   if(((T_ETXFONT)E_TINY_FONT != carrot_graph_def->eFont) &&
	  ((T_ETXFONT)E_SMALL_FONT != carrot_graph_def->eFont) &&
	  ((T_ETXFONT)E_NORMAL_FONT != carrot_graph_def->eFont) &&
	  ((T_ETXFONT)E_LARGE_FONT != carrot_graph_def->eFont) &&
	  ((T_ETXFONT)E_BEZEL_FONT != carrot_graph_def->eFont))
   {
	   carrot_graph_def->eFont = (T_ETXFONT)E_NO_FONT;
   }
   else
   {    
       ; /* Do nothing */
   }
   /*hdudispfcarrotgraph-CarrotGraphAllocat-DB-LLR-003*/
   /* Link object to owner. */
   carrot_graph->carrot_graph_def = carrot_graph_def;
   /* Red X not yet defined. */
   carrot_graph->psPolyRedX = (T_SPOLY *)ZERO;

    /* Updated as per PR100083*/
   num_dec = (carrot_graph->carrot_graph_def->u16Format>>FOUR & SEVEN);
   reading = (T_INT32)(((carrot_graph_def->psParam->fread*THOUSAND*
                  (T_FLOAT)CalculatePower((T_FLOAT)TEN,(T_INT32)num_dec))+FIVE)/TEN);
   /* Initialize the digital reading. */
   carrot_graph->sWidgetParm.s32DisDig = reading;
   carrot_graph->sWidgetParm.s32Dig = reading;
   /* Initialize the scaler reading. */
   carrot_graph->sWidgetParm.s32Scaler = reading;
   carrot_graph->sWidgetParm.s32ScalerStep = ZERO;

   /* Install all pointers. */
   ps_ptr_src = carrot_graph_def->asPtrSpec;
   ps_ptr_dest = carrot_graph->asPtrSpec;

   /* Make a copy of all pointers used. */
   while(ps_ptr_src->s32PtrShape)
   {
     /*hdudispfcarrotgraph-CarrotGraphAllocat-DB-LLR-004*/
      ps_ptr_src->psShape = PolygonsPsPolyInit(ps_ptr_src->s32PtrShape,
      carrot_graph_def->ptr_scale[u8_i].u16X0,
      MAG(carrot_graph_def->ptr_scale_offset[u8_i].u16X0),
	  carrot_graph_def->ptr_scale[u8_i].u16Y0,
      MAG(carrot_graph_def->ptr_scale_offset[u8_i].u16Y0),\
	  (T_INT16)carrot_graph_def->rotAngle[u8_i]);
      ps_ptr_dest->psShape = PolygonsPsDuplicate(ps_ptr_src->psShape);
      ps_ptr_dest->ePenColor = ps_ptr_src->ePenColor;
      ps_ptr_src++;
      ps_ptr_dest++;
      u8_i++;
   }
   /*hdudispfcarrotgraph-CarrotGraphAllocat-DB-LLR-005*/
    /* Updated as per PR100083*/
   carrot_graph->sOffSet = LookupTableLookup(carrot_graph_def->psGeometry,
                        carrot_graph->sWidgetParm.s32Scaler, &e_temp_stat);

   /* Delimit the pointer handle array. */
   ps_ptr_dest->psShape = (T_SPOLY *)ZERO;

   /* If the digital display has a width and the font is defined. */
   if(BinasGetWidth(carrot_graph_def->u16Format)&&(carrot_graph_def->eFont))
   {
        /*hdudispfcarrotgraph-CarrotGraphAllocat-DB-LLR-006*/
         /* Initialize the ascii reading. */
        /* Updated as per PR100083*/
         BinasByteFormatInfoBE (&(carrot_graph->sWidgetParm.s32DisDig), carrot_graph_def->u16Format,
                               (T_INT8*) carrot_graph->acDigText);

         /* Initialize the digital display. */
         TextAllocat( (T_PTEXT *) &(carrot_graph->sWidgetParm.pText),
               (T_UINT8 *) carrot_graph->acDigText,
               (T_UINT16)((carrot_graph_def->sDigCenterOffset.u16X0
               +carrot_graph_def->sUpperLeft.u16X0)/(T_UINT8)MAG_FACTOR),
               (T_UINT16)((carrot_graph_def->sDigCenterOffset.u16Y0
               +carrot_graph_def->sUpperLeft.u16Y0)/(T_UINT8)MAG_FACTOR),
               ALIGN_CENTER,
               carrot_graph_def->eFont,
               WHITE,
               V_NORMAL,
               TX_NO_FLASH
               );
   }
   /* If no digital display. */
   else
   {
     /*hdudispfcarrotgraph-CarrotGraphAllocat-DB-LLR-007*/
      carrot_graph->sWidgetParm.pText = (T_PTEXT *)ZERO;
   }
   /*hdudispfcarrotgraph-CarrotGraphAllocat-DB-LLR-008*/
   /* Inc carrot graphs installed. */
   U16_carrot_graphs_installed = (T_UINT16)(U16_carrot_graphs_installed + ONE);
}

/*
 *
 * Function                : CarrotGraphUpdate
 *
 * Description             : Update all installed carrot graphs
 *
 * Formal parameter(s)     : None
 *
 * Return Value            : None
 *
 * Assumption              : None
 *
 */
void CarrotGraphUpdate(void)
{
   T_UINT16 u16_carrot_graph_cntr = 0;
   T_SPTRSPEC  *ps_ptr_src = {0};
   T_PARAM_STAT   e_temp_stat = PARAM_OK;
   T_SCARROTGRAPH *ps_carrot_graph = {0};
   /* Updated as per PR100083*/
   T_UINT16 u16_field_width = 0;
   T_UINT16    num_dec=0;
   T_SRECTPOINT   s_rect_point = {0};

   /* Update readings used for digital and analog updates. */
   for (u16_carrot_graph_cntr=ZERO; u16_carrot_graph_cntr<U16_carrot_graphs_installed;
                                                             u16_carrot_graph_cntr++)
   {
     /*hdudispfcarrotgraph-CarrotGraphUpdate-DB-LLR-001*/
      ps_carrot_graph = &A_carrot_graph[u16_carrot_graph_cntr];
      /* Updated as per PR100083*/
      num_dec = (ps_carrot_graph->carrot_graph_def->u16Format>>FOUR & SEVEN);
      ps_carrot_graph->carrot_graph_def->psParam->r =
           (T_INT32)(((ps_carrot_graph->carrot_graph_def->psParam->fread*
        THOUSAND* (T_FLOAT)CalculatePower((T_FLOAT)TEN,(T_INT32)num_dec))+FIVE)/TEN);
      WidgetsUpdateRT(ps_carrot_graph->carrot_graph_def->psParam,
    		  &(ps_carrot_graph->sWidgetParm));
   }


   for (u16_carrot_graph_cntr=ZERO; u16_carrot_graph_cntr<U16_carrot_graphs_installed;
                                                                u16_carrot_graph_cntr++)
   {
     /*hdudispfcarrotgraph-CarrotGraphUpdate-DB-LLR-002*/
            ps_carrot_graph = &A_carrot_graph[u16_carrot_graph_cntr];

       /* Updated as per PR100083*/
      ps_carrot_graph->sOffSet = LookupTableLookup(ps_carrot_graph->carrot_graph_def->psGeometry,
                              ps_carrot_graph->sWidgetParm.s32Scaler, &e_temp_stat);

      if(ps_carrot_graph->carrot_graph_def->psParam->stat < PARAM_BAD)
      {
         /* If the dial has a digital display. */
         if(ps_carrot_graph->sWidgetParm.pText != ZERO)
         {
         /*hdudispfcarrotgraph-CarrotGraphUpdate-DB-LLR-003*/
            WidgetsNumUpdate(ps_carrot_graph->carrot_graph_def->psParam,
               &(ps_carrot_graph->sWidgetParm),
               ps_carrot_graph->acDigText,
               ps_carrot_graph->carrot_graph_def->u16Format, 0);
         }
         else
         {
            ;/*Do nothing*/
         }

            /* Update all pointers of this carrot graph. */
         for(ps_ptr_src = ps_carrot_graph->asPtrSpec; ps_ptr_src->psShape != (T_SPOLY *)ZERO;
                                 ps_ptr_src++)
         {
         /*hdudispfcarrotgraph-CarrotGraphUpdate-DB-LLR-004*/

            s_rect_point.s32X = (T_INT32)ps_carrot_graph->carrot_graph_def->sUpperLeft.u16X0
                        +  (T_INT32)ps_carrot_graph->carrot_graph_def->sDialCenterOffset.u16X0;

            s_rect_point.s32Y = (T_INT32)ps_carrot_graph->carrot_graph_def->sUpperLeft.u16Y0
                        +  (T_INT32)ps_carrot_graph->carrot_graph_def->sDialCenterOffset.u16Y0;

            if (CG_VERTICAL == ps_carrot_graph->carrot_graph_def->eCGHV)
            {
                s_rect_point.s32Y += ps_carrot_graph->sOffSet;
            }
            else
            {
                s_rect_point.s32X += ps_carrot_graph->sOffSet;
            }

            PolygonsvPolarToRect(ps_ptr_src->psShape,
                                             s_rect_point.s32X,
                                             s_rect_point.s32Y,
                                             ZERO,
                                             ZERO,
                                             ZERO,
                                             FALSE
                                             );
         }
      }
      /* If parameter is invalid. */
      else
      {
       /*hdudispfcarrotgraph-CarrotGraphUpdate-DB-LLR-005*/
         /* If a digital display is present. */
         if((T_PTEXT *)NULL != ps_carrot_graph->sWidgetParm.pText)
         {
            /* Replace all characters with a red x */
            u16_field_width = BinasGetWidth (ps_carrot_graph->carrot_graph_def->u16Format);
            ps_carrot_graph->acDigText[u16_field_width] = ZERO;
            while(u16_field_width)
            {
               ps_carrot_graph->acDigText[u16_field_width-ONE] = RED_X;
               u16_field_width=(T_UINT16)(u16_field_width -ONE);
            }
            TextUpdate((T_PTEXT) ps_carrot_graph->sWidgetParm.pText,LIGHT_RED,
                      TX_NO_FLASH,V_NORMAL);
         }
         else
         {
            ;/*Do nothing*/
         }
      }
   }
}

/*
 *
 * Function                : CarrotGraphDraw
 *
 * Description             : The function Draws the Carrot Graphs
 *
 * Formal parameter(s)     : None
 *
 * Return Value            : None
 *
 * Assumption              : None
 *
 */
void CarrotGraphDraw(void)
{
   T_UINT16 u16_carrot_graph_cntr = 0;
   T_UINT16 u16_carrot_x_cntr = 0;
   T_SCARROTGRAPH *ps_carrot_graph = {0};
   T_SPTRSPEC  *ptr_spec = {0};
    /* Updated as per PR100083*/
   static T_BOOL carrot_graph_sw_x[30] = {FALSE};
   T_BOOL draw_dial = TRUE;
   T_UINT8 assc_indx=0;
   for (u16_carrot_graph_cntr=ZERO; u16_carrot_graph_cntr<U16_carrot_graphs_installed;
                         u16_carrot_graph_cntr++)
   {
     /*hdudispfcarrotgraph-CarrotGraphDraw-DB-LLR-001*/
      ps_carrot_graph = &A_carrot_graph[u16_carrot_graph_cntr];
      /* Updated as per PR100083*/
      draw_dial = TRUE;
      /* If the driving parameter is invalid, RedX the region. */
      if(ps_carrot_graph->carrot_graph_def->psParam->stat >= PARAM_BAD)
      /* Updated as per PR100083*/
      {
         for(assc_indx=0;assc_indx<ASSC_LABEL_INDX;assc_indx++)
         {
            if(ps_carrot_graph->carrot_graph_def->associated_labels[assc_indx]!=0)
            {
               for(u16_carrot_x_cntr = 0; u16_carrot_x_cntr<U16_carrot_graphs_installed;
                   u16_carrot_x_cntr++)
                  {
                     if((ps_carrot_graph->carrot_graph_def->associated_labels[assc_indx]
                           == A_carrot_graph[u16_carrot_x_cntr].carrot_graph_def->label)
                           &&(!carrot_graph_sw_x[u16_carrot_x_cntr] ))
                     {
                        if(A_carrot_graph[u16_carrot_x_cntr].
                           carrot_graph_def->psParam->stat<PARAM_BAD)
                        {
                           draw_dial = FALSE;
                        }
                        break;
                     }
					 else
                     {
					     ; /*Do nothing*/
                     }
                  }

            }
            else
            {
               break;
            }
         }

         if((T_SDISREGION *)NULL != ps_carrot_graph->carrot_graph_def->psDisRegion
             && TRUE == draw_dial)
         {
         /*hdudispfcarrotgraph-CarrotGraphDraw-DB-LLR-002*/
            WidgetsRedX(ps_carrot_graph->carrot_graph_def->psDisRegion,
                        &(ps_carrot_graph->psPolyRedX ));
          /* Updated as per PR100083*/
            carrot_graph_sw_x[u16_carrot_graph_cntr] = TRUE;
         }
         else
         {
            ;/*Do nothing*/
         }
      }
      /* Else draw the pointer(s). */
      else
      {
       /* Updated as per PR100083*/
         carrot_graph_sw_x[u16_carrot_graph_cntr] = FALSE;

       /*hdudispfcarrotgraph-CarrotGraphDraw-DB-LLR-003*/
         ptr_spec = ps_carrot_graph->asPtrSpec;
         while(ptr_spec->psShape)
         {
            PolygonDrawPoly(ptr_spec->psShape, ptr_spec->ePenColor);
            ptr_spec++;
         }
      }
   }
}

/*
 *
 * Function                : CarrotGraphClear
 *
 * Description             : De-allocate Carrot Graphs.
 *
 * Formal parameter(s)     : None
 *
 * Return Value            : None
 *
 * Assumption              : None
 *
 */
void CarrotGraphClear(void)
{
   /*hdudispfcarrotgraph-CarrotGraphClear-DB-LLR-001*/
   while(U16_carrot_graphs_installed)
   {
      A_carrot_graph[U16_carrot_graphs_installed - ONE].psPolyRedX = (T_SPOLY *)ZERO;
      U16_carrot_graphs_installed = (T_UINT16)(U16_carrot_graphs_installed - ONE);
   }
}
