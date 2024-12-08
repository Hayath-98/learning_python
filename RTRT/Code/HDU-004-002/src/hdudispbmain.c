/*
 ******************************************************************************
 * License Information  :  Howell Instruments, Inc.                           *
 *                         "Licensed Software" and "All rights reserved".     *
 ******************************************************************************
 *  File                : hdudispbmain.c
 *
 *  Description         : The module does the following operation,
 *                        a) Checks whether SD card is present or not
 *                        b) performs CRC check
 *                        c) cofigure the system clock, MPU
 *                        d) enbable the CPU cache
 *                        e) transfers control to another function
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
 * <Version No.>     <Author>          <Date>         <Problem Report No.>
 *
 *      1.1          Ajay J G        02-Aug-2017             -
 *      1.2          Divya G P       02-Sep-2017            100028
 *      1.3          Shruthi M N     28-Sep-2017            100064
 *      1.4          Chaithra J      21-Jun-2020            100259
 *      1.5          Rona B.S        29-Jun-2020            100259
 *      1.6          Dhanalakshmi    20-Mar-2021            100331
 *      1.7          Dhanalakshmi    20-Mar-2021            100331
 *
 * Additional References : None
 *
 ******************************************************************************
 */

#include "hdulibstm32f7xxhalrccex.h"       /* Header files for RCC EX HAL module*/
#include "hdulibstm32f7xxhalrcc.h"         /* Header files for RCC HAL module*/
#include "hdudispbcrc.h"                   /* Contains functions prototypes of hdudispbcrc.*/
#include "hdudispbmain.h"                  /* Contains functions prototypes of hdudispbmain*/
#include "hdudispbpanel.h"                 /* Contains functions prototypes of hdudispbpanel.*/
#include "hdudispbpwm.h"                   /* Contains functions prototypes of hdudispbpwm.*/
#include "hdudispbrterr.h"                 /* Contains functions prototypes of hdudispbrterr.*/
#include "hdudispbtext.h"                  /* Contains functions prototypes of hdudispbtext.*/
#include "hdulibbasictypes.h"              /* Basic data types.*/
#include "hdudispbboot.h"                  /* Contains functions prototypes of hdudispbboot.*/
#include "hdulibstm32f7xxhalgpio.h"        /* Header files for RCC GPIO module.*/
#include "hdulibstm32f7xxhalflashex.h"     /* Header file of FLASH HAL Extension module. */
#include "hdulibstm32f7xxhalcortex.h"      /* Header file of CORTEX HAL module */
#include "hdulibstm32f7xxhalpwrex.h"       /* Header file of PWR HAL Extension module. */
#include "hdudispbrevno.h"                 /* Revision number ID */
#include "hdulibstm32hallegacy.h"         /* Aliases definition for the STM32Cube HAL constants*/
#include "hdulibcmsisgcc.h"               /*CMSIS Cortex-M Core Function*/
#include "hdudispbappdata.h"			  /* Contains appdata structure for configuration file*/

/* Private function prototypes */
static void SystemClockConfig(void);
static void CpuCacheEnable(void);
static void MpuConfig(void);
static T_INT8 ConfigChecks(void);

#define SD_PRESENT               ((T_UINT8)0x01)
#define SD_NOT_PRESENT           ((T_UINT8)0x00)
#define CONFIG_PASS               ((T_UINT8)0x01)
#define CONFIG_ERROR              ((T_UINT8)0x00)
#define SD_DETECT_PIN            GPIO_PIN_13
#define SD_DETECT_GPIO_PORT      GPIOC
#define RIGHT_ENC_NOT_PRESSED    ((T_UINT8)0x00)
#define RIGHT_ENC_PRESSED        ((T_UINT8)0x01)
#define BUTTON8_NOT_PRESSED     ((T_UINT8)0x00)
#define BUTTON8_PRESSED         ((T_UINT8)0x01)
#define GPIOC_CLK_ENABLE()       __HAL_RCC_GPIOC_CLK_ENABLE()
#define GPIOB_CLK_ENABLE()       __HAL_RCC_GPIOB_CLK_ENABLE()
#define TWENTY_FIVE              ((T_UINT8)0x19)
#define FOURHUNDRED_THIRTY_TWO   ((T_UINT16)0x1B0)
#define ONEHUNDRED_SIXTY         ((T_UINT8)0xA0)
#define TOTAL_DISPLAY_CONFIG 6

