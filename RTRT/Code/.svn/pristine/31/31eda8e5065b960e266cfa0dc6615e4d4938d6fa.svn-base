/*
 ******************************************************************************
 * License Information  :  Howell Instruments, Inc.                           *
 *                         "Licensed Software" and "All rights reserved".     *
 ******************************************************************************
 *  File                : hdudispfpara.c
 *
 *  Description         : This function builds faults, message and system information list
 *                         and configures the top menu.
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
 *      1.3           Shruthi M N      13-Oct-2017             100083, 100087
 *      1.4           Shruthi M N      30-Oct-2017             100104
 *      1.5           Shilpa A R       09-Nov-2017             100164
 *      1.6           Rona B.S         23-Mar-2018             100196
 *      1.7           Shruthi M N      03-Apr-2018             100205
 *      1.8           Gururaj C        21-Jun-2020             100259
 *      1.9           Rona B S         29-Jun-2020             100259
 *      1.10          Dhanalakshmi     05-Aug-2020             100270
 *      1.11          Dhanalakshmi     20-Mar-2021             100331
 *      1.12          Dhanalakshmi     20-Mar-2021             100331
 *
 * Additional References : None
 *
 ******************************************************************************
 */

#include "hdudispfa429.h"  /* Routines for Arinc 429 */
#include "hdudispfpdidata.h" /* Extract the data from NOR flash */
#include "hdudispfrevno.h" /* contains rev no */
#include "hdudispfpara.h"  /* prototype for builds faults, message and system information  */
#include "hdulibbasictypes.h" /* Standard basic data type definitions */
#include "hdudispfconfig.h"  /* contains page and color config information */
#include "hdudispfparams.h"  /* provides the tags for various parameters and parameter units */
#include "hdudispfpdicheck.h" /*contains pdi check*/

#define MAX_CAUT_IN_ID        16

/*
 * Variables to suppress compiler warning for option -Wcast-qual.
 */
static T_CHAR Demo_mode_text[10] = "DEMO MODE";
static T_CHAR No_sys_info_text[12] = "No Sys Info";
static T_CHAR Disp_sw_info_text[22] = "DISPLAY SOFTWARE INFO";
static T_CHAR Comm_sw_info_text[28] = "COMMUNICATION SOFTWARE INFO";
static T_CHAR Disp_config_info_text[27] = "DISPLAY CONFIGURATION INFO";
static T_CHAR Xlink_fail_text[26] = "DISPLAY CROSSLINK FAILURE";
static T_CHAR No_eiu_comm_text[22] = "NO EIU COMMUNICATION";
static T_CHAR Pbit_err00_text[20] = "PBIT ERROR - ERR 00";
static T_CHAR Pbit_err01_text[20] = "PBIT ERROR - ERR 01";
static T_CHAR Pbit_err02_text[20] = "PBIT ERROR - ERR 02";
static T_CHAR Pbit_err03_text[20] = "PBIT ERROR - ERR 03";
static T_CHAR Pbit_err04_text[20] = "PBIT ERROR - ERR 04";
static T_CHAR Pbit_err05_text[20] = "PBIT ERROR - ERR 05";
static T_CHAR Pbit_err06_text[20] = "PBIT ERROR - ERR 06";
static T_CHAR Pbit_err07_text[20] = "PBIT ERROR - ERR 07";
static T_CHAR Pbit_err08_text[20] = "PBIT ERROR - ERR 08";
static T_CHAR Pbit_err09_text[20] = "PBIT ERROR - ERR 09";
static T_CHAR Pbit_err10_text[20] = "PBIT ERROR - ERR 10";
static T_CHAR Pbit_err11_text[20] = "PBIT ERROR - ERR 11";
static T_CHAR Cbit_err01_text[20] = "CBIT ERROR - ERR 01";
static T_CHAR Cbit_err02_text[20] = "CBIT ERROR - ERR 02";
static T_CHAR Cbit_err03_text[20] = "CBIT ERROR - ERR 03";
static T_CHAR No_inter_system_comm_text[30] = "NO INTERSYSTEM COMMUNICATION";
static T_CHAR Empty_strng[2] = "";
static T_CHAR Airframe_msg[32] = "AIRFRAME CONFIG MISMATCH";
static T_CHAR Pbit_err12_text[20] = "PBIT ERROR - ERR 12";
static T_CHAR No_msgs_text[12] = "No Messages";
static T_CHAR Empty_str[1] = "";
static T_CHAR Scu_probe_err01[19] = "SCU Probe ERROR 01";
static T_CHAR Scu_probe_err02[19] = "SCU Probe ERROR 02";
static T_CHAR Scu_probe_err03[19] = "SCU Probe ERROR 03";
static T_CHAR Scu_sys_status_err01[27] = "SCU System Status Error 01";
static T_CHAR Scu_sys_status_err02[27] = "SCU System Status Error 02";
static T_CHAR Scu_sys_status_err03[27] = "SCU System Status Error 03";
static T_CHAR Scu_sys_status_err04[27] = "SCU System Status Error 04";
static T_CHAR Scu_sys_status_err05[27] = "SCU System Status Error 05";
static T_CHAR Scu_arinc_err01[19] = "SCU ARINC Error 01";
static T_CHAR Scu_arinc_err02[19] = "SCU ARINC Error 02";


