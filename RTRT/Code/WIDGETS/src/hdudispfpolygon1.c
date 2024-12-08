/*
 ******************************************************************************
 * License Information  :  Howell Instruments, Inc.                           *
 *                         "Licensed Software" and "All rights reserved".     *
 ******************************************************************************
 *  File                : hdudispfpolygon1.c
 *
 *  Description         : This file implements the "scan line" method polygon fill.
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
 *      1.5          Rona B.S        04-Nov-2017             100156
 *      1.6          Rona B S        02-Jul-2020             100259
 *      1.7          Rona B S        28-Sep-2020             100284 
 *
 * Additional References : None
 *
 ******************************************************************************
 */

#include "hdudispfdma2d.h"  /* contains the common defines and functions prototypes for dma2d */
#include "hdudispfpolygon1.h"    /*provides routines for "scan line" method polygon fill.*/
#include "hdudispfrterror.h"      /*provides stub routine for run time errors.*/
#include "hdudispftext.h"       /*  Routines which maintain text display and updates */
#include "hdudispfconfig.h"     /* contains page and color config information */
#include "hdudispfwidgets.h"    /* Contains routines for widget params */
#include "hdulibbasictypes.h" /*provides basic data types.*/
#include "hdudispfpanel.h"   /* Contains functions prototypes of panel.*/

#define MAX_EDGES       MAX_PP

static T_EPENCOLOR E_pen_color = BLACK;

/* VERTICES LIST ROUTINES.*/
#define MAX_VERTICES    50U
#define SLOPE_VAL     65536


static T_VERTEX S_origin = {0};

/*  Heap data for vertex allocation.*/

static T_INT16 S16_next_vert = 0;
static T_VERTEX S_vert_pool[MAX_VERTICES*2] = {0};

 /* SCAN LINE ROUTINES. */

/*----------   Declarations for the "Active Edge" list   --------------*/
T_UINT8  U8_which_mag_line = 0;
T_UINT8  U8_mag_line1[(MAX_PANEL_WIDTH+1)] = {0};
T_UINT8  U8_mag_line2[(MAX_PANEL_WIDTH+1)] = {0};

T_INT32 S16_scan_xmin = 1;
T_INT32 S16_scan_xmax = 0;

/* Edge heap storage.                        */
static T_EDGE   S_edge_pool[MAX_EDGES] = {0};
/* Number edges allocated.                */
static T_INT16 S16_next_edge = 0;
/* Number of edges presently in the active edge list. */
static T_INT16 S16_active_edges = 0;
static T_EDGE S_active_edge_list = {0};

/*Static functions*/
static void VFreeVertList(void);
static T_VERTEX *PsAllocVert(void);
static T_VERTEX *SpFindLine(T_INT16 s16_scan_line);
static void VInsertVert(T_SRECTPOINT *ps_prev_p, T_SRECTPOINT *ps_vert_p,
                                          T_SRECTPOINT *ps_next_p);
static void VFreeEdgeList(void);
static void VBuildVertList(T_SRECTPOINT *points_frst, T_UINT16 point_count);
static T_EDGE *PsAllocEdge(void);
static void VEdgeInsert(T_EDGE *ps_this);
static void VEdgeInit(T_EDGE *ps_edge, T_SRECTPOINT *ps_first_p, T_SRECTPOINT *ps_secnd_p);
static void VAddEdges(T_VERTEX *ps_vert);
static void VProcessMagLine(T_INT16 s16_scan_y);
static void VProcessPairsHR(T_INT16 s16_scan_y);
static void VRemoveEdges(void);
static void VCalculateIntersections(T_INT16 s16_scan_y);
static void VScanLines(void);
static void PolygonFillRectTranslate(T_INT16 s16_ulx, T_INT16 s16_uly, T_INT16 s16_width,
                       T_INT16 s16_height,T_EPENCOLOR e_color, T_UINT8  u8_translate);

/*
 *
 * Function                : VFreeVertList
 *
 * Description             : Free all vertex storage.
 *
 * Formal parameter(s)     : None
 *
 * Return Value            : None
 *
 * Assumption              : None
 *
 */
static void VFreeVertList(void)
{
   /*hdudispfpolygon1-VFreeVertList-DB-LLR-001*/
   /* Free  the vertices storage.         */
   S_origin.psPrevL = (T_VERTEX *)ZERO;
   S_origin.psNextL = (T_VERTEX *)ZERO;
   S16_next_vert = ((T_INT16)ZERO);
}

/*
 *
 * Function                : PsAllocVert
 *
 * Description             : Allocate a Vertex from the free list.
 *
 * Formal parameter(s)     : None
 *
 * Return Value            : T_VERTEX * - pointer to vertex
 *
 * Assumption              : None
 *
 */
