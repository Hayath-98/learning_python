/*
 ******************************************************************************
 * License Information  :  Howell Instruments, Inc.                           *
 *                         "Licensed Software" and "All rights reserved".     *
 ******************************************************************************
 *  File                : hdudispbtext.c
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
 *  Author(s)           : Ajay J G
 *
 *  Version History     :
 * <Version No.>        <Author>          <Date>            <Problem Report No.>
 *
 *      1.1             Ajay J G          28-Jul-2017             -
 *      1.2             Divya G P         02-Sep-2017          100028
 *      1.3             Rona B.S          04-Nov-2017          100156 
 *      1.4             Rona B.S          05-Jul-2020          100259 
 *
 * Additional References : None
 *
 ******************************************************************************
 */

#include "hdudispbfonts.h"       /* Contains functions prototypes of hdudispbfonts*/
#include "hdudispbpanel.h"       /* Contains functions prototypes of hdudispbpanel.*/
#include "hdulibbasictypes.h"    /* Contains basic data types.*/
#include "hdudispbtext.h"        /* Contains functions prototypes of hdudispbtext.*/
#include "hdudispbappdata.h"     /* Contains appdata structure for configuration file*/


static T_UINT16   U16_char_x = ZERO;           /* Character Cell column.*/
static T_UINT16   U16_char_y = ZERO;         /*  Character Cell Row. */

/* Note that the boot loader uses a fixed width font. */
static T_UINT16   U16_font_width = ZERO;     /* Width of a character. */
static T_UINT16   U16_font_height = ZERO;    /* Height of the Character. */
static T_UINT16   U16_dis_width = ZERO;      /* Width of the display in characters. */
static T_UINT16   U16_dis_height = ZERO;     /* Height of the display in characters. */

static void TextScroll(void);

/*
 * Function                :  DrawChar
 *
 * Description             :  This function is simple character display routine.
 *
 * Formal parameter(s)     :  T_UINT8 *pu8_char_map - IN Bit map of the character to print
 *                            T_UINT8 *pu8_dot_addr - OUT Frame buffer location of the char image
 *                            T_INT16 s16_font_height - IN height of the font
 *                            T_INT16 s16_char_width - IN width of the character
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */
static void DrawChar(const T_UINT8 *pu8_char_map, T_UINT8 *pu8_dot_addr, T_INT16 s16_font_height,
                                                                         T_INT16 s16_char_width)
{
   T_UINT8           u8_rows = ZERO;       /* Rows in the character bit map. */
   T_UINT8           u8_columns = ZERO;    /* Columns in the character bit map. */
   T_UINT16          u16_bpl = ZERO;       /* Bytes per line. */

   /*hdudispbtext-DrawChar-DB-LLR-001*/
   u16_bpl = (T_UINT16)((T_UINT16)s16_char_width+ONE)/TWO;

   /*hdudispbtext-DrawChar-DB-LLR-002*/
   /* Process all nibble pairs.  */
   for(u8_rows = ZERO; u8_rows < s16_font_height; u8_rows++)
   {
      for(u8_columns = ZERO; u8_columns<u16_bpl; u8_columns++, pu8_char_map++)
      {
         *(pu8_dot_addr) = (T_UINT8)((((*pu8_char_map) & MASK_LSB) << FOUR) | (T_UINT8)Pen_color);

         pu8_dot_addr += ONE;

         *(pu8_dot_addr) = (T_UINT8)(((*pu8_char_map) & MASK_MSB)  | Pen_color);

         pu8_dot_addr += ONE;
      }

      /* Step to the next row location.   */
      pu8_dot_addr += (PANEL_WIDTH-(u16_bpl*TWO));

      }
}


/*
 * Function                :  TextPrintChar
 *
 * Description             :  This function prints a character at the present display location.
 *
 * Formal parameter(s)     :  T_UINT8 u8_char - IN Bit map of the character
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */

void TextPrintChar(T_UINT8 u8_char)
{
   T_UINT8  *pu8_dot_addr  = ZERO;              /* Frame buffer location of the char image. */
   const T_UINT8   *pu8_char_map  = ZERO;       /* Bit map of the character to print.  */
   const T_BFC_FONT *ps_font = {ZERO};          /* Which font (at present just SysFont) */

   T_UINT16 u16_dot_x = ZERO;                   /* Pixel Column location for printing. */
   T_UINT16 u16_dot_y = ZERO;                   /* Pixel Row location for printing. */

   /*hdudispbtext-TextPrintChar-DB-LLR-001*/
   ps_font = FontsGetFont(SYSFONT);

   /*hdudispbtext-TextPrintChar-DB-LLR-002*/
   if(ps_font != NULL)
   {
      /* Process control characters. */
      /* Line feed. */
      if(TEN == u8_char)
      {
         U16_char_y = (T_UINT16)(U16_char_y + ONE);

         if(U16_char_y >= U16_dis_height)
         {
            U16_char_y = (T_UINT16)(U16_char_y - ONE);
            TextScroll();
         }
         else
         {
            ;
         }
         return;
      }
      /* Carriage return. */
      else if(THIRTEEN == u8_char)
      {
         U16_char_x = ZERO;
         return;
      }
      else
      {
       ;
      }

      /*hdudispbtext-TextPrintChar-DB-LLR-003*/
      pu8_char_map = Pu8GetCharBitMap(ps_font, u8_char);

      /*hdudispbtext-TextPrintChar-DB-LLR-004*/
      /* If the character is printable. */
      if(pu8_char_map != NULL )
      {
         u16_dot_x = (T_UINT16)(U16_char_x*U16_font_width);
         u16_dot_y = (T_UINT16)(U16_char_y*U16_font_height);

         /* If printing off the end of the line, auto CR/LF. */
         if((u16_dot_x+U16_font_width)>=PANEL_WIDTH)
         {
            U16_char_x = ZERO;
            u16_dot_x = ZERO;

            U16_char_y = (T_UINT16)(U16_char_y + ONE);
            u16_dot_y = (T_UINT16)(u16_dot_y + U16_font_height);
         }
         else
         {
          ;
         }

         /* If printing off the bottom of the display, scroll. */
         if((u16_dot_y+U16_font_height)>=PANEL_HEIGHT)
         {
            u16_dot_y = (T_UINT16)(u16_dot_y - U16_font_height);
            U16_char_y = (T_UINT16)(U16_char_y - ONE);
            TextScroll();
         }
         else
         {
          ;
         }

         /* Calculate absolute address in the frame buffer */

         pu8_dot_addr = (T_UINT8 *) ((T_UINT32)Vp_fgfb + (T_UINT32)u16_dot_x +
                                    (T_UINT32)(u16_dot_y * PANEL_WIDTH));
         DrawChar(pu8_char_map, pu8_dot_addr, (T_INT16)U16_font_height, (T_INT16)U16_font_width);
         U16_char_x = (T_UINT16)(U16_char_x + ONE);
      }
      /* If the character is not printable. */
      else
      {
         /*hdudispbtext-TextPrintChar-DB-LLR-005*/
         return;
      }
   }
   else
   {
      ;
   }
}

/*
 * Function                :  TextPrintString
 *
 * Description             :  This function is simple character display routine.
 *
 * Formal parameter(s)     :  T_UINT8 pu8_string - IN Pointer to the string
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */
void TextPrintString(T_UINT8  *pu8_string)
{
   /*hdudispbtext-TextPrintString-DB-LLR-001*/
   while(*pu8_string != ZERO)
   {
      TextPrintChar(*(pu8_string++));
   }
}

/*
 * Function                 :  TextClearEOL
 *
 * Description             :  This function clears end of line.
 *
 * Formal parameter(s)     :  None
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */

void TextClearEOL(void)
{
   T_UINT16 u16_temp_char = U16_char_x;

   /*hdudispbtext-TextClearEOL-DB-LLR-001*/
   while(U16_char_x < (U16_dis_width-ONE))
   {
      TextPrintChar(' ');
   }
   U16_char_x = u16_temp_char;
}

/*
 * Function                :  TextScroll
 *
 * Description             :  This function performs scroll operation.
 *
 * Formal parameter(s)     :  None
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */
static void TextScroll(void)
{
   T_UINT8     *pu8_src = ZERO;
   T_UINT8     *pu8_dest = ZERO;
   T_UINT32  u32_cnt = ZERO;

   /*hdudispbtext-TextScroll-DB-LLR-001*/
   pu8_src = (T_UINT8 *)((T_UINT8 *)Vp_fgfb + (U16_font_height*PANEL_WIDTH));

   /*hdudispbtext-TextScroll-DB-LLR-002*/
   pu8_dest = (T_UINT8 *)Vp_fgfb;

   /*hdudispbtext-TextScroll-DB-LLR-003*/
   u32_cnt = (T_UINT32)(((((PANEL_HEIGHT/U16_font_height)*U16_font_height)
            - U16_font_height) *PANEL_WIDTH));

   /*hdudispbtext-TextScroll-DB-LLR-004*/
   while(u32_cnt != ZERO)
   {
      *(pu8_dest++) = *(pu8_src++);
      u32_cnt = u32_cnt - ONE;
   }

   /*hdudispbtext-TextScroll-DB-LLR-005*/
   TextClearEOL();
}

/*
 * Function                 :  TextInit
 *
 * Description             :  This function initializes the various variables used while outputting
 *                            text to the LCD.
 *
 * Formal parameter(s)     :  None
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */

void  TextInit(void)
{
   /*hdudispbtext-TextInit-DB-LLR-001*/
   U16_font_width = (T_UINT16) FontsGetCharWidth(SYSFONT, (T_UINT8)'A');

   /*hdudispbtext-TextInit-DB-LLR-002*/
   U16_font_height = (T_UINT16) FontsGetFontHeight(SYSFONT);

   /*hdudispbtext-TextInit-DB-LLR-003*/
   U16_dis_width =(T_UINT16) (PANEL_WIDTH/U16_font_width);

   /*hdudispbtext-TextInit-DB-LLR-004*/
   U16_dis_height = (T_UINT16)(PANEL_HEIGHT/U16_font_height);
}

