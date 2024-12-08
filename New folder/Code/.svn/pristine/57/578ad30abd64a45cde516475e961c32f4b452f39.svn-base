/*
 ******************************************************************************
 * License Information  :  Howell Instruments, Inc.                           *
 *                         "Licensed Software" and "All rights reserved".     *
 ******************************************************************************
 *  File                : hdulibstm32f7xxhalfmc.h
 *
 *  Description         : Header file of FMC HAL module
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
 *      1.2          Shilpa A R      02-Sep-2017           100028
 *      1.3          Shilpa A R      30-Sep-2017           100064
 *      1.4          Divya G P       09-Oct-2017           100064
 *
 * Additional References : None
 *
 ******************************************************************************
 */

/* Define to prevent recursive inclusion */
#ifndef _HDULIBSTM32F7XXHALFMC_H_
#define _HDULIBSTM32F7XXHALFMC_H_

/* Includes */
#include "hdulibstm32f7xxhaldef.h"      /*Contains the HAL defination module */
#include "hdulibstm32f746xx.h"         /* CMSIS Cortex-M7 Device Peripheral Access Layer */


#define IS_FMC_NORSRAM_BANK(BANK) (((BANK) == FMC_NORSRAM_BANK1) || \
                                   ((BANK) == FMC_NORSRAM_BANK2) || \
                                   ((BANK) == FMC_NORSRAM_BANK3) || \
                                   ((BANK) == FMC_NORSRAM_BANK4))

#define IS_FMC_MUX(__MUX__) (((__MUX__) == FMC_DATA_ADDRESS_MUX_DISABLE) || \
                              ((__MUX__) == FMC_DATA_ADDRESS_MUX_ENABLE))

#define IS_FMC_MEMORY(__MEMORY__) (((__MEMORY__) == FMC_MEMORY_TYPE_SRAM) || \
                                    ((__MEMORY__) == FMC_MEMORY_TYPE_PSRAM)|| \
                                    ((__MEMORY__) == FMC_MEMORY_TYPE_NOR))

#define IS_FMC_NORSRAM_MEMORY_WIDTH(__WIDTH__) (((__WIDTH__) == FMC_NORSRAM_MEM_BUS_WIDTH_8)  || \
                                                 ((__WIDTH__) == FMC_NORSRAM_MEM_BUS_WIDTH_16) || \
                                                 ((__WIDTH__) == FMC_NORSRAM_MEM_BUS_WIDTH_32))

#define IS_FMC_ACCESS_MODE(__MODE__) (((__MODE__) == FMC_ACCESS_MODE_A) || \
                                       ((__MODE__) == FMC_ACCESS_MODE_B) || \
                                       ((__MODE__) == FMC_ACCESS_MODE_C) || \
                                       ((__MODE__) == FMC_ACCESS_MODE_D))

#define IS_FMC_NAND_BANK(BANK) ((BANK) == FMC_NAND_BANK3)

#define IS_FMC_WAIT_FEATURE(FEATURE) (((FEATURE) == FMC_NAND_WAIT_FEATURE_DISABLE) || \
                                      ((FEATURE) == FMC_NAND_WAIT_FEATURE_ENABLE))

#define IS_FMC_NAND_MEMORY_WIDTH(WIDTH) (((WIDTH) == FMC_NAND_MEM_BUS_WIDTH_8) || \
                                         ((WIDTH) == FMC_NAND_MEM_BUS_WIDTH_16))

#define IS_FMC_ECC_STATE(STATE) (((STATE) == FMC_NAND_ECC_DISABLE) || \
                                 ((STATE) == FMC_NAND_ECC_ENABLE))

#define IS_FMC_ECCPAGE_SIZE(SIZE) (((SIZE) == FMC_NAND_ECC_PAGE_SIZE_256BYTE)  || \
                                   ((SIZE) == FMC_NAND_ECC_PAGE_SIZE_512BYTE)  || \
                                   ((SIZE) == FMC_NAND_ECC_PAGE_SIZE_1024BYTE) || \
                                   ((SIZE) == FMC_NAND_ECC_PAGE_SIZE_2048BYTE) || \
                                   ((SIZE) == FMC_NAND_ECC_PAGE_SIZE_4096BYTE) || \
                                   ((SIZE) == FMC_NAND_ECC_PAGE_SIZE_8192BYTE))

#define IS_FMC_SDMEMORY_WIDTH(WIDTH) (((WIDTH) == FMC_SDRAM_MEM_BUS_WIDTH_8)  || \
                                      ((WIDTH) == FMC_SDRAM_MEM_BUS_WIDTH_16) || \
                                      ((WIDTH) == FMC_SDRAM_MEM_BUS_WIDTH_32))

