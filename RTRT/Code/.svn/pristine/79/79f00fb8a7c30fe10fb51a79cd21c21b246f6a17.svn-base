/*
 ******************************************************************************
 * License Information  :  Howell Instruments, Inc.                           *
 *                         "Licensed Software" and "All rights reserved".     *
 ******************************************************************************
 *  File                : hdudispbfonts.c
 *
 *  Description         : The hdudispbfonts CSC contains the routines for the fonts module.
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
 *
 * <Version No.>     <Author>          <Date>         <Problem Report No.>
 *
 *      1.1          Ajay J G        02-Aug-2017             -
 *      1.2          Divya G P       02-Sep-2017           100028
 *      1.3          Rona B S        04-Nov-2017           100156
 *      1.4          Rona B.S        05-Jul-2020           100259
 *
 * Additional References : None
 *
 ******************************************************************************
 */
#include "hdudispbfonts.h"       /* Contains functions prototypes of hdudispbfonts*/
#include "hdulibbasictypes.h"    /* Basic data types.*/
#include "hdudispbbfcfont.h"     /* BitFontCreator (Pro & Grayscale) font header */

/*
 * Function                :  Pu8GetCharBitMap
 *
 * Description             :  This function is used to Return a pointer
 *                                           to a character's bit map. Null if undefined.
 *
 * Formal parameter(s)     :  T_BFC_FONT *ps_font IN - Pointer to font structure of
 *                            character to be searched
 *                            T_UINT8 u8_char IN - Character to be seacrched
 *
 * Return Value            :  T_UINT8* --  Pointer to a character's bit map
 *
 * Assumption              :  None
 *
 */
const T_UINT8  *Pu8GetCharBitMap(const T_BFC_FONT *ps_font, T_UINT8 u8_char)
{
   const T_BFC_FONT_PROP *ps_group = NULL;

   const T_UINT8  *pu8_retval = (T_UINT8  *)0;  /* Default return value. */

   /*hdudispbfonts-Pu8GetCharBitMap-DB-LLR-001*/
   if( SUPPORTED_FONT_TYPE == ps_font->FontType)
   {
      ps_group = (ps_font->Font.pProp);
      while(ps_group)
      {
         if((u8_char >= (ps_group->FirstChar)) && (u8_char <= (ps_group->LastChar)))
         {
            pu8_retval = (const T_UINT8 *)((ps_group->pFirstCharInfo +
                         (u8_char - ps_group->FirstChar))->CharInfo.pData8);
            break;
         }
         else
         {
            ps_group = (ps_group->pNextProp);
         }
      }
   }
   else
   {
      ; /* Do nothing */
   }
   /*hdudispbfonts-Pu8GetCharBitMap-DB-LLR-002*/
   return(pu8_retval);
}

/*
 * Function                :  PsGetCharInfo
 *
 * Description             :  This function is used to Return a pointer
 *                                           to a character's char info map. Null if undefined.
 *
 * Formal parameter(s)     :  T_BFC_FONT *ps_font IN - Pointer to font structure
 *                            of character to be searched
 *                            T_UINT8 u8_char IN - Character to be seacrched
 *
 * Return Value            :  T_BFC_CHARINFO* - Pointer to character info map
 *
 * Assumption              :  None
 *
 */
const T_BFC_CHARINFO *PsGetCharInfo(const T_BFC_FONT *ps_font, T_UINT8 u8_char)
{
   const T_BFC_FONT_PROP *ps_group = NULL;
   const T_BFC_CHARINFO *ps_retval = (T_BFC_CHARINFO *)0;   /* Default return value. */

   /*hdudispbfonts-PsGetCharInfo-DB-LLR-001*/
   if(SUPPORTED_FONT_TYPE == ps_font->FontType )
   {
      ps_group = (T_BFC_FONT_PROP *)(ps_font->Font.pProp);
      while(ps_group)
      {
         if((u8_char >= (ps_group->FirstChar)) && (u8_char <= (ps_group->LastChar)))
         {
            ps_retval = (const T_BFC_CHARINFO   *)(ps_group->pFirstCharInfo
                        + (u8_char - ps_group->FirstChar));
            break;
         }
         else
         {
            ps_group = (ps_group->pNextProp);
         }
      }
   }
   else
   {
      ; /* Do nothing */
   }
   /*hdudispbfonts-PsGetCharInfo-DB-LLR-002*/
   return(ps_retval);
}

