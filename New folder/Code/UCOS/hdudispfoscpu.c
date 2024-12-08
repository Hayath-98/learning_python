/*
 ******************************************************************************
 * License Information  :  Howell Instruments, Inc.                           *
 *                         "Licensed Software" and "All rights reserved".     *
 ******************************************************************************
 *  File                : hdudispfoscpu.c
 *
 *  Description         : This module defines the OS Task creation function.
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
 * <Version No.>      <Author>          <Date>         <Problem Report No.>
 *
 *      1.1           Vinay H         14-Sep-2017             100064
 *
 * Additional References : None
 *
 ******************************************************************************
 */

#include "hdudispfoscpu.h"               /* OS function declarations */

#include "hdudispfucos.h"                 /* uC/OS routines for the real-time kernel */
#include "hdulibbasictypes.h"           /* Contains basic data types */

T_UINT32 U32_critical_sr = 0;

#define FPCCR           0x80000000UL      /* Floating-point context control Register */
#define FPSCR           0x00000000UL      /* Floating-point status control Register  */
#define XPSR            0x01000000UL      /* Program status control Register  */
#define R14_LR          0xFFFFFFFEUL      /* Link Register  */
#define NO_OF_REM_REG   24U               /* Remaining registers saved on process stack*/


/*
 * Function                : OsTaskCreate
 *
 * Description             : This function creates OS Task
 *
 * Formal parameter(s)     : void (*p_task)(void *d_ptr) - IN  function pointer to the task
 *                           void *p_data              - IN  pointer to task parameters
 *                           void *pt_os               - OUT pointer to top of stack
 *                           T_UINT8 u8_prio           - IN  task priority
 *
 * Return Value            : T_UINT8  - returns task creation status
 *                           OS_PRIO_EXIST    - Task already exists
 *                           OS_NO_ERR        - Task created successfully
 *                           OS_NO_MORE_TCB   - No more free TCB in the TCB list
 *
 * Assumption              : None
 *
 */

T_UINT8 OsTaskCreate(void (*p_task)(void *d_ptr),void *p_data, void *pt_os,
                     T_UINT8 u8_prio)
{

    /* hdudispfoscpu-OsTaskCreate-DB-LLR-001 */
   T_UINT32 *pu32_stk = ZERO;
   T_UINT8 u8_err = ZERO;

   /* hdudispfoscpu-OsTaskCreate-DB-LLR-002 */
   OS_ENTER_CRITICAL();

   /* Avoid creating task if already exist */
   if (ZERO == Os_tcb_prio_tbl[u8_prio])
   {
   /* hdudispfoscpu-OsTaskCreate-DB-LLR-003 */
      OS_EXIT_CRITICAL();

      /* Top of stack pointer */
      pu32_stk = pt_os;

      /* Registers stacked as if auto-saved on exception */
      pu32_stk = pu32_stk - 1;
      *(pu32_stk) = (T_UINT32)FPCCR;        /* FPCCR */

      pu32_stk = pu32_stk - 1;
      *(pu32_stk) = (T_UINT32)FPSCR;        /* FPSCR */

      pu32_stk -= SIXTEEN;                  /* S15 to S0 */
      pu32_stk = pu32_stk - 1;
      *(pu32_stk) = (T_UINT32)XPSR;         /* xPSR */

      pu32_stk = pu32_stk - 1;
      *(pu32_stk) = (T_UINT32)p_task;       /* Entry Point */

      pu32_stk = pu32_stk - 1;
      *(pu32_stk) = (T_UINT32)R14_LR;       /* R14 (LR) */
      pu32_stk -= FOUR;                     /* R12, R3 to R1 */

      pu32_stk = pu32_stk - 1;
      *(pu32_stk)  = (T_UINT32)p_data;      /* R0 */

      /* Remaining registers saved on process stack */
      pu32_stk -= NO_OF_REM_REG;              /* R4 to R11, S16 to S31 */

      /* Get and initialize a TCB */
      u8_err= OsTcbInit(u8_prio, (void *)pu32_stk);

      if (OS_NO_ERR == u8_err)
      {
         if (TRUE == Os_running)
         {
            /* Find highest priority task if multitasking has started */
            OsSched();
         }
         else
         {
            ; /* Do nothing */
         }
      }
      else
      {
         ;/*Do nothing*/
      }

      return (u8_err);
    }


   else
   {
     /* hdudispfoscpu-OsTaskCreate-DB-LLR-004 */
     OS_EXIT_CRITICAL();

      /*
       * return with OS_PRIO_EXIST if the task priority to be created
       * already exists
       */
     return (OS_PRIO_EXIST);
   }
}

