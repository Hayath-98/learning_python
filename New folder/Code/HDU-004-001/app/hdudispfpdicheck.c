/*
 ******************************************************************************
 * License Information  :  Howell Instruments, Inc.                           *
 *                         "Licensed Software" and "All rights reserved".     *
 ******************************************************************************
 *  File                : hdudispfpdicheck.c
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
 *      1.1          Gururaj C       21-Jun-2020             100259
 *      1.2          Dhanalakshmi    29-Jun-2020             100259
 *      1.3          Rona B S        24-Jul-2020             100259
 *      1.4          Dhanalakshmi    05-Aug-2020             100270
 *      1.5          Dhanalakshmi    12-Sep-2020             100276
 *      1.6          Dhanalakshmi    15-Sep-2020             100276
 *      1.7          Dhanalakshmi    28-Sep-2020             100284
 *      1.8          Dhanalakshmi    30-Sep-2020             100284
 *      1.9          Dhanalakshmi    05-Oct-2020             100288
 *      1.10         Dhanalakshmi    09-Oct-2020             100288
 *      1.11         Dhanalakshmi    21-Oct-2020             100314
 *      1.12         Dhanalakshmi     20-Mar-2021             100331
 *      1.13         Dhanalakshmi     20-Mar-2021             100331
 *      1.14         Dhanalakshmi     03-Apr-2021             100330
 *      1.15         Dhanalakshmi     16-Apr-2021             100339
 *      1.16         Dhanalakshmi     24-Apr-2021             1003xx
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
#include "hdudispfpanel.h"   /* Contains functions prototypes of panel.*/
#include "hdulibbasictypes.h" /* contains Define standard types  */
#include "hdudispfrterror.h"  /* Contains Error Types  */
#include "hdudispflookup.h" /* contains prototype of lookup  Table*/
#include "hdudispffonts.h"  /* contains prototype of Fonts */

T_BOOL Global_check = FALSE;
T_UINT16 Pdi_error_count = 0;   /* Stores error messages */
T_UINT8 Label_size = 4;        /* Label size */

#define M_FOURTY_FIVE 45
#define MAX_CAS_FLASH_TIMER 999
#define MAX_CAS_FLASH_TIMER_9999 9999

/*
 * Array which stores 5 error messages
 * as string of byte 20 characters each
 */
T_CHAR Error_msg_string[5][40] = {"0"};
T_BOOL Page_check[20] = {FALSE};
T_BOOL Global_parameter_error = FALSE;
T_BOOL Page_parameter_error[20] = {FALSE};
T_UINT8 Index_value =ZERO;
T_UINT32 Timer_axis_error = ZERO;
T_UINT32 Acdt_axis_error = ZERO;
T_UINT32 Cas_error = ZERO;
T_UINT32 Exceed_error = FALSE;
T_UINT32 Ex_timer_error = FALSE;
static T_BOOL CheckFont(T_UINT16 font);
static T_BOOL CheckMinMax(T_INT32 param, T_INT32 min, T_INT32 max);
static T_BOOL CheckAxisMinMax(T_INT32 param, T_INT32 min, T_INT32 max_value1, T_INT32 max_value2);
static T_BOOL CheckAxisMinMax2 (T_INT32 param, T_INT32 min1,T_INT32 min2,T_INT32 max_value1,\
	   T_INT32 max_value2);
static T_BOOL CheckDuResolution();
static T_BOOL CheckFloatMinMax(T_FLOAT param, T_FLOAT min, T_FLOAT max);
static T_BOOL CheckString(T_UINT8 *str, T_UINT16 length);
static void BuildErrorMsg(const T_CHAR str1[],const T_CHAR str2[],\
                          const T_CHAR str3[], T_CHAR* str);
static T_UINT32 OnlyOneBitSetToOne(T_UINT32 checkBit);
static T_BOOL CheckColor(T_UINT16 color);
static T_BOOL CheckCasType(T_UINT16 type);
static void CheckConfig();
static void CheckCASParameters();
static void CheckA429Parameters();
static void CheckElogTrig();
static void CheckElogParam();
static void CheckAcdtParams();
static void CheckPageSettings();
static void CheckForegroundParameters();
static void CheckBarGraph();
static void CheckRoundDial();
static void CheckNumberBox();
static void CheckCarrotGraph();
static void CheckCasLocationSett();
static void CheckExceedParam();
static void CheckTextBox();
static void CheckText();
static void CheckPoly();
static T_BOOL CheckVerPos(T_FLOAT pos);
static void CheckExceedTimerSettings();

/*
 *
 * Function                : CheckFont
 *
 * Description             : This function checks if font is in range
 *
 * Formal parameter(s)     : T_UINT16 font - IN font sent from PDI
 *
 * Return Value            : T_BOOL - status
 *
 * Assumption              : None
 *
 */

static T_BOOL CheckFont(T_UINT16 font)
{
	  T_BOOL ret_val=FALSE;
	  /*hdudispfpdicheck-CheckFont-DB-LLR-001*/
	   switch(font)
	   {
	   case E_TINY_FONT:
		   ret_val = TRUE;
		   break;

	   case E_SMALL_FONT:
		   ret_val = TRUE;
		   break;

	   case E_NORMAL_FONT:
		   ret_val = TRUE;
		   break;

	   case E_LARGE_FONT:
		   ret_val = TRUE;
		   break;

	   case E_BEZEL_FONT:
		   ret_val = TRUE;
		   break;
       /*hdudispfpdicheck-CheckFont-DB-LLR-002*/
	   default:
		   ret_val = FALSE;
		   break;
	   }
	   return ret_val;

}

/*
 *
 * Function                : CheckDecimalFormat
 *
 * Description             : This function checks if decimal format is in range
 *
 * Formal parameter(s)     : T_UINT16 format - IN decimal format from PDI
 *
 * Return Value            : T_BOOL - status
 *
 * Assumption              : None
 *
 */

T_BOOL CheckDecimalFormat(T_FORMAT format)
{
	  T_BOOL ret_val=FALSE;
	   switch(format)
	   {
	   /*hdudispfpdicheck-CheckDecimalFormat-DB-LLR-001*/
	   case NUM_ONED:
		   ret_val = TRUE;
		   break;

	   case NUM_TWOD:
		   ret_val = TRUE;
		   break;

	   case NUM_THREED:
		   ret_val = TRUE;
		   break;

	   case NUM_FOURD:
		   ret_val = TRUE;
		   break;

	   case NUM_FIVED:
		   ret_val = TRUE;
		   break;

	   case NUM_SIXD:
		   ret_val = TRUE;
		   break;

       /*hdudispfpdicheck-CheckDecimalFormat-DB-LLR-002*/
	   default:
		   ret_val = FALSE;
		   break;
	   }

	   return ret_val;

}
/*
 *
 * Function                : CalStringParam
 *
 * Description             : This function checks number of newline , return carriage.
 *
 * Formal parameter(s)     : T_UINT8 *string_txt - IN Input String
 *                           T_UINT16 *max_width - OUT Maximum Width per line
 *							 T_UINT16 *line_count - OUT Number of lines
 *
 * Return Value            : T_BOOL - status
 *
 * Assumption              : None
 *
 */

T_BOOL CalStringParam( T_UINT8 *string_txt,T_UINT16 *max_width,T_UINT16 *line_count)
{
    T_UINT16  temp_width =0;
    T_UINT16 length_text =0;
    T_BOOL fail_indication = FALSE;
	T_UINT8 index_nxtline = 0;


    /*hdudispfpdicheck-CalStringParam-DB-LLR-001*/
	*max_width = 0;
    *line_count = 0;
    length_text = StrLen((T_CHAR*)string_txt);

    /*hdudispfpdicheck-CalStringParam-DB-LLR-002*/
    for ( index_nxtline = 0; index_nxtline < length_text;index_nxtline++)
        {
            temp_width = (T_UINT16)(temp_width+ONE);
            if ((('\r' == string_txt[index_nxtline]) && (index_nxtline+1 < length_text))
				&& ('\n' == string_txt[index_nxtline+1]))
            {
                *line_count = (T_UINT16)(*line_count+1);
                if ( *max_width < (temp_width -1) )
                {
                   *max_width = (T_UINT16)(temp_width - ONE);
                }
                temp_width = 0;
                fail_indication = FALSE;
                index_nxtline = (T_UINT8)(index_nxtline + ONE);
            }
            else if('\r' == string_txt[index_nxtline] && index_nxtline+1 < length_text
					&& '\n' != string_txt[index_nxtline+1])
            {
                 fail_indication = TRUE;
                 break;
            }
            else if (index_nxtline ==(length_text -1))
                       {
                           *line_count = (T_UINT16)(*line_count+1);
                           if ( *max_width < temp_width )
                           {
                              *max_width = temp_width;
                           }
                           temp_width = 0;
                           fail_indication = FALSE;
                       }
            else
            {
                 fail_indication = TRUE;
            }
        }
    return fail_indication;
}
/*
 * Function                : CheckMinMax
 *
 * Description             : This function checks if a parameter is within range
 *
 * Formal parameter(s)     : T_INT32 param   - parameter
 *                           T_INT32 min     - minimum value
 *                           T_INT32 max     - maximum value
 *
 * Return Value            : T_BOOL
 *
 * Assumption              : None
 *
 */
static T_BOOL CheckMinMax(T_INT32 param, T_INT32 min, T_INT32 max)
{
    /*hdudispfpdicheck-CheckMinMax-DB-LLR-001*/
    if (param < min || param > max)
    {
        return FALSE;
    }
    /*hdudispfpdicheck-CheckMinMax-DB-LLR-002*/
    else
    {
    return TRUE;
    }
}

/*
 * Function                : CheckFloatMinMax
 *
 * Description             : This function checks if a parameter is within range
 *
 * Formal parameter(s)     : T_FLOAT param   - parameter
 *                           T_FLOAT min     - minimum value
 *                           T_FLOAT max     - maximum value
 *
 * Return Value            : T_BOOL
 *
 * Assumption              : None
 *
 */
static T_BOOL CheckFloatMinMax(T_FLOAT param, T_FLOAT min, T_FLOAT max)
{
    /*hdudispfpdicheck-CheckFloatMinMax-DB-LLR-001*/
    if (param < min || param > max)
    {
        return FALSE;
    }
    else
    {
    return TRUE;
    }
}

/*
 * Function                : CheckAxisMinMax
 *
 * Description             : This function checks if a parameter is within range
 * 							 based on orientation.Minimum value is same for
 * 							 any orientation
 *
 * Formal parameter(s)     : T_INT32 param   - parameter
 *                           T_INT32 min     - minimum value
 *                           T_INT32 max_value1  - maximum value
 *                           T_INT32 max_value2  - maximum value
 *
 * Return Value            : T_BOOL
 *
 * Assumption              : None
 *
 */

static T_BOOL CheckAxisMinMax(T_INT32 param, T_INT32 min, T_INT32 max_value1, T_INT32 max_value2)
{
	if (E_PORTRAIT == E_orientation)
	{
		/*hdudispfpdicheck-CheckAxisMinMax-DB-LLR-001*/
		if (param < min || param > max_value1)
		{
			return FALSE;
		}
		else
		{
			return TRUE;
		}
	}
	else
	{
		/*hdudispfpdicheck-CheckAxisMinMax-DB-LLR-002*/
		if (param < min || param > max_value2)
		{
			return FALSE;
		}
		else
		{
			return TRUE;
		}
	}

}

/*
 * Function                : CheckAxisMinMax2
 *
 * Description             : This function checks if a parameter is within range
 * 							 based on orientation .Minimum value differs for
 * 							 orientation
 *
 * Formal parameter(s)     : T_INT32 param   - parameter
 *                           T_INT32 min1     - minimum value
 *                           T_INT32 min2     - minimum value
 *                           T_INT32 max_value1  - maximum value
 *                           T_INT32 max_value2  - maximum value
 *
 * Return Value            : T_BOOL
 *
 * Assumption              : None
 *
 */


static T_BOOL CheckAxisMinMax2 (T_INT32 param, T_INT32 min1,T_INT32 min2,
                                T_INT32 max_value1, T_INT32 max_value2)
{
	if (E_PORTRAIT == E_orientation)
	{
		/*hdudispfpdicheck-CheckAxisMinMax2-DB-LLR-001*/
		if (param < min1|| param > max_value1)
		{
			return FALSE;
		}
		else
		{
			return TRUE;
		}
	}
	else
	{
		/*hdudispfpdicheck-CheckAxisMinMax2-DB-LLR-002*/
		if (param < min2 || param > max_value2)
		{
			return FALSE;
		}
		else
		{
			return TRUE;
		}
	}

}


/*
 *
 * Function                : FindTotalDigits
 *
 * Description             : This function calculates the total
 *                           number of digits used to display number.
 *
 * Formal parameter(s)     : T_UINT32 format -IN Format
 *
 * Return Value            : T_UINT16 - returns total digits.
 *
 * Assumption              : None
 *
 */

T_UINT16 FindTotalDigits(T_UINT32 format)
{
	T_UINT16 total_digits = ZERO;/* Stores total digits to display number*/

   /*hdudispfpdicheck-FindTotalDigits-DB-LLR-001*/
   if(ZERO != (format & NUM_ONEW))
   {
	   total_digits = (T_UINT16)(total_digits + 1);
   }
   else
   {
      ; /* Do nothing */
   }

   if(ZERO != (format & NUM_TWOW))
   {
	   total_digits=(T_UINT16)(total_digits + 2);
   }
   else
   {
      ; /* Do nothing */
   }


   if(ZERO != (format & NUM_THREEW))
   {
	   total_digits=(T_UINT16)(total_digits + 3);
   }
   else
   {
      ; /* Do nothing */
   }

   if(ZERO != (format & NUM_FOURW))
   {
	   total_digits=(T_UINT16)(total_digits + 4);
   }
   else
   {
      ; /* Do nothing */
   }

   /*hdudispfpdicheck-FindTotalDigits-DB-LLR-002*/
   if(ZERO != (format & NUM_FIVEW))
   {
	   total_digits=(T_UINT16)(total_digits + 5);
   }
   else
   {
      ; /* Do nothing */
   }

   if(ZERO != (format & NUM_SIXW))
   {
	   total_digits=(T_UINT16)(total_digits + 6);
   }
   else
   {
      ; /* Do nothing */
   }
   if(ZERO != (format & NUM_SEVENW))
   {
	   total_digits=(T_UINT16)(total_digits + 7);
   }
   else
   {
      ; /* Do nothing */
   }
   if(ZERO != (format & NUM_EIGHTW))
   {
	   total_digits=(T_UINT16)(total_digits + 8);
   }
   else
   {
      ; /* Do nothing */
   }
   /*hdudispfpdicheck-FindTotalDigits-DB-LLR-005*/
   return total_digits;
}



/*
 * Function                : CheckDuResolution
 *
 * Description             : This function checks the resolution of DU
 *
 * Formal parameter(s)     : None
 *
 * Return Value            : T_BOOL
 *
 * Assumption              : None
 *
 */

static T_BOOL CheckDuResolution(void)
{
	 T_BOOL ret_val=FALSE;

	 /*hdudispfpdicheck-CheckDuResolution-DB-LLR-001*/
     if (E_7_INCH == Display_size)
     {
	 if (PANEL_HEIGHT == Config_data.du_resolution.u16_x && \
	     PANEL_WIDTH == Config_data.du_resolution.u16_y)
	 {
	    ret_val = FALSE ;
	 }
	 else
	 {
	    ret_val = TRUE;
	 }
     }
     else if (E_10_INCH == Display_size)
     {
	 if (PANEL_HEIGHT == Config_data.du_resolution.u16_x && \
	     PANEL_WIDTH == Config_data.du_resolution.u16_y)
	 {
	    ret_val = FALSE ;
	 }
	 else
	 {
	    ret_val = TRUE;
	 }
     }
     else
     {
    	 ;
     }
	 return ret_val;
}
/*
 * Function                : CheckString
 *
 * Description             : This function checks string for max length
 *
 * Formal parameter(s)     : T_UINT8 *str   - String that is to be checked for length
 *                           T_UNIT16 length - Max length of string.
 *
 * Return Value            : None
 *
 * Assumption              : None
 *
 */
static T_BOOL CheckString(T_UINT8 *str, T_UINT16 length)
{
    T_UINT32 valid = FALSE;
    T_UINT16 i_cntr = ZERO;

    /*hdudispfpdicheck-CheckString-DB-LLR-001*/
    for (i_cntr = ZERO; i_cntr <= length; i_cntr++)
    {
        if ('\0' == str[i_cntr])
        {
        	/* valid is set to TRUE if NULL character is found within Maximum length */
            valid = TRUE;
            break;
        }
        else
        {
        	/* To raise error if string is configured with more than maximum characters */
        	valid = FALSE;
        }
    }
    /*hdudispfpdicheck-CheckString-DB-LLR-002*/
    return valid;
}

/*
 *
 * Function                : BuildErrorMsg
 *
 * Description             : This function frames the error message that is to
 *                           be displayed on screen
 *
 * Formal parameter(s)     : None
 *
 * Return Value            : None
 *
 * Assumption              : None
 *
 */

static void BuildErrorMsg(const T_CHAR str1[], const T_CHAR str2[],
                          const T_CHAR str3[], T_CHAR* str)
{
    T_UINT16 var_i=ZERO;        /* Loop variable for concatenating strings */
    T_UINT8 loop = ZERO;        /* Variable to iterate on concatenated string */

    /*hdudispfpdicheck-BuildErrorMsg-DB-LLR-001*/
    while(str1[var_i] != '\0')
    {
        str[loop++] = str1[var_i];
        var_i++;
    }
    /*hdudispfpdicheck-BuildErrorMsg-DB-LLR-002*/
    str[loop++] = ' ';

    var_i = ZERO;

    while(str2[var_i] != '\0')
    {
        str[loop++] = str2[var_i];
        var_i++;
    }
    /*hdudispfpdicheck-BuildErrorMsg-DB-LLR-003*/
    str[loop++] = ' ';

    var_i = ZERO;
    while(str3[var_i] != '\0')
    {
        str[loop++] = str3[var_i];
        var_i++;
    }
}

/*
 *
 * Function                : OctToStringTrim
 *
 * Description             : This function changes data type of label from OCTAL to CHAR array
 *
 * Formal parameter(s)     : T_UINT8 label - label value that needs to be converted into string
 *							 T_UINT8 label_size - Size of the value to be converted
 *							 T_CHAR *str - Converted Value.
 *
 * Return Value            : None
 *
 * Assumption              : None
 *
 */
void OctToStringTrim(T_UINT8 label,T_UINT8 label_size, T_CHAR *str)
{
    T_UINT8 var_i=ZERO;                          /* Loop variable */
    T_UINT8 oct_val[4]={ZERO};
    T_UINT8 temp_label=ZERO;
    T_UINT8 loop_index= ZERO;

    loop_index = (T_UINT8)(label_size-ONE);

   /* hdudispfpdicheck-OctToStringTrim-DB-LLR-001 */
    temp_label = label;
    while(temp_label != ZERO)
    {
    	oct_val[loop_index] = temp_label % 8;
    	temp_label = temp_label /8;
    	loop_index--;
    }


    for (var_i = 0; var_i < label_size; var_i++)
    {
    	str[var_i] = (T_CHAR)(oct_val[var_i] + '0');
    }
    str[var_i] = '\0';

}
/*
 *
 * Function                : IntToStringTrim
 *
 * Description             : This function changes data type of BIT from INT to CHAR array
 *
 * Formal parameter(s)     : T_UINT8 bit - bit value that needs to be converted into string
 *						     T_UINT8 bit_size - Size of the bit to be converted
 *							 T_CHAR *str - Converted string
 *
 * Return Value            : None
 *
 * Assumption              : None
 *
 */
void IntToStringTrim(T_UINT8 bit,T_UINT8 bit_size, T_CHAR *str)
{
    T_UINT8 var_i=ZERO;                          /* Loop variable */

    /* hdudispfpdicheck-IntTostring_TRIM-DB-LLR-001 */
    for (var_i = ONE; var_i <= bit_size; var_i++)
    {
        str[bit_size-var_i] = (T_CHAR)((bit % TEN) + '0');
        bit = bit / TEN;
    }
    str[var_i-1] = '\0';
}

/*
 *
 * Function                : OnlyOneBitSetToOne
 *
 * Description             : This function checks set Bit.
 *
 * Formal parameter(s)     : T_UINT32 checkBit - bit that needs to be checked
 *
 * Return Value            : None
 *
 * Assumption              : None
 *
 */
static T_UINT32 OnlyOneBitSetToOne(T_UINT32 check_bit)
{
    /*hdudispfpdicheck-OnlyOneBitSetToOne-DB-LLR-001*/
    return check_bit && !(check_bit & (check_bit-ONE));
}

/*
 *
 * Function                : FindColorRange
 *
 * Description             : This function returns the required color
 *
 * Formal parameter(s)     : T_UINT16 color - IN color sent from T_UINT16
 *
 * Return Value            : T_COLOR - color returned
 *
 * Assumption              : None
 *
 */



T_COLOR FindColorRange(T_UINT16 color)
{
   T_COLOR ret_cal=COLOR_WHITE;
   switch(color)
   {
   /*hdudispfpdicheck-FindColorRange-DB-LLR-001*/
   case BLACK:
      ret_cal=COLOR_BLACK;
       break;
   /*hdudispfpdicheck-FindColorRange-DB-LLR-002*/
   case DARK_RED:
      ret_cal=COLOR_DARK_RED;
       break;
   case RED:
      ret_cal=COLOR_RED;
      break;
      /*hdudispfpdicheck-FindColorRange-DB-LLR-003*/
   case CAS_REV_RED:
      ret_cal=COLOR_LIGHT_RED;
      break;
   case PINK:
      ret_cal=COLOR_PINK;
      break;
   case VIOLET:
      ret_cal=COLOR_VIOLET;
      break;
      /*hdudispfpdicheck-FindColorRange-DB-LLR-004*/
   case TEAL:
      ret_cal=COLOR_TEAL;
      break;
   case TURQUOISE:
      ret_cal=COLOR_TURQUOISE;
      break;
      /*hdudispfpdicheck-FindColorRange-DB-LLR-005*/
   case GREEN:
      ret_cal=COLOR_GREEN;
      break;
   case BRIGHT_GREEN:
       ret_cal=COLOR_BRIGHT_GREEN;
       break;
      /*hdudispfpdicheck-FindColorRange-DB-LLR-006*/
   case DARK_BLUE:
      ret_cal=COLOR_DARK_BLUE;
      break;
      /*hdudispfpdicheck-FindColorRange-DB-LLR-007*/
   case BLUE:
      ret_cal=COLOR_BLUE;
      break;
      /*hdudispfpdicheck-FindColorRange-DB-LLR-008*/
   case LIGHT_GRAY:
      ret_cal=COLOR_LIGHT_GRAY;
      break;
   case GRAY:
       ret_cal=COLOR_GRAY;
       break;
    case DARK_GRAY:
        ret_cal=COLOR_DARK_GRAY;
        break;
      /*hdudispfpdicheck-FindColorRange-DB-LLR-009*/
   case YELLOW:
      ret_cal=COLOR_YELLOW;
      break;
   case ORANGE:
       ret_cal=COLOR_ORANGE;
       break;
      /*hdudispfpdicheck-FindColorRange-DB-LLR-010*/
   case WHITE:
      ret_cal=COLOR_WHITE;
      break;
      /*hdudispfpdicheck-FindColorRange-DB-LLR-011*/
   default:
	   ret_cal=COLOR_MAX;
      break;
   }
   return ret_cal;
}

/*
 *
 * Function                : CheckColor
 *
 * Description             : This function checks if color is in range
 *
 * Formal parameter(s)     : T_UINT16 color - IN color sent from PDI
 *
 * Return Value            : T_BOOL - status
 *
 * Assumption              : None
 *
 */

static T_BOOL CheckColor(T_UINT16 color)
{
   T_BOOL ret_val=FALSE;
   if (ZERO == color)
   {
	   ret_val = TRUE;
   }
   else
   {
   switch(color)
   {
   /*hdudispfpdicheck-CheckColor-DB-LLR-001*/
   case COLOR_BLACK:
   ret_val = TRUE;
       break;

   /*hdudispfpdicheck-CheckColor-DB-LLR-012*/
   case COLOR_DARK_RED:
       ret_val = TRUE;
           break;

   /*hdudispfpdicheck-CheckColor-DB-LLR-002*/
   case COLOR_RED:
   ret_val = TRUE;
      break;

   /*hdudispfpdicheck-CheckColor-DB-LLR-003*/
   case COLOR_LIGHT_RED:
   ret_val = TRUE;
      break;

   /*hdudispfpdicheck-CheckColor-DB-LLR-013*/
   case COLOR_PINK:
   ret_val = TRUE;
       break;

   /*hdudispfpdicheck-CheckColor-DB-LLR-004*/
   case COLOR_TEAL:
   ret_val = TRUE;
      break;

   /*hdudispfpdicheck-CheckColor-DB-LLR-005*/
   case COLOR_GREEN:
   ret_val = TRUE;
      break;

   /*hdudispfpdicheck-CheckColor-DB-LLR-014*/
   case COLOR_BRIGHT_GREEN:
   ret_val = TRUE;
      break;

   /*hdudispfpdicheck-CheckColor-DB-LLR-015*/
   case COLOR_TURQUOISE:
   ret_val = TRUE;
      break;

   /*hdudispfpdicheck-CheckColor-DB-LLR-006*/
   case COLOR_DARK_BLUE:
   ret_val = TRUE;
      break;

   /*hdudispfpdicheck-CheckColor-DB-LLR-016*/
   case COLOR_VIOLET:
   ret_val = TRUE;
      break;

   /*hdudispfpdicheck-CheckColor-DB-LLR-007*/
   case COLOR_BLUE:
   ret_val = TRUE;
      break;

   /*hdudispfpdicheck-CheckColor-DB-LLR-008*/
   case COLOR_LIGHT_GRAY:
   ret_val = TRUE;
      break;

   /*hdudispfpdicheck-CheckColor-DB-LLR-017*/
   case COLOR_GRAY:
   ret_val = TRUE;
      break;

   /*hdudispfpdicheck-CheckColor-DB-LLR-018*/
   case COLOR_DARK_GRAY:
   ret_val = TRUE;
      break;

   /*hdudispfpdicheck-CheckColor-DB-LLR-019*/
   case COLOR_DARK_YELLOW:
   ret_val = TRUE;
      break;

   /*hdudispfpdicheck-CheckColor-DB-LLR-009*/
   case COLOR_YELLOW:
   ret_val = TRUE;
      break;

   /*hdudispfpdicheck-CheckColor-DB-LLR-020*/
   case COLOR_ORANGE:
   ret_val = TRUE;
      break;

   /*hdudispfpdicheck-CheckColor-DB-LLR-010*/
   case COLOR_WHITE:
   ret_val = TRUE;
      break;

   /*hdudispfpdicheck-CheckColor-DB-LLR-011*/
   default:
   ret_val = FALSE;
      break;
   }
   }
   return ret_val;
}

/*
 * Function                : CheckVerPos
 *
 * Description             : This function checks if a parameter is within range
 *
 * Formal parameter(s)     : T_UINT8 pos : IN - Position
 *
 * Return Value            : T_BOOL
 *
 * Assumption              : None
 *
 */
static T_BOOL CheckVerPos(T_FLOAT pos)
{
	T_BOOL ret_val=FALSE;

		/* hdudispfpdicheck-CheckVerPos-DB-LLR-001 */
		if (M_FP_COMPARE>(ZERO-pos) && M_FP_COMPARE> (pos-ZERO))
		{
			ret_val= TRUE;
		}
		else if (M_FP_COMPARE>(ONE-pos) && M_FP_COMPARE> (pos-ONE))
		{
			ret_val= TRUE;
		}
		else if(M_FP_COMPARE>(TEN-pos) && M_FP_COMPARE> (pos-TEN))
		{
			ret_val= TRUE;
		}
		else if (M_FP_COMPARE>(ONE_HUNDRED-pos) && M_FP_COMPARE> (pos-ONE_HUNDRED))
		{
			ret_val= TRUE;
		}
		else if(M_FP_COMPARE>(0.1f-pos) && M_FP_COMPARE> (pos-0.1f))
		{
			ret_val= TRUE;
		}
		else if (M_FP_COMPARE>(0.01f-pos) && M_FP_COMPARE> (pos-0.01f))
		{
			ret_val= TRUE;
		}
		else
		{
		    /* hdudispfpdicheck-CheckVerPos-DB-LLR-002 */
			ret_val= FALSE;
		}
	return ret_val;
}

/*
 * Function                : CheckCasType
 *
 * Description             : This function checks if CAS type is within range.
 *
 * Formal parameter(s)     : T_UINT16 type : IN - CAS type
 *
 * Return Value            : T_BOOL
 *
 * Assumption              : None
 *
 */

static T_BOOL CheckCasType(T_UINT16 type)
{
   T_BOOL ret_val=FALSE;
   switch(type)
   {
   /*hdudispfpdicheck-CheckCasType-DB-LLR-001*/
   case ADVISORY:
       ret_val=TRUE;
       break;

   case CAUTION:
       ret_val=TRUE;
       break;

   case WARNING:
       ret_val=TRUE;
       break;

 /*hdudispfpdicheck-CheckCasType-DB-LLR-002*/
   default:
      ret_val=FALSE;
      break;
   }
   return ret_val;
}

/*
 *
 * Function                : CheckConfig
 *
 * Description             : This function checks configuration parameters
 *
 * Formal parameter(s)     : None
 *
 * Return Value            : None
 *
 * Assumption              : None
 *
 */
static void CheckConfig()
{
    /* Check for config_name */
    /* hdudispfpdicheck-CheckConfig-DB-LLR-001 */
    if (!CheckString(Config_data.config_name, MAX_CONFIG_NAME)&&(Pdi_error_count<MAX_ERROR_MSG))
    {
        /*Frame the Error Message */
        BuildErrorMsg("CONFIG_NAME","\0", "\0", Error_msg_string[Pdi_error_count]);

        /* Increment the PDI Error Index */
        ++Pdi_error_count;

    }

    /* Check for config_version */
    /* hdudispfpdicheck-CheckConfig-DB-LLR-002 */
    if (!CheckString(Config_data.config_version,MAX_CONFIG_VERSION)
        &&(Pdi_error_count<MAX_ERROR_MSG))
    {
        /*Frame the Error Message */
        BuildErrorMsg("CONFIG_PN_VN", "\0", "\0", Error_msg_string[Pdi_error_count]);

        /* Increment the PDI Error Index */
        ++Pdi_error_count;

    }
    /* Check for du_resolution */
        /* hdudispfpdicheck-CheckConfig-DB-LLR-003 */
    if((TRUE == CheckDuResolution())&& (Pdi_error_count < MAX_ERROR_MSG))
    {
        /*Frame the Error Message */
        BuildErrorMsg("DU_RESOLUTION", "\0", "\0", Error_msg_string[Pdi_error_count]);

        /* Increment the PDI Error Index */
        ++Pdi_error_count;
    }

    /* Check for config_engine */
        /* hdudispfpdicheck-CheckConfig-DB-LLR-004 */
    if (!CheckString(Config_data.config_engine, MAX_CONFIG_ENGINE)
         && (Pdi_error_count < MAX_ERROR_MSG))
    {
        /*Frame the Error Message */
        BuildErrorMsg("CONFIG_ENGINE", "\0", "\0", Error_msg_string[Pdi_error_count]);

        /* Increment the PDI Error Index */
        ++Pdi_error_count;

    }

    /* Check for Channel */
        /* hdudispfpdicheck-CheckConfig-DB-LLR-005 */
    if ((!CheckMinMax(Config_data.channels.u16_x, ZERO , ONE)   ||
         !CheckMinMax(Config_data.channels.u16_y, ZERO , ONE)) &&
         (Pdi_error_count < MAX_ERROR_MSG))
    {
        /*Frame the Error Message */
        BuildErrorMsg("CHANNEL", "\0", "\0", Error_msg_string[Pdi_error_count]);

        /* Increment the PDI Error Index */
        ++Pdi_error_count;

    }
    /* Check for ENG_SDI */
        /* hdudispfpdicheck-CheckConfig-DB-LLR-006 */
     if (!CheckMinMax(Config_data.eng_sdi, FALSE , TRUE)&&
            (Pdi_error_count < MAX_ERROR_MSG))
    {
        /*Frame the Error Message */
        BuildErrorMsg("ENG_SDI", "\0", "\0", Error_msg_string[Pdi_error_count]);

        /* Increment the PDI Error Index */
        ++Pdi_error_count;
    }

     /* Check for SCU_ENABLE */
         /* hdudispfpdicheck-CheckConfig-DB-LLR-007 */
      if (!CheckMinMax(Config_data.scu_enable, ZERO , ONE)&&
             (Pdi_error_count < MAX_ERROR_MSG))
      {
         /*Frame the Error Message */
         BuildErrorMsg("LMS_SCU_ENABLE", "\0", "\0", Error_msg_string[Pdi_error_count]);

         /* Increment the PDI Error Index */
         ++Pdi_error_count;
      }
}

/*
 *
 * Function                : CheckCASParameters
 *
 * Description             : This function check CAS parameters
 *
 * Formal parameter(s)     : None
 *
 * Return Value            : None
 *
 * Assumption              : None
 *
 */