T_APPDATA_APPDATA_BOOT *Appdata_appdata_boot = (T_APPDATA_APPDATA_BOOT*) 0x8010000;
/* LOAD_SW_FLAG is used to check loader binary flag */

/*
 * Function                :  SDCardInserted
 *
 * Description             :  This function is used for Detecting if an SD card is Present.
 *
 * Formal parameter(s)     :  None
 *
 * Return Value            :  T_INT8 - Status of SD card availability
 *                                     SD_PRESENT - SD card is present
 *                                     SD_NOT_PRESENT - SD card is not inserted
 *
 * Assumption              :  None
 *
 */
static T_INT8 SDCardInserted(void)
{
   /* GPIO Init Structure Declaration */
   T_GPIO_INIT  gpio_init_structure = {ZERO};
   T_INT8 status = SD_PRESENT;

   /*hdudispbmain-SDCardInserted-DB-LLR-001*/
   GPIOC_CLK_ENABLE();

   /*hdudispbmain-SDCardInserted-DB-LLR-002*/
   /* GPIO Configuration in Input for SD Card Detect signal */
   gpio_init_structure.Pin    = SD_DETECT_PIN;
   gpio_init_structure.Mode   = GPIO_MODE_INPUT;
   gpio_init_structure.Pull   = GPIO_PULLUP;
   gpio_init_structure.Speed  = GPIO_SPEED_HIGH;
   HalGpioInit(SD_DETECT_GPIO_PORT, &gpio_init_structure);

   /*hdudispbmain-SDCardInserted-DB-LLR-003*/
   /* Check SD Card Detect Pin */
   if (GPIO_PIN_SET == HalGpioReadPin(SD_DETECT_GPIO_PORT, SD_DETECT_PIN))
   {
      status = SD_NOT_PRESENT;
   }
   else
   {
      ; /* Do nothing */
   }
   /*hdudispbmain-SDCardInserted-DB-LLR-004*/
   return status;
}
/*
 * Function                :  RightEncoderInput
 *
 * Description             :  This function is used for detecting Right Encoder (E2) Input.
 *
 * Formal parameter(s)     :  None
 *
 * Return Value            :  T_INT8 - Status of Right Encoder Input availability
 *                                     RIGHT_ENC_PRESSED - Right Encoder is selected
 *                                     SD_NOT_PRESENT - Right Encoder is not selected
 *
 * Assumption              :  None
 *
 */
static T_INT8  RightEncoderInput(void)
{
   /* GPIO Init Structure Declaration */
   T_GPIO_INIT  gpio_init_structure = {ZERO};
   T_INT8 status = RIGHT_ENC_PRESSED;

   /*hdudispbmain-RightEncoderInput-DB-LLR-001*/
   GPIOC_CLK_ENABLE();

   /*hdudispbmain-RightEncoderInput-DB-LLR-002*/
   /* GPIO Configuration in Input for Right Encoder Input Signal */
   gpio_init_structure.Pin       = GPIO_PIN_4;
   gpio_init_structure.Mode      = GPIO_MODE_INPUT;
   gpio_init_structure.Pull      = GPIO_PULLUP;
   gpio_init_structure.Speed     = GPIO_SPEED_HIGH;
   HalGpioInit(GPIOC, &gpio_init_structure);

   /*hdudispbmain-RightEncoderInput-DB-LLR-003*/
   /* Check Right Encoder (E2) Input Pin */
   if (GPIO_PIN_SET == HalGpioReadPin(GPIOC, GPIO_PIN_4))
   {
      status = RIGHT_ENC_NOT_PRESSED;
   }
   else
   {
      ;  /* Do nothing */
   }

   /*hdudispbmain-RightEncoderInput-DB-LLR-004*/
   return status;
}

/*
 * Function                :  Button8Input
 *
 * Description             :  This function is used for detecting Bezel button 8 (B8) Input.
 *
 * Formal parameter(s)     :  None
 *
 * Return Value            :  T_INT8 - Status of Button8 Input availability
 *                                     BUTTON8_PRESSED - Button8 is selected
 *                                     BUTTON8_NOT_PRESSED - Button8 is not selected
 *
 * Assumption              :  None
 *
 */
