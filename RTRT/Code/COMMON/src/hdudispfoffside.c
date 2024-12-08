/*
 ******************************************************************************
 * License Information  :  Howell Instruments, Inc.                           *
 *                         "Licensed Software" and "All rights reserved".     *
 ******************************************************************************
 *  File                : hdudispfoffside.c
 *
 *  Description         : This file performs transmissions and processing of
 *                        user defined node service codes ,heart beat NOC, calibration.
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
 *      1.5           Rona B S         29-Jun-2020             100259
 *      1.6           Dhanalakshmi     20-Mar-2021             100331
 *      1.7           Dhanalakshmi     20-Mar-2021             100331
 *
 * Additional References : None
 *
 ******************************************************************************
 */

#include "hdudispfa429.h" /* Routines for arinc 429 */
#include "hdudispfdauprofile.h"  /* defines the constants for ARINC 825  Message Traffic.*/
#include "hdudispfglobalsettings.h" /* Routines to read and write data to NVRAM  */
#include "hdudispfoffside.h"  /* Screen, message and timer configuration */
#include "hdudispfpara.h"   /* prototype for builds faults, message and system information  */
#include "hdudispfrtd.h" /* Provide mapping for all A825 incoming parameters */
#include "hdudispfarinc825.h" /* Define the structure for an ARINC 825 Message. */
#include "hdulibbasictypes.h" /* Standard basic data type definitions */
/* Updated as per PR 100083 */
#include "hdudispfpdidata.h" /* provides pdi declarations */
#include "hdudispfgrapp.h" /* routines for all graph */
#include "hdudispfmenu.h" /* contains prototype for menu module*/
#include "hdudispfdemo.h"  /* Provides demo declarations */
#include "hdudispfa429.h"  /* Routines for arinc 429 */

#define HEARTBEAT_PAYLOAD     0x12345678UL
void ProcessCaliA825(T_INT32 arinc_word);

/*
 * Function                :  OffsideSwitchScreen
 *
 * Description             :  This function triggers the transmission of
 *                            switch screen service code.
 *
 * Formal parameter(s)     :  T_UINT8 u8_page_num - IN Page number
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */

void OffsideSwitchScreen(T_UINT8 u8_page_num)
{
   T_A825_MESSAGE  s_mess = {ZERO};

   /* hdudispfoffside-OffsideSwitchScreen-DB-LLR-001 */
   INIT_NSC_REQUEST(s_mess);
   s_mess.sID.PID.sid    = EISDSPLY_SID;
   s_mess.u8PaySize      = THREE;
   s_mess.sID.PID.rci = (T_UCHAR)(Du_position & THREE);
   /* Updated as per PR 100083 */
   *((T_UINT16 *)s_mess.u8PayLoad) = NSC_SWITCH_SCREEN;
   s_mess.u8PayLoad[2] = u8_page_num;

   /* hdudispfoffside-OffsideSwitchScreen-DB-LLR-002 */
   A8252Xmit(&s_mess);
}

/*
 * Function                :  OffsideTimerStart
 *
 * Description             :  This function triggers the transmission of
 *                            start timer service code.             :
 *
 * Formal parameter(s)     :  T_UINT32 U32_initial_value - IN Initial value.
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */

void OffsideTimerStart(T_UINT32 U32_initial_value)
{
   T_A825_MESSAGE   s_mess =  {ZERO};
   T_PARAM_READING temp = {ZERO};
   /* hdudispfoffside-OffsideTimerStart-DB-LLR-003 */
   RTDGetParamDdw(0, &temp);  /* Check for heart beat message status */

   if (MISSING != temp.stat)
   {

   /* hdudispfoffside-OffsideTimerStart-DB-LLR-001 */
   INIT_NSC_REQUEST(s_mess);
   s_mess.sID.PID.sid    = EISDSPLY_SID;
   s_mess.u8PaySize      = SIX;
   s_mess.sID.PID.rci = (T_UCHAR)(Du_position & THREE);
   *((T_INT16 *)s_mess.u8PayLoad) = (T_INT16)NSC_TIMER_START;
   *((T_UINT32 *)(&(s_mess.u8PayLoad[2]))) = U32_initial_value;

   /* hdudispfoffside-OffsideTimerStart-DB-LLR-002 */
   A8252Xmit(&s_mess);
   }
}

