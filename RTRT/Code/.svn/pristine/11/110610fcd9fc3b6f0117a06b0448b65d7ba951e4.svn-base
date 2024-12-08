/*
 ******************************************************************************
 * License Information  :  Howell Instruments, Inc.                           *
 *                         "Licensed Software" and "All rights reserved".     *
 ******************************************************************************
 *  File                : hdudispfpdidata.c
 *
 *  Description         : This file extracts all the required data from the PDI
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
 *  Author(s)           : Shruthi MN
 *
 *  Version History     :
 * <Version No.>     <Author>          <Date>         <Problem Report No.>
 *
 *      1.1          Shruthi MN        26-Sep-2017             100064
 *      1.2          Divya G P         10-Oct-2017             100064
 *      1.3          Divya G P,
 *                   Shruthi M N       12-Oct-2017             100073,100087
 *      1.4          Shruthi M N       30-Oct-2017             100104
 *      1.5          Rona B.S          09-Nov-2017             100164
 *      1.6          Rona B S          23-Mar-2018             100196
 *      1.7          Rona B S          28-Mar-2018             100196
 *      1.8          Vinay H           05-Apr-2018             100205
 *      1.9          Chaithra J        21-Jun-2020             100259
 *      1.10         Rona B S          30-Jun-2020             100259
 *      1.11         Dhanalakshmi      05-Aug-2020             100270
 *      1.12         Dhanalakshmi      12-Sep-2020             100276
 *      1.13         Dhanalakshmi      28-Sep-2020             100284
 *      1.14         Dhanalakshmi      09-Oct-2020             100288
 *      1.15         Dhanalakshmi     20-Mar-2021              100331
 *      1.16         Dhanalakshmi     20-Mar-2021              100331
 *      1.17         Dhanalakshmi     11-May-2021              100350
 *
 * Additional References : None
 *
 ******************************************************************************
 */

#include "hdudispfgrapp.h"   /* defines graphical applications */
#include "hdudispfpdidata.h" /* provides pdi declarations */
#include "hdudispfbargraphs.h" /* definitions for bar graphs */
#include "hdudispfrounddial.h" /* definitions for round dials */
#include "hdudispfbinascii.h" /* converts character to ascii */
#include "hdudispfpara.h"  /*builds faults, messages, sys info list and configures the top menu*/
#include "hdudispfnumbox.h"  /* definitions for number box */
#include "hdudispfcarrotgraph.h"  /* definitions for number box */
#include "hdudispfmenu.h"    /* contains prototype for menu module*/
#include "hdudispfa429.h"    /* contains definition of a429*/
#include "hdudispfconfig.h"   /* contains page and color config information*/
#include "hdudispfresource.h"  /* provides central location to use On Chip Peripherals*/
#include "hdudispfforeground.h"  /* provides coordinates for displaying redx on screen*/
#include "hdudispfpdicheck.h" /*contains pdi check*/
#include "hdudispfpolygon2.h" /* definitions for polygon */

T_UINT16 A429_settings_cnt __attribute__ ((section(".sdram_var"))) =0;
T_UINT16 Cas_word_cnt=0;
T_UINT8 Exceed_cnt=0;
T_UINT8 Bg_cnt=0;
T_UINT8 Rd_cnt __attribute__ ((section(".sdram_var"))) =0;
T_UINT8 Text_cnt __attribute__ ((section(".sdram_var"))) =0;
T_UINT8 Nb_cnt __attribute__ ((section(".sdram_var"))) =0;
T_UINT8 Cg_cnt __attribute__ ((section(".sdram_var"))) =0;
T_UINT8 Pg_cnt __attribute__ ((section(".sdram_var"))) =0;
T_UINT8 Tb_cnt __attribute__ ((section(".sdram_var"))) =0;
T_UINT8 Cas_cnt __attribute__ ((section(".sdram_var"))) = 0;
T_UINT8 Page_cas __attribute__ ((section(".sdram_var"))) = 0;
T_UINT8 Timer_cnt __attribute__ ((section(".sdram_var"))) =0;
T_BOOL Bg_tracker[PARAMTR_MAX_VAL_FG][PARAMTR_MAX_VAL] __attribute__ ((section(".sdram_var")))= \
																						{FALSE};
T_BOOL Rd_tracker[PARAMTR_MAX_VAL_FG][PARAMTR_MAX_VAL] __attribute__ ((section(".sdram_var")))= \
																						{FALSE};
T_BOOL Cg_tracker[PARAMTR_MAX_VAL_FG][PARAMTR_MAX_VAL] __attribute__ ((section(".sdram_var")))= \
																						{FALSE};
T_BOOL Nb_tracker[PARAMTR_MAX_VAL_FG][PARAMTR_MAX_VAL] __attribute__ ((section(".sdram_var")))= \
																						{FALSE};
T_BOOL Elog_trig_bool = FALSE;
T_BOOL Elog_param = FALSE;
T_BOOL Acdt_parameters = FALSE;
T_BOOL Caslocationset_parameters = FALSE;
T_UINT8 Scu_label_flag = FALSE;

/*Variable to set a bit for the parameters to determine the occurrence*/
T_UINT16 Bg_parameter_occurrence[PARAMTR_MAX_VAL_FG] = {0};
T_UINT16 Rd_parameter_occurrence[PARAMTR_MAX_VAL_FG] = {0};
T_UINT16 Nb_parameter_occurrence[PARAMTR_MAX_VAL] = {0};
T_UINT16 Cg_parameter_occurrence[PARAMTR_MAX_VAL_FG] = {0};
T_UINT16 Tb_parameter_occurrence[PARAMTR_MAX_VAL] = {0};
T_UINT16 Text_parameter_occurrence[PARAMTR_MAX_VAL_FG] = {0};

/* updated as per 100073 */
T_UINT8 Page_name_char_cnt=0;
T_UINT32 Rd_lin_angle_status[PARAMTR_MAX_VAL_FG]  __attribute__ \
                           ((section(".sdram_var"))) = {0};

/* updated as per PR 100073*/
T_CONFIG_STRUCT Config_data  __attribute__ ((section(".sdram_var"))) = {0};

T_LOOKUP_TABLE Bg_lookuptable[30] = {{0,0}};
T_LOOKUP_TABLE Rd_lookuptable[30] = {{0,0}};
T_LOOKUP_TABLE Cg_lookuptable[30] = {{0,0}};
T_SDISREGION Rd_dis_region[30] __attribute__ ((section(".sdram_var")))  = \
{{E_REGION_TYPE_GAUGE,{0},0,0,{0},E_NO_FONT,0}};
T_SDISREGION Bg_dis_region[30] __attribute__ ((section(".sdram_var")))  = \
{{E_REGION_TYPE_GAUGE,{0},0,0,{0},E_NO_FONT,0}};
T_SDISREGION Nb_dis_region[50] __attribute__ ((section(".sdram_var")))  = \
{{E_REGION_TYPE_GAUGE,{0},0,0,{0},E_NO_FONT,0}};
T_SDISREGION Cg_dis_region[30] __attribute__ ((section(".sdram_var")))  = \
{{E_REGION_TYPE_GAUGE,{0},0,0,{0},E_NO_FONT,0}};
T_SDISREGION Txt_dis_region[30] __attribute__ ((section(".sdram_var")))  = \
{{E_REGION_TYPE_GAUGE,{0},0,0,{0},E_NO_FONT,0}};
T_SDISREGION Tb_dis_region[50] __attribute__ ((section(".sdram_var"))) = \
{{E_REGION_TYPE_GAUGE,{0},0,0,{0},E_NO_FONT,0}};

T_SFLOATPOLY Pg_dis_region[30] __attribute__ ((section(".sdram_var"))) = {{
		   0,
		   (T_SFLOATPOLY *)0,
		   {
		      {0 , 0 },
		   }
		}};
T_SFLOATPOLY Pg_inc_dis_region[30] __attribute__ ((section(".sdram_var"))) = {{
		   0,
		   (T_SFLOATPOLY *)0,
		   {
		      {0 , 0 },
		   }
		}};
T_PAGE Page_settings = {0};
T_POLYGRAPH Pg_settings[30] __attribute__ \
                         ((section(".sdram_var")))= {0};

T_CAS_MESSAGE_STRUCT Cas_messages[36] = {0};
T_EXCEED_STRUCT Exceed_data[MAX_NUM_EXCE] ={0};
T_A429_PARAMS A429_cfg_data[256] = {0};

/* TRUE for MD aircrafts */
T_BOOL Md_engine_flag =FALSE;

/* updated as per PR 100073*/
T_UINT8 Max_num_of_pages=0;
T_BOOL Acdt_flag=FALSE;
T_BOOL Timer_flag=FALSE;
/*Updated as per PR100196*/
#define NULL_LABEL 0

T_UINT8 Cond_cnt[MAX_ELOG_EVENT] = {0};
/*
 *
 * Function                : FindColor
 *
 * Description             : This function returns the required color
 *
 * Formal parameter(s)     : T_UINT16 color - IN color sent from PDI
 *
 * Return Value            : T_EPENCOLOR - color returned
 *
 * Assumption              : None
 *
 */

T_EPENCOLOR FindColor(T_UINT16 color)
{
   T_EPENCOLOR ret_val=WHITE;
   if(ZERO == color)
   {
	   ;
   }
   else
   {
   switch(color)
   {
   /*hdudispfpdidata-FindColor-DB-LLR-001*/
   case COLOR_BLACK:
       ret_val=BLACK;
       break;

   /*hdudispfpdidata-FindColor-DB-LLR-002*/
   case COLOR_DARK_RED:
       ret_val=DARK_RED;
       break;

   /*hdudispfpdidata-FindColor-DB-LLR-003*/
   case COLOR_RED:
      ret_val=RED;
      break;

   /*hdudispfpdidata-FindColor-DB-LLR-004*/
   case COLOR_LIGHT_RED:
      ret_val=CAS_REV_RED;
      break;

   /*hdudispfpdidata-FindColor-DB-LLR-005*/
   case COLOR_PINK:
      ret_val=PINK;
      break;

   /*hdudispfpdidata-FindColor-DB-LLR-006*/
   case COLOR_TEAL:
      ret_val=TEAL;
      break;

   /*hdudispfpdidata-FindColor-DB-LLR-007*/
   case COLOR_GREEN:
      ret_val=GREEN;
      break;

   /*hdudispfpdidata-FindColor-DB-LLR-008*/
   case COLOR_BRIGHT_GREEN:
   ret_val=BRIGHT_GREEN;
      break;

   /*hdudispfpdidata-FindColor-DB-LLR-009*/
   case COLOR_TURQUOISE:
   ret_val=TURQUOISE;
      break;

   /*hdudispfpdidata-FindColor-DB-LLR-010*/
   case COLOR_DARK_BLUE:
      ret_val=DARK_BLUE;
      break;

   /*hdudispfpdidata-FindColor-DB-LLR-011*/
   case COLOR_VIOLET:
     ret_val=VIOLET;
      break;

   /*hdudispfpdidata-FindColor-DB-LLR-012*/
   case COLOR_BLUE:
      ret_val=BLUE;
      break;

   /*hdudispfpdidata-FindColor-DB-LLR-013*/
   case COLOR_LIGHT_GRAY:
      ret_val=LIGHT_GRAY;
      break;

   /*hdudispfpdidata-FindColor-DB-LLR-014*/
   case COLOR_GRAY:
      ret_val=GRAY;
      break;

   /*hdudispfpdidata-FindColor-DB-LLR-015*/
   case COLOR_DARK_GRAY:
      ret_val=DARK_GRAY;
      break;

   /*hdudispfpdidata-FindColor-DB-LLR-016*/
   case COLOR_DARK_YELLOW:
      ret_val=DARK_YELLOW;
      break;

   /*hdudispfpdidata-FindColor-DB-LLR-017*/
   case COLOR_YELLOW:
      ret_val=YELLOW;
      break;

   /*hdudispfpdidata-FindColor-DB-LLR-018*/
   case COLOR_ORANGE:
      ret_val=ORANGE;
      break;

   /*hdudispfpdidata-FindColor-DB-LLR-019*/
   case COLOR_WHITE:
      ret_val=WHITE;
      break;

   /*hdudispfpdidata-FindColor-DB-LLR-020*/
    default:
	  ret_val=INVALID_COLOR;
      break;
    }
   }
   return ret_val;
}

/*
 *
 * Function                : TextAlign
 *
 * Description             : This function returns the required alignment of text
 *
 * Formal parameter(s)     : T_UINT16 align - IN align sent from PDI
 *
 * Return Value            : T_ETXALIGN - Align returned
 *
 * Assumption              : None
 *
 */

T_ETXALIGN TextAlign(T_UINT16 align)
{
   T_ETXALIGN ret_val=ALIGN_CENTER;
   switch(align)
   {
   /*hdudispfpdidata-TextAlign-DB-LLR-001*/
   case ALIGN_CENTER_LEFT:
       ret_val=ALIGN_CENTER_LEFT;
       break;

   /*hdudispfpdidata-TextAlign-DB-LLR-002*/
   case ALIGN_RIGHT:
      ret_val=ALIGN_RIGHT;
      break;

   /*hdudispfpdidata-TextAlign-DB-LLR-003*/
   case ALIGN_LEFT:
      ret_val=ALIGN_LEFT;
      break;

  /*hdudispfpdidata-TextAlign-DB-LLR-004*/
   case ALIGN_CENTER:
      ret_val=ALIGN_CENTER;
      break;

   /*hdudispfpdidata-TextAlign-DB-LLR-005*/
   default:
      break;
   }
   /*hdudispfpdidata-TextAlign-DB-LLR-006*/
   return ret_val;
}
/*
 *
 * Function                : TextFlash
 *
 * Description             : This function returns the text flashing status
 *
 * Formal parameter(s)     : T_UINT16 flash - IN flash sent from PDI
 *
 * Return Value            : T_ETXFLASH - Flash returned
 *
 * Assumption              : None
 *
 */

T_ETXFLASH TextFlash(T_UINT16 flash)
{
   T_ETXFLASH ret_val=TX_NO_FLASH;
   switch(flash)
   {
   /*hdudispfpdidata-TextFlash-DB-LLR-001*/
   case TEXT_FLASH_OFF:
       ret_val=TX_NO_FLASH;
       break;

   /*hdudispfpdidata-TextFlash-DB-LLR-002*/
   case TEXT_FLASH_ON:
     ret_val=TX_FLASH;
      break;
   /*hdudispfpdidata-TextFlash-DB-LLR-003*/
   default:
      break;
   }
   /*hdudispfpdidata-TextFlash-DB-LLR-004*/
  return ret_val;
}
/*
 *
 * Function                : TextState
 *
 * Description             : This function returns the text state
 *
 * Formal parameter(s)     : T_UINT16 state - IN state sent from PDI
 *
 * Return Value            : T_ETXV - Flash returned
 *
 * Assumption              : None
 *
 */

T_ETXV TextState(T_UINT16 state)
{
    T_ETXV ret_val=V_NORMAL;
   switch(state)
   {
   /*hdudispfpdidata-TextState-DB-LLR-001*/
   case TXT_STATE_NORMAL:
       ret_val=V_NORMAL;
       break;

   /*hdudispfpdidata-TextState-DB-LLR-002*/
   case TXT_STATE_REVERSE:
     ret_val=V_REVERSE;
      break;
   /*hdudispfpdidata-TextState-DB-LLR-003*/
   default:
      break;
   }
   /*hdudispfpdidata-TextState-DB-LLR-004*/
  return ret_val;
}
/*
 *
 * Function                : FindFormat
 *
 * Description             : This function maps the format obtained from PDI data.
 *
 * Formal parameter(s)     : T_UINT32 format -IN Format
 *
 * Return Value            : T_UINT32 - returns the word size
 *
 * Assumption              : None
 *
 */

T_UINT32 FindFormat(T_UINT32 format)
{
   T_UINT32 ret_word_size=0;

   /*hdudispfpdidata-FindFormat-DB-LLR-001*/
   if(ZERO != (format & NUM_ONEW))
   {
      ret_word_size=ret_word_size|ONEW;
   }
   else
   {
      ; /* Do nothing */
   }

   /*hdudispfpdidata-FindFormat-DB-LLR-002*/
   if(ZERO != (format & NUM_TWOW))
   {
      ret_word_size=ret_word_size|TWOW;
   }
   else
   {
      ; /* Do nothing */
   }

   /*hdudispfpdidata-FindFormat-DB-LLR-003*/
   if(ZERO != (format & NUM_THREEW))
   {
      ret_word_size=ret_word_size|THREEW;
   }
   else
   {
      ; /* Do nothing */
   }

   /*hdudispfpdidata-FindFormat-DB-LLR-004*/
   if(ZERO != (format & NUM_FOURW))
   {
      ret_word_size=ret_word_size|FOURW;
   }
   else
   {
      ; /* Do nothing */
   }

   /*hdudispfpdidata-FindFormat-DB-LLR-005*/
   if(ZERO != (format & NUM_FIVEW))
   {
      ret_word_size=ret_word_size|FIVEW;
   }
   else
   {
      ; /* Do nothing */
   }

   if(ZERO != (format & NUM_SIXW))
   {
      ret_word_size=ret_word_size|SIXW;
   }
   else
   {
      ; /* Do nothing */
   }
   if(ZERO != (format & NUM_SEVENW))
   {
      ret_word_size=ret_word_size|SEVENW;
   }
   else
   {
      ; /* Do nothing */
   }
   if(ZERO != (format & NUM_EIGHTW))
   {
      ret_word_size=ret_word_size|EIGHTW;
   }
   else
   {
      ; /* Do nothing */
   }
   /*hdudispfpdidata-FindFormat-DB-LLR-009*/
   if(ZERO != (format & NUM_ONED))
   {
      ret_word_size=ret_word_size|ONED;
   }
   else
   {
      ; /* Do nothing */
   }
   if(ZERO != (format & NUM_TWOD))
   {
      ret_word_size=ret_word_size|TWOD;
   }
   else
   {
      ; /* Do nothing */
   }
   if(ZERO != (format & NUM_THREED))
   {
      ret_word_size=ret_word_size|THREED;
   }
   else
   {
      ; /* Do nothing */
   }
   if(ZERO != (format & NUM_FOURD))
   {
      ret_word_size=ret_word_size|FOURD;
   }
   else
   {
      ; /* Do nothing */
   }
   if(ZERO != (format & NUM_FIVED))
   {
      ret_word_size=ret_word_size|FIVED;
   }
   else
   {
      ; /* Do nothing */
   }
   if(ZERO != (format & NUM_SIXD))
   {
      ret_word_size=ret_word_size|SIXD;
   }
   else
   {
      ; /* Do nothing */
   }
   if(ZERO != (format & NUM_SEVEND))
   {
      ret_word_size=ret_word_size|SEVEND;
   }
   else
   {
      ; /* Do nothing */
   }

   /*hdudispfpdidata-FindFormat-DB-LLR-016*/
   if(ZERO != (format & NUM_ONEB))
   {
      ret_word_size=ret_word_size|ONEB;
   }
   else
   {
      ; /* Do nothing */
   }

   /*hdudispfpdidata-FindFormat-DB-LLR-017*/
   if(ZERO != (format & NUM_TWOB))
   {
      ret_word_size=ret_word_size|TWOB;
   }
   else
   {
      ; /* Do nothing */
   }

   if(ZERO != (format & NUM_THREEB))
   {
      ret_word_size=ret_word_size|THREEB;
   }
   else
   {
      ; /* Do nothing */
   }
   if(ZERO != (format & NUM_FOURB))
   {
      ret_word_size=ret_word_size|FOURB;
   }
   else
   {
      ; /* Do nothing */
   }
   /*hdudispfpdidata-FindFormat-DB-LLR-020*/
   return ret_word_size;
}

/* Updtaed as per 100073 */
/*
 *
 * Function                : CalculatePower
 *
 * Description             : This function calculates power.
 *
 * Formal parameter(s)     : T_FLOAT value -IN base value
 *                           T_INT32 mul - INOUT power value
 *
 * Return Value            : T_FLOAT - returns the result of raising value to the power mul
 *
 * Assumption              : None
 *
 */
T_FLOAT CalculatePower (T_FLOAT value, T_INT32 mul)
{
   T_UINT32 index = 0;
   T_FLOAT new_value = 0;

   /* hdudispfpdidata-CalculatePower-DB-LLR-001 */
   new_value = value;

   /* hdudispfpdidata-CalculatePower-DB-LLR-002 */
   /*if mul is 0, return the value of 1 */
   if(0 == mul)
   {
      /*if below 0 apply n -1 */
      return 1.0f;
   }
   else
   {
      ; /* Do nothing */
   }

   /*if less than 0 , multiply by -1*/
   if (mul < 0)
   {
      /* hdudispfpdidata-CalculatePower-DB-LLR-003 */
      mul = (mul*-1);
      for (index = 0; index < (T_UINT32)mul+1; index++)
      {
         new_value /= value;
      }
   }
   else
   {
      /* hdudispfpdidata-CalculatePower-DB-LLR-004 */
      for (index = 0; index <(T_UINT32)mul-1; index++)
      {
         new_value *= value;
      }
   }

   /* hdudispfpdidata-CalculatePower-DB-LLR-005 */
   return new_value;
}

/*
 *
 * Function                : IeeeToFloat
 *
 * Description             : This function converts IEEE format into floating point format.
 *
 * Formal parameter(s)     : T_UINT32 number_convert IN- number to be converted
 *
 * Return Value            : T_FLOAT - converted number
 *
 * Assumption              : None
 */

T_FLOAT IeeeToFloat(T_UINT32 number_convert)
{
   T_UINT32 sign=0;
   T_UINT32 mantissa=0;
   T_UINT32 exponent=0;
   T_FLOAT num_f=0.0f;

   /*hdudispfpdidata-IeeeToFloat-DB-LLR-001*/
   if (0 != number_convert)
   {
      sign=(number_convert>>THIRTY_ONE) & 1;
      exponent=number_convert>>23 & 0xFF;
      mantissa=(number_convert&0xFFFFFF)|0x800000;

     /* Updtaed as per 100073 */
      num_f=(T_FLOAT)((CalculatePower((-1),(T_INT32)sign)*((T_FLOAT)mantissa*
                  CalculatePower(2,POWER_23))*CalculatePower(2,((T_INT32)(exponent-
                             (T_UINT32)EXPONENT_127)))));
   }
   else
   {
      ;/*Do nothing*/
   }
   return num_f;
}

/*
 * Function                : FindCasType
 *
 * Description             : This function returns the CAS type
 *
 * Formal parameter(s)     : T_UINT16 type IN - data to be searched
 *
 * Return Value            : T_CAS_TYPE - returns CAS types
 *
 * Assumption              : None
 *
 */

T_CAS_TYPE FindCasType(T_UINT16 type)
{
   T_CAS_TYPE ret_val=CAS_ADVISORY;
   switch(type)
   {
   /*hdudispfpdidata-FindCasType-DB-LLR-001*/
   case ADVISORY:
       ret_val=CAS_ADVISORY;
       break;

   /*hdudispfpdidata-FindCasType-DB-LLR-002*/
   case CAUTION:
       ret_val=CAS_CAUTION;
       break;

   /*hdudispfpdidata-FindCasType-DB-LLR-003*/
   case WARNING:
       ret_val=CAS_WARNING;
       break;

   /*hdudispfpdidata-FindCasType-DB-LLR-004*/
   default:
      break;
   }
   return ret_val;
}

/*
 * Function                : FindParamType
 *
 * Description             : This function returns the Param type
 *
 * Formal parameter(s)     : T_UINT16 type IN - data to be searched
 *
 * Return Value            : T_PARAM_STAT - returns PARAM types
 *
 * Assumption              : None
 *
 */

T_PARAM_STAT FindParamType(T_UINT16 type)
{

	T_PARAM_STAT ret_val=PARAM_OK;
	/* hdudispfpdidata-FindParamType-DB-LLR-001 */
    switch(type)
    {
    case TYPE_NORMAL:
    	ret_val=PARAM_OK;
	    break;
    case TYPE_ADVISORY:
    	ret_val=PARAM_ADVISORY;
	    break;
	case TYPE_CAUTION:
	    ret_val=PARAM_CAUTION;
	    break;
	case TYPE_WARNING:
	    ret_val=PARAM_WARNING;
	    break;
    default:
    	break;
   }
   return ret_val;

}

