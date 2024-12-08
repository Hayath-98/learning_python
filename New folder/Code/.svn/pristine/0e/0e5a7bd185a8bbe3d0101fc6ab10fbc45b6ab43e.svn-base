/*
 ******************************************************************************
 * License Information  :  Howell Instruments, Inc.                           *
 *                         "Licensed Software" and "All rights reserved".     *
 ******************************************************************************
 *  File                : hdulibbasictypes.h
 *
 *  Description         : Define standard types for increased portability between 8,
 *                        16, and 32 bit machines.
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
 *      1.1          Ajay J G        03-Aug-2017             -
 *      1.2          Rona B.S        02-Sep-2017            100028
 *      1.3          Rona B.S        30-Sep-2017            100064
 *      1.4          Shruthi M N     30-Oct-2017            100104
 *      1.5          Shilpa AR       23-Mar-2018            100196
 *      1.6          Rona B.S        13-Jul-2020            100259
 *      1.7          Dhanalakshmi    12-Sep-2020            100276
 *      1.8          Rona B S        28-Sep-2020            100284
 *      1.9          Dhanalakshmi    20-Mar-2021            100331
 *      1.10         Dhanalakshmi    20-Mar-2021            100331
 *      1.11         Dhanalakshmi    24-Apr-2021            100344
 *
 * Additional References : None
 *
 ******************************************************************************
 */
#ifndef _HDULIBBASICTYPES_H_
#define _HDULIBBASICTYPES_H_

/* TYPES*/
typedef  char                 T_CHAR;
typedef  unsigned char        T_UCHAR;
typedef  short int            T_SHORT;
typedef  unsigned short int   T_USHORT;
typedef  long int             T_LONG;
typedef  unsigned long int    T_ULONG;
typedef  float                T_FLOAT;
typedef signed char           T_INT8 ;
typedef unsigned char         T_UINT8;
typedef signed short int      T_INT16;
typedef unsigned short int    T_UINT16;
typedef signed  long  int     T_INT32;
typedef unsigned  long int    T_UINT32;
typedef signed  long int      T_INTL32;
typedef unsigned long int     T_UINTL32;
typedef signed long int       T_INT64;
typedef unsigned long int     T_UINT64;
typedef unsigned char         T_BOOLEAN;
typedef unsigned char         T_UBYTE;
typedef signed   char         T_BYTE;
typedef T_UINT16              T_UWORD;
typedef T_INT16               T_WORD;
typedef double            T_DOUBLE;

/* Character code support macros */
#define IS_UPPER(c)  (((c)>='A')&&((c)<='Z'))
#define IS_LOWER(c)  (((c)>='a')&&((c)<='z'))
#define IS_DIGIT(c)  (((c)>='0')&&((c)<='9'))


#define YES       1
#define EVER      ;;
#define NULL      ((void *)0)

#define STD_NUMBER_OF(x) (sizeof(x)/sizeof(x[0]))
#define STD_IS_IN_RANGE(val,minval,maxval) \
                     (((val)<(minval)) ? FALSE : (((val)>(maxval)) ? FALSE : TRUE))
#define ABS(X)    ((X) > 0 ? (X) : -(X))
#define MIN(x,y) ((x)<(y)?(x):(y))
#define MAX(x,y) ((x)>(y)?(x):(y))

#define  OS_FAR
#define  OS_STK_TYPE    T_ULONG
#define MASK_LSB                    ((T_UINT8)0x0F)
#define MASK_MSB                    ((T_UINT8)0xF0)
#define ZERO                        0U
#define ONE                         1U
#define TWO                         2U
#define THREE                       3U
#define FOUR                        4U
#define FIVE                        5U
#define SIX                         6U
#define SEVEN                       7U
#define EIGHT                       8U
#define NINE                        9U
#define TEN                         10U
#define ELEVEN                      11U
#define TWELVE                      12U
#define THIRTEEN                    13U
#define FIFTEEN                     15U
#define SIXTEEN                     16U
#define SEVENTEEN                   17U
#define NINTEEN                     19U
#define TWENTY_ONE                  21U
#define TWENTY_TWO                  22U
#define TWENTY_FOUR                 24U
#define TWENTY_SIX                  26U
#define TWENTY_EIGHT                28U
#define TWENTY_NINE                 29U

#define THIRTY_TWO                  32U
#define SIXTY_FIVE                  65U
#define HEX_PLLCFGR                 (T_UINT32)0x24003010
#define HSE_CSS_PLL                 (T_UINT32)0xFEF6FFFF
#define HEX_HSEBYP                  (T_UINT32)0xFFFBFFFF
#define HEX_ONE                     (T_UINT32)0x00000001
#define HEX_THREE                    (T_UINT32)0x00000003
#define HEX_ZERO                    (T_UINT32)0x00000000
#define SIXTY_THOUSAND              60000
#define ONE_HUNDRED                 100
#define ONE_LAKH                    100000
#define TWOHUNDRED_FIFTY_FIVE       ((T_UINT8)0xff)
#define MPU_BASE_ADDR1              0x20000000UL
#define MPU_BASE_ADDR2              0xc0000000UL
#define MPU_BASE_ADDR3              0x60000000UL
#define TWENTY                      20U
#define MINUS_ONE                   -1
#define MINUS_100                   -100
#define ONEHUNDRED_TWENTY_EIGHT     0x80U
#define THIRTY                      30U
#define THIRTY_ONE                  31U
#define DEC_ONE         1
#define DEC_TWO			2
#define DEC_FOUR        4
#define DEC_FIVE 		5
#define DEC_SIX 		6

/*Updated for PR100196 */
#define TWO_THOUSAND                2000
#define THOUSAND_FIVE_HUNDRED       1500
#define MAX_EXCEED_TIME             60000
#define FIFTY                       50U

#define  CHAR0 '0'
#define  CHAR9 '9'
#define  CHARUA 'A'
#define  CHARUZ 'Z'
#define  CHARLA 'a'
#define  CHARLZ 'z'
#define  POINT '.'
#define  HYPHEN '-'
#define  SPACE ' '

typedef enum
{
   FALSE = 0,
   TRUE  = !FALSE
} T_BOOL;

typedef enum
{
   OFF,
   ON
}  T_STATE;

#endif

