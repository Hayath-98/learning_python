/*
 ******************************************************************************
 * License Information  :  Howell Instruments, Inc.                           *
 *                         "Licensed Software" and "All rights reserved".     *
 ******************************************************************************
 *  File                : hdudispfucos.c
 *
 *  Description         : This module contains implementation of uC/OS routines for
 *                        the real-time kernel.
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
 *      1.1           Vinay H       14-Sep-2017             100064
 *      1.2           Vinay H       10-Oct-2017             100064
 *      1.3          Shruthi M N    30-Oct-2017             100104
 *      1.4          Vinay H        09-Nov-2017             100164
 *
 * Additional References : None
 *
 ******************************************************************************
 */

#include "hdudispfucos.h"                 /* uC/OS routines for the real-time kernel */
#include "hdulibbasictypes.h"           /* Contains basic data types */
#include "hdudispfoscpu.h"               /* OS function declarations */

/*
 *CONSTANTS
 */

#define  OS_STAT_RDY       0x00U        /* Ready to run*/
#define  OS_STAT_SEM       0x01U        /* Pending on semaphore*/
#define  OS_STAT_SUSPEND   0x08U        /* Task is suspended*/
#define  TRUE               1U
#define  FALSE              0U
#define MAX_SEMAPHORE      65535U
#define MAX_RDY_LST        8
#define MAX_PRIO_TBL       64
#define STK_DEF_VAL   0xDEADDEADU

/*
 * MAPPING TABLE TO MAP BIT POSITION TO BIT MASK
 */

static const T_UBYTE Os_map_tbl[]   = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80};

T_UWORD     Os_ctx_sw_ctr    = 0;
T_OS_TCB  *Os_tcb_prio_tbl[64] = {(void *)0};
T_OS_TCB  *Os_tcb_high_rdy = (void *)0;
T_BOOLEAN   Os_running = FALSE;
T_UBYTE     Os_int_nesting = 0;
T_OS_TCB  *Os_tcb_cur = (void *)0;
volatile  T_ULONG  Os_idle_ctr = 0;

/*
 * PRIORITY RESOLUTION TABLE
 */

const T_UBYTE Os_un_map_tbl[] = {
    0, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    5, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    6, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    5, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    7, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    5, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    6, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    5, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0
};

/*
 * LOCAL VARIABLES
 */

static  T_OS_TCB     *Os_tcb_list = {0};        /* Pointer to doubly linked list of TCBs*/
static  T_UBYTE        Os_rdy_grp = 0;            /* Ready list group*/
static  T_UBYTE        Os_rdy_tbl[8] = {0};       /* Table of tasks which are ready to run*/
static  T_UBYTE        Os_lock_nesting = 0;       /* Multitasking lock nesting level*/
static  T_OS_TCB     *Os_tcb_free_list = {0};   /* Pointer to list of free TCBs*/
static  T_OS_EVENT   *Os_event_free_list = {0}; /* Pointer to list of free EVENT control blocks*/
static  T_ULONG        Os_time = 0;               /* Current value of system time (in ticks)*/

/* Variable used by 'OsIntExit' to prevent using locals */
static  T_UBYTE        Os_int_exit_y = 0;
T_OS_STK       Os_task_idle_stk[OS_IDLE_TASK_STK_SIZE] = {0};/* Idle task stack*/
static  T_OS_TCB     Os_tcb_tbl[OS_MAX_TASKS+1] = {0};     /* Table of TCBs*/

/* Table of EVENT control blocks*/
static  T_OS_EVENT   Os_event_tbl[OS_MAX_EVENTS] = {0};


/*
 * LOCAL FUNCTION PROTOTYPES
 */

static void OsTaskIdle(void *data);

/*
 * uC/OS INITIALIZATION
 */

/*
 * Function                :  OsInit
 *
 * Description             :  This function initializes the Os ready to run task list,
 *                            TCB priority table list, list of free TCBs, list of free Event
 *                            Control Blocks to default values. The function creates the
 *                            OsTaskIdle function
 *
 * Formal parameter(s)     :  None
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */

void OsInit(void)
{
    /*hdudispfucos-OsInit-DB-LLR-001*/
    T_UBYTE index     = ZERO;
    T_UINT16 u16_ctr = ZERO;
    Os_time         = ZERO;
    Os_tcb_high_rdy = (T_OS_TCB *)ZERO;
    Os_tcb_cur      = (T_OS_TCB *)ZERO;
    Os_tcb_list     = (T_OS_TCB *)ZERO;
    Os_int_nesting  = ZERO;
    Os_lock_nesting = ZERO;
    Os_running      = FALSE;
    Os_idle_ctr     = ZERO;
    Os_ctx_sw_ctr   = ZERO;
    Os_rdy_grp      = ZERO;

    /*hdudispfucos-OsInit-DB-LLR-001*/
    /* Clear the ready list*/
    for (index = ZERO; index < MAX_RDY_LST; index++)
    {
        Os_rdy_tbl[index] = ZERO;
    }

    /* Clear the priority table*/
    for (index = ZERO; index < MAX_PRIO_TBL; index++)
    {
        Os_tcb_prio_tbl[index] = (T_OS_TCB *)ZERO;
    }

    /* Init. list of free TCBs*/
    for (index = ZERO; index < OS_MAX_TASKS; index++)
    {
        Os_tcb_tbl[index].OSTCBNext = &Os_tcb_tbl[index+1];
    }

    /* Last T_OS_TCB is for OsTaskIdle()*/
    Os_tcb_tbl[OS_MAX_TASKS].OSTCBNext = (T_OS_TCB *)ZERO;
    Os_tcb_free_list                    = &Os_tcb_tbl[0];

     /* Init. list of free EVENT control blocks*/
    for (index = ZERO; index < (OS_MAX_EVENTS - ONE); index++)
    {
        Os_event_tbl[index].OSEventPtr = &Os_event_tbl[index+1];
    }

    Os_event_tbl[OS_MAX_EVENTS - 1].OSEventPtr = (T_OS_EVENT *)ZERO;
    Os_event_free_list                         = &Os_event_tbl[0];


    for(u16_ctr=0; u16_ctr<OS_IDLE_TASK_STK_SIZE; u16_ctr++)
   {
      Os_task_idle_stk[u16_ctr] = STK_DEF_VAL;
   }

    /*hdudispfucos-OsInit-DB-LLR-002*/
    OsTaskCreate(OsTaskIdle, (void *)ZERO,(void *)&Os_task_idle_stk[OS_IDLE_TASK_STK_SIZE],
                 OS_LOWEST_PRIO);
}

/*
 * Function                :  OsTaskIdle
 *
 * Description             :  This function is the Os Idle task to keep track of the CPU
 *                            idle time and reset the watch dog counter.
 *
 * Formal parameter(s)     :  void *data -IN pointer to data
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */

static void OsTaskIdle(void *data)
{
   /*hdudispfucos-OsTaskIdle-DB-LLR-002*/
   data = (T_UINT8*)data + ZERO;

   /*hdudispfucos-OsTaskIdle-DB-LLR-001*/
    while (TRUE)
    {
        OS_ENTER_CRITICAL();
        Os_idle_ctr++;
        OS_EXIT_CRITICAL();

    }
}

/*
 * Function                :  OsStart
 *
 * Description             :  This function starts the multitasking process, allowing
 *                            uC/OS to manage tasks that have been created.
 *
 * Formal parameter(s)     :  None
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */

void OsStart(void)
{
   T_UBYTE y_val = ZERO;
   T_UBYTE x_val = ZERO;
   T_UBYTE prio =  ZERO;

   y_val        = Os_un_map_tbl[Os_rdy_grp];

   /* Find highest priority's task priority number*/
   x_val        = Os_un_map_tbl[Os_rdy_tbl[y_val]];
   prio         = (T_UBYTE)((y_val << THREE) + x_val);

   /*hdudispfucos-OsStart-DB-LLR-001*/
   /* Point to highest priority task ready to run*/
   Os_tcb_high_rdy   = Os_tcb_prio_tbl[prio];
   /*hdudispfucos-OsStart-DB-LLR-002*/
   Os_tcb_cur        = Os_tcb_high_rdy;
   /*hdudispfucos-OsStart-DB-LLR-003*/
   Os_running        = TRUE;

   /*hdudispfucos-OsStart-DB-LLR-004*/
   /* Execute target specific code to start task*/
   OsStartHighRdy();
}