#define IS_FMC_WRITE_PROTECTION(__WRITE__) (((__WRITE__) == FMC_SDRAM_WRT_PRTCTN_DISABLE) || \
                                            ((__WRITE__) == FMC_SDRAM_WRT_PRTCTN_ENABLE))

#define IS_FMC_SDCLOCK_PERIOD(__PERIOD__) (((__PERIOD__) == FMC_SDRAM_CLOCK_DISABLE)  || \
                                           ((__PERIOD__) == FMC_SDRAM_CLOCK_PERIOD_2) || \
                                           ((__PERIOD__) == FMC_SDRAM_CLOCK_PERIOD_3))

#define IS_FMC_READ_BURST(__RBURST__) (((__RBURST__) == FMC_SDRAM_RBURST_DISABLE) || \
                                       ((__RBURST__) == FMC_SDRAM_RBURST_ENABLE))

#define IS_FMC_READPIPE_DELAY(__DELAY__) (((__DELAY__) == FMC_SDRAM_RPIPE_DELAY_0) || \
                                          ((__DELAY__) == FMC_SDRAM_RPIPE_DELAY_1) || \
                                          ((__DELAY__) == FMC_SDRAM_RPIPE_DELAY_2))

#define IS_FMC_COMMAND_MODE(__COMMAND__) (((__COMMAND__) == FMC_SDRAM_CMD_NORMAL_MODE)      || \
                                          ((__COMMAND__) == FMC_SDRAM_CMD_CLK_ENABLE)       || \
                                          ((__COMMAND__) == FMC_SDRAM_CMD_PALL)             || \
                                          ((__COMMAND__) == FMC_SDRAM_CMD_AUTOREFRESH_MODE) || \
                                          ((__COMMAND__) == FMC_SDRAM_CMD_LOAD_MODE)        || \
                                          ((__COMMAND__) == FMC_SDRAM_CMD_SELFREFRESH_MODE) || \
                                          ((__COMMAND__) == FMC_SDRAM_CMD_POWERDOWN_MODE))

#define IS_FMC_COMMAND_TARGET(__TARGET__) (((__TARGET__) == FMC_SDRAM_CMD_TARGET_BANK1) || \
                                           ((__TARGET__) == FMC_SDRAM_CMD_TARGET_BANK2) || \
                                           ((__TARGET__) == FMC_SDRAM_CMD_TARGET_BANK1_2))


#define IS_FMC_TCLR_TIME(__TIME__) ((__TIME__) <= 255)

#define IS_FMC_TAR_TIME(TIME) ((TIME) <= 255)

#define IS_FMC_SETUP_TIME(TIME) ((TIME) <= 254)

#define IS_FMC_WAIT_TIME(TIME) ((TIME) <= 254)

#define IS_FMC_HOLD_TIME(TIME) ((TIME) <= 254)

#define IS_FMC_HIZ_TIME(TIME) ((TIME) <= 254)


#define IS_FMC_BURSTMODE(__STATE__) (((__STATE__) == FMC_BURST_ACCESS_MODE_DISABLE) || \
                                      ((__STATE__) == FMC_BURST_ACCESS_MODE_ENABLE))

#define IS_FMC_WAIT_POLARITY(__POLARITY__) (((__POLARITY__) == FMC_WAIT_SIGNAL_POLARITY_LOW) || \
                                             ((__POLARITY__) == FMC_WAIT_SIGNAL_POLARITY_HIGH))

#define IS_FMC_WAIT_SIGNAL_ACTIVE(__ACTIVE__) (((__ACTIVE__) == FMC_WAIT_TIMING_BEFORE_WS) || \
                                                ((__ACTIVE__) == FMC_WAIT_TIMING_DURING_WS))

#define IS_FMC_WRITE_OPERATION(__OPERATION__) (((__OPERATION__)== FMC_WRITE_OPERATION_DISABLE) || \
                                                ((__OPERATION__) == FMC_WRITE_OPERATION_ENABLE))

#define IS_FMC_WAITE_SIGNAL(__SIGNAL__) (((__SIGNAL__) == FMC_WAIT_SIGNAL_DISABLE) || \
                                          ((__SIGNAL__) == FMC_WAIT_SIGNAL_ENABLE))

#define IS_FMC_EXTENDED_MODE(__MODE__) (((__MODE__) == FMC_EXTENDED_MODE_DISABLE) || \
                                         ((__MODE__) == FMC_EXTENDED_MODE_ENABLE))

#define IS_FMC_ASYNWAIT(__STATE__) (((__STATE__) == FMC_ASYNCHRONOUS_WAIT_DISABLE) || \
                                     ((__STATE__) == FMC_ASYNCHRONOUS_WAIT_ENABLE))

#define IS_FMC_DATA_LATENCY(__LATENCY__) (((__LATENCY__) > 1) && ((__LATENCY__) <= 17))

#define IS_FMC_WRITE_BURST(__BURST__) (((__BURST__) == FMC_WRITE_BURST_DISABLE) || \
                                        ((__BURST__) == FMC_WRITE_BURST_ENABLE))

