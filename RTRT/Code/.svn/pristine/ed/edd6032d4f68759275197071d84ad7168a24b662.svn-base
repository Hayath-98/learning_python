/*
 ******************************************************************************
 * License Information  :  Howell Instruments, Inc.                           *
 *                         "Licensed Software" and "All rights reserved".     *
 ******************************************************************************
 *  File                : hdudispffonts.h
 *
 *  Description         : Contains different font information.
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
 *  Author(s)           : Shilpa A R
 *
 *  Version History     :
 * <Version No.>      <Author>          <Date>         <Problem Report No.>
 *
 *      1.1           Shilpa A R       20-Jul-2017             100064
 *      1.2           Shruthi M N      19-Oct-2017             100087
 *      1.3           Dhanalakshmi D   21-Jun-2020             100259
 *      1.4           Rona B S         02-Jul-2020             100259
 *
 * Additional References : None
 *
 ******************************************************************************
 */

#ifndef _HDUDISPFFONTS_H_
#define _HDUDISPFFONTS_H_

#include "hdudispfbfcfont.h"    /* BitFontCreator (Pro & Grayscale) font header */

/* Define the special characters. */

#define RED_X              0x10U
#define CIRCLE_E           0x11U
#define BAR                0x12U
#define BINASCII_SPACE     0x15U
#define LEFT_BE            0x17U
#define RIGHT_BE           0x18U

#define SUPPORTED_FONT_TYPE   (FONTTYPE_PROP_AA4 | LITTLE_ENDIAN1 | COLUMN_BASED | \
                                    COLUMN_PREFERRED | ENCODING_ASCII | DATALENGTH_8)

extern T_BFC_FONT Font_tiny;
extern T_BFC_FONT Font_small;
extern T_BFC_FONT Font_normal;
extern T_BFC_FONT Font_tiny_10inch;    
extern T_BFC_FONT Font_small_10inch;
extern T_BFC_FONT Font_normal_10inch;  
extern T_BFC_FONT Font_large_10inch;
extern T_BFC_FONT Font_large;
extern T_BFC_FONT Font_bezel;


/* Available fonts. */
typedef enum
{
   E_NO_FONT,
   E_TINY_FONT=350,
   E_SMALL_FONT=351,
   E_NORMAL_FONT=352,
   E_LARGE_FONT=353,
   E_BEZEL_FONT=356
}  T_ETXFONT;

extern const T_UINT8 *Pu8GetCharBitMap(T_BFC_FONT *ps_font, T_UINT8 u8_char);
extern const T_BFC_CHARINFO *PsGetCharInfo(T_BFC_FONT *ps_font, T_UINT8 u8_char);
extern T_BFC_FONT *FontsGetFont(T_ETXFONT e_tx_font);
extern T_INT16 FontsGetCharWidth(T_ETXFONT e_tx_font, T_UINT8 u8_achar);
extern T_INT16 FontsGetFontHeight(T_ETXFONT e_tx_font);
extern T_INT16 FontsGetStringWidth(T_UINT8 *pu8_string, T_ETXFONT e_tx_font);

#endif   /* _HDUDISPFFONTS_H_ */