static T_VERTEX *PsAllocVert(void)
{
   T_VERTEX *ps_this = (T_VERTEX *)NULL;

   static T_CHAR param_message[] = "To many vertices in polyfill.";
   T_CHAR file_name[] = __FILE__;

   /*hdudispfpolygon1-PsAllocVert-DB-LLR-001*/
   /* Check for runtime error.   */
   if((MAX_VERTICES*TWO) == S16_next_vert)
   {
      RterrWidget((T_CHAR *)&file_name,__LINE__, (T_CHAR *) &param_message);
   }
   else
   {
      ;/* Does nothing */
   }
   /*hdudispfpolygon1-PsAllocVert-DB-LLR-002*/
   ps_this = &(S_vert_pool[S16_next_vert]);

   /* Initialize the structure.  */
   ps_this->psPrevV = ZERO;
   ps_this->psNextV = ZERO;
   ps_this->psPrevL = ZERO;
   ps_this->psNextL = ZERO;
   ps_this->s16SLineNum = (T_INT16)MINUS_ONE;

   S16_next_vert = (T_INT16)(S16_next_vert + (T_INT16)ONE);
   return(ps_this);
}

/*
 *
 * Function                : SpFindLine
 *
 * Description             : Locates the scan line for this vertex.
 *
 * Formal parameter(s)     : T_INT16 s16_scan_line - IN Input scan line
 *
 * Return Value            : T_VERTEX * - pointer to vertex
 *
 * Assumption              : None
 *
 */
static T_VERTEX *SpFindLine(T_INT16 s16_scan_line)
{
   T_VERTEX *ps_lw = &S_origin;
   T_VERTEX *ps_new_line = (void *)ZERO;

   static T_CHAR param_message[] = "Polly exceeds display size.";
   T_CHAR file_name[] = __FILE__;

   /*hdudispfpolygon1-SpFindLine-DB-LLR-001*/
   /* Check for valid scan line. */
   if((s16_scan_line < (T_INT16)ZERO) || (s16_scan_line >= (T_INT16)\
      (S16_panel_height* (T_INT16)MAG_FACTOR)))
   {
      RterrWidget((T_CHAR *)&file_name,__LINE__, (T_CHAR *) &param_message);
   }
   else
   {
      ;/*Do nothing*/
   }

   /*hdudispfpolygon1-SpFindLine-DB-LLR-002*/
   while(ps_lw->psNextL)
   {
      ps_lw = ps_lw->psNextL;

      /* If this scan line already exists.   */
      if((ps_lw->s16SLineNum) == s16_scan_line)
      {
         return(ps_lw);
      }

      /* If this scan does not exist and is lower. */
      /* Back up and insert. */
      else if((ps_lw->s16SLineNum) > s16_scan_line)
      {
         ps_lw = ps_lw->psPrevL;
         break;
      }
      else
      {
         ;/*Do nothing*/
      }
   }

   /*hdudispfpolygon1-SpFindLine-DB-LLR-003*/
   /* If new line.   */
   ps_new_line = PsAllocVert();
   ps_new_line->s16SLineNum = s16_scan_line;

   if(((T_VERTEX *)NULL) != ps_lw->psNextL)
   {
      (ps_lw->psNextL)->psPrevL = ps_new_line;
   }
   else
   {
      ;/*Do nothing*/
   }
   ps_new_line->psNextL = ps_lw->psNextL;
   ps_lw->psNextL = ps_new_line;
   ps_new_line->psPrevL = ps_lw;

   return(ps_new_line);
}

/*
 *
 * Function                : VInsertVert
 *
 * Description             : This routine inserts a vertices into the vertices list in
 *                                        ascending Y order.
 *
 * Formal parameter(s)     : T_SRECTPOINT *ps_prev_p - IN Pointer to previous rectangular points
 *                           T_SRECTPOINT *ps_vert_p - IN Pointer to current rectangular points
 *                           T_SRECTPOINT *ps_next_p - IN Pointer to the next rectangular points
 *
 * Return Value            : None
 *
 * Assumption              : None
 *
 */
static void VInsertVert(T_SRECTPOINT *ps_prev_p, T_SRECTPOINT *ps_vert_p, T_SRECTPOINT *ps_next_p)
{
   T_VERTEX *ps_lw = (T_VERTEX *)NULL;
   T_VERTEX *ps_new_vert = (T_VERTEX *)NULL;

   /*hdudispfpolygon1-VInsertVert-DB-LLR-001*/
   /* Else if at least one line to follow. */
   if(((ps_prev_p->s32Y) > (ps_vert_p->s32Y)) ||  ((ps_next_p->s32Y) > (ps_vert_p->s32Y)))
   {
      ps_lw = SpFindLine((T_INT16)(ps_vert_p->s32Y));
   }
   /* Ignore minimums. */
   else
   {
      return;
   }

   /*hdudispfpolygon1-VInsertVert-DB-LLR-002*/
   /* Initialize the new vertex. */
   ps_new_vert = PsAllocVert();
   ps_new_vert->sPrevP = *ps_prev_p;
   ps_new_vert->sVertP = *ps_vert_p;
   ps_new_vert->sNextP = *ps_next_p;

   /*hdudispfpolygon1-VInsertVert-DB-LLR-003*/
   /* While not at the end of the list. */
   while(ps_lw->psNextV)
   {
      ps_lw = ps_lw->psNextV;

      /* If the X of the new vert is lower than the list element. */
      /* Backup and exit. */
      if((ps_new_vert->sVertP.s32X) <= (ps_lw->sVertP.s32X))
      {
         ps_lw = ps_lw->psPrevV;
         break;
      }
      else
      {
         ;/*Do nothing*/
      }
   }

   /*hdudispfpolygon1-VInsertVert-DB-LLR-004*/
   /* Insert after list walker.  */
   if((ps_lw->psNextV)!= ZERO)
   {
      (ps_lw->psNextV)->psPrevV = ps_new_vert;
   }
   else
   {
      ;/*Do nothing*/
   }

   ps_new_vert->psNextV = ps_lw->psNextV;
   ps_lw->psNextV = ps_new_vert;
   ps_new_vert->psPrevV = ps_lw;
}

