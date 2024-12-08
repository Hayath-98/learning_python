/*
 ******************************************************************************
 * License Information  :  Howell Instruments, Inc.                           *
 *                         "Licensed Software" and "All rights reserved".     *
 ******************************************************************************
 *  File                : hdudispfbargraphs.c
 *
 *  Description         : This file contains the routines which maintain the
 *                                  "Real Time" bar-graphs of the foreground display.
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
 *      1.1          Vinay H         18-Jul-2017             100064
 *      1.2          Shilpa A R      09-Oct-2017             100064
 *      1.3          Shruthi M N     15-Oct-2017             100083
 *      1.4          Shruthi M N     30-Oct-2017             100104
 *      1.5          Shruthi M N     07-Nov-2017             100161
 *      1.6          Rona B S  		 02-Jul-2020             100259
 *      1.7          Dhanalakshmi    12-Sep-2020             100276 
 *      1.8          Dhanalakshmi    09-Oct-2020             100288  
 *
 * Additional References : None
 *
 ******************************************************************************
 */

#include "hdudispfdma2d.h"  /* contains the common defines and functions prototypes for dma2d */
#include "hdudispfpolygon1.h"    /* implements the "scan line" method polygon fill */
#include "hdudispfrterror.h"      /*provides stub routine for run time errors.*/
#include "hdudispftext.h"          /*  Routines which maintain text display and updates */
#include "hdudispfbargraphs.h"  /* Routines which maintain the "Real Time" bar-graphs */
#include "hdudispfconfig.h"       /* contains page and color config information */
#include "hdudispfbinascii.h" /* contains Utility routines to convert binary to ascii base 10. */
#include "hdulibbasictypes.h"  /*provides basic data types.*/
#include "hdudispffonts.h"  /* Contains different font information */
#include "hdudispfpdidata.h" /* provides pdi declarations */

#define PIXEL_INC_A4_VER      0x44U
#define PIXEL_INC_A4_HOR      0x4U

/* Line used to anti alias the tip of the bar.*/
static T_UINT8 U8_aa_line[MAX_BAR_WIDTH] = {0};

/* Statically allocate pool of bar graphs.   */
static T_SBARGRAPH As_bar_graph[MAX_BARS] = {0};
static T_UINT16   U16_bar_graphs_installed = 0;

/*
 * Function                : BargraphAllocat
 *
 * Description             : The function allocate the bar graphs.
 *
 * Formal parameter(s)     : T_SBARGRAPHDEF *ps_bar_graph_def - INOUT Bar graph definition
 *
 * Return Value            : None
 *
 * Assumption              : None
 *
 */
void BargraphAllocat(T_SBARGRAPHDEF *ps_bar_graph_def)
{
   T_PSBARGRAPH   ps_bar_graph = {0};

 /* Updated as per PR100083*/
   T_UINT8 num_dec=0;
   T_INT32 reading=0;
   static T_CHAR param_message2[] = "Too many bar graphs.";
   T_CHAR file_name[] = __FILE__;

   /*hdudispfbargraphs-BargraphAllocat-DB-LLR-002*/
   /* Trap for over allocated.*/
   if(MAX_BARS == U16_bar_graphs_installed)
   {
      RterrWidget((T_CHAR *)&file_name,__LINE__, (T_CHAR *) &param_message2);
   }
   else
   {
      ; /*Do nothing*/
   }
   /*hdudispfbargraphs-BargraphAllocat-DB-LLR-001*/
   if(((T_ETXFONT)E_TINY_FONT != ps_bar_graph_def->eFont) &&
	  ((T_ETXFONT)E_SMALL_FONT != ps_bar_graph_def->eFont) &&
	  ((T_ETXFONT)E_NORMAL_FONT != ps_bar_graph_def->eFont) &&
	  ((T_ETXFONT)E_LARGE_FONT != ps_bar_graph_def->eFont) &&
	  ((T_ETXFONT)E_BEZEL_FONT != ps_bar_graph_def->eFont))
   {
	   ps_bar_graph_def->eFont = (T_ETXFONT)E_NO_FONT;
   }
   else
   {    
       ; /* Do nothing */
   }

   /*hdudispfbargraphs-BargraphAllocat-DB-LLR-003*/
   ps_bar_graph = &(As_bar_graph[U16_bar_graphs_installed]);

   /* Link owner and object.*/
   ps_bar_graph->ps_bar_graph_def = ps_bar_graph_def;
   ps_bar_graph_def->psbargraph = (T_PSBARGRAPH *)ps_bar_graph;

   /* Updated as per PR100083*/
   num_dec = (ps_bar_graph->ps_bar_graph_def->u16Format>>FOUR & SEVEN);
   /*Updated as per PR100161*/
   reading = (T_INT32)( ( (ps_bar_graph_def->psParam->fread * (T_FLOAT)ONE_HUNDRED
                * (T_FLOAT)CalculatePower((T_FLOAT)TEN, (T_INT32)num_dec) ) + 
                (T_FLOAT)FIVE) / (T_FLOAT)TEN);


   /* Initialize the digital reading.*/
   ps_bar_graph->sWidgetParm.s32DisDig = reading;
   ps_bar_graph->sWidgetParm.s32Dig = reading;
   /* Initialize the scaler reading.*/
   ps_bar_graph->sWidgetParm.s32Scaler = reading;
   ps_bar_graph->sWidgetParm.s32ScalerStep = 0;
   ps_bar_graph->sWidgetParm.pText = (T_PTEXT *)ZERO;
   /*hdudispfbargraphs-BargraphAllocat-DB-LLR-006*/
   /* Inc Bar Graphs installed.*/
   U16_bar_graphs_installed = (T_UINT16) (U16_bar_graphs_installed + ONE);
}

