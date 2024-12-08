/*
 ******************************************************************************
 * License Information  :  Howell Instruments, Inc.                           *
 *                         "Licensed Software" and "All rights reserved".     *
 ******************************************************************************
 *  File                : hdudispfbinascii.c
 *
 *  Description         : This file contains Utility routines to convert binary to ascii base 10.
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
 *      1.2          Shilpa A R      09-Oct-2017             100064
 *      1.3          Shruthi M N     30-Oct-2017             100104
 *      1.4          Rona B.S        04-Nov-2017             100156  
 *      1.5          Rona B S        02-Jul-2020             100259
 *
 * Additional References : None
 *
 ******************************************************************************
 */
#include "hdudispffonts.h"         /*Contains different font information*/
#include "hdulibbasictypes.h"    /*provides user defined types for basic types.*/
#include "hdudispfbinascii.h"      /*Utility routines to convert binary to ascii base 10.*/

/* Base of conversion.*/
/* Note that MAX_BASE10_SPACE must be adjusted if BASE changes.*/
#define  BASE                 10U

/* Maximum space for base 10 ascii of a T_UINT32 + null delimiter.*/
#define  MAX_BASE10_SPACE     11U

/* Index of the delimiter.*/
#define DELIMITER_POS         10U

/* Index of the last ascii character in the ascii.*/
#define  LAST_DIGIT_POS 9U

/* Ascii string delimiter.*/
#define DELIMITER            (T_INT8)0U

/* Ascii offset to '0'.*/
#define AZERO                 48U

#define SET_TPH       0x80
#define EXTRACT_BIT_8 0x80

#define ISDIGIT(c)   (((c)>='0')&&((c)<='9'))

/**********************************************************************************/
/*                           Function Definition                                  */
/**********************************************************************************/
/*
 *
 * Function                : BinasByte
 *
 * Description             : Converts an unsigned four byte binary number to ascii.
 *
 * Formal parameter(s)     : T_UINT32   src -IN The number to convert.
 *                           T_INT8 *dest   -OUT Receives the ascii conversion.
 *
 * Return Value            : T_INT8 * - The address of the string delimiter.
 *
 * Assumption              : None
 *
 */
static T_INT8 *BinasByte(T_UINT32   src,  T_INT8 *dest)
{
   T_INT8   buffer[MAX_BASE10_SPACE] = {0};   /* Temporary buffer for ascii.*/
   T_INT8   *next_byte = NULL;                /* Address of next byte in buffer.*/

   /*hdudispfbinascii-BinasByte-DB-LLR-001*/
   /* Delimit the buffer.*/
   buffer[DELIMITER_POS] = DELIMITER;

   /* Set next T_INT8 to least significant position.*/
   next_byte = buffer + LAST_DIGIT_POS;

   /*hdudispfbinascii-BinasByte-DB-LLR-002*/
   /* Do calculate a character.*/
   do
   {
      *next_byte = (T_INT8)(src % (T_UINT32)BASE);       /* Calculate a digit.*/
      *next_byte = (T_INT8)(*next_byte + (T_INT8)AZERO); /* Add the ascii offset.*/
      next_byte = next_byte - ONE;                         /* Step to the next T_INT8.*/
      src = (T_UINT32) (src / (T_UINT32)BASE);           /* Remove digit from src.*/
   }
   while(src);

   /* While the source is non zero.*/

   /* next_char points to the most sig digit.*/
   /*hdudispfbinascii-BinasByte-DB-LLR-003*/
   next_byte += ONE;

   /*hdudispfbinascii-BinasByte-DB-LLR-004*/
   /* While the delimiter has not been reached.*/
   while(*next_byte)
   {
       /* Transfer a character to dest.*/
      *(dest++) = *(next_byte++);
   }
   /*hdudispfbinascii-BinasByte-DB-LLR-005*/
   /* Add the delimiter to the buffer.*/
   *(dest) = DELIMITER;

   /* Return the address of the delimiter.*/
   return(dest);
}

/*
 *
 * Function                :BinasByteFormatInfo
 *
 * Description             :Converts a binary number to ascii. The supplied
 *                          formatting information is applied to the converted number.
 *
 * Formal parameter(s)     :void *src -IN Points to the number to convert.
 *                          Allowable sizes are 1, 2, and 4 bytes.
 *                          T_UINT16 format -IN The format used in the conversion.  The format
 *                          has the following structure.
 *
 *                          FEDCBA9876543210
 *                          ||||||||||||||||
 *                          ||||||||||||||||
 *                          ||||||||||||>>>>-> FIELD WIDTH [0..15].
 *                          |||||||||>>>-----> DECIMAL PLACES [0..7].
 *                          ||||||||>--------> UNSIGNED IF ONE.
 *                          ||||||>>---------> BYTES - 1, BYTES = [1..4].
 *                          |||||>-----------> NO LEADING 0 BLANKING IF ONE.
 *                          ||||>------------> PREFIX WITH '+' IF NUM POS.
 *                          |||>-------------> FLASH ALL ['0'..'9'] IF ONE.
 *                          ||>--------------> DO NOT FLASH IF OVERFLOW.
 *                          >>---------------> NOT USED
 *                          T_INT8 *dest -OUT Receives the ascii conversion.
 *
 * Return Value            : T_INT8 - The destination of the ascii.
 *
 * Assumption              : None
 *
 */