static void CheckCASParameters()
{
    T_CHAR element[4] = "CAS";                     /* Element type */
    T_CHAR labelstring[5]={0};     /* Variable used to store label in string format */
    T_UINT8 loop_cascnt = ZERO;                         /* CAS count required for loop */
    T_UINT8 max_string = ZERO;
    T_UINT8 cas_id = ZERO;
    T_UINT8 temp_length = ZERO;

    for (loop_cascnt = ONE; loop_cascnt <= Cas_word_cnt; loop_cascnt++)
    {
        /* Converts the label as array of characters */
    	OctToStringTrim(Cas_messages[loop_cascnt-ONE].label, Label_size, labelstring);
        temp_length = (T_UINT8)(StrLen((T_CHAR*)&Cas_messages[loop_cascnt-ONE].cas_string));
        if (max_string < temp_length)
        {
        	Index_value = loop_cascnt;
            max_string = temp_length;
        }
        else
        {
            ;
        }

        /*hdudispfpdicheck-CheckCASParameters-DB-LLR-001*/
        /* Check cas_string */
        if (!CheckString(Cas_messages[loop_cascnt-ONE].cas_string, (MAX_CAS_STRING_TXT - DEC_ONE))
            &&(Pdi_error_count < MAX_ERROR_MSG))
        {
            /* Frame the Error Message */
            BuildErrorMsg(element, labelstring, "CAS_STRING", Error_msg_string[Pdi_error_count]);

            /* Increment the PDI Error Index */
            ++Pdi_error_count;

        }
        /*hdudispfpdicheck-CheckCASParameters-DB-LLR-002*/
        /* Check cas_label */
        if (!CheckMinMax(Cas_messages[loop_cascnt-ONE].label, ONE, MAX_LABEL) &&
            (Pdi_error_count < MAX_ERROR_MSG))
        {
            /* Frame the Error Message */
            BuildErrorMsg(element, labelstring, "LABEL", Error_msg_string[Pdi_error_count]);

            /* Increment the PDI Error Index */
            ++Pdi_error_count;

        }
        /*hdudispfpdicheck-CheckCASParameters-DB-LLR-003*/
        /* Check for cas_start_bit */
        if (!CheckMinMax(Cas_messages[loop_cascnt-ONE].cas_start_bit,MIN_CAS_START_BIT,
            MAX_CAS_START_BIT) &&(Pdi_error_count < MAX_ERROR_MSG))
        {
            /* Frame the Error Message */
            BuildErrorMsg(element, labelstring, "CAS_START_BIT",\
									Error_msg_string[Pdi_error_count]);

            /* Increment the PDI Error Index */
            ++Pdi_error_count;

        }
        /*hdudispfpdicheck-CheckCASParameters-DB-LLR-004*/
        /* Check cas_priority */
        if (!CheckMinMax(Cas_messages[loop_cascnt-ONE].cas_priority, ONE, MAX_CAS_PRIORITY) &&
            (Pdi_error_count < MAX_ERROR_MSG))
        {
            /* Frame the Error Message */
            BuildErrorMsg(element, labelstring, "CAS_PRIORITY", Error_msg_string[Pdi_error_count]);

            /* Increment the PDI Error Index */
            ++Pdi_error_count;

        }
        /*hdudispfpdicheck-CheckCASParameters-DB-LLR-005*/
        /* Check cas_type */
        if (!CheckCasType(Cas_messages[loop_cascnt-ONE].cas_type) &&
        	(Cas_messages[loop_cascnt-ONE].cas_type != ZERO) &&
            (Pdi_error_count < MAX_ERROR_MSG))
        {
            /* Frame the Error Message */
            BuildErrorMsg(element, labelstring, "CAS_TYPE", Error_msg_string[Pdi_error_count]);

            /* Increment the PDI Error Index */
            ++Pdi_error_count;

        }
        /*hdudispfpdicheck-CheckCASParameters-DB-LLR-006*/
        /* Check cas_id */
        cas_id = (T_UINT8)Cas_messages[loop_cascnt-ONE].cas_id;
        if (!CheckMinMax(cas_id, ZERO, MAX_CAS_ID) &&
            (Pdi_error_count < MAX_ERROR_MSG))
        {
            /* Frame the Error Message*/
            BuildErrorMsg(element, labelstring, "CAS_ID", Error_msg_string[Pdi_error_count]);

            /* Increment the PDI Error Index*/
            ++Pdi_error_count;
        }
    }
}

/*
 *
 * Function                : CheckARINCParameters
 *
 * Description             : This function checks ARINC parameters
 *
 * Formal parameter(s)     : None
 *
 * Return Value            : None
 *
 * Assumption              : None
 *
 */
static void CheckA429Parameters()
{
    T_CHAR element[5] = "A429";                   /* Element type*/
    T_CHAR labelstring[5]={0};     /* Variable used to store label in string format*/
    T_UINT16 loop_a29cnt = ZERO;                       /* ARINC count required for loop*/

    for (loop_a29cnt = ONE; loop_a29cnt < A429_settings_cnt; loop_a29cnt++)
    {
        /* Converts the label as array of characters */
        /*hdudispfpdicheck-CheckA429Parameters-DB-LLR-001*/
    	OctToStringTrim(A429_cfg_data[loop_a29cnt-ONE].A429_label, Label_size, labelstring);

        /* Check for A429_PORT */
        if ((!(ONE == (A429_cfg_data[loop_a29cnt-ONE].A429_port))  &&
                !(TWO == (A429_cfg_data[loop_a29cnt-ONE].A429_port))) &&
             (Pdi_error_count < MAX_ERROR_MSG))
        {
            /* Frame the Error Message*/
            BuildErrorMsg(element, labelstring, "A429_PORT", Error_msg_string[Pdi_error_count]);

            /* Increment the PDI Error Index*/
            ++Pdi_error_count;

        }

        /* Check for LABEL */
        /*hdudispfpdicheck-CheckA429Parameters-DB-LLR-002*/
        if (!CheckMinMax(A429_cfg_data[loop_a29cnt-ONE].A429_label, ONE, MAX_LABEL) &&
            (Pdi_error_count < MAX_ERROR_MSG))
        {
            /* Frame the Error Message*/
            BuildErrorMsg(element, labelstring, "LABEL", Error_msg_string[Pdi_error_count]);

            /* Increment the PDI Error Index*/
            ++Pdi_error_count;

        }

		/*hdudispfpdicheck-CheckA429Parameters-DB-LLR-012*/
		if ((TRUE == Config_data.eng_sdi)&&
		(!CheckMinMax(A429_cfg_data[loop_a29cnt-ONE].A429_sdi, ZERO, THREE))&&
         (Pdi_error_count < MAX_ERROR_MSG))
        {
        /*Frame the Error Message */
        BuildErrorMsg(element, labelstring, "SDI",
                        Error_msg_string[Pdi_error_count]);

        /* Increment the PDI Error Index */
        ++Pdi_error_count;

        }

        /* Check for A429_TYPE */
        /*hdudispfpdicheck-CheckA429Parameters-DB-LLR-003*/
        if ((A429_cfg_data[loop_a29cnt-ONE].A429_type != BNR) &&
        	(A429_cfg_data[loop_a29cnt-ONE].A429_type != DDW)&&
            (Pdi_error_count < MAX_ERROR_MSG))
        {
            /* Frame the Error Message */
            BuildErrorMsg(element, labelstring, "A429_TYPE", Error_msg_string[Pdi_error_count]);

            /* Increment the PDI Error Index */
            ++Pdi_error_count;

        }

        if ( BNR == A429_cfg_data[loop_a29cnt-ONE].A429_type)
        {
            /* Check for A429_BNR_BITS */
            /*hdudispfpdicheck-CheckA429Parameters-DB-LLR-004*/
            if (!CheckMinMax((T_INT32)A429_cfg_data[loop_a29cnt-ONE].\
			     label_data.A429_bnr_data.A429_bnr_bits,
                 ONE, MAX_BNR_BITS) && (Pdi_error_count < MAX_ERROR_MSG))
            {
              /* Frame the Error Message*/
              BuildErrorMsg(element,labelstring,"A429_BNR_BITS",Error_msg_string[Pdi_error_count]);

              /* Increment the PDI Error Index*/
              ++Pdi_error_count;

            }

            /* Check for A429_BNR_START_BITS*/
            /*hdudispfpdicheck-CheckA429Parameters-DB-LLR-005*/
            if (!CheckMinMax((T_INT32)A429_cfg_data[loop_a29cnt-ONE].label_data.A429_bnr_data.
                A429_bnr_start_bit,MIN_START_BIT, MAX_START_BIT) &&
                (Pdi_error_count < MAX_ERROR_MSG))
            {
                /* Frame the Error Message*/
                BuildErrorMsg(element, labelstring, "A429_BNR_START_BIT",
                        Error_msg_string[Pdi_error_count]);

                /* Increment the PDI Error Index*/
                ++Pdi_error_count;

            }

            /* Check for A429_BNR_MAX*/
            /*hdudispfpdicheck-CheckA429Parameters-DB-LLR-006*/
            if ((A429_cfg_data[loop_a29cnt-ONE].label_data.A429_bnr_data.A429_bnr_max >
               (T_FLOAT)MAX_BNR) && (Pdi_error_count < MAX_ERROR_MSG))
            {
                /* Frame the Error Message*/
                BuildErrorMsg(element, labelstring, "A429_BNR_MAX",
                        Error_msg_string[Pdi_error_count]);

            /* Increment the PDI Error Index*/
                ++Pdi_error_count;

            }

            /* Check for A429_BNR_MIN*/
            /*hdudispfpdicheck-CheckA429Parameters-DB-LLR-007*/
            if ((A429_cfg_data[loop_a29cnt-ONE].label_data.A429_bnr_data.A429_bnr_min <
            	(T_FLOAT)MIN_BNR)
                && (Pdi_error_count < MAX_ERROR_MSG))
            {
                /* Frame the Error Message*/
                BuildErrorMsg(element,labelstring,"A429_BNR_MIN",\
							Error_msg_string[Pdi_error_count]);

                /* Increment the PDI Error Index*/
                ++Pdi_error_count;

            }

            /* Check for A429_BNR_OFFSET*/
            /*hdudispfpdicheck-CheckA429Parameters-DB-LLR-008*/
            if (!CheckMinMax((T_INT32)A429_cfg_data[loop_a29cnt-ONE].label_data.A429_bnr_data.\
				A429_bnr_offset,ZERO, MAX_BNR_OFFSET) && (Pdi_error_count < MAX_ERROR_MSG))
            {
                /* Frame the Error Message*/
                BuildErrorMsg(element, labelstring,"A429_BNR_OFFSET",
                        Error_msg_string[Pdi_error_count]);

                /* Increment the PDI Error Index*/
                ++Pdi_error_count;

            }

            /* Check for A429_BNR_TIMEOUT*/
            /*hdudispfpdicheck-CheckA429Parameters-DB-LLR-009*/
            if (!CheckMinMax((T_INT32)A429_cfg_data[loop_a29cnt-ONE].label_data.A429_bnr_data.\
                A429_bnr_timeout, ZERO, MAX_TIMEOUT) && (Pdi_error_count < MAX_ERROR_MSG))
            {
                /* Frame the Error Message*/
                BuildErrorMsg(element, labelstring, "A429_BNR_TIMEOUT",
                        Error_msg_string[Pdi_error_count]);

                /* Increment the PDI Error Index*/
                ++Pdi_error_count;

            }
            /* Check for Float value*/
            /* Check for A429_SCALE_FACTOR*/
            /*hdudispfpdicheck-CheckA429Parameters-DB-LLR-010*/
           if (!CheckFloatMinMax(A429_cfg_data[loop_a29cnt-ONE].label_data.A429_bnr_data.
                A429_bnr_scale_fact, ZERO, TWO) && (Pdi_error_count < MAX_ERROR_MSG))
            {
                /* Frame the Error Message*/
                BuildErrorMsg(element, labelstring,"A429_BNR_SCALE_FACTOR",
                        Error_msg_string[Pdi_error_count]);

                /* Increment the PDI Error Index*/
                ++Pdi_error_count;

            }
        }
        else if (DDW == A429_cfg_data[loop_a29cnt-ONE].A429_type)
        {
            /* Check for A429_DDW_TIMEOUT*/
            /*hdudispfpdicheck-CheckA429Parameters-DB-LLR-011*/
            if(!CheckMinMax((T_INT32)A429_cfg_data[loop_a29cnt-ONE].label_data.A429_ddw_timeout,
                ZERO, MAX_TIMEOUT) && (Pdi_error_count < MAX_ERROR_MSG))
            {
                /* Frame the Error Message*/
            BuildErrorMsg(element,labelstring,"A429_DDW_TIMEOUT",\
			              Error_msg_string[Pdi_error_count]);

            /* Increment the PDI Error Index*/
            ++Pdi_error_count;
            }

        }
        else
        {
            ; /* Do Nothing*/
        }
    }
	 /* hdudispfpdicheck-CheckA429Parameters-DB-LLR-013 */
     /* Check if label 0250, 0272 and 0247 are not configured when SCU unit is present */
    if((ONE == Config_data.scu_enable) && (SEVEN != Scu_label_flag) &&\
    		(Pdi_error_count < MAX_ERROR_MSG))
    {
        /* Frame the Error Message */
        BuildErrorMsg("SCU LABEL NOT CONFIGURED", "\0", "\0", Error_msg_string[Pdi_error_count]);

        /*  Increment the PDI Error Index */
        ++Pdi_error_count;
    }
}

/*
 *
 * Function                : CheckElogTrig
 *
 * Description             : This function checks Exceedance Log Trigger Parameters
 *
 * Formal parameter(s)     : None
 *
 * Return Value            : None
 *
 * Assumption              : None
 *
 */
static void CheckElogTrig()
{
    T_UINT8 u8_i = ZERO;         /* Loop variable for number of log_trig_conditions */
    T_CHAR labelstring[5]={0};     /* Variable used to store label in string format*/
    T_CHAR element[10] = "ELOG_TRIG";      /* Stores Element type */
    T_UINT16 loop_elogcnt=ZERO;

    /* Return if no elog_trig parameters */
    /*hdudispfpdicheck-CheckElogTrig-DB-LLR-001*/
    if (FALSE == Elog_trig_bool)
    {
        return;
    }

    for (loop_elogcnt = ZERO; loop_elogcnt < MAX_ELOG_EVENT; loop_elogcnt++)
    {
        for (u8_i = ZERO; u8_i<MAX_ELOG_TRIG_COND; u8_i++)
        {
            /* Converts the label as array of characters*/
        	OctToStringTrim(Elog_trig[loop_elogcnt].elog_trig_label[u8_i],Label_size,labelstring);
             /*hdudispfpdicheck-CheckElogTrig-DB-LLR-002*/
            /* Check for ELOG_TRIG_LABEL*/
            if (!CheckMinMax(Elog_trig[loop_elogcnt].elog_trig_label[u8_i], ONE, MAX_LABEL) &&
            	(Elog_trig[loop_elogcnt].elog_trig_label[u8_i] != ZERO) &&
                (Pdi_error_count < MAX_ERROR_MSG))
            {
                /* Frame the Error Message */
                BuildErrorMsg(element, labelstring, "ELOG_TRIG_LABEL",
                        Error_msg_string[Pdi_error_count]);

                /* Increment the PDI Error Index */
                ++Pdi_error_count;

            }

              /*hdudispfpdicheck-CheckElogTrig-DB-LLR-006*/
		if ((TRUE == Config_data.eng_sdi)&& \
			(!CheckMinMax(Elog_trig[loop_elogcnt].elog_trig_sdi[u8_i], ZERO , THREE))&&
                (Pdi_error_count < MAX_ERROR_MSG))
            {
                /*Frame the Error Message */
                  BuildErrorMsg(element, labelstring, "ELOG_TRIG_SDI",
                        Error_msg_string[Pdi_error_count]);

                    /* Increment the PDI Error Index */
                    ++Pdi_error_count;

            }


        /* Check for ELOG_TRIG_STRT_VAL */
        /*hdudispfpdicheck-CheckElogTrig-DB-LLR-003*/
    if ((Elog_trig[loop_elogcnt].elog_trig_start_type[u8_i] != ZERO) &&
	    (!CheckMinMax(Elog_trig[loop_elogcnt].elog_trig_start_type[u8_i],\
	    ONE,MAX_SYMBOL_VAL))
    	&&(Pdi_error_count < MAX_ERROR_MSG))
        {
            /* Frame the Error Message */
            BuildErrorMsg(element, labelstring, "ELOG_TRIG_STRT_VAL",
                    Error_msg_string[Pdi_error_count]);

            /* Increment the PDI Error Index */
            ++Pdi_error_count;
        }
        /* Check for ELOG_TRIG_STRT_VAL */
    if ((!CheckFloatMinMax(Elog_trig[loop_elogcnt].elog_trig_start_val[u8_i] ,\
           MIN_RANGE, MAX_RANGE))
    	&&(Pdi_error_count < MAX_ERROR_MSG))
        {
            /* Frame the Error Message */
            BuildErrorMsg(element, labelstring, "ELOG_TRIG_STRT_VAL",
                    Error_msg_string[Pdi_error_count]);

            /* Increment the PDI Error Index */
            ++Pdi_error_count;

        }
    /* Check for ELOG_TRIG_CROSS_VAL */
    /*hdudispfpdicheck-CheckElogTrig-DB-LLR-004*/
if ((((Elog_trig[loop_elogcnt].elog_trig_cross_type[u8_i] != ZERO) &&
   (!CheckMinMax(Elog_trig[loop_elogcnt].elog_trig_cross_type[u8_i], ONE, SIX))))
	&& (Pdi_error_count < MAX_ERROR_MSG))
    {
        /* Frame the Error Message */
        BuildErrorMsg(element, labelstring, "ELOG_TRIG_CROSS_VAL",
                Error_msg_string[Pdi_error_count]);

        /* Increment the PDI Error Index */
        ++Pdi_error_count;
    }

	/* Check for ELOG_TRIG_CROSS_VAL */
    /*hdudispfpdicheck-CheckElogTrig-DB-LLR-004*/
if ((!CheckFloatMinMax((T_FLOAT)Elog_trig[loop_elogcnt].elog_trig_cross_val[u8_i],
     MIN_RANGE, MAX_RANGE))
	&& (Pdi_error_count < MAX_ERROR_MSG))
    {
        /* Frame the Error Message */
        BuildErrorMsg(element, labelstring, "ELOG_TRIG_CROSS_VAL",
                Error_msg_string[Pdi_error_count]);

        /* Increment the PDI Error Index */
        ++Pdi_error_count;
    }

            /* Check for ELOG_TRIG_TIME*/
            /*hdudispfpdicheck-CheckElogTrig-DB-LLR-005*/
            if (!CheckMinMax(Elog_trig[loop_elogcnt].elog_trig_time[u8_i], ZERO,
                EXCEEDANCE_LOG_TRIG_TIME) && (Pdi_error_count < MAX_ERROR_MSG))
            {
                /* Frame the Error Message */
                BuildErrorMsg(element, labelstring, "ELOG_TRIG_TIME",
                        Error_msg_string[Pdi_error_count]);

                /* Increment the PDI Error Index */
                ++Pdi_error_count;

            }
        }
    }
}

/*
 *
 * Function                : CheckElogParam
 *
 * Description             : This function checks exceedance log event parameters
 *
 * Formal parameter(s)     : None
 *
 * Return Value            : None
 *
 * Assumption              : None
 *
 */
static void CheckElogParam()
{
    T_CHAR element[5] = "ELOG"; /* Element type */
    T_CHAR labelstring[5]={0};     /* Variable used to store label in string format */
    T_UINT16 loop_elogcnt=ZERO;    /* Round dial count required for loop */
    T_UINT16 var_j=ZERO;        /* Loop variable for traversing over size of parameters */
    T_UINT16 u8_i=ZERO;        /* Loop variable used to traverse over labels */


    /* Return if no elog param parameters */
    /*hdudispfpdicheck-CheckElogParam-DB-LLR-001*/
    if (FALSE == Elog_param)
    {
        return;
    }


    for (loop_elogcnt = ZERO; loop_elogcnt < MAX_ELOG_EVENT; loop_elogcnt++)
    {
        /* Converts the label as array of characters*/
		 /*hdudispfpdicheck-CheckElogParam-DB-LLR-002*/
    	OctToStringTrim(Elog_label[loop_elogcnt].elog_label, Label_size, labelstring);

        /* Check elog_label*/
        if (!CheckMinMax(Elog_label[loop_elogcnt].elog_label, ONE, MAX_LABEL) &&
        	(ZERO != Elog_label[loop_elogcnt].elog_label) &&
            (Pdi_error_count < MAX_ERROR_MSG))
        {
            /* Frame the Error Message*/
            BuildErrorMsg(element, labelstring, "ELOG_LABEL", Error_msg_string[Pdi_error_count]);

            /* Increment the PDI Error Index*/
            ++Pdi_error_count;

        }
        /* hdudispfpdicheck-CheckElogParam-DB-LLR-005 */
		if ((TRUE == Config_data.eng_sdi)&& \
		(!CheckMinMax(Elog_label[loop_elogcnt].elog_sdi, ZERO , THREE))&&
         (Pdi_error_count < MAX_ERROR_MSG))
        {
             /*Frame the Error Message */
               BuildErrorMsg(element, labelstring, "ELOG_SDI",
                Error_msg_string[Pdi_error_count]);

               /* Increment the PDI Error Index */
               ++Pdi_error_count;

        }


        /* Check elog_bit_label*/
        for ( u8_i = ZERO; u8_i < MAX_ELOG_PARAM ; u8_i++)
        {
            /*hdudispfpdicheck-CheckElogParam-DB-LLR-003*/
            if (!CheckMinMax(Elog_label[loop_elogcnt].elog_bit_label[u8_i], ONE, MAX_LABEL) &&
            	(Elog_label[loop_elogcnt].elog_bit_label[u8_i] != ZERO) &&
                (Pdi_error_count < MAX_ERROR_MSG))
            {
                /* Frame the Error Message*/
                BuildErrorMsg(element, labelstring, "ELOG_BIT_LABEL",
                        Error_msg_string[Pdi_error_count]);

                /* Increment the PDI Error Index*/
                ++Pdi_error_count;

            }

            /* Check for elog_bit_param*/
            for (var_j = ZERO; var_j < MAX_ELOG_PARAM_SIZE + TWO; var_j++)
            {
               /*hdudispfpdicheck-CheckElogParam-DB-LLR-004*/
                if (!CheckString(&Elog_label[loop_elogcnt].elog_bit_param[u8_i][var_j],
                    MAX_ELOG_BIT_PARAM) && (Pdi_error_count < MAX_ERROR_MSG))
                {
                    /* Frame the Error Message*/
                    BuildErrorMsg(element, labelstring, "ELOG_BIT_PARAM",
                            Error_msg_string[Pdi_error_count]);

                    /* Increment the PDI Error Index*/
                    ++Pdi_error_count;

                }
            }
        }
    }
}

/*
 *
 * Function                : CheckACDTParams
 *
 * Description             : This function checks ACDT parameters
 *
 * Formal parameter(s)     : None
 *
 * Return Value            : None
 *
 * Assumption              : None
 *
 */
static void CheckAcdtParams()
{
    T_CHAR element[5] = "ACDT";     /*Element type*/
    T_CHAR labelstring[5]={0};     /* Variable used to store label in string format*/

    /*hdudispfpdicheck-CheckAcdtParams-DB-LLR-001*/
    if (FALSE == Acdt_parameters)
    {
        return;
    }

    /* Converts label to array for characters*/
	/*hdudispfpdicheck-CheckAcdtParams-DB-LLR-002*/
    OctToStringTrim( Auto_cool_down_tmr.label, Label_size, labelstring);

    /* Check for label*/
    if (!CheckMinMax( Auto_cool_down_tmr.label, ONE, MAX_LABEL) &&
        (Pdi_error_count < MAX_ERROR_MSG))
    {
        /* Frame the Error Message*/
        BuildErrorMsg(element, labelstring, "LABEL", Error_msg_string[Pdi_error_count]);

        /* Increment the PDI Error Index*/
        ++Pdi_error_count;

    }

    /* Check ACDT_time*/
     /*hdudispfpdicheck-CheckAcdtParams-DB-LLR-003*/
    if (!CheckMinMax( Auto_cool_down_tmr.acdt_time, ZERO, MAX_TIMER) &&
        (Pdi_error_count < MAX_ERROR_MSG))
    {
        /* Frame the Error Message*/
        BuildErrorMsg(element, labelstring, "ACDT_TIME", Error_msg_string[Pdi_error_count]);

        /* Increment the PDI Error Index*/
        ++Pdi_error_count;

    }

    /* Check WOG_LABEL*/
     /*hdudispfpdicheck-CheckAcdtParams-DB-LLR-004*/
    if (!CheckMinMax(Auto_cool_down_tmr.wog_label, ONE, MAX_LABEL) &&
        (Pdi_error_count < MAX_ERROR_MSG))
    {
        /* Frame the Error Message*/
        BuildErrorMsg(element, labelstring, "WOG_LABEL", Error_msg_string[Pdi_error_count]);

        /* Increment the PDI Error Index*/
        ++Pdi_error_count;

    }

    /* Check WOG_START_BIT*/
     /*hdudispfpdicheck-CheckAcdtParams-DB-LLR-005*/
    /* Change "0" to "11"*/
    if (!CheckMinMax(Auto_cool_down_tmr.wog_start_bit, ELEVEN, MAX_WOG_START_BIT) &&
        (Pdi_error_count < MAX_ERROR_MSG))
    {
        /* Frame the Error Message*/
        BuildErrorMsg(element, labelstring, "WOG_START_BIT", Error_msg_string[Pdi_error_count]);

        /* Increment the PDI Error Index*/
        ++Pdi_error_count;

    }

    /* Check ACDT_ON_TRIGGER*/
     /*hdudispfpdicheck-CheckAcdtParams-DB-LLR-006*/
    if((!CheckMinMax(Auto_cool_down_tmr.acdt_on_trigger, ONE, SIX) ||
       !CheckFloatMinMax(Auto_cool_down_tmr.acdt_on_trigger_value,\
	   ZERO,(T_INT32) MAX_ACDT_TIMER)) &&
       (Pdi_error_count < MAX_ERROR_MSG))
    {
        /* Frame the Error Message*/
        BuildErrorMsg(element, labelstring, "ACDT_ON_TRIGGER", Error_msg_string[Pdi_error_count]);
        /* Increment the PDI Error Index*/
        ++Pdi_error_count;

    }

    /* Check ACDT_ON_COND*/
     /*hdudispfpdicheck-CheckAcdtParams-DB-LLR-007*/
    if ((!CheckMinMax(Auto_cool_down_tmr.acdt_on_cond, ONE, SIX) ||
        !CheckFloatMinMax(Auto_cool_down_tmr.acdt_on_cond_value, ZERO,
		(T_INT32)MAX_ACDT_TIMER)) && (Pdi_error_count < MAX_ERROR_MSG))
    {
        /* Frame the Error Message*/
        BuildErrorMsg(element, labelstring, "ACDT_ON_COND", Error_msg_string[Pdi_error_count]);

        /* Increment the PDI Error Index*/
        ++Pdi_error_count;

    }

    /* Check ACDT_OFF_CONDITION*/
     /*hdudispfpdicheck-CheckAcdtParams-DB-LLR-008*/
    if ((!CheckMinMax(Auto_cool_down_tmr.acdt_off_condition, ONE, SIX) ||
        (!CheckFloatMinMax(Auto_cool_down_tmr.acdt_off_condition_value, ZERO,
        (T_INT32)MAX_ACDT_TIMER))) && (Pdi_error_count < MAX_ERROR_MSG))
    {
        /* Frame the Error Message*/
        BuildErrorMsg(element, labelstring, "ACDT_OFF_CONDITION", \
		Error_msg_string[Pdi_error_count]);

        /* Increment the PDI Error Index*/
        ++Pdi_error_count;

    }
}

/*
 *
 * Function                : CheckPageSettings
 *
 * Description             : This function check page settings
 *
 * Formal parameter(s)     : None
 *
 * Return Value            : None
 *
 * Assumption              : None
 *
 */
static void CheckPageSettings()
{
    T_CHAR element[3]="PG";     /*Element Type*/
    T_CHAR pagestring[5]={0};     /* Variable used to store label in string format*/
    T_UINT8 pagesize = FOUR;
    T_UINT16 color_value = ZERO;
    T_UINT8 timer[8] = "0:00:00";
    T_UINT16 string_width = ZERO;
    T_UINT16 string_height = ZERO;

    /* Check for page_num*/
    IntToStringTrim(Page_settings.page_num, pagesize, pagestring);
    /*hdudispfpdicheck-CheckPageSettings-DB-LLR-001*/
    if (!CheckMinMax(Page_settings.page_num, ZERO, MAX_PAGE_NUM) &&
        (Pdi_error_count < MAX_ERROR_MSG))
    {
        /*Frame the Error Message*/
        BuildErrorMsg(element, pagestring, "PAGE_NUM", Error_msg_string[Pdi_error_count]);

        /* Increment the PDI Error Index*/
        ++Pdi_error_count;

    }

    /* Check Page_name*/
    /*hdudispfpdicheck-CheckPageSettings-DB-LLR-002*/
    if (!CheckString(Page_settings.page_name, MAX_PAGE_NAME) &&
        (Pdi_error_count < MAX_ERROR_MSG))
    {
        /*Frame the Error Message*/
        BuildErrorMsg(element, pagestring, "PAGE_NAME", Error_msg_string[Pdi_error_count]);

        /* Increment the PDI Error Index*/
        ++Pdi_error_count;

    }

/*
 * Check page_menu
 * Starting from left, when bit in nth position is set to 1 it indicates that Button
 * n is enabled for the page.
 * E.g. value 0x2 indicates Button 1 is enabled. value 0x3FFE (16382) indicates
 * buttons 1 to 13 have been enabled
 */

 /* hdudispfpdicheck-CheckPageSettings-DB-LLR-003 */
    if (!CheckAxisMinMax((T_INT32)Page_settings.page_menu, ZERO, MAX_PAGE_MENU,\
    	MAX_PAGE_MENU_10INCH) && (Pdi_error_count<MAX_ERROR_MSG))
    {
        /*Frame the Error Message*/
        BuildErrorMsg(element, pagestring, "PAGE_MENU", Error_msg_string[Pdi_error_count]);

        /* Increment the PDI Error Index*/
        ++Pdi_error_count;

    }
    /* Check for menu_color*/
    /*hdudispfpdicheck-CheckPageSettings-DB-LLR-004*/
    color_value = FindColorRange(Page_settings.menu_color);
    if (!CheckColor(color_value) &&
        (Pdi_error_count < MAX_ERROR_MSG))
    {
        /*Frame the Error Message*/
        BuildErrorMsg(element, pagestring, "MENU_COLOR", Error_msg_string[Pdi_error_count]);
        Page_settings.menu_color = BLUE;
        /* Increment the PDI Error Index*/
        ++Pdi_error_count;

    }

    /* Check for action_color*/
    /*hdudispfpdicheck-CheckPageSettings-DB-LLR-005*/
    color_value = FindColorRange(Page_settings.action_color);
    if (!CheckColor(color_value) &&
        (Pdi_error_count < MAX_ERROR_MSG))
    {
        /*Frame the Error Message*/
        BuildErrorMsg(element, pagestring, "ACTION_COLOR", Error_msg_string[Pdi_error_count]);
        Page_settings.action_color = DARK_BLUE;
        /* Increment the PDI Error Index*/
        ++Pdi_error_count;

    }

    /* Check for menu_txt_color*/
    /*hdudispfpdicheck-CheckPageSettings-DB-LLR-006*/
    color_value = FindColorRange(Page_settings.menu_txt_color);
    if (!CheckColor(color_value) &&
        (Pdi_error_count < MAX_ERROR_MSG))
    {
        /*Frame the Error Message*/
        BuildErrorMsg(element, pagestring, "MENU_TXT_COLOR", Error_msg_string[Pdi_error_count]);

        /* Increment the PDI Error Index*/
        ++Pdi_error_count;
    }
    /* check for timer_font*/
    /*hdudispfpdicheck-CheckPageSettings-DB-LLR-008*/
    if (!CheckFont(Page_settings.timer_font) &&
    	(Page_settings.timer_font != ZERO) && (Pdi_error_count < MAX_ERROR_MSG))
    {
        /*Frame the Error Message*/
        BuildErrorMsg(element, pagestring, "TIMER_FONT", Error_msg_string[Pdi_error_count]);

        /* Increment the PDI Error Index*/
        ++Pdi_error_count;
        Timer_axis_error = (ONE << Page_num) | Timer_axis_error;
    }

    /* Check for timer_axis*/
    /*hdudispfpdicheck-CheckPageSettings-DB-LLR-007*/
    if ((TRUE == Timer_flag) &&
    	(!CheckAxisMinMax(Page_settings.timer_axis.u16_x, ZERO, PANEL_HEIGHT,PANEL_WIDTH) ||
        !CheckAxisMinMax(Page_settings.timer_axis.u16_y, ZERO, PANEL_WIDTH,PANEL_HEIGHT)) &&
         (Pdi_error_count < MAX_ERROR_MSG))
    {
        /*Frame the Error Message*/
        BuildErrorMsg(element, pagestring, "TIMER_AXIS", Error_msg_string[Pdi_error_count]);
        /* Increment the PDI Error Index*/
        ++Pdi_error_count;
        Timer_axis_error = (ONE << Page_num) | Timer_axis_error;
    }

    string_width= ((T_UINT16)(FontsGetStringWidth(&timer[0],Page_settings.timer_font)));
    string_height=(T_UINT16)(FontsGetFontHeight(Page_settings.timer_font));
     if (ONE == (string_width & 1))
     {
    	 string_width = (T_UINT16)(string_width + 1);
     }

     /* Check for timer_axis*/
     /*hdudispfpdicheck-CheckPageSettings-DB-LLR-010*/
     if ((TRUE == Timer_flag) &&
    	 ((!CheckAxisMinMax(Page_settings.timer_axis.u16_x+(string_width/2),ZERO , \
		 PANEL_HEIGHT,PANEL_WIDTH)   || \
		 (!CheckAxisMinMax(Page_settings.timer_axis.u16_x-(string_width/2),ZERO ,\
		  PANEL_HEIGHT,PANEL_WIDTH))) ||
          (!CheckAxisMinMax(Page_settings.timer_axis.u16_y+(string_height/2), ZERO,\
		  PANEL_WIDTH,PANEL_HEIGHT)) ||
		  (!CheckAxisMinMax(Page_settings.timer_axis.u16_y -(string_height/2), ZERO, \
		  PANEL_WIDTH,PANEL_HEIGHT)))
		  && (Pdi_error_count < MAX_ERROR_MSG))
     {
         /*Frame the Error Message*/
         BuildErrorMsg(element, pagestring, "TIMER_AXIS", Error_msg_string[Pdi_error_count]);
         /* Increment the PDI Error Index*/
         ++Pdi_error_count;
         Timer_axis_error = (ONE << Page_num) | Timer_axis_error;
     }
     /* Check acdt_axis*/
     /*hdudispfpdicheck-CheckPageSettings-DB-LLR-009*/
      if ((TRUE == Acdt_flag) &&
    	 (!CheckAxisMinMax(Page_settings.acdt_axis.u16_x, ACDT_X_AXIS,
		 PANEL_HEIGHT-ACDT_X_AXIS, PANEL_WIDTH-ACDT_X_AXIS)||
         !CheckAxisMinMax(Page_settings.acdt_axis.u16_y,ACDT_Y_AXIS,
		 PANEL_WIDTH-ACDT_Y_AXIS, PANEL_HEIGHT-ACDT_Y_AXIS)) &&
         (Pdi_error_count < MAX_ERROR_MSG))
     {
         /*Frame the Error Message*/
         BuildErrorMsg(element, pagestring, "ACDT_AXIS", Error_msg_string[Pdi_error_count]);
         /* Increment the PDI Error Index*/
         ++Pdi_error_count;
         Acdt_axis_error = (ONE << Page_num) | Acdt_axis_error;
     }
}

