/*
 ******************************************************************************
 * License Information  :  Howell Instruments, Inc.                           *
 *                         "Licensed Software" and "All rights reserved".     *
 ******************************************************************************
 *  File                : hdulibstm32f7xxhaldma.h
 *
 *  Description         : Header file of DMA HAL module.
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
 ******************************************************************************
 */
#ifndef _HDULIBSTM32F7XXHALDMA_H_
#define _HDULIBSTM32F7XXHALDMA_H_

/* Includes */
#include "hdulibstm32f7xxhaldmaex.h"       /*Contains the DMA EX HAL module */
#include "hdulibstm32f7xxhaldef.h"         /*Contains the HAL defination module */
#include "hdulibstm32f746xx.h"   /*CMSIS Cortex-M7 Device Peripheral Access Layer Header File.*/
#include "hdulibcorecm7.h"       /*CMSIS Cortex-M7 Core Peripheral Access Layer Header File*/

typedef struct
{
  T_UINT32 Channel;    /*
                        * Specifies the channel used for the specified stream.
                        * This parameter can be a value of @ref DMAEx_Channel_selection
                        */

  T_UINT32 Direction;  /*
                        * Specifies if the data will be transferred from memory to peripheral,
                        * from memory to memory or from peripheral to memory.
                        * This parameter can be a value of @ref DMA_Data_transfer_direction
                        */

  T_UINT32 PeriphInc;  /*
                        * Specifies whether the Peripheral address register should be
                        * incremented or not.
                        * This parameter can be a value of @ref DMA_Peripheral_incremented_mode
                        */

  T_UINT32 MemInc;     /*
                        * Specifies whether the memory address register should be incremented
                        * or not.
                        * This parameter can be a value of @ref DMA_Memory_incremented_mode
                        */

  T_UINT32 PeriphDataAlignment;  /*
                                  * Specifies the Peripheral data width.
                                  * This parameter can be a value of @ref DMA_Peripheral_data_size
                                  */

  T_UINT32 MemDataAlignment;     /*
                                  * Specifies the Memory data width.
                                  * This parameter can be a value of @ref DMA_Memory_data_size
                                  */

  T_UINT32 Mode;          /*
                           * Specifies the operation mode of the DMAy Streamx.
                           * This parameter can be a value of @ref DMA_mode
                           * @note The circular buffer mode cannot be used if the memory-to-memory
                           * data transfer is configured on the selected Stream
                           */

  T_UINT32 Priority;      /*
                           * Specifies the software priority for the DMAy Streamx.
                           * This parameter can be a value of @ref DMA_Priority_level
                           */

  T_UINT32 FIFOMode;      /*
                           * Specifies if the FIFO mode or Direct mode will be used
                           * for the specified stream.
                           * This parameter can be a value of @ref DMA_FIFO_direct_mode
                           * @note The Direct mode (FIFO mode disabled) cannot be used if the
                           * memory-to-memory data transfer is configured on the selected stream
                           */

  T_UINT32 FIFOThreshold; /*
                           * Specifies the FIFO threshold level.
                           * This parameter can be a value of @ref DMA_FIFO_threshold_level
                           */

  T_UINT32 MemBurst;      /*
                           * Specifies the Burst transfer configuration for the memory transfers.
                           * It specifies the amount of data to be transferred in a single
                           * non interruptible
                           * transaction.
                           * This parameter can be a value of @ref DMA_Memory_burst
                           *  @note The burst mode is possible only if the address Increment
                           *  mode is enabled.
                           */

  T_UINT32 PeriphBurst;   /*
                           *Specifies the Burst transfer configuration for the peripheral transfers.
                           *    It specifies the amount of data to be transferred in a single
                           *     non interruptible
                           *     transaction.
                           *    This parameter can be a value of @ref DMA_Peripheral_burst
                           *    @note The burst mode is possible only if the address Increment
                           *    mode is enabled.
                           */
}T_DMA_INIT;

