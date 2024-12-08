/*
 ******************************************************************************
 * License Information  :  Howell Instruments, Inc.                           *
 *                         "Licensed Software" and "All rights reserved".     *
 ******************************************************************************
 *  File                : hdudispftextbox.c
 *
 *  Description         : The file contains routines for text box draw and updates
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
 *      1.2          Shilpa A R      10-Oct-2017             100064
 *      1.3          Rona B.S        11-Oct-2017             100064
 *      1.4          Shruthi M N     15-Oct-2017             100083
 *      1.5          Shruthi M N     30-Oct-2017             100104
 *      1.6          Rona B S        04-Nov-2017             100156
 *      1.7          Gururaj C       21-Jun-2020             100259
 *      1.8          Rona B S        02-Jul-2020             100259
 *      1.9          Dhanalakshmi    05-Aug-2020             100270 
 *      1.10         Dhanalakshmi    12-Sep-2020             100276 
 *      1.11         Dhanalakshmi    28-Sep-2020             100284 
 *      1.12         Dhanalakshmi    20-Mar-2021             100331  
 *
 * Additional References : None
 *
 ******************************************************************************
 */

#include "hdudispffonts.h"     /*Contains different font information*/
#include "hdudispfpolygon1.h"   /*provides routines for "scan line" method polygon fill.*/
#include "hdudispftext.h"      /* Routines which maintain text display and updates */
#include "hdudispftextbox.h"   /* routines for text box draw and updates */
#include "hdudispfconfig.h"    /* contains page and color config information */
#include "hdulibbasictypes.h" /* Contains different font information */
#include "hdudispfbfcfont.h"  /* BitFontCreator (Pro & Grayscale) font header */
#include "hdudispfpdidata.h"  /* contains pdidata information */
#include "hdudispfgrapp.h"    /* Routines for exceedence,CDT,rounddails,timers,bar graphs */
#include "hdudispfrterror.h"       /*provides stub routine for run time errors.*/

#define MAX_TEXT_BOXES           50U
#define BB_FONT GUI_FontConsolas 20U
#define BB_OUTSIDE_MARGIN        10U
#define  BB_INSIDE_MARGIN        4U
#define BB_END_MARGIN            6U
#define CARRIAGE_RTN             0x0dU
#define LINE_FEED                0x0aU

T_CHAR Pc_more_below[] = "\x13"" MORE ""\x13";
static T_UINT16   U16_next_box = 0;                      /* Next text box to allocate. */
static T_UINT16   U16_next_textbox = 0; /* Next text box to allocate from PDI */
static T_STEXTBOX S_text_boxes[MAX_TEXT_BOXES] = {0};     /* "Pool" of text boxes */
static T_STEXTBOXPDI S_pditext_boxes[MAX_TEXT_BOXES] = {0};     /* "Pool" of text boxes. */
extern T_INT8 S8_had_flash;
extern T_ETXFS Flash_state;

/*Static functions*/
static void TBDisplayString(T_CHAR *pc_text, T_STEXTBOX *ps_tb, T_EPENCOLOR e_color);

static void LBPrint(T_CHAR **pc_text_list, T_STEXTBOX *ps_tb, T_STEXTBOXDATA *ps_tbd,
                                             T_EPENCOLOR e_color);
static T_BOOL LBPrintMore(T_CHAR **pc_text_list, T_STEXTBOX *ps_tb, T_STEXTBOXDATA *ps_tbd);
static void TBPrint(T_CHAR *pc_text, T_STEXTBOX *ps_tb, T_STEXTBOXDATA *ps_tbd,
                                                            T_EPENCOLOR e_color);

static void TBDisplayStringPDI(T_CHAR *pc_text,  T_STEXTBOXPDI *ps_tb,\
              T_EPENCOLOR e_color,T_UINT16 alignment);


static void TBPrintPDI(T_CHAR *pc_text, T_STEXTBOXPDI *ps_tb, T_STEXTBOXPDIDATA *ps_tbd, \
						T_EPENCOLOR e_color);
/*
 *
 * Function                : StrLen
 *
 * Description             : The function returns the length of the string.
 *
 * Formal parameter(s)     : T_CHAR *str - IN string to which length has be calculated.
 *
 * Return Value            : T_UINT16 - length of the string
 *
 * Assumption              : None
 *
 */
T_UINT16 StrLen( T_CHAR *str)
{

   T_UINT16 count = 0;
   T_UINT16 index = 0;

   /*hdudispftextbox-StrLen-DB-LLR-001*/
   for (index = 0 ; str[index] != '\0'; index++)
   {
      count = (T_UINT16)(count + ONE);
   }

   return count;
}

/*
 *
 * Function                : TextBoxInit
 *
 * Description             : The function initializes the text box.
 *
 * Formal parameter(s)     : T_STEXTBOXDATA *ps_text_box_data - INOUT  - Pointer to
 *                            the text box structure
 *
 * Return Value            : None
 *
 * Assumption              : None
 *
 */
