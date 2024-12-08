/*
 ******************************************************************************
 * License Information  :  Howell Instruments, Inc.                           *
 *                         "Licensed Software" and "All rights reserved".     *
 ******************************************************************************
 *  File                : hdudispfrounddial.h
 *
 *  Description         : Contains routines which draws and updates round dail
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
 *      1.1          Vinay H         19-Jul-2017             100064
 *      1.2          Shilpa A R      10-Oct-2017             100064
 *      1.3          Shruthi M N     15-Oct-2017             100083,100073
 *      1.4          Sainath G N     21-Jun-2020             100259
 *      1.5          Rona B S        02-Jul-2020             100259
 *      1.6          Rona B S        24-Jul-2020             100259
 *      1.7          Dhanalakshmi    05-Aug-2020             100270 
 *      1.8          Dhanalakshmi    12-Sep-2020             100276 
 *
 * Additional References : None
 *
 ******************************************************************************
 */

#ifndef _HDUDISPFROUNDDIAL_H_
#define _HDUDISPFROUNDDIAL_H_

#include "hdudispfwidgets.h"    /* Contains routines for widget params */
#include "hdudispflookup.h"     /* Provide the table lookup routines */
#include "hdudispfparams.h"     /* provides the tags for various parameters and parameter units */
#include "hdudispfpointers.h"   /* contains pointers for polygon shapes */
#include "hdudispfconfig.h"     /* contains page and color config information */
#include "hdulibbasictypes.h"   /* provides basic data types.*/

/* Updated due to PR 100083 */
#define CVT(x)   ((T_INT32)(((((T_FLOAT)x)/360.0f)*32768.0f)))
/* Maximum number of active round dials. */
#define MAX_PPD 5U      /* Maximum pointers per dial definition. */

typedef struct RoundDial *T_PROUNDDIAL;

typedef struct
{
   /* Static   Data  */
   T_SDISLOC         sUpperLeft;             /* Upper left of bit map. */
   T_SDISLOC         sDialCenterOffset;      /* Offset to center of dial. */
   T_LOOKUP_TABLE *psGeometry;               /* Pointer vs. Param. */
   T_PARAM_READING   *psParam;               /* Parameter driving the pointer. */
   T_SPTRSPEC     asPtrSpec[MAX_PPD+1];      /* Which pointers to use. */
   T_SDISLOC  ptr_scale[MAX_PPD+1];
   T_SDISLOC  ptr_scale_offset[MAX_PPD+1];
   T_INT32       rotAngle[MAX_PPD+1];        /* Angle to rotate. */ 
   T_UINT16       usLength;                  /* Length of Pointer in "MAG" pixels. */
   T_UINT16       u16Format;                 /* Binascii format for digital. */
   T_ETXFONT         eFont;                  /* Which font to use for the digital reading. */
   T_UINT8         numLimit  ;
   T_UINT8         vernStatus  ;
   T_FLOAT        vernPos  ;
   T_FLOAT         limVal[10];
   T_UINT8         limValtype[10];
   T_UINT16        limColor[10] ;
   T_UINT16        limType[10] ;
   /* Updtaed as per 100073 */
   T_UINT8         label;
   T_UINT16 associated_labels[5];
   /* Offset from dial center to the center of the digital window. */
   T_SDISLOC         sDigCenterOffset;
   T_SDISREGION   *psDisRegion;              /* Pointer to region to fail. */
   T_PROUNDDIAL   pRoundDial;                /* Handle to the runtime structure. */
}  T_ROUNDDIALDEF;

typedef struct RoundDial
{
   T_ROUNDDIALDEF *round_dial_def;              /* Ptr to Round Dial Definition. */
   T_SWIDGETPARAM sWidgetParm;                  /* Run time data.  */
    /* Updated as per PR100083*/
   T_INT32              sAngle;                /* Angle of pointer on dial face.   */
   T_SPTRSPEC        asPtrSpec[MAX_PPD+1];     /* Pointer Handle.			       */ 
   T_CHAR                 acDigText[MAX_DPD];  /* digits+delimiter + "book ends".  */
   T_SPOLY              *psPolyRedX;           /* Polygon to "Red X" the region.   */
}  T_ROUNDDIAL;

extern void RoundDialAllocat(T_ROUNDDIALDEF *round_dial_def);
extern void RoundDialUpdate(void);
extern void RoundDialDraw(void);
extern void RoundDialClear(void);

#endif /* _HDUDISPFROUNDDIAL_H_ */
