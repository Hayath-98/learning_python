/*
 ******************************************************************************
 * License Information  :  Howell Instruments, Inc.                           *
 *                         "Licensed Software" and "All rights reserved".     *
 ******************************************************************************
 *  File                : hdulibstm32f7xxhalfmc.c
 *
 *  Description         : This file provides firmware functions to manage the
 *                        functionalities of the Flexible Memory Controller (FMC)
 *                        peripheral memories
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
 *      1.1           Shilpa A R    28-Jul-2017          -
 *      1.2           Shilpa A R    05-Sep-2017         100028
 *      1.3           Shilpa A R    02-Oct-2017         100064
 *      1.4           Shilpa A R    04-Nov-2017         100156
 *
 * Additional References : None
 *
 ******************************************************************************
 */

/* Includes*/
#include "hdulibstm32f7xxhal.h"     /* Header files for HAL driver*/
#include "hdulibbasictypes.h"       /* Contains basic data types*/
#include "hdulibstm32f7xxhalfmc.h"   /* Header files for FMC HAL driver*/


#define BWTR_VAL  0x0FFFFFFF
/*
 * Function                :  FmcNorSramInit
 *
 * Description             :  This function Initialize the FMC_NORSRAM device
 *
 * Formal parameter(s)     :  T_FMC_NORSRAM *device - INOUT Pointer to NORSRAM device instance.
 *                            T_FMC_NORSRAM_INIT init - IN Pointer to NORSRAM Initialization
 *                             structure.
 *
 * Return Value            :  T_HAL_STATUS - HAL status
 *
 * Assumption              :  None
 *
 */

T_HAL_STATUS  FmcNorSramInit(T_FMC_NORSRAM *device, T_FMC_NORSRAM_INIT * init)
{
  T_UINT32 temp_reg = ZERO;

  /*hdulibstm32f7xxhalfmc-FmcNorSramInit-DB-LLR-001*/
  /* Get the BTCR register value */
  temp_reg = device->BTCR[init->NSBank];

  /*hdulibstm32f7xxhalfmc-FmcNorSramInit-DB-LLR-002*/
  /* Updated as per PR 100156 */
  /*
   * Clear MBKEN, MUXEN, MTYP, MWID, FACCEN, BURSTEN, WAITPOL,CPSIZE, WAITCFG, WREN,
   * WAITEN, EXTMOD, ASYNCWAIT, CBURSTRW, CCLKEN and WFDIS bits
   */
  temp_reg &= ((T_UINT32)~(FMC_BCR1_MBKEN     | FMC_BCR1_MUXEN    | FMC_BCR1_MTYP     | \
                       FMC_BCR1_MWID      | FMC_BCR1_FACCEN   | FMC_BCR1_BURSTEN  | \
                       FMC_BCR1_WAITPOL   | FMC_BCR1_CPSIZE    | FMC_BCR1_WAITCFG  | \
                       FMC_BCR1_WREN      | FMC_BCR1_WAITEN   | FMC_BCR1_EXTMOD   | \
                       FMC_BCR1_ASYNCWAIT | FMC_BCR1_CBURSTRW | FMC_BCR1_CCLKEN | FMC_BCR1_WFDIS));

  /*hdulibstm32f7xxhalfmc-FmcNorSramInit-DB-LLR-003*/
  /* Set NORSRAM device control parameters */
  temp_reg |= (T_UINT32)(init->DataAddressMux       |\
                    init->MemoryType           |\
                    init->MemoryDataWidth      |\
                    init->BurstAccessMode      |\
                    init->WaitSignalPolarity   |\
                    init->WaitSignalActive     |\
                    init->WriteOperation       |\
                    init->WaitSignal           |\
                    init->ExtendedMode         |\
                    init->AsynchronousWait     |\
                    init->WriteBurst           |\
                    init->ContinuousClock      |\
                    init->PageSize             |\
                    init->WriteFifo);

  /*hdulibstm32f7xxhalfmc-FmcNorSramInit-DB-LLR-004*/
  if(FMC_MEMORY_TYPE_NOR == init->MemoryType)
  {
    temp_reg |= (T_UINT32)FMC_NORSRAM_FLASH_ACCESS_ENABLE;
  }
  else
  {
   ;
  }

  /*hdulibstm32f7xxhalfmc-FmcNorSramInit-DB-LLR-005*/
  device->BTCR[init->NSBank] = temp_reg;

  /*hdulibstm32f7xxhalfmc-FmcNorSramInit-DB-LLR-006*/
  /* Configure synchronous mode when Continuous clock is enabled for bank2..4 */
  if((FMC_CONTINUOUS_CLOCK_SYNC_ASYNC == init->ContinuousClock) &&
    (init->NSBank != FMC_NORSRAM_BANK1))
  {
    device->BTCR[FMC_NORSRAM_BANK1] |= (T_UINT32)(init->ContinuousClock);
  }
  else
  {
   ;
  }

  /*hdulibstm32f7xxhalfmc-FmcNorSramInit-DB-LLR-007*/
  if(init->NSBank != FMC_NORSRAM_BANK1)
  {
    device->BTCR[FMC_NORSRAM_BANK1] |= (T_UINT32)(init->WriteFifo);
  }
  else
  {
   ;
  }
  /*hdulibstm32f7xxhalfmc-FmcNorSramInit-DB-LLR-008*/
  return HAL_OK;
}