void TextBoxInit(T_STEXTBOXDATA *ps_text_box_data)
{

   T_BFC_FONT  *ps_font = 0;
 
   static T_CHAR param_message[] = "Too many Text Box.";
   T_CHAR file_name[] = __FILE__; 

   /*hdudispftextbox-TextBoxInit-DB-LLR-001*/
   /* Assume invalid data. */
   ps_text_box_data->psTextBox = (T_PSTEXTBOX)ZERO;

   /* Trap for bad box num. */
   if(U16_next_box >= MAX_TEXT_BOXES)
   {
      /*hdudispftextbox-TextBoxInit-DB-LLR-002*/
	    RterrWidget((T_CHAR *)&file_name,__LINE__, (T_CHAR *) &param_message);
      return;
   }
   else
   {
      ;/*Do nothing*/
   }
   /*hdudispftextbox-TextBoxInit-DB-LLR-003*/
   ps_font = (T_BFC_FONT *)FontsGetFont(ps_text_box_data->eTXFont);

   if ((T_BFC_FONT *)ZERO == ps_font)
   {
      /*hdudispftextbox-TextBoxInit-DB-LLR-004*/
      return;
   }
   else
   {
      ;/*Do nothing*/
   }

   /*hdudispftextbox-TextBoxInit-DB-LLR-005*/

   S_text_boxes[U16_next_box].psFont = ps_font;
   S_text_boxes[U16_next_box].s16FontHeight = FontsGetFontHeight(ps_text_box_data->eTXFont);
   S_text_boxes[U16_next_box].s16FontWidth = FontsGetCharWidth(ps_text_box_data->eTXFont, 'A');
   S_text_boxes[U16_next_box].pT_STEXTBOXDATA = ps_text_box_data;
   ps_text_box_data->psTextBox = &(S_text_boxes[U16_next_box]);

   if((TEXT_BOX == ps_text_box_data->eTBoxType)||(LIST_BOX == ps_text_box_data->eTBoxType)||
       (SELECT_BOX == ps_text_box_data->eTBoxType))
   {
       /*hdudispftextbox-TextBoxInit-DB-LLR-006*/
         S_text_boxes[U16_next_box].s16LeftMargin = ps_text_box_data->s16Margin;
         S_text_boxes[U16_next_box].s16RightMargin = ps_text_box_data->s16Margin;
         S_text_boxes[U16_next_box].s16ToptMargin = ps_text_box_data->s16Margin;
         S_text_boxes[U16_next_box].s16BottomMargin = ps_text_box_data->s16Margin;
   }
   else if(BB_RIGHT == ps_text_box_data->eTBoxType)
   {
       /*hdudispftextbox-TextBoxInit-DB-LLR-007*/
      S_text_boxes[U16_next_box].s16LeftMargin = ps_text_box_data->s16Margin;
      S_text_boxes[U16_next_box].s16RightMargin = ((T_INT16)ZERO);
      S_text_boxes[U16_next_box].s16ToptMargin = ((T_INT16)ZERO);
      S_text_boxes[U16_next_box].s16BottomMargin = ((T_INT16)ZERO);
   }
   else if(BB_BOTTOM == ps_text_box_data->eTBoxType)
   {
       /*hdudispftextbox-TextBoxInit-DB-LLR-008*/
      S_text_boxes[U16_next_box].s16LeftMargin = ((T_INT16)ZERO);
      S_text_boxes[U16_next_box].s16RightMargin = ((T_INT16)ZERO);
      S_text_boxes[U16_next_box].s16ToptMargin = ps_text_box_data->s16Margin;
      S_text_boxes[U16_next_box].s16BottomMargin = ((T_INT16)ZERO);
   }
   else if(BB_CENTER == ps_text_box_data->eTBoxType)
   {
       /*hdudispftextbox-TextBoxInit-DB-LLR-010*/
      S_text_boxes[U16_next_box].s16LeftMargin = THREE;
      S_text_boxes[U16_next_box].s16RightMargin = THREE;
      S_text_boxes[U16_next_box].s16ToptMargin = ps_text_box_data->s16Margin;
      S_text_boxes[U16_next_box].s16BottomMargin = ps_text_box_data->s16Margin;
   }
   else
   {
    ; /* Do nothing */
   }
   /*hdudispftextbox-TextBoxInit-DB-LLR-009*/
   S_text_boxes[U16_next_box].eState = OFF;
   S_text_boxes[U16_next_box].s16DrawX = ((T_INT16)ZERO);
   S_text_boxes[U16_next_box].s16DrawY = ((T_INT16)ZERO);
   S_text_boxes[U16_next_box].bFlashing = FALSE;

   ps_text_box_data->psTextBox = &(S_text_boxes[U16_next_box]);
   U16_next_box = (T_UINT16)(U16_next_box + ONE);
}

/*
 *
 * Function                : TextBoxPdiAllocate
 *
 * Description             : The function allocates the text box from PDI.
 *
 * Formal parameter(s)     : T_STEXTBOXDATA *ps_text_box_data - INOUT  - Pointer to
 *                            the text box structure
 *
 * Return Value            : None
 *
 * Assumption              : None
 *
 */
void TextBoxPdiAllocate(T_STEXTBOXPDIDATA *ps_text_box_data)
{

   T_BFC_FONT  *ps_tbfont = 0;
   static T_CHAR param_message[] = "Too many Text boxes";
   T_CHAR file_name[] = __FILE__;

   /*hdudispftextbox-TextBoxPdiAllocate-DB-LLR-001*/
   /* Assume invalid data. */
   ps_text_box_data->psTextBox = (T_PSTEXTBOXPDI)ZERO;

   /* Trap for bad box num. */
   if(Tb_cnt > MAX_TEXT_BOXES)
   {
      /*hdudispftextbox-TextBoxPdiAllocate-DB-LLR-002*/
	    RterrWidget((T_CHAR *)&file_name,__LINE__, (T_CHAR *) &param_message);
	    ps_text_box_data->psTextBox = (T_PSTEXTBOXPDI)ZERO;
      return;
   }
   else
   {
      ;/*Do nothing*/
   }
   /*hdudispftextbox-TextBoxPdiAllocate-DB-LLR-003*/
   ps_tbfont = (T_BFC_FONT *)FontsGetFont(ps_text_box_data->eTXFont);

   if ((T_BFC_FONT *)ZERO == ps_tbfont)
   {
      /*hdudispftextbox-TextBoxPdiAllocate-DB-LLR-004*/
      return;
   }
   else
   {
      ;/*Do nothing*/
   }

   /*hdudispftextbox-TextBoxPdiAllocate-DB-LLR-005*/

   S_pditext_boxes[U16_next_textbox].psFont = ps_tbfont;
   S_pditext_boxes[U16_next_textbox].s16FontHeight =
		   FontsGetFontHeight(ps_text_box_data->eTXFont);
   S_pditext_boxes[U16_next_textbox].s16FontWidth = FontsGetCharWidth
		                                            (ps_text_box_data->eTXFont, 'A');
   S_pditext_boxes[U16_next_textbox].pT_STEXTBOXPDIDATA = ps_text_box_data;
   ps_text_box_data->psTextBox = &(S_pditext_boxes[U16_next_textbox]);

   if((TEXT_BOX == ps_text_box_data->eTBoxType)||(LIST_BOX == ps_text_box_data->eTBoxType)||
       (SELECT_BOX == ps_text_box_data->eTBoxType))
   {
       /*hdudispftextbox-TextBoxPdiAllocate-DB-LLR-006*/
	   S_pditext_boxes[U16_next_textbox].s16LeftMargin = ps_text_box_data->s16Margin;
	   S_pditext_boxes[U16_next_textbox].s16RightMargin = ps_text_box_data->s16Margin;
	   S_pditext_boxes[U16_next_textbox].s16ToptMargin = ps_text_box_data->s16Margin;
	   S_pditext_boxes[U16_next_textbox].s16BottomMargin = ps_text_box_data->s16Margin;
   }
   else if(BB_RIGHT == ps_text_box_data->eTBoxType)
   {
       /*hdudispftextbox-TextBoxPdiAllocate-DB-LLR-007*/
	   S_pditext_boxes[U16_next_textbox].s16LeftMargin = ps_text_box_data->s16Margin;
	   S_pditext_boxes[U16_next_textbox].s16RightMargin = ((T_INT16)ZERO);
	   S_pditext_boxes[U16_next_textbox].s16ToptMargin = ((T_INT16)ZERO);
	   S_pditext_boxes[U16_next_textbox].s16BottomMargin = ((T_INT16)ZERO);
   }
   else if(BB_BOTTOM == ps_text_box_data->eTBoxType)
   {
       /*hdudispftextbox-TextBoxPdiAllocate-DB-LLR-008*/
	  S_pditext_boxes[U16_next_textbox].s16LeftMargin = ((T_INT16)ZERO);
      S_pditext_boxes[U16_next_textbox].s16RightMargin = ((T_INT16)ZERO);
      S_pditext_boxes[U16_next_textbox].s16ToptMargin = ps_text_box_data->s16Margin;
      S_pditext_boxes[U16_next_textbox].s16BottomMargin = ((T_INT16)ZERO);
   }
   else
   {
    ; /* Do nothing */
   }
   /*hdudispftextbox-TextBoxPdiAllocate-DB-LLR-009*/
   if((T_UINT16)TXT_STATE_REVERSE == Page_settings.Tb_settings[U16_next_textbox].tb_state)

   {
	   S_pditext_boxes[U16_next_textbox].eState = ON;
   }
   else if((T_UINT16) TXT_STATE_NORMAL == Page_settings.Tb_settings[U16_next_textbox].tb_state)
   {
	   S_pditext_boxes[U16_next_textbox].eState = OFF;
   }
   else
   {
	   S_pditext_boxes[U16_next_textbox].eState = OFF;
   }

   if((T_UINT16)TEXT_FLASH_ON == Page_settings.Tb_settings[U16_next_textbox].tb_flash)
   {
	   S_pditext_boxes[U16_next_textbox].bFlashing = TRUE;
   }
   else if((T_UINT16)TEXT_FLASH_OFF == Page_settings.Tb_settings[U16_next_textbox].tb_flash)
   {
	   S_pditext_boxes[U16_next_textbox].bFlashing = FALSE;
   }
   else
   {
	   S_pditext_boxes[U16_next_textbox].bFlashing = FALSE;
   }

   S_pditext_boxes[U16_next_textbox].s16DrawX = ((T_INT16)ZERO);
   S_pditext_boxes[U16_next_textbox].s16DrawY = ((T_INT16)ZERO);

   ps_text_box_data->psTextBox = &(S_pditext_boxes[U16_next_textbox]);
   U16_next_textbox = (T_UINT16)(U16_next_textbox + ONE);
}
/*
 *
 * Function                : TBPrint
 *
 * Description             : The function draws the text box.
 *
 * Formal parameter(s)     : T_CHAR *pc_text - INOPUT Text to be displayed in text box
 *                           T_STEXTBOX *ps_tb - OUT Text to be displayed in text box
 *                           T_STEXTBOXDATA *ps_tbd - IN Pointer to text box data parameters
 *                           T_EPENCOLOR e_color - IN Color of the text box
 *
 * Return Value            : None
 *
 * Assumption              : None
 *
 */
