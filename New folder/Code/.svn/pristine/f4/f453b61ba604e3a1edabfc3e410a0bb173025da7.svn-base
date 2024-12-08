/*
 ******************************************************************************
 * License Information  :  Howell Instruments, Inc.                           *
 *                         "Licensed Software" and "All rights reserved".     *
 ******************************************************************************
 *  File                : hdudispflmsscu.c
 *
 *  Description         : This file processes LMS SCU labels, sends fault log to NVRAM.
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
 *  Author(s)           : Dhanalakshmi D
 *
 *  Version History     :
 *
 * <Version No.>     <Author>          <Date>         <Problem Report No.>
 *
 *      1.1         Dhanalakshmi       20-Mar-2021             100331
 *      1.2         Dhanalakshmi       20-Mar-2021             100331
 *      1.3         Dhanalakshmi       03-Apr-2021             100330
 *      1.4         Dhanalakshmi       16-Apr-2021             100339
 *      1.5         Dhanalakshmi       24-Apr-2021             100344
 *      1.6         Dhanalakshmi       13-May-2021             100350
 *      1.7         Chaithra J         04-Mar-2022             100368
 * Additional References : None
 *
 *****************************************************************************
 */

#include "hdudispflmsscu.h"  /* SCU rtd processing and error codes  */
#include "hdudispfa429.h"  /* Routines for arinc 429 */
#include "hdulibbasictypes.h"      /* Standard basic data type definitions */
#include "hdudispfgrapp.h"           /* routines for all graph */
#include "hdudispfdauprofile.h"     /* defines the constants for ARINC 825  Message Traffic.*/
#include "hdudispfarinc825.h" /* Define the structure for an ARINC 825 Message. */
#include "hdudispftimer.h"         /* Consistency Check*/
#include "hdudispfglobalsettings.h" /* Routines to read and write data to NVRAM  */
#include "hdudispfapp.h"             /* contains Engine Information System application */

static void StartProcessingFaultLog(T_UINT8 fault_type, T_UINT8 fault, T_UINT8 arr_index);
static void StopProcessingFaultLog(T_UINT8 arr_index);
static void GetFaultParamData(T_UINT8 arr_index);

/* Storage for "Real Time Data" from LMS SCU (Signal Conditioning Unit). */
static T_SRTD_READING Scu_rtd_readings[SCU_RTDMAX_PARAM] = {{ZERO,ZERO,RTD_MISSING}};

T_FAULT_DATA Fault_data[6] = \
{{0276, {0, PARAM_OK, 0}}, {050, {0, PARAM_OK, 0}}, {0344, {0, PARAM_OK, 0}},\
{0317, {0, PARAM_OK, 0}}, {0265, {0, PARAM_OK, 0}}, {0103, {0, PARAM_OK, 0}}};
T_UINT16 Scu_error_code =0;

static T_FAULT_DATA Previous_fault_data[6]= \
{{0276, {0, PARAM_OK, 0}}, {050, {0, PARAM_OK, 0}}, {0344, {0, PARAM_OK, 0}}, \
 {0317, {0, PARAM_OK, 0}}, {0265, {0, PARAM_OK, 0}}, {0103, {0, PARAM_OK, 0}}};

T_FLOAT N1_value = 0.0f;
static T_UINT8 Fault_set=0;
static T_UINT8 Arinc_fault_set=0;
static T_UINT8 Ssm_ncd =ZERO;
static T_BOOL Stop_log = FALSE;
static T_BOOL Stop_ft_log = FALSE;
T_TIMER Fault_timer[6] = {0};
static T_TIMER Fault_timer_mirror[6] = {0};
static T_BOOL Param_ssm_validity[6] = {FALSE, FALSE, FALSE, FALSE, FALSE, FALSE};
T_FAULT_LOG Fault_log_structure[MAX_FAULT_LOG] =\
		   {{0,0,NO_ERROR,0,0,{0,0,0,0,0,0},FALSE,0,0, {FALSE,FALSE,FALSE,FALSE,FALSE,FALSE}, \
			   FALSE,FALSE,FALSE,FALSE,TRUE,{FALSE,FALSE,FALSE,FALSE,FALSE,FALSE}},
			{0,0,NO_ERROR,0,0,{0,0,0,0,0,0},FALSE,0,0, {FALSE,FALSE,FALSE,FALSE,FALSE,FALSE}, \
			   FALSE,FALSE,FALSE,FALSE,TRUE,{FALSE,FALSE,FALSE,FALSE,FALSE,FALSE}},
			{0,0,NO_ERROR,0,0,{0,0,0,0,0,0},FALSE,0,0, {FALSE,FALSE,FALSE,FALSE,FALSE,FALSE}, \
			   FALSE,FALSE,FALSE,FALSE,TRUE,{FALSE,FALSE,FALSE,FALSE,FALSE,FALSE}},
			{0,0,NO_ERROR,0,0,{0,0,0,0,0,0},FALSE,0,0, {FALSE,FALSE,FALSE,FALSE,FALSE,FALSE}, \
			   FALSE,FALSE,FALSE,FALSE,TRUE,{FALSE,FALSE,FALSE,FALSE,FALSE,FALSE}},
			{0,0,NO_ERROR,0,0,{0,0,0,0,0,0},FALSE,0,0, {FALSE,FALSE,FALSE,FALSE,FALSE,FALSE}, \
			   FALSE,FALSE,FALSE,FALSE,TRUE,{FALSE,FALSE,FALSE,FALSE,FALSE,FALSE}},
			{0,0,NO_ERROR,0,0,{0,0,0,0,0,0},FALSE,0,0, {FALSE,FALSE,FALSE,FALSE,FALSE,FALSE}, \
			   FALSE,FALSE,FALSE,FALSE,TRUE,{FALSE,FALSE,FALSE,FALSE,FALSE,FALSE}},
			{0,0,NO_ERROR,0,0,{0,0,0,0,0,0},FALSE,0,0, {FALSE,FALSE,FALSE,FALSE,FALSE,FALSE}, \
			   FALSE,FALSE,FALSE,FALSE,TRUE,{FALSE,FALSE,FALSE,FALSE,FALSE,FALSE}},
			{0,0,NO_ERROR,0,0,{0,0,0,0,0,0},FALSE,0,0, {FALSE,FALSE,FALSE,FALSE,FALSE,FALSE}, \
			   FALSE,FALSE,FALSE,FALSE,TRUE,{FALSE,FALSE,FALSE,FALSE,FALSE,FALSE}},
			{0,0,NO_ERROR,0,0,{0,0,0,0,0,0},FALSE,0,0, {FALSE,FALSE,FALSE,FALSE,FALSE,FALSE}, \
			   FALSE,FALSE,FALSE,FALSE,TRUE,{FALSE,FALSE,FALSE,FALSE,FALSE,FALSE}},
			{0,0,NO_ERROR,0,0,{0,0,0,0,0,0},FALSE,0,0, {FALSE,FALSE,FALSE,FALSE,FALSE,FALSE}, \
			   FALSE,FALSE,FALSE,FALSE,TRUE,{FALSE,FALSE,FALSE,FALSE,FALSE,FALSE}}};
/* no of fault logs backup to NVRAM. */
T_UINT16  Flt_id_count = 0;

