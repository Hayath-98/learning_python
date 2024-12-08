/*
 ******************************************************************************
 * License Information  :  Howell Instruments, Inc.                           *
 *                         "Licensed Software" and "All rights reserved".     *
 ******************************************************************************
 *  File                : hdudispfoscpua.s
 *
 *  Description         : This file defines assembly functions used by the OS.
 *
 *  Compiler            : GNU gcc(GNU Tools for ARM Embedded Processors) version 5.4.1 20160919
 *
 *  Compiler options    : As per section 10.3.2 of Software Development Plan (HDU-001-002).
 *
 *  Pragma              : None
 *
 *  H/W platform        : ARM Cortex-M7 (STM32F767)
 *
 *  Portability         : None
 *
 *  Author(s)           : Shilpa A R
 *
 *  Version History     :
 * <Version No.>      <Author>          <Date>         <Problem Report No.>
 *
 *      1.1           Shilpa A R     25-Jul-2017             100064
 *      1.2           Rona B S       11-Oct-2017             100064
 *
 * Additional References : None
 *
 ******************************************************************************
 */

.cpu cortex-m4		/* processor used is cortex-m4 */
.syntax unified		/* use modern assembler syntax + auto-generate IT instructions. */
.thumb   			/* thumb instruction set  */
.text			  /* all output from now on goes into '.text' section  */

    .equ NVIC_INT_CTRL,     0xE000ED04  /* Interrupt control state register */
    .equ NVIC_SYSPRI14,     0xE000ED22  /* System prio register (prio 14) */
    .equ NVIC_PENDSV_PRI,   0xFF        /* PendSV priority value (lowest) */
    .equ NVIC_PENDSVSET,    0x10000000  /* Value to trigger PendSV isr */

   .equ DEFAULT_VAL,       0x0          /* default Value  */
   .equ DEFAULT_TRUE_VAL,  0x1          /* default True Value  */
   .equ EXCEPTION_RETURN,   0x4         /* Exception return value*/
   /* global */
    .global OsCtxSw
    .global SaveStatusReg
    .global RestoreStatusReg
    .global OsStartHighRdy
    .global OsCtxSw
    .global OsIntCtxSw
    .global PendSVHandlerFlight

    .extern Os_running
    .extern OSPrioCur
    .extern OSPrioHighRdy
    .extern Os_tcb_cur
    .extern Os_tcb_high_rdy
    .extern Os_int_nesting
    .extern OsIntExit
    .extern OSTaskSwHook

/*
 * Function                :  OsCtxSw
 *
 * Description             :  This function performs a task level context switch.
 *                            NOTE : This function triggers the PendSV exception (PendSV is an
 *                            interrupt-driven request for system-level service. Use PendSV for
 *                            context switching when no other exception is active, PendSV handler
 *                            will run when interrupts are re-enabled, after call to the OS_EXIT_CRITICAL())
 *
 * Formal parameter(s)     :  None
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */

.thumb_func
.align(4)
OsCtxSw:
    /*	hdudispfoscpua-OsCtxSw-DB-LLR-001 */
    LDR     R0, =NVIC_INT_CTRL     
    LDR     R1, =NVIC_PENDSVSET
    STR     R1, [R0]
    BX      LR

/*
 * Function                :  OsIntCtxSw
 *
 * Description             :  This function performs a task level context switch same as OSCtxSw.
 *                            Note:OSIntCtxSw() is called by OsIntExit() when it determines a
 *                            context switch is needed as the result of an interrupt.
 *                            This function simply triggers a PendSV exception which will
 *                            be handled when there are no more interrupts active and interrupts
 *                            are enabled.
 *
 * Formal parameter(s)     :  None
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */

.thumb_func
.align(4)
OsIntCtxSw:
    /*	hdudispfoscpua-OsIntCtxSw-DB-LLR-001 */
    LDR     R0, =NVIC_INT_CTRL     
    LDR     R1, =NVIC_PENDSVSET
    STR     R1, [R0]
    BX      LR

/*
 * Function                :  SaveStatusReg
 *
 * Description             :  This function save the interrupt mask register and
 *                            then disables interrupts to enter into critical section.
 *                            This function is invoked by the OS_ENTER_CRITICAL().
 *                            NOTE : When this function returns,  R0 contains the state
 *                            of the PRIMASK register which contains the global
 *                            interrupt mask prior to disabling interrupts.
 *
 * Formal parameter(s)     :  None
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */

.thumb_func
.align(4)
SaveStatusReg:
    /*	hdudispfoscpua-SaveStatusReg-DB-LLR-001 */
    MRS     R0, PRIMASK  
    CPSID   I
    BX      LR

