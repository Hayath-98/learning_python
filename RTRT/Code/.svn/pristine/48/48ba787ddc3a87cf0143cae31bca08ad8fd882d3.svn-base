/*
 ******************************************************************************
 * License Information  :  Howell Instruments, Inc.                           *
 *                         "Licensed Software" and "All rights reserved".     *
 ******************************************************************************
 *  File                : hdudispfdma2d.h
 *
 *  Description         : This file contains the common defines and functions prototypes for
 *                        hdudispfdma2d.c
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
 *      1.2          Vinay H         10-Oct-2017             100064
 *      1.3          Shruthi M N     30-Oct-2017             100104
 *
 * Additional References : None
 *
 *****************************************************************************
 */

#ifndef _HDUDISPFDMA2D_H_
#define _HDUDISPFDMA2D_H_

#include "hdulibbasictypes.h"  /* Standard basic data type definitions */
#include "hdulibstm32f7xxhaldma2d.h" /* Defines dma2d routines */
#include "hdulibcorecm7.h" /* Cortex-M7 processor and core peripherals */

#define HEX_F00 0xf00
#define HEX_0F0 0x0f0
#define HEX_00F 0x00f
#define HEX_1001 0x1001

#define __HAL_RCC_DMA2D_CLK_ENABLE()   do { \
                                        __IO T_UINT32 tmpreg; \
                                        SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_DMA2DEN);\
                                        /* Delay after an RCC peripheral clock enabling */ \
                                        tmpreg = READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_DMA2DEN);\
                                        UNUSED(tmpreg); \
                                      } while(0)
#define DMA2D_ARGB8888          DMA2D_OUTPUT_ARGB8888
#define DMA2D_RGB888            DMA2D_OUTPUT_RGB888
#define DMA2D_RGB565            DMA2D_OUTPUT_RGB565
#define DMA2D_ARGB1555          DMA2D_OUTPUT_ARGB1555
#define DMA2D_ARGB4444          DMA2D_OUTPUT_ARGB4444

#define CM_ARGB8888             DMA2D_INPUT_ARGB8888
#define CM_RGB888               DMA2D_INPUT_RGB888
#define CM_RGB565               DMA2D_INPUT_RGB565
#define CM_ARGB1555             DMA2D_INPUT_ARGB1555
#define CM_ARGB4444             DMA2D_INPUT_ARGB4444
#define CM_L8                   DMA2D_INPUT_L8
#define CM_AL44                 DMA2D_INPUT_AL44
#define CM_AL88                 DMA2D_INPUT_AL88
#define CM_L4                   DMA2D_INPUT_L4
#define CM_A8                   DMA2D_INPUT_A8
#define CM_A4                   DMA2D_INPUT_A4

/*defgroup DMA2D_Mode DMA2D Mode */
/*!< DMA2D memory to memory transfer mode */
#define DMA2D_M2M                   ((T_UINT32)0x00000000U)

/* DMA2D_CLUT_CM DMA2D CLUT Color Mode */
#define DMA2D_CCM_ARGB8888          ((T_UINT32)0x00000000U) /*!< ARGB8888 DMA2D CLUT color mode */
#define DMA2D_CCM_RGB888            ((T_UINT32)0x00000001U) /*!< RGB888 DMA2D CLUT color mode   */

/* DMA2D_Interrupts DMA2D Interrupts */
#define DMA2D_IT_CE                 DMA2D_CR_CEIE      /*!< Configuration Error Interrupt */
#define DMA2D_IT_CTC                DMA2D_CR_CTCIE     /*!< CLUT Transfer Complete Interrupt */
#define DMA2D_IT_CAE                DMA2D_CR_CAEIE     /*!< CLUT Access Error Interrupt */
#define DMA2D_IT_TW                 DMA2D_CR_TWIE      /*!< Transfer Watermark Interrupt */
#define DMA2D_IT_TC                 DMA2D_CR_TCIE      /*!< Transfer Complete Interrupt */
#define DMA2D_IT_TE                 DMA2D_CR_TEIE      /*!< Transfer Error Interrupt */

