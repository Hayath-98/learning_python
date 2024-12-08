/*
 ******************************************************************************
 * License Information  :  Howell Instruments, Inc.                           *
 *                         "Licensed Software" and "All rights reserved".     *
 ******************************************************************************
 *  File                : hdudispbbinascii.c
 *
 *  Description         : Utility routines to convert binary to ascii base 10
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
 * <Version No.>     <Author>          <Date>         <Problem Report No.>
 *
 *      1.1          Ajay J G        28-Jul-2017             -
 *      1.2          Divya G P       02-Sep-2017           100028
 *      1.3          Shruthi M N     28-Sep-2017           100064
 *      1.4          Rajalakshmi S   10-Oct-2017           100064
 *      1.5          Shruthi M N     04-Nov-2017           100156
 *      1.6          Vinay H    	 09-Nov-2017           100164
 *      1.7          Rona B.S        05-Jul-2020           100259
 *
 * Additional References : None
 *
 ******************************************************************************
 */

#include "hdudispbbinascii.h"    /* Contains function prtotypes*/
#include "hdulibbasictypes.h"    /* Contains basic data types */

/* Base of conversion.*/
/* Note that MAX_LONG_CHAR must be adjusted if BASE changes.*/
#define  BASE                 10U
/* Maximum space for base 10 ascii of a T_ULONG + null delimiter.*/
#define  MAX_LONG_CHAR     11U
/* Index of the delimiter.*/
#define DELIMITER_POS      10U
/* Index of the last ascii character in the ascii.*/
#define  LAST_DIGIT_POS 9U
/* Ascii string delimiter.*/
#define DELIMITER          (T_CHAR)0
/* Ascii offset to '0'.*/
#define AZERO                 48U


/*
 * Function                : BinAsciiConv
 *
 * Description             : This function is used for converts an unsigned four byte
 *                           binary number to ascii.
 *
 * Formal parameter(s)     : T_ULONG src   - INOUT The number to convert.
 *                           T_CHAR *dest   - OUT  Receives the ascii conversion.
 *
 * Return Value            : T_CHAR * - The address of the string delimiter.
 *
 * Assumption              : None
 */
static T_CHAR *BinAsciiConv(T_ULONG   src,  T_CHAR *dest)
{
   T_CHAR  buffer[MAX_LONG_CHAR] = {ZERO};     /* Temporary buffer for ascii.*/
   T_CHAR  *next_char = NULL;                  /* Address of next char in buffer.*/

   /* Delimit the buffer.*/
   /*hdudispbbinascii-BinAsciiConv-DB-LLR-001*/
   buffer[DELIMITER_POS] = DELIMITER;

   /* Set next character to least significant position.*/
   /*hdudispbbinascii-BinAsciiConv-DB-LLR-002*/
   next_char = buffer+LAST_DIGIT_POS;

   /* Do calculate a character.*/
   /*hdudispbbinascii-BinAsciiConv-DB-LLR-003*/
   do
   {
      *next_char = (T_CHAR)(src % (T_ULONG)BASE);    /* Calculate a digit.*/
      *next_char = (T_CHAR)(*next_char + AZERO);     /* Add the ascii offset.*/
      next_char = next_char - ONE;                   /* Step to the next char.*/
      src =(src / ((T_ULONG)BASE));                  /* Remove digit from src.*/
   }
   while(src);
   /* While the source is non zero.*/

   /* next_char points to the most sig digit.*/
   /*hdudispbbinascii-BinAsciiConv-DB-LLR-004*/
   next_char += ONE;

   /* While the delimiter has not been reached.*/
   /*hdudispbbinascii-BinAsciiConv-DB-LLR-005*/
   while(*next_char)
   {
      *(dest++) = *(next_char++);                  /* Transfer a character to dest.*/
   }
   /* Add the delimiter to the buffer.*/
   *(dest) = DELIMITER;

   /* Return the address of the delimiter.*/
   /*hdudispbbinascii-BinAsciiConv-DB-LLR-006*/
   return(dest);
}

/*
 * Function                : BinAscii
 *
 * Description             : This function is used for Converting a binary number to ascii.
 *                           The supplied formatting information is applied to the
 *                           converted number.
 *
 * Formal parameter(s)     : void *src - IN Points to the number to convert. Allowable sizes
 *                                        are 1, 2, and 4 bytes.
 *                           T_USHORT format - IN The format used in the conversion. The format
 *                                              has the following structure.
 *                           T_CHAR *dest - OUT  The destination of the ascii.
 *
 * Return Value            : T_CHAR - A pointer to the null terminator of the ascii results.
 *
 * Assumption              : None
 */
