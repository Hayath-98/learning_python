/*
 ******************************************************************************
 * License Information  :  Howell Instruments, Inc.                           *
 *                         "Licensed Software" and "All rights reserved".     *
 ******************************************************************************
 *  File                : hdudispfdma2d.c
 *
 *  Description         : This file contains routines related to DMA2D.
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
 *      1.3          Shruthi M N     16-Oct-2017             100083
 *      1.4          Shruthi M N     30-Oct-2017             100104
 *      1.5          Divya G P       02-Nov-2017             100156
 *      1.6          Rona B S        05-Jul-2020             100259
 *      1.7          Rona B S        24-Jul-2020             100259
 * Additional References : None
 *
 *****************************************************************************
 */
#include "hdudispfdma2d.h" /* Routines for dma2d */
#include "hdulibcmsisgcc.h" /*CMSIS Cortex-M Core Function*/
#include "hdulibstm32f746xx.h" /* CMSIS Cortex-M7 Device Peripheral Access Layer */
#include "hdulibstm32f7xxhaldma2d.h" /* routines for HAL dma2d */
#include "hdulibstm32f7xxhalltdc.h"  /* Header file of LTDC HAL module.*/
#include "hdudispfconfig.h"  /* contains page and color config information */
#include "hdudispfwidgets.h"  /* Contains routines for widget params */
#include "hdulibstm32hallegacy.h" /* definition for the STM32Cube HAL */
#include "hdulibbasictypes.h"  /* Standard basic data type definitions */
#include "hdulibstm32f7xx.h"        /* CMSIS STM32F7xx Peripheral Access Layer Header File.*/

T_DMA2D_HANDLE_TYPE Dma2d_handle = {0};

static T_DMA2D_MODE Dma2d_mode = NONE;

static T_UINT8    *Clear_addr = ZERO;
static T_UINT32    Clear_count = ZERO;

static void Dma2dSetConfig(T_DMA2D_HANDLE_TYPE *h_dma2d, const T_UINT32 p_data,
                            T_UINT32 dst_address, T_UINT32 width, T_UINT32 height);

static void Dma2dInitRtoM(void);
static void Dma2dInitChartoM(void);
static void ClearScanLine(void);
static void Dma2dInitScanLine(void);
static void Dma2dInitRgbToArgb4444(void);

/*
 * Function                : HalDma2dConfigLayer
 *
 * Description             : The function configures the DMA2D Layer according to the specified
 *                           parameters in the T_DMA2D_HANDLE_TYPE and create the
 *                           associated handle.
 *
 * Formal parameter(s)     : T_DMA2D_HANDLE_TYPE *h_dma2d _ IN pointer to a T_DMA2D_HANDLE_TYPE
 *                           structure that contains the configuration information for the DMA2D.
 *                           T_UINT32 layer_idx -IN DMA2D Layer index.
 *
 * Return Value            : None
 *
 * Assumption              : None
 *
 */

