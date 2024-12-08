/*
 ******************************************************************************
 * License Information  :  Howell Instruments, Inc.                           *
 *                         "Licensed Software" and "All rights reserved".     *
 ******************************************************************************
 *  File                : hdudispfpara.h
 *
 *  Description         : prototype to builds faults, message and system information list
 *                         and configures the top menu
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
 *      1.1           Shilpa A R       11-Sep-2017             100064.
 *      1.2           Rona B S         10-Oct-2017             100064
 *      1.3           Shruthi M N      13-Oct-2017             100073,100083,100087
 *      1.4           Shilpa A R       09-Nov-2017             100164
 *      1.5           Gururaj C        21-Jun-2020             100259
 *      1.6           Rona B S         29-Jun-2020             100259
 *      1.7           Rona B S         12-Sept-2020            100276
 *      1.8           Dhanalakshmi     20-Mar-2021             100331
 *      1.9           Dhanalakshmi     20-Mar-2021             100331
 *
 * Additional References : None
 *
 ******************************************************************************
 */

#ifndef _HDUDISPFPARA_H_
#define _HDUDISPFPARA_H_

#include "hdudispftextbox.h"  /* routines for text box draw and updtaes */
#include "hdudispftimer.h"  /* increment a set of user installed timers. */
#include "hdudispfrtd.h"  /* defines structure, enum of A825 incomming data. */
#include "hdulibbasictypes.h" /* Standard basic data type definitions */

/* Updated as per PR 100083 */
typedef enum
{
      EPAGE0 = 0,
      EPAGE1,
      EPAGE2,
      EPAGE3,
      EPAGE4,
      EPAGE5,
      EPAGE6,
      EPAGE7,
      EPAGE8,
      EPAGE9,
      EPAGE10,
      EPAGE11,
      EPAGE12,
      EPAGE13,
      EPAGE14,
      EPAGE15,
      EPAGE16,
      EPAGE17,
      EPAGE18,
      EPAGE19,
      EPAGEMAX,
      EPAGEINVALID = 255
}  T_EPAGE_NUM;

/* MESSAGE WORDS. */
/* Updtaed as per PR 100083 */

#define MAX_MESSAGE_WORDS  3

#define MAX_MESSAGES    MAX_MESSAGE_WORDS*16
extern T_UINT16   U16_message_words[MAX_MESSAGE_WORDS];


extern T_INT16 ParaGetMessageCount(T_INT16  s16MessageNumber);
extern T_CHAR *Message_list[MAX_MESSAGES+1];
extern T_CHAR *Pc_empty_message_list[];
extern T_BOOL New_message;
extern T_UINT32 CheckforNewMessages(void);
/* Updtaed as per PR 100083 */
#define MAX_SYSINFO_WORDS  2
#define MAX_SYSINFO_MESSAGES  MAX_SYSINFO_WORDS*16
extern T_INT16 ParaGetSysInfoCount(T_INT16 s16_sys_info_index);
extern T_CHAR *Pc_sys_info_list[MAX_SYSINFO_MESSAGES+1];
extern T_CHAR *Empty_sys_info_list[];
extern T_UINT16  U16_sys_info_words[MAX_SYSINFO_WORDS];
extern T_INT16 BuildMessageList(void);
extern T_INT16 BuildSysInfoList(void);

extern void ParaConfigTopMenu(T_STEXTBOXDATA **pps_items, T_EPAGE_NUM page_num);

#define MAX_CAS_LENGTH     32    /* Maximum number of chars in a cas message. */
#define MAX_CAS_MESSAGES   64    /* Must be a factor of 8 */
#define MAX_FLAG_WORDS     (MAX_CAS_MESSAGES/8)
#define MAX_BUTTONS        13
#define EXTR_LAST_BIT      0x1