typedef enum
{
  HAL_DMA_STATE_RESET             = 0x00U,  /* DMA not yet initialized or disabled */
  HAL_DMA_STATE_READY             = 0x01U,  /* DMA initialized and ready for use   */
  HAL_DMA_STATE_BUSY              = 0x02U,  /* DMA process is ongoing*/
  HAL_DMA_STATE_TIMEOUT           = 0x03U,  /* DMA timeout state*/
  HAL_DMA_STATE_ERROR             = 0x04U,  /* DMA error state*/
  HAL_DMA_STATE_ABORT             = 0x05U  /* DMA Abort state*/
}T_HAL_DMA_STATE;

typedef enum
{
  HAL_DMA_FULL_TRANSFER      = 0x00U,    /* Full transfer*/
  HAL_DMA_HALF_TRANSFER      = 0x01U    /* Half Transfer*/
}T_HAL_DMA_LEVELCMPT;

typedef enum
{
  HAL_DMA_XFER_CPLT_CB_ID          = 0x00U,    /* Full transfer*/
  HAL_DMA_XFER_HALFCPLT_CB_ID      = 0x01U,    /* Half Transfer*/
  HAL_DMA_XFER_M1CPLT_CB_ID        = 0x02U,    /* M1 Full Transfer*/
  HAL_DMA_XFER_M1HALFCPLT_CB_ID    = 0x03U,    /* M1 Half Transfer*/
  HAL_DMA_XFER_ERROR_CB_ID         = 0x04U,    /* Error*/
  HAL_DMA_XFER_ABORT_CB_ID         = 0x05U,    /* Abort*/
  HAL_DMA_XFER_ALL_CB_ID           = 0x06U     /* All*/
}T_HAL_DMA_CALLBACK_ID;

typedef struct __T_DMA_HANDLE
{
  /* Register base address*/
  T_DMA_STREAM         *Instance;

  /* DMA communication parameters*/
  T_DMA_INIT            Init;

   /* DMA locking object*/
  T_HAL_LOCK            Lock;

 /* DMA transfer state*/
  __IO T_HAL_DMA_STATE  State;

  /* Parent object state*/
  void                       *Parent;

  /* DMA transfer complete callback*/
  void                       (* XferCpltCallback)( struct __T_DMA_HANDLE * hdma);

  /* DMA Half transfer complete callback*/
  void                       (* XferHalfCpltCallback)( struct __T_DMA_HANDLE * hdma);

 /* DMA transfer complete Memory1 callback*/
  void                       (* XferM1CpltCallback)( struct __T_DMA_HANDLE * hdma);

  /* DMA transfer Half complete Memory1 callback */
  void                       (* XferM1HalfCpltCallback)( struct __T_DMA_HANDLE * hdma);

  /* DMA transfer error callback*/
  void                       (* XferErrorCallback)( struct __T_DMA_HANDLE * hdma);

 /* DMA transfer Abort callback*/
  void                       (* XferAbortCallback)( struct __T_DMA_HANDLE * hdma);

 /* DMA Error code*/
 __IO T_UINT32               ErrorCode;

/* DMA Stream Base Address*/
 T_UINT32                    StreamBaseAddress;

  /* DMA Stream Index*/
 T_UINT32                    StreamIndex;

}T_DMA_HANDLE;

#define HAL_DMA_ERROR_NONE            ((T_UINT32)0x00000000U)    /* No error*/
#define HAL_DMA_ERROR_TE              ((T_UINT32)0x00000001U)    /* Transfer error*/
#define HAL_DMA_ERROR_FE              ((T_UINT32)0x00000002U)    /* FIFO error*/
#define HAL_DMA_ERROR_DME             ((T_UINT32)0x00000004U)    /* Direct Mode error*/
#define HAL_DMA_ERROR_TIMEOUT         ((T_UINT32)0x00000020U)    /* Timeout error*/
#define HAL_DMA_ERROR_PARAM           ((T_UINT32)0x00000040U)    /* Parameter error*/
 /* Abort requested with no Xfer ongoing*/
#define HAL_DMA_ERROR_NO_XFER         ((T_UINT32)0x00000080U)
#define HAL_DMA_ERROR_NOT_SUPPORTED   ((T_UINT32)0x00000100U)    /* Not supported mode*/

 /* Peripheral to memory direction */