/*
 * Function                : BargraphUpdate
 *
 * Description             : The function update all installed bargraphs
 *
 * Formal parameter(s)     : None
 *
 * Return Value            : None
 *
 * Assumption              : None
 *
 */
void BargraphUpdate(void)
{
   T_UINT16          u16_bar_cntr = 0;
   T_PARAM_STAT      e_temp_stat = PARAM_OK;
   T_PSBARGRAPH      ps_bar_graph = {0};
   T_UINT16          u16_field_width = 0;
    /* Updated as per PR100083*/
   T_UINT8 num_dec=0;

   /*hdudispfbargraphs-BargraphUpdate-DB-LLR-001*/
   /* Update readings used for digital and analog updates.*/
   for (u16_bar_cntr=0; u16_bar_cntr<U16_bar_graphs_installed; u16_bar_cntr++)
   {
      ps_bar_graph = &As_bar_graph[u16_bar_cntr];
      /* Updated as per PR100083*/
      num_dec = (ps_bar_graph->ps_bar_graph_def->u16Format>>FOUR & SEVEN);
      /*Updated as per PR100161*/
      ps_bar_graph->ps_bar_graph_def->psParam->r = (T_INT32)(
            ((ps_bar_graph->ps_bar_graph_def->psParam->
                  fread*(T_FLOAT)ONE_HUNDRED*(T_FLOAT)CalculatePower((T_FLOAT)TEN,
                  (T_INT32)num_dec))+(T_FLOAT)FIVE)/(T_FLOAT)TEN);
      WidgetsUpdateRT(ps_bar_graph->ps_bar_graph_def->psParam,  &(ps_bar_graph->sWidgetParm));
   }

   /*hdudispfbargraphs-BargraphUpdate-DB-LLR-002*/
   /* Update the length of each bar graph.*/
   for (u16_bar_cntr=0; u16_bar_cntr<U16_bar_graphs_installed; u16_bar_cntr++)
   {
      /* Update the length of each bargraph.*/
      /* Updated as per PR100083*/
      ps_bar_graph = &As_bar_graph[u16_bar_cntr];
      ps_bar_graph->sLength = LookupTableLookup(ps_bar_graph->ps_bar_graph_def->psGeometry,
            ps_bar_graph->sWidgetParm.s32Scaler, &e_temp_stat);

      if(ps_bar_graph->ps_bar_graph_def->psParam->stat < PARAM_BAD)
      {
         if(NULL != ps_bar_graph->sWidgetParm.pText)
         {
         /*hdudispfbargraphs-BargraphUpdate-DB-LLR-003*/
            WidgetsNumUpdate
            (ps_bar_graph->ps_bar_graph_def->psParam
               ,&(ps_bar_graph->sWidgetParm)
               ,(T_CHAR *) ps_bar_graph->acDigText
               ,ps_bar_graph->ps_bar_graph_def->u16Format, ps_bar_graph->ps_bar_graph_def->ePenColor
            );
         }
         else
         {
            ; /*Do nothing*/
         }
      }
      else
      {
            if(NULL  != ps_bar_graph->sWidgetParm.pText)
            {
               /*hdudispfbargraphs-BargraphUpdate-DB-LLR-004*/
               /* Replace all characters with a red x */
               u16_field_width = BinasGetWidth (ps_bar_graph->ps_bar_graph_def->u16Format);
               ps_bar_graph->acDigText[u16_field_width] = ZERO;
               while(u16_field_width)
               {
                  /*hdudispfbargraphs-BargraphUpdate-DB-LLR-005*/
                  ps_bar_graph->acDigText[u16_field_width-1] = RED_X;
                  u16_field_width = (T_UINT16)(u16_field_width -ONE);
               }
               /*hdudispfbargraphs-BargraphUpdate-DB-LLR-006*/
               TextUpdate((T_PTEXT)ps_bar_graph->sWidgetParm.pText,LIGHT_RED,
                                 TX_NO_FLASH, V_NORMAL);
            }
            else
            {
               ; /*Do nothing*/
            }
         }
      }
}

