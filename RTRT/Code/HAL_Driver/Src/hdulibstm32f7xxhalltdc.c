/*
 ******************************************************************************
 * License Information  :  Howell Instruments, Inc.                           *
 *                         "Licensed Software" and "All rights reserved".     *
 ******************************************************************************
 *  File                : hdulibstm32f7xxhalltdc.c
 *
 *  Description         : This file provides firmware functions to manage
 *                        Initialization, de-initialization, Peripheral Control
 *                        Peripheral State and errors of the LTDC peripheral
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
 *  Author(s)           : Shilpa A R
 *
 *  Version History     :
 * <Version No.>      <Author>          <Date>         <Problem Report No.>
 *
 *      1.1           Shilpa A R    27-Jul-2017          -
 *      1.2           Divya G P     02-Sep-2017        100028
 *      1.3           Shilpa A R    02-Oct-2017        100064
 *      1.4          Shruthi M N    30-Oct-2017        100104
 *
 * Additional References : None
 *
 ******************************************************************************
 */

/* Includes */
#include "hdulibstm32f7xxhal.h"         /* Header files for HAL driver*/
#include "hdulibstm32f7xxhalltdc.h"     /* Header files for LTDC HAL driver*/
#include "hdulibbasictypes.h"           /* Contains basic data types*/
#include "hdulibstm32f7xxhalmsp.h"      /*Header file of HAL MSP module.*/
#include "hdulibstm32f7xxhaldef.h"      /*Header file of HAL DEF module.*/
#include "hdulibstm32f746xx.h"   /*CMSIS Cortex-M7 Device Peripheral Access Layer Header File.*/

static void LtdcSetConfig(T_LTDC_HANDLE *h_ltdc, T_LTDC_LAYERCFG *p_layer_cfg, T_UINT32 layer_idx);


/*
 * Function                :  HalLtdcInit
 *
 * Description             :  This function Initializes the LTDC according to the specified
 *                            parameters in the T_LTDC_INIT and create the associated handle.
 *
 * Formal parameter(s)     :  T_LTDC_HANDLE *h_ltdc - INOUT
 *                            pointer to a T_LTDC_HANDLE structure
 *
 * Return Value            :  T_HAL_STATUS - returns HAL status
 *
 * Assumption              :  None
 *
 */