void HalDma2dConfigLayer(T_DMA2D_HANDLE_TYPE *h_dma2d, T_UINT32 layer_idx)
{
  T_DMA2D_LAYER_CFG *player_cfg = &h_dma2d->LayerCfg[layer_idx];

  T_UINT32 reg_mask = ZERO;
  T_UINT32 reg_value = ZERO;

  /* DMA2D BGPFCR register configuration */
  /* Prepare the value to be written to the BGPFCCR register */
  /*hdudispfdma2d-HalDma2dConfigLayer-DB-LLR-001*/
  reg_value = player_cfg->InputColorMode | (player_cfg->AlphaMode
                                   << DMA2D_POSITION_BGPFCCR_AM);
  /*hdudispfdma2d-HalDma2dConfigLayer-DB-LLR-002*/
  reg_mask  = DMA2D_BGPFCCR_CM | DMA2D_BGPFCCR_AM | DMA2D_BGPFCCR_ALPHA;

  if ((DMA2D_INPUT_A4 == player_cfg->InputColorMode) ||
                (DMA2D_INPUT_A8 == player_cfg->InputColorMode))
  {
   /*hdudispfdma2d-HalDma2dConfigLayer-DB-LLR-003*/
    reg_value |= (player_cfg->InputAlpha & DMA2D_BGPFCCR_ALPHA);
  }
  else
  {
   /*hdudispfdma2d-HalDma2dConfigLayer-DB-LLR-004*/
    reg_value |=  (player_cfg->InputAlpha << DMA2D_POSITION_BGPFCCR_ALPHA);
  }

  /* Configure the background DMA2D layer */
  if(ZERO == layer_idx )
  {
   /*hdudispfdma2d-HalDma2dConfigLayer-DB-LLR-005*/
    /* Write DMA2D BGPFCCR register */
    MODIFY_REG(h_dma2d->Instance->BGPFCCR, reg_mask, reg_value);

   /*hdudispfdma2d-HalDma2dConfigLayer-DB-LLR-006*/
    /* DMA2D BGOR register configuration */
    WRITE_REG(h_dma2d->Instance->BGOR, player_cfg->InputOffset);

   /*hdudispfdma2d-HalDma2dConfigLayer-DB-LLR-007*/
    /* DMA2D BGCOLR register configuration */
    if ((DMA2D_INPUT_A4 == player_cfg->InputColorMode) ||
              (DMA2D_INPUT_A8 == player_cfg->InputColorMode ))
    {
      WRITE_REG(h_dma2d->Instance->BGCOLR, player_cfg->InputAlpha &
                               (DMA2D_BGCOLR_BLUE|DMA2D_BGCOLR_GREEN|DMA2D_BGCOLR_RED));
    }
    else
    {
     ; /*Do nothing */
    }
  }
  /* Configure the foreground DMA2D layer */
  else
  {
   /*hdudispfdma2d-HalDma2dConfigLayer-DB-LLR-009*/
     /* Write DMA2D FGPFCCR register */
    MODIFY_REG(h_dma2d->Instance->FGPFCCR, reg_mask, reg_value);

   /*hdudispfdma2d-HalDma2dConfigLayer-DB-LLR-008*/
    /* DMA2D FGOR register configuration */
    WRITE_REG(h_dma2d->Instance->FGOR, player_cfg->InputOffset);

   /*hdudispfdma2d-HalDma2dConfigLayer-DB-LLR-010*/
    /* DMA2D FGCOLR register configuration */
    if ((DMA2D_INPUT_A4 == player_cfg->InputColorMode) ||
                   (DMA2D_INPUT_A8 == player_cfg->InputColorMode))
    {
      WRITE_REG(h_dma2d->Instance->FGCOLR, player_cfg->InputAlpha &
                             (DMA2D_FGCOLR_BLUE|DMA2D_FGCOLR_GREEN|DMA2D_FGCOLR_RED));
    }
    else
    {
     ; /*Do nothing */
    }
  }
}

/*
 * Function                :  Dma2dSetConfig
 *
 * Description             :  Set the DMA2D transfer parameters.
 *
 * Formal parameter(s)     :  T_DMA2D_HANDLE_TYPE *h_dma2d -IN Pointer to a T_DMA2D_HANDLE_TYPE
 *                            structure that contains the configuration information for
 *                             the specified DMA2D.
 *                            T_UINT32 p_data -IN    The source memory Buffer address
 *                            T_UINT32 dst_address -IN The destination memory Buffer address
 *                            T_UINT32 width -IN The width of data to be transferred from
 *                             source to destination.
 *                            T_UINT32 height -IN The height of data to be transferred
 *                            from source to destination.
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */

static void Dma2dSetConfig(T_DMA2D_HANDLE_TYPE *h_dma2d, T_UINT32 p_data, T_UINT32 dst_address,
                           T_UINT32 width, T_UINT32 height)
{
  T_UINT32 tmp_val = ZERO;
  T_UINT32 tmp1 = ZERO;
  T_UINT32 tmp2 = ZERO;
  T_UINT32 tmp3 = ZERO;
  T_UINT32 tmp4 = ZERO;

  /*hdudispfdma2d-Dma2dSetConfig-DB-LLR-001*/
  /* Configure DMA2D data size */
  MODIFY_REG(h_dma2d->Instance->NLR, (DMA2D_NLR_NL|DMA2D_NLR_PL),
                  (height| (width << DMA2D_POSITION_NLR_PL)));

  /*hdudispfdma2d-Dma2dSetConfig-DB-LLR-002*/
  /* Configure DMA2D destination address */
  WRITE_REG(h_dma2d->Instance->OMAR, dst_address);

  /* Register to memory DMA2D mode selected */
  if (DMA2D_R2M == h_dma2d->Init.Mode)
  {
    tmp1 = p_data & DMA2D_OCOLR_ALPHA_1;
    tmp2 = p_data & DMA2D_OCOLR_RED_1;
    tmp3 = p_data & DMA2D_OCOLR_GREEN_1;
    tmp4 = p_data & DMA2D_OCOLR_BLUE_1;

    /* Prepare the value to be written to the OCOLR register according to the color mode */
    if (DMA2D_OUTPUT_ARGB8888 == h_dma2d->Init.ColorMode )
    {
     /*hdudispfdma2d-Dma2dSetConfig-DB-LLR-003*/
      tmp_val = (tmp3 | tmp2 | tmp1| tmp4);
    }
    else if (DMA2D_OUTPUT_RGB888 == h_dma2d->Init.ColorMode )
    {
     /*hdudispfdma2d-Dma2dSetConfig-DB-LLR-004*/
      tmp_val = (tmp3 | tmp2 | tmp4);
    }
    else if (DMA2D_OUTPUT_RGB565 == h_dma2d->Init.ColorMode )
    {
     /*hdudispfdma2d-Dma2dSetConfig-DB-LLR-005*/
      tmp2 = (tmp2 >> NINTEEN);
      tmp3 = (tmp3 >> TEN);
      tmp4 = (tmp4 >> THREE );
      tmp_val  = ((tmp3 << FIVE) | (tmp2 << ELEVEN) | tmp4);
    }
    else if (DMA2D_OUTPUT_ARGB1555 == h_dma2d->Init.ColorMode )
    {
     /*hdudispfdma2d-Dma2dSetConfig-DB-LLR-006*/
      tmp1 = (tmp1 >> THIRTY_ONE);
      tmp2 = (tmp2 >> NINTEEN);
      tmp3 = (tmp3 >> ELEVEN);
      tmp4 = (tmp4 >> THREE );
      tmp_val  = ((tmp3 << FIVE) | (tmp2 << TEN) | (tmp1 << FIFTEEN) | tmp4);
    }
    else
    {
      /*hdudispfdma2d-Dma2dSetConfig-DB-LLR-007*/
      tmp1 = (tmp1 >> TWENTY_EIGHT);
      tmp2 = (tmp2 >> TWENTY);
      tmp3 = (tmp3 >> TWELVE);
      tmp4 = (tmp4 >> FOUR );
      tmp_val  = ((tmp3 << FOUR) | (tmp2 << EIGHT) | (tmp1 << TWELVE) | tmp4);
    }
    /*hdudispfdma2d-Dma2dSetConfig-DB-LLR-008*/
    /* Write to DMA2D OCOLR register */
    WRITE_REG(h_dma2d->Instance->OCOLR, tmp_val);
  }
  else /* M2M, M2M_PFC or M2M_Blending DMA2D Mode */
  {
   /*hdudispfdma2d-Dma2dSetConfig-DB-LLR-009*/
    /* Configure DMA2D source address */
    WRITE_REG(h_dma2d->Instance->FGMAR, p_data);
  }
}

/*
 * Function                :  HalDma2dBlendingStartIt
 *
 * Description             :  The function configures the DMA2D registers for background
 *                            and foreground image blending and enables the transfer interrupts.
 *
 * Formal parameter(s)     :  T_DMA2D_HANDLE_TYPE *h_dma2d - IN Pointer to a T_DMA2D_HANDLE_TYPE
 *                            structure that contains the configuration information for
 *                            the specified DMA2D.
 *                            T_UINT32 src_address_1 - IN Foreground Image address
 *                            T_UINT32  src_address_2 - IN Background Image address
 *                            T_UINT32 dst_address - IN Destination address
 *                            T_UINT32 width - IN The width of the image.
 *                            T_UINT32 height - IN The height of the image.
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */

void HalDma2dBlendingStartIt(T_DMA2D_HANDLE_TYPE *h_dma2d, T_UINT32 src_address_1,
      T_UINT32  src_address_2, T_UINT32 dst_address, T_UINT32 width,  T_UINT32 height)
{
  /*hdudispfdma2d-HalDma2dBlendingStartIt-DB-LLR-001*/
  /* Configure DMA2D Stream source2 address */
  WRITE_REG(h_dma2d->Instance->BGMAR, src_address_2);

  /*hdudispfdma2d-HalDma2dBlendingStartIt-DB-LLR-002*/
  /* Configure the source, destination address and the data size */
  Dma2dSetConfig(h_dma2d, src_address_1, dst_address, width, height);

  /*hdudispfdma2d-HalDma2dBlendingStartIt-DB-LLR-003*/
  /* Enable the transfer complete, transfer error and configuration error interrupts */
  __HAL_DMA2D_ENABLE_IT(DMA2D, DMA2D_IT_TC|DMA2D_IT_TE|DMA2D_IT_CE);

  /* Enable the Peripheral */
  __HAL_DMA2D_ENABLE(DMA2D);
}

