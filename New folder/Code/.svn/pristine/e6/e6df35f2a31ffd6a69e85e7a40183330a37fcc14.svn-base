/*
 ******************************************************************************
 * License Information  :  Howell Instruments, Inc.                           *
 *                         "Licensed Software" and "All rights reserved".     *
 ******************************************************************************
 *  File                : hdudispfa429.c
 *
 *  Description         : This file defines the a429 driver and its labels.
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
 *      1.3          Shruthi M N     15-Oct-2017             100083
 *      1.4          Shruthi M N     30-Oct-2017             100104
 *      1.5          Shruthi M N     04-Nov-2017             100116,100156
 *      1.6          Rona B.S        23-Mar-2018             100196
 *      1.7          Rona B.S        28-Mar-2018             100196
 *      1.8          Shruthi M N     03-Apr-2018             100205
 *      1.9          Rona B.S        16-Apr-2018             100211
 *      1.10         Chaithra J      21-Jun-2020             100259
 *      1.11         Rona B S      	 29-Jun-2020             100259
 *      1.12         Rona B S      	 24-Jul-2020             100259
 *      1.13         Dhanalakshmi    05-Aug-2020             100270
 *      1.14         Dhanalakshmi    12-Sep-2020             100276
 *      1.15         Dhanalakshmi    28-Sep-2020             100284
 *      1.16         Dhanalakshmi    20-Mar-2021             100331
 *      1.17         Dhanalakshmi    20-Mar-2021             100331
 *      1.18         Dhanalakshmi    20-Mar-2021             100331
 *      1.19         Dhanalakshmi    03-Apr-2021             100330
 *      1.20         Dhanalakshmi    16-Apr-2021             100339
 *      1.21         Dhanalakshmi    13-May-2021             100350
 *      1.22         Chaithra J      04-Mar-2022             100368
 *
 * Additional References : None
 *
 *****************************************************************************
 */

#include "hdudispflmsscu.h"  /* SCU rtd processing and error codes  */
#include "hdudispfa429.h"  /* Routines for arinc 429 */
#include "hdudispfcas.h"   /* prototypes for CAS extraction, sorting and initialization */
#include "hdudispfdauprofile.h"  /* defines the constants for ARINC 825  Message Traffic.*/
#include "hdudispfglobalsettings.h"  /* Routines to read and write data to NVRAM  */
#include "hdudispfrtd.h"   /* defines structure, enum of A825 incoming data. */
#include "hdulibbasictypes.h" /* Standard basic data type definitions */
#include "hdudispfpara.h"        /* prototype for builds faults, message and system information */
#include "hdudispfarinc825.h"   /* Define the structure for an ARINC 825 Message. */
#include "hdudispftext.h"       /* Routines which maintain text display and updates */
/* Updated as per PR 100083 */
#include "hdudispfrevno.h"  /* contains rev no */
#include "hdudispfpdidata.h" /* Extract the data from NOR flash */
#include "hdudispfgrapp.h"  /* routines for all graph */
#include "hdudispfpbit.h"        /* contains prototypes for PBIT test. */
#include "hdulibcorecm7.h"     /* Cortex-M7 processor and core peripherals */
#include "hdudispfmenu.h"            /* contains prototype for menu module*/
#include "hdudispfmdff.h" /* contains Fuel flow functionalities */

#define EXTRACT_1ST_BYTE 0x00000FF
#define HEX_F0           0xF0
#define HEX_0F           0x0F
#define HEX_CC           0xCC
#define HEX_33           0x33
#define HEX_AA           0xAA
#define HEX_55           0x55
#define EXTRACT_2BYTE    0x0000FFFF
#define HEX_7F           0x7F
T_UINT8 Calibration_label[CALILABELCOUNT] = {LABEL_051,LABEL_052};

/* Updated as per PR 100083 */
#define SEVENTEEN                17U
#define TWENTY_FOUR              24U
#define REVNO_DISP_FLIGHT_CRC    0x0817FFFC
#define REVNO_DISP_BOOT_PN       0x0800FFEC
#define REVNO_DISP_BOOT_CRC      0x0800FFFC
#define REVNO_DISP_MAINT_PN      0x080BFFEC
#define REVNO_DISP_MAINT_CRC     0x080BFFFC
#define REVNO_DISP_MAINT_CFG_PN  0x08010000
#define REVNO_DISP_MAINT_CFG_CRC 0x08017FFC
#define REVNO_DISP_SL_PN         0x0803FFEC
#define REVNO_DISP_SL_CRC        0x0803FFFC
#define REVNO_BMP_PN             0x6321FFEC
#define REVNO_BMP_CRC            0x6321FFFC
#define REVNO_PDI_CRC            0x63FFFFFC
#define REVNO_LEN                16U
#define CRC_LEN                  4U
#define SYSINFO_LABEL_WORDS      81
#define TO_HEX(i)               ((T_CHAR)(i <= 9 ? '0' + i : 'A' - 10 + i))

/*Updated as per PR100196 */
#define AIRFRAME_LABEL_WORDS      36

/* Updated as per PR 100083 */
#define BIT_SHIFT_BY_512         512
#define BIT_SHIFT_BY_1024        1024
#define BIT_SHIFT_BY_256         256
#define BIT_SHIFT_BY_2048        2048
#define BIT_SHIFT_BY_4096        4096
#define BIT_SHIFT_BY_128         128
#define BIT_SHIFT_BY_4           4
#define SHIFT_BY_28              28
#define SHIFT_BY_24              24
#define SHIFT_BY_20              20
#define SHIFT_BY_16              16
#define SHIFT_BY_12              12
#define SHIFT_BY_8               8
#define SHIFT_BY_4               4
#define EXT_BIT_28_31            0xF0000000
#define EXT_BIT_24_27            0x0F000000
#define EXT_BIT_20_23            0x00F00000
#define EXT_BIT_16_19            0x000F0000
#define EXT_BIT_12_15            0x0000F000
#define EXT_BIT_8_11             0x00000F00
#define EXT_BIT_4_7              0x000000F0
#define EXT_BIT_0_3              0x0000000F
#define MAX_64_BIT               0xFFFFFFFF
#define BUF_LEN_22               22
#define BUF_LEN_6                6
#define BUF_LEN_16               16
#define CHAR_H                   'H'
#define CHAR_LEN_6               6
#define CHAR_LEN_17              17
#define MAX_32           0xFFFFFFFF

#define BIT_16_SET      32768

/* Updated as per PR 100083 */
T_UINT8 App_revno[31] = "DISFA ";
T_UINT8 Boot_revno[31] = "DISBL ";
T_UINT8 Maint_revno[31] = "DISMA ";
T_UINT8 Maint_config_revno[31] = "DISMC ";
T_UINT8 Soft_loader_revno[31] = "DISSL ";
T_UINT8 Bitmap_revno[25] = {0};
T_UINT8  Commf_part[31] = "COMFA ";
T_UINT8  Commb_part[31] = "COMBL ";
T_UINT8  Maint_part[31] = "COMMA ";
T_UINT8  Commsl_part[31] = "COMSL ";
/* Updated as per PR 100083 */
T_UINT8  Eiu_heading[18] = " ";
T_UINT8 Config_id[55] = {0};
T_UINT8 Dau_config_id_disp[55] = {0};
T_UINT8 Dau_config_id_dau[55] = {0};
T_UINT8 Config_crc[55] = {0};
T_UINT8  Eiufli_part[31]= {0};   /*"EIUFA "*/
T_UINT8  Eiucfg_part[31]=  {0};  /*"EIUCA "*/
T_UINT8  Eiucmub_part[31]= {0};  /*"CMUBL "*/
T_UINT8  Eiucmuf_part[31]= {0};  /*"CMUFA "*/
T_UINT8  Eiucmum_part[31]= {0};  /*"CMUMA "*/
T_BOOL A429_data_recieved = FALSE;
T_BOOL A429_data_recieved_0370 = FALSE;
T_BOOL Cas_data_recieved = FALSE;
T_BOOL Cas_wog_data_recieved = FALSE;
T_UINT8 Cas_ssm = 0;
T_UINT32 Dau_timer=0;
T_UINT16 Scu_timer[3]={0,0,0};
T_UINT8 Du_position=0;
T_BOOL Du_identified = FALSE;
static T_UINT16 U16_wdog = 0;
T_UINT16 Data_cnt=0;

T_BOOL  Fault_log_adv = FALSE;
/* Updated as per PR 100083 */
/* MESSAGE WORDS. */
static T_SYS_INFO_STRUCT  Sys_info_words[SYSINFO_LABEL_WORDS] = {{0,0,0}};
T_A429_DATA_STRUCT A429_data[2][256]={{{0}}};
T_UINT16 Port1_label_count=0;
T_UINT16 Port2_label_count=0;
T_UINT16 Cas_label_start_idx=0;

T_BOOL Offset_bool[NUMBEROFENGINES]={FALSE};
T_BOOL Gain_bool[NUMBEROFENGINES]={FALSE};

static void Process429Words(T_INT32 i32_arinc_word, T_UINT8 channel);

/* Updated as per PR100196 */
T_UINT8  Dau_config_info[25] = {0};
T_UINT8  Aircraft_model[60]=   "AIRCRAFT MODEL ";
T_UINT8  Engine_type[60]=      "ENGINE TYPE    ";
T_UINT8  Engine_serial[50]=    "ENGINE SN      ";
T_UINT8  Aircraft_serial[50]=  "AIRCRAFT SN    ";
T_UINT8  Aircraft_regstrn[50]= "AIRCRAFT REGN  ";

#define ARCFT_MDL_BYTE   7
#define ENGINE_TYPE_BYTE 15
#define ENGINE_SER_BYTE  23
#define AICFT_SER_BYTE   31
#define AICFT_REGS_BYTE  35
#define CHAR_LEN_24      24

static T_SYS_INFO_STRUCT Sys_airframe_words[AIRFRAME_LABEL_WORDS] = {{0,0,0}};

T_FLOAT Scu_bg_lim_val[2] = {0.0f, 0.0f};
T_UINT8 Scu_fty_offset_flag = ZERO;

