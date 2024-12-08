/*
 ******************************************************************************
 * License Information  :  Howell Instruments, Inc.                           *
 *                         "Licensed Software" and "All rights reserved".     *
 ******************************************************************************
 *  File                : hdudispftext.c
 *
 *  Description         : Display Text module
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
 *      1.3          Shruthi M N     15-Oct-2017             100083
 *      1.4          Shruthi M N     30-Oct-2017             100104
 *      1.5          Shruthi M N     04-Nov-2017             100120
 *      1.6          Chaithra J      21-Jun-2020             100259
 *      1.7          Rona B S        02-Jul-2020             100259
 *      1.8          Dhanalakshmi    05-Aug-2020             100270 
 *      1.9          Dhanalakshmi    12-Sep-2020             100276  
 *      1.10         Dhanalakshmi    28-Sep-2020             100284   
 *
 * Additional References : None
 *
 ******************************************************************************
 */

#include "hdudispfdma2d.h"    /* contains the common defines and functions prototypes for dma2d */
#include "hdudispffonts.h"    /*Contains different font information*/
#include "hdudispfrterror.h"    /* Stub routine for run time errors.*/
#include "hdudispftext.h"     /*  Routines which maintain text display and updates */
#include "hdudispfwidgets.h"  /* Contains routines for widget params */
#include "hdudispfconfig.h"   /* contains page and color config information */
#include "hdudispfforeground.h"  /* contains the routines for foreground layer of the display */
#include "hdulibbasictypes.h"   /* Standard basic data type definitions */
#include "hdudispfpanel.h"   /* Contains functions prototypes of panel.*/
#include "hdudispfgrapp.h"           /* routines for all graph */

#define SET_8_BIT        0x80U

/* Static allocation of all possible text objects. */
static T_TEXT A_text[MAX_TEXT_OBJECTS] = {0};

static T_TEXT A_text_pdi[MAX_TEXT_PDI_OBJECTS] = {0};
static T_UINT16 Text_installed = 0;

static T_UINT16 Text_objects_installed = 0;

/*Static function*/
static void DispStringAt(T_INT8 *pc_string, T_UINT16 u16_x, T_UINT16 u16_y, T_BFC_FONT *ps_font,
                         T_EPENCOLOR e_pen_color, T_ETXFLASH e_tx_flash, T_ETXV e_txv);

/*
 *
 * Function                : TextDrawChar
 *
 * Description             : Draw a single character
 *
 * Formal parameter(s)     : T_UINT8 u8_char - IN Character to be drawn
 *                           T_UINT16 u16_dis_x - INOUT X coordinate of position
 *                           T_UINT16 u16_dis_y - IN Y coordinate of position
 *                           T_BFC_FONT *p_font - IN Font of the character
 *                           T_EPENCOLOR e_color - IN Color
 *
 * Return Value            : T_UINT16 - Width of the character displayed
 *
 * Assumption              : None
 *
 */