typedef enum CAS_INDEX
{
   CAS_DELIM = 0,
   AIR_FILTER_CLOGGED,
   AIRFRAME_FUEL_FILTER,
   OVERRIDE_FAULT,
   ANTI_ICE_ON_OFF,
   ANTI_ICE_FAIL,
   CH_A_BEC_ACTIVE,
   CH_B_BEC_ACTIVE,
   BATTERY_OVERTEMP_140F,
   BATTERY_OVERTEMP_160F,
   STARTER_ON,
   IGNITION_ON,
   CHANNEL_A_CAPABLE_OF_CONTROL,
   CHANNEL_B_CAPABLE_OF_CONTROL,
   FADEC_FAIL,
   EEC_A_FAIL,
   EEC_B_FAIL,
   ENGINE_CHIP_DETECTOR,
   ENGINE_FIRE,
   ENGINE_OUT,
   FADEC_FAIL_SPARE,  /* Previously referred as FADEC_fail. */
   FADEC_SYSTEM_MANUAL,
   FADEC_ECU_DEGRADED,
   FUEL_LOW,
   GENERATOR_OUT,
   LIMIT_FAULT,
   MAIN_ROTOR_CHIP_DETECTOR,
   RESTART_FAULT,
   AFT_XMSN_CHIP_DETECTOR,
   TRANSMISSION_OIL_PRESSURE,
   TRANSMISSION_OIL_TEMPERATURE,
   LOW_ROTOR,
   ENGINE_FAULT,
   AUTO_RE_IGNITION_ACTIVE,
   MAINTENANCE_ACTION,
   EOT_CAS,
   EOP_CAS,
   SCAVENGE_OIL_FILTER_BYPASS,
   TOT_CAS,
   TRQ_CAS,
   WOG,
   CHANNEL_A_B_IDENTIFIER,
   THIS_CHANNEL_IN_CONTROL,
   FUEL_FILTER_IMPENDING_BYPASS,
   FUEL_FILTER_BYPASS_A429,
   FUEL_FLOW,
   SKIP1,
   SKIP2,
  Overspeed
}  T_ECAS_INDEX;

typedef struct
{
   T_EPENCOLOR ePenColor;
   T_CHAR           acCASText[MAX_CAS_LENGTH+1];
   T_UINT8        u8Stat;
   T_TIMER           Flash_timer;
}  T_CAS_MESSAGE;

typedef struct
{
   T_EPENCOLOR ePenColor;
   T_SDISLOC      sOrigin;
   T_UINT8        row;
   T_UINT8        column;
   T_UINT16        rowHeight;
   T_UINT16       columnWidth;
   T_ETXFONT      eFont;
   T_TIMER        adv_flash_timer;
   T_TIMER        caut_flash_timer;
   T_TIMER        warn_flash_timer;
   T_UINT8       cas_redx_txt[32];
}  T_CAS_MSG;

typedef enum CAS_TYPE
{
   CAS_ADVISORY = 0,
   CAS_CAUTION,
   CAS_WARNING
}T_CAS_TYPE;

typedef struct
{
   T_EPENCOLOR    ePenColor;
   T_UINT8        acCASText[MAX_CAS_LENGTH+1];
   T_UINT8        u8Start;
   T_UINT8        priority;
   T_CAS_TYPE     type;
   T_UINT8        Id;
   T_UINT8        label;
   T_UINT8        Status;

}  T_CAS_MSG_DEF;

#define REV_VID 1U

/* All possible CAS messages. */
extern T_CAS_MESSAGE All_cas_messages[MAX_CAS_MESSAGES];

/* Array of indexes into Cas_messages in priority order.*/
extern enum CAS_INDEX Cas_app_array[MAX_CAS_MESSAGES+1];


extern T_CAS_MSG_DEF Cas_msg[MAX_CAS_MESSAGES];
extern T_CAS_MSG Cas_messages_setting;
extern T_UINT8  Cas_message_count;

#endif /* _HDUDISPFPARA_H_ */
