/*
 ******************************************************************************
 * License Information  :  Howell Instruments, Inc.                           *
 *                         "Licensed Software" and "All rights reserved".     *
 ******************************************************************************
 *  File                : hdudispfrtd.h
 *
 *  Description         : This file defines structure, enum of A825 incomming data.
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
 *      1.1           Shilpa A R       11-Sep-2017             100064
 *      1.2           Shruthi M N      13-Oct-2017             100083
 *      1.3           Shruthi M N      30-Oct-2017             100104
 *      1.4           Dhanalakshmi D   21-Jun-2020             100259
 *      1.5           Rona B S		   29-Jun-2020             100259
 *      1.6           Dhanalakshmi     20-Mar-2021             100331
 *      1.7           Dhanalakshmi     20-Mar-2021             100331
 *      1.8           Chaithra J       04-Mar-2022             100368
 *
 * Additional References : None
 *
 ******************************************************************************
 */

#ifndef _HDUDISPFRTD_H_
#define _HDUDISPFRTD_H_

#include "hdudispfparams.h"  /* provides the tags for various parameters and parameter units */

/* Max time (mSec) between data updates.*/
#define RTD_MAX_INTERVAL   2000
#define RTD_MAX_INTERVAL_SCU 10000

#define RTDMAX_PARAM       60
#define SCU_RTDMAX_PARAM   3

typedef enum
{
   RTD_STAT_FAIL = 0,
   RTD_NCD       = 1,
   RTD_MISSING   = 2,
   RTD_NORMAL    = 3,
   RTD_RANGE_ERR = 4
}  T_RTD_STATUS;

#define A429EX_OT_MASK     0x01U
#define A429EX_OP_MASK     0x02U
#define A429EX_N1_MASK     0x04U
#define A429EX_NP_MASK     0x08U
#define A429EX_NR_MASK     0x10U
#define A429EX_Q_MASK      0x20U
#define A429EX_TOT_MASK    0x40U

/* TYPES */
/* All A825 channel readings have this form.  */
typedef struct
{
   T_FLOAT                s32reading;    /* Reading to be reported.  */
   T_UINT16               usRTimer;         /* Reading timer for Param. "MISSING".*/
   T_RTD_STATUS           eRTDStat;       /* Status comming from the 429 bus.*/
}  T_SRTD_READING;

typedef enum
{
   A429TAG_RESERVED=0,
   A429TAGBUS_VOLTAGE,
   A429TAG_EOP,
   A429TAG_EOT,
   A429TAGFUEL_FLOW,
   A429TAGFUEL_QUANTITY,
   A429TAGGEN_AMPS,
   A429TAG_N1,
   A429TAG_N2,
   A429TAG_NR,
   A429TAG_OAT,
   A429TAG_TORQUE,
   A429TAG_TOT,
   /* Updated as per PR 100083 */
   A429TAG_CAUTIONWARNINGS_0,
   A429TAG_CAUTIONWARNINGS_1,
   A429TAG_CAUTIONWARNINGS_2,
   A429TAG_CAUTIONWARNINGS_3,
   A429TAG_CAUTIONWARNINGS_4,
   A429TAG_CAUTIONWARNINGS_5,
   A429TAG_CRC,
   A429TAG_INFORMATION,
   A429TAGEFD_DISCRETE,
   A429TAG_EXCEEDANCES,
   A429TAG_HEARTBEAT,
   A429TAG_LASTPARAM
}  T_EA429_TAG;
extern T_BOOL Both_dau_fail;

extern void RTDGetParam(T_UINT16 a429_tag, T_PARAM_READING *ps_dest);
extern void RTDSetParam(T_UINT8 channel, T_UINT16 a429_tag,
   T_FLOAT s32_data, T_RTD_STATUS ertd_stat);
extern void RTDWatchdog(void);
extern void RTDInit(void);
extern void RTDGetParamDdw(T_UINT16 a429_tag, T_PARAM_READING *ps_dest);


#endif /* _HDUDISPFRTD_H_ */
