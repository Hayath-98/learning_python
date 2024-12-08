/*
 ******************************************************************************
 * License Information  :  Howell Instruments, Inc.                           *
 *                         "Licensed Software" and "All rights reserved".     *
 ******************************************************************************
 *  File                : hdulibstm32f7xxhaldma2d.h
 *
 *  Description         : Header file of HAL DMA2D module.
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
 *      1.1          Rona B.S          12-Sep-2017          100064
 *      1.2          Divya G P         10-Oct-2017          100064
 *
 * Additional References : None
 *
 ******************************************************************************
 */


/* Define to prevent recursive inclusion */
#ifndef _HDULIBSTM32F7XXHALDMA2D_H_
#define _HDULIBSTM32F7XXHALDMA2D_H_

/* Includes */
#include "hdulibstm32f746xx.h" /* CMSIS STM32F7xx Device Peripheral Access Layer file*/
#include "hdulibstm32f7xxhalconf.h" /* contains HAL common defines,enum,macro and structures */
#include "hdulibstm32f7xxhaldef.h" /* contains common defines */

#define MAX_DMA2D_LAYER  2U


typedef struct
{
   T_UINT32 Blue; /*
                   * Configures the blue value.
                   * This parameter must be a number between Min_Data = 0x00 and Max_Data = 0xFF.
                   */

  T_UINT32 Green; /*
                   * Configures the green value.
                   * This parameter must be a number between Min_Data = 0x00 and Max_Data = 0xFF.
                   */

  T_UINT32 Red;   /*
                   * Configures the red value.
                   * This parameter must be a number between Min_Data = 0x00 and Max_Data = 0xFF.
                   */
} T_DMA2D_COLOR_TYPE;


typedef struct
{
  T_UINT32 *pCLUT;           /* Configures the DMA2D CLUT memory address.*/

  T_UINT32 CLUTColorMode;    /*
                              * Configures the DMA2D CLUT color mode.
                              * This parameter can be one value of @ref DMA2D_CLUT_CM.
                              */

  T_UINT32 Size;             /*
                              * Configures the DMA2D CLUT size.
                              * This parameter must be a number between Min_Data = 0x00
                              * and Max_Data = 0xFF.
                              */
} T_DMA2D_CLUT_CFG_TYPE;


typedef struct
{

   /*
    * Configures the DMA2D transfer mode.
    * This parameter can be one value of @ref DMA2D_Mode.
    */
   T_UINT32             Mode;

   /*
    * Configures the color format of the output image.
    * This parameter can be one value of DMA2D_Output_Color_Mode
    */
   T_UINT32             ColorMode;

   /*
    * Specifies the Offset value.
    * This parameter must be a number between Min_Data = 0x0000
    * and Max_Data = 0x3FFF.
    */
   T_UINT32             OutputOffset;

} T_DMA2D_INIT_TYPE;


typedef struct
{

   /*
    * Configures the DMA2D foreground or background offset.
    * This parameter must be a number between Min_Data = 0x0000
    * and Max_Data = 0x3FFF.
    */
   T_UINT32             InputOffset;

   /*
    * Configures the DMA2D foreground or background color mode.
    * This parameter can be one value of DMA2D_Input_Color_Mode
    */
   T_UINT32             InputColorMode;

   /*
    * Configures the DMA2D foreground or background alpha mode.
    * This parameter can be one value of @ref DMA2D_Alpha_Mode.
    */
   T_UINT32             AlphaMode;

   /*
    * Specifies the DMA2D foreground or background alpha value
    * and color value in case of A8 or A4 color mode.
    */
   T_UINT32             InputAlpha;

} T_DMA2D_LAYER_CFG;