/*
 * Function                :  RestoreStatusReg
 *
 * Description             :  This function restores the interrupt disable
 *                            mask to its original value.
 *
 * Formal parameter(s)     :  None
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */

.thumb_func
.align(4)
RestoreStatusReg:
    /*	hdudispfoscpua-RestoreStatusReg-DB-LLR-001 */
    MSR     PRIMASK, R0
    BX      LR

/*
 * Function                :  OsStartHighRdy
 *
 * Description             :  This function starts running the highest priority task.
 *                            NOTE : OSStartHighRdy() is called by OsStart(). OsStart()
 *                            sets Os_tcb_high_rdypoint to the OS_TCB of the highest priority task.
 *                            The highest priority task should be created before call to OsStart.
 *
 * Formal parameter(s)     :  None
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */

.thumb_func
.align(4)
OsStartHighRdy:
    /*	hdudispfoscpua-OsStartHighRdy-DB-LLR-001 */
    /* Set the PendSV exception priority */
    LDR     R0, =NVIC_SYSPRI14
    LDR     R1, =NVIC_PENDSV_PRI
    STRB    R1, [R0]

    /*	hdudispfoscpua-OsStartHighRdy-DB-LLR-002 */
    /* Set the PSP to 0 for initial context switch call */
    MOVS    R0, DEFAULT_VAL
    MSR     PSP, R0

    /*	hdudispfoscpua-OsStartHighRdy-DB-LLR-003 */
    /* OSRunning = TRUE */
    LDR     R0, =Os_running
    MOVS    R1, DEFAULT_TRUE_VAL
    STRB    R1, [R0]

    /*	hdudispfoscpua-OsStartHighRdy-DB-LLR-004 */
    /* Trigger the PendSV exception (causes context switch) */
    LDR     R0, =NVIC_INT_CTRL
    LDR     R1, =NVIC_PENDSVSET
    STR     R1, [R0]

    /*	hdudispfoscpua-OsStartHighRdy-DB-LLR-005 */
    /* Enable interrupts at processor level */
    CPSIE   I

   /*	hdudispfoscpua-OsStartHighRdy-DB-LLR-006 */
OsStartHang:
    /* Should never get here */
    B       OsStartHang

/*
 * Function                :  PendSVHandlerFlight
 *
 * Description             :  This function handles all context switching for uCOS.
 *
 * Formal parameter(s)     :  None
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */

.thumb_func
.align(4)
PendSVHandlerFlight:
    /*	hdudispfoscpua-PendSVHandlerFlight-DB-LLR-001 */
    /* Prevent interruption during context switch */
    CPSID   I

    /*	hdudispfoscpua-PendSVHandlerFlight-DB-LLR-002 */
    /* PSP is process stack pointer */
    MRS     R0, PSP

    /*	hdudispfoscpua-PendSVHandlerFlight-DB-LLR-003 */
    /* Skip register save the first time */
    CBZ     R0, PendSVHandlernosave

    /*	hdudispfoscpua-PendSVHandlerFlight-DB-LLR-004 */
    /* Save remaining regs r4-11 on process stack */
    STMDB   R0!, {R4-R11}

    /*	hdudispfoscpua-PendSVHandlerFlight-DB-LLR-005 */
    /* Save remaining floating point regs s16-31 */
    VSTMDB  R0!, {S16-S31}

    /*	hdudispfoscpua-PendSVHandlerFlight-DB-LLR-006 */
    /* Os_tcb_cur->OSTCBStkPtr = SP */
    LDR     R1, =Os_tcb_cur
    LDR     R1, [R1]

    /*	hdudispfoscpua-PendSVHandlerFlight-DB-LLR-006 */
    /* R0 is SP of process being switched out */
    STR     R0, [R1]

/* At this point, entire context of process has been saved */

/*hdudispfoscpua-PendSVHandlerFlight-DB-LLR-007 */
PendSVHandlernosave:
    /* Os_tcb_cur  = Os_tcb_high_rdy*/
    LDR     R0, =Os_tcb_cur
    LDR     R1, =Os_tcb_high_rdy
    LDR     R2, [R1]
    STR     R2, [R0]

    /* R0 is new process SP; SP = Os_tcb_high_rdy->OSTCBStkPtr */
    LDR     R0, [R2]

    /* Restore S16-31 from new process stack */
    VLDMIA  R0!, {S16-S31}

    /* Restore r4-11 from new process stack */
    LDMIA   R0!, {R4-R11}

    /* Load PSP with new process SP */
    MSR     PSP, R0

    /* Ensure exception return uses process stack */
    ORR     LR, LR, EXCEPTION_RETURN
    CPSIE   I

    /* Exception return will restore remaining context */
    BX      LR

    .end