/*
 * Function                :  Process429Words
 *
 * Description             :  This function is used to process A429 words.
 *
 * Formal parameter(s)     :  T_INT32 i32_arinc_word - IN A429 Words.
 *                            T_UINT8 channel -IN Selected channel
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */
static void Process429Words(T_INT32 i32_arinc_word, T_UINT8 channel)
{
    T_UINT8 u8_label = ZERO,
            u8_sdi = ZERO,
            u8_ssm = ZERO,
            u8_id = ZERO;
    T_INT32 sign = ZERO;
    T_INT32 s32_data_neg = ZERO;
    T_INT32 data_zeros = ZERO;
    T_FLOAT s32_data = ZERO;
    /* Updated as per PR 100083 */
   T_UINT8  u8_sequence = ZERO;
   T_UINT16 data = ZERO,
         u16_i=ZERO,
         max_label=ZERO;
   T_UINT8 data1 = ZERO;
   T_BOOL label_found=FALSE;
   T_UINT8 data2 = ZERO;
   T_UINT8 airframe_data1 = ZERO;
   T_UINT8 airframe_data2 = ZERO;
   T_UINT8 airframe_sequence = ZERO;
   T_UINT8 loop_i = 0;
   T_UINT8 engine_sdi = 0;
   T_BOOL source_eiu1 = FALSE,
		   source_eiu2 = FALSE;
   T_UINT8 u8_timer_id = ZERO;
   static T_BOOL ff_once_flag =FALSE;
   T_UINT8 tmr_index = ZERO;

   /*hdudispfa429-Process429Words-DB-LLR-001*/
   /* extract out Label */
   u8_label = (T_UINT8) ((T_UINT32) i32_arinc_word & EXTRACT_1ST_BYTE);

   /*Flip MSB with LSB to read correct octal value */
   u8_label = (T_UINT8)((u8_label & HEX_F0)>>FOUR|(u8_label & HEX_0F)<<FOUR);
   u8_label = (T_UINT8)((u8_label & HEX_CC)>>TWO|(u8_label & HEX_33)<<TWO);
   u8_label = (T_UINT8)((u8_label & HEX_AA)>>ONE|(u8_label & HEX_55)<<ONE);

   /*hdudispfa429-Process429Words-DB-LLR-002*/
    /* extract out SDI */
   u8_sdi = (T_UINT8) ((T_UINT32) i32_arinc_word>>EIGHT & THREE);
   /* Updated as per PR 100083 */

   /*hdudispfa429-Process429Words-DB-LLR-003*/
    /* extract out SSM */
   u8_ssm = (T_UINT8) (((T_UINT32) i32_arinc_word>>TWENTY_NINE) & THREE);

   if(0 == channel)
   {
      max_label=Port1_label_count;
   }
   else
   {
      max_label=Port2_label_count;
   }

   /* Check if sdi's are considered for determining the engines */
   if (ONE == Config_data.eng_sdi)
   {
	   engine_sdi = u8_sdi;
	   if (Config_data.channels.u16_x == channel)
	   {
		   source_eiu1 = TRUE;
	   }
	   else if (Config_data.channels.u16_y == channel)
	   {
		   source_eiu2 = TRUE;
	   }
	   else
	   {
		   ;
	   }
   }
   else
   {
	   engine_sdi = 0;
	   if (ONE == u8_sdi)
	   {
		   source_eiu1 = TRUE;
	   }
	   else if (TWO == u8_sdi)
	   {
		   source_eiu2 = TRUE;
	   }
	   else
	   {
		   ;
	   }

   }


   /*Calibration*/
   if (((EIU1 == Active_eiu)&&(TRUE == source_eiu1)) ||
	  ((EIU2 == Active_eiu)&&(TRUE == source_eiu2)))
   {
	   /* OFFSET */
	   /*Process only the first occurence or after losing DAU connection*/
	   if ((LABEL_051 == u8_label) && (FALSE == Offset_bool[engine_sdi]))
	   {
		   Offset_value_cal[engine_sdi] = ((i32_arinc_word >> TEN) & (0xFFFF));
		   OffsetInttoIntArray(engine_sdi);
		   Offset_bool[engine_sdi]  = TRUE;
	   }
	   /* Gain */
       else if ((LABEL_052 == u8_label) && (FALSE == Gain_bool[engine_sdi]))
	   {
	   	   Gain_value_cal[engine_sdi] = ((i32_arinc_word >> TEN) & (0xFFFF));
	   	   GainInttoIntArray(engine_sdi);
    	   Gain_bool[engine_sdi]  = TRUE;
	   }
	   else
	   {
	   	   ; /* Do Nothing*/
	   }
   }
   else
   {
	   ;
   }

   while((u16_i<max_label) && (TRUE != label_found))
   {
       /*hdudispfa429-Process429Words-DB-LLR-004*/
      if((u8_label==A429_data[channel][u16_i].label) &&
    	 (engine_sdi==A429_data[channel][u16_i].sdi))
      {
         label_found=TRUE;
      }
      else
      {
         u16_i++;
      }
   }
   /*When Configured labels are received, Dau_timer is reseted so that REDX is not displayed*/
   if(TRUE == label_found)
   {
      Dau_timer=0;
   }
   else
   {
      ;  /* Does nothing */
   }
   /*'data_zeros' variable to check Data fields unused bits to zero*/
   for(loop_i = 0;loop_i < (A429_data[channel][u16_i].start_bit - 1 -(T_INT32)TEN);loop_i++)
   {
	   data_zeros += (T_INT32)1<<loop_i;
   }
   /*hdudispfa429-Process429Words-DB-LLR-025*/
   /* check if LMS SCU is is present */
 if((ONE == Config_data.scu_enable) && (TRUE==label_found) && (ZERO == Pbit_test_result))
 {
        if((BNR==A429_data[channel][u16_i].type) &&
         (((T_INT32)ZERO) == (T_INT32)(i32_arinc_word>>TEN & (T_INT32)data_zeros))
         && ((LABEL_0247 ==u8_label) || (LABEL_055 ==u8_label) || (LABEL_057 ==u8_label)))
         {

            sign=(T_INT32)((T_FLOAT)((i32_arinc_word>>TWENTY_EIGHT)& (T_INT32)ONE));

            if (((T_INT32)ZERO) != sign && DATA_28_BIT ==\
               (A429_data[channel][u16_i].sig_bits+
                A429_data[channel][u16_i].start_bit-1))
               {
                     s32_data_neg =\
                  	(T_INT32)((i32_arinc_word>>(A429_data[channel][u16_i].start_bit-1))&
                     (T_INT32)((T_UINT32)MAX_32>>((T_UINT32)THIRTY_TWO-
                        ((T_UINT32)A429_data[channel][u16_i].sig_bits+1))));
                        /* One's Complement*/
                        s32_data_neg = ~(T_INT32)s32_data_neg;
                        /* Two's Complement*/
                        s32_data_neg = (T_INT32)(((T_INT32)s32_data_neg &
                        (T_INT32)((T_UINT32)MAX_32>>((T_UINT32)THIRTY_TWO-
                           ((T_UINT32)A429_data[channel][u16_i].sig_bits+1)))) + 1);
                        /* After two's Complement multiply with -1*/
                        s32_data =(T_FLOAT)((T_FLOAT)s32_data_neg*
                        (A429_data[channel][u16_i].scale_factor)*(-1));

               }
              /*hdudispfa429-Process429Words-DB-LLR-026*/
                else
                 {
                     s32_data = \
                     (T_FLOAT)((i32_arinc_word>>(A429_data[channel][u16_i].start_bit-1))&
                     (T_INT32)((T_UINT32)MAX_32>>((T_UINT32)THIRTY_TWO-
                     (T_UINT32)A429_data[channel][u16_i].sig_bits)))*
                     (A429_data[channel][u16_i].scale_factor);
                    }
                  /*hdudispfa429-Process429Words-DB-LLR-027*/
                     s32_data= (T_FLOAT)(s32_data+(T_FLOAT)A429_data[channel][u16_i].offset);

                    /*hdudispfa429-Process429Words-DB-LLR-028*/
                if((LABEL_0247 == A429_data[channel][u16_i].label) &&
              	  (((((EIU1 == Active_eiu)&&(ONE == channel)) ||
              	  ((EIU2 == Active_eiu)&&(ZERO == channel))) && (TWO == Du_position))
			   || ((((EIU1 == Active_eiu)&&(ZERO == channel)) ||
                ((EIU2 == Active_eiu)&&(ONE == channel))) && (ONE == Du_position))))
                {
                     Scu_timer[0] = ZERO;
                     /* updates fuel qty A429 max value with max display value */
			   /* received from EIU */
                     if(ONE == ((Scu_fty_offset_flag >> ONE) & ONE))
                     {
                         A429_data[channel][u16_i].max_val = Scu_bg_lim_val[1];
                     }
                     else
                     {
                     	 ;/*Do nothing */
                     }
               /*hdudispfa429-Process429Words-DB-LLR-029*/
                     ScuRTDSetParam(channel,(T_UINT16)(u16_i+1), ZERO, s32_data, \
                  		   (T_RTD_STATUS) u8_ssm);
                        /*hdudispfa429-Process429Words-DB-LLR-030*/
                     ProcessingArinc01Fault();
                }
              /*hdudispfa429-Process429Words-DB-LLR-031*/
                else if((LABEL_055 == A429_data[channel][u16_i].label) &&
               	  (((((EIU1 == Active_eiu)&&(ONE == channel)) ||
               	  ((EIU2 == Active_eiu)&&(ZERO == channel))) && (TWO == Du_position))
				  || ((((EIU1 == Active_eiu)&&(ZERO == channel)) ||
	               ((EIU2 == Active_eiu)&&(ONE == channel))) && (ONE == Du_position))))
                {
                	 if(THREE == u8_ssm)
                	 {
                	   Scu_bg_lim_val[0] = s32_data;
                 if((s32_data >= 40)  && (s32_data <= 50))
                 {
                	  /* set the 1st bit when SSM is valid :indicates 055 label is received */
                	   Scu_fty_offset_flag = Scu_fty_offset_flag | ONE;
                	 /* reset the 3rd bit when label 055 data SSM is valid */
                	   Scu_fty_offset_flag = Scu_fty_offset_flag & 0xFB;
                 }
                 else
                 {
               	  /* set the 3rd bit when label 055 data SSM is invalid */
               	  Scu_fty_offset_flag = Scu_fty_offset_flag | FOUR;
                 }
                	 }
                	 else
                	 {
                		 /* set the 3rd bit when label 055 data SSM is invalid */
                		 Scu_fty_offset_flag = Scu_fty_offset_flag | FOUR;
                		/* reset the 1st bit when SSM is invalid */
                		 Scu_fty_offset_flag = Scu_fty_offset_flag & 0xFE;
                	 }
                }
             /*hdudispfa429-Process429Words-DB-LLR-032*/
                else if((LABEL_057 == A429_data[channel][u16_i].label) &&
               	  (((((EIU1 == Active_eiu)&&(ONE == channel)) ||
               	  ((EIU2 == Active_eiu)&&(ZERO == channel))) && (TWO == Du_position))
				  || ((((EIU1 == Active_eiu)&&(ZERO == channel)) ||
	               ((EIU2 == Active_eiu)&&(ONE == channel))) && (ONE == Du_position))))
                {
                	 if(THREE == u8_ssm)
                	 {
                	    Scu_bg_lim_val[1] = s32_data;

                	  if((s32_data >= 151)  && (s32_data <= 425))
                	  {
                  	 /* set the 2nd bit when SSM is valid :indicates 057 label is received */
                  	  Scu_fty_offset_flag = Scu_fty_offset_flag | TWO;

                      /* reset the 4th bit when label 057 data SSM is valid */
                	      Scu_fty_offset_flag = Scu_fty_offset_flag & 0xF7;
                	  }
                	  else
                	  {
                		/* set the 4th bit when label 057 data SSM is invalid */
                		Scu_fty_offset_flag = Scu_fty_offset_flag | EIGHT;
                	  }
                	 }
                	 else
                	 {
                		/* set the 4th bit when label 057 data SSM is invalid */
                		Scu_fty_offset_flag = Scu_fty_offset_flag | EIGHT;
                		/* reset the 2nd bit when label 057 SSM is invalid */
                		Scu_fty_offset_flag = Scu_fty_offset_flag & 0xFD;
                	 }
                }
                /*hdudispfa429-Process429Words-DB-LLR-033*/
                else
                {
                	 ;
                }
               }
               /*hdudispfa429-Process429Words-DB-LLR-034*/
               else if((DDW==A429_data[channel][u16_i].type) &&
                    (LABEL_0272 == A429_data[channel][u16_i].label) &&
                  (ZERO == u8_sdi) &&
            	  (((((EIU1 == Active_eiu)&&(ONE == channel)) ||
            	  ((EIU2 == Active_eiu)&&(ZERO == channel))) && (TWO == Du_position))
	              || ((((EIU1 == Active_eiu)&&(ZERO == channel)) ||
                  ((EIU2 == Active_eiu)&&(ONE == channel))) && (ONE == Du_position))))
                {
                  Scu_timer[1] = ZERO;
                  s32_data = (T_FLOAT)(i32_arinc_word>>TEN);
                  ScuRTDSetParam(channel,(T_UINT16)(u16_i+1), ONE, s32_data, \
                 		 (T_RTD_STATUS) u8_ssm);
                  ProcessLmsScuSysStatusErr(((T_UINT32) i32_arinc_word>>EIGHT & 0X1FFFFF),\
                 (T_RTD_STATUS) u8_ssm);
                    /*hdudispfa429-Process429Words-DB-LLR-035*/
                    ProcessingArinc01Fault();
               }
             /*hdudispfa429-Process429Words-DB-LLR-036*/
               else if((DDW==A429_data[channel][u16_i].type) &&
                      (LABEL_0250 == A429_data[channel][u16_i].label) &&
              	  (((((EIU1 == Active_eiu)&&(ONE == channel)) ||
              	  ((EIU2 == Active_eiu)&&(ZERO == channel))) && (TWO == Du_position))
			   || ((((EIU1 == Active_eiu)&&(ZERO == channel)) ||
                 ((EIU2 == Active_eiu)&&(ONE == channel))) && (ONE == Du_position))))
               {
                    Scu_timer[2] = ZERO;
                    s32_data = (T_FLOAT)(i32_arinc_word>>TEN);
                    ScuRTDSetParam(channel,(T_UINT16)(u16_i+1), TWO, s32_data,\
                 		   (T_RTD_STATUS) u8_ssm);
                    ProcessLmsScuProbeErr(((T_UINT32) i32_arinc_word>>EIGHT & 0X1FFFFF),\
                 		   (T_RTD_STATUS) u8_ssm);                     
                    ProcessingArinc01Fault();
               }
               else
               {
                  ;
               }
	}
	 /*hdudispfa429-Process429Words-DB-LLR-037*/
    else if((ONE == Config_data.scu_enable) && ((SEVEN == Scu_label_flag) &&
    	  ((RTD_MAX_INTERVAL_SCU <= Scu_timer[0]) || (RTD_MAX_INTERVAL_SCU <= Scu_timer[1])
    	   || (RTD_MAX_INTERVAL_SCU <= Scu_timer[2]))))
    {
    	/* process SCU ARINC 01 error when labels 0247, 0250 or 0272 is received for 10 seconds */
    	ProcessingArinc01Fault();
    }
    else
    {
    	;
    }
   /*hdudispfa429-Process429Words-DB-LLR-005*/
   if ((((EIU1 == Active_eiu)&&(TRUE == source_eiu1)) ||
	   ((EIU2 == Active_eiu)&&(TRUE == source_eiu2)))&&
         (TRUE==label_found)&&(ZERO == Pbit_test_result))
   {
      if((BNR==A429_data[channel][u16_i].type) &&
            (((T_INT32)ZERO) == (T_INT32)(i32_arinc_word>>TEN & (T_INT32)data_zeros)))
      {
         A429_data_recieved = TRUE;

         sign=(T_INT32)((T_FLOAT)((i32_arinc_word>>TWENTY_EIGHT)& (T_INT32)ONE));

           if (((T_INT32)ZERO) != sign && DATA_28_BIT == (A429_data[channel][u16_i].sig_bits+
               A429_data[channel][u16_i].start_bit-1))
           {
            /*hdudispfa429-Process429Words-DB-LLR-006*/
            s32_data_neg = (T_INT32)((i32_arinc_word>>(A429_data[channel][u16_i].start_bit-1))&
                  (T_INT32)((T_UINT32)MAX_32>>((T_UINT32)THIRTY_TWO-
                       ((T_UINT32)A429_data[channel][u16_i].sig_bits+1))));
            /* One's Complement*/
            s32_data_neg = ~(T_INT32)s32_data_neg;
            /* Two's Complement*/
            s32_data_neg = (T_INT32)(((T_INT32)s32_data_neg &
            		(T_INT32)((T_UINT32)MAX_32>>((T_UINT32)THIRTY_TWO-
                                ((T_UINT32)A429_data[channel][u16_i].sig_bits+1)))) + 1);
            /* After two's Complement multiply with -1*/
            s32_data =(T_FLOAT)((T_FLOAT)s32_data_neg*
            		(A429_data[channel][u16_i].scale_factor)*(-1));

           }
           else
           {
              /*hdudispfa429-Process429Words-DB-LLR-007*/
            s32_data = (T_FLOAT)((i32_arinc_word>>(A429_data[channel][u16_i].start_bit-1))&
                   (T_INT32)((T_UINT32)MAX_32>>((T_UINT32)THIRTY_TWO-
                       (T_UINT32)A429_data[channel][u16_i].sig_bits)))*
                          (A429_data[channel][u16_i].scale_factor);
           }
           /*hdudispfa429-Process429Words-DB-LLR-008*/
           s32_data= (T_FLOAT)(s32_data+(T_FLOAT)A429_data[channel][u16_i].offset);

         RTDSetParam(channel,(T_UINT16)(u16_i+1), s32_data, (T_RTD_STATUS) u8_ssm);

        /*hdudispfa429-Process429Words-DB-LLR-018*/
         /* MD Specific requirement : check FF is enabled or not */
         if((ONE == Cmu_fuel_flow) && (TRUE == Md_engine_flag))
         {
              if (LABEL_0244 == u8_label)
              {
      	         SetFuelFlowData((T_UINT8) (u16_i+1), (T_FLOAT)s32_data);
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
         if((LABEL_0346 == A429_data[channel][u16_i].label) && (THREE == u8_ssm))
         {
        	 /* Consider N1 value when SSM is valid */
        	 N1_value = s32_data;
         }
      }
	  /*hdudispfa429-Process429Words-DB-LLR-019*/
      else if((DDW==A429_data[channel][u16_i].type) &&
    		  (u8_label!=Cas_msg[0].label)&& (Exceed_data[0].label !=u8_label) &&
			  (Auto_cool_down_tmr.wog_label !=u8_label) &&
    		  (LABEL_0360!=A429_data[channel][u16_i].label) &&
              (LABEL_0370!=A429_data[channel][u16_i].label))

      {
      	   for(tmr_index=0; tmr_index< Timer_cnt; tmr_index++)
      	   {
      		   if((Page_settings.Timer_settings[tmr_index].timer_label ==
      		       A429_data[channel][u16_i].label) &&
      			  (Page_settings.Timer_settings[tmr_index].timer_sdi ==
      			   A429_data[channel][u16_i].sdi))
      		   {
      			  Exceed_timer_params[tmr_index].timer_a249_label =
      			  					A429_data[channel][u16_i].label;
      			  Exceed_timer_params[tmr_index].timer_a429_sdi =
      			  					A429_data[channel][u16_i].sdi;
                   break;
      		   }
      		   else
      		   {
      			   ;
      		   }
      	   }
    	  u8_timer_id = (T_UINT8) (((T_UINT32) i32_arinc_word >> TEN) & THREE);

    	  s32_data = (T_FLOAT)(i32_arinc_word>>TEN);
		  /*hdudispfa429-Process429Words-DB-LLR-020*/
    	  if(ONE == u8_timer_id)
    	  {
    		  Exceed_timer_params[tmr_index].timer_id = u8_timer_id;
    		  Exceed_timer_params[tmr_index].timer_param =
                               (T_UINT8) (((T_UINT32) i32_arinc_word>>THIRTEEN) & FIFTEEN);
    		  Exceed_timer_params[tmr_index].timer_color =
                               (T_UINT8) (((T_UINT32) i32_arinc_word>> SEVENTEEN) & FIFTEEN);
    		  Exceed_timer_params[tmr_index].timer_flash =
    				  (T_UINT8) (((T_UINT32) i32_arinc_word>> TWENTY_ONE) & ONE);
    		  Exceed_timer_params[tmr_index].timer_data_flag = TRUE;
    	  }
		  /*hdudispfa429-Process429Words-DB-LLR-021*/
    	  else if(TWO == u8_timer_id)
    	  {
    		  Exceed_timer_params[tmr_index].timer_id = u8_timer_id;
    		  Exceed_timer_params[tmr_index].timer_seconds =
                              (T_UINT32) ((T_UINT32) i32_arinc_word>>THIRTEEN & 0xFFFF);
    		  Exceed_timer_params[tmr_index].timer_sec_flag = TRUE;
    	  }
		  /*hdudispfa429-Process429Words-DB-LLR-022*/
    	  else if(ZERO == u8_timer_id)
    	  {
    		  Exceed_timer_params[tmr_index].timer_id = u8_timer_id;
    		  Exceed_timer_params[tmr_index].timer_data_flag = FALSE;
    		  Exceed_timer_params[tmr_index].timer_sec_flag = FALSE;
    	  }
    	  else
    	  {
    		  ;
    	  }
		  /*hdudispfa429-Process429Words-DB-LLR-023*/
    	  RTDSetParam(channel,(T_UINT16)(u16_i+1), s32_data, (T_RTD_STATUS) u8_ssm);
    	  Timer_a429_tag[tmr_index] = (T_UINT16)(u16_i+1);
      }
      else if((DDW==A429_data[channel][u16_i].type) &&
             (LABEL_0360!=A429_data[channel][u16_i].label) &&
           (LABEL_0370!=A429_data[channel][u16_i].label))
      {
         /*hdudispfa429-Process429Words-DB-LLR-009*/
         A429_data_recieved = TRUE;

          s32_data = (T_FLOAT)(i32_arinc_word>>TEN);

          /*hdudispfa429-Process429Words-DB-LLR-024*/
          if((LABEL_0273 == u8_label) && (TRUE == Md_engine_flag) && (FALSE == ff_once_flag))
          {
              u8_id = (T_UINT8) (((T_UINT32) i32_arinc_word>>TWENTY_SIX) & SEVEN);

              if((THREE == u8_id) && (ZERO == u8_ssm))
              {
            	  SetCMUFuelFlowEnable((T_UINT8)(((T_UINT32) i32_arinc_word>>TWENTY_FOUR)&ONE));
            	  ff_once_flag = TRUE;
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
          if((Cas_cnt!=0) && (u8_label==Cas_msg[0].label))
          {
            /*hdudispfa429-Process429Words-DB-LLR-010*/
            u8_id = (T_UINT8) (((T_UINT32) i32_arinc_word>>TWENTY_SIX) & SEVEN);
            data = (T_UINT16)(i32_arinc_word>>TEN)&EXTRACT_2BYTE;
            RTDSetParam(channel,(T_UINT16)(u16_i+u8_id+1), s32_data, (T_RTD_STATUS) u8_ssm);
            /*
             * WOG data is right shifted by start bit-10-1 as start bit is specified
             * for 32 bit arinc word. But wog_data contains 32-bit arinc word >>10 value.
             */

              if (FOUR == u8_id)
              {
                  /*hdudispfa429-Process429Words-DB-LLR-016 */
                 data = (T_UINT16)(data|(U16_wdog<<FIFTEEN));
              }
              else
              {
            	  ; /* Do nothing */
              }

              /*hdudispfa429-Process429Words-DB-LLR-038*/
              if(ONE == Config_data.scu_enable)
              {
                 if (FIVE == u8_id)
                 {
            	    Fault_log_adv = Fault_log_adv | (T_BOOL)((data >> FORTEEN) & ONE);
            	    if(TRUE == Fault_log_adv)
            	    {
            		   data = data | (T_UINT16)(ONE << FORTEEN);
            	    }
            	    else
            	    {
            		   ;/* Do nothing */
            	    }

                 }
                 else
                 {
            	     ;/* Do nothing */
                 }
              }
              else
              {
            	  ; /* Do Nothing */
              }

             /* hdudispfa429-Process429Words-DB-LLR-012 */
              if(ZERO==u8_ssm)
              {
                 CasSetCasWord(u8_id, data);
              }
           else
           {
            ;
           }
             Cas_data_recieved = TRUE;
          }
          else if(Auto_cool_down_tmr.wog_label==u8_label)
          {
             /* hdudispfa429-Process429Words-DB-LLR-013 */
            if(ZERO==u8_ssm)
            {
                RTDSetParam(channel,(T_UINT16)(u16_i+1), s32_data, (T_RTD_STATUS) u8_ssm);

                U16_wdog=(T_UINT16)(((i32_arinc_word>>(Auto_cool_down_tmr.wog_start_bit-ONE))&
                                 (T_INT32)THREE));
               U16_cas_words[FOUR] |= (T_UINT16)(U16_wdog<<FIFTEEN);
            }
         else
         {
            ;
         }
            Cas_wog_data_recieved = TRUE;
          }
          else
          {
              /* hdudispfa429-Process429Words-DB-LLR-014 */
        	  if((Exceed_data[0].label==u8_label)&& (RTD_STAT_FAIL==u8_ssm))
        	  {
        		  /* If ssm is NO then set to S32_data_exceed(ssm 0 is normal operation for DDW). */
        		  S32_data_exceed[engine_sdi]=S32_data_exceed[engine_sdi]|(T_INT32)s32_data;

        	  }
        	  else
        	  {
        		  ;
        	  }
              RTDSetParam(channel,(T_UINT16)(u16_i+1), s32_data, (T_RTD_STATUS) u8_ssm);
          }
      }
      else if((DDW==A429_data[channel][u16_i].type) &&
               (LABEL_0360==A429_data[channel][u16_i].label))
      {
          /* hdudispfa429-Process429Words-DB-LLR-015 */
          A429_data_recieved = TRUE;
          /* extract out Data */
          data2 = (T_UINT8)((T_UINT32) i32_arinc_word>>TWENTY_FOUR & HEX_7F);
          data1 = (T_UINT8)((T_UINT32) i32_arinc_word>>SEVENTEEN & HEX_7F);

          /* extract out ID */
         u8_sequence = (T_UINT8) ((T_UINT32) i32_arinc_word>>TEN & HEX_7F);

         SetSysInfoWords(u8_sequence, data1, data2);
      }
      else if((DDW==A429_data[channel][u16_i].type) &&
              (LABEL_0370==A429_data[channel][u16_i].label))
      {
          /* hdudispfa429-Process429Words-DB-LLR-017 */
          A429_data_recieved_0370 = TRUE;
          /* extract out Data */
          airframe_data2 = (T_UINT8)((T_UINT32) i32_arinc_word>>TWENTY_FOUR & HEX_7F);
          airframe_data1 = (T_UINT8)((T_UINT32) i32_arinc_word>>SEVENTEEN & HEX_7F);

          /* extract out ID */
          airframe_sequence = (T_UINT8) ((T_UINT32) i32_arinc_word>>TEN & HEX_7F);

          SetSysAirFrameWords(airframe_sequence, airframe_data1, airframe_data2);
      }
      else
      {
    	  ;
      }
   }
   else
   {

   }
}

/*
 * Function                :  A429Init
 *
 * Description             :  This function Process the A429 message.
 *
 * Formal parameter(s)     :  None
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */
void A429Init()
{
   T_UINT16 u16_i=ZERO;
   T_UINT16 port1_indx=0;
   T_UINT16 port2_indx=0;
   T_UINT16 u16_j=0;

   /* hdudispfa429-A429Init-DB-LLR-001 */
   CasExtract((T_UINT8 *)CAS_MESSAGE_ADDRESS);

   A429Extract((T_UINT8 *)A429_MESSAGE_ADDRESS);

   for(u16_i=ZERO;u16_i<A429_settings_cnt;u16_i++)
   {
      if(ONE == A429_cfg_data[u16_i].A429_port)
      {

         if(BNR==A429_cfg_data[u16_i].A429_type)
         {
             /* hdudispfa429-A429Init-DB-LLR-002 */
            A429_data[0][port1_indx].label=
                  A429_cfg_data[u16_i].A429_label;
            A429_data[0][port1_indx].sdi=
                  A429_cfg_data[u16_i].A429_sdi;
            A429_data[0][port1_indx].type=
                  A429_cfg_data[u16_i].A429_type;
            A429_data[0][port1_indx].sig_bits=
                  (T_UINT8)A429_cfg_data[u16_i].label_data.A429_bnr_data.A429_bnr_bits;
            A429_data[0][port1_indx].start_bit=
                  (T_UINT8)A429_cfg_data[u16_i].label_data.A429_bnr_data.A429_bnr_start_bit;
            A429_data[0][port1_indx].min_val=
                  A429_cfg_data[u16_i].label_data.A429_bnr_data.A429_bnr_min;
            A429_data[0][port1_indx].max_val=
                  A429_cfg_data[u16_i].label_data.A429_bnr_data.A429_bnr_max;
            A429_data[0][port1_indx].scale_factor=
                  A429_cfg_data[u16_i].label_data.A429_bnr_data.A429_bnr_scale_fact;
            A429_data[0][port1_indx].offset=
                  A429_cfg_data[u16_i].label_data.A429_bnr_data.A429_bnr_offset;
            A429_data[0][port1_indx].timeout=
                  (T_UINT16)A429_cfg_data[u16_i].label_data.A429_bnr_data.A429_bnr_timeout;
            port1_indx++;
         }
         else if(DDW==A429_cfg_data[u16_i].A429_type)
         {
            if((Cas_cnt!=0) && (A429_cfg_data[u16_i].A429_label==Cas_msg[0].label))
            {
               for(u16_j=0;u16_j<CAU_WARN_MAX_ID;u16_j++)
               {
                  /*
                   * Caution/warning label is received with 6 IDs.
                   * Hence same label is stored in 6 continuous indices of Parameters
                   */
                  /* hdudispfa429-A429Init-DB-LLR-003 */
                  A429_data[0][port1_indx].label=
                        A429_cfg_data[u16_i].A429_label;
                  A429_data[0][port1_indx].sdi=
                        A429_cfg_data[u16_i].A429_sdi;
                  A429_data[0][port1_indx].type=
                        A429_cfg_data[u16_i].A429_type;
                  A429_data[0][port1_indx].sig_bits=DDW_SIG_BIT;
                  A429_data[0][port1_indx].start_bit=ONE;
                  A429_data[0][port1_indx].min_val=ONE;
                  A429_data[0][port1_indx].max_val=ONE;
                  A429_data[0][port1_indx].scale_factor=ONE;
                  A429_data[0][port1_indx].timeout=
                       (T_UINT16)A429_cfg_data[u16_i].label_data.A429_ddw_timeout;
                  port1_indx++;
               }
            }
            else
            {
                /* hdudispfa429-A429Init-DB-LLR-004 */
               A429_data[0][port1_indx].label=
                     A429_cfg_data[u16_i].A429_label;
               A429_data[0][port1_indx].sdi=
                     A429_cfg_data[u16_i].A429_sdi;
               A429_data[0][port1_indx].type=
                     A429_cfg_data[u16_i].A429_type;
               A429_data[0][port1_indx].sig_bits=DDW_SIG_BIT;
               A429_data[0][port1_indx].start_bit=ONE;
               A429_data[0][port1_indx].min_val=ONE;
               A429_data[0][port1_indx].max_val=ONE;
               A429_data[0][port1_indx].scale_factor=ONE;
               A429_data[0][port1_indx].timeout=
                     (T_UINT16)A429_cfg_data[u16_i].label_data.A429_ddw_timeout;
               port1_indx++;
            }

         }
         else
         {
            ;
         }
      }
      else if (TWO == A429_cfg_data[u16_i].A429_port)
      {
         if(BNR==A429_cfg_data[u16_i].A429_type)
         {
             /* hdudispfa429-A429Init-DB-LLR-005 */
            A429_data[1][port2_indx].label=
                  A429_cfg_data[u16_i].A429_label;
            A429_data[1][port2_indx].sdi=
                  A429_cfg_data[u16_i].A429_sdi;
            A429_data[1][port2_indx].type=
                  A429_cfg_data[u16_i].A429_type;
            A429_data[1][port2_indx].sig_bits=
                  (T_UINT8)A429_cfg_data[u16_i].label_data.A429_bnr_data.A429_bnr_bits;
            A429_data[1][port2_indx].start_bit=
                  (T_UINT8)A429_cfg_data[u16_i].label_data.A429_bnr_data.A429_bnr_start_bit;
            A429_data[1][port2_indx].min_val=
                  A429_cfg_data[u16_i].label_data.A429_bnr_data.A429_bnr_min;
            A429_data[1][port2_indx].max_val=
                  A429_cfg_data[u16_i].label_data.A429_bnr_data.A429_bnr_max;
            A429_data[1][port2_indx].scale_factor=
                  A429_cfg_data[u16_i].label_data.A429_bnr_data.A429_bnr_scale_fact;
            A429_data[1][port2_indx].offset=
                  A429_cfg_data[u16_i].label_data.A429_bnr_data.A429_bnr_offset;
            A429_data[1][port2_indx].timeout=
                  (T_UINT16)A429_cfg_data[u16_i].label_data.A429_bnr_data.A429_bnr_timeout;
            port2_indx++;
         }
         else if(DDW==A429_cfg_data[u16_i].A429_type)
         {
            if((Cas_cnt!=0) && (A429_cfg_data[u16_i].A429_label==Cas_msg[0].label))
            {
               /* hdudispfa429-A429Init-DB-LLR-006 */
               Cas_label_start_idx=(T_UINT16)(port2_indx+1);
               for(u16_j=0;u16_j<CAU_WARN_MAX_ID;u16_j++)
               {
                  /*
                   * Caution/warning label is received with 6 IDs.
                   * Hence same label is stored in 6 continuous indices of Parameters
                   */
                  A429_data[1][port2_indx].label=
                        A429_cfg_data[u16_i].A429_label;
                  A429_data[1][port2_indx].sdi=
                        A429_cfg_data[u16_i].A429_sdi;
                  A429_data[1][port2_indx].type=
                        A429_cfg_data[u16_i].A429_type;
                  A429_data[1][port2_indx].sig_bits=DDW_SIG_BIT;
                  A429_data[1][port2_indx].start_bit=ONE;
                  A429_data[1][port2_indx].min_val=ONE;
                  A429_data[1][port2_indx].max_val=ONE;
                  A429_data[1][port2_indx].scale_factor=ONE;
                  A429_data[1][port2_indx].timeout=
                       (T_UINT16)A429_cfg_data[u16_i].label_data.A429_ddw_timeout;
                  port2_indx++;
               }
            }
            else
            {
               /* hdudispfa429-A429Init-DB-LLR-007 */
               A429_data[1][port2_indx].label=
                     A429_cfg_data[u16_i].A429_label;
               A429_data[1][port2_indx].sdi=
                     A429_cfg_data[u16_i].A429_sdi;
               A429_data[1][port2_indx].type=
                     A429_cfg_data[u16_i].A429_type;
               A429_data[1][port2_indx].sig_bits=DDW_SIG_BIT;
               A429_data[1][port2_indx].start_bit=ONE;
               A429_data[1][port2_indx].min_val=ONE;
               A429_data[1][port2_indx].max_val=ONE;
               A429_data[1][port2_indx].scale_factor=ONE;
               A429_data[1][port2_indx].timeout=
                     (T_UINT16)A429_cfg_data[u16_i].label_data.A429_ddw_timeout;
               port2_indx++;
            }
         }
         else
         {
            ;
         }
      }
   }
   /* hdudispfa429-A429Init-DB-LLR-008 */
   Port1_label_count=port1_indx;
   Port2_label_count=port2_indx;

    /*hdudispfa429-A429Init-DB-LLR-010*/
   if(Port1_label_count==Port2_label_count)
   {
      for(u16_i=0;u16_i<Port1_label_count;u16_i++)
      {
    	  if (TRUE == Config_data.scu_enable)
    	  {
    		  if(LABEL_0247 == A429_data[0][u16_i].label)
    		  {
    			  Scu_parameters[0].label = A429_data[0][u16_i].label;
    			  Scu_parameters[0].sdi =A429_data[0][u16_i].sdi;
    			  Scu_parameters[0].type = A429_data[0][u16_i].type;
    		  }
			  /*hdudispfa429-A429Init-DB-LLR-011*/
    	      else if((LABEL_0272 == A429_data[0][u16_i].label) &&
    			 (ZERO == A429_data[0][u16_i].sdi))
    		  {
    			  Scu_parameters[1].label = A429_data[0][u16_i].label;
    			  Scu_parameters[1].sdi =A429_data[0][u16_i].sdi;
    			  Scu_parameters[1].type = A429_data[0][u16_i].type;
    		  }
			  /*hdudispfa429-A429Init-DB-LLR-012*/
    	      else if (LABEL_0250 == A429_data[0][u16_i].label)
    	      {
    			  Scu_parameters[2].label = A429_data[0][u16_i].label;
    			  Scu_parameters[2].sdi =A429_data[0][u16_i].sdi;
    			  Scu_parameters[2].type = A429_data[0][u16_i].type;
    	      }
			  /*hdudispfa429-A429Init-DB-LLR-013*/
    	      else
    	      {
    	          Parameters[u16_i+1].label=A429_data[0][u16_i].label;
    	          Parameters_numbox[u16_i+1].label=A429_data[0][u16_i].label;
    	          Parameters[u16_i+1].sdi=A429_data[0][u16_i].sdi;
    	          Parameters_numbox[u16_i+1].sdi=A429_data[0][u16_i].sdi;
    	          Parameters[u16_i+1].type=A429_data[0][u16_i].type;
    	          Parameters_numbox[u16_i+1].type=A429_data[0][u16_i].type;
    	      }
    	  }
    	  else
    	  {
              /* hdudispfa429-A429Init-DB-LLR-009 */
             Parameters[u16_i+1].label=A429_data[0][u16_i].label;
             Parameters_numbox[u16_i+1].label=A429_data[0][u16_i].label;
             Parameters[u16_i+1].sdi=A429_data[0][u16_i].sdi;
             Parameters_numbox[u16_i+1].sdi=A429_data[0][u16_i].sdi;
             Parameters[u16_i+1].type=A429_data[0][u16_i].type;
             Parameters_numbox[u16_i+1].type=A429_data[0][u16_i].type;
    	  }
      }
   }
   else
   {
      ;/* ERROR IN PDI DATA */
   }
}
/* Updtaed as per PR 100083 */
/*
 * Function                :  ProcessF4PbitErr
 *
 * Description             :  This function process the pbit error of communication board
 *
 * Formal parameter(s)     :  T_A825_MESSAGE  *s_mess - IN A825 messages.
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */
void ProcessF4PbitErr(T_A825_MESSAGE  *s_mess)
{
   if(TRUE==((s_mess->u8PayLoad[0]>>ZERO)& (T_UINT8)ONE)) /* F4 boot CRC fail */
   {
      /* hdudispfa429-ProcessF4PbitErr-DB-LLR-001 */
      U16_message_words[0] |= BIT_SHIFT_BY_512;
   }
   else if(TRUE==((s_mess->u8PayLoad[0]>>ONE)& ONE)) /* F4 Maint CRC fail */
   {
      /* hdudispfa429-ProcessF4PbitErr-DB-LLR-002 */
      U16_message_words[0] |= BIT_SHIFT_BY_1024;
   }
   else if(TRUE==((s_mess->u8PayLoad[0]>>TWO)& ONE)) /* F4 App CRC fail */
   {
      /* hdudispfa429-ProcessF4PbitErr-DB-LLR-003 */
      U16_message_words[0] |= BIT_SHIFT_BY_256;
   }
   else if(TRUE==((s_mess->u8PayLoad[0]>>THREE)& ONE)) /* F4 CPU test fail */
   {
      /* hdudispfa429-ProcessF4PbitErr-DB-LLR-004 */
      U16_message_words[0] |= BIT_SHIFT_BY_2048;
   }
   else if(TRUE==((s_mess->u8PayLoad[0]>>FOUR)& ONE)) /* F4 SDRAM test fail */
   {
      /* hdudispfa429-ProcessF4PbitErr-DB-LLR-005 */
      U16_message_words[0] |= BIT_SHIFT_BY_4096;
   }
   else if(TRUE==((s_mess->u8PayLoad[0]>>FIVE)& ONE)) /* F4- NVRAM test fail */
   {
      /* hdudispfa429-ProcessF4PbitErr-DB-LLR-006 */
      U16_message_words[0] |= BIT_SHIFT_BY_128;
   }
   else if(TRUE==((s_mess->u8PayLoad[0]>>SIX)& ONE)) /* F4- Loopback test fail */
   {
      /* hdudispfa429-ProcessF4PbitErr-DB-LLR-007 */
      U16_message_words[0] |= BIT_SHIFT_BY_4;
   }
   else
   {
      ; /* Do nothing */
   }
}

/*
 * Function                :  ProcessF4CbitErr
 *
 * Description             :  This function process the cbit error of communication board
 *
 * Formal parameter(s)     :  T_A825_MESSAGE  *s_mess - IN A825 messages.
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */
void ProcessF4CbitErr(T_A825_MESSAGE  *s_mess)
{
   /* hdudispfa429-ProcessF4CbitErr-DB-LLR-001 */
   if(ONE==((s_mess->u8PayLoad[0]>>0)&1)) /* Cbit fail */
   {
      /* Updated as per PR100116 */
      U16_message_words[0] |= BIT_16_SET;
   }
   else
   {
      ; /* Do nothing */
   }

}

/*
 * Function                :  A429ProcessA825
 *
 * Description             :  This function decodes A825 messages to extract A429 words.
 *
 * Formal parameter(s)     :  T_A825_MESSAGE  *s_mess - IN A825 messages.
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */

void A429ProcessA825(T_A825_MESSAGE  *s_mess)
{
   T_INT32  s32_a429 = ZERO;
   T_UINT8  *pu8_src = ZERO;
   T_UINT8  *pu8_dest = ZERO;
   T_UINT8  u8_cntr = ZERO;

   /*hdudispfa429-A429ProcessA825-DB-LLR-001*/
   if(A429_CHAN_1 == s_mess->sID.BID.doc )
   {
      pu8_src = ((T_UINT8*)&(s_mess->u8PayLoad));
      pu8_dest = (T_UINT8*)&s32_a429;

      for(u8_cntr = ZERO; u8_cntr < FOUR; u8_cntr++)
      {
         *pu8_dest = *pu8_src;
         pu8_dest += ONE;
         pu8_src += ONE;
      }
      if((((T_UINT32) s32_a429>>EIGHT & THREE)>ZERO) && (FALSE == Du_identified))
      {
         Du_position= (T_UINT8) ((T_UINT32) s32_a429>>EIGHT & THREE);
         Du_identified = TRUE;
      }
      /*hdudispfa429-A429ProcessA825-DB-LLR-002*/
      Process429Words(s32_a429,0);

      /*hdudispfa429-A429ProcessA825-DB-LLR-003*/
      if(EIGHT == s_mess->u8PaySize)
      {
         pu8_src = &(s_mess->u8PayLoad[4]);
         pu8_dest = (T_UINT8*)&s32_a429;

         for(u8_cntr = ZERO; u8_cntr < FOUR; u8_cntr++)
         {
            *pu8_dest = *pu8_src;
            pu8_dest += ONE;
            pu8_src += ONE;
         }

         /*hdudispfa429-A429ProcessA825-DB-LLR-004*/
         Process429Words(s32_a429,0);
      }
      else
      {
       ; /* Do nothing */
      }
   }
   /*hdudispfa429-A429ProcessA825-DB-LLR-005*/
   else if(A429_CHAN_2 == s_mess->sID.BID.doc)
   {
      pu8_src = ((T_UINT8*)&(s_mess->u8PayLoad));
      pu8_dest = (T_UINT8*)&s32_a429;

      for(u8_cntr = ZERO; u8_cntr < FOUR; u8_cntr++)
      {
         *pu8_dest = *pu8_src;
         pu8_dest += ONE;
         pu8_src += ONE;
      }

      /*hdudispfa429-A429ProcessA825-DB-LLR-006*/
      Process429Words(s32_a429,1);

      /*hdudispfa429-A429ProcessA825-DB-LLR-007*/
      if(EIGHT == s_mess->u8PaySize)
      {
         pu8_src = &(s_mess->u8PayLoad[4]);
         pu8_dest = (T_UINT8*)&s32_a429;

         for(u8_cntr = ZERO; u8_cntr < FOUR; u8_cntr++)
         {
            *pu8_dest = *pu8_src;
            pu8_dest += ONE;
            pu8_src += ONE;
         }

         /*hdudispfa429-A429ProcessA825-DB-LLR-008*/
         Process429Words(s32_a429,1);
      }
      else
      {
       ; /* Do nothing */
      }
   }
   /*add in code to receive and process F4 board SW PN's and CRC's */
   else if( DIS_COMAPP_REVNO1 == s_mess->sID.BID.doc )
   /* Extracts the revno or CRC based on the DOC id of arinc msg received */
   {
      /*hdudispfa429-A429ProcessA825-DB-LLR-009*/
      ProcessSWPartNum(s_mess);
   }
   else if(DIS_COMAPP_REVNO2 == s_mess->sID.BID.doc)
   {
      /*hdudispfa429-A429ProcessA825-DB-LLR-010*/
      ProcessSWPartNum(s_mess);
   }
   else if (DIS_COMBOOT_REVNO1 == s_mess->sID.BID.doc )
   {
      /*hdudispfa429-A429ProcessA825-DB-LLR-011*/
      ProcessSWPartNum(s_mess);
   }
   else if (DIS_COMBOOT_REVNO2 == s_mess->sID.BID.doc )
   {
      /*hdudispfa429-A429ProcessA825-DB-LLR-012*/
      ProcessSWPartNum(s_mess);
   }
   else if (DIS_COMMAINT_REVNO1 == s_mess->sID.BID.doc )
   {
      /*hdudispfa429-A429ProcessA825-DB-LLR-013*/
      ProcessSWPartNum(s_mess);
   }
   /*hdudispfa429-A429ProcessA825-DB-LLR-014*/
   else if (DIS_COMMAINT_REVNO2 == s_mess->sID.BID.doc )
   {

      ProcessSWPartNum(s_mess);
   }
   else if (DIS_COMSL_REVNO1 == s_mess->sID.BID.doc )
   {

      ProcessSWPartNum(s_mess);
   }
   else if (DIS_COMSL_REVNO2 == s_mess->sID.BID.doc )
   {

      ProcessSWPartNum(s_mess);
   }
   else if (DIS_COMBOOT_CRC == s_mess->sID.BID.doc )
   {
      /*hdudispfa429-A429ProcessA825-DB-LLR-015*/
      ProcessSWPartNum(s_mess);
   }
   else if (DIS_COMMAINT_CRC == s_mess->sID.BID.doc )
   {
      /*hdudispfa429-A429ProcessA825-DB-LLR-016*/
      ProcessSWPartNum(s_mess);
   }
   /* Updated as per PR 100064 */
   /*hdudispfa429-A429ProcessA825-DB-LLR-017*/
   else if (DIS_COMAPP_CRC == s_mess->sID.BID.doc )
   {

      ProcessSWPartNum(s_mess);
   }
   else if (DIS_COMSL_CRC == s_mess->sID.BID.doc )
   {

      ProcessSWPartNum(s_mess);
   }
   /* Updtaed as per PR 100083 */
   else if (F4_PBIT_ERR == s_mess->sID.BID.doc )
   {
      /* hdudispfa429-A429ProcessA825-DB-LLR-018 */
     ProcessF4PbitErr(s_mess);
   }
   else if (F4_CBIT_ERR == s_mess->sID.BID.doc )
   {
      /* hdudispfa429-A429ProcessA825-DB-LLR-019 */
     ProcessF4CbitErr(s_mess);
   }
   else
   {
      ;
   }

}

/* Updated as per PR 100083 */
/*
 * Function                :  BinAsciiCRC
 *
 * Description             :  This function is to convert digits of CRC to
 *                            ASCII character.
 *
 * Formal parameter(s)     :  T_ULONG x_val - IN  Digits to be converted
 *                            T_CHAR *out_buf - OUT Output ASCII character pointer
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */
void BinAsciiCRC(T_ULONG x_val, T_CHAR *out_buf)
{

    /* hdudispfa429-BinAsciiCRC-DB-LLR-001 */
    if (x_val <= MAX_64_BIT)
    {
        out_buf[6] = TO_HEX(((x_val & EXT_BIT_28_31) >> SHIFT_BY_28));
        out_buf[7] = TO_HEX(((x_val & EXT_BIT_24_27) >> SHIFT_BY_24));
        out_buf[4] = TO_HEX(((x_val & EXT_BIT_20_23) >> SHIFT_BY_20));
        out_buf[5] = TO_HEX(((x_val & EXT_BIT_16_19) >> SHIFT_BY_16));
        out_buf[2] = TO_HEX(((x_val & EXT_BIT_12_15) >> SHIFT_BY_12));
        out_buf[3] = TO_HEX(((x_val & EXT_BIT_8_11) >> SHIFT_BY_8));
        out_buf[0] = TO_HEX(((x_val & EXT_BIT_4_7) >> SHIFT_BY_4));
        out_buf[1] = TO_HEX((x_val & EXT_BIT_0_3));
        out_buf[8] = '\0';
    }
    else
    {
      ;/* Does nothing */
    }
}

/* Updated as per PR 100083 */
/*
 * Function                :  MemCpy
 *
 * Description             :  This function copies data from source buffer to destination buffer.
 *
 * Formal parameter(s)     :  void *p_dest   - INOUT pointer to destination buffer,
 *                            void *p_src    - IN  pointer to source buffer,
 *                            T_UINT16 count   - IN  number of bytes to be copied.
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */
void MemCpy (void* p_dest, const void* p_src, T_UINT16 count)
{
   T_UINT8 *destp = (T_UINT8*)p_dest;
   const T_UINT8 *srcp = (const T_UINT8*)p_src;

   /* hdudispfa429-MemCpy-DB-LLR-001 */
   while (ZERO != count--)
   {
      *destp = *srcp;
      destp++;
      srcp++;
   }
}

/* Updated as per PR 100083 */
/*
 * Function                :  MemSet
 *
 * Description             :  This function copies value to destination buffer.
 *
 * Formal parameter(s)     :  void *p_dest   - INOUT pointer to destination buffer,
 *                            T_UINT16 val  - IN value to be copied into the destination buffer,
 *                            T_UINT32 cnt   - IN  number of bytes to be copied.
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */
void MemSet (void* p_dest, T_UINT16 val, T_UINT32 cnt)
{
   T_UINT8 *dest_var = (T_UINT8*)p_dest;
   /* hdudispfa429-MemSet-DB-LLR-001 */
   while (cnt--)
   {
      *dest_var = (T_UINT8)val;
      dest_var++;
   }
}

/*
 * Function                :  ProcessSWPartNum
 *
 * Description             :  This function process software part number.
 *
 * Formal parameter(s)     :  T_A825_MESSAGE  *s_mess - IN A825 messages.
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */

void ProcessSWPartNum(T_A825_MESSAGE  *s_mess)
{
   /* Updated as per PR 100083 */
   T_UINT32  crc_word = 0;

   if( DIS_COMAPP_REVNO1 == s_mess->sID.BID.doc )
   {
      /*hdudispfa429-ProcessSWPartNum-DB-LLR-001 */
      MemCpy(&Commf_part[6], s_mess->u8PayLoad, EIGHT);
   }
   else
   {
      ;/* Does noting */
   }

   if( DIS_COMAPP_REVNO2 == s_mess->sID.BID.doc )
   {
      /*hdudispfa429-ProcessSWPartNum-DB-LLR-002 */
     MemCpy(&Commf_part[14], s_mess->u8PayLoad, EIGHT);
   }
   else
   {
      ;/* Does noting */
   }

   if(DIS_COMBOOT_REVNO1 ==  s_mess->sID.BID.doc )
   {
      /*hdudispfa429-ProcessSWPartNum-DB-LLR-003 */
     MemCpy(&Commb_part[6], s_mess->u8PayLoad, EIGHT);
   }
   else
   {
      ;/* Does noting */
   }

   if(DIS_COMBOOT_REVNO2 == s_mess->sID.BID.doc )
   {
      /*hdudispfa429-ProcessSWPartNum-DB-LLR-004 */
    MemCpy(&Commb_part[14], s_mess->u8PayLoad, EIGHT);
   }
   else
   {
      ;/* Does noting */
   }

   if( DIS_COMMAINT_REVNO1 == s_mess->sID.BID.doc )
   {
      /*hdudispfa429-ProcessSWPartNum-DB-LLR-005 */
     MemCpy(&Maint_part[6], s_mess->u8PayLoad, EIGHT);
   }
   else
   {
      ;/* Does noting */
   }
   /*hdudispfa429-ProcessSWPartNum-DB-LLR-006 */
   if( DIS_COMMAINT_REVNO2 == s_mess->sID.BID.doc )
   {
     MemCpy(&Maint_part[14], s_mess->u8PayLoad, EIGHT);
   }
   else
   {
      ;/* Does noting */
   }

   if( DIS_COMSL_REVNO1 == s_mess->sID.BID.doc )
   {
     MemCpy(&Commsl_part[6], s_mess->u8PayLoad, EIGHT);
   }
   else
   {
      ;/* Does noting */
   }

   if( DIS_COMSL_REVNO2 == s_mess->sID.BID.doc )
   {
     MemCpy(&Commsl_part[14], s_mess->u8PayLoad, EIGHT);
   }
   else
   {
      ;/* Does noting */
   }


   if( DIS_COMAPP_CRC == s_mess->sID.BID.doc )
   {
      /*hdudispfa429-ProcessSWPartNum-DB-LLR-007 */
      MemCpy(&crc_word, s_mess->u8PayLoad, FOUR);
      BinAsciiCRC(crc_word, (T_CHAR *) &Commf_part[22]);
   }
   else
   {
      ;/* Does noting */
   }

   if(DIS_COMBOOT_CRC == s_mess->sID.BID.doc )
   {
      /*hdudispfa429-ProcessSWPartNum-DB-LLR-008 */
      MemCpy(&crc_word, s_mess->u8PayLoad, FOUR);
     BinAsciiCRC(crc_word, (T_CHAR *) &Commb_part[22]);
   }
   else
   {
      ;/* Does noting */
   }

   /*hdudispfa429-ProcessSWPartNum-DB-LLR-009 */
   if(DIS_COMMAINT_CRC ==  s_mess->sID.BID.doc )
   {
      MemCpy(&crc_word, s_mess->u8PayLoad, FOUR);
     BinAsciiCRC(crc_word, (T_CHAR *) &Maint_part[22]);
   }
   else
   {
      ;/* Does noting */
   }

   if(DIS_COMSL_CRC ==  s_mess->sID.BID.doc )
   {
      MemCpy(&crc_word, s_mess->u8PayLoad, FOUR);
     BinAsciiCRC(crc_word, (T_CHAR *) &Commsl_part[22]);
   }
   else
   {
      ;/* Does noting */
   }


}

/*
 * Function                :  SetSysInfoWords
 *
 * Description             :  This function stores all the system information words read
 *                             from label 360
 *
 * Formal parameter(s)     :  T_UINT8 u8_index - IN system information index
 *                            T_UINT8 data1 - IN First character
 *                            T_UINT8 data2 - IN Second character
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */

void SetSysInfoWords(T_UINT8 u8_index, T_UINT8 data1, T_UINT8 data2)
{
   /* hdudispfa429-SetSysInfoWords-DB-LLR-001 */
   Sys_info_words[u8_index % SYSINFO_LABEL_WORDS].data1 = data1;
   Sys_info_words[u8_index % SYSINFO_LABEL_WORDS].data2 = data2;
   Sys_info_words[u8_index % SYSINFO_LABEL_WORDS].sequence = u8_index;
}


/*
 * Function                :  SetSysAirFrameWords
 *
 * Description             :  This function stores all the system information words read
 *                             from label 370
 *
 * Formal parameter(s)     :  T_UINT8 u8_index - IN system information index
 *                            T_UINT8 data1 - IN First character
 *                            T_UINT8 data2 - IN Second character
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */

void SetSysAirFrameWords(T_UINT8 u8_index, T_UINT8 data1, T_UINT8 data2)
{
   /* hdudispfa429-SetSysAirFrameWords-DB-LLR-001 */
   Sys_airframe_words[u8_index % AIRFRAME_LABEL_WORDS].data1 = data1;
   Sys_airframe_words[u8_index % AIRFRAME_LABEL_WORDS].data2 = data2;
   Sys_airframe_words[u8_index % AIRFRAME_LABEL_WORDS].sequence = u8_index;
}


/*
 * Function                :  ProcessSysInfoWords
 *
 * Description             :  This function performs the following
 *                            1. Reads Display Application, boot and Maintenance
 *                                PartNumbers and CRC
 *                            2. Processes the system information words read from label 360
 *                               and stores them in proper format to be displayed in system
 *                               information area
 *
 * Formal parameter(s)     :  None
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */
void ProcessSysInfoWords(void)
{
   T_UINT8 u16_index     = ZERO;
   T_UINT8  index1=0,
            index2=0,
            index3=0,
            index4=0,
            index5=0;
   T_UINT32  crc_word = 0;
   T_BOOL flag3 = 0;

   T_BOOL flag1 =0;
   T_BOOL flag2 =0;

   /* hdudispfa429-ProcessSysInfoWords-DB-LLR-001 */
   /* Display App PN and CRC */
   MemCpy(&App_revno[BUF_LEN_6], &Revno_id, REVNO_LEN);
   MemCpy(&crc_word, (T_UINT8 *)REVNO_DISP_FLIGHT_CRC, CRC_LEN);
   BinAsciiCRC(crc_word, (T_CHAR *) &App_revno[BUF_LEN_22]);

   /* hdudispfa429-ProcessSysInfoWords-DB-LLR-002 */
   /* Display boot PN and CRC */
   MemCpy(&Boot_revno[BUF_LEN_6], (T_UINT8 *)REVNO_DISP_BOOT_PN, REVNO_LEN);
   MemCpy(&crc_word,(T_UINT8 *)REVNO_DISP_BOOT_CRC, CRC_LEN);
   BinAsciiCRC(crc_word, (T_CHAR *) &Boot_revno[BUF_LEN_22]);

   /* hdudispfa429-ProcessSysInfoWords-DB-LLR-003 */
   /* Display Maintenance PN and CRC */
   MemCpy(&Maint_revno[BUF_LEN_6], (T_UINT8 *)REVNO_DISP_MAINT_PN, REVNO_LEN);
   MemCpy(&crc_word, (T_UINT8 *)REVNO_DISP_MAINT_CRC, CRC_LEN);
   BinAsciiCRC(crc_word, (T_CHAR *) &Maint_revno[BUF_LEN_22]);

   /* Display Maintenance Config PN and CRC */
   MemCpy(&Maint_config_revno[BUF_LEN_6], (T_UINT8 *)REVNO_DISP_MAINT_CFG_PN, REVNO_LEN);
   MemCpy(&crc_word, (T_UINT8 *)REVNO_DISP_MAINT_CFG_CRC, CRC_LEN);
   BinAsciiCRC(crc_word, (T_CHAR *) &Maint_config_revno[BUF_LEN_22]);

   /* Display Software Loader PN and CRC */
   MemCpy(&Soft_loader_revno[BUF_LEN_6], (T_UINT8 *)REVNO_DISP_SL_PN, REVNO_LEN);
   MemCpy(&crc_word, (T_UINT8 *)REVNO_DISP_SL_CRC, CRC_LEN);
   BinAsciiCRC(crc_word, (T_CHAR *) &Soft_loader_revno[BUF_LEN_22]);


   /* hdudispfa429-ProcessSysInfoWords-DB-LLR-004 */
   MemCpy(&Bitmap_revno[0], (T_UINT8 *)REVNO_BMP_PN, REVNO_LEN);
   MemCpy(&crc_word, (T_UINT8 *)REVNO_BMP_CRC, CRC_LEN);
   BinAsciiCRC(crc_word, (T_CHAR *) &Bitmap_revno[BUF_LEN_16]);

   /* hdudispfa429-ProcessSysInfoWords-DB-LLR-005 */
   /* Updated for PR 100083 */
   MemCpy(&Dau_config_info[0], "DAU CONFIGURATION INFO", CHAR_LEN_24);
   U16_sys_info_words[1] |= DAU_CONFIGURATION_INFO_VAL;
   ProcessAirframeInfoWords();


   MemCpy(Config_id,Config_data.config_version, REVNO_LEN);
   MemCpy(&crc_word, (T_UINT8 *)REVNO_PDI_CRC, CRC_LEN);
   BinAsciiCRC(crc_word, (T_CHAR *) &Config_id[BUF_LEN_16]);

   /* To avoid spaces if PN and CRC are not read */
   if(Bitmap_revno[0]!= CHAR_H)
   {
      /* hdudispfa429-ProcessSysInfoWords-DB-LLR-006 */
      MemSet(Bitmap_revno, 0, BITMAP_REVNO_LEN);
   }
   else
   {
      U16_sys_info_words[0] |=BITMAP_REVNO_ERR;
      U16_sys_info_words[1] |=BITMAP_REVNO_ERR1;
   }

   if(Config_data.config_version[0]!=CHAR_H)
   {
      /* hdudispfa429-ProcessSysInfoWords-DB-LLR-007 */
      MemSet(Config_data.config_version, 0, CONFIG_VER_LEN);
   }
   else
   {
      U16_sys_info_words[0] |=CONFIG_VER_ERR;
      U16_sys_info_words[1] |=CONFIG_VER_ERR1;
   }

   if(App_revno[BUF_LEN_6]!= CHAR_H)
   {
      /* hdudispfa429-ProcessSysInfoWords-DB-LLR-008 */
      MemSet(App_revno, 0, REVNO_MAX_LEN);
      MemCpy(App_revno,"DISFA ",CHAR_LEN_6);
   }
   else
   {
      U16_sys_info_words[0] |=APP_REVNO_ERR;
   }

   if(Boot_revno[BUF_LEN_6]!= CHAR_H)
   {
      /* hdudispfa429-ProcessSysInfoWords-DB-LLR-009 */
      MemSet(Boot_revno, 0, REVNO_MAX_LEN);
      MemCpy(Boot_revno,"DISBL ",CHAR_LEN_6);
   }
   else
   {
      U16_sys_info_words[0] |=BOOT_REVNO_ERR;
   }

   /* hdudispfa429-ProcessSysInfoWords-DB-LLR-010 */
   if(Maint_revno[BUF_LEN_6]!= CHAR_H)
   {
      MemSet(Maint_revno, 0, REVNO_MAX_LEN);
      MemCpy(Maint_revno,"DISMA ",CHAR_LEN_6);
   }
   else
   {
      U16_sys_info_words[0] |=MAINT_REVNO_ERR;
   }

   if(Maint_config_revno[BUF_LEN_6]!= CHAR_H)
   {
      MemSet(Maint_config_revno, 0, REVNO_MAX_LEN);
      MemCpy(Maint_config_revno,"DISMC ",CHAR_LEN_6);
   }
   else
   {
      U16_sys_info_words[0] |=MAINT_CONF_REVNO_ERR;
   }

   if(Soft_loader_revno[BUF_LEN_6]!= CHAR_H)
   {
      MemSet(Soft_loader_revno, 0, REVNO_MAX_LEN);
      MemCpy(Soft_loader_revno,"DISSL ",CHAR_LEN_6);
   }
   else
   {
      U16_sys_info_words[0] |=SL_REVNO_ERR;
   }

   if(Commf_part[BUF_LEN_6]!= CHAR_H)
   {
      /* hdudispfa429-ProcessSysInfoWords-DB-LLR-011 */
      MemSet(Commf_part, 0, PART_MAX_LEN);
      MemCpy(Commf_part,"COMFA ",CHAR_LEN_6);
   }
   else
   {
      U16_sys_info_words[0] |=COMMF_PART_ERR;
   }

   if(Commb_part[BUF_LEN_6]!= CHAR_H)
   {
      /* hdudispfa429-ProcessSysInfoWords-DB-LLR-012 */
      MemSet(Commb_part, 0, PART_MAX_LEN);
      MemCpy(Commb_part,"COMBL ",CHAR_LEN_6);
   }
   else
   {
      U16_sys_info_words[0] |=COMMB_PART_ERR;
   }
   /* hdudispfa429-ProcessSysInfoWords-DB-LLR-013 */
   if(Maint_part[BUF_LEN_6]!= CHAR_H)
   {
      MemSet(Maint_part, 0, PART_MAX_LEN);
      MemCpy(Maint_part,"COMMA ",CHAR_LEN_6);
   }
   else
   {
      U16_sys_info_words[0] |=MAINT_PART_ERR;
   }
   if(Commsl_part[BUF_LEN_6]!= CHAR_H)
   {
      MemSet(Commsl_part, 0, PART_MAX_LEN);
      MemCpy(Commsl_part,"COMSL ",CHAR_LEN_6);
   }
   else
   {
      U16_sys_info_words[0] |=COMSL_PART_ERR;
   }


   /* hdudispfa429-ProcessSysInfoWords-DB-LLR-014 */
   if(TRUE == A429_data_recieved)
   {
	  MemCpy(&Eiu_heading[0], "DAU SOFTWARE INFO", CHAR_LEN_17);
	  U16_sys_info_words[1] |= DAU_SOFTWARE_INFO_VAL;
   }
   else
   {
      ;/* Does nothing */
   }
   MemCpy(Dau_config_id_dau,Config_data.config_engine, ENG_CONFIG_LEN);

   for(u16_index = 1; u16_index<SYSINFO_LABEL_WORDS; u16_index++)
   {
      /* hdudispfa429-ProcessSysInfoWords-DB-LLR-015 */
      if ('\t' == Sys_info_words[u16_index].data1 || '\r' == Sys_info_words[u16_index].data1 )
      {
         flag1 = 1;
      }
      else
      {
         ;/* Does nothing */
      }

      /* hdudispfa429-ProcessSysInfoWords-DB-LLR-016 */
      if ('\r' == Sys_info_words[u16_index].data2)
      {
         flag2 = 1;
      }
      else
      {
         ;/* Does nothing */
      }

      /* hdudispfa429-ProcessSysInfoWords-DB-LLR-017 */
      if('\t' == Sys_info_words[u16_index].data2)
      {
         flag3 = 1;
      }
      else
      {
         ;/* Does nothing */
      }

      if((Sys_info_words[u16_index].sequence <= SIXTEEN)&&
         (Sys_info_words[u16_index].sequence!=ZERO))
      {
         /* hdudispfa429-ProcessSysInfoWords-DB-LLR-018 */
         if (1 == flag1)
         {
            Eiufli_part[index1++] = (T_UINT8) Sys_info_words[u16_index].data2;
            flag1 = 0;
         }
         else if (1 == flag2)
         {
            Eiufli_part[index1++] = (T_UINT8) Sys_info_words[u16_index].data1;
            flag2 = 0;
         }
         else if (1 == flag3)
         {
            Eiufli_part[index1++] = (T_UINT8) Sys_info_words[u16_index].data1;
            Eiufli_part[index1++] = ' ';
            flag3 = 0;
         }
         else
         {
            Eiufli_part[index1++] = (T_UINT8) Sys_info_words[u16_index].data1;
            Eiufli_part[index1++] = (T_UINT8) Sys_info_words[u16_index].data2;
         }
      }
      else if((Sys_info_words[u16_index].sequence <= THIRTY_TWO)&&
         (Sys_info_words[u16_index].sequence!=ZERO))
      {
         /* hdudispfa429-ProcessSysInfoWords-DB-LLR-019 */
         if (1 == flag1)
         {
            Eiucfg_part[index2++] = (T_UINT8) Sys_info_words[u16_index].data2;
            flag1 = 0;
         }
         else if (1 == flag2)
         {
            Eiucfg_part[index2++] = (T_UINT8) Sys_info_words[u16_index].data1;
            flag2 = 0;
         }
         else if (1 == flag3)
         {
            Eiucfg_part[index2++] = (T_UINT8) Sys_info_words[u16_index].data1;
            Eiucfg_part[index2++] = ' ';
            flag3 = 0;
         }
         else
         {
            Eiucfg_part[index2++] = (T_UINT8) Sys_info_words[u16_index].data1;
            Eiucfg_part[index2++] = (T_UINT8) Sys_info_words[u16_index].data2;
         }
      }
      else if(( Sys_info_words[u16_index].sequence <= SYS_INFO_WORDS_48)&&
         (Sys_info_words[u16_index].sequence!=ZERO))
      {
         /* hdudispfa429-ProcessSysInfoWords-DB-LLR-020 */
         if (1 == flag1)
         {
            Eiucmub_part[index3++] = (T_UINT8) Sys_info_words[u16_index].data2;
            flag1 = 0;
         }
         else if (1 == flag2)
         {
            Eiucmub_part[index3++] = (T_UINT8) Sys_info_words[u16_index].data1;
            flag2 = 0;
         }
         else if (1 == flag3)
         {
            Eiucmub_part[index3++] = (T_UINT8) Sys_info_words[u16_index].data1;
            Eiucmub_part[index3++] = ' ';
            flag3 = 0;
         }
         else
         {
            Eiucmub_part[index3++] = (T_UINT8) Sys_info_words[u16_index].data1;
            Eiucmub_part[index3++] = (T_UINT8) Sys_info_words[u16_index].data2;
         }
      }
      else if( (Sys_info_words[u16_index].sequence <= SYS_INFO_WORDS_64)&&
         (Sys_info_words[u16_index].sequence!=ZERO))
      {
         /* hdudispfa429-ProcessSysInfoWords-DB-LLR-021 */
         if (1 == flag1)
         {
            Eiucmuf_part[index4++] = (T_UINT8) Sys_info_words[u16_index].data2;
            flag1 = 0;
         }
         else if (1 == flag2)
         {
            Eiucmuf_part[index4++] = (T_UINT8) Sys_info_words[u16_index].data1;
            flag2 = 0;
         }
         else if (1 == flag3)
         {
            Eiucmuf_part[index4++] = (T_UINT8) Sys_info_words[u16_index].data1;
            Eiucmuf_part[index4++] = ' ';
            flag3 = 0;
         }
         else
         {
            Eiucmuf_part[index4++] = (T_UINT8) Sys_info_words[u16_index].data1;
            Eiucmuf_part[index4++] = (T_UINT8) Sys_info_words[u16_index].data2;
         }
      }
      else if(( Sys_info_words[u16_index].sequence <= SYS_INFO_WORDS_80)&&
         (Sys_info_words[u16_index].sequence!=ZERO))
      {
         /* hdudispfa429-ProcessSysInfoWords-DB-LLR-022 */
         if (1 == flag1)
         {
            Eiucmum_part[index5++] = (T_UINT8) Sys_info_words[u16_index].data2;
            flag1 = 0;
         }
         else if (1 == flag2)
         {
            Eiucmum_part[index5++] = (T_UINT8) Sys_info_words[u16_index].data1;
            flag2 = 0;
         }
         else if (1 == flag3)
         {
            Eiucmum_part[index5++] = (T_UINT8) Sys_info_words[u16_index].data1;
            Eiucmum_part[index5++] = ' ';
            flag3 = 0;
         }
         else
         {
            Eiucmum_part[index5++] = (T_UINT8) Sys_info_words[u16_index].data1;
            Eiucmum_part[index5++] = (T_UINT8) Sys_info_words[u16_index].data2;
         }
      }
      else
      {
         ;/* Does nothing */
      }
   }

   /* hdudispfa429-ProcessSysInfoWords-DB-LLR-023 */
   if(Eiufli_part[0]!=0)
   {
      U16_sys_info_words[1] |=EIUFLI_PART_ERR;
   }
   else
   {
      ;/* Does nothing */
   }

   if(Eiucfg_part[0]!=0)
   {
      U16_sys_info_words[1] |=EIUCFG_PART_ERR;
   }
   else
   {
      ;/* Does nothing */
   }

   if(Eiucmub_part[0]!=0)
   {
      U16_sys_info_words[1] |=EIUCMUB_PART_ERR;
   }
   else
   {
      ;/* Does nothing */
   }

   if(Eiucmuf_part[0]!=0)
   {
      U16_sys_info_words[1] |=EIUCMUF_PART_ERR;
   }
   else
   {
      ;/* Does nothing */
   }

   if(Eiucmum_part[0]!=0)
   {
      U16_sys_info_words[1] |=EIUCMUM_PART_ERR;
   }
   else
   {
      ;/* Does nothing */
   }
}


/*
 * Function                :  ProcessAirframeInfoWords
 *
 * Description             :  This function processes the system information words read from
 *                            label 370and stores them in proper format to be displayed
 *                            in system information area
 *
 * Formal parameter(s)     :  None
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */

void ProcessAirframeInfoWords(void)
{
   T_UINT8  airframe_id1 = 0,
        airframe_id2 = 0,
        airframe_id3 = 15,
        airframe_id4 = 15,
        airframe_id5 = 15;
   T_UINT8 u16_index = 0;
   T_UINT8 aircrft_model_temp[30] = {0};
   T_UINT8 engine_typ_temp[30] = {0};
   T_UINT8 var_i = 0;
   T_UINT8 split_word1[30] =  {0};
   T_UINT8 split_word2[30] =  {0};
   T_UINT16 len_config_engine = 0;

    for(u16_index = 0; u16_index<AIRFRAME_LABEL_WORDS; u16_index++)
    {
      if((Sys_airframe_words[u16_index].sequence <= ARCFT_MDL_BYTE) &&
         (u16_index <= ARCFT_MDL_BYTE))
      {
         /*hdudispfa429-ProcessAirframeInfoWords-DB-LLR-001*/
         aircrft_model_temp[airframe_id1++] = (T_UINT8) Sys_airframe_words[u16_index].data1;
         aircrft_model_temp[airframe_id1++] = (T_UINT8) Sys_airframe_words[u16_index].data2;
      }
      else if((Sys_airframe_words[u16_index].sequence <= ENGINE_TYPE_BYTE) &&
               (u16_index <= ENGINE_TYPE_BYTE))
      {
         /*hdudispfa429-ProcessAirframeInfoWords-DB-LLR-002*/
         engine_typ_temp[airframe_id2++] = (T_UINT8) Sys_airframe_words[u16_index].data1;
         engine_typ_temp[airframe_id2++] = (T_UINT8) Sys_airframe_words[u16_index].data2;
      }
      else if( (Sys_airframe_words[u16_index].sequence <= ENGINE_SER_BYTE) &&
               (u16_index <= ENGINE_SER_BYTE))
      {
         /*hdudispfa429-ProcessAirframeInfoWords-DB-LLR-003*/
         Engine_serial[airframe_id3++] = (T_UINT8) Sys_airframe_words[u16_index].data1;
         Engine_serial[airframe_id3++] = (T_UINT8) Sys_airframe_words[u16_index].data2;
      }
      else if((Sys_airframe_words[u16_index].sequence <= AICFT_SER_BYTE) &&
               (u16_index <= AICFT_SER_BYTE))
      {
         /*hdudispfa429-ProcessAirframeInfoWords-DB-LLR-004*/
         Aircraft_serial[airframe_id4++] = (T_UINT8) Sys_airframe_words[u16_index].data1;
         Aircraft_serial[airframe_id4++] = (T_UINT8) Sys_airframe_words[u16_index].data2;
      }
      else if(Sys_airframe_words[u16_index].sequence <= AICFT_REGS_BYTE)
      {
         /*hdudispfa429-ProcessAirframeInfoWords-DB-LLR-005*/
         Aircraft_regstrn[airframe_id5++] = (T_UINT8) Sys_airframe_words[u16_index].data1;
         Aircraft_regstrn[airframe_id5++] = (T_UINT8) Sys_airframe_words[u16_index].data2;
      }
      else
      {
         ;/*Do nothing*/
      }
   }

   /*hdudispfa429-ProcessAirframeInfoWords-DB-LLR-009*/
   MemCpy(Dau_config_id_disp,Config_data.config_engine, ENG_CONFIG_LEN);
   len_config_engine = StrLen((T_CHAR *)Dau_config_id_disp);

   for (var_i = 0; var_i<len_config_engine;var_i++)
   {
      if (' ' == Dau_config_id_disp[var_i])
      {
         break;
      }
      else
      {
         ;/*Do nothing*/
      }
   }

   /*hdudispfa429-ProcessAirframeInfoWords-DB-LLR-010*/
   MemCpy(split_word1,Dau_config_id_disp,var_i);
   MemCpy(split_word2,&Dau_config_id_disp[var_i + 1],(T_UINT16)(len_config_engine-var_i));


   if((TRUE == StringCompare((T_CHAR *)split_word1,(T_CHAR *)aircrft_model_temp)) &&
   (TRUE == StringCompare((T_CHAR *)split_word2,(T_CHAR *)engine_typ_temp)))
   {
      /*hdudispfa429-ProcessAirframeInfoWords-DB-LLR-011*/
	  U16_message_words[1] &= ARCFT_ENGN_TYP_ERR_NEG;
   }
   else
   {
      /*hdudispfa429-ProcessAirframeInfoWords-DB-LLR-012*/
	  U16_message_words[1] |= ARCFT_ENGN_TYP_ERR;
   }

   /*hdudispfa429-ProcessAirframeInfoWords-DB-LLR-013*/
   MemCpy(&Aircraft_model[15],aircrft_model_temp,StrLen(( T_CHAR *)aircrft_model_temp));
   MemCpy(&Engine_type[15],engine_typ_temp,StrLen(( T_CHAR *)engine_typ_temp));
   U16_sys_info_words[1] |= (ENGN_SER_PART_ERR|ARCFT_SER_PART_ERR|ARCFT_REG_PART_ERR|
		   ARCFT_MDL_PART_ERR|ENGN_TYP_PART_ERR);

}

/*
 * Function                :  StringCompare
 *
 * Description             :  This function is used to compare the data of two strings.
 *
 * Formal parameter(s)     :  T_CHAR *char1 - IN String 1 to be compared
 *                        T_CHAR *char2 - IN String 2 to be compared
 *
 * Return Value            :  T_BOOL - Comparison Status
 *
 * Assumption              :  None
 *
 */

T_BOOL StringCompare(T_CHAR *char1, T_CHAR *char2)
{
    T_UINT16 len1 = 0;
    T_UINT16 len2 = 0;
    T_UINT8 var_i = 0;

    /*hdudispfa429-StringCompare-DB-LLR-001*/
    len1 = StrLen(char1);
    len2 = StrLen(char2);

    if(len1 == len2)
    {
      /*hdudispfa429-StringCompare-DB-LLR-002*/
      for(var_i = 0; var_i < len2; var_i++)
      {
         if(char1[var_i] == char2[var_i])
         {
           ; /* Do nothing */
         }
         else
         {
           return FALSE;
         }
      }
      return TRUE;
    }
   else
    {
      /*hdudispfa429-StringCompare-DB-LLR-003*/
      return FALSE;
    }
}

/*
 * Function                :  CalibrationLabels
 *
 * Description             :  This function converts the calibration labels to A429 representation
 *
 * Formal parameter(s)     :  None
 *
 * Return Value            : None
 *
 * Assumption              :  None
 *
 */
void CalibrationLabels()
{
	T_UINT8 loop_j = 0;

    /* hdudispfa429-CalibrationLabels-DB-LLR-001 */
	for (loop_j = 0;loop_j < CALILABELCOUNT;loop_j++)
	{
		Calibration_label[loop_j] = (T_UINT8)((Calibration_label[loop_j] & HEX_F0)>>FOUR|
	    (Calibration_label[loop_j] & HEX_0F)<<FOUR);
		Calibration_label[loop_j] = (T_UINT8)((Calibration_label[loop_j] & HEX_CC)>>TWO|
		(Calibration_label[loop_j] & HEX_33)<<TWO);
		Calibration_label[loop_j] = (T_UINT8)((Calibration_label[loop_j] & HEX_AA)>>ONE|
		(Calibration_label[loop_j] & HEX_55)<<ONE);
	}

}