/* Updated for PR 100073 */
/*
 * Function                : NumberOfPages
 *
 * Description             : This function identifies the number of pages
 *
 * Formal parameter(s)     : None
 *
 * Return Value            : None
 *
 * Assumption              : None
 *
 */

void NumberOfPages(void)
{
   T_UINT8 page_count=0;
   T_UINT8 len_val=0;
   T_UINT8 page_char_cnt=0; /* Page character count*/
   T_UINT16 char_en_cnt=0; /* character count in encoder string*/

   /* hdudispfpdidata-NumberOfPages-DB-LLR-001 */
   while((page_count < EPAGE19) && (*((T_UINT8 *)((page_count* SECTOR_SIZE + PAGE_NUM_BASE_ADDR)+\
         len_val))
                                      != INVALID_PAGE_NUM))
   {
      if(page_count!= ZERO )
      {
         page_char_cnt = ZERO;
         len_val = (T_UINT8)(len_val + THREE);
         while(((*((T_UINT8 *)((page_count*SECTOR_SIZE+PAGE_NUM_BASE_ADDR)+len_val)))!= ZERO)
                               && (page_char_cnt < MAX_NUM_CHAR))
         {
            Encoder_page_text[char_en_cnt]=(*((T_UINT8 *)((page_count*SECTOR_SIZE +
                                  PAGE_NUM_BASE_ADDR)+len_val)));
            char_en_cnt++;
            len_val++;
            page_char_cnt++;
         }
         if(Page_name_char_cnt<page_char_cnt)
         {
          Page_name_char_cnt=page_char_cnt;
         }
         else
         {
            ;/* Does nothing */
         }
         Encoder_page_text[char_en_cnt++]='\r';
         Encoder_page_text[char_en_cnt++]='\n';
      }
      else
      {
         ;/* Does nothing */
      }
      len_val=TWO;
      page_count++;
   }

   /* hdudispfpdidata-NumberOfPages-DB-LLR-002 */
   Max_num_of_pages=page_count;
}

/* Updated for PR 100073 */
/*
 * Function                : ConfigExtract
 *
 * Description             : This function extract the configuration info
 *
 * Formal parameter(s)     : T_UINT8 *address - IN address from where configuration
 *                           info is extracted
 *
 * Return Value            : None
 *
 * Assumption              : None
 *
 */
void ConfigExtract(T_UINT8 *address)
{
   T_UINT8 index_val=0;
   T_UINT16 len_val=0;

   /* hdudispfpdidata-ConfigExtract-DB-LLR-001 */
   if( (T_UINT8 *)NULL == address)
   {
      return;
   }
   else
   {
      ;/* DOes nothing */
   }

   /* hdudispfpdidata-ConfigExtract-DB-LLR-002 */
   len_val=TWO;
   index_val=ZERO;

   /* hdudispfpdidata-ConfigExtract-DB-LLR-003 */
   while((*((T_UINT8 *)(address+len_val))!= ZERO ) && (index_val< MAX_CONFIG))
   {
      Config_data.config_name[index_val]=*((T_UINT8 *)(address+len_val));
      index_val++;
      len_val++;
   }

   /* hdudispfpdidata-ConfigExtract-DB-LLR-004 */
   Config_data.config_name[index_val]=*((T_UINT8 *)(address+len_val));

   len_val=(T_UINT16)(len_val+THREE);

   Config_data.du_resolution.u16_x=*((T_UINT16 *)(address+len_val));
   len_val=(T_UINT16)(len_val+TWO);
   Config_data.du_resolution.u16_y=*((T_UINT16 *)(address+len_val));
   len_val=(T_UINT16)(len_val+TWO);

   index_val = ZERO;
   len_val=(T_UINT16)(len_val+TWO);
   while(index_val < ENG_CONFIG_LEN &&(*((T_UINT8 *)(address+len_val))!= ZERO ) )
   {
      Config_data.config_engine[index_val]=*((T_UINT8 *)(address+len_val));
      index_val++;
      len_val++;
   }

   len_val=(T_UINT16)(len_val+THREE);

   Config_data.channels.u16_x=*((T_UINT16 *)(address+len_val));
   len_val=(T_UINT16)(len_val+TWO);
   Config_data.channels.u16_y=*((T_UINT16 *)(address+len_val));
   len_val=(T_UINT16)(len_val+TWO);

   len_val=(T_UINT16)(len_val+TWO);

   Config_data.eng_sdi=*((T_UINT8 *)(address+len_val));

   len_val=(T_UINT16)(len_val+THREE);
   Config_data.scu_enable=*((T_UINT8 *)(address+len_val));
   address = (T_UINT8*)(PDI_PART_NUM_ADDR);
   len_val = ZERO;
   index_val = ZERO;

   /* hdudispfpdidata-ConfigExtract-DB-LLR-005 */
   while(index_val < PDI_PART_NUM_SIZE )
   {
      Config_data.config_version[index_val]=*((T_UINT8 *)(address+len_val));
      index_val++;
      len_val++;
   }

   /* hdudispfpdidata-ConfigExtract-DB-LLR-006 */
   Config_data.config_CRC=*((T_UINT32 *)(address+len_val));

     /*hdudispfpdidata-ConfigExtract-DB-LLR-007*/
   if('M' == Config_data.config_engine[0]  && 'D' == Config_data.config_engine[1])
   {
       Md_engine_flag = TRUE;
   }
   else
   {
	   Md_engine_flag = FALSE;
   }
}
/*
 *
 * Function                : GlobalExtract
 *
 * Description             : This function extracts global parameters
 *
 * Formal parameter(s)     : T_UINT8 *address IN- page address
 *
 * Return Value            : None
 *
 * Assumption              : None
 *
 */

void GlobalExtract(T_UINT8 *address)
{
	T_UINT8 indx=0;
    T_UINT8 u8_j=0;
    T_UINT32 offset=0;
    T_UINT16 var_j=0;
    T_UINT16 var_i=0;
    T_UINT16 enum_val=0;
    T_UINT16 element=0;
    T_UINT32 length_count=0;
	Pg_cnt=0;

	/* hdudispfpdidata-GlobalExtract-DB-LLR-001 */
	for(var_i=0;var_i<MAX_POLYGON_GRAPHS;var_i++)
	{
	    length_count=0;
		while(length_count<SECTOR_SIZE)
		{

		  enum_val=*((T_UINT16 *)(address+offset+length_count));
		  length_count=length_count+TWO;
		  if(MAX_16_BITS == enum_val)
		  {
			 break;
		  }
		  else
		  {
			 ;
		  }
		  /* hdudispfpdidata-GlobalExtract-DB-LLR-002 */
		  if(ELEMENT_GLOBAL == enum_val)
		  {

			 element=*((T_UINT16 *)(address+offset+length_count));
			 length_count=length_count+TWO;
			 if (POLY_GRAPH == element)
			 {

				 Pg_cnt++;
				 Pg_settings[Pg_cnt-1].element=element;
			 }
			 else
			 {
				 ;
			 }
		  }
		  else
		  {
			  switch(enum_val)
			  {
				  case POLY_SHAPE:
						/* hdudispfpdidata-GlobalExtract-DB-LLR-003 */
					   Pg_settings[Pg_cnt-1].poly_shape=
							 *((T_UINT16 *)(address+offset+length_count));
					   length_count=length_count+TWO;
					   break;
					case POLY_NO_PTS:
						/* hdudispfpdidata-GlobalExtract-DB-LLR-004 */
					   Pg_settings[Pg_cnt-1].poly_no_pts=
							 *((T_UINT8 *)(address+offset+length_count));
					   length_count=length_count+1;
					   break;
					case POLY_PTS:
						/* hdudispfpdidata-GlobalExtract-DB-LLR-005 */
					   for(var_j=0;var_j<Pg_settings[Pg_cnt-1].poly_no_pts;var_j++)
					   {
						  Pg_settings[Pg_cnt-1].poly_pts[var_j][0]=
								  IeeeToFloat(*((T_UINT32 *)(address+offset+length_count)));
						  length_count=length_count+FOUR;
						  Pg_settings[Pg_cnt-1].poly_pts[var_j][1]=
								  IeeeToFloat(*((T_UINT32 *)(address+offset+length_count)));
						  length_count=length_count+FOUR;
					   }
					   break;
				case POLY_INC_NO_PTS:
					/* hdudispfpdidata-GlobalExtract-DB-LLR-006 */
				   Pg_settings[Pg_cnt-1].poly_inc_no_pts=
						 *((T_UINT8 *)(address+offset+length_count));
				   length_count=length_count+1;
				   break;
				case POLY_INC_PTS:
					/* hdudispfpdidata-GlobalExtract-DB-LLR-007 */
				   for(var_j=0;var_j<Pg_settings[Pg_cnt-1].poly_inc_no_pts;var_j++)
				   {
					  Pg_settings[Pg_cnt-1].poly_inc_pts[var_j][0]=
							  IeeeToFloat(*((T_UINT32 *)(address+offset+length_count)));
					  length_count=length_count+FOUR;
					  Pg_settings[Pg_cnt-1].poly_inc_pts[var_j][1]=
							  IeeeToFloat(*((T_UINT32 *)(address+offset+length_count)));
					  length_count=length_count+FOUR;
				   }
				   break;
					  default:
						 break;

			  }
		   }
		}
		/* hdudispfpdidata-GlobalExtract-DB-LLR-007 */
		offset=offset+500;
    }
	/* POLY GRAPH */
	  /* hdudispfpdidata-GlobalExtract-DB-LLR-008 */
	  for(indx=0;indx<MAX_POLYGON_GRAPHS;indx++)
	  {
		   MemSet(&Ap_poly_graph[indx],0,sizeof(T_POLYGRAPHDEF));
	  }
	  for(indx=0;indx<Pg_cnt;indx++)
	  {
			/* hdudispfpdidata-GlobalExtract-DB-LLR-009 */
		  Ap_poly_graph[indx].polygon_shape = Pg_settings[indx].poly_shape;
		  Ap_poly_graph[indx].polygon_no_pts = Pg_settings[indx].poly_no_pts;
		  Pg_dis_region[indx].s16Points =  Pg_settings[indx].poly_no_pts;
			/* hdudispfpdidata-GlobalExtract-DB-LLR-010 */
		  for(u8_j=0;u8_j<Pg_settings[indx].poly_no_pts;u8_j++)
		  {
			  Pg_dis_region[indx].asFloatPoint[u8_j].fX= \
			  (T_FLOAT)Pg_settings[indx].poly_pts[u8_j][0];
			  Pg_dis_region[indx].asFloatPoint[u8_j].fY= \
			  (T_FLOAT)Pg_settings[indx].poly_pts[u8_j][1];
		  }
			/* hdudispfpdidata-GlobalExtract-DB-LLR-011 */
		  if (Pg_settings[indx].poly_inc_no_pts != 0)
			{

			 Pg_inc_dis_region[indx].s16Points =  Pg_settings[indx].poly_inc_no_pts;
			 for(u8_j=0;u8_j<Pg_settings[indx].poly_inc_no_pts;u8_j++)
			  {
				  Pg_inc_dis_region[indx].asFloatPoint[u8_j].fX= \
				  (T_FLOAT)Pg_settings[indx].poly_inc_pts[u8_j][0];
				  Pg_inc_dis_region[indx].asFloatPoint[u8_j].fY= \
				  (T_FLOAT)Pg_settings[indx].poly_inc_pts[u8_j][1];
				  Pg_inc_dis_region[indx].psNext = NULL;
			  }
			  Pg_dis_region[indx].psNext = &Pg_inc_dis_region[indx];
		     }
		  else
		  {
			  Pg_dis_region[indx].psNext = NULL;
		  }
			/* hdudispfpdidata-GlobalExtract-DB-LLR-012 */
		  Ap_poly_graph[indx].polystruct = &Pg_dis_region[indx];
	  }

        /* hdudispfpdidata-GlobalExtract-DB-LLR-013 */
		 element=*((T_UINT16 *)(address+offset+2));
		 if (POLY_GRAPH == element)
		 {
			 Pg_cnt++;
		 }
		 else
		 {
			 ;
		 }
}

/*
 *
 * Function                : PageExtract
 *
 * Description             : This function extracts page settings from pdi
 *
 * Formal parameter(s)     : T_UINT8 *address IN- page address
 *
 * Return Value            : None
 *
 * Assumption              : None
 *
 */
/* Updtaed as per 100073 */
void PageExtract(T_UINT8 *address)
{
   T_UINT32 offset=0;
   T_UINT16 var_j=0;  /* character count in page name*/
   T_UINT16 enum_val=0;
   T_UINT32 length_count=0;

   length_count=0;

   /* hdudispfpdidata-PageExtract-DB-LLR-001 */
   if(NULL == address)
   {
      return;
   }
   else
   {
      ;/*Do nothing*/
   }

   /* hdudispfpdidata-PageExtract-DB-LLR-002 */
   Acdt_flag=FALSE;
   Timer_flag = FALSE;
   Page_settings.menu_color= BLUE;
   Page_settings.action_color = DARK_BLUE;
   Page_settings.menu_txt_color = WHITE;

   while(length_count<PAGE_SET_LEN)
   {
      /* hdudispfpdidata-PageExtract-DB-LLR-003 */
      enum_val=*((T_UINT16 *)(address+offset+length_count));
      length_count=length_count+TWO;
      if(MAX_16_BITS == enum_val)
      {
         break;
      }
      else
      {
         ;
      }

      switch(enum_val)
      {
         case PAGE_NUM:
            /* hdudispfpdidata-PageExtract-DB-LLR-004 */
            Page_settings.page_num=*((T_UINT8 *)(address+offset+length_count));
            length_count=length_count+1;
            break;
         case PAGE_NAME:
            /* hdudispfpdidata-PageExtract-DB-LLR-005 */
            var_j=0;
            while(ZERO != (*((T_UINT8 *)(address+offset+length_count))) && (var_j<20))
            {
               Page_settings.page_name[var_j]=*((T_UINT8 *)(address+offset+length_count));
               var_j++;
               length_count++;
            }
            Page_settings.page_name[var_j]=*((T_UINT8 *)(address+offset+length_count));
            length_count++;
            break;
         case PAGE_MENU:
            /* hdudispfpdidata-PageExtract-DB-LLR-006 */
        	/* Starting from left, if bit in nth position is set to 1 it indicates that */
			/*Button n is enabled for the page. */
            /*For e.g. value 0x2 indicates Button 1 is enabled; value 0x3FFE (16382) */
			/*indicates buttons 1 – 13 have been enabled */
            Page_settings.page_menu=*((T_UINT32 *)(address+offset+length_count));
            length_count=length_count+FOUR;
            break;
         case PAGE_MENU_COLOR:
            /* hdudispfpdidata-PageExtract-DB-LLR-007 */
            Page_settings.menu_color=FindColor(*((T_UINT16 *)(address+offset+length_count)));
            length_count=length_count+TWO;
            break;
         case PAGE_ACTION_COLOR:
            /* hdudispfpdidata-PageExtract-DB-LLR-008 */
            Page_settings.action_color=FindColor(*((T_UINT16 *)(address+offset+length_count)));
            length_count=length_count+TWO;
            break;
         case MENU_TXT_COLOR:
            /* hdudispfpdidata-PageExtract-DB-LLR-009 */
            Page_settings.menu_txt_color=FindColor(*((T_UINT16 *)(address+offset+length_count)));
            length_count=length_count+TWO;
            break;
         case TIMER_AXIS:
            /* hdudispfpdidata-PageExtract-DB-LLR-010 */
            Page_settings.timer_axis.u16_x=*((T_UINT16 *)(address+offset+length_count));
            length_count=length_count+TWO;
            Page_settings.timer_axis.u16_y=*((T_UINT16 *)(address+offset+length_count));
            length_count=length_count+TWO;
            Timer_flag = TRUE;
            break;
         case TIMER_FONT:
            /* hdudispfpdidata-PageExtract-DB-LLR-011 */
            Page_settings.timer_font=*((T_UINT16 *)(address+offset+length_count));
            length_count=length_count+TWO;
            break;
         case ACDT_AXIS:
            /* hdudispfpdidata-PageExtract-DB-LLR-013 */
            Page_settings.acdt_axis.u16_x=*((T_UINT16 *)(address+offset+length_count));
            length_count=length_count+TWO;
            Page_settings.acdt_axis.u16_y=*((T_UINT16 *)(address+offset+length_count));
            length_count=length_count+TWO;
            Acdt_flag=TRUE;
            break;
         default:
            break;
      }
   }
}

/*
 *
 * Function                : ForegroundExtract
 *
 * Description             : This function extracts foreground elements from pdi
 *
 * Formal parameter(s)     : T_UINT8 *address IN- page address
 *
 * Return Value            : None
 *
 * Assumption              : None
 *
 */