/*
 *
 * Function                : VBuildVertList
 *
 * Description             : Build the list of vertices from the list of polygon points.
 *
 * Formal parameter(s)     : T_SRECTPOINT *points_frst - IN Pointer to the first point in
 *                             the polygon point list.
 *                           T_UINT16 point_count - INOUT The number of points in the list.
 *
 * Return Value            : None
 *
 * Assumption              : None
 */
static void VBuildVertList(T_SRECTPOINT *points_frst, T_UINT16 point_count)
{
  /*hdudispfpolygon1-VBuildVertList-DB-LLR-001*/
  /*  Insert the first vertices.       */
  VInsertVert((points_frst+point_count-ONE), points_frst, (points_frst+ONE));

  /*hdudispfpolygon1-VBuildVertList-DB-LLR-002*/
   /* Insert the last vertices.              */
  VInsertVert(points_frst+point_count-TWO, (points_frst+point_count-ONE), points_frst);

  /*hdudispfpolygon1-VBuildVertList-DB-LLR-003*/
  point_count = (T_UINT16)(point_count - TWO);

  /*hdudispfpolygon1-VBuildVertList-DB-LLR-004*/
   /* Insert all but the first and last vertices.  */
  while(point_count--)
  {
    VInsertVert(points_frst, points_frst+ONE, (points_frst+TWO));
    points_frst++;
  }
}

/*
 *
 * Function                : VFreeEdgeList
 *
 * Description             : Clear the list of active edges.
 *
 * Formal parameter(s)     : None
 *
 * Return Value            : None
 *
 * Assumption              : None
 *
 */
static void VFreeEdgeList(void)
{
   /*hdudispfpolygon1-VFreeEdgeList-DB-LLR-001*/
   /* Free the edge list.  */
   S16_next_edge = ((T_INT16)ZERO);
   S16_active_edges = ((T_INT16)ZERO);
   S_active_edge_list.psNextE = (T_EDGE  *)ZERO;
   S_active_edge_list.psPrevE = (T_EDGE  *)ZERO;
}

/*
 *
 * Function                : PsAllocEdge
 *
 * Description             : Allocate an edge from the edge pool.
 *
 * Formal parameter(s)     : None
 *
 * Return Value            : T_EDGE * - pointer to edge
 *
 * Assumption              : None
 *
 */
static T_EDGE *PsAllocEdge(void)
{
   T_EDGE *ps_this = 0;

   static T_CHAR param_message[] = "Unable to allocate poly edge.";
   T_CHAR file_name[] = __FILE__;

   /*hdudispfpolygon1-PsAllocEdge-DB-LLR-001*/
   /* Check for runtime error.   */
   if(MAX_EDGES == S16_next_edge)
   {
      RterrWidget((T_CHAR *)&file_name,__LINE__, (T_CHAR *) &param_message);
   }
   else
   {
      /* Does nothing */
   }

   /*hdudispfpolygon1-PsAllocEdge-DB-LLR-002*/
   ps_this = &(S_edge_pool[S16_next_edge]);
   ps_this->psPrevE = (T_EDGE  *)ZERO;
   ps_this->psNextE = (T_EDGE  *)ZERO;

   S16_next_edge = (T_INT16)(S16_next_edge + (T_INT16)ONE);
   return(ps_this);
}

/*
 *
 * Function                : VEdgeInsert
 *
 * Description             : Insert edges for a given scan line.
 *
 * Formal parameter(s)     : T_EDGE *ps_this - INOUT Input scan line
 *
 * Return Value            : None
 *
 * Assumption              : None
 *
 */
