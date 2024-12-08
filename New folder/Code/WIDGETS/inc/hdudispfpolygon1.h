/*
 ******************************************************************************
 * License Information  :  Howell Instruments, Inc.                           *
 *                         "Licensed Software" and "All rights reserved".     *
 ******************************************************************************
 *  File                : hdudispfpolygon1.h
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
 *      1.3          Rona B S        02-Jul-2020             100259
 *
 * Additional References : None
 *
 ******************************************************************************
 */

#ifndef _HDUDISPFPOLYGON_H_
#define _HDUDISPFPOLYGON_H_

#include "hdudispfconfig.h"      /* contains page and color config information */
#include "hdudispfpolygon2.h"    /* contains routines for ploygons configuration */
#include "hdulibbasictypes.h"  /*provides basic data types.*/

/* Maximum number of points in a polygon. */
#define MAX_PP                 50U
#define PIXEL_BOUN             0x0fU
#define HR_16_PIXEL_BOUN       0x3f3f3f3fUL
#define HR_8_PIXEL_BOUN        0x3f3fU
#define HR_4_PIXEL_BOUN        0x3fU
#define REM_PIXEL_BOUN         0x0fU
#define BIT_9_TO_12            0x0f00U
#define BIT_5_TO_8             0x00f0U
#define BIT_1_TO_4             0x000fU
#define BIT_25_TO_32           0xff000000UL

/* Type for a standard polygon point.*/
typedef struct
{
  T_INT16 X;
  T_INT16 Y;
}T_POINT, * T_PPOINT;

typedef struct Vertex
{
   T_INT16     s16SLineNum;

   T_SRECTPOINT      sPrevP;
   T_SRECTPOINT      sVertP;
   T_SRECTPOINT      sNextP;

   struct Vertex *psPrevV;
   struct Vertex *psNextV;

   struct Vertex *psPrevL;
   struct Vertex *psNextL;
}T_VERTEX;


/* Structure for a single edge.  */
typedef struct Edge
{
   T_SRECTPOINT   sFirstP;
   T_SRECTPOINT   sSecndP;

   T_INT32  s32Y0;
   T_INT32  s32_x0;
   T_INT32  s32_x1;

   T_INT32  s32YLength;

   T_INT32  s32Slope;
   T_INT32  s32XAcc;

   struct   Edge  *psPrevE;
   struct   Edge  *psNextE;
}T_EDGE;

/*Functions*/
extern void PolygonFillRect(T_INT16 s16_ulx, T_INT16 s16_uly, T_INT16 width, T_INT16 height,
                                        T_EPENCOLOR e_color);
extern void PolygonFillRectNT(T_INT16 s16_ulx, T_INT16 s16_uly, T_INT16 s16_width,
                                  T_INT16 s16_height, T_EPENCOLOR e_color);
extern void PolygonDrawFrame(T_INT16 s16_ulx, T_INT16 s16_uly,
                                 T_INT16 width, T_INT16 height,
                                 T_INT16 s16Thickness, T_EPENCOLOR e_color);

extern void PolygonDrawPoly (T_SPOLY   *ps_poly, T_EPENCOLOR e_color);


#endif /* _HDUDISPFPOLYGON_H_ */