/*
 * Function                :  OsSched
 *
 * Description             :  This function is the uC/OS scheduler which determines which
 *                            task has the highest priority and thus will be next to run.
 *
 * Formal parameter(s)     :  None
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */

void OsSched(void)
{
    T_UBYTE y_val = ZERO;

    /*hdudispfucos-OsSched-DB-LLR-001*/
    OS_ENTER_CRITICAL();

     /* Task scheduling must be enabled and not ISR level*/
    if (ZERO == (Os_lock_nesting | Os_int_nesting))
    {
      /*hdudispfucos-OsSched-DB-LLR-002*/
      y_val  = Os_un_map_tbl[Os_rdy_grp];

      /* Get pointer to highest priority task ready to run*/
      Os_tcb_high_rdy  = Os_tcb_prio_tbl[(y_val << THREE)
                  + Os_un_map_tbl[Os_rdy_tbl[y_val]]];

        /* Make sure this is not the current task running*/
        if (Os_tcb_high_rdy != Os_tcb_cur)
        {
         /*hdudispfucos-OsSched-DB-LLR-003*/
             /* Increment context switch counter*/
            Os_ctx_sw_ctr++;

             /* Perform a context switch*/
            OS_TASK_SW();
        }
        else
        {
         ;/*Do nothing*/
        }
    }
    else
    {
      ;/*Do nothing*/
    }

   /*hdudispfucos-OsSched-DB-LLR-004*/
    OS_EXIT_CRITICAL();
}

/*
 * Function                :  OsTcbInit
 *
 * Description             :  This function initializes the task control block (TCB).
 *
 * Formal parameter(s)     :  T_UBYTE prio - IN priority
 *                            void *stk - IN address of stack
 *
 * Return Value            :  T_UBYTE - returns error status
 *
 * Assumption              :  None
 *
 */

T_UBYTE OsTcbInit(T_UBYTE prio, void *stk)

{
    T_OS_TCB *ptr_tcb = {ZERO};

    /*hdudispfucos-OsTcbInit-DB-LLR-001*/
    OS_ENTER_CRITICAL();

    /*hdudispfucos-OsTcbInit-DB-LLR-002*/
    ptr_tcb = Os_tcb_free_list;

    /* Get a free TCB from the free TCB list*/
    if (ptr_tcb != (T_OS_TCB *)ZERO)
    {
        /*hdudispfucos-OsTcbInit-DB-LLR-003*/
        /* Update pointer to free TCB list*/
        Os_tcb_free_list        = ptr_tcb->OSTCBNext;

        OS_EXIT_CRITICAL();

        ptr_tcb->OSTCBStkPtr       = stk;                     /* Load Stack pointer in TCB*/
        ptr_tcb->OSTCBPrio         = (T_UBYTE)prio;             /* Load task priority into TCB*/
        ptr_tcb->OSTCBStat         = OS_STAT_RDY;             /* Task is ready to run*/
        ptr_tcb->OSTCBDly          = ZERO;
        ptr_tcb->OSTCBY            = prio >> THREE;
        ptr_tcb->OSTCBBitY         = Os_map_tbl[ptr_tcb->OSTCBY];
        ptr_tcb->OSTCBX            = prio & SEVEN;
        ptr_tcb->OSTCBBitX         = Os_map_tbl[ptr_tcb->OSTCBX];

        /* Task is not pending on an event*/
        ptr_tcb->OSTCBEventPtr     = (T_OS_EVENT *)ZERO;

        OS_ENTER_CRITICAL();

        Os_tcb_prio_tbl[prio]   = ptr_tcb;

        /* Link into TCB chain*/
        ptr_tcb->OSTCBNext      = Os_tcb_list;
        ptr_tcb->OSTCBPrev      = (T_OS_TCB *)ZERO;

        if (Os_tcb_list != (T_OS_TCB *)ZERO)
        {
            Os_tcb_list->OSTCBPrev = ptr_tcb;
        }
        else
        {
         ;/*Do nothing*/
        }

        Os_tcb_list                  = ptr_tcb;

        /* Make task ready to run*/
        Os_rdy_grp                  |= ptr_tcb->OSTCBBitY;
        Os_rdy_tbl[ptr_tcb->OSTCBY] |= ptr_tcb->OSTCBBitX;
        OS_EXIT_CRITICAL();

        return (OS_NO_ERR);
    }
    else
    {
        /*hdudispfucos-OsTcbInit-DB-LLR-004*/
        OS_EXIT_CRITICAL();
        /*hdudispfucos-OsTcbInit-DB-LLR-005*/
        return (OS_NO_MORE_TCB);
    }
}

