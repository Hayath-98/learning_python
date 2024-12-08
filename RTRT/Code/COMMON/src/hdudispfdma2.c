/*
 ******************************************************************************
 * License Information  :  Howell Instruments, Inc.                           *
 *                         "Licensed Software" and "All rights reserved".     *
 ******************************************************************************
 *  File                : hdudispfdma2.c
 *
 *  Description         : This file contains the routines to use DMA channel
 *                        to transfer a word data buffer from FLASH memory to embedded
 *                        SRAM memory through the STM32F7xx HAL API.
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
 *  Author(s)           : Rona B.S
 *
 *  Version History     :
 *
 * <Version No.>     <Author>          <Date>         <Problem Report No.>
 *
 *      1.1          Rona B.S        11-Sep-2017             100064
 *      1.2          Rona B.S        10-Oct-2017             100064
 *      1.3          Shruthi M N     30-Oct-2017             100104
 *
 * Additional References : None
 *
 *****************************************************************************
 */

/* Includes*/
#include "hdudispfdma2.h"   /*Contains the defination for DMA */
#include "hdulibstm32f7xxhalcortex.h" /* Header file of CORTEX HAL module */
#include "hdulibstm32f7xxhalrccex.h"  /* Header files for RCC EX HAL module*/
#include "hdulibstm32f7xxhaldef.h"  /*Contains the HAL defination module */
#include "hdulibstm32f7xxhaldma.h"  /* Header files for DMA HAL driver*/
#include "hdulibbasictypes.h" /* Standard basic data type definitions */

T_DMA_HANDLE Dma_handle = {0};

static T_UINT32 U32_clr_address = 0;
static T_UINT32 U32_data_length = 0;
static T_UINT32 Transfer_error_detected = 0;

/* Private function prototypes*/
static void DmaConfig(void);
static void ErrorHandler(void);
static void TransferComplete(T_DMA_HANDLE *Dma_handle);
static void TransferError();

#define CLEAR_SIZE   10000
#define THOUSAND     1000

static const T_UINT32 U32_clear_data[CLEAR_SIZE] = {ZERO};

/*
 * Function                :  DmaConfig
 *
 * Description             :  This function configures the DMA controller according
 *                            to the Stream parameters.
 *                            This function is used to :
 *                            1.Enable DMA2 clock
 *                            2.Select the DMA functional Parameters
 *                            3.Select the DMA instance to be used for the transfer
 *                            4.Select Callbacks functions called after Transfer complete
 *                              and Transfer error interrupt detection
 *                            5.Initialize the DMA stream
 *                            6.Configure NVIC for DMA transfer complete/error interrupts
 *                            7.Start the DMA transfer using the interrupt mode
 *
 * Formal parameter(s)     :  None
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */

static void DmaConfig(void)
{
  /*Enable DMA2 clock*/
  /*hdudispfdma2-DmaConfig-DB-LLR-001*/
  __HAL_RCC_DMA2_CLK_ENABLE();

  /*Select the DMA functional Parameters*/
  /*hdudispfdma2-DmaConfig-DB-LLR-002*/
  Dma_handle.Init.Channel     = DMA_CHANNEL;           /* DMA_CHANNEL_0                    */
  Dma_handle.Init.Direction   = DMA_MEMORY_TO_MEMORY;  /* M2M transfer mode                */
  Dma_handle.Init.PeriphInc   = DMA_PINC_ENABLE;       /* Peripheral increment mode Enable */
  Dma_handle.Init.MemInc      = DMA_MINC_ENABLE;       /* Memory increment mode Enable     */
  Dma_handle.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD; /* Peripheral data alignment  */
  Dma_handle.Init.MemDataAlignment    = DMA_MDATAALIGN_WORD; /* memory data alignment : Word */
  Dma_handle.Init.Mode          = DMA_NORMAL;                /* Normal DMA mode              */
  Dma_handle.Init.Priority      = DMA_PRIORITY_HIGH;         /* priority level : high        */
  Dma_handle.Init.FIFOMode      = DMA_FIFOMODE_DISABLE;      /* FIFO mode disabled           */
  Dma_handle.Init.FIFOThreshold = DMA_FIFO_THRESHOLD_FULL;
  Dma_handle.Init.MemBurst      = DMA_MBURST_SINGLE;         /* Memory burst                 */
  Dma_handle.Init.PeriphBurst   = DMA_PBURST_SINGLE;         /* Peripheral burst             */

  /*Select the DMA instance to be used for the transfer : DMA2_Stream0*/
  /*hdudispfdma2-DmaConfig-DB-LLR-003*/
  Dma_handle.Instance = DMA_INSTANCE;

  /*Initialize the DMA stream*/
  if (HalDmaInit(&Dma_handle) != HAL_OK)
  {
    /*Initialization Error */
    /*hdudispfdma2-DmaConfig-DB-LLR-004*/
    ErrorHandler();
  }
  else
  {
   ; /* Do nothing */
  }

  /*Select Callbacks functions called after Transfer complete and Transfer error */
  /*hdudispfdma2-DmaConfig-DB-LLR-005*/
  HALDmaRegisterCallback(&Dma_handle, HAL_DMA_XFER_CPLT_CB_ID,TransferComplete);
  HALDmaRegisterCallback(&Dma_handle, HAL_DMA_XFER_ERROR_CB_ID,TransferError);

  /*Configure NVIC for DMA transfer complete/error interrupts*/
  /* Set Interrupt Group Priority */
  /*hdudispfdma2-DmaConfig-DB-LLR-006*/
  HalNvicSetPriority(DMA_INSTANCE_IRQ, ZERO, ZERO);

  /*Enable the DMA STREAM global Interrupt*/
  HalNvicEnableIrq(DMA_INSTANCE_IRQ);

}

