/*
 ******************************************************************************
 * License Information  :  Howell Instruments, Inc.                           *
 *                         "Licensed Software" and "All rights reserved".     *
 ******************************************************************************
 *  File                : hdudispfglobalsettings.c
 *
 *  Description         : This file stores the global settings, saves,
 *                        retrieves and processes the backup storage and sets
 *                        the active EIU.
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
 *      1.5           Divya G P        04-Nov-2017             100156
 *      1.6           Vinay H          23-Mar-2018             100196
 *      1.7           Rona B S         28-Mar-2018             100196
 *      1.8           Shruthi M N      03-Apr-2018             100205
 *      1.9           Chaithra J       21-Jun-2020             100259
 *      1.10          Rona B S         29-Jun-2020             100259
 *      1.11          Dhanalakshmi     12-Sep-2020             100276
 *      1.12          Rona B S         28-Sep-2020             100284
 *      1.13          Dhanalakshmi     20-Mar-2021             100331
 *      1.14          Dhanalakshmi     20-Mar-2021             100331
 *
 * Additional References : None
 *
 ******************************************************************************
 */

#include "hdudispfpdidata.h"         /* contains routines for PDI data */
#include "hdudispfdemo.h"           /* provides demo functionalities */
#include "hdudispfa429.h"           /* Routines for arinc 429 */
#include "hdudispfcrc.h"            /* Contains functions prototypes of hdudispbcrc*/
#include "hdudispfdauprofile.h"     /* defines the constants for ARINC 825  Message Traffic.*/
#include "hdudispfglobalsettings.h" /* Routines to read and write data to NVRAM  */
#include "hdudispfgrapp.h"          /* routines for all graph */
#include "hdudispfarinc825.h"      /* Define the structure for an ARINC 825 Message. */
#include "hdudispfpara.h"       /* prototype for builds faults, message and system information*/
#include "hdulibbasictypes.h"   /* Standard basic data type definitions */
#include "hdudispfoscpu.h"      /* OS function declarations */
#include "hdudispfmenu.h" /* contains prototype for menu module*/
#include "hdudispftimer.h"         /* Consistency Check*/
#include "hdudispfresource.h"/* provides resources */
#include "hdudispfucos.h" /* provides ucos functionalities */
#include "hdudispfgrapp.h"           /* routines for all graph */
#include "hdudispfpbit.h"        /* contains prototypes for PBIT test. */
#include "hdudispfmenu.h"            /* contains prototype for menu module*/
#include "hdudispflmsscu.h"  /* SCU rtd processing and error codes  */

T_INT32 S32_data_exceed[NUMBEROFENGINES] = {0};
T_BOOL Pull_flag = FALSE;

/* Updated per ECM 38, 39, 41*/
T_UINT16  Ex_id_count = 0;
T_BOOL    Log_overflow = FALSE;
T_BOOL    Ft_log_overflow =FALSE;
T_UINT16  Flight_count = 0;
T_BOOL  Exceedance_startup_check[MAX_ELOG_EVENT] = {FALSE};
static T_BOOL Nv_ram_read = FALSE;


static T_INT32  Prev_peak_val[EXCEED_LOG_SIZE] = {0};
static T_UINT32  Prev_duration_val[EXCEED_LOG_SIZE] = {0};

T_GLOBAL_EXCEED Exceedance_log[EXCEED_LOG_SIZE] = {0};

T_TIMER Flight_timer_exceed[EXCEED_LOG_SIZE] = {0};
static T_TIMER Flight_timer_mirror_exceed[EXCEED_LOG_SIZE] = {0};

#define DEFAULT_MANUAL_BRIGHTNESS   500
#define DEFAULT_AUTO_BRIGHTNESS  100
#define DEFAULT_BRIGHTNESS_MODE EBRIGHTNESS_AUTO
#define DEFAULT_COOL_DOWN_STATE ECOOLDOWN_OFF
#define DEFAULT_FUEL_FLOW_STATE FUEL_FLOW_ON
#define PULL_RESEND_TIME_TICK  250
#define MAX_ELOG_TRIG_COND     5

T_BOOL Demo_mode = FALSE;
T_BOOL Demo_mode_activate = FALSE;
T_BOOL Data_received = FALSE;
T_INT16 Manual_brightness = DEFAULT_MANUAL_BRIGHTNESS;
T_INT16 Auto_brightness  = DEFAULT_AUTO_BRIGHTNESS;
T_BRIGHTNESS_MODE Brightness_mode = DEFAULT_BRIGHTNESS_MODE;
T_COOLDOWN_STATE Cool_down_state = DEFAULT_COOL_DOWN_STATE;
T_FUEL_FLOW_STATE   Fuel_flow_state =DEFAULT_FUEL_FLOW_STATE;
T_EIU Active_eiu = EIU1;
T_BOOL Nv_crc_fail = FALSE;

static T_NV_STORAGE Nv_storage =
{
		{
		  EBRIGHTNESS_MANUAL,
			0,
			0,
			EIU1,
			ECOOLDOWN_ON,
			EPAGE0,
			EPAGE0,
			FUEL_FLOW_ON,
			{0},
			0U,
			0U,
			0U,
			0U,
		    {0U},
			0U,
			0U,
			0U
   }
 };

static T_NV_STORAGE Nv_storage_in =
{
		{
		  EBRIGHTNESS_MANUAL,
			0,
			0,
			EIU1,
			ECOOLDOWN_ON,
			EPAGE0,
			EPAGE0,
			FUEL_FLOW_ON,
			{0},
			0U,
			0U,
			0U,
			0U,
		    {0U},
			0U,
			0U,
			0U
   }
 };

#define DELAY_40MS 40
#define EXCEED_ID_LOG_SIZE 200