void ForegroundExtract(T_UINT8 *address)
{
   T_UINT8 indx=0;
   T_UINT8 u8_i=0;
   T_UINT8 u8_j=0;
   T_UINT32 offset=0;
   T_UINT16 var_j=0;
   T_UINT16 enum_val=0;
   T_UINT16 element=0;
   T_UINT16 num_dec=0;
   T_UINT32 length_count=0;
   T_FLOAT rd_lin_rnge[30][16]={{0}};
   T_BOOL scu_bg_limval[2] = {FALSE,FALSE};

   /* hdudispfpdidata-ForegroundExtract-DB-LLR-001 */
   if(NULL==address)
   {
      return;
   }
   else
   {
      ;/*Do nothing*/
   }

   /* hdudispfpdidata-ForegroundExtract-DB-LLR-002 */
   length_count=0;
   offset=0;
   Bg_cnt=0;
   Rd_cnt=0;
   Nb_cnt=0;
   Tb_cnt=0;
   Text_cnt = 0;
   Cg_cnt=0;
   Timer_cnt=0;
   while(length_count<SECTOR_SIZE)
   {
      /* hdudispfpdidata-ForegroundExtract-DB-LLR-003 */
      enum_val=*((T_UINT16 *)(address+offset+length_count));
      length_count=length_count+TWO;
      if(MAX_16_BITS == enum_val)
      {
         break;
      }
      else
      {
         ;/*Do nothing*/
      }
      if(ELEMENT == enum_val)
      {
         /* hdudispfpdidata-ForegroundExtract-DB-LLR-004 */
         element=*((T_UINT16 *)(address+offset+length_count));
         length_count=length_count+TWO;
         if(BAR_GRAPH == element)
         {
            /* hdudispfpdidata-ForegroundExtract-DB-LLR-005 */
            Bg_cnt++;
            Page_settings.Bg_settings[Bg_cnt-1].element=element;
            enum_val=*((T_UINT16 *)(address+offset+length_count));
            length_count=length_count+TWO;
            if(LABEL == enum_val)
            {
               Page_settings.Bg_settings[Bg_cnt-1].label =
                             *((T_UINT8 *)(address+offset+length_count));
               length_count=length_count+1;
            }
            else
            {
               ;/*Do nothing*/
            }
            /* hdudispfpdidata-ForegroundExtract-DB-LLR-005 */
            enum_val=*((T_UINT16 *)(address+offset+length_count));
            length_count=length_count+TWO;
            if(SDI == enum_val)
            {
                Page_settings.Bg_settings[Bg_cnt-1].sdi =
                              *((T_UINT8 *)(address+offset+length_count));
                length_count=length_count+1;
            }
            else
            {
                ;/*Do nothing*/
            }
         }
         else if (ROUND_DIAL == element)
         {
            /* hdudispfpdidata-ForegroundExtract-DB-LLR-006 */
            Rd_cnt++;
            Page_settings.Rd_settings[Rd_cnt-1].element=element;
            enum_val=*((T_UINT16 *)(address+offset+length_count));
            length_count=length_count+TWO;
            if(LABEL==enum_val)
            {
               Page_settings.Rd_settings[Rd_cnt-1].label =
                              *((T_UINT8 *)(address+offset+length_count));
               length_count=length_count+1;
            }
            else
            {
               ;/*Do nothing*/
            }
            Rd_lin_angle_status[Rd_cnt-1] = ZERO;
            /* hdudispfpdidata-ForegroundExtract-DB-LLR-006 */
            enum_val=*((T_UINT16 *)(address+offset+length_count));
            length_count=length_count+TWO;
            if(SDI==enum_val)
            {
                Page_settings.Rd_settings[Rd_cnt-1].sdi =
                              *((T_UINT8 *)(address+offset+length_count));
               length_count=length_count+1;
            }
            else
            {
               ;/*Do nothing*/
            }

         }
         else if (NUMBER_BOX == element)
         {
            /* hdudispfpdidata-ForegroundExtract-DB-LLR-008 */
            Nb_cnt++;
            Page_settings.Nb_settings[Nb_cnt-1].element=element;
            enum_val=*((T_UINT16 *)(address+offset+length_count));
            length_count=length_count+TWO;
            if(LABEL==enum_val)
            {
               Page_settings.Nb_settings[Nb_cnt-1].label =
                                     *((T_UINT8 *)(address+offset+length_count));
               length_count=length_count+1;
            }
            else
            {
               ;/*Do nothing*/
            }
            enum_val=*((T_UINT16 *)(address+offset+length_count));
            length_count=length_count+TWO;
            if(SDI==enum_val)
            {
               Page_settings.Nb_settings[Nb_cnt-1].sdi =
                        *((T_UINT8 *)(address+offset+length_count));
               length_count=length_count+1;
            }
            else
            {
               ;/*Do nothing*/
            }
         }
         else if (CARROT_GRAPH == element)
         {
             /* hdudispfpdidata-ForegroundExtract-DB-LLR-081 */
             Cg_cnt++;
             Page_settings.Cg_settings[Cg_cnt-1].element=element;
             enum_val=*((T_UINT16 *)(address+offset+length_count));
             length_count=length_count+TWO;
             if(LABEL==enum_val)
             {
                Page_settings.Cg_settings[Cg_cnt-1].label =
                               *((T_UINT8 *)(address+offset+length_count));
                length_count=length_count+1;
             }
             else
             {
                ;/*Do nothing*/
             }
             enum_val=*((T_UINT16 *)(address+offset+length_count));
             length_count=length_count+TWO;
             if(SDI==enum_val)
             {
                Page_settings.Cg_settings[Cg_cnt-1].sdi =
                             *((T_UINT8 *)(address+offset+length_count));
                length_count=length_count+1;
             }
             else
             {
                ;/*Do nothing*/
             }

         }
        else if (TEXT_BOX_PDI == element)
         {
         /* hdudispfpdidata-ForegroundExtract-DB-LLR-141 */
            Tb_cnt++;
            Page_settings.Tb_settings[Tb_cnt-1].element=element;
            enum_val=*((T_UINT16 *)(address+offset+length_count));
            length_count=length_count+TWO;
            if(LABEL==enum_val)
            {
               Page_settings.Tb_settings[Tb_cnt-1].label =
                                     *((T_UINT8 *)(address+offset+length_count));
               length_count=length_count+1;
            }
            else
            {
            	;
            }
            enum_val=*((T_UINT16 *)(address+offset+length_count));
            length_count=length_count+TWO;
            if(SDI==enum_val)
            {
               Page_settings.Tb_settings[Tb_cnt-1].sdi =
                            *((T_UINT8 *)(address+offset+length_count));
               length_count=length_count+1;
            }
            else
            {
               ;/*Do nothing*/
            }
         }
         else if (TEXT_ONLY == element)
         {
         /* hdudispfpdidata-ForegroundExtract-DB-LLR-142 */
            Text_cnt++;
            Page_settings.Text_settings[Text_cnt-1].element=element;
            enum_val=*((T_UINT16 *)(address+offset+length_count));
            length_count=length_count+TWO;
            if(LABEL==enum_val)
            {
               Page_settings.Text_settings[Text_cnt-1].label =
                                     *((T_UINT8 *)(address+offset+length_count));
               length_count=length_count+1;
               enum_val=*((T_UINT16 *)(address+offset+length_count));
            }
            if(SDI==enum_val)
            {
               length_count=length_count+TWO;
               Page_settings.Text_settings[Text_cnt-1].sdi =
                            *((T_UINT8 *)(address+offset+length_count));
               length_count=length_count+1;
            }
            else
            {
               ;/*Do nothing*/
            }
         }
		 /*hdudispfpdidata-ForegroundExtract-DB-LLR-165*/
         else if(EXCEED_TIMER == element)
         {
            Timer_cnt++;
            Page_settings.Timer_settings[Timer_cnt-1].element=element;
            enum_val=*((T_UINT16 *)(address+offset+length_count));
            length_count=length_count+TWO;
            if(LABEL == enum_val)
            {
               Page_settings.Timer_settings[Timer_cnt-1].timer_label =
                             *((T_UINT8 *)(address+offset+length_count));
               length_count=length_count+1;
            }
            else
            {
               ;/*Do nothing*/
            }
            enum_val=*((T_UINT16 *)(address+offset+length_count));
            length_count=length_count+TWO;
            if(SDI == enum_val)
            {
                Page_settings.Timer_settings[Timer_cnt-1].timer_sdi =
                              *((T_UINT8 *)(address+offset+length_count));
                length_count=length_count+1;
            }
            else
            {
                ;/*Do nothing*/
            }
         }
      }
      else
      {
         switch(enum_val)
         {
            case BG_AXIS:
               /* hdudispfpdidata-ForegroundExtract-DB-LLR-011 */
               Page_settings.Bg_settings[Bg_cnt-1].bg_axis.u16_x=
                              *((T_UINT16 *)(address+offset+length_count));
               length_count=length_count+TWO;
               Page_settings.Bg_settings[Bg_cnt-1].bg_axis.u16_y=
                              *((T_UINT16 *)(address+offset+length_count));
               length_count=length_count+TWO;
               break;
            case BG_NO_LIN:
               /* hdudispfpdidata-ForegroundExtract-DB-LLR-012 */
               Page_settings.Bg_settings[Bg_cnt-1].bg_no_lin=
                              *((T_UINT8 *)(address+offset+length_count));
               length_count=length_count+1;
               break;
            case BG_LIN_RANGE:
               /* hdudispfpdidata-ForegroundExtract-DB-LLR-013 */
               Page_settings.Bg_settings[Bg_cnt-1].bg_lin_range[0]=
                   Page_settings.Bg_settings[Bg_cnt-1].bg_no_lin;
               for(var_j=1;var_j<=Page_settings.Bg_settings[Bg_cnt-1].bg_no_lin;var_j++)
               {
                  /* Updated as per PR 100073 */
                  Page_settings.Bg_settings[Bg_cnt-1].bg_lin_range[var_j]=(T_INT32)
                 (IeeeToFloat(*((T_UINT32 *)(address+offset+length_count))));
                  length_count=length_count+FOUR;
               }
               break;
            case BG_LIN_LENGTH:
               /* hdudispfpdidata-ForegroundExtract-DB-LLR-014 */
               Page_settings.Bg_settings[Bg_cnt-1].bg_lin_length[0]=
                     Page_settings.Bg_settings[Bg_cnt-1].bg_no_lin;
               for(var_j=1;var_j<=Page_settings.Bg_settings[Bg_cnt-1].bg_no_lin;var_j++)
               {
                  Page_settings.Bg_settings[Bg_cnt-1].bg_lin_length[var_j]=
                        (T_INT32)MAG_BG(*((T_INT16 *)(address+offset+length_count)));
                  length_count=length_count+TWO;
               }
               break;
            case BG_WIDTH:
               /* hdudispfpdidata-ForegroundExtract-DB-LLR-015 */
               Page_settings.Bg_settings[Bg_cnt-1].bg_width =
                                          *((T_UINT16 *)(address+offset+length_count));
               length_count=length_count+TWO;
               break;
            case BG_ORIEN:
               /* hdudispfpdidata-ForegroundExtract-DB-LLR-016 */
               Page_settings.Bg_settings[Bg_cnt-1].bg_orien =
                                          *((T_UINT16 *)(address+offset+length_count));
               length_count=length_count+TWO;
               /*Variable to determine the occurrence of the parameter*/
               Bg_parameter_occurrence[Bg_cnt-1] |= BIT_ONE;
               break;
            case BG_NB_AXIS:
               /* hdudispfpdidata-ForegroundExtract-DB-LLR-017 */
               Nb_cnt++;
               Bg_tracker[Bg_cnt-1][Nb_cnt-1] = TRUE;
               Page_settings.Nb_settings[Nb_cnt-1].nb_axis.u16_x=
                     *((T_UINT16 *)(address+offset+length_count));
               length_count=length_count+TWO;
               Page_settings.Nb_settings[Nb_cnt-1].nb_axis.u16_y=
                     *((T_UINT16 *)(address+offset+length_count));
               length_count=length_count+TWO;
               Page_settings.Nb_settings[Nb_cnt-1].label=
                     Page_settings.Bg_settings[Bg_cnt-1].label;
               Page_settings.Nb_settings[Nb_cnt-1].sdi=
                     Page_settings.Bg_settings[Bg_cnt-1].sdi;
               Bg_parameter_occurrence[Bg_cnt-1] |= BIT_TWO;
               break;
            case BG_NB_FORMAT:
               /* hdudispfpdidata-ForegroundExtract-DB-LLR-018 */
               Page_settings.Nb_settings[Nb_cnt-1].nb_format=
                     *((T_UINT32 *)(address+offset+length_count));
               Page_settings.Bg_settings[Bg_cnt-1].bg_nb_format=
                   Page_settings.Nb_settings[Nb_cnt-1].nb_format;
               length_count=length_count+FOUR;
               Bg_parameter_occurrence[Bg_cnt-1] |= BIT_THREE;
               break;
            case BG_NB_FONT:
               /* hdudispfpdidata-ForegroundExtract-DB-LLR-019 */
               Page_settings.Nb_settings[Nb_cnt-1].nb_font=
                     *((T_UINT16 *)(address+offset+length_count));
               length_count=length_count+TWO;
               Bg_parameter_occurrence[Bg_cnt-1] |= BIT_FOUR;
               break;
            case BG_NO_LIM:
               /* hdudispfpdidata-ForegroundExtract-DB-LLR-020 */
               Page_settings.Bg_settings[Bg_cnt-1].bg_no_lim=
                     *((T_UINT8 *)(address+offset+length_count));
               Page_settings.Nb_settings[Nb_cnt-1].nb_no_lim=
                     Page_settings.Bg_settings[Bg_cnt-1].bg_no_lim;
               length_count=length_count+1;
               Bg_parameter_occurrence[Bg_cnt-1] |= BIT_FIVE;
               break;
            case BG_LIM_VAL:
               /* hdudispfpdidata-ForegroundExtract-DB-LLR-021 */
               for(var_j=0;var_j<Page_settings.Bg_settings[Bg_cnt-1].bg_no_lim;var_j++)
               {
                  Page_settings.Bg_settings[Bg_cnt-1].bg_lim_val_type[var_j]=
                           *((T_UINT8 *)(address+offset+length_count));
                  Page_settings.Nb_settings[Nb_cnt-1].nb_lim_val_type[var_j]=
                           Page_settings.Bg_settings[Bg_cnt-1].bg_lim_val_type[var_j];
                  length_count=length_count+1;
                  Page_settings.Bg_settings[Bg_cnt-1].bg_lim_val[var_j]=
                           IeeeToFloat(*((T_UINT32 *)(address+offset+length_count)));
                  Page_settings.Nb_settings[Nb_cnt-1].nb_lim_val[var_j]=
                           Page_settings.Bg_settings[Bg_cnt-1].bg_lim_val[var_j];
                  length_count=length_count+FOUR;
               }
               Bg_parameter_occurrence[Bg_cnt-1] |= BIT_SIX;
               break;
            case BG_LIM_COLOR:
               /* hdudispfpdidata-ForegroundExtract-DB-LLR-022 */
               for(var_j=0;var_j<Page_settings.Bg_settings[Bg_cnt-1].bg_no_lim;var_j++)
               {
                  Page_settings.Bg_settings[Bg_cnt-1].bg_lim_color[var_j]=
                        *((T_UINT16 *)(address+offset+length_count));
                  length_count=length_count+TWO;
               }
               Bg_parameter_occurrence[Bg_cnt-1] |= BIT_SEVEN;
               break;
            case BG_NB_LIM_COLOR:
               /* hdudispfpdidata-ForegroundExtract-DB-LLR-080 */
               for(var_j=0;var_j<Page_settings.Bg_settings[Bg_cnt-1].bg_no_lim;var_j++)
               {
                  Page_settings.Nb_settings[Nb_cnt-1].nb_lim_color[var_j]=
                         *((T_UINT16 *)(address+offset+length_count));
                  length_count=length_count+TWO;
               }
               Bg_parameter_occurrence[Bg_cnt-1] |= BIT_EIGHT;
               break;
            case BG_LIM_TYPE:
               /* hdudispfpdidata-ForegroundExtract-DB-LLR-164 */
               for(var_j=0;var_j<Page_settings.Bg_settings[Bg_cnt-1].bg_no_lim;var_j++)
               {
            	  Page_settings.Bg_settings[Bg_cnt-1].bg_lim_type[var_j]=
                         *((T_UINT16 *)(address+offset+length_count));
                  Page_settings.Nb_settings[Nb_cnt-1].nb_lim_type[var_j]=
                	     Page_settings.Bg_settings[Bg_cnt-1].bg_lim_type[var_j];
                  length_count=length_count+TWO;
               }
               break;
            case BG_REDX_AXIS:
               /* hdudispfpdidata-ForegroundExtract-DB-LLR-023 */
               Page_settings.Bg_settings[Bg_cnt-1].bg_redx_axis.u16_x=
                     *((T_UINT16 *)(address+offset+length_count));
               Page_settings.Nb_settings[Nb_cnt-1].nb_redx_axis.u16_x=
                     Page_settings.Nb_settings[Nb_cnt-1].nb_axis.u16_x;
               length_count=length_count+TWO;
               Page_settings.Bg_settings[Bg_cnt-1].bg_redx_axis.u16_y=
                     *((T_UINT16 *)(address+offset+length_count));
               Page_settings.Nb_settings[Nb_cnt-1].nb_redx_axis.u16_y=
                     Page_settings.Nb_settings[Nb_cnt-1].nb_axis.u16_y;
               length_count=length_count+TWO;
               Bg_parameter_occurrence[Bg_cnt-1] |= BIT_NINE;
               break;
            case BG_REDX_WIDTH:
               /* hdudispfpdidata-ForegroundExtract-DB-LLR-024 */
               Page_settings.Bg_settings[Bg_cnt-1].bg_redx_width=
                     *((T_UINT16 *)(address+offset+length_count));
               length_count=length_count+TWO;
               Bg_parameter_occurrence[Bg_cnt-1] |= BIT_TEN;
               break;
            case BG_REDX_HEIGHT:
               /* hdudispfpdidata-ForegroundExtract-DB-LLR-025 */
               Page_settings.Bg_settings[Bg_cnt-1].bg_redx_height=
                     *((T_UINT16 *)(address+offset+length_count));
               length_count=length_count+TWO;
               Bg_parameter_occurrence[Bg_cnt-1] |= BIT_ELEVEN;
               break;
            case BG_REDX_OFFSET_AXIS:
               /* hdudispfpdidata-ForegroundExtract-DB-LLR-026 */
               Page_settings.Bg_settings[Bg_cnt-1].bg_redx_offset_axis.u16_x=
                     *((T_UINT16 *)(address+offset+length_count));
               Page_settings.Nb_settings[Nb_cnt-1].nb_redx_offset_axis.u16_x=0;
               length_count=length_count+TWO;
               Page_settings.Bg_settings[Bg_cnt-1].bg_redx_offset_axis.u16_y=
                     *((T_UINT16 *)(address+offset+length_count));
               Page_settings.Nb_settings[Nb_cnt-1].nb_redx_offset_axis.u16_y=0;
               length_count=length_count+TWO;
               Bg_parameter_occurrence[Bg_cnt-1] |= BIT_TWELVE;
               break;
            case BG_REDX_FONT:
               /* hdudispfpdidata-ForegroundExtract-DB-LLR-027 */
               Page_settings.Bg_settings[Bg_cnt-1].bg_redx_font=
                     *((T_UINT16 *)(address+offset+length_count));
               Page_settings.Nb_settings[Nb_cnt-1].nb_redx_font=
                     Page_settings.Bg_settings[Bg_cnt-1].bg_redx_font;
               length_count=length_count+TWO;
               Bg_parameter_occurrence[Bg_cnt-1] |= BIT_THIRTEEN;
               break;
            case BG_REDX_TXT:
               /* hdudispfpdidata-ForegroundExtract-DB-LLR-028 */
               var_j=0;
               while((*((T_UINT8 *)(address+offset+length_count))!=0) && (var_j<THIRTY_ONE))
               {
                  Page_settings.Bg_settings[Bg_cnt-1].bg_redx_txt[var_j]=
                        *((T_UINT8 *)(address+offset+length_count));
                  if(('n' == Page_settings.Bg_settings[Bg_cnt-1].bg_redx_txt[var_j])
                      &&( '\\' == Page_settings.Bg_settings[Bg_cnt-1].bg_redx_txt[var_j-1] ))
                  {
                   Page_settings.Bg_settings[Bg_cnt-1].bg_redx_txt[var_j-1] ='\n';
                  }
                  else if(('r' == Page_settings.Bg_settings[Bg_cnt-1].bg_redx_txt[var_j])
                      &&('\\' == Page_settings.Bg_settings[Bg_cnt-1].bg_redx_txt[var_j-1]))
                  {
                   Page_settings.Bg_settings[Bg_cnt-1].bg_redx_txt[var_j-1] ='\r';
                  }
                  else
                  {
                      var_j++;
                  }
                  length_count++;
               }

               /* hdudispfpdidata-ForegroundExtract-DB-LLR-029 */
               Page_settings.Bg_settings[Bg_cnt-1].bg_redx_txt[var_j]=
                        *((T_UINT8 *)(address+offset+length_count));
               Page_settings.Nb_settings[Nb_cnt-1].nb_redx_txt[0]='X';
               Page_settings.Nb_settings[Nb_cnt-1].nb_redx_txt[1]='X';
               Page_settings.Nb_settings[Nb_cnt-1].nb_redx_txt[2]='X';
               Page_settings.Nb_settings[Nb_cnt-1].nb_redx_txt[3]='X';
               length_count++;
               Bg_parameter_occurrence[Bg_cnt-1] |= BIT_FOURTEEN;
               break;
            case RD_ASSOCIATED_LABELS:
               /* hdudispfpdidata-ForegroundExtract-DB-LLR-079 */
               for(var_j=0;var_j<ASSOCIALTED_LABEL;var_j++)
               {
                  Page_settings.Rd_settings[Rd_cnt-1].assc_labels[var_j]=
                        *((T_UINT16 *)(address+offset+length_count));
                  length_count=length_count+TWO;
               }
               break;
            case RD_AXIS:
               /* hdudispfpdidata-ForegroundExtract-DB-LLR-030 */
               Page_settings.Rd_settings[Rd_cnt-1].rd_axis.u16_x=
                     *((T_UINT16 *)(address+offset+length_count));
               length_count=length_count+TWO;
               Page_settings.Rd_settings[Rd_cnt-1].rd_axis.u16_y=
                     *((T_UINT16 *)(address+offset+length_count));
               length_count=length_count+TWO;
               break;
            case RD_NO_LIN:
               /* hdudispfpdidata-ForegroundExtract-DB-LLR-031 */
               Page_settings.Rd_settings[Rd_cnt-1].rd_no_lin=
                     *((T_UINT8 *)(address+offset+length_count));
               length_count=length_count+1;
               break;
            case RD_LIN_RANGE:
               /* hdudispfpdidata-ForegroundExtract-DB-LLR-032 */
               /* Updated for PR 100073  */
               rd_lin_rnge[Rd_cnt-1][0]=
                  Page_settings.Rd_settings[Rd_cnt-1].rd_no_lin;
               for(var_j=1;var_j<=Page_settings.Rd_settings[Rd_cnt-1].rd_no_lin;var_j++)
               {
                rd_lin_rnge[Rd_cnt-1][var_j]=
                        IeeeToFloat(*((T_UINT32 *)(address+offset+length_count)));
                  length_count=length_count+FOUR;
               }
               break;
            case RD_LIN_ANGLE:
               /* hdudispfpdidata-ForegroundExtract-DB-LLR-033 */
               Page_settings.Rd_settings[Rd_cnt-1].rd_lin_angle[0]=
                  Page_settings.Rd_settings[Rd_cnt-1].rd_no_lin;
               for(var_j=1;var_j<=Page_settings.Rd_settings[Rd_cnt-1].rd_no_lin;var_j++)
               {
                  Page_settings.Rd_settings[Rd_cnt-1].rd_lin_angle[var_j]=(T_INT32)
                  (IeeeToFloat(*((T_UINT32 *)(address+offset+length_count))));
                  length_count=length_count+FOUR;

                 if(MIN_LIN_ANGLE >Page_settings.Rd_settings[Rd_cnt-1].rd_lin_angle[var_j] ||
					MAX_LIN_ANGLE <Page_settings.Rd_settings[Rd_cnt-1].rd_lin_angle[var_j])
                 {
                	 Rd_lin_angle_status[Rd_cnt-1] = Rd_lin_angle_status[Rd_cnt-1] |(ONE<< (var_j-1));
                 }
                 else
                 {
                	 Page_settings.Rd_settings[Rd_cnt-1].rd_lin_angle[var_j]=
                	 CVT(Page_settings.Rd_settings[Rd_cnt-1].rd_lin_angle[var_j]);
                 }
               }
               break;
            case RD_NO_PTR:
               /* hdudispfpdidata-ForegroundExtract-DB-LLR-034 */
               Page_settings.Rd_settings[Rd_cnt-1].rd_no_ptr=
                     *((T_UINT8 *)(address+offset+length_count));
               length_count=length_count+ONE;
               break;
            case RD_PTR_COLOR:
               /* hdudispfpdidata-ForegroundExtract-DB-LLR-035 */
               for(var_j=0;var_j<Page_settings.Rd_settings[Rd_cnt-1].rd_no_ptr;var_j++)
               {
                  Page_settings.Rd_settings[Rd_cnt-1].rd_ptr_color[var_j]=
                        *((T_UINT16 *)(address+offset+length_count));
                  length_count=length_count+TWO;
               }
               break;
            case RD_PTR_SHAPE:
               /* hdudispfpdidata-ForegroundExtract-DB-LLR-036 */
               for(var_j=0;var_j<Page_settings.Rd_settings[Rd_cnt-1].rd_no_ptr;var_j++)
               {
                  Page_settings.Rd_settings[Rd_cnt-1].rd_ptr_shape[var_j]=
                     *((T_UINT16 *)(address+offset+length_count));
                  length_count=length_count+TWO;
               }
               break;
            case RD_PTR_SCALE:
               /* hdudispfpdidata-ForegroundExtract-DB-LLR-037 */
               for(var_j=0;var_j<Page_settings.Rd_settings[Rd_cnt-1].rd_no_ptr;var_j++)
               {
                  /* Updated for PR 100073 */
                  Page_settings.Rd_settings[Rd_cnt-1].rd_ptr_scale[var_j][0]=
                     *((T_INT16 *)(address+offset+length_count));
                  length_count=length_count+TWO;
                  Page_settings.Rd_settings[Rd_cnt-1].rd_ptr_scale[var_j][1]=
                     *((T_INT16 *)(address+offset+length_count));
                  length_count=length_count+TWO;
               }
               break;
            case RD_PTR_SCALE_OFFSET:
               /* hdudispfpdidata-ForegroundExtract-DB-LLR-038 */
               for(var_j=0;var_j<Page_settings.Rd_settings[Rd_cnt-1].rd_no_ptr;var_j++)
               {
                  /* Updated for PR 100073 */
                  Page_settings.Rd_settings[Rd_cnt-1].rd_ptr_scale_offset[var_j][0]=
                     *((T_INT16 *)(address+offset+length_count));
                  length_count=length_count+TWO;
                  Page_settings.Rd_settings[Rd_cnt-1].rd_ptr_scale_offset[var_j][1]=
                     *((T_INT16 *)(address+offset+length_count));
                  length_count=length_count+TWO;
               }
               break;
            case RD_PTR_ROT:
                 /* hdudispfpdidata-ForegroundExtract-DB-LLR-082*/
               for(var_j=0;var_j<Page_settings.Rd_settings[Rd_cnt-1].rd_no_ptr;var_j++)
               {
                  Page_settings.Rd_settings[Rd_cnt-1].rd_ptr_rot[var_j]=
                        *((T_INT16 *)(address+offset+length_count));
                  length_count=length_count+TWO;
               }
               break;
            case RD_LENGTH:
               /* hdudispfpdidata-ForegroundExtract-DB-LLR-039 */
               Page_settings.Rd_settings[Rd_cnt-1].rd_length=
                  *((T_UINT16 *)(address+offset+length_count));
               length_count=length_count+TWO;
               break;
            case RD_VERN:
                /* hdudispfpdidata-ForegroundExtract-DB-LLR-083 */
                Page_settings.Rd_settings[Rd_cnt-1].rd_vern=
                        *((T_UINT8 *)(address+offset+length_count));
                length_count=length_count+1;
                break;
            case RD_VERN_POS:
                /* hdudispfpdidata-ForegroundExtract-DB-LLR-084 */
                Page_settings.Rd_settings[Rd_cnt-1].rd_vern_pos=
                        IeeeToFloat(*((T_UINT32 *)(address+offset+length_count)));
                length_count=length_count+FOUR;
                break;
            case RD_NB_AXIS:
               /* hdudispfpdidata-ForegroundExtract-DB-LLR-040 */
               Nb_cnt++;
               Rd_tracker[Rd_cnt-1][Nb_cnt-1] = TRUE;
               Page_settings.Nb_settings[Nb_cnt-1].nb_axis.u16_x=
                  *((T_UINT16 *)(address+offset+length_count));
               length_count=length_count+TWO;
               Page_settings.Nb_settings[Nb_cnt-1].nb_axis.u16_y=
                  *((T_UINT16 *)(address+offset+length_count));
               length_count=length_count+TWO;
               Page_settings.Nb_settings[Nb_cnt-1].label=
                  Page_settings.Rd_settings[Rd_cnt-1].label;
               Page_settings.Nb_settings[Nb_cnt-1].sdi=
                  Page_settings.Rd_settings[Rd_cnt-1].sdi;
               Rd_parameter_occurrence[Rd_cnt-1] |= BIT_ONE;
               break;
            case RD_NB_FORMAT:
               /* hdudispfpdidata-ForegroundExtract-DB-LLR-041 */
               Page_settings.Nb_settings[Nb_cnt-1].nb_format=
                  *((T_UINT32 *)(address+offset+length_count));
               Page_settings.Rd_settings[Rd_cnt-1].rd_nb_format=
                   Page_settings.Nb_settings[Nb_cnt-1].nb_format;
               length_count=length_count+FOUR;
               Rd_parameter_occurrence[Rd_cnt-1] |= BIT_TWO;
               break;
            case RD_NB_FONT:
               /* hdudispfpdidata-ForegroundExtract-DB-LLR-042 */
               Page_settings.Nb_settings[Nb_cnt-1].nb_font=
                  *((T_UINT16 *)(address+offset+length_count));
               length_count=length_count+TWO;
               Rd_parameter_occurrence[Rd_cnt-1] |= BIT_THREE;
               break;
            case RD_NO_LIM:
               /* hdudispfpdidata-ForegroundExtract-DB-LLR-043 */
               Page_settings.Rd_settings[Rd_cnt-1].rd_no_lim=
                  *((T_UINT8 *)(address+offset+length_count));
               Page_settings.Nb_settings[Nb_cnt-1].nb_no_lim=
                  Page_settings.Rd_settings[Rd_cnt-1].rd_no_lim;
               length_count=length_count+1;
               Rd_parameter_occurrence[Rd_cnt-1] |= BIT_FOUR;
               break;
            case RD_LIM_VAL:
               /* hdudispfpdidata-ForegroundExtract-DB-LLR-044 */
               for(var_j=0;var_j<Page_settings.Rd_settings[Rd_cnt-1].rd_no_lim;var_j++)
               {
                  Page_settings.Rd_settings[Rd_cnt-1].rd_lim_val_type[var_j]=
                     *((T_UINT8 *)(address+offset+length_count));
                  Page_settings.Nb_settings[Nb_cnt-1].nb_lim_val_type[var_j]=
                     Page_settings.Rd_settings[Rd_cnt-1].rd_lim_val_type[var_j];
                  length_count=length_count+1;
                  Page_settings.Rd_settings[Rd_cnt-1].rd_lim_val[var_j]=
                     IeeeToFloat(*((T_UINT32 *)(address+offset+length_count)));
                  Page_settings.Nb_settings[Nb_cnt-1].nb_lim_val[var_j]=
                     Page_settings.Rd_settings[Rd_cnt-1].rd_lim_val[var_j];
                  length_count=length_count+FOUR;
               }
               Rd_parameter_occurrence[Rd_cnt-1] |= BIT_FIVE;
               break;
            case RD_LIM_COLOR:
               /* hdudispfpdidata-ForegroundExtract-DB-LLR-045 */
               for(var_j=0;var_j<Page_settings.Rd_settings[Rd_cnt-1].rd_no_lim;var_j++)
               {
                  Page_settings.Rd_settings[Rd_cnt-1].rd_lim_color[var_j]=
                     *((T_UINT16 *)(address+offset+length_count));
                  Page_settings.Nb_settings[Nb_cnt-1].nb_lim_color[var_j]=
                     Page_settings.Rd_settings[Rd_cnt-1].rd_lim_color[var_j];
                  length_count=length_count+TWO;
               }
               Rd_parameter_occurrence[Rd_cnt-1] |= BIT_SIX;
               break;
            case RD_LIM_TYPE:
               /* hdudispfpdidata-ForegroundExtract-DB-LLR-082 */
               for(var_j=0;var_j<Page_settings.Rd_settings[Rd_cnt-1].rd_no_lim;var_j++)
               {
                  Page_settings.Rd_settings[Rd_cnt-1].rd_lim_type[var_j]=
                     *((T_UINT16 *)(address+offset+length_count));
                  Page_settings.Nb_settings[Nb_cnt-1].nb_lim_type[var_j]=
                     Page_settings.Rd_settings[Rd_cnt-1].rd_lim_type[var_j];
                  length_count=length_count+TWO;
               }
               break;
            case RD_REDX_AXIS:
               /* hdudispfpdidata-ForegroundExtract-DB-LLR-046 */
               Page_settings.Rd_settings[Rd_cnt-1].rd_redx_axis.u16_x=
                  *((T_UINT16 *)(address+offset+length_count));
               Page_settings.Nb_settings[Nb_cnt-1].nb_redx_axis.u16_x=
                  Page_settings.Nb_settings[Nb_cnt-1].nb_axis.u16_x;
               length_count=length_count+TWO;
               Page_settings.Rd_settings[Rd_cnt-1].rd_redx_axis.u16_y=
                  *((T_UINT16 *)(address+offset+length_count));
               Page_settings.Nb_settings[Nb_cnt-1].nb_redx_axis.u16_y=
                  Page_settings.Nb_settings[Nb_cnt-1].nb_axis.u16_y;
               length_count=length_count+TWO;
               Rd_parameter_occurrence[Rd_cnt-1] |= BIT_SEVEN;
               break;
            case RD_REDX_WIDTH:
               /* hdudispfpdidata-ForegroundExtract-DB-LLR-047 */
               Page_settings.Rd_settings[Rd_cnt-1].rd_redx_width=
                  *((T_UINT16 *)(address+offset+length_count));
               length_count=length_count+TWO;
               Rd_parameter_occurrence[Rd_cnt-1] |= BIT_EIGHT;
               break;
            case RD_REDX_HEIGHT:
               /* hdudispfpdidata-ForegroundExtract-DB-LLR-048 */
               Page_settings.Rd_settings[Rd_cnt-1].rd_redx_height=
                  *((T_UINT16 *)(address+offset+length_count));
               length_count=length_count+TWO;
               Rd_parameter_occurrence[Rd_cnt-1] |= BIT_NINE;
               break;
            case RD_REDX_OFFSET_AXIS:
               /* hdudispfpdidata-ForegroundExtract-DB-LLR-049 */
               Page_settings.Rd_settings[Rd_cnt-1].rd_redx_offset_axis.u16_x=
                  *((T_UINT16 *)(address+offset+length_count));
               Page_settings.Nb_settings[Nb_cnt-1].nb_redx_offset_axis.u16_x=0;
               length_count=length_count+TWO;
               Page_settings.Rd_settings[Rd_cnt-1].rd_redx_offset_axis.u16_y=
                  *((T_UINT16 *)(address+offset+length_count));
               Page_settings.Nb_settings[Nb_cnt-1].nb_redx_offset_axis.u16_y=0;
               length_count=length_count+TWO;
               Rd_parameter_occurrence[Rd_cnt-1] |= BIT_TEN;
               break;
            case RD_REDX_FONT:
               /* hdudispfpdidata-ForegroundExtract-DB-LLR-050 */
               Page_settings.Rd_settings[Rd_cnt-1].rd_redx_font=
                  *((T_UINT16 *)(address+offset+length_count));
               Page_settings.Nb_settings[Nb_cnt-1].nb_redx_font=
                  Page_settings.Rd_settings[Rd_cnt-1].rd_redx_font;
               length_count=length_count+TWO;
               Rd_parameter_occurrence[Rd_cnt-1] |= BIT_ELEVEN;
               break;
            case RD_REDX_TXT:
               /* hdudispfpdidata-ForegroundExtract-DB-LLR-051 */
                var_j=0;
                while((*((T_UINT8 *)(address+offset+length_count))!=0) && (var_j<THIRTY_ONE))
                {

                    Page_settings.Rd_settings[Rd_cnt-1].rd_redx_txt[var_j]=
                          *((T_UINT8 *)(address+offset+length_count));
                    if(('n' == Page_settings.Rd_settings[Rd_cnt-1].rd_redx_txt[var_j])
                        &&( '\\' == Page_settings.Rd_settings[Rd_cnt-1].rd_redx_txt[var_j-1] ))
                    {
                       Page_settings.Rd_settings[Rd_cnt-1].rd_redx_txt[var_j-1] ='\n';
                    }
                    else if(('r' == Page_settings.Rd_settings[Rd_cnt-1].rd_redx_txt[var_j])
                         &&('\\' == Page_settings.Rd_settings[Rd_cnt-1].rd_redx_txt[var_j-1]))
                    {
                       Page_settings.Rd_settings[Rd_cnt-1].rd_redx_txt[var_j-1] ='\r';
                    }
                    else
                    {
                        var_j++;
                    }
                    length_count++;
                }
                /* hdudispfpdidata-ForegroundExtract-DB-LLR-052 */
                Page_settings.Rd_settings[Rd_cnt-1].rd_redx_txt[var_j]=
                   *((T_UINT8 *)(address+offset+length_count));
               Page_settings.Nb_settings[Nb_cnt-1].nb_redx_txt[0]='X';
               Page_settings.Nb_settings[Nb_cnt-1].nb_redx_txt[1]='X';
               Page_settings.Nb_settings[Nb_cnt-1].nb_redx_txt[2]='X';
               Page_settings.Nb_settings[Nb_cnt-1].nb_redx_txt[3]='X';
               length_count++;
               Rd_parameter_occurrence[Rd_cnt-1] |= BIT_TWELVE;
               break;
            case NB_AXIS:
               /* hdudispfpdidata-ForegroundExtract-DB-LLR-053 */
                Nb_tracker[Nb_cnt-1][Nb_cnt-1] = TRUE;
               Page_settings.Nb_settings[Nb_cnt-1].nb_axis.u16_x=
                  *((T_UINT16 *)(address+offset+length_count));
               length_count=length_count+TWO;
               Page_settings.Nb_settings[Nb_cnt-1].nb_axis.u16_y=
                  *((T_UINT16 *)(address+offset+length_count));
               length_count=length_count+TWO;
               break;
            case NB_FORMAT:
               /* hdudispfpdidata-ForegroundExtract-DB-LLR-054 */
               Page_settings.Nb_settings[Nb_cnt-1].nb_format=
                  *((T_UINT32 *)(address+offset+length_count));
               length_count=length_count+FOUR;
               Nb_parameter_occurrence[Nb_cnt-1] |= BIT_ONE;
               break;
            case NB_FONT:
               /* hdudispfpdidata-ForegroundExtract-DB-LLR-055 */
               Page_settings.Nb_settings[Nb_cnt-1].nb_font=
                  *((T_UINT16 *)(address+offset+length_count));
               length_count=length_count+TWO;
               Nb_parameter_occurrence[Nb_cnt-1] |= BIT_TWO;
               break;
            case NB_NO_LIM:
               /* hdudispfpdidata-ForegroundExtract-DB-LLR-056 */
               Page_settings.Nb_settings[Nb_cnt-1].nb_no_lim=
                  *((T_UINT8 *)(address+offset+length_count));
               length_count=length_count+1;
               Nb_parameter_occurrence[Nb_cnt-1] |= BIT_THREE;
               break;
            case NB_LIM_VAL:
               /* hdudispfpdidata-ForegroundExtract-DB-LLR-057 */
               for(var_j=0;var_j<Page_settings.Nb_settings[Nb_cnt-1].nb_no_lim;var_j++)
               {
                  Page_settings.Nb_settings[Nb_cnt-1].nb_lim_val_type[var_j]=
                     *((T_UINT8 *)(address+offset+length_count));
                  length_count=length_count+1;
                  Page_settings.Nb_settings[Nb_cnt-1].nb_lim_val[var_j]=
                  IeeeToFloat(*((T_UINT32 *)(address+offset+length_count)));
                  length_count=length_count+FOUR;
               }
               Nb_parameter_occurrence[Nb_cnt-1] |= BIT_FOUR;
               break;
            case NB_LIM_COLOR:
               /* hdudispfpdidata-ForegroundExtract-DB-LLR-058 */
               for(var_j=0;var_j<Page_settings.Nb_settings[Nb_cnt-1].nb_no_lim;var_j++)
               {
                  Page_settings.Nb_settings[Nb_cnt-1].nb_lim_color[var_j]=
                     *((T_UINT16 *)(address+offset+length_count));
                  length_count=length_count+TWO;
               }
               Nb_parameter_occurrence[Nb_cnt-1] |= BIT_FIVE;
               break;
            case NB_LIM_TYPE:
               /* hdudispfpdidata-ForegroundExtract-DB-LLR-155 */
               for(var_j=0;var_j<Page_settings.Nb_settings[Nb_cnt-1].nb_no_lim;var_j++)
               {
                  Page_settings.Nb_settings[Nb_cnt-1].nb_lim_type[var_j]=
                     *((T_UINT16 *)(address+offset+length_count));
                  length_count=length_count+TWO;
               }
               break;
            case NB_REDX_AXIS:
               /* hdudispfpdidata-ForegroundExtract-DB-LLR-059 */
               Page_settings.Nb_settings[Nb_cnt-1].nb_redx_axis.u16_x=
                  *((T_UINT16 *)(address+offset+length_count));
               length_count=length_count+TWO;
               Page_settings.Nb_settings[Nb_cnt-1].nb_redx_axis.u16_y=
                  *((T_UINT16 *)(address+offset+length_count));
               length_count=length_count+TWO;
               Nb_parameter_occurrence[Nb_cnt-1] |= BIT_SIX;
               break;
            case NB_REDX_WIDTH:
               /* hdudispfpdidata-ForegroundExtract-DB-LLR-060 */
               Page_settings.Nb_settings[Nb_cnt-1].nb_redx_width=
                  *((T_UINT16 *)(address+offset+length_count));
                length_count=length_count+TWO;
                Nb_parameter_occurrence[Nb_cnt-1] |= BIT_SEVEN;
               break;
            case NB_REDX_HEIGHT:
               /* hdudispfpdidata-ForegroundExtract-DB-LLR-061 */
               Page_settings.Nb_settings[Nb_cnt-1].nb_redx_height=
                  *((T_UINT16 *)(address+offset+length_count));
                length_count=length_count+TWO;
                Nb_parameter_occurrence[Nb_cnt-1] |= BIT_EIGHT;
               break;
            case NB_REDX_OFFSET_AXIS:
               /* hdudispfpdidata-ForegroundExtract-DB-LLR-062 */
               Page_settings.Nb_settings[Nb_cnt-1].nb_redx_offset_axis.u16_x=
                  *((T_UINT16 *)(address+offset+length_count));
               length_count=length_count+TWO;
               Page_settings.Nb_settings[Nb_cnt-1].nb_redx_offset_axis.u16_y=
                  *((T_UINT16 *)(address+offset+length_count));
               length_count=length_count+TWO;
               Nb_parameter_occurrence[Nb_cnt-1] |= BIT_NINE;
               break;
            case NB_REDX_FONT:
               /* hdudispfpdidata-ForegroundExtract-DB-LLR-063 */
               Page_settings.Nb_settings[Nb_cnt-1].nb_redx_font=
                  *((T_UINT16 *)(address+offset+length_count));
               length_count=length_count+TWO;
               Nb_parameter_occurrence[Nb_cnt-1] |= BIT_TEN;
               break;
            case NB_REDX_TXT:
               /* hdudispfpdidata-ForegroundExtract-DB-LLR-064 */
               var_j=0;
               while((*((T_UINT8 *)(address+offset+length_count))!=0) && (var_j<THIRTY_ONE))
               {
                  Page_settings.Nb_settings[Nb_cnt-1].nb_redx_txt[var_j]=
                     *((T_UINT8 *)(address+offset+length_count));
                  var_j++;
                  length_count++;
               }
               Page_settings.Nb_settings[Nb_cnt-1].nb_redx_txt[var_j]=
                  *((T_UINT8 *)(address+offset+length_count));
               length_count++;
               Nb_parameter_occurrence[Nb_cnt-1] |= BIT_ELEVEN;
               break;
           case TB_STRING:
                /* hdudispfpdidata-ForegroundExtract-DB-LLR-115 */
               var_j=0;
              while((*((T_UINT8 *)(address+offset+length_count))!=0) && (var_j<THIRTY_ONE))
              {
                 Page_settings.Tb_settings[Tb_cnt-1].tb_string[var_j]=
                         *((T_UINT8 *)(address+offset+length_count));
                  if(('n' == Page_settings.Tb_settings[Tb_cnt-1].tb_string[var_j])
                      &&( '\\' == Page_settings.Tb_settings[Tb_cnt-1].tb_string[var_j-1] ))
                  {
                     Page_settings.Tb_settings[Tb_cnt-1].tb_string[var_j-1] ='\n';
                  }
                  else if(('r' == Page_settings.Tb_settings[Tb_cnt-1].tb_string[var_j])
                       &&('\\' == Page_settings.Tb_settings[Tb_cnt-1].tb_string[var_j-1]))
                  {
                     Page_settings.Tb_settings[Tb_cnt-1].tb_string[var_j-1] ='\r';
                  }
                  else
                  {
                      var_j++;
                  }
                 length_count++;
              }
              Page_settings.Tb_settings[Tb_cnt-1].tb_string[var_j]=
                      *((T_UINT8 *)(address+offset+length_count));
              length_count++;
              /*Variable to determine the occurrence of the parameter*/
              break;
            case TB_AXIS:
               /* hdudispfpdidata-ForegroundExtract-DB-LLR-116 */
               Page_settings.Tb_settings[Tb_cnt-1].tb_axis.u16_x=
                       *((T_UINT16 *)(address+offset+length_count));
               length_count=length_count+TWO;
               Page_settings.Tb_settings[Tb_cnt-1].tb_axis.u16_y=
                       *((T_UINT16 *)(address+offset+length_count));
               length_count=length_count+TWO;
               break;
            case TB_WIDTH:
               /* hdudispfpdidata-ForegroundExtract-DB-LLR-117 */
               Page_settings.Tb_settings[Tb_cnt-1].tb_width=
                       *((T_UINT16 *)(address+offset+length_count));
               length_count=length_count+TWO;
               break;
            case TB_HEIGHT:
               /* hdudispfpdidata-ForegroundExtract-DB-LLR-118 */
               Page_settings.Tb_settings[Tb_cnt-1].tb_height=
                       *((T_UINT16 *)(address+offset+length_count));
               length_count=length_count+TWO;
               break;
            case TB_MARGIN:
               /* hdudispfpdidata-ForegroundExtract-DB-LLR-119 */
               Page_settings.Tb_settings[Tb_cnt-1].tb_margin=
                       *((T_UINT16 *)(address+offset+length_count));
               length_count=length_count+TWO;
               break;
            case TB_FRAME_WIDTH:
            /* hdudispfpdidata-ForegroundExtract-DB-LLR-120 */
               Page_settings.Tb_settings[Tb_cnt-1].tb_frame_width=
                       *((T_UINT16 *)(address+offset+length_count));
               length_count=length_count+TWO;
               break;
            case TB_FRAME_COLOR:
            /* hdudispfpdidata-ForegroundExtract-DB-LLR-121 */
               Page_settings.Tb_settings[Tb_cnt-1].tb_frame_color=
                       *((T_UINT16 *)(address+offset+length_count));
               length_count=length_count+TWO;
               break;
            case TB_BG_COLOR:
            /* hdudispfpdidata-ForegroundExtract-DB-LLR-122 */
               Page_settings.Tb_settings[Tb_cnt-1].tb_bg_color=
                       *((T_UINT16 *)(address+offset+length_count));
               length_count=length_count+TWO;
               break;
            case TB_BIT:
               /* hdudispfpdidata-ForegroundExtract-DB-LLR-145 */
               Page_settings.Tb_settings[Tb_cnt-1].tb_bit=
                       *((T_UINT16 *)(address+offset+length_count));
               length_count=length_count+TWO;
               Tb_parameter_occurrence[Tb_cnt-1] |= BIT_ONE;
               break;
             case TB_CROSS_VAL:
			 /* hdudispfpdidata-ForegroundExtract-DB-LLR-146 */
                 Page_settings.Tb_settings[Tb_cnt-1].tb_cross_val_type=
                    *((T_UINT8 *)(address+offset+length_count));
                 length_count=length_count+1;
                 Page_settings.Tb_settings[Tb_cnt-1].tb_cross_val=
                 IeeeToFloat(*((T_UINT32 *)(address+offset+length_count)));
                 length_count=length_count+FOUR;
                 Tb_parameter_occurrence[Tb_cnt-1] |= BIT_TWO;
               break;
            case TB_ALIGN:
            /* hdudispfpdidata-ForegroundExtract-DB-LLR-123 */
               Page_settings.Tb_settings[Tb_cnt-1].tb_align=
                       *((T_UINT16 *)(address+offset+length_count));
               length_count=length_count+TWO;
               Tb_parameter_occurrence[Tb_cnt-1] |= BIT_THREE;
               break;
            case TB_FONT:
            /* hdudispfpdidata-ForegroundExtract-DB-LLR-124 */
               Page_settings.Tb_settings[Tb_cnt-1].tb_font=
                      *((T_UINT16 *)(address+offset+length_count));
               length_count=length_count+TWO;
               Tb_parameter_occurrence[Tb_cnt-1] |= BIT_FOUR;
               break;
            case TB_COLOR:
            /* hdudispfpdidata-ForegroundExtract-DB-LLR-125 */
               Page_settings.Tb_settings[Tb_cnt-1].tb_color=
                       *((T_UINT16 *)(address+offset+length_count));
               length_count=length_count+TWO;
               Tb_parameter_occurrence[Tb_cnt-1] |= BIT_FIVE;
               break;
            case TB_STATE:
            /* hdudispfpdidata-ForegroundExtract-DB-LLR-153 */
               Page_settings.Tb_settings[Tb_cnt-1].tb_state=
                      (*((T_UINT16 *)(address+offset+length_count)));
               length_count=length_count+TWO;
               Tb_parameter_occurrence[Tb_cnt-1] |= BIT_SIX;
               break;
            case TB_FLASH:
            /* hdudispfpdidata-ForegroundExtract-DB-LLR-154 */
               Page_settings.Tb_settings[Tb_cnt-1].tb_flash=
                    *((T_UINT16 *)(address+offset+length_count));
               length_count=length_count+TWO;
               Tb_parameter_occurrence[Tb_cnt-1] |= BIT_SEVEN;
               break;
            case TB_FLASH_COLOR:
			   /* hdudispfpdidata-ForegroundExtract-DB-LLR-156 */
               Page_settings.Tb_settings[Tb_cnt-1].tb_flash_color=
                       *((T_UINT16 *)(address+offset+length_count));
               length_count=length_count+TWO;
               Tb_parameter_occurrence[Tb_cnt-1] |= BIT_FOURTEEN;
               break;
            case TB_REDX_AXIS:
            /* hdudispfpdidata-ForegroundExtract-DB-LLR-126 */
               Page_settings.Tb_settings[Tb_cnt-1].tb_redx_axis.u16_x=
                       *((T_UINT16 *)(address+offset+length_count));
               length_count=length_count+TWO;
               Page_settings.Tb_settings[Tb_cnt-1].tb_redx_axis.u16_y=
                       *((T_UINT16 *)(address+offset+length_count));
               length_count=length_count+TWO;
               Tb_parameter_occurrence[Tb_cnt-1] |= BIT_EIGHT;
               break;
            case TB_REDX_WIDTH:
            /* hdudispfpdidata-ForegroundExtract-DB-LLR-127 */
               Page_settings.Tb_settings[Tb_cnt-1].tb_redx_width=

                     *((T_UINT16 *)(address+offset+length_count));
               length_count=length_count+TWO;
               Tb_parameter_occurrence[Tb_cnt-1] |= BIT_NINE;
               break;
            case TB_REDX_HEIGHT:
            /* hdudispfpdidata-ForegroundExtract-DB-LLR-128 */
               Page_settings.Tb_settings[Tb_cnt-1].tb_redx_height=
                    *((T_UINT16 *)(address+offset+length_count));
               length_count=length_count+TWO;
               Tb_parameter_occurrence[Tb_cnt-1] |= BIT_TEN;
               break;
            case TB_REDX_OFFSET_AXIS:
            /* hdudispfpdidata-ForegroundExtract-DB-LLR-129 */
               Page_settings.Tb_settings[Tb_cnt-1].tb_redx_offset_axis.u16_x=
                       *((T_UINT16 *)(address+offset+length_count));
               length_count=length_count+TWO;
               Page_settings.Tb_settings[Tb_cnt-1].tb_redx_offset_axis.u16_y=
                       *((T_UINT16 *)(address+offset+length_count));
               length_count=length_count+TWO;
               Tb_parameter_occurrence[Tb_cnt-1] |= BIT_ELEVEN;
               break;
            case TB_REDX_FONT:
            /* hdudispfpdidata-ForegroundExtract-DB-LLR-130 */
               Page_settings.Tb_settings[Tb_cnt-1].tb_redx_font=
                       *((T_UINT16 *)(address+offset+length_count));
               length_count=length_count+TWO;
               Tb_parameter_occurrence[Tb_cnt-1] |= BIT_TWELVE;
               break;
            case TB_REDX_TXT:
            /* hdudispfpdidata-ForegroundExtract-DB-LLR-131 */
                var_j=0;
                while((*((T_UINT8 *)(address+offset+length_count))!=0) && (var_j<THIRTY_ONE))
                {
                   Page_settings.Tb_settings[Tb_cnt-1].tb_redx_txt[var_j]=
                           *((T_UINT8 *)(address+offset+length_count));
                    if(('n' == Page_settings.Tb_settings[Tb_cnt-1].tb_redx_txt[var_j])
                        &&( '\\' == Page_settings.Tb_settings[Tb_cnt-1].tb_redx_txt[var_j-1] ))
                    {
                       Page_settings.Tb_settings[Tb_cnt-1].tb_redx_txt[var_j-1] ='\n';
                    }
                    else if(('r' == Page_settings.Tb_settings[Tb_cnt-1].tb_redx_txt[var_j])
                         &&('\\' == Page_settings.Tb_settings[Tb_cnt-1].tb_redx_txt[var_j-1]))
                    {
                       Page_settings.Tb_settings[Tb_cnt-1].tb_redx_txt[var_j-1] ='\r';
                    }
                    else
                    {
                        var_j++;
                    }
                   length_count++;
                }
                Page_settings.Tb_settings[Tb_cnt-1].tb_redx_txt[var_j]=
                        *((T_UINT8 *)(address+offset+length_count));
                length_count++;
                Tb_parameter_occurrence[Tb_cnt-1] |= BIT_THIRTEEN;
               break;
            case TXT_STRING:
            /* hdudispfpdidata-ForegroundExtract-DB-LLR-132 */
                var_j=0;
                while((*((T_UINT8 *)(address+offset+length_count))!=0) && (var_j<THIRTY_ONE))
                {
                   Page_settings.Text_settings[Text_cnt-1].txt_string[var_j]=
                        *((T_UINT8 *)(address+offset+length_count));
                if(('n' == Page_settings.Text_settings[Text_cnt-1].txt_string[var_j])
                    &&( '\\' == Page_settings.Text_settings[Text_cnt-1].txt_string[var_j-1] ))
                {
                   Page_settings.Text_settings[Text_cnt-1].txt_string[var_j-1] ='\n';
                }
                else if(('r' == Page_settings.Text_settings[Text_cnt-1].txt_string[var_j])
                     &&('\\' == Page_settings.Text_settings[Text_cnt-1].txt_string[var_j-1]))
                {
                   Page_settings.Text_settings[Text_cnt-1].txt_string[var_j-1] ='\r';
                }
                else
                {
                    var_j++;
                }
                length_count++;
                }
                Page_settings.Text_settings[Text_cnt-1].txt_string[var_j]=
                     *((T_UINT8 *)(address+offset+length_count));
                length_count++;
                   break;
                case TXT_AXIS:
                /* hdudispfpdidata-ForegroundExtract-DB-LLR-133 */
                   Page_settings.Text_settings[Text_cnt-1].txt_axis.u16_x=
                        *((T_UINT16 *)(address+offset+length_count));
                   length_count=length_count+TWO;
                   Page_settings.Text_settings[Text_cnt-1].txt_axis.u16_y=
                        *((T_UINT16 *)(address+offset+length_count));
                   length_count=length_count+TWO;
                   break;
                case TXT_BIT:
				   /* hdudispfpdidata-ForegroundExtract-DB-LLR-143 */
                   Page_settings.Text_settings[Text_cnt-1].txt_bit=
                           *((T_UINT16 *)(address+offset+length_count));
                   length_count=length_count+TWO;
                   Text_parameter_occurrence[Text_cnt-1] |= BIT_ONE;
                   break;
                case TXT_CROSS_VAL:
				   /* hdudispfpdidata-ForegroundExtract-DB-LLR-144 */
                    Page_settings.Text_settings[Text_cnt-1].txt_cross_val_type=
                       *((T_UINT8 *)(address+offset+length_count));
                    length_count=length_count+1;
                   Page_settings.Text_settings[Text_cnt-1].txt_cross_val=
                   (IeeeToFloat(*((T_UINT32 *)(address+offset+length_count))));
                   length_count=length_count+FOUR;
                   Text_parameter_occurrence[Text_cnt-1] |= BIT_TWO;
                   break;
                case TXT_ALIGN:
                /* hdudispfpdidata-ForegroundExtract-DB-LLR-134 */
                   Page_settings.Text_settings[Text_cnt-1].txt_align=
                        /*TextAlign(*((T_UINT16 *)(address+offset+length_count)));*/
                           *((T_UINT16 *)(address+offset+length_count));
                   length_count=length_count+TWO;
                   Text_parameter_occurrence[Text_cnt-1] |= BIT_THREE;
                   break;
                case TXT_FONT:
                /* hdudispfpdidata-ForegroundExtract-DB-LLR-135 */
                   Page_settings.Text_settings[Text_cnt-1].txt_font=
                        *((T_UINT16 *)(address+offset+length_count));
                   length_count=length_count+TWO;
                   Text_parameter_occurrence[Text_cnt-1] |= BIT_FOUR;

                   break;
                case TXT_COLOR:
                /* hdudispfpdidata-ForegroundExtract-DB-LLR-136 */
                   Page_settings.Text_settings[Text_cnt-1].txt_color=
                        *((T_UINT16 *)(address+offset+length_count));
                   length_count=length_count+TWO;
                   Text_parameter_occurrence[Text_cnt-1] |= BIT_FIVE;
                   break;
                case TXT_STATE:
                /* hdudispfpdidata-ForegroundExtract-DB-LLR-137 */
                   Page_settings.Text_settings[Text_cnt-1].txt_state=
                          (*((T_UINT16 *)(address+offset+length_count)));
                   length_count=length_count+TWO;
                   Text_parameter_occurrence[Text_cnt-1] |= BIT_SIX;
                   break;
                case TXT_FLASH:
                /* hdudispfpdidata-ForegroundExtract-DB-LLR-138 */
                   Page_settings.Text_settings[Text_cnt-1].txt_flash=
                        *((T_UINT16 *)(address+offset+length_count));
                   length_count=length_count+TWO;
                   Text_parameter_occurrence[Text_cnt-1] |= BIT_SEVEN;
                   break;
                case TXT_REDX_AXIS:
				   /* hdudispfpdidata-ForegroundExtract-DB-LLR-147*/
                   Page_settings.Text_settings[Text_cnt-1].txt_redx_axis.u16_x=\
				   *((T_UINT16 *)(address+offset+length_count));
                   length_count=length_count+TWO;
                   Page_settings.Text_settings[Text_cnt-1].txt_redx_axis.u16_y=\
				   *((T_UINT16 *)(address+offset+length_count));
                   length_count=length_count+TWO;
                   Text_parameter_occurrence[Text_cnt-1] |= BIT_EIGHT;
                   break;
                case TXT_REDX_WIDTH:
				    /* hdudispfpdidata-ForegroundExtract-DB-LLR-148*/
                   Page_settings.Text_settings[Text_cnt-1].txt_redx_width=\
				   *((T_UINT16 *)(address+offset+length_count));
                   length_count=length_count+TWO;
                   Text_parameter_occurrence[Text_cnt-1] |= BIT_NINE;
                   break;
                case TXT_REDX_HEIGHT:
				    /* hdudispfpdidata-ForegroundExtract-DB-LLR-149*/
                   Page_settings.Text_settings[Text_cnt-1].txt_redx_height=\
				   *((T_UINT16 *)(address+offset+length_count));
                   length_count=length_count+TWO;
                   Text_parameter_occurrence[Text_cnt-1] |= BIT_TEN;
                   break;
                case TXT_REDX_OFFSET_AXIS:
				   /* hdudispfpdidata-ForegroundExtract-DB-LLR-150*/
                   Page_settings.Text_settings[Text_cnt-1].txt_redx_offset_axis.u16_x=\
				   *((T_UINT16 *)(address+offset+length_count));
                   length_count=length_count+TWO;
                   Page_settings.Text_settings[Text_cnt-1].txt_redx_offset_axis.u16_y=\
				   *((T_UINT16 *)(address+offset+length_count));
                   length_count=length_count+TWO;
                   Text_parameter_occurrence[Text_cnt-1] |= BIT_ELEVEN;
                   break;
                case TXT_REDX_FONT:
				   /* hdudispfpdidata-ForegroundExtract-DB-LLR-151*/
                   Page_settings.Text_settings[Text_cnt-1].txt_redx_font=\
				   *((T_UINT16 *)(address+offset+length_count));
                   length_count=length_count+TWO;
                   Text_parameter_occurrence[Text_cnt-1] |= BIT_TWELVE;
                   break;
                case TXT_REDX_TXT:
				   /* hdudispfpdidata-ForegroundExtract-DB-LLR-152*/
                    var_j=0;
                    while((*((T_UINT8 *)(address+offset+length_count))!=0) && (var_j<THIRTY_ONE))
                    {
                       Page_settings.Text_settings[Text_cnt-1].txt_redx_txt[var_j]=\
 					  *((T_UINT8 *)(address+offset+length_count));
                    if(('n' == Page_settings.Text_settings[Text_cnt-1].txt_redx_txt[var_j])
                        &&( '\\' == Page_settings.Text_settings[Text_cnt-1].txt_redx_txt[var_j-1] ))
                    {
                       Page_settings.Text_settings[Text_cnt-1].txt_redx_txt[var_j-1] ='\n';
                    }
                    else if(('r' == Page_settings.Text_settings[Text_cnt-1].txt_redx_txt[var_j])
                         &&('\\' == Page_settings.Text_settings[Text_cnt-1].txt_redx_txt[var_j-1]))
                    {
                       Page_settings.Text_settings[Text_cnt-1].txt_redx_txt[var_j-1] ='\r';
                    }
                    else
                    {
                        var_j++;
                    }
                       length_count++;
                    }
                    Page_settings.Text_settings[Text_cnt-1].txt_redx_txt[var_j]=\
 				   *((T_UINT8 *)(address+offset+length_count));
                    length_count++;
                    Text_parameter_occurrence[Text_cnt-1] |= BIT_THIRTEEN;
                    break;
            case CG_AXIS:
               /* hdudispfpdidata-ForegroundExtract-DB-LLR-085 */
               Page_settings.Cg_settings[Cg_cnt-1].cg_axis.u16_x=
                     *((T_UINT16 *)(address+offset+length_count));
               length_count=length_count+TWO;
               Page_settings.Cg_settings[Cg_cnt-1].cg_axis.u16_y=
                     *((T_UINT16 *)(address+offset+length_count));
               length_count=length_count+TWO;
               break;
            case CG_NO_LIN:
               /* hdudispfpdidata-ForegroundExtract-DB-LLR-086 */
               Page_settings.Cg_settings[Cg_cnt-1].cg_no_lin=
                     *((T_UINT8 *)(address+offset+length_count));
               length_count=length_count+1;
               break;
            case CG_LIN_RANGE:
               /* hdudispfpdidata-ForegroundExtract-DB-LLR-087 */
               /* Updated for PR 100073  */
                Page_settings.Cg_settings[Cg_cnt-1].cg_lin_range[0]=
                                   Page_settings.Cg_settings[Cg_cnt-1].cg_no_lin;
               for(var_j=1;var_j<=Page_settings.Cg_settings[Cg_cnt-1].cg_no_lin;var_j++)
               {
                  /* Updated as per PR 100073 */
                  Page_settings.Cg_settings[Cg_cnt-1].cg_lin_range[var_j]=(T_INT32)
                  (IeeeToFloat(*((T_UINT32 *)(address+offset+length_count))));
                  length_count=length_count+FOUR;
               }
               break;
            case CG_LIN_OFFSET:
                /*hdudispfpdidata-ForegroundExtract-DB-LLR-088*/
                Page_settings.Cg_settings[Cg_cnt-1].cg_lin_offset[0]=
                                     Page_settings.Cg_settings[Cg_cnt-1].cg_no_lin;
               for(var_j=1;var_j<=Page_settings.Cg_settings[Cg_cnt-1].cg_no_lin;var_j++)
               {
                  Page_settings.Cg_settings[Cg_cnt-1].cg_lin_offset[var_j]=
                        (T_INT32)MAG_BG(*((T_INT16 *)(address+offset+length_count)));
                  length_count=length_count+TWO;
               }
               break;
            case CG_NO_PTR:
               /* hdudispfpdidata-ForegroundExtract-DB-LLR-089 */
               Page_settings.Cg_settings[Cg_cnt-1].cg_no_ptr=
                     *((T_UINT8 *)(address+offset+length_count));
               length_count=length_count+1;
               break;
            case CG_PTR_COLOR:
               /* hdudispfpdidata-ForegroundExtract-DB-LLR-090 */
               for(var_j=0;var_j<Page_settings.Cg_settings[Cg_cnt-1].cg_no_ptr;var_j++)
               {
                  Page_settings.Cg_settings[Cg_cnt-1].cg_ptr_color[var_j]=
                        *((T_UINT16 *)(address+offset+length_count));
                  length_count=length_count+TWO;
               }
               break;
            case CG_PTR_SHAPE:
               /* hdudispfpdidata-ForegroundExtract-DB-LLR-091 */
               for(var_j=0;var_j<Page_settings.Cg_settings[Cg_cnt-1].cg_no_ptr;var_j++)
               {
                  Page_settings.Cg_settings[Cg_cnt-1].cg_ptr_shape[var_j]=
                     *((T_UINT16 *)(address+offset+length_count));
                  length_count=length_count+TWO;
               }
               break;
            case CG_PTR_SCALE:
               /* hdudispfpdidata-ForegroundExtract-DB-LLR-092 */
               for(var_j=0;var_j<Page_settings.Cg_settings[Cg_cnt-1].cg_no_ptr;var_j++)
               {
                  /* Updated for PR 100073 */
                  Page_settings.Cg_settings[Cg_cnt-1].cg_ptr_scale[var_j][0]=
                     *((T_INT16 *)(address+offset+length_count));
                  length_count=length_count+TWO;
                  Page_settings.Cg_settings[Cg_cnt-1].cg_ptr_scale[var_j][1]=
                     *((T_INT16 *)(address+offset+length_count));
                  length_count=length_count+TWO;
               }
               break;
            case CG_PTR_SCALE_OFFSET:
               /* hdudispfpdidata-ForegroundExtract-DB-LLR-093 */
               for(var_j=0;var_j<Page_settings.Cg_settings[Cg_cnt-1].cg_no_ptr;var_j++)
               {
                  /* Updated for PR 100073 */
                  Page_settings.Cg_settings[Cg_cnt-1].cg_ptr_scale_offset[var_j][0]=
                     *((T_INT16 *)(address+offset+length_count));
                  length_count=length_count+TWO;
                  Page_settings.Cg_settings[Cg_cnt-1].cg_ptr_scale_offset[var_j][1]=
                     *((T_INT16 *)(address+offset+length_count));
                  length_count=length_count+TWO;
               }
               break;
            case CG_PTR_ROT:
               /* hdudispfpdidata-ForegroundExtract-DB-LLR-094 */
               for(var_j=0;var_j<Page_settings.Cg_settings[Cg_cnt-1].cg_no_ptr;var_j++)
               {
                  Page_settings.Cg_settings[Cg_cnt-1].cg_ptr_rot[var_j]=
                       (*((T_INT16 *)(address+offset+length_count)));
                  length_count=length_count+TWO;
               }
               break;
            case CG_ORIEN:
               /* hdudispfpdidata-ForegroundExtract-DB-LLR-095 */
                  Page_settings.Cg_settings[Cg_cnt-1].cg_orien =
                  *((T_UINT16 *)(address+offset+length_count));
                  length_count=length_count+TWO;
                break;
            case CG_NB_AXIS:
               /* hdudispfpdidata-ForegroundExtract-DB-LLR-096 */
               Nb_cnt++;
               Cg_tracker[Cg_cnt-1][Nb_cnt-1] = TRUE;
               Page_settings.Nb_settings[Nb_cnt-1].nb_axis.u16_x=
                  *((T_UINT16 *)(address+offset+length_count));
               length_count=length_count+TWO;
               Page_settings.Nb_settings[Nb_cnt-1].nb_axis.u16_y=
                  *((T_UINT16 *)(address+offset+length_count));
               length_count=length_count+TWO;
               Page_settings.Nb_settings[Nb_cnt-1].label=
                  Page_settings.Cg_settings[Cg_cnt-1].label;
               Page_settings.Nb_settings[Nb_cnt-1].sdi=
                  Page_settings.Cg_settings[Cg_cnt-1].sdi;
               Cg_parameter_occurrence[Cg_cnt-1] |= BIT_ONE;
               break;
            case CG_NB_FORMAT:
               /* hdudispfpdidata-ForegroundExtract-DB-LLR-097 */
               Page_settings.Nb_settings[Nb_cnt-1].nb_format=
                  *((T_UINT32 *)(address+offset+length_count));
               Page_settings.Cg_settings[Cg_cnt-1].cg_nb_format=
                   Page_settings.Nb_settings[Nb_cnt-1].nb_format;
               length_count=length_count+FOUR;
               Cg_parameter_occurrence[Cg_cnt-1] |= BIT_TWO;
               break;
            case CG_NB_FONT:
               /* hdudispfpdidata-ForegroundExtract-DB-LLR-098 */
               Page_settings.Nb_settings[Nb_cnt-1].nb_font=
                  *((T_UINT16 *)(address+offset+length_count));
               length_count=length_count+TWO;
               Cg_parameter_occurrence[Cg_cnt-1] |= BIT_THREE;
               break;
            case CG_NO_LIM:
               /* hdudispfpdidata-ForegroundExtract-DB-LLR-099 */
               Page_settings.Cg_settings[Cg_cnt-1].cg_no_lim=
                  *((T_UINT8 *)(address+offset+length_count));
               Page_settings.Nb_settings[Nb_cnt-1].nb_no_lim=
                  Page_settings.Cg_settings[Cg_cnt-1].cg_no_lim;
               length_count=length_count+1;
               Cg_parameter_occurrence[Cg_cnt-1] |= BIT_FOUR;
               break;
            case CG_LIM_VAL:
               /* hdudispfpdidata-ForegroundExtract-DB-LLR-100 */
               for(var_j=0;var_j<Page_settings.Cg_settings[Cg_cnt-1].cg_no_lim;var_j++)
               {
                  Page_settings.Cg_settings[Cg_cnt-1].cg_lim_val_type[var_j]=
                     *((T_UINT8 *)(address+offset+length_count));
                  Page_settings.Nb_settings[Nb_cnt-1].nb_lim_val_type[var_j]=
                     Page_settings.Cg_settings[Cg_cnt-1].cg_lim_val_type[var_j];
                  length_count=length_count+1;
                  Page_settings.Cg_settings[Cg_cnt-1].cg_lim_val[var_j]=
                     IeeeToFloat(*((T_UINT32 *)(address+offset+length_count)));
                  Page_settings.Nb_settings[Nb_cnt-1].nb_lim_val[var_j]=
                     Page_settings.Cg_settings[Cg_cnt-1].cg_lim_val[var_j];
                  length_count=length_count+4;
               }
               Cg_parameter_occurrence[Cg_cnt-1] |= BIT_FIVE;
               break;
            case CG_LIM_COLOR:
               /* hdudispfpdidata-ForegroundExtract-DB-LLR-101 */
               for(var_j=0;var_j<Page_settings.Cg_settings[Cg_cnt-1].cg_no_lim;var_j++)
               {
                  Page_settings.Cg_settings[Cg_cnt-1].cg_lim_color[var_j]=
                     *((T_UINT16 *)(address+offset+length_count));
                  Page_settings.Nb_settings[Nb_cnt-1].nb_lim_color[var_j]=
                     Page_settings.Cg_settings[Cg_cnt-1].cg_lim_color[var_j];
                  length_count=length_count+TWO;
               }
               Cg_parameter_occurrence[Cg_cnt-1] |= BIT_SIX;
               break;
            case CG_LIM_TYPE:
               /* hdudispfpdidata-ForegroundExtract-DB-LLR-157 */
               for(var_j=0;var_j<Page_settings.Cg_settings[Cg_cnt-1].cg_no_lim;var_j++)
               {
                  Page_settings.Cg_settings[Cg_cnt-1].cg_lim_type[var_j]=
                     *((T_UINT16 *)(address+offset+length_count));
                  Page_settings.Nb_settings[Nb_cnt-1].nb_lim_type[var_j]=
                     Page_settings.Cg_settings[Cg_cnt-1].cg_lim_type[var_j];
                  length_count=length_count+TWO;
               }
               break;
            case CG_REDX_AXIS:
               /* hdudispfpdidata-ForegroundExtract-DB-LLR-102 */
               Page_settings.Cg_settings[Cg_cnt-1].cg_redx_axis.u16_x=
                  *((T_UINT16 *)(address+offset+length_count));
               Page_settings.Nb_settings[Nb_cnt-1].nb_redx_axis.u16_x=
                  Page_settings.Nb_settings[Nb_cnt-1].nb_axis.u16_x;
               length_count=length_count+TWO;
               Page_settings.Cg_settings[Cg_cnt-1].cg_redx_axis.u16_y=
                  *((T_UINT16 *)(address+offset+length_count));
               Page_settings.Nb_settings[Nb_cnt-1].nb_redx_axis.u16_y=
                  Page_settings.Nb_settings[Nb_cnt-1].nb_axis.u16_y;
               length_count=length_count+TWO;
               Cg_parameter_occurrence[Cg_cnt-1] |= BIT_SEVEN;
               break;
            case CG_REDX_WIDTH:
               /* hdudispfpdidata-ForegroundExtract-DB-LLR-103 */
               Page_settings.Cg_settings[Cg_cnt-1].cg_redx_width=
                  *((T_UINT16 *)(address+offset+length_count));
               length_count=length_count+TWO;
               Cg_parameter_occurrence[Cg_cnt-1] |= BIT_EIGHT;
               break;
            case CG_REDX_HEIGHT:
               /* hdudispfpdidata-ForegroundExtract-DB-LLR-104 */
               Page_settings.Cg_settings[Cg_cnt-1].cg_redx_height=
                  *((T_UINT16 *)(address+offset+length_count));
               length_count=length_count+TWO;
               Cg_parameter_occurrence[Cg_cnt-1] |= BIT_NINE;
               break;
            case CG_REDX_OFFSET_AXIS:
               /* hdudispfpdidata-ForegroundExtract-DB-LLR-105 */
               Page_settings.Cg_settings[Cg_cnt-1].cg_redx_offset_axis.u16_x=
                  *((T_UINT16 *)(address+offset+length_count));
               Page_settings.Nb_settings[Nb_cnt-1].nb_redx_offset_axis.u16_x=0;
               length_count=length_count+TWO;
               Page_settings.Cg_settings[Cg_cnt-1].cg_redx_offset_axis.u16_y=
                  *((T_UINT16 *)(address+offset+length_count));
               Page_settings.Nb_settings[Nb_cnt-1].nb_redx_offset_axis.u16_y=0;
               length_count=length_count+TWO;
               Cg_parameter_occurrence[Cg_cnt-1] |= BIT_TEN;
               break;
            case CG_REDX_FONT:
               /* hdudispfpdidata-ForegroundExtract-DB-LLR-106 */
               Page_settings.Cg_settings[Cg_cnt-1].cg_redx_font=
                  *((T_UINT16 *)(address+offset+length_count));
               Page_settings.Nb_settings[Nb_cnt-1].nb_redx_font=
                  Page_settings.Cg_settings[Cg_cnt-1].cg_redx_font;
               length_count=length_count+TWO;
               Cg_parameter_occurrence[Cg_cnt-1] |= BIT_ELEVEN;
               break;
            case CG_REDX_TXT:
               /* hdudispfpdidata-ForegroundExtract-DB-LLR-107 */
               var_j=0;
               while((*((T_UINT8 *)(address+offset+length_count))!=0) && (var_j<THIRTY_ONE))
               {

                   Page_settings.Cg_settings[Cg_cnt-1].cg_redx_txt[var_j]=
                         *((T_UINT8 *)(address+offset+length_count));
                   if(('n' == Page_settings.Cg_settings[Cg_cnt-1].cg_redx_txt[var_j])
                       &&( '\\' == Page_settings.Cg_settings[Cg_cnt-1].cg_redx_txt[var_j-1] ))
                   {
                      Page_settings.Cg_settings[Cg_cnt-1].cg_redx_txt[var_j-1] ='\n';
                   }
                   else if(('r' == Page_settings.Cg_settings[Cg_cnt-1].cg_redx_txt[var_j])
                        &&('\\' == Page_settings.Cg_settings[Cg_cnt-1].cg_redx_txt[var_j-1]))
                   {
                      Page_settings.Cg_settings[Cg_cnt-1].cg_redx_txt[var_j-1] ='\r';
                   }
                   else
                   {
                       var_j++;
                   }
                   length_count++;
               }
               /* hdudispfpdidata-ForegroundExtract-DB-LLR-107 */
               Page_settings.Cg_settings[Cg_cnt-1].cg_redx_txt[var_j]=
                  *((T_UINT8 *)(address+offset+length_count));
               Page_settings.Nb_settings[Nb_cnt-1].nb_redx_txt[0]='X';
               Page_settings.Nb_settings[Nb_cnt-1].nb_redx_txt[1]='X';
               Page_settings.Nb_settings[Nb_cnt-1].nb_redx_txt[2]='X';
               Page_settings.Nb_settings[Nb_cnt-1].nb_redx_txt[3]='X';
               length_count++;
               Cg_parameter_occurrence[Cg_cnt-1] |= BIT_TWELVE;
               break;
			   /*hdudispfpdidata-ForegroundExtract-DB-LLR-166*/
            case EXCEED_TIMER_AXIS:
               Page_settings.Timer_settings[Timer_cnt-1].timer_axis.u16_x =
                                    *((T_UINT16 *)(address+offset+length_count));
               length_count = (T_UINT16)(length_count+TWO);
               Page_settings.Timer_settings[Timer_cnt-1].timer_axis.u16_y =
                                    *((T_UINT16 *)(address+offset+length_count));
               length_count = (T_UINT16)(length_count + TWO);
               break;
              /*hdudispfpdidata-ForegroundExtract-DB-LLR-167*/
            case EXCEED_TIMER_FONT:
                Page_settings.Timer_settings[Timer_cnt-1].timer_font =
			      *((T_UINT16 *)(address+offset+length_count));
               length_count= (T_UINT16)(length_count + TWO);
               break;
             /*hdudispfpdidata-ForegroundExtract-DB-LLR-168*/
            case EXCEED_TIMER_FORMAT:
                Page_settings.Timer_settings[Timer_cnt-1].timer_format =
			      *((T_UINT16 *)(address+offset+length_count));
               length_count= (T_UINT16)(length_count + TWO);
               break;
              default:
               break;
         }
      }
   }
   for(indx=0;indx<Bg_cnt;indx++)
   {
      /* hdudispfpdidata-ForegroundExtract-DB-LLR-065 */
      for(u8_i=0;u8_i<PARAMTR_MAX_VAL_FG;u8_i++)
      {
     	  if (ONE == Config_data.scu_enable)
     	  {
              if((Scu_parameters[0].label == Page_settings.Bg_settings[indx].label)
                 && (Scu_parameters[0].sdi == Page_settings.Bg_settings[indx].sdi))
              {
        	     Ap_page1_bar_graphs[indx].psParam = &Scu_parameters[0].reading;
        	     /* If Yellow line value is received, update it to limVal and lin_range */
                 if(ONE == (Scu_fty_offset_flag & ONE))
                 {
                	 Ap_page1_bar_graphs[indx].limVal[0] = Scu_bg_lim_val[0];
                	 Page_settings.Bg_settings[indx].bg_lin_range[2] = (T_INT32)Scu_bg_lim_val[0];
                	 scu_bg_limval[0] = TRUE;
                 }
                 else
                 {
                	 ;
                 }
        	     /* If Max Display value is received, update it to limVal and lin_range */
                 if(ONE == ((Scu_fty_offset_flag >> ONE) & ONE))
                 {
                	 Ap_page1_bar_graphs[indx].limVal[1] = Scu_bg_lim_val[1];
                	 Page_settings.Bg_settings[indx].bg_lin_range[3] = (T_INT32)Scu_bg_lim_val[1];
                	 scu_bg_limval[1] = TRUE;
                 }
                 else
                 {
               	  ;
                 }
        	     break;
              }
              else if((Parameters[u8_i].label == Page_settings.Bg_settings[indx].label) &&
                  (Parameters[u8_i].sdi == Page_settings.Bg_settings[indx].sdi))
             {
                 Ap_page1_bar_graphs[indx].psParam=&Parameters[u8_i].reading;
                 break;
             }
             else
             {
                ;
             }
     	  }
     	  else
     	  {
     		 if((Parameters[u8_i].label == Page_settings.Bg_settings[indx].label) &&
     		    (Parameters[u8_i].sdi == Page_settings.Bg_settings[indx].sdi))
     		   {
     		       Ap_page1_bar_graphs[indx].psParam=&Parameters[u8_i].reading;
     		       break;
     		   }
     		   else
     		   {
     		       ;
     		   }
     	  }
      }
	  /* hdudispfpdidata-ForegroundExtract-DB-LLR-158 */
      if(ZERO == Page_settings.Bg_settings[indx].bg_nb_font)
      {
    	  Page_settings.Bg_settings[indx].bg_nb_font = FONT_NORMAL;
      }
      else
      {
    	  ;
      }
      if(ZERO == Page_settings.Bg_settings[indx].bg_redx_font)
      {
    	  Page_settings.Bg_settings[indx].bg_redx_font = FONT_NORMAL;
      }
      else
      {
    	  ;
      }

	  /* hdudispfpdidata-ForegroundExtract-DB-LLR-066 */
      Bg_lookuptable[indx].x=Page_settings.Bg_settings[indx].bg_lin_range;
      Bg_lookuptable[indx].y=Page_settings.Bg_settings[indx].bg_lin_length;
      Ap_page1_bar_graphs[indx].psGeometry=&Bg_lookuptable[indx];
      Ap_page1_bar_graphs[indx].u16Width=Page_settings.Bg_settings[indx].bg_width;
      Ap_page1_bar_graphs[indx].sOrigin.u16X0=
                      (T_INT16)Page_settings.Bg_settings[indx].bg_axis.u16_x;
      Ap_page1_bar_graphs[indx].sOrigin.u16Y0=
                       (T_INT16)Page_settings.Bg_settings[indx].bg_axis.u16_y;
      Ap_page1_bar_graphs[indx].sDigOffset.u16X0=
           (T_INT16)Page_settings.Bg_settings[indx].bg_nb_axis.u16_x;
      Ap_page1_bar_graphs[indx].sDigOffset.u16Y0=
           (T_INT16)Page_settings.Bg_settings[indx].bg_nb_axis.u16_y;
      Ap_page1_bar_graphs[indx].ePenColor=WHITE;
      Ap_page1_bar_graphs[indx].eFont=
              (T_ETXFONT)Page_settings.Bg_settings[indx].bg_nb_font;
      Ap_page1_bar_graphs[indx].eBGHV= (T_EBGHV)Page_settings.Bg_settings[indx].bg_orien;
      Ap_page1_bar_graphs[indx].numLimit=Page_settings.Bg_settings[indx].bg_no_lim;

      /* hdudispfpdidata-ForegroundExtract-DB-LLR-067 */
      for(u8_j=0;u8_j<Page_settings.Bg_settings[indx].bg_no_lim;u8_j++)
      {
    	  if((TRUE == scu_bg_limval[0])&& (ZERO == u8_j))
    	  {
    		  scu_bg_limval[0] = FALSE;
    	         Ap_page1_bar_graphs[indx].limValtype[u8_j]=
    	            Page_settings.Bg_settings[indx].bg_lim_val_type[u8_j];
    	         Ap_page1_bar_graphs[indx].limColor[u8_j]=
    	            FindColor(Page_settings.Bg_settings[indx].bg_lim_color[u8_j]);
    	         Ap_page1_bar_graphs[indx].limType[u8_j]=
    	        	FindParamType(Page_settings.Bg_settings[indx].bg_lim_type[u8_j]);
    	  }
    	  else if((TRUE == scu_bg_limval[1])&& (ONE == u8_j))
    	  {
    		  scu_bg_limval[1] = FALSE;
    	         Ap_page1_bar_graphs[indx].limValtype[u8_j]=
    	            Page_settings.Bg_settings[indx].bg_lim_val_type[u8_j];
    	         Ap_page1_bar_graphs[indx].limColor[u8_j]=
    	            FindColor(Page_settings.Bg_settings[indx].bg_lim_color[u8_j]);
    	         Ap_page1_bar_graphs[indx].limType[u8_j]=
    	        	FindParamType(Page_settings.Bg_settings[indx].bg_lim_type[u8_j]);
    	  }
    	  else
    	  {
              Ap_page1_bar_graphs[indx].limVal[u8_j]=
                Page_settings.Bg_settings[indx].bg_lim_val[u8_j];
              Ap_page1_bar_graphs[indx].limValtype[u8_j]=
                Page_settings.Bg_settings[indx].bg_lim_val_type[u8_j];
              Ap_page1_bar_graphs[indx].limColor[u8_j]=
                FindColor(Page_settings.Bg_settings[indx].bg_lim_color[u8_j]);
              Ap_page1_bar_graphs[indx].limType[u8_j]=
        	    FindParamType(Page_settings.Bg_settings[indx].bg_lim_type[u8_j]);
    	  }
      }

      /* hdudispfpdidata-ForegroundExtract-DB-LLR-068 */
      Bg_dis_region[indx].sDisLocCtr.u16X0=
                      (T_INT16)Page_settings.Bg_settings[indx].bg_redx_axis.u16_x;
      Bg_dis_region[indx].sDisLocCtr.u16Y0=
                      (T_INT16)Page_settings.Bg_settings[indx].bg_redx_axis.u16_y;
      Bg_dis_region[indx].s32Width=Page_settings.Bg_settings[indx].bg_redx_width;
      Bg_dis_region[indx].eTXFont=
              (T_ETXFONT)Page_settings.Bg_settings[indx].bg_redx_font;
      Bg_dis_region[indx].s32Height=Page_settings.Bg_settings[indx].bg_redx_height;
      Bg_dis_region[indx].sDisLocO.u16X0=
           (T_INT16)Page_settings.Bg_settings[indx].bg_redx_offset_axis.u16_x;
      Bg_dis_region[indx].sDisLocO.u16Y0=
           (T_INT16)Page_settings.Bg_settings[indx].bg_redx_offset_axis.u16_y;
      Bg_dis_region[indx].pu8Text=Page_settings.Bg_settings[indx].bg_redx_txt;
      Bg_dis_region[indx].eRegionType=E_REGION_TYPE_GAUGE;
      Ap_page1_bar_graphs[indx].psDisRegion=&Bg_dis_region[indx];
      Ap_page1_bar_graphs[indx].u16Format=
               (T_UINT16)(FindFormat(Page_settings.Bg_settings[indx].bg_nb_format));
      num_dec=0;
       num_dec = (Ap_page1_bar_graphs[indx].u16Format>>FOUR & SEVEN);
      for(u8_i=1;u8_i<=Page_settings.Bg_settings[indx].bg_no_lin;u8_i++)
      {
         Page_settings.Bg_settings[indx].bg_lin_range[u8_i]=(T_INT32)(
         (T_FLOAT)Page_settings.Bg_settings[indx].bg_lin_range[u8_i]*10.0f*
                               CalculatePower(10,num_dec));
      }
   }

   /* hdudispfpdidata-ForegroundExtract-DB-LLR-077 */
   for(indx=0;indx<MAX_NUM_PAGE_DIALS;indx++)
   {
       /*updated for PR 100073*/
      MemSet(&Ap_page0_dials[indx],0,sizeof(T_ROUNDDIALDEF));
   }
   for(indx=0;indx<Rd_cnt;indx++)
   {
      /* hdudispfpdidata-ForegroundExtract-DB-LLR-069 */
      for(u8_i=0;u8_i<PARAMTR_MAX_VAL_FG;u8_i++)
      {
         if((Parameters[u8_i].label == Page_settings.Rd_settings[indx].label) &&
            (Parameters[u8_i].sdi == Page_settings.Rd_settings[indx].sdi))
         {
            Ap_page0_dials[indx].psParam=&Parameters[u8_i].reading;
            break;
         }
         else
         {
            ;
         }
      }
	  /* hdudispfpdidata-ForegroundExtract-DB-LLR-159 */
      if(ZERO == Page_settings.Rd_settings[indx].rd_nb_font)
      {
    	  Page_settings.Rd_settings[indx].rd_nb_font = FONT_NORMAL;
      }
      else
      {
    	  ;
      }
      if(ZERO == Page_settings.Rd_settings[indx].rd_redx_font)
      {
    	  Page_settings.Rd_settings[indx].rd_redx_font = FONT_NORMAL;
      }
      else
      {
    	  ;
      }
      /* hdudispfpdidata-ForegroundExtract-DB-LLR-070 */
      Rd_lookuptable[indx].x=Page_settings.Rd_settings[indx].rd_lin_range;
      Rd_lookuptable[indx].y=Page_settings.Rd_settings[indx].rd_lin_angle;
      Ap_page0_dials[indx].psGeometry=&Rd_lookuptable[indx];
      Ap_page0_dials[indx].sDialCenterOffset.u16X0=
           (T_INT16)MAG((T_INT16)Page_settings.Rd_settings[indx].rd_axis.u16_x);
      Ap_page0_dials[indx].sDialCenterOffset.u16Y0=
           (T_INT16)MAG((T_INT16)Page_settings.Rd_settings[indx].rd_axis.u16_y);
      Ap_page0_dials[indx].usLength=
            (T_UINT16)MAG((T_INT16)Page_settings.Rd_settings[indx].rd_length);
      Ap_page0_dials[indx].numLimit=Page_settings.Rd_settings[indx].rd_no_lim;
      Ap_page0_dials[indx].vernStatus=Page_settings.Rd_settings[indx].rd_vern;
      Ap_page0_dials[indx].vernPos=Page_settings.Rd_settings[indx].rd_vern_pos;

      /* hdudispfpdidata-ForegroundExtract-DB-LLR-071 */
      for(u8_j=0;u8_j<Page_settings.Rd_settings[indx].rd_no_lim;u8_j++)
      {
         Ap_page0_dials[indx].limColor[u8_j]=
            FindColor(Page_settings.Rd_settings[indx].rd_lim_color[u8_j]);
         Ap_page0_dials[indx].limVal[u8_j]=
            Page_settings.Rd_settings[indx].rd_lim_val[u8_j];
         Ap_page0_dials[indx].limValtype[u8_j]=
            Page_settings.Rd_settings[indx].rd_lim_val_type[u8_j];
         Ap_page0_dials[indx].limType[u8_j]=
        	FindParamType(Page_settings.Rd_settings[indx].rd_lim_type[u8_j]);
      }

      /* hdudispfpdidata-ForegroundExtract-DB-LLR-072 */
      for(u8_j=0;u8_j<Page_settings.Rd_settings[indx].rd_no_ptr;u8_j++)
      {
    	  if(ZERO == Page_settings.Rd_settings[indx].rd_ptr_shape[u8_j])
    	  {
    		  Page_settings.Rd_settings[indx].rd_ptr_shape[u8_j] = FG_STANDARD_POINTER;
    	  }
         Ap_page0_dials[indx].asPtrSpec[u8_j].ePenColor=
            FindColor(Page_settings.Rd_settings[indx].rd_ptr_color[u8_j]);
         Ap_page0_dials[indx].asPtrSpec[u8_j].s32PtrShape=
            Page_settings.Rd_settings[indx].rd_ptr_shape[u8_j];
         Ap_page0_dials[indx].ptr_scale[u8_j].u16X0=
            Page_settings.Rd_settings[indx].rd_ptr_scale[u8_j][0];
         Ap_page0_dials[indx].ptr_scale[u8_j].u16Y0=
            Page_settings.Rd_settings[indx].rd_ptr_scale[u8_j][1];
         Ap_page0_dials[indx].ptr_scale_offset[u8_j].u16X0=
            Page_settings.Rd_settings[indx].rd_ptr_scale_offset[u8_j][0];
         Ap_page0_dials[indx].ptr_scale_offset[u8_j].u16Y0=
            Page_settings.Rd_settings[indx].rd_ptr_scale_offset[u8_j][1];
         Ap_page0_dials[indx].rotAngle[u8_j]=
            Page_settings.Rd_settings[indx].rd_ptr_rot[u8_j];
      }

      /* hdudispfpdidata-ForegroundExtract-DB-LLR-073 */
      Ap_page0_dials[indx].u16Format =
                    (T_UINT16)FindFormat(Page_settings.Rd_settings[indx].rd_nb_format);
      Rd_dis_region[indx].sDisLocCtr.u16X0=
                    (T_INT16)Page_settings.Rd_settings[indx].rd_redx_axis.u16_x;
      Rd_dis_region[indx].sDisLocCtr.u16Y0=
                    (T_INT16)Page_settings.Rd_settings[indx].rd_redx_axis.u16_y;
      /* Updated for PR 100073 */
      Rd_dis_region[indx].s32Width=(T_INT32)Page_settings.Rd_settings[indx].rd_redx_width;
      Rd_dis_region[indx].eTXFont=
              (T_ETXFONT)Page_settings.Rd_settings[indx].rd_redx_font;
      /* Updated for PR 100073 */
      Rd_dis_region[indx].s32Height=(T_INT32)Page_settings.Rd_settings[indx].rd_redx_height;
      Rd_dis_region[indx].sDisLocO.u16X0=
           (T_INT16)Page_settings.Rd_settings[indx].rd_redx_offset_axis.u16_x;
      Rd_dis_region[indx].sDisLocO.u16Y0=
           (T_INT16)Page_settings.Rd_settings[indx].rd_redx_offset_axis.u16_y;
      Rd_dis_region[indx].pu8Text=Page_settings.Rd_settings[indx].rd_redx_txt;
      Rd_dis_region[indx].eRegionType=E_REGION_TYPE_GAUGE;
      Ap_page0_dials[indx].psDisRegion=&Rd_dis_region[indx];
      Ap_page0_dials[indx].sDigCenterOffset.u16X0=
           (T_INT16)MAG((T_INT16)Page_settings.Rd_settings[indx].rd_nb_axis.u16_x);
      Ap_page0_dials[indx].sDigCenterOffset.u16Y0=
           (T_INT16)MAG((T_INT16)Page_settings.Rd_settings[indx].rd_nb_axis.u16_y);
      Ap_page0_dials[indx].label=Page_settings.Rd_settings[indx].label;

      for(u8_j=0;u8_j<ASSOCIALTED_LABEL;u8_j++)
      {
         Ap_page0_dials[indx].associated_labels[u8_j]=
               Page_settings.Rd_settings[indx].assc_labels[u8_j];
      }
       num_dec = (Ap_page0_dials[indx].u16Format>>FOUR & SEVEN);
       /* updated for PR 100073 */
       Page_settings.Rd_settings[indx].rd_lin_range[0]=(T_INT32)rd_lin_rnge[indx][0];
      for(u8_i=1;u8_i<=Page_settings.Rd_settings[indx].rd_no_lin;u8_i++)
      {
         Page_settings.Rd_settings[indx].rd_lin_range[u8_i]=
         (T_INT32)(rd_lin_rnge[indx][u8_i]*100*CalculatePower(10,num_dec));
      }
   }

   /* hdudispfpdidata-ForegroundExtract-DB-LLR-078 */
   for(indx=0;indx<MAX_NUM_PAGE_DIALS;indx++)
   {
       /*updated for PR 100073*/
       MemSet(&Page_num_boxes[indx],0,sizeof(T_SNUMBOXDEF));
   }

   for(indx=0;indx<Nb_cnt;indx++)
   {
      /* hdudispfpdidata-ForegroundExtract-DB-LLR-074 */
      for(u8_i=0;u8_i<PARAMTR_MAX_VAL;u8_i++)
      {
     	  if (ONE == Config_data.scu_enable)
     	  {
          if((Scu_parameters[0].label ==
             Page_settings.Nb_settings[indx].label) &&
             (Scu_parameters[0].sdi == Page_settings.Nb_settings[indx].sdi))
          {
              Page_num_boxes[indx].psParam=&Scu_parameters[0].reading;
              if(ONE == (Scu_fty_offset_flag & ONE))
              {
            	  Page_num_boxes[indx].limVal[0] = Scu_bg_lim_val[0];
            	  scu_bg_limval[0] = TRUE;
              }
              else
              {
            	  ;
              }
              if(ONE == ((Scu_fty_offset_flag >> ONE) & ONE))
              {
            	  Page_num_boxes[indx].limVal[1] = Scu_bg_lim_val[1];
            	  scu_bg_limval[1] = TRUE;
              }
              else
              {
            	  ;
              }
              break;
          }
          else if((Parameters_numbox[u8_i].label ==
                 Page_settings.Nb_settings[indx].label) &&
                 (Parameters_numbox[u8_i].sdi == Page_settings.Nb_settings[indx].sdi))
         {
             Page_num_boxes[indx].psParam=&Parameters_numbox[u8_i].reading;
             break;
         }
         else
         {
            ;
         }
     	  }
     	  else
     	  {
              /* Updated for PR 100073 */
              if((Parameters_numbox[u8_i].label ==
                      Page_settings.Nb_settings[indx].label) &&
                      (Parameters_numbox[u8_i].sdi == Page_settings.Nb_settings[indx].sdi))
              {
                  Page_num_boxes[indx].psParam=&Parameters_numbox[u8_i].reading;
                  break;
              }
              else
              {
                 ;
              }
     	  }
      }

      /* hdudispfpdidata-ForegroundExtract-DB-LLR-160 */
      if(ZERO == Page_settings.Nb_settings[indx].nb_font)
      {
    	  Page_settings.Nb_settings[indx].nb_font = FONT_NORMAL;
      }
      else
      {
    	  ;
      }
      if(ZERO == Page_settings.Nb_settings[indx].nb_redx_font)
      {
    	  Page_settings.Nb_settings[indx].nb_redx_font = FONT_NORMAL;
      }
      else
      {
    	  ;
      }

	  /* hdudispfpdidata-ForegroundExtract-DB-LLR-075 */
      Page_num_boxes[indx].sCenter.u16X0=
                 (T_INT16)MAG((T_INT16)Page_settings.Nb_settings[indx].nb_axis.u16_x);
      Page_num_boxes[indx].sCenter.u16Y0=
                 (T_INT16)MAG((T_INT16)Page_settings.Nb_settings[indx].nb_axis.u16_y);
      Page_num_boxes[indx].u16Format =
                 (T_UINT16) FindFormat(Page_settings.Nb_settings[indx].nb_format);
      Page_num_boxes[indx].eFont =
                  (T_ETXFONT)Page_settings.Nb_settings[indx].nb_font;
      Nb_dis_region[indx].sDisLocO.u16X0=
           (T_INT16)Page_settings.Nb_settings[indx].nb_redx_offset_axis.u16_x;
      Nb_dis_region[indx].sDisLocO.u16Y0 =
           (T_INT16)Page_settings.Nb_settings[indx].nb_redx_offset_axis.u16_y;
      Nb_dis_region[indx].sDisLocCtr.u16X0=
           (T_INT16)Page_settings.Nb_settings[indx].nb_redx_axis.u16_x;
      Nb_dis_region[indx].sDisLocCtr.u16Y0 =
           (T_INT16)Page_settings.Nb_settings[indx].nb_redx_axis.u16_y;
      Nb_dis_region[indx].eTXFont =
              (T_ETXFONT)Page_settings.Nb_settings[indx].nb_redx_font;
      Nb_dis_region[indx].s32Height=
         Page_settings.Nb_settings[indx].nb_redx_height;
      Nb_dis_region[indx].s32Width=
         Page_settings.Nb_settings[indx].nb_redx_width;
      Nb_dis_region[indx].pu8Text =
         Page_settings.Nb_settings[indx].nb_redx_txt;
      Nb_dis_region[indx].eRegionType=
         E_REGION_TYPE_GAUGE;
      Page_num_boxes[indx].psDisRegion=
         &Nb_dis_region[indx];
      Page_num_boxes[indx].numLimit =
         Page_settings.Nb_settings[indx].nb_no_lim;
      Page_num_boxes[indx].ePenColor=WHITE;

      /* hdudispfpdidata-ForegroundExtract-DB-LLR-076 */
      for(u8_j=0;u8_j<Page_settings.Nb_settings[indx].nb_no_lim;u8_j++)
      {
    	  if((TRUE == scu_bg_limval[0])&& (ZERO == u8_j))
    	  {
    		  scu_bg_limval[0] = FALSE;
    	      Page_num_boxes[indx].limValtype[u8_j]=
    	          Page_settings.Nb_settings[indx].nb_lim_val_type[u8_j];
    	      Page_num_boxes[indx].limColor[u8_j]=
    	          FindColor(Page_settings.Nb_settings[indx].nb_lim_color[u8_j]);
    	      Page_num_boxes[indx].limType[u8_j]=
    	          FindParamType(Page_settings.Nb_settings[indx].nb_lim_type[u8_j]);
    	  }
    	  else if((TRUE == scu_bg_limval[1])&& (ONE == u8_j))
    	  {
    		  scu_bg_limval[1] = FALSE;
    	      Page_num_boxes[indx].limValtype[u8_j]=
    	         Page_settings.Nb_settings[indx].nb_lim_val_type[u8_j];
    	      Page_num_boxes[indx].limColor[u8_j]=
    	         FindColor(Page_settings.Nb_settings[indx].nb_lim_color[u8_j]);
    	      Page_num_boxes[indx].limType[u8_j]=
    	        FindParamType(Page_settings.Nb_settings[indx].nb_lim_type[u8_j]);
    	  }
    	  else
    	  {
              Page_num_boxes[indx].limVal[u8_j]=
                Page_settings.Nb_settings[indx].nb_lim_val[u8_j];
              Page_num_boxes[indx].limValtype[u8_j]=
                Page_settings.Nb_settings[indx].nb_lim_val_type[u8_j];
              Page_num_boxes[indx].limColor[u8_j]=
                FindColor(Page_settings.Nb_settings[indx].nb_lim_color[u8_j]);
              Page_num_boxes[indx].limType[u8_j]=
                FindParamType(Page_settings.Nb_settings[indx].nb_lim_type[u8_j]);
    	  }
      }
   }

      for(indx=0;indx<MAX_NUM_PAGE_DIALS;indx++)
      {
          /*updated for PR 100073*/
         MemSet(&Ap_page2_carrot[indx],0,sizeof(T_CARROTGRAPHDEF));
      }
      for(indx=0;indx<Cg_cnt;indx++)
      {
         /* hdudispfpdidata-ForegroundExtract-DB-LLR-108 */
         for(u8_i=0;u8_i<PARAMTR_MAX_VAL_FG;u8_i++)
         {
            if((Parameters[u8_i].label == Page_settings.Cg_settings[indx].label) &&
                    (Parameters[u8_i].sdi == Page_settings.Cg_settings[indx].sdi))
            {
               Ap_page2_carrot[indx].psParam=&Parameters[u8_i].reading;
               break;
            }
            else
            {
               ;
            }
         }
		  /* hdudispfpdidata-ForegroundExtract-DB-LLR-161 */
         if(ZERO == Page_settings.Cg_settings[indx].cg_redx_font)
         {
       	  Page_settings.Cg_settings[indx].cg_redx_font = FONT_NORMAL;
         }
         else
         {
        	 ;
         }
         if(ZERO == Page_settings.Cg_settings[indx].cg_nb_font)
         {
       	  Page_settings.Cg_settings[indx].cg_nb_font = FONT_NORMAL;
         }
         else
         {
        	 ;
         }

         /* hdudispfpdidata-ForegroundExtract-DB-LLR-109 */
         Cg_lookuptable[indx].x=Page_settings.Cg_settings[indx].cg_lin_range;
         Cg_lookuptable[indx].y=Page_settings.Cg_settings[indx].cg_lin_offset;
         Ap_page2_carrot[indx].psGeometry=&Cg_lookuptable[indx];
         Ap_page2_carrot[indx].sDialCenterOffset.u16X0=
              (T_INT16)MAG((T_INT16)Page_settings.Cg_settings[indx].cg_axis.u16_x);
         Ap_page2_carrot[indx].sDialCenterOffset.u16Y0=
              (T_INT16)MAG((T_INT16)Page_settings.Cg_settings[indx].cg_axis.u16_y);
         Ap_page2_carrot[indx].eCGHV= (T_ECGHV)Page_settings.Cg_settings[indx].cg_orien;
         Ap_page2_carrot[indx].numLimit=Page_settings.Cg_settings[indx].cg_no_lim;

         /* hdudispfpdidata-ForegroundExtract-DB-LLR-110 */
         for(u8_j=0;u8_j<Page_settings.Cg_settings[indx].cg_no_lim;u8_j++)
         {
            Ap_page2_carrot[indx].limColor[u8_j]=
               FindColor(Page_settings.Cg_settings[indx].cg_lim_color[u8_j]);
            Ap_page2_carrot[indx].limVal[u8_j]=
               Page_settings.Cg_settings[indx].cg_lim_val[u8_j];
            Ap_page2_carrot[indx].limValtype[u8_j]=
               Page_settings.Cg_settings[indx].cg_lim_val_type[u8_j];
            Ap_page2_carrot[indx].limType[u8_j]=
               FindParamType(Page_settings.Cg_settings[indx].cg_lim_type[u8_j]);
         }

         /* hdudispfpdidata-ForegroundExtract-DB-LLR-111 */
         for(u8_j=0;u8_j<Page_settings.Cg_settings[indx].cg_no_ptr;u8_j++)
         {
            Ap_page2_carrot[indx].asPtrSpec[u8_j].ePenColor=
               FindColor(Page_settings.Cg_settings[indx].cg_ptr_color[u8_j]);
            Ap_page2_carrot[indx].asPtrSpec[u8_j].s32PtrShape=
               Page_settings.Cg_settings[indx].cg_ptr_shape[u8_j];
            Ap_page2_carrot[indx].ptr_scale[u8_j].u16X0=
               Page_settings.Cg_settings[indx].cg_ptr_scale[u8_j][0];
            Ap_page2_carrot[indx].ptr_scale[u8_j].u16Y0=
               Page_settings.Cg_settings[indx].cg_ptr_scale[u8_j][1];
            Ap_page2_carrot[indx].ptr_scale_offset[u8_j].u16X0=
               Page_settings.Cg_settings[indx].cg_ptr_scale_offset[u8_j][0];
            Ap_page2_carrot[indx].ptr_scale_offset[u8_j].u16Y0=
               Page_settings.Cg_settings[indx].cg_ptr_scale_offset[u8_j][1];
            Ap_page2_carrot[indx].rotAngle[u8_j]=
               Page_settings.Cg_settings[indx].cg_ptr_rot[u8_j];
         }

         /* hdudispfpdidata-ForegroundExtract-DB-LLR-112 */
         Ap_page2_carrot[indx].u16Format =
                       (T_UINT16)FindFormat(Page_settings.Cg_settings[indx].cg_nb_format);
         Cg_dis_region[indx].sDisLocCtr.u16X0=
                       (T_INT16)Page_settings.Cg_settings[indx].cg_redx_axis.u16_x;
         Cg_dis_region[indx].sDisLocCtr.u16Y0=
                       (T_INT16)Page_settings.Cg_settings[indx].cg_redx_axis.u16_y;
         /* Updated for PR 100073 */
         Cg_dis_region[indx].s32Width=(T_INT32)Page_settings.Cg_settings[indx].cg_redx_width;
         Cg_dis_region[indx].eTXFont=
              (T_ETXFONT)Page_settings.Cg_settings[indx].cg_redx_font;
         /* Updated for PR 100073 */
          /* hdudispfpdidata-ForegroundExtract-DB-LLR-113 */
         Cg_dis_region[indx].s32Height=(T_INT32)Page_settings.Cg_settings[indx].cg_redx_height;
         Cg_dis_region[indx].sDisLocO.u16X0=
              (T_INT16)Page_settings.Cg_settings[indx].cg_redx_offset_axis.u16_x;
         Cg_dis_region[indx].sDisLocO.u16Y0=
              (T_INT16)Page_settings.Cg_settings[indx].cg_redx_offset_axis.u16_y;
         Cg_dis_region[indx].pu8Text=Page_settings.Cg_settings[indx].cg_redx_txt;
         Cg_dis_region[indx].eRegionType=E_REGION_TYPE_GAUGE;
         Ap_page2_carrot[indx].psDisRegion=&Cg_dis_region[indx];
         Ap_page2_carrot[indx].sDigCenterOffset.u16X0=
              (T_INT16)MAG((T_INT16)Page_settings.Cg_settings[indx].cg_nb_axis.u16_x);
         Ap_page2_carrot[indx].sDigCenterOffset.u16Y0=
              (T_INT16)MAG((T_INT16)Page_settings.Cg_settings[indx].cg_nb_axis.u16_y);
         Ap_page2_carrot[indx].label=Page_settings.Cg_settings[indx].label;

          num_dec = (Ap_page2_carrot[indx].u16Format>>FOUR & SEVEN);

         for(u8_i=1;u8_i<=Page_settings.Cg_settings[indx].cg_no_lin;u8_i++)
         {
            Page_settings.Cg_settings[indx].cg_lin_range[u8_i]=
            (T_INT32)((T_FLOAT)Page_settings.Cg_settings[indx].
            cg_lin_range[u8_i]*100*CalculatePower(10,num_dec));
         }
      }

 for(indx=0;indx<Tb_cnt;indx++)
   {
    /* hdudispfpdidata-ForegroundExtract-DB-LLR-162 */
     if(ZERO == Page_settings.Tb_settings[indx].tb_font)
     {
   	  Page_settings.Tb_settings[indx].tb_font = (T_UINT16)FONT_NORMAL;
     }
     if(ZERO == Page_settings.Tb_settings[indx].tb_redx_font)
     {
   	  Page_settings.Tb_settings[indx].tb_redx_font = (T_UINT16)FONT_NORMAL;
     }
     if(ZERO == Page_settings.Tb_settings[indx].tb_align)
     {
    	 Page_settings.Tb_settings[indx].tb_align = (T_UINT16)ALIGN_CENTER;
     }
     if(ZERO == Page_settings.Tb_settings[indx].tb_state)
     {
    	 Page_settings.Tb_settings[indx].tb_state = (T_UINT16)TXT_STATE_NORMAL;
     }
     if(ZERO == Page_settings.Tb_settings[indx].tb_flash)
     {
    	 Page_settings.Tb_settings[indx].tb_flash = (T_UINT16)TEXT_FLASH_OFF;
     }

      /* hdudispfpdidata-ForegroundExtract-DB-LLR-139 */
      Ap_page_tbs[indx].s16ULX = (T_INT16)Page_settings.Tb_settings[indx].tb_axis.u16_x;
      Ap_page_tbs[indx].s16ULY = (T_INT16)Page_settings.Tb_settings[indx].tb_axis.u16_y;
      Ap_page_tbs[indx].s16PixWidth = (T_INT16)Page_settings.Tb_settings[indx].tb_width;
      Ap_page_tbs[indx].s16PixHeight = (T_INT16)Page_settings.Tb_settings[indx].tb_height;
      Ap_page_tbs[indx].s16FrameWidth = (T_INT16)Page_settings.Tb_settings[indx].tb_frame_width;
      Ap_page_tbs[indx].s16Margin = (T_INT16)Page_settings.Tb_settings[indx].tb_margin;
      Ap_page_tbs[indx].eFrameColor = FindColor(Page_settings.Tb_settings[indx].tb_frame_color);
      Ap_page_tbs[indx].eBackGroundColor = FindColor(Page_settings.Tb_settings[indx].tb_bg_color);
      Ap_page_tbs[indx].pcTitle = (T_CHAR*)Page_settings.Tb_settings[indx].tb_string;
      Ap_page_tbs[indx].eFontColor= FindColor(Page_settings.Tb_settings[indx].tb_color);
      Ap_page_tbs[indx].eFlashColor= FindColor(Page_settings.Tb_settings[indx].tb_flash_color);
      Ap_page_tbs[indx].eTXFont = Page_settings.Tb_settings[indx].tb_font;
      Ap_page_tbs[indx].psTextBox->eState =
    		  TextState(Page_settings.Tb_settings[indx].tb_state);
      Ap_page_tbs[indx].psTextBox->bFlashing =
    		  TextFlash(Page_settings.Tb_settings[indx].tb_flash);
      Tb_dis_region[indx].sDisLocCtr.u16X0 = \
	  (T_INT16)Page_settings.Tb_settings[indx].tb_redx_axis.u16_x;
      Tb_dis_region[indx].sDisLocCtr.u16Y0 = \
	  (T_INT16)Page_settings.Tb_settings[indx].tb_redx_axis.u16_y;
      Tb_dis_region[indx].s32Width = (T_INT32)Page_settings.Tb_settings[indx].tb_redx_width;
      Tb_dis_region[indx].s32Height = (T_INT32)Page_settings.Tb_settings[indx].tb_redx_height;
      Tb_dis_region[indx].sDisLocO.u16X0 =\
	  (T_INT16)Page_settings.Tb_settings[indx].tb_redx_offset_axis.u16_x;
      Tb_dis_region[indx].sDisLocO.u16Y0 =\
	  (T_INT16)Page_settings.Tb_settings[indx].tb_redx_offset_axis.u16_y;
      Tb_dis_region[indx].eTXFont = (T_ETXFONT)Page_settings.Tb_settings[indx].tb_redx_font;
      Tb_dis_region[indx].pu8Text = Page_settings.Tb_settings[indx].tb_redx_txt;
      Tb_dis_region[indx].eRegionType=E_REGION_TYPE_GAUGE;
      Ap_page_tbs[indx].psDisRegion =  &Tb_dis_region[indx];
   }

   for(indx=0;indx<Text_cnt;indx++)
   {
         /* hdudispfpdidata-ForegroundExtract-DB-LLR-163 */
	     if(ZERO == Page_settings.Text_settings[indx].txt_font)
	     {
	   	  Page_settings.Text_settings[indx].txt_font = (T_UINT16)FONT_NORMAL;
	     }
	     if(ZERO == Page_settings.Text_settings[indx].txt_redx_font)
	     {
	   	  Page_settings.Text_settings[indx].txt_redx_font = (T_UINT16)FONT_NORMAL;
	     }
	     if(ZERO == Page_settings.Text_settings[indx].txt_align)
	     {
	    	 Page_settings.Text_settings[indx].txt_align = (T_UINT16)ALIGN_CENTER;
	     }
	     if(ZERO == Page_settings.Text_settings[indx].txt_state)
	     {
	    	 Page_settings.Text_settings[indx].txt_state = (T_UINT16)TXT_STATE_NORMAL;
	     }
	     if(ZERO == Page_settings.Text_settings[indx].txt_flash)
	     {
	    	 Page_settings.Text_settings[indx].txt_flash = (T_UINT16)TEXT_FLASH_OFF;
	     }
       /* hdudispfpdidata-ForegroundExtract-DB-LLR-140 */
       Page_txt[indx].ePenColor=FindColor(Page_settings.Text_settings[indx].txt_color);
       Page_txt[indx].eTXAlign=TextAlign(Page_settings.Text_settings[indx].txt_align);
       Page_txt[indx].eTXFlash=TextFlash(Page_settings.Text_settings[indx].txt_flash);
       Page_txt[indx].eTXFont=Page_settings.Text_settings[indx].txt_font;
       Page_txt[indx].eTXV=TextState(Page_settings.Text_settings[indx].txt_state);
       Page_txt[indx].pu8String=Page_settings.Text_settings[indx].txt_string;
       Page_txt[indx].u16X0=Page_settings.Text_settings[indx].txt_axis.u16_x;
       Page_txt[indx].u16Y0=Page_settings.Text_settings[indx].txt_axis.u16_y;
       Txt_dis_region[indx].sDisLocCtr.u16X0 =\
	   (T_INT16)Page_settings.Text_settings[indx].txt_redx_axis.u16_x;
       Txt_dis_region[indx].sDisLocCtr.u16Y0 =\

	   (T_INT16)Page_settings.Text_settings[indx].txt_redx_axis.u16_y;
       Txt_dis_region[indx].s32Width = (T_INT32)Page_settings.Text_settings[indx].txt_redx_width;
       Txt_dis_region[indx].s32Height = (T_INT32)Page_settings.Text_settings[indx].txt_redx_height;
       Txt_dis_region[indx].sDisLocO.u16X0 =\
	   (T_INT16)Page_settings.Text_settings[indx].txt_redx_offset_axis.u16_x;
       Txt_dis_region[indx].sDisLocO.u16Y0 =\
	   (T_INT16)Page_settings.Text_settings[indx].txt_redx_offset_axis.u16_y;
       Txt_dis_region[indx].eTXFont = (T_ETXFONT)Page_settings.Text_settings[indx].txt_redx_font;
       Txt_dis_region[indx].pu8Text = Page_settings.Text_settings[indx].txt_redx_txt;
       Txt_dis_region[indx].eRegionType=E_REGION_TYPE_GAUGE;
       Page_txt[indx].psDisRegion =  (T_SDISREGION_TXT*)&Txt_dis_region[indx];
    }
}