static void VEdgeInsert(T_EDGE *ps_this)
{
   T_EDGE *ps_lw = &S_active_edge_list;

   /*hdudispfpolygon1-VEdgeInsert-DB-LLR-001*/
   while(ps_lw->psNextE)
   {
      ps_lw=ps_lw->psNextE;

      if((ps_this->sFirstP.s32X)==(ps_lw->s32_x1))
      {
         if((ps_this->s32Slope) < (ps_lw->s32Slope))
         {
            ps_lw=ps_lw->psPrevE;
         }
         else
         {
            ;/*Do nothing*/
         }
         break;
      }
      else
      {
         ;/*Do nothing*/
      }
      if((ps_this->sFirstP.s32X)<(ps_lw->s32_x1))
      {
         ps_lw=ps_lw->psPrevE;
         break;
      }
      else
      {
         ;/*Do nothing*/
      }
   }

   /*hdudispfpolygon1-VEdgeInsert-DB-LLR-002*/
   if((ps_lw->psNextE)!=ZERO)
   {
      ps_lw->psNextE->psPrevE = ps_this;
   }
   else
   {
      ;/*Do nothing*/
   }

   ps_this->psNextE = ps_lw->psNextE;
   ps_lw->psNextE = ps_this;
   ps_this->psPrevE = ps_lw;

   S16_active_edges = (T_INT16) (S16_active_edges + (T_INT16)ONE);
}

/*
 *
 * Function                : VEdgeInit
 *
 * Description             : Initialize edge members
 *
 * Formal parameter(s)     : T_EDGE *ps_edge - OUT Edges of the polygon
 *                           T_SRECTPOINT *ps_first_p - IN First rectangular point
 *                           T_SRECTPOINT *ps_secnd_p - IN Second rectangular point
 *
 * Return Value            : None
 *
 * Assumption              : None
 */
static void VEdgeInit(T_EDGE *ps_edge, T_SRECTPOINT *ps_first_p, T_SRECTPOINT *ps_secnd_p)
{
   /* Initialize the edge members.  */

   /*hdudispfpolygon1-VEdgeInit-DB-LLR-001*/
   ps_edge->sFirstP = *ps_first_p;
   ps_edge->sSecndP = *ps_secnd_p;

   ps_edge->s32Y0 = ps_edge->sFirstP.s32Y;
   ps_edge->s32_x0 = ps_edge->sFirstP.s32X;
   ps_edge->s32_x1 = ps_edge->sFirstP.s32X;

   ps_edge->s32YLength = ps_edge->sSecndP.s32Y - ps_edge->sFirstP.s32Y;

   ps_edge->s32Slope = (T_INT32)(ps_edge->sSecndP.s32X - ps_edge->sFirstP.s32X);
   ps_edge->s32Slope *= SLOPE_VAL;

   /*hdudispfpolygon1-VEdgeInit-DB-LLR-002*/
   if( ((T_INT32)ZERO) != ps_edge->s32YLength)
   {
      ps_edge->s32Slope= (T_INT32) (ps_edge->s32Slope / ps_edge->s32YLength);
   }
   else
   {
      ;/*Do nothing*/
   }
   if(ps_edge->s32Slope < ((T_INT32)ZERO))
   {
      ps_edge->s32Slope = (T_INT32) (ps_edge->s32Slope - (T_INT32)ONE);
   }
   else
   {
      ps_edge->s32Slope = (T_INT32) (ps_edge->s32Slope + (T_INT32)ONE);
   }
}

/*
 *
 * Function                : VAddEdges
 *
 * Description             : Add edge members for a given scan line.
 *
 * Formal parameter(s)     : T_VERTEX *ps_vert - INOUT Input scan line
 *
 * Return Value            : None
 *
 * Assumption              : None
 *
 */
static void VAddEdges(T_VERTEX *ps_vert)
{
   T_EDGE *ps_edge = 0;

   while(ps_vert->psNextV != ZERO)
   {
      /*hdudispfpolygon1-VAddEdges-DB-LLR-001*/
      ps_vert = ps_vert->psNextV;

      /*hdudispfpolygon1-VAddEdges-DB-LLR-002*/
      if((ps_vert->sNextP.s32Y) > (ps_vert->sVertP.s32Y))
      {
         ps_edge = PsAllocEdge();
         VEdgeInit(ps_edge, &ps_vert->sVertP, &ps_vert->sNextP);
         VEdgeInsert(ps_edge);
      }
      else
      {
         ;/*Do nothing*/
      }

      /*hdudispfpolygon1-VAddEdges-DB-LLR-003*/
      if((ps_vert->sPrevP.s32Y) > (ps_vert->sVertP.s32Y))
      {
         ps_edge = PsAllocEdge();
         VEdgeInit(ps_edge, &ps_vert->sVertP, &ps_vert->sPrevP);
         VEdgeInsert(ps_edge);
      }
      else
      {
         ;/*Do nothing*/
      }
   }
}

/*
 *
 * Function                : VProcessMagLine
 *
 * Description             : Add edge members for a given scan line.
 *
 * Formal parameter(s)     : T_INT16 s16_scan_y - IN Input scan line
 *
 * Return Value            : None
 *
 * Assumption              : None
 *
 */