T_INT8 *BinasByteFormatInfo (void *src, T_UINT16 format, T_INT8 *dest)
{
   T_INT16     field_width = 0;        /* Field with of formatted output.           */
   T_INT16     size = 0;               /* Size (in bytes) of the input.             */
   T_INT16     decimals = 0;           /* Number of decimal places in the output.   */
   T_INT8      buffer[30] = {0};       /* Temp buffer for conversion.               */
   T_INT8      *byte_ptr = NULL;       /* Pointer to view input as bytes.           */
   T_INT8      *temp_bp = NULL;        /* Temp pointer.                             */
   T_INT16     counter = 0;            /* Loop counter.                             */
   T_INT32     number = 0;             /* Temp storage for number to convert.       */
   T_UINT16    negative = 0;           /* Number to convert is negative.            */
   T_INT8      *first_byte = NULL;     /* Points to the first ascii character.    */
   T_INT8      *last_byte = NULL;      /* Points to the conversion delimiter.       */
   T_INT8      *sign_pt = NULL;        /* Where to place the '+' or '-'.            */
   T_INT8      fill_byte = 0;          /* Prefix with either ' ' or '0'.            */
   T_INT8      sign = 0;               /* '+' or '-' or 0 if no sign.               */
   T_INT8      flash_it = 0;           /* Used to set text parity high if flash.    */

   /*hdudispfbinascii-BinasByteFormatInfo-DB-LLR-001*/
   /* If nothing to do, just exit.*/
   if(NO_NUMBER == format)
   {
      return(dest);
   }
   else
   {
    ;  /* Do nothing */
   }

   /*hdudispfbinascii-BinasByteFormatInfo-DB-LLR-002*/
   /* View the source on a per byte basis.*/
   byte_ptr       = (T_INT8*)src;
   size  = (T_INT16)(((format & S_M) >> S_P) + (T_INT16)ONE);

   /* Sign extend the number.                         */
   if((*(byte_ptr + size - ONE) & EXTRACT_BIT_8) && (!(format & UNSIGNED)))
   {
      /*hdudispfbinascii-BinasByteFormatInfo-DB-LLR-003*/
      number = MINUS_ONE;
      negative = TRUE;
   }
   else
   {
     /*hdudispfbinascii-BinasByteFormatInfo-DB-LLR-004*/
      number =  ZERO;
      negative = FALSE;
   }

   /* Copy the number to be converted.*/
   temp_bp = (T_INT8*)(&number);
   /*hdudispfbinascii-BinasByteFormatInfo-DB-LLR-005*/
   while(size)
   {
      *temp_bp = *byte_ptr;
      temp_bp  = temp_bp + ONE;
      byte_ptr = byte_ptr + ONE;
      size = (T_UINT8)(size - (T_UINT8)ONE);
   }

   /*hdudispfbinascii-BinasByteFormatInfo-DB-LLR-006*/
   /* Perform raw binary to ascii conversion.*/
   if(negative != ZERO)
   {
      number = (-number);
   }
   else
   {
      ; /*Do nothing*/
   }

   /*hdudispfbinascii-BinasByteFormatInfo-DB-LLR-007*/
   first_byte = buffer + FIFTEEN;
   last_byte = BinasByte ((T_UINT32)number,first_byte);

   /* Insert the decimal point if needed.       */
   decimals       = (format & D_M) >> D_P;
   if (decimals != ZERO)
   {
     /*hdudispfbinascii-BinasByteFormatInfo-DB-LLR-008*/
      for (counter=decimals, byte_ptr=last_byte - ONE ; counter> (T_INT16)ZERO; counter--)
      {
         *(byte_ptr+1) = *(byte_ptr);    /* Shift a digit right.             */
         byte_ptr = byte_ptr - 1;        /* Step to the next digit.          */
         if(byte_ptr < first_byte)       /* If past the first, pad '0'.      */
         {
            *(byte_ptr) = '0';
         }
         else
         {
            ; /*Do nothing*/
         }
      }
      /*hdudispfbinascii-BinasByteFormatInfo-DB-LLR-009*/
      /* If past the first, update first. */
      if(byte_ptr < first_byte)
      {
         first_byte = byte_ptr;
      }
      else
      {
         ; /*Do nothing*/
      }
      /*hdudispfbinascii-BinasByteFormatInfo-DB-LLR-010*/
      *(byte_ptr+1) = '.';               /* Put the decimal in.          */
      last_byte = last_byte + ONE;       /* Last T_INT8 moved one right. */
      *last_byte = DELIMITER;            /* Delimiter moved one right.   */
   }
   else
   {
      ; /*Do nothing*/
   }
   /*hdudispfbinascii-BinasByteFormatInfo-DB-LLR-011*/
   /* If the number is negative.*/
   if (negative != 0)
   {
      first_byte = first_byte - ONE;     /* First T_INT8 moved one right.*/
      sign = '-';                        /* Set the sign character.    */
   }
   /* Else if format calls for a plus sign.*/
   else if ((format & PUT_PLUS) != ZERO)
   {
      first_byte = first_byte - ONE;      /* First T_INT8 moved one right.*/
      sign = '+';                         /* Set the sign character.    */
   }
   /* Else set the sign to null.*/
   else
   {
      sign = (T_INT8)ZERO;
   }
   /*hdudispfbinascii-BinasByteFormatInfo-DB-LLR-012*/
   /* Extract the field width from the format.*/
   field_width = (format & W_M) >> W_P;

   /*hdudispfbinascii-BinasByteFormatInfo-DB-LLR-012*/
   /* Counter = requested fw - required fw.*/
   counter = (T_INT16) (field_width - (last_byte - first_byte));

   /* If the conversion will not fit in the requested field.*/
   if (counter < (T_INT16)ZERO)
   {
   /*hdudispfbinascii-BinasByteFormatInfo-DB-LLR-013*/
      /* Trivial case of 0 field width.*/
      if (ZERO == field_width)
      {
         *dest = ZERO;
         return (dest);
      }
      else
      {
         ; /*Do nothing*/
      }
      /* Point to last T_INT8 that will fit in field width.*/
      first_byte = last_byte - field_width;

      /* If a sign is required, step on left most with sign.*/
      if (sign != ZERO)
      {
         *(first_byte) = sign;
      }
      else
      {
         ; /*Do nothing*/
      }
      /* Replace all ['0'..'9'] with '?' to indicate overflow. */
      byte_ptr = first_byte;
      while (byte_ptr < last_byte)
      {
         if (ISDIGIT (*byte_ptr++))
         {
            *(byte_ptr - ONE) = '?';
         }
         else
         {
            ; /*Do nothing*/
         }
      }
   }

   /* Else the conversion will fit.*/
   else
   {
   /*hdudispfbinascii-BinasByteFormatInfo-DB-LLR-014*/
      sign_pt = first_byte;               /* Next to number if LZB.        */
      fill_byte = BINASCII_SPACE;         /* Default leading zero blank.   */
      first_byte = first_byte - counter;  /* Include full field width.     */

      /* If leading zeros are not to be blanked.*/
      if ((format & NOLZB) != ZERO)
      {
         fill_byte = '0';                /* Set to plug '0', not ' '.      */
         sign_pt = first_byte;           /* If no LZB, sign at far left.   */
      }
      else
      {
         ; /*Do nothing*/
      }

      byte_ptr = first_byte;             /* Set temp to first T_INT8.*/

      /*
       *If there is a sign, one more byte will need to be filled.
       * This way the results will be what is desired regardless
       * of LZB..
       */
      if (sign != ZERO)
      {
         counter =(T_INT16) (counter + (T_INT16)ONE);
      }
      else
      {
         ; /*Do nothing*/
      }
      /* Prefix the conversion with ' ' or '0'*/
      while (counter >(T_INT16)ZERO)
      {
         *(byte_ptr++) = fill_byte;
         counter =(T_INT16) (counter - (T_INT16)ONE);
      }

      /* If a sign is needed, place the sign.*/
      if (sign != ZERO)
      {
         *sign_pt = sign;
      }
      else
      {
         ; /*Do nothing*/
      }
   }
   /*hdudispfbinascii-BinasByteFormatInfo-DB-LLR-015*/
   flash_it = ZERO;                          /* Assume no flash.*/

   if ((format & FLASHIT) != ZERO)
   {
      flash_it = (T_INT8) SET_TPH;           /* If flash is needed, set TPH.*/
   }
   else
   {
      ; /*Do nothing*/
   }
   /*hdudispfbinascii-BinasByteFormatInfo-DB-LLR-016*/
   /* While more int8_tacters in the field.*/
   while (field_width >= (T_INT16)ZERO)
   {
      /* If flashing needed.*/
      if(flash_it != ZERO)
      {
         /* If the character is a digit.*/
         if ((ISDIGIT (*first_byte)) != ZERO)
         {
            /* Set text parity high.*/
            *first_byte |= flash_it;
         }
         else
         {
            ; /*Do nothing*/
         }
      }
      /* Transfer the byte to the destination.*/
      *(dest++) = *(first_byte++);

      /* Dec the number of int8_tacters to transfer.*/
      field_width =(T_INT16) (field_width - (T_INT16)ONE);
   }
   /*hdudispfbinascii-BinasByteFormatInfo-DB-LLR-017*/
   /* Return a pointer to the delimiter.  */
   return (dest - ONE);
}