#define DMA_PERIPH_TO_MEMORY         ((T_UINT32)0x00000000U)
 /* Memory to peripheral direction */
#define DMA_MEMORY_TO_PERIPH         ((T_UINT32)DMA_SXCR_DIR_0)
#define DMA_MEMORY_TO_MEMORY         ((T_UINT32)DMA_SXCR_DIR_1)  /* Memory to memory direction*/

#define DMA_PINC_ENABLE        ((T_UINT32)DMA_SXCR_PINC)  /* Peripheral increment mode enable  */
#define DMA_PINC_DISABLE       ((T_UINT32)0x00000000U)    /* Peripheral increment mode disable */

#define DMA_MINC_ENABLE         ((T_UINT32)DMA_SXCR_MINC)  /* Memory increment mode enable  */
#define DMA_MINC_DISABLE        ((T_UINT32)0x00000000U)    /* Memory increment mode disable */

/* Peripheral data alignment: Byte     */
#define DMA_PDATAALIGN_BYTE          ((T_UINT32)0x00000000U)
/* Peripheral data alignment: HalfWord */
#define DMA_PDATAALIGN_HALFWORD      ((T_UINT32)DMA_SXCR_PSIZE_0)
 /* Peripheral data alignment: Word     */
#define DMA_PDATAALIGN_WORD          ((T_UINT32)DMA_SXCR_PSIZE_1)

 /* Memory data alignment: Byte*/
#define DMA_MDATAALIGN_BYTE          ((T_UINT32)0x00000000U)
/* Memory data alignment: HalfWord */
#define DMA_MDATAALIGN_HALFWORD      ((T_UINT32)DMA_SXCR_MSIZE_0)
/* Memory data alignment: Word     */
#define DMA_MDATAALIGN_WORD          ((T_UINT32)DMA_SXCR_MSIZE_1)

#define DMA_NORMAL         ((T_UINT32)0x00000000U)       /* Normal mode                  */
#define DMA_CIRCULAR       ((T_UINT32)DMA_SXCR_CIRC)    /* Circular mode                */
#define DMA_PFCTRL         ((T_UINT32)DMA_SXCR_PFCTRL)  /* Peripheral flow control mode */

#define DMA_PRIORITY_LOW             ((T_UINT32)0x00000000U)     /* Priority level: Low*/
#define DMA_PRIORITY_MEDIUM          ((T_UINT32)DMA_SXCR_PL_0)  /* Priority level: Medium    */
#define DMA_PRIORITY_HIGH            ((T_UINT32)DMA_SXCR_PL_1)  /* Priority level: High      */
#define DMA_PRIORITY_VERY_HIGH       ((T_UINT32)DMA_SXCR_PL)    /* Priority level: Very High */

#define DMA_FIFOMODE_DISABLE        ((T_UINT32)0x00000000U)       /* FIFO mode disable */
#define DMA_FIFOMODE_ENABLE         ((T_UINT32)DMA_SXFCR_DMDIS)  /* FIFO mode enable  */

/* FIFO threshold 1 quart full configuration  */
#define DMA_FIFO_THRESHOLD_1QUARTERFULL       ((T_UINT32)0x00000000U)
/* FIFO threshold half full configuration     */
#define DMA_FIFO_THRESHOLD_HALFFULL           ((T_UINT32)DMA_SXFCR_FTH_0)
/* FIFO threshold 3 quarts full configuration */
#define DMA_FIFO_THRESHOLD_3QUARTERSFULL      ((T_UINT32)DMA_SXFCR_FTH_1)
/* FIFO threshold full configuration          */
#define DMA_FIFO_THRESHOLD_FULL               ((T_UINT32)DMA_SXFCR_FTH)

#define DMA_MBURST_SINGLE       ((T_UINT32)0x00000000U)
#define DMA_MBURST_INC4         ((T_UINT32)DMA_SXCR_MBURST_0)
#define DMA_MBURST_INC8         ((T_UINT32)DMA_SXCR_MBURST_1)
#define DMA_MBURST_INC16        ((T_UINT32)DMA_SXCR_MBURST)

