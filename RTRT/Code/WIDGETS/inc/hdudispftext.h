/*
 ******************************************************************************
 * License Information  :  Howell Instruments, Inc.                           *
 *                         "Licensed Software" and "All rights reserved".     *
 ******************************************************************************
 *  File                : hdudispftext.h
 *
 *  Description         : Contains routines which maintains text display and updates.
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
 *  Portability         : None
 *
 *  Author(s)           : Vinay H
 *
 *  Version History     :
 * <Version No.>     <Author>          <Date>         <Problem Report No.>
 *
 *      1.1          Vinay H         19-Jul-2017             100064
 *      1.2          Shilpa A R      10-Oct-2017             100064
 *      1.3          Chaithra J      21-Jun-2020             100259
 *      1.4          Rona B S        02-Jul-2020             100259
 *      1.5          Dhanalakshmi    12-Sep-2020             100276 
 *
 * Additional References : None
 *
 ******************************************************************************
 */

#ifndef _HDUDISPFTEXT_H_
#define _HDUDISPFTEXT_H_

#include "hdudispffonts.h"     /*Contains different font information*/
#include "hdudispfconfig.h"    /* contains page and color config information */
#include "hdudispfparams.h"	   /* provides the tags for various parameters and parameter units */
#include "hdudispfpolygon2.h"  /* contains routines for ploygons configuration */
/* CONFIGURATION */

#define MAX_TEXT_OBJECTS   50U    /* No more than 40 active text objects. */
#define EXTRACT_8_BIT      0x80U
#define EXTRACT_1_7_BIT    0x7fU
#define TOGGLE_8_BIT       0x80U
#define MAX_TEXT_PDI_OBJECTS   30U
typedef struct Text *T_PTEXT;

typedef enum
{
  ALIGN_CENTER = 354,      /* Text prints centered about a point. */
  ALIGN_CENTER_LEFT, /* Text prints centered and left justified about a point. */
  ALIGN_RIGHT,       /*  Text prints down and to the right. */
  ALIGN_LEFT         /*  Text prints down and to the left. */
}T_ETXALIGN;

/* Presentation options. */
typedef enum
{
   TX_NO_FLASH,  /* Text is not to flash. */
   TX_FLASH      /* Text flashes on and off. */
}T_ETXFLASH;

/* State when not flashing. */
typedef enum
{
   V_NORMAL,      /* Foreground object is normal video. */
   V_REVERSE      /* Foreground object is reverse video. */
}T_ETXV;

typedef enum
{
   FLASH_STATE_OFF,
   FLASH_STATE_ON
}  T_ETXFS;
typedef enum
{
   E_REGION_TYPE_GAUGE_TXT,
   E_REGION_TYPE_NUMBER_TXT
} T_EREGIONTYPE_TXT;
typedef struct
{
   T_INT16  u16X0;
   T_INT16  u16Y0;
}  T_SDISLOC_TXT;
typedef struct
{
	T_EREGIONTYPE_TXT  eRegionType;    /* What type of region is it? */
	T_SDISLOC_TXT      sDisLocCtr;     /* Center of the region. */
    /* Width of the region if Gauge type, Width of the line if Number type. */
   T_INT32           s32Width;
   T_INT32           s32Height;   /* Height of the region. */
   /* Offset from center to center of text if Gauge, offset to start of line if Number type. */
   T_SDISLOC_TXT         sDisLocO;
   T_ETXFONT         eTXFont;     /* Which font to use. */
   T_UINT8           *pu8Text;    /* Region Text. */
}  T_SDISREGION_TXT;
typedef struct Text
{
   T_PTEXT          *ppsOwner;
   T_UINT16          u16X0;
   T_UINT16          u16Y0;
   T_ETXALIGN        eTXAlign;
   T_ETXFONT         eTXFont;
   T_EPENCOLOR       ePenColor;
   T_ETXV            eTXV;
   T_ETXFLASH        eTXFlash;
   T_UINT8           *pu8String;
   T_UINT16          cross_val;
   T_SDISREGION_TXT      *psDisRegion;   /*  Region used for RED X         */
   T_PARAM_READING   *psParam;   		 /*  Parameter driving the number. */
   T_SPOLY           *psPolyRedX;        /* Polygon to "Red X" the region. */
}  T_TEXT;

/* FUNCTIONS */
extern void TextAllocat(T_PTEXT *pps_handle_add, T_UINT8 *pu8_string, T_UINT16 u16_x0,
                         T_UINT16 u16_y0, T_ETXALIGN e_tx_align, T_ETXFONT e_tx_font,
                          T_EPENCOLOR e_pen_color, T_ETXV e_txv, T_ETXFLASH e_tx_flash);

extern void TextUpdate(T_PTEXT p_text, T_EPENCOLOR e_pen_color, T_ETXFLASH e_tx_flash,
                                                                     T_ETXV e_txv);

extern void TextClear(void);

extern void TextDispString(T_INT8 *pc_string, T_UINT16 u16_x, T_UINT16 u16_y, T_ETXFONT e_tx_font,
      T_EPENCOLOR e_pen_color, T_ETXFLASH e_tx_flash, T_ETXV e_txv, T_ETXALIGN e_tx_align);

extern void TextDraw(void);

extern T_UINT16 TextDrawChar(T_UINT8 u8_char, T_UINT16   u16_dis_x, T_UINT16  u16_dis_y,
                                 T_BFC_FONT *p_font, T_EPENCOLOR e_color);

extern void TextDrawPDI(void);

extern void TextAllocatPdi(T_PTEXT *pps_handle_add, T_UINT8 *pu8_string, T_UINT16 u16_x0, 
						T_UINT16 u16_y0,T_ETXALIGN e_tx_align,T_ETXFONT e_tx_font,
						T_EPENCOLOR e_pen_color, T_ETXV e_txv, T_ETXFLASH e_tx_flash);

#endif /* _HDUDISPFTEXT_H_ */