/*
 *
 * Function                : BinasByteFormatInfoBE
 *
 * Description             : Converts a binary number to ascii. The supplied
 *                           formatting information is applied to the converted number.
 *                           Also, "book ends" are added to the ends of the
 *                           conversion to smooth the look of reverse video.
 *
 * Formal parameter(s)     : void *src -IN Points to the number to convert.
 *                           Allowable sizes are 1, 2, and 4 bytes.
 *                           T_UINT16 format -IN The format used in the conversion.  The format
 *                           has the following structure.
 *
 *                            FEDCBA9876543210
 *                            ||||||||||||||||
 *                            ||||||||||||||||
 *                            ||||||||||||>>>>-> FIELD WIDTH [0..15].
 *                            |||||||||>>>-----> DECIMAL PLACES [0..7].
 *                            ||||||||>--------> UNSIGNED IF ONE.
 *                            ||||||>>---------> BYTES - 1, BYTES = [1..4].
 *                            |||||>-----------> NO LEADING 0 BLANKING IF ONE.
 *                            ||||>------------> PREFIX WITH '+' IF NUM POS.
 *                            |||>-------------> FLASH ALL ['0'..'9'] IF ONE.
 *                            ||>--------------> DO NOT FLASH IF OVERFLOW.
 *                            >>---------------> NOT USED
 *
 *                           T_INT8 *dest -OUT Receives the ascii conversion.
 *
 * Return Value            : T_INT8 - A pointer to the null terminator of the ascii results.
 *
 * Assumption              : None
 *
 */

