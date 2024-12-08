/*
 ******************************************************************************
 * License Information  :  Howell Instruments, Inc.                           *
 *                         "Licensed Software" and "All rights reserved".     *
 ******************************************************************************
 *  File                : hdudispbrterr.c
 *
 *  Description         : Sub routine for run time errors.
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
 *  Author(s)           : Ajay J G
 *
 *  Version History     :
 * <Version No.>     <Author>          <Date>         <Problem Report No.>
 *
 *      1.1          Ajay J G        02-Aug-2017             -
 *      1.2          Divya G P       01-Sep-2017          100028
 *      1.3          Rona B.S        04-Nov-2017          100156
 *      1.4          Vinay H         23-Mar-2018          100196
 *
 * Additional References : None
 *
 ******************************************************************************
 */
#include "hdudispbbinascii.h"            /* Contains functions prototypes of hdudispbbinascii.*/
#include "hdudispbpanel.h"               /* Contains functions prototypes of hdudispbpanel.*/
#include "hdudispbrterr.h"               /* Contains functions prototypes of hdudispbrterr*/
#include "hdudispbtext.h"                /* Contains functions prototypes of hdudispbtext.*/
#include "hdulibbasictypes.h"               /* Basic data types.*/

static T_CHAR  Ascii_num[9] = {ZERO};

/*
 * Function                :  RterrFunc
 *
 * Description             :  This function is used to display error message.
 *
 * Formal parameter(s)     :  T_UINT8 *ptr_file - IN Pointer to the file,
 *                            T_INT32 s32_line_number - IN Line Number,
 *                            T_UINT8 *ptr_message - IN Pointer to the message
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */
void RterrFunc(T_UINT8 *ptr_file, T_INT32 s32_line_number, T_UINT8 *ptr_message)
{
   static T_CHAR breakline[] = "\r\n";
   static T_CHAR param_message1[] = "\r\nFile: ";
   static T_CHAR param_message2[] = "\r\nLine #:";
   static T_CHAR param_message3[] = "\r\nHalted!!!";

   /*hdudispbrterr-RterrFunc-DB-LLR-001*/
   BspLcdSetPenColor(RED_BPC);

   /*hdudispbrterr-RterrFunc-DB-LLR-002*/
   BinAscii(&s32_line_number, FOURB+FOURW, Ascii_num);

   /*hdudispbrterr-RterrFunc-DB-LLR-003*/
   TextPrintString((T_UINT8 *)&breakline);
   TextPrintString((T_UINT8 *)ptr_message);
   TextPrintString((T_UINT8 *)&param_message1);
   TextPrintString((T_UINT8 *)ptr_file);
   TextPrintString((T_UINT8 *)&param_message2);
   TextPrintString((T_UINT8 *)Ascii_num);
   TextPrintString((T_UINT8 *)&breakline);
   TextPrintString((T_UINT8 *)&param_message3);
   while(ONE)
   {
      ;/* Does nothing */
   }
}