/*
 *
 * Function                : CasExtract
 *
 * Description             : This function extract CAS data from the pdi
 *
 * Formal parameter(s)     : T_UINT8 *address IN - CAS address
 *
 * Return Value            : None
 *
 * Assumption              : None
 *
 */

void CasExtract(T_UINT8 *address)
{
   T_UINT8 indx = 0;
   T_UINT8 indx1 = 0;
   T_UINT32 offset = 0;
   T_UINT16 var_i = 0;
   T_UINT16 var_j = 0;
   T_UINT16 length_count = 0;
   T_UINT16 enum_val = 0;

   /*hdudispfpdidata-CasExtract-DB-LLR-001*/
   if(NULL==address)
   {
      return;
   }
   else
   {
      ;/*Do nothing*/
   }
   /*hdudispfpdidata-CasExtract-DB-LLR-002*/
   offset=0;
   Cas_word_cnt = 0;

   /*hdudispfpdidata-CasExtract-DB-LLR-003*/
   for(var_i=0;var_i<MAX_NUM_CAS;var_i++)
   {
      length_count=0;

      while(length_count<MAX_LEN_CAS)
      {
         enum_val=*((T_UINT16 *)(address+offset+length_count));
         length_count = (T_UINT16)(length_count + 2);
         if(MAX_16_BITS == enum_val)
         {
            break;
         }
         else
         {
            ;/*Do nothing*/
         }
         switch(enum_val)
         {
            case CAS_STRING:
               Cas_word_cnt++;
               var_j=0;
               while((*((T_UINT8 *)(address+offset+length_count))!=0) &&
			              (var_j<MAX_CAS_STRING_TXT))
               {
                  Cas_messages[Cas_word_cnt-1].cas_string[var_j]=
                     *((T_UINT8 *)(address+offset+length_count));
                  var_j++;
                  length_count++;
               }
               Cas_messages[Cas_word_cnt-1].cas_string[var_j]=
                  *((T_UINT8 *)(address+offset+length_count));
               length_count++;
               break;
            case LABEL:
               Cas_messages[Cas_word_cnt-1].label=*((T_UINT8 *)(address+offset+length_count));
               length_count = (T_UINT16)(length_count + 1);
               break;
            case CAS_START_BIT:
               Cas_messages[Cas_word_cnt-1].cas_start_bit=
                  *((T_UINT16 *)(address+offset+length_count));
               length_count = (T_UINT16)(length_count + 2);
               break;
            case CAS_PRIORITY:
               Cas_messages[Cas_word_cnt-1].cas_priority=
                  *((T_UINT16 *)(address+offset+length_count));
               length_count = (T_UINT16)(length_count + 2);
               break;
            case CAS_TYPE:
               Cas_messages[Cas_word_cnt-1].cas_type=
                  *((T_UINT16 *)(address+offset+length_count));
               length_count = (T_UINT16)(length_count + 2);
               break;
            case CAS_ID:
               Cas_messages[Cas_word_cnt-1].cas_id =
                  *((T_UINT16 *)(address+offset+length_count));
               length_count = (T_UINT16)(length_count + 2);
               break;
            default:
               break;
         }
      }
      offset=offset+FIFTY_BYTES;
   }

   /*hdudispfpdidata-CasExtract-DB-LLR-004*/
   Cas_cnt = ZERO;
   Cas_message_count = (T_UINT8)Cas_word_cnt;

   /*hdudispfpdidata-CasExtract-DB-LLR-005*/
   for(indx=0;indx<Cas_word_cnt;indx++)
   {

         for(indx1=0;indx1<MAX_CAS_TEXT_LEN;indx1++)
         {
            Cas_msg[Cas_cnt].acCASText[indx1] = Cas_messages[indx].cas_string[indx1];
         }
         Cas_msg[Cas_cnt].label=Cas_messages[indx].label;
         Cas_msg[Cas_cnt].type = FindCasType(Cas_messages[indx].cas_type);
         Cas_msg[Cas_cnt].priority =  (T_UINT8)Cas_messages[indx].cas_priority;
         Cas_msg[Cas_cnt].u8Start = (T_UINT8)Cas_messages[indx].cas_start_bit;
         Cas_msg[Cas_cnt].Id = (T_UINT8)Cas_messages[indx].cas_id;
         Cas_cnt++;

  }

}

