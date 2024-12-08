/*
 ******************************************************************************
 * License Information  :  Howell Instruments, Inc.                           *
 *                         "Licensed Software" and "All rights reserved".     *
 ******************************************************************************
 *  File                : hdudispffonts.c
 *
 *  Description         : The file defines the fonts format.
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
 *      1.1          Vinay H         19-Jul-2017             100064
 *      1.2          Shilpa A R      10-Oct-2017             100064
 *      1.3          Shruthi M N     19-Oct-2017             100087
 *      1.4          Shruthi M N     30-Oct-2017             100104
 *      1.5          Dhanalakshmi D  21-Jun-2020             100259
 *      1.6          Rona B S        02-Jul-2020             100259
 *      1.7         Dhanalakshmi     20-Mar-2021             100331  
 *
 * Additional References : None
 *
 ******************************************************************************
 */

#include "hdudispfpanel.h"  /* Contains functions prototypes of panel.*/
#include "hdudispfbfcfont.h"      /* BitFontCreator (Pro & Grayscale) font header */
#include "hdudispffonts.h"        /*Contains different font information*/
#include "hdudispfrterror.h"        /* Provides routine for run time errors.*/
#include "hdulibbasictypes.h"   /* Standard basic data type definitions */

static const T_UINT8 *Pu8FindCharBitMap(T_BFC_FONT *ps_font, T_UINT8 u8_char);

/*
 *
 * Function                : Pu8FindCharBitMap
 *
 * Description             : The function finds the character bit map
 *
 * Formal parameter(s)     : T_BFC_FONT *ps_font - IN pointer to the structure font
 *                           T_UINT8 u8_char - IN Character
 *
 * Return Value            : T_UINT8 - return value
 *
 * Assumption              : None
 *
 */
static const T_UINT8 *Pu8FindCharBitMap(T_BFC_FONT *ps_font, T_UINT8 u8_char)
{
   const T_BFC_FONT_PROP *ps_group = (T_BFC_FONT_PROP *)NULL;

   const T_UINT8  *pu8_ret_val = (T_UINT8*)0;  /* Default return value. */

   /*hdudispffonts-Pu8FindCharBitMap-DB-LLR-001*/
   ps_group = ps_font->p_var_type.pProp;
   while(ps_group)
   {
      if((u8_char >= (ps_group->FirstChar)) && (u8_char <= (ps_group->LastChar)))
      {
       /*hdudispffonts-Pu8FindCharBitMap-DB-LLR-002*/
         pu8_ret_val = (ps_group->pFirstCharInfo +
                              (u8_char - ps_group->FirstChar))->p_var_type.pData8;
         break;
      }
      else
      {
       /*hdudispffonts-Pu8FindCharBitMap-DB-LLR-003*/
         ps_group = ps_group->pNextProp;
      }
   }
   /*hdudispffonts-Pu8FindCharBitMap-DB-LLR-004*/
   return(pu8_ret_val);
}

/*
 *
 * Function                : Pu8GetCharBitMap
 *
 * Description             : Return a pointer to a character's bit map. Null if undefined.
 *
 * Formal parameter(s)     : T_BFC_FONT *ps_font - IN pointer to the structure font
 *                           T_UINT8 u8_char - IN Character
 *
 * Return Value            : T_UINT8 - Pointer to character Bit map
 *
 * Assumption              : None
 *
 */
const T_UINT8  *Pu8GetCharBitMap(T_BFC_FONT *ps_font, T_UINT8 u8_char)
{
   const T_UINT8  *pu8_ret_val = (T_UINT8 *)0;  /* Default return value. */

   /*hdudispffonts-Pu8GetCharBitMap-DB-LLR-001*/
   pu8_ret_val = Pu8FindCharBitMap(ps_font, u8_char);

   if((T_UINT8 *)ZERO == pu8_ret_val)
   {
     /*hdudispffonts-Pu8GetCharBitMap-DB-LLR-002*/
      pu8_ret_val = Pu8FindCharBitMap(ps_font, '?');
   }
   else
   {
	   ;/* do nothing */
   }
   /*hdudispffonts-Pu8GetCharBitMap-DB-LLR-003*/
   return(pu8_ret_val);
}

