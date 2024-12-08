/*
 ******************************************************************************
 * License Information  :  Howell Instruments, Inc.                           *
 *                         "Licensed Software" and "All rights reserved".     *
 ******************************************************************************
 *  File                : hdudispfapp.c
 *
 *  Description         : This file contains Engine Information System application
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
 *      1.1           Shilpa A R        12-Sep-2017             100064
 *      1.2           Divya G P         10-Oct-2017             100064
 *      1.3           Shruthi M N       15-Oct-2017             100083
 *      1.4           Shruthi M N       30-Oct-2017             100104
 *      1.5           Shilpa A R        23-Mar-2018             100196
 *      1.6           Dhanalakshmi D    21-Jun-2020             100259
 *      1.7           Rona B S          29-Jun-2020             100259
 *      1.8           Dhanalakshmi      12-Sep-2020             100276
 *      1.9           Dhanalakshmi      20-Mar-2021             100331
 *      1.10          Dhanalakshmi      20-Mar-2021             100331
 *
 * Additional References : None
 *
 ******************************************************************************
 */

#include "hdudispfa429.h"            /* Routines for arinc 429 */
#include "hdudispfapp.h"             /* contains Engine Information System application */
#include "hdudispfbspnor.h" /* contains the common defines and functions prototypes bspnor*/
#include "hdudispfcas.h"             /* defines and functions prototypes for CAS */
#include "hdudispfdma2.h"   /* contains the common defines and functions prototypes for dma */
#include "hdudispfdma2d.h"  /* contains the common defines and functions prototypes for dma2d */
#include "hdudispfglobalsettings.h"  /* contains prototype for Global settings module*/
#include "hdudispfgrapp.h"           /* routines for all graph */
#include "hdudispfmenu.h"            /* contains prototype for menu module*/
#include "hdudispfoffside.h"         /* contains prototype for offside modules*/
#include "hdudispfpbit.h"            /* contains prototypes for PBIT test. */
#include "hdudispfpbs.h"             /* Contains functions prototypes of pbs.*/
#include "hdudispfresource.h"        /* provides central location to use of On Chip Peripherals*/
#include "hdudispfstandard.h"        /* Standard definitions */
#include "hdudispfucos.h"            /* uC/OS routines for the real-time kernel */
#include "hdulibbasictypes.h"      /* Standard basic data type definitions */
#include "hdudispfpara.h"     /* prototype for builds faults, message and system information */
#include "hdudispfpanel.h"           /* Contains functions prototypes of panel.*/
#include "hdudispfrtd.h"             /* Provide mapping for all A825 incoming parameters */
#include "hdudispfforeground.h"     /* contains the routines for foreground layer of the display */
#include "hdudispfarinc825.h"        /* Define the structure for an ARINC 825 Message. */
#include "hdudispfa825comm.h"        /* Routines for arinc 825 communication */
#include "hdudispfoscpu.h"           /* OS function declarations */
#include "hdudispfparams.h"     /* provides the tags for various parameters and parameter units */
/* Updated as per PR100083*/
#include "hdudispfwdog.h"            /* Watch dog timer declarations */
#include "hdudispfdauprofile.h"   /* defines the constants for ARINC 825  Message Traffic.*/
#include "hdudispfpdidata.h" /* provides pdi declarations */
#include "hdulibcorecm7.h"  /* Cortex-M7 processor and core peripherals */
#include "hdudispfpdicheck.h" /* Provides PDI check declarations */
#include "hdudispfrterror.h"       /*provides stub routine for run time errors.*/
#include "hdudispfmdff.h"            /*  Description contains Fuel flow functionalities */
#include "hdudispflmsscu.h"  /* SCU rtd processing and error codes  */

#define STK_DEF_VAL   0xDEADDEADU
#define ZERO_TIME_OUT 0U
#define SEM_CNT_VAL   0U
#define MAX_FRAME_VAL 25U
#define BIT_15_SET    16384U
#define DU_POSITION_SFC 49169U
#define PEAK_PICKER_RATE 5U

T_UINT8 Engine_count_app = 0;
T_UINT32 Time_in_sec =0;