/*
 * Function                :  FontsGetFont
 *
 * Description             :  This function is used to Get font.
 *
 * Formal parameter(s)     :  T_ETXFONT e_tx_font INOUT - Specifies the font
 *
 * Return Value            :  T_BFC_FONT* - returns address of font
 *
 * Assumption              :  None
 *
 */
const T_BFC_FONT *FontsGetFont(T_ETXFONT e_tx_font)
{
   const T_BFC_FONT *ps_retval = NULL;
   e_tx_font = (T_ETXFONT)(e_tx_font + 0);
   switch (e_tx_font)
   {
      case SYSFONT:
      {
      /*hdudispbfonts-FontsGetFont-DB-LLR-001*/
         ps_retval = (const T_BFC_FONT *)(&Font_consolas24_haa4);
         break;
      }
      default:
      {
      /*hdudispbfonts-FontsGetFont-DB-LLR-002*/
         ps_retval = (T_BFC_FONT *)ZERO;
         break;
      }
   }
   return(ps_retval);
}

/*
 * Function                :  FontsGetCharWidth
 *
 * Description             :  This function is used to get the width
 *                            of the character font indicated by T_ETXFONT and u8_char
 *
 * Formal parameter(s)     :  T_ETXFONT e_tx_font IN - Specifies the font
 *                            T_UINT8 u8_char IN - Specifies the character.
 *
 * Return Value            :  T_INT16 - Returns information about character
 *
 * Assumption              :  None
 *
 */
T_INT16 FontsGetCharWidth(T_ETXFONT e_tx_font, T_UINT8 u8_char)
{
   const T_BFC_FONT        *ps_font_ptr_width = NULL;     /*Font indicated by e_tx_font */
   const T_BFC_CHARINFO    *ps_char_info = NULL; /*Char indicated by u8_char */
   T_INT16                 s16_retval = ZERO;     /*Return value of the function. */

   /* Presume failure */
   s16_retval  = ZERO;
   /* Retrieve the font. */

   /*hdudispbfonts-FontsGetCharWidth-DB-LLR-001*/
   ps_font_ptr_width = FontsGetFont(e_tx_font);

   /* If e_tx_font is valid. */
   /*hdudispbfonts-FontsGetCharWidth-DB-LLR-002*/
   if(NULL != ps_font_ptr_width)
   {
      ps_char_info = PsGetCharInfo(ps_font_ptr_width, u8_char);
      /* If the char is valid. */
      if(NULL != ps_char_info)
      {
         s16_retval = (T_INT16)(ps_char_info->Width);
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

   /*hdudispbfonts-FontsGetCharWidth-DB-LLR-003*/
   return(s16_retval);
}

/*
 * Function                :  FontsGetFontHeight
 *
 * Description             :  This function is used to get the height of the font
 *                                            indicated by T_ETXFONT.
 *
 * Formal parameter(s)     :  T_ETXFONT e_tx_font IN - Specifies the font
 *
 * Return Value            :  T_INT16 - height of the font
 *
 * Assumption              :  None
 *
 */
T_INT16 FontsGetFontHeight(T_ETXFONT e_tx_font)
{
   const T_BFC_FONT *ps_font_ptr_height = NULL;      /*Font indicated by e_tx_font */
   T_INT16           s16_retval = ZERO;    /*Return value of the function. */

   /* Presume failure */
   s16_retval  = ZERO;

   /*hdudispbfonts-FontsGetFontHeight-DB-LLR-001*/
   /* Retrieve the font. */
   ps_font_ptr_height = FontsGetFont(e_tx_font);

   /* If e_tx_font is valid. */
   if(NULL != ps_font_ptr_height)
   {
      /*hdudispbfonts-FontsGetFontHeight-DB-LLR-002*/
      s16_retval = (T_INT16)ps_font_ptr_height->FontHeight;
   }
   else
   {
      ; /* Do nothing */
   }
   /*hdudispbfonts-FontsGetFontHeight-DB-LLR-003*/
   return(s16_retval);
}