T_CHAR *BinAscii (void *src, T_USHORT format, T_CHAR* dest)
{
   T_SHORT    field_width = ZERO;      /* Field with of formatted output.*/
   T_SHORT    size        = ZERO;      /* Size (in bytes) of the input.*/
   T_SHORT    decimals    = ZERO;      /* Number of decimal places in the output.*/
   T_CHAR     buffer [30] = {ZERO};    /* Temp buffer for conversion.*/
   T_CHAR     *byte_ptr   = ZERO;      /* Pointer to view input as bytes.*/
   T_CHAR     *temp_bp    = ZERO;      /* Temp pointer.*/
   T_SHORT    counter     = ZERO;      /* Loop counter.*/
   T_LONG     number      = ZERO;      /* Temp storage for number to convert.*/
   T_USHORT   negative    = ZERO;      /* Number to convert is negetive.*/
   T_CHAR     *first_char = ZERO;      /* Points to the first ascii character.*/
   T_CHAR     *last_char  = ZERO;      /* Points to the conversion delimiter.*/
   T_CHAR     *sign_pt    = ZERO;      /* Where to place the '+' or '-'.*/
   T_CHAR     fill_char   = ZERO;      /* Prefix with either ' ' or '0'.*/
   T_CHAR     sign        = ZERO;      /* '+' or '-' or 0 if no sign.*/
   T_CHAR     flash_it    = ZERO;      /* Used to set text parity high if flash.*/

   /*hdudispbbinascii-BinAscii-DB-LLR-001*/
   if( NO_NUMBER == format)
   {
      return(dest);
   }
   else
   {
      ;
   }

   /* View the source on a per byte basis.*/
   /*hdudispbbinascii-BinAscii-DB-LLR-002*/
   byte_ptr       = (T_CHAR*)src;

   /*hdudispbbinascii-BinAscii-DB-LLR-003*/
   size  = (T_SHORT)(((format & S_M) >> S_P) + (T_SHORT)ONE);

   /* Sign extend the number.                         */
   /*hdudispbbinascii-BinAscii-DB-LLR-004*/
   if((*(byte_ptr + size - ONE) & ONEHUNDRED_TWENTY_EIGHT) && (!(format & UNSIGNED)))
   {
      number = MINUS_ONE;
      negative = ONE;
   }
   else
   {
      number = ZERO;
      negative = ZERO;
   }

   /* Copy the number to be converted.*/
   /*hdudispbbinascii-BinAscii-DB-LLR-005*/
   temp_bp = (T_CHAR*)(&number);
   while(ZERO != size)
   {
      *temp_bp    = *byte_ptr;
      temp_bp  += ONE;
      byte_ptr    += ONE;
      size = (T_SHORT)(size - (T_SHORT)ONE);
   }

   /* Perform raw binary to ascii conversion.*/
   /*hdudispbbinascii-BinAscii-DB-LLR-006*/
   if(ZERO != negative)
   {
      number = (-number);
   }
   else
   {
      ;
   }
   /*hdudispbbinascii-BinAscii-DB-LLR-007*/
   first_char = buffer+FIFTEEN;

   /*hdudispbbinascii-BinAscii-DB-LLR-008*/
   last_char = BinAsciiConv ((T_ULONG)number,first_char);

   /* Insert the decimal point if needed.*/
   /*hdudispbbinascii-BinAscii-DB-LLR-009*/
   decimals       = (format & D_M) >> D_P;

   /*hdudispbbinascii-BinAscii-DB-LLR-010*/
   if (decimals != ZERO)
   {
      for (counter = decimals, byte_ptr=last_char - ONE ; counter>(T_UINT8)ZERO; counter--)
      {
         *(byte_ptr+ONE) = *(byte_ptr);   /* Shift a digit right.*/
         byte_ptr -= ONE;                 /* Step to the next digit.*/
         if(byte_ptr < first_char)        /* If past the first, pad '0'*/
         {
            *(byte_ptr) = '0';
         }
         else
         {
            ;
         }
      }

      /* If past the first, update first. */
      if(byte_ptr < first_char)
         {
            first_char = byte_ptr;
         }
      else
         {
            ;
         }
      *(byte_ptr+ONE) = '.';                 /* Put the decimal in.*/
      last_char += ONE;                      /* Last char moved one right.*/
      *last_char = DELIMITER;                /* Delimiter moved one right.*/
   }
   else
   {
      ;
   }

   /*hdudispbbinascii-BinAscii-DB-LLR-011*/
   /* If the number is negative.*/
   if (ZERO != negative)
   {
      --first_char;        /* First char moved one right.*/
      sign = '-';          /* Set the sign character.*/
   }
   /* Else if format calls for a plus sign.*/
   /*hdudispbbinascii-BinAscii-DB-LLR-012*/
   else if (ZERO != (format & PUT_PLUS))
   {
      --first_char;        /* First char moved one right*/
      sign = '+';          /* Set the sign character.*/
   }
   /* Else set the sign to null.*/
   /*hdudispbbinascii-BinAscii-DB-LLR-012*/
   else
   {
      sign = DELIMITER;
   }

   /* Extract the field width from the format.*/
   /*hdudispbbinascii-BinAscii-DB-LLR-013*/
   field_width = (format & W_M) >> W_P;

   /* Counter = requested fw - required fw.*/
   /*hdudispbbinascii-BinAscii-DB-LLR-014*/
   counter = (T_SHORT) (field_width - (last_char - first_char));

   /* If the conversion will not fit in the requested field.*/
   /*hdudispbbinascii-BinAscii-DB-LLR-015*/
   if (counter < (T_UINT8)ZERO)
   {
      /* Trivial case of 0 field width.*/
      if (ZERO == field_width )
      {
         *dest = HEX_ZERO;
         return (dest);
      }
      else
      {
         ; /* Do nothing */
      }
      /* Point to last char that will fit in field width.*/
      first_char = last_char - field_width;

      /* If a sign is required, step on left most with sign.*/
      if (ZERO != sign)
      {
         *(first_char) = sign;
      }
      else
      {
         ; /* Do nothing */
      }

      /* Replace all ['0'..'9'] with '?' to indicate overflow. */
      byte_ptr = first_char;
      while (byte_ptr < last_char)
      {
         if (ZERO != (IS_DIGIT (*byte_ptr++)))
         {
            *(byte_ptr - ONE) = '?';
         }
         else
         {
            ; /* Do nothing */
         }
      }
   }

   /* Else the conversion will fit.*/
   /*hdudispbbinascii-BinAscii-DB-LLR-016*/
   else
   {
      sign_pt = first_char;                  /* Next to number if LZB.*/
      fill_char = SPACE;                       /* Default leading zero blank.*/
      first_char = first_char - counter;     /* Include full field width.     */

      /* If leading zeros are not to be blanked.*/
      if (ZERO != (format & NOLZB))
      {
         fill_char = CHAR0;                      /* Set to plug '0', not ' '.*/
         sign_pt = first_char;                 /* If no LZB, sign at far left.*/
      }
      else
      {
         ; /* Do nothing */
      }

      byte_ptr = first_char;                   /* Set temp to first char.*/

      /* If there is a sign, one more byte will need to be filled.*/
      if (sign != ZERO)
      {
         counter=(T_SHORT)(counter + (T_SHORT)ONE);
      }
      else
      {
         ; /* Do nothing */
      }

      /* Prefix the conversion with ' ' or '0'*/
      while (counter > (T_UINT8)ZERO)
      {
         *(byte_ptr++) = fill_char;
         counter =(T_SHORT)(counter - (T_SHORT)ONE);
      }

      /* If a sign is needed, place the sign.*/
      if (sign != ZERO)
      {
         *sign_pt = sign;
      }
      else
      {
         ; /* Do nothing */
      }
   }

   flash_it = ZERO;
   /* Assume no flash.*/

  /*hdudispbbinascii-BinAscii-DB-LLR-017*/
   if (ZERO !=(format & FLASHIT))
   {
      flash_it = ONEHUNDRED_TWENTY_EIGHT;/* If flash is needed, set TPH.*/
   }
   else
   {
      ; /* Do nothing */
   }


   /* While more characters in the field. */
   /*hdudispbbinascii-BinAscii-DB-LLR-018*/
   while (field_width >= (T_UINT8)ONE)
   {
      /* If flashing needed.*/
      if(ZERO != flash_it)
      {
         /* If the character is a digit.*/
         if (IS_DIGIT (*first_char))
         {
            /* Set text parity high.*/
            *first_char |= flash_it;
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
      /* Transfer the byte to the destination.*/
      *(dest++) = *(first_char++);

      /* Dec the number of characters to transfer.*/
      field_width = (T_SHORT)(field_width -(T_SHORT)ONE);
   }
   /* Return a pointer to the delimiter.*/
   /*hdudispbbinascii-BinAscii-DB-LLR-019*/
   return (dest - ONE);
}