static void TBPrint(T_CHAR *pc_text, T_STEXTBOX *ps_tb, T_STEXTBOXDATA *ps_tbd, T_EPENCOLOR e_color)
{
   while(*pc_text != ZERO)
   {
      /* Carriage Return*/
      if(CARRIAGE_RTN == *pc_text)
      {
       /*hdudispftextbox-TBPrint-DB-LLR-001*/
         ps_tb->s16DrawX = ZERO;
      }
      /* Line Feed*/
      else if(LINE_FEED == *pc_text)
      {
         if((ps_tb->s16DrawY+ps_tb->psFont->FontHeight) < ps_tbd->s16PixHeight)
         {
         /*hdudispftextbox-TBPrint-DB-LLR-002*/
            ps_tb->s16DrawY = (T_INT16)(ps_tb->s16DrawY + ps_tb->psFont->FontHeight);
         }
         else
         {
           ; /* Do nothing */
         }
      }
      else
      {
         if(
               (ps_tb->s16DrawX <= (ps_tbd->s16PixWidth-ps_tb->s16FontWidth)) &&
               (ps_tb->s16DrawY <= (ps_tbd->s16PixHeight-ps_tb->s16FontHeight))
            )
            {
         /*hdudispftextbox-TBPrint-DB-LLR-003*/
               ps_tb->s16DrawX = (T_INT16)(ps_tb->s16DrawX + TextDrawChar((*pc_text),
                                 (T_UINT16)(ps_tbd->s16ULX+ps_tb->s16DrawX),
                                 (T_UINT16)(ps_tbd->s16ULY+ps_tb->s16DrawY),
                                  ps_tb->psFont, e_color));
            }
         else
         {
           ; /* Do nothing */
         }

         if(BB_RIGHT == ps_tbd->eTBoxType)
         {
         /*hdudispftextbox-TBPrint-DB-LLR-004*/
            ps_tb->s16DrawX = ZERO;

            if((ps_tb->s16DrawY+ps_tb->s16FontHeight) < ps_tbd->s16PixHeight)
            {
           /*hdudispftextbox-TBPrint-DB-LLR-005*/
              ps_tb->s16DrawY = (T_INT16)(ps_tb->s16DrawY + ps_tb->psFont->FontHeight);
            }
            else
            {
              ; /* Do nothing */
            }
         }
        else
        {
         ; /* Do nothing */
        }

      }
     /*hdudispftextbox-TBPrint-DB-LLR-006*/
      pc_text++;
   }
}

/*
 *
 * Function                : LBPrintMore
 *
 * Description             : The function checks the height of the textbox and text to be
 *                           displayed and displays the text.
 *
 * Formal parameter(s)     : T_CHAR **pc_text_list - IN Text that has to be displayed
 *                           T_STEXTBOX *ps_tb - INOUT Pointer to the structure T_STEXTBOX
 *                           T_STEXTBOXDATA *ps_tbd - IN Pointer to the structure T_STEXTBOXDATA
 *
 * Return Value            : None
 *
 * Assumption              : None
 *
 */
static T_BOOL LBPrintMore(T_CHAR **pc_text_list, T_STEXTBOX *ps_tb, T_STEXTBOXDATA *ps_tbd)
{
   T_CHAR  *pc_scanner = ZERO;
   T_BOOL   had_lf = FALSE;
   /*hdudispftextbox-LBPrintMore-DB-LLR-001*/
   pc_scanner = *((T_CHAR **)pc_text_list);

   had_lf = FALSE;

   while(ZERO != *pc_scanner)
   {
     /*hdudispftextbox-LBPrintMore-DB-LLR-002*/
      pc_scanner = pc_scanner + ONE;

      if('\n' == *pc_scanner )
      {
         /*hdudispftextbox-LBPrintMore-DB-LLR-003*/
         had_lf = TRUE;
      }
      else
      {
        ; /* Do nothing */
      }
   }

   /* If this is the last line */
   if((ps_tb->s16DrawY+ps_tb->psFont->FontHeight) >= ps_tbd->s16PixHeight)
   {
      if((had_lf) || *(T_CHAR **)(pc_text_list+1))
      {
       /*hdudispftextbox-LBPrintMore-DB-LLR-004*/
         ps_tb->s16DrawX = (T_INT16)(((T_INT16)ps_tbd->s16PixWidth - (StrLen(Pc_more_below) *
                           (T_INT16)ps_tb->s16FontWidth))/(T_INT16)TWO);

         if(ps_tb->s16DrawX < (T_INT16)ZERO)
         {
       /*hdudispftextbox-LBPrintMore-DB-LLR-005*/
            ps_tb->s16DrawX = ((T_INT16)ZERO);
         }
         else
         {
           ; /* Do nothing */
         }
       /*hdudispftextbox-LBPrintMore-DB-LLR-006*/
         TBPrint(Pc_more_below, ps_tb, ps_tbd, YELLOW);
         ps_tb->s16DrawX = ((T_INT16)ZERO);
         return(TRUE);
      }
	  else
      {
         ; /*Do nothing*/
      }
   }
    else
   {
      ; /*Do nothing*/
   }
   /*hdudispftextbox-LBPrintMore-DB-LLR-007*/
   return(FALSE);
}