#define IS_FMC_CONTINOUS_CLOCK(CCLOCK) (((CCLOCK) == FMC_CONTINUOUS_CLOCK_SYNC_ONLY) || \
                                        ((CCLOCK) == FMC_CONTINUOUS_CLOCK_SYNC_ASYNC))

#define IS_FMC_ADDRESS_SETUP_TIME(__TIME__) ((__TIME__) <= 15)

#define IS_FMC_ADDRESS_HOLD_TIME(__TIME__) (((__TIME__) > 0) && ((__TIME__) <= 15))

#define IS_FMC_DATASETUP_TIME(__TIME__) (((__TIME__) > 0) && ((__TIME__) <= 255))

#define IS_FMC_TURNAROUND_TIME(__TIME__) ((__TIME__) <= 15)

#define IS_FMC_CLK_DIV(DIV) (((DIV) > 1) && ((DIV) <= 16))

#define IS_FMC_LOADTOACTIVE_DELAY(__DELAY__) (((__DELAY__) > 0) && ((__DELAY__) <= 16))

#define IS_FMC_EXITSELFREFRESH_DELAY(__DELAY__) (((__DELAY__) > 0) && ((__DELAY__) <= 16))

#define IS_FMC_SELFREFRESH_TIME(__TIME__) (((__TIME__) > 0) && ((__TIME__) <= 16))

#define IS_FMC_ROWCYCLE_DELAY(__DELAY__) (((__DELAY__) > 0) && ((__DELAY__) <= 16))

#define IS_FMC_WRITE_RECOVERY_TIME(__TIME__) (((__TIME__) > 0) && ((__TIME__) <= 16))

#define IS_FMC_RP_DELAY(__DELAY__) (((__DELAY__) > 0) && ((__DELAY__) <= 16))

#define IS_FMC_RCD_DELAY(__DELAY__) (((__DELAY__) > 0) && ((__DELAY__) <= 16))

#define IS_FMC_AUTOREFRESH_NUMBER(__NUMBER__) (((__NUMBER__) > 0) && ((__NUMBER__) <= 16))

#define IS_FMC_MODE_REGISTER(__CONTENT__) ((__CONTENT__) <= 8191)

#define IS_FMC_REFRESH_RATE(__RATE__) ((__RATE__) <= 8191)

#define IS_FMC_NORSRAM_EXTENDED_DEVICE(__INSTANCE__) ((__INSTANCE__) == FMC_NORSRAM_EXTENDED_DEVICE)

#define IS_FMC_NAND_DEVICE(__INSTANCE__) ((__INSTANCE__) == FMC_NAND_DEVICE)

#define IS_FMC_SDRAM_BANK(BANK) (((BANK) == FMC_SDRAM_BANK1) || \
                                 ((BANK) == FMC_SDRAM_BANK2))

#define IS_FMC_COLUMNBITS_NUMBER(COLUMN) (((COLUMN) == FMC_SDRAM_COLUMN_BITS_NUM_8)  || \
                                          ((COLUMN) == FMC_SDRAM_COLUMN_BITS_NUM_9)  || \
                                          ((COLUMN) == FMC_SDRAM_COLUMN_BITS_NUM_10) || \
                                          ((COLUMN) == FMC_SDRAM_COLUMN_BITS_NUM_11))

#define IS_FMC_ROWBITS_NUMBER(ROW) (((ROW) == FMC_SDRAM_ROW_BITS_NUM_11) || \
                                    ((ROW) == FMC_SDRAM_ROW_BITS_NUM_12) || \
                                    ((ROW) == FMC_SDRAM_ROW_BITS_NUM_13))

#define IS_FMC_INTERNALBANK_NUMBER(NUMBER) (((NUMBER) == FMC_SDRAM_INTERN_BANKS_NUM_2) || \
                                            ((NUMBER) == FMC_SDRAM_INTERN_BANKS_NUM_4))


#define IS_FMC_CAS_LATENCY(LATENCY) (((LATENCY) == FMC_SDRAM_CAS_LATENCY_1) || \
                                     ((LATENCY) == FMC_SDRAM_CAS_LATENCY_2) || \
                                     ((LATENCY) == FMC_SDRAM_CAS_LATENCY_3))

#define IS_FMC_PAGESIZE(__SIZE__) (((__SIZE__) == FMC_PAGE_SIZE_NONE) || \
                                   ((__SIZE__) == FMC_PAGE_SIZE_128) || \
                                   ((__SIZE__) == FMC_PAGE_SIZE_256) || \
                                   ((__SIZE__) == FMC_PAGE_SIZE_512) || \
                                   ((__SIZE__) == FMC_PAGE_SIZE_1024))

