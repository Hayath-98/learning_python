/*
 ******************************************************************************
 * License Information  :  Howell Instruments, Inc.                           *
 *                         "Licensed Software" and "All rights reserved".     *
 ******************************************************************************
 *  File                : hdudispftimers.c
 *
 *  Description         : This file processes exceedance timers.
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
 *      1.1           Dhanalakshmi     20-Mar-2021             100331
 *      1.2           Dhanalakshmi     20-Mar-2021             100331
 *      1.3           Dhanalakshmi     03-Apr-2021             100330
 *      1.4           Dhanalakshmi     16-Apr-2021             100339
 *      1.5           Dhanalakshmi     24-Apr-2021             100344
 *      1.6           Dhanalakshmi     13-May-2021             100350
 *
 * Additional References : None
 *
 *****************************************************************************
 */

#include "hdudispftimers.h"  /* Contains functions for exceedance timers */
#include "hdudispfgrapp.h"           /* routines for all graph */
#include "hdudispfbinascii.h"     /*Utility routines to convert binary to ascii base 10.*/
#include "hdudispfpdidata.h" /* provides pdi declarations */
#include "hdudispfrterror.h"           /* Provides sub routine for run time errors.*/

T_TIMER_PARAM_STRUCT Exceed_timer_params[MAX_EXCEED_TIMERS] =\
   {{0,0, FALSE, FALSE, 0U, 0U, 0U, 0U, 0U},\
	{0,0, FALSE, FALSE, 0U, 0U, 0U, 0U, 0U},\
	{0,0, FALSE, FALSE, 0U, 0U, 0U, 0U, 0U},\
	{0,0, FALSE, FALSE, 0U, 0U, 0U, 0U, 0U},\
	{0,0, FALSE, FALSE, 0U, 0U, 0U, 0U, 0U},\
	{0,0, FALSE, FALSE, 0U, 0U, 0U, 0U, 0U},\
	{0,0, FALSE, FALSE, 0U, 0U, 0U, 0U, 0U},\
	{0,0, FALSE, FALSE, 0U, 0U, 0U, 0U, 0U}};

T_UINT16 Timer_a429_tag[MAX_EXCEED_TIMERS]={0};

static T_EPENCOLOR FindTimerColor(T_UINT8 color);
static void FindTimerParam(T_UINT8 value, T_CHAR * param);

/*
 *
 * Function                : FindTimerColor
 *
 * Description             : This function decodes the timer color sent from DAU
 *
 * Formal parameter(s)     : T_UINT16 color - IN color sent from DAU
 *
 * Return Value            : T_EPENCOLOR - color returned
 *
 * Assumption              : None
 *
 */

static T_EPENCOLOR FindTimerColor(T_UINT8 color)
{
   T_EPENCOLOR ret_val=WHITE;

   switch(color)
   {
     /*hdudispftimers-FindTimerColor-DB-LLR-001*/
     case 1:
      ret_val=YELLOW;
      break;

      /*hdudispftimers-FindTimerColor-DB-LLR-002*/
     case 2:
      ret_val=RED;
      break;

    /* hdudispftimers-FindTimerColor-DB-LLR-003*/
    default:
	  ret_val=INVALID_COLOR;
      break;
    }
   return ret_val;
}

/*
 *
 * Function                : FindTimerParam
 *
 * Description             : This function decodes the parameter sent from DAU
 *
 * Formal parameter(s)     : T_CHAR * value - OUT Timer parameter
 *
 * Return Value            : None
 *
 * Assumption              : None
 *
 */

static void FindTimerParam(T_UINT8 value, T_CHAR * param)
{
   switch(value)
   {

   /*hdudispftimers-FindTimerParam-DB-LLR-001*/
   case 1:
      MemCpy(param, "N1 ", 4);
      break;

   /*hdudispftimers-FindTimerParam-DB-LLR-002*/
   case 2:
	   MemCpy(param, "TOT", 4);
       break;

   /*hdudispftimers-FindTimerParam-DB-LLR-003*/
   case 3:
       MemCpy(param, "TRQ", 4);
       break;

   /*hdudispftimers-FindTimerParam-DB-LLR-004*/
  default :
	  MemCpy(param, "XXX", 4);
      break;
   }
}

