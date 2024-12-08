/*
 ******************************************************************************
 * License Information  :  Howell Instruments, Inc.                           *
 *                         "Licensed software and All rights reserved".       *
 ******************************************************************************
 *  File                : hdudispfpbit.c
 *
 *  Description         : This file contains routines for PBIT test.
 *
 *  Compiler            : GNU gcc(GNU Tools for ARM Embedded Processors) version 5.4.1 20160919
 *
 *  Compiler options    : As per section 10.3.1 of Software Development Plan (HDU-001-002).
 *
 *  Pragma              : None.
 *
 *  H/W platform        : ARM Cortex-M7 (STM32F767)
 *
 *  Portability         : None
 *
 *  Author(s)           : Rajalakshmi S
 *
 *  Version History     :
 * <Version No.>      <Author>        <Date>         <Problem Report No.>
 *     1.1            Rajalakshmi S    08-Sep-2017             100064
 *     1.2            Divya G P        09-oct-2017             100064
 *     1.3             Rona B.S        11-Oct-2017             100064
 *     1.4            Shruthi M N      13-Oct-2017             100083,100087
 *     1.5            Shruthi M N      30-Oct-2017             100104
 *     1.6            Divya G P        04-Nov-2017             100156
 *     1.7            Shruthi M N      07-Nov-2017             100161
 *     1.8            Shruthi M N      08-Nov-2017             100164
 *     1.9            Rona B.S         23-Mar-2018             100196
 *     1.10           Vinay H          28-Mar-2018             100196
 *     1.11           Rona B.S         05-Apr-2018             100205
 *     1.12           Rona B.S         16-Apr-2018             100211
 *     1.13           Rona B.S         18-Apr-2018             100216
 *     1.14           Dhanalakshmi D   24-Apr-2020             100241
 *     1.15           Dhanalakshmi D   15-May-2020             100247
 *     1.16           Gururaj C        21-Jun-2020             100259
 *     1.17           Rona B S         29-Jun-2020             100259
 *     1.18           Dhanalakshmi     12-Sep-2020             100276
 *     1.19           Rona B S         28-Sep-2020             100284 
 *
 * Additional References : None
 *
 ******************************************************************************
 */
#include "hdudispfpbit.h"        /* contains prototypes for PBIT test. */
#include "hdulibbasictypes.h"  /* provides basic data types.*/
#include "hdudispfpara.h"        /* prototype for builds faults, message and system information */
#include "hdudispfpolygon2.h"    /* contains routines for ploygons configuration */
#include "hdudispfcrc.h" /* contains the common defines and functions prototypes for CRC*/
#include "hdudispfpdidata.h" /* provides pdi declarations */
#include "hdudispfresource.h"  /* provides central location to use On Chip Peripherals*/
#include "hdudispfmenu.h"            /* contains prototype for menu module*/
#include "hdudispfpanel.h"			/* contains prototype for Panel module*/

/* SRAM buffer */
T_UINT16 Sram_buffer_check[RAM_SIZE] __attribute__ ((section(".ram_test")))= {ZERO};

/* SRAM buffer */
T_UINT16 Sdram_buffer_check[SDRAM_SIZE] __attribute__ ((section(".sdram_test")))= {ZERO};

/* CPU test result */
T_UINT32 Proc_test_res = FAILED;
T_UINT16 Pbit_test_result =0;
T_EPAGE_NUM Page_num_check = EPAGE0;
/* Updated as per PR 100083 */
#define BIT_SHIFT_BY_16       16
#define BIT_SHIFT_BY_8        8
#define BIT_SHIFT_BY_8192     8192
#define BIT_SHIFT_BY_64       64
#define BMP_START_ADDR        0x60000000
#define BITMAP_SECTOR_OFFSET  0x280000


/*Application information.*/
T_SPDIFILE Pdi_file_code =
{
      PDI_ADDR,
      PDI_SIZE
};

/*
 * Function                : RamTest
 *
 * Description             : This function performs the SRAM test.
 *
 * Formal parameter(s)     : None
 *
 * Return Value            : None
 *
 * Assumption              : None
 *
 */
void RamTest()
{
   T_UINT16 sram_buffer = ZERO;

   /* hdudispfpbit-RamTest-DB-LLR-001 */
   for(sram_buffer = ZERO; sram_buffer < RAM_SIZE; sram_buffer++)
   {
      Sram_buffer_check[sram_buffer] = CHECK_5A5A;

      if (CHECK_5A5A == Sram_buffer_check[sram_buffer] )
      {
         Sram_buffer_check[sram_buffer] = CHECK_A5A5;
         if (CHECK_A5A5 != Sram_buffer_check[sram_buffer] )
         {
            Pbit_test_result=1;
            /* Updated as per PR 100083 */
            U16_message_words[0] |= BIT_SHIFT_BY_8192;
            return ;
         }
         else
         {
            ;
         }
      }
      else
      {
         Pbit_test_result=1;
         /* Updated as per PR 100083 */
         U16_message_words[0] |= BIT_SHIFT_BY_8192;
         return ;
      }
   }
}

/*
 * Function                : ProcessorTest
 *
 * Description             : This function performs the CPU test.
 *
 * Formal parameter(s)     : None
 *
 * Return Value            : None
 *
 * Assumption              : None
 *
 */