/*
 * Function                :  OffsideCoolTimer
 *
 * Description             :  This function triggers the transmission of
 *                            start timer service code.             :
 *
 * Formal parameter(s)     :  T_UINT8 cool_timer_state - IN Cool down timer state.
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */

void OffsideCoolTimer(T_UINT8 cool_timer_state)
{
   T_A825_MESSAGE   s_mess =  {ZERO};
   T_PARAM_READING temp = {ZERO};
   /* hdudispfoffside-OffsideCoolTimer-DB-LLR-003 */
   RTDGetParamDdw(0, &temp);  /* Check for heart beat message status */
   if (MISSING != temp.stat)
   {

   /* hdudispfoffside-OffsideCoolTimer-DB-LLR-001 */
   INIT_NSC_REQUEST(s_mess);
   s_mess.sID.PID.sid    = EISDSPLY_SID;
   s_mess.u8PaySize      = THREE;
   s_mess.sID.PID.rci = (T_UCHAR)(Du_position & THREE);
   *((T_UINT16 *)s_mess.u8PayLoad) = NSC_COOL_TIMER_STATE;
   s_mess.u8PayLoad[2] = cool_timer_state;

   /* hdudispfoffside-OffsideCoolTimer-DB-LLR-002 */
   A8252Xmit(&s_mess);
   }
}

/*
 * Function                :  OffsideFuelFlow
 *
 * Description             :  This function triggers the transmission of
 *                            fuel flow state service code.
 *
 * Formal parameter(s)     :  T_UINT8 Fuel_flow_state - IN fuel flow state.
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */

void OffsideFuelFlow(T_UINT8 fuel_flow_state)
{
   T_A825_MESSAGE   s_mess =  {ZERO};
   T_PARAM_READING temp = {ZERO};

   /*hdudispfoffside-OffsideFuelFlow-DB-LLR-001*/
   RTDGetParamDdw(0, &temp);  /* Check for heart beat message status */
   /*hdudispfoffside-OffsideFuelFlow-DB-LLR-002*/
   if (MISSING != temp.stat)
   {

   INIT_NSC_REQUEST(s_mess);
   s_mess.sID.PID.sid    = EISDSPLY_SID;
   s_mess.u8PaySize      = THREE;
   s_mess.sID.PID.rci = (T_UCHAR)(Du_position & THREE);
   *((T_UINT16 *)s_mess.u8PayLoad) = NSC_FUEL_FLOW_STATE;
   s_mess.u8PayLoad[2] = fuel_flow_state;
   /*hdudispfoffside-OffsideFuelFlow-DB-LLR-003*/
   A8252Xmit(&s_mess);
   }
}

/*
 * Function                :  OffsideTimerStop
 *
 * Description             :  This function triggers the transmission of
 *                            stop timer service code.
 *
 * Formal parameter(s)     :  T_UINT32 u32_stop_value - IN stop value.
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */

void OffsideTimerStop(T_UINT32 u32_stop_value)
{
   T_A825_MESSAGE   s_mess = {ZERO};
   T_PARAM_READING temp = {ZERO};
   /* hdudispfoffside-OffsideTimerStop-DB-LLR-003 */
   RTDGetParamDdw(0, &temp);  /* Check for heart beat message status */
   if (MISSING != temp.stat)
   {

   /* hdudispfoffside-OffsideTimerStop-DB-LLR-001 */
   INIT_NSC_REQUEST(s_mess);
   s_mess.sID.PID.sid    = EISDSPLY_SID;
   s_mess.u8PaySize      = SIX;
   s_mess.sID.PID.rci = (T_UCHAR)(Du_position & THREE);
   *((T_UINT16 *)s_mess.u8PayLoad) = NSC_TIMER_STOP;
   *((T_UINT32 *)(&(s_mess.u8PayLoad[2]))) = u32_stop_value;

   /* hdudispfoffside-OffsideTimerStop-DB-LLR-002 */
   A8252Xmit(&s_mess);
   }
}

