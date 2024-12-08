/*
 ******************************************************************************
 * License Information  :  Howell Instruments, Inc.                           *
 *                         "Licensed software and All rights reserved".       *
 ******************************************************************************
 *  File                : hdudispfcbit.c
 *
 *  Description         : This file contains routines for CBIT test.
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
 *     1.5            Shruthi M N      04-Nov-2017             100116
 *     1.6            Vinay H          23-Mar-2018             100196
 *
 * Additional References : None
 *
 ******************************************************************************
 */

#include "hdudispfdemo.h"     /* Contains prototypes of hdudispfdemo */
#include "hdudispfapp.h"       /* routines for all graph */
#include "hdudispfcbit.h"      /* contains prototypes for CBIT test. */
#include "hdudispfinit.h"      /* Contains functions prototypes of initialization function.*/
#include "hdudispfoscpu.h"    /* OS function declarations */
#include "hdudispfpoller.h"    /* Engine Information System poller. */
#include "hdudispfresource.h"  /* provides central location to use On Chip Peripherals*/
#include "hdudispfrterror.h"     /*provides stub routine for run time errors.*/
#include "hdudispfucos.h"      /* uC/OS routines for the real-time kernel */
#include "hdudispfa825comm.h"  /* Routines for arinc 825 communication */
#include "hdudispfpara.h"      /* prototype for builds faults, message and system information */

#define GET_80PERC_STACK(x)  ((T_UINT32)(80*x)/100)

T_OS_STK Cbit_task_stack[CBIT_TASK_STK_SIZE] =
{
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL
};

T_OS_EVENT *Sem_cbit_task = NULL;

/**********************************************************************************/
/*                          Local Function Prototype                              */
/**********************************************************************************/
static void CbitTask(void *pData);
static void StackTest(T_UINT32 *buffer, T_UINT32 length);
/**********************************************************************************/
/*                           Function Definition                                  */
/**********************************************************************************/

/*
 * Function                : StackTest
 *
 * Description             : The function performs Stack Test.
 *                           Note : Stack test should be done after the 80% of the stack.
 *
 *
 * Formal parameter(s)     : T_UINT32 *buffer IN- Pointer to the top-of-stack address
 *                           T_UINT32 length IN - length of stack.
 *
 * Return Value            : None
 *
 * Assumption              : None
 *
 */
static void StackTest(T_UINT32 *buffer, T_UINT32 length)
{
   T_UINT32 index = ZERO;

   T_UINT32 size =  GET_80PERC_STACK(length);

   /* hdudispfcbit-StackTest-DB-LLR-001 */
   /*stack overflow condition check for the last 20 percent of the stack*/

   for(index = ZERO; index<=size; index++)
   {
      buffer--;
   }
   for(index = ZERO; index<=TEN; index++)
   {
      if( STK_VAL == *buffer)
      {
         ;
      }
      else
      {
         /* Updated as per PR 100083 */
       /* Updated as per PR100116 */
          U16_message_words[1] |= 1;
         while(1)
         {
            ;
         }
      }
      buffer--;
   }
}

/*
 *
 * Function                : CbitTask
 *
 * Description             : The function initiate the CBIT.
 *
 * Formal parameter(s)     : void *p_data - Not used
 *
 * Return Value            : None
 *
 * Assumption              : None
 *
 */

static void CbitTask(void *p_data)
{
   T_UINT8 u8_err = ZERO;

   p_data =(T_UINT8 *)p_data + ZERO;

   /* hdudispfcbit-CbitTask-DB-LLR-001 */
   while (TRUE)
   {
      OsSemPend(Sem_cbit_task, 0, &u8_err);
      StackTest(&Cbit_task_stack[CBIT_TASK_STK_SIZE], CBIT_TASK_STK_SIZE);
      StackTest(&Os_task_idle_stk[OS_IDLE_TASK_STK_SIZE], OS_IDLE_TASK_STK_SIZE);
      StackTest(&Init_task_stk[INIT_TASK_STK_SIZE],INIT_TASK_STK_SIZE);
      StackTest(&App_task_stk[APP_TASK_STK_SIZE],APP_TASK_STK_SIZE);
      StackTest(&Poller_task_stk[POLLER_TASK_STK_SIZE],POLLER_TASK_STK_SIZE);
      StackTest(&A825_comm1_task_stk[A825COMM_TASK_STK_SIZE],A825COMM_TASK_STK_SIZE);
      StackTest(&A825_comm2_task_stk[A825COMM_TASK_STK_SIZE],A825COMM_TASK_STK_SIZE);
      StackTest(&Demo_task_stk[DEMO_TASK_STK_SIZE],DEMO_TASK_STK_SIZE);

   }
}

/*
 *
 * Function                : CbitSignalTask
 *
 * Description             : The function signals the CBIT task
 *
 * Formal parameter(s)     : None
 *
 * Return Value            : None
 *
 * Assumption              : None
 *
 */
void CbitSignalTask(void)
{
   static T_UINT16 u16tickcntr = 0;

   /* hdudispfcbit-CbitSignalTask-DB-LLR-001 */
   if (++u16tickcntr >= CBIT_TASK_TICKS)
   {
      u16tickcntr = 0;
      OsSemPost(Sem_cbit_task);
   }
}

/*
 * Function                : CbitInit
 *
 * Description             : The function initializes stack and creates Task to implement CBIT.
 *
 * Formal parameter(s)     : None
 *
 * Return Value            : None
 *
 * Assumption              : None
 *
 */

void CbitInit(void)
{
   T_CHAR file_name[] = __FILE__;
   T_CHAR error_msg[16]="OS KERNEL ERROR";
   /* hdudispfcbit-CbitInit-DB-LLR-001 */
   Sem_cbit_task = OsSemCreate(ZERO);

   /* hdudispfcbit-CbitInit-DB-LLR-002 */
   if((T_OS_EVENT *)NULL == Sem_cbit_task)
   {
      RterrWidget((T_CHAR *)&file_name, __LINE__, &error_msg[0]);
   }
   else
   {
      ;
   }

   /* hdudispfcbit-CbitInit-DB-LLR-003 */
   /* create CBIT Task as the first task to run of RTOS */
   if( OS_NO_ERR != OsTaskCreate(CbitTask, NULL, &Cbit_task_stack[CBIT_TASK_STK_SIZE],
         CBIT_TASK_PRIO))
   {
      RterrWidget((T_CHAR *)&file_name, __LINE__, &error_msg[0]);
   }
   else
   {
      ;
   }
}