typedef enum
{
  HAL_DMA2D_STATE_RESET             = 0x00U,    /* DMA2D not yet initialized or disabled     */
  HAL_DMA2D_STATE_READY             = 0x01U,    /* Peripheral Initialized and ready for use  */
  HAL_DMA2D_STATE_BUSY              = 0x02U,    /* An internal process is ongoing            */
  HAL_DMA2D_STATE_TIMEOUT           = 0x03U,    /* Timeout state                             */
  HAL_DMA2D_STATE_ERROR             = 0x04U,    /* DMA2D state error                         */
  HAL_DMA2D_STATE_SUSPEND           = 0x05U     /* DMA2D process is suspended                */
}T_HAL_DMA2D_STATE_TYPE;


typedef struct __DMA2D_HandleTypeDef
{
  /* DMA2D register base address.*/
  T_DMA2D               *Instance;

  /* DMA2D communication parameters.*/
  T_DMA2D_INIT_TYPE     Init;

  /* DMA2D transfer complete callback.*/
  void                  (* XferCpltCallback)(struct __DMA2D_HandleTypeDef * hdma2d);

   /* DMA2D transfer error callback.*/
  void                  (* XferErrorCallback)(struct __DMA2D_HandleTypeDef * hdma2d);

   /* DMA2D Layers parameters           */
  T_DMA2D_LAYER_CFG     LayerCfg[MAX_DMA2D_LAYER];

   /* DMA2D lock.*/
  T_HAL_LOCK            Lock;

  /* DMA2D transfer state.*/
  T_HAL_DMA2D_STATE_TYPE State;

   /* DMA2D error code.*/
  __IO T_UINT32               ErrorCode;

} T_DMA2D_HANDLE_TYPE;


/* Required left shift to set background alpha mode */
#define DMA2D_POSITION_BGPFCCR_AM      (T_UINT32)POSITION_VAL(DMA2D_BGPFCCR_AM)

/* Required left shift to set background alpha value */
#define DMA2D_POSITION_BGPFCCR_ALPHA   (T_UINT32)POSITION_VAL(DMA2D_BGPFCCR_ALPHA)

/* Required left shift to set pixels per lines value */
#define DMA2D_POSITION_NLR_PL          (T_UINT32)POSITION_VAL(DMA2D_NLR_PL)

/* No error             */
#define HAL_DMA2D_ERROR_NONE           ((T_UINT32)0x00000000U)

/* Transfer error       */
#define HAL_DMA2D_ERROR_TE             ((T_UINT32)0x00000001U)

/* Configuration error  */
#define HAL_DMA2D_ERROR_CE             ((T_UINT32)0x00000002U)

/* CLUT access error    */
#define HAL_DMA2D_ERROR_CAE            ((T_UINT32)0x00000004U)

/* DMA2D memory to memory with pixel format conversion transfer mode */
#define DMA2D_M2M_PFC                  DMA2D_CR_MODE_0

/* DMA2D memory to memory with blending transfer mode */
#define DMA2D_M2M_BLEND                DMA2D_CR_MODE_1

/* DMA2D register to memory transfer mode */
#define DMA2D_R2M                      DMA2D_CR_MODE

/* ARGB8888 DMA2D color mode */
#define DMA2D_OUTPUT_ARGB8888          ((T_UINT32)0x00000000U)

/* RGB888 DMA2D color mode   */
#define DMA2D_OUTPUT_RGB888            DMA2D_OPFCCR_CM_0

/* RGB565 DMA2D color mode   */
#define DMA2D_OUTPUT_RGB565            DMA2D_OPFCCR_CM_1

/* ARGB1555 DMA2D color mode */
#define DMA2D_OUTPUT_ARGB1555          (DMA2D_OPFCCR_CM_0|DMA2D_OPFCCR_CM_1)

/* ARGB4444 DMA2D color mode */
#define DMA2D_OUTPUT_ARGB4444          DMA2D_OPFCCR_CM_2

/* ARGB8888 color mode */
#define DMA2D_INPUT_ARGB8888           ((T_UINT32)0x00000000U)