/*      M E S S A G E   P A G E    C O D E */
/* Updated as per PR 100083 */
T_UINT16 U16_message_words[MAX_MESSAGE_WORDS] = {0x0000,0x0000,0x0000};
T_UINT16 U16_old_message_words[MAX_MESSAGE_WORDS] = {0x0000,0x0000,0x0000};

/* MESSAGE MESSAGE LIST. */
T_CHAR *Message_list[MAX_MESSAGES+1] = {0};

/* New fault added?  This will be cleared by the menu code. */
T_BOOL   New_message = TRUE;

/* Default list if no faults. */
T_CHAR *Pc_empty_message_list[2] =
{
      &No_msgs_text[0],
      0
};

/* Updated as per PR 100083 */
static T_CHAR *Pc_message_text[MAX_MESSAGES] =
{
   &Xlink_fail_text[0],
   &No_eiu_comm_text[0],
   &Pbit_err00_text[0],
   &Pbit_err01_text[0],
   &Pbit_err02_text[0],
   &Pbit_err03_text[0],
   &Pbit_err04_text[0],
   &Pbit_err05_text[0],
   &Pbit_err06_text[0],
   &Pbit_err07_text[0],
   &Pbit_err08_text[0],
   &Pbit_err09_text[0],
   &Pbit_err10_text[0],
   &Pbit_err11_text[0],
   &Cbit_err01_text[0],
   &Cbit_err02_text[0],
   &Cbit_err03_text[0],
   &No_inter_system_comm_text[0],
   &Demo_mode_text[0],
   &Empty_strng[0],
   &Empty_strng[0],
   &Pbit_err12_text[0],
   &Airframe_msg[0],
   (T_CHAR *)&Error_msg_string[0],
   (T_CHAR *)&Error_msg_string[1],
   (T_CHAR *)&Error_msg_string[2],
   (T_CHAR *)&Error_msg_string[3],
   (T_CHAR *)&Error_msg_string[4],
   &Scu_probe_err01[0],
   &Scu_probe_err02[0],
   &Scu_probe_err03[0],
   &Scu_sys_status_err01[0],
   &Scu_sys_status_err02[0],
   &Scu_sys_status_err03[0],
   &Scu_sys_status_err04[0],
   &Scu_sys_status_err05[0],
   &Scu_arinc_err01[0],
   &Scu_arinc_err02[0]
};


T_CHAR *Pc_sys_info_list[MAX_SYSINFO_MESSAGES+1] = {0};

/* MESSAGE WORDS. */
/* Updtaed as per PR 100083 */
T_UINT16  U16_sys_info_words[MAX_SYSINFO_WORDS] = {0,0};

/* Default list if no faults. */
T_CHAR *Empty_sys_info_list[2] =
{
      No_sys_info_text,
      0
};

static T_CHAR *Pc_sys_info_text[MAX_MESSAGES] =
{
     Disp_sw_info_text,
     (T_CHAR *)App_revno,
     (T_CHAR *)Boot_revno,
     (T_CHAR *)Maint_revno,
     (T_CHAR *)Maint_config_revno,
     (T_CHAR *)Soft_loader_revno,
     (T_CHAR *)Empty_str,
     (T_CHAR *)Comm_sw_info_text,
     (T_CHAR *)Commf_part,
     (T_CHAR *)Commb_part,
     (T_CHAR *)Maint_part,
	 (T_CHAR *)Commsl_part,
     (T_CHAR *)Empty_str,
     (T_CHAR *)Disp_config_info_text,
     (T_CHAR *)Dau_config_id_dau,
     (T_CHAR *)Config_id,
      /*Config_crc,*/
     (T_CHAR *)Bitmap_revno,
     (T_CHAR *)Empty_str,
    /*AirframeInfo*/
    (T_CHAR *)Dau_config_info,
     (T_CHAR *)Aircraft_model,
     (T_CHAR *)Engine_type,
     (T_CHAR *)Engine_serial,
     (T_CHAR *)Aircraft_serial,
     (T_CHAR *)Aircraft_regstrn,
    (T_CHAR *)Empty_str,
    /*DAU SOFTWARE INFO*/
     (T_CHAR *)Eiu_heading,
     (T_CHAR *)Eiufli_part,
     (T_CHAR *)Eiucfg_part,
     (T_CHAR *)Eiucmub_part,
     (T_CHAR *)Eiucmuf_part,
     (T_CHAR *)Eiucmum_part
};