/* Allocate stack for the appliication task. */
T_OS_EVENT *Sem_app_task = ZERO;
T_OS_STK App_task_stk[APP_TASK_STK_SIZE] =
{
  STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,
  STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,
  STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,
  STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,
  STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,
  STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,
  STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,
  STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,
  STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,
  STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,
  STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,
  STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,
  STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,
  STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,
  STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,
  STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,
  STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,
  STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,
  STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,
  STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,
  STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,
  STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,
  STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,
  STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,
  STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,
  STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,
  STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,
  STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,
  STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,
  STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,
  STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,
  STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,
  STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,
  STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,
  STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,
  STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,
  STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,
  STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,
  STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,
  STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,
  STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,
  STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,
  STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,
  STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,
  STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,
  STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,
  STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,
  STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,
  STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,
  STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,
  STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,
  STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,
  STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,
  STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,
  STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,
  STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,
  STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,
  STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,
  STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,
  STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,
  STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,
  STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,
  STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,
  STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,
  STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,
  STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,
  STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,
  STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,
  STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,
  STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,
  STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,
  STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,
  STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,
  STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,
  STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,
  STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,
  STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,
  STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,
  STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,
  STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,
  STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,
  STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,
  STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,
  STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,
  STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,
  STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,
  STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,
  STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,
  STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,
  STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,
  STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,
  STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,
  STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,
  STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,
  STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,
  STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,
  STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,
  STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,
  STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,
  STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,
  STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,
  STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,
  STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,
  STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,
  STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,
  STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,
  STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,
  STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,
  STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,
  STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,
  STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,
  STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,
  STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,
  STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,
  STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,
  STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,
  STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,
  STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,
  STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,
  STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,
  STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,
  STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,
  STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,
  STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,
  STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,
  STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,
  STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,
  STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL,STK_DEF_VAL
};

static void AppTask(void *p_data);
static void CheckMsgCtrlArea(void);

/*
 * Function                :  AppTask
 *
 * Description             :  This function is used by the OS to create the task for this module
 *
 * Formal parameter(s)     :  void *p_data - IN pointer to null data(not used)
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */

static void AppTask(void *p_data)
{
   T_UINT8  u8_err = ZERO;
   static T_UINT32 u32_frame_counter = ZERO;
   static T_UINT8  toggle = ZERO;
   static T_UINT8  toggle_log = ZERO;
   /* Updated for PR 100083 */
   T_A825_MESSAGE   s_mess = {ZERO};
   static T_UINT32 re_pull_cnt = 0;
   /*hdudispfapp-AppTask-DB-LLR-014*/
   p_data = (T_UINT8 *)p_data + 0;

   /*hdudispfapp-AppTask-DB-LLR-002*/
   /* Initialize the DMA2D. */
   Dma2dInit();

    /* Updated as per PR100083*/
   WdogKickWatchDog();

   /*hdudispfapp-AppTask-DB-LLR-003*/
   /* Initialize the DMA2. */
   Dma2Init();

    /* Updated as per PR100083*/
   WdogKickWatchDog();

   /*hdudispfapp-AppTask-DB-LLR-012*/
   /* Initialize foreground draw routines. */
   ForegroundInit();

   /* Updated as per PR100083*/
   WdogKickWatchDog();

   /*hdudispfapp-AppTask-DB-LLR-004*/
   /* Initialize the graphic draw routines. */
   GrappInit();

    /* Updated as per PR100083*/
   WdogKickWatchDog();

   /*hdudispfapp-AppTask-DB-LLR-013*/
   /* Updated as per PR100083*/
   A429Init();
   WdogKickWatchDog();

   /*hdudispfapp-AppTask-DB-LLR-005*/
   PdiDataInit();

   /* Updated as per PR100083*/
   WdogKickWatchDog();

   /*hdudispfapp-AppTask-DB-LLR-006*/
   /* Initialize the CAS draw routines. */
   CasInit();

   /* Updated as per PR100083*/
   WdogKickWatchDog();

   /*hdudispfapp-AppTask-DB-LLR-007*/
   /* Updated as per PR 100083 */
   /*Init the arinc 825 H.W. channels */
   A8251Init();
   WdogKickWatchDog();

   A8252Init();
   WdogKickWatchDog();

      /*Set up the task to process each incoming message. */
   A825CommInit1();
   WdogKickWatchDog();

   A825CommInit2();
   WdogKickWatchDog();

   /* Request Global settings from the 429 Interface board. */
   GlobalSettingsPull();

   /*Initialize the Menu Items*/
   MenuInitialize();
   /* Function to check PDI parameters */
   PdiDataCheck();
   /* Calibration labels conversion */
   CalibrationLabels();
   /*hdudispfapp-AppTask-DB-LLR-008*/
   /* Clear any pending signals. */
   while (ZERO != (OsSemAccept(Sem_app_task)))
   {
    /* Updated as per PR100083*/
     WdogKickWatchDog();

   }

   /*hdudispfapp-AppTask-DB-LLR-009*/
   while (TRUE)
   {
      /* Wait for a message to arrive. */
      OsSemPend(Sem_app_task, ZERO_TIME_OUT, &u8_err);

      /* Updated as per PR100083*/
      WdogKickWatchDog();

      /* Redraw the screen every other frame. */
      toggle = (toggle+ONE) & ONE;
      toggle_log = (T_UINT8)(toggle_log + 1);

      GlobalSettingsCheckTrig();

      /* Transmit Peak Picker Data for 100ms */
      if((ZERO != Data_received)&&(FALSE == Demo_mode)&&(PEAK_PICKER_RATE == toggle_log))
      {
    	  Time_in_sec++;
          toggle_log = 0;
          GlobalSettingsPushPeakLog();
           PushFaultLog();
      }
     else if(PEAK_PICKER_RATE == toggle_log)
     {
        toggle_log = 0;
     }
     else
     {
        ; /* Do nothing */
     }

      /* hdudispfapp-AppTask-DB-LLR-010 */
      if(ZERO != toggle)
      {
          /*Transmit Calibration A4825->A429*/
          if (Engine_count_app  > (NUMBEROFENGINES-1))
          {
        	  Engine_count_app = 0;
          }

         OffsideCalibration(Engine_count_app);
         Engine_count_app =(T_UINT8) (Engine_count_app + ONE);

         u32_frame_counter++;
         ForegroundReDraw1();
         PbsGet();                  /* Update the PBS reading. */

        /* Updated as per PR100083*/
         if(TRUE==Long_press)
         {
            INIT_NSC_REQUEST(s_mess);
            s_mess.sID.PID.sid    = EISDSPLYGATEWAY_SID;
            s_mess.u8PaySize      = TWO;
            s_mess.sID.PID.rci = (T_UCHAR)(Du_position & THREE);
            *((T_INT16 *)s_mess.u8PayLoad) = (T_INT16)DU_POSITION_SFC;
            A8251Xmit(&s_mess);
            OsTimeDly(ONE_HUNDRED);
            NVICSystemReset();
         }
         else
         {
          ;/* Do Nothing */
         }

         GrappApp();                /* Execute graphic application (Menu). */
         ForegroundReDraw2();       /* Update all widget positions. */
         ForegroundReDraw3();       /* Draw the widgets. */

         if((ZERO != Data_received))
         {
            GlobalSettingsPush();   /* Backup any global setting changes. */
         }
         else if(ZERO == Data_received)
         {
          /* attempt a repull */
          if(re_pull_cnt >TEN)
          {
             re_pull_cnt = ELEVEN;
             GlobalSettingsPull();
          }
          else
          {

             re_pull_cnt++;
          }
         }
         else
         {
            ; /* Do nothing */
         }
        /* Updated as per PR100083*/
         if (MAX_FRAME_VAL == u32_frame_counter)
         {
            OffsideHeartBeat();
            u32_frame_counter = 0;
         }

         if (ZERO == Pbit_test_result)
         {
            /* Check for Message Control area */
            CheckMsgCtrlArea();
         }
         else
         {
            ; /*Do nothing*/
         }
      }
      else
      {
         /*hdudispfapp-AppTask-DB-LLR-011*/
          /* If we are getting behind, degrade gracefully. */
         while(ZERO != OsSemAccept(Sem_app_task))
         {
               ;/*Kick Watchdog. */
         }
      }
   }
}

/*
 * Function                :  CheckMsgCtrlArea
 *
 * Description             :  This functions checks for Message Control area
 *
 * Formal parameter(s)     :  None
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */
 /* Updated as per PR100083*/
