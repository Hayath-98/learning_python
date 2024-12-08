/*
 ******************************************************************************
 * License Information  :  Howell Instruments, Inc.                           *
 *                         "Licensed Software" and "All rights reserved".     *
 ******************************************************************************
 *  File                : hdulibsystemstm32f7xx.c
 *
 *  Description         : CMSIS Cortex-M7 Device Peripheral Access Layer System Source File.
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
 *
 * <Version No.>        <Author>          <Date>              <Problem Report No.>
 *
 *      1.1             Ajay J G        03-Aug-2017               -
 *      1.2             Shilpa A R      02-Sep-2017            100028
 *      1.3             Shruthi M N     28-Sep-2017            100064
 *      1.4             Divya G P       09-Oct-2017            100064
 *      1.5             Dhanalakshmi    05-Jul-2020            100259
 *
 * Additional References : None
 *
 *******************************************************************************
 */
#include "hdulibcorecm7.h"          /* CMSIS STM32F7xx Core Peripheral Access Layer File*/
#include "hdulibstm32f7xx.h"           /* CMSIS STM32F7xx Device Peripheral Access Layer File*/
#include "hdulibbasictypes.h"          /* Contains basic data types.*/
#include "hdulibstm32f746xx.h"         /* CMSIS Cortex-M7 Device Peripheral Access Layer */
#include "hdulibsystemstm32f7xx.h" /* Cortex-M7 Device System Source File for STM32F7xx devices.*/
#include "hdulibstm32f7xxhalconf.h" /*HAL configurations*/

#define VECT_TAB_OFFSET_BOOT  0x0000
#define VECT_TAB_OFFSET_FLIGHT  0xC0000
T_UINT8 Vector_tab_sel = ZERO;
T_UINT32 System_core_clock = 16000000;
const T_UINT8 Ahb_presc_table[16] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 6, 7, 8, 9};
const T_UINT8 Apb_presc_table[8] = {0, 0, 0, 0, 1, 2, 3, 4};

/*
 * Function                :  SystemInit
 *
 * Description             :  This function is used to Initialize the Embedded Flash Interface,
 *                            the PLL and update the SystemFrequency variable.
 *
 * Formal parameter(s)     :  None
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */

void SystemInit(void)
{

  /*hdulibsystemstm32f7xx-SystemInit-DB-LLR-008*/
  SCB->CPACR |= ((THREE << TEN*TWO)|(THREE << ELEVEN*TWO));  /* set CP10 and CP11 Full Access */

  /* Reset the RCC clock configuration to the default reset state */

  /*hdulibsystemstm32f7xx-SystemInit-DB-LLR-001*/
  /* Set HSION bit */
  RCC->CR |= (T_UINT32)HEX_ONE;

  /*hdulibsystemstm32f7xx-SystemInit-DB-LLR-002*/
  /* Reset CFGR register */
  RCC->CFGR = HEX_ZERO;

  /*hdulibsystemstm32f7xx-SystemInit-DB-LLR-003*/
  /* Reset HSEON, CSSON and PLLON bits */
  RCC->CR &= HSE_CSS_PLL;

  /*hdulibsystemstm32f7xx-SystemInit-DB-LLR-004*/
  /* Reset PLLCFGR register */
  RCC->PLLCFGR = HEX_PLLCFGR;

  /*hdulibsystemstm32f7xx-SystemInit-DB-LLR-005*/
  /* Reset HSEBYP bit */
  RCC->CR &= HEX_HSEBYP;

  /*hdulibsystemstm32f7xx-SystemInit-DB-LLR-006*/
  /* Disable all interrupts */
  RCC->CIR = HEX_ZERO;


   /* Configure the Vector Table location add offset address*/
   /* Vector Table Relocation in Internal FLASH */

  /*hdulibsystemstm32f7xx-SystemInit-DB-LLR-009*/
  if(1 == Vector_tab_sel)
  {
     SCB->VTOR = FLASH_BASE | VECT_TAB_OFFSET_BOOT;
  }
  /*hdulibsystemstm32f7xx-SystemInit-DB-LLR-010*/
  else if(TWO == Vector_tab_sel)
  {
     SCB->VTOR = FLASH_BASE | VECT_TAB_OFFSET_FLIGHT;
  }
  else
  {
     ; /* Do nothing */
  }

}