/*
 * Function                :  ScuRTDGetParam
 *
 * Description             :  This function reads the message from RTD.
 *
 * Formal parameter(s)     :  T_UINT16 rtd_tag - IN scu index
 *                            T_PARAM_READING *ps_dest - OUT Updated with the arinc parameter.
 *                            T_A429_DATA_TYPE a429_type - IN A429 type (BNR/DDW)
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */

void ScuRTDGetParam(T_UINT16 rtd_tag, T_PARAM_READING *ps_dest, T_A429_DATA_TYPE a429_type)
{
   T_PARAM_READING temp_param = {ZERO};
   T_SRTD_READING  rtd_reading = {ZERO};

   /*hdudispflmsscu-ScuRTDGetParam-DB-LLR-001*/
   if(rtd_tag > SCU_RTDMAX_PARAM)
   {
	   rtd_tag = ZERO;
   }
   else
   {
      ; /*Does nothing */
   }

   /*hdudispflmsscu-ScuRTDGetParam-DB-LLR-002*/
   OS_ENTER_CRITICAL();

  /*hdudispflmsscu-ScuRTDGetParam-DB-LLR-003*/
   rtd_reading = Scu_rtd_readings[rtd_tag];
   /*hdudispflmsscu-ScuRTDGetParam-DB-LLR-004*/
   OS_EXIT_CRITICAL();

   /*hdudispflmsscu-ScuRTDGetParam-DB-LLR-005*/
   if(BNR == a429_type)
   {
       temp_param.fread = rtd_reading.s32reading;

       temp_param.r = (T_INT16)((rtd_reading.s32reading*ONE_HUNDRED+FIVE)/TEN);
   }
   else if(DDW == a429_type)
   {
	   temp_param.r=(T_INT16)rtd_reading.s32reading;
   }
   else
   {
	   ; /* Do Nothing */
   }
   switch(rtd_reading.eRTDStat)
   {
     /*hdudispflmsscu-ScuRTDGetParam-DB-LLR-006*/
      case RTD_STAT_FAIL:
         temp_param.stat = PARAM_BAD;
      break;

     /*hdudispflmsscu-ScuRTDGetParam-DB-LLR-007*/
      case RTD_NCD:
         temp_param.stat = NCD;
      break;

     /*hdudispflmsscu-ScuRTDGetParam-DB-LLR-008*/
      case  RTD_MISSING:
    	  if(ONE == (Fault_set>> TWO & ONE))
    	  {
            temp_param.stat = MISSING;
    	  }
    	  else
    	  {

    	  }
      break;

     /*hdudispflmsscu-ScuRTDGetParam-DB-LLR-009*/
      case RTD_NORMAL:
         temp_param.stat = PARAM_OK;
      break;

      case RTD_RANGE_ERR:
      /* hdudispflmsscu-ScuRTDGetParam-DB-LLR-010 */
       temp_param.stat = RANGE_ERROR;
     break;

     /*hdudispflmsscu-ScuRTDGetParam-DB-LLR-011*/
      default:
         temp_param.stat = PARAM_BAD;
      break;
   }
   *ps_dest = temp_param;
   /*hdudispflmsscu-ScuRTDGetParam-DB-LLR-012*/
   /* Display a red "X" over the Fuel Quantity Gauge for the following conditions: */
   /* 1. LMS SCU System Status errors are set */
   /* 2. LMS SCU probe faults are set */
   /* 3. invalid SSM or no data on ARINC 429 Label 250, 265 or 272 for longer than 10 seconds */
   if(((ZERO != Fault_set) && (ZERO == Ssm_ncd)) ||
	 ((ONE == ((Scu_fty_offset_flag >> TWO) & ONE)) ||
	 (ONE == ((Scu_fty_offset_flag >> THREE) & ONE))))
   {
	   Scu_rtd_readings[ZERO].eRTDStat = RTD_STAT_FAIL;
   }
   else if((ZERO != Fault_set) && (ZERO != Ssm_ncd) &&
		  (RANGE_ERROR != temp_param.stat))
   {
	   Scu_rtd_readings[ZERO].eRTDStat = RTD_NCD;
   }
   else
   {
	   ;
   }
}

/*
 * Function                :  ScuRTDWatchdog
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

void ScuRTDWatchdog(void)
{
   T_UINT16 u16_index = ZERO;

   /* hdudispflmsscu-ScuRTDWatchdog-DB-LLR-001*/
   for(u16_index=ZERO; u16_index<SCU_RTDMAX_PARAM; u16_index++)
   {
      OS_ENTER_CRITICAL();
      if(Scu_rtd_readings[u16_index].usRTimer < RTD_MAX_INTERVAL_SCU)
      {
         Scu_rtd_readings[u16_index].usRTimer =
               (T_UINT16)(Scu_rtd_readings[u16_index].usRTimer + ONE);
      }
      else
      {
         Scu_rtd_readings[u16_index].eRTDStat=RTD_MISSING;
      }
      if(Scu_timer[u16_index] < RTD_MAX_INTERVAL_SCU)
      {
    	  Scu_timer[u16_index]++;
      }
      else
      {
    	  /* if labels 0250, 0247, 0272 are not received for 10 seconds, set status as missing */
    	  Scu_rtd_readings[ZERO].eRTDStat=RTD_MISSING;
      }
      OS_EXIT_CRITICAL();
   }
}


/*
 * Function                :  ScuRTDSetParam
 *
 * Description             :  This routine is called to update RTD coming off the
 *                             A429 bus from LMS SCU and set the scu arinc error 01.
 *
 * Formal parameter(s)     :  T_UINT8 channel - IN - channel number
 *                            T_UINT16 a429_tag - IN - Arinc 429 tag
 *                            T_UINT8 rtd_tag - IN scu index
 *                            T_FLOAT s32_data - IN - Arinc data
 *                            T_RTD_STATUS ertd_stat - OUT - status
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */

void ScuRTDSetParam(T_UINT8 channel, T_UINT16 a429_tag, T_UINT8 rtd_tag,
					T_FLOAT s32_data, T_RTD_STATUS ertd_stat)
{
    /* hdudispflmsscu-ScuRTDSetParam-DB-LLR-001*/
   OS_ENTER_CRITICAL();

    
   Scu_rtd_readings[rtd_tag].usRTimer = ZERO;
   /* hdudispflmsscu-ScuRTDSetParam-DB-LLR-004*/
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

   /* hdudispflmsscu-ScuRTDSetParam-DB-LLR-002*/
    if((ZERO == rtd_tag)&& (THREE != ertd_stat))
    {
 	   Arinc_fault_set = Arinc_fault_set | ONE;
    	  if((ONE == ertd_stat) &&
    		 (RTD_RANGE_ERR != ertd_stat))
    	  {
    		 Ssm_ncd = Ssm_ncd | ONE;
       }
    	  else
    	  {
    		Ssm_ncd = Ssm_ncd & 0xFE;
    	  }
    }
    /* hdudispflmsscu-ScuRTDSetParam-DB-LLR-003*/
    else if((ZERO == rtd_tag)&& (THREE == ertd_stat))
    {
 	   Arinc_fault_set = Arinc_fault_set & 0xFE;
 	   Ssm_ncd = Ssm_ncd & 0xFE;
    }
    else
    {
 	   ; /* Do Nothing */
    }

   /* hdudispflmsscu-ScuRTDSetParam-DB-LLR-005*/
   Scu_rtd_readings[rtd_tag].s32reading = s32_data;
   Scu_rtd_readings[rtd_tag].eRTDStat= ertd_stat;
   OS_EXIT_CRITICAL();
}