/*
 *
 * Function                : CasLocationSett
 *
 * Description             : This function extracts CAS location settings
 *
 * Formal parameter(s)     : T_UINT8 *cas_sett_addr IN - address
 *
 * Return Value            : None
 *
 * Assumption              : None
 *
 */

void CasLocationSett(T_UINT8 *cas_sett_addr)
{
   T_UINT32 offset = 0;
   T_UINT16 var_j = 0;
   T_UINT16 length_count = 0;
   T_UINT16 enum_val = 0;

   /*hdudispfpdidata-CasLocationSett-DB-LLR-001*/
   if(NULL==cas_sett_addr)
   {
      return;
   }
   else
   {
      ;/*Do nothing*/
   }

   /*hdudispfpdidata-CasLocationSett-DB-LLR-002*/
   offset=0;
   length_count=0;
   Page_cas=0;

   /*hdudispfpdidata-CasLocationSett-DB-LLR-003*/
   while(length_count<CAS_LOC_MAX)
   {
      enum_val=*((T_UINT16 *)(cas_sett_addr+offset+length_count));
      length_count = (T_UINT16)(length_count + 2);
      if(MAX_16_BITS == enum_val)
      {
         break;
      }
      else
      {
         ;/*Do nothing*/
      }
      switch(enum_val)
      {
         case CAS_AXIS:
        	Caslocationset_parameters = TRUE;
            Page_cas=1;
            Page_settings.Cas_loc_settings.cas_axis.u16_x=
               *((T_UINT16 *)(cas_sett_addr+offset+length_count));
            length_count = (T_UINT16)(length_count + 2);
            Page_settings.Cas_loc_settings.cas_axis.u16_y=
               *((T_UINT16 *)(cas_sett_addr+offset+length_count));
            length_count = (T_UINT16)(length_count + 2);
            break;
         case CAS_NUM_ROWS:
            Page_settings.Cas_loc_settings.cas_num_rows=
             *((T_UINT16 *)(cas_sett_addr+offset+length_count));
            length_count = (T_UINT16)(length_count + 2);
            break;
         case CAS_NUM_COLUMN:
            Page_settings.Cas_loc_settings.cas_num_column=
               *((T_UINT16 *)(cas_sett_addr+offset+length_count));
            length_count = (T_UINT16)(length_count + 2);
            break;
         case CAS_ROW_HEIGHT:
            Page_settings.Cas_loc_settings.cas_row_height=
               *((T_UINT16 *)(cas_sett_addr+offset+length_count));
            length_count = (T_UINT16)(length_count + 2);
            break;
         case CAS_COL_WIDTH:
            Page_settings.Cas_loc_settings.cas_col_width=
               *((T_UINT16 *)(cas_sett_addr+offset+length_count));
            length_count = (T_UINT16)(length_count + 2);
            break;
         case CAS_FONT:
            Page_settings.Cas_loc_settings.cas_font=
               *((T_UINT16 *)(cas_sett_addr+offset+length_count));
            length_count = (T_UINT16)(length_count + 2);
            break;
         case CAS_ADV_FLASH_TIMER:
            Page_settings.Cas_loc_settings.cas_adv_flash_timer=
               *((T_UINT16 *)(cas_sett_addr+offset+length_count));
            length_count = (T_UINT16)(length_count + 2);
            break;
         case CAS_CAUT_FLASH_TIMER:
            Page_settings.Cas_loc_settings.cas_caut_flash_timer=
               *((T_UINT16 *)(cas_sett_addr+offset+length_count));
            length_count = (T_UINT16)(length_count + 2);
            break;
         case CAS_WARN_FLASH_TIMER:
            Page_settings.Cas_loc_settings.cas_warn_flash_timer=
               *((T_UINT16 *)(cas_sett_addr+offset+length_count));
            length_count = (T_UINT16)(length_count + 2);
            break;
         case CAS_REDX_TXT:
             var_j=0;
             while((*((T_UINT8 *)(cas_sett_addr+offset+length_count))!=0) &&
			                      (var_j<REDX_STRING_MAX))
             {
                Page_settings.Cas_loc_settings.cas_redx_txt[var_j]=
                   *((T_UINT8 *)(cas_sett_addr+offset+length_count));
                    if(('n' == Page_settings.Cas_loc_settings.cas_redx_txt[var_j])
                        &&( '\\' == Page_settings.Cas_loc_settings.cas_redx_txt[var_j-1] ))
                    {
                       Page_settings.Cas_loc_settings.cas_redx_txt[var_j-1] ='\n';
                       Cas_messages_setting.cas_redx_txt[var_j-1] =
                       Page_settings.Cas_loc_settings.cas_redx_txt[var_j-1];
                    }
                    else if(('r' == Page_settings.Cas_loc_settings.cas_redx_txt[var_j])
                         &&('\\' == Page_settings.Cas_loc_settings.cas_redx_txt[var_j-1]))
                    {
                       Page_settings.Cas_loc_settings.cas_redx_txt[var_j-1] ='\r';
                       Cas_messages_setting.cas_redx_txt[var_j-1] =
                       Page_settings.Cas_loc_settings.cas_redx_txt[var_j-1];
                    }
                    else
                    {
                        Cas_messages_setting.cas_redx_txt[var_j] =
                        Page_settings.Cas_loc_settings.cas_redx_txt[var_j];
                        var_j++;
                    }
               length_count++;
             }
             Page_settings.Cas_loc_settings.cas_redx_txt[var_j]=
              *((T_UINT8 *)(cas_sett_addr+offset+length_count));
             length_count++;
             Cas_messages_setting.cas_redx_txt[var_j] =
             Page_settings.Cas_loc_settings.cas_redx_txt[var_j];
            break;
         default:
            break;
      }
   }

   /*hdudispfpdidata-CasLocationSett-DB-LLR-004*/
   Cas_messages_setting.adv_flash_timer = (T_TIMER)
      ((Page_settings.Cas_loc_settings.cas_adv_flash_timer)*CAS_TICKS);
   Cas_messages_setting.caut_flash_timer = (T_TIMER)
      ((Page_settings.Cas_loc_settings.cas_caut_flash_timer)*CAS_TICKS);
   Cas_messages_setting.warn_flash_timer = (T_TIMER)
      ((Page_settings.Cas_loc_settings.cas_warn_flash_timer)*CAS_TICKS);
   Cas_messages_setting.column = (T_UINT8)Page_settings.Cas_loc_settings.cas_num_column;
   Cas_messages_setting.columnWidth =
   (T_UINT16)Page_settings.Cas_loc_settings.cas_col_width;
   Cas_messages_setting.row = (T_UINT8)Page_settings.Cas_loc_settings.cas_num_rows;
   Cas_messages_setting.rowHeight =
   (T_UINT16)Page_settings.Cas_loc_settings.cas_row_height;
   Cas_messages_setting.eFont = (T_ETXFONT)Page_settings.Cas_loc_settings.cas_font;
   Cas_messages_setting.sOrigin.u16X0 =
         ((T_INT16)Page_settings.Cas_loc_settings.cas_axis.u16_x);
   Cas_messages_setting.sOrigin.u16Y0 =
         ((T_INT16)Page_settings.Cas_loc_settings.cas_axis.u16_y);
}