/*
 *
 * Function                : CheckBarGraph
 *
 * Description             : This function checks Bar Graph parameters
 *
 * Formal parameter(s)     : None
 *
 * Return Value            : None
 *
 * Assumption              : None
 *
 */
static void CheckBarGraph()
{
    T_CHAR element[3] = "BG";    /* Element type*/
    T_CHAR labelstring[5]={0};     /* Variable used to store label in string format*/
    T_UINT16 loop_bgcnt=ZERO;        /* Graph count required for loop*/
    T_UINT16 var_j=ZERO;            /* Loop variable*/
    T_UINT32 bool_format=ZERO;     /* Decision variable for BG_NB_FORMAT*/
    T_UINT16 loop_nbcnt=ZERO;         /* Graph count required for loop*/
    T_UINT32 nb_byte_format=ZERO;
    T_UINT32 nb_decimal_format=ZERO;
    T_UINT32 nb_word_format=ZERO;
    T_UINT16 total_digits = ZERO;
    T_UINT16 one_char_width = ZERO;
    T_UINT16 nb_width = ZERO;
    T_UINT16 nb_height = ZERO;
    T_UINT16 max_width = ZERO;
    T_UINT16 lin_count = ZERO;
    T_BOOL new_line_indication = ZERO;
    T_UINT16 num_dec = ZERO;
    T_CHAR char_a[] = "A";
    T_UINT16 bg_width_temp = ZERO;

    for (loop_bgcnt = ONE; loop_bgcnt <= Bg_cnt; loop_bgcnt++)
    {
        /* Converts the label as array of characters*/
    	OctToStringTrim(Page_settings.Bg_settings[loop_bgcnt-ONE].label, Label_size, labelstring);
        /*hdudispfpdicheck-CheckBarGraph-DB-LLR-001*/
        /* Check for Bar Graph Label*/
        if (!CheckMinMax(Page_settings.Bg_settings[loop_bgcnt-ONE].label, ONE, MAX_LABEL) &&
            (Pdi_error_count < MAX_ERROR_MSG))
        {
            /*Frame the Error Message*/
            BuildErrorMsg(element, labelstring, "LABEL", Error_msg_string[Pdi_error_count]);

            /* Increment the PDI Error Index*/
            ++Pdi_error_count;

        }
		/* Check Bar Graph SDI */
        /*hdudispfpdicheck-CheckBarGraph-DB-LLR-023*/
        if ((TRUE == Config_data.eng_sdi)&&\
		(!CheckMinMax(Page_settings.Bg_settings[loop_bgcnt-ONE].sdi, ZERO , THREE))&&
           (Pdi_error_count < MAX_ERROR_MSG))
        {
              /*Frame the Error Message */
              BuildErrorMsg(element, labelstring, "SDI",
                        Error_msg_string[Pdi_error_count]);

                /* Increment the PDI Error Index */
                ++Pdi_error_count;

        }

        /* Check for Bar graph axis*/
        /*hdudispfpdicheck-CheckBarGraph-DB-LLR-002*/
        /* Bar graph axis does not depend on orientation */
      if ((!CheckAxisMinMax(Page_settings.Bg_settings[loop_bgcnt-ONE].bg_axis.u16_x,\
      ZERO,PANEL_HEIGHT, PANEL_WIDTH) || !CheckAxisMinMax(Page_settings.\
      Bg_settings[loop_bgcnt-ONE].bg_axis.u16_y, ZERO, PANEL_WIDTH,PANEL_HEIGHT))
        		&&(Pdi_error_count < MAX_ERROR_MSG))
        {
            /* Frame the Error Message*/
            BuildErrorMsg(element, labelstring, "BG_AXIS", Error_msg_string[Pdi_error_count]);

            /* Increment the PDI Error Index*/
            ++Pdi_error_count;

        }

        /* Check for BG_ORIEN*/
        /*hdudispfpdicheck-CheckBarGraph-DB-LLR-007*/
        if ((((T_UINT16)Page_settings.Bg_settings[loop_bgcnt - ONE].bg_orien != BG_VERTICAL)  &&
            ((T_UINT16)Page_settings.Bg_settings[loop_bgcnt - ONE].bg_orien != BG_HORIZONTAL)) &&
        	(Pdi_error_count < MAX_ERROR_MSG) && (Bg_parameter_occurrence[loop_bgcnt-ONE]&BIT_ONE))
        {
            /* Frame the Error Message*/
            BuildErrorMsg(element, labelstring, "BG_ORIEN", Error_msg_string[Pdi_error_count]);
            /* Increment the PDI Error Index*/
            ++Pdi_error_count;
        }

        /* Check for Bar graph axis*/
        /*hdudispfpdicheck-CheckBarGraph-DB-LLR-006*/
        if (BG_VERTICAL == Page_settings.Bg_settings[loop_bgcnt - ONE].bg_orien)
        {
    		for (var_j = ONE; var_j <= Page_settings.Bg_settings[loop_bgcnt-ONE].bg_no_lin; var_j++)
            {
            /* Check for BG_LIN_LENGTH*/
			/* bg_lin_length with multiplied with MAG_FACTOR during extraction from PDI, */
			/* so it is divided by FOUR for bg_lin_length check */
            if (!CheckAxisMinMax((T_INT32)((T_INT32)(Page_settings.Bg_settings[loop_bgcnt-ONE].\
            	bg_lin_length[var_j] / (T_INT32)FOUR) + \
				(T_INT32)Page_settings.Bg_settings[loop_bgcnt-1].bg_axis.u16_y), ZERO,
                PANEL_WIDTH,PANEL_HEIGHT) && (Pdi_error_count < MAX_ERROR_MSG))
            {
                /*Frame the Error Message*/
                BuildErrorMsg(element, labelstring, "BG_LIN_LENGTH",
                        Error_msg_string[Pdi_error_count]);

                /* Increment the PDI Error Index*/
                ++Pdi_error_count;
            }
            }


            /* Check for BG_width*/
    		 if (!CheckAxisMinMax(Page_settings.Bg_settings[loop_bgcnt-ONE].bg_width,ONE,\
    				 PANEL_HEIGHT,PANEL_WIDTH) &&(Pdi_error_count < MAX_ERROR_MSG))
    		  {
    		         /* Frame the Error Message*/
    		       BuildErrorMsg(element, labelstring, "BG_WIDTH", Error_msg_string[Pdi_error_count]);

    		       /* Increment the PDI Error Index*/
    		       ++Pdi_error_count;

    		  }
              if ((T_UINT16)ONE == (Page_settings.Bg_settings[loop_bgcnt-ONE].bg_width & ONE))
              {
              	bg_width_temp = (T_UINT16)(Page_settings.Bg_settings[loop_bgcnt-ONE].bg_width + ONE);
              }
    		  else
    		  {
    		     bg_width_temp = Page_settings.Bg_settings[loop_bgcnt-ONE].bg_width;
    		  }

            /* Check for BG_width*/
            if ((!CheckAxisMinMax(bg_width_temp / (T_INT32)TWO +
                 Page_settings.Bg_settings[loop_bgcnt-ONE].bg_axis.u16_x, ZERO,\
    			 PANEL_HEIGHT,PANEL_WIDTH) ||
            	!CheckAxisMinMax(Page_settings.Bg_settings[loop_bgcnt-ONE].bg_axis.u16_x - \
            	bg_width_temp / (T_INT32)TWO , ZERO,
            	 PANEL_HEIGHT,PANEL_WIDTH))&&(Pdi_error_count < MAX_ERROR_MSG))
            {
                /* Frame the Error Message*/
                BuildErrorMsg(element, labelstring, "BG_WIDTH", Error_msg_string[Pdi_error_count]);

                /* Increment the PDI Error Index*/
                ++Pdi_error_count;
            }

        }
        else if(BG_HORIZONTAL == Page_settings.Bg_settings[loop_bgcnt - ONE].bg_orien)
        {
          /*hdudispfpdicheck-CheckBarGraph-DB-LLR-005*/
    		for (var_j = ONE; var_j <= Page_settings.Bg_settings[loop_bgcnt-ONE].bg_no_lin; var_j++)
            {
            /* Check for BG_LIN_LENGTH*/
			/* bg_lin_length with multiplied with MAG_FACTOR during extraction from PDI, */
			/* so it is divided by FOUR for bg_lin_length check */
            if (!CheckAxisMinMax((T_INT32)((T_INT32)(Page_settings.Bg_settings[loop_bgcnt-ONE].\
            	bg_lin_length[var_j] / (T_INT32)FOUR) + \
				(T_INT32)Page_settings.Bg_settings[loop_bgcnt-1].bg_axis.u16_x), ZERO,
                PANEL_HEIGHT,PANEL_WIDTH) && (Pdi_error_count < MAX_ERROR_MSG))
            {
                /*Frame the Error Message*/
                BuildErrorMsg(element, labelstring, "BG_LIN_LENGTH",
                        Error_msg_string[Pdi_error_count]);

                /* Increment the PDI Error Index*/
                ++Pdi_error_count;
            }
            }

            /* Check for BG_width*/
    		 if (!CheckAxisMinMax(Page_settings.Bg_settings[loop_bgcnt-ONE].bg_width,ONE,\
    				 PANEL_WIDTH,PANEL_HEIGHT) &&(Pdi_error_count < MAX_ERROR_MSG))
    		  {
    		         /* Frame the Error Message*/
    		       BuildErrorMsg(element, labelstring, "BG_WIDTH", Error_msg_string[Pdi_error_count]);

    		       /* Increment the PDI Error Index*/
    		       ++Pdi_error_count;

    		  }
              if ((T_UINT16)ONE == (Page_settings.Bg_settings[loop_bgcnt-ONE].bg_width & ONE))
              {
              	bg_width_temp = (T_UINT16)(Page_settings.Bg_settings[loop_bgcnt-ONE].bg_width + ONE);
              }
    		  else
    		  {
    		     bg_width_temp = Page_settings.Bg_settings[loop_bgcnt-ONE].bg_width;
    		  }

            /* Check for BG_width*/
            if ((!CheckAxisMinMax(bg_width_temp / (T_INT32)TWO +
                 Page_settings.Bg_settings[loop_bgcnt-ONE].bg_axis.u16_y, ZERO,\
    			 PANEL_WIDTH,PANEL_HEIGHT) ||
            	!CheckAxisMinMax(Page_settings.Bg_settings[loop_bgcnt-ONE].bg_axis.u16_y - \
            	bg_width_temp / (T_INT32)TWO , ZERO,
            	 PANEL_WIDTH,PANEL_HEIGHT))&&(Pdi_error_count < MAX_ERROR_MSG))
            {
                /* Frame the Error Message*/
                BuildErrorMsg(element, labelstring, "BG_WIDTH", Error_msg_string[Pdi_error_count]);

                /* Increment the PDI Error Index*/
                ++Pdi_error_count;
            }

        }
        else
        {
        	;
        }

        /* Check for BG_no_lin*/
        /*hdudispfpdicheck-CheckBarGraph-DB-LLR-003*/
        if (!CheckMinMax(Page_settings.Bg_settings[loop_bgcnt-ONE].bg_no_lin, ONE, MAX_NO_LIN) &&
            (Pdi_error_count < MAX_ERROR_MSG))
        {
            /* Frame the Error Message*/
            BuildErrorMsg(element, labelstring, "BG_NO_LIN", Error_msg_string[Pdi_error_count]);

            /* Increment the PDI Error Index*/
            ++Pdi_error_count;

        }

        num_dec = (Ap_page1_bar_graphs[loop_bgcnt-ONE].u16Format>>FOUR & SEVEN);

		for (var_j = ONE; var_j <= Page_settings.Bg_settings[loop_bgcnt-ONE].bg_no_lin; var_j++)
        {
            /*hdudispfpdicheck-CheckBarGraph-DB-LLR-004*/
            /* Check for BG_LIN_RANGE*/
            if (!CheckMinMax(Page_settings.Bg_settings[loop_bgcnt-ONE].bg_lin_range[var_j] /
			   (T_INT32)(10 * CalculatePower(10,num_dec)), MIN_LIN_RANGE, MAX_LIN_RANGE)
                 && (Pdi_error_count < MAX_ERROR_MSG))
            {
                /* Frame the Error Message*/
                BuildErrorMsg(element,labelstring,"BG_LIN_RANGE",\
				Error_msg_string[Pdi_error_count]);

                /* Increment the PDI Error Index*/
                ++Pdi_error_count;

            }

        }

        /* Check for BG_NO_LIM*/
        /*hdudispfpdicheck-CheckBarGraph-DB-LLR-008*/
        if (!CheckMinMax(Page_settings.Bg_settings[loop_bgcnt-ONE].bg_no_lim, ONE, MAX_NO_LIM) &&
            (Pdi_error_count < MAX_ERROR_MSG) && \
			(Bg_parameter_occurrence[loop_bgcnt-ONE]&BIT_FIVE))
        {
            /* Frame the Error Message*/
            BuildErrorMsg(element, labelstring, "BG_NO_LIM", Error_msg_string[Pdi_error_count]);

            /* Increment the PDI Error Index*/
            ++Pdi_error_count;

        }


            /* Check for BG_LIM_VAL*/
            /*hdudispfpdicheck-CheckBarGraph-DB-LLR-009*/
            for (var_j = ZERO;var_j < Page_settings.Bg_settings[loop_bgcnt-ONE].bg_no_lim; var_j++)
            {
                if ((!CheckMinMax(Page_settings.Bg_settings[loop_bgcnt-ONE].bg_lim_val_type[var_j],
                	ONE, MAX_LIM_VAL_TYPE) || (!CheckFloatMinMax(Page_settings.
                	Bg_settings[loop_bgcnt-ONE].bg_lim_val[var_j], MIN_RANGE, MAX_RANGE))) && \
    				(Pdi_error_count < MAX_ERROR_MSG) &&
                    (Bg_parameter_occurrence[loop_bgcnt-ONE] & BIT_SIX))
                {
                    /* Frame the Error Message*/
                    BuildErrorMsg(element, labelstring, "BG_LIM_VAL", \
    				Error_msg_string[Pdi_error_count]);
                    /* Increment the PDI Error Index*/
                    ++Pdi_error_count;
                }
            }

            /* Check for BG_LIM_COLOR*/
            /*hdudispfpdicheck-CheckBarGraph-DB-LLR-010*/
            for (var_j = ZERO; var_j < Page_settings.Bg_settings[loop_bgcnt-ONE].bg_no_lim; var_j++)
            {
                 if (((Page_settings.Bg_settings[loop_bgcnt-ONE].bg_lim_color[var_j] != ZERO) &&
                	(!CheckColor(Page_settings.Bg_settings[loop_bgcnt-ONE].bg_lim_color[var_j])))
                	 &&(Pdi_error_count < MAX_ERROR_MSG) &&
                   (Bg_parameter_occurrence[loop_bgcnt-ONE] & BIT_SEVEN))
                 {
                          /* Frame the Error Message*/
                      BuildErrorMsg(element, labelstring, "BG_LIM_COLOR", \
					  Error_msg_string[Pdi_error_count]);

                       /* Increment the PDI Error Index*/
                      ++Pdi_error_count;
        }
        }
            for (var_j = ZERO; var_j < Page_settings.Bg_settings[loop_bgcnt-ONE].bg_no_lim;\
                    var_j++)
            {
                /* Check for BG_LIM_TYPE*/
                /*hdudispfpdicheck-CheckBarGraph-DB-LLR-024*/
                if (!CheckMinMax(Page_settings.Bg_settings[loop_bgcnt-ONE].bg_lim_type[var_j] ,
                             TYPE_NORMAL, TYPE_WARNING) && (Pdi_error_count < MAX_ERROR_MSG))
                {
                    /* Frame the Error Message*/
                    BuildErrorMsg(element, labelstring, "BG_LIM_TYPE",
                            Error_msg_string[Pdi_error_count]);
                    /* Increment the PDI Error Index*/
                    ++Pdi_error_count;
                }
            }

        /* Check for BG_REDX_WIDTH*/
        /*hdudispfpdicheck-CheckBarGraph-DB-LLR-012*/
        if(!CheckAxisMinMax(Page_settings.Bg_settings[loop_bgcnt-ONE].bg_redx_width, ZERO, \
			PANEL_HEIGHT,PANEL_WIDTH) &&(Pdi_error_count < MAX_ERROR_MSG ) && \
		   (Bg_parameter_occurrence[loop_bgcnt-ONE] & BIT_TEN))
        {
            /* Frame the Error Message*/
            BuildErrorMsg(element, labelstring, "BG_REDX_WIDTH",Error_msg_string[Pdi_error_count]);
            /* Increment the PDI Error Index*/
            ++Pdi_error_count;
        }

        /* Check for BG_REDX_HEIGHT*/
        /*hdudispfpdicheck-CheckBarGraph-DB-LLR-013*/
        if (!CheckAxisMinMax(Page_settings.Bg_settings[loop_bgcnt-ONE].bg_redx_height, ZERO,\
			PANEL_WIDTH,PANEL_HEIGHT) &&(Pdi_error_count < MAX_ERROR_MSG) &&
            (Bg_parameter_occurrence[loop_bgcnt-ONE] & BIT_ELEVEN))
        {
            /* Frame the Error Message*/
            BuildErrorMsg(element, labelstring, "BG_REDX_HEIGHT",\
			Error_msg_string[Pdi_error_count]);
            /* Increment the PDI Error Index*/
            ++Pdi_error_count;
        }

        /* Check for BG_REDX_OFFEST_AXIS*/
        /*hdudispfpdicheck-CheckBarGraph-DB-LLR-014*/
       if ((!CheckAxisMinMax2((T_INT16)(Page_settings.Bg_settings[loop_bgcnt-ONE].\
        bg_redx_offset_axis.u16_x),-PANEL_HEIGHT, -PANEL_WIDTH, PANEL_HEIGHT, PANEL_WIDTH)|| \
        !CheckAxisMinMax2((T_INT16)(Page_settings.Bg_settings[loop_bgcnt-ONE].
        bg_redx_offset_axis.u16_y), -PANEL_WIDTH, -PANEL_HEIGHT, PANEL_WIDTH, PANEL_HEIGHT)) \
			&& (Pdi_error_count < MAX_ERROR_MSG)
                && (Bg_parameter_occurrence[loop_bgcnt-ONE] & BIT_TWELVE))
        {
            /* Frame the Error Message*/
            BuildErrorMsg(element, labelstring, "BG_REDX_OFFSET_AXIS",
                    Error_msg_string[Pdi_error_count]);
            /* Increment the PDI Error Index*/
            ++Pdi_error_count;
        }

        /*hdudispfpdicheck-CheckBarGraph-DB-LLR-025*/
       new_line_indication= CalStringParam(Page_settings.Bg_settings[loop_bgcnt-ONE].
                         bg_redx_txt, &max_width, &lin_count );
       max_width= (T_UINT16)(max_width * (T_UINT16)(FontsGetStringWidth((T_UINT8 *)char_a,
          		Page_settings.Bg_settings[loop_bgcnt-ONE].bg_redx_font)));
       lin_count= (T_UINT16)(lin_count *(T_UINT16)(FontsGetFontHeight
                  (Page_settings.Bg_settings[loop_bgcnt-ONE].bg_redx_font)));

       if (ONE == (max_width & 1))
       {
    	   max_width = (T_UINT16)(max_width + ONE);
       }
       else
       {
    	   ;
       }

       /* Check for BG_REDX_OFFEST_AXIS*/
      if (((TRUE ==new_line_indication) ||
        ((!CheckAxisMinMax((T_INT32)((T_INT16)(Page_settings.Bg_settings[loop_bgcnt-ONE].\
       bg_redx_offset_axis.u16_x) + Page_settings.Bg_settings[loop_bgcnt-ONE].bg_redx_axis.u16_x
	   + (max_width/2)),ZERO, PANEL_HEIGHT,PANEL_WIDTH))|| \
    	 (!CheckAxisMinMax((T_INT32)((T_INT16)(Page_settings.Bg_settings[loop_bgcnt-ONE].\
          bg_redx_offset_axis.u16_x) + Page_settings.Bg_settings[loop_bgcnt-ONE].bg_redx_axis.u16_x
		  - (max_width/2)),ZERO, PANEL_HEIGHT,PANEL_WIDTH))||
         (!CheckAxisMinMax((T_INT32)((T_INT16)(Page_settings.Bg_settings[loop_bgcnt-ONE].
         bg_redx_offset_axis.u16_y) +Page_settings.Bg_settings[loop_bgcnt-ONE].bg_redx_axis.u16_y
		 + (lin_count/2)), ZERO, PANEL_WIDTH,PANEL_HEIGHT))  || \
         (!CheckAxisMinMax((T_INT32)((T_INT16)(Page_settings.Bg_settings[loop_bgcnt-ONE].
    	 bg_redx_offset_axis.u16_y) +Page_settings.Bg_settings[loop_bgcnt-ONE].bg_redx_axis.u16_y
		 - (lin_count/2)), ZERO,PANEL_WIDTH,PANEL_HEIGHT))))
		&& (Pdi_error_count < MAX_ERROR_MSG)
        && (Bg_parameter_occurrence[loop_bgcnt-ONE] & BIT_TWELVE))
       {
           /* Frame the Error Message*/
          BuildErrorMsg(element, labelstring, "BG_REDX_OFFSET_AXIS",
                   Error_msg_string[Pdi_error_count]);

           /* Increment the PDI Error Index*/
          ++Pdi_error_count;
       }
        /* Check for BG_REDX_AXIS*/
        /*hdudispfpdicheck-CheckBarGraph-DB-LLR-011*/
      if ((!CheckAxisMinMax(Page_settings.Bg_settings[loop_bgcnt-ONE].bg_redx_axis.u16_x, ZERO,
           PANEL_HEIGHT,PANEL_WIDTH)   || !CheckAxisMinMax(Page_settings.
               Bg_settings[loop_bgcnt-ONE].bg_redx_axis.u16_y, ZERO, PANEL_WIDTH,PANEL_HEIGHT)) &&
        		(Pdi_error_count < MAX_ERROR_MSG) &&
            (Bg_parameter_occurrence[loop_bgcnt-ONE] & BIT_NINE))
        {
            /*Frame the Error Message*/
            BuildErrorMsg(element, labelstring, "BG_REDX_AXIS", Error_msg_string[Pdi_error_count]);
            /* Increment the PDI Error Index*/
            ++Pdi_error_count;

        }
            /* Check for BG_REDX_X_AXIS*/
            /*hdudispfpdicheck-CheckBarGraph-DB-LLR-026*/
	   if ((!CheckAxisMinMax(Page_settings.Bg_settings[loop_bgcnt-ONE].bg_redx_axis.u16_x,
			Page_settings.Bg_settings[loop_bgcnt-ONE].bg_redx_width /(T_INT32)TWO,
			PANEL_HEIGHT,PANEL_WIDTH ) ||
			!CheckAxisMinMax(Page_settings.Bg_settings[loop_bgcnt-ONE].bg_redx_axis.u16_x, ZERO,
		    (PANEL_HEIGHT - (Page_settings.Bg_settings[loop_bgcnt-ONE].bg_redx_width\
			/(T_INT32)TWO)),(PANEL_WIDTH - \
			Page_settings.Bg_settings[loop_bgcnt-ONE].bg_redx_width /(T_INT32)TWO))) &&
		   (Pdi_error_count < MAX_ERROR_MSG) && \
		   (Bg_parameter_occurrence[loop_bgcnt-ONE] & BIT_NINE))
         {
			/*Frame the Error Message*/
			BuildErrorMsg(element, labelstring, "BG_REDX_AXIS", Error_msg_string[Pdi_error_count]);
			/* Increment the PDI Error Index*/
			++Pdi_error_count;

         }
          /* Check for BG_REDX_Y_AXIS*/
          /*hdudispfpdicheck-CheckBarGraph-DB-LLR-027*/
         if ((!CheckAxisMinMax(Page_settings.Bg_settings[loop_bgcnt-ONE].bg_redx_axis.u16_y,
            Page_settings.Bg_settings[loop_bgcnt-ONE].bg_redx_height /(T_INT32)TWO,
            PANEL_WIDTH, PANEL_HEIGHT) ||
            !CheckAxisMinMax(Page_settings.Bg_settings[loop_bgcnt-ONE].bg_redx_axis.u16_y,
            ZERO,(PANEL_WIDTH - (Page_settings.Bg_settings[loop_bgcnt-ONE].bg_redx_height\
			/(T_INT32)TWO)),(PANEL_HEIGHT - \
			Page_settings.Bg_settings[loop_bgcnt-ONE].bg_redx_height /(T_INT32)TWO))) &&
            (Pdi_error_count < MAX_ERROR_MSG) &&
            (Bg_parameter_occurrence[loop_bgcnt-ONE] & BIT_NINE))
            {
				/*Frame the Error Message*/
				BuildErrorMsg(element, labelstring, "BG_REDX_AXIS",\
				Error_msg_string[Pdi_error_count]);
				/* Increment the PDI Error Index*/
				++Pdi_error_count;
             }


        /* Check for BG_REDX_FONT*/
        /*hdudispfpdicheck-CheckBarGraph-DB-LLR-015*/
        if (!CheckFont(Page_settings.Bg_settings[loop_bgcnt-ONE].bg_redx_font) &&
           (Pdi_error_count < MAX_ERROR_MSG) &&
           (Bg_parameter_occurrence[loop_bgcnt-ONE] & BIT_THIRTEEN))
        {
            /* Frame the Error Message*/
            BuildErrorMsg(element, labelstring, "BG_REDX_FONT", Error_msg_string[Pdi_error_count]);
            /* Increment the PDI Error Index*/
            ++Pdi_error_count;

        }

        /* Check for REDX_TXT string length*/
        /*hdudispfpdicheck-CheckBarGraph-DB-LLR-016*/
        if (!CheckString( Page_settings.Bg_settings[loop_bgcnt-ONE].bg_redx_txt,
            MAX_STRING_CHAR_TXT) && (Pdi_error_count < MAX_ERROR_MSG) &&
            (Bg_parameter_occurrence[loop_bgcnt-ONE] & BIT_FOURTEEN))
        {
            /* Frame the Error Message*/
            BuildErrorMsg(element, labelstring, "BG_REDX_TXT",Error_msg_string[Pdi_error_count]);
            /* Increment the PDI Error Index*/
            ++Pdi_error_count;
        }

        for (loop_nbcnt = ONE; loop_nbcnt <= Nb_cnt; loop_nbcnt++)
        {
            if(TRUE == Bg_tracker[loop_bgcnt- ONE][loop_nbcnt- ONE])
            {
                for (var_j = ZERO; var_j < Page_settings.Bg_settings[loop_bgcnt-ONE].bg_no_lim;\
        				var_j++)
                {
                    /*hdudispfpdicheck-CheckBarGraph-DB-LLR-017*/
                    /* Check for BG_NB_LIM_COLOR*/
                    if (((Page_settings.Nb_settings[loop_nbcnt-ONE].nb_lim_color[var_j] != ZERO) &&
                       (!CheckColor(Page_settings.Nb_settings[loop_nbcnt-ONE].nb_lim_color[var_j])))
                    		&& (Pdi_error_count < MAX_ERROR_MSG)
                        && (Bg_parameter_occurrence[loop_bgcnt-ONE] & BIT_EIGHT))
                    {
                        /* Frame the Error Message*/
                        BuildErrorMsg(element, labelstring, "BG_NB_LIM_COLOR",
                                Error_msg_string[Pdi_error_count]);
                        /* Increment the PDI Error Index*/
                        ++Pdi_error_count;
                    }
                }

                /* Check for BG_NB_FONT*/
                /*hdudispfpdicheck-CheckBarGraph-DB-LLR-018*/
                if (!CheckFont(Page_settings.Nb_settings[loop_nbcnt-ONE].nb_font) &&
                	(Pdi_error_count < MAX_ERROR_MSG)
                    && (Bg_parameter_occurrence[loop_bgcnt-ONE] & BIT_FOUR))
                {
                    /* Frame the Error Message*/
                    BuildErrorMsg(element, labelstring, "BG_NB_FONT",
                            Error_msg_string[Pdi_error_count]);
                    /* To prevent hard fault error during initialization, when */
                     /* invalid font is configured, it is initialized to normal font */
                    Ap_page1_bar_graphs[loop_nbcnt-ONE].eFont = E_NO_FONT;
                    /* Increment the PDI Error Index*/
                    ++Pdi_error_count;
                }

                /* Check for BG_NB_FORMAT*/
                /*hdudispfpdicheck-CheckBarGraph-DB-LLR-020*/
                nb_byte_format = Page_settings.Bg_settings[loop_bgcnt-ONE].
                                          bg_nb_format & 0xF00000;
                nb_decimal_format = Page_settings.Bg_settings[loop_bgcnt-ONE].
                                             bg_nb_format & 0x1FC00;
                nb_word_format = Page_settings.Bg_settings[loop_bgcnt-ONE].
                                           bg_nb_format & 0xFF;

                if (((nb_byte_format != NUM_ONEB) && (nb_byte_format != NUM_TWOB) &&
                	(nb_byte_format != NUM_THREEB) && (nb_byte_format != NUM_FOURB)) &&
                    (Pdi_error_count < MAX_ERROR_MSG) &&
                    (Bg_parameter_occurrence[loop_bgcnt-ONE] & BIT_THREE))
                {
                    /* Frame the Error Message*/
                    BuildErrorMsg(element, labelstring, "BG_NB_FORMAT",
                            Error_msg_string[Pdi_error_count]);

                    /* Increment the PDI Error Index*/
                    ++Pdi_error_count;
                }
                 /*hdudispfpdicheck-CheckBarGraph-DB-LLR-021*/
                if(((!CheckDecimalFormat((T_FORMAT)nb_decimal_format)) && \
				(nb_decimal_format != ZERO)) && (Pdi_error_count < MAX_ERROR_MSG) &&
                    (Bg_parameter_occurrence[loop_bgcnt-ONE] & BIT_THREE))
                {
                    /* Frame the Error Message*/
                    BuildErrorMsg(element, labelstring, "BG_NB_FORMAT",
                            Error_msg_string[Pdi_error_count]);

                    /* Increment the PDI Error Index*/
                    ++Pdi_error_count;
                }
                /*hdudispfpdicheck-CheckBarGraph-DB-LLR-022*/
                bool_format = OnlyOneBitSetToOne(nb_word_format) & (nb_word_format <= NUM_EIGHTW);

                if ((ZERO == bool_format) && (Pdi_error_count <= MAX_ERROR_MSG) &&
                    (Bg_parameter_occurrence[loop_bgcnt-ONE] & BIT_THREE))
                {
                    /* Frame the Error Message*/
                    BuildErrorMsg(element, labelstring, "BG_NB_FORMAT",
                            Error_msg_string[Pdi_error_count]);

                    /* Increment the PDI Error Index*/
                    ++Pdi_error_count;
                }
                /* Check for BG_NB_AXIS*/
                /*hdudispfpdicheck-CheckBarGraph-DB-LLR-019*/
                if ((!CheckAxisMinMax(Page_settings.Nb_settings[loop_nbcnt - ONE].nb_axis.u16_x,
                    ZERO, PANEL_HEIGHT,PANEL_WIDTH)||!CheckAxisMinMax(Page_settings.
                    Nb_settings[loop_nbcnt - ONE].nb_axis.u16_y, ZERO, PANEL_WIDTH,PANEL_HEIGHT))
                		&& (Pdi_error_count < MAX_ERROR_MSG)
                    && (Bg_parameter_occurrence[loop_bgcnt-ONE] & BIT_TWO))
                {
                    /* Frame the Error Message*/
                    BuildErrorMsg(element, labelstring, "BG_NB_AXIS",
                            Error_msg_string[Pdi_error_count]);

                    /* Increment the PDI Error Index*/
                    ++Pdi_error_count;

                }
			 /*hdudispfpdicheck-CheckBarGraph-DB-LLR-028*/
                total_digits=(T_UINT16)FindTotalDigits(Page_settings.Bg_settings[loop_bgcnt-ONE].
                        bg_nb_format);
                one_char_width=(T_UINT16)(FontsGetStringWidth((T_UINT8 *)char_a,
                		Page_settings.Nb_settings[loop_nbcnt-ONE].nb_font));
                nb_width=(T_UINT16)(total_digits * one_char_width);
                nb_height=(T_UINT16)(FontsGetFontHeight
                                (Page_settings.Nb_settings[loop_nbcnt-ONE].nb_font));
                if (ONE == (nb_width & 1))
                {
                	nb_width = (T_UINT16)(nb_width + 1);
                }
                else
                {
                	;
                }
                /* Check for BG_NB_AXIS*/
                if ((((!CheckAxisMinMax(Page_settings.Nb_settings[loop_nbcnt - ONE].
                	   nb_axis.u16_x + nb_width/2,
                       ZERO, PANEL_HEIGHT-DEC_SIX ,PANEL_WIDTH-DEC_SIX)) ||
                		(!CheckAxisMinMax(Page_settings.Nb_settings[loop_nbcnt - ONE].
                	   nb_axis.u16_x - nb_width/2,
                	   ZERO, PANEL_HEIGHT-DEC_SIX ,PANEL_WIDTH-DEC_SIX))) ||
                      ((!CheckAxisMinMax(Page_settings.Nb_settings[loop_nbcnt - ONE].nb_axis.u16_y
					  + nb_height/2, ZERO,PANEL_WIDTH,PANEL_HEIGHT)) ||
                      (!CheckAxisMinMax(Page_settings.Nb_settings[loop_nbcnt - ONE].nb_axis.u16_y
					  - nb_height/2, ZERO,PANEL_WIDTH,PANEL_HEIGHT))))
                 		&& (Pdi_error_count < MAX_ERROR_MSG)
                     && (Bg_parameter_occurrence[loop_bgcnt-ONE] & BIT_TWO))
                 {
                     /* Frame the Error Message*/
                     BuildErrorMsg(element, labelstring, "BG_NB_AXIS",
                             Error_msg_string[Pdi_error_count]);
                     /* Increment the PDI Error Index*/
                     ++Pdi_error_count;
                 }
            }
        }
    }
}