T_HAL_STATUS HalLtdcInit(T_LTDC_HANDLE *h_ltdc)
{
  T_UINT32 temp = ZERO,
           temp1 = ZERO;

  /*hdulibstm32f7xxhalltdc-HalLtdcInit-DB-LLR-001*/
  /* Check the LTDC peripheral state */
  if(NULL == h_ltdc)
  {
    return HAL_ERROR;
  }
  else
  {
     ;/* Does nothing */
  }

  /* Check function parameters */
  /*hdulibstm32f7xxhalltdc-HalLtdcInit-DB-LLR-002*/
  if(HAL_LTDC_STATE_RESET == h_ltdc->State)
  {
    /* Allocate lock resource and initialize it */
    h_ltdc->Lock = HAL_UNLOCKED;

    /* Init the low level hardware */
    HalLtdcMspInit();
  }
  else
  {
     ;/* Does nothing */
  }

  /*hdulibstm32f7xxhalltdc-HalLtdcInit-DB-LLR-003*/
  /* Change LTDC peripheral state */
  h_ltdc->State = HAL_LTDC_STATE_BUSY;

  /*hdulibstm32f7xxhalltdc-HalLtdcInit-DB-LLR-004*/
  /* Configures the HS, VS, DE and PC polarity */
  h_ltdc->Instance->GCR &= ~(LTDC_GCR_HSPOL | LTDC_GCR_VSPOL | LTDC_GCR_DEPOL | LTDC_GCR_PCPOL);
  h_ltdc->Instance->GCR |=  (T_UINT32)(h_ltdc->Init.HSPolarity | h_ltdc->Init.VSPolarity | \
  h_ltdc->Init.DEPolarity | h_ltdc->Init.PCPolarity);

  /*hdulibstm32f7xxhalltdc-HalLtdcInit-DB-LLR-005*/
  /* Sets Synchronization size */
  h_ltdc->Instance->SSCR &= ~(LTDC_SSCR_VSH | LTDC_SSCR_HSW);
  temp = (h_ltdc->Init.HorizontalSync << SIXTEEN);
  h_ltdc->Instance->SSCR |= (temp | h_ltdc->Init.VerticalSync);

  /*hdulibstm32f7xxhalltdc-HalLtdcInit-DB-LLR-006*/
  /* Sets Accumulated Back porch */
  h_ltdc->Instance->BPCR &= ~(LTDC_BPCR_AVBP | LTDC_BPCR_AHBP);
  temp = (h_ltdc->Init.AccumulatedHBP << SIXTEEN);
  h_ltdc->Instance->BPCR |= (temp | h_ltdc->Init.AccumulatedVBP);

  /*hdulibstm32f7xxhalltdc-HalLtdcInit-DB-LLR-007*/
  /* Sets Accumulated Active Width */
  h_ltdc->Instance->AWCR &= ~(LTDC_AWCR_AAH | LTDC_AWCR_AAW);
  temp = (h_ltdc->Init.AccumulatedActiveW << SIXTEEN);
  h_ltdc->Instance->AWCR |= (temp | h_ltdc->Init.AccumulatedActiveH);

  /*hdulibstm32f7xxhalltdc-HalLtdcInit-DB-LLR-008*/
  /* Sets Total Width */
  h_ltdc->Instance->TWCR &= ~(LTDC_TWCR_TOTALH | LTDC_TWCR_TOTALW);
  temp = (h_ltdc->Init.TotalWidth << SIXTEEN);
  h_ltdc->Instance->TWCR |= (temp | h_ltdc->Init.TotalHeigh);

  /*hdulibstm32f7xxhalltdc-HalLtdcInit-DB-LLR-009*/
  /* Sets the background color value */
  temp = ((T_UINT32)(h_ltdc->Init.Backcolor.Green) << EIGHT);
  temp1 = ((T_UINT32)(h_ltdc->Init.Backcolor.Red) << SIXTEEN);
  h_ltdc->Instance->BCCR &= ~(LTDC_BCCR_BCBLUE | LTDC_BCCR_BCGREEN | LTDC_BCCR_BCRED);
  h_ltdc->Instance->BCCR |= (temp1 | temp | h_ltdc->Init.Backcolor.Blue);

  /*hdulibstm32f7xxhalltdc-HalLtdcInit-DB-LLR-010*/
  /* Enable the transfer Error interrupt */
  __HAL_LTDC_ENABLE_IT(h_ltdc, LTDC_IT_TE);

  /*hdulibstm32f7xxhalltdc-HalLtdcInit-DB-LLR-011*/
  /* Enable the FIFO underrun interrupt */
  __HAL_LTDC_ENABLE_IT(h_ltdc, LTDC_IT_FU);

  /*hdulibstm32f7xxhalltdc-HalLtdcInit-DB-LLR-012*/
  /* Enable LTDC by setting LTDCEN bit */
  __HAL_LTDC_ENABLE(h_ltdc);

  /*hdulibstm32f7xxhalltdc-HalLtdcInit-DB-LLR-013*/
  /* Initialize the error code */
  h_ltdc->ErrorCode = HAL_LTDC_ERROR_NONE;

  /*hdulibstm32f7xxhalltdc-HalLtdcInit-DB-LLR-014*/
  /* Initialize the LTDC state*/
  h_ltdc->State = HAL_LTDC_STATE_READY;

  return HAL_OK;
}

/*
 * Function                :  HalLtdcConfigLayer
 *
 * Description             :  Configure the LTDC Layer according to the specified
 *                            parameters in the LTDC_InitTypeDef and create the associated handle.
 *
 * Formal parameter(s)     :  T_LTDC_HANDLE h_ltdc - INOUT pointer to a T_LTDC_HANDLE structure
 *                            that contains the configuration information for the LTDC.
 *                            T_LTDC_LAYERCFG p_layer_cfg - IN pointer to a T_LTDC_LAYERCFG
 *                            structure that contains the configuration information for the Layer.
 *                            T_UINT32 layer_idx - IN  LTDC Layer index.
 *                            This parameter can be one of the following values:
 *                            0 or 1
 *
 * Return Value            :  T_HAL_STATUS - HAL status
 *
 * Assumption              :  None
 *
 */