/*
 *
 * Function                : AcdtExtract
 *
 * Description             : This function extracts acdt settings
 *
 * Formal parameter(s)     : T_UINT8 *address IN- acdt sector address
 *
 * Return Value            : None
 *
 * Assumption              : None
 */

void AcdtExtract(T_UINT8 *address)
{
   T_UINT32 u8_i = 0;
   T_UINT32 offset=0;
   T_UINT16 enum_val=0;
   T_UINT32 length_count=0;

   /*hdudispfpdidata-AcdtExtract-DB-LLR-001*/
   length_count=0;

   /*hdudispfpdidata-AcdtExtract-DB-LLR-002*/
   if(NULL==address)
   {
      return;
   }
   else
   {
      ;/*Do nothing*/
   }
   /*hdudispfpdidata-AcdtExtract-DB-LLR-003*/
   while(length_count<MAX_LEN_ACDT)
   {
      enum_val=*((T_UINT16 *)(address+offset+length_count));
      length_count=length_count+TWO;
      if(MAX_16_BITS == enum_val)
      {
         break;
      }
      else
      {
         ;
      }
      switch(enum_val)
      {
         case LABEL:
             Acdt_parameters = TRUE;
            Auto_cool_down_tmr.label=*((T_UINT8 *)(address+offset+length_count));
            length_count=length_count+1;

            for(u8_i=0;u8_i<PARA_MAX_SIZE;u8_i++)
            {
               if(Parameters[u8_i].label == Auto_cool_down_tmr.label)
               {
                  Auto_cool_down_tmr.acdt_reading = &Parameters[u8_i].reading;
               }
               else
               {
                  ;
               }
            }
            break;
        case ACDT_TIME:
            Auto_cool_down_tmr.acdt_time=*((T_UINT16 *)(address+offset+length_count));
            length_count=length_count+TWO;
            break;
        case WOG_LABEL:
            Auto_cool_down_tmr.wog_label=*((T_UINT8 *)(address+offset+length_count));
            length_count=length_count+1;
            for(u8_i=0;u8_i<PARA_MAX_SIZE;u8_i++)
            {
               if(Parameters[u8_i].label == Auto_cool_down_tmr.wog_label)
               {
                  Auto_cool_down_tmr.wog_data =(T_PARAM_READING *)&Parameters[u8_i].reading;
                  break;
               }
               else
               {
                  ;
               }
            }
            break;
        case WOG_START_BIT:
            Auto_cool_down_tmr.wog_start_bit=*((T_UINT16 *)(address+offset+length_count));
            length_count=length_count+TWO;
            break;
        case ACDT_ON_TRIGGER:
            Auto_cool_down_tmr.acdt_on_trigger=*((T_UINT8 *)(address+offset+length_count));
            length_count=length_count+1;
            Auto_cool_down_tmr.acdt_on_trigger_value=
               IeeeToFloat(*((T_UINT32 *)(address+offset+length_count)));
            length_count=length_count+FOUR;
            break;
        case ACDT_ON_COND:
            Auto_cool_down_tmr.acdt_on_cond=(T_UINT8)*((T_UINT32 *)(address+offset+length_count));
            length_count=length_count+1;
            Auto_cool_down_tmr.acdt_on_cond_value=
               IeeeToFloat(*((T_UINT32 *)(address+offset+length_count)));
            length_count=length_count+FOUR;
            break;
        case ACDT_OFF_CONDITION:
            Auto_cool_down_tmr.acdt_off_condition=*((T_UINT8 *)(address+offset+length_count));
            length_count=length_count+1;
            Auto_cool_down_tmr.acdt_off_condition_value=
               IeeeToFloat(*((T_UINT32 *)(address+offset+length_count)));
            length_count=length_count+FOUR;
            break;
        default:
           break;
     }
  }
}