static T_INT8 Button8Input(void)
{
   /* GPIO Init Structure Declaration */
   T_GPIO_INIT  gpio_init_structure = {ZERO};
   T_INT8 status = BUTTON8_PRESSED;

   /*hdudispbmain-Button8Input-DB-LLR-001*/
   GPIOB_CLK_ENABLE();

   /*hdudispbmain-Button8Input-DB-LLR-002*/
   /* GPIO Configuration in Input for Button 8 Input Signal */
   gpio_init_structure.Pin       = GPIO_PIN_13;
   gpio_init_structure.Mode      = GPIO_MODE_INPUT;
   gpio_init_structure.Pull      = GPIO_PULLUP;
   gpio_init_structure.Speed     = GPIO_SPEED_HIGH;
   HalGpioInit(GPIOB, &gpio_init_structure);

   /*hdudispbmain-Button8Input-DB-LLR-003*/
   /* Check Button 8 Input Pin */
   if (GPIO_PIN_SET == HalGpioReadPin(GPIOB, GPIO_PIN_13))
   {
	   status = BUTTON8_NOT_PRESSED;
   }
   else
   {
      ;  /* Do nothing */
   }

   /*hdudispbmain-Button8Input-DB-LLR-004*/
   return status;
}
/*
 * Function                :  TransferControl
 *
 * Description             :  This function transfers control to another program.
 *
 * Formal parameter(s)     :  T_SBOOTFILE *ps_boot_file - In Pointer to the file
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */

void TransferControl(T_SBOOTFILE *ps_boot_file)
{
   /* Typedef */
   typedef void (*T_P_FUNCTION)(void);
   /* Function Pointer */
   T_P_FUNCTION jump_to_application = NULL;
   /* Jump Address */
   T_UINT32 jump_to_address = ZERO;

   /*hdudispbmain-TransferControl-DB-LLR-001*/
   /* Jump to Secondary application */
   jump_to_address = ps_boot_file->u32LoadAddr + FOUR;
   jump_to_address = *((T_UINT32*)jump_to_address);
   jump_to_application = (T_P_FUNCTION)jump_to_address;

   /*hdudispbmain-TransferControl-DB-LLR-002*/
   /* Initialize Secondary application's Stack Pointer */
   __set_MSP(*(T_UINT32*) ps_boot_file->u32LoadAddr);

   jump_to_application();
}

/*
 * Function                :  MainFunc
 *
 * Description             :  This function checks crc sections and jumps to different application.
 *
 * Formal parameter(s)     :  None
 *
 * Return Value            :  T_INT32 - Returns 0 when succesfully executed the function
 *
 * Assumption              :  None
 *
 */

