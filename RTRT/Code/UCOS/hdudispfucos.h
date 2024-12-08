/*
 ******************************************************************************
 * License Information  :  Howell Instruments, Inc.                           *
 *                         "Licensed Software" and "All rights reserved".     *
 ******************************************************************************
 *  File                : hdudispfucos.h
 *
 *  Description         : This module declares uC/OS routines for the real-time kernel.
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
 *      1.2           Vinay H         10-Oct-2017             100064
 *
 * Additional References : None
 *
 ******************************************************************************
 */

#ifndef _HDUDISPFUCOS_H_
#define _HDUDISPFUCOS_H_

#include "hdulibbasictypes.h"        /* Contains basic data types */

#include "hdudispfoscpu.h"            /* OS function declarations */

#define OS_NO_ERR                 0U

#define OS_TIMEOUT               10U
#define OS_TASK_NOT_EXIST        11U

#define OS_PRIO_EXIST            40U
#define OS_PRIO_ERR              41U
#define OS_PRIO_INVALID          42U

#define OS_SEM_ERR               50U
#define OS_SEM_OVF               51U
#define OS_SEM_NOT_AVAIL         52U

#define OS_NO_MORE_TCB           70U

#define OS_TIME_NOT_DLY          80U

/* Max. number of event control blocks in your application.  MUST be >= 2.*/
#define OS_MAX_EVENTS            15U

/* Max. number of tasks in your application.  MUST be >= 2*/
#define OS_MAX_TASKS             63U

/* Lowest priority that can be assigned.  MUST NEVER be higher than 63!*/
#define OS_LOWEST_PRIO           63U

/* Idle task stack size (# of 32-bit wide entries)*/
#define OS_IDLE_TASK_STK_SIZE    512U

/* Set the number of ticks in one second.*/
#define  OS_TICKS_PER_SEC       1000U

/* MAIN STACK SIZE */
#define MAIN_STK_SIZE          1024U


/*
 * EVENT CONTROL BLOCK
 */

typedef struct os_event {
    T_UBYTE  OSEventGrp;           /* Group corresponding to tasks waiting for event to occur */
    T_UBYTE  OSEventTbl[8];        /* List of tasks waiting for event to occur                */
    T_UWORD  OSEventCnt;           /* Count of used when event is a semaphore                 */
    void  *OSEventPtr;           /* Pointer to message or queue structure                   */
} T_OS_EVENT;


/*
 *  uC/OS TASK CONTROL BLOCK
 */

typedef struct os_tcb {
    void           *OSTCBStkPtr;    /* Pointer to current top of stack                        */
    T_UBYTE          OSTCBStat;       /* Task status                                            */
    T_UBYTE          OSTCBPrio;       /* Task priority (0 == highest, 63 == lowest)             */
    T_UWORD          OSTCBDly;        /* Nbr ticks to delay task or, timeout waiting for event  */
    T_UBYTE          OSTCBX;          /* Bit position in group  corresponding to task priority  */
    T_UBYTE          OSTCBY;          /* Index into ready table corresponding to task priority  */
    T_UBYTE          OSTCBBitX;       /* Bit mask to access bit position in ready table         */
    T_UBYTE          OSTCBBitY;       /* Bit mask to access bit position in ready group         */
    T_OS_EVENT      *OSTCBEventPtr; /* Pointer to event control block                         */
    struct os_tcb *OSTCBNext;       /* Pointer to next     TCB in the TCB list                */
    struct os_tcb *OSTCBPrev;       /* Pointer to previous TCB in the TCB list                */
} T_OS_TCB;

/*
 * uC/OS GLOBAL VARIABLES
 */

/* SYSTEM VARIABLES */
extern  T_UWORD      Os_ctx_sw_ctr;         /* Counter of number of context Switches        */
extern  volatile T_ULONG  Os_idle_ctr;      /* Idle counter                                 */
extern  T_UBYTE      Os_int_nesting;        /* Interrupt nesting level                      */
extern  T_BOOLEAN    Os_running;            /* Flag indicating that kernel is running       */
extern  T_OS_TCB    *Os_tcb_cur;          /* Pointer to currently running TCB             */
extern  T_OS_TCB    *Os_tcb_high_rdy;     /* Pointer to highest priority TCB ready to run */
extern  T_OS_TCB    *Os_tcb_prio_tbl[64]; /* Table of pointers to all created TCBs        */

/*
 * uC/OS FUNCTION PROTOTYPES
 */

extern void        OsInit(void);
extern void        OsStart(void);
extern void        OsStartHighRdy(void);
extern void        OsSched(void);
extern T_UBYTE       OsTaskCreate(void (*task)(void *pd), void *pdata, void *pstk, T_UBYTE prio);
extern T_UBYTE       OsTcbInit(T_UBYTE prio, void  *stk);
extern void        OsIntEnter(void);
extern void        OsIntExit(void);
extern void        OsIntCtxSw(void);
extern void        OsCtxSw(void);
extern void        OsTimeDly(T_UWORD ticks);
extern void        OsTimeTick(void);
extern T_OS_EVENT  *OsSemCreate(T_UWORD count);
extern T_INT16     OsSemAccept(T_OS_EVENT *param_event);
extern T_UBYTE       OsSemPost(T_OS_EVENT *param_event);
extern void        OsSemPend(T_OS_EVENT *p_event, T_UWORD time_out, T_UBYTE *error);
extern T_OS_STK Os_task_idle_stk[OS_IDLE_TASK_STK_SIZE];

#endif    /*_HDUDISPFUCOS_H_*/