#define DMA_PBURST_SINGLE       ((T_UINT32)0x00000000U)
#define DMA_PBURST_INC4         ((T_UINT32)DMA_SXCR_PBURST_0)
#define DMA_PBURST_INC8         ((T_UINT32)DMA_SXCR_PBURST_1)
#define DMA_PBURST_INC16        ((T_UINT32)DMA_SXCR_PBURST)

#define DMA_IT_TC                         ((T_UINT32)DMA_SXCR_TCIE)
#define DMA_IT_HT                         ((T_UINT32)DMA_SXCR_HTIE)
#define DMA_IT_TE                         ((T_UINT32)DMA_SXCR_TEIE)
#define DMA_IT_DME                        ((T_UINT32)DMA_SXCR_DMEIE)
#define DMA_IT_FE                         ((T_UINT32)0x00000080U)

#define DMA_FLAG_FEIF0_4                    ((T_UINT32)0x00800001U)
#define DMA_FLAG_DMEIF0_4                   ((T_UINT32)0x00800004U)
#define DMA_FLAG_TEIF0_4                    ((T_UINT32)0x00000008U)
#define DMA_FLAG_HTIF0_4                    ((T_UINT32)0x00000010U)
#define DMA_FLAG_TCIF0_4                    ((T_UINT32)0x00000020U)
#define DMA_FLAG_FEIF1_5                    ((T_UINT32)0x00000040U)
#define DMA_FLAG_DMEIF1_5                   ((T_UINT32)0x00000100U)
#define DMA_FLAG_TEIF1_5                    ((T_UINT32)0x00000200U)
#define DMA_FLAG_HTIF1_5                    ((T_UINT32)0x00000400U)
#define DMA_FLAG_TCIF1_5                    ((T_UINT32)0x00000800U)
#define DMA_FLAG_FEIF2_6                    ((T_UINT32)0x00010000U)
#define DMA_FLAG_DMEIF2_6                   ((T_UINT32)0x00040000U)
#define DMA_FLAG_TEIF2_6                    ((T_UINT32)0x00080000U)
#define DMA_FLAG_HTIF2_6                    ((T_UINT32)0x00100000U)
#define DMA_FLAG_TCIF2_6                    ((T_UINT32)0x00200000U)
#define DMA_FLAG_FEIF3_7                    ((T_UINT32)0x00400000U)
#define DMA_FLAG_DMEIF3_7                   ((T_UINT32)0x01000000U)
#define DMA_FLAG_TEIF3_7                    ((T_UINT32)0x02000000U)
#define DMA_FLAG_HTIF3_7                    ((T_UINT32)0x04000000U)
#define DMA_FLAG_TCIF3_7                    ((T_UINT32)0x08000000U)

#define __HAL_DMA_RESET_HANDLE_STATE(__HANDLE__) ((__HANDLE__)->State = HAL_DMA_STATE_RESET)

#define __HAL_DMA_GET_FS(__HANDLE__)      (((__HANDLE__)->Instance->FCR & (DMA_SXFCR_FS)))

#define __HAL_DMA_ENABLE(__HANDLE__)      ((__HANDLE__)->Instance->CR |=  DMA_SXCR_EN)

#define __HAL_DMA_DISABLE(__HANDLE__)     ((__HANDLE__)->Instance->CR &=  ~DMA_SXCR_EN)