static void VProcessMagLine(T_INT16 s16_scan_y)
{
   T_UINT8     *pu8_scan_ptr = (void *)0;
   T_UINT16 *pu16_frame_ptr = 0;
   T_UINT32 u32_width = 0;
   T_UINT8     *u8_mag_line = (void *)0;

   /*hdudispfpolygon1-VProcessMagLine-DB-LLR-001*/
   if(S16_scan_xmin > S16_scan_xmax)
   {
      return;
   }
   else
   {
      ;/*Do nothing*/
   }
   if(ZERO == U8_which_mag_line)
   {
      /*hdudispfpolygon1-VProcessMagLine-DB-LLR-002*/
      u8_mag_line = U8_mag_line1;
      U8_which_mag_line = ONE;
   }
   else
   {
      /*hdudispfpolygon1-VProcessMagLine-DB-LLR-003*/
      u8_mag_line = U8_mag_line2;
      U8_which_mag_line = ZERO;
   }

   /*hdudispfpolygon1-VProcessMagLine-DB-LLR-004*/
   pu8_scan_ptr =  &(u8_mag_line[S16_scan_xmin/(T_INT32)FOUR]);
   pu16_frame_ptr =  ((T_UINT16 *)Vp_fgfb2 + (((S16_scan_xmin/((T_INT32)FOUR)))
                                  + (s16_scan_y/((T_INT16)FOUR))*S16_panel_width));
   u32_width = (T_UINT32)(((S16_scan_xmax/((T_INT32)FOUR) -
                    S16_scan_xmin/((T_INT32)FOUR)) + ((T_INT32)ONE)));

   Dma2dScanLineBlend((void *)pu8_scan_ptr, (void *)pu16_frame_ptr, u32_width, E_pen_color);

   S16_scan_xmin = S16_panel_width*((T_INT16)FOUR);
   S16_scan_xmax = ((T_INT32)ZERO);
}

/*
 *
 * Function                : VProcessPairsHR
 *
 * Description             : Fill alternate pairs of lines.
 *
 * Formal parameter(s)     : T_INT16 s16_scan_y - IN Input scan line
 *
 * Return Value            : None
 *
 * Assumption              : None
 *
 */

static void VProcessPairsHR(T_INT16 s16_scan_y)
{
   T_EDGE *ps_this = (void *)0;
   T_INT32        s32_x0 = 0;
   T_INT32        s32_x1 = 0;
   T_UINT8        *u8_mag_line = (void *)0;

   static T_CHAR param_message[] = "Odd number of segments in poly fill.";
   T_CHAR file_name[] = __FILE__;
   /*hdudispfpolygon1-VProcessPairsHR-DB-LLR-001*/
   /* If no more edges to process.     */
   if(((T_INT32)ZERO) == S16_active_edges)
   {
      return;
   }
   else
   {
      ;/* Does nothing */
   }
   /*hdudispfpolygon1-VProcessPairsHR-DB-LLR-002*/
   /* Must have an even number of edges.  */
   if( ((T_INT16)ZERO) != (S16_active_edges % ((T_INT16)TWO)))
   {
      RterrWidget((T_CHAR *)&file_name,__LINE__, (T_CHAR *) &param_message);
   }
   else
   {
      ;/* Does nothing */
   }

   if(ZERO == U8_which_mag_line)
   {
      /*hdudispfpolygon1-VProcessPairsHR-DB-LLR-003*/
      u8_mag_line = U8_mag_line1;
   }
   else
   {
      /*hdudispfpolygon1-VProcessPairsHR-DB-LLR-004*/
      u8_mag_line = U8_mag_line2;
   }

   /* Fill scan line between each pair.   */
   ps_this  = S_active_edge_list.psNextE;

   while(ZERO != ps_this)
   {
     /*hdudispfpolygon1-VProcessPairsHR-DB-LLR-005*/
      S16_scan_xmin = MIN((ps_this->s32_x1), S16_scan_xmin);
      S16_scan_xmax = MAX((ps_this->psNextE->s32_x1), S16_scan_xmax);

      /* Start of scan. */
      s32_x0 = (ps_this->s32_x1);

      /* End of the scan. */
      s32_x1 = ps_this->psNextE->s32_x1;
      /*hdudispfpolygon1-VProcessPairsHR-DB-LLR-006*/
      /* Process to a pixel boundary. */
      while((s32_x0<s32_x1) && (s32_x0% ((T_INT32)FOUR)))
      {
         u8_mag_line[s32_x0/(T_INT32)FOUR] = (T_UINT8) (u8_mag_line[s32_x0/(T_INT32)FOUR] \
		+ PIXEL_BOUN);
         s32_x0 += ((T_INT32)ONE);
      }
      /*hdudispfpolygon1-VProcessPairsHR-DB-LLR-007*/
      /* Process 16 high res pixels at a time. */
      while((s32_x1-s32_x0)  > (T_INT32)SIXTEEN)
      {
         *((T_UINT32 *)(&(u8_mag_line[s32_x0/(T_INT32)FOUR]))) += HR_16_PIXEL_BOUN;
         s32_x0 += ((T_INT32)SIXTEEN);
      }
      /*hdudispfpolygon1-VProcessPairsHR-DB-LLR-008*/
      /* Process 8 high res pixels if available. */
      if((s32_x1-s32_x0) > ((T_INT32)EIGHT))
      {
         *((T_UINT16 *)(&(u8_mag_line[s32_x0/(T_INT32)FOUR]))) =
            (T_UINT16)(*((T_UINT16 *)(&(u8_mag_line[s32_x0/(T_INT32)FOUR]))) + HR_8_PIXEL_BOUN);

         s32_x0 += ((T_INT32)EIGHT);
      }
      else
      {
         ;/* Does nothing */
      }

      /*hdudispfpolygon1-VProcessPairsHR-DB-LLR-009*/
      /* Process 4 high res pixels if available. */
      if((s32_x1-s32_x0) > ((T_INT32)FOUR) )
      {
         u8_mag_line[s32_x0/(T_INT32)FOUR] = (T_UINT8) (u8_mag_line[s32_x0/(T_INT32)FOUR] + \
        HR_4_PIXEL_BOUN);
         s32_x0 += ((T_INT32)FOUR);
      }
      else
      {
         ;/* Does nothing */
      }

      /*hdudispfpolygon1-VProcessPairsHR-DB-LLR-010*/
      /* Process the remaining high res pixels. */
      u8_mag_line[s32_x0/(T_INT32)FOUR] = (T_UINT8)((u8_mag_line[s32_x0/(T_INT32)FOUR]) +
                              ((T_INT32)REM_PIXEL_BOUN * (s32_x1-s32_x0)));

      ps_this = ps_this->psNextE;
      ps_this = ps_this->psNextE;
   }
   /*hdudispfpolygon1-VProcessPairsHR-DB-LLR-011*/
   if( ((T_INT16)THREE) == (s16_scan_y %((T_INT16)FOUR)))
   {
      VProcessMagLine(s16_scan_y);
   }
   else
   {
      ;/* Does nothing */
   }
}