/*
 *
 * Function                : CheckRoundDial
 *
 * Description             : This function checks round dial parameters
 *
 * Formal parameter(s)     : T_UINT16 rd_count - count of round dial
 *
 * Return Value            : None
 *
 * Assumption              : None
 *
 */
static void CheckRoundDial()
{
    T_UINT16 var_j = ZERO;       /* Loop variable to iterate over parameter values*/
    T_CHAR element[3] = "RD";        /* Element type*/
    T_CHAR labelstring[5]={0};       /* Variable used to store label in string format*/
	/* Round dial count required for loop to check each parameter of each round dial */
    T_UINT16 loop_rdcnt = ZERO;
    T_UINT32 bool_format = ZERO;        /* Decision variable for RD_NB_FORMAT*/
    T_UINT16 loop_nbcnt = ZERO;         /* Number box count required for loop*/
    T_UINT32 nb_byte_format = ZERO;
    T_UINT32 nb_decimal_format = ZERO;
    T_UINT32 nb_word_format = ZERO;
    T_UINT16 num_dec=0;
    T_UINT16 max_width = ZERO;
    T_UINT16 lin_count = ZERO;
    T_BOOL new_line_indication = ZERO;
    T_CHAR char_a[] = "A";
    T_UINT16 total_digits = ZERO;
    T_UINT16 one_char_width = ZERO;
    T_UINT16 nb_width = ZERO;
    T_UINT16 nb_height = ZERO;

    for (loop_rdcnt=ONE;loop_rdcnt <= Rd_cnt;loop_rdcnt++)
    {
        /* Converts the label as array of characters*/
        /*hdudispfpdicheck-CheckRoundDial-DB-LLR-001*/
    	OctToStringTrim(Page_settings.Rd_settings[loop_rdcnt-ONE].label, Label_size, labelstring);

        /* Check for label*/

        /*hdudispfpdicheck-CheckRoundDial-DB-LLR-002*/
        if (!CheckMinMax(Page_settings.Rd_settings[loop_rdcnt-ONE].label, ONE, MAX_LABEL) &&
            (Pdi_error_count < MAX_ERROR_MSG))
        {
            /* Frame the Error Message*/
            BuildErrorMsg(element, labelstring, "LABEL",Error_msg_string[Pdi_error_count]);

            /* Increment the PDI Error Index*/
            ++Pdi_error_count;

        }
		/* Round Dial SDI */
		/*hdudispfpdicheck-CheckRoundDial-DB-LLR-024*/
		if ((TRUE == Config_data.eng_sdi)&& \
		(!CheckMinMax(Page_settings.Rd_settings[loop_rdcnt-ONE].sdi, ZERO , THREE))&&
         (Pdi_error_count < MAX_ERROR_MSG))
        {
             /*Frame the Error Message */
             BuildErrorMsg(element, labelstring, "SDI",
                        Error_msg_string[Pdi_error_count]);

               /* Increment the PDI Error Index */
                ++Pdi_error_count;

        }

        /* Check RD_ASSOCIATED_LABELS*/
        /*hdudispfpdicheck-CheckRoundDial-DB-LLR-004*/
		for(var_j=ZERO;var_j<ASSOCIALTED_LABEL;var_j++)
        {
           if(!CheckMinMax(Page_settings.Rd_settings[loop_rdcnt-ONE].assc_labels[var_j],\
        	  ONE, MAX_LABEL) &&
			(Page_settings.Rd_settings[loop_rdcnt-ONE].assc_labels[var_j] != ZERO)
             && (Pdi_error_count < MAX_ERROR_MSG))
            {
                        /* Frame the Error Message*/
                        BuildErrorMsg(element, labelstring, "RD_ASSOCIATED_LABELS",\
						Error_msg_string[Pdi_error_count]);

                        /* Increment the PDI Error Index*/
                        ++Pdi_error_count;
            }
        }

        /* Check for RD_AXIS*/
        /*hdudispfpdicheck-CheckRoundDial-DB-LLR-005*/
        if ((!CheckAxisMinMax(Page_settings.Rd_settings[loop_rdcnt-ONE].rd_axis.u16_x, \
		     ZERO, PANEL_HEIGHT, PANEL_WIDTH) \
			||!CheckAxisMinMax(Page_settings.Rd_settings[loop_rdcnt-ONE].rd_axis.u16_y,\
			ZERO, PANEL_WIDTH, PANEL_HEIGHT))\
			&&(Pdi_error_count < MAX_ERROR_MSG))
        {
            /* Frame the Error Message*/
            BuildErrorMsg(element, labelstring, "RD_AXIS",Error_msg_string[Pdi_error_count]);

            /* Increment the PDI Error Index*/
            ++Pdi_error_count;

        }

        /* Check for RD_NO_LIN*/
        /*hdudispfpdicheck-CheckRoundDial-DB-LLR-002*/
        if(!CheckMinMax(Page_settings.Rd_settings[loop_rdcnt-ONE].rd_no_lin, ONE, MAX_NO_LIN) &&
           (Pdi_error_count < MAX_ERROR_MSG))
        {
            /* Frame the Error Message*/
            BuildErrorMsg(element, labelstring, "RD_NO_LIN",Error_msg_string[Pdi_error_count]);

            /* Increment the PDI Error Index*/
            ++Pdi_error_count;

        }
        num_dec = (Ap_page0_dials[loop_rdcnt-ONE].u16Format>>FOUR & SEVEN);

            /* Check for RD_LIN_RANGE*/
            /*hdudispfpdicheck-CheckRoundDial-DB-LLR-006*/
            for(var_j = ONE; var_j <= Page_settings.Rd_settings[loop_rdcnt-ONE].rd_no_lin; var_j++)
            {
                if (!CheckMinMax((Page_settings.Rd_settings[loop_rdcnt-ONE].rd_lin_range[var_j] /
    			   (T_INT32)(ONE_HUNDRED * CalculatePower(10,num_dec))),
                		MIN_LIN_RANGE, MAX_LIN_RANGE) && (Pdi_error_count < MAX_ERROR_MSG))
                {
                    /* Frame the Error Message*/
                    BuildErrorMsg(element, labelstring, "RD_LIN_RANGE",
                            Error_msg_string[Pdi_error_count]);
                    /* Increment the PDI Error Index*/
                    ++Pdi_error_count;

                }
            }

            /* Check for RD_LIN_ANGLE*/
            /*hdudispfpdicheck-CheckRoundDial-DB-LLR-007*/
            for (var_j = ONE; var_j <= Page_settings.Rd_settings[loop_rdcnt-ONE].rd_no_lin; var_j++)
            {
                if (ONE ==(Rd_lin_angle_status[loop_rdcnt-ONE] >> (var_j - 1) & ONE)
                     && (Pdi_error_count < MAX_ERROR_MSG))
                {
                    /* Frame the Error Message*/
                    BuildErrorMsg(element, labelstring, "RD_LIN_ANGLE",
                            Error_msg_string[Pdi_error_count]);
                    /* Increment the PDI Error Index*/
                    ++Pdi_error_count;
                }
            }

        /* Check for RD_NO_PTR*/
        /*hdudispfpdicheck-CheckRoundDial-DB-LLR-002*/
        if (!CheckMinMax(Page_settings.Rd_settings[loop_rdcnt-ONE].rd_no_ptr, ONE, MAX_NO_PTR) &&
            (Pdi_error_count < MAX_ERROR_MSG))
        {
            /*Frame the Error Message*/
            BuildErrorMsg(element, labelstring, "RD_NO_PTR", Error_msg_string[Pdi_error_count]);

            /* Increment the PDI Error Index*/
            ++Pdi_error_count;

        }
    		/* Check for RD_PTR_SHAPE */
    		/*hdudispfpdicheck-CheckRoundDial-DB-LLR-025*/
            for (var_j = ZERO; var_j < Page_settings.Rd_settings[loop_rdcnt-ONE].rd_no_ptr; var_j++)
            {
                if (!CheckMinMax(Page_settings.Rd_settings[loop_rdcnt-ONE].rd_ptr_shape[var_j],
                    FG_CAPITAL_R_POINTER, FG_POINTER_SHAPE12) && (Pdi_error_count < MAX_ERROR_MSG))
                {
                    /* Frame the Error Message*/
                    BuildErrorMsg(element, labelstring, "RD_PTR_SHAPE",
                            Error_msg_string[Pdi_error_count]);

                    /* Increment the PDI Error Index*/
                    ++Pdi_error_count;

                }
            }

            /* Check for RD_PTR_COLOR*/
            /*hdudispfpdicheck-CheckRoundDial-DB-LLR-008*/
            for (var_j = ZERO; var_j < Page_settings.Rd_settings[loop_rdcnt-ONE].rd_no_ptr; var_j++)
            {
                if (!CheckColor(Page_settings.Rd_settings[loop_rdcnt-ONE].rd_ptr_color[var_j])
                	&& (Pdi_error_count < MAX_ERROR_MSG))
                {
                    /* Frame the Error Message*/
                    BuildErrorMsg(element, labelstring, "RD_PTR_COLOR",
                            Error_msg_string[Pdi_error_count]);

                    /* Increment the PDI Error Index*/
                    ++Pdi_error_count;

                }
            }

            /* Check for RD_PTR_SCALE*/
            /*hdudispfpdicheck-CheckRoundDial-DB-LLR-009*/
            for (var_j = ZERO; var_j < Page_settings.Rd_settings[loop_rdcnt-ONE].rd_no_ptr; var_j++)
            {
                if ((!CheckAxisMinMax(Page_settings.Rd_settings[loop_rdcnt-ONE].
                    rd_ptr_scale[var_j][ZERO],ZERO, PANEL_HEIGHT, PANEL_WIDTH)|| \
    				!CheckAxisMinMax(Page_settings.Rd_settings[loop_rdcnt-ONE].
                    rd_ptr_scale[var_j][ONE], ZERO, PANEL_WIDTH, PANEL_HEIGHT)) \
    				&& (Pdi_error_count < MAX_ERROR_MSG))
                {
                    /* Frame the Error Message*/
                    BuildErrorMsg(element,labelstring,"RD_PTR_SCALE",\
    				Error_msg_string[Pdi_error_count]);

                    /* Increment the PDI Error Index*/
                    ++Pdi_error_count;

                }
            }

            /* Check for RD_PTR_SCALE_OFFSET*/
            /*hdudispfpdicheck-CheckRoundDial-DB-LLR-010*/
            /* Note: since offset can be positive or negative, Pdi check is done for */
            /* the range -PANEL_HEIGHT to +PANEL_HEIGHT */
            for (var_j = ZERO; var_j < Page_settings.Rd_settings[loop_rdcnt-ONE].rd_no_ptr; var_j++)
            {
               if ((!CheckAxisMinMax2((T_INT16)Page_settings.Rd_settings[loop_rdcnt-ONE].\
    		   rd_ptr_scale_offset[var_j][ZERO], -PANEL_HEIGHT,-PANEL_WIDTH,PANEL_HEIGHT,PANEL_WIDTH) ||
    		   !CheckAxisMinMax2((T_INT16)Page_settings.Rd_settings
                	[loop_rdcnt-ONE].rd_ptr_scale_offset[var_j][ONE], -PANEL_WIDTH,-PANEL_HEIGHT,
                    PANEL_WIDTH,PANEL_HEIGHT)) &&\
    			   (Pdi_error_count < MAX_ERROR_MSG))
                {
                   /* Frame the Error Message*/
                   BuildErrorMsg(element, labelstring, "RD_PTR_SCALE_OFFSET",
                            Error_msg_string[Pdi_error_count]);

                    /* Increment the PDI Error Index*/
                    ++Pdi_error_count;

                }
            }

            /* Check RD_PTR_ROT*/
            /*hdudispfpdicheck-CheckRoundDial-DB-LLR-011*/
            for (var_j = ZERO; var_j < Page_settings.Rd_settings[loop_rdcnt-ONE].rd_no_ptr; var_j++)
            {
            if (!CheckMinMax((T_INT16)Page_settings.Rd_settings[loop_rdcnt-ONE].
                rd_ptr_rot[var_j], MIN_LIN_ANGLE , MAX_LIN_ANGLE ) &&
				(Pdi_error_count < MAX_ERROR_MSG))
                {
                    /* Frame the Error Message*/
                   BuildErrorMsg(element, labelstring,"RD_PTR_ROT",\
				               Error_msg_string[Pdi_error_count]);

                    /* Increment the PDI Error Index*/
                    ++Pdi_error_count;
                }
            else
            {
                Ap_page0_dials[loop_rdcnt-ONE].rotAngle[var_j]=
                CVT(Page_settings.Rd_settings[loop_rdcnt-ONE].rd_ptr_rot[var_j]);
            }
            }
        /* Check for RD_LENGTH*/
        /*hdudispfpdicheck-CheckRoundDial-DB-LLR-002*/
        if (!CheckAxisMinMax(Page_settings.Rd_settings[loop_rdcnt-ONE].rd_length, \
            ZERO, PANEL_HEIGHT, PANEL_WIDTH) && (Pdi_error_count < MAX_ERROR_MSG))
        {
            /* Frame the Error Message*/
            BuildErrorMsg(element, labelstring, "RD_LENGTH",Error_msg_string[Pdi_error_count]);

            /* Increment the PDI Error Index*/
            ++Pdi_error_count;

        }

        /* Check RD_VERN*/
        /*hdudispfpdicheck-CheckRoundDial-DB-LLR-002*/
        if (!CheckMinMax(Page_settings.Rd_settings[loop_rdcnt-ONE].rd_vern, ZERO, ONE) &&
                    (Pdi_error_count < MAX_ERROR_MSG))
        {
            /* Frame the Error Message*/
            BuildErrorMsg(element, labelstring, "RD_VERN",Error_msg_string[Pdi_error_count]);

            /* Increment the PDI Error Index*/
            ++Pdi_error_count;

        }
        /*hdudispfpdicheck-CheckRoundDial-DB-LLR-002*/
        if (!CheckVerPos((T_FLOAT)Page_settings.Rd_settings[loop_rdcnt-ONE].rd_vern_pos) &&
                     (Pdi_error_count < MAX_ERROR_MSG))
        {
            /* Frame the Error Message*/
            BuildErrorMsg(element, labelstring, "RD_VERN_POS",Error_msg_string[Pdi_error_count]);

            /* Increment the PDI Error Index*/
            ++Pdi_error_count;

        }

        /* Check for RD_NO_LIM*/
        /*hdudispfpdicheck-CheckRoundDial-DB-LLR-003*/
        if (!CheckMinMax(Page_settings.Rd_settings[loop_rdcnt-ONE].rd_no_lim, ONE, MAX_NO_LIM) &&
            (Pdi_error_count < MAX_ERROR_MSG) &&
            (Rd_parameter_occurrence[loop_rdcnt-ONE] & BIT_FOUR))
        {
            /* Frame the Error Message*/
            BuildErrorMsg(element, labelstring, "RD_NO_LIM", Error_msg_string[Pdi_error_count]);

            /* Increment the PDI Error Index*/
            ++Pdi_error_count;

        }
            /* Check for RD_LIM_VAL*/
            /*hdudispfpdicheck-CheckRoundDial-DB-LLR-012*/
            for (var_j = ZERO; var_j < Page_settings.Rd_settings[loop_rdcnt-ONE].rd_no_lim; var_j++)
            {
                if ((!CheckMinMax(Page_settings.Rd_settings[loop_rdcnt-ONE].rd_lim_val_type[var_j],
                    ONE, MAX_LIM_VAL_TYPE)||!CheckFloatMinMax(Page_settings.\
					Rd_settings[loop_rdcnt-ONE].rd_lim_val[var_j],
					MIN_RANGE, MAX_RANGE))  && (Pdi_error_count < MAX_ERROR_MSG) &&
                    (Rd_parameter_occurrence[loop_rdcnt-ONE] & BIT_FIVE))
                {
                    /* Frame the Error Message*/
                    BuildErrorMsg(element,labelstring,"RD_LIM_VAL",\
					Error_msg_string[Pdi_error_count]);

                    /* Increment the PDI Error Index*/
                    ++Pdi_error_count;

                }
            }

            /* Check for RD_LIM_TYPE*/
			/*hdudispfpdicheck-CheckRoundDial-DB-LLR-026*/
            for (var_j = ZERO;var_j < Page_settings.Rd_settings[loop_rdcnt-ONE].rd_no_lim; var_j++)
            {
                if (!CheckMinMax(Page_settings.Rd_settings[loop_rdcnt-1].rd_lim_type[var_j] ,
                        TYPE_NORMAL, TYPE_WARNING) && (Pdi_error_count < MAX_ERROR_MSG))
                {
                    /* Frame the Error Message*/
                    BuildErrorMsg(element,labelstring,"RD_LIM_TYPE",\
					Error_msg_string[Pdi_error_count]);

                    /* Increment the PDI Error Index*/
                    ++Pdi_error_count;
                }
            }

            /* Check for RD_LIM_COLOR*/
            /*hdudispfpdicheck-CheckRoundDial-DB-LLR-023*/
            for (var_j = ZERO;var_j < Page_settings.Rd_settings[loop_rdcnt-ONE].rd_no_lim; var_j++)
            {
               if (((Page_settings.Rd_settings[loop_rdcnt-ONE].rd_lim_color[var_j] !=
               ZERO) && (!CheckColor(Page_settings.Rd_settings[loop_rdcnt-ONE].\
            	rd_lim_color[var_j]))) &&  (Pdi_error_count < MAX_ERROR_MSG) &&
               (Rd_parameter_occurrence[loop_rdcnt-ONE] & BIT_SIX))
            {
                /* Frame the Error Message*/
                BuildErrorMsg(element, labelstring, "RD_LIM_COLOR", \
				Error_msg_string[Pdi_error_count]);

                /* Increment the PDI Error Index*/
                ++Pdi_error_count;

            }
            }
        /* Check for RD_REDX_AXIS*/
        /*hdudispfpdicheck-CheckRoundDial-DB-LLR-013*/
        if ((!CheckAxisMinMax(Page_settings.Rd_settings[loop_rdcnt-ONE].rd_redx_axis.u16_x,
            ZERO, PANEL_HEIGHT,PANEL_WIDTH)   || \
			!CheckAxisMinMax(Page_settings.Rd_settings[loop_rdcnt-ONE].
            rd_redx_axis.u16_y, ZERO, PANEL_WIDTH,PANEL_HEIGHT))  && \
			(Pdi_error_count < MAX_ERROR_MSG)
            && (Rd_parameter_occurrence[loop_rdcnt-ONE] & BIT_SEVEN))
        {
            /* Frame the Error Message*/
            BuildErrorMsg(element, labelstring, "RD_REDX_AXIS", Error_msg_string[Pdi_error_count]);

            /* Increment the PDI Error Index*/
            ++Pdi_error_count;

        }

        /* Check for RD_REDX_WIDTH*/
        /*hdudispfpdicheck-CheckRoundDial-DB-LLR-014*/
        if (!CheckAxisMinMax(Page_settings.Rd_settings[loop_rdcnt-ONE].rd_redx_width, \
			 ZERO, PANEL_HEIGHT, PANEL_WIDTH) &&
            (Pdi_error_count < MAX_ERROR_MSG)&&(Rd_parameter_occurrence[loop_rdcnt-1]&BIT_EIGHT))
        {
            /* Frame the Error Message*/
            BuildErrorMsg(element, labelstring, "RD_REDX_WIDTH",Error_msg_string[Pdi_error_count]);

            /* Increment the PDI Error Index*/
            ++Pdi_error_count;

        }

        /* Check for RD_REDX_HEIGHT*/
        /*hdudispfpdicheck-CheckRoundDial-DB-LLR-015*/
        if (!CheckAxisMinMax(Page_settings.Rd_settings[loop_rdcnt-ONE].rd_redx_height, \
			 ZERO, PANEL_WIDTH,PANEL_HEIGHT)&&
            (Pdi_error_count < MAX_ERROR_MSG)&& \
			(Rd_parameter_occurrence[loop_rdcnt-ONE] & BIT_NINE))
        {
            /* Frame the Error Message*/
            BuildErrorMsg(element, labelstring, "RD_REDX_HEIGHT", \
			Error_msg_string[Pdi_error_count]);

            /* Increment the PDI Error Index*/
            ++Pdi_error_count;

        }

        /* Check for RD_REDX_OFFSET_AXIS*/
        /*hdudispfpdicheck-CheckRoundDial-DB-LLR-016*/
        if((!CheckAxisMinMax2(((T_INT16)Page_settings.Rd_settings[loop_rdcnt-ONE].\
		rd_redx_offset_axis.u16_x),-PANEL_HEIGHT, -PANEL_WIDTH, PANEL_HEIGHT, PANEL_WIDTH)|| \
		!CheckAxisMinMax2(((T_INT16)Page_settings.Rd_settings[loop_rdcnt-ONE].
            rd_redx_offset_axis.u16_y), -PANEL_WIDTH, -PANEL_HEIGHT, \
			PANEL_WIDTH, PANEL_HEIGHT)) &&\
			(Pdi_error_count < MAX_ERROR_MSG) &&
            (Rd_parameter_occurrence[loop_rdcnt-ONE] & BIT_TEN))
        {
            /* Frame the Error Message*/
            BuildErrorMsg(element, labelstring, "RD_REDX_OFFSET_AXIS",
                    Error_msg_string[Pdi_error_count]);

            /* Increment the PDI Error Index*/
            ++Pdi_error_count;

        }
        /* Check for RD_REDX_X_AXIS*/
        /*hdudispfpdicheck-CheckRoundDial-DB-LLR-027*/
        if ((!CheckAxisMinMax(Page_settings.Rd_settings[loop_rdcnt-ONE].rd_redx_axis.u16_x,
        		Page_settings.Rd_settings[loop_rdcnt-ONE].rd_redx_width /(T_INT32)TWO,
				PANEL_HEIGHT,PANEL_WIDTH )   ||
			!CheckAxisMinMax(Page_settings.Rd_settings[loop_rdcnt-ONE].rd_redx_axis.u16_x,ZERO,
		(PANEL_HEIGHT-(Page_settings.Rd_settings[loop_rdcnt-ONE].rd_redx_width /(T_INT32)TWO)),
		(PANEL_WIDTH - (Page_settings.Rd_settings[loop_rdcnt-ONE].rd_redx_width /(T_INT32)TWO))))
        		&& (Pdi_error_count < MAX_ERROR_MSG)
            && (Rd_parameter_occurrence[loop_rdcnt-ONE] & BIT_SEVEN))
        {
            /* Frame the Error Message*/
            BuildErrorMsg(element, labelstring, "RD_REDX_AXIS", Error_msg_string[Pdi_error_count]);

            /* Increment the PDI Error Index*/
            ++Pdi_error_count;

        }

        /* Check for RD_REDX_Y_AXIS*/
        /*hdudispfpdicheck-CheckRoundDial-DB-LLR-028*/
        if ((!CheckAxisMinMax(Page_settings.Rd_settings[loop_rdcnt-ONE].rd_redx_axis.u16_y,
        		Page_settings.Rd_settings[loop_rdcnt-ONE].rd_redx_height /(T_INT32)TWO,
				PANEL_WIDTH ,PANEL_HEIGHT )   ||
			!CheckAxisMinMax(Page_settings.Rd_settings[loop_rdcnt-ONE].rd_redx_axis.u16_y,ZERO,
		(PANEL_WIDTH-(Page_settings.Rd_settings[loop_rdcnt-ONE].rd_redx_height /(T_INT32)TWO)),
		(PANEL_HEIGHT - (Page_settings.Rd_settings[loop_rdcnt-ONE].rd_redx_height /(T_INT32)TWO))))
        		&& (Pdi_error_count < MAX_ERROR_MSG)
            && (Rd_parameter_occurrence[loop_rdcnt-ONE] & BIT_SEVEN))
        {
            /* Frame the Error Message*/
            BuildErrorMsg(element, labelstring, "RD_REDX_AXIS", Error_msg_string[Pdi_error_count]);

            /* Increment the PDI Error Index*/
            ++Pdi_error_count;

        }

         /*hdudispfpdicheck-CheckRoundDial-DB-LLR-029*/
        new_line_indication= CalStringParam(Page_settings.Rd_settings[loop_rdcnt-ONE].\
		                     rd_redx_txt, &max_width, &lin_count );

        max_width=  (T_UINT16)(max_width * (T_UINT16)(FontsGetStringWidth((T_UINT8 *)char_a,
           		Page_settings.Rd_settings[loop_rdcnt-ONE].rd_redx_font)));
        lin_count=  (T_UINT16)(lin_count *(T_UINT16)(FontsGetFontHeight
                   (Page_settings.Rd_settings[loop_rdcnt-ONE].rd_redx_font)));
        if (ONE == (max_width & 1))
        {
     	   max_width = (T_UINT16)(max_width + 1);
        }
        else
        {
        	;
        }

        /* Check for RD_REDX_OFFSET_AXIS*/
       if (((TRUE == new_line_indication) ||
         ((!CheckAxisMinMax((T_INT32)((T_INT16)(Page_settings.Rd_settings[loop_rdcnt-ONE].\
        rd_redx_offset_axis.u16_x) + Page_settings.Rd_settings[loop_rdcnt-ONE].rd_redx_axis.u16_x
 	   + (max_width/2)),ZERO, PANEL_HEIGHT,PANEL_WIDTH))|| \
     	 (!CheckAxisMinMax((T_INT32)((T_INT16)(Page_settings.Rd_settings[loop_rdcnt-ONE].\
          rd_redx_offset_axis.u16_x) + Page_settings.Rd_settings[loop_rdcnt-ONE].rd_redx_axis.u16_x
 		  - (max_width/2)),ZERO, PANEL_HEIGHT,PANEL_WIDTH))||
          (!CheckAxisMinMax((T_INT32)((T_INT16)(Page_settings.Rd_settings[loop_rdcnt-ONE].
          rd_redx_offset_axis.u16_y) +Page_settings.Rd_settings[loop_rdcnt-ONE].rd_redx_axis.u16_y
 		 + (lin_count/2)), ZERO, PANEL_WIDTH,PANEL_HEIGHT))  || \
          (!CheckAxisMinMax((T_INT32)((T_INT16)(Page_settings.Rd_settings[loop_rdcnt-ONE].
     	 rd_redx_offset_axis.u16_y) +Page_settings.Rd_settings[loop_rdcnt-ONE].rd_redx_axis.u16_y
 		 - (lin_count/2)), ZERO,PANEL_WIDTH,PANEL_HEIGHT))))
 		&& (Pdi_error_count < MAX_ERROR_MSG)
         && (Rd_parameter_occurrence[loop_rdcnt-ONE] & BIT_TEN))
        {
            /* Frame the Error Message*/
           BuildErrorMsg(element, labelstring, "RD_REDX_OFFSET_AXIS",
                    Error_msg_string[Pdi_error_count]);
            /* Increment the PDI Error Index*/
           ++Pdi_error_count;
        }

        /* Check for RD_REDX_FONT*/
        /*hdudispfpdicheck-CheckRoundDial-DB-LLR-030*/
        if (!CheckFont(Page_settings.Rd_settings[loop_rdcnt-ONE].rd_redx_font) &&
        	(Pdi_error_count < MAX_ERROR_MSG) &&
            (Rd_parameter_occurrence[loop_rdcnt-ONE] & BIT_ELEVEN))
        {
            /* Frame the Error Message*/
            BuildErrorMsg(element, labelstring, "RD_REDX_FONT",
                    Error_msg_string[Pdi_error_count]);

            /* Increment the PDI Error Index*/
            ++Pdi_error_count;

        }

        /* Check for RD_REDX_TXT*/
        /*hdudispfpdicheck-CheckRoundDial-DB-LLR-017*/
        if (!CheckString(Page_settings.Rd_settings[loop_rdcnt-ONE].rd_redx_txt, \
        	MAX_STRING_CHAR_TXT)&& (Pdi_error_count < MAX_ERROR_MSG)&& \
		   (Rd_parameter_occurrence[loop_rdcnt-ONE] & BIT_TWELVE))
        {
            /* Frame the Error Message*/
            BuildErrorMsg(element, labelstring, "RD_REDX_TXT", Error_msg_string[Pdi_error_count]);

            /* Increment the PDI Error Index*/
            ++Pdi_error_count;

        }

         /* Number box count required for loop*/
        for (loop_nbcnt = ONE; loop_nbcnt <= Nb_cnt; loop_nbcnt++)
        {
            if(TRUE == Rd_tracker[loop_rdcnt-ONE][loop_nbcnt-ONE])
            {
                /* Check for RD_NB_FONT*/
                /*hdudispfpdicheck-CheckRoundDial-DB-LLR-019*/
                if (!CheckFont(Page_settings.Nb_settings[loop_nbcnt - ONE].nb_font) &&
                	(Pdi_error_count < MAX_ERROR_MSG) &&
                    (Rd_parameter_occurrence[loop_rdcnt-ONE] & BIT_THREE))
                {
                    /* Frame the Error Message*/
                    BuildErrorMsg(element, labelstring, "RD_NB_FONT",
                            Error_msg_string[Pdi_error_count]);
                    /* To prevent hard fault error during initialization, when invalid */
                    /* font is configured, it is initialized to normal font */
                    Page_num_boxes[loop_nbcnt - ONE].eFont = E_NO_FONT;
                    /* Increment the PDI Error Index*/
                    ++Pdi_error_count;
                }

                /* Check for RD_NB_FORMAT*/
                /*hdudispfpdicheck-CheckRoundDial-DB-LLR-020*/
                nb_byte_format = Page_settings.Rd_settings[loop_rdcnt-ONE].
                                          rd_nb_format & 0xF00000;
                nb_decimal_format = Page_settings.Rd_settings[loop_rdcnt-ONE].
                                          rd_nb_format & 0x1FC00;
                nb_word_format = Page_settings.Rd_settings[loop_rdcnt-ONE].
                                          rd_nb_format & 0xFF;

                if (((nb_byte_format != NUM_ONEB) && (nb_byte_format != NUM_TWOB) &&
                	(nb_byte_format != NUM_THREEB) && (nb_byte_format != NUM_FOURB)) &&
                    (Pdi_error_count < MAX_ERROR_MSG) &&
                    (Rd_parameter_occurrence[loop_rdcnt-ONE] & BIT_TWO))
                {
                    /* Frame the Error Message*/
                    BuildErrorMsg(element, labelstring, "RD_NB_FORMAT",
                            Error_msg_string[Pdi_error_count]);

                    /* Increment the PDI Error Index*/
                    ++Pdi_error_count;

                }
                 /*hdudispfpdicheck-CheckRoundDial-DB-LLR-021*/
                if (((!CheckDecimalFormat((T_FORMAT)nb_decimal_format))
					&& (nb_decimal_format != ZERO))
                   && (Pdi_error_count < MAX_ERROR_MSG)
                   && (Rd_parameter_occurrence[loop_rdcnt-ONE] & BIT_TWO))
                {
                    /* Frame the Error Message*/
                    BuildErrorMsg(element, labelstring, "RD_NB_FORMAT",
                            Error_msg_string[Pdi_error_count]);

                    /* Increment the PDI Error Index*/
                    ++Pdi_error_count;

                 }
                 /*hdudispfpdicheck-CheckRoundDial-DB-LLR-022*/
                bool_format = OnlyOneBitSetToOne(nb_word_format) & (nb_word_format <= NUM_EIGHTW);

                if ((ZERO == bool_format) && (Pdi_error_count < MAX_ERROR_MSG)
                        && (Rd_parameter_occurrence[loop_rdcnt-ONE] & BIT_TWO))
                {
                    /* Frame the Error Message*/
                    BuildErrorMsg(element, labelstring, "RD_NB_FORMAT",
                            Error_msg_string[Pdi_error_count]);

                    /* Increment the PDI Error Index*/
                    ++Pdi_error_count;

                }

		       /*hdudispfpdicheck-CheckRoundDial-DB-LLR-018*/
               /* Check for RD_NB_AXIS*/
                if ((!CheckAxisMinMax(Page_settings.Nb_settings[loop_nbcnt-ONE].nb_axis.u16_x,
                    ZERO, PANEL_HEIGHT,PANEL_WIDTH)|| \
					!CheckAxisMinMax(Page_settings.Nb_settings[loop_nbcnt-ONE].
                    nb_axis.u16_y, ZERO, PANEL_WIDTH,PANEL_HEIGHT))\
					&&(Pdi_error_count < MAX_ERROR_MSG)&&
                    (Rd_parameter_occurrence[loop_rdcnt-ONE] & BIT_ONE))
                {
                    /* Frame the Error Message*/
                    BuildErrorMsg(element, labelstring, "RD_NB_AXIS",
                            Error_msg_string[Pdi_error_count]);

                    /* Increment the PDI Error Index*/
                    ++Pdi_error_count;

                }

                total_digits=(T_UINT16)FindTotalDigits(Page_settings.Rd_settings[loop_rdcnt-ONE].
                        rd_nb_format);
                one_char_width=(T_UINT16)(FontsGetStringWidth((T_UINT8 *)char_a,
                		Page_settings.Nb_settings[loop_nbcnt-ONE].nb_font));
                nb_width=(T_UINT16)(total_digits * one_char_width);
                nb_height=(T_UINT16)(FontsGetFontHeight
                                (Page_settings.Nb_settings[loop_nbcnt-ONE].nb_font));
             if (ONE == (nb_width & 1))
             {
             	nb_width = (T_UINT16)(nb_width + 1);
             }
             else
             {
             	;
             }
                /* Check for RD_NB_AXIS*/
             if ((((!CheckAxisMinMax(Page_settings.Nb_settings[loop_nbcnt - ONE].
             	   nb_axis.u16_x + nb_width/2,
                    ZERO, PANEL_HEIGHT-DEC_SIX ,PANEL_WIDTH-DEC_SIX)) ||
             		(!CheckAxisMinMax(Page_settings.Nb_settings[loop_nbcnt - ONE].
             	   nb_axis.u16_x - nb_width/2,
             	   ZERO, PANEL_HEIGHT-DEC_SIX ,PANEL_WIDTH-DEC_SIX))) ||
                   ((!CheckAxisMinMax(Page_settings.Nb_settings[loop_nbcnt - ONE].nb_axis.u16_y
					  + nb_height/2, ZERO,PANEL_WIDTH,PANEL_HEIGHT)) ||
                   (!CheckAxisMinMax(Page_settings.Nb_settings[loop_nbcnt - ONE].nb_axis.u16_y
					  - nb_height/2, ZERO,PANEL_WIDTH,PANEL_HEIGHT))))
                 		&& (Pdi_error_count < MAX_ERROR_MSG)
                     && (Rd_parameter_occurrence[loop_rdcnt-ONE] & BIT_ONE))
                 {
                     /* Frame the Error Message*/
                     BuildErrorMsg(element, labelstring, "RD_NB_AXIS",
                             Error_msg_string[Pdi_error_count]);
                     /* Increment the PDI Error Index*/
                     ++Pdi_error_count;
                 }
            }
        }
    }
}