/*
 * Function                :  OffsideTimerReset
 *
 * Description             :  This function triggers the transmission of
 *                            reset timer service code.
 *
 * Formal parameter(s)     :  None
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */
void OffsideTimerReset(void)
{
   T_A825_MESSAGE   s_mess = {ZERO};
   T_PARAM_READING temp = {ZERO};
   /* hdudispfoffside-OffsideTimerReset-DB-LLR-003 */
   RTDGetParamDdw(0, &temp);  /* Check for heart beat message status */
   if (MISSING != temp.stat)
   {

   /* hdudispfoffside-OffsideTimerReset-DB-LLR-001 */
   INIT_NSC_REQUEST(s_mess);
   s_mess.sID.PID.sid    = EISDSPLY_SID;
   s_mess.u8PaySize      = TWO;
   s_mess.sID.PID.rci = (T_UCHAR)(Du_position & THREE);
   *((T_INT16 *)s_mess.u8PayLoad) = (T_INT16)NSC_TIMER_RESET;

   /* hdudispfoffside-OffsideTimerReset-DB-LLR-002 */
   A8252Xmit(&s_mess);
   }
}

/*
 * Function                :  OffsideProcessA825NSC
 *
 * Description             :  This function performs the processing of
 *                            requested user defined node service codes.
 *
 * Formal parameter(s)     :  T_A825_MESSAGE  *s_mess - IN ARINC message
 *                            to be processed.
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */

void OffsideProcessA825NSC(T_A825_MESSAGE  *s_mess)
{
   T_NSC_CODE     node_service_code = NSC_IDS;
   T_EPAGE_NUM  page_num = EPAGE0;
   T_UINT32    u32_timer = ZERO;
   T_INT32    cali_word = ZERO;
   /* Updated as per PR 100083 */

   node_service_code = (T_NSC_CODE)(*((T_UINT16 *)s_mess->u8PayLoad));
   switch(node_service_code)
   {
      case NSC_SWITCH_SCREEN:
         /* hdudispfoffside-OffsideProcessA825NSC-DB-LLR-001 */
        page_num = (T_EPAGE_NUM)(s_mess->u8PayLoad[2]);
        if(page_num!=EPAGE0)
        {

          if(EPAGE0 == Page_num )
          {
            Toggle_screen = ((page_num % (Max_num_of_pages-1))+1);
          }
          else
          {
             GrappSetPage((T_UINT8)((page_num % (Max_num_of_pages-1))+1));
          }

        }
      break;

      case NSC_TIMER_START:
         /* hdudispfoffside-OffsideProcessA825NSC-DB-LLR-003 */
         u32_timer = *((T_UINT32 *)(&s_mess->u8PayLoad[2]));
         OffsideManualTimerStart(u32_timer);
      break;

      case NSC_TIMER_STOP:
         /* hdudispfoffside-OffsideProcessA825NSC-DB-LLR-004 */
         u32_timer = *((T_UINT32 *)(&s_mess->u8PayLoad[2]));
         OffsideManualTimerStop(u32_timer);
      break;

      case NSC_TIMER_RESET:
         /* hdudispfoffside-OffsideProcessA825NSC-DB-LLR-005 */
         OffsideManualTimerReset();
      break;

      case   NSC_SET_EIU:
         /* hdudispfoffside-OffsideProcessA825NSC-DB-LLR-006 */
         Active_eiu = (T_EIU) (*((T_UINT8 *)(&s_mess->u8PayLoad[2])));
      break;

      case NSC_COOL_TIMER_STATE:
      /* hdudispfoffside-OffsideProcessA825NSC-DB-LLR-007 */
        Cool_down_select=(T_BOOL)(*((T_UINT8 *)(&s_mess->u8PayLoad[2])));
        if(TRUE==Cool_down_select)
        {
         Cool_down_state = ECOOLDOWN_ON;
        }
      break;

      case NSC_CALIBRATION:
          /* hdudispfoffside-OffsideProcessA825NSC-DB-LLR-008 */
    	  cali_word = *((T_INT32 *)(&s_mess->u8PayLoad[2]));
    	  ProcessCaliA825(cali_word);
      break;

      case NSC_FUEL_FLOW_STATE:
	      /*hdudispfoffside-OffsideProcessA825NSC-DB-LLR-009*/
    	  Fuel_flow_select=(T_BOOL)(*((T_UINT8 *)(&s_mess->u8PayLoad[2])));
          if(TRUE==Fuel_flow_select)
          {
        	  Fuel_flow_state = FUEL_FLOW_ON;
          }
        break;

      default:
      break;
   }
}