/* C A S   S Y S T E M   C O D E */
T_CAS_MESSAGE All_cas_messages[MAX_CAS_MESSAGES] = {0};

T_CAS_MSG_DEF Cas_msg[MAX_CAS_MESSAGES] = {{0}};
T_CAS_MSG Cas_messages_setting = {0};
T_UINT8 Cas_message_count = 0;

/* CAS Stack for the MD530F C30 */
T_ECAS_INDEX Cas_app_array[MAX_CAS_MESSAGES+1] =
{
  0
};


/* Updated as per PR 100083 */
/*
 * Function                :  CheckforNewMessages
 *
 * Description             :  This function checks for new messages
 *
 * Formal parameter(s)     :  None
 *
 * Return Value            :  T_UINT32 - new message count
 *
 * Assumption              :  None
 *
 */

T_UINT32 CheckforNewMessages(void)
{
   T_UINT32 new_msg = ZERO;
   T_UINT16 u16_i = 0;
   T_UINT16 u16_j = 0;
   T_UINT16 u16_bit_mask = 0;

   for(u16_j = 0; u16_j < MAX_MESSAGE_WORDS; u16_j++)
   {
      for(u16_i = 0; u16_i < MAX_CAUT_IN_ID ; u16_i++)
      {
          /*   hdudispfpara-CheckforNewMessages-DB-LLR-001 */
         u16_bit_mask = (T_UINT16)(0x0001<<u16_i);
         if((U16_message_words[u16_j] & u16_bit_mask) !=
               (U16_old_message_words[u16_j] & u16_bit_mask))
         {
            if(TRUE==((U16_message_words[u16_j]>>u16_i) & (T_UINT16)ONE))
            {
                /*   hdudispfpara-CheckforNewMessages-DB-LLR-002 */
               U16_old_message_words[u16_j] |= u16_bit_mask;
               new_msg += ONE;
            }
            else
            {
                /*   hdudispfpara-CheckforNewMessages-DB-LLR-003 */
               U16_old_message_words[u16_j] &= (T_UINT16)(~u16_bit_mask);
            }
         }
      }
   }
   /* hdudispfpara-CheckforNewMessages-DB-LLR-004 */
   return new_msg;
}

/*
 * Function                :  BuildMessageList
 *
 * Description             :  This function build a list of message.
 *
 * Formal parameter(s)     :  None
 *
 * Return Value            :  T_INT16 - Number of messages in list
 *
 * Assumption              :  None
 *
 */

T_INT16 BuildMessageList(void)
{
   T_UINT16 u16_word_cntr = ZERO;
   T_UINT16 u16_bit_mask = ZERO;

   T_CHAR **message_list_pointer = NULL;
   T_CHAR **message_message_pointer = NULL;

   T_INT16  s16_ret_val = (T_INT16)ZERO;

   /* hdudispfpara-BuildMessageList-DB-LLR-001 */
   message_list_pointer = Message_list;
   message_message_pointer = Pc_message_text;

   /* hdudispfpara-BuildMessageList-DB-LLR-002 */
   for(u16_word_cntr=ZERO; u16_word_cntr<MAX_MESSAGE_WORDS;u16_word_cntr++)
   {
      u16_bit_mask = ONE;
      while(u16_bit_mask)
      {
         if((U16_message_words[u16_word_cntr] & u16_bit_mask ) != ZERO)
         {
            *message_list_pointer = *message_message_pointer;
        	message_list_pointer += ONE;
            s16_ret_val = (T_INT16)((T_INT16)ONE + s16_ret_val);
         }
            /* Does nothing */
         message_message_pointer += ONE;
         u16_bit_mask =(T_UINT16)(u16_bit_mask << (T_UINT16)ONE);
      }
   }

   /* hdudispfpara-BuildMessageList-DB-LLR-003 */
   *message_list_pointer = ZERO;

   return(s16_ret_val);
}

/*
 * Function                :  ParaGetMessageCount
 *
 * Description             :  This function gives the message count.
 *
 * Formal parameter(s)     :  T_INT16  s16_message_number - IN message index number.
 *
 * Return Value            :  T_INT16 - Number of messages in list
 *
 * Assumption              :  None
 *
 */