/*
 * Function                :  FmcNorSramTimingInit
 *
 * Description             :  This function Initialize the FMC_NORSRAM Timing
 *
 * Formal parameter(s)     :  T_FMC_NORSRAM device - INOUT Pointer to NORSRAM device instance
 *                            T_FMC_NORSRAM_TIMING timing - IN Pointer to NORSRAM timing structure
 *                            T_UINT32 bank - IN NORSRAM bank number
 *
 * Return Value            :   T_HAL_STATUS - HAL status
 *
 * Assumption              :  None
 *
 */

T_HAL_STATUS FmcNorSramTimingInit(T_FMC_NORSRAM *device, T_FMC_NORSRAM_TIMING *timing,
                                  T_UINT32 bank)
{
  T_UINT32 temp_reg = ZERO;

  /*hdulibstm32f7xxhalfmc-FmcNorSramTimingInit-DB-LLR-001*/
  /* Get the BTCR register value */
  temp_reg = device->BTCR[bank + ONE];

  /*hdulibstm32f7xxhalfmc-FmcNorSramTimingInit-DB-LLR-002*/
  /* Clear ADDSET, ADDHLD, DATAST, BUSTURN, CLKDIV, DATLAT and ACCMOD bits */
  temp_reg &= ((T_UINT32)~(FMC_BTR1_ADDSET  | FMC_BTR1_ADDHLD | FMC_BTR1_DATAST | \
                       FMC_BTR1_BUSTURN | FMC_BTR1_CLKDIV | FMC_BTR1_DATLAT | \
                       FMC_BTR1_ACCMOD));

  /*hdulibstm32f7xxhalfmc-FmcNorSramTimingInit-DB-LLR-003*/
  /* Set FMC_NORSRAM device timing parameters */
  temp_reg |= (T_UINT32)(timing->AddressSetupTime                  |\
                   ((timing->AddressHoldTime) << FOUR)          |\
                   ((timing->DataSetupTime) << EIGHT)            |\
                   ((timing->BusTurnAroundDuration) << SIXTEEN)   |\
                   (((timing->CLKDivision)-ONE) << TWENTY)         |\
                   (((timing->DataLatency)-TWO) << TWENTY_FOUR)         |\
                    (timing->AccessMode)
                    );
  /*hdulibstm32f7xxhalfmc-FmcNorSramTimingInit-DB-LLR-004*/
  device->BTCR[bank + ONE] = temp_reg;

  /*hdulibstm32f7xxhalfmc-FmcNorSramTimingInit-DB-LLR-005*/
  /* Configure Clock division value (in NORSRAM bank 1) when continuous clock is enabled */
  if(ZERO != (HAL_IS_BIT_SET(device->BTCR[FMC_NORSRAM_BANK1], FMC_BCR1_CCLKEN)))
  {
    temp_reg = (T_UINT32)(device->BTCR[FMC_NORSRAM_BANK1 + ONE] & ~(((T_UINT32)FIFTEEN) << TWENTY));
    temp_reg |= (T_UINT32)(((timing->CLKDivision)-ONE) << TWENTY);
    device->BTCR[FMC_NORSRAM_BANK1 + ONE] = temp_reg;
  }
  else
  {
   ;
  }
  /*hdulibstm32f7xxhalfmc-FmcNorSramTimingInit-DB-LLR-006*/
  return HAL_OK;
}

