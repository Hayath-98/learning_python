/*
 ******************************************************************************
 * License Information  :  Howell Instruments, Inc.                           *
 *                         "Licensed Software" and "All rights reserved".     *
 ******************************************************************************
 *  File                : hdudispflmsscu.h
 *
 *  Description         : This file contains functions prototypes for
 *                        hdudispflmsscu.c
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
 *      1.1         Dhanalakshmi     20-Mar-2021             100331
 *      1.2         Dhanalakshmi     20-Mar-2021             100331
 *      1.3         Chaithra J       04-Mar-2022             100368
 *
 * Additional References : None
 *
 *****************************************************************************
 */

#ifndef _HDUDISPFLMS_H_
#define _HDUDISPFLMS_H_

#include "hdulibbasictypes.h"      /* Standard basic data type definitions */
#include "hdudispfpdidata.h"  /* Extracts the data from NOR flash */
#include "hdudispfucos.h"  /* defines the implementation of uC/OS routines  */
#include "hdudispfparams.h"  /* provides the tags for various parameters and parameter units. */
#include "hdudispfrtd.h"  /* Provide mapping for all A825 incoming parameters */
#include "hdulibbasictypes.h" /* Standard basic data type definitions */
#include "hdudispfoscpu.h"    /* OS function declarations */
#include "hdudispfa429.h"  /* Routines for arinc 429 */
#include "hdudispftimer.h"         /* Consistency Check*/


#define MAX_FAULT_LOG 10 /* 3 probe errors, 5 system status errors and 2  arinc errors  */
#define FT_LOG_SIZE 100
#define M_ENGSTART 55.0f

typedef enum
{
	PROBE_ERROR=1,
	SYS_STATUS_ERROR,
	ARINC_ERROR,
	NO_ERROR
}T_FAULT_TYPE;

typedef enum
{
	MISSING_PROBE_ERROR=1,
	SHORTED_PROBE_ERROR,
	FUEL_EXCITATION_ERROR,
	NO_PROBE_FAULT
}T_PROBE_FAULTS;

typedef enum
{
	POWER_SUPPLY_FAULT=1,
	APP_CRC_ERROR,
	MFG_CRC_ERROR,
	CONFIG_TABLE_CRC_ERROR,
	INVALID_TANK_TABLE,
	NO_SYS_FAULT
}T_SYS_FAULTS;

typedef enum
{
	INVALID_NO_ARINC_SIGNAL=1,
	DATA_OUT_OF_RANGE,
	NO_ARINC_FAULT
}T_ARINC_FAULTS;

typedef struct
{
    T_UINT16 Fault_index;
	T_UINT16 flight_number;
	T_FAULT_TYPE fault_type;
	T_UINT8 error_code;
	T_UINT32 timestamp;
	T_INT32 param_data[6];
	T_BOOL initial_fault_index;
	T_UINT32 start_duration;
	T_UINT32 stop_duration;
	T_BOOL param_data_present[6];
	T_BOOL data_present;
	T_BOOL fault_active_flag;
	T_BOOL fault_data_write;
	T_BOOL Last_ft_record;
	T_BOOL end_ft_transmission;
	T_BOOL param_data_write[6];
}T_FAULT_LOG;

typedef struct
{
	T_UINT8 fault_label;
	T_PARAM_READING label_data;
}T_FAULT_DATA;

extern T_FLOAT N1_value;
extern T_FAULT_DATA Fault_data[6];
extern T_FAULT_LOG Fault_log_structure[MAX_FAULT_LOG];
extern T_UINT16 Scu_error_code;
extern T_UINT16  Flt_id_count;
extern T_TIMER Fault_timer[6];

extern void ScuRTDGetParam(T_UINT16 a429_tag, T_PARAM_READING *ps_dest,
		T_A429_DATA_TYPE a429_type);
void ScuRTDSetParam(T_UINT8 channel, T_UINT16 a429_tag, T_UINT8 rtd_tag,
		T_FLOAT s32_data, T_RTD_STATUS ertd_stat);
extern void ScuRTDWatchdog(void);
extern void ScuRTDInit(void);

extern void ProcessLmsScuSysStatusErr(T_UINT32 data, T_UINT8 status);
extern void ProcessLmsScuProbeErr(T_UINT32 data, T_UINT8 status);
extern void ProcessingArinc01Fault(void);
extern void PushFaultLog(void);

#endif /* _HDUDISPFLMS_H_ */