/* DMA2D_Flags DMA2D Flags */
#define DMA2D_FLAG_CE               DMA2D_ISR_CEIF   /*!< Configuration Error Interrupt Flag */
#define DMA2D_FLAG_CTC              DMA2D_ISR_CTCIF  /*!< CLUT Transfer Complete Interrupt Flag */
#define DMA2D_FLAG_CAE              DMA2D_ISR_CAEIF  /*!< CLUT Access Error Interrupt Flag */
#define DMA2D_FLAG_TW               DMA2D_ISR_TWIF   /*!< Transfer Watermark Interrupt Flag */
#define DMA2D_FLAG_TC               DMA2D_ISR_TCIF   /*!< Transfer Complete Interrupt Flag */
#define DMA2D_FLAG_TE               DMA2D_ISR_TEIF   /*!< Transfer Error Interrupt Flag */

/* DMA2D_Exported_Macros DMA2D Exported Macros */
#define __HAL_DMA2D_ENABLE(__HANDLE__)        ((__HANDLE__)->CR |= DMA2D_CR_START)

/*
 * @brief  Enable the specified DMA2D interrupts.
 * @param  __HANDLE__: DMA2D handle
 * @param __INTERRUPT__: specifies the DMA2D interrupt sources to be enabled.
 *          This parameter can be any combination of the following values:
 *            @arg DMA2D_IT_CE:  Configuration error interrupt mask
 *            @arg DMA2D_IT_CTC: CLUT transfer complete interrupt mask
 *            @arg DMA2D_IT_CAE: CLUT access error interrupt mask
 *            @arg DMA2D_IT_TW:  Transfer Watermark interrupt mask
 *            @arg DMA2D_IT_TC:  Transfer complete interrupt mask
 *            @arg DMA2D_IT_TE:  Transfer error interrupt mask
 * @retval None
 */
#define __HAL_DMA2D_ENABLE_IT(__HANDLE__, __INTERRUPT__) ((__HANDLE__)->CR |= (__INTERRUPT__))

/* DMA2D_Maximum_Line_WaterMark DMA2D Maximum Line Watermark */
#define DMA2D_LINE_WATERMARK_MAX            DMA2D_LWR_LW  /*!< DMA2D maximum line watermark */

/* DMA2D_Color_Value DMA2D Color Value */
#define DMA2D_COLOR_VALUE                 ((T_UINT32)0x000000FFU)  /*!< Color value mask */

/* DMA2D_Max_Layer DMA2D Maximum Number of Layers */
#define DMA2D_MAX_LAYER         2         /*!< DMA2D maximum number of layers */

/* DMA2D_Offset DMA2D Offset */
#define DMA2D_OFFSET                DMA2D_FGOR_LO            /*!< Line Offset */

/* DMA2D_Size DMA2D Size */
#define DMA2D_PIXEL                 (DMA2D_NLR_PL >> 16U)  /*!< DMA2D number of pixels per line */
#define DMA2D_LINE                  DMA2D_NLR_NL           /*!< DMA2D number of lines           */

/* DMA2D_CLUT_Size DMA2D CLUT Size */
#define DMA2D_CLUT_SIZE             (DMA2D_FGPFCCR_CS >> 8)  /*!< DMA2D CLUT size */

/* DMA2D_Private_Macros DMA2D Private Macros */

#define IS_DMA2D_LINE(LINE)                   ((LINE) <= DMA2D_LINE)

/* DMA2D_Shifts DMA2D Shifts */
/*!< Required left shift to set foreground CLUT size */
#define DMA2D_POSITION_FGPFCCR_CS     (T_UINT32)POSITION_VAL(DMA2D_FGPFCCR_CS)
/*!< Required left shift to set background CLUT size */
#define DMA2D_POSITION_BGPFCCR_CS     (T_UINT32)POSITION_VAL(DMA2D_BGPFCCR_CS)

/*!< Required left shift to set foreground CLUT color mode */
#define DMA2D_POSITION_FGPFCCR_CCM    (T_UINT32)POSITION_VAL(DMA2D_FGPFCCR_CCM)
/*!< Required left shift to set background CLUT color mode */
#define DMA2D_POSITION_BGPFCCR_CCM    (T_UINT32)POSITION_VAL(DMA2D_BGPFCCR_CCM)