/*
 *
 * Function                : CheckNumberBox
 *
 * Description             : This function checks number box parameters
 *
 * Formal parameter(s)     : T_UINT16 nb_count - count of number boxes
 *
 * Return Value            : None
 *
 * Assumption              : None
 *
 */
static void CheckNumberBox()
{
    T_UINT16 var_j=ZERO;                     /* Loop variable NB_NO_LIM_VAL*/
    T_CHAR element[3] = "NB";                /* Element type*/
    T_CHAR labelstring[5]={0};               /* Variable used to store label in string format*/
    T_UINT16 loop_nbcnt = ZERO;              /* Number Box count required for loop*/
    T_UINT32 bool_format = ZERO;             /* Decision variable for NB_FORMAT*/
    T_UINT32 nb_byte_format = ZERO;
    T_UINT32 nb_decimal_format = ZERO;
    T_UINT32 nb_word_format = ZERO;
    T_UINT16 string_width = ZERO;
    T_UINT16 string_height = ZERO;
    T_UINT16 total_digits = ZERO;
    T_UINT16 one_char_width = ZERO;
    T_UINT16 nb_width = ZERO;
    T_UINT16 nb_height = ZERO;
    T_CHAR char_a[] = "A";

    for (loop_nbcnt = ONE; loop_nbcnt <= Nb_cnt; loop_nbcnt++)
    {
        if(TRUE == Nb_tracker[loop_nbcnt- ONE][loop_nbcnt- ONE])
        {
            /* Converts the label as array of characters*/
            /*hdudispfpdicheck-CheckNumberBox-DB-LLR-001*/
        	OctToStringTrim(Page_settings.Nb_settings[loop_nbcnt-ONE].label,
			                Label_size,labelstring);

            /* Check label*/
            if (!CheckMinMax(Page_settings.Nb_settings[loop_nbcnt-ONE].label, ONE,MAX_LABEL)&&
                (Pdi_error_count < MAX_ERROR_MSG))
            {
                /* Frame the Error Message*/
                BuildErrorMsg(element, labelstring, "LABEL", Error_msg_string[Pdi_error_count]);

                /* Increment the PDI Error Index*/
                ++Pdi_error_count;

            }
			/* Check for Number box SDI */
			/*hdudispfpdicheck-CheckNumberBox-DB-LLR-013*/
			if ((TRUE == Config_data.eng_sdi)&&\
			(!CheckMinMax(Page_settings.Nb_settings[loop_nbcnt-ONE].sdi, ZERO , THREE))&&
               (Pdi_error_count < MAX_ERROR_MSG))
            {
                 /*Frame the Error Message */
                   BuildErrorMsg(element, labelstring, "SDI",
                        Error_msg_string[Pdi_error_count]);

                  /* Increment the PDI Error Index */
                  ++Pdi_error_count;

            }

            /* Check for NB_FORMAT*/
            /*hdudispfpdicheck-CheckNumberBox-DB-LLR-004*/
            nb_byte_format = Page_settings.Nb_settings[loop_nbcnt-ONE].
                                       nb_format & 0xF00000;
            nb_decimal_format = Page_settings.Nb_settings[loop_nbcnt-ONE].
                                       nb_format & 0x1FC00;
            nb_word_format = Page_settings.Nb_settings[loop_nbcnt-ONE].
                                       nb_format & 0xFF;

            if (((nb_byte_format != NUM_ONEB) && (nb_byte_format != NUM_TWOB) &&
            	(nb_byte_format != NUM_THREEB) && (nb_byte_format != NUM_FOURB)) &&
                 (Pdi_error_count < MAX_ERROR_MSG) &&
                 (Nb_parameter_occurrence[loop_nbcnt-ONE] & BIT_ONE))
            {
                /* Frame the Error Message*/
                BuildErrorMsg(element, labelstring, "NB_FORMAT",Error_msg_string[Pdi_error_count]);

                /* Increment the PDI Error Index*/
                ++Pdi_error_count;

            }
             /*hdudispfpdicheck-CheckNumberBox-DB-LLR-005*/
            if(((!CheckDecimalFormat((T_FORMAT)nb_decimal_format)) && (nb_decimal_format != ZERO))
                 &&  (Pdi_error_count < MAX_ERROR_MSG)
                 && (Nb_parameter_occurrence[loop_nbcnt-ONE] & BIT_ONE))
            {
                /* Frame the Error Message*/
                BuildErrorMsg(element, labelstring, "NB_FORMAT",Error_msg_string[Pdi_error_count]);

                /* Increment the PDI Error Index*/
                ++Pdi_error_count;

            }
            /*hdudispfpdicheck-CheckNumberBox-DB-LLR-006*/
            bool_format = OnlyOneBitSetToOne(nb_word_format) & (nb_word_format <= NUM_EIGHTW);

            if ((ZERO == bool_format) && (Pdi_error_count < MAX_ERROR_MSG) &&
                    (Nb_parameter_occurrence[loop_nbcnt-ONE] & BIT_ONE))
            {
                /* Frame the Error Message*/
               BuildErrorMsg(element, labelstring, "NB_FORMAT",Error_msg_string[Pdi_error_count]);

            /* Increment the PDI Error Index*/
            ++Pdi_error_count;

            }

            /* Check for NB_FONT*/
            /*hdudispfpdicheck-CheckNumberBox-DB-LLR-015*/
            if (!CheckFont(Page_settings.Nb_settings[loop_nbcnt-ONE].nb_font) &&
               (Pdi_error_count < MAX_ERROR_MSG) &&
                (Nb_parameter_occurrence[loop_nbcnt-ONE] & BIT_TWO))
            {
                /* Frame the Error Message*/
                BuildErrorMsg(element, labelstring, "NB_FONT", Error_msg_string[Pdi_error_count]);
                /* To prevent hard fault error during initialization, when invalid font */
                /* it is initialized to normal font */

                Page_num_boxes[loop_nbcnt - ONE].eFont = E_NO_FONT;
                /* Increment the PDI Error Index*/
                ++Pdi_error_count;
            }
	        /* Check for nb_axis*/
            /*hdudispfpdicheck-CheckNumberBox-DB-LLR-003*/
            if((!CheckAxisMinMax(Page_settings.Nb_settings[loop_nbcnt-ONE].nb_axis.u16_x,\
			ZERO,PANEL_HEIGHT,PANEL_WIDTH)||
			!CheckAxisMinMax(Page_settings.Nb_settings[loop_nbcnt-ONE].nb_axis.u16_y,
			ZERO, PANEL_WIDTH,PANEL_HEIGHT)) && (Pdi_error_count < MAX_ERROR_MSG))
            {
                /* Frame the Error Message*/
                BuildErrorMsg(element, labelstring, "NB_AXIS", Error_msg_string[Pdi_error_count]);

                /* Increment the PDI Error Index*/
                ++Pdi_error_count;
            }

           /*hdudispfpdicheck-CheckNumberBox-DB-LLR-016*/

            total_digits=(T_UINT16)FindTotalDigits(Page_settings.
            		Nb_settings[loop_nbcnt-ONE].nb_format);
            one_char_width=(T_UINT16)(FontsGetStringWidth((T_UINT8 *)char_a,
            		Page_settings.Nb_settings[loop_nbcnt-ONE].nb_font));
            nb_width= (T_UINT16)(total_digits * one_char_width);
            nb_height=(T_UINT16)(FontsGetFontHeight
                                  (Page_settings.Nb_settings[loop_nbcnt-ONE].nb_font));
                if (ONE == (nb_width & 1))
                {
                	nb_width = (T_UINT16)(nb_width + 1);
                }
                else
                {
                	;
                }
            /* Check for nb_axis*/
                if ((((!CheckAxisMinMax(Page_settings.Nb_settings[loop_nbcnt - ONE].
                      nb_axis.u16_x + nb_width/2,
                       ZERO, PANEL_HEIGHT-DEC_SIX ,PANEL_WIDTH-DEC_SIX)) ||
                   (!CheckAxisMinMax(Page_settings.Nb_settings[loop_nbcnt - ONE].
                      nb_axis.u16_x - nb_width/2,
                      ZERO, PANEL_HEIGHT-DEC_SIX ,PANEL_WIDTH-DEC_SIX))) ||
                   ((!CheckAxisMinMax(Page_settings.Nb_settings[loop_nbcnt - ONE].nb_axis.u16_y
	             + nb_height/2, ZERO,PANEL_WIDTH,PANEL_HEIGHT)) ||
                   (!CheckAxisMinMax(Page_settings.Nb_settings[loop_nbcnt - ONE].nb_axis.u16_y
	           - nb_height/2, ZERO,PANEL_WIDTH,PANEL_HEIGHT))))
                    && (Pdi_error_count < MAX_ERROR_MSG))
            {
                /* Frame the Error Message*/
                BuildErrorMsg(element, labelstring, "NB_AXIS", Error_msg_string[Pdi_error_count]);

                /* Increment the PDI Error Index*/
                ++Pdi_error_count;

            }

            /* Check for nb_no_lim*/
            /*hdudispfpdicheck-CheckNumberBox-DB-LLR-002*/
            if(!CheckMinMax(Page_settings.Nb_settings[loop_nbcnt-ONE].nb_no_lim, ONE, MAX_NO_LIM)&&
               (Pdi_error_count < MAX_ERROR_MSG) &&
               (Nb_parameter_occurrence[loop_nbcnt-ONE] & BIT_THREE))
            {
                /* Frame the Error Message*/
                BuildErrorMsg(element, labelstring, "NB_NO_LIM", \
				Error_msg_string[Pdi_error_count]);

                /* Increment the PDI Error Index*/
                ++Pdi_error_count;

            }

                /* Check for nb_no_lim_val*/
                /*hdudispfpdicheck-CheckNumberBox-DB-LLR-007*/
                for (var_j = ZERO;var_j < Page_settings.Nb_settings[loop_nbcnt-ONE].nb_no_lim;
       				 var_j++)
                {
                    if ((!CheckMinMax(Page_settings.Nb_settings[loop_nbcnt-ONE].
                        nb_lim_val_type[var_j],ONE, MAX_LIM_VAL_TYPE) || \
    					(!CheckFloatMinMax(Page_settings.Nb_settings[loop_nbcnt-ONE].\
    					nb_lim_val[var_j], MIN_RANGE, MAX_RANGE))) &&
						(Pdi_error_count < MAX_ERROR_MSG) &&
                        (Nb_parameter_occurrence[loop_nbcnt-ONE] & BIT_FOUR))
                    {
                        /* Frame the Error Message*/
                        BuildErrorMsg(element, labelstring, "NB_LIM_VAL", \
    					Error_msg_string[Pdi_error_count]);

                        /* Increment the PDI Error Index*/
                        ++Pdi_error_count;

                    }
                }

                /* Check for NB_LIM_COLOR*/
                /*hdudispfpdicheck-CheckNumberBox-DB-LLR-013*/
                for (var_j = ZERO;var_j < Page_settings.Nb_settings[loop_nbcnt-ONE].nb_no_lim;
       				var_j++)
                {
                if (((Page_settings.Nb_settings[loop_nbcnt-ONE].nb_lim_color[var_j] != ZERO) &&
                	(!CheckColor(Page_settings.Nb_settings[loop_nbcnt-ONE].nb_lim_color[var_j])))
                	&& (Pdi_error_count < MAX_ERROR_MSG) &&
                    (Nb_parameter_occurrence[loop_nbcnt-ONE] & BIT_FIVE))
                {
                    /* Frame the Error Message*/
                    BuildErrorMsg(element,labelstring,"NB_LIM_COLOR",\
    				Error_msg_string[Pdi_error_count]);

                    /* Increment the PDI Error Index*/
                    ++Pdi_error_count;
                }
                }
				/*hdudispfpdicheck-CheckNumberBox-DB-LLR-017*/
                for (var_j = ZERO;var_j < Page_settings.Nb_settings[loop_nbcnt-ONE].nb_no_lim;
     				var_j++)
                {
                     if (!CheckMinMax(Page_settings.Nb_settings[loop_nbcnt-ONE].nb_lim_type[var_j],
                          TYPE_NORMAL, TYPE_WARNING) && (Pdi_error_count < MAX_ERROR_MSG))
                     {
                            /* Frame the Error Message*/
                           BuildErrorMsg(element,labelstring,"NB_LIM_TYPE",\
                           Error_msg_string[Pdi_error_count]);
                            /* Increment the PDI Error Index*/
                            ++Pdi_error_count;
                     }
                }
            /* Check for NB_REDX_AXIS*/
            /*hdudispfpdicheck-CheckNumberBox-DB-LLR-008*/
            if ((!CheckAxisMinMax(Page_settings.Nb_settings[loop_nbcnt-ONE].nb_redx_axis.u16_x,
                ZERO, PANEL_HEIGHT,PANEL_WIDTH)|| \
				!CheckAxisMinMax(Page_settings.Nb_settings[loop_nbcnt-ONE].
                nb_redx_axis.u16_y, ZERO, PANEL_WIDTH,PANEL_HEIGHT)) &&\
				(Pdi_error_count < MAX_ERROR_MSG) &&
                (Nb_parameter_occurrence[loop_nbcnt-ONE] & BIT_SIX))
            {
            /* Frame the Error Message*/
                BuildErrorMsg(element, labelstring, "NB_REDX_AXIS",
                        Error_msg_string[Pdi_error_count]);

                /* Increment the PDI Error Index*/
                ++Pdi_error_count;

            }

                string_width=(T_UINT16)(FontsGetStringWidth(Page_settings.
                		Nb_settings[loop_nbcnt-ONE].nb_redx_txt,
                          Page_settings.Nb_settings[loop_nbcnt-ONE].nb_redx_font));
                string_height=(T_UINT16)(FontsGetFontHeight
                          (Page_settings.Nb_settings[loop_nbcnt-ONE].nb_redx_font));
                if (ONE == (string_width & 1))
                {
                	string_width = (T_UINT16)(string_width + 1);
                }
                else
                {
                	;
                }

            /* Check for NB_REDX_Y_AXIS*/
            /*hdudispfpdicheck-CheckNumberBox-DB-LLR-018*/
            if ((!CheckAxisMinMax(Page_settings.Nb_settings[loop_nbcnt-ONE].nb_redx_axis.u16_x,
            		string_width/2, PANEL_HEIGHT,PANEL_WIDTH)|| \
				!CheckAxisMinMax(Page_settings.Nb_settings[loop_nbcnt-ONE].
                nb_redx_axis.u16_x, ZERO, PANEL_HEIGHT - (string_width/2),
				PANEL_WIDTH - (string_width/2))) &&\
				(Pdi_error_count < MAX_ERROR_MSG) &&
                (Nb_parameter_occurrence[loop_nbcnt-ONE] & BIT_SIX))
            {
            /* Frame the Error Message*/
                BuildErrorMsg(element, labelstring, "NB_REDX_AXIS",
                        Error_msg_string[Pdi_error_count]);

                /* Increment the PDI Error Index*/
                ++Pdi_error_count;
            }

            /* Check for NB_REDX_Y_AXIS*/
            /*hdudispfpdicheck-CheckNumberBox-DB-LLR-019*/
            if ((!CheckAxisMinMax(Page_settings.Nb_settings[loop_nbcnt-ONE].nb_redx_axis.u16_y,
            		string_height/2,PANEL_WIDTH,PANEL_HEIGHT)|| \
				!CheckAxisMinMax(Page_settings.Nb_settings[loop_nbcnt-ONE].
                nb_redx_axis.u16_y, ZERO, PANEL_WIDTH - (string_height/2),
				PANEL_HEIGHT - (string_height/2))) &&\
				(Pdi_error_count < MAX_ERROR_MSG) &&
                (Nb_parameter_occurrence[loop_nbcnt-ONE] & BIT_SIX))
            {
            /* Frame the Error Message*/
                BuildErrorMsg(element, labelstring, "NB_REDX_AXIS",
                        Error_msg_string[Pdi_error_count]);

                /* Increment the PDI Error Index*/
                ++Pdi_error_count;

            }

            /* Check for nb_redx_width*/
            /*hdudispfpdicheck-CheckNumberBox-DB-LLR-009*/
            if (!CheckAxisMinMax((T_INT16)Page_settings.Nb_settings[loop_nbcnt-ONE].nb_redx_width, \
				 ZERO, PANEL_HEIGHT, PANEL_WIDTH)&&
                (Pdi_error_count < MAX_ERROR_MSG) &&
                 (Nb_parameter_occurrence[loop_nbcnt-ONE] & BIT_SEVEN))
            {
                /* Frame the Error Message*/
                BuildErrorMsg(element, labelstring, "NB_REDX_WIDTH",
                        Error_msg_string[Pdi_error_count]);

                /* Increment the PDI Error Index*/
                ++Pdi_error_count;
            }

            if (!CheckAxisMinMax((T_INT16)(Page_settings.Nb_settings[loop_nbcnt-ONE].
            	nb_redx_axis.u16_x -Page_settings.Nb_settings[loop_nbcnt-ONE].nb_redx_width/2), \
				 ZERO, PANEL_HEIGHT, PANEL_WIDTH)&&
                (Pdi_error_count < MAX_ERROR_MSG) &&
                 (Nb_parameter_occurrence[loop_nbcnt-ONE] & BIT_SEVEN))
            {
                /* Frame the Error Message*/
                BuildErrorMsg(element, labelstring, "NB_REDX_WIDTH",
                        Error_msg_string[Pdi_error_count]);

                /* Increment the PDI Error Index*/
                ++Pdi_error_count;
            }

            /* Check for NB_REDX_HEIGHT*/
            /*hdudispfpdicheck-CheckNumberBox-DB-LLR-010*/
            if (!CheckAxisMinMax((T_INT16)
            (Page_settings.Nb_settings[loop_nbcnt-ONE].nb_redx_height),ZERO,
				 PANEL_WIDTH,PANEL_HEIGHT) &&
                (Pdi_error_count < MAX_ERROR_MSG) &&
                 (Nb_parameter_occurrence[loop_nbcnt-ONE] & BIT_EIGHT))
            {
                /* Frame the Error Message*/
                BuildErrorMsg(element, labelstring, "NB_REDX_HEIGHT",
                        Error_msg_string[Pdi_error_count]);

                /* Increment the PDI Error Index*/
                ++Pdi_error_count;
            }

            if (!CheckAxisMinMax((T_INT16)(
            	Page_settings.Nb_settings[loop_nbcnt-ONE].nb_redx_axis.u16_y -
            	Page_settings.Nb_settings[loop_nbcnt-ONE].nb_redx_height/2),ZERO,
				 PANEL_WIDTH,PANEL_HEIGHT) &&
                (Pdi_error_count < MAX_ERROR_MSG) &&
                 (Nb_parameter_occurrence[loop_nbcnt-ONE] & BIT_EIGHT))
            {
                /* Frame the Error Message*/
                BuildErrorMsg(element, labelstring, "NB_REDX_HEIGHT",
                        Error_msg_string[Pdi_error_count]);

                /* Increment the PDI Error Index*/
                ++Pdi_error_count;

            }

         /* Check for NB_OFFSET_AXIS*/
         /*hdudispfpdicheck-CheckNumberBox-DB-LLR-011*/
         if ((!CheckAxisMinMax2((T_INT16)Page_settings.Nb_settings[loop_nbcnt-ONE].
             nb_redx_offset_axis.u16_x,-PANEL_HEIGHT,-PANEL_WIDTH, PANEL_HEIGHT,PANEL_WIDTH)||\
				!CheckAxisMinMax2((T_INT16)Page_settings.Nb_settings[loop_nbcnt-ONE].
             nb_redx_offset_axis.u16_y, -PANEL_WIDTH,-PANEL_HEIGHT, \
			 PANEL_WIDTH,PANEL_HEIGHT))&& (Pdi_error_count<MAX_ERROR_MSG)&&
             (Nb_parameter_occurrence[loop_nbcnt-ONE] & BIT_NINE))
         {
             /* Frame the Error Message*/
             BuildErrorMsg(element, labelstring, "NB_REDX_OFFSET_AXIS", \
				Error_msg_string[Pdi_error_count]);

                /* Increment the PDI Error Index*/
                ++Pdi_error_count;

            }

			string_width=(T_UINT16)(FontsGetStringWidth(Page_settings.Nb_settings[loop_nbcnt-ONE].
                      nb_redx_txt,Page_settings.Nb_settings[loop_nbcnt-ONE].nb_redx_font));
            string_height=(T_UINT16)(FontsGetFontHeight
                      (Page_settings.Nb_settings[loop_nbcnt-ONE].nb_redx_font));
            if (ONE == (string_width & 1))
            {
            	string_width = (T_UINT16)(string_width + 1);
            }
            else
            {
            	;
            }

			/*hdudispfpdicheck-CheckNumberBox-DB-LLR-020*/
            /* Check for NB_REDX_OFFEST_X_AXIS*/
           if ((!CheckAxisMinMax((T_INT16)(Page_settings.Nb_settings[loop_nbcnt-ONE].
             nb_redx_axis.u16_x +
			 (T_INT16)Page_settings.Nb_settings[loop_nbcnt-ONE].nb_redx_offset_axis.u16_x),\
    		 string_width/2, PANEL_HEIGHT,PANEL_WIDTH)|| \
            !CheckAxisMinMax2((T_INT16)(Page_settings.Nb_settings[loop_nbcnt-ONE].
			 nb_redx_axis.u16_x + (T_INT16)
            Page_settings.Nb_settings[loop_nbcnt-ONE].nb_redx_offset_axis.u16_x),\
			(-PANEL_HEIGHT+string_width/2),(-PANEL_WIDTH+string_width/2),
    		(PANEL_HEIGHT-string_width/2),(PANEL_WIDTH-string_width/2))) &&
            (Pdi_error_count < MAX_ERROR_MSG)&&(Nb_parameter_occurrence[loop_nbcnt-ONE] &
			  BIT_NINE))
            {
                /* Frame the Error Message*/
                BuildErrorMsg(element, labelstring, "NB_REDX_OFFSET_AXIS",
                        Error_msg_string[Pdi_error_count]);
                /* Increment the PDI Error Index*/
                ++Pdi_error_count;
            }

		   /*hdudispfpdicheck-CheckNumberBox-DB-LLR-021*/
           /* Check for NB_REDX_OFFEST_Y_AXIS*/
          if ((!CheckAxisMinMax((T_INT16)(Page_settings.Nb_settings[loop_nbcnt-ONE].
		  nb_redx_axis.u16_y + (T_INT16)Page_settings.Nb_settings[loop_nbcnt-ONE].
		  nb_redx_offset_axis.u16_y), string_height/2,\
		  PANEL_WIDTH,PANEL_HEIGHT)|| \
          !CheckAxisMinMax2((T_INT16)(Page_settings.Nb_settings[loop_nbcnt-ONE].nb_redx_axis.u16_y +
          (T_INT16)Page_settings.Nb_settings[loop_nbcnt-ONE].nb_redx_offset_axis.u16_y),
		  (-PANEL_WIDTH+string_height/2),(-PANEL_HEIGHT+string_height/2),
		  (PANEL_WIDTH-string_height/2), (PANEL_HEIGHT-string_height/2))) &&
          (Pdi_error_count < MAX_ERROR_MSG) \
          && (Nb_parameter_occurrence[loop_nbcnt-ONE] & BIT_NINE))
           {
               /* Frame the Error Message*/
               BuildErrorMsg(element, labelstring, "NB_REDX_OFFSET_AXIS",
                       Error_msg_string[Pdi_error_count]);
               /* Increment the PDI Error Index*/
               ++Pdi_error_count;
           }
            /* Check for NB_REDX_FONT*/
            /*hdudispfpdicheck-CheckNumberBox-DB-LLR-022*/
            if (!CheckFont(Page_settings.Nb_settings[loop_nbcnt-ONE].nb_redx_font) &&
            	(Pdi_error_count < MAX_ERROR_MSG) &&
                (Nb_parameter_occurrence[loop_nbcnt-ONE] & BIT_TEN))
            {
                /* Frame the Error Message*/
                BuildErrorMsg(element,labelstring,"NB_REDX_FONT",\
				Error_msg_string[Pdi_error_count]);

                /* Increment the PDI Error Index*/
                ++Pdi_error_count;

            }

            /* Check for nb_redx_txt*/
            /*hdudispfpdicheck-CheckNumberBox-DB-LLR-012*/
            if (!CheckString( Page_settings.Nb_settings[loop_nbcnt-ONE].nb_redx_txt,
                MAX_STRING_CHAR_TXT) && (Pdi_error_count < MAX_ERROR_MSG)
                && (Nb_parameter_occurrence[loop_nbcnt-ONE] & BIT_ELEVEN))
            {
                /* Frame the Error Message*/
                BuildErrorMsg(element, labelstring, "NB_REDX_TXT",
                        Error_msg_string[Pdi_error_count]);

                /* Increment the PDI Error Index*/
                ++Pdi_error_count;

            }
        }
    }
}

/*
 *
 * Function                : CheckCarrotGraph
 *
 * Description             : This function checks Carrot Graph parameters
 *
 * Formal parameter(s)     : None
 *
 * Return Value            : None
 *
 * Assumption              : None
 *
 */