/*
 * Function                :  OsIntEnter
 *
 * Description             :  This function increments the ISR nesting level and
 *                            to inform the uC/OS on entering the ISR.
 *
 * Formal parameter(s)     :  None
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */
void OsIntEnter(void)
{
    /*hdudispfucos-OsIntEnter-DB-LLR-001*/
    OS_ENTER_CRITICAL();

    /* Increment ISR nesting level*/
    Os_int_nesting++;

    OS_EXIT_CRITICAL();
}


/*
 * Function                :  OsIntExit
 *
 * Description             :  This function will decrement ISR nesting level and perform
 *                            interrupt level context switching.
 *
 * Formal parameter(s)     :  None
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */

void OsIntExit(void)
{
   /*hdudispfucos-OsIntExit-DB-LLR-001*/
    OS_ENTER_CRITICAL();

    if (ZERO == (--Os_int_nesting | Os_lock_nesting))
    {
      /*hdudispfucos-OsIntExit-DB-LLR-002*/
       /* Reschedule only if all ISRs completed & not locked */
        Os_int_exit_y   = Os_un_map_tbl[Os_rdy_grp];
        Os_tcb_high_rdy = Os_tcb_prio_tbl[(Os_int_exit_y << THREE)
                          + Os_un_map_tbl[Os_rdy_tbl[Os_int_exit_y]]];

        if (Os_tcb_high_rdy != Os_tcb_cur)
        {
           /*hdudispfucos-OsIntExit-DB-LLR-003*/
           /* No context switch if current task is highest ready */
            Os_ctx_sw_ctr++;

            /* Perform interrupt level context switch*/
            OsIntCtxSw();
        }
        else
        {
         ;/*Do nothing*/
        }
    }
    else
    {
      ;/*Do nothing*/
    }

    /*hdudispfucos-OsIntExit-DB-LLR-004*/
    OS_EXIT_CRITICAL();
}

/*
 * Function                :  OsTimeDly
 *
 * Description             :  This function allows the calling task to delay for a
 *                            specific number of clock ticks
 *
 * Formal parameter(s)     :  T_UWORD ticks - IN time in ticks
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */

void OsTimeDly(T_UWORD ticks)
{
    if (ticks > ZERO)
    {
      /*hdudispfucos-OsTimeDly-DB-LLR-001*/
        OS_ENTER_CRITICAL();

        /* Delay current task*/
        if (ZERO == (Os_rdy_tbl[Os_tcb_cur->OSTCBY] = (T_UBYTE)(Os_rdy_tbl[Os_tcb_cur->OSTCBY]
                                    & (~Os_tcb_cur->OSTCBBitX))))
        {
            Os_rdy_grp = (T_UBYTE)(Os_rdy_grp & (~Os_tcb_cur->OSTCBBitY));
        }
        else
        {
         ;/*Do nothing*/
        }

        /* Load ticks in TCB*/
        Os_tcb_cur->OSTCBDly = ticks;
        OS_EXIT_CRITICAL();
        OsSched();
    }

    else
    {
      /*hdudispfucos-OsTimeDly-DB-LLR-002*/
      ;/*Do nothing*/
    }
}

/*
 * Function                :  OsTimeTick
 *
 * Description             :  This function increments the ISR nesting level and
 *                            to inform the uC/OS on entering the ISR.
 *
 * Formal parameter(s)     :  None
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */


void OsTimeTick(void)
{
    T_OS_TCB *ptr_tcb = {ZERO};

    /* Point at first TCB in TCB list*/
    ptr_tcb = Os_tcb_list;

    /*hdudispfucos-OsTimeTick-DB-LLR-001*/
     /* Go through all TCBs in TCB list*/
    while (ptr_tcb->OSTCBPrio != OS_LOWEST_PRIO)
    {
        OS_ENTER_CRITICAL();

         /* Delayed or waiting for event with TO*/
        if (ptr_tcb->OSTCBDly != ZERO)
        {
         ptr_tcb->OSTCBDly = (T_UWORD)(ptr_tcb->OSTCBDly - ONE);

             /* Decrement nbr of ticks to end of delay*/
            if (ZERO == ptr_tcb->OSTCBDly)
            {
                if (ZERO == (ptr_tcb->OSTCBStat & OS_STAT_SUSPEND))
                {
                    Os_rdy_grp               |= ptr_tcb->OSTCBBitY;
                    Os_rdy_tbl[ptr_tcb->OSTCBY] |= ptr_tcb->OSTCBBitX;
                }
                else
                {
                    ptr_tcb->OSTCBDly = ONE;
                }
            }
            else
            {
               ;/*Do nothing*/
            }
        }
        else
        {
         ;/*Do nothing*/
        }
        OS_EXIT_CRITICAL();

        /* Point at next TCB in TCB list*/
        ptr_tcb = ptr_tcb->OSTCBNext;
    }

     /*hdudispfucos-OsTimeTick-DB-LLR-002*/
    OS_ENTER_CRITICAL();

    /*hdudispfucos-OsTimeTick-DB-LLR-003*/
    Os_time++;

    /*hdudispfucos-OsTimeTick-DB-LLR-004*/
    OS_EXIT_CRITICAL();
}

/*
 * Function                :  OsSemCreate
 *
 * Description             :  This function creates and initializes the Semaphore.
 *
 * Formal parameter(s)     :  T_UWORD cnt - IN events count
 *
 * Return Value            :   T_OS_EVENT * - returns reference to the obtained ECB on
 *                             successful creation of Semaphore else returns NULL.
 *
 * Assumption              :  None
 *
 */

T_OS_EVENT *OsSemCreate(T_UWORD count)
{

   T_OS_EVENT *p_event = {ZERO};

   /*hdudispfucos-OsSemCreate-DB-LLR-001*/
   OS_ENTER_CRITICAL();

   /*hdudispfucos-OsSemCreate-DB-LLR-002*/
   /* Get next free event control block*/
   p_event = Os_event_free_list;

   /* See if pool of free ECB pool was empty*/
   if (Os_event_free_list != (T_OS_EVENT *)ZERO)
   {
     /*hdudispfucos-OsSemCreate-DB-LLR-003*/
      Os_event_free_list = (T_OS_EVENT *)Os_event_free_list->OSEventPtr;
   }
   else
   {
      ;/*Do nothing*/
   }

   /*hdudispfucos-OsSemCreate-DB-LLR-004*/
   OS_EXIT_CRITICAL();

   /*hdudispfucos-OsSemCreate-DB-LLR-005*/
   /* Get an event control block*/
   if (p_event != (T_OS_EVENT *)ZERO)
   {
      /* Set semaphore value*/
      p_event->OSEventCnt    = count;

      /* Initialize rest of event control block*/
      p_event->OSEventGrp    = ZERO;
      p_event->OSEventTbl[0] = ZERO;
      p_event->OSEventTbl[1] = ZERO;
      p_event->OSEventTbl[2] = ZERO;
      p_event->OSEventTbl[3] = ZERO;
      p_event->OSEventTbl[4] = ZERO;
      p_event->OSEventTbl[5] = ZERO;
      p_event->OSEventTbl[6] = ZERO;
      p_event->OSEventTbl[7] = ZERO;

      return (p_event);
   }
   else
   {
      return ((T_OS_EVENT *)ZERO);
   }
}


/*
 * Function             :  OsSemAccept
 *
 * Description          :  This function checks the semaphore to see if the resource is
 *                         available or if an event occurred.  Unlike OsSemPend(), OsSemAccept()
 *                         does not suspend the calling task if the resource is not
 *                         available or the event did not occur.
 *
 * Formal parameter(s)  :  T_OS_EVENT *param_event - IN Pointer to the task event
 *
 * Return Value         :  T_INT16 - returns counter value
 *
 * Assumption           :  None
 *
 */