#define __HAL_DMA_GET_TC_FLAG_INDEX(__HANDLE__) \
(((T_UINT32)((__HANDLE__)->Instance) == ((T_UINT32)DMA1_Stream0))? DMA_FLAG_TCIF0_4 :\
 ((T_UINT32)((__HANDLE__)->Instance) == ((T_UINT32)DMA2_Stream0))? DMA_FLAG_TCIF0_4 :\
 ((T_UINT32)((__HANDLE__)->Instance) == ((T_UINT32)DMA1_Stream4))? DMA_FLAG_TCIF0_4 :\
 ((T_UINT32)((__HANDLE__)->Instance) == ((T_UINT32)DMA2_Stream4))? DMA_FLAG_TCIF0_4 :\
 ((T_UINT32)((__HANDLE__)->Instance) == ((T_UINT32)DMA1_Stream1))? DMA_FLAG_TCIF1_5 :\
 ((T_UINT32)((__HANDLE__)->Instance) == ((T_UINT32)DMA2_Stream1))? DMA_FLAG_TCIF1_5 :\
 ((T_UINT32)((__HANDLE__)->Instance) == ((T_UINT32)DMA1_Stream5))? DMA_FLAG_TCIF1_5 :\
 ((T_UINT32)((__HANDLE__)->Instance) == ((T_UINT32)DMA2_Stream5))? DMA_FLAG_TCIF1_5 :\
 ((T_UINT32)((__HANDLE__)->Instance) == ((T_UINT32)DMA1_Stream2))? DMA_FLAG_TCIF2_6 :\
 ((T_UINT32)((__HANDLE__)->Instance) == ((T_UINT32)DMA2_Stream2))? DMA_FLAG_TCIF2_6 :\
 ((T_UINT32)((__HANDLE__)->Instance) == ((T_UINT32)DMA1_Stream6))? DMA_FLAG_TCIF2_6 :\
 ((T_UINT32)((__HANDLE__)->Instance) == ((T_UINT32)DMA2_Stream6))? DMA_FLAG_TCIF2_6 :\
   DMA_FLAG_TCIF3_7)

#define __HAL_DMA_GET_HT_FLAG_INDEX(__HANDLE__)\
(((T_UINT32)((__HANDLE__)->Instance) == ((T_UINT32)DMA1_Stream0))? DMA_FLAG_HTIF0_4 :\
 ((T_UINT32)((__HANDLE__)->Instance) == ((T_UINT32)DMA2_Stream0))? DMA_FLAG_HTIF0_4 :\
 ((T_UINT32)((__HANDLE__)->Instance) == ((T_UINT32)DMA1_Stream4))? DMA_FLAG_HTIF0_4 :\
 ((T_UINT32)((__HANDLE__)->Instance) == ((T_UINT32)DMA2_Stream4))? DMA_FLAG_HTIF0_4 :\
 ((T_UINT32)((__HANDLE__)->Instance) == ((T_UINT32)DMA1_Stream1))? DMA_FLAG_HTIF1_5 :\
 ((T_UINT32)((__HANDLE__)->Instance) == ((T_UINT32)DMA2_Stream1))? DMA_FLAG_HTIF1_5 :\
 ((T_UINT32)((__HANDLE__)->Instance) == ((T_UINT32)DMA1_Stream5))? DMA_FLAG_HTIF1_5 :\
 ((T_UINT32)((__HANDLE__)->Instance) == ((T_UINT32)DMA2_Stream5))? DMA_FLAG_HTIF1_5 :\
 ((T_UINT32)((__HANDLE__)->Instance) == ((T_UINT32)DMA1_Stream2))? DMA_FLAG_HTIF2_6 :\
 ((T_UINT32)((__HANDLE__)->Instance) == ((T_UINT32)DMA2_Stream2))? DMA_FLAG_HTIF2_6 :\
 ((T_UINT32)((__HANDLE__)->Instance) == ((T_UINT32)DMA1_Stream6))? DMA_FLAG_HTIF2_6 :\
 ((T_UINT32)((__HANDLE__)->Instance) == ((T_UINT32)DMA2_Stream6))? DMA_FLAG_HTIF2_6 :\
   DMA_FLAG_HTIF3_7)