static void CheckCarrotGraph(void)
{
    T_CHAR element[3] = "CG";    /* Element type*/
    T_CHAR labelstring[5]={0};     /* Variable used to store label in string format*/
    T_UINT16 loop_cgcnt = ZERO;        /* Graph count required for loop*/
    T_UINT16 var_j = ZERO;            /*Loop variable*/
    T_UINT32 bool_format = ZERO;     /* Decision variable for CG_NB_FORMAT*/
    T_UINT16 loop_nbcnt = ZERO;         /* Graph count required for loop*/
    T_UINT32 nb_byte_format = ZERO;
    T_UINT32 nb_decimal_format = ZERO;
    T_UINT32 nb_word_format = ZERO;
    T_UINT16 nb_width = ZERO;
    T_UINT16 nb_height = ZERO;
    T_UINT16 max_width = ZERO;
    T_UINT16 lin_count = ZERO;
    T_BOOL new_line_indication = ZERO;
    T_UINT16 total_digits = ZERO;
    T_UINT16 one_char_width = ZERO;
    T_UINT16 num_dec = ZERO;
    T_CHAR char_a[] = "A";

    for (loop_cgcnt = ONE; loop_cgcnt <= Cg_cnt; loop_cgcnt++)
    {
        /* Converts the label as array of characters*/
         /*hdudispfpdicheck-CheckCarrotGraph-DB-LLR-001*/
    	OctToStringTrim(Page_settings.Cg_settings[loop_cgcnt-ONE].label, Label_size, labelstring);

        /* Check for Carrot Graph Label*/
         /*hdudispfpdicheck-CheckCarrotGraph-DB-LLR-002*/
        if (!CheckMinMax(Page_settings.Cg_settings[loop_cgcnt-ONE].label, ONE, MAX_LABEL) &&
            (Pdi_error_count < MAX_ERROR_MSG))
        {
            /*Frame the Error Message*/
            BuildErrorMsg(element, labelstring, "LABEL", Error_msg_string[Pdi_error_count]);

            /* Increment the PDI Error Index*/
            ++Pdi_error_count;

        }

		/* Check for Carrot Graph SDIs */
		/*hdudispfpdicheck-CheckCarrotGraph-DB-LLR-024*/
		if ((TRUE == Config_data.eng_sdi)&& \
		(!CheckMinMax(Page_settings.Cg_settings[loop_cgcnt-ONE].sdi, ZERO , THREE))&&
           (Pdi_error_count < MAX_ERROR_MSG))
        {
           /*Frame the Error Message */
            BuildErrorMsg(element, labelstring, "SDI",
                        Error_msg_string[Pdi_error_count]);

              /* Increment the PDI Error Index */
             ++Pdi_error_count;
        }
        /* Check for CG_ORIEN*/
         /*hdudispfpdicheck-CheckCarrotGraph-DB-LLR-011*/
        if (((BG_VERTICAL != Page_settings.Cg_settings[loop_cgcnt - ONE].cg_orien ) &&
             (BG_HORIZONTAL != Page_settings.Cg_settings[loop_cgcnt - ONE].cg_orien)) &&
        	 (Pdi_error_count < MAX_ERROR_MSG))
        {
            /* Frame the Error Message*/
            BuildErrorMsg(element, labelstring, "CG_ORIEN", Error_msg_string[Pdi_error_count]);

            /* Increment the PDI Error Index*/
            ++Pdi_error_count;

        }

        /* Check for Carrot graph axis*/
         /*hdudispfpdicheck-CheckCarrotGraph-DB-LLR-004*/
        /* Carrot graph axis does not depend on orientation */
        if ((!CheckAxisMinMax(Page_settings.Cg_settings[loop_cgcnt-ONE].cg_axis.u16_x, \
		     ZERO, PANEL_HEIGHT,PANEL_WIDTH)|| \
             !CheckAxisMinMax(Page_settings.Cg_settings[loop_cgcnt-ONE].cg_axis.u16_y,ZERO, \
			 PANEL_WIDTH,PANEL_HEIGHT))&&(Pdi_error_count < MAX_ERROR_MSG))
        {
            /* Frame the Error Message*/
            BuildErrorMsg(element, labelstring, "CG_AXIS", Error_msg_string[Pdi_error_count]);

            /* Increment the PDI Error Index*/
            ++Pdi_error_count;
        }

        /* Check for CG_no_lin*/
         /*hdudispfpdicheck-CheckCarrotGraph-DB-LLR-002*/
        if (!CheckMinMax(Page_settings.Cg_settings[loop_cgcnt-ONE].cg_no_lin, ONE,MAX_NO_LIN)&&
            (Pdi_error_count < MAX_ERROR_MSG))
        {
            /* Frame the Error Message*/
            BuildErrorMsg(element, labelstring, "CG_NO_LIN", Error_msg_string[Pdi_error_count]);

            /* Increment the PDI Error Index*/
            ++Pdi_error_count;

        }
        num_dec = (Ap_page2_carrot[loop_cgcnt-ONE].u16Format>>FOUR & SEVEN);
        for (var_j = ONE; var_j <= Page_settings.Cg_settings[loop_cgcnt-ONE].cg_no_lin; var_j++)
        {
            /* Check for CG_LIN_RANGE*/
             /*hdudispfpdicheck-CheckCarrotGraph-DB-LLR-005*/
            if ((!CheckMinMax((Page_settings.Cg_settings[loop_cgcnt-ONE].cg_lin_range[var_j] /
               (T_INT32)(ONE_HUNDRED * CalculatePower(10,num_dec))),MIN_LIN_RANGE, MAX_LIN_RANGE))
                    && (Pdi_error_count < MAX_ERROR_MSG))
            {
                /* Frame the Error Message*/
                BuildErrorMsg(element, labelstring,"CG_LIN_RANGE",\
                Error_msg_string[Pdi_error_count]);
                /* Increment the PDI Error Index*/
                ++Pdi_error_count;
            }

            /* Check for CG_LIN_OFFSET*/
             /*hdudispfpdicheck-CheckCarrotGraph-DB-LLR-006*/
            /* cg_lin_offset with multiplied with MAG_FACTOR during extraction from PDI, */
            /* so it is divided by FOUR for cg_lin_offset check */
		if ( BG_VERTICAL == Page_settings.Cg_settings[loop_cgcnt - ONE].cg_orien)

        {
            if (!CheckAxisMinMax((T_INT32)ABS(((T_INT32)(Page_settings.\
			     Cg_settings[loop_cgcnt-1].cg_lin_offset[var_j] / (T_INT32)FOUR) +
            		Page_settings.Cg_settings[loop_cgcnt-1].cg_axis.u16_y)),
                ZERO, PANEL_WIDTH,PANEL_HEIGHT) && (Pdi_error_count < MAX_ERROR_MSG))
            {
                /* Frame the Error Message*/
                BuildErrorMsg(element,labelstring,"CG_LIN_OFFSET",\
				Error_msg_string[Pdi_error_count]);

                /* Increment the PDI Error Index*/
                ++Pdi_error_count;
            }
		}
		else if ( BG_HORIZONTAL == Page_settings.Cg_settings[loop_cgcnt - ONE].cg_orien)

        {
            if (!CheckAxisMinMax((T_INT32)ABS(((T_INT32)(Page_settings.\
			     Cg_settings[loop_cgcnt-1].cg_lin_offset[var_j] / (T_INT32)FOUR) +
            		Page_settings.Cg_settings[loop_cgcnt-1].cg_axis.u16_x)),
                ZERO,PANEL_HEIGHT,PANEL_WIDTH) && (Pdi_error_count < MAX_ERROR_MSG))
            {
                /* Frame the Error Message*/
                BuildErrorMsg(element,labelstring,"CG_LIN_OFFSET",\
				Error_msg_string[Pdi_error_count]);

                /* Increment the PDI Error Index*/
                ++Pdi_error_count;
            }
		}
		else
		{
			; /* Do nothing */
        }
        }
        /* Check for CG_NO_PTR*/
         /*hdudispfpdicheck-CheckCarrotGraph-DB-LLR-002*/
        if (!CheckMinMax(Page_settings.Cg_settings[loop_cgcnt-ONE].cg_no_ptr, ONE, MAX_NO_PTR) &&
            (Pdi_error_count < MAX_ERROR_MSG))
        {
            /* Frame the Error Message*/
            BuildErrorMsg(element, labelstring, "CG_NO_PTR", Error_msg_string[Pdi_error_count]);

            /* Increment the PDI Error Index*/
            ++Pdi_error_count;
        }

		/* Check for CG_PTR_SHAPE  */
        /*hdudispfpdicheck-CheckCarrotGraph-DB-LLR-007*/
		for (var_j = ZERO; var_j < Page_settings.Cg_settings[loop_cgcnt-ONE].cg_no_ptr; var_j++)
        {
            if (!CheckMinMax(Page_settings.Cg_settings[loop_cgcnt-1].cg_ptr_shape[var_j] ,
            		FG_CAPITAL_R_POINTER, FG_POINTER_SHAPE12) && (Pdi_error_count < MAX_ERROR_MSG))
            {
                /* Frame the Error Message*/
                BuildErrorMsg(element, labelstring, "CG_PTR_SHAPE",
                        Error_msg_string[Pdi_error_count]);

                    /* Increment the PDI Error Index*/
                    ++Pdi_error_count;
                }
            }

            for (var_j = ZERO; var_j < Page_settings.Cg_settings[loop_cgcnt-ONE].cg_no_ptr; var_j++)
            {
                /* Check for CG_PTR_COLOR*/
				/*hdudispfpdicheck-CheckCarrotGraph-DB-LLR-033*/
                if (!CheckColor(Page_settings.Cg_settings[loop_cgcnt-ONE].cg_ptr_color[var_j])
                    && (Pdi_error_count < MAX_ERROR_MSG))
                {
                    /* Frame the Error Message*/
                    BuildErrorMsg(element,labelstring,"CG_PTR_COLOR",\
    				Error_msg_string[Pdi_error_count]);

                    /* Increment the PDI Error Index*/
                    ++Pdi_error_count;
                }

                /* Check for CG_PTR_SCALE*/
                 /*hdudispfpdicheck-CheckCarrotGraph-DB-LLR-008*/
                if ((!CheckAxisMinMax(Page_settings.Cg_settings[loop_cgcnt-ONE].
                    cg_ptr_scale[var_j][ZERO],ZERO, PANEL_HEIGHT,PANEL_WIDTH)||\
    				!CheckAxisMinMax(Page_settings.Cg_settings[loop_cgcnt-ONE].
                    cg_ptr_scale[var_j][ONE], ZERO, PANEL_WIDTH, PANEL_HEIGHT)) && \
    				(Pdi_error_count < MAX_ERROR_MSG))
                    {
                        /* Frame the Error Message*/
                        BuildErrorMsg(element, labelstring, "CG_PTR_SCALE",
                                Error_msg_string[Pdi_error_count]);

                        /* Increment the PDI Error Index*/
                        ++Pdi_error_count;

                    }

                /* Check for CG_PTR_SCALE_OFFSET*/
                 /*hdudispfpdicheck-CheckCarrotGraph-DB-LLR-009*/
                if ((!CheckAxisMinMax2((T_INT16)Page_settings.Cg_settings[loop_cgcnt-ONE].\
    			cg_ptr_scale_offset[var_j][ZERO],-PANEL_HEIGHT, -PANEL_WIDTH,
				PANEL_HEIGHT, PANEL_WIDTH)|| \
                !CheckAxisMinMax2((T_INT16)Page_settings.Cg_settings[loop_cgcnt-ONE].
                cg_ptr_scale_offset[var_j][ONE], -PANEL_WIDTH, -PANEL_HEIGHT,
				PANEL_WIDTH, PANEL_HEIGHT))
                && (Pdi_error_count < MAX_ERROR_MSG))
                    {
                        /* Frame the Error Message*/
                        BuildErrorMsg(element, labelstring, "CG_PTR_SCALE_OFFSET",
                                Error_msg_string[Pdi_error_count]);

                        /* Increment the PDI Error Index*/
                        ++Pdi_error_count;

                    }

                /* Check for CG_PTR_ROT*/
                 /*hdudispfpdicheck-CheckCarrotGraph-DB-LLR-010*/
                    if (!CheckMinMax(Page_settings.Cg_settings[loop_cgcnt-ONE].
                    cg_ptr_rot[var_j],MIN_LIN_ANGLE, MAX_LIN_ANGLE) &&
					(Pdi_error_count < MAX_ERROR_MSG))
                    {
                       /* Frame the Error Message*/
                       BuildErrorMsg(element, labelstring, "CG_PTR_ROT",
                            Error_msg_string[Pdi_error_count]);

                      /* Increment the PDI Error Index*/
                      ++Pdi_error_count;

                   }
                    else
                    {
                        Ap_page2_carrot[loop_cgcnt-ONE].rotAngle[var_j]=
                        CVT(Page_settings.Cg_settings[loop_cgcnt-ONE].cg_ptr_rot[var_j]);
                    }
                }

        /* Check for CG_NO_LIM*/
         /*hdudispfpdicheck-CheckCarrotGraph-DB-LLR-003*/
        if (!CheckMinMax(Page_settings.Cg_settings[loop_cgcnt-ONE].cg_no_lim, ONE, MAX_NO_LIM) &&
                (Pdi_error_count < MAX_ERROR_MSG) &&
                (Cg_parameter_occurrence[loop_cgcnt-ONE] & BIT_FOUR))
        {
            /* Frame the Error Message*/
            BuildErrorMsg(element, labelstring, "CG_NO_LIM", Error_msg_string[Pdi_error_count]);

            /* Increment the PDI Error Index*/
            ++Pdi_error_count;

        }
            /* Check for CG_LIM_VAL*/
            for (var_j = ZERO; var_j < Page_settings.Cg_settings[loop_cgcnt-ONE].cg_no_lim; var_j++)
            {
                 /*hdudispfpdicheck-CheckCarrotGraph-DB-LLR-012*/
                if ((!CheckMinMax(Page_settings.Cg_settings[loop_cgcnt-ONE].cg_lim_val_type[var_j],
                    ONE, MAX_LIM_VAL_TYPE) ||  !CheckFloatMinMax(Page_settings.\
    				Cg_settings[loop_cgcnt-ONE].cg_lim_val[var_j], MIN_RANGE, MAX_RANGE)) && \
    				(Pdi_error_count < MAX_ERROR_MSG) &&
                    (Cg_parameter_occurrence[loop_cgcnt-ONE] & BIT_FIVE))
                {
                    /* Frame the Error Message*/
                    BuildErrorMsg(element, labelstring, "CG_LIM_VAL", \
    				Error_msg_string[Pdi_error_count]);

                    /* Increment the PDI Error Index*/
                    ++Pdi_error_count;
                }
            }
                /* Check for CG_LIM_COLOR*/
                 /*hdudispfpdicheck-CheckCarrotGraph-DB-LLR-013*/
                for (var_j = ZERO; var_j < Page_settings.Cg_settings[loop_cgcnt-ONE].cg_no_lim;
    			     var_j++)
                {
                if (((Page_settings.Cg_settings[loop_cgcnt-ONE].cg_lim_color[var_j] != ZERO) &&
                   (!CheckColor(Page_settings.Cg_settings[loop_cgcnt-ONE].cg_lim_color[var_j])))
                		&& (Pdi_error_count < MAX_ERROR_MSG) &&
                   (Cg_parameter_occurrence[loop_cgcnt-ONE] & BIT_SIX))
                {
                        /* Frame the Error Message*/
                        BuildErrorMsg(element, labelstring, "CG_LIM_COLOR",
                                Error_msg_string[Pdi_error_count]);

                        /* Increment the PDI Error Index*/
                        ++Pdi_error_count;
            }
            }
		     	/*hdudispfpdicheck-CheckCarrotGraph-DB-LLR-025*/
                for (var_j = ZERO; var_j < Page_settings.Cg_settings[loop_cgcnt-ONE].cg_no_lim;
                     var_j++)
                {
                    if (!CheckMinMax(Page_settings.Cg_settings[loop_cgcnt-ONE].cg_lim_type[var_j] ,
                        TYPE_NORMAL, TYPE_WARNING) && (Pdi_error_count < MAX_ERROR_MSG))
                    {
                        BuildErrorMsg(element, labelstring, "CG_LIM_TYPE",
                                Error_msg_string[Pdi_error_count]);
                        /* Increment the PDI Error Index*/
                        ++Pdi_error_count;
                    }
                }

		     /* Check for CG_REDX_AXIS*/
             /*hdudispfpdicheck-CheckCarrotGraph-DB-LLR-014*/
        if ((!CheckAxisMinMax(Page_settings.Cg_settings[loop_cgcnt-ONE].cg_redx_axis.u16_x,
            ZERO, PANEL_HEIGHT,PANEL_WIDTH)||\
			!CheckAxisMinMax(Page_settings.Cg_settings[loop_cgcnt-ONE].
            cg_redx_axis.u16_y, ZERO, PANEL_WIDTH,PANEL_HEIGHT)) && \
			(Pdi_error_count < MAX_ERROR_MSG) &&
            (Cg_parameter_occurrence[loop_cgcnt-ONE] & BIT_SEVEN))
        {
            /*Frame the Error Message*/
            BuildErrorMsg(element, labelstring, "CG_REDX_AXIS", Error_msg_string[Pdi_error_count]);

            /* Increment the PDI Error Index*/
            ++Pdi_error_count;
        }

        /* Check for CG_REDX_WIDTH*/
         /*hdudispfpdicheck-CheckCarrotGraph-DB-LLR-026*/
        if(!CheckAxisMinMax(Page_settings.Cg_settings[loop_cgcnt-ONE].cg_redx_width, \
			ZERO, PANEL_HEIGHT,PANEL_WIDTH) &&
           (Pdi_error_count < MAX_ERROR_MSG ) &&
           (Cg_parameter_occurrence[loop_cgcnt-ONE] & BIT_EIGHT))
        {
            /* Frame the Error Message*/
            BuildErrorMsg(element, labelstring, "CG_REDX_WIDTH",Error_msg_string[Pdi_error_count]);

            /* Increment the PDI Error Index*/
            ++Pdi_error_count;

        }

        /* Check for CG_REDX_HEIGHT*/
         /*hdudispfpdicheck-CheckCarrotGraph-DB-LLR-027*/
        if (!CheckAxisMinMax(Page_settings.Cg_settings[loop_cgcnt-ONE].cg_redx_height,\
			 ZERO, PANEL_WIDTH,PANEL_HEIGHT) &&
            (Pdi_error_count < MAX_ERROR_MSG) &&
            (Cg_parameter_occurrence[loop_cgcnt-ONE] & BIT_NINE))
        {
            /* Frame the Error Message*/
            BuildErrorMsg(element, labelstring, "CG_REDX_HEIGHT",
                    Error_msg_string[Pdi_error_count]);
            /* Increment the PDI Error Index*/
            ++Pdi_error_count;

        }

        /* Check for CG_REDX_OFFEST_AXIS*/
         /*hdudispfpdicheck-CheckCarrotGraph-DB-LLR-017*/
        if ((!CheckAxisMinMax2(((T_INT16)Page_settings.Cg_settings[loop_cgcnt-ONE].\
		cg_redx_offset_axis.u16_x),-PANEL_HEIGHT, -PANEL_WIDTH, PANEL_HEIGHT, PANEL_WIDTH)||\
		!CheckAxisMinMax2(((T_INT16)Page_settings.\
		Cg_settings[loop_cgcnt-ONE].cg_redx_offset_axis.u16_y), -PANEL_WIDTH, -PANEL_HEIGHT,
				PANEL_WIDTH, PANEL_HEIGHT)) && \
		(Pdi_error_count < MAX_ERROR_MSG) &&
        (Cg_parameter_occurrence[loop_cgcnt-ONE] & BIT_TEN))
        {
            /* Frame the Error Message*/
            BuildErrorMsg(element, labelstring, "CG_REDX_OFFSET_AXIS",
                    Error_msg_string[Pdi_error_count]);

            /* Increment the PDI Error Index*/
            ++Pdi_error_count;

        }
            /* Check for CG_REDX_X_AXIS*/
             /*hdudispfpdicheck-CheckCarrotGraph-DB-LLR-028*/
        if ((!CheckAxisMinMax(Page_settings.Cg_settings[loop_cgcnt-ONE].cg_redx_axis.u16_x,
        		Page_settings.Cg_settings[loop_cgcnt-ONE].cg_redx_width / 2,
			PANEL_HEIGHT,PANEL_WIDTH)||\
			!CheckAxisMinMax(Page_settings.Cg_settings[loop_cgcnt-ONE].cg_redx_axis.u16_x, ZERO,
					PANEL_HEIGHT - (Page_settings.Cg_settings[loop_cgcnt-ONE].cg_redx_width / 2),
					PANEL_WIDTH-(Page_settings.Cg_settings[loop_cgcnt-ONE].cg_redx_width / 2))) && \
			(Pdi_error_count < MAX_ERROR_MSG) &&
            (Cg_parameter_occurrence[loop_cgcnt-ONE] & BIT_SEVEN))
        {
            /*Frame the Error Message*/
            BuildErrorMsg(element, labelstring, "CG_REDX_AXIS", Error_msg_string[Pdi_error_count]);

            /* Increment the PDI Error Index*/
            ++Pdi_error_count;

        }

        /* Check for CG_REDX_Y_AXIS*/
         /*hdudispfpdicheck-CheckCarrotGraph-DB-LLR-029*/
    if ((!CheckAxisMinMax(Page_settings.Cg_settings[loop_cgcnt-ONE].cg_redx_axis.u16_y,
    		Page_settings.Cg_settings[loop_cgcnt-ONE].cg_redx_height / 2,
			PANEL_WIDTH,PANEL_HEIGHT)||\
		!CheckAxisMinMax(Page_settings.Cg_settings[loop_cgcnt-ONE].cg_redx_axis.u16_y, ZERO,
				PANEL_WIDTH - (Page_settings.Cg_settings[loop_cgcnt-ONE].cg_redx_height / 2),
				PANEL_HEIGHT-(Page_settings.Cg_settings[loop_cgcnt-ONE].cg_redx_height / 2))) && \
		(Pdi_error_count < MAX_ERROR_MSG) &&
        (Cg_parameter_occurrence[loop_cgcnt-ONE] & BIT_SEVEN))
    {
        /*Frame the Error Message*/
        BuildErrorMsg(element, labelstring, "CG_REDX_AXIS", Error_msg_string[Pdi_error_count]);

           /* Increment the PDI Error Index*/
           ++Pdi_error_count;

        }

        /* Check for CG_REDX_FONT*/
         /*hdudispfpdicheck-CheckCarrotGraph-DB-LLR-030*/
        if (!CheckFont(Page_settings.Cg_settings[loop_cgcnt-ONE].cg_redx_font)
        	&& (Pdi_error_count < MAX_ERROR_MSG) &&
            (Cg_parameter_occurrence[loop_cgcnt-ONE] & BIT_ELEVEN))
        {
            /* Frame the Error Message*/
            BuildErrorMsg(element, labelstring, "CG_REDX_FONT",
                    Error_msg_string[Pdi_error_count]);
            /* Increment the PDI Error Index*/
            ++Pdi_error_count;
        }

        /* Check for CG_REDX_TXT string length*/
        /*hdudispfpdicheck-CheckCarrotGraph-DB-LLR-018*/
        if (!CheckString( Page_settings.Cg_settings[loop_cgcnt-ONE].cg_redx_txt,
            MAX_STRING_CHAR_TXT) && (Pdi_error_count < MAX_ERROR_MSG) &&
            (Cg_parameter_occurrence[loop_cgcnt-ONE] & BIT_TWELVE))
        {
            /* Frame the Error Message*/
            BuildErrorMsg(element, labelstring, "CG_REDX_TXT",Error_msg_string[Pdi_error_count]);

            /* Increment the PDI Error Index*/
            ++Pdi_error_count;

        }

         /*hdudispfpdicheck-CheckCarrotGraph-DB-LLR-031*/
        new_line_indication= CalStringParam(Page_settings.Cg_settings[loop_cgcnt-ONE].cg_redx_txt,
		                    &max_width, &lin_count );

        max_width=  (T_UINT16)(max_width * (T_UINT16)(FontsGetStringWidth((T_UINT8 *)char_a,
           		Page_settings.Cg_settings[loop_cgcnt-ONE].cg_redx_font)));
        lin_count=  (T_UINT16)(lin_count *(T_UINT16)(FontsGetFontHeight(\
        		Page_settings.Cg_settings[loop_cgcnt-ONE].cg_redx_font)));
        if (ONE == (max_width & 1))
        {
     	   max_width = (T_UINT16)(max_width + 1);
        }
        else
        {
        	;
        }

        /* Check for CG_REDX_OFFSET_AXIS*/
       if (((TRUE == new_line_indication) ||
         ((!CheckAxisMinMax((T_INT32)((T_INT16)(Page_settings.Cg_settings[loop_cgcnt-ONE].\
        cg_redx_offset_axis.u16_x) + Page_settings.Cg_settings[loop_cgcnt-ONE].cg_redx_axis.u16_x
 	   + (max_width/2)),ZERO, PANEL_HEIGHT,PANEL_WIDTH))|| \
     	 (!CheckAxisMinMax((T_INT32)((T_INT16)(Page_settings.Cg_settings[loop_cgcnt-ONE].\
          cg_redx_offset_axis.u16_x) + Page_settings.Cg_settings[loop_cgcnt-ONE].cg_redx_axis.u16_x
 		  - (max_width/2)),ZERO, PANEL_HEIGHT,PANEL_WIDTH))||
          (!CheckAxisMinMax((T_INT32)((T_INT16)(Page_settings.Cg_settings[loop_cgcnt-ONE].
          cg_redx_offset_axis.u16_y) +Page_settings.Cg_settings[loop_cgcnt-ONE].cg_redx_axis.u16_y
 		 + (lin_count/2)), ZERO, PANEL_WIDTH,PANEL_HEIGHT))  || \
          (!CheckAxisMinMax((T_INT32)((T_INT16)(Page_settings.Cg_settings[loop_cgcnt-ONE].
     	 cg_redx_offset_axis.u16_y) +Page_settings.Cg_settings[loop_cgcnt-ONE].cg_redx_axis.u16_y
 		 - (lin_count/2)), ZERO,PANEL_WIDTH,PANEL_HEIGHT))))
 		&& (Pdi_error_count < MAX_ERROR_MSG)
         && (Cg_parameter_occurrence[loop_cgcnt-ONE] & BIT_TEN))
        {
            /* Frame the Error Message*/
           BuildErrorMsg(element, labelstring, "CG_REDX_OFFSET_AXIS",
                    Error_msg_string[Pdi_error_count]);

            /* Increment the PDI Error Index*/
           ++Pdi_error_count;

        }

        for (loop_nbcnt = ONE; loop_nbcnt <= Nb_cnt; loop_nbcnt++)
        {
                /* Check for CG_NB_FORMAT*/
                /*hdudispfpdicheck-CheckCarrotGraph-DB-LLR-020*/
                nb_byte_format = Page_settings.Cg_settings[loop_cgcnt-ONE].
                                          cg_nb_format & 0xF00000;
                nb_decimal_format = Page_settings.Cg_settings[loop_cgcnt-ONE].
                                          cg_nb_format & 0x1FC00;
                nb_word_format = Page_settings.Cg_settings[loop_cgcnt-ONE].
                                          cg_nb_format & 0xFF;

                if (((nb_byte_format != NUM_ONEB) && (nb_byte_format != NUM_TWOB) &&
                	(nb_byte_format != NUM_THREEB) && (nb_byte_format != NUM_FOURB)) &&
                      (Pdi_error_count < MAX_ERROR_MSG) &&
                      (Cg_parameter_occurrence[loop_cgcnt-ONE] & BIT_TWO))
                {
                    /* Frame the Error Message*/
                    BuildErrorMsg(element, labelstring, "CG_NB_FORMAT",
                            Error_msg_string[Pdi_error_count]);

                    /* Increment the PDI Error Index*/
                    ++Pdi_error_count;
                }
                /*hdudispfpdicheck-CheckCarrotGraph-DB-LLR-021*/
                if (((!CheckDecimalFormat((T_FORMAT)nb_decimal_format))
					&& (nb_decimal_format != ZERO))
                    && (Pdi_error_count < MAX_ERROR_MSG)
                    && (Cg_parameter_occurrence[loop_cgcnt-ONE] & BIT_TWO))
                {
                    /* Frame the Error Message*/
                    BuildErrorMsg(element, labelstring, "CG_NB_FORMAT",
                            Error_msg_string[Pdi_error_count]);

                    /* Increment the PDI Error Index*/
                    ++Pdi_error_count;

                }
                /*hdudispfpdicheck-CheckCarrotGraph-DB-LLR-022*/
                bool_format = OnlyOneBitSetToOne(nb_word_format) & (nb_word_format <= NUM_EIGHTW);

                if ((ZERO == bool_format) && (Pdi_error_count < MAX_ERROR_MSG) &&
                    (Cg_parameter_occurrence[loop_cgcnt-ONE] & BIT_TWO))
                {
                    /* Frame the Error Message*/
                    BuildErrorMsg(element, labelstring, "CG_NB_FORMAT",
                            Error_msg_string[Pdi_error_count]);

                    /* Increment the PDI Error Index*/
                    ++Pdi_error_count;

                }
                if(TRUE == Cg_tracker[loop_cgcnt- ONE][loop_nbcnt- ONE])
                {
                /* Check for CG_NB_FONT*/
                /*hdudispfpdicheck-CheckCarrotGraph-DB-LLR-023*/
                if (!CheckFont(Page_settings.Nb_settings[loop_nbcnt-ONE].nb_font) &&
                   (Pdi_error_count < MAX_ERROR_MSG) &&
                    (Cg_parameter_occurrence[loop_cgcnt-ONE] & BIT_THREE))
                {
                    /* Frame the Error Message*/
                    BuildErrorMsg(element, labelstring, "CG_NB_FONT",
                            Error_msg_string[Pdi_error_count]);
                /* To prevent hard fault error during initialization, when invalid font */
                /* it is initialized to normal font */
                    Page_num_boxes[loop_nbcnt - ONE].eFont = E_NO_FONT;
                    /* Increment the PDI Error Index*/
                    ++Pdi_error_count;
                }
                }
                /*hdudispfpdicheck-CheckCarrotGraph-DB-LLR-019*/
                /* Check for CG_NB_AXIS*/
                if ((!CheckAxisMinMax(Page_settings.Nb_settings[loop_nbcnt - ONE].nb_axis.u16_x,
                      ZERO, PANEL_HEIGHT,PANEL_WIDTH) || !CheckAxisMinMax(Page_settings.
                      Nb_settings[loop_nbcnt - ONE].nb_axis.u16_y, ZERO,
					  PANEL_WIDTH,PANEL_HEIGHT)) && (Pdi_error_count < MAX_ERROR_MSG) &&
                     (Cg_parameter_occurrence[loop_cgcnt-ONE] & BIT_ONE))
                {
                    /* Frame the Error Message*/
                    BuildErrorMsg(element, labelstring, "CG_NB_AXIS", \
					Error_msg_string[Pdi_error_count]);

                    /* Increment the PDI Error Index*/
                    ++Pdi_error_count;

                }
                 /*hdudispfpdicheck-CheckCarrotGraph-DB-LLR-032*/
                total_digits=(T_UINT16)FindTotalDigits(Page_settings.Cg_settings[loop_cgcnt-ONE].
                        cg_nb_format);
                one_char_width=(T_UINT16)(FontsGetStringWidth((T_UINT8 *)char_a,
                		Page_settings.Nb_settings[loop_nbcnt-ONE].nb_font));
                nb_width= (T_UINT16)(total_digits * one_char_width);
                nb_height=(T_UINT16)(FontsGetFontHeight
                  (Page_settings.Nb_settings[loop_nbcnt-ONE].nb_font));
                if (ONE == (nb_width & 1))
                {
                	nb_width = (T_UINT16)(nb_width + 1);
                }
                else
                {
                	;
                }

                /* Check for CG_NB_AXIS*/
                if ((((!CheckAxisMinMax(Page_settings.Nb_settings[loop_nbcnt - ONE].
                	   nb_axis.u16_x + nb_width/2,
                       ZERO, PANEL_HEIGHT-DEC_SIX ,PANEL_WIDTH-DEC_SIX)) ||
                		(!CheckAxisMinMax(Page_settings.Nb_settings[loop_nbcnt - ONE].
                	   nb_axis.u16_x - nb_width/2,
                	   ZERO, PANEL_HEIGHT-DEC_SIX ,PANEL_WIDTH-DEC_SIX))) ||
                      ((!CheckAxisMinMax(Page_settings.Nb_settings[loop_nbcnt - ONE].nb_axis.u16_y
					  + nb_height/2, ZERO,PANEL_WIDTH,PANEL_HEIGHT)) ||
                      (!CheckAxisMinMax(Page_settings.Nb_settings[loop_nbcnt - ONE].nb_axis.u16_y
					  - nb_height/2, ZERO,PANEL_WIDTH,PANEL_HEIGHT)))) &&
					  (Pdi_error_count < MAX_ERROR_MSG) &&
                     (Cg_parameter_occurrence[loop_cgcnt-ONE] & BIT_ONE))
                {
                    /* Frame the Error Message*/
                    BuildErrorMsg(element, labelstring, "CG_NB_AXIS", \
					Error_msg_string[Pdi_error_count]);

                    /* Increment the PDI Error Index*/
                    ++Pdi_error_count;

                }
        }
    }
}

/*
 *
 * Function                : CheckTextBox
 *
 * Description             : This function checks TextBox parameters
 *
 * Formal parameter(s)     : None
 *
 * Return Value            : None
 *
 * Assumption              : None
 *
 */
