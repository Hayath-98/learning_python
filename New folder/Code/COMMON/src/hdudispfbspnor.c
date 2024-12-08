/*
 ******************************************************************************
 * License Information  :  Howell Instruments, Inc.                           *
 *                         "Licensed Software" and "All rights reserved".     *
 ******************************************************************************
 *  File                : hdudispfbspnor.c
 *
 *  Description         : This file includes a standard driver for the PC28F128M29EWLA NOR flash
 *                        memory device mounted on STM32756G-EVAL and STM32746G-EVAL
 *                        evaluation boards.
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
 *
 * Additional References : None
 *
 *****************************************************************************
 */

/* Includes*/
#include "hdudispfbspnor.h" /* contains the common defines and functions prototypes bspnor*/
#include "hdulibstm32f7xxhalfmc.h" /* Header file of FMC HAL module */
#include "hdulibstm32f7xxhalnor.h"  /* provides a generic firmware to drive NOR memories */
#include "hdulibstm32f7xxhalrccex.h" /* Header file of RCC HAL Extension module.*/
#include "hdudispfucos.h"   /* defines the implementation of uC/OS routines  */
#include "hdulibstm32f7xxhalgpio.h" /* Header file of GPIO HAL module. */
#include "hdulibbasictypes.h"  /* Standard basic data type definitions */
#include "hdulibstm32hallegacy.h" /* definition for the STM32Cube HAL */

static T_NOR_HANDLE_TYPE Nor_handle = {0};
static T_FMC_NORSRAM_TIMING Timing = {0};

/*
 * Function                :  BspNorInit
 *
 * Description             :  This function initializes the NOR device.
 *
 * Formal parameter(s)     :  None
 *
 * Return Value            :  T_UINT8  - NOR memory status
 *
 * Assumption              :  None
 *
 */

T_UINT8 BspNorInit(void)
{
  static T_UINT8 nor_status = NOR_STATUS_ERROR;

  /*hdudispfbspnor-BspNorInit-DB-LLR-001*/
  Nor_handle.Instance  = FMC_NORSRAM_DEVICE;
  Nor_handle.Extended  = FMC_NORSRAM_EXTENDED_DEVICE;

  /* NOR device configuration */
  /*
   * Timing configuration derived from system clock (up to 216Mhz)
   *  for 108Mhz as NOR clock frequency
   */
  /*hdudispfbspnor-BspNorInit-DB-LLR-002*/
  Timing.AddressSetupTime      = FIFTEEN;
  Timing.AddressHoldTime       = ZERO;
  Timing.DataSetupTime         = TWENTY;
  Timing.BusTurnAroundDuration = TEN;
  Timing.CLKDivision           = TWO;
  Timing.DataLatency           = ZERO;
  Timing.AccessMode            = FMC_ACCESS_MODE_A;

  /*hdudispfbspnor-BspNorInit-DB-LLR-003*/
  Nor_handle.Init.NSBank             = FMC_NORSRAM_BANK1;
  Nor_handle.Init.DataAddressMux     = FMC_DATA_ADDRESS_MUX_DISABLE;
  Nor_handle.Init.MemoryType         = FMC_MEMORY_TYPE_NOR;
  Nor_handle.Init.MemoryDataWidth    = NOR_MEMORY_WIDTH;
  Nor_handle.Init.BurstAccessMode    = NOR_BURSTACCESS;
  Nor_handle.Init.WaitSignalPolarity = FMC_WAIT_SIGNAL_POLARITY_LOW;
  Nor_handle.Init.WaitSignalActive   = FMC_WAIT_TIMING_BEFORE_WS;
  Nor_handle.Init.WriteOperation     = FMC_WRITE_OPERATION_ENABLE;
  Nor_handle.Init.WaitSignal         = FMC_WAIT_SIGNAL_DISABLE;
  Nor_handle.Init.ExtendedMode       = FMC_EXTENDED_MODE_DISABLE;
  Nor_handle.Init.AsynchronousWait   = FMC_ASYNCHRONOUS_WAIT_DISABLE;
  Nor_handle.Init.WriteBurst         = NOR_WRITEBURST;
  Nor_handle.Init.ContinuousClock    = CONTINUOUSCLOCK_FEATURE;

  /*hdudispfbspnor-BspNorInit-DB-LLR-004*/
  /* NOR controller initialization */
  BspNorMspInit();

  /*hdudispfbspnor-BspNorInit-DB-LLR-005*/
  if(HalNorInit(&Nor_handle, &Timing, &Timing) != HAL_OK)
  {
    nor_status = NOR_STATUS_ERROR;
  }
  else
  {
    nor_status = NOR_STATUS_OK;
  }
  return nor_status;
}