/*
 *
 * Function                : LBPrint
 *
 * Description             : The function to display the stings of textboxes.
 *
 * Formal parameter(s)     : T_CHAR **pc_text_list - INOUT String that has to be displayed
 *                           T_STEXTBOX *ps_tb - OUT Pointer to the structure T_STEXTBOX
 *                           T_STEXTBOXDATA *ps_tbd - IN Pointer to structure T_STEXTBOXDATA
 *                           T_EPENCOLOR e_color - IN Color of the text to be displayed
 *
 * Return Value            : None
 *
 * Assumption              : None
 *
 */
static void LBPrint(T_CHAR **pc_text_list, T_STEXTBOX *ps_tb, T_STEXTBOXDATA *ps_tbd,
                                             T_EPENCOLOR e_color)
{
   T_CHAR *pc_text = *pc_text_list;

   if(ZERO != LBPrintMore(pc_text_list, ps_tb, ps_tbd))
   {
     /*hdudispftextbox-LBPrint-DB-LLR-001*/
      return;
   }
   else
   {
    ; /* Do nothing */
   }

   while(*pc_text != ZERO)
   {
      /* Carriage Return*/
      if(CARRIAGE_RTN == *pc_text)
      {
        /*hdudispftextbox-LBPrint-DB-LLR-002*/
         ps_tb->s16DrawX = ZERO;
      }
      /* Line Feed*/
      else if(LINE_FEED == *pc_text)
      {
         if((ps_tb->s16DrawY+ps_tb->psFont->FontHeight) < ps_tbd->s16PixHeight)
         {
        /*hdudispftextbox-LBPrint-DB-LLR-003*/
            ps_tb->s16DrawY = (T_INT16)(ps_tb->s16DrawY + ps_tb->psFont->FontHeight);

            if (FALSE != LBPrintMore(pc_text_list, ps_tb, ps_tbd))
            {
             /*hdudispftextbox-LBPrint-DB-LLR-004*/
               return;
            }
            else
            {
             ; /* Do nothing */
            }
         }
         else
         {
        /*hdudispftextbox-LBPrint-DB-LLR-005*/
            return;
         }
      }
      else
      {
         if(
               (ps_tb->s16DrawX <= (ps_tbd->s16PixWidth-ps_tb->s16FontWidth)) &&
               (ps_tb->s16DrawY <= (ps_tbd->s16PixHeight-ps_tb->s16FontHeight))
            )
           {
             /*hdudispftextbox-LBPrint-DB-LLR-006*/
                 ps_tb->s16DrawX = (T_INT16)(ps_tb->s16DrawX + TextDrawChar((*pc_text),
                 (T_UINT16)(ps_tbd->s16ULX+ps_tb->s16DrawX),
                 (T_UINT16)(ps_tbd->s16ULY+ps_tb->s16DrawY),
                  ps_tb->psFont, e_color));
           }
           else
           {
              ; /* Do nothing */
           }
      }
      /*hdudispftextbox-LBPrint-DB-LLR-007*/
      pc_text++;
   }
}

/*
 * Function                : TBDisplayString
 *
 * Description             : The function displays the string in  the text box.
 *
 * Formal parameter(s)     : T_CHAR *pc_text - INOUT Text to be displayed
 *                           T_STEXTBOX *ps_tb - INOUT Pointer to the structure T_STEXTBOX
 *                           T_EPENCOLOR e_color - IN Color to be displayed
 *
 * Return Value            : None
 *
 * Assumption              : None
 *
 */