/*
 * Function                :  FmcNorSramExtendedTimingInit
 *
 * Description             :  This function initializes the FMC_NORSRAM Extended mode timing
 *                            according to the specified parameters in the T_FMC_NORSRAM_TIMING.
 *
 * Formal parameter(s)     :  T_FMC_NORSRAM_EXTENDED device - INOUT Pointer to NORSRAM
 *                             device instance
 *                            T_FMC_NORSRAM_TIMING timing - IN Pointer to NORSRAM timing structure
 *                            T_UINT32 bank - IN NORSRAM bank number
 *                            T_UINT32 extended_mode - IN Specifies the extended mode
 *
 * Return Value            :  T_HAL_STATUS - HAL status
 *
 * Assumption              :  None
 *
 */


T_HAL_STATUS  FmcNorSramExtendedTimingInit(T_FMC_NORSRAM_EXTENDED *device,
                        T_FMC_NORSRAM_TIMING *timing, T_UINT32 bank, T_UINT32 extended_mode)
{
  T_UINT32 temp_reg = ZERO;

   /*hdulibstm32f7xxhalfmc-FmcNorSramExtendedTimingInit-DB-LLR-001*/
  /* Set NORSRAM device timing register for write configuration, if extended mode is used */
  if(FMC_EXTENDED_MODE_ENABLE == extended_mode )
  {

    /* Get the BWTR register value */
    temp_reg = device->BWTR[bank];

    /* Clear ADDSET, ADDHLD, DATAST, BUSTURN, CLKDIV, DATLAT and ACCMOD bits */
    temp_reg &= ((T_UINT32)~(FMC_BWTR1_ADDSET  | FMC_BWTR1_ADDHLD | FMC_BWTR1_DATAST | \
                         FMC_BWTR1_BUSTURN | FMC_BWTR1_ACCMOD));

    temp_reg |= (T_UINT32)(timing->AddressSetupTime                 |\
                      ((timing->AddressHoldTime) << FOUR)          |\
                      ((timing->DataSetupTime) << EIGHT)            |\
                      ((timing->BusTurnAroundDuration) << SIXTEEN)   |\
                      (timing->AccessMode));

    device->BWTR[bank] = temp_reg;
  }
   /*hdulibstm32f7xxhalfmc-FmcNorSramExtendedTimingInit-DB-LLR-002*/
  else
  {
    device->BWTR[bank] = BWTR_VAL;
  }
  /*hdulibstm32f7xxhalfmc-FmcNorSramExtendedTimingInit-DB-LLR-003*/
  return HAL_OK;
}

/*
 * Function                :  FmcSdramInit
 *
 * Description             :  This function Initializes the FMC_SDRAM device timing according
 *                             to the specified parameters in the T_FMC_SDRAM_INIT
 *
 * Formal parameter(s)     :  T_FMC_SDRAM device - INOUT Pointer to SDRAM device instance
 *                            T_FMC_SDRAM_INIT Init - IN Pointer to SDRAM Initialization structure
 *
 * Return Value            :  T_HAL_STATUS - HAL state
 *
 * Assumption              :  None
 *
 */

