/*
 ******************************************************************************
 * License Information  :  Howell Instruments, Inc.                           *
 *                         "Licensed Software" and "All rights reserved".     *
 ******************************************************************************
 *  File                : hdulibstm32756gevalsdram.c
 *
 *  Description         : This file includes the SDRAM driver for the MT48LC4M32B2B5-7 memory
 *                        device mounted on STM32756G-EVAL and STM32746G-EVAL evaluation boards.
 *
 *  Compiler            : GNU gcc(GNU Tools for ARM Embedded Processors) version 5.4.1 20160919
 *
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
 * <Version No.>     <Author>          <Date>         <Problem Report No.>
 *
 *      1.1          Ajay J G        28-Jul-2017            -
 *      1.2          Shilpa A R      01-Sep-2017         100028
 *
 * Additional References : None
 *
 ******************************************************************************
 */

/* Includes*/
#include "hdulibstm32756gevalsdram.h"   /* Header includes of file of SDRAM HAL module*/
#include "hdulibstm32f7xxhalfmc.h"       /* Header files for lfmc driver*/
#include "hdulibbasictypes.h"                /*Basic data types */
#include "hdulibstm32f7xxhalgpio.h"     /* Header files for Gpio driver*/
#include "hdulibstm32f7xxhaldma.h"      /* Header file of DMA HAL module. */
#include "hdulibstm32f7xxhalsdram.h"    /* Header file of SDRAM HAL module. */
#include "hdulibstm32f7xxhalrccex.h"    /* Header files for RCC EX HAL module*/
#include "hdulibstm32f7xxhalcortex.h"   /* Header file of CORTEX HAL module */
#include "hdulibstm32f7xxhal.h"         /* Header files for HAL driver*/
#include "hdulibcorecm7.h"              /* CMSIS STM32F7xx Core Peripheral Access Layer File*/
#include "hdulibstm32hallegacy.h"       /* defines the STM32Cube HAL constants, function */
#include "hdulibstm32f7xxhalgpioex.h"   /* Header file of GPIO HAL Extension module.*/

/*STM32756G_EVAL_SDRAM_Private_Variables */
static T_SDRAM_HANDLE Sdram_handle = {ZERO};
static T_FMC_SDRAM_TIMING Timing = {ZERO};
static T_FMC_SDRAM_COMMAND Command = {ZERO};


/*
 * Function                :  BspSdramInit
 *
 * Description             :  This function initializes the SDRAM device.
 *
 * Formal parameter(s)     :  None
 *
 * Return Value            :  T_UINT8 - SDRAM status
 *
 * Assumption              :  None
 *
 */

T_UINT8 BspSdramInit(void)
{
  static T_UINT8 sdram_status = SDRAM_ERROR;

  /*hdulibstm32756gevalsdram-BspSdramInit-DB-LLR-001*/
  /* SDRAM device configuration */
  Sdram_handle.Instance = FMC_SDRAM_DEVICE;

  /*hdulibstm32756gevalsdram-BspSdramInit-DB-LLR-002*/
  /* Timing configuration for 100Mhz as SDRAM clock frequency (System clock is up to 200Mhz) */
  Timing.LoadToActiveDelay    = TWO;
  Timing.ExitSelfRefreshDelay = SEVEN;
  Timing.SelfRefreshTime      = FOUR;
  Timing.RowCycleDelay        = SEVEN;
  Timing.WriteRecoveryTime    = TWO;
  Timing.RPDelay              = TWO;
  Timing.RCDDelay             = TWO;

  /*hdulibstm32756gevalsdram-BspSdramInit-DB-LLR-003*/
  Sdram_handle.Init.SDBank             = FMC_SDRAM_BANK1;
  Sdram_handle.Init.ColumnBitsNumber   = FMC_SDRAM_COLUMN_BITS_NUM_9;
  Sdram_handle.Init.RowBitsNumber      = FMC_SDRAM_ROW_BITS_NUM_12;
  Sdram_handle.Init.MemoryDataWidth    = SDRAM_MEMORY_WIDTH;
  Sdram_handle.Init.InternalBankNumber = FMC_SDRAM_INTERN_BANKS_NUM_4;
  Sdram_handle.Init.CASLatency         = FMC_SDRAM_CAS_LATENCY_3;
  Sdram_handle.Init.WriteProtection    = FMC_SDRAM_WRT_PRTCTN_DISABLE;
  Sdram_handle.Init.SDClockPeriod      = SDCLOCK_PERIOD;
  Sdram_handle.Init.ReadBurst          = FMC_SDRAM_RBURST_ENABLE;
  Sdram_handle.Init.ReadPipeDelay      = FMC_SDRAM_RPIPE_DELAY_0;

  /* SDRAM controller initialization */
  /*hdulibstm32756gevalsdram-BspSdramInit-DB-LLR-004*/
  BspSdramMspInit(&Sdram_handle); /* __weak function can be rewritten by the application */

  if(HALSdramInit(&Sdram_handle, &Timing) != HAL_OK)
  {
    /*hdulibstm32756gevalsdram-BspSdramInit-DB-LLR-005*/
    sdram_status = SDRAM_ERROR;
  }
  else
  {
    /*hdulibstm32756gevalsdram-BspSdramInit-DB-LLR-006*/
    sdram_status = SDRAM_OK;
  }

  /*hdulibstm32756gevalsdram-BspSdramInit-DB-LLR-007*/
  /* SDRAM initialization sequence */
  BspSdramInitializationSequence(REFRESH_COUNT);

  /*hdulibstm32756gevalsdram-BspSdramInit-DB-LLR-008*/
  return sdram_status;
}