T_UINT16 TextDrawChar(T_UINT8 u8_char, T_UINT16 u16_dis_x, T_UINT16  u16_dis_y,
                      T_BFC_FONT *p_font, T_EPENCOLOR e_color)
{
   const T_UINT8   *pu8_cbit_map = NULL;   /* Bit map of the character. */
   T_UINT16 *pu16_dot_add = NULL;          /* Address of the pixel */
   T_UINT16 u16_width = 0;                 /* Width of the font in pixels. */
   T_UINT16 u16_height = 0;                /* Height of font in pixels. */

   /*hdudispftext-TextDrawChar-DB-LLR-001*/
   /* Fetch the character bit map address. */
   pu8_cbit_map = Pu8GetCharBitMap(p_font, u8_char);

   /* Fetch the character width and make even. */
   u16_width = (PsGetCharInfo(p_font, u8_char))->Width;

   /* Fetch the character height. */
   u16_height = p_font->FontHeight;

   /* Calculate the pixel address in the frame buffer. */
   if(E_PORTRAIT == E_orientation)
   {
     /*hdudispftext-TextDrawChar-DB-LLR-002*/
     /* Updated as per PR100083*/
      u16_dis_x = (T_UINT16) (u16_dis_x + u16_width);
      pu16_dot_add = (T_UINT16 *)((T_UINT32) Vp_fgfb2 + (T_UINT32)(((((T_UINT32)S16_panel_height -
                (T_UINT32)u16_dis_x) * (T_UINT32)S16_panel_width) + (T_UINT32)u16_dis_y) * TWO));
   }
   else
   {
     /*hdudispftext-TextDrawChar-DB-LLR-003*/
      pu16_dot_add = ((T_UINT16 *) ((T_UINT32)Vp_fgfb2 + (T_UINT32)(u16_dis_x*2) +
                         ((T_UINT32)u16_dis_y*TWO)  * (T_UINT32)S16_panel_width));
   }

   /* Blend the character with the frame buffer background. */

   if(E_LAND_SCAPE == E_orientation)
   {
     /*hdudispftext-TextDrawChar-DB-LLR-004*/
      Dma2dDrawChar((const void *)pu8_cbit_map, (void *)pu16_dot_add, (T_UINT32)u16_width,
                    (T_UINT32) u16_height, e_color);

      if((CAS_RED == e_color)&&(u8_char & EXTRACT_8_BIT))
      {
       /*hdudispftext-TextDrawChar-DB-LLR-005*/
         Dma2dDrawChar((const void *)pu8_cbit_map, (void *)pu16_dot_add, (T_UINT32)u16_width,
                                                        (T_UINT32) u16_height, CAS_REV_RED);
         pu8_cbit_map = (const T_UINT8 *)Pu8GetCharBitMap(p_font, (u8_char & EXTRACT_1_7_BIT));

         Dma2dDrawChar((const void *)pu8_cbit_map, (void *)pu16_dot_add, (T_UINT32)u16_width,
                                                            (T_UINT32) u16_height, WHITE);
      }
      else
      {
       /*hdudispftext-TextDrawChar-DB-LLR-007*/
         Dma2dDrawChar((const void *)pu8_cbit_map, (void *)pu16_dot_add, (T_UINT32)u16_width,
                       (T_UINT32) u16_height, e_color);
      }
   }
   else
   {
      if((CAS_RED == e_color)&&(u8_char & EXTRACT_8_BIT))
      {
       /*hdudispftext-TextDrawChar-DB-LLR-008*/
         Dma2dDrawChar(( const void *)pu8_cbit_map, (void *)pu16_dot_add, (T_UINT32)u16_height,
                                                            (T_UINT32) u16_width, CAS_REV_RED);
         pu8_cbit_map = (const T_UINT8 *)Pu8GetCharBitMap(p_font,u8_char & EXTRACT_1_7_BIT);
         Dma2dDrawChar((const void *)pu8_cbit_map, (void *)pu16_dot_add, (T_UINT32)u16_height,
                                                              (T_UINT32) u16_width, WHITE);
      }
    else
      {
       /*hdudispftext-TextDrawChar-DB-LLR-010*/
         Dma2dDrawChar(pu8_cbit_map, (void *)pu16_dot_add, (T_UINT32)u16_height,
                       (T_UINT32) u16_width, e_color);
      }
   }
   /*hdudispftext-TextDrawChar-DB-LLR-011*/
   return(u16_width);
}

/*
 * Function                : DispStringAt
 *
 * Description             : The function displays the string at specified at the same location.
 *
 * Formal parameter(s)     : T_INT8 *pc_string - IN String to be displayed
 *                           T_UINT16 u16_x - INOUT X co-ordinate of the text
 *                           T_UINT16 u16_y - IN Y co-ordinate of the text
 *                           T_BFC_FONT *ps_font - IN Font of the text
 *                           T_EPENCOLOR e_pen_color - IN Color of the text
 *                           T_ETXFLASH e_tx_flash - IN Flash mode ( On or Off)
 *                           T_ETXV e_txv - IN Text video type.(Normal or Rev)
 *
 * Return Value            : None
 *
 * Assumption              : None
 *
 */
