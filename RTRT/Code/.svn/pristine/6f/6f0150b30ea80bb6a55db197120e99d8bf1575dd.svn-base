/*
 ******************************************************************************
 * License Information  :  Howell Instruments, Inc.                           *
 *                         "Licensed Software" and "All rights reserved".     *
 ******************************************************************************
 *  File                : hdudispfmain.c
 *
 *  Description         : The file Performs essential peripheral and OS initialization.
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
 *      1.1           Shilpa A R        25-Jul-2017             100064
 *      1.2           Divya G P         09-Oct-2017             100064
 *      1.3           Shruthi M N       30-Oct-2017             100104
 *      1.4           Rona B S          01-Jul-2020             100259
 *
 * Additional References : None
 *
 ******************************************************************************
 */

#include "hdudispfbspnor.h"   /* contains the common defines and functions prototypes bspnor*/
#include "hdudispfinit.h"      /* Contains functions prototypes of initialization function.*/
#include "hdudispfmain.h"                       /* Contains prototype for Main module */
#include "hdulibstm32756gevalsdram.h"    /* Header includes of file of SDRAM HAL module*/
#include "hdulibstm32f7xxhalcortex.h"    /* Header file of CORTEX HAL module */
#include "hdulibstm32f7xxhalflashex.h"  /* Header file of Flash HAL Extension module. */
#include "hdulibstm32f7xxhalpwrex.h"       /* Header file of PWR HAL Extension module. */
#include "hdulibstm32f7xxhalrcc.h"          /* Header files for RCC HAL module*/
#include "hdulibstm32f7xxhalrccex.h"    /* Header files for RCC EX HAL module*/
#include "hdulibstm32f7xxhaldef.h"          /*Contains the HAL defination module */
#include "hdudispfpanel.h"               /* Contains functions prototypes of panel.*/
#include "hdudispfucos.h"                /* Need OS_ENTER_CRITICAL and OS_EXIT_CRITICAL. */
#include "hdulibcorecm7.h"            /* Cortex-M7 processor and core peripherals */
#include "hdulibstm32f7xxhal.h"           /* Header file of LTDC HAL module.*/
#include "hdudispftbase.h"    /* provides tbase functionalities */
#include "hdudispfpbit.h"        /* contains prototypes for PBIT test. */

#define ZERO            0U
#define RCC_PLLM_CONFIG 24U
#define RCC_PLLN_CONFIG 432U
#define RCC_PLLQ_CONFIG 9U
#define MPU_BASEADDR    0x20010000U
#define PLLSAIN_CONFIG  192U
#define PLLSAIR_CONFIG  4U
#define TRUE            1U

static void SystemClockConfig(void);
static void CpuCacheEnable(void);
static void MpuCacheEnable(void);
/*
 * Function                :  SystemClockConfig
 *
 * Description             :  This function configures the system clock
 *
 * Formal parameter(s)     :  None
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */

static void SystemClockConfig(void)
{
   T_RCC_CLK_INIT rcc_clk_init_struct = {0};
   T_RCC_OSC_INIT rcc_osc_init_struct = {0};
   T_HAL_STATUS ret_value = HAL_OK;

   /* hdudispfmain-SystemClockConfig-DB-LLR-001 */
   /* Enable HSE Oscillator and activate PLL with HSE as source */
   rcc_osc_init_struct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
   rcc_osc_init_struct.HSEState = RCC_HSE_ON;
   rcc_osc_init_struct.PLL.PLLState = RCC_PLL_ON;
   rcc_osc_init_struct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
   rcc_osc_init_struct.PLL.PLLM = RCC_PLLM_CONFIG;
   rcc_osc_init_struct.PLL.PLLN = RCC_PLLN_CONFIG;
   rcc_osc_init_struct.PLL.PLLP = RCC_PLLP_DIV2;
   rcc_osc_init_struct.PLL.PLLQ = RCC_PLLQ_CONFIG;

   /* hdudispfmain-SystemClockConfig-DB-LLR-002 */
   ret_value = HalRccOscConfig(&rcc_osc_init_struct);
   if(HAL_OK != ret_value)
   {
      while(TRUE)
      {
         ;
      }
   }
   else
   {
      ;/* Do nothing */
   }

   /* hdudispfmain-SystemClockConfig-DB-LLR-003 */
   /* Activate the OverDrive to reach the 216 MHz Frequency */
   ret_value = HalPwrExEnableOverDrive();
   if(HAL_OK != ret_value)
   {
      while(TRUE)
      {
         ;
      }
   }
   else
   {
      ;/* Do nothing */
   }

   /* hdudispfmain-SystemClockConfig-DB-LLR-004 */
   /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2 clocks dividers */
   rcc_clk_init_struct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK |
                                              RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
   rcc_clk_init_struct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
   rcc_clk_init_struct.AHBCLKDivider = RCC_SYSCLK_DIV1;
   rcc_clk_init_struct.APB1CLKDivider = RCC_HCLK_DIV4;
   rcc_clk_init_struct.APB2CLKDivider = RCC_HCLK_DIV2;

   /* hdudispfmain-SystemClockConfig-DB-LLR-005*/
   ret_value = HalRccClockConfig(&rcc_clk_init_struct, FLASH_LATENCY_7);
   if(HAL_OK != ret_value)
   {
      while(TRUE)
      {
         ;
      }
   }
   else
   {
      ;/* Do nothing */
   }
}