/*!< Required left shift to set output alpha inversion     */
#define DMA2D_POSITION_OPFCCR_AI      (T_UINT32)POSITION_VAL(DMA2D_OPFCCR_AI)
/*!< Required left shift to set foreground alpha inversion */
#define DMA2D_POSITION_FGPFCCR_AI     (T_UINT32)POSITION_VAL(DMA2D_FGPFCCR_AI)
/*!< Required left shift to set background alpha inversion */
#define DMA2D_POSITION_BGPFCCR_AI     (T_UINT32)POSITION_VAL(DMA2D_BGPFCCR_AI)

 /*!< Required left shift to set output Red/Blue swap     */
#define DMA2D_POSITION_OPFCCR_RBS     (T_UINT32)POSITION_VAL(DMA2D_OPFCCR_RBS)
/*!< Required left shift to set foreground Red/Blue swap */
#define DMA2D_POSITION_FGPFCCR_RBS    (T_UINT32)POSITION_VAL(DMA2D_FGPFCCR_RBS)
 /*!< Required left shift to set background Red/Blue swap */
#define DMA2D_POSITION_BGPFCCR_RBS    (T_UINT32)POSITION_VAL(DMA2D_BGPFCCR_RBS)

/*!< Required left shift to set deadtime value */
#define DMA2D_POSITION_AMTCR_DT       (T_UINT32)POSITION_VAL(DMA2D_AMTCR_DT)

 /*!< Required left shift to set foreground alpha mode */
#define DMA2D_POSITION_FGPFCCR_AM     (T_UINT32)POSITION_VAL(DMA2D_FGPFCCR_AM)
/*!< Required left shift to set background alpha mode */

/*!< Required left shift to set foreground alpha value */
#define DMA2D_POSITION_FGPFCCR_ALPHA  (T_UINT32)POSITION_VAL(DMA2D_FGPFCCR_ALPHA)
/*!< Required left shift to set background alpha value */

/*!< Required left shift to set pixels per lines value */
#define DMA2D_POSITION_NLR_PL         (T_UINT32)POSITION_VAL(DMA2D_NLR_PL)

/* LTDC_Pixelformat LTDC Pixel format */
/*!< ARGB8888 LTDC pixel format */
#define LTDC_PIXEL_FORMAT_ARGB8888                  ((T_UINT32)0x00000000U)
/*!< RGB888 LTDC pixel format   */
#define LTDC_PIXEL_FORMAT_RGB888                    ((T_UINT32)0x00000001U)
/*!< RGB565 LTDC pixel format   */
#define LTDC_PIXEL_FORMAT_RGB565                    ((T_UINT32)0x00000002U)
/*!< ARGB1555 LTDC pixel format */
#define LTDC_PIXEL_FORMAT_ARGB1555                  ((T_UINT32)0x00000003U)
/*!< ARGB4444 LTDC pixel format */
#define LTDC_PIXEL_FORMAT_ARGB4444                  ((T_UINT32)0x00000004U)
/*!< L8 LTDC pixel format       */
#define LTDC_PIXEL_FORMAT_L8                        ((T_UINT32)0x00000005U)
/*!< AL44 LTDC pixel format     */
#define LTDC_PIXEL_FORMAT_AL44                      ((T_UINT32)0x00000006U)
/*!< AL88 LTDC pixel format     */
#define LTDC_PIXEL_FORMAT_AL88                      ((T_UINT32)0x00000007U)


typedef enum
{
   NONE,
   RTOM,
   RTOM1,
   MTOM,
   CHARTOM,
   SCAN_LINE,
   RGB565TOFG,
   RGB565TOARGB4444
} T_DMA2D_MODE;

extern void Dma2dInit(void);
extern void Dma2dFillBox(T_UINT16 u16_x_loc, T_UINT16 u16_y_loc, T_UINT16 width,
                         T_UINT16 height, T_UINT32 u32_color);
extern void Dma2dDrawChar(const void *character_data, void *write_loc, T_UINT32 u32_width,
                          T_UINT32 u32_height, T_UINT16 e_color);
extern void Dma2dScanLineBlend(void *scan_line, void *frame_data, T_UINT32 u32_width,
                                                                 T_UINT16 e_color);
extern void Dma2dRgbToArgb4444(void *bit_map, void *write_loc, T_UINT32 u32_width,
                                                             T_UINT32 u32_height);

extern T_INT16 Dma2dIsBusy(void);

#endif /* _HDUDISPFDMA2D_H_ */