T_INT16 OsSemAccept(T_OS_EVENT *param_event)
{
    T_UINT16 cntr = ZERO;

   /*hdudispfucos-OsSemAccept-DB-LLR-001*/
    OS_ENTER_CRITICAL();

    cntr = (T_UINT16)param_event->OSEventCnt;

   /*hdudispfucos-OsSemAccept-DB-LLR-002*/
    /* See if resource is available*/
    if (cntr > ZERO)
    {
      /* Yes, decrement semaphore and notify caller*/
      param_event->OSEventCnt--;
    }
    else
    {
      ;/*Do nothing*/

    }

   /*hdudispfucos-OsSemAccept-DB-LLR-003*/
    OS_EXIT_CRITICAL();

   /*hdudispfucos-OsSemAccept-DB-LLR-004*/
    /* Return semaphore count*/
    return (T_INT16)(cntr);
}


/*
 * Function                :  OSSemPeek
 *
 * Description             :  This function enters to critical condition.
 *
 * Formal parameter(s)     :  T_OS_EVENT *p_event - IN Pointer to the task event
 *
 * Return Value            :  T_INT16 - Counter value
 *
 * Assumption              :  None
 *
 */

T_INT16 OSSemPeek(T_OS_EVENT *p_event)
{
    T_INT16 cntr = ZERO;

    /*hdudispfucos-OSSemPeek-DB-LLR-001*/
    OS_ENTER_CRITICAL();
    cntr = (T_INT16)p_event->OSEventCnt;
    OS_EXIT_CRITICAL();

    /* Return semaphore count*/
    return (cntr);
}

/*
 * Function                :  OsSemPend
 *
 * Description             :  This function function waits on a Semaphore.
 *
 * Formal parameter(s)     :  T_OS_EVENT *p_event - IN Pointer to the task event
 *                            T_UWORD time_out - IN wait time
 *                            T_UBYTE *error - OUT error status
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */

void OsSemPend(T_OS_EVENT *p_event, T_UWORD time_out, T_UBYTE *error)
{
   /*hdudispfucos-OsSemPend-DB-LLR-001*/
    OS_ENTER_CRITICAL();

     /* If sem. is positive, resource available ...*/
    if (p_event->OSEventCnt > ZERO)
    {
      /*hdudispfucos-OsSemPend-DB-LLR-002*/
        p_event->OSEventCnt--;

        /* ... decrement semaphore only if positive.*/
        OS_EXIT_CRITICAL();

        *error = OS_NO_ERR;
    }
    /* Otherwise, must wait until event occurs*/
    else
    {
      /*hdudispfucos-OsSemPend-DB-LLR-003*/
        /* Resource not available, pend on semaphore*/
        Os_tcb_cur->OSTCBStat    |= OS_STAT_SEM;

        /* Store pend time_out in TCB*/
        Os_tcb_cur->OSTCBDly      = time_out;

         /* Store pointer to ECB in TCB*/
        Os_tcb_cur->OSTCBEventPtr = p_event;

        /* Task no longer ready*/
        if (ZERO == (Os_rdy_tbl[Os_tcb_cur->OSTCBY] &= (T_UBYTE) ~Os_tcb_cur->OSTCBBitX))
        {
            Os_rdy_grp &= (T_UBYTE) ~Os_tcb_cur->OSTCBBitY;
        }
        else
        {
         ;/*Do nothing*/
        }

        /* Put task in waiting list*/
        p_event->OSEventTbl[Os_tcb_cur->OSTCBY] |= Os_tcb_cur->OSTCBBitX;
        p_event->OSEventGrp                     |= Os_tcb_cur->OSTCBBitY;

        OS_EXIT_CRITICAL();

         /* Find next highest priority task ready*/
        OsSched();

        OS_ENTER_CRITICAL();

        /* Must have timed out if still waiting for event*/
        if ((Os_tcb_cur->OSTCBStat & OS_STAT_SEM)!= ZERO)
        {
            if (ZERO == (p_event->OSEventTbl[Os_tcb_cur->OSTCBY] &=
               (T_UBYTE) ~Os_tcb_cur->OSTCBBitX))
            {
                p_event->OSEventGrp &= (T_UBYTE) ~Os_tcb_cur->OSTCBBitY;
            }
            else
            {
               ;/*Do nothing*/
            }

            /* Set status to ready*/
            Os_tcb_cur->OSTCBStat     = OS_STAT_RDY;

             /* Task is no longer waiting for the event*/
            Os_tcb_cur->OSTCBEventPtr = (T_OS_EVENT *)ZERO;
            OS_EXIT_CRITICAL();

            /* Indicate that didn't get event within TO*/
            *error = OS_TIMEOUT;
        }
        else
        {
            Os_tcb_cur->OSTCBEventPtr = (T_OS_EVENT *)ZERO;
            OS_EXIT_CRITICAL();
            *error = OS_NO_ERR;
        }
    }
}

