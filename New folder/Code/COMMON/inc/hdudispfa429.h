/*
 ******************************************************************************
 * License Information  :  Howell Instruments, Inc.                           *
 *                         "Licensed Software" and "All rights reserved".     *
 ******************************************************************************
 *  File                : hdudispfa429.h
 *
 *  Description         : This file defines the drivers and labels of the a429.
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
 *  Author(s)           : Rona B.S
 *
 *  Version History     :
 *
 * <Version No.>     <Author>          <Date>         <Problem Report No.>
 *
 *      1.1          Rona B.S        11-Sep-2017             100064
 *      1.2          Rona B.S        10-Oct-2017             100064
 *      1.3          Shruthi M N     13-Oct-2017             100083
 *      1.4          Shruthi M N     04-Nov-2017             100156
 *      1.5          Rona B.S        23-Mar-2018             100196
 *      1.6          Vinay H         30-Mar-2018             100196
 *      1.7          Chaithra J      21-Jun-2020             100259
 *      1.8          Rona B S        01-Jul-2020             100259
 *      1.9          Dhanalakshmi    05-Aug-2020             100270
 *      1.10         Dhanalakshmi    28-Sep-2020             100284
 *      1.11         Dhanalakshmi    20-Mar-2021             100331
 *      1.12         Dhanalakshmi    20-Mar-2021             100331
 *      1.13         Chaithra J      04-Mar-2022             100368
 *
 * Additional References : None
 *
 *****************************************************************************
 */

#ifndef _HDUDISPFA429_H_
#define _HDUDISPFA429_H_

#include "hdudispfarinc825.h"  /* Define the structure for an ARINC 825 Message. */
#include "hdulibbasictypes.h"      /* Standard basic data type definitions */
#include "hdudispfmenu.h"            /* contains prototype for menu module*/

/* Updated as per PR 100083 */
#define REVNO_LEN 16U
#define CRC_LEN   4U
#define BITMAP_REVNO_LEN      25
#define ENG_CONFIG_LEN        34
#define BITMAP_REVNO_ERR      24576
#define BITMAP_REVNO_ERR1     3
#define CONFIG_VER_LEN        31
#define CONFIG_VER_ERR        57344
#define CONFIG_VER_ERR1       2
#define REVNO_MAX_LEN         25
#define APP_REVNO_ERR         67
#define BOOT_REVNO_ERR        69
#define MAINT_REVNO_ERR       73
#define MAINT_CONF_REVNO_ERR  81
#define SL_REVNO_ERR          97
#define PART_MAX_LEN          25
#define COMMF_PART_ERR        4480
#define COMMB_PART_ERR        4736
#define MAINT_PART_ERR        5248
#define COMSL_PART_ERR        6272
#define EIUFLI_PART_ERR       1024
#define EIUCFG_PART_ERR       2048
#define EIUCMUB_PART_ERR      4096
#define EIUCMUF_PART_ERR      8192
#define EIUCMUM_PART_ERR      16384
#define DATA_28_BIT           28
#define SYS_INFO_WORDS_48     48
#define SYS_INFO_WORDS_64     64
#define SYS_INFO_WORDS_80     80
#define DAU_SOFTWARE_INFO_VAL 768 /*Sets empty string and dau Info */
#define CAU_WARN_MAX_ID 6
#define DDW_SIG_BIT     19

#define DAU_CONFIGURATION_INFO_VAL 4
#define ARCFT_MDL_PART_ERR    8
#define ENGN_TYP_PART_ERR     16
#define ENGN_SER_PART_ERR     32
#define ARCFT_SER_PART_ERR    64
#define ARCFT_REG_PART_ERR    128
#define ARCFT_ENGN_TYP_ERR    64
#define ARCFT_ENGN_TYP_ERR_NEG 0xFFBF
#define LABEL_0360    0360
#define LABEL_0370    0370
#define LABEL_051    051
#define LABEL_052    052
#define LABEL_0244   0244
#define CALILABELCOUNT 2
#define LABEL_0240    0240
#define LABEL_0273    0273
#define LABEL_0272    0272
#define LABEL_0250    0250
#define LABEL_0247    0247
#define LABEL_055     055
#define LABEL_057     057
#define LABEL_0346    0346
extern T_UINT16 Scu_timer[3];
extern T_FLOAT Scu_bg_lim_val[2];
extern T_UINT8 Scu_fty_offset_flag;
extern T_UINT8 Calibration_label[CALILABELCOUNT];