/*
 * Function                :  OffsideHeartBeat
 *
 * Description             :  This function triggers the transmission of
 *                            heart beat.
 *
 * Formal parameter(s)     :  None
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */

void OffsideHeartBeat(void)
{
   T_A825_MESSAGE   s_mess = {ZERO};

   /* hdudispfoffside-OffsideHeartBeat-DB-LLR-001 */
   INIT_NOC_MESSAGE(s_mess);
   s_mess.u8PaySize      = FOUR;
   s_mess.sID.BID.doc = HEART_BEAT;
   s_mess.sID.BID.rci = (T_UCHAR)(Du_position & THREE);
   /* Updated as per PR 100083 */
   *((T_UINT32 *)s_mess.u8PayLoad) = HEARTBEAT_PAYLOAD;

   /* hdudispfoffside-OffsideHeartBeat-DB-LLR-002 */
   A8252Xmit(&s_mess);
}

/*
 * Function                :  OffsideProcessA825NOC
 *
 * Description             :  This function processes the HEART_BEAT
 *                            Data Object Code.
 *
 * Formal parameter(s)     :  T_A825_MESSAGE  *s_mess - IN ARINC message
 *                            to be processed.
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */

void OffsideProcessA825NOC(T_A825_MESSAGE  *s_mess)
{
   /* hdudispfoffside-OffsideProcessA825NOC-DB-LLR-001 */
   if(HEART_BEAT == s_mess->sID.BID.doc)
   {
      RTDSetParam( 0, 0, (T_FLOAT)*((T_UINT32 *)(&s_mess->u8PayLoad[0])), RTD_STAT_FAIL);
   }
}


/*
 * Function                :  OffsideCalibrationA825
 *
 * Description             :  This function sends the calibration data between the displays
 *
 * Formal parameter(s)     :  T_UINT8 u8_page_num - IN Page number
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */

void OffsideCalibrationA825(T_UINT8 engine_count, T_UINT8 parameter_label)
{
   T_A825_MESSAGE  s_message = {ZERO};

   /* hdudispfoffside-OffsideCalibrationA825-DB-LLR-001 */
   INIT_NSC_REQUEST(s_message);
   s_message.sID.PID.sid    = EISDSPLY_SID;
   s_message.u8PaySize      = SEVEN;
   s_message.sID.PID.rci = (T_UCHAR)(Du_position & THREE);
   *((T_UINT16 *)s_message.u8PayLoad) = NSC_CALIBRATION;

   if (LABEL_051 == parameter_label)
   {
	   *((T_UINT32 *)(&(s_message.u8PayLoad[2]))) = (T_UINT32)(parameter_label
	      	          |(((T_UINT32)engine_count)<<EIGHT)|
					  (( (T_UINT32)Offset_value_cal[engine_count]) << TEN));
   }
   else if (LABEL_052 == parameter_label)
   {
	   *((T_UINT32 *)(&(s_message.u8PayLoad[2]))) = (T_UINT32)(parameter_label
	   	      	      |(((T_UINT32)engine_count)<<EIGHT)|
					  (( (T_UINT32)Gain_value_cal[engine_count]) << TEN));
   }
   else
   {
	   ; /*Do nothing*/
   }


   A8252Xmit(&s_message);
}



