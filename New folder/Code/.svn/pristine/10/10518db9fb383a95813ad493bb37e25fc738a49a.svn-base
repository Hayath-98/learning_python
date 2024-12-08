/*
 ******************************************************************************
 * License Information  :  Howell Instruments, Inc.                           *
 *                         "Licensed Software" and "All rights reserved".     *
 ******************************************************************************
 *  File                : hdulibstm32f7xxhalltdc.h
 *
 *  Description         : Header file of LTDC HAL module.
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
 *      1.2          Shilpa A R      02-Oct-2017           100064
 *      1.3          Divya G P       10-Oct-2017           100064
 *
 * Additional References : None
 *
 ******************************************************************************
 */

/* Define to prevent recursive inclusion*/
#ifndef _HDULIBSTM32F7XXHALLTDC_H_
#define _HDULIBSTM32F7XXHALLTDC_H_

/* Includes */
#include "hdulibstm32f7xxhaldef.h"     /* Header file of CORTEX HAL module */
#include "hdulibstm32f746xx.h"         /* CMSIS Cortex-M7 Device Peripheral Access Layer */
#include "hdulibstm32f7xx.h"           /* Header files for HAL driver*/
#include "hdulibcorecm7.h"             /* Cortex-M7 processor and core peripherals */

#if defined (STM32F746xx) || defined (STM32F756xx) || defined (STM32F767xx) || \
            defined (STM32F769xx) || defined (STM32F777xx) || defined (STM32F779xx)

#define MAX_LAYER  2U

typedef struct
{
   /*
    * Configures the blue value.
    * This parameter must be a number between Min_Data = 0x00 and Max_Data = 0xFF.
    */
   T_UINT8 Blue;

   /*
    * Configures the green value.
    * This parameter must be a number between Min_Data = 0x00 and Max_Data = 0xFF.
    */
   T_UINT8 Green;

   /*
    * Configures the red value.
    * This parameter must be a number between Min_Data = 0x00 and Max_Data = 0xFF.
    */
   T_UINT8 Red;

   T_UINT8 Reserved;                /* Reserved 0xFF */
} T_LTDC_COLOR;

typedef struct
{
   /*
    * configures the horizontal synchronization polarity.
    * This parameter can be one value of @ref LTDC_HS_POLARITY
    */
   T_UINT32            HSPolarity;

   /*
    * configures the vertical synchronization polarity.
    * This parameter can be one value of @ref LTDC_VS_POLARITY
    */
   T_UINT32            VSPolarity;

   /*
    * configures the data enable polarity.
    * This parameter can be one of value of @ref LTDC_DE_POLARITY
    */
   T_UINT32            DEPolarity;

   /*
    * configures the pixel clock polarity.
    * This parameter can be one of value of @ref LTDC_PC_POLARITY
    */
   T_UINT32            PCPolarity;

   /*
    * configures the number of Horizontal synchronization width.
    * This parameter must be a number between Min_Data = 0x000 and Max_Data = 0xFFF.
    */
   T_UINT32            HorizontalSync;

   /*
    * configures the number of Vertical synchronization height.
    * This parameter must be a number between Min_Data = 0x000 and Max_Data = 0x7FF.
    */
   T_UINT32            VerticalSync;

   /*
    * configures the accumulated horizontal back porch width.
    * This parameter must be a number between Min_Data = LTDC_HorizontalSync and Max_Data = 0xFFF.
    */
   T_UINT32            AccumulatedHBP;

   /*
    * configures the accumulated vertical back porch height.
    * This parameter must be a number between Min_Data = LTDC_VerticalSync and Max_Data = 0x7FF.
    */
   T_UINT32            AccumulatedVBP;

   /*
    * configures the accumulated active width.
    * This parameter must be a number between Min_Data = LTDC_AccumulatedHBP and Max_Data = 0xFFF.
    */
   T_UINT32            AccumulatedActiveW;

   /*
    * configures the accumulated active height.
    * This parameter must be a number between Min_Data = LTDC_AccumulatedVBP and Max_Data = 0x7FF.
    */
   T_UINT32            AccumulatedActiveH;

   /*
    * configures the total width.
    * This parameter must be a number between Min_Data = LTDC_AccumulatedActiveW
    * and Max_Data = 0xFFF.
    */
   T_UINT32            TotalWidth;

   /*
    * configures the total height.
    * This parameter must be a number between Min_Data = LTDC_AccumulatedActiveH
    * and Max_Data = 0x7FF.
    */
   T_UINT32            TotalHeigh;

  T_LTDC_COLOR   Backcolor;    /* Configures the background color. */
} T_LTDC_INIT;