T_INT32 MainFunc(void)
{
   T_UINT8 u8_error_stat = ZERO;
   T_UINT32 u32_cntr = ZERO;
   T_UINT32 *pu32_dest = ZERO;
   T_UINT8 u8_index = ZERO;

   static T_UINT8 param_message1[] = "BootLoader CRC Error.";
   static T_UINT8 param_message2[] = "Maintenance CRC Error.";
   static T_UINT8 param_message3[] = "Application CRC Error.";
   static T_UINT8 param_message4[] = "Software Loader CRC Error.";
   static T_UINT8 param_message5[] = "Configuration Check Error.";
   T_UINT8 file_name[] = __FILE__;

   T_RCC_PERIPH_CLK periph_clk_init_struct = {ZERO};

   /*hdudispbmain-MainFunc-DB-LLR-021*/
   for (u8_index = ZERO; u8_index < SIXTEEN; u8_index++)
   {
      if(((Revno_id[u8_index] >= CHAR0) && (Revno_id[u8_index] <= CHAR9))||
      ((Revno_id[u8_index] >= CHARUA) && (Revno_id[u8_index] <= CHARUZ)) ||
      ((Revno_id[u8_index] >= CHARLA) && (Revno_id[u8_index] <= CHARLZ)) ||
      (HYPHEN == Revno_id[u8_index]) || (POINT == Revno_id[u8_index]) ||
      (SPACE == Revno_id[u8_index]))
      {
         /* Do nothing */
      }
      else
      {
         ;
      }
   }
if( CONFIG_PASS  == ConfigChecks())
{
   if(ZERO != (CRCRom(&Boot_file_boot_code)))
   {
      /* If the SD Card is *NOT* plugged in. */


      if ((SD_PRESENT == SDCardInserted()) && (((ORIENTATION == PORTRAIT) && 
		(RIGHT_ENC_PRESSED == RightEncoderInput())) ||
    	 ((ORIENTATION == LAND_SCAPE) && (RIGHT_ENC_PRESSED == Button8Input()))) && (SW_FLAG))
	      {

			       /*hdudispbmain-MainFunc-DB-LLR-001*/
	              if(ZERO !=(CRCRom(&Boot_file_maint_code)))
	              {
	                 /* Transfer control to the maintenance. */
	                 TransferControl(&Boot_file_maint_code);
	              }
	              else
	              {
	                 /*hdudispbmain-MainFunc-DB-LLR-002*/
	                 u8_error_stat = TWO;
	              }
	    	  }
      else if ((SD_PRESENT == SDCardInserted())&&
         (((ORIENTATION == PORTRAIT) && (RIGHT_ENC_PRESSED == RightEncoderInput())) ||
    	 ((ORIENTATION == LAND_SCAPE) && (RIGHT_ENC_PRESSED == Button8Input()))) && (!SW_FLAG))
	    	  {
         if(ZERO !=(CRCRom(&Boot_file_swl_code)))
	              {
				       /*hdudispbmain-MainFunc-DB-LLR-024 */
	                 /* Transfer control to the loader software. */
            TransferControl(&Boot_file_swl_code);
	              }
	              else
	              {
	                 /*hdudispbmain-MainFunc-DB-LLR-025 */
            u8_error_stat = THREE;
	              }
	    	  }

      else
      {
         /*hdudispbmain-MainFunc-DB-LLR-003*/
         /* If a valid application is loaded. */
         if(ZERO !=(CRCRom(&Boot_file_app_code)))
         {
            /* Transfer control to the application. */
            TransferControl(&Boot_file_app_code);
         }
         else
         {
            /*hdudispbmain-MainFunc-DB-LLR-004*/
            u8_error_stat =ONE;
         }
      }
   }
   else
   {
      /*hdudispbmain-MainFunc-DB-LLR-005*/
      u8_error_stat = FOUR;
   }
}
else
{     
    /*hdudispbmain-MainFunc-DB-LLR-027 */
	u8_error_stat = FIVE;
}
   /*hdudispbmain-MainFunc-DB-LLR-006*/
   /* Configure the MPU attributes as Write Through */
   MpuConfig();

   /*hdudispbmain-MainFunc-DB-LLR-007*/
   /* Enable the CPU Cache */
   CpuCacheEnable();

   /*hdudispbmain-MainFunc-DB-LLR-008*/
   HalInit();

   /*hdudispbmain-MainFunc-DB-LLR-009*/
   /*  Initialize the off chip RAM. */
   BspSdramInit();

   /*hdudispbmain-MainFunc-DB-LLR-010*/
   /*  Clear video RAM */
   for(u32_cntr=ZERO, pu32_dest = (T_UINT32 *)FB_ADDR; u32_cntr < (((T_UINT32)FG_FB_SIZE)/FOUR);
   u32_cntr++, pu32_dest++)
   {
   *pu32_dest = ZERO;
   }

   /*hdudispbmain-MainFunc-DB-LLR-011*/
   /* Configure the system clock to 216 MHz */
   SystemClockConfig();

   /*hdudispbmain-MainFunc-DB-LLR-012*/
   periph_clk_init_struct.PeriphClockSelection = RCC_PERIPHCLK_LTDC;
   periph_clk_init_struct.PLLSAI.PLLSAIN = ONEHUNDRED_SIXTY;
   periph_clk_init_struct.PLLSAI.PLLSAIR = FOUR;
   periph_clk_init_struct.PLLSAIDivR = RCC_PLLSAIDIVR_2;
   HalRccExPeriphCLKConfig(&periph_clk_init_struct);

   /*hdudispbmain-MainFunc-DB-LLR-013*/
   periph_clk_init_struct.PeriphClockSelection = RCC_PERIPHCLK_LTDC;
   periph_clk_init_struct.PLLSAI.PLLSAIN = ONEHUNDRED_TWENTY_EIGHT;
   periph_clk_init_struct.PLLSAI.PLLSAIR = TWO;
   periph_clk_init_struct.PLLSAIDivR = RCC_PLLSAIDIVR_2;
   HalRccExPeriphCLKConfig(&periph_clk_init_struct);

   /*hdudispbmain-MainFunc-DB-LLR-014*/
   /* Initialize the LCD.*/
   LcdConfig();

   /*hdudispbmain-MainFunc-DB-LLR-015*/
   /* Turn on the back light.*/
   PwmInit();

   /*hdudispbmain-MainFunc-DB-LLR-016*/
   /*Initialize the text routines.*/
   TextInit();

   if (ONE == u8_error_stat)
   {
       /* hdudispbmain-MainFunc-DB-LLR-028 */
	   /* error display for BootLoader CRC Error */
      RterrFunc((T_UINT8 *)file_name, __LINE__, (T_UINT8 *)param_message3);
   }
   else if (TWO == u8_error_stat)
   {
      /*hdudispbmain-MainFunc-DB-LLR-017*/
      RterrFunc((T_UINT8 *)file_name, __LINE__ , (T_UINT8 *) param_message2);
   }
   else if (THREE == u8_error_stat)
   {
      /*hdudispbmain-MainFunc-DB-LLR-018*/
      /* Software Loader CRC Error. */
      RterrFunc((T_UINT8 *)file_name, __LINE__, (T_UINT8 *)param_message4);
   }
   else if (FOUR == u8_error_stat)
   {
            /*hdudispbmain-MainFunc-DB-LLR-026*/
	      /* BootLoader CRC Error. */
      RterrFunc((T_UINT8 *)file_name, __LINE__, (T_UINT8 *)param_message1);
   }
   else
   {
      /*hdudispbmain-MainFunc-DB-LLR-019*/
	  /* Configuration Check Error */
	  RterrFunc((T_UINT8 *)file_name, __LINE__, (T_UINT8 *)param_message5);
   }
   /*hdudispbmain-MainFunc-DB-LLR-020*/
   return ZERO;
}