/*
 * Function                :  CpuCacheEnable
 *
 * Description             :  This function enables the instruction and data caches.
 *
 * Formal parameter(s)     :  None
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */

static void CpuCacheEnable(void)
{
   /* hdudispfmain-CpuCacheEnable-DB-LLR-001*/
   /* Enable I-Cache */
   ScbEnableICache();

   /* Enable D-Cache */
   ScbEnableDCache();
}

/*
 * Function                :  MpuCacheEnable
 *
 * Description             :  This function configures the MPU attributes
 *
 * Formal parameter(s)     :  None
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */

static void MpuCacheEnable(void)
{
   T_MPU_REGION_INIT mpu_init_struct = {0};

   /* hdudispfmain-MpuCacheEnable-DB-LLR-001 */
   /* Disable the MPU */
   HalMpuDisable();

   /* Configure the MPU attributes as WT for SRAM */
   mpu_init_struct.Enable = MPU_REGION_ENABLE;
   mpu_init_struct.BaseAddress = MPU_BASEADDR;
   mpu_init_struct.Size = MPU_REGION_SIZE_256KB;
   mpu_init_struct.AccessPermission = MPU_REGION_FULL_ACCESS;
   mpu_init_struct.IsBufferable = MPU_ACCESS_NOT_BUFFERABLE;
   mpu_init_struct.IsCacheable = MPU_ACCESS_CACHEABLE;
   mpu_init_struct.IsShareable = MPU_ACCESS_NOT_SHAREABLE;
   mpu_init_struct.Number = MPU_REGION_NUMBER0;
   mpu_init_struct.TypeExtField = MPU_TEX_LEVEL0;
   mpu_init_struct.SubRegionDisable = ZERO;
   mpu_init_struct.DisableExec = MPU_INSTRUCTION_ACCESS_ENABLE;

   HalMpuConfigRegion(&mpu_init_struct);

   /* Enable the MPU */
   HalMpuEnable(MPU_PRIVILEGED_DEFAULT);
}

/*
 * Function                :  DisplayMain
 *
 * Description             :  This function Performs essential peripheral and OS initialization
 *                            and launches the init task.
 *
 * Formal parameter(s)     :  None
 *
 * Return Value            :  T_INT32 - returns zero
 *
 * Assumption              :  None
 *
 */

T_INT32 DisplayMain(void)
{
   T_RCC_PERIPH_CLK  periph_clk_init_struct = {ZERO};
   T_UINT32    cntr = ZERO;
   T_UINT32 *dest = ZERO;

   /* hdudispfmain-DisplayMain-DB-LLR-001 */
   MpuCacheEnable();

   /* Enable the CPU Cache */
   CpuCacheEnable();

   HalInit();

   /*  Initialize the SDRAM.*/
   BspSdramInit();
   BspNorInit();

   /* Configure the system clock to 216 MHz */
   SystemClockConfig();

   /* hdudispfmain-DisplayMain-DB-LLR-002 */
   /* LTDC Clock Configuration */
   periph_clk_init_struct.PeriphClockSelection = RCC_PERIPHCLK_LTDC;
   periph_clk_init_struct.PLLSAI.PLLSAIN = PLLSAIN_CONFIG;
   periph_clk_init_struct.PLLSAI.PLLSAIR = PLLSAIR_CONFIG;
   periph_clk_init_struct.PLLSAIDivR = RCC_PLLSAIDIVR_2;
   HalRccExPeriphCLKConfig(&periph_clk_init_struct);

   /* hdudispfmain-DisplayMain-DB-LLR-003 */
   /*  Clear video RAM (4 frame buffers). */
   for(cntr=0, dest = (T_UINT32 *)VIDEO_RAM; cntr < (T_UINT32)(FG_FB_SIZE1); cntr++, dest++)
   {
      *dest = ZERO;
   }

   /* hdudispfmain-DisplayMain-DB-LLR-004 */
   /* Initialize the LCD and put up Howell's Splash screen.  */
   LCDConfig();

   PbitCheck();
   /* Initialize uCos  */
   OsInit();

   /* Set up the initialization task.   */
   InitInit();

   /* Start the scheduler.        */
   OsStart();

   return ZERO;
}

/*
 * Function                :  SysTickHandler
 *
 * Description             :  This function handles SysTick Handler.
 *
 * Formal parameter(s)     :  None
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */

void SysTickHandler(void)
{
   /* hdudispfmain-SysTickHandler-DB-LLR-001 */
   HalIncTick();
   HalSystickCallback();
}