static void CheckTextBox()
{
    T_CHAR element[3] = "TB";    /* Element type*/
    T_CHAR labelstring[5]={0};     /* Variable used to store label in string format*/
    T_UINT16 loop_tbcnt=ZERO;        /* Graph count required for loop*/
    T_UINT16 max_width = ZERO;
    T_UINT16 lin_count = ZERO;
    T_BOOL new_line_indication = ZERO;
    T_CHAR char_a[] = "A";

    for (loop_tbcnt = ONE; loop_tbcnt <= Tb_cnt; loop_tbcnt++)
    {
        /* Converts the label as array of characters*/
         /*hdudispfpdicheck-CheckTextBox-DB-LLR-018*/
    	OctToStringTrim(Page_settings.Tb_settings[loop_tbcnt-1].label, Label_size, labelstring);

        /* Check for Text box Label*/

        if (!CheckMinMax(Page_settings.Tb_settings[loop_tbcnt-1].label, 1, MAX_LABEL) &&
            (Pdi_error_count < MAX_ERROR_MSG))
        {
            /*Frame the Error Message*/
            BuildErrorMsg(element, labelstring, "LABEL", Error_msg_string[Pdi_error_count]);

            /* Increment the PDI Error Index*/
            ++Pdi_error_count;

        }


        /* Check for TB_STRING*/
        /*hdudispfpdicheck-CheckTextBox-DB-LLR-001*/
        if (!CheckString(Page_settings.Tb_settings[loop_tbcnt-ONE].tb_string, MAX_STRING_CHAR_TXT)
			&& (Pdi_error_count < MAX_ERROR_MSG))
        {
            /* Frame the Error Message*/
            BuildErrorMsg(element, labelstring, "TB_STRING", Error_msg_string[Pdi_error_count]);

            /* Increment the PDI Error Index*/
            ++Pdi_error_count;

        }

	    /* Check for SDI */
	    /*hdudispfpdicheck-CheckTextBox-DB-LLR-017*/
		if ((TRUE == Config_data.eng_sdi)&& \
		(!CheckMinMax(Page_settings.Tb_settings[loop_tbcnt-ONE].sdi, ZERO , THREE))&&
         (Pdi_error_count < MAX_ERROR_MSG))
        {
           /*Frame the Error Message */
           BuildErrorMsg(element, labelstring, "SDI",
                        Error_msg_string[Pdi_error_count]);

            /* Increment the PDI Error Index */
            ++Pdi_error_count;

        }
        /* Check for TB_AXIS*/
        /*hdudispfpdicheck-CheckTextBox-DB-LLR-002*/
        if ((!CheckAxisMinMax(Page_settings.Tb_settings[loop_tbcnt-ONE].tb_axis.u16_x, \
		     ZERO, PANEL_HEIGHT,PANEL_WIDTH)
            || !CheckAxisMinMax(Page_settings.Tb_settings[loop_tbcnt-ONE].tb_axis.u16_y, ZERO,
            PANEL_WIDTH,PANEL_HEIGHT)) && (Pdi_error_count < MAX_ERROR_MSG))
        {
            /* Frame the Error Message*/
            BuildErrorMsg(element, labelstring, "TB_AXIS", Error_msg_string[Pdi_error_count]);

            /* Increment the PDI Error Index*/
            ++Pdi_error_count;

        }

        /* Check for TB_width*/
        /*hdudispfpdicheck-CheckTextBox-DB-LLR-003*/
        if (!CheckAxisMinMax(Page_settings.Tb_settings[loop_tbcnt-ONE].tb_width, ZERO, \
			 PANEL_HEIGHT,PANEL_WIDTH) &&
            (Pdi_error_count < MAX_ERROR_MSG))
        {
            /* Frame the Error Message*/
            BuildErrorMsg(element, labelstring, "TB_WIDTH", Error_msg_string[Pdi_error_count]);

            /* Increment the PDI Error Index*/
            ++Pdi_error_count;

        }

        /* Check for TB_HEIGHT*/
        /*hdudispfpdicheck-CheckTextBox-DB-LLR-004*/
        if (!CheckAxisMinMax(Page_settings.Tb_settings[loop_tbcnt-ONE].tb_height, ZERO, \
			 PANEL_WIDTH,PANEL_HEIGHT) &&
            (Pdi_error_count < MAX_ERROR_MSG))
        {
            /* Frame the Error Message*/
            BuildErrorMsg(element, labelstring, "TB_HEIGHT", Error_msg_string[Pdi_error_count]);

            /* Increment the PDI Error Index*/
            ++Pdi_error_count;

        }

        /* Check for TB_MARGIN*/
        /*hdudispfpdicheck-CheckTextBox-DB-LLR-005*/
        if (!CheckMinMax(Page_settings.Tb_settings[loop_tbcnt-ONE].tb_margin, ZERO,
            TWENTY) && (Pdi_error_count < MAX_ERROR_MSG))
        {
            /* Frame the Error Message*/
            BuildErrorMsg(element, labelstring, "TB_MARGIN", Error_msg_string[Pdi_error_count]);

            /* Increment the PDI Error Index*/
            ++Pdi_error_count;

        }

        /* Check for TB_FRAME_WIDTH*/
        /*hdudispfpdicheck-CheckTextBox-DB-LLR-006*/
        if (!CheckMinMax(Page_settings.Tb_settings[loop_tbcnt-ONE].tb_frame_width, ZERO,
            TWENTY) && (Pdi_error_count < MAX_ERROR_MSG))
        {
            /* Frame the Error Message*/
            BuildErrorMsg(element, labelstring, "TB_FRAME_WIDTH",\
			Error_msg_string[Pdi_error_count]);

            /* Increment the PDI Error Index*/
            ++Pdi_error_count;

        }

		/* Check for TB_FRAME_COLOR*/
		/*hdudispfpdicheck-CheckTextBox-DB-LLR-007*/
		if (!CheckColor(Page_settings.Tb_settings[loop_tbcnt-ONE].tb_frame_color)
		  && (Pdi_error_count < MAX_ERROR_MSG))
		{
			/* Frame the Error Message*/
			BuildErrorMsg(element,labelstring,"TB_FRAME_COLOR",Error_msg_string[Pdi_error_count]);

			/* Increment the PDI Error Index*/
			++Pdi_error_count;

		}

		/* Check for TB_BG_COLOR*/
		/*hdudispfpdicheck-CheckTextBox-DB-LLR-008*/
		if (!CheckColor(Page_settings.Tb_settings[loop_tbcnt-ONE].tb_bg_color)
			&& (Pdi_error_count < MAX_ERROR_MSG))
		{
			/* Frame the Error Message*/
			BuildErrorMsg(element,labelstring,"TB_BG_COLOR",Error_msg_string[Pdi_error_count]);

			/* Increment the PDI Error Index*/
			++Pdi_error_count;

		}

	    /* Check for TB_BIT*/
	    /*hdudispfpdicheck-CheckTextBox-DB-LLR-019*/
	    if (!CheckMinMax(Page_settings.Tb_settings[loop_tbcnt-1].tb_bit, MIN_START_BIT,
	    	MAX_START_BIT) && (Pdi_error_count < MAX_ERROR_MSG)&&
		    (Tb_parameter_occurrence[loop_tbcnt-1]&BIT_ONE))
	    {
	            /* Frame the Error Message*/
	            BuildErrorMsg(element, labelstring, "TB_BIT", Error_msg_string[Pdi_error_count]);

	            /* Increment the PDI Error Index*/
	            ++Pdi_error_count;

	     }
	    /* Check for TB_CROSS_VAL*/
	    /*hdudispfpdicheck-CheckTextBox-DB-LLR-020*/
	    if ((!CheckMinMax(Page_settings.Tb_settings[loop_tbcnt-ONE].tb_cross_val_type,
            	ONE, MAX_LIM_VAL_TYPE) ||
	    	!CheckFloatMinMax(Page_settings.Tb_settings[loop_tbcnt-1].tb_cross_val, MIN_RANGE,
	    	MAX_RANGE)) && (Pdi_error_count < MAX_ERROR_MSG)&&
			(Tb_parameter_occurrence[loop_tbcnt-1]&BIT_TWO))
	    {
	            /* Frame the Error Message*/
	            BuildErrorMsg(element, labelstring, "TB_CROSS_VAL", \
				Error_msg_string[Pdi_error_count]);

	            /* Increment the PDI Error Index*/
	            ++Pdi_error_count;
	     }
		 /* Check for TB_ALIGN*/
		        /*hdudispfpdicheck-CheckTextBox-DB-LLR-021*/
		        if (!CheckMinMax(Page_settings.Tb_settings[loop_tbcnt-1].tb_align, ALIGN_CENTER,
		         ALIGN_LEFT) && (Pdi_error_count < MAX_ERROR_MSG)&&
		          (Tb_parameter_occurrence[loop_tbcnt-1]&BIT_THREE))
		        {
		            /* Frame the Error Message*/
		            BuildErrorMsg(element, labelstring, "TB_ALIGN", \
					Error_msg_string[Pdi_error_count]);

		            /* Increment the PDI Error Index*/
		            ++Pdi_error_count;

		        }


        /* Check for TB_FONT*/
        /*hdudispfpdicheck-CheckTextBox-DB-LLR-009*/
        if (!CheckFont(Page_settings.Tb_settings[loop_tbcnt-ONE].tb_font) &&
           (Pdi_error_count < MAX_ERROR_MSG) &&
           (Tb_parameter_occurrence[loop_tbcnt-ONE] & BIT_FOUR))
        {
            /* Frame the Error Message*/
            BuildErrorMsg(element, labelstring, "TB_FONT", Error_msg_string[Pdi_error_count]);

            /* Increment the PDI Error Index*/
            ++Pdi_error_count;

        }

		/* Check for TB_COLOR*/
		/*hdudispfpdicheck-CheckTextBox-DB-LLR-010*/
		if (!CheckColor(Page_settings.Tb_settings[loop_tbcnt-ONE].tb_color)
			&& (Pdi_error_count < MAX_ERROR_MSG) &&
           (Tb_parameter_occurrence[loop_tbcnt-ONE] & BIT_FIVE))
		{
			/* Frame the Error Message*/
			BuildErrorMsg(element,labelstring,"TB_COLOR",Error_msg_string[Pdi_error_count]);

			/* Increment the PDI Error Index*/
			++Pdi_error_count;

		}

        /* Check for TB_STATE*/
        /*hdudispfpdicheck-CheckTextBox-DB-LLR-022 */
        if (((Page_settings.Tb_settings[loop_tbcnt-ONE].tb_state != TXT_STATE_NORMAL) &&
        	(Page_settings.Tb_settings[loop_tbcnt-ONE].tb_state != TXT_STATE_REVERSE))
        	&& (Pdi_error_count < MAX_ERROR_MSG) &&
           (Tb_parameter_occurrence[loop_tbcnt-ONE] & BIT_SIX))
        {
            /* Frame the Error Message*/
            BuildErrorMsg(element, labelstring, "TB_STATE", Error_msg_string[Pdi_error_count]);

            /* Increment the PDI Error Index*/
            ++Pdi_error_count;
        }

        /* Check for TB_FLASH*/
        /*hdudispfpdicheck-CheckTextBox-DB-LLR-023*/
        if (((Page_settings.Tb_settings[loop_tbcnt-ONE].tb_flash != (T_UINT16)TEXT_FLASH_ON) &&
        	( Page_settings.Tb_settings[loop_tbcnt-ONE].tb_flash != (T_UINT16)TEXT_FLASH_OFF)) && \
           (Pdi_error_count < MAX_ERROR_MSG) &&
           (Tb_parameter_occurrence[loop_tbcnt-ONE] & BIT_SEVEN))
        {
            /* Frame the Error Message*/
            BuildErrorMsg(element, labelstring, "TB_FLASH", \
			Error_msg_string[Pdi_error_count]);

            /* Increment the PDI Error Index*/
            ++Pdi_error_count;
        }

		/* Check for TB_FLASH_COLOR*/
		/*hdudispfpdicheck-CheckTextBox-DB-LLR-024*/
		if (!CheckColor(Page_settings.Tb_settings[loop_tbcnt-ONE].tb_flash_color)
			&&  (Pdi_error_count < MAX_ERROR_MSG) &&
		(Tb_parameter_occurrence[loop_tbcnt-ONE] & BIT_FOURTEEN))
		{
			/* Frame the Error Message*/
			BuildErrorMsg(element,labelstring,"TB_FLASH_COLOR",Error_msg_string[Pdi_error_count]);
			/* Increment the PDI Error Index*/
			++Pdi_error_count;
		}
		        /* Check for TB_REDX_AXIS*/
        /*hdudispfpdicheck-CheckTextBox-DB-LLR-011*/
        if ((!CheckAxisMinMax(Page_settings.Tb_settings[loop_tbcnt-ONE].tb_redx_axis.u16_x, ZERO,
        	PANEL_HEIGHT,PANEL_WIDTH)   || \
			!CheckAxisMinMax(Page_settings.Tb_settings[loop_tbcnt-ONE].
            tb_redx_axis.u16_y, ZERO, PANEL_WIDTH,PANEL_HEIGHT)) && \
			(Pdi_error_count < MAX_ERROR_MSG) &&
            (Tb_parameter_occurrence[loop_tbcnt-ONE] & BIT_EIGHT))
        {
            /*Frame the Error Message*/
            BuildErrorMsg(element, labelstring, "TB_REDX_AXIS", Error_msg_string[Pdi_error_count]);

            /* Increment the PDI Error Index*/
            ++Pdi_error_count;

        }

        /* Check for TB_REDX_WIDTH*/
        /*hdudispfpdicheck-CheckTextBox-DB-LLR-012*/
        if(!CheckAxisMinMax(Page_settings.Tb_settings[loop_tbcnt-ONE].tb_redx_width, \
			ZERO, PANEL_HEIGHT,PANEL_WIDTH) &&
           (Pdi_error_count < MAX_ERROR_MSG ) &&
		   (Tb_parameter_occurrence[loop_tbcnt-ONE] & BIT_NINE))
        {
            /* Frame the Error Message*/
            BuildErrorMsg(element, labelstring, "TB_REDX_WIDTH",Error_msg_string[Pdi_error_count]);

            /* Increment the PDI Error Index*/
            ++Pdi_error_count;

        }

        /* Check for TB_REDX_X_AXIS*/
        /*hdudispfpdicheck-CheckTextBox-DB-LLR-025*/
        if ((!CheckAxisMinMax(Page_settings.Tb_settings[loop_tbcnt-ONE].tb_redx_axis.u16_x,
        	Page_settings.Tb_settings[loop_tbcnt-ONE].tb_redx_width / 2,
        	PANEL_HEIGHT,PANEL_WIDTH)   || \
			!CheckAxisMinMax(Page_settings.Tb_settings[loop_tbcnt-ONE].tb_redx_axis.u16_x, ZERO,
			PANEL_HEIGHT - (Page_settings.Tb_settings[loop_tbcnt-ONE].tb_redx_width / 2),
			PANEL_WIDTH - (Page_settings.Tb_settings[loop_tbcnt-ONE].tb_redx_width / 2))) && \
			(Pdi_error_count < MAX_ERROR_MSG) &&
            (Tb_parameter_occurrence[loop_tbcnt-ONE] & BIT_EIGHT))
        {
            /*Frame the Error Message*/
            BuildErrorMsg(element, labelstring, "TB_REDX_AXIS", Error_msg_string[Pdi_error_count]);

            /* Increment the PDI Error Index*/
            ++Pdi_error_count;

        }

        /* Check for TB_REDX_Y_AXIS*/
        /*hdudispfpdicheck-CheckTextBox-DB-LLR-026*/
        if ((!CheckAxisMinMax(Page_settings.Tb_settings[loop_tbcnt-ONE].tb_redx_axis.u16_y,
        	Page_settings.Tb_settings[loop_tbcnt-ONE].tb_redx_height / 2,
        	PANEL_WIDTH ,PANEL_HEIGHT)   || \
			!CheckAxisMinMax(Page_settings.Tb_settings[loop_tbcnt-ONE].tb_redx_axis.u16_y, ZERO,
			PANEL_WIDTH - (Page_settings.Tb_settings[loop_tbcnt-ONE].tb_redx_height / 2),
			PANEL_HEIGHT - (Page_settings.Tb_settings[loop_tbcnt-ONE].tb_redx_height / 2))) && \
			(Pdi_error_count < MAX_ERROR_MSG) &&
            (Tb_parameter_occurrence[loop_tbcnt-ONE] & BIT_EIGHT))
        {
            /*Frame the Error Message*/
            BuildErrorMsg(element, labelstring, "TB_REDX_AXIS", Error_msg_string[Pdi_error_count]);

            /* Increment the PDI Error Index*/
            ++Pdi_error_count;

        }

        /* Check for TB_REDX_HEIGHT*/
        /*hdudispfpdicheck-CheckTextBox-DB-LLR-013*/
        if (!CheckAxisMinMax(Page_settings.Tb_settings[loop_tbcnt-ONE].tb_redx_height, \
			 ZERO, PANEL_WIDTH,PANEL_HEIGHT) &&
            (Pdi_error_count < MAX_ERROR_MSG) &&
            (Tb_parameter_occurrence[loop_tbcnt-ONE] & BIT_TEN))
        {
            /* Frame the Error Message*/
            BuildErrorMsg(element, labelstring, "TB_REDX_HEIGHT",
			Error_msg_string[Pdi_error_count]);
            /* Increment the PDI Error Index*/
            ++Pdi_error_count;

        }

        /* Check for TB_REDX_OFFSET_AXIS*/
        /*hdudispfpdicheck-CheckTextBox-DB-LLR-014*/
        if ((!CheckAxisMinMax2((T_INT16)Page_settings.Tb_settings[loop_tbcnt-ONE].\
        	tb_redx_offset_axis.u16_x,-PANEL_HEIGHT,-PANEL_WIDTH, PANEL_HEIGHT,PANEL_WIDTH)|| \
			!CheckAxisMinMax2((T_INT16)Page_settings.Tb_settings[loop_tbcnt-ONE].
            tb_redx_offset_axis.u16_y, -PANEL_WIDTH,-PANEL_HEIGHT, PANEL_WIDTH,PANEL_HEIGHT)) && \
			(Pdi_error_count < MAX_ERROR_MSG)
                && (Tb_parameter_occurrence[loop_tbcnt-ONE] & BIT_ELEVEN))
        {
            /* Frame the Error Message*/
            BuildErrorMsg(element, labelstring, "TB_REDX_OFFSET_AXIS",
                    Error_msg_string[Pdi_error_count]);

            /* Increment the PDI Error Index*/
            ++Pdi_error_count;

        }

        /* Check for TB_REDX_FONT*/
        /*hdudispfpdicheck-CheckTextBox-DB-LLR-015*/
        if (!CheckFont(Page_settings.Tb_settings[loop_tbcnt-ONE].tb_redx_font) &&
           (Pdi_error_count < MAX_ERROR_MSG) &&
           (Tb_parameter_occurrence[loop_tbcnt-ONE] & BIT_TWELVE))
        {
            /* Frame the Error Message*/
            BuildErrorMsg(element, labelstring, "TB_REDX_FONT", Error_msg_string[Pdi_error_count]);

            /* Increment the PDI Error Index*/
            ++Pdi_error_count;

        }

        /* Check for TB_REDX_TXT string length*/
        /*hdudispfpdicheck-CheckTextBox-DB-LLR-016*/
        if (!CheckString( Page_settings.Tb_settings[loop_tbcnt-ONE].tb_redx_txt,
            MAX_STRING_CHAR_TXT) && (Pdi_error_count < MAX_ERROR_MSG) &&
            (Tb_parameter_occurrence[loop_tbcnt-ONE] & BIT_THIRTEEN))
        {
            /* Frame the Error Message*/
            BuildErrorMsg(element, labelstring, "TB_REDX_TXT",Error_msg_string[Pdi_error_count]);

            /* Increment the PDI Error Index*/
            ++Pdi_error_count;

        }

         /*hdudispfpdicheck-CheckTextBox-DB-LLR-027*/
        new_line_indication= CalStringParam(Page_settings.Tb_settings[loop_tbcnt-ONE].tb_redx_txt,
                     		&max_width, &lin_count );

        max_width=  (T_UINT16)(max_width * (T_UINT16)(FontsGetStringWidth((T_UINT8 *)char_a,
           		Page_settings.Tb_settings[loop_tbcnt-ONE].tb_redx_font)));
        lin_count=  (T_UINT16)(lin_count *(T_UINT16)(FontsGetFontHeight
                   (Page_settings.Tb_settings[loop_tbcnt-ONE].tb_redx_font)));
        if (ONE == (max_width & 1))
        {
     	   max_width = (T_UINT16)(max_width + 1);
        }
        else
        {
        	;
        }

        /* Check for TB_REDX_OFFSET_AXIS*/
       if (((TRUE == new_line_indication) ||
         ((!CheckAxisMinMax((T_INT32)((T_INT16)(Page_settings.Tb_settings[loop_tbcnt-ONE].\
        tb_redx_offset_axis.u16_x) + Page_settings.Tb_settings[loop_tbcnt-ONE].tb_redx_axis.u16_x
 	   + (max_width/2)),ZERO, PANEL_HEIGHT,PANEL_WIDTH))|| \
     	 (!CheckAxisMinMax((T_INT32)((T_INT16)(Page_settings.Tb_settings[loop_tbcnt-ONE].\
         tb_redx_offset_axis.u16_x) + Page_settings.Tb_settings[loop_tbcnt-ONE].tb_redx_axis.u16_x
 		  - (max_width/2)),ZERO, PANEL_HEIGHT,PANEL_WIDTH))||
          (!CheckAxisMinMax((T_INT32)((T_INT16)(Page_settings.Tb_settings[loop_tbcnt-ONE].
          tb_redx_offset_axis.u16_y) +Page_settings.Tb_settings[loop_tbcnt-ONE].tb_redx_axis.u16_y
 		 + (lin_count/2)), ZERO, PANEL_WIDTH,PANEL_HEIGHT))  || \
          (!CheckAxisMinMax((T_INT32)((T_INT16)(Page_settings.Tb_settings[loop_tbcnt-ONE].
     	 tb_redx_offset_axis.u16_y) +Page_settings.Tb_settings[loop_tbcnt-ONE].tb_redx_axis.u16_y
 		 - (lin_count/2)), ZERO,PANEL_WIDTH,PANEL_HEIGHT))))
 		&& (Pdi_error_count < MAX_ERROR_MSG)
         && (Tb_parameter_occurrence[loop_tbcnt-ONE] & BIT_ELEVEN))
        {
            /* Frame the Error Message*/
           BuildErrorMsg(element, labelstring, "TB_REDX_OFFSET_AXIS",
                    Error_msg_string[Pdi_error_count]);

            /* Increment the PDI Error Index*/
           ++Pdi_error_count;

        }
    }
}



/*
 *
 * Function                : CheckText
 *
 * Description             : This function checks Text parameters
 *
 * Formal parameter(s)     : None
 *
 * Return Value            : None
 *
 * Assumption              : None
 *
 */
static void CheckText()
{
    T_CHAR element[5] = "TEXT";    /* Element type*/
    T_CHAR labelstring[5]={0};     /* Variable used to store label in string format*/
    T_UINT16 loop_textcnt=ZERO;        /* Graph count required for loop*/
    T_UINT16 max_width = ZERO;
    T_UINT16 lin_count = ZERO;
    T_BOOL new_line_indication = ZERO;
    T_CHAR char_a[] = "A";
    T_INT16 text_x_axis = ZERO;
    T_INT16 text_y_axis = ZERO;

    for (loop_textcnt = ONE; loop_textcnt <= Text_cnt; loop_textcnt++)
    {

         /* Converts the label as array of characters*/
    	 /*hdudispfpdicheck-CheckText-DB-LLR-009*/
    	OctToStringTrim(Page_settings.Text_settings[loop_textcnt-1].label,\
		 Label_size, labelstring);

    	 /* Check for Text Label*/

       if (!CheckMinMax(Page_settings.Text_settings[loop_textcnt-1].label, 1, MAX_LABEL) &&
    	    (Pdi_error_count < MAX_ERROR_MSG))
        {
    	     /*Frame the Error Message*/
    	     BuildErrorMsg(element, labelstring, "LABEL", Error_msg_string[Pdi_error_count]);

    	     /* Increment the PDI Error Index*/
    	      ++Pdi_error_count;

         }

        /* Check for TXT_STRING*/
        /*hdudispfpdicheck-CheckText-DB-LLR-001*/
        if (!CheckString(Page_settings.Text_settings[loop_textcnt-ONE].txt_string,\
		MAX_STRING_CHAR_TXT)&& (Pdi_error_count < MAX_ERROR_MSG))
        {
            /* Frame the Error Message*/
            BuildErrorMsg(element, labelstring, "TXT_STRING", Error_msg_string[Pdi_error_count]);

            /* Increment the PDI Error Index*/
           ++Pdi_error_count;
        }

		/* Check for TEXT SDI */
         /*hdudispfpdicheck-CheckText-DB-LLR-008*/
		if ((TRUE == Config_data.eng_sdi)&& \
		(!CheckMinMax(Page_settings.Text_settings[loop_textcnt-ONE].sdi, ZERO , THREE))&&
         (Pdi_error_count < MAX_ERROR_MSG))
        {
            /*Frame the Error Message */
            BuildErrorMsg(element, labelstring, "SDI",
                        Error_msg_string[Pdi_error_count]);

            /* Increment the PDI Error Index */
            ++Pdi_error_count;
        }

        /* Check for TXT_ALIGN*/
        /*hdudispfpdicheck-CheckText-DB-LLR-003*/
        if (!CheckMinMax(Page_settings.Text_settings[loop_textcnt-ONE].txt_align, ALIGN_CENTER,
            ALIGN_LEFT) && (Pdi_error_count < MAX_ERROR_MSG) &&
           (Text_parameter_occurrence[loop_textcnt-ONE] & BIT_THREE))
        {
            /* Frame the Error Message*/
            BuildErrorMsg(element, labelstring, "TXT_ALIGN", Error_msg_string[Pdi_error_count]);

            /* Increment the PDI Error Index*/
            ++Pdi_error_count;

        }

        /* Check for TXT_FONT*/
        /*hdudispfpdicheck-CheckText-DB-LLR-004*/
        if (!CheckFont(Page_settings.Text_settings[loop_textcnt-ONE].txt_font) &&
           (Pdi_error_count < MAX_ERROR_MSG) &&
           (Text_parameter_occurrence[loop_textcnt-ONE] & BIT_FOUR))
        {
            /* Frame the Error Message*/
            BuildErrorMsg(element, labelstring, "TXT_FONT", Error_msg_string[Pdi_error_count]);

            /* Increment the PDI Error Index*/
            ++Pdi_error_count;

        }

        /* Check for TXT_AXIS*/
        /*hdudispfpdicheck-CheckText-DB-LLR-002*/
        if ((!CheckAxisMinMax(Page_settings.Text_settings[loop_textcnt-ONE].txt_axis.u16_x, \
		    ZERO, PANEL_HEIGHT,PANEL_WIDTH)
            || !CheckAxisMinMax(Page_settings.Text_settings[loop_textcnt-ONE].txt_axis.u16_y, ZERO,
            PANEL_WIDTH,PANEL_HEIGHT)) && (Pdi_error_count < MAX_ERROR_MSG))
        {
            /* Frame the Error Message*/
            BuildErrorMsg(element, labelstring, "TXT_AXIS", Error_msg_string[Pdi_error_count]);

            /* Increment the PDI Error Index*/
            ++Pdi_error_count;
        }

        /*hdudispfpdicheck-CheckText-DB-LLR-021*/
        new_line_indication= CalStringParam(Page_settings.Text_settings[loop_textcnt-ONE].
      		  txt_string, &max_width, &lin_count );
        max_width= (T_UINT16)(max_width * (T_UINT16)(FontsGetStringWidth((T_UINT8 *)char_a,
           		Page_settings.Text_settings[loop_textcnt-ONE].txt_font)));
        lin_count= (T_UINT16)(lin_count *(T_UINT16)(FontsGetFontHeight
                   (Page_settings.Text_settings[loop_textcnt-ONE].txt_font)));

        if (ONE == (max_width & 1))
        {
     	   max_width = (T_UINT16)(max_width + ONE);
        }

           /* If center alignment adjust the x and y draw point. */
           if(ALIGN_CENTER == Page_settings.Text_settings[loop_textcnt-ONE].txt_align)
           {

              /* Back up half of the string width. */
               text_x_axis = (T_INT16)(Page_settings.Text_settings[loop_textcnt-ONE].
                       txt_axis.u16_x -(T_UINT16)((max_width)/(T_INT16)TWO));



              /* Back up half the font height. */
               text_y_axis = (T_INT16)(Page_settings.Text_settings[loop_textcnt-ONE].
                       txt_axis.u16_y -(T_INT16)((T_INT16)(lin_count)/(T_INT16)TWO));
           }
           else if(ALIGN_CENTER_LEFT == Page_settings.Text_settings[loop_textcnt-ONE].txt_align)
           {

              /* Back up half the font height. */
               text_x_axis = (T_INT16)Page_settings.Text_settings[loop_textcnt-ONE].txt_axis.u16_x;
               text_y_axis = (T_INT16) (Page_settings.Text_settings[loop_textcnt-ONE].
                       txt_axis.u16_y -(T_INT16)(((T_INT16)lin_count)/(T_INT16)TWO));
           }
           else if(ALIGN_RIGHT == Page_settings.Text_settings[loop_textcnt-ONE].txt_align)
           {
               if(E_10_INCH == Display_size)
               {
                   text_x_axis = (T_INT16)( ((T_INT16)((PANEL_WIDTH))) -
				                 (((T_INT16)((max_width)))));
                   text_y_axis =
				   (T_INT16)Page_settings.Text_settings[loop_textcnt-ONE].txt_axis.u16_y;
               }
               else if (E_7_INCH == Display_size)
               {
                   text_x_axis = (T_INT16)( ((T_INT16)((PANEL_HEIGHT))) -
				                     (((T_INT16)((max_width)))));
                   text_y_axis =
				   (T_INT16)Page_settings.Text_settings[loop_textcnt-ONE].txt_axis.u16_y;
               }
               else
               {
            	   ;
               }
           }
           else
           {
               text_x_axis= (T_INT16)Page_settings.Text_settings[loop_textcnt-ONE].txt_axis.u16_x;
               text_y_axis= (T_INT16)Page_settings.Text_settings[loop_textcnt-ONE].txt_axis.u16_y;
           }

           /* Check for TXT_AXIS*/
           /*hdudispfpdicheck-CheckText-DB-LLR-022*/
              if (((!CheckAxisMinMax((T_INT16)(text_x_axis + max_width), ZERO,
			         PANEL_HEIGHT,PANEL_WIDTH)) ||
                  (!CheckAxisMinMax((T_INT16)(lin_count + text_y_axis), ZERO,
				    PANEL_WIDTH,PANEL_HEIGHT)))
                  && (Pdi_error_count < MAX_ERROR_MSG))
              {
                  /* Frame the Error Message*/
                  BuildErrorMsg(element, labelstring, "TXT_AXIS",
				              Error_msg_string[Pdi_error_count]);
                  /* Increment the PDI Error Index*/
                  ++Pdi_error_count;
              }

   	          /* Check for TXT_AXIS*/

              if (((!CheckAxisMinMax(text_x_axis, ZERO, PANEL_HEIGHT,PANEL_WIDTH))
                  || ((!CheckAxisMinMax(text_y_axis, ZERO,PANEL_WIDTH,PANEL_HEIGHT))))
                  && (Pdi_error_count < MAX_ERROR_MSG))
              {
                  /* Frame the Error Message*/
                  BuildErrorMsg(element, labelstring, "TXT_AXIS",
				           Error_msg_string[Pdi_error_count]);
                  /* Increment the PDI Error Index*/
                  ++Pdi_error_count;
              }
	    /* Check for TXT_BIT*/
	    /*hdudispfpdicheck-CheckText-DB-LLR-010*/
	    if (!CheckMinMax(Page_settings.Text_settings[loop_textcnt-1].txt_bit, MIN_START_BIT,
	    	MAX_START_BIT) && (Pdi_error_count < MAX_ERROR_MSG)&&
		    (Text_parameter_occurrence[loop_textcnt-1]&BIT_ONE))
	    {
	            /* Frame the Error Message*/
	            BuildErrorMsg(element, labelstring, "TXT_BIT", Error_msg_string[Pdi_error_count]);

	            /* Increment the PDI Error Index*/
	            ++Pdi_error_count;

	     }
	    /* Check for TXT_CROSS_VAL*/
	    /*hdudispfpdicheck-CheckText-DB-LLR-011*/
	    if ((!CheckMinMax(Page_settings.Text_settings[loop_textcnt-ONE].txt_cross_val_type,
            	ONE, MAX_LIM_VAL_TYPE) ||
	    	!CheckFloatMinMax(Page_settings.Text_settings[loop_textcnt-1].txt_cross_val,
	    		MIN_RANGE,MAX_RANGE)) && (Pdi_error_count < MAX_ERROR_MSG)&&
			(Text_parameter_occurrence[loop_textcnt-1]&BIT_TWO))
	    {
	            /* Frame the Error Message*/
	            BuildErrorMsg(element, labelstring, "TXT_CROSS_VAL", \
				Error_msg_string[Pdi_error_count]);

	            /* Increment the PDI Error Index*/
	            ++Pdi_error_count;

	     }


		/* Check for TXT_COLOR*/
		/*hdudispfpdicheck-CheckText-DB-LLR-005*/
		if (!CheckColor(Page_settings.Text_settings[loop_textcnt-ONE].txt_color)
		   && (Pdi_error_count < MAX_ERROR_MSG) &&
			(Text_parameter_occurrence[loop_textcnt-ONE] & BIT_FIVE))
		{
			/* Frame the Error Message*/
			BuildErrorMsg(element,labelstring,"TXT_COLOR",Error_msg_string[Pdi_error_count]);

			/* Increment the PDI Error Index*/
			++Pdi_error_count;

		}

        /* Check for TXT_STATE*/
        /*hdudispfpdicheck-CheckText-DB-LLR-006*/
        if (((Page_settings.Text_settings[loop_textcnt-ONE].txt_state != TXT_STATE_NORMAL) &&
        	(Page_settings.Text_settings[loop_textcnt-ONE].txt_state !=TXT_STATE_REVERSE))
			&& (Pdi_error_count < MAX_ERROR_MSG) &&
           (Text_parameter_occurrence[loop_textcnt-ONE] & BIT_SIX))
        {
            /* Frame the Error Message*/
            BuildErrorMsg(element, labelstring, "TXT_STATE", Error_msg_string[Pdi_error_count]);

            /* Increment the PDI Error Index*/
            ++Pdi_error_count;
        }

        /* Check for TXT_FLASH*/
        /*hdudispfpdicheck-CheckText-DB-LLR-007*/
        if (((Page_settings.Text_settings[loop_textcnt-ONE].txt_flash != TEXT_FLASH_ON) &&
        	(Page_settings.Text_settings[loop_textcnt-ONE].txt_flash != TEXT_FLASH_OFF)) &&
			(Pdi_error_count < MAX_ERROR_MSG) &&
           (Text_parameter_occurrence[loop_textcnt-ONE] & BIT_SEVEN))
        {
            /* Frame the Error Message*/
            BuildErrorMsg(element, labelstring, "TXT_FLASH", Error_msg_string[Pdi_error_count]);

            /* Increment the PDI Error Index*/
            ++Pdi_error_count;
        }
        /* Check for TXT_REDX_AXIS*/
               /*hdudispfpdicheck-CheckText-DB-LLR-012*/
               if ((!CheckAxisMinMax(Page_settings.Text_settings[loop_textcnt-1].
               	txt_redx_axis.u16_x,0,PANEL_HEIGHT,PANEL_WIDTH)   ||\
				!CheckAxisMinMax(Page_settings.Text_settings[loop_textcnt-1].
               			txt_redx_axis.u16_y, 0, PANEL_WIDTH,PANEL_HEIGHT)) &&\
						(Pdi_error_count < MAX_ERROR_MSG)
       		          &&(Text_parameter_occurrence [loop_textcnt-1]&BIT_EIGHT))
               {
                   /*Frame the Error Message*/
                   BuildErrorMsg(element, labelstring, "TXT_REDX_AXIS",\
				   Error_msg_string[Pdi_error_count]);

                   /* Increment the PDI Error Index*/
                   ++Pdi_error_count;

               }
               /* Check for TXT_REDX_WIDTH*/
               /*hdudispfpdicheck-CheckText-DB-LLR-013*/
               if(!CheckAxisMinMax(Page_settings.Text_settings[loop_textcnt-1].txt_redx_width, 0,
                  PANEL_HEIGHT,PANEL_WIDTH) &&(Pdi_error_count < MAX_ERROR_MSG )&&
       	          (Text_parameter_occurrence[loop_textcnt-1]&BIT_NINE) )
               {
                   /* Frame the Error Message*/
                   BuildErrorMsg(element, labelstring, "TXT_REDX_WIDTH",\
				   Error_msg_string[Pdi_error_count]);

                   /* Increment the PDI Error Index*/
                   ++Pdi_error_count;

               }

               /* Check for TXT_REDX_HEIGHT*/
               /*hdudispfpdicheck-CheckText-DB-LLR-014*/
               if (!CheckAxisMinMax(Page_settings.Text_settings[loop_textcnt-1].
                    txt_redx_height ,0, PANEL_WIDTH,PANEL_HEIGHT) &&
                   (Pdi_error_count < MAX_ERROR_MSG)&&
       	          (Text_parameter_occurrence[loop_textcnt-1]&BIT_TEN))
               {
                   /* Frame the Error Message*/
                   BuildErrorMsg(element, labelstring, "TXT_REDX_HEIGHT",
       			Error_msg_string[Pdi_error_count]);
                   /* Increment the PDI Error Index*/
                   ++Pdi_error_count;

               }

        /* Check for TXT_REDX_X_AXIS*/
        /*hdudispfpdicheck-CheckText-DB-LLR-018*/
        if ((!CheckAxisMinMax(Page_settings.Text_settings[loop_textcnt-1].
        	txt_redx_axis.u16_x,Page_settings.Text_settings[loop_textcnt-1].txt_redx_width / 2,
			PANEL_HEIGHT,PANEL_WIDTH)   ||\
        !CheckAxisMinMax(Page_settings.Text_settings[loop_textcnt-1].txt_redx_axis.u16_x, ZERO,
        	PANEL_HEIGHT - (Page_settings.Text_settings[loop_textcnt-1].txt_redx_width / 2),
			PANEL_WIDTH - (Page_settings.Text_settings[loop_textcnt-1].txt_redx_width / 2)))
        		&&(Pdi_error_count < MAX_ERROR_MSG)
               &&(Text_parameter_occurrence [loop_textcnt-1]&BIT_EIGHT))
        {
            /*Frame the Error Message*/
            BuildErrorMsg(element, labelstring, "TXT_REDX_AXIS",\
           Error_msg_string[Pdi_error_count]);

            /* Increment the PDI Error Index*/
            ++Pdi_error_count;

        }

        /* Check for TXT_REDX_Y_AXIS*/
        /*hdudispfpdicheck-CheckText-DB-LLR-019*/
        if ((!CheckAxisMinMax(Page_settings.Text_settings[loop_textcnt-1].
        	txt_redx_axis.u16_y,Page_settings.Text_settings[loop_textcnt-1].txt_redx_height / 2,
			PANEL_WIDTH , PANEL_HEIGHT)   ||\
        !CheckAxisMinMax(Page_settings.Text_settings[loop_textcnt-1].txt_redx_axis.u16_y, ZERO,
        	PANEL_WIDTH - (Page_settings.Text_settings[loop_textcnt-1].txt_redx_height / 2),
			PANEL_HEIGHT - (Page_settings.Text_settings[loop_textcnt-1].txt_redx_height / 2)))
        		&&(Pdi_error_count < MAX_ERROR_MSG)
               &&(Text_parameter_occurrence [loop_textcnt-1]&BIT_EIGHT))
        {
            /*Frame the Error Message*/
            BuildErrorMsg(element, labelstring, "TXT_REDX_AXIS",\
           Error_msg_string[Pdi_error_count]);

            /* Increment the PDI Error Index*/
            ++Pdi_error_count;
        }

               /* Check for TXT_REDX_OFFSET_AXIS*/
               /*hdudispfpdicheck-CheckText-DB-LLR-015*/
             if ((!CheckAxisMinMax2((T_INT16)Page_settings.Text_settings[loop_textcnt-1].
                txt_redx_offset_axis.u16_x,-PANEL_HEIGHT,-PANEL_WIDTH, PANEL_HEIGHT,PANEL_WIDTH)||
			   !CheckAxisMinMax2((T_INT16)Page_settings.Text_settings[loop_textcnt-1].
              txt_redx_offset_axis.u16_y, -PANEL_WIDTH,-PANEL_HEIGHT, PANEL_WIDTH,PANEL_HEIGHT))&&
				(Pdi_error_count < MAX_ERROR_MSG)&&
       		          (Text_parameter_occurrence[loop_textcnt-1]&BIT_ELEVEN))
               {
                   /* Frame the Error Message*/
                   BuildErrorMsg(element, labelstring, "TXT_REDX_OFFSET_AXIS",
                           Error_msg_string[Pdi_error_count]);

                   /* Increment the PDI Error Index*/
                   ++Pdi_error_count;

               }

               /* Check for TXT_REDX_FONT*/
               /*hdudispfpdicheck-CheckText-DB-LLR-016*/
               if (!CheckFont(Page_settings.Text_settings[loop_textcnt-1].txt_redx_font) &&
            	  (Pdi_error_count < MAX_ERROR_MSG)&&
       		      (Text_parameter_occurrence[loop_textcnt-1]&BIT_TWELVE))
               {
                   /* Frame the Error Message*/
                   BuildErrorMsg(element, labelstring, "TXT_REDX_FONT", \
				   Error_msg_string[Pdi_error_count]);

                   /* Increment the PDI Error Index*/
                   ++Pdi_error_count;

               }

               /* Check for TB_REDX_TXT string length*/
               /*hdudispfpdicheck-CheckText-DB-LLR-017*/
               if (!CheckString( Page_settings.Text_settings[loop_textcnt-1].txt_redx_txt,
                   MAX_STRING_CHAR_TXT) && (Pdi_error_count < MAX_ERROR_MSG)&&
       		          (Text_parameter_occurrence[loop_textcnt-1]&BIT_THIRTEEN))
               {
                   /* Frame the Error Message*/
                   BuildErrorMsg(element, labelstring, "TXT_REDX_TXT",\
				   Error_msg_string[Pdi_error_count]);

                   /* Increment the PDI Error Index*/
                   ++Pdi_error_count;

               }

			   /*hdudispfpdicheck-CheckText-DB-LLR-020*/
               new_line_indication= CalStringParam(Page_settings.Text_settings[loop_textcnt-ONE]
			   .txt_redx_txt,&max_width, &lin_count );

               max_width= (T_UINT16)(max_width * (T_UINT16)(FontsGetStringWidth((T_UINT8 *)char_a,
                  		Page_settings.Text_settings[loop_textcnt-ONE].txt_redx_font)));
               lin_count= (T_UINT16)(lin_count *(T_UINT16)(FontsGetFontHeight
                          (Page_settings.Text_settings[loop_textcnt-ONE].txt_redx_font)));
               if (ONE == (max_width & 1))
               {
            	   max_width = (T_UINT16)(max_width + 1);
               }
               else
               {
            	   ;
               }

               /* Check for TXT_REDX_OFFSET_AXIS*/
              if (((TRUE == new_line_indication) ||
                ((!CheckAxisMinMax((T_INT32)((T_INT16)(Page_settings.\
                 Text_settings[loop_textcnt-ONE].txt_redx_offset_axis.u16_x) +
			     Page_settings.Text_settings[loop_textcnt-ONE].txt_redx_axis.u16_x +
			     (max_width/2)),ZERO, PANEL_HEIGHT,PANEL_WIDTH))||
                 (!CheckAxisMinMax((T_INT32)((T_INT16)(Page_settings.\
			     Text_settings[loop_textcnt-ONE].txt_redx_offset_axis.u16_x) +
			     Page_settings.Text_settings[loop_textcnt-ONE].txt_redx_axis.u16_x
        		 - (max_width/2)),ZERO, PANEL_HEIGHT,PANEL_WIDTH))||
                 (!CheckAxisMinMax((T_INT32)((T_INT16)(Page_settings.
				 Text_settings[loop_textcnt-ONE].txt_redx_offset_axis.u16_y) +
				 Page_settings.Text_settings[loop_textcnt-ONE].txt_redx_axis.u16_y
        		 + (lin_count/2)), ZERO, PANEL_WIDTH,PANEL_HEIGHT))  || \
                 (!CheckAxisMinMax((T_INT32)((T_INT16)(Page_settings.
				 Text_settings[loop_textcnt-ONE].txt_redx_offset_axis.u16_y) +
				 Page_settings.Text_settings[loop_textcnt-ONE].txt_redx_axis.u16_y
        		 - (lin_count/2)), ZERO,PANEL_WIDTH,PANEL_HEIGHT))))
        		 && (Pdi_error_count < MAX_ERROR_MSG)
                 && (Text_parameter_occurrence[loop_textcnt-ONE] & BIT_ELEVEN))
               {
                   /* Frame the Error Message*/
                  BuildErrorMsg(element, labelstring, "TXT_REDX_OFFSET_AXIS",
                           Error_msg_string[Pdi_error_count]);

                   /* Increment the PDI Error Index*/
                  ++Pdi_error_count;

               }
    }
}
/*
 *
 * Function                : CheckPoly
 *
 * Description             : This function checks Text parameters
 *
 * Formal parameter(s)     : None
 *
 * Return Value            : None
 *
 * Assumption              : None
 *
 */