static void TBDisplayString(T_CHAR *pc_text,  T_STEXTBOX *ps_tb, T_EPENCOLOR e_color)
{
   T_STEXTBOXDATA *ps_tbd = ZERO;
   T_UINT16 u16_cntr = ZERO;

   /*hdudispftextbox-TBDisplayString-DB-LLR-001*/
   ps_tbd   =  ps_tb->pT_STEXTBOXDATA;

   /* Apply title to List or Text Box. */
   if((LIST_BOX == ps_tbd->eTBoxType) || (SELECT_BOX == ps_tbd->eTBoxType))
   {
      if(ZERO != ps_tbd->pcTitle)
      {
         /*hdudispftextbox-TBDisplayString-DB-LLR-002*/
         ps_tb->s16DrawX = (T_INT16)((ps_tbd->s16PixWidth - (StrLen(ps_tbd->pcTitle) *
                           (T_INT16)ps_tb->s16FontWidth))/(T_INT16)TWO);

         /* Updated as per PR100083*/
         if(ps_tb->s16DrawX < ((T_INT16)ZERO))
         {
            /*hdudispftextbox-TBDisplayString-DB-LLR-003*/
            ps_tb->s16DrawX = ((T_INT16)ZERO);
         }
         else
         {
          ; /* Do nothing */
         }
         /*hdudispftextbox-TBDisplayString-DB-LLR-004*/
         TBPrint(ps_tbd->pcTitle, ps_tb, ps_tbd, e_color);
         ps_tb->s16DrawX = ((T_INT16)ZERO);

         if((ps_tb->s16DrawY+ps_tb->psFont->FontHeight) < ps_tbd->s16PixHeight)
         {
         /*hdudispftextbox-TBDisplayString-DB-LLR-005*/
            ps_tb->s16DrawY = (T_INT16)(ps_tb->s16DrawY + ps_tb->psFont->FontHeight);
            u16_cntr = (T_UINT16)((ps_tbd->s16PixWidth)/(ps_tb->s16FontWidth));

            while(u16_cntr != ZERO)
            {
            /*hdudispftextbox-TBDisplayString-DB-LLR-006*/
               ps_tb->s16DrawX = (T_INT16)(ps_tb->s16DrawX + TextDrawChar(BAR,
                                 (T_UINT16)(ps_tbd->s16ULX+ps_tb->s16DrawX),
                                 (T_UINT16)(ps_tbd->s16ULY+ps_tb->s16DrawY),
                                 ps_tb->psFont, e_color));
               u16_cntr--;
            }
         }
         else
         {
          ; /* Do nothing */
         }
         /*hdudispftextbox-TBDisplayString-DB-LLR-007*/
         ps_tb->s16DrawX = ((T_INT16)ZERO);

         if((ps_tb->s16DrawY+ps_tb->psFont->FontHeight) < ps_tbd->s16PixHeight)
         {
          /*hdudispftextbox-TBDisplayString-DB-LLR-008*/
            ps_tb->s16DrawY = (T_INT16)(ps_tb->s16DrawY + ps_tb->psFont->FontHeight);
         }
         else
         {
          ; /* Do nothing */
         }

      }
      else
      {
       ; /* Do nothing */
      }
   }
   else
   {
    ; /* Do nothing */
   }

   if(LIST_BOX == ps_tbd->eTBoxType)
   {
      while(*(((T_CHAR **)pc_text)))
      {
         /*hdudispftextbox-TBDisplayString-DB-LLR-009*/
         LBPrint((T_CHAR **)pc_text, ps_tb, ps_tbd, e_color);

         if((ps_tb->s16DrawY+ps_tb->psFont->FontHeight) <= ps_tbd->s16PixHeight)
         {
            /*hdudispftextbox-TBDisplayString-DB-LLR-010*/
            ps_tb->s16DrawY = (T_INT16)(ps_tb->s16DrawY + ps_tb->psFont->FontHeight);
         }
         else
         {
         /*hdudispftextbox-TBDisplayString-DB-LLR-011*/
            return;
         }
      /*hdudispftextbox-TBDisplayString-DB-LLR-012*/
         ps_tb->s16DrawX = ((T_INT16)ZERO);
         pc_text += FOUR;
      }
    /*hdudispftextbox-TBDisplayString-DB-LLR-013*/
      return;
   }
   else
   {
    ; /* Do nothing */
   }

   /* Center right bezel bottom text. */
   if(BB_RIGHT == ps_tbd->eTBoxType)
   {
     /*hdudispftextbox-TBDisplayString-DB-LLR-014*/
     ps_tb->s16DrawY = (T_INT16)((ps_tbd->s16PixHeight - (StrLen(pc_text) *
                                    (T_INT16)ps_tb->s16FontHeight))/((T_INT16)TWO));

      if(ps_tb->s16DrawY < ((T_INT16)ZERO))
      {
      /*hdudispftextbox-TBDisplayString-DB-LLR-015*/
         ps_tb->s16DrawY = ((T_INT16)ZERO);
      }
      else
      {
       ;
      }
   }
   else
   {
    ; /* Do nothing */
   }

   /* Center bottom bezel bottom text. */
   if(BB_BOTTOM == ps_tbd->eTBoxType)
   {
      /*hdudispftextbox-TBDisplayString-DB-LLR-016*/
      ps_tb->s16DrawX = (T_INT16)((ps_tbd->s16PixWidth - (StrLen(pc_text) *
                                 (T_INT16)ps_tb->s16FontWidth))/((T_INT16)TWO));
      /* Updated as per PR100083*/
      if(ps_tb->s16DrawX < ((T_INT16)ZERO))
      {
         /*hdudispftextbox-TBDisplayString-DB-LLR-017*/
         ps_tb->s16DrawX = ((T_INT16)ZERO);
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
   /*hdudispftextbox-TBDisplayString-DB-LLR-018*/
   TBPrint(pc_text, ps_tb, ps_tbd, e_color);
}

/*
 * Function                : TextBoxDraw
 *
 * Description             : The function draws the text box.
 *
 * Formal parameter(s)     : None
 *
 * Return Value            : None
 *
 * Assumption              : None
 *
 */
void TextBoxDraw(void)
{
   T_UINT16                   u16_ctr = 0;
   T_STEXTBOX                 *ps_tb = {0};
   T_STEXTBOXDATA             *ps_tbd = {0};
   T_CHAR                     *pc_fill_data = NULL;
   T_EPENCOLOR                e_color = BLACK;

   for(u16_ctr = 0; u16_ctr < U16_next_box; u16_ctr++)
   {
      if(ON == S_text_boxes[u16_ctr].eState)
      {
         /*hdudispftextbox-TextBoxDraw-DB-LLR-001*/
         ps_tb = &(S_text_boxes[u16_ctr]);

         ps_tbd = ps_tb->pT_STEXTBOXDATA;

         if(ps_tb->bFlashing != ZERO)
         {
            /*hdudispftextbox-TextBoxDraw-DB-LLR-002*/
            S8_had_flash = TRUE;

            if(FLASH_STATE_ON == Flash_state)
            {
               /*hdudispftextbox-TextBoxDraw-DB-LLR-003*/
               e_color = ps_tbd->eBackGroundColor;
            }
            else
            {
               /*hdudispftextbox-TextBoxDraw-DB-LLR-004*/
               e_color = ps_tbd->eFontColor;
            }
         }
         else
         {
            /*hdudispftextbox-TextBoxDraw-DB-LLR-005*/
            e_color = ps_tbd->eBackGroundColor;
         }

         /*hdudispftextbox-TextBoxDraw-DB-LLR-006*/
         PolygonFillRect((T_INT16)(ps_tbd->s16ULX-ps_tb->s16LeftMargin),
               (T_INT16)(ps_tbd->s16ULY-ps_tb->s16ToptMargin),
               (T_INT16)(ps_tbd->s16PixWidth+ps_tb->s16LeftMargin+ps_tb->s16RightMargin),
               (T_INT16)(ps_tbd->s16PixHeight+ps_tb->s16ToptMargin+ps_tb->s16BottomMargin),
               e_color);

         if(ps_tbd->s16FrameWidth != ((T_INT16)ZERO))
         {
            if((TEXT_BOX == ps_tbd->eTBoxType) || (LIST_BOX == ps_tbd->eTBoxType)
                               || (SELECT_BOX == ps_tbd->eTBoxType))
            {
              /*hdudispftextbox-TextBoxDraw-DB-LLR-007*/
               PolygonDrawFrame((T_INT16)(ps_tbd->s16ULX-ps_tb->s16LeftMargin),
                (T_INT16)(ps_tbd->s16ULY-ps_tb->s16ToptMargin),
                (T_INT16)(ps_tbd->s16PixWidth+ps_tb->s16LeftMargin+ps_tb->s16RightMargin),
                (T_INT16)(ps_tbd->s16PixHeight+ps_tb->s16ToptMargin+ps_tb->s16BottomMargin),
                ps_tbd->s16FrameWidth,ps_tbd->eFrameColor);
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
         if(ps_tbd->fill != ZERO)
         {
         /*hdudispftextbox-TextBoxDraw-DB-LLR-008*/
            pc_fill_data = ps_tbd->fill();

            if(ps_tb->bFlashing != ZERO)
            {
               if(FLASH_STATE_ON == Flash_state)
               {
              /*hdudispftextbox-TextBoxDraw-DB-LLR-009*/
                  e_color = ps_tbd->eFontColor;
               }
               else
               {
              /*hdudispftextbox-TextBoxDraw-DB-LLR-010*/
                  e_color = ps_tbd->eBackGroundColor;
               }
            }
            else
            {
               /*hdudispftextbox-TextBoxDraw-DB-LLR-011*/
               e_color = ps_tbd->eFontColor;
            }

            /*hdudispftextbox-TextBoxDraw-DB-LLR-012*/
            TBDisplayString(pc_fill_data, &(S_text_boxes[u16_ctr]), e_color);
         }
		 else
         {
             ; /*Do nothing*/
         }

         /*hdudispftextbox-TextBoxDraw-DB-LLR-013*/
         ps_tb->s16DrawX = ((T_INT16)ZERO);
         ps_tb->s16DrawY = ((T_INT16)ZERO);
      }
   }
}

/*
 * Function                : TextBoxOn
 *
 * Description             : The function enables the text box.
 *
 * Formal parameter(s)     : T_STEXTBOXDATA *ps_this_box - INOUT pointer to textbox structure
 *
 * Return Value            : None
 *
 * Assumption              : None
 *
 */
void TextBoxOn(T_STEXTBOXDATA *ps_this_box)
{
   if((0 == ps_this_box->psTextBox) || (ps_this_box->psTextBox >= &(S_text_boxes[MAX_TEXT_BOXES])))
   {
      /*hdudispftextbox-TextBoxOn-DB-LLR-001*/
      return;
   }
   else
   {
      ;/*Do nothing*/
   }
   /*hdudispftextbox-TextBoxOn-DB-LLR-002*/
   ps_this_box->psTextBox->eState = ON;
}

/*
 *
 * Function                : TextBoxOff
 *
 * Description             : The function disables the text box.
 *
 * Formal parameter(s)     : T_STEXTBOXDATA *ps_this_box - INOUT pointer to textbox structure
 *
 * Return Value            : None
 *
 * Assumption              : None
 *
 */
void TextBoxOff(T_STEXTBOXDATA *ps_this_box)
{
   if((0 == ps_this_box->psTextBox) || (ps_this_box->psTextBox >= &(S_text_boxes[MAX_TEXT_BOXES])))
   {
      /*hdudispftextbox-TextBoxOff-DB-LLR-001*/
      return;
   }
   else
   {
      ;/*Do nothing*/
   }
   /*hdudispftextbox-TextBoxOff-DB-LLR-002*/
   ps_this_box->psTextBox->eState = OFF;
}

/*
 *
 * Function                : TextBoxFlash
 *
 * Description             : The function enables Flashing of text box.
 *
 * Formal parameter(s)     : T_STEXTBOXDATA *ps_this_box - INOUT pointer to textbox structure
 *
 * Return Value            : None
 *
 * Assumption              : None
 *
 */
void TextBoxFlash(T_STEXTBOXDATA *ps_this_box)
{
   if((ZERO == ps_this_box->psTextBox) || (ps_this_box->psTextBox >=
                                 &(S_text_boxes[MAX_TEXT_BOXES])))
   {
      /*hdudispftextbox-TextBoxFlash-DB-LLR-001*/
      return;
   }
   else
   {
      ;/*Do nothing*/
   }
   /*hdudispftextbox-TextBoxFlash-DB-LLR-002*/
   ps_this_box->psTextBox->bFlashing = TRUE;
}

/*
 *
 * Function                : TextBoxNoFlash
 *
 * Description             : The function enables Flashing of text box.
 *
 * Formal parameter(s)     : T_STEXTBOXDATA *ps_this_box - INOUT pointer to textbox structure
 *
 * Return Value            : None
 *
 * Assumption              : None
 *
 */
void TextBoxNoFlash(T_STEXTBOXDATA *ps_this_box)
{
   if((ZERO == ps_this_box->psTextBox) || (ps_this_box->psTextBox >=
                                    &(S_text_boxes[MAX_TEXT_BOXES])))
   {
      /*hdudispftextbox-TextBoxNoFlash-DB-LLR-001*/
      return;
   }
   else
   {
      ;/*Do nothing*/
   }

   /*hdudispftextbox-TextBoxNoFlash-DB-LLR-002*/
   ps_this_box->psTextBox->bFlashing = FALSE;
}
/*
 * Function                : TextBoxClear
 *
 * Description             : The function De-allocate the TextBox.
 *
 * Formal parameter(s)     : T_STEXTBOXDATA *ps_this_box-INOUT Pointer to the text box structure.
 *
 * Return Value            : None
 *
 * Assumption              : None
 *
 */
void TextBoxClear(T_STEXTBOXPDIDATA *ps_this_box)
{
 while(U16_next_textbox)
 {
	 /* hdudispftextbox-TextBoxClear-DB-LLR-001 */
     ps_this_box[U16_next_textbox-ONE].psTextBox->psPolyRedX=(T_SPOLY *)NULL;
     U16_next_textbox = (T_UINT16)(U16_next_textbox - ONE);
  }
}


/*
 * Function                : TextBoxPdiDraw
 *
 * Description             : The function draws the TextBox in PDI.
 *
 * Formal parameter(s)     : None
 *
 * Return Value            : T_BOOLEAN flag
 *
 * Assumption              : None
 *
 */
void TextBoxPdiDraw(void)
{
   T_UINT16                   u16_ctr = 0;
   T_STEXTBOXPDI                 *ps_tb = {0};
   T_STEXTBOXPDIDATA             *ps_tbd = {0};
   T_CHAR                     *pc_fill_data = NULL;
   T_EPENCOLOR                e_color = BLACK;
   T_UINT16                   loop_j = 0;
   T_UINT16 alignment =0;
   T_UINT8 comparelimit=0;
   typedef enum
   {
      NORMTEXTBOX =0,
      REDXTEXTBOX,
      NOTEXTBOX
   }T_TEXTBOX_STAT;
   
   T_TEXTBOX_STAT status_flag=NOTEXTBOX;

   /*hdudispftextbox-TextBoxPdiDraw-DB-LLR-020*/
   if ((T_UINT16)ZERO == Tb_cnt)
   {
	   return;
   }
   for(u16_ctr = ZERO; u16_ctr < Tb_cnt; u16_ctr++)
   {
	   alignment = (T_UINT16)Page_settings.Tb_settings[u16_ctr].tb_align;

		  for(loop_j=ZERO; loop_j<= TWOHUNDRED_FIFTY_FIVE; loop_j++)
		   {
		   if ( Page_settings.Tb_settings[u16_ctr].label == Parameters_reading[loop_j].label)
		   {
		       if(PARAM_OK ==  Parameters_reading[loop_j].reading.stat)
			   {
			       if(DDW == Parameters_reading[loop_j].type)
				   {
					  if(ZERO ==((T_UINT32)(Parameters_reading[loop_j].reading.r)
					  >> (Page_settings.Tb_settings[u16_ctr].tb_bit-ELEVEN) & ONE))
			          {
						   /*hdudispftextbox-TextBoxPdiDraw-DB-LLR-014*/
			         	   status_flag =NOTEXTBOX;
			          }
                      else
                      {
                           /*hdudispftextbox-TextBoxPdiDraw-DB-LLR-015*/
						   status_flag =NORMTEXTBOX;
                      }
				   }
				   else if(BNR == Parameters_reading[loop_j].type)
				   {
					   comparelimit=CompareLimit((T_FLOAT)(Parameters_reading[loop_j].reading.fread),
			        		   Page_settings.Tb_settings[u16_ctr].tb_cross_val,
							   Page_settings.Tb_settings[u16_ctr].tb_cross_val_type);
				      if(ZERO == comparelimit)
				      {
						  /*hdudispftextbox-TextBoxPdiDraw-DB-LLR-016*/
					       status_flag =NOTEXTBOX;
					  }
                      else
                      {
						  /*hdudispftextbox-TextBoxPdiDraw-DB-LLR-017*/
                           status_flag =NORMTEXTBOX;
                      }
                   }
				   else
				   {
					   ; /* Do nothing */   
				   }
			   }
               else
               {
				   /*hdudispftextbox-TextBoxPdiDraw-DB-LLR-018*/
                   	status_flag = REDXTEXTBOX;
			   }
				break;
		    }
            else
		    {
				;
			}
		   }

	        /*hdudispftextbox-TextBoxPdiDraw-DB-LLR-001*/
	         ps_tb = &(S_pditext_boxes[u16_ctr]);

	         ps_tbd = ps_tb->pT_STEXTBOXPDIDATA;

	         if((NORMTEXTBOX == status_flag))
	         {
			   if (OFF ==S_pditext_boxes[u16_ctr].eState)
			   {
			       if(ps_tb->bFlashing != ZERO)
	               {
	                   /*hdudispftextbox-TextBoxPdiDraw-DB-LLR-002*/
	                   S8_had_flash = TRUE;

	                  if(FLASH_STATE_ON == Flash_state)
	                  {
	                       /*hdudispftextbox-TextBoxPdiDraw-DB-LLR-003*/
						   e_color = ps_tbd->eBackGroundColor;
	                  }
	                  else
	                  {
	                      /*hdudispftextbox-TextBoxPdiDraw-DB-LLR-004*/
						   e_color = ps_tbd->eFlashColor;
	                  }
	               }
	               else
	               {
	                     /*hdudispftextbox-TextBoxPdiDraw-DB-LLR-005*/
	                     e_color = ps_tbd->eBackGroundColor;
	               }
			   }
			   else
			   {
			      /*hdudispftextbox-TextBoxPdiDraw-DB-LLR-021*/
			       if(ps_tb->bFlashing != ZERO)
	               {
	                   S8_had_flash = TRUE;
	                  if(FLASH_STATE_ON == Flash_state)
	                  {
						   e_color = ps_tbd->eFlashColor;
	                  }
	                  else
	                  {
	                     e_color = ps_tbd->eBackGroundColor;
	                  }
	               }
	               else
	               {
	                    e_color = ps_tbd->eFontColor;
	               }
			   }

	         /*hdudispftextbox-TextBoxPdiDraw-DB-LLR-006*/
	         PolygonFillRect((T_INT16)(ps_tbd->s16ULX-ps_tb->s16LeftMargin),
	               (T_INT16)(ps_tbd->s16ULY-ps_tb->s16ToptMargin),
	               (T_INT16)(ps_tbd->s16PixWidth+ps_tb->s16LeftMargin+ps_tb->s16RightMargin),
	               (T_INT16)(ps_tbd->s16PixHeight+ps_tb->s16ToptMargin+ps_tb->s16BottomMargin),
	               e_color);

	         if(ps_tbd->s16FrameWidth != ((T_INT16)ZERO))
	         {
	            if((TEXT_BOX == ps_tbd->eTBoxType) || (LIST_BOX == ps_tbd->eTBoxType)
	                               || (SELECT_BOX == ps_tbd->eTBoxType))
	            {
	              /*hdudispftextbox-TextBoxPdiDraw-DB-LLR-007*/
	               PolygonDrawFrame((T_INT16)(ps_tbd->s16ULX-ps_tb->s16LeftMargin),
	                (T_INT16)(ps_tbd->s16ULY-ps_tb->s16ToptMargin),
	                (T_INT16)(ps_tbd->s16PixWidth+ps_tb->s16LeftMargin+ps_tb->s16RightMargin),
	                (T_INT16)(ps_tbd->s16PixHeight+ps_tb->s16ToptMargin+ps_tb->s16BottomMargin),
	                ps_tbd->s16FrameWidth,ps_tbd->eFrameColor);
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
	         if(ps_tbd->pcTitle != '\0')
	         {
	         /*hdudispftextbox-TextBoxPdiDraw-DB-LLR-008*/
	           pc_fill_data = ps_tbd->pcTitle;

	               
				   	if (OFF ==S_pditext_boxes[u16_ctr].eState)
			        {
			           if(ps_tb->bFlashing != ZERO)
	                   {
		                   S8_had_flash = TRUE;
	                      if(FLASH_STATE_ON == Flash_state)
	                      {
	                         e_color = ps_tbd->eFontColor;
	                      }
	                      else
	                      {
	                         e_color = ps_tbd->eBackGroundColor;
	                      }
					   }
					   else
					   {
	                       e_color = ps_tbd->eFontColor;
					   }
				    }
				    else
					{
					   /*hdudispftextbox-TextBoxPdiDraw-DB-LLR-011*/
			           if(ps_tb->bFlashing != ZERO)
	                   {
	                      S8_had_flash = TRUE;
	                      if(FLASH_STATE_ON == Flash_state)
	                      {
						   e_color = ps_tbd->eBackGroundColor;
	                      }
	                      else
	                      {
						    e_color = ps_tbd->eFlashColor;
	                      }
	                    }
	                    else
	                    {
						   e_color = ps_tbd->eBackGroundColor;
	                    }
					}
	                }
					else
					{

					}
	            /*hdudispftextbox-TextBoxPdiDraw-DB-LLR-012*/
	            TBDisplayStringPDI(pc_fill_data, &(S_pditext_boxes[u16_ctr]), e_color,alignment);
	         }
	         else if (REDXTEXTBOX == status_flag)
	         {
	             if(ps_tbd->pcTitle != '\0' && ps_tbd->psDisRegion != NULL)
	             {
					/*hdudispftextbox-TextBoxPdiDraw-DB-LLR-019*/
	                /* Replace all characters with a red x */
	            	 WidgetsRedX(ps_tbd->psDisRegion,&(ps_tb->psPolyRedX));
	             }
	             else
	             {
	                ;/*Do nothing*/
	             }
	         }
	         else
	         {
	        	 ;
	         }
	         /*hdudispftextbox-TextBoxPdiDraw-DB-LLR-013*/
	         ps_tb->s16DrawX = ((T_INT16)ZERO);
	         ps_tb->s16DrawY = ((T_INT16)ZERO);
   }
}

/*
 *
 * Function                : TBPrintPDI
 *
 * Description             : The function draws the text box in PDI.
 *
 * Formal parameter(s)     : T_CHAR *pc_text - INOPUT Text to be displayed in text box
 *                           T_STEXTBOXPDI *ps_tb - OUT Text to be displayed in text box
 *                           T_STEXTBOXPDIDATA *ps_tbd - IN Pointer to text box data parameters
 *                           T_EPENCOLOR e_color - IN Color of the text box
 *
 * Return Value            : None
 *
 * Assumption              : None
 *
 */
static void TBPrintPDI(T_CHAR *pc_text, T_STEXTBOXPDI *ps_tb, T_STEXTBOXPDIDATA *ps_tbd,\
                        T_EPENCOLOR e_color)
{
	T_UINT16 u16_length = ZERO;
   while(*pc_text != ZERO)
   {
      /* Carriage Return*/
      if(CARRIAGE_RTN == *pc_text)
      {
       /*hdudispftextbox-TBPrintPDI-DB-LLR-001*/
         ps_tb->s16DrawX = (T_INT16)( ps_tb->s16DrawX - u16_length);
         u16_length = ZERO;
      }
      /* Line Feed*/
      else if(LINE_FEED == *pc_text)
      {
         if((ps_tb->s16DrawY+ps_tb->psFont->FontHeight) < ps_tbd->s16PixHeight)
         {
         /*hdudispftextbox-TBPrintPDI-DB-LLR-002*/
            ps_tb->s16DrawY = (T_INT16)(ps_tb->s16DrawY + ps_tb->psFont->FontHeight);
         }
         else
         {
           ; /* Do nothing */
         }
      }
      else
      {
         if(
               (ps_tb->s16DrawX <= (ps_tbd->s16PixWidth-ps_tb->s16FontWidth)) &&
               (ps_tb->s16DrawY <= (ps_tbd->s16PixHeight-ps_tb->s16FontHeight))
            )
            {
         /*hdudispftextbox-TBPrintPDI-DB-LLR-003*/
               ps_tb->s16DrawX = (T_INT16)(ps_tb->s16DrawX + TextDrawChar((*pc_text),
                                 (T_UINT16)(ps_tbd->s16ULX+ps_tb->s16DrawX),
                                 (T_UINT16)(ps_tbd->s16ULY+ps_tb->s16DrawY),
                                  ps_tb->psFont, e_color));
               u16_length = (T_UINT16)(u16_length + ps_tb->s16FontWidth);
            }
         else
         {
           ; /* Do nothing */
         }

         if(BB_RIGHT == ps_tbd->eTBoxType)
         {
         /*hdudispftextbox-TBPrintPDI-DB-LLR-004*/
            ps_tb->s16DrawX = ZERO;

            if((ps_tb->s16DrawY+ps_tb->s16FontHeight) < ps_tbd->s16PixHeight)
            {
           /*hdudispftextbox-TBPrintPDI-DB-LLR-005*/
              ps_tb->s16DrawY = (T_INT16)(ps_tb->s16DrawY + ps_tb->psFont->FontHeight);
            }
            else
            {
              ; /* Do nothing */
            }
         }
        else
        {
         ; /* Do nothing */
        }

      }
     /*hdudispftextbox-TBPrintPDI-DB-LLR-006*/
      pc_text++;
   }
}

/*
 * Function                : TBDisplayStringPDI
 *
 * Description             : The function displays the string in the PDI for text box.
 *
 * Formal parameter(s)     : T_CHAR *pc_text - INOUT Text to be displayed
 *                           T_STEXTBOXPDI *ps_tb - INOUT Pointer to the structure T_STEXTBOX
 *                           T_EPENCOLOR e_color - IN Color to be displayed
 *                           T_UINT16 alignment - IN  Alignment of text to be displayed.
 *
 * Return Value            : None
 *
 * Assumption              : None
 *
 */
static void TBDisplayStringPDI(T_CHAR *pc_text,  T_STEXTBOXPDI *ps_tb,
 T_EPENCOLOR e_color,T_UINT16 alignment )
{
	T_STEXTBOXPDIDATA *ps_tbd = ZERO;

   /*hdudispftextbox-TBDisplayStringPDI-DB-LLR-001*/
   ps_tbd   =  ps_tb->pT_STEXTBOXPDIDATA;

   if(ALIGN_CENTER == alignment)
   {

     ps_tb->s16DrawY = (T_INT16)((ps_tbd->s16PixHeight - (StrLen(pc_text) *
                                    (T_INT16)ps_tb->s16FontHeight))/((T_INT16)TWO));

     ps_tb->s16DrawX = (T_INT16)((ps_tbd->s16PixWidth - (StrLen(pc_text) *
                                     (T_INT16)ps_tb->s16FontWidth))/((T_INT16)TWO));

      if(ps_tb->s16DrawY < ((T_INT16)ZERO))
      {

         ps_tb->s16DrawY = ((T_INT16)ZERO);
      }
      else
      {
    	  ;
      }
      if(ps_tb->s16DrawX < ((T_INT16)ZERO))
           {
              ps_tb->s16DrawX = ((T_INT16)ZERO);
           }
      else
      {
       ;
      }
   }
   /*hdudispftextbox-TBDisplayStringPDI-DB-LLR-002*/
   else if(ALIGN_RIGHT == alignment)
   {
      /*hdudispftextbox-TBDisplayStringPDI-DB-LLR-016*/
      ps_tb->s16DrawX = (T_INT16)((ps_tbd->s16PixWidth - (StrLen(pc_text) *
                                 (T_INT16)ps_tb->s16FontWidth)));
      /* Updated as per PR100083*/
      if(ps_tb->s16DrawX > (T_INT16)(ps_tb->s16DrawX + ps_tb->s16FontWidth))
      {
         /*hdudispftextbox-TBDisplayStringPDI-DB-LLR-017*/
         ps_tb->s16DrawX = ((T_INT16)(ps_tb->s16DrawX + ps_tb->s16FontWidth));
      }
      else
      {
       ;
      }
   }
   /*hdudispftextbox-TBDisplayStringPDI-DB-LLR-003*/
   else if(ALIGN_CENTER_LEFT == alignment)
      {

        ps_tb->s16DrawY = (T_INT16)((ps_tbd->s16PixHeight - (StrLen(pc_text) *
                                       (T_INT16)ps_tb->s16FontHeight))/((T_INT16)TWO));

         if(ps_tb->s16DrawY < ((T_INT16)ZERO))
         {

            ps_tb->s16DrawY = ((T_INT16)ZERO);
         }
         else
         {
       	  ;
         }
      }
   else
   {
     ; /*Default Alignment is ALIGN_LEFT */
   }

   /*hdudispftextbox-TBDisplayStringPDI-DB-LLR-004*/
   TBPrintPDI(pc_text, ps_tb, ps_tbd, e_color);
}