T_HAL_STATUS HalLtdcConfigLayer(T_LTDC_HANDLE *h_ltdc, T_LTDC_LAYERCFG *p_layer_cfg,
                                T_UINT32 layer_idx)
{
  /*hdulibstm32f7xxhalltdc-HalLtdcConfigLayer-DB-LLR-001*/
  /* Process locked */
  __HAL_LOCK(h_ltdc);

  /*hdulibstm32f7xxhalltdc-HalLtdcConfigLayer-DB-LLR-002*/
  /* Change LTDC peripheral state */
  h_ltdc->State = HAL_LTDC_STATE_BUSY;

  /*hdulibstm32f7xxhalltdc-HalLtdcConfigLayer-DB-LLR-003*/
  /* Copy new layer configuration into handle structure */
  h_ltdc->LayerCfg[layer_idx] = *p_layer_cfg;

  /*hdulibstm32f7xxhalltdc-HalLtdcConfigLayer-DB-LLR-004*/
  /* Configure the LTDC Layer */
  LtdcSetConfig(h_ltdc, p_layer_cfg, layer_idx);

  /*hdulibstm32f7xxhalltdc-HalLtdcConfigLayer-DB-LLR-005*/
  /* Sets the Reload type */
  h_ltdc->Instance->SRCR = LTDC_SRCR_IMR;

  /*hdulibstm32f7xxhalltdc-HalLtdcConfigLayer-DB-LLR-006*/
  /* Initialize the LTDC state*/
  h_ltdc->State  = HAL_LTDC_STATE_READY;

  /*hdulibstm32f7xxhalltdc-HalLtdcConfigLayer-DB-LLR-007*/
  /* Process unlocked */
  __HAL_UNLOCK(h_ltdc);

  return HAL_OK;
}

/*
 * Function                :  HalLtdcSetAddress
 *
 * Description             :  Reconfigure the frame buffer Address.
 *
 * Formal parameter(s)     :  T_LTDC_HANDLE h_ltdc - INOUT pointer to a T_LTDC_HANDLE structure
 *                            that contains the configuration information for the LTDC.
 *                            T_UINT32 address - IN  new address value.
 *                            T_UINT32 layer_idx - IN  LTDC Layer index.
 *                            This parameter can be one of the following values:
 *                            0 or 1
 *
 * Return Value            :  T_HAL_STATUS - HAL status
 *
 * Assumption              :  None
 *
 */

T_HAL_STATUS HalLtdcSetAddress(T_LTDC_HANDLE *h_ltdc, T_UINT32 address, T_UINT32 layer_idx)
{
  T_LTDC_LAYERCFG *p_layer_cfg= {ZERO};

  /*hdulibstm32f7xxhalltdc-HalLtdcSetAddress-DB-LLR-001*/
  /* Process locked */
  __HAL_LOCK(h_ltdc);

  /*hdulibstm32f7xxhalltdc-HalLtdcSetAddress-DB-LLR-002*/
  /* Change LTDC peripheral state */
  h_ltdc->State = HAL_LTDC_STATE_BUSY;

  /*hdulibstm32f7xxhalltdc-HalLtdcSetAddress-DB-LLR-003*/
  /* Get layer configuration from handle structure */
  p_layer_cfg = &h_ltdc->LayerCfg[layer_idx];

  /*hdulibstm32f7xxhalltdc-HalLtdcSetAddress-DB-LLR-004*/
  /* Reconfigure the Address */
  p_layer_cfg->FBStartAdress = address;

  /*hdulibstm32f7xxhalltdc-HalLtdcSetAddress-DB-LLR-005*/
  /* Set LTDC parameters */
  LtdcSetConfig(h_ltdc, p_layer_cfg, layer_idx);

  /*hdulibstm32f7xxhalltdc-HalLtdcSetAddress-DB-LLR-006*/
  /* Sets the Reload type */
  h_ltdc->Instance->SRCR = LTDC_SRCR_IMR;

  /*hdulibstm32f7xxhalltdc-HalLtdcSetAddress-DB-LLR-007*/
  /* Change the LTDC state*/
  h_ltdc->State = HAL_LTDC_STATE_READY;

  /*hdulibstm32f7xxhalltdc-HalLtdcSetAddress-DB-LLR-008*/
  /* Process unlocked */
  __HAL_UNLOCK(h_ltdc);

  return HAL_OK;
}