typedef struct
{
   /*
    * Configures the Window Horizontal Start Position.
    * This parameter must be a number between Min_Data = 0x000 and Max_Data = 0xFFF.
    */
   T_UINT32 WindowX0;

   /*
    * Configures the Window Horizontal Stop Position.
    * This parameter must be a number between Min_Data = 0x000 and Max_Data = 0xFFF.
    */
   T_UINT32 WindowX1;

   /*
    * Configures the Window vertical Start Position.
    * This parameter must be a number between Min_Data = 0x000 and Max_Data = 0x7FF.
    */
   T_UINT32 WindowY0;

   /*
    * Configures the Window vertical Stop Position.
    * This parameter must be a number between Min_Data = 0x0000 and Max_Data = 0x7FF.
    */
   T_UINT32 WindowY1;

   /*
    * Specifies the pixel format.
    * This parameter can be one of value of @ref LTDC_Pixelformat
    */
   T_UINT32 PixelFormat;

   /*
    * Specifies the constant alpha used for blending.
    * This parameter must be a number between Min_Data = 0x00 and Max_Data = 0xFF.
    */
   T_UINT32 Alpha;

   /*
    * Configures the default alpha value.
    * This parameter must be a number between Min_Data = 0x00 and Max_Data = 0xFF.
    */
   T_UINT32 Alpha0;

   /*
    * Select the blending factor 1.
    * This parameter can be one of value of @ref LTDC_BlendingFactor1
    */
   T_UINT32 BlendingFactor1;

   /*
    * Select the blending factor 2.
    * This parameter can be one of value of @ref LTDC_BlendingFactor2
    */
   T_UINT32 BlendingFactor2;

   T_UINT32 FBStartAdress;              /* Configures the color frame buffer address */

   /*
    * Configures the color frame buffer line length.
    * This parameter must be a number between Min_Data = 0x0000 and Max_Data = 0x1FFF.
    */
   T_UINT32 ImageWidth;

   /*
    * Specifies the number of line in frame buffer.
    * This parameter must be a number between Min_Data = 0x000 and Max_Data = 0x7FF.
    */
   T_UINT32 ImageHeight;

   T_LTDC_COLOR   Backcolor;       /* Configures the layer background color. */
} T_LTDC_LAYERCFG;

typedef enum
{
   HAL_LTDC_STATE_RESET             = 0x00U,    /* LTDC not yet initialized or disabled */
   HAL_LTDC_STATE_READY             = 0x01U,    /* LTDC initialized and ready for use */
   HAL_LTDC_STATE_BUSY              = 0x02U,    /* LTDC internal process is ongoing */
   HAL_LTDC_STATE_TIMEOUT           = 0x03U,    /* LTDC Timeout state  */
   HAL_LTDC_STATE_ERROR             = 0x04U     /* LTDC state error  */
}T_HAL_LTDC_STATE;

typedef struct
{
   T_LTDC                *Instance;                /* LTDC Register base address */

   T_LTDC_INIT            Init;                     /* LTDC parameters */

   T_LTDC_LAYERCFG       LayerCfg[MAX_LAYER];      /* LTDC Layers parameters */

   T_HAL_LOCK            Lock;                     /* LTDC Lock */

   __IO T_HAL_LTDC_STATE  State;                   /* LTDC state  */

   __IO T_UINT32          ErrorCode;               /* LTDC Error code */

} T_LTDC_HANDLE;

