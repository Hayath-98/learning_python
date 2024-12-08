/*
 ******************************************************************************
 * License Information  :  Howell Instruments, Inc.                           *
 *                         "Licensed Software" and "All rights reserved".     *
 ******************************************************************************
 *  File                : hdudispfpoller.c
 *
 *  Description         : This file initialises, creates and schedules the poller task.
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
 *      1.1          Vinay H         24-Jul-2017             100064
 *      1.2          Divya G P       09-Oct-2017             100064
 *      1.3          Shruthi M N     13-Oct-2017             100083
 *      1.4          Shruthi M N     30-Oct-2017             100104
 *      1.5          Divya G P       02-Nov-2017             100156
 *      1.6          Rona B S        05-Jul-2020             100259
 *      1.7          Dhanalakshmi     20-Mar-2021            100331
 *      1.8          Dhanalakshmi     20-Mar-2021            100331
 *      1.9          Dhanalakshmi     13-May-2021            100350
 *
 * Additional References : None
 *
 ******************************************************************************
 */
#include "hdudispfpbs.h"/* Consistency check.  */
#include "hdudispfpoller.h" /*declarations for engine information system poller.*/
#include "hdudispfpwm.h"/*maintains the pulse width modulation channels*/
#include "hdudispfresource.h"/* provides resources */
#include "hdudispfstandard.h"/* provides standard definitions */
#include "hdudispfstmadc.h" /*declares the internal ADC and polls for conversion*/
#include "hdudispftimer.h" /* Defines the timer functionalities */
#include "hdudispfucos.h" /* provides ucos functionalities */
#include "hdulibbasictypes.h" /* provides basic datatypes */
#include "hdudispfoscpu.h"    /* OS function declarations */
#include "hdudispfcbit.h"     /* contains prototypes for CBIT test. */
#include "hdudispflmsscu.h"  /* SCU rtd processing and error codes  */

/* Updated as per PR100083 */
#include "hdudispfrtd.h"/*defines structure, enum of A825 incomming data.*/

/* Allocate stack for the poller task.          */
T_OS_EVENT *Sem_poller_task = {0};

T_OS_STK Poller_task_stk[POLLER_TASK_STK_SIZE] = {0};

/*Static functions*/
static void PollerTask(void *p_data);

/*
 *
 * Function                : PollerTask
 *
 * Description             : This task is signaled from the time base interrupt
 *                           to check push buttons, back light control and internal ADC
 *
 * Formal parameter(s)     : void *p_data - INOUT Pointer to the Task data
 *
 * Return Value            : None
 *
 * Assumption              : None
 *
 */

static void PollerTask(void *p_data)
{
   T_UINT8  u8_err = 0;

   /*hdudispfpoller-PollerTask-DB-LLR-001*/
   p_data = ((T_UINT8 *)p_data) + ZERO;

   /*hdudispfpoller-PollerTask-DB-LLR-002*/
   PwmInit();        /* Initialize the back light control.*/
   /*hdudispfpoller-PollerTask-DB-LLR-003*/
   PbsInit();        /* Initialize the PBS routines.*/
   /*hdudispfpoller-PollerTask-DB-LLR-004*/
   StmadcInit();     /* Initialize the internal ADC.*/

   /*hdudispfpoller-PollerTask-DB-LLR-005*/
   while (TRUE)
   {
      /* Wait for a message to arrive. */
      OsSemPend(Sem_poller_task, ZERO, &u8_err);
      TimerDriver();

     /* Updated as per PR100083 */
      RTDWatchdog();
      /* updated as per ECM70B */
      ScuRTDWatchdog();

      PbsDriver();
      StmadcDriver();
      PwmBackLightDriver();
   }
}

/*
 *
 * Function                : PollerSignalTask
 *
 * Description             : This function unlocks poller task semaphore
 *
 * Formal parameter(s)     : None
 *
 * Return Value            : None
 *
 * Assumption              : None
 *
 */

void PollerSignalTask(void)
{
   static T_UINT16 u16_tick_cntr = 0;

   /*hdudispfpoller-PollerSignalTask-DB-LLR-001*/
   u16_tick_cntr =(T_UINT16)(u16_tick_cntr + ONE);

   if (u16_tick_cntr >= POLLER_TASK_TICKS)
   {
      /*hdudispfpoller-PollerSignalTask-DB-LLR-002*/
      u16_tick_cntr = ZERO;
      OsSemPost(Sem_poller_task);
   }
   else
   {
      ;/*Do nothing*/
   }
}


/*
 *
 * Function                : PollerInit
 *
 * Description             : This routine is scheduled once per mSec to debounce the
 *                                         discrete inputs.
 *
 * Formal parameter(s)     : None
 *
 * Return Value            : None
 *
 * Assumption              : None
 *
 */

void PollerInit(void)
{
   T_UINT16 u16_ctr = 0;

   /*hdudispfpoller-PollerInit-DB-LLR-001*/
   /* Initialize semaphore for poller task */
   Sem_poller_task = OsSemCreate(ZERO);

   /*hdudispfpoller-PollerInit-DB-LLR-002*/
   /* Initialize the stack for run time checks. */
   for(u16_ctr=0; u16_ctr<POLLER_TASK_STK_SIZE; u16_ctr++)
   {
      Poller_task_stk[u16_ctr] = STK_VAL;
   }
   /*hdudispfpoller-PollerInit-DB-LLR-003*/
   /* create InitTask as the first task to run of RTOS */
   OsTaskCreate(PollerTask, NULL, &Poller_task_stk[POLLER_TASK_STK_SIZE], POLLER_TASK_PRIO);
}