/*
 * Function                :  HalDma2dStartIt
 *
 * Description             :  The function configures DMA and enables transfers interrupts.
 *
 * Formal parameter(s)     :  T_DMA2D_HANDLE_TYPE *h_dma2d  - IN pointer to a T_DMA2D_HANDLE_TYPE
 *                            structure that contains the configuration information for the DMA2D.
 *                            T_UINT32 p_data  - IN The source memory Buffer address
 *                            T_UINT32 dst_address  - IN The destination memory Buffer address
 *                            T_UINT32 width - IN The width of data to be transferred from
 *                            source to destination.
 *                            T_UINT32height - IN The height of data to be transferred from
 *                            source to destination.
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */

void HalDma2dStartIt(T_DMA2D_HANDLE_TYPE *h_dma2d, T_UINT32 p_data, T_UINT32 dst_address,
                                       T_UINT32 width,  T_UINT32 height)
{
  /*hdudispfdma2d-HalDma2dStartIt-DB-LLR-001*/
  /* Configure the source, destination address and the data size */
  Dma2dSetConfig(h_dma2d, p_data, dst_address, width, height);

  /*hdudispfdma2d-HalDma2dStartIt-DB-LLR-002*/
  /* Enable the transfer complete, transfer error and configuration error interrupts */
  __HAL_DMA2D_ENABLE_IT(DMA2D, DMA2D_IT_TC|DMA2D_IT_TE|DMA2D_IT_CE);

  /*hdudispfdma2d-HalDma2dStartIt-DB-LLR-003*/
  /* Enable the Peripheral */
  __HAL_DMA2D_ENABLE(DMA2D);
}


/*
 * Function                :  HalDma2dInit
 *
 * Description             :  Initialize the DMA2D according to the specified parameters
 *                            in the T_DMA2D_HANDLE_TYPE and create the associated handle.
 *
 * Formal parameter(s)     :  T_DMA2D_HANDLE_TYPE *h_dma2d  - IN pointer to a
 *                             T_DMA2D_HANDLE_TYPE structure that contains the configuration
 *                             information for the DMA2D.
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */

void HalDma2dInit(T_DMA2D_HANDLE_TYPE *h_dma2d)
{
  /*hdudispfdma2d-HalDma2dInit-DB-LLR-001*/
  /* DMA2D CR register configuration */
  MODIFY_REG(DMA2D->CR, DMA2D_CR_MODE, h_dma2d->Init.Mode);

  /*hdudispfdma2d-HalDma2dInit-DB-LLR-002*/
  /* DMA2D OPFCCR register configuration */
  MODIFY_REG(DMA2D->OPFCCR, DMA2D_OPFCCR_CM, h_dma2d->Init.ColorMode);

  /*hdudispfdma2d-HalDma2dInit-DB-LLR-003*/
  /* DMA2D OOR register configuration */
  MODIFY_REG(DMA2D->OOR, DMA2D_OOR_LO, h_dma2d->Init.OutputOffset);
}


/*
 * Function                :  Dma2dWait
 *
 * Description             :  The function waits for DMA2D to complete execution.
 *
 * Formal parameter(s)     :  None
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */

void  Dma2dWait(void)
{
   static T_UINT8 u8_first_call = ONE;
   T_UINT32 u32_test = ZERO;

   /*hdudispfdma2d-Dma2dWait-DB-LLR-001*/
   if(ZERO != u8_first_call)
   {
      u8_first_call = ZERO;
      return;
   }
   else
   {
    ; /*Do nothing*/
   }
   /*hdudispfdma2d-Dma2dWait-DB-LLR-002*/
   while(ZERO == (DMA2D->ISR & DMA2D_ISR_TCIF))
   {
      u32_test++;
   }
   /*hdudispfdma2d-Dma2dWait-DB-LLR-003*/
   DMA2D->IFCR = DMA2D_ISR_TCIF;
}


/*
 * Function                :  Dma2dIsBusy
 *
 * Description             :  The function checks wheather DMA2D is busy.
 *
 * Formal parameter(s)     :  None
 *
 * Return Value            :  T_INT16 - returns zero or one
 *
 * Assumption              :  None
 *
 */

T_INT16  Dma2dIsBusy(void)
{
   /* hdudispfdma2d-Dma2dIsBusy-DB-LLR-001 */
   return((DMA2D->ISR & DMA2D_ISR_TCIF) == ZERO);
}

/*
 * Function                :  Dma2dInitRtoM
 *
 * Description             :  The function initializes the DMA2D for
 *                            the register to memory mode.
 *
 * Formal parameter(s)     :  None
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */

static void Dma2dInitRtoM(void)
{
   /*hdudispfdma2d-Dma2dInitRtoM-DB-LLR-001*/
   /* Configure the DMA2D Mode, Color Mode and output offset */
   Dma2d_handle.Init.Mode         = DMA2D_R2M;
   Dma2d_handle.Init.ColorMode    = DMA2D_ARGB4444;
   Dma2d_handle.Init.OutputOffset = ZERO;

   /*hdudispfdma2d-Dma2dInitRtoM-DB-LLR-002*/
   /* Foreground layer Configuration : layer 1 */
   Dma2d_handle.LayerCfg[1].AlphaMode = DMA2D_REPLACE_ALPHA;
   Dma2d_handle.LayerCfg[1].InputAlpha = ZERO;
   Dma2d_handle.LayerCfg[1].InputColorMode = CM_ARGB4444;
   Dma2d_handle.LayerCfg[1].InputOffset = ZERO;

   /*hdudispfdma2d-Dma2dInitRtoM-DB-LLR-003*/
   Dma2d_handle.Instance = DMA2D;

   HalDma2dInit(&Dma2d_handle);

   Dma2d_mode = RTOM1;
}

/*
 * Function                :  Dma2dFillBox
 *
 * Description             :  The function fills specified region with specified color.
 *
 * Formal parameter(s)     :  T_UINT16 u16_x_loc  - IN Starting X-axis offset of region
 *                            to be coloured.
 *                            T_UINT16 u16_y_loc  - IN Starting Y-axis offset of region
 *                            to be coloured.
 *                            T_UINT16 width  - IN The width of the region to be coloured.
 *                            T_UINT16 height  - IN  The height of the region to be coloured.
 *                            T_UINT32 u32_color  - IN Colour to be used to fill the region.
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */

void Dma2dFillBox(T_UINT16 u16_x_loc, T_UINT16 u16_y_loc, T_UINT16 width, T_UINT16 height,
                                               T_UINT32 u32_color)
{
   T_UINT32 u32_start_loc = ZERO;

   u32_start_loc = (T_UINT32)((u16_y_loc * (T_UINT16)S16_panel_width) *(T_UINT16)TWO);
   u32_start_loc = (T_UINT32)(u32_start_loc + ((T_UINT32)(u16_x_loc * TWO)));
   u32_start_loc = (T_UINT32)(u32_start_loc + (T_UINT32)Vp_fgfb2);

   /*hdudispfdma2d-Dma2dFillBox-DB-LLR-001*/
   Dma2dWait();

   /*hdudispfdma2d-Dma2dFillBox-DB-LLR-002*/
   if(Dma2d_mode != RTOM)
   {
      Dma2dInitRtoM();
   }
   else
   {
     ; /*Do nothing */
   }

   /*hdudispfdma2d-Dma2dFillBox-DB-LLR-003*/
   Dma2d_handle.Instance->OOR = ((T_UINT32)(S16_panel_width - width));

   Dma2d_handle.Instance->AMTCR = HEX_1001;

   /*hdudispfdma2d-Dma2dFillBox-DB-LLR-004*/
   HalDma2dStartIt(&Dma2d_handle, u32_color, u32_start_loc, width, height);
}


/*
 * Function                :  Dma2dInitChartoM
 *
 * Description             :  The function initializes the DMA2D for character to memory.
 *
 * Formal parameter(s)     :  None
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */

static void Dma2dInitChartoM(void)
{
  /*hdudispfdma2d-Dma2dInitChartoM-DB-LLR-001*/
  /* Configure the DMA2D Mode, Color Mode and output offset */
  Dma2d_handle.Init.Mode         = DMA2D_M2M_BLEND;
  Dma2d_handle.Init.ColorMode    = LTDC_PIXEL_FORMAT_ARGB4444;
  Dma2d_handle.Init.OutputOffset = ZERO;

  /*hdudispfdma2d-Dma2dInitChartoM-DB-LLR-002*/
  /* Foreground layer Configuration */
  Dma2d_handle.LayerCfg[1].AlphaMode = DMA2D_NO_MODIF_ALPHA;
  Dma2d_handle.LayerCfg[1].InputAlpha = HEX_FF;
  Dma2d_handle.LayerCfg[1].InputColorMode = DMA2D_INPUT_A4;
  Dma2d_handle.LayerCfg[1].InputOffset = ZERO;

  /*hdudispfdma2d-Dma2dInitChartoM-DB-LLR-003*/
  /* Background layer Configuration */
  Dma2d_handle.LayerCfg[0].AlphaMode = DMA2D_NO_MODIF_ALPHA;
  Dma2d_handle.LayerCfg[0].InputAlpha = HEX_FF;
  Dma2d_handle.LayerCfg[0].InputColorMode = LTDC_PIXEL_FORMAT_ARGB4444;
  Dma2d_handle.LayerCfg[0].InputOffset = ZERO;

  /*hdudispfdma2d-Dma2dInitChartoM-DB-LLR-004*/
  /* DMA2D Initialization */
  HalDma2dInit(&Dma2d_handle);

  /* Apply DMA2D Foreground configuration */
  HalDma2dConfigLayer(&Dma2d_handle, ONE);

  /* Apply DMA2D Background configuration */
  HalDma2dConfigLayer(&Dma2d_handle, ZERO);

  Dma2d_mode = CHARTOM;
}