#define HAL_LTDC_ERROR_NONE      ((T_UINT32)0x00000000U)    /* LTDC No error  */
#define HAL_LTDC_ERROR_TE        ((T_UINT32)0x00000001U)    /* LTDC Transfer error */
#define HAL_LTDC_ERROR_FU        ((T_UINT32)0x00000002U)    /* LTDC FIFO Underrun  */
#define HAL_LTDC_ERROR_TIMEOUT   ((T_UINT32)0x00000020U)    /* LTDC Timeout error  */
/* Horizontal Synchronization is active low. */
#define LTDC_HSPOLARITY_AL       ((T_UINT32)0x00000000U)
/* Horizontal Synchronization is active high. */
#define LTDC_HSPOLARITY_AH       LTDC_GCR_HSPOL
/* Vertical Synchronization is active low. */
#define LTDC_VSPOLARITY_AL       ((T_UINT32)0x00000000U)
/* Vertical Synchronization is active high. */
#define LTDC_VSPOLARITY_AH       LTDC_GCR_VSPOL
#define LTDC_DEPOLARITY_AL       ((T_UINT32)0x00000000U)    /* Data Enable, is active low. */
#define LTDC_DEPOLARITY_AH       LTDC_GCR_DEPOL             /* Data Enable, is active high. */
#define LTDC_PCPOLARITY_IPC      ((T_UINT32)0x00000000U)    /* input pixel clock. */
#define LTDC_PCPOLARITY_IIPC     LTDC_GCR_PCPOL             /* inverted input pixel clock. */
#define LTDC_HORIZONTALSYNC      (LTDC_SSCR_HSW >> 16)      /* Horizontal synchronization width. */
#define LTDC_VERTICALSYNC        LTDC_SSCR_VSH              /* Vertical synchronization height. */

#define LTDC_COLOR                   ((T_UINT32)0x000000FFU)                     /* Color mask */

#define LTDC_BLENDING_FACTOR1_CA     ((T_UINT32)0x00000400U)   /* Blending factor : Cte Alpha */
/* Blending factor : Cte Alpha x Pixel Alpha*/
#define LTDC_BLENDING_FACTOR1_PAXCA  ((T_UINT32)0x00000600U)

#define LTDC_BLENDING_FACTOR2_CA     ((T_UINT32)0x00000005U)   /* Blending factor : Cte Alpha */
/* Blending factor : Cte Alpha x Pixel Alpha*/
#define LTDC_BLENDING_FACTOR2_PAXCA  ((T_UINT32)0x00000007U)

#define LTDC_PIXEL_FORMAT_ARGB8888   ((T_UINT32)0x00000000U)      /* ARGB8888 LTDC pixel format */
#define LTDC_PIXEL_FORMAT_RGB888     ((T_UINT32)0x00000001U)      /* RGB888 LTDC pixel format */
#define LTDC_PIXEL_FORMAT_RGB565     ((T_UINT32)0x00000002U)      /* RGB565 LTDC pixel format */
#define LTDC_PIXEL_FORMAT_ARGB1555   ((T_UINT32)0x00000003U)      /* ARGB1555 LTDC pixel format */
#define LTDC_PIXEL_FORMAT_ARGB4444   ((T_UINT32)0x00000004U)      /* ARGB4444 LTDC pixel format */
#define LTDC_PIXEL_FORMAT_L8         ((T_UINT32)0x00000005U)      /* L8 LTDC pixel format */
#define LTDC_PIXEL_FORMAT_AL44       ((T_UINT32)0x00000006U)      /* AL44 LTDC pixel format */
#define LTDC_PIXEL_FORMAT_AL88       ((T_UINT32)0x00000007U)      /* AL88 LTDC pixel format */

#define LTDC_ALPHA               LTDC_LXCACR_CONSTA               /* LTDC Cte Alpha mask */

#define LTDC_STOPPOSITION            (LTDC_LXWHPCR_WHSPPOS >> 16)   /* LTDC Layer stop position  */
#define LTDC_STARTPOSITION           LTDC_LXWHPCR_WHSTPOS           /* LTDC Layer start position */

#define LTDC_COLOR_FRAME_BUFFER      LTDC_LXCFBLR_CFBLL             /* LTDC Layer Line length  */
#define LTDC_LINE_NUMBER             LTDC_LXCFBLNR_CFBLNBR         /* LTDC Layer Line number  */

#define LTDC_IT_LI                   LTDC_IER_LIE
#define LTDC_IT_FU                   LTDC_IER_FUIE
#define LTDC_IT_TE                   LTDC_IER_TERRIE
#define LTDC_IT_RR                   LTDC_IER_RRIE

#define LTDC_FLAG_LI                 LTDC_ISR_LIF
#define LTDC_FLAG_FU                 LTDC_ISR_FUIF
#define LTDC_FLAG_TE                 LTDC_ISR_TERRIF
#define LTDC_FLAG_RR                 LTDC_ISR_RRIF

