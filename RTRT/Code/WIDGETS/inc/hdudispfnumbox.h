/*
 ******************************************************************************
 * License Information  :  Howell Instruments, Inc.                           *
 *                         "Licensed Software" and "All rights reserved".     *
 ******************************************************************************
 *  File                : hdudispfnumbox.h
 *
 *  Description         : This file contains the routines which maintain the
 *                                  "Real Time" Number box of the foreground display.
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
 *      1.2          Shruthi M N     16-Oct-2017             100083
 *      1.3          Sainath G N     21-Jun-2020             100259
 *      1.4          Rona B S        02-Jul-2020             100259
 *      1.5          Dhanalakshmi    05-Aug-2020             100270 
 *      1.6          Dhanalakshmi    12-Sep-2020             100276 
 *      1.7          Dhanalakshmi    28-Sep-2020             100285 
 *
 * Additional References : None
 *
 ******************************************************************************
 */

#ifndef _HDUDISPFNUMBOX_H_
#define _HDUDISPFNUMBOX_H_

#include "hdudispfwidgets.h"  /* Contains routines for widget params */
#include "hdudispfbinascii.h" /* Contains function prtotypes*/
#include "hdudispflookup.h"   /* Provide the table lookup routines */
#include "hdudispfparams.h"   /* provides the tags for various parameters and parameter units */
#include "hdudispfpointers.h"   /* contains pointers for polygon shapes */
#include "hdudispfconfig.h"  /* contains page and color config information */
#include "hdulibbasictypes.h" /* Standard basic data type definitions */

/*=============  Configuration Definitions.  =========*/
#define MAX_NUMBOX   50U            /* Maximum number of active carrot graphs. */
#define NB_DFT_FORMAT  277
typedef struct sNumBox *T_PSNUMBOX;

typedef struct
{
   /* Static   Data  */
   T_PARAM_READING      *psParam;   /* Parameter driving the number. */
   T_SDISLOC            sCenter;    /* Origin of the number. */
   T_UINT16          u16Format;     /* Format for number. */
   T_ETXFONT            eFont;      /* Which font to use for the digital reading. */
   T_EPENCOLOR     ePenColor;
  T_UINT8         numLimit;
  T_FLOAT        limVal[10];
  T_UINT8         limValtype[10];
  T_UINT16        limColor[10];
  T_UINT16        limType[10] ;
   T_SDISREGION      *psDisRegion;  /* Region used for RED X */
   T_PSNUMBOX        *psNumBox;     /* Ptr to run time structure. */
}  T_SNUMBOXDEF;

typedef struct sNumBox
{
   T_SNUMBOXDEF      *psNumBoxDef;
   T_SWIDGETPARAM sWidgetParm;
   T_UINT8              acDigText[MAX_DPD+3];    /* Ascii of digital readout. */
   T_SPOLY              *psPolyRedX;             /* Polygon to "Red X" the region. */
}  T_SNUMBOX;

extern void NumboxAllocat(T_SNUMBOXDEF *psNumBoxDef);

extern void NumboxUpdate(void);
extern void NumboxDraw(void);
extern void NumboxClear(void);

#endif /* _HDUDISPFNUMBOX_H_ */