T_INT16 ParaGetMessageCount(T_INT16  s16_message_number)
{
   T_INT16  s16_ret_val = ZERO;

   /* hdudispfpara-ParaGetMessageCount-DB-LLR-001 */
   s16_ret_val = BuildMessageList();

   if((s16_ret_val-1) < s16_message_number)
   {
      /* hdudispfpara-ParaGetMessageCount-DB-LLR-002 */
      return(T_INT16)(s16_ret_val-1);
   }
   else
   {
      /* hdudispfpara-ParaGetMessageCount-DB-LLR-003 */
      return(T_INT16)(s16_message_number);
   }
}

/*
 * Function                :  BuildSysInfoList
 *
 * Description             :  This function builds list of system information.
 *
 * Formal parameter(s)     :  None
 *
 * Return Value            :  T_INT16 - returns the Count
 *
 * Assumption              :  None
 *
 */
T_INT16 BuildSysInfoList(void)
{
   T_UINT16 u16_word_cntr = ZERO;
   T_UINT16 u16_bit_mask = ZERO;

   T_CHAR **sys_info_list_pointer = NULL;
   T_CHAR **sys_info_sys_info_pointer = NULL;

   T_INT16 s16_ret_val = ZERO;

   /* hdudispfpara-BuildSysInfoList-DB-LLR-001 */
   sys_info_list_pointer = Pc_sys_info_list;
   sys_info_sys_info_pointer = Pc_sys_info_text;

   /* hdudispfpara-BuildSysInfoList-DB-LLR-002 */
   for(u16_word_cntr=ZERO; u16_word_cntr<MAX_SYSINFO_WORDS;u16_word_cntr++)
   {
      u16_bit_mask = ONE;
      while(u16_bit_mask != ZERO)
      {
         if((U16_sys_info_words[u16_word_cntr] & u16_bit_mask) != ZERO )
         {
            *sys_info_list_pointer = *sys_info_sys_info_pointer;
            sys_info_list_pointer += ONE;
            s16_ret_val = (T_INT16)(s16_ret_val+(T_INT16)ONE);
         }
         sys_info_sys_info_pointer += ONE;
         u16_bit_mask = (T_UINT16)(u16_bit_mask << (T_UINT16)ONE);
      }
   }

   /* hdudispfpara-BuildSysInfoList-DB-LLR-003 */
   *sys_info_list_pointer = ZERO;

   return(s16_ret_val);
}

/*
 * Function                :  ParaGetSysInfoCount
 *
 * Description             :  This function gives the count for elements in list of system count.
 *
 * Formal parameter(s)     :  T_INT16 s16_sys_info_index - IN index value of list of system count.
 *
 * Return Value            :  T_INT16 - returns the Count
 *
 * Assumption              :  None
 *
 */

T_INT16 ParaGetSysInfoCount(T_INT16 s16_sys_info_index)
{
   T_INT16  s16_ret_val = ZERO;

   /* hdudispfpara-ParaGetSysInfoCount-DB-LLR-001 */
   s16_ret_val = BuildSysInfoList();

   if((T_INT16)(s16_ret_val-(T_INT16)ONE) < s16_sys_info_index)
   {
      /* hdudispfpara-ParaGetSysInfoCount-DB-LLR-002 */
      return(T_INT16)(s16_ret_val-(T_INT16)ONE);
   }
   else
   {
      /* hdudispfpara-ParaGetSysInfoCount-DB-LLR-003 */
      return(T_INT16)(s16_sys_info_index);
   }
}

/*
 * Function                :  ParaConfigTopMenu
 *
 * Description             :  This function configures the top menu.
 *
 * Formal parameter(s)     :  T_STEXTBOXDATA pps_items - IN Pointer to text box data
 *                            T_EPAGE_NUM page_num - IN Active page number.
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */

void ParaConfigTopMenu(T_STEXTBOXDATA **pps_items, T_EPAGE_NUM page_num)
{
   T_STEXTBOXDATA **pps_next_item = NULL;
   T_UINT8 indx=1;
   pps_next_item = pps_items;

   if(Page_settings.page_num==page_num)
   {
      while(indx<=MAX_BUTTONS)
      {
         if(ONE == ((Page_settings.page_menu>>indx) & EXTR_LAST_BIT))
         {
            /* hdudispfpara-ParaConfigTopMenu-DB-LLR-001 */
            TextBoxOn(*pps_next_item);
            pps_next_item++;
         }
         else
         {
            /* hdudispfpara-ParaConfigTopMenu-DB-LLR-002 */
            TextBoxOff(*pps_next_item);
            pps_next_item++;
         }
         indx++;
      }
   }

}