static void CheckMsgCtrlArea(void)
{
   T_PARAM_READING temp = {ZERO};

   T_UINT8 count = ZERO;

   T_UINT16 loop_counter=ZERO;

   static T_BOOL hb_prev_missing = TRUE;

   /*hdudispfapp-CheckMsgCtrlArea-DB-LLR-001*/
   RTDGetParamDdw(0, &temp);  /*Check for heart beat message status */

   if (MISSING == temp.stat)
   {
      U16_message_words[0] |= ONE;
      hb_prev_missing = TRUE;
   }
   else
   {
       /*hdudispfapp-CheckMsgCtrlArea-DB-LLR-016*/
      if((TRUE==hb_prev_missing)&&(TRUE==Du_identified)&&
          (Data_received !=ZERO)&&(TRUE==Splash_done))
      {
         hb_prev_missing = FALSE;
          if(ONE==Du_position)
          {
             OffsideSwitchScreen(Page_num);
             OffsideCoolTimer(Cool_down_select);
             OffsideFuelFlow(Fuel_flow_select);
             GlobalSettingsSetEIU(Active_eiu);
          }
          else
          {
             ;
          }
      }
      else
      {
         ;
      }
       U16_message_words[0] = (T_UINT16)(U16_message_words[0] & ~ONE); /* Do nothing */
   }

   /*hdudispfapp-CheckMsgCtrlArea-DB-LLR-002*/
   /*Check for selected EIU status */
   for(loop_counter=1;loop_counter<=Port1_label_count;loop_counter++)
   {
      RTDGetParam(loop_counter, &temp);

      if (MISSING == temp.stat)
       {
            ++count;
       }
       else
       {
            ; /* Do nothing */
       }
   }

   /*hdudispfapp-CheckMsgCtrlArea-DB-LLR-003*/
   if (Port1_label_count == count)
   {
      U16_message_words[0] |= TWO;
   }
   else
   {
    /* Updated as per PR 100083 */
     U16_message_words[0] = (T_UINT16)(U16_message_words[0] & ~TWO);
   }

   /*hdudispfapp-CheckMsgCtrlArea-DB-LLR-004*/
   if(TRUE == Both_dau_fail)
   {
    U16_message_words[0] |=BIT_15_SET;
   }
   else
   {
    U16_message_words[0] = (T_UINT16)(U16_message_words[0] & ~BIT_15_SET);
   }

   /*hdudispfapp-CheckMsgCtrlArea-DB-LLR-005*/
   if(Can1_msg_cntr>=FOUR)
   {
    Can1_msg_cntr=FOUR;
    U16_message_words[1] |= TWO;
   }
   else
   {
    U16_message_words[1] = (T_UINT16)(U16_message_words[1] & ~TWO);
   }

   /*hdudispfapp-CheckMsgCtrlArea-DB-LLR-006*/
   if(CheckforNewMessages() > 0)
   {
    New_message = TRUE;
    TextBoxOn(Top_menu[5]);
   }
}

/*
 * Function                :  AppU32NOC
 *
 * Description             :  This function process the NOC ARINC message.
 *
 * Formal parameter(s)     :  T_A825_MESSAGE   *s_mess -IN ARINC message
 *                            T_EA825BUS a825_bus - IN A825 bus
 *
 * Return Value            :  T_UINT32 - Returns the error status
 *
 * Assumption              :  None
 *
 */

T_UINT32 AppU32NOC(T_A825_MESSAGE *s_mess, T_EA825BUS a825_bus)
{
   if(A825_1 == a825_bus)
   {
      /*hdudispfapp-AppU32NOC-DB-LLR-001*/
      A429ProcessA825(s_mess);
      return(ZERO);
   }
   else
   {
      /*hdudispfapp-AppU32NOC-DB-LLR-002*/
      OffsideProcessA825NOC(s_mess);
      return(ZERO);
   }
}

/*
 * Function                :  AppU32NSC
 *
 * Description             :  This function process the NSC ARINC message.
 *
 * Formal parameter(s)     :  T_A825_MESSAGE   *smess -IN ARINC message
 *                            T_EA825BUS a825_bus - IN A825 channel
 *
 * Return Value            :  T_UINT32 - Returns the error status
 *
 * Assumption              :  None
 *
 */

T_UINT32 AppU32NSC(T_A825_MESSAGE *s_mess, T_EA825BUS a825_bus)
{
   if(A825_1 == a825_bus)
   {
      /*hdudispfapp-AppU32NSC-DB-LLR-001*/
      GlobalSettingsProcessNSC(s_mess);
      return(ZERO);
   }
   else
   {
      /*hdudispfapp-AppU32NSC-DB-LLR-002*/
      OffsideProcessA825NSC(s_mess);
      return(ZERO);
   }
}

/*
 * Function                :  AppInit
 *
 * Description             :  This function initializes the application task.
 *
 * Formal parameter(s)     :  None
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */
void AppInit(void)
{
   T_UINT16 u16_ctr = ZERO;

   /*hdudispfapp-AppInit-DB-LLR-001*/
   /* Initialize semaphore for application task */
   Sem_app_task = OsSemCreate(SEM_CNT_VAL);

   /*hdudispfapp-AppInit-DB-LLR-002*/
   /* Initialize the stack for run time checks. */
   for(u16_ctr=ZERO; u16_ctr<APP_TASK_STK_SIZE; u16_ctr++)
   {
      App_task_stk[u16_ctr] = STK_DEF_VAL;
   }
   /*hdudispfapp-AppInit-DB-LLR-003*/
   /* create InitTask as the first task to run of RTOS */
   OsTaskCreate(AppTask, NULL, &App_task_stk[APP_TASK_STK_SIZE], APP_TASK_PRIO);
}