T_HAL_STATUS FmcSdramInit(T_FMC_SDRAM *device, T_FMC_SDRAM_INIT *Init)
{
  T_UINT32 temp_reg1 = ZERO;
  T_UINT32 temp_reg2 = ZERO;

   /*hdulibstm32f7xxhalfmc-FmcSdramInit-DB-LLR-001*/
  /* Set SDRAM bank configuration parameters */
  if (Init->SDBank != FMC_SDRAM_BANK2)
  {
    temp_reg1 = device->SDCR[FMC_SDRAM_BANK1];

    /* Clear NC, NR, MWID, NB, CAS, WP, SDCLK, RBURST, and RPIPE bits */
    temp_reg1 &= ((T_UINT32)~(FMC_SDCR1_NC  | FMC_SDCR1_NR | FMC_SDCR1_MWID | \
                          FMC_SDCR1_NB  | FMC_SDCR1_CAS | FMC_SDCR1_WP   | \
                          FMC_SDCR1_SDCLK | FMC_SDCR1_RBURST | FMC_SDCR1_RPIPE));

    temp_reg1 |= (T_UINT32)(Init->ColumnBitsNumber   |\
                        Init->RowBitsNumber      |\
                        Init->MemoryDataWidth    |\
                        Init->InternalBankNumber |\
                        Init->CASLatency         |\
                        Init->WriteProtection    |\
                        Init->SDClockPeriod      |\
                        Init->ReadBurst          |\
                        Init->ReadPipeDelay
                        );
    device->SDCR[FMC_SDRAM_BANK1] = temp_reg1;
  }
   /*hdulibstm32f7xxhalfmc-FmcSdramInit-DB-LLR-002*/
  else /* FMC_Bank2_SDRAM */
  {
    temp_reg1 = device->SDCR[FMC_SDRAM_BANK1];

    /* Clear SDCLK, RBURST, and RPIPE bits */
    temp_reg1 &= ((T_UINT32)~(FMC_SDCR1_SDCLK | FMC_SDCR1_RBURST | FMC_SDCR1_RPIPE));

    temp_reg1 |= (T_UINT32)(Init->SDClockPeriod      |\
                        Init->ReadBurst          |\
                        Init->ReadPipeDelay);

    temp_reg2 = device->SDCR[FMC_SDRAM_BANK2];

    /* Clear NC, NR, MWID, NB, CAS, WP, SDCLK, RBURST, and RPIPE bits */
    temp_reg2 &= ((T_UINT32)~(FMC_SDCR1_NC  | FMC_SDCR1_NR | FMC_SDCR1_MWID | \
                          FMC_SDCR1_NB  | FMC_SDCR1_CAS | FMC_SDCR1_WP   | \
                          FMC_SDCR1_SDCLK | FMC_SDCR1_RBURST | FMC_SDCR1_RPIPE));

    temp_reg2 |= (T_UINT32)(Init->ColumnBitsNumber   |\
                       Init->RowBitsNumber       |\
                       Init->MemoryDataWidth     |\
                       Init->InternalBankNumber  |\
                       Init->CASLatency          |\
                       Init->WriteProtection);

    device->SDCR[FMC_SDRAM_BANK1] = temp_reg1;
    device->SDCR[FMC_SDRAM_BANK2] = temp_reg2;
  }
  /*hdulibstm32f7xxhalfmc-FmcSdramInit-DB-LLR-003*/
  return HAL_OK;
}

/*
 * Function                :  FmcSdramTimingInit
 *
 * Description             :  This function initializes the FMC_SDRAM device timing according
 *                            to the specified parameters in the T_FMC_SDRAM_TIMING.
 *
 * Formal parameter(s)     :  T_FMC_SDRAM device - INOUT Pointer to SDRAM device instance
 *                            T_FMC_SDRAM_TIMING timing -IN Pointer to SDRAM timing structure
 *                            T_UINT32 bank - IN SDRAM bank number
 *
 * Return Value            :  T_HAL_STATUS - HAL state
 *
 * Assumption              :  None
 *
 */

T_HAL_STATUS FmcSdramTimingInit(T_FMC_SDRAM *device, T_FMC_SDRAM_TIMING *timing, T_UINT32 bank)
{
  T_UINT32 temp_reg1 = ZERO;
  T_UINT32 temp_reg2 = ZERO;

   /*hdulibstm32f7xxhalfmc-FmcSdramTimingInit-DB-LLR-001*/
  /* Set SDRAM device timing parameters */
  if (bank != FMC_SDRAM_BANK2)
  {
    temp_reg1 = device->SDTR[FMC_SDRAM_BANK1];

    /* Clear TMRD, TXSR, TRAS, TRC, TWR, TRP and TRCD bits */
    temp_reg1 &= ((T_UINT32)~(FMC_SDTR1_TMRD  | FMC_SDTR1_TXSR | FMC_SDTR1_TRAS | \
                          FMC_SDTR1_TRC  | FMC_SDTR1_TWR | FMC_SDTR1_TRP | \
                          FMC_SDTR1_TRCD));

    temp_reg1 |= (T_UINT32)(((timing->LoadToActiveDelay)-ONE)           |\
                       (((timing->ExitSelfRefreshDelay)-ONE) << FOUR) |\
                       (((timing->SelfRefreshTime)-ONE) << EIGHT)      |\
                       (((timing->RowCycleDelay)-ONE) << TWELVE)       |\
                       (((timing->WriteRecoveryTime)-ONE) << SIXTEEN)    |\
                       (((timing->RPDelay)-ONE) << TWENTY)             |\
                       (((timing->RCDDelay)-ONE) << TWENTY_FOUR));
    device->SDTR[FMC_SDRAM_BANK1] = temp_reg1;
  }
   /*hdulibstm32f7xxhalfmc-FmcSdramTimingInit-DB-LLR-002*/
  else /* FMC_Bank2_SDRAM */
  {
    temp_reg1 = device->SDTR[FMC_SDRAM_BANK1];

    /* Clear TRC and TRP bits */
    temp_reg1 &= ((T_UINT32)~(FMC_SDTR1_TRC | FMC_SDTR1_TRP));

    temp_reg1 |= (T_UINT32)((((timing->RowCycleDelay)-ONE) << TWELVE)       |\
                        (((timing->RPDelay)-ONE) << TWENTY));

    temp_reg2 = device->SDTR[FMC_SDRAM_BANK2];

    /* Clear TMRD, TXSR, TRAS, TRC, TWR, TRP and TRCD bits */
    temp_reg2 &= ((T_UINT32)~(FMC_SDTR1_TMRD  | FMC_SDTR1_TXSR | FMC_SDTR1_TRAS | \
                          FMC_SDTR1_TRC  | FMC_SDTR1_TWR | FMC_SDTR1_TRP | \
                          FMC_SDTR1_TRCD));

    temp_reg2 |= (T_UINT32)(((timing->LoadToActiveDelay)-ONE)           |\
                       (((timing->ExitSelfRefreshDelay)-ONE) << FOUR)  |\
                       (((timing->SelfRefreshTime)-ONE) << EIGHT)       |\
                       (((timing->WriteRecoveryTime)-ONE) <<SIXTEEN)     |\
                       (((timing->RCDDelay)-ONE) << TWENTY_FOUR));

    device->SDTR[FMC_SDRAM_BANK1] = temp_reg1;
    device->SDTR[FMC_SDRAM_BANK2] = temp_reg2;
  }

   /*hdulibstm32f7xxhalfmc-FmcSdramTimingInit-DB-LLR-003*/
  return HAL_OK;
}