/*
 *
 * Function                : VRemoveEdges
 *
 * Description             : Remove edges from the edge list.
 *
 * Formal parameter(s)     : None
 *
 * Return Value            : None
 *
 * Assumption              : None
 *
 */
static void VRemoveEdges(void)
{
   T_EDGE *ps_this = (T_EDGE *)NULL;

   ps_this  = S_active_edge_list.psNextE;
   while(ps_this)
   {
     /*hdudispfpolygon1-VRemoveEdges-DB-LLR-001*/
      if(0 == (ps_this->s32YLength -= ((T_INT32)ONE)))
      {
         ps_this->psPrevE->psNextE = ps_this->psNextE;

         if( (T_EDGE *)NULL != ps_this->psNextE)
         {
            ps_this->psNextE->psPrevE = ps_this->psPrevE;
         }
         else
         {
            ;/*Do nothing*/
         }
         S16_active_edges = (T_INT16) (S16_active_edges - (T_INT16)ONE);
      }
      else
      {
         ;/*Do nothing*/
      }
      ps_this = ps_this->psNextE;
   }
}

/*
 *
 * Function                : VCalculateIntersections
 *
 * Description             : Calculate intersection of segments and scan lines.
 *
 * Formal parameter(s)     : T_INT16 s16_scan_y - IN Input Scan line
 *
 * Return Value            : None
 *
 * Assumption              : None
 *
 */
static void VCalculateIntersections(T_INT16 s16_scan_y)
{
   T_EDGE *ps_this = (T_EDGE *)NULL;

   /*hdudispfpolygon1-VCalculateIntersections-DB-LLR-001*/
   /* Calculate intersection of each edge.   */
   ps_this  = S_active_edge_list.psNextE;
   while(ps_this)
   {
      ps_this->s32_x1 = ps_this->s32_x0 + (((T_INT32)(s16_scan_y -ps_this->s32Y0) *
                                    ps_this->s32Slope)>>SIXTEEN);
      ps_this = ps_this->psNextE;
   }
}

/*
 *
 * Function                : VScanLines
 *
 * Description             : Fill the polygon using the scan line algorithm.
 *
 * Formal parameter(s)     : None
 *
 * Return Value            : None
 *
 * Assumption              : None
 *
 */