/*
 * Function                : PsGetCharInfo
 *
 * Description             : Return a pointer to a character's char info map. Null if undefined.
 *
 * Formal parameter(s)     : T_BFC_FONT *ps_font - IN pointer to the structure font
 *                           T_UINT8 u8_char - IN Character
 *
 * Return Value            : T_BFC_CHARINFO - pointer to structure character information
 *
 * Assumption              : None
 *
 */
const T_BFC_CHARINFO *PsGetCharInfo(T_BFC_FONT *ps_font, T_UINT8 u8_char)
{
   const T_BFC_FONT_PROP *ps_group = {0};

   const T_BFC_CHARINFO *ps_ret_val = (T_BFC_CHARINFO *)0;  /* Default return value. */

   /* hdudispffonts-PsGetCharInfo-DB-LLR-001 */
   ps_group = ps_font->p_var_type.pProp;

   while(ps_group)
   {
      if((u8_char >= (ps_group->FirstChar)) && (u8_char <= (ps_group->LastChar)))
      {
         /* hdudispffonts-PsGetCharInfo-DB-LLR-002 */
         ps_ret_val = (ps_group->pFirstCharInfo + (u8_char - ps_group->FirstChar));
         break;
      }
      else
      {
         /* hdudispffonts-PsGetCharInfo-DB-LLR-003 */
         ps_group = ps_group->pNextProp;
      }
   }
   /* hdudispffonts-PsGetCharInfo-DB-LLR-004 */
   return(ps_ret_val);
}

/*
 * Function                : FontsGetFont
 *
 * Description             : The function is used to Get font.
 *
 * Formal parameter(s)     : T_ETXFONT e_tx_font - IN Specifies the font
 *
 * Return Value            : T_BFC_FONT - Returns the font information
 *
 * Assumption              : None
 *
 */
T_BFC_FONT *FontsGetFont(T_ETXFONT e_tx_font)
{
   T_BFC_FONT *ps_ret_val = {0};
   if (E_PORTRAIT == E_orientation)
   {
       switch (e_tx_font)
       {
          case E_TINY_FONT:
          {
           /*hdudispffonts-FontsGetFont-DB-LLR-001*/
             ps_ret_val = &Font_tiny;
             break;
          }
          case E_SMALL_FONT:
          {
           /*hdudispffonts-FontsGetFont-DB-LLR-002*/

             ps_ret_val = &Font_small;
             break;
          }
         case E_NORMAL_FONT:
          {
           /*hdudispffonts-FontsGetFont-DB-LLR-003*/
             ps_ret_val = &Font_normal;
             break;
          }
          case E_LARGE_FONT:
          {
           /*hdudispffonts-FontsGetFont-DB-LLR-004*/
             ps_ret_val = &Font_large;
             break;
          }
          case E_BEZEL_FONT:
          {
           /*hdudispffonts-FontsGetFont-DB-LLR-007*/
             ps_ret_val = &Font_bezel;
             break;
          }
          default:
          {
           /*hdudispffonts-FontsGetFont-DB-LLR-008*/
             ps_ret_val = (T_BFC_FONT *)0;
             break;
          }
       }
    }
    else
    {
        switch (e_tx_font)
        {
            case E_TINY_FONT:
            {
             /*hdudispffonts-FontsGetFont-DB-LLR-009*/
               ps_ret_val = &Font_tiny_10inch;
               break;
            }
            case E_SMALL_FONT:
            {
             /*hdudispffonts-FontsGetFont-DB-LLR-010*/
               ps_ret_val = &Font_small_10inch;
               break;
            }
            case E_NORMAL_FONT:
            {
            /*hdudispffonts-FontsGetFont-DB-LLR-011 */
               ps_ret_val = &Font_normal_10inch;
                break;
             }
             case E_LARGE_FONT:
             {
              /*hdudispffonts-FontsGetFont-DB-LLR-012*/
                ps_ret_val = &Font_large_10inch;
                break;
             }
             case E_BEZEL_FONT:
             {
              /*hdudispffonts-FontsGetFont-DB-LLR-013*/
                ps_ret_val = &Font_small_10inch;
                break;
             }
             default:
             {
              /*hdudispffonts-FontsGetFont-DB-LLR-014*/
                ps_ret_val = (T_BFC_FONT *)0;
                break;
             }
         }
    }
  
   return(ps_ret_val);
}