void ProcessorTest()
{
   /* hdudispfpbit-ProcessorTest-DB-LLR-001 */
   Proc_test_res=FAILED;

    AluTest();

   if( FAILED == Proc_test_res)
   {
    /* Updated as per PR 100083 */
      U16_message_words[0] |= BIT_SHIFT_BY_16;
      Pbit_test_result=1;
   }
   else
   {
      /* Do nothing */
      ;
   }
}

/*
 * Function                : SDRamTest
 *
 * Description             : This function performs the SDRAM test.
 *
 * Formal parameter(s)     : None
 *
 * Return Value            : None
 *
 * Assumption              : None
 *
 */
void SDRamTest()
{
   T_UINT16 sdram_buffer = ZERO;

   /* hdudispfpbit-SDRamTest-DB-LLR-001 */
   for(sdram_buffer = ZERO; sdram_buffer < SDRAM_SIZE; sdram_buffer++)
   {
      Sdram_buffer_check[sdram_buffer] = CHECK_5A5A;

      if (CHECK_5A5A == Sdram_buffer_check[sdram_buffer] )
      {
         Sdram_buffer_check[sdram_buffer] = CHECK_A5A5;
         if (CHECK_A5A5 != Sdram_buffer_check[sdram_buffer] )
         {
            Pbit_test_result=1;
            /* Updated as per PR 100083 */
            U16_message_words[0] |= BIT_SHIFT_BY_8;
            return ;
         }
         else
         {
            ;
         }
      }
      else
      {
         Pbit_test_result=1;
         /* Updated as per PR 100083 */
         U16_message_words[0] |= BIT_SHIFT_BY_8;
         return;
      }
   }
}

/*
 * Function                : PdiIntegrityCheck
 *
 * Description             : This function performs the PdiIntegrityCheck test.
 *
 * Formal parameter(s)     : None
 *
 * Return Value            : None
 *
 * Assumption              : None
 *
 */
void PdiIntegrityCheck()
{
   volatile T_UINT32 u32_crc_value = 0;
   T_UINT32    u32_flash_crc = 0;
   T_UINT32 *pu32_flash_crc = 0;

   /* hdudispfpbit-PdiIntegrityCheck-DB-LLR-001 */
   u32_crc_value=(T_UINT32)(CrcCalculate((T_UINT32 *)(Pdi_file_code.u32LoadAddr),
         (T_UINT32)(((Pdi_file_code.u32LoadSize)/(T_UINT32)4)-(T_UINT32)1)));

   /* hdudispfpbit-PdiIntegrityCheck-DB-LLR-002 */
   /*
    * CRC resides in the last 4 bytes in the last but 1 line of the binary and hence
    * to extract the CRC, following formula is used (address + size - 4) which gives the
    * starting address of the CRC.
    */
   pu32_flash_crc = (T_UINT32 *)((Pdi_file_code.u32LoadAddr) + (Pdi_file_code.u32LoadSize)- 4);

   u32_flash_crc = *pu32_flash_crc;

   /* hdudispfpbit-PdiIntegrityCheck-DB-LLR-003 */
   if(u32_crc_value != u32_flash_crc)
   {
      Pbit_test_result=1;
      /* Updated as per PR 100083 */
      U16_message_words[0] |= BIT_SHIFT_BY_64;
   }
   else
   {
      ;
   }
   /*hdudispfpbit-PdiIntegrityCheck-DB-LLR-004*/

   CrcPages(EPAGE19);
   Bitmap_crc_check_bit[EPAGE19]=TRUE;
}



/*
 * Function                : PbitCheck
 *
 * Description             : This function performs the Power-on Built in test.
 *
 * Formal parameter(s)     : None
 *
 * Return Value            : None
 *
 * Assumption              : None
 *
 */
void PbitCheck()
{
   /* hdudispfpbit-PbitCheck-DB-LLR-001 */
   ProcessorTest();
   RamTest();
   SDRamTest();
   PdiIntegrityCheck();

}


/*
 * Function                : CrcPages
 *
 * Description             : This function performs the CRC check for Bitmaps.
 *
 * Formal parameter(s)     : None
 *
 * Return Value            : None
 *
 * Assumption              : None
 *
 */
void CrcPages(T_EPAGE_NUM page_count)
{
	  T_UINT8 page_num=0xFF;
	  T_UINT32 u32_bmp_crc_value = 0;
	  T_UINT32    u32_flash_bmp_crc = 0;

	  /*hdudispfpbit-CrcPages-DB-LLR-001 */
	       page_num=*((T_UINT8 *)((page_count* SECTOR_SIZE + PAGE_NUM_BASE_ADDR)+TWO));
	      if(page_num < TWENTY)
	      {
	         u32_bmp_crc_value=(T_UINT32)(CrcCalculate((T_UINT32 *)(BMP_START_ADDR+
	               page_num*BITMAP_SECTOR_OFFSET),
	               (T_UINT32)((BITMAP_SECTOR_OFFSET/(T_UINT32)FOUR)-(T_UINT32)ONE)));

	         u32_flash_bmp_crc=*((T_UINT32 *)((BMP_START_ADDR+page_num*BITMAP_SECTOR_OFFSET)+
	               BITMAP_SECTOR_OFFSET-DEC_FOUR));

	          if(u32_bmp_crc_value != u32_flash_bmp_crc)
	           {
	           Pbit_test_result=ONE;
	           U16_message_words[1] |= THIRTY_TWO;
	           }
	           else
	           {
	            ;
	           }
	      }
	      else
	      {
	         ;
	      }

}

