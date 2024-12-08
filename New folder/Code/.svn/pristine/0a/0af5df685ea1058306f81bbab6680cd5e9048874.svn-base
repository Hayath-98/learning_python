/*
 ******************************************************************************
 * License Information  :  Howell Instruments, Inc.                           *
 *                         "Licensed Software" and "All rights reserved".     *
 ******************************************************************************
 *  File                : hdulibstm32f7xxhaldma2d.c
 *
 *  Description         : This file provides firmware functions to manage the following
 *                        functionalities of the DMA2D peripheral:
 *                        - Initialization and de-initialization functions
 *                        - IO operation functions
 *                        - Peripheral Control functions
 *                        - Peripheral State and Errors functions
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
 * <Version No.>     <Author>          <Date>         <Problem Report No.>
 *
 *      1.1          Rona B.S          12-Sep-2017            100064
 *      1.2          Divya G P         09-Oct-2017            100064
 *
 * Additional References : None
 *
 ******************************************************************************
 */

/* Includes*/
#include "hdulibstm32f7xxhaldma2d.h" /* Defines DMA2D specification */
#include "hdulibstm32f7xxhal.h" /* Header files for HAL driver*/

/*
 * Function                :  HalDma2dIrqHandler
 *
 * Description             :  This function handles DMA2D interrupt request.
 *
 * Formal parameter(s)     :  T_DMA2D_HANDLE_TYPE *h_dma2d - IN/OUT Pointer to a
 *                            T_DMA2D_HANDLE_TYPE structure  that contains the
 *                            configuration information for the DMA2D.
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */

void HalDma2dIrqHandler(T_DMA2D_HANDLE_TYPE *h_dma2d)
{
   T_UINT32 isr_flags = READ_REG(h_dma2d->Instance->ISR);
   T_UINT32 cr_flags = READ_REG(h_dma2d->Instance->CR);

   /* Transfer Error Interrupt management*/
   if (RESET != (isr_flags & DMA2D_FLAG_TE))
   {
      if ( RESET != (cr_flags & DMA2D_IT_TE))
      {
         /* hdulibstm32f7xxhaldma2d-HalDma2dIrqHandler-DB-LLR-001 */
         /* Disable the transfer Error interrupt */
         __HAL_DMA2D_DISABLE_IT(h_dma2d, DMA2D_IT_TE);

         /* Update error code */
         h_dma2d->ErrorCode |= HAL_DMA2D_ERROR_TE;

         /* Clear the transfer error flag */
         __HAL_DMA2D_CLEAR_FLAG(h_dma2d, DMA2D_FLAG_TE);

         /* Change DMA2D state */
         h_dma2d->State = HAL_DMA2D_STATE_ERROR;

         /* Process Unlocked */
         __HAL_UNLOCK(h_dma2d);


         /* hdulibstm32f7xxhaldma2d-HalDma2dIrqHandler-DB-LLR-002 */
         if(NULL != h_dma2d->XferErrorCallback)
         {
            /* Transfer error Callback */
            h_dma2d->XferErrorCallback(h_dma2d);
         }
         else
         {
            ; /* Do nothing */
         }
      }
      else
      {
         ; /* Do nothing */
      }
   }
   else
   {
      ; /* Do nothing */
   }

   /* Configuration Error Interrupt management*/
   if (RESET != (isr_flags & DMA2D_FLAG_CE))
   {
      if (RESET != (cr_flags & DMA2D_IT_CE))
      {
         /* hdulibstm32f7xxhaldma2d-HalDma2dIrqHandler-DB-LLR-003 */
         /* Disable the Configuration Error interrupt */
         __HAL_DMA2D_DISABLE_IT(h_dma2d, DMA2D_IT_CE);

         /* Clear the Configuration error flag */
         __HAL_DMA2D_CLEAR_FLAG(h_dma2d, DMA2D_FLAG_CE);

         /* Update error code */
         h_dma2d->ErrorCode |= HAL_DMA2D_ERROR_CE;

         /* Change DMA2D state */
         h_dma2d->State = HAL_DMA2D_STATE_ERROR;

         /* Process Unlocked */
         __HAL_UNLOCK(h_dma2d);

         /* hdulibstm32f7xxhaldma2d-HalDma2dIrqHandler-DB-LLR-004 */
         if(NULL != h_dma2d->XferErrorCallback )
         {
            /* Transfer error Callback */
            h_dma2d->XferErrorCallback(h_dma2d);
         }
         else
         {
            ; /* Do nothing */
         }
      }
      else
      {
         ; /* Do nothing */
      }
   }
   else
   {
      ; /* Do nothing */
   }

   /* CLUT access Error Interrupt management*/
   if (RESET != (isr_flags & DMA2D_FLAG_CAE))
   {
      if (RESET != (cr_flags & DMA2D_IT_CAE))
      {
         /* hdulibstm32f7xxhaldma2d-HalDma2dIrqHandler-DB-LLR-005 */
         /* Disable the CLUT access error interrupt */
         __HAL_DMA2D_DISABLE_IT(h_dma2d, DMA2D_IT_CAE);

         /* Clear the CLUT access error flag */
         __HAL_DMA2D_CLEAR_FLAG(h_dma2d, DMA2D_FLAG_CAE);

         /* Update error code */
         h_dma2d->ErrorCode |= HAL_DMA2D_ERROR_CAE;

         /* Change DMA2D state */
         h_dma2d->State = HAL_DMA2D_STATE_ERROR;

         /* Process Unlocked */
         __HAL_UNLOCK(h_dma2d);

         /* hdulibstm32f7xxhaldma2d-HalDma2dIrqHandler-DB-LLR-006 */
         if(NULL != h_dma2d->XferErrorCallback)
         {
            /* Transfer error Callback */
            h_dma2d->XferErrorCallback(h_dma2d);
         }
         else
         {
            ; /* Do nothing */
         }
      }
      else
      {
      ; /* Do nothing */
      }
   }
   else
   {
      ; /* Do nothing */
   }

   /* Transfer watermark Interrupt management*/
   if (RESET != (isr_flags & DMA2D_FLAG_TW))
   {
      if (RESET != (cr_flags & DMA2D_IT_TW) )
      {
         /* hdulibstm32f7xxhaldma2d-HalDma2dIrqHandler-DB-LLR-007 */
         /* Disable the transfer watermark interrupt */
         __HAL_DMA2D_DISABLE_IT(h_dma2d, DMA2D_IT_TW);

         /* Clear the transfer watermark flag */
         __HAL_DMA2D_CLEAR_FLAG(h_dma2d, DMA2D_FLAG_TW);

         /* Transfer watermark Callback */
         HalDma2dLineEventCallback(h_dma2d);
      }
      else
      {
         ; /* Do nothing */
      }
   }
   else
   {
      ; /* Do nothing */
   }

   /* Transfer Complete Interrupt management*/
   if (RESET != (isr_flags & DMA2D_FLAG_TC))
   {
      if (RESET != (cr_flags & DMA2D_IT_TC))
      {
         /* hdulibstm32f7xxhaldma2d-HalDma2dIrqHandler-DB-LLR-008 */
         /* Disable the transfer complete interrupt */
         __HAL_DMA2D_DISABLE_IT(h_dma2d, DMA2D_IT_TC);

         /* Clear the transfer complete interrupt flag */
         __HAL_DMA2D_CLEAR_FLAG(h_dma2d, DMA2D_FLAG_TC);

         /* Update error code */
         h_dma2d->ErrorCode |= HAL_DMA2D_ERROR_NONE;

         /* Change DMA2D state */
         h_dma2d->State = HAL_DMA2D_STATE_READY;

         /* Process Unlocked */
         __HAL_UNLOCK(h_dma2d);

         /* hdulibstm32f7xxhaldma2d-HalDma2dIrqHandler-DB-LLR-009 */
         if(NULL != h_dma2d->XferCpltCallback)
         {
            /* Transfer complete Callback */
            h_dma2d->XferCpltCallback(h_dma2d);
         }
         else
         {
            ; /* Do nothing */
         }
      }
      else
      {
         ; /* Do nothing */
      }
   }
   else
   {
      ; /* Do nothing */
   }

   /* CLUT Transfer Complete Interrupt management*/
   if (RESET != (isr_flags & DMA2D_FLAG_CTC) )
   {
      if (RESET != (cr_flags & DMA2D_IT_CTC))
      {
         /* hdulibstm32f7xxhaldma2d-HalDma2dIrqHandler-DB-LLR-010 */
         /* Disable the CLUT transfer complete interrupt */
         __HAL_DMA2D_DISABLE_IT(h_dma2d, DMA2D_IT_CTC);

         /* Clear the CLUT transfer complete interrupt flag */
         __HAL_DMA2D_CLEAR_FLAG(h_dma2d, DMA2D_FLAG_CTC);

         /* Update error code */
         h_dma2d->ErrorCode |= HAL_DMA2D_ERROR_NONE;

         /* Change DMA2D state */
         h_dma2d->State = HAL_DMA2D_STATE_READY;

         /* Process Unlocked */
         __HAL_UNLOCK(h_dma2d);

         /* CLUT Transfer complete Callback */
         HalDma2dClutLdingCpltCallback(h_dma2d);
      }
      else
      {
         ; /* Do nothing */
      }
   }
   else
   {
      ; /* Do nothing */
   }
}

/*
 * Function                :  HalDma2dLineEventCallback
 *
 * Description             :  This function transfers watermark callback.
 *
 * Formal parameter(s)     :  T_DMA2D_HANDLE_TYPE *h_dma2d -IN pointer to a
 *                            T_DMA2D_HANDLE_TYPE structure that contains the configuration
 *                            information for the DMA2D.
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */

void HalDma2dLineEventCallback(T_DMA2D_HANDLE_TYPE *h_dma2d)
{
   /* hdulibstm32f7xxhaldma2d-HalDma2dLineEventCallback-DB-LLR-001 */
   /* Prevent unused argument(s) compilation warning */
   UNUSED(h_dma2d);
}


/*
 * Function                :  HalDma2dClutLdingCpltCallback
 *
 * Description             :  This function performs CLUT Transfer Complete callback.
 *
 * Formal parameter(s)     :  T_DMA2D_HANDLE_TYPE *h_dma2d -IN pointer to a T_DMA2D_HANDLE_TYPE
 *                            structure that contains the configuration
 *                            information for the DMA2D.
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */

void HalDma2dClutLdingCpltCallback(T_DMA2D_HANDLE_TYPE *h_dma2d)
{
   /* hdulibstm32f7xxhaldma2d-HalDma2dClutLdingCpltCallback-DB-LLR-001 */
   /* Prevent unused argument(s) compilation warning */
   UNUSED(h_dma2d);

}

