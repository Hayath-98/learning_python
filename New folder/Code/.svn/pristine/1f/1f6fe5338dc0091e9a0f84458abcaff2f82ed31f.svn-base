/*
 ******************************************************************************
 * License Information  :  Howell Instruments, Inc.                           *
 *                         "Licensed software and All rights reserved".       *
 ******************************************************************************
 *  File                : hdudispfpbita.s
 *
 *  Description         : This file contains routines for PBIT test.
 *
 *  Compiler            : GNU gcc(GNU Tools for ARM Embedded Processors) version 5.4.1 20160919
 *
 *  Compiler options    : As per section 10.3.2 of Software Development Plan (HDU-001-002).
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
 *     1.2            Divya G P        10-Oct-2017             100064
 *
 * Additional References : None
 *
 ******************************************************************************/

.cpu cortex-m7
.syntax unified /* unified Thumb assembly syntax. */
.thumb          /* The start of a Thumb mode function for ARM-Thumb  */
.text

   .equ CONST_CARRY_FLAG,     0x20000000
   .equ CONST_ZERO_FLAG,      0x60000000
   .equ CONST_OVERFLOW_FLAG,  0x90000000
   .equ CONST_PATTERN,        0x7FFFFFFF
   .equ CONST_HEX_ONE,        0x01
   .equ CONST_ONE,            0x1
   .equ CONST_TWO,            0x2
   .equ CONST_THREE,          0x3
   .equ CONST_FOUR,           0x4
   .equ CONST_FIVE,           0x5
   .equ CONST_SIX,            0x6
   .equ CONST_ELEVEN,         0xB
   .equ CONST_SIXTEEN,        0x10
   .equ CONST_SEVENTEEN,      0x11


    .global AluTest

    .extern Proc_test_res

/*
 * Function                : AluTest
 *
 * Description             : This function performs the arithmetical and logical operations
 *                           on registers.
 *
 * Formal parameter(s)     : None
 *
 * Return Value            : None
 *
 * Assumption              : None
 *
 */
 
.thumb_func
.align(4)
AluTest:

/*hdudispfpbita-AluTest-DB-LLR-001*/
/* addition operation*/

   MOV     R1, CONST_SIX
   MOV     R2, CONST_FIVE
   ADD     R2, R1                         /* R2 = R1 + R2  */
   CMP     R2, CONST_ELEVEN           /* R2 = 0xB      */
   BEQ     carry_flag
   BX      LR

/* status of the carry flag */
carry_flag:
   /*hdudispfpbita-AluTest-DB-LLR-002*/
   MOVS     R1, CONST_SIX
   MOVS     R2, CONST_FIVE
   ADD      R2, R1
   MRS      R4,APSR
   CMP      R4, CONST_CARRY_FLAG
   BEQ     zero_flag
   BX       LR

/*status of the overflow flag */
overflow_flag:

   /*hdudispfpbita-AluTest-DB-LLR-004*/
   MOVS     R1, CONST_PATTERN
   MOVS     R2, CONST_PATTERN
   ADDS      R2, R1
   MRS      R4,APSR
   CMP      R4, CONST_OVERFLOW_FLAG
   BEQ      subtract
   BX       LR
    
 /* status of the zero flag */   
zero_flag:
   /*hdudispfpbita-AluTest-DB-LLR-003*/
   MOVS     R1, CONST_SIX
   MOVS     R2, CONST_FIVE
   ADD      R2, R1
   CMP      R2, CONST_ELEVEN
   MRS      R4,APSR
   CMP      R4, CONST_ZERO_FLAG
   BEQ      overflow_flag
   BX       LR


/*subtract operation on registers(R1,R2) */
subtract:

   /*hdudispfpbita-AluTest-DB-LLR-005*/
   MOV     R1, CONST_SIX
   MOV     R2, CONST_FIVE
   SUB     R1, R2                     /*  R1 = R1 - R2=6-5=1  */
   CMP     R1, CONST_ONE            /*  R1 = 1-1 =0     */
   BEQ     multiply
   BX      LR

/*multiply operation on registers(R1,R2) */
multiply:

   /*hdudispfpbita-AluTest-DB-LLR-006*/
   MOV     R1, CONST_THREE
   MOV     R2, CONST_TWO
   MUL     R1, R2               /*  R2 = R1*R2  */
   CMP     R1, CONST_SIX
   BEQ     division
   BX      LR
    
/*division operation on registers(R1,R2) */
division:

   /*hdudispfpbita-AluTest-DB-LLR-007*/
   MOV     R1, CONST_FOUR
   MOV     R2, CONST_TWO
   UDIV    R1, R2
   CMP     R1, CONST_TWO
   BEQ     logicaland
   BX      LR

/*logical AND operation on registers(R1,R2) */
logicaland:

   /*hdudispfpbita-AluTest-DB-LLR-008*/
   MOV     R1, CONST_HEX_ONE
   MOV     R2, CONST_SEVENTEEN
   AND     R3, R1, R2           /* R3 = R1&&R2   */
   CMP     R3, CONST_ONE
   BEQ     logicalor
   BX      LR

/*logical OR operation on registers(R1,R2)*/

logicalor:

   /*hdudispfpbita-AluTest-DB-LLR-009*/
   MOV     R1, CONST_SIXTEEN
   MOV     R2, CONST_HEX_ONE
   ORR     R3, R1,R2            /* R3 = R1||R2   */
   CMP     R3, CONST_SEVENTEEN
   BEQ     exlusiveor
   BX      LR

/*logical XOR operation on registers(R1,R2) */
exlusiveor:


   /*hdudispfpbita-AluTest-DB-LLR-010*/
   MOV     R1, CONST_SEVENTEEN
   MOV     R2, CONST_HEX_ONE
   EOR     R3, R1, R2      /* R3 = R1^R2   */
   CMP     R3, CONST_SIXTEEN
   BEQ     Testresult
   BX      LR

/* Test result */
Testresult:
   /*hdudispfpbita-AluTest-DB-LLR-011*/
   MOV     R4, CONST_ONE
   LDR     R2, =Proc_test_res
   STRB    R4, [R2]
   BX      LR
   .end