#define IS_FMC_WRITE_FIFO(__FIFO__) (((__FIFO__) == FMC_WRITE_FIFO_DISABLE) || \
                                     ((__FIFO__) == FMC_WRITE_FIFO_ENABLE))
#define T_FMC_NORSRAM            T_FMC_BANK1
#define T_FMC_NORSRAM_EXTENDED   T_FMC_BANK1E
#define T_FMC_SDRAM              T_FMC_BANK5_6

/* added for PR 100064 */
#define FMC_NORSRAM_DEVICE             FMC_BANK1
#define FMC_NORSRAM_EXTENDED_DEVICE    FMC_BANK1E

#define FMC_SDRAM_DEVICE               FMC_BANK5_6


typedef struct
{
  T_UINT32 NSBank;                /* Specifies the NORSRAM memory device that will be used. */

  T_UINT32 DataAddressMux;       /*
                                  * Specifies whether the address and data values are
                                  *  multiplexed on the data bus or not.
                                  */

  T_UINT32 MemoryType;           /*
                                  * Specifies the type of external memory attached to
                                  * the corresponding memory device.
                                  */

  T_UINT32 MemoryDataWidth;       /* Specifies the external memory data width. */

  T_UINT32 BurstAccessMode;      /*
                                  * Enables or disables the burst access mode for Flash memory,
                                  * valid only with synchronous burst Flash memories.
                                  */

  T_UINT32 WaitSignalPolarity;   /*
                                  * Specifies the wait signal polarity, valid only when accessing
                                  * the Flash memory in burst mode.
                                  */

  T_UINT32 WaitSignalActive;     /*
                                  * Specifies if the wait signal is asserted by the memory one
                                  * clock cycle before the wait state or during the wait state,
                                  * valid only when accessing memories in burst mode.
                                  */

  T_UINT32 WriteOperation;       /*
                                  * Enables or disables the write operation
                                  * in the selected device by the FMC.
                                  */

  T_UINT32 WaitSignal;           /*
                                  * Enables or disables the wait state insertion via wait
                                  * signal, valid for Flash memory access in burst mode.
                                  */

  T_UINT32 ExtendedMode;          /* Enables or disables the extended mode.*/

  T_UINT32 AsynchronousWait;     /*
                                  * Enables or disables wait signal during asynchronous transfers,
                                  * valid only with asynchronous Flash memories.
                                  */

  T_UINT32 WriteBurst;            /* Enables or disables the write burst operation. */

  T_UINT32 ContinuousClock;       /*
                                   * Enables or disables the FMC clock output to external
                                   * memory devices.
                                   */


  T_UINT32 WriteFifo;             /*
                                   * Enables or disables the write FIFO used
                                   *    by the FMC controller.
                                   */

  T_UINT32 PageSize;              /* Specifies the memory page size.*/

}T_FMC_NORSRAM_INIT;


typedef struct
{
  T_UINT32 AddressSetupTime;     /*
                                  * Defines the number of HCLK cycles to configure
                                  * the duration of the address setup time.
                                  * This parameter can be a value between Min_Data = 0
                                  * and Max_Data = 15.
                                  * @note This parameter is not used with synchronous NOR
                                  * Flash memories.
                                  */

  T_UINT32 AddressHoldTime;      /*
                                  * Defines the number of HCLK cycles to configure
                                  * the duration of the address hold time.
                                  * This parameter can be a value between Min_Data = 1
                                  * and Max_Data = 15.
                                  * @note This parameter is not used with synchronous NOR
                                  * Flash memories.  .
                                  */

  T_UINT32 DataSetupTime;        /*
                                  * Defines the number of HCLK cycles to configure
                                  * the duration of the data setup time.
                                  * This parameter can be a value between Min_Data = 1
                                  * and Max_Data = 255.
                                  * @note This parameter is used for SRAMs, ROMs and asynchronous
                                  * multiplexed NOR Flash memories.
                                  */

  T_UINT32 BusTurnAroundDuration;/*
                                  * Defines the number of HCLK cycles to configure
                                  * the duration of the bus turnaround.
                                  * This parameter can be a value between Min_Data = 0
                                  * and Max_Data = 15.
                                  * @note This parameter is only used for multiplexed
                                  * NOR Flash memories.
                                  */

  T_UINT32 CLKDivision;          /*
                                  * Defines the period of CLK clock output signal, expressed
                                  * in number of
                                  * HCLK cycles. This parameter can be a value between
                                  * Min_Data = 2 and Max_Data = 16.
                                  * @note This parameter is not used for asynchronous NOR Flash
                                  * ,SRAM or ROM accesses.
                                  */

  T_UINT32 DataLatency;          /*
                                  * Defines the number of memory clock cycles to issue
                                  * to the memory before getting the first data.
                                  * The parameter value depends on the memory type as shown below:
                                  * - It must be set to 0 in case of a CRAM
                                  * - It is don't care in asynchronous NOR, SRAM or ROM accesses
                                  * - It may assume a value between Min_Data = 2
                                  *   and Max_Data = 17 in NOR Flash memories
                                  *   with synchronous burst mode enable
                                  */

  T_UINT32 AccessMode;           /*
                                  * Specifies the asynchronous access mode.
                                  *   This parameter can be a value of @ref FMC_Access_Mode
                                  */
}T_FMC_NORSRAM_TIMING;