/*
 * Function                :  AppExTimerDraw
 *
 * Description             :  This function checks for timer condition and
 *                            displays exceedance timer
 *
 * Formal parameter(s)     :  None
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */
void AppExTimerDraw( void)
{
   T_CHAR file_name2[] = __FILE__;
   T_CHAR exceed_tmr_msg[] = "Too many Exceed Timers";
   static T_EPENCOLOR color = 1; /* yellow */
   static T_UINT8 u8_param = 0;
   T_CHAR *timer_string = NULL;
   T_CHAR colon = ':';
   T_UINT32 u32_time =0;
   T_UINT32 u32_seconds =0;
   T_UINT32 u32_minutes =0;
   T_UINT32 u32_hours = 0;
   T_UINT8 tmr_index=0;
   T_UINT8 tmr_index_1 = 0;

   /*hdudispftimers-AppExTimerDraw-DB-LLR-001*/
   /* If Exceed timer is not configured, return from the function */
   if(ZERO== (T_UINT16)Timer_cnt)
   {
	   return;
   }

        /*hdudispftimers-AppExTimerDraw-DB-LLR-002*/
		if((T_UINT16)MAX_EXCEED_TIMERS < (T_UINT16)Timer_cnt)
	   {
	      RterrWidget((T_CHAR *)&file_name2, __LINE__, &exceed_tmr_msg[0]);
	   }
	   else
	   {
		   ; /* Does Nothing */
	   }
    for(tmr_index_1=0; tmr_index_1< Timer_cnt; tmr_index_1++)
	{
	   for(tmr_index=0; tmr_index< Timer_cnt; tmr_index++)
	   {
		   if((Exceed_timer_params[tmr_index_1].timer_a249_label ==
			  Page_settings.Timer_settings[tmr_index].timer_label) &&
			 (Exceed_timer_params[tmr_index_1].timer_a429_sdi ==
			  Page_settings.Timer_settings[tmr_index].timer_sdi))
		   {
			         /* hdudispftimers-AppExTimerDraw-DB-LLR-003 */
			         /* label 240 id-1 contains exceeded parameter and color information */
			         if (TRUE == Exceed_timer_params[tmr_index_1].timer_data_flag)
			         {
			          u8_param = Exceed_timer_params[tmr_index_1].timer_param;
			          color = FindTimerColor(Exceed_timer_params[tmr_index_1].timer_color);
			      	   /* finds the exceeded parameter sent from DAU */
			   	      FindTimerParam(u8_param,&Timer_message[0]);
			         }
			         else
			         {
			        	 ; /* Does nothing */
			         }
			         /*hdudispftimers-AppExTimerDraw-DB-LLR-004 */
			         /* label 240 id-2 contains time in seconds */
			         if  (TRUE == Exceed_timer_params[tmr_index_1].timer_sec_flag)
			         {
			       	  u32_time = (T_UINT32) Exceed_timer_params[tmr_index_1].timer_seconds;
			         }
			         else
			         {
			        	 ; /* Does nothing */
			         }
			         /*hdudispftimers-AppExTimerDraw-DB-LLR-005 */
			         /* label 240 id-0 indicates exceedance timer should stop displaying */
			         if ((ZERO == Exceed_timer_params[tmr_index_1].timer_id) &&
			       		  (FALSE == Exceed_timer_params[tmr_index_1].timer_data_flag) &&
			   			  (FALSE == Exceed_timer_params[tmr_index_1].timer_sec_flag))
			         {
			      	   return;
			         }
			         else
			         {
			        	 ; /* Does nothing */
			         }

			         /* hdudispftimers-AppExTimerDraw-DB-LLR-006 */
			         if((TRUE == Exceed_timer_params[tmr_index_1].timer_data_flag) &&
			       	 (TRUE == Exceed_timer_params[tmr_index_1].timer_sec_flag))
			         {
			       	  /* Display XXXX when color or parameter or SSM is invalid */
			             if((INVALID_COLOR == color) || ((ONE != u8_param) &&
			                (TWO != u8_param) && (THREE != u8_param)) ||
			   			 (PARAM_OK != Parameters[Timer_a429_tag[tmr_index_1]].reading.stat))
			             {
			           	  MemCpy(&Timer_message[0], "  XXXX  ", 9);
			                TextDispString((T_INT8*)Timer_message,
			          	     Page_settings.Timer_settings[tmr_index].timer_axis.u16_x,
			          	     Page_settings.Timer_settings[tmr_index].timer_axis.u16_y,
			          	     Page_settings.Timer_settings[tmr_index].timer_font,
			         		 RED, TX_NO_FLASH, V_NORMAL, ALIGN_LEFT);
			                break;
			             }
			             else
			             {
			           	  ; /* Does nothing */
			             }
			       /* hdudispftimers-AppExTimerDraw-DB-LLR-007 */
			   	   Timer_message[3] = ' ';
			   	   u32_hours = u32_time / (SEC_PER_MIN * MIN_PER_HOUR);
			   	   u32_minutes = u32_time / SEC_PER_MIN;

			   	   u32_seconds = u32_time % SEC_PER_MIN;


			   	   /* hdudispftimers-AppExTimerDraw-DB-LLR-008 */
			   	   /* Exceed timer displays exceeded parameter and time in seconds format */
			   	   if(SECONDS == Page_settings.Timer_settings[tmr_index].timer_format )
			   	   {
			   	   	   timer_string = (T_CHAR *)BinasByteFormatInfo (&u32_time, FOURB+FIVEW+UNSIGNED+NOLZB,
			   	   			(T_INT8 *)&Timer_message[4]);
			   	   }
			   	   /* hdudispftimers-AppExTimerDraw-DB-LLR-009 */
			   	   /* Exceed timer displays exceeded parameter and time in minutes:seconds format */
			   	   else if(MIN_SEC == Page_settings.Timer_settings[tmr_index].timer_format )
			   	   {
			   	   	   if(u32_minutes > 99)
			   	   	   {
			   	   	   timer_string = (T_CHAR *)BinasByteFormatInfo (&u32_minutes, 
			   	   	               FOURB+THREEW+UNSIGNED+NOLZB,(T_INT8 *)&Timer_message[4]);

			   	   	   *(timer_string++) = colon;

			   	   	   timer_string = (T_CHAR *)BinasByteFormatInfo (&u32_seconds, FOURB+TWOW+UNSIGNED+NOLZB,
			   	   	                                    (T_INT8 *)timer_string);
			   	   	   }
			   	   	   else
			   	   	   {
				   	   	   timer_string = (T_CHAR *)BinasByteFormatInfo (&u32_minutes,
				   	   	               FOURB+TWOW+UNSIGNED+NOLZB,(T_INT8 *)&Timer_message[4]);

				   	   	   *(timer_string++) = colon;

				   	   	   timer_string = (T_CHAR *)BinasByteFormatInfo (&u32_seconds, \
				   	   		FOURB+TWOW+UNSIGNED+NOLZB, (T_INT8 *)timer_string);
			   	   	   }
			   	   }
			       /* hdudispftimers-AppExTimerDraw-DB-LLR-010 */
			   	   /* Exceed timer displays exceeded parameter and time in hours:minutes:seconds format */
			   	   else if(HOUR_MIN_SEC == Page_settings.Timer_settings[tmr_index].timer_format )
			   	   {
			   		u32_minutes %= MIN_PER_HOUR;
			   	   	   if(u32_hours > 0)
			   	   	   {
			   	   	      timer_string =
			                  (T_CHAR *)BinasByteFormatInfo (&u32_hours, ONEB+ONEW+UNSIGNED+NOLZB,
							  (T_INT8 *)&Timer_message[4]);

			   	   	      *(timer_string++) = colon;

			   		   	   timer_string = (T_CHAR *)BinasByteFormatInfo (&u32_minutes,
						   FOURB+TWOW+UNSIGNED+NOLZB,(T_INT8 *)&Timer_message[6]);

			   		   	   *(timer_string++) = colon;

			   		   	   timer_string = (T_CHAR *)BinasByteFormatInfo (&u32_seconds,
			   		   	                  FOURB+TWOW+UNSIGNED+NOLZB,(T_INT8 *)timer_string);
			   	   	   }
			   	     	/* hdudispftimers-AppExTimerDraw-DB-LLR-011 */
			   	   	   else
			   	   	   {
			   		   	   timer_string = (T_CHAR *)BinasByteFormatInfo (&u32_minutes,
			   		   	                   FOURB+TWOW+UNSIGNED+NOLZB,(T_INT8 *)&Timer_message[4]);

			   		   	   *(timer_string++) = colon;

			   		   	   timer_string = (T_CHAR *)BinasByteFormatInfo (&u32_seconds,
			   		   	                  FOURB+TWOW+UNSIGNED+NOLZB,(T_INT8 *)timer_string);
			   	   	   }

			   	   }
			   	   else
			   	   {
			   	      ; /* Does nothing */
			   	   }

			   	   if(ONE == Exceed_timer_params[tmr_index_1].timer_flash)
			   	   {
			   	     /* hdudispftimers-AppExTimerDraw-DB-LLR-012 */
			         /* Displays the exceed timer with axis and font configured in the PDI */
			         TextDispString((T_INT8*)Timer_message,
			   	     Page_settings.Timer_settings[tmr_index].timer_axis.u16_x,
			   	     Page_settings.Timer_settings[tmr_index].timer_axis.u16_y,
			   	     Page_settings.Timer_settings[tmr_index].timer_font,
			   	     color, TX_FLASH, V_REVERSE, ALIGN_LEFT);
			   	   }
			   	   else
			   	   {
			   		 /* Displays the exceed timer with axis and font configured in the PDI */
			   		  TextDispString((T_INT8*)Timer_message,
			   		  Page_settings.Timer_settings[tmr_index].timer_axis.u16_x,
			   		  Page_settings.Timer_settings[tmr_index].timer_axis.u16_y,
			   		  Page_settings.Timer_settings[tmr_index].timer_font,
			   		  color, TX_NO_FLASH, V_REVERSE, ALIGN_LEFT);
			   	   }
			      }
			      else
			      {
			         ; /* Does nothing */
			      }

		   }
		   else
		   {
			   ; /* Does nothing */
		   }
	   }
	}
}
