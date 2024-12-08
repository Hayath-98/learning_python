/*
 ******************************************************************************
 * License Information  :  Howell Instruments, Inc.                           *
 *                         "Licensed Software" and "All rights reserved".     *
 ******************************************************************************
 *  File                : hdudispfrtd.c
 *
 *  Description         : This file maintains the repository of A825 incoming data.
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
 *      1.2           Rona B S         10-Oct-2017             100064
 *      1.3           Shruthi M N      13-Oct-2017             100083
 *      1.4           Shruthi M N      30-Oct-2017             100104
 *      1.5           Shilpa A R       09-Nov-2017             100164
 *      1.6           Dhanalakshmi D   21-Jun-2020             100259
 *      1.7           Rona B S         29-Jun-2020             100259
 *
 * Additional References : None
 *
 ******************************************************************************
 */

#include "hdudispfpdidata.h"  /* Extracts the data from NOR flash */
#include "hdudispfucos.h"  /* defines the implementation of uC/OS routines  */
#include "hdudispfparams.h"  /* provides the tags for various parameters and parameter units. */
#include "hdudispfrtd.h"  /* Provide mapping for all A825 incoming parameters */
#include "hdulibbasictypes.h" /* Standard basic data type definitions */
#include "hdudispfoscpu.h"    /* OS function declarations */
/* Updated as per PR 100083 */
#include "hdudispfa429.h"  /* Routines for arinc 429 */

/* Storage for "Real Time Data". */
static T_SRTD_READING Srtd_readings[RTDMAX_PARAM] = {{ZERO,ZERO,RTD_MISSING}};
T_BOOL Both_dau_fail=FALSE;

/* Updated as per PR 100164 */
/*
 * Function                :  RTDGetParam
 *
 * Description             :  This function reads the message from RTD.
 *
 * Formal parameter(s)     :  T_UINT16 a429_tag - IN A429 tag
 *                            T_PARAM_READING *ps_dest - OUT Updated with the arinc parameter.
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */

void RTDGetParam(T_UINT16 a429_tag, T_PARAM_READING *ps_dest)
{
   T_PARAM_READING temp_param = {ZERO};
   T_SRTD_READING  rtd_reading = {ZERO};

   /*hdudispfrtd-RTDGetParam-DB-LLR-001*/
   if(a429_tag >= RTDMAX_PARAM)
   {
      a429_tag = ZERO;
   }
   else
   {
      ; /*Does nothing */
   }

   /*hdudispfrtd-RTDGetParam-DB-LLR-002*/
   OS_ENTER_CRITICAL();

  /*hdudispfrtd-RTDGetParam-DB-LLR-003*/
   rtd_reading = Srtd_readings[a429_tag];
   /*hdudispfrtd-RTDGetParam-DB-LLR-004*/
   OS_EXIT_CRITICAL();

   /*hdudispfrtd-RTDGetParam-DB-LLR-005*/
   /* Updated as per PR 100083 */
   temp_param.fread = rtd_reading.s32reading;
  
   temp_param.r = (T_INT16)((rtd_reading.s32reading*ONE_HUNDRED+FIVE)/TEN);

   switch(rtd_reading.eRTDStat)
   {
     /*hdudispfrtd-RTDGetParam-DB-LLR-006*/
      case RTD_STAT_FAIL:
         temp_param.stat = PARAM_BAD;
      break;

     /*hdudispfrtd-RTDGetParam-DB-LLR-007*/
      case RTD_NCD:
         temp_param.stat = NCD;
      break;

     /*hdudispfrtd-RTDGetParam-DB-LLR-008*/
      case  RTD_MISSING:
         temp_param.stat = MISSING;
      break;

     /*hdudispfrtd-RTDGetParam-DB-LLR-009*/
      case RTD_NORMAL:
         temp_param.stat = PARAM_OK;
      break;

      case RTD_RANGE_ERR:
      /* hdudispfrtd-RTDGetParam-DB-LLR-011 */
       temp_param.stat = RANGE_ERROR;
     break;

     /*hdudispfrtd-RTDGetParam-DB-LLR-010*/
      default:
         temp_param.stat = PARAM_BAD;
      break;
   }
   *ps_dest = temp_param;
}

/* Updated as per PR 100083 */
/*
 * Function                :  RTDGetParamDdw
 *
 * Description             :  This function reads the discrete word.
 *
 * Formal parameter(s)     :  T_UINT16 a429_tag - IN A429 tag
 *                            T_PARAM_READING *ps_dest -OUT - status of message is stored
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */

void RTDGetParamDdw(T_UINT16 a429_tag, T_PARAM_READING *ps_dest)
{
   T_PARAM_READING temp_param = {ZERO};
   T_SRTD_READING  rtd_reading = {ZERO};

   /* hdudispfrtd-RTDGetParamDdw-DB-LLR-001 */
   OS_ENTER_CRITICAL();

   rtd_reading = Srtd_readings[a429_tag];

   OS_EXIT_CRITICAL();
   temp_param.r=(T_INT16)rtd_reading.s32reading;
   switch(rtd_reading.eRTDStat)
   {
      case RTD_STAT_FAIL:
        /* hdudispfrtd-RTDGetParamDdw-DB-LLR-002 */
         temp_param.stat = PARAM_OK;
      break;

      case RTD_NCD:
        /* hdudispfrtd-RTDGetParamDdw-DB-LLR-003 */
         temp_param.stat = NCD;
      break;

      case  RTD_MISSING:
        /* hdudispfrtd-RTDGetParamDdw-DB-LLR-004 */
         temp_param.stat = MISSING;
      break;

      case RTD_NORMAL:
        /* hdudispfrtd-RTDGetParamDdw-DB-LLR-005 */
         temp_param.stat = PARAM_BAD;
      break;

      case RTD_RANGE_ERR:
      /* hdudispfrtd-RTDGetParamDdw-DB-LLR-008 */
       temp_param.stat = RANGE_ERROR;
      break;

      default:
        /* hdudispfrtd-RTDGetParamDdw-DB-LLR-006 */
         temp_param.stat = PARAM_BAD;
      break;
   }
   /* hdudispfrtd-RTDGetParamDdw-DB-LLR-007 */
   *ps_dest = temp_param;
}

/*
 * Function                :  RTDWatchdog
 *
 * Description             :  This routine is called once per mSec to detect
 *                            "MISSING" parameters.
 *
 * Formal parameter(s)     :  None
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */

void RTDWatchdog(void)
{
   T_UINT16 u16_index = ZERO;

   /* hdudispfrtd-RTDWatchdog-DB-LLR-001*/
   for(u16_index=ZERO; u16_index<RTDMAX_PARAM; u16_index++)
   {
      OS_ENTER_CRITICAL();
      if(Srtd_readings[u16_index].usRTimer < RTD_MAX_INTERVAL)
      {
         Srtd_readings[u16_index].usRTimer = (T_UINT16)(Srtd_readings[u16_index].usRTimer + ONE);
      }
      else
      {
         Srtd_readings[u16_index].eRTDStat=RTD_MISSING;
      }
      OS_EXIT_CRITICAL();
   }

   /* hdudispfrtd-RTDWatchdog-DB-LLR-002 */
   OS_ENTER_CRITICAL();
   if(Dau_timer < RTD_MAX_INTERVAL)
   {
      Dau_timer++;
      Both_dau_fail=FALSE;
   }
   else
   {
     Both_dau_fail=TRUE;
   }
   OS_EXIT_CRITICAL();
}

/*
 * Function                :  RTDSetParam
 *
 * Description             :  This routine is called to update RTD coming off the
 *                             A429 bus.
 *
 * Formal parameter(s)     :  T_UINT8 channel - IN - channel number
 *                            T_UINT16 a429_tag - IN - Arinc 429 tag
 *                            T_FLOAT s32_data - IN - Arinc data
 *                            T_RTD_STATUS ertd_stat - OUT - status
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */

void RTDSetParam(T_UINT8 channel, T_UINT16 a429_tag, T_FLOAT s32_data, T_RTD_STATUS ertd_stat)
{
   /* Updated as per PR 100083 */

    /* hdudispfrtd-RTDSetParam-DB-LLR-002*/
   OS_ENTER_CRITICAL();

    /* hdudispfrtd-RTDSetParam-DB-LLR-003*/
   Srtd_readings[a429_tag].usRTimer = ZERO;

   /* hdudispfrtd-RTDSetParam-DB-LLR-004*/
   if(a429_tag!=ZERO)
   {
      if (BNR==A429_data[channel][a429_tag-1].type)
      {
         if((s32_data < A429_data[channel][a429_tag-1].min_val) ||
               (s32_data > A429_data[channel][a429_tag-1].max_val))
         {
            ertd_stat=RTD_RANGE_ERR;
         }
         else
         {
          ; /* Do nothing */
         }

      }
   }

   /* hdudispfrtd-RTDSetParam-DB-LLR-005*/
   Srtd_readings[a429_tag].s32reading = s32_data;
   Srtd_readings[a429_tag].eRTDStat= ertd_stat;
   OS_EXIT_CRITICAL();
}

/*
 * Function                :  RTDInit
 *
 * Description             :  This routine is called to initialize RTD coming off the
 *                             A429 bus
 *
 * Formal parameter(s)     :  None
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */

void RTDInit(void)
{
   T_UINT16 u16_index = ZERO;

   /* hdudispfrtd-RTDInit-DB-LLR-001*/
   for(u16_index=ONE; u16_index<RTDMAX_PARAM; u16_index++)
   {
      OS_ENTER_CRITICAL();
      Srtd_readings[u16_index].usRTimer = RTD_MAX_INTERVAL;
      OS_EXIT_CRITICAL();
   }
}