typedef struct
{
  T_UINT32 SDBank;                      /* Specifies the SDRAM memory device that will be used.*/

  T_UINT32 ColumnBitsNumber;            /* Defines the number of bits of column address.*/

  T_UINT32 RowBitsNumber;               /* Defines the number of bits of row address.*/

  T_UINT32 MemoryDataWidth;             /* Defines the memory device width.*/

  T_UINT32 InternalBankNumber;          /* Defines the number of the device's internal banks.*/

  T_UINT32 CASLatency;                  /*
                                         * Defines the SDRAM CAS latency in number of
                                         * memory clock cycles.
                                         */

  T_UINT32 WriteProtection;             /* Enables the SDRAM device to be accessed in write mode.*/

  T_UINT32 SDClockPeriod;               /*
                                         * Define the SDRAM Clock Period for both SDRAM devices
                                         * and they allow to disable the clock before
                                         * changing frequency.
                                         */

  T_UINT32 ReadBurst;                   /*
                                         * This bit enable the SDRAM controller to anticipate
                                         * the next read   commands during the CAS latency and
                                         * stores data in the Read FIFO.
                                         */

  T_UINT32 ReadPipeDelay;               /*
                                         * Define the delay in system clock cycles on
                                         * read data path.
                                         */
}T_FMC_SDRAM_INIT;


typedef struct
{
  T_UINT32 LoadToActiveDelay;      /*
                                    * Defines the delay between a Load Mode Register command and
                                    * an active or Refresh command in number of memory
                                    * clock cycles.This parameter can be a value between
                                    * Min_Data = 1 and Max_Data = 16
                                    */

  T_UINT32 ExitSelfRefreshDelay;   /*
                                    * Defines the delay from releasing the self refresh command to
                                    * issuing the Activate command in number of memory
                                    * clock cycles. This parameter can be a value between
                                    * Min_Data = 1 and Max_Data = 16
                                    */

  T_UINT32 SelfRefreshTime;        /*
                                    * Defines the minimum Self Refresh period in number of
                                    * memory clock cycles.
                                    * This parameter can be a value between Min_Data = 1
                                    * and Max_Data = 16
                                    */

  T_UINT32 RowCycleDelay;          /*
                                    * Defines the delay between the Refresh command and the
                                    * Activate command and the delay between two consecutive
                                    * Refresh commands in number of  memory clock cycles.
                                    * This parameter can be a value between Min_Data = 1
                                    * and Max_Data = 16
                                    */

  T_UINT32 WriteRecoveryTime;      /*
                                    * Defines the Write recovery Time in number of memory
                                    * clock cycles. This parameter can be a value between
                                    * Min_Data = 1 and Max_Data = 16
                                    */

  T_UINT32 RPDelay;                /*
                                    * Defines the delay between a Precharge Command and an
                                    * other command in number of memory clock cycles.
                                    * This parameter can be a value between Min_Data = 1
                                    * and Max_Data = 16
                                    */

  T_UINT32 RCDDelay;               /*
                                    * Defines the delay between the Activate Command and a
                                    * Read/Write  command in number of memory clock cycles.
                                    * This parameter can be a value between Min_Data = 1
                                    * and Max_Data = 16
                                    */
}T_FMC_SDRAM_TIMING;


typedef struct
{
  T_UINT32 CommandMode;            /*
                                    * Defines the command issued to the SDRAM device.
                                    */

  T_UINT32 CommandTarget;          /*
                                    * Defines which device (1 or 2) the command will be issued to.
                                    */

  T_UINT32 AutoRefreshNumber;      /*
                                    *Defines the number of consecutive auto refresh
                                    */

  T_UINT32 ModeRegisterDefinition; /*Defines the SDRAM Mode register content*/
}T_FMC_SDRAM_COMMAND;

