/*
 ******************************************************************************
 * License Information  :  Howell Instruments, Inc.                           *
 *                         "Licensed Software" and "All rights reserved".     *
 ******************************************************************************
 *  File                : hdulibstm32f7xxhaldma.c
 *
 *  Description         : This file provides firmware functions to manage the following
 *                        functionalities of the Direct Memory Access (DMA) peripheral:
 *                      - Initialization and de-initialization functions
 *                      - IO operation functions
 *                      - Peripheral State and errors functions
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
 *      1.1          Vinay H         26-Jul-2017             -
 *      1.2          Rona B.S        02-Sep-2017            100028  
 *
 * Additional References : None
 *
 *************************************************
 */

/* Includes */
#include "hdulibstm32f746xx.h"      /* Header files for HAL driver*/
#include "hdulibstm32f7xxhal.h"     /* Header files for HAL driver*/
#include "hdulibbasictypes.h"       /* Contains basic data types*/
#include "hdulibstm32f7xxhaldma.h"  /* Header files for DMA HAL driver*/

typedef struct
{
  __IO T_UINT32 ISR;       /* DMA interrupt status register */
  __IO T_UINT32 Reserved0;
  __IO T_UINT32 IFCR;      /* DMA interrupt flag clear register */
} T_DMA_BASE_REGISTERS;

#define HAL_TIMEOUT_DMA_ABORT    ((T_UINT32)5)  /* 5 ms */
#define CLR_IFCR                  0x3FU
#define DMA_FCR                  (T_UINT32)0x00000021U
#define TWO_HUNDRED_FIFTY_FIVE   0xFFU
#define THOUSAND_TWENTY_THREE    0x3FFU
#define NINETY_SIX_THOUSAND      9600U

static void DmaSetConfig(T_DMA_HANDLE *h_dma, T_UINT32 src_address, T_UINT32 dest_address,
                         T_UINT32 data_length);
static T_UINT32 DmaCalcBaseAndBitShift(T_DMA_HANDLE *h_dma);
static T_HAL_STATUS DmaCheckFifoParam(T_DMA_HANDLE *h_dma);

/*
 * Function                :  HalDmaInit
 *
 * Description             :  This function initializes the DMA according to the specified
 *                            parameters in the T_DMA_INIT.
 *
 * Formal parameter(s)     :  T_DMA_HANDLE* h_dma - INOUT pointer to a T_DMA_HANDLE structure 
 *                            that handles DMA.
 *
 * Return Value            :  T_HAL_STATUS - HAL status 
 *
 * Assumption              :  None
 *
 */