T_INT8 *BinasByteFormatInfoBE (void *src, T_UINT16 format, T_INT8* dest)
{
   T_INT8   *ps8_scanner = ZERO;

   /*hdudispfbinascii-BinasByteFormatInfoBE-DB-LLR-001*/
   ps8_scanner = dest+ONE;

   *dest = LEFT_BE;                                /* Prepend the left book end. */
    dest = dest + ONE;
    dest = BinasByteFormatInfo (src, format, dest);/* Insert the conversion. */
   *dest = RIGHT_BE;                               /* Append the right book end. */
    dest = dest + ONE;
   *dest = ZERO;                                   /* Delimit. */

   /*hdudispfbinascii-BinasByteFormatInfoBE-DB-LLR-002*/
   while(BINASCII_SPACE == *ps8_scanner)
   {
      *(ps8_scanner) =  LEFT_BE;
      *(ps8_scanner-ONE) = BINASCII_SPACE;
      ps8_scanner += ONE;
   }

   /*hdudispfbinascii-BinasByteFormatInfoBE-DB-LLR-003*/
   return(dest);
}

/*
 *
 * Function                : BinasGetWidth
 *
 * Description             : Returns the width of the supplied format word.
 *
 * Formal parameter(s)     : T_UINT16 format  - OUT The format word
 *
 *                           FEDCBA9876543210
 *                           ||||||||||||||||
 *                           ||||||||||||||||
 *                           ||||||||||||>>>>-> FIELD WIDTH [0..15].
 *                           |||||||||>>>-----> DECIMAL PLACES [0..7].
 *                           ||||||||>--------> UNSIGNED IF ONE.
 *                           ||||||>>---------> BYTES - 1, BYTES = [1..4].
 *                           |||||>-----------> NO LEADING 0 BLANKING IF ONE.
 *                           ||||>------------> PREFIX WITH '+' IF NUM POS.
 *                           |||>-------------> FLASH ALL ['0'..'9'] IF ONE.
 *                           ||>--------------> DO NOT FLASH IF OVERFLOW.
 *                           >>---------------> NOT USED
 *
 * Return Value            : T_UINT16 - The width of the specified output field.
 *
 * Assumption              : None
 *
 */

T_UINT16 BinasGetWidth (T_UINT16 format)
{
   /* hdudispfbinascii-BinasGetWidth-DB-LLR-001 */
   return(format & W_M);
}