typedef struct
{
   T_UINT8 sequence;
   T_UINT8 data1;
   T_UINT8 data2;
}T_SYS_INFO_STRUCT;

typedef enum
{
   BNR =280,
   BCD,
   DDW
}T_A429_DATA_TYPE;
typedef struct
{
   T_UINT8 label;
   T_UINT8 sdi;
   T_A429_DATA_TYPE type;
   T_UINT8 sig_bits;
   T_FLOAT scale_factor;
   T_UINT8 start_bit;
   T_FLOAT min_val;
   T_FLOAT max_val;
   T_UINT32 offset;
   T_UINT16 timeout;
}T_A429_DATA_STRUCT;

extern T_A429_DATA_STRUCT A429_data[2][256];
extern T_UINT8  Commf_part[31];
extern T_UINT8  Commb_part[31];
extern T_UINT8  Maint_part[31];
extern T_UINT8  Commsl_part[31];
extern T_UINT8  App_revno[31];
extern T_UINT8  Boot_revno[31];
extern T_UINT8  Maint_revno[31];
extern T_UINT8  Maint_config_revno[31];
extern T_UINT8  Soft_loader_revno[31];
extern T_UINT8  Bitmap_revno[25];
/*Updtaed as per PR 100083 */
extern T_UINT8  Eiu_heading[18];
extern T_UINT8 Config_id[55];
extern T_UINT8 Dau_config_id_disp[55];
extern T_UINT8 Dau_config_id_dau[55];
extern T_UINT8 Config_crc[55];
extern T_UINT8  Eiufli_part[31];
extern T_UINT8  Eiucfg_part[31];
extern T_UINT8  Eiucmub_part[31];
extern T_UINT8  Eiucmuf_part[31];
extern T_UINT8  Eiucmum_part[31];
extern T_BOOL A429_data_recieved;
extern T_BOOL Cas_data_recieved;
extern T_BOOL Cas_wog_data_recieved;
extern T_UINT8 Cas_ssm;
extern T_UINT32 Dau_timer;
extern T_UINT16 Port1_label_count;
extern T_UINT16 Port2_label_count;
extern T_UINT8 Du_position;
extern T_BOOL Du_identified;
extern T_UINT16 Cas_label_start_idx;
extern T_UINT16 Data_cnt;
extern T_BOOL  Fault_log_adv;

extern T_BOOL Offset_bool[NUMBEROFENGINES];
extern T_BOOL Gain_bool[NUMBEROFENGINES];

extern void A429ProcessA825(T_A825_MESSAGE  *s_mess);
/*Updtaed as per PR 100083 */
extern void BinAsciiCRC(T_ULONG x_val, T_CHAR *out_buf);
extern void MemCpy (void* p_dest, const void* p_src, T_UINT16 count);
extern void MemSet (void* p_dest, T_UINT16 val, T_UINT32 cnt);
extern void ProcessSWPartNum(T_A825_MESSAGE  *s_mess);
extern void SetSysInfoWords(T_UINT8 u8_index, T_UINT8 data1, T_UINT8 data2);
extern void ProcessSysInfoWords(void);
extern void A429Init();
extern void ProcessF4PbitErr(T_A825_MESSAGE  *s_mess);
extern void ProcessF4CbitErr(T_A825_MESSAGE  *s_mess);
extern void CalibrationLabels();

/*Updated as per PR100196 */
extern T_UINT8  Dau_config_info[25];
extern T_UINT8  Aircraft_model[60];
extern T_UINT8  Engine_type[60];
extern T_UINT8  Engine_serial[50];
extern T_UINT8  Aircraft_serial[50];
extern T_UINT8  Aircraft_regstrn[50];
extern T_BOOL A429_data_recieved_0370;

extern void SetSysAirFrameWords(T_UINT8 u8_index, T_UINT8 data1, T_UINT8 data2);
extern void ProcessAirframeInfoWords(void);
extern T_BOOL StringCompare(T_CHAR *char1, T_CHAR *char2);
#endif /* _HDUDISPFA429_H_ */