static void CheckPoly()
{

    T_CHAR element[5] = "POLY";    /* Element type*/
    T_CHAR labelstring[5]={"\0"};     /* Variable used to store label in string format*/
    T_UINT16 loop_polycnt=ZERO;        /* Graph count required for loop*/
    T_UINT8 loop_polypts =ZERO;

    /*hdudispfpdicheck-CheckPoly-DB-LLR-001*/
    if(Pg_cnt>MAX_POLYGON_GRAPHS)
    {
    	return;
    }
	else
	{
	    ; /* Do Nothing */
	}

    for (loop_polycnt = 1; loop_polycnt <= Pg_cnt; loop_polycnt++)
    {

    	   /* Check for POLY_SHAPE*/
		        if (!CheckMinMax(Pg_settings[loop_polycnt-1].poly_shape,\
				FG_CAPITAL_R_POINTER, FG_POINTER_SHAPE12) &&
		            (Pdi_error_count < MAX_ERROR_MSG))
		        {
		            /*Frame the Error Message*/
		            BuildErrorMsg(element, labelstring, "POLY_SHAPE", \
					Error_msg_string[Pdi_error_count]);

		            /* Increment the PDI Error Index*/
		            ++Pdi_error_count;

		        }

		        /* Check for POLY_NO_PTS*/
		        /*hdudispfpdicheck-CheckPoly-DB-LLR-002*/
		        if (!CheckMinMax(Pg_settings[loop_polycnt-1].poly_no_pts,\
				THREE, M_FOURTY_FIVE) &&(Pdi_error_count < MAX_ERROR_MSG))
		        {
		            /*Frame the Error Message*/
		            BuildErrorMsg(element, labelstring, "POLY_NO_PTS",\
					Error_msg_string[Pdi_error_count]);

		            /* Increment the PDI Error Index*/
		            ++Pdi_error_count;

		        }
		        /* Check for POLY_INC_NO_PTS*/
		        /*hdudispfpdicheck-CheckPoly-DB-LLR-003*/
		        if (((ZERO != Pg_settings[loop_polycnt-1].poly_inc_no_pts) &&
		        	(!CheckMinMax(Pg_settings[loop_polycnt-1].poly_inc_no_pts,\
				THREE, M_FOURTY_FIVE))) && (Pdi_error_count < MAX_ERROR_MSG))
		        {
		            /*Frame the Error Message*/
		            BuildErrorMsg(element, labelstring, "POLY_INC_NO_PTS", \
					Error_msg_string[Pdi_error_count]);

		            /* Increment the PDI Error Index*/
		            ++Pdi_error_count;

		        }
 		        /*hdudispfpdicheck-CheckPoly-DB-LLR-004 */
		        /* Check for POLY_PTS*/
		       for(loop_polypts = ZERO; loop_polypts<  \
		        Pg_settings[loop_polycnt-1].poly_no_pts; loop_polypts++)
		        {
			        if (!CheckFloatMinMax((T_FLOAT)Pg_settings[loop_polycnt-1].\
			        poly_pts[loop_polypts][0],(T_FLOAT)-1.0f, (T_FLOAT)1.0f) &&
			        (!CheckFloatMinMax((T_FLOAT)Pg_settings[loop_polycnt-1].\
			        poly_pts[loop_polypts][1],(T_FLOAT)-1.0f, (T_FLOAT)1.0f)) && \
					(Pdi_error_count < MAX_ERROR_MSG))
			        {
			            /*Frame the Error Message*/
			            BuildErrorMsg(element, labelstring, "POLY_PTS", \
						Error_msg_string[Pdi_error_count]);

			            /* Increment the PDI Error Index*/
			            ++Pdi_error_count;
			        }
		        }
		        /* Check for POLY_INC_PTS*/
		        for(loop_polypts = ZERO; loop_polypts<  \
		        Pg_settings[loop_polycnt-1].poly_inc_no_pts; loop_polypts++)
		        {
			        if (!CheckFloatMinMax((T_FLOAT)Pg_settings[loop_polycnt-1].\
					 poly_inc_pts[loop_polypts][0],-1.0f, 1.0f) &&
			        (!CheckFloatMinMax((T_FLOAT)Pg_settings[loop_polycnt-1].\
    				 poly_inc_pts[loop_polypts][1],-1.0f, 1.0f)) && (Pdi_error_count < MAX_ERROR_MSG))
			        {
			            /*Frame the Error Message*/
			            BuildErrorMsg(element, labelstring, "POLY_INC_PTS", \
						Error_msg_string[Pdi_error_count]);

			            /* Increment the PDI Error Index*/
			            ++Pdi_error_count;

			        }
		        }
    }
}


/*
 *
 * Function                : CheckForegroundParameters
 *
 * Description             : This function checks BarGraph,Round dial,Number box,
 *							 Carrot Graph,Text box and Text.
 *
 * Formal parameter(s)     : None
 *
 * Return Value            : None
 *
 * Assumption              : None
 *
 */
static void CheckForegroundParameters()
{
    /*hdudispfpdicheck-CheckForegroundParameters-DB-LLR-001*/
    CheckBarGraph();
    CheckRoundDial();
    CheckNumberBox();
    CheckCarrotGraph();
    CheckTextBox();
    CheckText();

}

/*
 *
 * Function                : CheckCasLocationSett
 *
 * Description             : This function checks CAS parameters from the pdi
 *
 * Formal parameter(s)     : None
 *
 * Return Value            : None
 *
 * Assumption              : None
 *
 */
static void CheckCasLocationSett()
{
    T_CHAR element[4]  = "CAS";   /* Element type*/
    T_CHAR pagestring[5]={0};     /* Variable used to store label in string format*/
    T_UINT8 pagesize = 4;
    T_UINT16 col_max_width = ZERO;
    T_UINT16 string_height = ZERO;
    T_UINT16 row_value = ZERO;
    T_UINT16 col_value = ZERO;

    /*hdudispfpdicheck-CheckCasLocationSett-DB-LLR-001*/
    if (FALSE == Caslocationset_parameters)
    {
        return;
    }

    /* Check for page_num*/
	 /*hdudispfpdicheck-CheckCasLocationSett-DB-LLR-002*/
    IntToStringTrim(Page_settings.page_num, pagesize, pagestring);

    /* Check for cas_axis*/
    if ((!CheckAxisMinMax(Page_settings.Cas_loc_settings.cas_axis.u16_x, ZERO, \
	     PANEL_HEIGHT-6,PANEL_WIDTH-6)   ||
         !CheckAxisMinMax(Page_settings.Cas_loc_settings.cas_axis.u16_y, ZERO, \
		 PANEL_WIDTH,PANEL_HEIGHT)) &&
         (Pdi_error_count < MAX_ERROR_MSG))
    {
        /* Frame the Error Message*/
        BuildErrorMsg(element, pagestring, "CAS_AXIS", Error_msg_string[Pdi_error_count]);

        /* Increment the PDI Error Index*/
        ++Pdi_error_count;
        Cas_error = (ONE << Page_num) | Cas_error;
    }

    /* Check for cas_num_rows*/
      /*hdudispfpdicheck-CheckCasLocationSett-DB-LLR-003*/
    if (!CheckMinMax(Page_settings.Cas_loc_settings.cas_num_rows, ONE, MAX_CAS_NUM_ROWS) &&
        (Pdi_error_count < MAX_ERROR_MSG))
    {
        /* Frame the Error Message*/
        BuildErrorMsg(element, pagestring, "CAS_NUM_ROWS", Error_msg_string[Pdi_error_count]);

        /* Increment the PDI Error Index*/
        ++Pdi_error_count;
        Cas_error = (ONE << Page_num) | Cas_error;
    }

    /* Check for cas_num_columns*/
      /*hdudispfpdicheck-CheckCasLocationSett-DB-LLR-004*/
    if (!CheckMinMax(Page_settings.Cas_loc_settings.cas_num_column, ONE, MAX_CAS_COLUMNS) &&
        (Pdi_error_count < MAX_ERROR_MSG))
    {
        /* Frame the Error Message*/
        BuildErrorMsg(element, pagestring, "CAS_NUM_COLUMN",\
		Error_msg_string[Pdi_error_count]);

        /* Increment the PDI Error Index*/
        ++Pdi_error_count;
        Cas_error = (ONE << Page_num) | Cas_error;
    }

    /* Check for cas_row_height*/
      /*hdudispfpdicheck-CheckCasLocationSett-DB-LLR-005*/
    if (!CheckAxisMinMax(Page_settings.Cas_loc_settings.cas_row_height, ZERO,
        PANEL_WIDTH,PANEL_HEIGHT) &&(Pdi_error_count < MAX_ERROR_MSG))
    {
        /* Frame the Error Message*/
        BuildErrorMsg(element, pagestring, "CAS_ROW_HEIGHT", \
		Error_msg_string[Pdi_error_count]);

        /* Increment the PDI Error Index*/
        ++Pdi_error_count;
        Cas_error = (ONE << Page_num) | Cas_error;
    }

    /* Check for cas_col_width*/
      /*hdudispfpdicheck-CheckCasLocationSett-DB-LLR-006*/
    if (!CheckAxisMinMax(Page_settings.Cas_loc_settings.cas_col_width
    		, ZERO, PANEL_HEIGHT,PANEL_WIDTH) &&
        (Pdi_error_count < MAX_ERROR_MSG))
    {
        /* Frame the Error Message*/
        BuildErrorMsg(element, pagestring, "CAS_COL_WIDTH", \
		Error_msg_string[Pdi_error_count]);

        /* Increment the PDI Error Index*/
        ++Pdi_error_count;
        Cas_error = (ONE << Page_num) | Cas_error;
    }
    /* Check cas_font*/
      /*hdudispfpdicheck-CheckCasLocationSett-DB-LLR-007*/
    if (!CheckFont(Page_settings.Cas_loc_settings.cas_font) &&
        (Pdi_error_count < MAX_ERROR_MSG))
    {
        /* Frame the Error Message*/
        BuildErrorMsg(element, pagestring, "CAS_FONT", \
		Error_msg_string[Pdi_error_count]);

        /* Increment the PDI Error Index*/
        ++Pdi_error_count;
        Cas_error = (ONE << Page_num) | Cas_error;
    }

	 /*hdudispfpdicheck-CheckCasLocationSett-DB-LLR-012*/
    row_value = (T_UINT16)(Page_settings.Cas_loc_settings.cas_num_rows*
						  Page_settings.Cas_loc_settings.cas_row_height);
    col_value = (T_UINT16)(Page_settings.Cas_loc_settings.cas_num_column*
						  Page_settings.Cas_loc_settings.cas_col_width);
    col_max_width = (T_UINT16)(((Page_settings.Cas_loc_settings.cas_num_column - 1)*
					 Page_settings.Cas_loc_settings.cas_col_width)+
                    (FontsGetStringWidth(Cas_messages[Index_value-1].cas_string,
					Page_settings.Cas_loc_settings.cas_font)));
    string_height = (T_UINT16)(((Page_settings.Cas_loc_settings.cas_num_rows - 1)*
					Page_settings.Cas_loc_settings.cas_row_height)+
                     (FontsGetFontHeight(Page_settings.Cas_loc_settings.cas_font)));

        if ((!CheckAxisMinMax(Page_settings.Cas_loc_settings.cas_axis.u16_y + row_value, ZERO, \
             PANEL_WIDTH,PANEL_HEIGHT)   ||
            (!CheckAxisMinMax(Page_settings.Cas_loc_settings.cas_axis.u16_x + col_max_width,\
        	 ZERO,PANEL_HEIGHT-DEC_SIX,PANEL_WIDTH-DEC_SIX) ||
             !CheckAxisMinMax(Page_settings.Cas_loc_settings.cas_axis.u16_x + col_value, ZERO,\
             PANEL_HEIGHT,PANEL_WIDTH) ||
			 (!CheckAxisMinMax(Page_settings.Cas_loc_settings.cas_axis.u16_y + string_height, ZERO,\
			  PANEL_WIDTH,PANEL_HEIGHT)))) &&
             (Pdi_error_count < MAX_ERROR_MSG))
        {
            /* Frame the Error Message*/
            BuildErrorMsg(element, pagestring, "CAS_AXIS", Error_msg_string[Pdi_error_count]);
            /* Increment the PDI Error Index*/
            ++Pdi_error_count;
            Cas_error = (ONE << Page_num) | Cas_error;
        }

    /* Check for cas_adv_flash_timer*/
      /*hdudispfpdicheck-CheckCasLocationSett-DB-LLR-008*/
    if (!CheckMinMax( Page_settings.Cas_loc_settings.cas_adv_flash_timer, ONE, MAX_TIMER) &&
       (Page_settings.Cas_loc_settings.cas_adv_flash_timer != MAX_CAS_FLASH_TIMER )&&
	   (Page_settings.Cas_loc_settings.cas_adv_flash_timer != MAX_CAS_FLASH_TIMER_9999 )&&
	   (Page_settings.Cas_loc_settings.cas_adv_flash_timer != ZERO) &&
        (Pdi_error_count < MAX_ERROR_MSG))
    {
        /* Frame the Error Message*/
        BuildErrorMsg(element, pagestring, "CAS_ADV_FLASH_TIMER", \
		Error_msg_string[Pdi_error_count]);

        /* Increment the PDI Error Index*/
        ++Pdi_error_count;
        Cas_error = (ONE << Page_num) | Cas_error;
    }

    /* Check for cas_caut_flash_timer*/
      /*hdudispfpdicheck-CheckCasLocationSett-DB-LLR-009*/
    if ((!CheckMinMax(Page_settings.Cas_loc_settings.cas_caut_flash_timer, ONE, MAX_TIMER) &&
    		(Page_settings.Cas_loc_settings.cas_caut_flash_timer != ZERO) &&
			(Page_settings.Cas_loc_settings.cas_caut_flash_timer != MAX_CAS_FLASH_TIMER_9999) &&
			(Page_settings.Cas_loc_settings.cas_caut_flash_timer != MAX_CAS_FLASH_TIMER)) &&
        (Pdi_error_count < MAX_ERROR_MSG))
    {
        /* Frame the Error Message*/
        BuildErrorMsg(element,pagestring,"CAS_CAUT_FLASH_TIMER",\
		Error_msg_string[Pdi_error_count]);

        /* Increment the PDI Error Index*/
        ++Pdi_error_count;
        Cas_error = (ONE << Page_num) | Cas_error;
    }

    /* Check for cas_warn_flash_timer*/
      /*hdudispfpdicheck-CheckCasLocationSett-DB-LLR-010*/
    if ((!CheckMinMax(Page_settings.Cas_loc_settings.cas_warn_flash_timer, ONE, MAX_TIMER) &&
    		(Page_settings.Cas_loc_settings.cas_warn_flash_timer != ZERO) &&
			(Page_settings.Cas_loc_settings.cas_warn_flash_timer != MAX_CAS_FLASH_TIMER_9999) &&
			(Page_settings.Cas_loc_settings.cas_warn_flash_timer != MAX_CAS_FLASH_TIMER)) &&
        (Pdi_error_count < MAX_ERROR_MSG))
    {
        /* Frame the Error Message*/
        BuildErrorMsg(element,pagestring,"CAS_WARN_FLASH_TIMER",\
		Error_msg_string[Pdi_error_count]);

        /* Increment the PDI Error Index*/
        ++Pdi_error_count;
        Cas_error = (ONE << Page_num) | Cas_error;
    }

    /* Check for cas_redx_txt*/
      /*hdudispfpdicheck-CheckCasLocationSett-DB-LLR-011*/
    if (!CheckString(Page_settings.Cas_loc_settings.cas_redx_txt, MAX_STRING_CHAR_TXT) &&
        (Pdi_error_count < MAX_ERROR_MSG))
    {
        /* Frame the Error Message*/
        BuildErrorMsg(element, pagestring, "CAS_REDX_TXT", \
		Error_msg_string[Pdi_error_count]);

        /* Increment the PDI Error Index*/
        ++Pdi_error_count;
        Cas_error = (ONE << Page_num) | Cas_error;
    }
}

/*
 *
 * Function                : CheckExceedParam
 *
 * Description             : This function checks Exceed parameters
 *
 * Formal parameter(s)     : None
 *
 * Return Value            : None
 *
 * Assumption              : None
 *
 */
static void CheckExceedParam()
{
    T_CHAR element[7] = "EXCEED";          /* Element type*/
    T_CHAR bitstring[5]={0};               /* Variable used to store label in string format*/
    T_CHAR bitsize = TWO;                  /* Variable used to store label in string format*/
    T_UINT16 loop_exceedcnt=ZERO;          /* EXCEED messages count required for loop*/
    T_UINT32 exceed_bit_temp=(T_UINT8)ZERO;
    T_UINT16 string_width = ZERO;
    T_UINT16 string_height = ZERO;
    T_CHAR letter_e[] = "E";

    for (loop_exceedcnt = ZERO; loop_exceedcnt < Exceed_cnt; loop_exceedcnt++)
    {
        /* Converts the label as array of characters*/
        exceed_bit_temp = (T_UINT32)Exceed_data[loop_exceedcnt].exceed_bit + (T_UINT32)TEN;

        IntToStringTrim((T_UINT8)exceed_bit_temp, (T_UINT8)bitsize, bitstring);
        /*hdudispfpdicheck-CheckExceedParam-DB-LLR-001*/
        /* Check exceed_bit*/
        if (!CheckMinMax((T_INT32)exceed_bit_temp, MIN_START_BIT, MAX_START_BIT) &&
            (Pdi_error_count < MAX_ERROR_MSG))
        {
            /* Frame the Error Message*/
            BuildErrorMsg(element, bitstring, "EXCEED_BIT", Error_msg_string[Pdi_error_count]);

            /* Increment the PDI Error Index*/
            ++Pdi_error_count;
            Exceed_error = ((ONE << Page_num ) | Exceed_error);
        }

        /* Check label*/
        /*hdudispfpdicheck-CheckExceedParam-DB-LLR-002*/
        if (!CheckMinMax(Exceed_data[loop_exceedcnt].label, ONE, MAX_LABEL) &&
            (Pdi_error_count < MAX_ERROR_MSG))
        {
            /* Frame the Error Message*/
            BuildErrorMsg(element, bitstring, "LABEL", Error_msg_string[Pdi_error_count]);

            /* Increment the PDI Error Index*/
            ++Pdi_error_count;
            Exceed_error = ((ONE << Page_num ) | Exceed_error);
        }

		/* Check SDI */
         /*hdudispfpdicheck-CheckExceedParam-DB-LLR-005*/
		if ((TRUE == Config_data.eng_sdi)&& \
		(!CheckMinMax(Exceed_data[loop_exceedcnt].sdi, ZERO , THREE))&&
         (Pdi_error_count < MAX_ERROR_MSG))
        {
            /*Frame the Error Message */
            BuildErrorMsg(element, bitstring, "SDI",
                        Error_msg_string[Pdi_error_count]);

            /* Increment the PDI Error Index */
            ++Pdi_error_count;
            Exceed_error = ((ONE << Page_num ) | Exceed_error);
        }

        /* Check exceed_font*/
        /*hdudispfpdicheck-CheckExceedParam-DB-LLR-004*/
        if (!CheckFont(Exceed_data[loop_exceedcnt].exceed_font) &&
            (Pdi_error_count < MAX_ERROR_MSG))
        {
            /* Frame the Error Message*/
            BuildErrorMsg(element, bitstring, "EXCEED_FONT", Error_msg_string[Pdi_error_count]);

            /* Increment the PDI Error Index*/
            ++Pdi_error_count;
            Exceed_error = ((ONE << Page_num ) | Exceed_error);
        }

    /* Check exceed_axis*/
        /*hdudispfpdicheck-CheckExceedParam-DB-LLR-003*/
        if ((!CheckAxisMinMax(Exceed_data[loop_exceedcnt].exceed_axis.u16_x, ZERO, PANEL_HEIGHT,
        		PANEL_WIDTH)||
             !CheckAxisMinMax(Exceed_data[loop_exceedcnt].exceed_axis.u16_y, ZERO, PANEL_WIDTH,
            		 PANEL_HEIGHT))&&
             (Pdi_error_count < MAX_ERROR_MSG))
        {
            /* Frame the Error Message*/
            BuildErrorMsg(element, bitstring, "EXCEED_AXIS", Error_msg_string[Pdi_error_count]);

            /* Increment the PDI Error Index*/
            ++Pdi_error_count;
            Exceed_error = ((ONE << Page_num ) | Exceed_error);
        }

        /* Check exceed_axis*/
        /*hdudispfpdicheck-CheckExceedParam-DB-LLR-006*/
	    string_width= (T_UINT16)(FontsGetStringWidth((T_UINT8 *)letter_e, \
		Exceed_data[loop_exceedcnt].exceed_font));
        string_height=(T_UINT16)(FontsGetFontHeight(Exceed_data[loop_exceedcnt].exceed_font));
        if (ONE == (string_width & 1))
        {
       	 string_width = (T_UINT16)(string_width + 1);
        }
        else
        {
        	;
        }

        if (((!CheckAxisMinMax((Exceed_data[loop_exceedcnt].exceed_axis.u16_x + string_width/2),
        		ZERO, PANEL_HEIGHT,PANEL_WIDTH))||
             (!CheckAxisMinMax((Exceed_data[loop_exceedcnt].exceed_axis.u16_x - string_width/2),
            	ZERO, PANEL_HEIGHT, PANEL_WIDTH))||
             (!CheckAxisMinMax((Exceed_data[loop_exceedcnt].exceed_axis.u16_y + string_height/2),
               ZERO, PANEL_WIDTH,PANEL_HEIGHT)) ||
             (!CheckAxisMinMax((Exceed_data[loop_exceedcnt].exceed_axis.u16_y - string_height/2),
               ZERO, PANEL_WIDTH, PANEL_HEIGHT)))&&
              (Pdi_error_count < MAX_ERROR_MSG))
                {
                    /* Frame the Error Message*/
                    BuildErrorMsg(element, bitstring, "EXCEED_AXIS",\
					Error_msg_string[Pdi_error_count]);

                    /* Increment the PDI Error Index*/
                    ++Pdi_error_count;
                    Exceed_error = ((ONE << Page_num ) | Exceed_error);
                }
    }
}

/*
 *
 * Function                : CheckExceedTimerSettings
 *
 * Description             : This function checks Exceed timer parameters
 *
 * Formal parameter(s)     : None
 *
 * Return Value            : None
 *
 * Assumption              : None
 *
 */
static void CheckExceedTimerSettings()
{
    T_CHAR element[13] = "EXCEED_TIMER";          /* Element type*/
    T_UINT16 loop_timercnt=ZERO;          /* Timer messages count required for loop*/
    T_UINT16 string_width = ZERO;
    T_UINT16 string_height = ZERO;
    T_CHAR timer_text[13] = "TOT 9:59:59";
    T_CHAR labelstring[5]={0};       /* Variable used to store label in string format*/
    /*hdudispfpdicheck-CheckExceedTimerSettings-DB-LLR-001*/
    for (loop_timercnt = ZERO; loop_timercnt < Timer_cnt; loop_timercnt++)
    {
        /* Converts the label as array of characters*/
	    OctToStringTrim(Page_settings.Timer_settings[loop_timercnt].timer_label,
		Label_size, labelstring);
        /* Check label*/
		/*hdudispfpdicheck-CheckExceedTimerSettings-DB-LLR-002*/
        if (!CheckMinMax(Page_settings.Timer_settings[loop_timercnt].timer_label, ONE, MAX_LABEL) &&
            (Pdi_error_count < MAX_ERROR_MSG))
        {
            /* Frame the Error Message*/
            BuildErrorMsg(element, labelstring, "LABEL", Error_msg_string[Pdi_error_count]);

            /* Increment the PDI Error Index*/
            ++Pdi_error_count;
            Ex_timer_error = ((ONE << Page_num ) | Ex_timer_error);
        }
        /*hdudispfpdicheck-CheckExceedTimerSettings-DB-LLR-003*/
		/* Check SDI */
		if ((TRUE == Config_data.eng_sdi)&& \
		(!CheckMinMax(Page_settings.Timer_settings[loop_timercnt].timer_sdi, ZERO , THREE))&&
         (Pdi_error_count < MAX_ERROR_MSG))
        {
            /*Frame the Error Message */
            BuildErrorMsg(element, labelstring, "SDI",
                        Error_msg_string[Pdi_error_count]);

            /* Increment the PDI Error Index */
            ++Pdi_error_count;
            Ex_timer_error = ((ONE << Page_num ) | Ex_timer_error);
        }
       /*hdudispfpdicheck-CheckExceedTimerSettings-DB-LLR-004*/
        /* Check timer_font*/
        if (!CheckFont(Page_settings.Timer_settings[loop_timercnt].timer_font) &&
            (Pdi_error_count < MAX_ERROR_MSG))
        {
            /* Frame the Error Message*/
            BuildErrorMsg(element, labelstring, "EXCEED_TIMER_FONT", \
            		Error_msg_string[Pdi_error_count]);

            /* Increment the PDI Error Index*/
            ++Pdi_error_count;
            Ex_timer_error = ((ONE << Page_num ) | Ex_timer_error);
        }
        /*hdudispfpdicheck-CheckExceedTimerSettings-DB-LLR-005*/
        /* Check timer_axis*/
        if(!CheckAxisMinMax(Page_settings.Timer_settings[loop_timercnt].timer_axis.u16_x,
        		ZERO,PANEL_HEIGHT,PANEL_WIDTH) ||
           (!CheckAxisMinMax(Page_settings.Timer_settings[loop_timercnt].timer_axis.u16_y,
        		   ZERO,PANEL_WIDTH,PANEL_HEIGHT) &&
             (Pdi_error_count < MAX_ERROR_MSG)))
        {
            /* Frame the Error Message*/
            BuildErrorMsg(element, labelstring, "EXCEED_TIMER_AXIS", \
            		Error_msg_string[Pdi_error_count]);

            /* Increment the PDI Error Index*/
            ++Pdi_error_count;
            Ex_timer_error = ((ONE << Page_num ) | Ex_timer_error);
        }
       /*hdudispfpdicheck-CheckExceedTimerSettings-DB-LLR-006*/
        /* Check timer_axis*/
	    string_width= (T_UINT16)(FontsGetStringWidth((T_UINT8 *)timer_text, \
	    		Page_settings.Timer_settings[loop_timercnt].timer_font));
        string_height=
           (T_UINT16)(FontsGetFontHeight(Page_settings.Timer_settings[loop_timercnt].timer_font));
        if (ONE == (string_width & 1))
        {
       	 string_width = (T_UINT16)(string_width + 1);
        }
        else
        {
        	;
        }

        if(((!CheckAxisMinMax((Page_settings.Timer_settings[loop_timercnt].
                timer_axis.u16_x + string_width),ZERO, PANEL_HEIGHT,PANEL_WIDTH))||
            (!CheckAxisMinMax((Page_settings.Timer_settings[loop_timercnt].
               timer_axis.u16_y + string_height),ZERO, PANEL_WIDTH,PANEL_HEIGHT)))&&
              (Pdi_error_count < MAX_ERROR_MSG))
                {
                    /* Frame the Error Message*/
                    BuildErrorMsg(element, labelstring, "EXCEED_TIMER_AXIS",\
					Error_msg_string[Pdi_error_count]);

                    /* Increment the PDI Error Index*/
                    ++Pdi_error_count;
                    Ex_timer_error = ((ONE << Page_num ) | Ex_timer_error);
                }
        /*hdudispfpdicheck-CheckExceedTimerSettings-DB-LLR-007*/
        /* Check timer_format*/
		if((!CheckMinMax(Page_settings.Timer_settings[loop_timercnt].timer_format,\
				SECONDS ,HOUR_MIN_SEC))
               && (Pdi_error_count < MAX_ERROR_MSG))
        {
            /*Frame the Error Message */
            BuildErrorMsg(element, labelstring, "EXCEED_TIMER_FORMAT",
                        Error_msg_string[Pdi_error_count]);

            /* Increment the PDI Error Index */
            ++Pdi_error_count;
            Ex_timer_error = ((ONE << Page_num ) | Ex_timer_error);
        }
    }
}

/*
 *
 * Function                : PdiDataCheck
 *
 * Description             : This function check for the Pdi parameters
 *
 * Formal parameter(s)     : None
 *
 * Return Value            : None
 *
 * Assumption              : None
 *
 */
void PdiDataCheck()
{
    T_UINT16 loop_i = ZERO;
    T_UINT16 error_count_temp = ZERO;
    T_UINT16 pdi_error_temp = ZERO;
    T_UINT16 loop_rdcnt = ZERO;
    T_UINT16 loop_cgcnt = ZERO;
    T_UINT16 var_j = ZERO;

    /* Check global parameters only once*/
    /*hdudispfpdicheck-PdiDataCheck-DB-LLR-001*/
    if(FALSE == Global_check)
    {
    	Global_check = TRUE;
        CheckConfig();
        CheckCASParameters();
        CheckA429Parameters();
        CheckElogTrig();
        CheckElogParam();
        CheckAcdtParams();
        CheckPoly();
        /* error_count_temp !=0 confirms error occurred in global parameters */
        error_count_temp = Pdi_error_count;

    }
    else
    {
        /*Check page parameters only once*/
        if (FALSE == Page_check[Page_num])
        {
        	Page_check[Page_num] = TRUE;
        	/*To Check if the Pdi error count was increased in that particular page*/
        	pdi_error_temp = Pdi_error_count;
            CheckPageSettings();
            CheckForegroundParameters();
            CheckCasLocationSett();
            CheckExceedParam();
            CheckExceedTimerSettings();
        }
        else
        {
		     /*hdudispfpdicheck-PdiDataCheck-DB-LLR-004*/
            for (loop_rdcnt=ONE;loop_rdcnt <= Rd_cnt;loop_rdcnt++)
            {
        			for (var_j = ZERO; var_j < Page_settings.Rd_settings[loop_rdcnt-ONE].rd_no_ptr; var_j++)
                    {
                        Ap_page0_dials[loop_rdcnt-ONE].rotAngle[var_j]=
                        CVT(Page_settings.Rd_settings[loop_rdcnt-ONE].rd_ptr_rot[var_j]);
                    }
        	}
            for (loop_cgcnt = ONE; loop_cgcnt <= Cg_cnt; loop_cgcnt++)
            {
        			for (var_j = ZERO; var_j < Page_settings.Cg_settings[loop_cgcnt-ONE].cg_no_ptr; var_j++)
                    {
        			            Ap_page2_carrot[loop_cgcnt-ONE].rotAngle[var_j]=
                                CVT(Page_settings.Cg_settings[loop_cgcnt-ONE].cg_ptr_rot[var_j]);
                    }
        	}

            return;
        }

    }

    /* Enable the bits for pdi error Msgs */
    if (Pdi_error_count != ZERO )
    {
        /*hdudispfpdicheck-PdiDataCheck-DB-LLR-002*/
        for (loop_i = ZERO; loop_i < Pdi_error_count; loop_i++)
        {
            U16_message_words[ONE] = U16_message_words[ONE] | (T_UINT16)(ONE << (SEVEN + loop_i));

        }

        /*hdudispfpdicheck-PdiDataCheck-DB-LLR-003*/
        /* To determine the error occurred in global Parameters or Page Parameters*/
        if (error_count_temp != ZERO)
        {
             Global_parameter_error = TRUE;
        }
        /*True only if Pdi error count was increased in that particular page*/
        else if (pdi_error_temp != Pdi_error_count)
        {
             Page_parameter_error[Page_num] = TRUE;
        }
        else
        {
        	;
        }
    }
}