#define __HAL_DMA_GET_TE_FLAG_INDEX(__HANDLE__)\
(((T_UINT32)((__HANDLE__)->Instance) == ((T_UINT32)DMA1_Stream0))? DMA_FLAG_TEIF0_4 :\
 ((T_UINT32)((__HANDLE__)->Instance) == ((T_UINT32)DMA2_Stream0))? DMA_FLAG_TEIF0_4 :\
 ((T_UINT32)((__HANDLE__)->Instance) == ((T_UINT32)DMA1_Stream4))? DMA_FLAG_TEIF0_4 :\
 ((T_UINT32)((__HANDLE__)->Instance) == ((T_UINT32)DMA2_Stream4))? DMA_FLAG_TEIF0_4 :\
 ((T_UINT32)((__HANDLE__)->Instance) == ((T_UINT32)DMA1_Stream1))? DMA_FLAG_TEIF1_5 :\
 ((T_UINT32)((__HANDLE__)->Instance) == ((T_UINT32)DMA2_Stream1))? DMA_FLAG_TEIF1_5 :\
 ((T_UINT32)((__HANDLE__)->Instance) == ((T_UINT32)DMA1_Stream5))? DMA_FLAG_TEIF1_5 :\
 ((T_UINT32)((__HANDLE__)->Instance) == ((T_UINT32)DMA2_Stream5))? DMA_FLAG_TEIF1_5 :\
 ((T_UINT32)((__HANDLE__)->Instance) == ((T_UINT32)DMA1_Stream2))? DMA_FLAG_TEIF2_6 :\
 ((T_UINT32)((__HANDLE__)->Instance) == ((T_UINT32)DMA2_Stream2))? DMA_FLAG_TEIF2_6 :\
 ((T_UINT32)((__HANDLE__)->Instance) == ((T_UINT32)DMA1_Stream6))? DMA_FLAG_TEIF2_6 :\
 ((T_UINT32)((__HANDLE__)->Instance) == ((T_UINT32)DMA2_Stream6))? DMA_FLAG_TEIF2_6 :\
   DMA_FLAG_TEIF3_7)

#define __HAL_DMA_GET_FE_FLAG_INDEX(__HANDLE__)\
(((T_UINT32)((__HANDLE__)->Instance) == ((T_UINT32)DMA1_Stream0))? DMA_FLAG_FEIF0_4 :\
 ((T_UINT32)((__HANDLE__)->Instance) == ((T_UINT32)DMA2_Stream0))? DMA_FLAG_FEIF0_4 :\
 ((T_UINT32)((__HANDLE__)->Instance) == ((T_UINT32)DMA1_Stream4))? DMA_FLAG_FEIF0_4 :\
 ((T_UINT32)((__HANDLE__)->Instance) == ((T_UINT32)DMA2_Stream4))? DMA_FLAG_FEIF0_4 :\
 ((T_UINT32)((__HANDLE__)->Instance) == ((T_UINT32)DMA1_Stream1))? DMA_FLAG_FEIF1_5 :\
 ((T_UINT32)((__HANDLE__)->Instance) == ((T_UINT32)DMA2_Stream1))? DMA_FLAG_FEIF1_5 :\
 ((T_UINT32)((__HANDLE__)->Instance) == ((T_UINT32)DMA1_Stream5))? DMA_FLAG_FEIF1_5 :\
 ((T_UINT32)((__HANDLE__)->Instance) == ((T_UINT32)DMA2_Stream5))? DMA_FLAG_FEIF1_5 :\
 ((T_UINT32)((__HANDLE__)->Instance) == ((T_UINT32)DMA1_Stream2))? DMA_FLAG_FEIF2_6 :\
 ((T_UINT32)((__HANDLE__)->Instance) == ((T_UINT32)DMA2_Stream2))? DMA_FLAG_FEIF2_6 :\
 ((T_UINT32)((__HANDLE__)->Instance) == ((T_UINT32)DMA1_Stream6))? DMA_FLAG_FEIF2_6 :\
 ((T_UINT32)((__HANDLE__)->Instance) == ((T_UINT32)DMA2_Stream6))? DMA_FLAG_FEIF2_6 :\
   DMA_FLAG_FEIF3_7)