static void DispStringAt(T_INT8 *pc_string, T_UINT16 u16_x, T_UINT16 u16_y, T_BFC_FONT *ps_font,
                         T_EPENCOLOR e_pen_color, T_ETXFLASH e_tx_flash, T_ETXV e_txv)
{
   T_UINT8  *pu8_scanner = NULL;
   T_UINT8  u8_achar = ZERO;
    /* Updated as per PR100083*/
   T_UINT16  u16_length = ZERO;
   const T_BFC_CHARINFO    *ps_char_info = {0}; /*Char indicated by u8_achar */

   pu8_scanner = (T_UINT8 *)pc_string;

   /*hdudispftext-DispStringAt-DB-LLR-001*/
   while((u8_achar = *(pu8_scanner++)) != ((T_UINT8)ZERO))
   {
      if((V_REVERSE == e_txv) && ('\n' != u8_achar) && ('\r' != u8_achar))
      {
       /*hdudispftext-DispStringAt-DB-LLR-002*/
         u8_achar |= SET_8_BIT;
      }
      else
      {
         ;/*Do nothing*/
      }
      if((TX_FLASH == e_tx_flash) && ('\n' != u8_achar) && ('\r' != u8_achar))
      {
       /*hdudispftext-DispStringAt-DB-LLR-003*/
         VHadFlash();

         if(FLASH_OFF == EGetFlashState())
         {
            if(V_REVERSE == e_txv)
            {
            /*hdudispftext-DispStringAt-DB-LLR-004*/
               u8_achar ^= TOGGLE_8_BIT;
            }
            else
            {
               return;
            }
         }
         else
         {
            ;/*Do nothing*/
         }
      }
      else
      {
         ;/*Do nothing*/
      }
      /* Updated as PR 100083 */
      if('\n' == u8_achar )
      {
          /* hdudispftext-DispStringAt-DB-LLR-006 */
          u16_y = (T_UINT16)(u16_y + (T_UINT16)ps_font->FontHeight + ((T_UINT16)ONE) );
      }
      else if('\r' == u8_achar)
      {
         /* hdudispftext-DispStringAt-DB-LLR-007 */
         u16_x = (T_UINT16)(u16_x - u16_length);
          u16_length = ZERO;
      }
      else
      {
         /*hdudispftext-DispStringAt-DB-LLR-005*/
         u16_x =  (T_UINT16) (u16_x + TextDrawChar(u8_achar, u16_x, u16_y, ps_font, e_pen_color));
         /* Retrieve the char info. */
         ps_char_info = PsGetCharInfo(ps_font, u8_achar);
         u16_length = (T_UINT16)(u16_length + (T_UINT16)ps_char_info->Width);
      }
   }
}

/*
 *
 * Function                : TextDispString
 *
 * Description             : The function display the string at specified location
 *                           with specified parameters
 *
 * Formal parameter(s)     : T_INT8 *pc_string - IN String to be displayed
 *                           T_UINT16 u16_x - INOUT X co-ordinate of the text
 *                           T_UINT16 u16_y - INOUT Y co-ordinate of the text
 *                           T_ETXFONT e_tx_font - Font of the text
 *                           T_EPENCOLOR e_pen_color - Color of the text to be displayed
 *                           T_ETXFLASH e_tx_flash - Flash mode ( On or Off)
 *                           T_ETXV e_txv - Text video type.(Normal or Rev)
 *                           T_ETXALIGN e_tx_align - Alignment of the text.
 *
 * Return Value            : None
 *
 * Assumption              : None
 *
 */
