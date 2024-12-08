/*
 ******************************************************************************
 * License Information  :  Howell Instruments, Inc.                           *
 *                         "Licensed Software" and "All rights reserved".     *
 ******************************************************************************
 *  File                : hdudispbfonts.h
 *
 *  Description         :This file contains the common defines and functions prototypes for
 *                       hdudispbfonts.c.
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
 *      1.2          Divya G P       02-Sep-2017       100028
 *      1.3          Rona B.S        05-Jul-2020       100259
 *
 * Additional References : None
 *
 ******************************************************************************
 */

#ifndef _HDUDISPBFONTS_H_
#define _HDUDISPBFONTS_H_

#include "hdudispbbfcfont.h"     /* BitFontCreator (Pro & Grayscale) font header */

#define SUPPORTED_FONT_TYPE   (FONTTYPE_PROP_AA4 | LITTLE_ENDIAN1 | ENCODING_ASCII | DATALENGTH_8)

/* Available fonts. */
typedef enum
{
   FONT_NO_FONT_1,
   SYSFONT
}  T_ETXFONT;

extern const T_BFC_FONT Font_consolas24_haa4;

extern const T_UINT8 *Pu8GetCharBitMap(const T_BFC_FONT *ps_font, T_UINT8 u8_char);
extern const T_BFC_CHARINFO *PsGetCharInfo(const T_BFC_FONT *ps_font, T_UINT8 u8_char);
extern const T_BFC_FONT *FontsGetFont(T_ETXFONT e_tx_font);
extern T_INT16 FontsGetCharWidth(T_ETXFONT e_tx_font, T_UINT8 u8_char);
extern T_INT16 FontsGetFontHeight(T_ETXFONT e_tx_font);

#endif