#define LTDC_RELOAD_IMMEDIATE            LTDC_SRCR_IMR       /* Immediate Reload */
#define LTDC_RELOAD_VERTICAL_BLANKING    LTDC_SRCR_VBR       /* Vertical Blanking Reload */

#define __HAL_LTDC_RESET_HANDLE_STATE(__HANDLE__) ((__HANDLE__)->State = HAL_LTDC_STATE_RESET)

#define __HAL_LTDC_ENABLE(__HANDLE__)    ((__HANDLE__)->Instance->GCR |= LTDC_GCR_LTDCEN)

#define __HAL_LTDC_DISABLE(__HANDLE__)   ((__HANDLE__)->Instance->GCR &= ~(LTDC_GCR_LTDCEN))

#define __HAL_LTDC_LAYER_ENABLE(__HANDLE__, __LAYER__)  ((LTDC_LAYER((__HANDLE__), \
                                    (__LAYER__)))->CR |= (T_UINT32)LTDC_LXCR_LEN)

#define __HAL_LTDC_LAYER_DISABLE(__HANDLE__, __LAYER__) ((LTDC_LAYER((__HANDLE__), \
                                    (__LAYER__)))->CR &= ~(T_UINT32)LTDC_LXCR_LEN)

#define __HAL_LTDC_RELOAD_CONFIG(__HANDLE__)   ((__HANDLE__)->Instance->SRCR |= LTDC_SRCR_IMR)

#define __HAL_LTDC_GET_FLAG(__HANDLE__, __FLAG__) ((__HANDLE__)->Instance->ISR & (__FLAG__))

#define __HAL_LTDC_CLEAR_FLAG(__HANDLE__, __FLAG__) ((__HANDLE__)->Instance->ICR = (__FLAG__))

#define __HAL_LTDC_ENABLE_IT(__HANDLE__, __INTERRUPT__) ((__HANDLE__)->Instance->IER |= \
                                                         (__INTERRUPT__))

#define __HAL_LTDC_DISABLE_IT(__HANDLE__, __INTERRUPT__) ((__HANDLE__)->Instance->IER &= \
                                                         ~(__INTERRUPT__))

#define __HAL_LTDC_GET_IT_SOURCE(__HANDLE__, __INTERRUPT__) ((__HANDLE__)->Instance->ISR & \
                                                            (__INTERRUPT__))

T_HAL_STATUS HalLtdcInit(T_LTDC_HANDLE *hltdc);

T_HAL_STATUS HalLtdcConfigLayer(T_LTDC_HANDLE *hltdc, T_LTDC_LAYERCFG *pLayerCfg,
                                 T_UINT32 LayerIdx);
T_HAL_STATUS HalLtdcSetAddress(T_LTDC_HANDLE *hltdc, T_UINT32 Address, T_UINT32 LayerIdx);
T_HAL_STATUS HalLtdcEnableClut(T_LTDC_HANDLE *hltdc, T_UINT32 LayerIdx);
T_HAL_STATUS HalLtdcConfigClut(T_LTDC_HANDLE *hltdc, T_UINT32 *pCLUT, T_UINT32 CLUTSize,
                              T_UINT32 LayerIdx);

#define LTDC_LAYER(__HANDLE__, __LAYER__)         ((T_LTDC_LAYER *)((T_UINT32)(((T_UINT32) \
            ((__HANDLE__)->Instance)) + 0x84 + (0x80*(__LAYER__)))))
#define IS_LTDC_LAYER(LAYER)                      ((LAYER) <= MAX_LAYER)
#define IS_LTDC_HSPOL(HSPOL)                      (((HSPOL) == LTDC_HSPOLARITY_AL) || \
                                                   ((HSPOL) == LTDC_HSPOLARITY_AH))
#define IS_LTDC_VSPOL(VSPOL)                      (((VSPOL) == LTDC_VSPOLARITY_AL) || \
                                                   ((VSPOL) == LTDC_VSPOLARITY_AH))
#define IS_LTDC_DEPOL(DEPOL)                      (((DEPOL) ==  LTDC_DEPOLARITY_AL) || \
                                                   ((DEPOL) ==  LTDC_DEPOLARITY_AH))
#define IS_LTDC_PCPOL(PCPOL)                      (((PCPOL) ==  LTDC_PCPOLARITY_IPC) || \
                                                   ((PCPOL) ==  LTDC_PCPOLARITY_IIPC))