void  TextDispString(T_INT8 *pc_string, T_UINT16 u16_x, T_UINT16 u16_y, T_ETXFONT e_tx_font,
           T_EPENCOLOR e_pen_color, T_ETXFLASH e_tx_flash, T_ETXV e_txv, T_ETXALIGN e_tx_align)
{
	
   T_BFC_FONT  *ps_font = NULL;

   /*hdudispftext-TextDispString-DB-LLR-001*/
   ps_font = (T_BFC_FONT *)FontsGetFont(e_tx_font); 
   
   /* If center alignment adjust the x and y draw point. */
   if(ALIGN_CENTER == e_tx_align)
   {
      /*hdudispftext-TextDispString-DB-LLR-002*/
      /* Back up half of the string width. */
      u16_x = (T_UINT16)(u16_x - (T_UINT16)((FontsGetStringWidth((T_UINT8 *)pc_string,
                                    e_tx_font))/(T_INT16)TWO));

      /* Back up half the font height. */
      u16_y = (T_UINT16)(u16_y - (T_UINT16)((T_UINT16)(FontsGetFontHeight(e_tx_font))/
                                    (T_UINT16)TWO));
   }
   else if(ALIGN_CENTER_LEFT == e_tx_align)
   {
     /*hdudispftext-TextDispString-DB-LLR-003*/
      /* Back up half the font height. */
      u16_y = (T_UINT16) (u16_y - (T_UINT16)(((T_UINT16)FontsGetFontHeight(e_tx_font))/
                           (T_UINT16)TWO));
   }
   else if(ALIGN_RIGHT == e_tx_align)
   {
	    /*hdudispftext-TextDispString-DB-LLR-005*/     
		 if(E_10_INCH == Display_size)
         {
             u16_x = (T_UINT16)( ((T_UINT16)PANEL_WIDTH) - \
                     (((T_UINT16)((FontsGetStringWidth((T_UINT8 *)pc_string,e_tx_font))))));
         }
         else if(E_7_INCH == Display_size)
         {
             u16_x = (T_UINT16)( ((T_UINT16)PANEL_HEIGHT) - \
                     (((T_UINT16)((FontsGetStringWidth((T_UINT8 *)pc_string,e_tx_font))))));
         }
         else
         {
             ;
         }
     }
	 else
	 {
	   ; /*Do nothing */
	 }
   /*hdudispftext-TextDispString-DB-LLR-004*/
   DispStringAt(pc_string, u16_x, u16_y, ps_font, e_pen_color, e_tx_flash, e_txv);
}

/*
 * Function                : TextAllocat
 *
 * Description             : The function allocates text structure for the new
 *                           strings to be displayed
 *
 * Formal parameter(s)     : T_PTEXT *pps_handle_add - INOUT Address of text parameters structure
 *                           T_UINT8 *pu8_string - IN String to be displayed
 *                           T_UINT16 u16_x0 - IN X co-ordinate of the  text
 *                           T_UINT16 u16_y0 - IN Y co-ordinate of the  text
 *                           T_ETXALIGN e_tx_align - IN Alignment of the text
 *                           T_ETXFONT e_tx_font - IN Font of the text.
 *                           T_EPENCOLOR e_pen_color - IN Color of the text
 *                           T_ETXV e_txv - IN Text video type.(Normal or Rev)
 *                           T_ETXFLASH e_tx_flash - IN Flash Mode (on or off).
 *
 * Return Value            : None
 *
 * Assumption              : None
 *
 */
void TextAllocat(T_PTEXT *pps_handle_add, T_UINT8 *pu8_string, T_UINT16 u16_x0, T_UINT16 u16_y0,
                    T_ETXALIGN e_tx_align,T_ETXFONT e_tx_font, T_EPENCOLOR e_pen_color,
                    T_ETXV e_txv, T_ETXFLASH e_tx_flash)
{
   /* Assume an object is available. */
   T_TEXT   *ps_text = &(A_text[Text_objects_installed]);

      /* Link the text object back to the current owner. */
      ps_text->ppsOwner = pps_handle_add;

      /* Initialize supplied fields. */
      ps_text->u16X0        = u16_x0;
      ps_text->u16Y0        = u16_y0;
      ps_text->eTXAlign     = e_tx_align;
      ps_text->eTXFont      = e_tx_font;
      ps_text->ePenColor    = e_pen_color;
      ps_text->eTXV         = e_txv;
      ps_text->eTXFlash     = e_tx_flash;
      ps_text->pu8String    = pu8_string;

      /* Provide client with the text object address. */
      *pps_handle_add = ps_text;

   Text_objects_installed = (T_UINT16)(Text_objects_installed + ONE);
}