/*
 * Function                :  SystemClockConfig
 *
 * Description             :  This function is used to Configure System Clock,
 *                            The system Clock is configured as follow :
 *                            System Clock source            = PLL (HSE)
 *                            SYSCLK(Hz)                     = 216000000
 *                            HCLK(Hz)                       = 216000000
 *                            AHB Prescaler                  = 1
 *                            APB1 Prescaler                 = 4
 *                            APB2 Prescaler                 = 2
 *                            HSE Frequency(Hz)              = 25000000
 *                            PLL_M                          = 25
 *                            PLL_N                          = 432
 *                            PLL_P                          = 2
 *                            PLL_Q                          = 9
 *                            VDD(V)                         = 3.3
 *                            Main regulator output voltage  = Scale1 mode
 *                            Flash Latency(WS)              = 7
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
   T_RCC_CLK_INIT rcc_clkinitstruct = {ZERO};
   T_RCC_OSC_INIT rcc_oscinitstruct = {ZERO};

   /*hdudispbmain-SystemClockConfig-DB-LLR-001*/
   /* Enable HSE Oscillator and activate PLL with HSE as source */
   rcc_oscinitstruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
   rcc_oscinitstruct.HSEState = RCC_HSE_ON;
   rcc_oscinitstruct.PLL.PLLState = RCC_PLL_ON;
   rcc_oscinitstruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
   rcc_oscinitstruct.PLL.PLLM = TWENTY_FIVE;
   rcc_oscinitstruct.PLL.PLLN = FOURHUNDRED_THIRTY_TWO;
   rcc_oscinitstruct.PLL.PLLP = RCC_PLLP_DIV2;
   rcc_oscinitstruct.PLL.PLLQ = NINE;

   /*hdudispbmain-SystemClockConfig-DB-LLR-002*/
   /* Configures the internal and/or external oscillators, PLL source and factors. */
   if(HalRccOscConfig(&rcc_oscinitstruct) != HAL_OK)
   {
      while(ONE)
      {
         ;
      }
   }
   else
   {
      ; /* Do nothing */
   }

   /*hdudispbmain-SystemClockConfig-DB-LLR-003*/
   /* Activate the OverDrive to reach the 216 MHz Frequency */
   if(HalPwrExEnableOverDrive() != HAL_OK)
   {
      while(ONE)
      {
         ; /* Do nothing */
      }
   }
   else
   {
      ; /* Do nothing */
   }

   /*hdudispbmain-SystemClockConfig-DB-LLR-004*/
   /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2 clocks dividers */
   rcc_clkinitstruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK |
                                 RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
   rcc_clkinitstruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
   rcc_clkinitstruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
   rcc_clkinitstruct.APB1CLKDivider = RCC_HCLK_DIV4;
   rcc_clkinitstruct.APB2CLKDivider = RCC_HCLK_DIV2;

   /*hdudispbmain-SystemClockConfig-DB-LLR-005*/
   /* Configures the System Clock Source, Flash Latency and AHB and APB Prescalers */
   if(HalRccClockConfig(&rcc_clkinitstruct, FLASH_LATENCY_7) != HAL_OK)
   {
      while(ONE)
      {
         ;
      }
   }
   else
   {
      ; /* Do nothing */
   }
}