/*
 *
 * Function                : FontsGetCharWidth
 *
 * Description             : Get the width of the character font indicated by T_ETXFONT and u8_achar
 *
 * Formal parameter(s)     : T_ETXFONT e_tx_font - IN font of the character.
 *                           T_UINT8 u8_achar – IN Input character
 *
 * Return Value            : T_INT16 - width of the character
 *
 * Assumption              : None
 *
 */
T_INT16 FontsGetCharWidth(T_ETXFONT e_tx_font, T_UINT8 u8_achar)
{
   T_BFC_FONT        *ps_font_ptr = {0};     /*Font indicated by e_tx_font */
   const T_BFC_CHARINFO    *ps_char_info = {0}; /*Char indicated by u8_achar */
   T_INT16           s16_ret_val = 0;      /*Return value of the function. */

   /* Presume failure */
   s16_ret_val = 0;
   /*hdudispffonts-FontsGetCharWidth-DB-LLR-001*/
   /* Retrieve the font. */
   ps_font_ptr = FontsGetFont(e_tx_font);

   /* If e_tx_font is valid. */
   if((T_BFC_FONT *)NULL != ps_font_ptr)
   {
     /*hdudispffonts-FontsGetCharWidth-DB-LLR-002*/
      /* Retrieve the char info. */
      ps_char_info = PsGetCharInfo(ps_font_ptr, u8_achar);
      /* If the char is valid. */
      if((T_BFC_CHARINFO *)NULL != ps_char_info)
      {
       /*hdudispffonts-FontsGetCharWidth-DB-LLR-003*/
         s16_ret_val = (T_INT16)ps_char_info->Width;
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
   /*hdudispffonts-FontsGetCharWidth-DB-LLR-004*/
   return(s16_ret_val);
}

/*
 *
 * Function                : FontsGetFontHeight
 *
 * Description             : Get the height of the font indicated by T_ETXFONT.
 *
 * Formal parameter(s)     : T_ETXFONT e_tx_font - IN font of the character.
 *
 * Return Value            : T_INT16 - Height of the font
 *
 * Assumption              : None
 *
 */
T_INT16 FontsGetFontHeight(T_ETXFONT e_tx_font)
{
   T_BFC_FONT        *ps_font_ptr = {0};     /* Font indicated by e_tx_font */
   T_INT16           s16_ret_val = 0;     /* Return value of the function.  */

   /* Presume failure */
   s16_ret_val = 0;
   /*hdudispffonts-FontsGetFontHeight-DB-LLR-001*/
   /* Retrieve the font. */
   ps_font_ptr = FontsGetFont(e_tx_font);

   /*hdudispffonts-FontsGetFontHeight-DB-LLR-002*/
   /* If e_tx_font is valid. */
   if((T_BFC_FONT *)NULL != ps_font_ptr)
   {
      s16_ret_val = (T_INT16)ps_font_ptr->FontHeight;
   }
   else
   {
      ;/*Do nothing*/
   }
   /*hdudispffonts-FontsGetFontHeight-DB-LLR-003*/
   return(s16_ret_val);
}

/*
 * Function                : FontsGetStringWidth
 *
 * Description             : The function Get the width of the string indicated by T_ETXFONT
 *
 * Formal parameter(s)     : T_UINT8 *pu8_string - IN Input string
 *                           T_ETXFONT e_tx_font - IN font of the string
 *
 * Return Value            : T_INT16 - width of the string
 *
 * Assumption              : None
 *
 */
T_INT16 FontsGetStringWidth(T_UINT8 *pu8_string, T_ETXFONT e_tx_font)
{
   T_BFC_FONT        *ps_font_ptr = {0};  /*Font indicated by e_tx_font */
   T_INT16           s16_ret_val = 0;     /*Function return value. */

   s16_ret_val = 0;

   /*hdudispffonts-FontsGetStringWidth-DB-LLR-001*/
   ps_font_ptr = FontsGetFont(e_tx_font);

   if((T_BFC_FONT *)NULL != ps_font_ptr)
   {
      while(*pu8_string)
      {
       /*hdudispffonts-FontsGetStringWidth-DB-LLR-002*/
         s16_ret_val = (T_INT16)( s16_ret_val + FontsGetCharWidth(e_tx_font, *pu8_string));
         pu8_string += 1;
      }
   }
   else
   {
      ;/*Do nothing*/
   }
   /*hdudispffonts-FontsGetStringWidth-DB-LLR-003*/
   return(s16_ret_val);
}