#define __HAL_DMA_GET_DME_FLAG_INDEX(__HANDLE__)\
(((T_UINT32)((__HANDLE__)->Instance) == ((T_UINT32)DMA1_Stream0))? DMA_FLAG_DMEIF0_4 :\
 ((T_UINT32)((__HANDLE__)->Instance) == ((T_UINT32)DMA2_Stream0))? DMA_FLAG_DMEIF0_4 :\
 ((T_UINT32)((__HANDLE__)->Instance) == ((T_UINT32)DMA1_Stream4))? DMA_FLAG_DMEIF0_4 :\
 ((T_UINT32)((__HANDLE__)->Instance) == ((T_UINT32)DMA2_Stream4))? DMA_FLAG_DMEIF0_4 :\
 ((T_UINT32)((__HANDLE__)->Instance) == ((T_UINT32)DMA1_Stream1))? DMA_FLAG_DMEIF1_5 :\
 ((T_UINT32)((__HANDLE__)->Instance) == ((T_UINT32)DMA2_Stream1))? DMA_FLAG_DMEIF1_5 :\
 ((T_UINT32)((__HANDLE__)->Instance) == ((T_UINT32)DMA1_Stream5))? DMA_FLAG_DMEIF1_5 :\
 ((T_UINT32)((__HANDLE__)->Instance) == ((T_UINT32)DMA2_Stream5))? DMA_FLAG_DMEIF1_5 :\
 ((T_UINT32)((__HANDLE__)->Instance) == ((T_UINT32)DMA1_Stream2))? DMA_FLAG_DMEIF2_6 :\
 ((T_UINT32)((__HANDLE__)->Instance) == ((T_UINT32)DMA2_Stream2))? DMA_FLAG_DMEIF2_6 :\
 ((T_UINT32)((__HANDLE__)->Instance) == ((T_UINT32)DMA1_Stream6))? DMA_FLAG_DMEIF2_6 :\
 ((T_UINT32)((__HANDLE__)->Instance) == ((T_UINT32)DMA2_Stream6))? DMA_FLAG_DMEIF2_6 :\
   DMA_FLAG_DMEIF3_7)

#define __HAL_DMA_GET_FLAG(__HANDLE__, __FLAG__)\
(((T_UINT32)((__HANDLE__)->Instance) > (T_UINT32)DMA2_Stream3)? (DMA2->HISR & (__FLAG__)) :\
 ((T_UINT32)((__HANDLE__)->Instance) > (T_UINT32)DMA1_Stream7)? (DMA2->LISR & (__FLAG__)) :\
 ((T_UINT32)((__HANDLE__)->Instance) > (T_UINT32)DMA1_Stream3)? (DMA1->HISR & (__FLAG__)) :\
                                                               (DMA1->LISR & (__FLAG__)))
                                                               
#define __HAL_DMA_CLEAR_FLAG(__HANDLE__, __FLAG__) \
(((T_UINT32)((__HANDLE__)->Instance) > (T_UINT32)DMA2_Stream3)? (DMA2->HIFCR = (__FLAG__)) :\
 ((T_UINT32)((__HANDLE__)->Instance) > (T_UINT32)DMA1_Stream7)? (DMA2->LIFCR = (__FLAG__)) :\
 ((T_UINT32)((__HANDLE__)->Instance) > (T_UINT32)DMA1_Stream3)? (DMA1->HIFCR = (__FLAG__)) :\
                                       (DMA1->LIFCR = (__FLAG__)))

#define __HAL_DMA_ENABLE_IT(__HANDLE__, __INTERRUPT__)   (((__INTERRUPT__) != DMA_IT_FE)? \
((__HANDLE__)->Instance->CR |= (__INTERRUPT__)) : ((__HANDLE__)->Instance->FCR |= (__INTERRUPT__)))

#define __HAL_DMA_DISABLE_IT(__HANDLE__, __INTERRUPT__)  (((__INTERRUPT__) != DMA_IT_FE)? \
                                          ((__HANDLE__)->Instance->CR &= ~(__INTERRUPT__)) :\
                                          ((__HANDLE__)->Instance->FCR &= ~(__INTERRUPT__)))

#define __HAL_DMA_GET_IT_SOURCE(__HANDLE__, __INTERRUPT__)  (((__INTERRUPT__) != DMA_IT_FE)? \
                                             ((__HANDLE__)->Instance->CR & (__INTERRUPT__)) : \
                                             ((__HANDLE__)->Instance->FCR & (__INTERRUPT__)))

#define __HAL_DMA_SET_COUNTER(__HANDLE__, __COUNTER__) ((__HANDLE__)->Instance->NDTR = \
                                                   (T_UINT16)(__COUNTER__))

#define __HAL_DMA_GET_COUNTER(__HANDLE__) ((__HANDLE__)->Instance->NDTR)

T_HAL_STATUS HalDmaInit(T_DMA_HANDLE *hdma);
T_HAL_STATUS HalDmaDeInit(T_DMA_HANDLE *hdma);