#define FMC_NORSRAM_BANK1                       ((T_UINT32)0x00000000U)
#define FMC_NORSRAM_BANK2                       ((T_UINT32)0x00000002U)
#define FMC_NORSRAM_BANK3                       ((T_UINT32)0x00000004U)
#define FMC_NORSRAM_BANK4                       ((T_UINT32)0x00000006U)
#define FMC_DATA_ADDRESS_MUX_DISABLE            ((T_UINT32)0x00000000U)
#define FMC_DATA_ADDRESS_MUX_ENABLE             ((T_UINT32)0x00000002U)
#define FMC_MEMORY_TYPE_SRAM                    ((T_UINT32)0x00000000U)
#define FMC_MEMORY_TYPE_PSRAM                   ((T_UINT32)0x00000004U)
#define FMC_MEMORY_TYPE_NOR                     ((T_UINT32)0x00000008U)
#define FMC_NORSRAM_MEM_BUS_WIDTH_8             ((T_UINT32)0x00000000U)
#define FMC_NORSRAM_MEM_BUS_WIDTH_16            ((T_UINT32)0x00000010U)
#define FMC_NORSRAM_MEM_BUS_WIDTH_32            ((T_UINT32)0x00000020U)
#define FMC_NORSRAM_FLASH_ACCESS_ENABLE         ((T_UINT32)0x00000040U)
#define FMC_NORSRAM_FLASH_ACCESS_DISABLE        ((T_UINT32)0x00000000U)
#define FMC_BURST_ACCESS_MODE_DISABLE           ((T_UINT32)0x00000000U)
#define FMC_BURST_ACCESS_MODE_ENABLE            ((T_UINT32)0x00000100U)
#define FMC_WAIT_SIGNAL_POLARITY_LOW            ((T_UINT32)0x00000000U)
#define FMC_WAIT_SIGNAL_POLARITY_HIGH           ((T_UINT32)0x00000200U)
#define FMC_WAIT_TIMING_BEFORE_WS               ((T_UINT32)0x00000000U)
#define FMC_WAIT_TIMING_DURING_WS               ((T_UINT32)0x00000800U)
#define FMC_WRITE_OPERATION_DISABLE             ((T_UINT32)0x00000000U)
#define FMC_WRITE_OPERATION_ENABLE              ((T_UINT32)0x00001000U)
#define FMC_WAIT_SIGNAL_DISABLE                 ((T_UINT32)0x00000000U)
#define FMC_WAIT_SIGNAL_ENABLE                  ((T_UINT32)0x00002000U)
#define FMC_EXTENDED_MODE_DISABLE               ((T_UINT32)0x00000000U)
#define FMC_EXTENDED_MODE_ENABLE                ((T_UINT32)0x00004000U)
#define FMC_ASYNCHRONOUS_WAIT_DISABLE           ((T_UINT32)0x00000000U)
#define FMC_ASYNCHRONOUS_WAIT_ENABLE            ((T_UINT32)0x00008000U)
#define FMC_PAGE_SIZE_NONE                      ((T_UINT32)0x00000000U)
#define FMC_PAGE_SIZE_128                       ((T_UINT32)FMC_BCR1_CPSIZE_0)
#define FMC_PAGE_SIZE_256                       ((T_UINT32)FMC_BCR1_CPSIZE_1)
#define FMC_PAGE_SIZE_512                       ((T_UINT32)(FMC_BCR1_CPSIZE_0 | FMC_BCR1_CPSIZE_1))
#define FMC_PAGE_SIZE_1024                      ((T_UINT32)FMC_BCR1_CPSIZE_2)
#define FMC_WRITE_BURST_DISABLE                 ((T_UINT32)0x00000000U)
#define FMC_WRITE_BURST_ENABLE                  ((T_UINT32)0x00080000U)
#define FMC_CONTINUOUS_CLOCK_SYNC_ONLY          ((T_UINT32)0x00000000U)
#define FMC_CONTINUOUS_CLOCK_SYNC_ASYNC         ((T_UINT32)0x00100000U)
#define FMC_WRITE_FIFO_DISABLE                  ((T_UINT32)FMC_BCR1_WFDIS)
#define FMC_WRITE_FIFO_ENABLE                   ((T_UINT32)0x00000000U)
#define FMC_ACCESS_MODE_A                       ((T_UINT32)0x00000000U)
#define FMC_ACCESS_MODE_B                       ((T_UINT32)0x10000000U)
#define FMC_ACCESS_MODE_C                       ((T_UINT32)0x20000000U)
#define FMC_ACCESS_MODE_D                       ((T_UINT32)0x30000000)
#define FMC_NAND_BANK3                          ((T_UINT32)0x00000100U)
#define FMC_NAND_WAIT_FEATURE_DISABLE           ((T_UINT32)0x00000000U)
#define FMC_NAND_WAIT_FEATURE_ENABLE            ((T_UINT32)0x00000002U)
#define FMC_PCR_MEMORY_TYPE_NAND                ((T_UINT32)0x00000008U)
#define FMC_NAND_MEM_BUS_WIDTH_8                ((T_UINT32)0x00000000U)
#define FMC_NAND_MEM_BUS_WIDTH_16               ((T_UINT32)0x00000010U)
#define FMC_NAND_ECC_DISABLE                    ((T_UINT32)0x00000000U)
#define FMC_NAND_ECC_ENABLE                     ((T_UINT32)0x00000040U)
#define FMC_NAND_ECC_PAGE_SIZE_256BYTE          ((T_UINT32)0x00000000U)
#define FMC_NAND_ECC_PAGE_SIZE_512BYTE          ((T_UINT32)0x00020000U)
#define FMC_NAND_ECC_PAGE_SIZE_1024BYTE         ((T_UINT32)0x00040000U)
#define FMC_NAND_ECC_PAGE_SIZE_2048BYTE         ((T_UINT32)0x00060000U)
#define FMC_NAND_ECC_PAGE_SIZE_4096BYTE         ((T_UINT32)0x00080000U)
#define FMC_NAND_ECC_PAGE_SIZE_8192BYTE         ((T_UINT32)0x000A0000U)
#define FMC_SDRAM_BANK1                         ((T_UINT32)0x00000000U)
#define FMC_SDRAM_BANK2                         ((T_UINT32)0x00000001U)
#define FMC_SDRAM_COLUMN_BITS_NUM_8             ((T_UINT32)0x00000000U)
#define FMC_SDRAM_COLUMN_BITS_NUM_9             ((T_UINT32)0x00000001U)
#define FMC_SDRAM_COLUMN_BITS_NUM_10            ((T_UINT32)0x00000002U)
#define FMC_SDRAM_COLUMN_BITS_NUM_11            ((T_UINT32)0x00000003U)
#define FMC_SDRAM_ROW_BITS_NUM_11               ((T_UINT32)0x00000000U)
#define FMC_SDRAM_ROW_BITS_NUM_12               ((T_UINT32)0x00000004U)
#define FMC_SDRAM_ROW_BITS_NUM_13               ((T_UINT32)0x00000008U)
#define FMC_SDRAM_MEM_BUS_WIDTH_8               ((T_UINT32)0x00000000U)
#define FMC_SDRAM_MEM_BUS_WIDTH_16              ((T_UINT32)0x00000010U)
#define FMC_SDRAM_MEM_BUS_WIDTH_32              ((T_UINT32)0x00000020U)
#define FMC_SDRAM_INTERN_BANKS_NUM_2            ((T_UINT32)0x00000000U)
#define FMC_SDRAM_INTERN_BANKS_NUM_4            ((T_UINT32)0x00000040U)
#define FMC_SDRAM_CAS_LATENCY_1                 ((T_UINT32)0x00000080U)
#define FMC_SDRAM_CAS_LATENCY_2                 ((T_UINT32)0x00000100U)
#define FMC_SDRAM_CAS_LATENCY_3                 ((T_UINT32)0x00000180)
#define FMC_SDRAM_WRT_PRTCTN_DISABLE            ((T_UINT32)0x00000000U)
#define FMC_SDRAM_WRT_PRTCTN_ENABLE             ((T_UINT32)0x00000200U)
#define FMC_SDRAM_CLOCK_DISABLE                 ((T_UINT32)0x00000000U)
#define FMC_SDRAM_CLOCK_PERIOD_2                ((T_UINT32)0x00000800U)
#define FMC_SDRAM_CLOCK_PERIOD_3                ((T_UINT32)0x00000C00)
#define FMC_SDRAM_RBURST_DISABLE                ((T_UINT32)0x00000000U)
#define FMC_SDRAM_RBURST_ENABLE                 ((T_UINT32)0x00001000U)
#define FMC_SDRAM_RPIPE_DELAY_0                 ((T_UINT32)0x00000000U)
#define FMC_SDRAM_RPIPE_DELAY_1                 ((T_UINT32)0x00002000U)
#define FMC_SDRAM_RPIPE_DELAY_2                 ((T_UINT32)0x00004000U)
#define FMC_SDRAM_CMD_NORMAL_MODE               ((T_UINT32)0x00000000U)
#define FMC_SDRAM_CMD_CLK_ENABLE                ((T_UINT32)0x00000001U)
#define FMC_SDRAM_CMD_PALL                      ((T_UINT32)0x00000002U)
#define FMC_SDRAM_CMD_AUTOREFRESH_MODE          ((T_UINT32)0x00000003U)
#define FMC_SDRAM_CMD_LOAD_MODE                 ((T_UINT32)0x00000004U)
#define FMC_SDRAM_CMD_SELFREFRESH_MODE          ((T_UINT32)0x00000005U)
#define FMC_SDRAM_CMD_POWERDOWN_MODE            ((T_UINT32)0x00000006U)
#define FMC_SDRAM_CMD_TARGET_BANK2              FMC_SDCMR_CTB2
#define FMC_SDRAM_CMD_TARGET_BANK1              FMC_SDCMR_CTB1
#define FMC_SDRAM_CMD_TARGET_BANK1_2            ((T_UINT32)0x00000018U)
#define FMC_SDRAM_NORMAL_MODE                   ((T_UINT32)0x00000000U)
#define FMC_SDRAM_SELF_REFRESH_MODE             FMC_SDSR_MODES1_0
#define FMC_SDRAM_POWER_DOWN_MODE               FMC_SDSR_MODES1_1
#define FMC_IT_RISING_EDGE                      ((T_UINT32)0x00000008U)
#define FMC_IT_LEVEL                            ((T_UINT32)0x00000010U)
#define FMC_IT_FALLING_EDGE                     ((T_UINT32)0x00000020U)
#define FMC_IT_REFRESH_ERROR                    ((T_UINT32)0x00004000U)
#define FMC_FLAG_RISING_EDGE                    ((T_UINT32)0x00000001U)
#define FMC_FLAG_LEVEL                          ((T_UINT32)0x00000002U)
#define FMC_FLAG_FALLING_EDGE                   ((T_UINT32)0x00000004U)
#define FMC_FLAG_FEMPT                          ((T_UINT32)0x00000040U)
#define FMC_SDRAM_FLAG_REFRESH_IT               FMC_SDSR_RE
#define FMC_SDRAM_FLAG_BUSY                     FMC_SDSR_BUSY
#define FMC_SDRAM_FLAG_REFRESH_ERROR            FMC_SDRTR_CRE

