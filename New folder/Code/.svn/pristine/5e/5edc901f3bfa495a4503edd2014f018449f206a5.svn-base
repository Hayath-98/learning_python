/*
 ******************************************************************************
 * License Information  :  Howell Instruments, Inc.                           *
 *                         "Licensed Software" and "All rights reserved".     *
 ******************************************************************************
 *  File                : hdudispbbfcfont.h
 *
 *  Description         : BitFontCreator (Pro & Grayscale) font header include file
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
 *      1.2          Shilpa A R      02-Oct-2017           100064
 *
 * Additional References : None
 *
 ******************************************************************************
 */
#ifndef _HDUDISPBBFCFONT_H_
#define _HDUDISPBBFCFONT_H_

#include "hdulibbasictypes.h"    /* Contains basic data types */

#define FONTTYPE_MONO         (1<<0)      /* Is monospaced font */
#define FONTTYPE_PROP         (1<<1)      /* Is proportional font */
#define FONTTYPE_MONO_AA2     (1<<2)      /* Is an antialiased mono font, 2bpp */
#define FONTTYPE_MONO_AA4     (1<<3)      /* Is an antialiased mono font, 4bpp */
#define FONTTYPE_MONO_AA8     (1<<4)      /* Is an antialiased mono font, 8bpp */
#define FONTTYPE_PROP_AA2     (1<<5)      /* Is an antialiased prop font, 2bpp */
#define FONTTYPE_PROP_AA4     (1<<6)      /* Is an antialiased prop font, 4bpp */
#define FONTTYPE_PROP_AA8     (1<<7)      /* Is an antialiased prop font, 8bpp */

/* the following 4 flags are added since BitFontCreator Pro v3.7 & Grayscale v4.5 */
#define LITTLE_ENDIAN1        (1<<8)      /* Is Little Endian if set, or is Big Endian (default) */
#define COLUMN_BASED          (1<<9)      /* Is Column if set, or is Row (default) */
#define COLUMN_PREFERRED      (1<<10)     /* Is Column if set, or is Row (default) */
#define DATA_PACKED           (1<<11)     /* Is Packed if set, or is Unpacked (default) */

#define ENCODING_ASCII        (1<<16)     /* Character encoding: Ascii + ISO8859 */
#define ENCODING_UNICODE      (1<<17)     /* Character encoding: Unicode */
#define ENCODING_SHIFTJIS     (1<<18)     /* Character encoding: Shift_JIS */
#define ENCODING_BIG5         (1<<19)     /* Character encoding: Big5 */
#define ENCODING_GBK          (1<<20)     /* Character encoding: GBK */
#define ENCODING_JOHAB        (1<<21)     /* Character encoding: Johab */

#define DATALENGTH_8          (1<<24)     /* Data length:  8 bits per unit (1 byte) */
#define DATALENGTH_16         (1<<25)     /* Data length: 16 bits per unit (2 bytes) */
#define DATALENGTH_32         (1<<26)     /* Data length: 32 bits per unit (4 bytes) */

typedef struct T_BFC_CHARINFO
{
   T_UINT16    Width;         /* character width in pixels */
   T_UINT16    DataSize;      /* # bytes/words/dwords of pixel data */
   union
   {
      const void     *pData;
      const T_UINT8     *pData8; /* pixel data in bytes */
      const T_UINT16 *pData16;   /* pixel data in words */
      const T_UINT32    *pData32;   /* pixel data in dwords */
   } CharInfo;
} T_BFC_CHARINFO;

typedef struct T_BFC_FONT_PROP
{
   T_UINT16    FirstChar;     /* index of first character */
   T_UINT16    LastChar;      /* index of last character */
   const T_BFC_CHARINFO *pFirstCharInfo;  /* address of first character */
   const struct T_BFC_FONT_PROP  *pNextProp; /* pointer to next BFC_FONT_PROP */
} T_BFC_FONT_PROP;

typedef struct T_BFC_FONT_MONO
{
   T_UINT16    FirstChar;     /* index of first character */
   T_UINT16    LastChar;      /* index of last character */
   T_UINT16    FontWidth;     /* font width in pixels */
   T_UINT16    DataSize;      /* # bytes/words/dwords data of single character */
   union
   {
      const void     *pData;
      const T_UINT8     *pData8; /* pixel data in bytes */
      const T_UINT16 *pData16;   /* pixel data in words */
      const T_UINT32    *pData32;   /* pixel data in dwords */
   } Font_Mono;
} T_BFC_FONT_MONO;

typedef struct
{
   T_UINT32    FontType;      /* font type */
   T_UINT16    FontHeight;    /* font height in pixels */
   T_UINT16    Baseline;      /* font ascent (baseline) in pixels */
   T_UINT32    Reversed;      /* reversed, =0 */
   union
   {
      const void        * pData;
       T_BFC_FONT_MONO  * pMono; /* point to Monospaced font */
       T_BFC_FONT_PROP  * pProp; /* point to proportional font */
   } Font;
} T_BFC_FONT;


/* Binary font structures (BIN) */
typedef struct
{
   T_UINT32    FontType;      /* font type */
   T_UINT16    FontHeight;    /* font height in pixels */
   T_UINT16    Baseline;      /* font ascent (baseline) in pixels */
   T_UINT16    Reversed;      /* reversed, =0 */
   T_UINT16    NumRanges;     /* number of character ranges */
} T_BFC_BIN_FONT;

typedef struct
{
   T_UINT16    FirstChar;     /* index of first character */
   T_UINT16    LastChar;      /* index of last charcter */
} T_BFC_BIN_CHARRANGE;

typedef struct
{
   T_UINT16    Width;         /* character width in pixels */
   T_UINT16    DataSize;      /* # bytes/words/dwords of pixel data */
   T_UINT32    OffData;    /* Offset of pixel data */
} T_BFC_BIN_CHARINFO;


#endif