#define IS_LTDC_HSYNC(HSYNC)                      ((HSYNC)  <= LTDC_HORIZONTALSYNC)
#define IS_LTDC_VSYNC(VSYNC)                      ((VSYNC)  <= LTDC_VERTICALSYNC)
#define IS_LTDC_AHBP(AHBP)                        ((AHBP)   <= LTDC_HORIZONTALSYNC)
#define IS_LTDC_AVBP(AVBP)                        ((AVBP)   <= LTDC_VERTICALSYNC)
#define IS_LTDC_AAW(AAW)                          ((AAW)    <= LTDC_HORIZONTALSYNC)
#define IS_LTDC_AAH(AAH)                          ((AAH)    <= LTDC_VERTICALSYNC)
#define IS_LTDC_TOTALW(TOTALW)                    ((TOTALW) <= LTDC_HORIZONTALSYNC)
#define IS_LTDC_TOTALH(TOTALH)                    ((TOTALH) <= LTDC_VERTICALSYNC)
#define IS_LTDC_BLUEVALUE(BBLUE)                  ((BBLUE)  <= LTDC_COLOR)
#define IS_LTDC_GREENVALUE(BGREEN)                ((BGREEN) <= LTDC_COLOR)
#define IS_LTDC_REDVALUE(BRED)                    ((BRED)   <= LTDC_COLOR)
#define IS_LTDC_BLENDING_FACTOR1(BlendingFactor1) (((BlendingFactor1) == \
                                 LTDC_BLENDING_FACTOR1_CA) || \
                                 ((BlendingFactor1) == LTDC_BLENDING_FACTOR1_PAXCA))
#define IS_LTDC_BLENDING_FACTOR2(BlendingFactor2) (((BlendingFactor2) == \
                                 LTDC_BLENDING_FACTOR2_CA) || \
                                 ((BlendingFactor2) == LTDC_BLENDING_FACTOR2_PAXCA))
#define IS_LTDC_PIXEL_FORMAT(Pixelformat) (((Pixelformat) == LTDC_PIXEL_FORMAT_ARGB8888) || \
                                          ((Pixelformat) == LTDC_PIXEL_FORMAT_RGB888)   || \
                                          ((Pixelformat) == LTDC_PIXEL_FORMAT_RGB565)   || \
                                          ((Pixelformat) == LTDC_PIXEL_FORMAT_ARGB1555) || \
                                          ((Pixelformat) == LTDC_PIXEL_FORMAT_ARGB4444) || \
                                          ((Pixelformat) == LTDC_PIXEL_FORMAT_L8)       || \
                                          ((Pixelformat) == LTDC_PIXEL_FORMAT_AL44)     || \
                                          ((Pixelformat) == LTDC_PIXEL_FORMAT_AL88))

#define IS_LTDC_ALPHA(ALPHA)                      ((ALPHA) <= LTDC_ALPHA)
#define IS_LTDC_HCONFIGST(HCONFIGST)              ((HCONFIGST) <= LTDC_STARTPOSITION)
#define IS_LTDC_HCONFIGSP(HCONFIGSP)              ((HCONFIGSP) <= LTDC_STOPPOSITION)
#define IS_LTDC_VCONFIGST(VCONFIGST)              ((VCONFIGST) <= LTDC_STARTPOSITION)
#define IS_LTDC_VCONFIGSP(VCONFIGSP)              ((VCONFIGSP) <= LTDC_STOPPOSITION)
#define IS_LTDC_CFBP(CFBP)                        ((CFBP) <= LTDC_COLOR_FRAME_BUFFER)
#define IS_LTDC_CFBLL(CFBLL)                      ((CFBLL) <= LTDC_COLOR_FRAME_BUFFER)
#define IS_LTDC_CFBLNBR(CFBLNBR)                  ((CFBLNBR) <= LTDC_LINE_NUMBER)
#define IS_LTDC_LIPOS(LIPOS)                      ((LIPOS) <= 0x7FF)
#define IS_LTDC_RELAOD(RELOADTYPE)                (((RELOADTYPE) == LTDC_RELOAD_IMMEDIATE) || \
                                                   ((RELOADTYPE) == LTDC_SRCR_VBR))

#endif /* STM32F746xx || STM32F756xx || STM32F767xx || STM32F769xx || STM32F777xx || STM32F779xx */

#endif
