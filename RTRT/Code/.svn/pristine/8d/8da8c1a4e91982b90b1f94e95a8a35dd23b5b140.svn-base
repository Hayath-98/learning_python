/*
 ******************************************************************************
 * License Information  :  Howell Instruments, Inc.                           *
 *                         "Licensed Software" and "All rights reserved".     *
 ******************************************************************************
 *  File                : hdudispfpolygon2.h
 *
 *  Description         : Contains routines for polygons configuration.
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
 *      1.1           Shilpa A R          19-Jul-2017             100064
 *      1.2           Shilpa A R          09-Oct-2017             100064
 *      1.3           Rona B S            11-Oct-2017             100064
 *      1.4           Shruthi M N         15-Oct-2017             100083,100087
 *      1.5           Vinay H             23-Mar-2018             100196
 *      1.6           Sainath G N         21-Jun-2020             100259
 *      1.7           Rona B S            02-Jul-2020             100259
 *      1.8           Rona B S            05-Oct-2020             100288 
 *
 * Additional References : None
 *
 ******************************************************************************
 */

#ifndef _HDUDISPFPOLYGONS_H_
#define _HDUDISPFPOLYGONS_H_

#include "hdulibbasictypes.h"  /* Contains basic data types.*/

/* Factor of four magnification is used for anti-aliasing.  */
#define MAG_FACTOR      4U
#define ANGLE_MASK      0x7fffU
#define ANGLE_SUBT      0x2000U
#define ANGLE_PIBY2     0x2000U
#define ANGLE_3PIBY2_1  0x6000U
#define ANGLE_3PIBY2_2  0x4000U
#define PI_2_RAD_MAX    0x8000U
#define POINT_FIVE      0.5f
#define SIXTEEN_POINT_ZERO 16.0f

#define DEC_TWO			2
#define TWO             2U
#define THREE           3U
#define FORTEEN         14U
#define FL2XPI          (2.0f * PI_VAL)

/* Parameters to function PolygonsvPolarToRect */
#define XOFF_ZERO (T_INT32)0
#define YOFF_ZERO (T_INT32)0
#define LEN_ZERO  0U
#define ROT_ZERO  0U
#define MAX_POLYS 30U

/* Stock polygon shapes.   */
typedef enum
{
   EEND = 0,
   ENOSHAPE = 0,
   ECAPRSHAPE=360,
   EEQUILATERALTRIANGLE =361,
   EREDXSHAPE=362,
   ESTDPTRSHAPE=363,
   ESTDTIPSHAPE=364,
   EDIMONDPOINTSHAPE=365,
   EDIMONDPOINTTIPSHAPE=366,
   ECAPTSHAPE=367,
   ESQUARE=368,
   ECAPESHAPE=369,
   ELOWERBOXPOINTERSHAPE = 370,
   ECAPGSHAPE = 371,
   EMIDDLEBOXPOINTERSHAPE=372,
   EDIMONDPOINTFINESHAPE=373,
   EDIMONDPOINTFINETIPSHAPE=374,
   ERIGHTTRIANGLE = 375,
   ERIGHT2TRIANGLE = 376,
   EMOVINGROUNDDIAL = 377,
   EPOINTERSHAPE1 = 378,
   EPOINTERSHAPE2 = 379,
   EPOINTERSHAPE3 = 380,
   EPOINTERSHAPE4 = 381,
   EPOINTERSHAPE5 = 382,
   EPOINTERSHAPE6 = 383,
   EPOINTERSHAPE7 = 384,
   EPOINTERSHAPE8 = 385,
   EPOINTERSHAPE9 = 386,
   EPOINTERSHAPE10 = 387,
   EPOINTERSHAPE11 = 388,
   EPOINTERSHAPE12 = 389,
   EMAXSTOCKSHAPE=390
}  T_ESTOCKSHAPE;

/* Single point of a polygon. */
typedef struct sRectPoint
{
   T_INT32  s32X;    /* X coordinate. */
   T_INT32  s32Y;    /* Y coordinate. */
}  T_SRECTPOINT;

/* Single vector in a polygon. */
typedef struct sPolarPoint
{
   T_INT32  s32R;       /* Radius */
   T_INT32  s32A;       /* Angle */
}  T_SPOLARPOINT;

/* Union of Rectangular and Polar polygon element. */
typedef union uPolyElement
{
   T_SRECTPOINT   sRP;
   T_SPOLARPOINT  sPP;
}  T_UPOLYELEMENT;

/*
 * Each polygon will be initialized with both polar and rectangular information.
 * This will allow each polygon to be translated, rotated, and projected
 * along the axis of rotation independently.
 */

/* Structure for a composite polar/rectangular polygon. */
typedef struct sPoly
{
   T_INT16           s16Pts;  /* Number of points in the polygon. */
   T_SRECTPOINT   *psRP;      /* Pointer to array of rectangular points. */
   T_SPOLARPOINT  *psPP;      /* Pointer to array of vectors points. */
   struct sPoly   *psNext;    /* Next polygon in the string. */
}  T_SPOLY;

typedef struct
{
   T_FLOAT fX;
   T_FLOAT fY;
}  T_SFLOATPOINT;

/* Floating Point Polygon. */
typedef struct sFloatPoly
{
   T_INT16  s16Points;                 /* Number of points. */
   const struct sFloatPoly *psNext;    /* Pointer to next polygon (inclusion). */
    /* Updated as per PR100083*/
   T_SFLOATPOINT  asFloatPoint[45];    /* Array of points. */
}  T_SFLOATPOLY;

typedef struct
{
    T_UINT16 polygon_shape;
    T_UINT8 polygon_no_pts;
    T_SFLOATPOLY *polystruct;
}  T_POLYGRAPHDEF;

extern T_SPOLY * PolygonsPsPolyInit(T_ESTOCKSHAPE  e_poly_shape
                                                      ,T_FLOAT         fx_scale
                                                      ,T_INT16    s16_xoff
                                                      ,T_FLOAT         fy_scale
                                                      ,T_INT16    s16_yoff
                                                      ,T_INT16    s16_rot
);

extern void PolygonsClear(void);
extern T_SPOLY *PolygonsPsDuplicate(T_SPOLY *ps_poly_src);
extern void PolygonsvTranslate(T_SRECTPOINT *s_rect_point);
 /* Updated as per PR100083*/
extern void PolygonsvPolarToRect(T_SPOLY *ps_poly, T_INT32 s32_xoff, T_INT32 s32_yoff,
         T_UINT16 u16_len, T_INT32 u32_rot,
		 T_INT32 u32_rot_rd, T_BOOL moving_rd);

#endif /* _HDUDISPFPOLYGONS_H_ */