#define __FMC_NORSRAM_ENABLE(__INSTANCE__, __BANK__)  ((__INSTANCE__)->BTCR[(__BANK__)] \
                                                      |= FMC_BCR1_MBKEN)

#define __FMC_NORSRAM_DISABLE(__INSTANCE__, __BANK__) \
                      ((__INSTANCE__)->BTCR[(__BANK__)] &= ~FMC_BCR1_MBKEN)

#define __FMC_NAND_ENABLE(__INSTANCE__) \
                      ((__INSTANCE__)->PCR |= FMC_PCR_PBKEN)

#define __FMC_NAND_DISABLE(__INSTANCE__) \
                        ((__INSTANCE__)->PCR &= ~FMC_PCR_PBKEN)

#define __FMC_NAND_ENABLE_IT(__INSTANCE__, __INTERRUPT__) \
                        ((__INSTANCE__)->SR |= (__INTERRUPT__))

#define __FMC_NAND_DISABLE_IT(__INSTANCE__, __INTERRUPT__)  \
                        ((__INSTANCE__)->SR &= ~(__INTERRUPT__))

#define __FMC_NAND_GET_FLAG(__INSTANCE__, __BANK__, __FLAG__) \
                        (((__INSTANCE__)->SR &(__FLAG__)) == (__FLAG__))