/*
 * Function                :  Dma2dDrawChar
 *
 * Description             :  The function draws a 4bbp font character.
 *
 * Formal parameter(s)     :  void *character_data  - IN Bitmap address of the
 *                             character to be displayed.
 *                            void *write_loc  - IN Destination address.
 *                            T_UINT32 u32_width  - IN The width of the data.
 *                            T_UINT32 u32_height  - IN The height of the data.
 *                            T_UINT16 e_color  - IN Color in which character is displayed.
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */

void Dma2dDrawChar(const void *character_data, void *write_loc, T_UINT32 u32_width,
                                      T_UINT32 u32_height, T_UINT16 e_color)
{
   static T_UINT16   static_color = ZERO;
   static T_UINT32   u32_color = ZERO;

   /*hdudispfdma2d-Dma2dDrawChar-DB-LLR-001*/
   if(e_color != static_color)
   {
      u32_color = WidgetsRGB444ToRGB888(e_color);
      static_color = e_color;
   }
   else
   {
      ;/*Does nothing*/
   }

   /*hdudispfdma2d-Dma2dDrawChar-DB-LLR-002*/
   Dma2dWait();

   /*hdudispfdma2d-Dma2dDrawChar-DB-LLR-003*/
   if(Dma2d_mode != CHARTOM)
   {
      Dma2dInitChartoM();
   }
   else
   {
      ;/*Does nothing*/
   }
   /*hdudispfdma2d-Dma2dDrawChar-DB-LLR-004*/
   u32_width += u32_width%TWO;
   Dma2d_handle.Instance->OOR = ((T_UINT32)S16_panel_width - u32_width);
   Dma2d_handle.Instance->BGOR = (((T_UINT32)S16_panel_width - u32_width));
   Dma2d_handle.Instance->FGCOLR = u32_color;

  /*hdudispfdma2d-Dma2dDrawChar-DB-LLR-005*/
  HalDma2dBlendingStartIt( &Dma2d_handle, (const T_UINT32)character_data,(T_UINT32)write_loc,
        (T_UINT32)write_loc, u32_width,u32_height );
}

/*
 * Function                :  ClearScanLine
 *
 * Description             :  The function clears the specified number of line points.
 *
 * Formal parameter(s)     :  None
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */

static void ClearScanLine(void)
{
   if(Clear_count != ZERO)
   {
      /*hdudispfdma2d-ClearScanLine-DB-LLR-001*/
      while(Clear_count > FOUR)
      {
         *((T_UINT32 *)(Clear_addr)) = ZERO;
         Clear_addr+=FOUR;
         Clear_count-=FOUR;
      }
      /*hdudispfdma2d-ClearScanLine-DB-LLR-002*/
      while(ZERO != Clear_count)
      {
         *((T_UINT8 *)(Clear_addr)) = ZERO;
         Clear_addr = Clear_addr + ONE;
         Clear_count = Clear_count - ONE;
      }
   }
   else
   {
      ;/*Does nothing*/
   }
}

/*
 * Function                :  Dma2dInitScanLine
 *
 * Description             :  This function initializes the DMA2D for scan line blend.
 *
 * Formal parameter(s)     :  None
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */

static void Dma2dInitScanLine(void)
{

	/* hdudispfdma2d-Dma2dInitScanLine-DB-LLR-001 */
  /* Configure the DMA2D Mode, Color Mode and output offset */
  Dma2d_handle.Init.Mode    = DMA2D_M2M_BLEND; /* DMA2D mode Memory to Memory with Blending */

  Dma2d_handle.Init.ColorMode    = LTDC_PIXEL_FORMAT_ARGB4444; /* output format of DMA2D */
  Dma2d_handle.Init.OutputOffset = ZERO;  /* No offset in output */

  /* hdudispfdma2d-Dma2dInitScanLine-DB-LLR-002 */
  /* Foreground layer Configuration */
  Dma2d_handle.LayerCfg[1].AlphaMode = DMA2D_NO_MODIF_ALPHA;
  Dma2d_handle.LayerCfg[1].InputAlpha = HEX_FF;
  Dma2d_handle.LayerCfg[1].InputColorMode = DMA2D_INPUT_A8;
  Dma2d_handle.LayerCfg[1].InputOffset = ZERO; /* No offset in input */

  /* hdudispfdma2d-Dma2dInitScanLine-DB-LLR-003 */
  /* Background layer Configuration */
  Dma2d_handle.LayerCfg[0].AlphaMode = DMA2D_NO_MODIF_ALPHA;
  Dma2d_handle.LayerCfg[0].InputAlpha = HEX_FF; /* 127 : semi-transparent */
  Dma2d_handle.LayerCfg[0].InputColorMode = DMA2D_INPUT_ARGB4444;
  Dma2d_handle.LayerCfg[0].InputOffset = ZERO; /* No offset in input */

  /* hdudispfdma2d-Dma2dInitScanLine-DB-LLR-004 */
  Dma2d_handle.Instance = DMA2D;

  /* DMA2D Initialization */
  HalDma2dInit(&Dma2d_handle);

  /* Apply DMA2D Foreground configuration */
  HalDma2dConfigLayer(&Dma2d_handle, ONE);

  /* Apply DMA2D Background configuration */
  HalDma2dConfigLayer(&Dma2d_handle, ZERO);

  Dma2d_mode = SCAN_LINE;
}

/*
 * Function                :  Dma2dScanLineBlend
 *
 * Description             :  This function Blends a Scan Line into the frame buffer.
 *
 * Formal parameter(s)     :  void *scan_line  - IN Image(Line) Source Location.
 *                            void *frame_data  - IN Destination address.
 *                            T_UINT32 u32_width  - IN The width of the data.
 *                            T_UINT16 e_color  - IN Color to be displayed.
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */

void Dma2dScanLineBlend(void *scan_line, void *frame_data, T_UINT32 u32_width, T_UINT16 e_color)
{
   T_UINT32 u32_red   = ZERO;
   T_UINT32 u32_blue  = ZERO;
   T_UINT32 u32_green = ZERO;

   static T_UINT32 u32_color    = ZERO;
   static T_UINT16 static_color = ZERO;

   /*hdudispfdma2d-Dma2dScanLineBlend-DB-LLR-001*/
   if(static_color != e_color)
   {
      u32_red = (T_UINT32) ((e_color & HEX_F00) >> EIGHT);
      u32_red = ((u32_red <<FOUR) + u32_red) << SIXTEEN;

      u32_green = (T_UINT32) ((e_color & HEX_0F0) >> FOUR);
      u32_green = ((u32_green <<FOUR) + u32_green) << EIGHT;

      u32_blue = (T_UINT32) ((e_color & HEX_00F));
      u32_blue =  ((u32_blue <<FOUR) + u32_blue);

      u32_color = u32_red | u32_green | u32_blue;

      static_color = e_color;
   }
   else
   {
      ;/*Does nothing*/
   }
   /*hdudispfdma2d-Dma2dScanLineBlend-DB-LLR-002*/
   Dma2dWait();

   /*hdudispfdma2d-Dma2dScanLineBlend-DB-LLR-003*/
   if(Dma2d_mode != SCAN_LINE)
   {
      Dma2dInitScanLine();
      Dma2d_handle.Instance->OOR = (T_UINT32)(S16_panel_width);
      Dma2d_handle.Instance->BGOR = (T_UINT32)(S16_panel_width);
   }

   /*hdudispfdma2d-Dma2dScanLineBlend-DB-LLR-004*/
   /* Configure the color register. */
   WRITE_REG(DMA2D->FGCOLR, u32_color);

   /*hdudispfdma2d-Dma2dScanLineBlend-DB-LLR-005*/
   /* Configure DMA2D source address */
   WRITE_REG(DMA2D->FGMAR, (T_UINT32)scan_line);

   /*hdudispfdma2d-Dma2dScanLineBlend-DB-LLR-006*/
   /* Configure Background address */
   WRITE_REG(DMA2D->BGMAR, (T_UINT32)frame_data);

   /*hdudispfdma2d-Dma2dScanLineBlend-DB-LLR-007*/
   /* Configure DMA2D destination address */
   WRITE_REG(DMA2D->OMAR,(T_UINT32)frame_data);

   /*hdudispfdma2d-Dma2dScanLineBlend-DB-LLR-008*/
   /* Configure DMA2D data size */
   MODIFY_REG(DMA2D->NLR, (DMA2D_NLR_NL|DMA2D_NLR_PL), (1 | (u32_width << DMA2D_POSITION_NLR_PL)));

   /*hdudispfdma2d-Dma2dScanLineBlend-DB-LLR-009*/
   /* Enable transfer complete interrupt.*/
   DMA2D->CR |= DMA2D_IT_TC;

   /*hdudispfdma2d-Dma2dScanLineBlend-DB-LLR-010*/
   /* Enable the Peripheral */
   DMA2D->CR |= DMA2D_CR_START;

   /*hdudispfdma2d-Dma2dScanLineBlend-DB-LLR-011*/
   ClearScanLine();

   /*hdudispfdma2d-Dma2dScanLineBlend-DB-LLR-012*/
   /* Save for the clear function.*/
   Clear_addr = (T_UINT8 *)scan_line;
   Clear_count = u32_width;

}

