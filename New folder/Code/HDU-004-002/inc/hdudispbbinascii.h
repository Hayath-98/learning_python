/*
 ******************************************************************************
 * License Information  :  Howell Instruments, Inc.                           *
 *                         "Licensed Software" and "All rights reserved".     *
 ******************************************************************************
 *  File                : hdudispbbinascii.h
 *
 *  Description         : Utility routines to convert binary to ascii base 10.
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
 *      1.2          Divya G P       02-Sep-2017      100028
 *
 * Additional References : None
 *
 ******************************************************************************
 */
#ifndef  _HDUDISPBBINASCII_H_
#define  _HDUDISPBBINASCII_H_

#include "hdulibbasictypes.h"             /* Contains basic data types */

/*CONST*/
#define  NO_NUMBER      0x8000   /* No Number (Invalid Format.)*/
#define MAX_NUM_LEN  16          /* Max length of field and null delimiter.*/

#define  W_B   0x0f              /* Four bits for field width.*/
#define  W_P   0                 /* Use bits [0..3]*/
#define  W_M (W_B << W_P)         /* Mask for field width.*/

#define ONEW      (1 << W_P)     /* One character wide.*/
#define TWOW      (2 << W_P)     /* Two characters wide.*/
#define THREEW (3 << W_P)        /* Three characters wide.*/
#define  FOURW    (4 << W_P)     /* Four characters wide.*/
#define FIVEW     (5 << W_P)     /* Five characters wide.*/
#define SIXW      (6 << W_P)     /* Six characters wide.*/
#define SEVENW (7 << W_P)        /* Seven characters wide.*/
#define  EIGHTW   (8 << W_P)

#define D_B 0x07                 /* Three bits for decimal places.*/
#define D_P 4                    /* Use bits [4..6].*/
#define D_M (D_B << D_P)         /* Mask for decimal places.*/

#define ONED         (1 << D_P)  /* One decimal.*/
#define TWOD         (2 << D_P)  /* Two decimals.*/
#define THREED    (3 << D_P)     /* Three decimals.*/
#define FOURD        (4 << D_P)  /* Four decimals.*/
#define FIVED        (5 << D_P)  /* Five decimals.*/
#define SIXD         (6 << D_P)  /* Six decimals.*/
#define SEVEND    (7 << D_P)     /* Seven decimals.*/

#define U_B 0x01                 /* One bit for unsigned conversion.*/
#define U_P 7                    /* Use Bit 7.*/
#define U_M (U_B << U_P)         /* Mask for Unsigned conversion.*/

#define UNSIGNED  U_M            /* Flag for unsigned conversion.*/

#define S_B 0x03                 /* Two bits for the number size.*/
#define S_P 8                    /* Use bits [8..9].*/
#define S_M (S_B << S_P)         /* Mask for size.*/

#define ONEB      (0 << S_P)     /* One byte.*/
#define TWOB      (1 << S_P)     /* Two bytes.*/
#define THREEB (2 << S_P)        /* Three bytes.*/
#define FOURB     (3 << S_P)     /* Four bytes.*/

#define LZ_B   0x01              /* One bit for leave leading zeros.*/
#define LZ_P   10                /* Use bit 10*/
#define LZ_M (LZ_B << LZ_P)      /* Mask for no leading zero blanking.*/

#define NOLZB     LZ_M           /* Flag for no leading zero blanking.*/

#define PP_B   0x01              /* One bit for prefix with plus.*/
#define PP_P   11                /* Use bit 11.*/
#define PP_M   (PP_B << PP_P)    /* Mask for prefix with '+'.*/

#define  PUT_PLUS PP_M           /* Flag for prefix with '+' if positive.*/

#define F_B    0x01              /* One bit for flash.*/
#define F_P    12                /* Use bit 12.*/
#define F_M    (F_B << F_P)      /* Mask for flashing.*/

#define  FLASHIT  F_M            /* Flag for flash numeric characters.*/

extern T_CHAR *BinAscii (void *src, T_USHORT format, T_CHAR *dest);

#endif
