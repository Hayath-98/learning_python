/*
 ******************************************************************************
 * License Information  :  Howell Instruments, Inc.                           *
 *                         "Licensed Software" and "All rights reserved".     *
 ******************************************************************************
 *  File                : hdudispbstm32f7xxhalmsp.c
 *
 *  Description         : Provides routines for HAL MSP module.
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
 * <Version No.>        <Author>          <Date>               <Problem Report No.>
 *
 *      1.1             Ajay J G          02-Aug-2017             -
 *      1.2             Divya G P         02-Sep-2017          100028
 *
 * Additional References : None
 *
 ******************************************************************************
 */

/* Includes */
#include "hdulibstm32f7xxhalmsp.h"     /* contains HAL msp function prototypes */
#include "hdulibstm32f7xxhalcrc.h"     /* Header files for CRC HAL  driver*/
#include "hdulibstm32f7xxhalltdc.h"    /* Header files for LTDC HAL  driver*/
#include "hdulibstm32f7xxhal.h"        /*Funnction prototypes for the HAL module driver */
#include "hdulibbasictypes.h"          /*Basic data types */
#include "hdulibstm32f7xxhalgpio.h"    /* Header files for Gpio driver*/
#include "hdulibstm32f7xxhalrcc.h"     /* Header files for RCC EX HAL module*/
#include "hdulibstm32f7xxhalrccex.h"   /* Header files for RCC EX HAL module*/
#include "hdulibstm32f7xxhalgpioex.h"  /* Header file of GPIO HAL Extension module.*/
#include "hdulibstm32hallegacy.h"  /* Header definition for the STM32Cube HAL constants*/ 

/*
 * Function                :  HalLtdcMspInit
 *
 * Description             :  This function initializes the LTDC MSP.
 *
 * Formal parameter(s)     :  None
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */

void HalLtdcMspInit()
{
   T_GPIO_INIT gpio_init_structure = {ZERO};

   /*hdudispbstm32f7xxhalmsp-HalLtdcMspInit-DB-LLR-001*/
   /* Enable the LTDC Clock */
   __HAL_RCC_LTDC_CLK_ENABLE();

   /*hdudispbstm32f7xxhalmsp-HalLtdcMspInit-DB-LLR-002*/
   /* Enable GPIO Clock */
   __HAL_RCC_GPIOI_CLK_ENABLE();
   __HAL_RCC_GPIOJ_CLK_ENABLE();
   __HAL_RCC_GPIOK_CLK_ENABLE();
   __HAL_RCC_GPIOA_CLK_ENABLE();
   __HAL_RCC_GPIOB_CLK_ENABLE();

   /*Configure peripheral GPIO*/
   /*LTDC Pins configuration*/

   /*hdudispbstm32f7xxhalmsp-HalLtdcMspInit-DB-LLR-003*/
   /* GPIOI LTDC alternate configuration */
   gpio_init_structure.Pin       = GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15;
   gpio_init_structure.Pull      = GPIO_NOPULL;
   gpio_init_structure.Speed     = GPIO_SPEED_FAST;
   gpio_init_structure.Mode      = GPIO_MODE_AF_PP;
   gpio_init_structure.Alternate = GPIO_AF14_LTDC;
   HalGpioInit(GPIOI, &gpio_init_structure);

   /* GPIOJ configuration */
   gpio_init_structure.Pin       = GPIO_PIN_ALL;
   gpio_init_structure.Pull      = GPIO_NOPULL;
   gpio_init_structure.Speed     = GPIO_SPEED_FAST;
   gpio_init_structure.Mode      = GPIO_MODE_AF_PP;
   gpio_init_structure.Alternate = GPIO_AF14_LTDC;
   HalGpioInit(GPIOJ, &gpio_init_structure);

   /*hdudispbstm32f7xxhalmsp-HalLtdcMspInit-DB-LLR-005*/
   /* GPIOK configuration */
   gpio_init_structure.Pin       = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | \
                                  GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7;
   gpio_init_structure.Pull      = GPIO_NOPULL;
   gpio_init_structure.Speed     = GPIO_SPEED_FAST;
   gpio_init_structure.Mode      = GPIO_MODE_AF_PP;
   gpio_init_structure.Alternate = GPIO_AF14_LTDC;
   HalGpioInit(GPIOK, &gpio_init_structure);
}

/*
 * Function                :  HalCRCMspInit
 *
 * Description             :  This function initializes the CRC MSP.
 *
 * Formal parameter(s)     :  None
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */

void HalCRCMspInit()
{
   /*hdudispbstm32f7xxhalmsp-HalCRCMspInit-DB-LLR-001*/
   /* CRC Peripheral clock enable */
   __HAL_RCC_CRC_CLK_ENABLE();
}