/*
 * Function                :  OsSemPost
 *
 * Description             :  This function posts a Semaphore.
 *
 * Formal parameter(s)     :  T_OS_EVENT *param_event - INOUT Pointer to the task event
 *
 * Return Value            :  T_UBYTE returns the error code
 *
 * Assumption              :  None
 *
 */

T_UBYTE OsSemPost(T_OS_EVENT *param_event)
{
    T_OS_TCB *ptr_tcb = {ZERO};
    T_UBYTE   x_val = ZERO;
    T_UBYTE   y_val = ZERO;
    T_UBYTE   bit_x = ZERO;
    T_UBYTE   bit_y = ZERO;
    T_UBYTE   p_val = ZERO;

    /* hdudispfucos-OsSemPost-DB-LLR-001 */
    OS_ENTER_CRITICAL();

    /*See if any task waiting for semaphore*/
    if (param_event->OSEventGrp != ZERO)
    {
      /* hdudispfucos-OsSemPost-DB-LLR-002 */
        /*Find highest priority task pending on event*/
        y_val  = Os_un_map_tbl[param_event->OSEventGrp];
        bit_y  = Os_map_tbl[y_val];
        x_val  = Os_un_map_tbl[param_event->OSEventTbl[y_val]];
        bit_x  = Os_map_tbl[x_val];
        p_val  = (T_UBYTE)((y_val << THREE) + x_val);

        /* Remove this task from the waiting list*/
        if (ZERO == (param_event->OSEventTbl[y_val] &= (T_UBYTE) ~bit_x))
        {
            param_event->OSEventGrp &= (T_UBYTE) ~bit_y;
        }
        else
        {
         ;/*Do nothing*/
        }

       /* Point to this task's T_OS_TCB*/
        ptr_tcb                 =  Os_tcb_prio_tbl[p_val];

        /* Prevent OsTimeTick() from readying this task*/
        ptr_tcb->OSTCBDly       =  ZERO;

        /* Unlink event control block from this task*/
        ptr_tcb->OSTCBEventPtr  = (T_OS_EVENT *)ZERO;

        /* Clear bit associated with event type*/
        ptr_tcb->OSTCBStat     &= (T_UBYTE)~OS_STAT_SEM;

        /* See if task is ready (could be suspended)*/
        if (OS_STAT_RDY == ptr_tcb->OSTCBStat)
        {
            /* Put task in the ready to run list*/
            Os_rdy_grp            |=  bit_y;
            Os_rdy_tbl[y_val]     |=  bit_x;
        }
        else
        {
         ;/*Do nothing*/
        }

        OS_EXIT_CRITICAL();

        /* Find highest priority task ready to run*/
        OsSched();

        return (OS_NO_ERR);
    }
    else
    {
         /* Make sure semaphore will not overflow*/
        if (param_event->OSEventCnt < MAX_SEMAPHORE)
        {
            /* hdudispfucos-OsSemPost-DB-LLR-003 */
            param_event->OSEventCnt++;

             /* Increment semaphore count to register event*/
            OS_EXIT_CRITICAL();

            return (OS_NO_ERR);
        }
        /* Semaphore value has reached its maximum*/
        else
        {
            /* hdudispfucos-OsSemPost-DB-LLR-004 */
            OS_EXIT_CRITICAL();
            return (OS_SEM_OVF);
        }
    }
}