/*
 * Function                :  Dma2dInitRgbToArgb4444
 *
 * Description             :  This function initializes the DMA2D for
 *                            character draws.
 *
 * Formal parameter(s)     :  None
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */

static void Dma2dInitRgbToArgb4444(void)
{
  /*hdudispfdma2d-Dma2dInitRgbToArgb4444-DB-LLR-001*/
  /* Configure the DMA2D Mode, Color Mode and output offset */
  Dma2d_handle.Init.Mode         = DMA2D_M2M_PFC;
  Dma2d_handle.Init.ColorMode    = LTDC_PIXEL_FORMAT_ARGB4444;
  Dma2d_handle.Init.OutputOffset = ZERO;

  /*hdudispfdma2d-Dma2dInitRgbToArgb4444-DB-LLR-002*/
  /* Foreground layer Configuration */
  Dma2d_handle.LayerCfg[1].AlphaMode          = DMA2D_NO_MODIF_ALPHA;
  Dma2d_handle.LayerCfg[1].InputAlpha         = HEX_FF;
  Dma2d_handle.LayerCfg[1].InputColorMode     = DMA2D_INPUT_RGB565;
  Dma2d_handle.LayerCfg[1].InputOffset        = ZERO;

  /*hdudispfdma2d-Dma2dInitRgbToArgb4444-DB-LLR-003*/
  Dma2d_handle.Instance = DMA2D;

  /* DMA2D Initialization */
  HalDma2dInit(&Dma2d_handle);

  /* Apply DMA2D Foreground configuration */
  HalDma2dConfigLayer(&Dma2d_handle, ONE);

  Dma2d_mode = RGB565TOARGB4444;
}

/*
 * Function                :  Dma2dRgbToArgb4444
 *
 * Description             :  This function copies an RGB565 bit map to the foreground.
 *
 * Formal parameter(s)     :  void *bit_map - IN Bitmap address of the image to be displayed.
 *                            void *write_loc  - IN Destination address.
 *                            T_UINT32 u32_width  - IN The width of the data.
 *                            T_UINT32 u32_height  - IN The height of the data.
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */

void Dma2dRgbToArgb4444(void *bit_map, void *write_loc, T_UINT32 u32_width,  T_UINT32 u32_height)
{
   /*hdudispfdma2d-Dma2dRgbToArgb4444-DB-LLR-001*/
   Dma2dWait();

   /*hdudispfdma2d-Dma2dRgbToArgb4444-DB-LLR-002*/
   if(Dma2d_mode != RGB565TOARGB4444)
   {
      Dma2dInitRgbToArgb4444();
   }
   else
   {
    ;
   }
  /*hdudispfdma2d-Dma2dRgbToArgb4444-DB-LLR-003*/
  Dma2d_handle.Instance->OOR =  ((T_UINT32)S16_panel_width - u32_width);
  Dma2d_handle.Instance->BGOR = (((T_UINT32)S16_panel_width - u32_width));
  HalDma2dStartIt(&Dma2d_handle,(T_UINT32)bit_map,(T_UINT32)write_loc,u32_width,
                                 u32_height);

}

/*
 * Function                :  Dma2dInit
 *
 * Description             :  This function initializes the DMA2D.
 *
 * Formal parameter(s)     :  None
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */

void Dma2dInit(void)
{
  /*hdudispfdma2d-Dma2dInit-DB-LLR-001*/
  __HAL_RCC_DMA2D_CLK_ENABLE();

  Dma2d_handle.Instance = DMA2D;

}