/*
 * Function                :  ScuRTDInit
 *
 * Description             :  This routine is called to initialize RTD coming off the
 *                             A429 bus from LMS SCU
 *
 * Formal parameter(s)     :  None
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */

void ScuRTDInit(void)
{
   T_UINT16 u16_index = ZERO;

   /* hdudispflmsscu-ScuRTDInit-DB-LLR-001*/
   for(u16_index=ONE; u16_index<SCU_RTDMAX_PARAM; u16_index++)
   {
      OS_ENTER_CRITICAL();
      Scu_rtd_readings[u16_index].usRTimer = RTD_MAX_INTERVAL_SCU;
      OS_EXIT_CRITICAL();
   }
}



/*
 * Function                :  FaultTimer
 *
 * Description             :  This function starts the fault timer when ssm is invalid
 *
 * Formal parameter(s)     :  T_UINT8 index - IN fault timer index
 *
 * Return Value            :  T_BOOL - Returns TRUE OR FALSE
 *
 * Assumption              :  None
 *
 */

static T_BOOL FaultTimer(T_UINT8 index)
{
   static T_BOOL init_var = TRUE;

  /* hdudispflmsscu-FaultTimer-DB-LLR-001 */
   if (TRUE == init_var)
   {
      TimerInstall(&Fault_timer_mirror[index]);
      TimerInstall(&Fault_timer[index]);
      Fault_timer[index] = ZERO;
      TimerPreset(&Fault_timer_mirror[index],
           (T_INT32)Fault_timer[index]);
      init_var = FALSE;
   }
   else
   {
      ; /* Do nothing */
   }
   /*hdudispflmsscu-FaultTimer-DB-LLR-002*/
   if (Fault_timer[index] > TIME_FRAME)
   {
       return TRUE;
   }
   else
   {
      ; /* Do nothing */
   }
  /* hdudispflmsscu-FaultTimer-DB-LLR-003*/
   return FALSE;
}