T_GLOBAL_SETTINGSTRIG Trig_setting[MAX_ELOG_EVENT] = {
{
                {FALSE,FALSE,FALSE,FALSE,FALSE},
                {{0,PARAM_OK,0.0f}},
                0U,
                TRUE,
                {FALSE,FALSE,FALSE,FALSE,FALSE},
                {FALSE,FALSE,FALSE,FALSE,FALSE},
                {FALSE,FALSE,FALSE,FALSE,FALSE},
                {TRUE,TRUE,TRUE,TRUE,TRUE},
                0U,
                0U,
                0U,
                {0U},
                {0U},
                {0U}
},
{
                {FALSE,FALSE,FALSE,FALSE,FALSE},
                {{0,PARAM_OK,0.0f}},
                0U,
                TRUE,
                {FALSE,FALSE,FALSE,FALSE,FALSE},
                {FALSE,FALSE,FALSE,FALSE,FALSE},
                {FALSE,FALSE,FALSE,FALSE,FALSE},
                {TRUE,TRUE,TRUE,TRUE,TRUE},
                0U,
                0U,
                0U,
                {0U},
                {0U},
                {0U}
},
{
                {FALSE,FALSE,FALSE,FALSE,FALSE},
                {{0,PARAM_OK,0.0f}},
                0U,
                TRUE,
                {FALSE,FALSE,FALSE,FALSE,FALSE},
                {FALSE,FALSE,FALSE,FALSE,FALSE},
                {FALSE,FALSE,FALSE,FALSE,FALSE},
                {TRUE,TRUE,TRUE,TRUE,TRUE},
                0U,
                0U,
                0U,
                {0U},
                {0U},
                {0U}
},
{
                {FALSE,FALSE,FALSE,FALSE,FALSE},
                {{0,PARAM_OK,0.0f}},
                0U,
                TRUE,
                {FALSE,FALSE,FALSE,FALSE,FALSE},
                {FALSE,FALSE,FALSE,FALSE,FALSE},
                {FALSE,FALSE,FALSE,FALSE,FALSE},
                {TRUE,TRUE,TRUE,TRUE,TRUE},
                0U,
                0U,
                0U,
                {0U},
                {0U},
                {0U}
},
{
                {FALSE,FALSE,FALSE,FALSE,FALSE},
                {{0,PARAM_OK,0.0f}},
                0U,
                TRUE,
                {FALSE,FALSE,FALSE,FALSE,FALSE},
                {FALSE,FALSE,FALSE,FALSE,FALSE},
                {FALSE,FALSE,FALSE,FALSE,FALSE},
                {TRUE,TRUE,TRUE,TRUE,TRUE},
                0U,
                0U,
                0U,
                {0U},
                {0U},
                {0U}
}};


/* STORE GLOBAL SETTINGS */

/*
 * Function                :  GlobalSettingsPush
 *
 * Description             :  This function copies the global settings to
 *                            backup structure, calculates crc for raw data,
 *                            transmits and saves the raw data in backup
 *                            structure.
 *
 * Formal parameter(s)     :  None
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */

void GlobalSettingsPush(void)
{
   T_UINT8 loop_sdi = 0;
   T_UINT8 loop_exx = 0;
   T_UINT32 *pu32_vn_ptr = ZERO;
   T_UINT32 u32_crc = ZERO;
   T_UINT16 u16_sequence = ZERO;
   T_A825_MESSAGE s_xm =  {
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


   /* hdudispfglobalsettings-GlobalSettingsPush-DB-LLR-002 */
   INIT_NSC_REQUEST(s_xm);
   s_xm.sID.PID.sid   = EISDSPLYGATEWAY_SID;
   s_xm.u8PaySize     = EIGHT;
   s_xm.sID.PID.rci = (T_UCHAR)(Du_position & THREE);
   *((T_UINT16 *)s_xm.u8PayLoad) = NSC_NVS;

   if(TRUE != Demo_mode)
   {
   /* hdudispfglobalsettings-GlobalSettingsPush-DB-LLR-001 */
   /* Copy all global settings into the backup structure. */
   Nv_storage.sGC.Active_eiu = Active_eiu;
   Nv_storage.sGC.Brightness_mode = Brightness_mode;
   Nv_storage.sGC.Cool_down_state = (T_COOLDOWN_STATE)Cool_down_select;
   Nv_storage.sGC.Auto_brightness = Auto_brightness;
   Nv_storage.sGC.sManual_brightness = Manual_brightness;
   /* Updated as per PR 100083 */
   Nv_storage.sGC.ePageNumber = Page_num;
   Nv_storage.sGC.eRevPageNumber = Toggle_screen;
   Nv_storage.sGC.Fuel_flow_state = Fuel_flow_select;
   for (loop_sdi = 0; loop_sdi < NUMBEROFENGINES; loop_sdi++)
   {
	   Nv_storage.sGC.s32DataExceed[loop_sdi] = S32_data_exceed[loop_sdi];
   }

   /* Updated per ECM 38, 39, 41*/
   Nv_storage.sGC.ExceedCount = Ex_id_count;
   Nv_storage.sGC.Overflow = Log_overflow;
   Nv_storage.sGC.FlightCount = Flight_count;
   Nv_storage.sGC.DemoMode = ZERO;
   for (loop_exx = 0; loop_exx < MAX_ELOG_EVENT; loop_exx++)
   {
	   Nv_storage.sGC.ExceedStartCheck[loop_exx] = Exceedance_startup_check[loop_exx];
   }
   Nv_storage.sGC.FaultCount = Flt_id_count;
   Nv_storage.sGC.FaultLogAdv = Fault_log_adv;
   Nv_storage.sGC.Ft_overflow = Ft_log_overflow;

   u32_crc = CrcCalculate(Nv_storage.sRaw.au32RawStorage, NV_SIZE);
   Nv_storage.sRaw.u32CRC = u32_crc;
	   pu32_vn_ptr = Nv_storage.sRaw.au32RawStorage;
   }
   else
   {
       /* hdudispfglobalsettings-GlobalSettingsPush-DB-LLR-003 */
	   Nv_storage_in.sGC.DemoMode = ZERO;
	   u32_crc = CrcCalculate(Nv_storage_in.sRaw.au32RawStorage, NV_SIZE);
	   Nv_storage_in.sRaw.u32CRC = u32_crc;
	   pu32_vn_ptr = Nv_storage_in.sRaw.au32RawStorage;
   }

   for(u16_sequence = ZERO; u16_sequence <= NV_SIZE; u16_sequence++, pu32_vn_ptr++)
   {
      *((T_UINT16 *)&(s_xm.u8PayLoad[2])) = u16_sequence;
      *((T_UINT32 *)(&(s_xm.u8PayLoad[4]))) = *pu32_vn_ptr;
	  /* hdudispfglobalsettings-GlobalSettingsPush-DB-LLR-004 */
      test_res = A8251Xmit(&s_xm);
      /* hdudispfglobalsettings-GlobalSettingsPush-DB-LLR-005 */
      if(test_res != A825_XM_OK)
      {
         test_res = (T_A825_XMITRESULT)FIVE;
      }
      else
      {
         ;/* Does nothing */
      }
      OsTimeDly(1);
   }

   /* hdudispfglobalsettings-GlobalSettingsPush-DB-LLR-006 */
   /* Transmit the "Save" command with address and 32 bit CRC. */
   *((T_UINT16 *)s_xm.u8PayLoad) = (T_UINT16)NSC_PUSH_MEM;
   s_xm.u8PaySize                    = TWO;
   A8251Xmit(&s_xm);

   if(TRUE == Demo_mode)
   {
      /* hdudispfglobalsettings-GlobalSettingsPush-DB-LLR-007 */
      Demo_mode_activate = TRUE;
   }
   else
   {
      ;/*Do nothing*/
   }
};

/*
 * Function                :  GlobalSettingsPull
 *
 * Description             :  This function Trigger the transmission of global
 *                            settings from 429 board.
 *
 * Formal parameter(s)     :  None
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */

/* Trigger the transmission of global settings from 429 board. */

void GlobalSettingsPull(void)
{
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

   /* hdudispfglobalsettings-GlobalSettingsPull-DB-LLR-001 */
   INIT_NSC_REQUEST(s_xm);
   s_xm.sID.PID.sid   = EISDSPLYGATEWAY_SID;
   s_xm.u8PaySize     = TWO;
   s_xm.sID.PID.rci = (T_UCHAR)(Du_position & THREE);
   *((T_INT16 *)s_xm.u8PayLoad) = (T_INT16)NSC_PULL_MEM;
   /* hdudispfglobalsettings-GlobalSettingsPull-DB-LLR-002 */
   A8251Xmit(&s_xm);
};

/*
 * Function                :  GlobalSettingsProcessNSC
 *
 * Description             :  This function Processes incoming GLOBAL Config Data.
 *
 * Formal parameter(s)     :  T_A825_MESSAGE *s_mess IN - ARINC message
 *                            to be processed.
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */

void GlobalSettingsProcessNSC(T_A825_MESSAGE *s_mess)
{
   T_UINT8 loop_sdi = 0;
   T_UINT8 loop_exx = 0;
   T_NSC_CODE node_service_code = NSC_IDS;
   T_UINT32 u32_data = ZERO;
   T_UINT32 u32_crc = ZERO;

   T_UINT16 u16_sequence = ZERO;

   /* hdudispfglobalsettings-GlobalSettingsProcessNSC-DB-LLR-005 */
   node_service_code = (T_NSC_CODE)(*((T_UINT16 *)s_mess->u8PayLoad));

   switch(node_service_code)
   {
      case NSC_NVS:
         /* hdudispfglobalsettings-GlobalSettingsProcessNSC-DB-LLR-001 */
         Pull_flag = TRUE;
         u16_sequence = *((T_UINT16 *)&(s_mess->u8PayLoad[TWO]));

         if(u16_sequence <= NV_SIZE)
         {
            u32_data = *((T_UINT32 *)(&(s_mess->u8PayLoad[FOUR])));
            Nv_storage_in.sRaw.au32RawStorage[u16_sequence] = u32_data;
         }
         else
         {
            ;/* Does nothing */
         }

         break;

      case NSC_PULL_MEM:

         /* hdudispfglobalsettings-GlobalSettingsProcessNSC-DB-LLR-002 */
         Nv_ram_read = TRUE;
         u32_crc = CrcCalculate(Nv_storage_in.sRaw.au32RawStorage, NV_SIZE);

         /* hdudispfglobalsettings-GlobalSettingsProcessNSC-DB-LLR-003 */
         if(u32_crc == Nv_storage_in.sRaw.u32CRC)
         {
            /* Copy all global settings into the backup structure. */
            OS_ENTER_CRITICAL();
            Active_eiu =         Nv_storage_in.sGC.Active_eiu;
            Brightness_mode =    Nv_storage_in.sGC.Brightness_mode;
            Cool_down_select =   (T_BOOL) Nv_storage_in.sGC.Cool_down_state;
            Auto_brightness =    Nv_storage_in.sGC.Auto_brightness;
            Manual_brightness = Nv_storage_in.sGC.sManual_brightness;
            /* Updated as per PR 100083 */
            Page_num =       Nv_storage_in.sGC.ePageNumber;
            Toggle_screen = Nv_storage_in.sGC.eRevPageNumber;
            Fuel_flow_select =  Nv_storage_in.sGC.Fuel_flow_state;
            for (loop_sdi = 0; loop_sdi < NUMBEROFENGINES; loop_sdi++)
            {
            	S32_data_exceed[loop_sdi] = Nv_storage_in.sGC.s32DataExceed[loop_sdi];
            }
            /* Updated per ECM 38, 39, 41*/
            Ex_id_count = (T_UINT16)(Nv_storage_in.sGC.ExceedCount);
            Log_overflow = (T_BOOL) Nv_storage_in.sGC.Overflow;
            Flight_count = Nv_storage_in.sGC.FlightCount;
            Demo_mode = (T_BOOL) Nv_storage_in.sGC.DemoMode;/* Always turn off */
            for (loop_exx = 0; loop_exx < MAX_ELOG_EVENT; loop_exx++)
            {
            	Exceedance_startup_check[loop_exx] =
            			(T_BOOL) Nv_storage_in.sGC.ExceedStartCheck[loop_exx];
            }
            Flt_id_count =  Nv_storage_in.sGC.FaultCount;
            Fault_log_adv =(T_BOOL) Nv_storage_in.sGC.FaultLogAdv;
            Ft_log_overflow = (T_BOOL) Nv_storage_in.sGC.Ft_overflow;

            if(TRUE == Demo_mode)
            {
               Active_eiu = EIU1;
               /*Push to Clear DemoMode for next Startup */
               GlobalSettingsSetSysInfo();
            }
            else
            {
               ; /*Do nothing */
            }

            if(TRUE==Cool_down_select)
            {
               Cool_down_state=ECOOLDOWN_ON;
            }
            else
            {
               ; /*Do nothing */
            }

            OS_EXIT_CRITICAL();
            Nv_crc_fail=FALSE;
         }
         else
         {
            Nv_crc_fail=TRUE;/* Does nothing */
         }

         Data_received = TRUE;

         break;

      /* hdudispfglobalsettings-GlobalSettingsProcessNSC-DB-LLR-004 */
      case NSC_PULL_RESEND:

         OsTimeDly(PULL_RESEND_TIME_TICK);
         GlobalSettingsPull();

         break;

      default:

         break;
   }
}

/*
 * Function                :  GlobalSettingsSetEIU
 *
 * Description             :  This function sets Active EIU.
 *
 * Formal parameter(s)     :  T_EIU eiu IN - active EIU number to be set
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */
/* Updated as per PR 100083 */
void GlobalSettingsSetEIU(T_EIU eiu)
{
   T_A825_MESSAGE   s_mess = {
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
   T_PARAM_READING temp = {ZERO};

   /* hdudispfglobalsettings-GlobalSettingsSetEIU-DB-LLR-006 */
   RTDGetParamDdw(0, &temp);  /*Check for heart beat message status */

   if (MISSING != temp.stat)
   {
      /* hdudispfglobalsettings-GlobalSettingsSetEIU-DB-LLR-001 */
      Active_eiu = eiu;

      /* hdudispfglobalsettings-GlobalSettingsSetEIU-DB-LLR-002 */
      INIT_NSC_REQUEST(s_mess);
      s_mess.sID.PID.sid    = EISDSPLY_SID;
      s_mess.u8PaySize      = THREE;
      s_mess.sID.PID.rci = (T_UCHAR)(Du_position & THREE);
      *((T_INT16 *)s_mess.u8PayLoad) = (T_INT16)NSC_SET_EIU;
      *((T_UINT8 *)(&(s_mess.u8PayLoad[2]))) = (T_UINT8)eiu;

      /* hdudispfglobalsettings-GlobalSettingsSetEIU-DB-LLR-003 */
      A8252Xmit(&s_mess);
   }
   else
   {
      ;/* Does nothing */
   }

}

/* Updated as per PR 100083 */
/*
 * Function                :  GlobalSettingsSetSysInfo
 *
 * Description             :  This function send message to get part number and CRC
 *                            of communication board.
 *
 * Formal parameter(s)     :  None
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */
void GlobalSettingsSetSysInfo(void)
{
   T_A825_MESSAGE  s_mess = {
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

   /* hdudispfglobalsettings-GlobalSettingsSetSysInfo-DB-LLR-001 */
   INIT_NOC_MESSAGE(s_mess);

   s_mess.u8PaySize      = ZERO;
   s_mess.sID.BID.doc = ACQUIRE;
   s_mess.sID.BID.rci = (T_UCHAR)(Du_position & THREE);

   A8251Xmit(&s_mess);
}

/* Updated per ECM 38, 39, 41*/
/*
 * Function                :  GlobalSettingsPushPeakLog
 *
 * Description             :  This function transmits and saves the peak log
 *                            data in NVRAM.
 *
 * Formal parameter(s)     :  None
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */

void GlobalSettingsPushPeakLog(void)
{
   T_UINT16 u16_sequence = ZERO;
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

   /*hdudispfglobalsettings-GlobalSettingsPushPeakLog-DB-LLR-001*/
   INIT_NOC_MESSAGE(s_xm);

   s_xm.u8PaySize     = EIGHT;
   s_xm.sID.PID.rci = (T_UCHAR)(Du_position & THREE);

   for(u16_sequence = ZERO;u16_sequence<EXCEED_LOG_SIZE;u16_sequence++)
   {
      if((Exceedance_log[u16_sequence].Exceedance_index > ZERO) &&
         (FALSE == Exceedance_log[u16_sequence].End_transmission))
      {
         /*hdudispfglobalsettings-GlobalSettingsPushPeakLog-DB-LLR-002*/
         *((T_UINT16 *)s_xm.u8PayLoad) = Exceedance_log[u16_sequence].Exceedance_index;

         if(TRUE == Exceedance_log[u16_sequence].Fst_log_rec_stat)
         {
            /* Xmit all peak log data. */
            s_xm.sID.BID.doc   = DIS_PEAK_ID;
            s_xm.u8PayLoad[2] = Exceedance_log[u16_sequence].Param_name[0];
            s_xm.u8PayLoad[3] = Exceedance_log[u16_sequence].Param_name[1];
            s_xm.u8PayLoad[4] = Exceedance_log[u16_sequence].Param_name[2];
            s_xm.u8PayLoad[5] = Exceedance_log[u16_sequence].Param_name[3];
            s_xm.u8PayLoad[6] = Exceedance_log[u16_sequence].Param_name[4];
            s_xm.u8PayLoad[7] = Exceedance_log[u16_sequence].Param_name[5];
            test_res = A8251Xmit(&s_xm);

            OsTimeDly(DELAY_40MS);

            if(test_res != A825_XM_OK)
            {
               test_res = (T_A825_XMITRESULT)FIVE;
            }
            else
            {
               ;/* Does nothing */
            }

            Exceedance_log[u16_sequence].Fst_log_rec_stat = FALSE;

         }
         else
         {
            ;/*Does nothing*/
         }

         if((TRUE == Exceedance_log[u16_sequence].Data_log_rec_stat)
             || (TRUE == Exceedance_log[u16_sequence].Flght_log_rec_stat)
          || (TRUE == Exceedance_log[u16_sequence].Lst_log_rec))
         {
            /*hdudispfglobalsettings-GlobalSettingsPushPeakLog-DB-LLR-003*/
            /* Xmit all peak log data. */
            s_xm.sID.BID.doc   = DIS_PEAK_DATA;
            *((T_INT32 *)(&(s_xm.u8PayLoad[2]))) = Exceedance_log[u16_sequence].Peak_value;
            *((T_UINT16 *)(&(s_xm.u8PayLoad[6]))) = Exceedance_log[u16_sequence].Flight_number;
            test_res = A8251Xmit(&s_xm);

            if(test_res != A825_XM_OK)
            {
               test_res = (T_A825_XMITRESULT)FIVE;
            }
            else
            {
               ;/* Does nothing */
            }

            if(TRUE == Exceedance_log[u16_sequence].Data_log_rec_stat)
            {
               Exceedance_log[u16_sequence].Data_log_rec_stat = FALSE;
            }
         else
         {
            ;/*Do nothing*/
         }
            if(TRUE == Exceedance_log[u16_sequence].Flght_log_rec_stat)
            {
               Exceedance_log[u16_sequence].Flght_log_rec_stat = FALSE;
            }
         else
         {
            ;/*Do nothing*/
         }
         }
         else
         {
            ; /*Do nothing */
         }

         /*hdudispfglobalsettings-GlobalSettingsPushPeakLog-DB-LLR-004*/
         /* Xmit all peak log data. */
         s_xm.sID.BID.doc   = DIS_PEAK_DUR;
         *((T_UINT32 *)(&(s_xm.u8PayLoad[2]))) = Exceedance_log[u16_sequence].Duration;
         *((T_UINT16 *)(&(s_xm.u8PayLoad[6]))) = ZERO;
         test_res = A8251Xmit(&s_xm);

         if(test_res != A825_XM_OK)
         {
            test_res = (T_A825_XMITRESULT)FIVE;
         }
         else
         {
            ;/* Does nothing */
         }


         if (TRUE == Exceedance_log[u16_sequence].Lst_log_rec)
         {
            Exceedance_log[u16_sequence].End_transmission = TRUE;
         }
         else
         {
            ; /*Do nothing */
         }

      }

   } /*end of for loop */

}

/*
 * Function                :  GlobalSettingsCheckExParam
 *
 * Description             :  This function checks exceedance log parameters
 *
 * Formal parameter(s)     :  None
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */

void GlobalSettingsCheckExParam(void)
{
   static T_BOOL init_exceed_id[5][18] = {FALSE};
   static T_BOOL init_peak_value[5][18] = {FALSE};
   static T_BOOL init_duration[5][18] = {FALSE};
   static T_UINT32 duration_counter[5][18] = {0};
   static T_BOOL timer_reset_state[7]={FALSE};
   T_BOOL flight_old_stat[90] = {FALSE};

   T_PARAM_READING exceed_read = {ZERO};
   T_PARAM_READING s32_data = {ZERO};
   T_UINT16 u8_index = 0;
   T_BOOL is_log_param = FALSE;
   T_UINT16 u16_i = 0;
   T_UINT16 u16_k = 0;
   T_UINT16 port_index = 0;
   T_UINT16 tag_index = 0;
   /*Updated as per  PR100196 */
   T_UINT16  exceed_log_index = 0;

   for (u16_k = 0; u16_k < FIVE; ++u16_k)
   {
      for (u16_i = 0; u16_i < Port1_label_count; ++u16_i)
      {
         if ((A429_data[0][u16_i].label == Elog_label[u16_k].elog_label)&&
        		 (A429_data[0][u16_i].sdi == Elog_label[u16_k].elog_sdi))
         {
            /*hdudispfglobalsettings-GlobalSettingsCheckExParam-DB-LLR-001*/
            port_index = (T_UINT16)(u16_i + 1);

            RTDGetParamDdw(port_index, &exceed_read);

            if (PARAM_OK == exceed_read.stat)
            {
               for (u8_index = 0; u8_index < MAX_ELOG_PARAM; u8_index++)
               {
                  /*hdudispfglobalsettings-GlobalSettingsCheckExParam-DB-LLR-002*/
                  is_log_param = (T_BOOL)((exceed_read.r>>u8_index) & (T_INT32)ONE);

                  /* Peak Value */
                  for (u16_i = 0; u16_i < Port1_label_count; ++u16_i)
                  {
                     if ((A429_data[0][u16_i].label ==
                           Elog_label[u16_k].elog_bit_label[u8_index])&&
                    		 (A429_data[0][u16_i].sdi == Elog_label[u16_k].elog_sdi))
                     {
                        port_index = (T_UINT16)(u16_i+1);
                        break;
                     }
                     else
                     {
                        ;/* Does nothing */
                     }
                  }

                  RTDGetParam(port_index, &s32_data);

                  /* Get the Exceedance Log index from the PDI Settings position */
                  exceed_log_index = (T_UINT16)((u16_k * MAX_ELOG_PARAM) + u8_index);

              /*hdudispfglobalsettings-GlobalSettingsCheckExParam-DB-LLR-003*/
                  if (TRUE == is_log_param &&
                	Elog_label[u16_k].elog_bit_label[u8_index]!=ZERO)
                  {
                     if ((TRUE != init_exceed_id[u16_k][u8_index]) &&
                         (PARAM_OK == s32_data.stat))
                     {
                        /* Exceedance ID */
                        init_exceed_id[u16_k][u8_index] = TRUE;
                        ++Ex_id_count;
                        Exceedance_log[exceed_log_index].Exceedance_index = Ex_id_count;

                        /* Parameter */
                        for (tag_index = 0; tag_index < PARAM_SIZE; tag_index++)
                        {
                           Exceedance_log[exceed_log_index].Param_name[tag_index] =
                           Elog_label[u16_k].elog_bit_param[u8_index][tag_index];
                        }
                        /*Set first log */
                        Exceedance_log[exceed_log_index].Fst_log_rec_stat = TRUE;
                        Exceedance_log[exceed_log_index].Lst_log_rec = FALSE;
                        Exceedance_log[exceed_log_index].End_transmission = FALSE;
                     }
                     else
                     {
                        ;/* Does nothing */
                     }

                /*hdudispfglobalsettings-GlobalSettingsCheckExParam-DB-LLR-004*/
                     if(PARAM_OK == s32_data.stat)
                     {
                      /*Store the previous peak value on Normal Operation */
                      Prev_peak_val[exceed_log_index] = s32_data.r;
                      timer_reset_state[exceed_log_index]=FALSE;
                     }
                     else
                     {
                      if(FALSE == timer_reset_state[exceed_log_index])
                      {
                         timer_reset_state[exceed_log_index]=TRUE;
                         Flight_timer_exceed[exceed_log_index]= ZERO;
                      }
                   else
                   {
                     ;/*Do nothing*/
                   }
                        /*Start timer */
                         if(TRUE == FlightTimerStartExceed(exceed_log_index))
                         {
                            if (PARAM_OK != s32_data.stat)
                            {
                              flight_old_stat[exceed_log_index] = TRUE;
                            }
                            else
                            {
                                ; /*Do nothing */
                            }
                         }
                   else
                   {
                     ;/*Do nothing*/
                   }
                     }

                     /*hdudispfglobalsettings-GlobalSettingsCheckExParam-DB-LLR-005*/
                     /* Duration */
                     if ((TRUE != init_duration[u16_k][u8_index])&& (PARAM_OK == s32_data.stat))
                     {
                        duration_counter[u16_k][u8_index] = ZERO;
                        init_duration[u16_k][u8_index] = TRUE;
                     }
                     else
                     {
                      ++duration_counter[u16_k][u8_index];

                      if(PARAM_OK == s32_data.stat)
                      {
                         Prev_duration_val[exceed_log_index] =
                               duration_counter[u16_k][u8_index];
                      }
                      else
                      {
                           ;/* Does nothing */
                      }

                         if(TRUE == flight_old_stat[exceed_log_index])
                         {
                         Exceedance_log[exceed_log_index].Duration =
                            (Prev_duration_val[exceed_log_index]  / (T_UINT32)FIVE) + TEN;
                         }
                         else
                         {
                         Exceedance_log[exceed_log_index].Duration =
                               (duration_counter[u16_k][u8_index]  / (T_UINT32)FIVE);

                         }
                     }

                     /*hdudispfglobalsettings-GlobalSettingsCheckExParam-DB-LLR-006*/
                     if ((TRUE != init_peak_value[u16_k][u8_index]) &&
                         (PARAM_OK == s32_data.stat))
                     {
                        init_peak_value[u16_k][u8_index] = TRUE;
                        Exceedance_log[exceed_log_index].Data_log_rec_stat = TRUE;
                        Exceedance_log[exceed_log_index].Peak_value = s32_data.r;
                     }
                     else if (((Exceedance_log[exceed_log_index].Peak_value < s32_data.r)
                         && (PARAM_OK == s32_data.stat))
                         || (TRUE == flight_old_stat[exceed_log_index]))
                     {
                        Exceedance_log[exceed_log_index].Data_log_rec_stat = TRUE;

                        if((TRUE == flight_old_stat[exceed_log_index]))
                        {
                           Exceedance_log[exceed_log_index].Peak_value =
                                 Prev_peak_val[exceed_log_index];
                           init_exceed_id[u16_k][u8_index] = FALSE;
                           flight_old_stat[exceed_log_index] = FALSE;
                           Exceedance_log[exceed_log_index].Lst_log_rec = TRUE;
                           init_duration[u16_k][u8_index] = FALSE;
                           init_peak_value[u16_k][u8_index] = FALSE;
                        }
                        else
                        {
                           Exceedance_log[exceed_log_index].Peak_value = s32_data.r;
                        }
                     }
                     else
                     {
                        ;
                     }


                     /*hdudispfglobalsettings-GlobalSettingsCheckExParam-DB-LLR-007*/
                     if(Exceedance_log[exceed_log_index].Flight_number != Flight_count)
                     {
                        Exceedance_log[exceed_log_index].Flght_log_rec_stat = TRUE;
                        Exceedance_log[exceed_log_index].Flight_number = Flight_count;
                     }
                     else
                     {
                        ; /*Do nothing */
                     }
                  }
                  else
                  {
                     ;/* Does nothing */
                  }

                  /*hdudispfglobalsettings-GlobalSettingsCheckExParam-DB-LLR-008*/
                  if ((TRUE == init_exceed_id[u16_k][u8_index])  &&  (TRUE != is_log_param))
                  {
                     /* Exceedance ID */
                     init_exceed_id[u16_k][u8_index] = FALSE;

                     /* Peak Value */
                     init_peak_value[u16_k][u8_index] = FALSE;

                     /* Duration */
                     init_duration[u16_k][u8_index] = FALSE;

                     if (Ex_id_count > EXCEED_ID_LOG_SIZE)
                     {
                        Log_overflow = TRUE;
                     }
                     else
                     {
                        ; /*Do nothing */
                     }
                     Exceedance_log[exceed_log_index].Lst_log_rec = TRUE;
                  }
                  else
                  {
                     ;/* Does nothing */
                  }
               }
            }
            else
            {
               ;/* Does nothing */
            }

            /*hdudispfglobalsettings-GlobalSettingsCheckExParam-DB-LLR-009*/
            break;
         }
         else
         {
            ;/* Does nothing */
         }
      }
   }
}

/*
 * Function                :  GlobalSettingsCheckTrig
 *
 * Description             :  This function checks exceedance log trigger condition
 *
 * Formal parameter(s)     :  None
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */

void GlobalSettingsCheckTrig(void)
{

   T_UINT8 u16_j = 0;
   T_UINT16 u16_i = 0;
   T_UINT8 condition_cnt[MAX_ELOG_EVENT]={0};
   T_UINT8 var_i = 0;
   T_BOOL checkexparam = FALSE;

   /*hdudispfglobalsettins-GlobalSettingsCheckTrig-DB-LLR-001*/
   if (TRUE != Nv_ram_read)
   {
      return;
   }
   else
   {
      ;/* Does nothing */
   }

   /*Function modified to consider the engines with same label and different SDIs */
   for(var_i=0;var_i<MAX_ELOG_EVENT;var_i++)

   {
	   /* Obtains the condition count */
	   /*hdudispfglobalsettings-GlobalSettingsCheckTrig-DB-LLR-002*/
	   condition_cnt[var_i] = Cond_cnt[var_i];

	   if (TRUE == Trig_setting[var_i].init_value)
       {
          for (u16_j = 0; u16_j < condition_cnt[var_i]; u16_j++)
          {
             for (u16_i = 0; u16_i < Port1_label_count; ++u16_i)
             {
                if ((A429_data[0][u16_i].label == Elog_trig[var_i].elog_trig_label[u16_j])&&
                		(A429_data[0][u16_i].sdi == Elog_trig[var_i].elog_trig_sdi[u16_j]))
                {
                	Trig_setting[var_i].port_index = (T_UINT16)(u16_i+1);
                   break;
                }
                else
                {
                   ;/* Does nothing */
                }
             }

             /*hdudispfglobalsettings-GlobalSettingsCheckTrig-DB-LLR-003*/
             RTDGetParam(Trig_setting[var_i].port_index,
            		 &Trig_setting[var_i].s32_data[u16_j]);

             /*hdudispfglobalsettings-GlobalSettingsCheckTrig-DB-LLR-004*/
             if ((ONE == CompareLimit((T_FLOAT)Trig_setting[var_i].s32_data[u16_j].r,
                    (T_FLOAT)((T_INT32)Elog_trig[var_i].elog_trig_start_val[u16_j] *
                    (T_INT32)TEN),Elog_trig[var_i].elog_trig_start_type[u16_j])) &&
                    (TRUE != Trig_setting[var_i].init_start[u16_j]) &&
					(PARAM_OK == Trig_setting[var_i].s32_data[u16_j].stat))
             {
            	Trig_setting[var_i].init_start[u16_j] = TRUE;
                Exceedance_startup_check[var_i] = FALSE;
             }
             else
             {
                ;/* Does nothing */
             }

             /*hdudispfglobalsettings-GlobalSettingsCheckTrig-DB-LLR-005*/
             if ((ONE == CompareLimit((T_FLOAT)Trig_setting[var_i].s32_data[u16_j].r,
                  (T_FLOAT)(Elog_trig[var_i].elog_trig_cross_val[u16_j] * TEN),
                  Elog_trig[var_i].elog_trig_cross_type[u16_j])) &&
            		 (TRUE == Trig_setting[var_i].init_start[u16_j]))
             {
            	Trig_setting[var_i].init_start[u16_j] = FALSE;
            	Trig_setting[var_i].init_cross[u16_j] = TRUE;

                if(FALSE == Trig_setting[var_i].state_var[u16_j])
                {
                	Trig_setting[var_i].Engine_timer[u16_j] = ZERO;
                }
                else
                {
                   ; /* Does nothing */
                }

                Trig_setting[var_i].state_var[u16_j] = TRUE;
             }
             else
             {
                ;/* Does nothing */
             }

             /*hdudispfglobalsettings-GlobalSettingsCheckTrig-DB-LLR-006*/
             if (TRUE == Trig_setting[var_i].init_cross[u16_j])
             {
            	Trig_setting[var_i].Engine_started[u16_j] =
                 FlightTimerStart((T_UINT32)Elog_trig[var_i].elog_trig_time[u16_j],u16_j,var_i);
             }
             else
             {
                ;/* Does nothing */
             }

             /*hdudispfglobalsettings-GlobalSettingsCheckTrig-DB-LLR-007*/
             /* Multiply by 10 for Floating point */
             if ((TRUE == Trig_setting[var_i].Engine_started[u16_j]) &&
            		 (ONE == (CompareLimit((T_FLOAT)Trig_setting[var_i].s32_data[u16_j].r,
                (T_FLOAT)((T_INT32)Elog_trig[var_i].elog_trig_cross_val[u16_j] * (T_INT32)TEN),
                 Elog_trig[var_i].elog_trig_cross_type[u16_j]))))
             {
            	 Trig_setting[var_i].tgr_fgt_cond++;

                if((u16_j == (condition_cnt[var_i]-1)) &&
                		(Trig_setting[var_i].tgr_fgt_cond == condition_cnt[var_i]))
                {
                   Trig_setting[var_i].tgr_fgt_cond = ZERO;
                   Trig_setting[var_i].init_value = FALSE;
                   /*Added to increase to flight Count only when all the Engines are grounded*/
                   if ((FALSE == Exceedance_startup_check[0]) &&
                		   (FALSE == Exceedance_startup_check[1])
                    && (FALSE == Exceedance_startup_check[2]) &&
					(FALSE == Exceedance_startup_check[3])
					&& (FALSE == Exceedance_startup_check[4]))
                   {
                	   Flight_count++;
                   }

                   Trig_setting[var_i].chck_trg_cnd = 1;
                   Exceedance_startup_check[var_i] = TRUE;
                }
                else if(u16_j == (condition_cnt[var_i]-1))
                {
                	Trig_setting[var_i].tgr_fgt_cond = ZERO;
                }
                else
                {
                   ;/*Do nothing*/
                }
             }
             else
             {
                ;/*Do nothing*/
             }
          }

          if((ONE == Trig_setting[var_i].chck_trg_cnd) ||
        		  (TRUE == Exceedance_startup_check[var_i]))
          {
             /*hdudispfglobalsettings-GlobalSettingsCheckTrig-DB-LLR-008*/
             GlobalSettingsCheckExParam();
          }
          else
          {
             ; /* Do nothing */
          }
       }
       else
       {
      /*hdudispfglobalsettings-GlobalSettingsCheckTrig-DB-LLR-009*/
    	   /*Check to call the CheckExParam function only once during a cycle*/
    	  if (FALSE == checkexparam)
    	  {
    		  checkexparam = TRUE;
    		  GlobalSettingsCheckExParam();
    	  }
      }
   }

   for(var_i=0;var_i<MAX_ELOG_EVENT;var_i++)
   {
       for (u16_j = 0; u16_j < condition_cnt[var_i]; u16_j++)
       {
          /*hdudispfglobalsettings-GlobalSettingsCheckTrig-DB-LLR-010*/
          for (u16_i = 0; u16_i < Port1_label_count; ++u16_i)
          {
             if ((A429_data[0][u16_i].label == Elog_trig[var_i].elog_trig_label[u16_j])&&
            		 (A429_data[0][u16_i].sdi == Elog_trig[var_i].elog_trig_sdi[u16_j]))
             {
            	 Trig_setting[var_i].port_index = (T_UINT16)(u16_i+1);
                break;
             }
             else
             {
                ;/* Does nothing */
             }
          }

          /*hdudispfglobalsettings-GlobalSettingsCheckTrig-DB-LLR-011*/
          RTDGetParam(Trig_setting[var_i].port_index,
        		  &Trig_setting[var_i].s32_data[u16_j]);

          /*hdudispfglobalsettings-GlobalSettingsCheckTrig-DB-LLR-012*/
          /* Multiply by 10 for Floating point */
          if ((TRUE == Trig_setting[var_i].init_cross[u16_j]) &&
        		  (TRUE == Trig_setting[var_i].Engine_started[u16_j]))
          {
             if(ONE != (CompareLimit((T_FLOAT)Trig_setting[var_i].s32_data[u16_j].r,
             (T_FLOAT)((T_INT32)Elog_trig[var_i].elog_trig_cross_val[u16_j] * (T_INT32)TEN),
               Elog_trig[var_i].elog_trig_cross_type[u16_j])))
             {
            	 Trig_setting[var_i].re_entry[u16_j] = TRUE;
             }
             else
             {
                ;/* Does nothing */
             }
          }
          else
          {
             ;/* Does nothing */
          }

          /* Multiply by 10 for Floating point */
          if ((TRUE == Trig_setting[var_i].re_entry[u16_j]) &&
        		  (ONE == (CompareLimit((T_FLOAT)Trig_setting[var_i].s32_data[u16_j].r,
                   (T_FLOAT)((T_INT32)Elog_trig[var_i].elog_trig_start_val[u16_j] *
                   (T_INT32)TEN),Elog_trig[var_i].elog_trig_start_type[u16_j]))))
          {

             /*hdudispfglobalsettings-GlobalSettingsCheckTrig-DB-LLR-013*/
        	 Trig_setting[var_i].tgr_fgt_reentry++;
        	 Trig_setting[var_i].re_entry[u16_j] = FALSE;
        	 Trig_setting[var_i].init_cross[u16_j]= FALSE;

             /*hdudispfglobalsettings-GlobalSettingsCheckTrig-DB-LLR-014*/
             if((u16_j == condition_cnt[var_i]-1) &&
            		 (Trig_setting[var_i].tgr_fgt_reentry == condition_cnt[var_i]))
             {
            	Trig_setting[var_i].init_value = TRUE;
                Exceedance_startup_check[var_i] = FALSE;
                Trig_setting[var_i].state_var[u16_j] = FALSE;
                Trig_setting[var_i].chck_trg_cnd = 0;
                Trig_setting[var_i].tgr_fgt_reentry = 0;
             }
             else if (u16_j == condition_cnt[var_i]-1)
             {
            	Trig_setting[var_i].tgr_fgt_reentry = 0;
             }
             else
             {
                ;/*Do nothing*/
             }
          }
          else
          {
             ;/* Does nothing */
          }
       }
    }
}

/*
 * Function                :  FlightTimerStart
 *
 * Description             :  This function starts the flight timer
 *
 * Formal parameter(s)     :  T_UINT32 trigger_time - holds the trigger time value
 *                        T_UINT8 flight_index - holds the flight index value
 *
 * Return Value            :  T_BOOL - Returns TRUE OR FALSE
 *
 * Assumption              :  None
 *
 */

T_BOOL FlightTimerStart(T_UINT32 trigger_time,
		T_UINT8 condition_index,T_UINT8 engine_index)
{
   T_UINT32 u32_flight_down = trigger_time * DEC_1000;
   static T_BOOL init_var[MAX_ELOG_EVENT][MAX_ELOG_EVENT] = {{TRUE,TRUE,TRUE,TRUE,TRUE},
		                                                     {TRUE,TRUE,TRUE,TRUE,TRUE},
		                                                     {TRUE,TRUE,TRUE,TRUE,TRUE},
		                                                     {TRUE,TRUE,TRUE,TRUE,TRUE},
		                                                     {TRUE,TRUE,TRUE,TRUE,TRUE}};

   /*hdudispfglobalsettings-FlightTimerStart-DB-LLR-001*/
   if (TRUE == init_var[engine_index][condition_index])
   {
      TimerInstall(&Trig_setting[engine_index].Engine_timer_mirror[condition_index]);
      TimerInstall(&Trig_setting[engine_index].Engine_timer[condition_index]);
      Trig_setting[engine_index].Engine_timer[condition_index] = ZERO;
      TimerPreset(&Trig_setting[engine_index].Engine_timer_mirror[condition_index],
    		  (T_INT32)Trig_setting[engine_index].Engine_timer[condition_index]);
      init_var[engine_index][condition_index] = FALSE;
   }
   else
   {
      ;/*Do nothing*/
   }
   /*hdudispfglobalsettings-FlightTimerStart-DB-LLR-002*/
   if (Trig_setting[engine_index].Engine_timer[condition_index] > u32_flight_down)
   {
       return TRUE;
   }
   else
   {
      ;/*Do nothing*/
   }
   /*hdudispfglobalsettings-FlightTimerStart-DB-LLR-003*/
   return FALSE;
}

/*
 * Function                :  FlightTimerStartExceed
 *
 * Description             :  This function starts the flight exceed timer
 *
 * Formal parameter(s)     :  T_UINT16 flight_index - holds the flight index value
 *
 * Return Value            :  T_BOOL - Returns TRUE OR FALSE
 *
 * Assumption              :  None
 *
 */

T_BOOL FlightTimerStartExceed(T_UINT16 flight_index)
{
   static T_BOOL init_var = TRUE;

   /*hdudispfglobalsettings-FlightTimerStartExceed-DB-LLR-001*/
   if (TRUE == init_var)
   {
      TimerInstall(&Flight_timer_mirror_exceed[flight_index]);
      TimerInstall(&Flight_timer_exceed[flight_index]);
      Flight_timer_exceed[flight_index] = ZERO;
      TimerPreset(&Flight_timer_mirror_exceed[flight_index],
           (T_INT32)Flight_timer_exceed[flight_index]);
      init_var = FALSE;
   }
   else
   {
      ;/*Do nothing*/
   }
   /*hdudispfglobalsettings-FlightTimerStartExceed-DB-LLR-002*/
   if (Flight_timer_exceed[flight_index] > TIME_FRAME)
   {
       return TRUE;
   }
   else
   {
      ;/*Do nothing*/
   }
   /*hdudispfglobalsettings-FlightTimerStartExceed-DB-LLR-003*/
   return FALSE;
}