T_HAL_STATUS HALDmaStartIT(T_DMA_HANDLE *hdma, T_UINT32 SrcAddress, T_UINT32 DstAddress,
                           T_UINT32 DataLength);
void              HALDmaIrqHandler(T_DMA_HANDLE *hdma);
T_HAL_STATUS HAL_DMA_CleanCallbacks(T_DMA_HANDLE *hdma);
T_HAL_STATUS HALDmaRegisterCallback(T_DMA_HANDLE *hdma, T_HAL_DMA_CALLBACK_ID CallbackID,
                                    void (* pCallback)(T_DMA_HANDLE *_hdma));

#define IS_DMA_DIRECTION(DIRECTION) (((DIRECTION) == DMA_PERIPH_TO_MEMORY ) || \
                                     ((DIRECTION) == DMA_MEMORY_TO_PERIPH)  || \
                                     ((DIRECTION) == DMA_MEMORY_TO_MEMORY))

#define IS_DMA_BUFFER_SIZE(SIZE) (((SIZE) >= 0x01U) && ((SIZE) < 0x10000U))

#define IS_DMA_PERIPHERAL_INC_STATE(STATE) (((STATE) == DMA_PINC_ENABLE) || \
                                            ((STATE) == DMA_PINC_DISABLE))

#define IS_DMA_MEMORY_INC_STATE(STATE) (((STATE) == DMA_MINC_ENABLE)  || \
                                        ((STATE) == DMA_MINC_DISABLE))

#define IS_DMA_PERIPHERAL_DATA_SIZE(SIZE) (((SIZE) == DMA_PDATAALIGN_BYTE)     || \
                                           ((SIZE) == DMA_PDATAALIGN_HALFWORD) || \
                                           ((SIZE) == DMA_PDATAALIGN_WORD))

#define IS_DMA_MEMORY_DATA_SIZE(SIZE) (((SIZE) == DMA_MDATAALIGN_BYTE)     || \
                                       ((SIZE) == DMA_MDATAALIGN_HALFWORD) || \
                                       ((SIZE) == DMA_MDATAALIGN_WORD ))

#define IS_DMA_MODE(MODE) (((MODE) == DMA_NORMAL )  || \
                           ((MODE) == DMA_CIRCULAR) || \
                           ((MODE) == DMA_PFCTRL))

#define IS_DMA_PRIORITY(PRIORITY) (((PRIORITY) == DMA_PRIORITY_LOW )   || \
                                   ((PRIORITY) == DMA_PRIORITY_MEDIUM) || \
                                   ((PRIORITY) == DMA_PRIORITY_HIGH)   || \
                                   ((PRIORITY) == DMA_PRIORITY_VERY_HIGH))

#define IS_DMA_FIFO_MODE_STATE(STATE) (((STATE) == DMA_FIFOMODE_DISABLE ) || \
                                       ((STATE) == DMA_FIFOMODE_ENABLE))

#define IS_DMA_FIFO_THRESHOLD(THRESHOLD) (((THRESHOLD) == DMA_FIFO_THRESHOLD_1QUARTERFULL ) || \
                                          ((THRESHOLD) == DMA_FIFO_THRESHOLD_HALFFULL)      || \
                                          ((THRESHOLD) == DMA_FIFO_THRESHOLD_3QUARTERSFULL) || \
                                          ((THRESHOLD) == DMA_FIFO_THRESHOLD_FULL))

#define IS_DMA_MEMORY_BURST(BURST) (((BURST) == DMA_MBURST_SINGLE) || \
                                    ((BURST) == DMA_MBURST_INC4)   || \
                                    ((BURST) == DMA_MBURST_INC8)   || \
                                    ((BURST) == DMA_MBURST_INC16))

#define IS_DMA_PERIPHERAL_BURST(BURST) (((BURST) == DMA_PBURST_SINGLE) || \
                                        ((BURST) == DMA_PBURST_INC4)   || \
                                        ((BURST) == DMA_PBURST_INC8)   || \
                                        ((BURST) == DMA_PBURST_INC16))

#endif /* _HDULIBSTM32F7XXHALDMA_H_ */