/*
 * Function                : TextDraw
 *
 * Description             : The function dispalys the text.
 *
 * Formal parameter(s)     : None
 *
 * Return Value            : None
 *
 * Assumption              : None
 *
 */
void TextDraw(void)
{
   T_UINT16 u16_text_ctr = 0;
   T_PTEXT  p_text = {0};

   /*hdudispftext-TextDraw-DB-LLR-001*/
   /* Display each text types string. */
   for(u16_text_ctr = 0, p_text = A_text; u16_text_ctr<Text_objects_installed; u16_text_ctr++,
                                                                                   p_text++)
   {
      TextDispString((T_INT8 *)p_text->pu8String,
                      p_text->u16X0,
                      p_text->u16Y0,
                      p_text->eTXFont,
                      p_text->ePenColor,
                      p_text->eTXFlash,
                      p_text->eTXV,
                      p_text->eTXAlign
                     );
   }
}

/*
 * Function                : TextUpdate
 *
 * Description             : The function updates the text parameters.
 *
 * Formal parameter(s)     : T_PTEXT p_text - OUT Structure to text parameter
 *                           T_EPENCOLOR e_pen_color - IN Color of the text
 *                           T_ETXFLASH e_tx_flash - IN Flash Mode (On or off).
 *                           T_ETXV e_txv - IN Text video type.(Normal or Rev)
 *
 * Return Value            : None
 *
 * Assumption              : None
 *
 */
void TextUpdate(T_PTEXT p_text, T_EPENCOLOR e_pen_color, T_ETXFLASH e_tx_flash, T_ETXV e_txv)
{
   /*hdudispftext-TextUpdate-DB-LLR-001*/
   p_text->ePenColor = e_pen_color;
   p_text->eTXFlash = e_tx_flash;
   p_text->eTXV = e_txv;
}

/*
 *
 * Function                : TextClear
 *
 * Description             : De-allocate all text objects.
 *
 * Formal parameter(s)     : None
 *
 * Return Value            : None
 *
 * Assumption              : None
 *
 */
void TextClear(void)
{
   /*hdudispftext-TextClear-DB-LLR-001*/
   Text_objects_installed = ZERO;
   Text_installed = ZERO;
}


/*
 * Function                : TextDrawPDI
 *
 * Description             : The function dispalys the text.
 *
 * Formal parameter(s)     : None
 *
 * Return Value            : None
 *
 * Assumption              : None
 *
 */
void TextDrawPDI(void)
{
   T_UINT16 u16_text_ctr = 0;
   T_PTEXT  p_text = {0};
   T_UINT16 loop_j=0;
   T_TEXT   *ps_txt = 0;
   T_UINT8 comparelimit=0;

  /*hdudispftext-TextDrawPDI-DB-LLR-001*/
  if ((T_UINT16)ZERO == Text_cnt)
  {
	return;
  }
   
   /* Display each text types string. */
   for(u16_text_ctr = ZERO, p_text = A_text_pdi; u16_text_ctr<Text_installed; u16_text_ctr++,
                                                                                   p_text++)
   {
	   for(loop_j=ZERO; loop_j<= TWOHUNDRED_FIFTY_FIVE; loop_j++)
	    {
	     	   ps_txt = &(Page_txt[u16_text_ctr]);

	   		   if ( Page_settings.Text_settings[u16_text_ctr].label == Parameters_reading[loop_j].label)
	   		   {
	   			   if(PARAM_OK ==  Parameters_reading[loop_j].reading.stat)
				   {
				      if(DDW == Parameters_reading[loop_j].type)
					  {

					    if(ZERO == ((T_UINT32)(Parameters_reading[loop_j].reading.r) >>
                        (Page_settings.Text_settings[u16_text_ctr].txt_bit-ELEVEN) & ONE))
						{
						    ;
					    }
						else
						{
							/*hdudispftext-TextDrawPDI-DB-LLR-003*/
						    TextDispString((T_INT8 *)p_text->pu8String,
						    p_text->u16X0,
						    p_text->u16Y0,
						    p_text->eTXFont,
						    p_text->ePenColor,
						    p_text->eTXFlash,
						    p_text->eTXV,
						    p_text->eTXAlign
						    );
						}
					  }
					  else if (BNR == Parameters_reading[loop_j].type)
					  {
				          /*hdudispftext-TextDrawPDI-DB-LLR-002*/
						  comparelimit=CompareLimit((T_FLOAT)(Parameters_reading[loop_j].reading.fread),
							 Page_settings.Text_settings[u16_text_ctr].txt_cross_val ,
							 Page_settings.Text_settings[u16_text_ctr].txt_cross_val_type);

					    if(ONE == comparelimit)
						{
                           TextDispString((T_INT8 *)p_text->pu8String,
						   p_text->u16X0,
						   p_text->u16Y0,
						   p_text->eTXFont,
						   p_text->ePenColor,
						   p_text->eTXFlash,
						   p_text->eTXV,
						   p_text->eTXAlign
						  );
                        }
						else
						{
						   ;
						}
					  }
				    }
					else 
					{
						/*hdudispftext-TextDrawPDI-DB-LLR-004*/
						if( ps_txt->psDisRegion != NULL)
						 {
							/* Replace all characters with a red x */
							 WidgetsRedX((T_SDISREGION*)ps_txt->psDisRegion,&(ps_txt->psPolyRedX));
						 }
						 else
						 {
							;/*Do nothing*/
						 }
				    }
					break;
				}
				else
				{
				   ;
				}
		}
	}	
}