/*
 * Function                :  OffsideCalibration
 *
 * Description             :  This function triggers the transmission of
 *                            switch screen service code.
 *
 * Formal parameter(s)     :  T_UINT8 u8_page_num - IN Page number
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */


void OffsideCalibration(T_UINT8 loop_i)
{
   T_A825_MESSAGE  cal_mess = {ZERO};

   /* hdudispfoffside-OffsideCalibration-DB-LLR-001 */
   INIT_NSC_REQUEST(cal_mess);
   cal_mess.sID.PID.sid    = EISDSPLYGATEWAY_SID;
   cal_mess.u8PaySize      = 7;
   cal_mess.sID.PID.rci = (T_UCHAR)(Du_position & THREE);
   *((T_UINT16 *)cal_mess.u8PayLoad) = NSC_SEND_A429;

  /*Offset*/
   /* hdudispfoffside-OffsideCalibration-DB-LLR-002 */  
	 *((T_UINT32 *)(&(cal_mess.u8PayLoad[2]))) = (T_UINT32)(Calibration_label[0]
	                               |(((T_UINT32)loop_i)<<EIGHT)|
								   (( (T_UINT32)Offset_value_cal[loop_i]) << TEN));

	 /*transmit only after receiving first Msg from DAU*/
	 if (TRUE  == Offset_bool[loop_i])
	 {
	   A8251Xmit(&cal_mess);
	 }
	 else
	 {
		 ; /* Do nothing */
	 }

   /*gain*/
  /* hdudispfoffside-OffsideCalibration-DB-LLR-003 */  
	   *((T_UINT32 *)(&(cal_mess.u8PayLoad[2]))) = (T_UINT32)(Calibration_label[1]
	   	                           |(((T_UINT32)loop_i)<<EIGHT)|
								   (( (T_UINT32)Gain_value_cal[loop_i]) << TEN));

	 if (TRUE  == Gain_bool[loop_i])
	 {
	   A8251Xmit(&cal_mess);
	 }
	 else
	 {
		 ; /* Do nothing */
	 }
}


/*
 * Function                :  ProcessCaliA825
 *
 * Description             :  This function sends the calibration datas between the displays once
 *                            entered
 *
 * Formal parameter(s)     :  T_UINT8 u8_page_num - IN Page number
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */


void ProcessCaliA825(T_INT32 arinc_word)
{
	T_UINT8 u8_label = ZERO;
	T_UINT8 u8_sdi = ZERO;

    /* hdudispfoffside-ProcessCaliA825-DB-LLR-001 */
	u8_label = (T_UINT8) ((T_UINT32) arinc_word & (0x00000FF));

    u8_sdi = (T_UINT8) ((T_UINT32) arinc_word>>EIGHT & THREE);

	 if (LABEL_051 == u8_label)
	 {
	    Offset_value_cal[u8_sdi] = ((arinc_word >> TEN) & (0xFFFF));
	    OffsetInttoIntArray(u8_sdi);

	 }
	 else if (LABEL_052 == u8_label)
	 {
		Gain_value_cal[u8_sdi] = ((arinc_word >> TEN) & (0xFFFF));
		GainInttoIntArray(u8_sdi);

	 }
	 else
	 {
		; /* Do Nothing*/
	 }

}