/*
 * Function                :  HalLtdcEnableClut
 *
 * Description             :  Enable the color lookup table.
 *
 * Formal parameter(s)     :  T_LTDC_HANDLE h_ltdc - INOUT pointer to a T_LTDC_HANDLE structure
 *                            that contains the configuration information for the LTDC.
 *                            T_UINT32 layer_idx - IN LTDC Layer index.
 *                            This parameter can be one of the following values:
 *                            0 or 1
 *
 * Return Value            :  T_HAL_STATUS - HAL status
 *
 * Assumption              :  None
 *
 */


T_HAL_STATUS HalLtdcEnableClut(T_LTDC_HANDLE *h_ltdc, T_UINT32 layer_idx)
{

  /*hdulibstm32f7xxhalltdc-HalLtdcEnableClut-DB-LLR-001*/
  /* Process locked */
  __HAL_LOCK(h_ltdc);

  /*hdulibstm32f7xxhalltdc-HalLtdcEnableClut-DB-LLR-002*/
  /* Change LTDC peripheral state */
  h_ltdc->State = HAL_LTDC_STATE_BUSY;

  /*hdulibstm32f7xxhalltdc-HalLtdcEnableClut-DB-LLR-003*/
  /* Disable LTDC color lookup table by setting CLUTEN bit */
  LTDC_LAYER(h_ltdc, layer_idx)->CR |= (T_UINT32)LTDC_LXCR_CLUTEN;

  /*hdulibstm32f7xxhalltdc-HalLtdcEnableClut-DB-LLR-004*/
  /* Sets the Reload type */
  h_ltdc->Instance->SRCR = LTDC_SRCR_IMR;

  /*hdulibstm32f7xxhalltdc-HalLtdcEnableClut-DB-LLR-005*/
  /* Change the LTDC state*/
  h_ltdc->State = HAL_LTDC_STATE_READY;

  /*hdulibstm32f7xxhalltdc-HalLtdcEnableClut-DB-LLR-006*/
  /* Process unlocked */
  __HAL_UNLOCK(h_ltdc);

  return HAL_OK;
}

/*
 * Function                :  HalLtdcConfigClut
 *
 * Description             :  Load the color lookup table.
 *
 * Formal parameter(s)     :  T_LTDC_HANDLE h_ltdc - INOUT pointer to a T_LTDC_HANDLE structure
 *                             that contains the configuration information for the LTDC.
 *                            clut_size: the color lookup table size.
 *                            T_UINT32 p_clut - INOUT  pointer to the color lookup table address.
 *                            This parameter can be one of the following values:
 *                            0 or 1
 *                            T_UINT32 layer_idx - IN LTDC Layer index.
 *
 * Return Value            :  T_HAL_STATUS - HAL status
 *
 * Assumption              :  None
 *
 */

T_HAL_STATUS HalLtdcConfigClut(T_LTDC_HANDLE *h_ltdc, T_UINT32 *p_clut, T_UINT32 clut_size,
                               T_UINT32 layer_idx)
{
  T_UINT32 temp = ZERO;
  T_UINT32 counter = ZERO;
  T_UINT32 p_counter = ZERO;

  /*hdulibstm32f7xxhalltdc-HalLtdcConfigClut-DB-LLR-001*/
  /* Process locked */
  __HAL_LOCK(h_ltdc);

  /*hdulibstm32f7xxhalltdc-HalLtdcConfigClut-DB-LLR-002*/
  /* Change LTDC peripheral state */
  h_ltdc->State = HAL_LTDC_STATE_BUSY;

  /*hdulibstm32f7xxhalltdc-HalLtdcConfigClut-DB-LLR-003*/
  for(counter = ZERO; (counter < clut_size); counter++)
  {
    if(LTDC_PIXEL_FORMAT_AL44 == h_ltdc->LayerCfg[layer_idx].PixelFormat)
    {
      temp  = (((counter + SIXTEEN*counter) << TWENTY_FOUR) | ((T_UINT32)(*p_clut) & 0xFF) |
               ((T_UINT32)(*p_clut) & 0xFF00) | ((T_UINT32)(*p_clut) & 0xFF0000));
    }
    else
    {
      temp  = ((counter << TWENTY_FOUR) | ((T_UINT32)(*p_clut) & 0xFF) | ((T_UINT32)(*p_clut)
              & 0xFF00) |((T_UINT32)(*p_clut) & 0xFF0000));
    }
    p_counter = (T_UINT32)p_clut + sizeof(*p_clut);
    p_clut = (T_UINT32 *)p_counter;

    /* Specifies the C-LUT address and RGB value */
    LTDC_LAYER(h_ltdc, layer_idx)->CLUTWR  = temp;
  }

  /*hdulibstm32f7xxhalltdc-HalLtdcConfigClut-DB-LLR-004*/
  /* Change the LTDC state*/
  h_ltdc->State = HAL_LTDC_STATE_READY;

  /*hdulibstm32f7xxhalltdc-HalLtdcConfigClut-DB-LLR-005*/
  /* Process unlocked */
  __HAL_UNLOCK(h_ltdc);

  return HAL_OK;
}