/*
 * Function                :  BspNorMspInit
 *
 * Description             :  This function initializes the NOR MSP.
 *
 * Formal parameter(s)     :  None
 *
 * Return Value            :  T_UINT8  - NOR memory status
 *
 * Assumption              :  None
 *
 */

void BspNorMspInit()
{
  T_GPIO_INIT gpio_init_structure ={0};

  /*hdudispfbspnor-BspNorMspInit-DB-LLR-001*/
  /* Enable FMC clock */
  __HAL_RCC_FMC_CLK_ENABLE();

  /* Enable GPIOs clock */
  /*hdudispfbspnor-BspNorMspInit-DB-LLR-002*/
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*hdudispfbspnor-BspNorMspInit-DB-LLR-003*/
  __HAL_RCC_GPIOE_CLK_ENABLE();

  /*hdudispfbspnor-BspNorMspInit-DB-LLR-004*/
  __HAL_RCC_GPIOF_CLK_ENABLE();

  /*hdudispfbspnor-BspNorMspInit-DB-LLR-005*/
  __HAL_RCC_GPIOG_CLK_ENABLE();

  /*hdudispfbspnor-BspNorMspInit-DB-LLR-006*/
  /* Common GPIO configuration */
  gpio_init_structure.Mode      = GPIO_MODE_AF_PP;
  gpio_init_structure.Pull      = GPIO_PULLUP;
  gpio_init_structure.Speed     = GPIO_SPEED_HIGH;
  gpio_init_structure.Alternate = GPIO_AF12_FMC;

  /*hdudispfbspnor-BspNorMspInit-DB-LLR-007*/
  /* GPIOD configuration */
  gpio_init_structure.Pin   = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6   |\
                              GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11 |\
                              GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15;
  HalGpioInit(GPIOD, &gpio_init_structure);

  /*hdudispfbspnor-BspNorMspInit-DB-LLR-008*/
  /* GPIOE configuration */
  gpio_init_structure.Pin   = GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6|\
                              GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11 |\
                              GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15;
  HalGpioInit(GPIOE, &gpio_init_structure);

  /*hdudispfbspnor-BspNorMspInit-DB-LLR-009*/
  /* GPIOF configuration */
  gpio_init_structure.Pin   = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2| GPIO_PIN_3 | GPIO_PIN_4|\
                              GPIO_PIN_5 | GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15;
  HalGpioInit(GPIOF, &gpio_init_structure);

  /*hdudispfbspnor-BspNorMspInit-DB-LLR-010*/
  /* GPIOG configuration */
  gpio_init_structure.Pin   = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2| GPIO_PIN_3 | GPIO_PIN_4|\
                              GPIO_PIN_5 | GPIO_PIN_12 | GPIO_PIN_13;
  HalGpioInit(GPIOG, &gpio_init_structure);

  /*hdudispfbspnor-BspNorMspInit-DB-LLR-011*/
  gpio_init_structure.Pin =  GPIO_PIN_14;
  gpio_init_structure.Mode = GPIO_MODE_OUTPUT_PP;
  gpio_init_structure.Pull = GPIO_PULLDOWN;
  gpio_init_structure.Speed = GPIO_SPEED_HIGH;

  HalGpioInit(GPIOG, &gpio_init_structure);

  /*hdudispfbspnor-BspNorMspInit-DB-LLR-012*/
  HALGpioWritePin(GPIOG, GPIO_PIN_14, GPIO_PIN_RESET);

}
