/*
 ******************************************************************************
 * License Information  :  Howell Instruments, Inc.                           *
 *                         "Licensed Software" and "All rights reserved".     *
 ******************************************************************************
 *  File                : hdudispfbargraphs.h
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
 *      1.2          Shruthi M N     15-Oct-2017             100083
 *      1.3          Rona B S  		 02-Jul-2020             100259
 *      1.4          Dhanalakshmi    05-Aug-2020             100270 
 *      1.5          Dhanalakshmi    12-Sep-2020             100276 
 *
 * Additional References : None
 *
 ******************************************************************************
 */
#ifndef _HDUDISPFBARGRAPHS_H_
#define _HDUDISPFBARGRAPHS_H_

#include "hdudispfwidgets.h" /* Contains routines for widget params */
#include "hdudispflookup.h"     /* provide the table lookup routines. */
#include "hdudispfparams.h"     /* provides the tags for various parameters and parameter units. */
#include "hdudispfpointers.h"   /* contains pointers for polygon shapes */
#include "hdudispfconfig.h"  /* contains page and color config information */

/*=============  Configuration Definitions.  =========*/

#define MAX_BARS        30U      /* Maximum number of active carrot graphs. */
#define MAX_BAR_WIDTH   600U     /* Maximum width of a bar in pixels. */

/* Is the bar graph vertical or horizontal. */
typedef  enum
{
   BG_VERTICAL=398,
   BG_HORIZONTAL=397
}  T_EBGHV;

typedef struct sBarGraph *T_PSBARGRAPH;

typedef struct
{
   /* Static   Data  */
   T_PARAM_READING      *psParam;       /* Parameter driving the pointer.*/
   T_SDISLOC            sOrigin;        /* Origin of the graph.*/
   const T_LOOKUP_TABLE      *psGeometry;/* Length vs. Param. */
   T_UINT16          u16Width;          /* Width of the bar. */
   T_EPENCOLOR       ePenColor;         /* Color of the bargraph. */
   T_EBGHV              eBGHV;          /* Horizontal or vertical type? */
   T_UINT16          u16Format;         /* Binascii format for digital. */
   T_SDISLOC            sDigOffset;     /* Center of Digital Reading. */
   T_ETXFONT            eFont;          /* Which font to use for the digital reading.T_PSBARGRAPH */
   T_UINT8         numLimit  ;
  /* Updated as per PR100083*/
   T_FLOAT         limVal[10];
   T_UINT8         limValtype[10];
   T_UINT16        limColor[10] ;
   T_UINT16        limType[10] ;
   T_SDISREGION      *psDisRegion;      /* Region pointer if invalid parameter. */
   T_PSBARGRAPH    *psbargraph;         /* Ptr to run time structure. */
}  T_SBARGRAPHDEF;

typedef struct sBarGraph
{
   T_SBARGRAPHDEF *ps_bar_graph_def;
   T_SWIDGETPARAM sWidgetParm;               /* Run time data. */
   /* Updated as per PR100083*/ 
   T_INT32              sLength;             /* Length of the bar graph. */
   T_UINT8              acDigText[MAX_DPD];  /*  Ascii of digital readout. */
   T_SPOLY              *psPolyRedX;         /* Polygon to "Red X" the region. */
}  T_SBARGRAPH;

/*Functions*/
extern void BargraphAllocat(T_SBARGRAPHDEF *psBarGraphDef);

extern void BargraphUpdate(void);
extern void BargraphDraw(void);
extern void BargraphClear(void);

#endif /* BARGRAPHS_H_ */
