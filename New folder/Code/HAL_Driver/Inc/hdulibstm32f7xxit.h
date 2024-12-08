/*
 ******************************************************************************
 * License Information  :  Howell Instruments, Inc.                           *
 *                         "Licensed Software" and "All rights reserved".     *
 ******************************************************************************
 *  File                : hdulibstm32f7xxit.h
 *
 *  Description         : This file contains the headers of the interrupt handlers.
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
 * <Version No.>     <Author>          <Date>         <Problem Report No.>
 *
 *      1.1          Ajay J G        03-Aug-2017             -
 *      1.2          Shilpa A R      02-Sep-2017           100028
 *      1.3          Shruthi M N     28-Sep-2017           100064
 *
 * Additional References : None
 *
 ******************************************************************************
 */

#ifndef _HDULIBSTM32F7XXIT_H_
#define _HDULIBSTM32F7XXIT_H_

/* Added for PR 100064 */
#define LTDC_LI_PRIORITY   3
#define VB_END             959U
#define DISPLAY_END  495U

/* Added for PR 100064 */
extern T_OS_EVENT *Sem_app_task;
extern T_BOOL Init_b_done;
extern T_DMA_HANDLE   Dma_handle;

extern void NmiHandler(void);
extern void HardFaultHandler(void);
extern void MemManageHandler(void);
extern void BusFaultHandler(void);
extern void UsageFaultHandler(void);
extern void SvcHandler(void);
extern void DebugMonHandler(void);
extern void PendSVHandler(void);
extern void Dma2Stream0IrqHandler(void);
extern void ITInterrupsInit(void);
extern void LtdcIrqHandler(void);

#endif /*_HDULIBSTM32F7XXIT_H_ */