/*
 * Function                :  TransferComplete
 *
 * Description             :  This function is executed when the transfer complete interrupt
 *                            is generated.
 *
 * Formal parameter(s)     :  T_DMA_HANDLE *dma_handle - Pointer to the structure T_DMA_HANDLE.
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */

static void TransferComplete(T_DMA_HANDLE *dma_handle)
{


  if(ZERO == U32_data_length)
  {
    /*hdudispfdma2-TransferComplete-DB-LLR-001*/
    return;
  }
  else if(ONE == U32_data_length)
  {
   /*hdudispfdma2-TransferComplete-DB-LLR-002*/
   *((T_UINT32 *)U32_clr_address) = ZERO;
   U32_data_length = ZERO;
   return;

  }
  else
  {
   if(U32_data_length > CLEAR_SIZE)
   {
     /*hdudispfdma2-TransferComplete-DB-LLR-003*/
      HALDmaStartIT(dma_handle, (T_UINT32)U32_clear_data, U32_clr_address, CLEAR_SIZE);
      U32_clr_address = U32_clr_address + (CLEAR_SIZE * FOUR);
      U32_data_length = U32_data_length - CLEAR_SIZE;
   }
   else
   {
   /*hdudispfdma2-TransferComplete-DB-LLR-004*/
    HALDmaStartIT(dma_handle, (T_UINT32)U32_clear_data, U32_clr_address,
                                             U32_data_length);
    U32_data_length = ZERO;

   }
  }
  return;
}

/*
 * Function                :  TransferError
 *
 * Description             :  This function is executed when the transfer error interrupt
 *                            is generated during DMA transfer.
 *
 * Formal parameter(s)     :  None
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */

static void TransferError()
{
  /*hdudispfdma2-TransferError-DB-LLR-001*/
  Transfer_error_detected = ONE;
}

/*
 * Function                :  ErrorHandler
 *
 * Description             :  This function Handles the error.
 *
 * Formal parameter(s)     :  None
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */

static void ErrorHandler(void)
{
  /*hdudispfdma2-ErrorHandler-DB-LLR-001*/
  while (ONE)
  {
    HalDelay(THOUSAND);
  }
}

/*
 * Function                :  Dma2ClearForeground
 *
 * Description             :  This function clears the foreground from specified starting address
 *                            till the size specified.
 *
 * Formal parameter(s)     :  void *frame_buffer - IN Starting address of the frame.
 *                            T_UINT32 u32_bytes - IN Size in bytes.
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */

void Dma2ClearForeground(void *frame_buffer, T_UINT32 u32_bytes)
{

   /*hdudispfdma2-Dma2ClearForeground-DB-LLR-001*/
   U32_clr_address = (T_UINT32)frame_buffer;
   U32_data_length = u32_bytes/FOUR;

   TransferComplete(&Dma_handle);

}

/*
 * Function                :  Dma2Init
 *
 * Description             :  This function initializes the DMA controller.
 *
 * Formal parameter(s)     :  None
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */

void Dma2Init(void)
{
   /*hdudispfdma2-Dma2Init-DB-LLR-001*/
   DmaConfig();
}