/*
 * Function                : TextAllocatPdi
 *
 * Description             : The function allocates text structure for the new
 *                           strings to be displayed
 *
 * Formal parameter(s)     : T_PTEXT *pps_handle_add - INOUT Address of text parameters structure
 *                           T_UINT8 *pu8_string - IN String to be displayed
 *                           T_UINT16 u16_x0 - IN X co-ordinate of the  text
 *                           T_UINT16 u16_y0 - IN Y co-ordinate of the  text
 *                           T_ETXALIGN e_tx_align - IN Alignment of the text
 *                           T_ETXFONT e_tx_font - IN Font of the text.
 *                           T_EPENCOLOR e_pen_color - IN Color of the text
 *                           T_ETXV e_txv - IN Text video type.(Normal or Rev)
 *                           T_ETXFLASH e_tx_flash - IN Flash Mode (on or off).
 *
 * Return Value            : None
 *
 * Assumption              : None
 *
 */
void TextAllocatPdi(T_PTEXT *pps_handle_add, T_UINT8 *pu8_string, T_UINT16 u16_x0, T_UINT16 u16_y0,
                    T_ETXALIGN e_tx_align,T_ETXFONT e_tx_font, T_EPENCOLOR e_pen_color,
                    T_ETXV e_txv, T_ETXFLASH e_tx_flash)
{
   /* Assume an object is available. */
   T_TEXT   *ps_text = &(A_text_pdi[Text_installed]);

   static T_CHAR param_message[] = "Too many text";

   T_CHAR file_name[] = __FILE__;

   /* Check for over allocated. */
   if(MAX_TEXT_PDI_OBJECTS < Text_cnt)
   {
     /*hdudispftext-TextAllocatPdi-DB-LLR-001*/
      RterrWidget((T_CHAR *)&file_name,__LINE__, (T_CHAR *) &param_message);
      return;
   }
   else
   {
     /*hdudispftext-TextAllocatPdi-DB-LLR-002*/
      /* Link the text object back to the current owner. */
      ps_text->ppsOwner = pps_handle_add;

      /* Initialize supplied fields. */
      ps_text->u16X0        = u16_x0;
      ps_text->u16Y0        = u16_y0;
      ps_text->eTXAlign     = e_tx_align;
      ps_text->eTXFont      = e_tx_font;
      ps_text->ePenColor    = e_pen_color;
      ps_text->eTXV         = e_txv;
      ps_text->eTXFlash     = e_tx_flash;
      ps_text->pu8String    = pu8_string;

      /* Provide client with the text object address. */
      *pps_handle_add = ps_text;
   }
   /*hdudispftext-TextAllocatPdi-DB-LLR-003*/
   Text_installed = (T_UINT16)(Text_installed + ONE);
}