/*
 *
 * Function                : ExceedExtract
 *
 * Description             : This function extracts exceedence settings
 *
 * Formal parameter(s)     : T_UINT8 *address IN - exceedence sector address
 *
 * Return Value            : None
 *
 * Assumption              : None
 */

void ExceedExtract(T_UINT8 *address)
{
   T_UINT32 offset=0;
   T_UINT16 var_i=0;
   T_UINT16 length_count=0;
   T_UINT16 enum_val=0;
   T_UINT16 u8_i=0;
   length_count=0;

   /*hdudispfpdidata-ExceedExtract-DB-LLR-001*/
   Exceed_cnt = 0;

   /*hdudispfpdidata-ExceedExtract-DB-LLR-002*/
   if(NULL==address)
   {
      return;
   }
   else
   {
      ;/*Do nothing*/
   }
   offset=0;
   /*hdudispfpdidata-ExceedExtract-DB-LLR-003*/
   for(var_i=0;var_i<MAX_NUM_EXCE;var_i++)
   {
      length_count=0;
      while(length_count<MAX_LEN_EXCE)
      {
         enum_val=*((T_UINT16 *)(address+offset+length_count));
         length_count=(T_UINT16)(length_count+TWO);
         if(MAX_16_BITS == enum_val)
         {
            break;
         }
         else
         {
            ;/*Do nothing*/
         }
         switch(enum_val)
         {
            case EXCEED_BIT:
               Exceed_data[Exceed_cnt].exceed_bit = *((T_UINT16 *)(address+offset+length_count));
               Exceed_data[Exceed_cnt].exceed_bit =
                               (T_UINT16)(Exceed_data[Exceed_cnt].exceed_bit - 10);
               length_count = (T_UINT16)(length_count+TWO);
               break;

            case LABEL:
               Exceed_data[Exceed_cnt].label=*((T_UINT8 *)(address+offset+length_count));
               length_count=(T_UINT16)(length_count+1);
               break;
            case SDI:
               Exceed_data[Exceed_cnt].sdi=*((T_UINT8 *)(address+offset+length_count));
               length_count=(T_UINT16)(length_count+1);
               for(u8_i=0;u8_i<PARA_MAX_SIZE;u8_i++)
               {
                  if((Parameters[u8_i].label == Exceed_data[Exceed_cnt].label) &&
                          (Parameters[u8_i].sdi == Exceed_data[Exceed_cnt].sdi))
                  {
                     Exceed_data[Exceed_cnt].exceed_reading =
                        (T_PARAM_READING *)&Parameters[u8_i].reading;
                  }
                  else
                  {
                     ;
                  }
               }
               break;

            case EXCEED_AXIS:
               Exceed_data[Exceed_cnt].exceed_axis.u16_x =
                                    *((T_UINT16 *)(address+offset+length_count));
               length_count = (T_UINT16)(length_count+TWO);
               Exceed_data[Exceed_cnt].exceed_axis.u16_y =
                                    *((T_UINT16 *)(address+offset+length_count));
               length_count = (T_UINT16)(length_count + TWO);
               break;

            case EXCEED_FONT:
               Exceed_data[Exceed_cnt].exceed_font = *((T_UINT16 *)(address+offset+length_count));
               length_count= (T_UINT16)(length_count + TWO);
               Exceed_cnt++;
               break;

            default:
               break;
         }
      }
      offset=offset+MAX_LEN_EXCE;
   }
}