/*
 * Function                :  BspSdramInitializationSequence
 *
 * Description             :  This function programs the SDRAM device.
 *
 * Formal parameter(s)     :  refresh_count - SDRAM refresh counter value
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */

void BspSdramInitializationSequence(T_UINT32 refresh_count)
{
  __IO T_UINT32 tmp_mrd = ZERO;

  /*hdulibstm32756gevalsdram-BspSdramInitializationSequence-DB-LLR-001*/
  /* Step 1: Configure a clock configuration enable command */
  Command.CommandMode            = FMC_SDRAM_CMD_CLK_ENABLE;
  Command.CommandTarget          = FMC_SDRAM_CMD_TARGET_BANK1;
  Command.AutoRefreshNumber      = ONE;
  Command.ModeRegisterDefinition = ZERO;

  /* Send the command */
  HalSdramSendCommand(&Sdram_handle, &Command, SDRAM_TIMEOUT);

  /* Step 2: Insert 100 us minimum delay */
  /* Inserted delay is equal to 1 ms due to systick time base unit (ms) */
 /*hdulibstm32756gevalsdram-BspSdramInitializationSequence-DB-LLR-002*/
  HalDelay(ONE);

  /*hdulibstm32756gevalsdram-BspSdramInitializationSequence-DB-LLR-003*/
  /* Step 3: Configure a PALL (pre charge all) command */
  Command.CommandMode            = FMC_SDRAM_CMD_PALL;
  Command.CommandTarget          = FMC_SDRAM_CMD_TARGET_BANK1;
  Command.AutoRefreshNumber      = ONE;
  Command.ModeRegisterDefinition = ZERO;

  /* Send the command */
  HalSdramSendCommand(&Sdram_handle, &Command, SDRAM_TIMEOUT);

  /*hdulibstm32756gevalsdram-BspSdramInitializationSequence-DB-LLR-004*/
  /* Step 4: Configure an Auto Refresh command */
  Command.CommandMode            = FMC_SDRAM_CMD_AUTOREFRESH_MODE;
  Command.CommandTarget          = FMC_SDRAM_CMD_TARGET_BANK1;
  Command.AutoRefreshNumber      = EIGHT;
  Command.ModeRegisterDefinition = ZERO;

  /* Send the command */
  HalSdramSendCommand(&Sdram_handle, &Command, SDRAM_TIMEOUT);

  /*hdulibstm32756gevalsdram-BspSdramInitializationSequence-DB-LLR-005*/
  /* Step 5: Program the external memory mode register */
  tmp_mrd = (T_UINT32)SDRAM_MODEREG_BURST_LENGTH_1          |\
                 SDRAM_MODEREG_BURST_TYPE_SEQUEN   |\
                     SDRAM_MODEREG_CAS_LATENCY_3           |\
                SDRAM_MODEREG_OPERATING_MODE_STD |\
                SDRAM_MODEREG_WRBURST_MODE_PRG;

  Command.CommandMode            = FMC_SDRAM_CMD_LOAD_MODE;
  Command.CommandTarget          = FMC_SDRAM_CMD_TARGET_BANK1;
  Command.AutoRefreshNumber      = ONE;
  Command.ModeRegisterDefinition = tmp_mrd;

  /* Send the command */
  HalSdramSendCommand(&Sdram_handle, &Command, SDRAM_TIMEOUT);

  /*hdulibstm32756gevalsdram-BspSdramInitializationSequence-DB-LLR-006*/
  /* Step 6: Set the refresh rate counter */
  /* Set the device refresh rate */
  HalSdramProgramRefreshRate(&Sdram_handle, refresh_count);
}


/*
 * Function                :  BspSdramMspInit
 *
 * Description             :  This function initializes SDRAM MSP.
 *
 * Formal parameter(s)     :  h_sdram: SDRAM handle
 *
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */

void BspSdramMspInit(T_SDRAM_HANDLE  *h_sdram)
{

  static T_DMA_HANDLE dma_handle = {ZERO};
  T_GPIO_INIT  gpio_init_structure = {ZERO};

  /*hdulibstm32756gevalsdram-BspSdramMspInit-DB-LLR-001*/
  /* Enable FMC clock */
  __HAL_RCC_FMC_CLK_ENABLE();

  /*hdulibstm32756gevalsdram-BspSdramMspInit-DB-LLR-002*/
  /* Enable chosen DMAx clock */
  __DMAX_CLK_ENABLE();

 /*hdulibstm32756gevalsdram-BspSdramMspInit-DB-LLR-003*/
  /* Enable GPIOs clock */
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOG_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOI_CLK_ENABLE();

  /*hdulibstm32756gevalsdram-BspSdramMspInit-DB-LLR-004*/
  /* Common GPIO configuration */
  gpio_init_structure.Mode      = GPIO_MODE_AF_PP;
  gpio_init_structure.Pull      = GPIO_PULLUP;
  gpio_init_structure.Speed     = GPIO_SPEED_FAST;
  gpio_init_structure.Alternate = GPIO_AF12_FMC;

  /*hdulibstm32756gevalsdram-BspSdramMspInit-DB-LLR-005*/
  /* GPIOD configuration */
  gpio_init_structure.Pin   = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_8| GPIO_PIN_9 | GPIO_PIN_10 |\
                              GPIO_PIN_14 | GPIO_PIN_15;


  HalGpioInit(GPIOD, &gpio_init_structure);

 /*hdulibstm32756gevalsdram-BspSdramMspInit-DB-LLR-006*/
  /* GPIOE configuration */
  gpio_init_structure.Pin   = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_7| GPIO_PIN_8 | GPIO_PIN_9 |\
                              GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 |\
                              GPIO_PIN_15;

  HalGpioInit(GPIOE, &gpio_init_structure);

  /*hdulibstm32756gevalsdram-BspSdramMspInit-DB-LLR-007*/
  /* GPIOF configuration */
  gpio_init_structure.Pin   = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2| GPIO_PIN_3 | GPIO_PIN_4 |\
                              GPIO_PIN_5 | GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 |\
                              GPIO_PIN_15;

  HalGpioInit(GPIOF, &gpio_init_structure);

  /*hdulibstm32756gevalsdram-BspSdramMspInit-DB-LLR-008*/
  /* GPIOG configuration */
  gpio_init_structure.Pin   = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_4| GPIO_PIN_5 | GPIO_PIN_8 |\
                              GPIO_PIN_15;
  HalGpioInit(GPIOG, &gpio_init_structure);

/*hdulibstm32756gevalsdram-BspSdramMspInit-DB-LLR-009*/
  /* GPIOH configuration */
  gpio_init_structure.Pin   = GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_5 | GPIO_PIN_8 | GPIO_PIN_9 |\
                              GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 |\
                              GPIO_PIN_15;
  HalGpioInit(GPIOH, &gpio_init_structure);

  /*hdulibstm32756gevalsdram-BspSdramMspInit-DB-LLR-010*/
  /* GPIOI configuration */
  gpio_init_structure.Pin   = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 |\
                              GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7 | GPIO_PIN_9 | GPIO_PIN_10;
  HalGpioInit(GPIOI, &gpio_init_structure);

  /*hdulibstm32756gevalsdram-BspSdramMspInit-DB-LLR-011*/
  /* Configure common DMA parameters */
  dma_handle.Init.Channel             = SDRAM_DMAX_CHANNEL;
  dma_handle.Init.Direction           = DMA_MEMORY_TO_MEMORY;
  dma_handle.Init.PeriphInc           = DMA_PINC_ENABLE;
  dma_handle.Init.MemInc              = DMA_MINC_ENABLE;
  dma_handle.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD;
  dma_handle.Init.MemDataAlignment    = DMA_MDATAALIGN_WORD;
  dma_handle.Init.Mode                = DMA_NORMAL;
  dma_handle.Init.Priority            = DMA_PRIORITY_HIGH;
  dma_handle.Init.FIFOMode            = DMA_FIFOMODE_DISABLE;
  dma_handle.Init.FIFOThreshold       = DMA_FIFO_THRESHOLD_FULL;
  dma_handle.Init.MemBurst            = DMA_MBURST_SINGLE;
  dma_handle.Init.PeriphBurst         = DMA_PBURST_SINGLE;

  dma_handle.Instance = SDRAM_DMAX_STREAM;

   /* Associate the DMA handle */
  __HAL_LINKDMA(h_sdram, hdma, dma_handle);

  /*hdulibstm32756gevalsdram-BspSdramMspInit-DB-LLR-012*/
  /* Deinitialize the stream for new transfer */
  HalDmaDeInit(&dma_handle);

  /*hdulibstm32756gevalsdram-BspSdramMspInit-DB-LLR-013*/
  /* Configure the DMA stream */
  HalDmaInit(&dma_handle);

  /*hdulibstm32756gevalsdram-BspSdramMspInit-DB-LLR-014*/
  /* NVIC configuration for DMA transfer complete interrupt */
  HalNvicSetPriority(SDRAM_DMAX_IRQN, MASK_LSB, ZERO);
  /*hdudispbstm32756gevalsdram-BspSdramMspInit-DB-LLR-015*/
  HalNvicEnableIrq(SDRAM_DMAX_IRQN);
}