/*
 * Function                :  LtdcSetConfig
 *
 * Description             :  This function Configure the LTDC Layer according to the specified
 *                            parameters in the T_LTDC_INIT and create the associated handle.
 *
 * Formal parameter(s)     :  T_LTDC_HANDLE *h_ltdc - INOUT pointer to a structure
 *                            that contains  the configuration information for the LTDC.
 *                            uint32_t p_layer_cfg -IN Pointer LTDC Layer Configuration structure
 *                            uint32_t layer_idx - IN LTDC Layer index.
 *                            This parameter can be 0 or 1
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */
static void LtdcSetConfig(T_LTDC_HANDLE *h_ltdc, T_LTDC_LAYERCFG *p_layer_cfg, T_UINT32 layer_idx)
{
  T_UINT32 temp = ZERO;
  T_UINT32 temp1 = ZERO;
  T_UINT32 tmp2 = ZERO;

  /*hdulibstm32f7xxhalltdc-LtdcSetConfig-DB-LLR-001*/
  /* Configures the horizontal start and stop position */
  temp = ((p_layer_cfg->WindowX1 + ((h_ltdc->Instance->BPCR & LTDC_BPCR_AHBP) >> SIXTEEN))
         << SIXTEEN);
  LTDC_LAYER(h_ltdc, layer_idx)->WHPCR &= ~(LTDC_LXWHPCR_WHSTPOS | LTDC_LXWHPCR_WHSPPOS);
  LTDC_LAYER(h_ltdc, layer_idx)->WHPCR = ((p_layer_cfg->WindowX0 + ((h_ltdc->Instance->BPCR &
                                          LTDC_BPCR_AHBP) >> SIXTEEN) + ONE) | temp);

  /*hdulibstm32f7xxhalltdc-LtdcSetConfig-DB-LLR-002*/
  /* Configures the vertical start and stop position */
  temp = ((p_layer_cfg->WindowY1 + (h_ltdc->Instance->BPCR & LTDC_BPCR_AVBP)) << SIXTEEN);
  LTDC_LAYER(h_ltdc, layer_idx)->WVPCR &= ~(LTDC_LXWVPCR_WVSTPOS | LTDC_LXWVPCR_WVSPPOS);
  LTDC_LAYER(h_ltdc, layer_idx)->WVPCR  = ((p_layer_cfg->WindowY0 + (h_ltdc->Instance->BPCR &
                                          LTDC_BPCR_AVBP) + ONE) | temp);

  /*hdulibstm32f7xxhalltdc-LtdcSetConfig-DB-LLR-003*/
  /* Specifies the pixel format */
  LTDC_LAYER(h_ltdc, layer_idx)->PFCR &= ~(LTDC_LXPFCR_PF);
  LTDC_LAYER(h_ltdc, layer_idx)->PFCR = (p_layer_cfg->PixelFormat);

  /*hdulibstm32f7xxhalltdc-LtdcSetConfig-DB-LLR-004*/
  /* Configures the default color values */
  temp = ((T_UINT32)(p_layer_cfg->Backcolor.Green) << EIGHT);
  temp1 = ((T_UINT32)(p_layer_cfg->Backcolor.Red) << SIXTEEN);
  tmp2 = (p_layer_cfg->Alpha0 << TWENTY_FOUR);
  LTDC_LAYER(h_ltdc, layer_idx)->DCCR &= ~(LTDC_LXDCCR_DCBLUE | LTDC_LXDCCR_DCGREEN
                                         | LTDC_LXDCCR_DCRED | LTDC_LXDCCR_DCALPHA);
  LTDC_LAYER(h_ltdc, layer_idx)->DCCR = (p_layer_cfg->Backcolor.Blue | temp | temp1 | tmp2);

  /*hdulibstm32f7xxhalltdc-LtdcSetConfig-DB-LLR-005*/
  /* Specifies the constant alpha value */
  LTDC_LAYER(h_ltdc, layer_idx)->CACR &= ~(LTDC_LXCACR_CONSTA);
  LTDC_LAYER(h_ltdc, layer_idx)->CACR = (p_layer_cfg->Alpha);

  /*hdulibstm32f7xxhalltdc-LtdcSetConfig-DB-LLR-006*/
  /* Specifies the blending factors */
  LTDC_LAYER(h_ltdc, layer_idx)->BFCR &= ~(LTDC_LXBFCR_BF2 | LTDC_LXBFCR_BF1);
  LTDC_LAYER(h_ltdc, layer_idx)->BFCR = (p_layer_cfg->BlendingFactor1 |
             p_layer_cfg->BlendingFactor2);

  /*hdulibstm32f7xxhalltdc-LtdcSetConfig-DB-LLR-007*/
  /* Configures the color frame buffer start address */
  LTDC_LAYER(h_ltdc, layer_idx)->CFBAR &= ~(LTDC_LXCFBAR_CFBADD);
  LTDC_LAYER(h_ltdc, layer_idx)->CFBAR = (p_layer_cfg->FBStartAdress);

  /*hdulibstm32f7xxhalltdc-LtdcSetConfig-DB-LLR-008*/
  if(LTDC_PIXEL_FORMAT_ARGB8888 == p_layer_cfg->PixelFormat )
  {
    temp = FOUR;
  }
  /*hdulibstm32f7xxhalltdc-LtdcSetConfig-DB-LLR-009*/
  else if (LTDC_PIXEL_FORMAT_RGB888 == p_layer_cfg->PixelFormat)
  {
    temp = THREE;
  }
  /*hdulibstm32f7xxhalltdc-LtdcSetConfig-DB-LLR-010*/
  else if((LTDC_PIXEL_FORMAT_ARGB4444 == p_layer_cfg->PixelFormat ) || \
    (LTDC_PIXEL_FORMAT_RGB565 == p_layer_cfg->PixelFormat)   || \
      (LTDC_PIXEL_FORMAT_ARGB1555 == p_layer_cfg->PixelFormat) || \
        (LTDC_PIXEL_FORMAT_AL88 == p_layer_cfg->PixelFormat))
  {
    temp = TWO;
  }
  /*hdulibstm32f7xxhalltdc-LtdcSetConfig-DB-LLR-011*/
  else
  {
    temp = ONE;
  }

  /*hdulibstm32f7xxhalltdc-LtdcSetConfig-DB-LLR-012*/
  /* Configures the color frame buffer pitch in byte */
  LTDC_LAYER(h_ltdc, layer_idx)->CFBLR  &= ~(LTDC_LXCFBLR_CFBLL | LTDC_LXCFBLR_CFBP);
  LTDC_LAYER(h_ltdc, layer_idx)->CFBLR  = (((p_layer_cfg->ImageWidth * temp) << SIXTEEN) |
        (((p_layer_cfg->WindowX1 - p_layer_cfg->WindowX0) * temp)  + THREE));

  /*hdulibstm32f7xxhalltdc-LtdcSetConfig-DB-LLR-013*/
  /* Configures the frame buffer line number */
  LTDC_LAYER(h_ltdc, layer_idx)->CFBLNR  &= ~(LTDC_LXCFBLNR_CFBLNBR);
  LTDC_LAYER(h_ltdc, layer_idx)->CFBLNR  = (p_layer_cfg->ImageHeight);

  /*hdulibstm32f7xxhalltdc-LtdcSetConfig-DB-LLR-014*/
  /* Enable LTDC_Layer by setting LEN bit */
  LTDC_LAYER(h_ltdc, layer_idx)->CR |= (T_UINT32)LTDC_LXCR_LEN;
}
