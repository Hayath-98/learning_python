/*
 ******************************************************************************
 * License Information  :  Howell Instruments, Inc.                           *
 *                         "Licensed Software" and "All rights reserved".     *
 ******************************************************************************
 *  File                : hdudispfrterror.c
 *
 *  Description         : This file provides Stub routine for run time errors.
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
 *  Author(s)           : Vinay H
 *
 *  Version History     :
 * <Version No.>     <Author>          <Date>         <Problem Report No.>
 *
 *      1.1          Vinay H         14-Sep-2017             100064
 *      1.2          Shilpa A R      09-Oct-2017             100064
 *      1.3          Shruthi M N     19-Oct-2017             100083
 *      1.4          Shruthi M N     30-Oct-2017             100104
 *      1.5          Rona B S        02-Jul-2020             100259
 *      1.6          Dhanalakshmi    12-Sep-2020             100276 
 *
 * Additional References : None
 *
 ******************************************************************************
 */

#include "hdudispfrterror.h"       /*provides stub routine for run time errors.*/
#include "hdulibbasictypes.h"  /*provides basic data types.*/
#include "hdudispfbinascii.h"  /*provides basic data types.*/
#include "hdudispffonts.h"  /*Contains different font information*/
#include "hdudispfconfig.h"  /* contains page and color config information */
#include "hdudispftext.h"       /* Routines which maintain text display and updates */
#include "hdudispfwdog.h"            /* Watch dog timer declarations */
#include "hdudispfpanel.h"     /* Contains functions prototypes of panel.*/
#include "hdudispfforeground.h" /* contains the routines for foreground layer of the display */

#define SDRAM_BASE 0xC0000000
#define M_TWENTY 20
#define M_TWENTY_FIVE 25
#define M_SEVENTY_FIVE 75
#define M_HUNDRED_TEN 110
#define M_ONEHUNDRED_TWENTY_FIVE 125

static T_CHAR  Ascii_num[9] = {ZERO};
/**********************************************************************************/
/*                           Function Definition                                  */
/**********************************************************************************/

/*
 *
 * Function                : RterrWidget
 *
 * Description             : This function goes to infinite loop when an error occurs.
 *
 * Formal parameter(s)     : T_CHAR *pc_file -IN Specifies the file
 *                           T_INT32 s32_line_number  -IN Specifies the line no
 *                           T_CHAR *pc_message -IN Message
 *
 * Return Value            : None
 *
 * Assumption              : None
 *
 */

void RterrWidget(T_CHAR *pc_file, T_INT32 s32_line_number, T_CHAR *pc_message)
{
   static T_CHAR breakline[] = "\r\n";
   static T_CHAR param_message1[] = "\r\nFile: ";
   static T_CHAR param_message2[] = "\r\nLine #:";
   static T_CHAR param_message3[] = "\r\nHalted!!!";
   T_UINT32 u32_cntr = 0;
   T_UINT32 *pu32_dest = NULL;

   /*hdudispfrterror-RterrWidget-DB-LLR-001*/
   LCDBackgroundOn();
   /* Clear video RAM */
   for (u32_cntr = ZERO, pu32_dest = (T_UINT32 *) SDRAM_BASE; u32_cntr < (T_UINT32)FG_FB_SIZE*FOUR;
           u32_cntr++, pu32_dest++)
   {
       *pu32_dest = ZERO;
   }
   BinasByteFormatInfo(&s32_line_number, FOURB+FOURW, (T_INT8*)Ascii_num);
   /*hdudispfrterror-RterrWidget-DB-LLR-003*/
   TextDispString((T_INT8 *)&breakline,M_TWENTY,ZERO,E_SMALL_FONT,RED,TX_NO_FLASH,\
				V_NORMAL,ALIGN_LEFT);
   TextDispString((T_INT8 *)pc_message,M_TWENTY,M_TWENTY_FIVE,E_SMALL_FONT,RED,TX_NO_FLASH,\
				 V_NORMAL,ALIGN_LEFT);
   TextDispString((T_INT8 *)&param_message1,M_TWENTY,M_TWENTY_FIVE,E_SMALL_FONT,RED,TX_NO_FLASH,
                 V_NORMAL,ALIGN_LEFT);
   TextDispString((T_INT8 *)pc_file,M_TWENTY,M_SEVENTY_FIVE,E_SMALL_FONT,RED,TX_NO_FLASH,\
				V_NORMAL,ALIGN_LEFT);
   TextDispString((T_INT8 *)&param_message2,M_TWENTY,M_SEVENTY_FIVE,E_SMALL_FONT,RED,
		   TX_NO_FLASH,V_NORMAL,ALIGN_LEFT);
   TextDispString((T_INT8 *)Ascii_num,M_HUNDRED_TEN,ONE_HUNDRED,E_SMALL_FONT,RED,TX_NO_FLASH,\
				V_NORMAL,ALIGN_LEFT);
   TextDispString((T_INT8 *)&breakline,M_TWENTY,ONE_HUNDRED,E_SMALL_FONT,RED,TX_NO_FLASH,\
				V_NORMAL,ALIGN_LEFT);
   TextDispString((T_INT8 *)&param_message3,M_TWENTY,M_ONEHUNDRED_TWENTY_FIVE,E_SMALL_FONT,
                 RED,TX_NO_FLASH,V_NORMAL,ALIGN_LEFT);
   ForegroundReDraw1();
   /*hdudispfrterror-RterrWidget-DB-LLR-002*/
   while(ONE)
   {
     ;/* Do nothing */
   }
}
