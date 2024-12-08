/*
 ******************************************************************************
 * License Information  :  Howell Instruments, Inc.                           *
 *                         "Licensed Software" and "All rights reserved".     *
 ******************************************************************************
 *  File                : hdudispfgrapp.h
 *
 *  Description         : Contains routines for displaying exceedences,cool down timer ,
 *                        bar graphs, rounddails and timers
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
 * <Version No.>     <Author>          <Date>         <Problem Report No.>
 *
 *      1.1          Shilpa A R       13-Sep-2017             100064
 *      1.2          Shruthi M N      13-Oct-2017             100083
 *      1.3          Shruthi M N      04-Nov-2017             100133
 *      1.4          Vinay H          23-Mar-2018             100196
 *      1.5          Rona B S         30-Jun-2020             100259
 *      1.6          Dhanalakshmi     05-Aug-2020             100270
 *      1.7          Dhanalakshmi     20-Mar-2021             100331
 *      1.8          Dhanalakshmi     20-Mar-2021             100331
 *
 * Additional References : None
 *
 ******************************************************************************
 */

#ifndef  _HDUDISPFGRAPP_H_
#define  _HDUDISPFGRAPP_H_

#include "hdudispfpara.h"          /* prototype for builds faults, message and system information */
#include "hdulibbasictypes.h"    /* Contains basic header definations */
#include "hdudispflookup.h"        /* Provide the table lookup routines */
#include "hdudispfbargraphs.h"     /* Routines which maintain the "Real Time" bar-graphs */
#include "hdudispfnumbox.h"        /* Number box routines*/
#include "hdudispfrounddial.h"     /* routines which draws and updates the round dial */
#include "hdudispfcarrotgraph.h"     /* routines which draws and updates the round dial */
/* updated as per PR 100083 */
#include "hdudispfa429.h"  /* Routines for arinc 429 */

/* updated as per PR 100083 */
#define PAGE_EXCEEDANCE_ADDR  (T_UINT8 *)0x63540000
#define SEC_PER_MIN     60U
#define MIN_PER_HOUR    60U

/* updated as per PR 100083 */
typedef struct
{
   T_UINT8 label;
   T_UINT8 sdi;
   T_A429_DATA_TYPE type;
   T_PARAM_READING reading;
}T_PARAM_TABLE;

typedef enum
{
   INVALID,           /* (invalid) 0 */
   LESS_THAN,         /* <         1 */
   LESS_THAN_EQUAL,   /* <=        2 */
   EQUAL,             /* =         3 */
   GREATER_THAN_EQUAL,/* >=        4 */
   GREATER_THAN,      /* >         5 */
   NOT_EQUAL          /* !=        6 */
}T_OPERATORS;

extern T_EPAGE_NUM Page_num;
extern T_SBARGRAPHDEF Ap_page1_bar_graphs[30];
extern T_ROUNDDIALDEF Ap_page0_dials[30];
extern T_CARROTGRAPHDEF Ap_page2_carrot[30];
extern T_POLYGRAPHDEF Ap_poly_graph[30];
/* updated as per PR 100083 */
extern T_PARAM_TABLE Parameters[256];
extern T_PARAM_TABLE Parameters_reading[256];
extern T_PARAM_TABLE Scu_parameters[3];
extern T_UINT8 Splash_done;
extern T_STEXTBOXDATA Rev_cool_down_pop_up_box;
extern T_SNUMBOXDEF Page_num_boxes[50];
extern T_STEXTBOXPDIDATA Ap_page_tbs[50];
extern T_STEXTBOXDATA Prim_cool_down_pop_up_box ;
extern T_PARAM_TABLE Parameters_numbox[256];
/* Updated for PR100133 */
extern T_UINT8 Splash_b1_press;

extern T_CHAR* RevCoolxBoxText(void);
extern void GrappInit(void);
extern void GrappApp(void);
extern void GrappSwithcScreens(T_EPAGE_NUM eNewPageNum);
extern T_CHAR* CoolxBoxText(void);
extern void AppDraw1(void);
extern T_UINT8 CompareLimit(T_FLOAT val, T_FLOAT range, T_UINT8 operator);
extern T_CHAR Timer_message[13];
#endif /* _HDUDISPFGRAPP_H */