/*
 * Function                :  ProcessLmsScuSysStatusErr
 *
 * Description             :  This function process the LMS SCU system status error
 *
 * Formal parameter(s)     :  T_FLOAT data - IN SCU data.
 *                            T_UINT8 status IN SCU SSM.
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */
void ProcessLmsScuSysStatusErr(T_UINT32 data, T_UINT8 status)
{
    T_BOOL err_stat = FALSE;
    static T_UINT8 index[5] ={ZERO};
    static T_BOOL index_flag[5] ={FALSE};
    T_UINT8 fault_index =ZERO;
    /*hdudispflmsscu-ProcessLmsScuSysStatusErr-DB-LLR-001*/
    for(fault_index = ZERO; fault_index < MAX_FAULT_LOG; fault_index++)
    {
    	if(FALSE == Fault_log_structure[fault_index].data_present)
    	{
    		break;
    	}
    	else
    	{
    		; /* Do Nothing */
    	}
    }
    /* process the SCU System status errors only when SSM is valid */
    /* SSM 3 and 0 are considered as Normal Operation */
    if((THREE == status) || (ZERO == status))
    {
	    /*hdudispflmsscu-ProcessLmsScuSysStatusErr-DB-LLR-002*/
    	Arinc_fault_set = Arinc_fault_set & 0xFD;
    	Ssm_ncd = Ssm_ncd & 0xFD;
		/*hdudispflmsscu-ProcessLmsScuSysStatusErr-DB-LLR-003*/
     	/* Power Supply Fault */
        if((T_UINT32)ONE ==(((T_UINT32) data>> NINE) & (T_UINT32) HEX_ONE))
        {
			err_stat = TRUE;
			/*
			 * When Power Supply Fault bit is set to 1 and N1 >= 55%,
			 * display REDX, display the Msg SYSTEM STATUS ERROR 01 and
			 * Log SYSTEM STATUS ERROR 01 fault to NVM
			 */
        	if (M_ENGSTART <= N1_value)
		    {
				U16_message_words[1] |= 32768;
				/*hdudispflmsscu-ProcessLmsScuSysStatusErr-DB-LLR-004*/
				if(FALSE == index_flag[0])
				{
				index[0] = fault_index;
				index_flag[0] = TRUE;
				}
				else
				{
					;
				}
				/*hdudispflmsscu-ProcessLmsScuSysStatusErr-DB-LLR-005*/
				GetFaultParamData(index[0]);
				 /*hdudispflmsscu-ProcessLmsScuSysStatusErr-DB-LLR-006*/
				if(FALSE == Fault_log_structure[index[0]].initial_fault_index)
				{
				   StartProcessingFaultLog(SYS_STATUS_ERROR, POWER_SUPPLY_FAULT, index[0]);

				 /*hdudispflmsscu-ProcessLmsScuSysStatusErr-DB-LLR-007*/
				   if((TEN > fault_index) && (FALSE == Stop_log))
					{
						fault_index++;
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
			}
        	else
        	{
			    /*hdudispflmsscu-ProcessLmsScuSysStatusErr-DB-LLR-040*/
				
        		/*
        		 * When Power Supply Fault bit is set to 1 and N1 < 55%,
        		 * Suppress Fault log and SYSTEM STATUS ERROR 01 Msg
        		 */
      	      if((TRUE == Fault_log_structure[index[0]].fault_active_flag) &&
      	         (TRUE == index_flag[0]))
      	      {
      	    	  StopProcessingFaultLog(index[0]);
      	    	  index_flag[0] = FALSE;
      	      }
      	      else
      	      {
      		     ;
      	      }
        		U16_message_words[1] = U16_message_words[1] & 32767;
        	}
	    }
		/*hdudispflmsscu-ProcessLmsScuSysStatusErr-DB-LLR-008*/
        else
        {
	      if((TRUE == Fault_log_structure[index[0]].fault_active_flag) &&
	         (TRUE == index_flag[0]))
	      {
	    	  StopProcessingFaultLog(index[0]);
	    	  index_flag[0] = FALSE;
	      }
	      else
	      {
		     ;
	      }
		  /*hdudispflmsscu-ProcessLmsScuSysStatusErr-DB-LLR-009*/
	      U16_message_words[1] = U16_message_words[1] & 32767;
        }
    /*hdudispflmsscu-ProcessLmsScuSysStatusErr-DB-LLR-010*/
   /* APP CRC Error */
   if((T_UINT32)ONE ==(((T_UINT32) data >>TWELVE)& (T_UINT32) HEX_ONE))
   {
	   err_stat = TRUE;
	   U16_message_words[2] |= 1;
	   /*hdudispflmsscu-ProcessLmsScuSysStatusErr-DB-LLR-011*/
       if(FALSE == index_flag[1])
       {
          index[1] = fault_index;
          index_flag[1] = TRUE;
       }
       else
       {
       	;
       }
	   /*hdudispflmsscu-ProcessLmsScuSysStatusErr-DB-LLR-012*/
       GetFaultParamData(index[1]);
	   /*hdudispflmsscu-ProcessLmsScuSysStatusErr-DB-LLR-013*/
       if(FALSE == Fault_log_structure[index[1]].initial_fault_index)
       {
    	   StartProcessingFaultLog(SYS_STATUS_ERROR, APP_CRC_ERROR, index[1]);
          /*hdudispflmsscu-ProcessLmsScuSysStatusErr-DB-LLR-014*/
    	   if((TEN > fault_index) && (FALSE == Stop_log))
   	      {
          	  fault_index++;
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
   }
   /*hdudispflmsscu-ProcessLmsScuSysStatusErr-DB-LLR-015*/
   else
   {
	   U16_message_words[2] = U16_message_words[2] & 65534;
	   /*hdudispflmsscu-ProcessLmsScuSysStatusErr-DB-LLR-016*/
	      if((TRUE == Fault_log_structure[index[1]].fault_active_flag) &&
	 	     (TRUE == index_flag[1]))
	      {
	    	  StopProcessingFaultLog(index[1]);
	    	  index_flag[1] = FALSE;
	      }
	      else
	      {
		     ;
	      }
   }
   /*hdudispflmsscu-ProcessLmsScuSysStatusErr-DB-LLR-017*/
   /* MFG CRC Error */
   if((T_UINT32)ONE ==(((T_UINT32) data>> THIRTEEN) & (T_UINT32) HEX_ONE))
   {
      U16_message_words[2] |= 2;
      err_stat = TRUE;
	  /*hdudispflmsscu-ProcessLmsScuSysStatusErr-DB-LLR-018*/
      if(FALSE == index_flag[2])
      {
      index[2] = fault_index;
      index_flag[2] = TRUE;
      }
      else
      {
      	;
      }
	  /*hdudispflmsscu-ProcessLmsScuSysStatusErr-DB-LLR-019*/
      GetFaultParamData(index[2]);
	  /*hdudispflmsscu-ProcessLmsScuSysStatusErr-DB-LLR-039*/
      if(FALSE == Fault_log_structure[index[2]].initial_fault_index)
      {
    	  StartProcessingFaultLog(SYS_STATUS_ERROR, MFG_CRC_ERROR, index[2]);
        /*hdudispflmsscu-ProcessLmsScuSysStatusErr-DB-LLR-020*/
    	  if((TEN > fault_index) && (FALSE == Stop_log))
  	      {
         	  fault_index++;
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
   }
   /*hdudispflmsscu-ProcessLmsScuSysStatusErr-DB-LLR-021*/
   else
   {
	   U16_message_words[2] = U16_message_words[2] & 65533;
	   /*hdudispflmsscu-ProcessLmsScuSysStatusErr-DB-LLR-022*/
	      if((TRUE == Fault_log_structure[index[2]].fault_active_flag) &&
	 	     (TRUE == index_flag[2]))
	      {
	    	  StopProcessingFaultLog(index[2]);
	    	  index_flag[2] = FALSE;
	      }
	      else
	      {
		     ;
	      }
   }
   /*hdudispflmsscu-ProcessLmsScuSysStatusErr-DB-LLR-023*/
   /* Configuration Table CRC Error */
   if((T_UINT32)ONE ==(((T_UINT32) data>> FORTEEN) & (T_UINT32) HEX_ONE))
   {
       U16_message_words[2] |= 4;
       err_stat = TRUE;
	   /*hdudispflmsscu-ProcessLmsScuSysStatusErr-DB-LLR-024*/
       if(FALSE == index_flag[3])
       {
       index[3] = fault_index;
       index_flag[3] = TRUE;
       }
       else
       {
       	;
       }
	   /*hdudispflmsscu-ProcessLmsScuSysStatusErr-DB-LLR-025*/
       GetFaultParamData(index[3]);
	   /*hdudispflmsscu-ProcessLmsScuSysStatusErr-DB-LLR-026*/
       if(FALSE == Fault_log_structure[index[3]].initial_fault_index)
       {
    	   StartProcessingFaultLog(SYS_STATUS_ERROR, CONFIG_TABLE_CRC_ERROR, index[3]);
          /*hdudispflmsscu-ProcessLmsScuSysStatusErr-DB-LLR-027*/
    	   if((TEN > fault_index) && (FALSE == Stop_log))
   	      {
          	  fault_index++;
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
   }
   /*hdudispflmsscu-ProcessLmsScuSysStatusErr-DB-LLR-028*/
   else
   {
	   U16_message_words[2] = U16_message_words[2] & 65531;
	   /*hdudispflmsscu-ProcessLmsScuSysStatusErr-DB-LLR-029*/
	      if((TRUE == Fault_log_structure[index[3]].fault_active_flag) &&
	 	     (TRUE == index_flag[3]))
	      {
	    	  StopProcessingFaultLog(index[3]);
	    	  index_flag[3] = FALSE;
	      }
	      else
	      {
		     ;
	      }
   }
   /*hdudispflmsscu-ProcessLmsScuSysStatusErr-DB-LLR-030*/
   /* Invalid Tank Table */
   if((T_UINT32)ONE ==(((T_UINT32) data>> FIFTEEN) & (T_UINT32) HEX_ONE))
   {
      U16_message_words[2] |= 8;
      err_stat = TRUE;
	  /*hdudispflmsscu-ProcessLmsScuSysStatusErr-DB-LLR-031*/
      if(FALSE == index_flag[4])
      {
      index[4] = fault_index;
      index_flag[4] = TRUE;
      }
      else
      {
      	;
      }
	  /*hdudispflmsscu-ProcessLmsScuSysStatusErr-DB-LLR-032*/
      GetFaultParamData(index[4]);
	  /*hdudispflmsscu-ProcessLmsScuSysStatusErr-DB-LLR-033*/
      if(FALSE == Fault_log_structure[index[4]].initial_fault_index)
      {
    	  StartProcessingFaultLog(SYS_STATUS_ERROR, INVALID_TANK_TABLE, index[4]);
       /*hdudispflmsscu-ProcessLmsScuSysStatusErr-DB-LLR-034*/
    	  if((TEN > fault_index) && (FALSE == Stop_log))
  	      {
         	  fault_index++;
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
   }
   /*hdudispflmsscu-ProcessLmsScuSysStatusErr-DB-LLR-035*/
   else
   {
	   U16_message_words[2] = U16_message_words[2] & 65527;
	   /*hdudispflmsscu-ProcessLmsScuSysStatusErr-DB-LLR-036*/
	      if((TRUE == Fault_log_structure[index[0]].fault_active_flag) &&
	 	     (TRUE == index_flag[4]))
	      {
	    	  StopProcessingFaultLog(index[4]);
	    	  index_flag[4] = FALSE;
	      }
	      else
	      {
		     ;
	      }
   }
    }
	/*hdudispflmsscu-ProcessLmsScuSysStatusErr-DB-LLR-037*/
    else
    {
    	Arinc_fault_set = Arinc_fault_set | TWO;
    	if(ONE == status)
    	{
    		Ssm_ncd = Ssm_ncd | TWO;
    	}
    	else
    	{
    		Ssm_ncd = Ssm_ncd & 0xFD;
    	}
    }

    /* Display a red "X" over the Fuel Quantity Gauge if LMS SCU System  */
    /* Status Error is received */
   /*hdudispflmsscu-ProcessLmsScuSysStatusErr-DB-LLR-038*/
    if(TRUE == err_stat)
    {
    	Fault_set = Fault_set | ONE;
    }
    else
    {
    	Fault_set = Fault_set & 0xFE;
    }
}


/*
 * Function                :  ProcessLmsScuProbeErr
 *
 * Description             :  This function process the LMS SCU probe errors
 *
 * Formal parameter(s)     :  T_FLOAT data - IN SCU data.
 *                            T_UINT8 status - IN SCU SSM.
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */
void ProcessLmsScuProbeErr(T_UINT32 data, T_UINT8 status)
{
    T_BOOL err_stat = FALSE;
    static T_UINT8 index[4] ={ZERO};
    static T_BOOL index_flag[4] ={FALSE};
    T_UINT8 fault_index =ZERO;

    /*hdudispflmsscu-ProcessLmsScuProbeErr-DB-LLR-001*/
    for(fault_index = ZERO; fault_index < MAX_FAULT_LOG; fault_index++)
    {
    	if(FALSE == Fault_log_structure[fault_index].data_present)
    	{
    		break;
    	}
    	else
    	{
    		; /* Do Nothing */
    	}
    }
    /* process the SCU probe errors only when SSM is valid */
    /* SSM 3 and 0 are considered as Normal Operation */
    if((THREE == status) || (ZERO == status))
    {
	     /*hdudispflmsscu-ProcessLmsScuProbeErr-DB-LLR-002*/
    	 Arinc_fault_set = Arinc_fault_set & 0xFB;
    	 Ssm_ncd = Ssm_ncd & 0xFB;
		/*hdudispflmsscu-ProcessLmsScuProbeErr-DB-LLR-003*/
    	/* Missing Probe Error */
     if((T_UINT32)ONE ==(((T_UINT32) data>> ZERO) & (T_UINT32) HEX_ONE))
     {
      U16_message_words[1] |= 4096;
      err_stat = TRUE;
	  /*hdudispflmsscu-ProcessLmsScuProbeErr-DB-LLR-004*/
      if(FALSE == index_flag[0])
      {
      index[0] = fault_index;
      index_flag[0] = TRUE;
      }
      else
      {
      	;
      }
	  /*hdudispflmsscu-ProcessLmsScuProbeErr-DB-LLR-005*/
      GetFaultParamData(index[0]);
	  /*hdudispflmsscu-ProcessLmsScuProbeErr-DB-LLR-006*/
      if(FALSE == Fault_log_structure[index[0]].initial_fault_index)
      {
    	  StartProcessingFaultLog(PROBE_ERROR, MISSING_PROBE_ERROR, index[0]);
       /*hdudispflmsscu-ProcessLmsScuProbeErr-DB-LLR-007*/
    	  if((TEN > fault_index) && (FALSE == Stop_log))
  	      {
         	  fault_index++;
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
   }
   /*hdudispflmsscu-ProcessLmsScuProbeErr-DB-LLR-008*/
   else
   {
	   U16_message_words[1] = U16_message_words[1] & 61439;
	   /*hdudispflmsscu-ProcessLmsScuProbeErr-DB-LLR-009*/
	      if((TRUE == Fault_log_structure[index[0]].fault_active_flag) &&
	 	     (TRUE == index_flag[0]))
	      {
	    	  StopProcessingFaultLog(index[0]);
	    	  index_flag[0] = FALSE;
	      }
	      else
	      {
		     ;
	      }
   }
   /*hdudispflmsscu-ProcessLmsScuProbeErr-DB-LLR-010*/
   /*Shorted Probe Error */
   if((T_UINT32)ONE ==(((T_UINT32) data >>ONE)& (T_UINT32) HEX_ONE))
   {
      U16_message_words[1] |= 8192;
      err_stat = TRUE;
	  /*hdudispflmsscu-ProcessLmsScuProbeErr-DB-LLR-011*/
      if(FALSE == index_flag[1])
      {
      index[1] = fault_index;
      index_flag[1] = TRUE;
      }
      else
      {
      	;
      }
	  /*hdudispflmsscu-ProcessLmsScuProbeErr-DB-LLR-012*/
      GetFaultParamData(index[1]);
	  /*hdudispflmsscu-ProcessLmsScuProbeErr-DB-LLR-013*/
      if(FALSE == Fault_log_structure[index[1]].initial_fault_index)
      {
    	  StartProcessingFaultLog(PROBE_ERROR, SHORTED_PROBE_ERROR, index[1]);
      /*hdudispflmsscu-ProcessLmsScuProbeErr-DB-LLR-014*/      
         if((TEN > fault_index) && (FALSE == Stop_log))
  	      {
         	  fault_index++;
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
   }
   /*hdudispflmsscu-ProcessLmsScuProbeErr-DB-LLR-015*/
   else
   {
	   U16_message_words[1] = U16_message_words[1] & 57343;
	   /*hdudispflmsscu-ProcessLmsScuProbeErr-DB-LLR-016*/
	      if((TRUE == Fault_log_structure[index[1]].fault_active_flag) &&
	 	     (TRUE == index_flag[1]))
	      {
	    	  StopProcessingFaultLog(index[1]);
	    	  index_flag[1] = FALSE;
	      }
	      else
	      {
		     ;
	      }
   }
    /*hdudispflmsscu-ProcessLmsScuProbeErr-DB-LLR-017*/
	/* Range Error */
   if((T_UINT32)ONE ==(((T_UINT32) data>> TWO) & (T_UINT32) HEX_ONE))
   {
	   U16_message_words[2] |= 32;
      err_stat = TRUE;
	  /*hdudispflmsscu-ProcessLmsScuProbeErr-DB-LLR-018*/
      if(FALSE == index_flag[2])
      {
      index[2] = fault_index;
      index_flag[2] = TRUE;
      }
      else
      {
      	;
      }
	  /*hdudispflmsscu-ProcessLmsScuProbeErr-DB-LLR-019*/
      GetFaultParamData(index[2]);
	  /*hdudispflmsscu-ProcessLmsScuProbeErr-DB-LLR-020*/
      if(FALSE == Fault_log_structure[index[2]].initial_fault_index)
      {
    	  StartProcessingFaultLog(ARINC_ERROR, DATA_OUT_OF_RANGE, index[2]);
       /*hdudispflmsscu-ProcessLmsScuProbeErr-DB-LLR-021*/
    	  if((TEN > fault_index) && (FALSE == Stop_log))
  	      {
         	  fault_index++;
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
   }
   /*hdudispflmsscu-ProcessLmsScuProbeErr-DB-LLR-022*/
   else
   {
         U16_message_words[2] = U16_message_words[2] & 65503;
		 /*hdudispflmsscu-ProcessLmsScuProbeErr-DB-LLR-023*/
         if((TRUE == Fault_log_structure[index[2]].fault_active_flag) &&
    	    (TRUE == index_flag[2]))
         {
	    	  StopProcessingFaultLog(index[2]);
  	         index_flag[2] = FALSE;
         }
         else
         {
	         ;
         }
   }
   /*hdudispflmsscu-ProcessLmsScuProbeErr-DB-LLR-024*/
   /* Fuel Excitation Error */
   if((T_UINT32)ONE ==(((T_UINT32) data>> THREE) & (T_UINT32) HEX_ONE))
   {
      U16_message_words[1] |= 16384;
      err_stat = TRUE;
	  /*hdudispflmsscu-ProcessLmsScuProbeErr-DB-LLR-025*/
      if(FALSE == index_flag[3])
      {
      index[3] = fault_index;
      index_flag[3] = TRUE;
      }
      else
      {
      	;
      }
	  /*hdudispflmsscu-ProcessLmsScuProbeErr-DB-LLR-026*/
      GetFaultParamData(index[3]);
	  /*hdudispflmsscu-ProcessLmsScuProbeErr-DB-LLR-027*/
      if(FALSE == Fault_log_structure[index[3]].initial_fault_index)
      {
    	  StartProcessingFaultLog(PROBE_ERROR, FUEL_EXCITATION_ERROR, index[3]);
       /*hdudispflmsscu-ProcessLmsScuProbeErr-DB-LLR-028*/
         if((TEN > fault_index) && (FALSE == Stop_log))
  	      {
         	  fault_index++;
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
   }
   /*hdudispflmsscu-ProcessLmsScuProbeErr-DB-LLR-029*/
   else
   {
	   U16_message_words[1] = U16_message_words[1] & 49151;
	   /*hdudispflmsscu-ProcessLmsScuProbeErr-DB-LLR-030*/
	      if((TRUE == Fault_log_structure[index[3]].fault_active_flag) &&
	 	     (TRUE == index_flag[3]))
	      {
	    	  StopProcessingFaultLog(index[3]);
	    	  index_flag[3] = FALSE;
	      }
	      else
	      {
		     ;
	      }
   }
    }
	/*hdudispflmsscu-ProcessLmsScuProbeErr-DB-LLR-031*/
   else
   {
	   Arinc_fault_set = Arinc_fault_set | FOUR;
     	if(ONE == status)
     	{
   		   Ssm_ncd = Ssm_ncd | FOUR;
   	    }
   	    else
   	    {
   	    	Ssm_ncd = Ssm_ncd & 0xFB;
   	    }
   }
   /*hdudispflmsscu-ProcessLmsScuProbeErr-DB-LLR-032*/
    /* Display a red "X" over the Fuel Quantity Gauge if probe faults  */
    /* from the Probe BIT is received */

    if(TRUE == err_stat)
    {
    	Fault_set = Fault_set | TWO;
    }
    else
    {
    	Fault_set = Fault_set & 0xFD;
    }
}
/*
 * Function                :  StartProcessFaultLog
 *
 * Description             :  This function sets the start flags when SCU fault log has occurred
 *
 * Formal parameter(s)     :  T_UINT8 fault_type - IN SCU fault type.
 *                            T_UINT8 fault - IN SCU fault.
 *                            T_UINT8 arr_index - IN array index
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */
static void StartProcessingFaultLog(T_UINT8 fault_type, T_UINT8 fault, T_UINT8 arr_index)
{
  /*hdudispflmsscu-StartProcessingFaultLog-DB-LLR-001*/
	if(FALSE == Stop_log)
	{
		Fault_log_structure[arr_index].initial_fault_index = TRUE;
	    Fault_log_structure[arr_index].fault_active_flag = TRUE;
		++Flt_id_count;
		if(65534 <Flt_id_count)
		{
			 Flt_id_count = (T_UINT16) Flt_id_count % 65534;
			 Fault_log_structure[arr_index].Fault_index = (T_UINT16) Flt_id_count;
		}
		else
		{
	    Fault_log_structure[arr_index].Fault_index = (T_UINT16) Flt_id_count;
		}
		/*hdudispflmsscu-StartProcessingFaultLog-DB-LLR-002*/
        if (Flt_id_count > FT_LOG_SIZE)
        {
        	Ft_log_overflow = TRUE;
        }
        else
        {
           ; /*Do nothing */
        }
		/*hdudispflmsscu-StartProcessingFaultLog-DB-LLR-003*/
	    Fault_log_structure[arr_index].flight_number =  (T_UINT16) Flight_count;
	    Fault_log_structure[arr_index].start_duration = (Time_in_sec/ (T_UINT32)FIVE);
	    Fault_log_structure[arr_index].stop_duration = (Time_in_sec/ (T_UINT32)FIVE);
	    Fault_log_structure[arr_index].fault_type =fault_type;
	    Fault_log_structure[arr_index].error_code= fault;
	    Fault_log_structure[arr_index].timestamp = \
	    Fault_log_structure[arr_index].stop_duration -
	    Fault_log_structure[arr_index].start_duration;
	    Fault_log_structure[arr_index].data_present = TRUE;
	    Fault_log_structure[arr_index].Last_ft_record = FALSE;
	    Fault_log_structure[arr_index].fault_data_write = FALSE;
	    Fault_log_structure[arr_index].end_ft_transmission = FALSE;
	    Fault_log_structure[arr_index].param_data_write[0] = FALSE;
	    Fault_log_structure[arr_index].param_data_write[1] = FALSE;
	    Fault_log_structure[arr_index].param_data_write[2] = FALSE;
	    Fault_log_structure[arr_index].param_data_write[3] = FALSE;
	    Fault_log_structure[arr_index].param_data_write[4] = FALSE;
	    Fault_log_structure[arr_index].param_data_write[5] = FALSE;
	}
	else
	{
		;
	}
}

/*
 * Function                :  StopProcessingFaultLog
 *
 * Description             :  This function resets the flags when SCU fault is stopped
 *
 * Formal parameter(s)     :  T_UINT8 arr_index - IN array index
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */
static void StopProcessingFaultLog(T_UINT8 arr_index)
{
     /*hdudispflmsscu-StopProcessingFaultLog-DB-LLR-001*/
	  Fault_log_structure[arr_index].Fault_index = ZERO;
      Fault_log_structure[arr_index].flight_number =  ZERO;
      Fault_log_structure[arr_index].start_duration = ZERO;
      Fault_log_structure[arr_index].stop_duration = ZERO;
	  Fault_log_structure[arr_index].fault_type =NO_ERROR;
	  Fault_log_structure[arr_index].error_code= ZERO;
	  Fault_log_structure[arr_index].end_ft_transmission = TRUE;
	  Fault_log_structure[arr_index].data_present = FALSE;
	  Fault_log_structure[arr_index].Last_ft_record = TRUE;
	  Fault_log_structure[arr_index].initial_fault_index = FALSE;
	  Fault_log_structure[arr_index].fault_active_flag = FALSE;
	  Fault_log_structure[arr_index].param_data_present[0] = FALSE;
	  Fault_log_structure[arr_index].param_data_present[1] = FALSE;
	  Fault_log_structure[arr_index].param_data_present[2] = FALSE;
	  Fault_log_structure[arr_index].param_data_present[3] = FALSE;
	  Fault_log_structure[arr_index].param_data_present[4] = FALSE;
	  Fault_log_structure[arr_index].param_data_present[5] = FALSE;
	  Fault_log_structure[arr_index].fault_data_write = TRUE;
}

/*
 * Function                :  ProcessingArinc01Fault
 *
 * Description             :  This function processes SCU Arinc 01 fault.
 *
 * Formal parameter(s)     :  None
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */
void ProcessingArinc01Fault()
{
    static T_UINT8 ft_index =ZERO;
    static T_BOOL ft_index_flag =FALSE;
    static T_BOOL err_set =FALSE;
    T_UINT8 fault_index =ZERO;

    
    if(TRUE != Demo_mode)
    {
      /*
       * Process SCU ARINC 01 when:
       * 1) SSM is invalid (other than 3 for label 0247 and other than 3 and 0 for
       *    labels 0250 and 0272)
       * 2) No Data (labels 0247, 0250 and 0272 not received) for 10 seconds
       */
	  if((ZERO != Arinc_fault_set)  ||
	  (((RTD_MAX_INTERVAL_SCU <= Scu_timer[0]) || (RTD_MAX_INTERVAL_SCU <= Scu_timer[1]) ||
	  (RTD_MAX_INTERVAL_SCU <= Scu_timer[2]))  && (SEVEN == Scu_label_flag)))
	  {
		if(FALSE == err_set)
		{
		/*hdudispflmsscu-ProcessingArinc01Fault-DB-LLR-001*/
			err_set = TRUE;
			Fault_set = Fault_set | FOUR;
			/*hdudispflmsscu-ProcessingArinc01Fault-DB-LLR-002*/
			U16_message_words[2] |= 16;
	    	for(fault_index = ZERO; fault_index < MAX_FAULT_LOG; fault_index++)
		    {
		    	if(FALSE == Fault_log_structure[fault_index].data_present)
		    	{
			       break;
			    }
			    else
			    {
			       ; /* Do Nothing */
			    }
		   }
                /*hdudispflmsscu-ProcessingArinc01Fault-DB-LLR-003*/
		        if(FALSE == ft_index_flag)
		        {
		        	ft_index = fault_index;
		        	ft_index_flag = TRUE;
		        }
		        else
		        {
		        	;
		        }
                 /*hdudispflmsscu-ProcessingArinc01Fault-DB-LLR-004*/
		          GetFaultParamData(ft_index);
                 /*hdudispflmsscu-ProcessingArinc01Fault-DB-LLR-005*/
		        if(FALSE == Fault_log_structure[ft_index].initial_fault_index)
		        {
		        	StartProcessingFaultLog(ARINC_ERROR, INVALID_NO_ARINC_SIGNAL, ft_index);
                     /*hdudispflmsscu-ProcessingArinc01Fault-DB-LLR-006*/
			        if((TEN > fault_index)  && (FALSE == Stop_log))
				    {
			        	fault_index++;
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
		}
	 }
	 /*hdudispflmsscu-ProcessingArinc01Fault-DB-LLR-007*/
	else
	{
		/*
		 * Stop processing SCU ARINC 01 error when labels 0247, 0250 and 0272 are received
		 * and SSM of all three labels are valid
		 */
		if( (ZERO == Arinc_fault_set) &&
		  ((RTD_MAX_INTERVAL_SCU > Scu_timer[0]) && (RTD_MAX_INTERVAL_SCU > Scu_timer[1]) &&
		   (RTD_MAX_INTERVAL_SCU > Scu_timer[2])))
		{
			U16_message_words[2] = U16_message_words[2] & 65519;
			err_set = FALSE;
			Fault_set = Fault_set & 0xFB;

			/*hdudispflmsscu-ProcessingArinc01Fault-DB-LLR-008*/
		    if((TRUE == Fault_log_structure[ft_index].fault_active_flag) &&
			     (TRUE == ft_index_flag))
		    {
		  	   StopProcessingFaultLog(ft_index);
		       ft_index_flag = FALSE;
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
	}
  }
}

/*
 * Function                :  GetFaultParamData
 *
 * Description             :  This function gets RTD data when a fault has occurred
 *
 * Formal parameter(s)     :  T_UINT8 arr_index - IN array index.
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */
static void GetFaultParamData(T_UINT8 arr_index)
{
  T_UINT16 u16_i = 0;
  T_UINT8 u16_j = 0;

  static T_BOOL param_timer_reset_stat[6] ={ZERO};
  static T_BOOL data_set_flag = FALSE;
        /*hdudispflmsscu-GetFaultParamData-DB-LLR-001*/
	    for (u16_i = 0; u16_i < Port1_label_count; ++u16_i)
	     {
	   	 for (u16_j = 0; u16_j < SIX; ++u16_j)
	   	  {
	   		 if(FALSE == data_set_flag)
	   		 {
	   	  	   if (A429_data[0][u16_i].label == Fault_data[0].fault_label)
	   		   {
	   		 	   RTDGetParamDdw((T_UINT16)(u16_i + 1), &Fault_data[0].label_data);
	   		 	   data_set_flag = TRUE;
	   		   }
			   /*hdudispflmsscu-GetFaultParamData-DB-LLR-002*/
	   		   else if (A429_data[0][u16_i].label == Fault_data[u16_j].fault_label)
	   	       {
	   		       RTDGetParam((T_UINT16)(u16_i + 1), &Fault_data[u16_j].label_data);
	   		       data_set_flag = TRUE;
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
			 /*hdudispflmsscu-GetFaultParamData-DB-LLR-003*/
	   		 if(TRUE == data_set_flag)
	   		 {
	   	       if(PARAM_OK == Fault_data[u16_j].label_data.stat)
	   	       {
	   	      	param_timer_reset_stat[u16_j] = FALSE;
				/*hdudispflmsscu-GetFaultParamData-DB-LLR-004*/
	   	    	if(FALSE == Fault_log_structure[arr_index].param_data_present[u16_j])
	   	    	{
		   	    	/* backup of the data when SSM is valid */
		   	    	Previous_fault_data[u16_j].label_data = Fault_data[u16_j].label_data;
	   	    	    Fault_log_structure[arr_index].param_data[u16_j] = \
	   	    	    		Fault_data[u16_j].label_data.r;
	   	    	    Fault_log_structure[arr_index].param_data_present[u16_j] = TRUE;
	   	    	}
	   	    	else
	   	    	{
	   	    		;
	   	    	}

	   	    }
	   	    else
	   	    {
		    	/*hdudispflmsscu-GetFaultParamData-DB-LLR-005*/
	   	    	if(FALSE == Fault_log_structure[arr_index].param_data_present[u16_j])
	   	    	{
	   	    		/* if SSM is invalid when a fault is set, consider the */
	   	    		/* parameter data when SSM was valid */
	   	    	    Fault_log_structure[arr_index].param_data[u16_j] = \
	   	    	    		Previous_fault_data[u16_j].label_data.r;
	   	    	    Fault_log_structure[arr_index].param_data_present[u16_j] = TRUE;
	   	    	}
	   	    	else
	   	    	{
	   	    		;
	   	    	}
	   	    	if(FALSE == param_timer_reset_stat[u16_j])
	   	    	{
	   	    		param_timer_reset_stat[u16_j] =TRUE;
	   	    		/* reset the parameter fault timer */
	   	    		Fault_timer[u16_j] = ZERO;

	   	    	}
	   	    	else
	   	    	{
	   	    		;
	   	    	}
                /*hdudispflmsscu-GetFaultParamData-DB-LLR-006*/
	   	    	if(TRUE == FaultTimer(u16_j)) /* SSM is invalid for 1 second */
	   	    	{
	   	    		/* SSM is invalid after 1 second */
	   	    		Param_ssm_validity[u16_j] = TRUE;
	   	    		Fault_log_structure[arr_index].Last_ft_record = TRUE;
	   	    	}
	   	    	else
	   	    	{
	   	    		;
	   	    	}
				/*hdudispflmsscu-GetFaultParamData-DB-LLR-007*/
		   	    if(TRUE == Param_ssm_validity[u16_j])
		   	    {
		   	    	/* When SSM is invalid for more than 1 sec, consider the data */
		   	    	/*  when the SSM was valid */

		   	    	Stop_ft_log = TRUE;
		   	        Param_ssm_validity[u16_j] = FALSE;
		   	    }
		   	    else
		   	    {
		   	    	;
		   	    }
	   	    }
			/*hdudispflmsscu-GetFaultParamData-DB-LLR-008*/
	   	      data_set_flag = FALSE;
	   		 }
	   		 else
	   		 {
	   			 ;
	   		 }
	      }
	    }
		/*hdudispflmsscu-GetFaultParamData-DB-LLR-009*/
	    if((PARAM_OK == Fault_data[0].label_data.stat) &&
	       (PARAM_OK == Fault_data[1].label_data.stat) &&
	       (PARAM_OK == Fault_data[2].label_data.stat) &&
		   (PARAM_OK == Fault_data[3].label_data.stat) &&
		   (PARAM_OK == Fault_data[4].label_data.stat) &&
		   (PARAM_OK == Fault_data[5].label_data.stat))
	    {
	    	Stop_ft_log = FALSE;
	    	Stop_log = FALSE;
	    }
	    else
	    {
	    	Stop_log = TRUE;
	    }
}
/*
 * Function                :  PushFaultLog
 *
 * Description             :  This function transmits the Fault log data
 *                            to communication board to store it in NVRAM.
 *
 * Formal parameter(s)     :  None
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */

void PushFaultLog(void)
{
    T_UINT8 fault_index = ZERO;
    T_UINT8 data_index = ZERO;
    T_UINT8 fault_doc_id = ZERO;
	T_A825_MESSAGE s_xm = {
		         EEC,             /*lcc*/
		         {                /*sid*/
		            {             /*bid*/
		               0,0,0,0,
		               0,0,
		            }
		         },
		         0 ,    /*u8_paysize*/
		         {               /*u8_payload*/
		            0,0,0,0,
		            0,0,0,0
		         }
		      };
	   T_A825_XMITRESULT test_res = A825_XM_OK;

      /*hdudispflmsscu-PushFaultLog-DB-LLR-001*/
	   INIT_NOC_MESSAGE(s_xm);
	   s_xm.u8PaySize     = EIGHT;
	   s_xm.sID.PID.rci = (T_UCHAR)(Du_position & THREE);

     /*hdudispflmsscu-PushFaultLog-DB-LLR-002*/
	   for(fault_index = ZERO;fault_index<MAX_FAULT_LOG;fault_index++)
	    {
		      if((Fault_log_structure[fault_index].Fault_index > ZERO) &&
		         (FALSE == Fault_log_structure[fault_index].end_ft_transmission)
				 && (FALSE == Stop_ft_log))
		      {

	   		     *((T_UINT16 *)s_xm.u8PayLoad) = \
	   		    		 (T_UINT16)Fault_log_structure[fault_index].Fault_index;
                /*hdudispflmsscu-PushFaultLog-DB-LLR-003*/
	     	     if(FALSE == Fault_log_structure[fault_index].fault_data_write)
	   	         {
	     	 	   s_xm.sID.BID.doc   = DIS_FAULT_LOG;
	   		        s_xm.u8PayLoad[2] = Fault_log_structure[fault_index].fault_type;
	   		        s_xm.u8PayLoad[3] = Fault_log_structure[fault_index].error_code;
	   		        *((T_UINT16 *)(&(s_xm.u8PayLoad[4]))) =
	   		            Fault_log_structure[fault_index].flight_number;

	   		        test_res = A8251Xmit(&s_xm);


               /*hdudispflmsscu-PushFaultLog-DB-LLR-004*/
	   		   if(test_res != A825_XM_OK)
	   		   {
	   			   test_res = (T_A825_XMITRESULT)FIVE;
	   		   }
	   		   else
	   		   {
	   			   ;/* Does nothing */
	   		   }
			   /*hdudispflmsscu-PushFaultLog-DB-LLR-005*/
	   		Fault_log_structure[fault_index].fault_data_write = TRUE;
	   	  }
	   	  else
	   	  {
	   		  ; /* Does nothing */
	   	  }
		       /*hdudispflmsscu-PushFaultLog-DB-LLR-006*/
	   		   s_xm.sID.BID.doc   = DIS_FAULT_TIMESTAMP;
			   /*hdudispflmsscu-PushFaultLog-DB-LLR-007*/
	   		   if(TRUE == Fault_log_structure[fault_index].fault_active_flag)
	   		   {
	   	   		    Fault_log_structure[fault_index].timestamp = (Time_in_sec/ (T_UINT32)FIVE) - \
	   	   		    Fault_log_structure[fault_index].start_duration ;
	   		   }
			   /*hdudispflmsscu-PushFaultLog-DB-LLR-008*/
	   		   else
	   		   {
	   			    Fault_log_structure[fault_index].timestamp =
	   			    Fault_log_structure[fault_index].stop_duration - \
	   				Fault_log_structure[fault_index].start_duration ;
	   		   }
                   /*hdudispflmsscu-PushFaultLog-DB-LLR-009*/
	   	   		   *((T_UINT32 *)(&(s_xm.u8PayLoad[2]))) = \
	   	   				   Fault_log_structure[fault_index].timestamp;
	   	   		   test_res = A8251Xmit(&s_xm);

                  /*hdudispflmsscu-PushFaultLog-DB-LLR-010*/
	   	   		   if(test_res != A825_XM_OK)
	   	   		   {
	   	   			   test_res = (T_A825_XMITRESULT)FIVE;
	   	   		   }
	   	   		   else
	   	   		   {
	   	   			   ;/* Does nothing */
	   	   		   }

            /*hdudispflmsscu-PushFaultLog-DB-LLR-011*/
	   		fault_doc_id =DIS_FAULT_PARAM_WOG;
	   		for(data_index= ZERO; data_index < SIX; data_index++)
	   		{
	   			if((TRUE == Fault_log_structure[fault_index].param_data_present[data_index]) &&
	   			  (FALSE == Fault_log_structure[fault_index].param_data_write[data_index]))
	   			{
	   		        s_xm.sID.BID.doc   = fault_doc_id ;
	   		        *((T_INT32 *)(&(s_xm.u8PayLoad[2]))) = \
	   		          Fault_log_structure[fault_index].param_data[data_index];
	   		        test_res = A8251Xmit(&s_xm);

                    /*hdudispflmsscu-PushFaultLog-DB-LLR-012*/
	   		        if(test_res != A825_XM_OK)
	   		        {
	   			      test_res = (T_A825_XMITRESULT)FIVE;
	   		        }
	   		        else
	   		        {
	   			       ; /* Does nothing */
	   		        }
					/*hdudispflmsscu-PushFaultLog-DB-LLR-013*/
	   		     *((T_INT32 *)(&(s_xm.u8PayLoad[2]))) = ZERO;
	   		      fault_doc_id++;
	   		   Fault_log_structure[fault_index].param_data_write[data_index] = TRUE;
	   			}
	   			else
	   			{
	   				; /* Does nothing */
	   			}
	   		}
			/*hdudispflmsscu-PushFaultLog-DB-LLR-014*/
	   		if( TRUE == Fault_log_structure[fault_index].Last_ft_record)
	   		{
	   		   Fault_log_structure[fault_index].end_ft_transmission = TRUE;
	   		}
	   		else
	   		{
	   			; /* Does nothing */
	   		}
	   }
	   else
	   {
		   ; /* Does nothing */
	   }
   }
}