#define __FMC_NAND_CLEAR_FLAG(__INSTANCE__, __FLAG__) \
                        ((__INSTANCE__)->SR &= ~(__FLAG__))

#define __FMC_SDRAM_ENABLE_IT(__INSTANCE__, __INTERRUPT__)  \
                        ((__INSTANCE__)->SDRTR |= (__INTERRUPT__))

#define __FMC_SDRAM_DISABLE_IT(__INSTANCE__, __INTERRUPT__) \
                        ((__INSTANCE__)->SDRTR &= ~(__INTERRUPT__))

#define __FMC_SDRAM_GET_FLAG(__INSTANCE__, __FLAG__) \
                        (((__INSTANCE__)->SDSR &(__FLAG__)) == (__FLAG__))

#define __FMC_SDRAM_CLEAR_FLAG(__INSTANCE__, __FLAG__)\
                        ((__INSTANCE__)->SDRTR |= (__FLAG__))

extern T_HAL_STATUS  FmcNorSramTimingInit(T_FMC_NORSRAM *Device,
                                       T_FMC_NORSRAM_TIMING *Timing, T_UINT32 Bank);
extern T_HAL_STATUS  FmcNorSramExtendedTimingInit(T_FMC_NORSRAM_EXTENDED *Device,
                              T_FMC_NORSRAM_TIMING *Timing, T_UINT32 Bank, T_UINT32 ExtendedMode);

extern T_HAL_STATUS  FmcSdramInit(T_FMC_SDRAM *Device, T_FMC_SDRAM_INIT *Init);
extern T_HAL_STATUS  FmcSdramTimingInit(T_FMC_SDRAM *Device, T_FMC_SDRAM_TIMING *Timing,
                                      T_UINT32 Bank);

extern T_HAL_STATUS  FmcSdramSendCommand(T_FMC_SDRAM *Device, T_FMC_SDRAM_COMMAND *Command,
                                    T_UINT32 Timeout);
extern T_HAL_STATUS  FmcSdramProgramRefreshRate(T_FMC_SDRAM *Device, T_UINT32 RefreshRate);

extern T_HAL_STATUS  FmcNorSramInit(T_FMC_NORSRAM *device, T_FMC_NORSRAM_INIT * init);

#endif /* _HDULIBSTM32F7XXLLFMC_H_ */
