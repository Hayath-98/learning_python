/*
 ******************************************************************************
 * License Information  :  Howell Instruments, Inc.                           *
 *                         "Licensed Software" and "All rights reserved".     *
 ******************************************************************************
 *  File                : hdudispfpdicheck.h
 *
 *  Description         : This file provides definitions for all the required data from the PDI
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
 *  Author(s)           :
 *
 *  Version History     :
 *      1.1          Gururaj C       21-Jun-2020             100259
 *      1.2          Dhanalakshmi    29-Jun-2020             100259
 *      1.3          Dhanalakshmi    05-Aug-2020             100270
 *      1.4          Dhanalakshmi    12-Sep-2020             100276
 *      1.5          Dhanalakshmi    28-Sep-2020             100284
 *      1.6           Dhanalakshmi     20-Mar-2021             100331
 *      1.7           Dhanalakshmi     20-Mar-2021             100331
 *
 * Additional References : None
 *
 ******************************************************************************
 */

#ifndef _HDUDISPFPDICHECK_H_
#define _HDUDISPFPDICHECK_H_

#define MAX_ERROR_MSG                5
#define MAX_LIN_RANGE                100000
#define MIN_RANGE                    -90000
#define MAX_RANGE                    100000
#define MIN_LIN_RANGE                -90000
#define MAX_NO_LIN                   20
#define MAX_NO_LIM                   10
#define MAX_STRING_CHAR_TXT          30
#define MAX_NO_PTR                   5
#define MAX_LIN_ANGLE                360      /* (360/360.0)*32768.0 */
#define MIN_LIN_ANGLE                -360    /* (360/360.0)*32768.0 */
#define MAX_LABEL                    255
#define MAX_BNR_BITS                 18
#define MAX_START_BIT                29
#define MIN_START_BIT                11
#define MAX_BNR                      524287
#define MIN_BNR                      -524288
#define MAX_TIMEOUT                  600
#define MAX_BNR_OFFSET               1000
#define MIN_CAS_START_BIT            11
#define MAX_CAS_START_BIT            28
#define MAX_CAS_PRIORITY             64
#define MAX_CAS_ID                   7
#define MAX_CAS_NUM_ROWS             7
#define MAX_CAS_COLUMNS              3
#define MAX_TIMER                    300
#define MAX_WOG_START_BIT            28
#define MAX_ACDT_TIMER               1000
#define EXCEEDANCE_LOG_TRIG_TIME     3600
#define MAX_PAGE_NUM                 19
#define MAX_PAGE_MENU                16382
#define MAX_PAGE_MENU_10INCH         510
#define MAX_PAGE_NAME                20
#define MAX_CONFIG_NAME              20
#define MAX_CONFIG_VERSION           16
#define MAX_CONFIG_ENGINE            34
#define MAX_LIM_VAL_TYPE              6
#define MAX_SYMBOL_VAL                6
#define MAX_ELOG_BIT_PARAM            10
#define MIN_START_BIT                 11
#define MAX_START_BIT                 29
#define ACDT_X_AXIS					  47
#define ACDT_Y_AXIS					  45

#define BIT_ONE                       1
#define BIT_TWO                       2
#define BIT_THREE                     4
#define BIT_FOUR                      8
#define BIT_FIVE                      16
#define BIT_SIX                       32
#define BIT_SEVEN                     64
#define BIT_EIGHT                     128
#define BIT_NINE                      256
#define BIT_TEN                       512
#define BIT_ELEVEN                    1024
#define BIT_TWELVE                    2048
#define BIT_THIRTEEN                  4096
#define BIT_FOURTEEN                  8192
#define M_FP_COMPARE          0.000001f

extern T_CHAR Error_msg_string[5][40];
extern T_UINT16 Pdi_error_count;
extern T_BOOL Page_check[20];
extern T_BOOL Global_parameter_error;
extern T_BOOL Page_parameter_error[20];
extern T_UINT32 Timer_axis_error;
extern T_UINT32 Acdt_axis_error;
extern T_UINT32 Cas_error;
extern T_UINT32 Exceed_error;
extern T_UINT32 Ex_timer_error;
extern T_UINT8 Index_value;
extern void IntToStringTrim(T_UINT8 bit,T_UINT8 bit_size, T_CHAR *str);
extern void OctToStringTrim(T_UINT8 label,T_UINT8 label_size, T_CHAR *str);
extern void PdiDataCheck();

#endif /* _HDUDISPFPDICHECK_H_ */