/*
 * Function                : BargraphDraw
 *
 * Description             : The function Draw the bargraph.
 *
 * Formal parameter(s)     : None
 *
 * Return Value            : None
 *
 * Assumption              : None
 *
 */
void BargraphDraw(void)
{
   T_UINT16          u16_bar_ctr = 0;              /*Iterator.*/
   T_PSBARGRAPH      ps_bar_graph  = {0};          /*Bargraph definition.*/
   T_SBARGRAPHDEF *ps_bar_graph_def = (void *)0;   /*Bargraph runtime.*/
    /* Updated as per PR100083*/
   T_INT32     s32_length = 0;        /* Length of the bar.*/
   T_SDISLOC   origin = {0,0};        /* Origin of the bar.*/
   T_EBGHV     bg_hv = BG_VERTICAL;   /* Is this horizontal or vertical?*/

   T_SDISLOC   ul_cor = {0,0};        /* Upper Left corner.*/
   T_UINT32    u32_corner_address = 0;/* Memory address of the upper left corner.*/
   T_UINT8     u8aaval = 0;           /* Anti Alias value for bar end.*/
   T_INT16     s16temp = 0;           /* Temporary variable.*/

   for(u16_bar_ctr=0, ps_bar_graph = As_bar_graph; u16_bar_ctr<U16_bar_graphs_installed;
                                          u16_bar_ctr++, ps_bar_graph++)
   {
     /*hdudispfbargraphs-BargraphDraw-DB-LLR-001*/
      ps_bar_graph_def = ps_bar_graph->ps_bar_graph_def;

      if(ps_bar_graph_def->psParam->stat < PARAM_BAD)
      {
         while(ZERO != Dma2dIsBusy())
         {
            ;
         }

         s32_length = ps_bar_graph->sLength;
         origin =   ps_bar_graph_def->sOrigin;
         bg_hv =     ps_bar_graph_def->eBGHV;

         if (E_PORTRAIT == E_orientation)
         {
         /*hdudispfbargraphs-BargraphDraw-DB-LLR-002*/
            s16temp=origin.u16X0;
            origin.u16X0 = origin.u16Y0;
            origin.u16Y0=(T_INT16) (S16_panel_height-s16temp);

            if(BG_HORIZONTAL == bg_hv)
            {
                bg_hv = BG_VERTICAL;
                s32_length = (T_INT32) (-(s32_length));
            }
            else
            {
                bg_hv = BG_HORIZONTAL;
            }
         }
         else
         {
            ; /*Do nothing*/
         }

         if(BG_VERTICAL == bg_hv)
         {
         /*hdudispfbargraphs-BargraphDraw-DB-LLR-003*/
            /* Step in 1/4 pix increments in A4 format.*/
            u8aaval = (T_UINT8)((ABS(s32_length)%(T_INT32)FOUR) * (T_INT32)PIXEL_INC_A4_VER);
            for(s16temp = ZERO; s16temp < (T_INT16)((ps_bar_graph_def->u16Width)/((T_INT16)TWO));
                                                                            s16temp++)
            {
               U8_aa_line[s16temp] = u8aaval;
            }

            ul_cor.u16X0 = (T_INT16)(origin.u16X0 - (T_INT16)(ps_bar_graph_def->u16Width/TWO));
            if(s32_length < ((T_INT32)ZERO))
            {
               ul_cor.u16Y0 = (T_INT16)(origin.u16Y0 + (s32_length/((T_INT16)FOUR)));
               PolygonFillRectNT((T_INT16)ul_cor.u16X0, (T_INT16)ul_cor.u16Y0,
                                       (T_INT16)ps_bar_graph_def->u16Width,
                       (T_INT16)((-(s32_length))/((T_INT16)FOUR)), ps_bar_graph_def->ePenColor);

               if(ZERO != u8aaval)
               {
                  ul_cor.u16Y0 = (T_INT16)(ul_cor.u16Y0 - (T_INT16)ONE);
                  u32_corner_address = WidgetsDotAddr(&ul_cor);
                  Dma2dDrawChar(U8_aa_line, (void *)u32_corner_address,
                        ps_bar_graph_def->u16Width, ONE, ps_bar_graph_def->ePenColor);
               }
               else
               {
                  ; /*Do nothing*/
               }
            }
            else if(s32_length > ((T_INT32)ZERO))
            {
            /*hdudispfbargraphs-BargraphDraw-DB-LLR-004*/
               ul_cor.u16Y0 = origin.u16Y0;
               PolygonFillRectNT((T_INT16)ul_cor.u16X0, (T_INT16)ul_cor.u16Y0,
               (T_INT16)ps_bar_graph_def->u16Width,(T_INT16)((s32_length)/((T_INT16)FOUR)),
                                                   ps_bar_graph_def->ePenColor);

               if(ZERO != u8aaval)
               {
                  /* Switch to lower left.*/
                  ul_cor.u16Y0 = (T_INT16)(origin.u16Y0 + (T_INT16)(s32_length/((T_INT32)FOUR)));
                  u32_corner_address = WidgetsDotAddr(&ul_cor);
                  Dma2dDrawChar(U8_aa_line,(void *)u32_corner_address,
                             ps_bar_graph_def->u16Width,ONE, ps_bar_graph_def->ePenColor);
               }
               else
               {
                     ; /*Do nothing*/
               }
            }
            else
            {
                  ; /*Do nothing*/
            }
         }

         /* Horizontal Bar Graph.*/
         else
         {
         /*hdudispfbargraphs-BargraphDraw-DB-LLR-005*/
            /* Step in 1/4 pix increments in A4 format.*/
            u8aaval = (T_UINT8) ((ABS(s32_length)%(T_INT32)FOUR) * (T_INT32)PIXEL_INC_A4_HOR);
            for(s16temp = ZERO; s16temp < (T_INT16)((ps_bar_graph_def->u16Width)); s16temp++)
            {
               U8_aa_line[s16temp] = u8aaval;
            }

            ul_cor.u16Y0 = (T_INT16)(origin.u16Y0 -
                            (T_INT16)(ps_bar_graph_def->u16Width/(T_UINT16)TWO));
            if(s32_length < ((T_INT32) ZERO) )
            {
               ul_cor.u16X0 = (T_INT16)(origin.u16X0 + (T_INT16)(s32_length/((T_INT32)FOUR)));
               PolygonFillRectNT((T_INT16)ul_cor.u16X0, (T_INT16)ul_cor.u16Y0,
                 (T_INT16)((-(s32_length))/((T_INT16)FOUR)), (T_INT16)ps_bar_graph_def->u16Width,
                                                            ps_bar_graph_def->ePenColor);

               if(ZERO != u8aaval)
               {
                  ul_cor.u16X0 = (T_INT16)(ul_cor.u16X0 - (T_INT16)ONE);
                  u32_corner_address = WidgetsDotAddr(&ul_cor);
                  Dma2dDrawChar(U8_aa_line, (void *)u32_corner_address, TWO,
                               ps_bar_graph_def->u16Width, ps_bar_graph_def->ePenColor);
               }
               else
               {
                     ; /*Do nothing*/
               }
            }
            else if(s32_length > ((T_INT32)ZERO))
            {
            /*hdudispfbargraphs-BargraphDraw-DB-LLR-006*/
               ul_cor.u16X0 = origin.u16X0;
               PolygonFillRectNT((T_INT16)ul_cor.u16X0, (T_INT16)ul_cor.u16Y0,
                  (T_INT16)((s32_length)/((T_INT16)FOUR)), (T_INT16)ps_bar_graph_def->u16Width,
                                                      ps_bar_graph_def->ePenColor);

               if(ZERO != u8aaval)
               {
                  /* Switch to lower left. */
                  ul_cor.u16X0 = (T_INT16)(origin.u16X0 + (T_INT16)(s32_length/((T_INT32)FOUR)));
                  u32_corner_address = WidgetsDotAddr(&ul_cor);
                  Dma2dDrawChar(U8_aa_line, (void *)u32_corner_address, TWO,
                                    ps_bar_graph_def->u16Width, ps_bar_graph_def->ePenColor);
               }
               else
               {
                     ; /*Do nothing*/
               }
            }
            else
            {
                  ; /*Do nothing*/
            }
         }
      }
      else
      {
       /*hdudispfbargraphs-BargraphDraw-DB-LLR-007*/
         if((ZERO != ps_bar_graph_def->psDisRegion))
         {
            WidgetsRedX (ps_bar_graph_def->psDisRegion, &(ps_bar_graph->psPolyRedX));
         }
         else
         {
               ; /*Do nothing*/
         }
      }
   }
}

/*
 * Function                : BargraphClear
 *
 * Description             : The function De-allocate the bar graphs.
 *
 * Formal parameter(s)     : None
 *
 * Return Value            : None
 *
 * Assumption              : None
 *
 */
void BargraphClear(void)
{
   /*hdudispfbargraphs-BargraphClear-DB-LLR-001*/
   while(U16_bar_graphs_installed)
   {
      As_bar_graph[U16_bar_graphs_installed - ONE].psPolyRedX = (T_SPOLY *)ZERO;
      U16_bar_graphs_installed = (T_UINT16)(U16_bar_graphs_installed - ONE);
   }
}