/* RGB888 color mode   */
#define DMA2D_INPUT_RGB888             ((T_UINT32)0x00000001U)

/* RGB565 color mode   */
#define DMA2D_INPUT_RGB565             ((T_UINT32)0x00000002U)

/* ARGB1555 color mode */
#define DMA2D_INPUT_ARGB1555           ((T_UINT32)0x00000003U)

/* ARGB4444 color mode */
#define DMA2D_INPUT_ARGB4444           ((T_UINT32)0x00000004U)

/* L8 color mode       */
#define DMA2D_INPUT_L8                 ((T_UINT32)0x00000005U)

/* AL44 color mode     */
#define DMA2D_INPUT_AL44               ((T_UINT32)0x00000006U)

/* AL88 color mode     */
#define DMA2D_INPUT_AL88               ((T_UINT32)0x00000007U)

/* L4 color mode       */
#define DMA2D_INPUT_L4                 ((T_UINT32)0x00000008U)

/* A8 color mode       */
#define DMA2D_INPUT_A8                 ((T_UINT32)0x00000009U)

/* A4 color mode       */
#define DMA2D_INPUT_A4                 ((T_UINT32)0x0000000AU)

/* No modification of the alpha channel value */
#define DMA2D_NO_MODIF_ALPHA           ((T_UINT32)0x00000000U)

/* Replace original alpha channel value by programmed alpha value */
#define DMA2D_REPLACE_ALPHA            ((T_UINT32)0x00000001U)

/* Configuration Error Interrupt */
#define DMA2D_IT_CE                 DMA2D_CR_CEIE

/* CLUT Transfer Complete Interrupt */
#define DMA2D_IT_CTC                DMA2D_CR_CTCIE

/* CLUT Access Error Interrupt */
#define DMA2D_IT_CAE                DMA2D_CR_CAEIE

/* Transfer Watermark Interrupt */
#define DMA2D_IT_TW                 DMA2D_CR_TWIE

/* Transfer Complete Interrupt */
#define DMA2D_IT_TC                 DMA2D_CR_TCIE

/* Transfer Error Interrupt */
#define DMA2D_IT_TE                 DMA2D_CR_TEIE

/* Configuration Error Interrupt Flag */
#define DMA2D_FLAG_CE               DMA2D_ISR_CEIF

/* CLUT Transfer Complete Interrupt Flag */
#define DMA2D_FLAG_CTC              DMA2D_ISR_CTCIF

/* CLUT Access Error Interrupt Flag */
#define DMA2D_FLAG_CAE              DMA2D_ISR_CAEIF

/* Transfer Watermark Interrupt Flag */
#define DMA2D_FLAG_TW               DMA2D_ISR_TWIF

/* Transfer Complete Interrupt Flag */
#define DMA2D_FLAG_TC               DMA2D_ISR_TCIF

/* Transfer Error Interrupt Flag */
#define DMA2D_FLAG_TE               DMA2D_ISR_TEIF

#define __HAL_DMA2D_CLEAR_FLAG(__HANDLE__, __FLAG__) \
            ((__HANDLE__)->Instance->IFCR = (__FLAG__))

#define __HAL_DMA2D_DISABLE_IT(__HANDLE__, __INTERRUPT__) \
            ((__HANDLE__)->Instance->CR &= ~(__INTERRUPT__))

#define DMA2D_TIMEOUT_ABORT           ((T_UINT32)1000)
#define DMA2D_TIMEOUT_SUSPEND         ((T_UINT32)1000)

extern void HalDma2dIrqHandler(T_DMA2D_HANDLE_TYPE *h_dma2d);
extern void HalDma2dLineEventCallback(T_DMA2D_HANDLE_TYPE *h_dma2d);
extern void HalDma2dClutLdingCpltCallback(T_DMA2D_HANDLE_TYPE *h_dma2d);

#endif /* _HDULIBSTM32F7XXHALDMA2D_H_ */