T_HAL_STATUS HalDmaInit(T_DMA_HANDLE *h_dma)
{
  T_UINT32 temp = ZERO;
  /*hdulibstm32f7xxhaldma-HalDmaInit-DB-LLR-001*/
  T_UINT32 tick_start = HALGetTick();
  T_DMA_BASE_REGISTERS *regs = {ZERO};

   /*hdulibstm32f7xxhaldma-HalDmaInit-DB-LLR-002*/
  /* Check the DMA peripheral state */
  if(NULL == h_dma)
  {
    return HAL_ERROR;
  }
  else
  {
     ;/*Do nothing*/
  }

   /*hdulibstm32f7xxhaldma-HalDmaInit-DB-LLR-003*/
  /* Allocate lock resource */
  __HAL_UNLOCK(h_dma);

   /*hdulibstm32f7xxhaldma-HalDmaInit-DB-LLR-004*/
  /* Change DMA peripheral state */
  h_dma->State = HAL_DMA_STATE_BUSY;

   /*hdulibstm32f7xxhaldma-HalDmaInit-DB-LLR-005*/
  /* Disable the peripheral */
  __HAL_DMA_DISABLE(h_dma);

  /* Check if the DMA Stream is effectively disabled */
  while((h_dma->Instance->CR & DMA_SXCR_EN) != RESET)
  {
      /*hdulibstm32f7xxhaldma-HalDmaInit-DB-LLR-006*/
    /* Check for the Timeout */
    if((HALGetTick() - tick_start ) > HAL_TIMEOUT_DMA_ABORT)
    {
      /* Update error code */
      h_dma->ErrorCode = HAL_DMA_ERROR_TIMEOUT;

      /* Change the DMA state */
      h_dma->State = HAL_DMA_STATE_TIMEOUT;

      return HAL_TIMEOUT;
    }
    else
    {
     ;/*Do nothing*/
    }
  }

   /*hdulibstm32f7xxhaldma-HalDmaInit-DB-LLR-007*/
  /* Get the CR register value */
  temp = h_dma->Instance->CR;

  /* Clear CHSEL, MBURST, PBURST, PL, MSIZE, PSIZE, MINC, PINC, CIRC, DIR, CT and DBM bits */
  temp &= ((T_UINT32)~(DMA_SXCR_CHSEL | DMA_SXCR_MBURST | DMA_SXCR_PBURST | \
                      DMA_SXCR_PL    | DMA_SXCR_MSIZE  | DMA_SXCR_PSIZE  | \
                      DMA_SXCR_MINC  | DMA_SXCR_PINC   | DMA_SXCR_CIRC   | \
                      DMA_SXCR_DIR   | DMA_SXCR_CT     | DMA_SXCR_DBM));

  /* Prepare the DMA Stream configuration */
  temp |=  h_dma->Init.Channel             | h_dma->Init.Direction        |
          h_dma->Init.PeriphInc           | h_dma->Init.MemInc           |
          h_dma->Init.PeriphDataAlignment | h_dma->Init.MemDataAlignment |
          h_dma->Init.Mode                | h_dma->Init.Priority;

  /* the Memory burst and peripheral burst are not used when the FIFO is disabled */
  if(DMA_FIFOMODE_ENABLE == h_dma->Init.FIFOMode)
  {
      /*hdulibstm32f7xxhaldma-HalDmaInit-DB-LLR-008*/
    /* Get memory burst and peripheral burst */
    temp |=  h_dma->Init.MemBurst | h_dma->Init.PeriphBurst;
  }
  else
  {
     ;/*Do nothing*/
  }
  
  /* Write to DMA Stream CR register */
  h_dma->Instance->CR = temp;

  /*hdulibstm32f7xxhaldma-HalDmaInit-DB-LLR-009*/
  /* Get the FCR register value */
  temp = h_dma->Instance->FCR;

  /* Clear Direct mode and FIFO threshold bits */
  temp &= (T_UINT32)~(DMA_SXFCR_DMDIS | DMA_SXFCR_FTH);

  /* Prepare the DMA Stream FIFO configuration */
  temp |= h_dma->Init.FIFOMode;

   /*hdulibstm32f7xxhaldma-HalDmaInit-DB-LLR-010*/
  /* the FIFO threshold is not used when the FIFO mode is disabled */
  if(DMA_FIFOMODE_ENABLE == h_dma->Init.FIFOMode)
  {
    /* Get the FIFO threshold */
    temp |= h_dma->Init.FIFOThreshold;

    if (DmaCheckFifoParam(h_dma) != HAL_OK)
    {
      /* Update error code */
      h_dma->ErrorCode = HAL_DMA_ERROR_PARAM;

      /* Change the DMA state */
      h_dma->State = HAL_DMA_STATE_READY;

      return HAL_ERROR;
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

  /* Write to DMA Stream FCR */
  h_dma->Instance->FCR = temp;

   /*hdulibstm32f7xxhaldma-HalDmaInit-DB-LLR-011*/
  /*
   * Initialize StreamBaseAddress and StreamIndex parameters to be used to calculate
   * DMA stream Base Address needed by HALDmaIrqHandler() and HAL_DMA_PollForTransfer()
   */
  regs = (T_DMA_BASE_REGISTERS *)DmaCalcBaseAndBitShift(h_dma);

  /* Clear all interrupt flags */
  regs->IFCR = CLR_IFCR << h_dma->StreamIndex;

   /*hdulibstm32f7xxhaldma-HalDmaInit-DB-LLR-012*/
  /* Initialize the error code */
  h_dma->ErrorCode = HAL_DMA_ERROR_NONE;

  /* Initialize the DMA state */
  h_dma->State = HAL_DMA_STATE_READY;

  return HAL_OK;
}

/*
 * Function                :  HALDmaDeInit
 *
 * Description             :  This function de-initializes the DMA peripheral
 *
 * Formal parameter(s)     :  T_DMA_HANDLE* h_dma - INOUT pointer to a T_DMA_HANDLE structure.
 *
 * Return Value            :  T_HAL_STATUS - HAL status 
 *
 * Assumption              :  None
 *
 */
T_HAL_STATUS HalDmaDeInit(T_DMA_HANDLE *h_dma)
{
  T_DMA_BASE_REGISTERS *regs = {ZERO};

   /*hdulibstm32f7xxhaldma-HALDmaDeInit-DB-LLR-001*/
  /* Check the DMA peripheral state */
  if(NULL == h_dma)
  {
    return HAL_ERROR;
  }
  else
  {
     ;/*Do nothing*/
  }

   /*hdulibstm32f7xxhaldma-HALDmaDeInit-DB-LLR-002*/
  /* Check the DMA peripheral state */
  if(HAL_DMA_STATE_BUSY == h_dma->State)
  {
    /* Return error status */
    return HAL_BUSY;
  }
  else
  {
     ;/*Do nothing*/
  }
   /*hdulibstm32f7xxhaldma-HALDmaDeInit-DB-LLR-003*/
  /* Disable the selected DMA Streamx */
  __HAL_DMA_DISABLE(h_dma);
  
   /*hdulibstm32f7xxhaldma-HALDmaDeInit-DB-LLR-004*/
  /* Reset DMA Streamx control register */
  h_dma->Instance->CR   = ZERO;

  /* Reset DMA Streamx number of data to transfer register */
  h_dma->Instance->NDTR = ZERO;

  /* Reset DMA Streamx peripheral address register */
  h_dma->Instance->PAR  = ZERO;

  /* Reset DMA Streamx memory 0 address register */
  h_dma->Instance->M0AR = ZERO;

  /* Reset DMA Streamx memory 1 address register */
  h_dma->Instance->M1AR = ZERO;

  /* Reset DMA Streamx FIFO control register */
  h_dma->Instance->FCR  = DMA_FCR;

   /*hdulibstm32f7xxhaldma-HALDmaDeInit-DB-LLR-005*/
  /* Get DMA stream Base Address */
  regs = (T_DMA_BASE_REGISTERS *)DmaCalcBaseAndBitShift(h_dma);

  /* Clear all interrupt flags at correct offset within the register */
  regs->IFCR = CLR_IFCR << h_dma->StreamIndex;

   /*hdulibstm32f7xxhaldma-HALDmaDeInit-DB-LLR-006*/
  /* Initialize the error code */
  h_dma->ErrorCode = HAL_DMA_ERROR_NONE;

  /* Initialize the DMA state */
  h_dma->State = HAL_DMA_STATE_RESET;

  /* Release Lock */
  __HAL_UNLOCK(h_dma);

  return HAL_OK;
}

/*
 * Function                :  HALDmaStartIT
 *
 * Description             :  This function Starts the DMA Transfer with interrupt enabled.
 *
 * Formal parameter(s)     :  T_DMA_HANDLE* h_dma - INOUT pointer to a T_DMA_HANDLE structure 
 *                            that handles CRC.
 *                            T_UINT32 src_address - IN The source memory Buffer address
 *                            T_UINT32 dest_address - IN The destination memory Buffer address
 *                            T_UINT32 data_length - IN The length of data to be transferred from
 *                            source to destination
 *
 * Return Value            :  T_HAL_STATUS - HAL status 
 *
 * Assumption              :  None
 *
 */
T_HAL_STATUS HALDmaStartIT(T_DMA_HANDLE *h_dma, T_UINT32 src_address, T_UINT32 dest_address,
                           T_UINT32 data_length)
{
  T_HAL_STATUS status = HAL_OK;

   /*hdulibstm32f7xxhaldma-HALDmaStartIT-DB-LLR-001*/
  /* calculate DMA base and stream number */
  T_DMA_BASE_REGISTERS *regs = (T_DMA_BASE_REGISTERS *)h_dma->StreamBaseAddress;

   /*hdulibstm32f7xxhaldma-HALDmaStartIT-DB-LLR-002*/
  /* Process locked */
  __HAL_LOCK(h_dma);

  if(HAL_DMA_STATE_READY == h_dma->State)
  {
     /*hdulibstm32f7xxhaldma-HALDmaStartIT-DB-LLR-003*/
    /* Change DMA peripheral state */
    h_dma->State = HAL_DMA_STATE_BUSY;

    /* Initialize the error code */
    h_dma->ErrorCode = HAL_DMA_ERROR_NONE;

    /* Configure the source, destination address and the data length */
    DmaSetConfig(h_dma, src_address, dest_address, data_length);

    /* Clear all interrupt flags at correct offset within the register */
    regs->IFCR = CLR_IFCR << h_dma->StreamIndex;

    /* Enable Common interrupts*/
    h_dma->Instance->CR  |= DMA_IT_TC | DMA_IT_TE | DMA_IT_DME;
    h_dma->Instance->FCR |= DMA_IT_FE;

    if(h_dma->XferHalfCpltCallback != NULL)
    {
      h_dma->Instance->CR  |= DMA_IT_HT;
    }
    else
    {
      ;/*Do Nothing*/
    }

    /* Enable the Peripheral */
    __HAL_DMA_ENABLE(h_dma);
  }
  else
  {
     /*hdulibstm32f7xxhaldma-HALDmaStartIT-DB-LLR-004*/
    /* Process unlocked */
    __HAL_UNLOCK(h_dma);

    /* Return error status */
    status = HAL_BUSY;
  }
   /*hdulibstm32f7xxhaldma-HALDmaStartIT-DB-LLR-005*/
  return status;
}

/*
 * Function                :  HALDmaIrqHandler
 *
 * Description             :  This function Handles DMA interrupt request.
 *
 * Formal parameter(s)     :  T_DMA_HANDLE* h_dma - INOUT pointer to a T_DMA_HANDLE structure
 *                            that handles CRC
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */
void HALDmaIrqHandler(T_DMA_HANDLE *h_dma)
{
  T_UINT32 tmp_isr = ZERO;
  __IO T_UINT32 count = ZERO;
  T_UINT32 timeout = (System_core_clock / NINETY_SIX_THOUSAND);

  /* calculate DMA base and stream number */
  T_DMA_BASE_REGISTERS *regs = (T_DMA_BASE_REGISTERS *)h_dma->StreamBaseAddress;

  tmp_isr = regs->ISR;

   /*hdulibstm32f7xxhaldma-HALDmaIrqHandler-DB-LLR-001*/
  /* Transfer Error Interrupt management*/
  if ((tmp_isr & (DMA_FLAG_TEIF0_4 << h_dma->StreamIndex)) != RESET)
  {
    if(__HAL_DMA_GET_IT_SOURCE(h_dma, DMA_IT_TE) != RESET)
    {
      /* Disable the transfer error interrupt */
      h_dma->Instance->CR  &= ~(DMA_IT_TE);

      /* Clear the transfer error flag */
      regs->IFCR = DMA_FLAG_TEIF0_4 << h_dma->StreamIndex;

      /* Update error code */
      h_dma->ErrorCode |= HAL_DMA_ERROR_TE;
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

   /*hdulibstm32f7xxhaldma-HALDmaIrqHandler-DB-LLR-002*/
  /* FIFO Error Interrupt management*/
  if ((tmp_isr & (DMA_FLAG_FEIF0_4 << h_dma->StreamIndex)) != RESET)
  {
    if(__HAL_DMA_GET_IT_SOURCE(h_dma, DMA_IT_FE) != RESET)
    {
      /* Clear the FIFO error flag */
      regs->IFCR = DMA_FLAG_FEIF0_4 << h_dma->StreamIndex;

      /* Update error code */
      h_dma->ErrorCode |= HAL_DMA_ERROR_FE;
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

   /*hdulibstm32f7xxhaldma-HALDmaIrqHandler-DB-LLR-003*/
  /* Direct Mode Error Interrupt management*/
  if ((tmp_isr & (DMA_FLAG_DMEIF0_4 << h_dma->StreamIndex)) != RESET)
  {
    if(__HAL_DMA_GET_IT_SOURCE(h_dma, DMA_IT_DME) != RESET)
    {
      /* Clear the direct mode error flag */
      regs->IFCR = DMA_FLAG_DMEIF0_4 << h_dma->StreamIndex;

      /* Update error code */
      h_dma->ErrorCode |= HAL_DMA_ERROR_DME;
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

  /* Half Transfer Complete Interrupt management*/
  if ((tmp_isr & (DMA_FLAG_HTIF0_4 << h_dma->StreamIndex)) != RESET)
  {
    if(__HAL_DMA_GET_IT_SOURCE(h_dma, DMA_IT_HT) != RESET)
    {
       /*hdulibstm32f7xxhaldma-HALDmaIrqHandler-DB-LLR-004*/
      /* Clear the half transfer complete flag */
      regs->IFCR = DMA_FLAG_HTIF0_4 << h_dma->StreamIndex;

      /* Multi_Buffering mode enabled */
      if(((h_dma->Instance->CR) & (T_UINT32)(DMA_SXCR_DBM)) != RESET)
      {
        /* Current memory buffer used is Memory 0 */
        if(RESET == (h_dma->Instance->CR & DMA_SXCR_CT))
        {
          if(h_dma->XferHalfCpltCallback != NULL)
          {
             /*hdulibstm32f7xxhaldma-HALDmaIrqHandler-DB-LLR-005*/
            /* Half transfer callback */
            h_dma->XferHalfCpltCallback(h_dma);
          }
          else
          {
            ;/*Do nothing*/
          }
        }
        /* Current memory buffer used is Memory 1 */
        else
        {
          if(h_dma->XferM1HalfCpltCallback != NULL)
          {
             /*hdulibstm32f7xxhaldma-HALDmaIrqHandler-DB-LLR-006*/
            /* Half transfer callback */
            h_dma->XferM1HalfCpltCallback(h_dma);
          }
          else
          {
            ;/*Do nothing*/
          }
        }
      }
      else
      {
        /* Disable the half transfer interrupt if the DMA mode is not CIRCULAR */
        if(RESET == (h_dma->Instance->CR & DMA_SXCR_CIRC))
        {
           /*hdulibstm32f7xxhaldma-HALDmaIrqHandler-DB-LLR-007*/
          /* Disable the half transfer interrupt */
          h_dma->Instance->CR  &= ~(DMA_IT_HT);
        }
        else
        {
         ;/*Do nothing*/
        }

        if(h_dma->XferHalfCpltCallback != NULL)
        {
           /*hdulibstm32f7xxhaldma-HALDmaIrqHandler-DB-LLR-008*/
          /* Half transfer callback */
          h_dma->XferHalfCpltCallback(h_dma);
        }
        else
        {
         ;/*Do nothing*/
        }
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

  /* Transfer Complete Interrupt management*/
  if ((tmp_isr & (DMA_FLAG_TCIF0_4 << h_dma->StreamIndex)) != RESET)
  {
    if(__HAL_DMA_GET_IT_SOURCE(h_dma, DMA_IT_TC) != RESET)
    {
       /*hdulibstm32f7xxhaldma-HALDmaIrqHandler-DB-LLR-009*/
      /* Clear the transfer complete flag */
      regs->IFCR = DMA_FLAG_TCIF0_4 << h_dma->StreamIndex;

      if(HAL_DMA_STATE_ABORT == h_dma->State)
      {
         /*hdulibstm32f7xxhaldma-HALDmaIrqHandler-DB-LLR-010*/
        /* Disable all the transfer interrupts */
        h_dma->Instance->CR  &= ~(DMA_IT_TC | DMA_IT_TE | DMA_IT_DME);
        h_dma->Instance->FCR &= ~(DMA_IT_FE);

        if((h_dma->XferHalfCpltCallback != NULL) || (h_dma->XferM1HalfCpltCallback != NULL))
        {
           /*hdulibstm32f7xxhaldma-HALDmaIrqHandler-DB-LLR-011*/
          h_dma->Instance->CR  &= ~(DMA_IT_HT);
        }
        else
        {
         ;/*Do nothing*/
        }

         /*hdulibstm32f7xxhaldma-HALDmaIrqHandler-DB-LLR-012*/
        /* Clear all interrupt flags at correct offset within the register */
        regs->IFCR = CLR_IFCR << h_dma->StreamIndex;

        /* Process Unlocked */
        __HAL_UNLOCK(h_dma);

        /* Change the DMA state */
        h_dma->State = HAL_DMA_STATE_READY;

        if(h_dma->XferAbortCallback != NULL)
        {
           /*hdulibstm32f7xxhaldma-HALDmaIrqHandler-DB-LLR-013*/
          h_dma->XferAbortCallback(h_dma);
        }
        else
        {
         ;/*Do nothing*/
        }
        return;
      }
      else
      {
         ;/*Do nothing*/
      }

      if(RESET != ((h_dma->Instance->CR) & (T_UINT32)(DMA_SXCR_DBM)))
      {
        /* Current memory buffer used is Memory 0 */
        if(RESET == (h_dma->Instance->CR & DMA_SXCR_CT))
        {
          if(h_dma->XferM1CpltCallback != NULL)
          {
             /*hdulibstm32f7xxhaldma-HALDmaIrqHandler-DB-LLR-014*/
            /* Transfer complete Callback for memory1 */
            h_dma->XferM1CpltCallback(h_dma);
          }
          else
          {
            ;/*Do nothing*/
          }
        }
        /* Current memory buffer used is Memory 1 */
        else
        {
          if(h_dma->XferCpltCallback != NULL)
          {
            /*hdulibstm32f7xxhaldma-HALDmaIrqHandler-DB-LLR-015*/
            /* Transfer complete Callback for memory0 */
            h_dma->XferCpltCallback(h_dma);
          }
          else
          {
            ;/*Do nothing*/
          }
        }
      }
      /* Disable the transfer complete interrupt if the DMA mode is not CIRCULAR */
      else
      {
        if(RESET == (h_dma->Instance->CR & DMA_SXCR_CIRC))
        {
           /*hdulibstm32f7xxhaldma-HALDmaIrqHandler-DB-LLR-016*/
          /* Disable the transfer complete interrupt */
          h_dma->Instance->CR  &= ~(DMA_IT_TC);

          /* Process Unlocked */
          __HAL_UNLOCK(h_dma);

          /* Change the DMA state */
          h_dma->State = HAL_DMA_STATE_READY;
        }
        else
        {
         ;/*Do nothing*/
        }

        if(h_dma->XferCpltCallback != NULL)
        {
           /*hdulibstm32f7xxhaldma-HALDmaIrqHandler-DB-LLR-017*/
          /* Transfer complete callback */
          h_dma->XferCpltCallback(h_dma);
        }
        else
        {
         ;/*Do nothing*/
        }
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

  /* manage error case */
  if(h_dma->ErrorCode != HAL_DMA_ERROR_NONE)
  {
    if((h_dma->ErrorCode & HAL_DMA_ERROR_TE) != RESET)
    {
       /*hdulibstm32f7xxhaldma-HALDmaIrqHandler-DB-LLR-018*/
      h_dma->State = HAL_DMA_STATE_ABORT;
      /* Disable the stream */
      __HAL_DMA_DISABLE(h_dma);
      /*hdulibstm32f7xxhaldma-HALDmaIrqHandler-DB-LLR-019*/
      do
      {
        if (++count > timeout)
        {

          break;
        }
        else
        {
         ;/*Do nothing*/
        }
      }
      while((h_dma->Instance->CR & DMA_SXCR_EN) != RESET);
      /* Process Unlocked */
      __HAL_UNLOCK(h_dma);
      /* Change the DMA state */
      h_dma->State = HAL_DMA_STATE_READY;
    }
      /*hdulibstm32f7xxhaldma-HALDmaIrqHandler-DB-LLR-020*/
    if(h_dma->XferErrorCallback != NULL)
    {
      /* Transfer error callback */
      h_dma->XferErrorCallback(h_dma);
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
}

/*
 * Function                :  HALDmaRegisterCallback
 *
 * Description             :  This function performs Register callback.
 *
 * Formal parameter(s)     :  T_DMA_HANDLE* h_dma - INOUT pointer to a T_DMA_HANDLE structure.
 *                            T_HAL_DMA_CALLBACK_ID callback_id - IN User Callback identifier
 *                            void (* p_callback)(T_DMA_HANDLE *_hdma) - pointer to private
 *                            callback  function which has pointer to a T_DMA_HANDLE structure
 *                            as parameter.
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */
T_HAL_STATUS HALDmaRegisterCallback(T_DMA_HANDLE *h_dma, T_HAL_DMA_CALLBACK_ID callback_id,
                                    void (* p_callback)(T_DMA_HANDLE *_h_dma))
{

  T_HAL_STATUS status = HAL_OK;

  /*hdulibstm32f7xxhaldma-HALDmaRegisterCallback-DB-LLR-001*/
  /* Process locked */
  __HAL_LOCK(h_dma);

  if(HAL_DMA_STATE_READY == h_dma->State)
  {
    switch(callback_id)
    {
    /*hdulibstm32f7xxhaldma-HALDmaRegisterCallback-DB-LLR-002*/
    case  HAL_DMA_XFER_CPLT_CB_ID:
      h_dma->XferCpltCallback = p_callback;
      break;

    /*hdulibstm32f7xxhaldma-HALDmaRegisterCallback-DB-LLR-003*/
    case  HAL_DMA_XFER_HALFCPLT_CB_ID:
      h_dma->XferHalfCpltCallback = p_callback;
      break;

    /*hdulibstm32f7xxhaldma-HALDmaRegisterCallback-DB-LLR-004*/
    case  HAL_DMA_XFER_M1CPLT_CB_ID:
      h_dma->XferM1CpltCallback = p_callback;
      break;

    /*hdulibstm32f7xxhaldma-HALDmaRegisterCallback-DB-LLR-005*/
    case  HAL_DMA_XFER_M1HALFCPLT_CB_ID:
      h_dma->XferM1HalfCpltCallback = p_callback;
      break;

    /*hdulibstm32f7xxhaldma-HALDmaRegisterCallback-DB-LLR-006*/
    case  HAL_DMA_XFER_ERROR_CB_ID:
      h_dma->XferErrorCallback = p_callback;
      break;

    /*hdulibstm32f7xxhaldma-HALDmaRegisterCallback-DB-LLR-007*/
    case  HAL_DMA_XFER_ABORT_CB_ID:
      h_dma->XferAbortCallback = p_callback;
      break;

    /*hdulibstm32f7xxhaldma-HALDmaRegisterCallback-DB-LLR-008*/
    default:
      break;
    }
  }
  else
  {
    /*hdulibstm32f7xxhaldma-HALDmaRegisterCallback-DB-LLR-009*/
   /* Return error status */
    status =  HAL_ERROR;
  }

  /*hdulibstm32f7xxhaldma-HALDmaRegisterCallback-DB-LLR-010*/
  /* Release Lock */
  __HAL_UNLOCK(h_dma);

  return status;
}

/*
 * Function                :  DmaSetConfig
 *
 * Description             :  This function Sets the DMA Transfer parameter.
 *
 * Formal parameter(s)     :  T_DMA_HANDLE* h_dma -INOUT pointer to a T_DMA_HANDLE structure.
 *                            T_UINT32 src_address -IN The source memory Buffer address
 *                            T_UINT32 dest_address -IN  The destination memory Buffer address
 *                            T_UINT32 data_length - IN The length of data to be transferred from
 *                            source to destination
 *
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */
static void DmaSetConfig(T_DMA_HANDLE *h_dma, T_UINT32 src_address, T_UINT32 dest_address,
                         T_UINT32 data_length)
{
  /*hdulibstm32f7xxhaldma-DmaSetConfig-DB-LLR-001*/
  /* Clear DBM bit */
  h_dma->Instance->CR &= (T_UINT32)(~DMA_SXCR_DBM);

  /*hdulibstm32f7xxhaldma-DmaSetConfig-DB-LLR-002*/
  /* Configure DMA Stream data length */
  h_dma->Instance->NDTR = data_length;

  /*hdulibstm32f7xxhaldma-DmaSetConfig-DB-LLR-003*/
  /* Peripheral to Memory */
  if(DMA_MEMORY_TO_PERIPH == (h_dma->Init.Direction))
  {
    /* Configure DMA Stream destination address */
    h_dma->Instance->PAR = dest_address;

    /* Configure DMA Stream source address */
    h_dma->Instance->M0AR = src_address;
  }
  /* Memory to Peripheral */
  else
  {
   /*hdulibstm32f7xxhaldma-DmaSetConfig-DB-LLR-004*/
    /* Configure DMA Stream source address */
    h_dma->Instance->PAR = src_address;

    /* Configure DMA Stream destination address */
    h_dma->Instance->M0AR = dest_address;
  }
}

/*
 * Function                :  DmaCalcBaseAndBitShift
 *
 * Description             :  This function Returns the DMA Stream base address depending
 *                            on stream number.
 *
 * Formal parameter(s)     :  T_DMA_HANDLE* h_dma -INOUT pointer to a T_DMA_HANDLE structure.
 *
 *
 * Return Value            :  T_UINT32 - DMA stream base address.
 *
 * Assumption              :  None
 *
 */
static T_UINT32 DmaCalcBaseAndBitShift(T_DMA_HANDLE *h_dma)
{
  /*hdulibstm32f7xxhaldma-DmaCalcBaseAndBitShift-DB-LLR-001*/
  T_UINT32 stream_number = (((T_UINT32)h_dma->Instance & TWO_HUNDRED_FIFTY_FIVE) \
                           - SIXTEEN) / TWENTY_FOUR;

  /* lookup table for necessary bitshift of flags within status registers */
  static const T_UINT8 flag_bit_shift_offset[8U] = {0U, 6U, 16U, 22U, 0U, 6U, 16U, 22U};
  /*hdulibstm32f7xxhaldma-DmaCalcBaseAndBitShift-DB-LLR-002*/
  h_dma->StreamIndex = flag_bit_shift_offset[stream_number];

  /*hdulibstm32f7xxhaldma-DmaCalcBaseAndBitShift-DB-LLR-003*/
  if (stream_number > THREE)
  {
    /* return pointer to HISR and HIFCR */
    h_dma->StreamBaseAddress = (((T_UINT32)h_dma->Instance & \
                              (T_UINT32)(~THOUSAND_TWENTY_THREE)) + FOUR);
  }
  else
  {
    /*hdulibstm32f7xxhaldma-DmaCalcBaseAndBitShift-DB-LLR-004*/
    /* return pointer to LISR and LIFCR */
    h_dma->StreamBaseAddress = ((T_UINT32)h_dma->Instance & (T_UINT32)(~THOUSAND_TWENTY_THREE));
  }

  /*hdulibstm32f7xxhaldma-DmaCalcBaseAndBitShift-DB-LLR-005*/
  return h_dma->StreamBaseAddress;
}

/*
 * Function                :  DmaCheckFifoParam
 *
 * Description             :  This function Checks compatibility between FIFO threshold level and
 *                            size of the memory burst
 *
 * Formal parameter(s)     :  T_DMA_HANDLE* h_dma -IN pointer to a T_DMA_HANDLE structure.
 *
 * Return Value            :  T_HAL_STATUS - HAL status
 *
 * Assumption              :  None
 *
 */
static T_HAL_STATUS DmaCheckFifoParam(T_DMA_HANDLE *h_dma)
{
  T_HAL_STATUS status = HAL_OK;
  T_UINT32 temp = h_dma->Init.FIFOThreshold;

  /* Memory Data size equal to Byte */
  if (DMA_MDATAALIGN_BYTE == h_dma->Init.MemDataAlignment)
  {
    switch (temp)
    {
      /*hdulibstm32f7xxhaldma-DmaCheckFifoParam-DB-LLR-001*/
      case DMA_FIFO_THRESHOLD_1QUARTERFULL:

        if (DMA_SXCR_MBURST_1 == (h_dma->Init.MemBurst & DMA_SXCR_MBURST_1))
        {
          status = HAL_ERROR;
        }
        else
        {
         ;/*Do nothing*/
        }
        break;

      /*hdulibstm32f7xxhaldma-DmaCheckFifoParam-DB-LLR-002*/
      case DMA_FIFO_THRESHOLD_HALFFULL:

        if (DMA_MBURST_INC16 == h_dma->Init.MemBurst)
        {
          status = HAL_ERROR;
        }
        else
        {
         ;/*Do nothing*/
        }
        break;

      /*hdulibstm32f7xxhaldma-DmaCheckFifoParam-DB-LLR-003*/
      case DMA_FIFO_THRESHOLD_3QUARTERSFULL:

        if (DMA_SXCR_MBURST_1 == (h_dma->Init.MemBurst & DMA_SXCR_MBURST_1))
        {
          status = HAL_ERROR;
        }
        else
        {
         ;/*Do nothing*/
        }
        break;

      /*hdulibstm32f7xxhaldma-DmaCheckFifoParam-DB-LLR-004*/
      case DMA_FIFO_THRESHOLD_FULL:
        break;

      /*hdulibstm32f7xxhaldma-DmaCheckFifoParam-DB-LLR-005*/
      default:
        break;
    }
  }

  /* Memory Data size equal to Half-Word */
  else if (DMA_MDATAALIGN_HALFWORD == h_dma->Init.MemDataAlignment)
  {
    switch (temp)
    {
      /*hdulibstm32f7xxhaldma-DmaCheckFifoParam-DB-LLR-006*/
      case DMA_FIFO_THRESHOLD_1QUARTERFULL:

        status = HAL_ERROR;
        break;

      /*hdulibstm32f7xxhaldma-DmaCheckFifoParam-DB-LLR-007*/
      case DMA_FIFO_THRESHOLD_HALFFULL:

        if ( DMA_SXCR_MBURST_1 == (h_dma->Init.MemBurst & DMA_SXCR_MBURST_1))
        {
          status = HAL_ERROR;
        }
        else
        {
         ;/*Do nothing*/
        }
        break;

      /*hdulibstm32f7xxhaldma-DmaCheckFifoParam-DB-LLR-008*/
      case DMA_FIFO_THRESHOLD_3QUARTERSFULL:

        status = HAL_ERROR;
        break;
        
      /*hdulibstm32f7xxhaldma-DmaCheckFifoParam-DB-LLR-009*/
      case DMA_FIFO_THRESHOLD_FULL:

        if ( DMA_MBURST_INC16 == h_dma->Init.MemBurst)
        {
          status = HAL_ERROR;
        }
        else
        {
         ;/*Do nothing*/
        }
        break;

      /*hdulibstm32f7xxhaldma-DmaCheckFifoParam-DB-LLR-010*/
      default:
        break;
    }
  }
  /* Memory Data size equal to Word */
  else
  {
    switch (temp)
    {
      /*hdulibstm32f7xxhaldma-DmaCheckFifoParam-DB-LLR-011*/
      case DMA_FIFO_THRESHOLD_1QUARTERFULL:
         status = HAL_ERROR;
         break;
      case DMA_FIFO_THRESHOLD_HALFFULL:
         status = HAL_ERROR;
         break;
      case DMA_FIFO_THRESHOLD_3QUARTERSFULL:

        status = HAL_ERROR;
        break;

      /*hdulibstm32f7xxhaldma-DmaCheckFifoParam-DB-LLR-012*/
      case DMA_FIFO_THRESHOLD_FULL:

        if (DMA_SXCR_MBURST_1 == (h_dma->Init.MemBurst & DMA_SXCR_MBURST_1))
        {
          status = HAL_ERROR;
        }
        else
        {
         ;/*do nothing*/
        }
      break;

      /*hdulibstm32f7xxhaldma-DmaCheckFifoParam-DB-LLR-013*/
      default:
        break;
    }
  }
  return status;
}
