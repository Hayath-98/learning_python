/*
 ******************************************************************************
 * License Information  :  Howell Instruments, Inc.                           *
 *                         "Licensed Software" and "All rights reserved".     *
 ******************************************************************************
 *  File                : hdudispfglobalsettings.h
 *
 *  Description         : Contains prototype to read and write data to NVRAM
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
 *      1.3           Vinay H          23-Mar-2018             100196
 *      1.4           Vinay H          28-Mar-2018             100196
 *      1.5           Chaithra J       21-Jun-2020             100259
 *      1.6           Rona  BS         02-Jul-2020             100259
 *      1.7           Dhanalakshmi     20-Mar-2021             100331
 *      1.8           Dhanalakshmi     20-Mar-2021             100331
 *      1.9           Dhanalakshmi     16-Apr-2021             100339
 *
 * Additional References : None
 *
 ******************************************************************************
 */

#ifndef _HDUDISPFGLOBALSETTINGS_H_
#define _HDUDISPFGLOBALSETTINGS_H_

#include "hdudispfarinc825.h" /* Define the structure for an ARINC 825 Message. */
#include "hdudispfpara.h" /* prototype for builds faults, message and system information  */
#include "hdulibbasictypes.h" /* Standard basic data type definitions */
#include "hdudispfpdidata.h" /* provides pdi declarations */

#define MIN_MANUAL_BRIGHTNESS 5
#define MAX_MANUAL_BRIGHTNESS 10000
#define MIN_AUTO_BRIGHTNESS   25
#define MAX_AUTO_BRIGHTNESS   400

#define NV_SIZE 46    /* Max 100 bytes of Global Config Data. */
#define PARAM_SIZE  6
#define EXCEED_LOG_SIZE 90
#define TIME_FRAME  1000U
#define DEC_1000        1000U

typedef enum
{
   EBRIGHTNESS_MANUAL,
   EBRIGHTNESS_AUTO
}  T_BRIGHTNESS_MODE;

extern T_BRIGHTNESS_MODE   Brightness_mode;
extern T_INT16             Manual_brightness;
extern T_INT16             Auto_brightness;

typedef enum
{
   ECOOLDOWN_ON,
   ECOOLDOWN_OFF
} T_COOLDOWN_STATE;

typedef enum
{
   FUEL_FLOW_ON,
   FUEL_FLOW_OFF

} T_FUEL_FLOW_STATE;

extern T_FUEL_FLOW_STATE Fuel_flow_state;
extern T_COOLDOWN_STATE Cool_down_state;

typedef enum
{
   EIU1,
   EIU2
} T_EIU;

extern T_EIU Active_eiu;

typedef struct
{
   T_BRIGHTNESS_MODE    Brightness_mode;
   T_INT16              sManual_brightness;
   T_INT16              Auto_brightness;
   T_EIU                Active_eiu;
   T_COOLDOWN_STATE     Cool_down_state;
   T_EPAGE_NUM          ePageNumber;
   /* Updated as per PR 100083 */
   T_EPAGE_NUM          eRevPageNumber;
   T_FUEL_FLOW_STATE    Fuel_flow_state;
   T_INT32              s32DataExceed[4];
   /* Updated per ECM 38, 39, 41*/
   T_UINT16             ExceedCount;
   T_UINT8              Overflow;
   T_UINT16             FlightCount;
   T_UINT8              DemoMode;
   T_UINT8              ExceedStartCheck[MAX_ELOG_EVENT];
   T_UINT16             FaultCount;
   T_UINT8              FaultLogAdv;
   T_UINT8              Ft_overflow;
}  T_GLOBAL_CONFIG;

typedef struct
{
   T_UINT32 au32RawStorage[NV_SIZE];
   T_UINT32 u32CRC;
}  T_SRAW;

typedef union
{
   T_GLOBAL_CONFIG      sGC;
   T_SRAW               sRaw;
}  T_NV_STORAGE;

/* Updated per ECM 38, 39, 41*/
extern T_BOOL Data_received;
extern T_BOOL Demo_mode;
extern T_BOOL Demo_mode_activate;

typedef struct
{
   T_UINT16            Exceedance_index;
   T_UINT8             Param_name[PARAM_SIZE];
   T_INT32             Peak_value;
   T_UINT32            Duration;
   T_UINT16            Flight_number;
   /*Updated as per PR100196 */
   T_BOOL            Fst_log_rec_stat;
   T_BOOL            Lst_log_rec;
   T_BOOL            End_transmission;
   T_BOOL            Data_log_rec_stat;
   T_BOOL            Flght_log_rec_stat;
}  T_GLOBAL_EXCEED;

typedef struct
{
   T_BOOL Engine_started[MAX_ELOG_EVENT];
   T_PARAM_READING s32_data[MAX_ELOG_EVENT];
   T_UINT16 port_index;
   T_BOOL init_value;
   T_BOOL init_start[MAX_ELOG_EVENT];
   T_BOOL init_cross[MAX_ELOG_EVENT];
   T_BOOL re_entry[MAX_ELOG_EVENT];
   T_BOOL state_var[MAX_ELOG_EVENT];
   T_UINT8 tgr_fgt_reentry;
   T_UINT8 chck_trg_cnd;
   T_UINT8 tgr_fgt_cond;
   T_UINT8 condition_cnt[MAX_ELOG_EVENT];
   T_TIMER Engine_timer[MAX_ELOG_EVENT];
   T_TIMER Engine_timer_mirror[MAX_ELOG_EVENT];
}  T_GLOBAL_SETTINGSTRIG;


extern T_UINT16  Ex_id_count;
extern T_BOOL    Log_overflow;
extern T_BOOL    Ft_log_overflow;
extern T_UINT16  Flight_count;
extern T_GLOBAL_EXCEED Exceedance_log[EXCEED_LOG_SIZE];
extern T_GLOBAL_SETTINGSTRIG Trig_setting[5];

extern void GlobalSettingsPushPeakLog(void);
extern void GlobalSettingsCheckTrig(void);
extern T_BOOL FlightTimerStart(T_UINT32 trigger_time,
		T_UINT8 condition_index,T_UINT8 engine_index);
extern T_BOOL FlightTimerStartExceed(T_UINT16 flight_index);
extern void GlobalSettingsPush(void);
extern void GlobalSettingsPull(void);
extern void GlobalSettingsProcessNSC(T_A825_MESSAGE *s_mess);
extern void GlobalSettingsSetEIU(T_EIU eiu);

/* Updated as per PR 100083 */
extern void GlobalSettingsSetSysInfo(void);

extern T_INT32 S32_data_exceed[4];

extern T_BOOL Pull_flag;

extern T_BOOL Nv_crc_fail;

extern T_BOOL  Exceedance_startup_check[MAX_ELOG_EVENT];
#endif /* _HDUDISPFGLOBALSETTINGS_H_ */