/*
 * Function                :  ConfigChecks
 *
 * Description             :  This function is used to Check the BootConfig Structure Validity.
 *
 * Formal parameter(s)     :  None
 *
 * Return Value            :  T_INT8
 *
 * Assumption              :  None
 *
 */
static T_INT8 ConfigChecks(void)
{
	T_INT8 panel_result = CONFIG_PASS;
	T_INT8 flag_result = CONFIG_ERROR;
	T_INT8 result = CONFIG_ERROR;
	T_APPDATA_PANEL **display_configs = Du_config_files;
	while(ZERO != *display_configs)
	{
       	/* hdudispbmain-ConfigChecks-DB-LLR-001 */
		panel_result = CONFIG_PASS;
		if(Appdata_appdata_boot->PanelStruct.PanelWidth!=(*display_configs)->PanelWidth)
		{
		    /* hdudispbmain-ConfigChecks-DB-LLR-002 */
			panel_result=CONFIG_ERROR;
		}
		else
		{
			;
		}
		if(Appdata_appdata_boot->PanelStruct.PanelHeight!=(*display_configs)->PanelHeight)
		{ 
		     /* hdudispbmain-ConfigChecks-DB-LLR-003 */
			panel_result=CONFIG_ERROR;
		}
		else
		{
			;
		}
		if(Appdata_appdata_boot->PanelStruct.PanelHSync!=(*display_configs)->PanelHSync)
		{
		    /* hdudispbmain-ConfigChecks-DB-LLR-004 */
			panel_result=CONFIG_ERROR;
		}
		else
		{
			;
		}
		if(Appdata_appdata_boot->PanelStruct.PanelHBP!=(*display_configs)->PanelHBP)
		{
		   /* hdudispbmain-ConfigChecks-DB-LLR-005 */
			panel_result=CONFIG_ERROR;
		}
		else
		{
			;
		}
		if(Appdata_appdata_boot->PanelStruct.PanelHFP!=(*display_configs)->PanelHFP)
		{
		    /* hdudispbmain-ConfigChecks-DB-LLR-006 */
			panel_result=CONFIG_ERROR;
		}
		else
		{
			;
		}
		if(Appdata_appdata_boot->PanelStruct.PanelVSync!=(*display_configs)->PanelVSync)
		{
		    /* hdudispbmain-ConfigChecks-DB-LLR-007 */
			panel_result=CONFIG_ERROR;
		}
		else
		{
			;
		}
		if(Appdata_appdata_boot->PanelStruct.PanelVbp!=(*display_configs)->PanelVbp)
		{
		   /* hdudispbmain-ConfigChecks-DB-LLR-008 */
			panel_result=CONFIG_ERROR;
		}
		else
		{
			;
		}
		if(Appdata_appdata_boot->PanelStruct.PanelVfp!=(*display_configs)->PanelVfp)
		{
		    /* hdudispbmain-ConfigChecks-DB-LLR-009 */
			panel_result=CONFIG_ERROR;
		}
		else
		{
			;
		}
		if(CONFIG_PASS == panel_result)
		{
		    /* hdudispbmain-ConfigChecks-DB-LLR-010 */
			break;
		}
		else
		{
			;
		}
		display_configs++;
	}
	if((ZERO == Appdata_appdata_boot->Flag.SoftwareJumpFlag)|| \
			(ONE == Appdata_appdata_boot->Flag.SoftwareJumpFlag))
	{
	     /* hdudispbmain-ConfigChecks-DB-LLR-011 */
		flag_result = CONFIG_PASS;
	}
	else
	{
		;
	}
	/* hdudispbmain-ConfigChecks-DB-LLR-012 */
	result = panel_result & flag_result;
	return result;
}
/*
 * Function                :  MpuConfig
 *
 * Description             :  This function is used to configure MFU attributes.
 *
 * Formal parameter(s)     :  None
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */
static void MpuConfig(void)
{
   T_MPU_REGION_INIT mpu_initstruct = {ZERO};

   /*hdudispbmain-MpuConfig-DB-LLR-001*/
   /* Disable the MPU */
   HalMpuDisable();

   /*hdudispbmain-MpuConfig-DB-LLR-002*/
   /* Configure the MPU attributes as WT for SRAM */
   mpu_initstruct.Enable = MPU_REGION_ENABLE;
   mpu_initstruct.BaseAddress = MPU_BASE_ADDR1;
   mpu_initstruct.Size = MPU_REGION_SIZE_256KB;
   mpu_initstruct.AccessPermission = MPU_REGION_FULL_ACCESS;
   mpu_initstruct.IsBufferable = MPU_ACCESS_NOT_BUFFERABLE;
   mpu_initstruct.IsCacheable = MPU_ACCESS_CACHEABLE;
   mpu_initstruct.IsShareable = MPU_ACCESS_NOT_SHAREABLE;
   mpu_initstruct.Number = MPU_REGION_NUMBER0;
   mpu_initstruct.TypeExtField = MPU_TEX_LEVEL0;
   mpu_initstruct.SubRegionDisable = ZERO;
   mpu_initstruct.DisableExec = MPU_INSTRUCTION_ACCESS_ENABLE;
   HalMpuConfigRegion(&mpu_initstruct);

   /*hdudispbmain-MpuConfig-DB-LLR-003*/
   /* Configure the MPU attributes as WT for SDRam */
   mpu_initstruct.BaseAddress = MPU_BASE_ADDR2;
   mpu_initstruct.Size = MPU_REGION_SIZE_64MB;
   mpu_initstruct.Number = MPU_REGION_NUMBER1;
   HalMpuConfigRegion(&mpu_initstruct);

   /*hdudispbmain-MpuConfig-DB-LLR-004*/
   /* Configure the MPU attributes as WT for NOR */
   mpu_initstruct.BaseAddress = MPU_BASE_ADDR3;
   mpu_initstruct.IsCacheable = MPU_ACCESS_NOT_CACHEABLE;
   mpu_initstruct.Size = MPU_REGION_SIZE_64MB;
   mpu_initstruct.Number = MPU_REGION_NUMBER2;
   HalMpuConfigRegion(&mpu_initstruct);

   /*hdudispbmain-MpuConfig-DB-LLR-005*/
   /* Enable the MPU */
   HalMpuEnable(MPU_PRIVILEGED_DEFAULT);
}

/*
 * Function                :  CpuCacheEnable
 *
 * Description             :  This function is used to enable CPU L1-Cache.
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
   /*hdudispbmain-CpuCacheEnable-DB-LLR-001*/
   /* Enable I-Cache */
    ScbEnableICache();

   /*hdudispbmain-CpuCacheEnable-DB-LLR-002*/
   /* Enable D-Cache */
   ScbEnableDCache();
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
/*hdudispbmain-SysTickHandler-DB-LLR-001*/
   HalIncTick();
}
