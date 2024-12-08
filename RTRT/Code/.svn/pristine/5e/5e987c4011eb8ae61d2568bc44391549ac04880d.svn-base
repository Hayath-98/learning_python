/*
 ******************************************************************************
 * License Information  :  Howell Instruments, Inc.                           *
 *                         "Licensed software and All rights reserved".       *
 ******************************************************************************
 *  File                : hdudispfpbit.h
 *
 *  Description         : This file contains prototypes for PBIT test.
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
 *     1.2            Divya G P        09-Oct-2017             100064
 *     1.3            Shruthi M N      13-Oct-2017             100083
 *     1.4            Shruthi M N      30-Oct-2017             100104
 *     1.5            Vinay H          23-Mar-2018             100196
 *     1.6            Gururaj C        21-Jun-2020             100259
 *     1.7            Rona B S         24-Jul-2020             100259
 *
 * Additional References : None
 *
 ******************************************************************************
 */

#ifndef _HDUDISPFPBIT_H_
#define _HDUDISPFPBIT_H_

#include "hdulibbasictypes.h"  /*provides basic data types.*/
#include "hdudispfpara.h"  /* prototype for builds faults, message and system information  */
#define RAM_SIZE                     100U
#define SDRAM_SIZE                   10U

/*Macros used for SRAM test*/
#define CHECK_5A5A                   0x5A5AU
#define CHECK_A5A5                   0xA5A5U

typedef enum
{
   FAILED = 0,
   PASSED  = !FAILED
} T_RESULT;
/*  structure defining hardware status */
typedef struct
{
   T_BOOL ram_test_fail;                  /* XRAM Read or Write fail */
   T_BOOL stack_test_fail;                /* Stack Read or Write fail */
   T_BOOL alu_test_fail;                  /* ALU Read or Write fail */
   T_BOOL sdram_test_fail;
   T_BOOL pdi_test_fail;

} T_BIT_ERROR;

typedef struct
{
   T_UINT32 u32LoadAddr;   /* Where the file will be loaded.*/
   T_UINT32 u32LoadSize;   /* Size of the load image. *** CAUTION  7 Meg Max.*/

}  T_SPDIFILE;

#define PDI_ADDR 0x63220000 
#define PDI_SIZE 0xDE0000 

/******** Global variables ********/

extern T_UINT32 Proc_test_res;
extern T_UINT16 Sram_buffer_check[RAM_SIZE];
extern T_UINT16 Pbit_test_result;
extern T_UINT16 Sdram_buffer_check[SDRAM_SIZE];

/******** Function Prototypes ********/

extern void RamTest(void);
extern void ProcessorTest(void);
extern void SDRamTest(void);
extern void PdiIntegrityCheck(void);

extern void PbitCheck(void);
extern void AluTest(void);
extern void CrcPages(T_EPAGE_NUM page_count);

#endif