/*
 * Function                :  FmcSdramSendCommand
 *
 * Description             :  This function sends command to the FMC SDRAM bank
 *
 * Formal parameter(s)     :  T_FMC_SDRAM device - INOUT Pointer to SDRAM device instance
 *                            T_FMC_SDRAM_COMMAND command - IN Pointer to SDRAM command structure
 *                            T_UINT32 time_out - IN time_out wait value
 *
 * Return Value            :  T_HAL_STATUS - HAL state
 *
 * Assumption              :  None
 *
 */


T_HAL_STATUS FmcSdramSendCommand(T_FMC_SDRAM *device, T_FMC_SDRAM_COMMAND *command,
                                 T_UINT32 time_out)
{
  __IO T_UINT32 temp_reg = ZERO;
  T_UINT32 tick_start = ZERO;

   /*hdulibstm32f7xxhalfmc-FmcSdramSendCommand-DB-LLR-001*/
  /* Set command register */
  temp_reg = (T_UINT32)((command->CommandMode)              |\
              (command->CommandTarget)                      |\
              (((command->AutoRefreshNumber)-ONE) << FIVE)  |\
              ((command->ModeRegisterDefinition) << NINE));

  device->SDCMR = temp_reg;

   /*hdulibstm32f7xxhalfmc-FmcSdramSendCommand-DB-LLR-002*/
  /* Get tick */
  tick_start = HALGetTick();

   /*hdulibstm32f7xxhalfmc-FmcSdramSendCommand-DB-LLR-003*/
  /* wait until command is send */
  while(ZERO != (HAL_IS_BIT_SET(device->SDSR, FMC_SDSR_BUSY)))
  {
    /* Check for the time_out */
    if(time_out != HAL_MAX_DELAY)
    {
      if((ZERO == time_out)||((HALGetTick() - tick_start ) > time_out))
      {
        return HAL_TIMEOUT;
      }
      else
      {
        ; /* Does nothing */
      }
    }
   else
   {
     ; /* Does nothing */
   }
  }
   /*hdulibstm32f7xxhalfmc-FmcSdramSendCommand-DB-LLR-004*/
  return HAL_OK;
}

/*
 * Function                :  FmcSdramProgramRefreshRate
 *
 * Description             :  This function programs the SDRAM Memory Refresh rate.
 *
 * Formal parameter(s)     :  T_FMC_SDRAM device -INOUT Pointer to SDRAM device instance
 *                            T_UINT32 refresh_rate -IN  The SDRAM refresh rate value.
 *
 * Return Value            :  T_HAL_STATUS - HAL state
 *
 * Assumption              :  None
 *
 */

T_HAL_STATUS FmcSdramProgramRefreshRate(T_FMC_SDRAM *device, T_UINT32 refresh_rate)
{
   /*hdulibstm32f7xxhalfmc-FmcSdramProgramRefreshRate-DB-LLR-001*/
  /* Set the refresh rate in command register */
  device->SDRTR |= (refresh_rate<<ONE);

  return HAL_OK;
}