/*
 *
 * Function                : A429Extract
 *
 * Description             : This function extracts A429  settings
 *
 * Formal parameter(s)     : T_UINT8 *address IN - a429 sector address
 *
 * Return Value            : None
 *
 * Assumption              : None
 *
 */

void A429Extract(T_UINT8 *address)
{
   T_UINT32 offset = 0;
   T_UINT16 var_i = 0;
   T_UINT16 length_count = 0;
   T_UINT16 enum_val = 0;

   /*hdudispfpdidata-A429Extract-DB-LLR-001*/
   if(NULL==address)
   {
      return;
   }
   else
   {
      ;/*Do nothing*/
   }
   /*hdudispfpdidata-A429Extract-DB-LLR-002*/
   offset=0;
   A429_settings_cnt=0;

   /*hdudispfpdidata-A429Extract-DB-LLR-003*/
   for(var_i=0;var_i<MAX_NUM_A429;var_i++)
   {
      length_count=0;

      while(length_count<MAX_LEN_A429)
      {
         enum_val=*((T_UINT16 *)(address+offset+length_count));
         length_count=(T_UINT16)(length_count+TWO);
         if(MAX_16_BITS == enum_val)
         {
              break;
         }
         else
         {
            ;/*Do nothing*/
         }
         switch(enum_val)
         {
            case A429_PORT:
               A429_settings_cnt++;
               A429_cfg_data[A429_settings_cnt-1].A429_port=
                  *((T_UINT8 *)(address+offset+length_count));
               length_count=(T_UINT16)(length_count+1);
               break;
            case LABEL:
               A429_cfg_data[A429_settings_cnt-1].A429_label=
                  *((T_UINT8 *)(address+offset+length_count));
               length_count=(T_UINT16)(length_count+1);
               if( ONE == Config_data.scu_enable)
               {
            	   if(LABEL_0250 == A429_cfg_data[A429_settings_cnt-1].A429_label)
            	   {
            		   Scu_label_flag = Scu_label_flag | ONE;
            	   }
            	   else
            	   {
            		   ;
            	   }
            	   if(LABEL_0272 == A429_cfg_data[A429_settings_cnt-1].A429_label)
            	   {
            		   Scu_label_flag = Scu_label_flag | TWO;
            	   }
            	   else
            	   {
            		   ;
            	   }
            	   if(LABEL_0247 == A429_cfg_data[A429_settings_cnt-1].A429_label)
            	   {
            		   Scu_label_flag = Scu_label_flag | FOUR;
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
               break;
            case SDI:
               A429_cfg_data[A429_settings_cnt-1].A429_sdi=
                   *((T_UINT8 *)(address+offset+length_count));
               length_count=(T_UINT16)(length_count+1);
               break;
            case A429_TYPE:
               A429_cfg_data[A429_settings_cnt-1].A429_type=
                  *((T_UINT16 *)(address+offset+length_count));
               length_count=(T_UINT16)(length_count+TWO);
               break;
            case A429_BNR_BITS:
               A429_cfg_data[A429_settings_cnt-1].label_data.A429_bnr_data.A429_bnr_bits=
                  *((T_UINT32 *)(address+offset+length_count));
               length_count=(T_UINT16)(length_count+FOUR);
               break;
            case A429_BNR_START_BIT:
                A429_cfg_data[A429_settings_cnt-1].label_data.A429_bnr_data.A429_bnr_start_bit=
                  *((T_UINT32 *)(address+offset+length_count));
                length_count=(T_UINT16)(length_count+FOUR);
                break;
            case A429_BNR_MAX:
               A429_cfg_data[A429_settings_cnt-1].label_data.A429_bnr_data.A429_bnr_max=
                 (T_FLOAT)IeeeToFloat( *((T_UINT32 *)(address+offset+length_count)));
               length_count=(T_UINT16)(length_count+FOUR);
               break;
            case A429_BNR_MIN:
               A429_cfg_data[A429_settings_cnt-1].label_data.A429_bnr_data.A429_bnr_min=
                     (T_FLOAT)IeeeToFloat(*((T_UINT32 *)(address+offset+length_count)));
               length_count=(T_UINT16)(length_count+FOUR);
               break;
            case A429_BNR_OFFSET:
               A429_cfg_data[A429_settings_cnt-1].label_data.A429_bnr_data.A429_bnr_offset=
                  *((T_UINT32 *)(address+offset+length_count));
               length_count=(T_UINT16)(length_count+FOUR);
               break;
            case A429_BNR_TIMEOUT:
               A429_cfg_data[A429_settings_cnt-1].label_data.A429_bnr_data.A429_bnr_timeout=
                  *((T_UINT32 *)(address+offset+length_count));
               length_count=(T_UINT16)(length_count+FOUR);
               break;
            /* Updated for PR 100073 */
            case A429_BNR_SCALE_FACTOR:
               A429_cfg_data[A429_settings_cnt-1].label_data.A429_bnr_data.A429_bnr_scale_fact =
                   IeeeToFloat(*((T_UINT32 *)(address+offset+length_count)));
               length_count=(T_UINT16)(length_count+FOUR);
               break;
            case A429_DDW_TIMEOUT:
               A429_cfg_data[A429_settings_cnt-1].label_data.A429_ddw_timeout=
                  *((T_UINT32 *)(address+offset+length_count));
               length_count=(T_UINT16)(length_count+FOUR);
               break;
            default:
               break;
         }
      }
      offset=offset+MAX_LEN_A429;
   }
}


/* Updated per ECM 38, 39, 41 */
/*
 *
 * Function                : ElogTrigExtract
 *
 * Description             : This function extracts ExLog Trigger settings
 *
 * Formal parameter(s)     : T_UINT8 *address IN - a429 sector address
 *
 * Return Value            : None
 *
 * Assumption              : None
 *
 */

void ElogTrigExtract(T_UINT8 *address)
{
   T_UINT32 u8_i = 0;
   T_UINT32 offset=0;
   T_UINT16 enum_val=0;
   T_UINT32 length_count=0;
   T_UINT16 var_i=0;

   length_count=0;

   /*hdudispfpdidata-ElogTrigExtract-DB-LLR-001*/
   for(var_i=0;var_i<MAX_ELOG_EVENT;var_i++)
   {
       Cond_cnt[var_i] = 0;
   }

   /*hdudispfpdidata-ElogTrigExtract-DB-LLR-001*/
   if(NULL==address)
   {
      return;
   }
   else
   {
      ;/*Do nothing*/
   }

   for(var_i=0;var_i<MAX_ELOG_EVENT;var_i++)
   {
       length_count=0;
       while(length_count<MAX_LEN_ELOG_TRIG)
       {
           /*hdudispfpdidata-ElogTrigExtract-DB-LLR-002*/
          enum_val=*((T_UINT16 *)(address+offset+length_count));
          length_count=length_count+TWO;
          if(MAX_16_BITS == enum_val)
          {
             break;
          }
          else
          {
             ;
          }

          switch(enum_val)
          {
             /*hdudispfpdidata-ElogTrigExtract-DB-LLR-003*/
             case ELOG_TRIG_LABEL:
                 Elog_trig_bool = TRUE;              /* Boolean to check for ELOG_TRIG parameters*/
                for (u8_i = 0; u8_i<MAX_ELOG_TRIG_COND; u8_i++)
                {
                   Elog_trig[var_i].elog_trig_label[u8_i]=
                           *((T_UINT8 *)(address+offset+length_count));
                   length_count=length_count+1;
                if(Elog_trig[var_i].elog_trig_label[u8_i] != NULL_LABEL)
                {
                   Cond_cnt[var_i]++;
                }
                else
                {
                   ;/*Do nothing*/
                }
                }
                break;

             case ELOG_TRIG_SDI:
                /* hdudispfpdidata-ElogTrigExtract-DB-LLR-008 */
                for (u8_i = 0; u8_i<MAX_ELOG_TRIG_COND; u8_i++)
                {
                 Elog_trig[var_i].elog_trig_sdi[u8_i]=*((T_UINT8 *)(address+offset+length_count));
                 length_count=length_count+1;
                }
                break;

            /*hdudispfpdidata-ElogTrigExtract-DB-LLR-004*/
            case ELOG_TRIG_STRT_VAL:
                for (u8_i = 0; u8_i<MAX_ELOG_TRIG_COND; u8_i++)
                {
                   Elog_trig[var_i].elog_trig_start_type[u8_i]=
                           *((T_UINT8 *)(address+offset+length_count));
                   length_count=length_count+1;
                   Elog_trig[var_i].elog_trig_start_val[u8_i]=
                                       IeeeToFloat(*((T_UINT32 *)(address+offset+length_count)));
                   length_count=length_count+FOUR;
                }
                break;

            /*hdudispfpdidata-ElogTrigExtract-DB-LLR-005*/
            case ELOG_TRIG_CROSS_VAL:
                for (u8_i = 0; u8_i<MAX_ELOG_TRIG_COND; u8_i++)
                {
                   Elog_trig[var_i].elog_trig_cross_type[u8_i]=
                           *((T_UINT8 *)(address+offset+length_count));
                   length_count=length_count+1;
                   Elog_trig[var_i].elog_trig_cross_val[u8_i]=
                                          IeeeToFloat(*((T_UINT32 *)(address+offset+length_count)));
                   length_count=length_count+FOUR;
                }
                break;

            /*hdudispfpdidata-ElogTrigExtract-DB-LLR-006*/
            case ELOG_TRIG_TIME:
                for (u8_i = 0; u8_i<MAX_ELOG_TRIG_COND; u8_i++)
                {
                   Elog_trig[var_i].elog_trig_time[u8_i]=
                           *((T_UINT16 *)(address+offset+length_count));
                   length_count=length_count+TWO;
                }
                break;

            /*hdudispfpdidata-ElogTrigExtract-DB-LLR-007*/
            default:
               break;
         }
      }
      offset=offset+MAX_LEN_ELOG_TRIG;
   }
}

/*
 *
 * Function                : ElogParamExtract
 *
 * Description             : This function extracts Exlog Event settings
 *
 * Formal parameter(s)     : T_UINT8 *address IN - a429 sector address
 *
 * Return Value            : None
 *
 * Assumption              : None
 *
 */
void ElogParamExtract(T_UINT8 *address)
{
   T_UINT32 offset=0;
   T_UINT16 var_i=0;
   T_UINT16 var_j = 0;
   T_UINT16 length_count=0;
   T_UINT16 enum_val=0;
   T_UINT16 u8_i=0;
   T_UINT8 character_var = 0;

   length_count=0;
   offset=0;

   /*hdudispfpdidata-ElogParamExtract-DB-LLR-001*/
   Exceed_cnt = 0;

   if(NULL==address)
   {
      return;
   }
   else
   {
      ;/*Do nothing*/
   }

   for(var_i=0;var_i<MAX_ELOG_EVENT;var_i++)
   {
      length_count=0;
      while(length_count<MAX_LEN_ELOG_EVENT)
      {
         /*hdudispfpdidata-ElogParamExtract-DB-LLR-002*/
         enum_val=*((T_UINT16 *)(address+offset+length_count));
         length_count=(T_UINT16)(length_count+TWO);
         if(MAX_16_BITS == enum_val)
         {
            break;
         }
         else
         {
            ;/*Do nothing*/
         }
         switch(enum_val)
         {
            /*hdudispfpdidata-ElogParamExtract-DB-LLR-003*/
            case ELOG_LABEL:
               Elog_param = TRUE;
               Elog_label[var_i].elog_label = *((T_UINT8 *)(address+offset+length_count));
               length_count = (T_UINT16)(length_count+1);
               break;

            case ELOG_SDI:
               Elog_label[var_i].elog_sdi = *((T_UINT8 *)(address+offset+length_count));
               length_count = (T_UINT16)(length_count+1);
               break;

            /*hdudispfpdidata-ElogParamExtract-DB-LLR-004*/
            case ELOG_BIT_LABEL:
               for(u8_i=0;u8_i<MAX_ELOG_PARAM;u8_i++)
               {
                  Elog_label[var_i].elog_bit_label[u8_i] =
                                            *((T_UINT8 *)(address+offset+length_count));
                  length_count=(T_UINT16)(length_count+1);
               }
               break;

            /*hdudispfpdidata-ElogParamExtract-DB-LLR-005*/
            case ELOG_BIT_PARAM:
                for(u8_i=0;u8_i<MAX_ELOG_PARAM;u8_i++)
                {
                   for(var_j = 0;var_j<MAX_ELOG_PARAM_SIZE + 2;var_j++)
                   {
                       character_var = *((T_UINT8 *)(address+offset+length_count));
                       length_count=(T_UINT16)(length_count+1);

                       if (NULL_LABEL == character_var)
                       {
                           character_var = *((T_UINT8 *)(address+offset+length_count));
                           length_count=(T_UINT16)(length_count+1);
                           if (NULL_LABEL == character_var)
                           {
                                 break;
                           }
                           else
                           {
                               Elog_label[var_i].elog_bit_param[u8_i][var_j] = NULL_LABEL;
                               Elog_label[var_i].elog_bit_param[u8_i][var_j + 1] = character_var;
                               ++var_j;
                           }
                       }
                       else
                       {
                           Elog_label[var_i].elog_bit_param[u8_i][var_j] = character_var;
                       }
                   }
                }
               break;

            /*hdudispfpdidata-ElogParamExtract-DB-LLR-006*/
            default:
               break;
         }
      }
      /*hdudispfpdidata-ElogParamExtract-DB-LLR-007*/
      offset=offset+MAX_LEN_ELOG_EVENT;
   }
}

/*
 *
 * Function                : PdiPageDataInit
 *
 * Description             : This function extracts all page data required from the pdi
 *
 * Formal parameter(s)     : T_UINT8 page_num - IN page number
 *
 * Return Value            : None
 *
 * Assumption              : None
 *
 */

void PdiPageDataInit(T_UINT8 page_num)
{
   /*hdudispfpdidata-PdiPageDataInit-DB-LLR-001*/
   PageExtract((T_UINT8 *)(PAGE_NUM_BASE_ADDR+(page_num*(T_UINT32)PAGE_NUM_BASE_OFFSET)));
   /*hdudispfpdidata-PdiPageDataInit-DB-LLR-002*/
   ForegroundExtract((T_UINT8 *)(PAGE_NUM_BASE_ADDR+(page_num*(T_UINT32)PAGE_NUM_BASE_OFFSET) +
         (T_UINT32)FRGRND_ADDR_60));
   /*hdudispfpdidata-PdiPageDataInit-DB-LLR-003*/
   CasLocationSett((T_UINT8 *)( (page_num* (T_UINT32)CAS_LOC_MAX)+CAS_SETTING_ADDRESS) );
   /*hdudispfpdidata-PdiPageDataInit-DB-LLR-004*/
   ExceedExtract((T_UINT8 *)(PAGE_EXCEEDANCE_ADDR+(Page_num*MAX_NUM_EXCE*MAX_LEN_EXCE)));
   /* Function to check PDI parameters */
   /*hdudispfpdidata-PdiPageDataInit-DB-LLR-005*/
   PdiDataCheck();
}

/*
 *
 * Function                : PdiDataInit
 *
 * Description             : This function extracts all the data required from the pdi
 *
 * Formal parameter(s)     : None
 *
 * Return Value            : None
 *
 * Assumption              : None
 *
 */

void PdiDataInit(void)
{
   /*Updated per ECM 38,39, 41*/
   /* hdudispfpdidata-PdiDataInit-DB-LLR-005 */
   ElogTrigExtract((T_UINT8*)ELOG_TRIG_ADDRESS);

   /* hdudispfpdidata-PdiDataInit-DB-LLR-006 */
   ElogParamExtract((T_UINT8*)ELOG_PARAM_ADDRESS);

   /* hdudispfpdidata-PdiDataInit-DB-LLR-002 */
   AcdtExtract((T_UINT8 *)ACDT_ADDRESS);
   /* Updated as per PR 100073 */
   /* hdudispfpdidata-PdiDataInit-DB-LLR-004 */
   NumberOfPages();
}
