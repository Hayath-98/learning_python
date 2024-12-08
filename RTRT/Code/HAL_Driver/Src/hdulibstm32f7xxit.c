/*
 ******************************************************************************
 * License Information  :  Howell Instruments, Inc.                           *
 *                         "Licensed Software" and "All rights reserved".     *
 ******************************************************************************
 *  File                : hdulibstm32f7xxit.c
 *
 *  Description         : Main Interrupt Service Routines.
 *                        This file provides template for all exceptions handler and
 *                        peripherals interrupt service routine.
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
 *
 * <Version No.>        <Author>          <Date>               <Problem Report No.>
 *
 *      1.1             Ajay J G          03-Aug-2017             -
 *      1.2             Shilpa A R        02-Sep-2017           100028
 *      1.3             Shruthi M N       28-Sep-2017           100064
 *      1.4             Divya G P         09-Oct-2017           100064
 *      1.5             Rona B S          12-Sep-2020           100276 
 *
 * Additional References : None
 *
 ******************************************************************************
 */

/* Includes */
#include "hdulibstm32f7xxhaldma2d.h" /* Defines DMA2D specification */
#include "hdulibstmcorecomm.h"    /* Header files for Core Communication*/
#include "hdulibstm32f7xxhal.h"    /* Header file of FMC HAL module */
#include "hdudispfucos.h"  /* defines the implementation of uC/OS routines  */
#include "hdulibbasictypes.h" /* Standard basic data type definitions */
#include "hdulibstm32f7xxit.h" /* contains the headers of the interrupt handlers */
#include "hdulibstm32f746xx.h" /* CMSIS Cortex-M7 Device Peripheral Access Layer */
#include "hdulibcorecm7.h"     /* Cortex-M7 processor and core peripherals */
#include "hdulibstm32f7xxhaldma.h"  /*Contains the DMA HAL defination module */

/*
 * Function                :  NmiHandler
 *
 * Description             :  This function handles NMI exception.
 *
 * Formal parameter(s)     :  None
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */
void NmiHandler(void)
{
 /*hdulibstm32f7xxit-NmiHandler-DB-LLR-001*/
   ;
}


/*
 * Function                :  HardFaultHandler
 *
 * Description             :  This function handles Hard Fault exception.
 *
 * Formal parameter(s)     :  None
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */
void HardFaultHandler(void)
{
  /*hdulibstm32f7xxit-HardFaultHandler-DB-LLR-001*/
  /* Go to infinite loop when Hard Fault exception occurs */
  while (ONE)
  {
  ;
  }
}


/*
 * Function                :  MemManageHandler
 *
 * Description             :  This function handles Memory Manage exception.
 *
 * Formal parameter(s)     :  None
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */
void MemManageHandler(void)
{
  /*hdulibstm32f7xxit-MemManageHandler-DB-LLR-001*/
  /* Go to infinite loop when Memory Manage exception occurs */
  while (ONE)
  {
  }
}


/*
 * Function                :  BusFaultHandler
 *
 * Description             :  This function handles Bus Fault exception.
 *
 * Formal parameter(s)     :  None
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */
void BusFaultHandler(void)
{
  /*hdulibstm32f7xxit-BusFaultHandler-DB-LLR-001*/
  /* Go to infinite loop when Bus Fault exception occurs */
  while (ONE)
  {
  }
}

/*
 * Function                :  UsageFaultHandler
 *
 * Description             :  This function handles Usage Fault exception.
 *
 * Formal parameter(s)     :  None
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */
void UsageFaultHandler(void)
{
  /*hdulibstm32f7xxit-UsageFaultHandler-DB-LLR-001*/
  /* Go to infinite loop when Usage Fault exception occurs */
  while (ONE)
  {
  }
}


/*
 * Function                :  SvcHandler
 *
 * Description             :  This function handles SVCall exception.
 *
 * Formal parameter(s)     :  None
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */
void SvcHandler(void)
{
/*hdulibstm32f7xxit-SvcHandler-DB-LLR-001*/
}

/*
 * Function                :  DebugMonHandler
 *
 * Description             :  This function handles Debug Monitor exception.
 *
 * Formal parameter(s)     :  None
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */
void DebugMonHandler(void)
{
/*hdulibstm32f7xxit-DebugMonHandler-DB-LLR-001*/
   ;/*Does nothing */
}


/*
 * Function                :  PendSVHandler
 *
 * Description             :  This function handles PendSVC exception.
 *
 * Formal parameter(s)     :  None
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */
void PendSVHandler(void)
{
/*hdulibstm32f7xxit-PendSVHandler-DB-LLR-001*/
   ;/*Does nothing */
}

/*
 * Function                :  LtdcIrqHandler
 *
 * Description             :  This function handles  the "Line Interrupt" from the LTDC.
 *
 * Formal parameter(s)     :  None
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */

void LtdcIrqHandler(void)
 {
   T_UINT8  loop_cntr = ZERO;
   /* Clear the line interrupt flag. */

   /*hdulibstm32f7xxit-LtdcIrqHandler-DB-LLR-001*/
   LTDC->ICR = LTDC_ICR_CLIF;

   /*hdulibstm32f7xxit-LtdcIrqHandler-DB-LLR-002*/
   for(loop_cntr=0; loop_cntr<TEN; loop_cntr++)
   {
      ;/*Do nothing */
   }

   /*hdulibstm32f7xxit-LtdcIrqHandler-DB-LLR-003*/
   /* Alternate between the "On screen" and "Off screen". */
   if(TRUE == Init_b_done)
   {
      OsIntEnter();
      OsSemPost(Sem_app_task);
      OsIntExit();
   }
   else
   {
      ;/*Do nothing */
   }
}

/*
 * Function                :  ITInterrupsInit
 *
 * Description             :  This function configures the LTDC Line interrupt.
 *
 * Formal parameter(s)     :  None
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */

void ITInterrupsInit(void)
{
   /* Configure the LTDC Line interrupt.   */
   /* Set to interrupt at the end of the vertical blanking period. */
   /*hdulibstm32f7xxit-ITInterrupsInit-DB-LLR-001*/
   LTDC->LIPCR = DISPLAY_END;
   LTDC->IER = LTDC_IER_LIE;
   NVICSetPriority(LTDC_IRQN, LTDC_LI_PRIORITY);
   NVICEnableIRQ(LTDC_IRQN);
}

/*
 * Function                :  Dma2Stream0IrqHandler
 *
 * Description             :  This function invokes the DMA interrupt request handler.
 *
 * Formal parameter(s)     :  None
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */
void Dma2Stream0IrqHandler(void)
{
   /*hdulibstm32f7xxit-Dma2Stream0IrqHandler-DB-LLR-001*/
   HALDmaIrqHandler(&Dma_handle);
}