static void VScanLines(void)
{
   T_INT16  s16_scan_y = 0;            /* Y coordinate of present scan line. */
   T_VERTEX *ps_lw = (void *)0;      /* -> next scan line with vertices. */

   /* First list of vertices.          */
   ps_lw = S_origin.psNextL;
   /*hdudispfpolygon1-VScanLines-DB-LLR-001*/
   /* If the Poly collapsed to zero height, just exit.   */
   if((T_VERTEX *)0 == ps_lw)
   {
      return;
   }
   else
   {
      /* Does nothing */
   }

   /* Least most Y scan coordinate. */
   s16_scan_y = ps_lw->s16SLineNum;
   /*hdudispfpolygon1-VScanLines-DB-LLR-002*/
   do
   {
      VRemoveEdges();
      VCalculateIntersections(s16_scan_y);
      if(s16_scan_y == ps_lw->s16SLineNum)
      {
         VAddEdges(ps_lw);
         if( ((T_VERTEX *)NULL) != ps_lw->psNextL)
         {
            ps_lw = ps_lw->psNextL;
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
      VProcessPairsHR(s16_scan_y);
       /* Updtaed as per PR 100083 */
      s16_scan_y = (T_INT16) (s16_scan_y + ((T_INT16)ONE));
   } while(S16_active_edges);

   /*hdudispfpolygon1-VScanLines-DB-LLR-003*/
   VProcessMagLine((T_INT16)(s16_scan_y- ((T_INT16)ONE)));
}

/*
 *
 * Function                : PolygonFillRectTranslate
 *
 * Description             : The function fills the rectangle with the specified color.
 *
 * Formal parameter(s)     : T_INT16 s16_ulx - INOUT X axis of the polygon
 *                           T_INT16 s16_uly - INOUT Y axis of the polygon
 *                           T_INT16 s16_width INOUT  Width of the polygon
 *                           T_INT16 s16_height - INOUT Height of the polygon
 *                           T_EPENCOLOR e_color - IN Color to be filled
 *                           T_UINT8 u8_translate - IN Polygon direction(0 – Horizontal,
 *                                                     1 – Vertical)
 *
 * Return Value            : None
 *
 * Assumption              : None
 *
 */
static void PolygonFillRectTranslate(T_INT16 s16_ulx, T_INT16 s16_uly,
      T_INT16 s16_width, T_INT16 s16_height, T_EPENCOLOR e_color, T_UINT8  u8_translate)
{
   T_INT16  s16_temp = 0;
   T_UINT32 u32_color = 0;
   T_UINT32 u32_red = 0;
   T_UINT32 u32_green = 0;
   T_UINT32 u32_blue = 0;

   if (E_PORTRAIT == E_orientation)
   {
      if(u8_translate != ZERO)
      {
         /*hdudispfpolygon1-PolygonFillRectTranslate-DB-LLR-001*/
         s16_temp = s16_ulx;
         s16_ulx = s16_uly;
         s16_uly = (T_INT16)(S16_panel_height - s16_temp - s16_width);
         s16_temp = s16_height;
         s16_height = s16_width;
         s16_width = s16_temp;
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
   /*hdudispfpolygon1-PolygonFillRectTranslate-DB-LLR-002*/
   s16_ulx = MAX(s16_ulx,0);
   s16_uly = MAX(s16_uly,0);
   s16_width = MAX(s16_width,0);
   s16_height = MAX(s16_height,0);

    /* Updated as per PR100083*/
   /*hdudispfpolygon1-PolygonFillRectTranslate-DB-LLR-003*/
   if(((s16_ulx + s16_width) > S16_panel_width) ||((s16_uly + s16_height) > S16_panel_height)
         || (((T_INT16)ZERO) == s16_width) ||(((T_INT16)ZERO) == s16_height))
   {
      return;
   }
   else
   {
      ;/*Do nothing*/
   }

   /*hdudispfpolygon1-PolygonFillRectTranslate-DB-LLR-004*/
   /* Convert RGB444 to RGB888 */
   u32_red = (e_color & BIT_9_TO_12)>>EIGHT;
   u32_red |= u32_red<<FOUR;

   u32_green = (e_color & BIT_5_TO_8)>>FOUR;
   u32_green |= u32_green<<FOUR;

   u32_blue = (e_color & BIT_1_TO_4);
   u32_blue = u32_blue<<FOUR;

   u32_color = BIT_25_TO_32;
   u32_color |= u32_red<<SIXTEEN;
   u32_color |= u32_green<<EIGHT;
   u32_color |= u32_blue;

   /*hdudispfpolygon1-PolygonFillRectTranslate-DB-LLR-005*/
   Dma2dFillBox((T_UINT16)s16_ulx, (T_UINT16)s16_uly, (T_UINT16)s16_width,
                   (T_UINT16)s16_height, u32_color);
}

/*
 *
 * Function                : PolygonFillRect
 *
 * Description             : The function fills the rectangle with the specified color.
 *
 * Formal parameter(s)     : T_INT16 s16_ulx - IN X axis of the rectangle
 *                           T_INT16 s16_uly - IN Y axis of the rectangle
 *                           T_INT16 s16_width - IN width of the rectangle
 *                           T_INT16 s16_height - IN height of the rectangle
 *                           T_EPENCOLOR e_color - IN Color to be filled.
 *
 *Return Value            : None
 *
 *Assumption              : None
 *
 */
 void PolygonFillRect(T_INT16 s16_ulx, T_INT16 s16_uly,
                                 T_INT16 s16_width, T_INT16 s16_height, T_EPENCOLOR e_color)
{

   /*hdudispfpolygon1-PolygonFillRect-DB-LLR-001*/
   PolygonFillRectTranslate(s16_ulx, s16_uly, s16_width, s16_height, e_color, ONE);
}

/*
 * Function                : PolygonFillRectNT
 *
 * Description             : The function fills the rectangle with specified color
 *
 * Formal parameter(s)     : T_INT16 s16_ulx - IN X axis of the rectangle
 *                           T_INT16 s16_uly -  IN Y axis of the rectangle
 *                           T_INT16 s16_width - IN Width of the rectangle
 *                           T_INT16 s16_height - IN Height of the rectangle
 *                           T_EPENCOLOR e_color - IN Color to be filled
 *
 *Return Value            : None
 *
 *Assumption              : None
 *
 */
 void PolygonFillRectNT(T_INT16 s16_ulx, T_INT16 s16_uly,
                                 T_INT16 s16_width, T_INT16 s16_height, T_EPENCOLOR e_color)
{
   /*hdudispfpolygon1-PolygonFillRectNT-DB-LLR-001*/
   PolygonFillRectTranslate(s16_ulx, s16_uly, s16_width, s16_height, e_color, ZERO);
}

/*
 *
 * Function                : PolygonDrawFrame
 *
 * Description             : The function draws the frame for the rectangle
 *
 * Formal parameter(s)     : T_INT16 s16_ulx - INOUT X axis of the polygon
 *                           T_INT16 s16_uly - INOUT Y axis of the polygon
 *                           T_INT16 s16_width - INOUT Width of the polygon
 *                           T_INT16 s16_height - INOUT Height of the polygon
 *                           T_INT16 s16_thickness - IN Thickness of the frame
 *                           T_EPENCOLOR e_color IN Color of the frame
 *
 * Return Value            : None
 *
 * Assumption              : None
 *
 */
void PolygonDrawFrame(T_INT16 s16_ulx, T_INT16 s16_uly,
                                 T_INT16 s16_width, T_INT16 s16_height,
                                 T_INT16 s16_thickness, T_EPENCOLOR e_color)
{
   T_UINT32 u32_color = 0;
   T_INT16  s16_temp = 0;

   /*hdudispfpolygon1-PolygonDrawFrame-DB-LLR-001*/
   if (E_PORTRAIT == E_orientation)
   {
      s16_temp=s16_uly;
      s16_uly= (T_INT16)(S16_panel_height-s16_ulx-s16_width);
      s16_ulx=s16_temp;
      s16_temp=s16_height;
      s16_height=s16_width;
      s16_width=s16_temp;
   }
   else
   {
      /* Does nothing */
   }

   /*hdudispfpolygon1-PolygonDrawFrame-DB-LLR-002*/
   u32_color = WidgetsRGB444ToRGB888(e_color);

   /* Keep the the frame on screen. */

   /*hdudispfpolygon1-PolygonDrawFrame-DB-LLR-003*/
   Dma2dFillBox((T_UINT16) (s16_ulx-s16_thickness)
                        ,(T_UINT16)(s16_uly-s16_thickness)
                        ,(T_UINT16)(s16_width+(((T_INT16)TWO)*s16_thickness))
                        ,(T_UINT16)s16_thickness
                        ,u32_color);

   /*hdudispfpolygon1-PolygonDrawFrame-DB-LLR-004*/
   Dma2dFillBox( (T_UINT16)(s16_ulx-s16_thickness)
                        ,(T_UINT16)(s16_uly-s16_thickness)
                        , (T_UINT16)s16_thickness
                        , (T_UINT16)(s16_height+(((T_INT16)TWO)*s16_thickness))
                        , u32_color);

   /*hdudispfpolygon1-PolygonDrawFrame-DB-LLR-005*/
   Dma2dFillBox( (T_UINT16)(s16_ulx+s16_width)
                        ,(T_UINT16)(s16_uly-s16_thickness)
                        ,(T_UINT16) s16_thickness
                        ,(T_UINT16)( s16_height+(((T_INT16)TWO)*s16_thickness))
                        , u32_color);

   /*hdudispfpolygon1-PolygonDrawFrame-DB-LLR-006*/
   Dma2dFillBox( (T_UINT16)(s16_ulx-s16_thickness)
                        ,(T_UINT16)(s16_uly+s16_height)
                        , (T_UINT16)(s16_width+(((T_INT16)TWO)*s16_thickness))
                        , (T_UINT16)(s16_thickness)
                        , u32_color);
}

/*
 *
 * Function                : PolygonDrawPoly
 *
 * Description             : The function Build the list of vertices from the list
 *                           of polygon points.
 *
 * Formal parameter(s)     : T_SPOLY *ps_poly - IN Polygons
 *                           T_EPENCOLOR e_color - IN Color of the frame
 *
 * Return Value            : None
 *
 * Assumption              : None
 *
 */
void PolygonDrawPoly (T_SPOLY *ps_poly, T_EPENCOLOR e_color)
{
   E_pen_color = e_color;

   /*hdudispfpolygon1-PolygonDrawPoly-DB-LLR-001*/
   /* Free  the vertices storage.         */
   VFreeVertList();
   VFreeEdgeList();

   /*hdudispfpolygon1-PolygonDrawPoly-DB-LLR-002*/
   do
   {
      VBuildVertList(ps_poly->psRP, (T_UINT16) ps_poly->s16Pts);
      ps_poly = ps_poly->psNext;
   }  while (ps_poly);

   /*hdudispfpolygon1-PolygonDrawPoly-DB-LLR-003*/
   VScanLines();
}
