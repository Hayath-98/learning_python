/*
 ******************************************************************************
 * License Information  :  Howell Instruments, Inc.                           *
 *                         "Licensed Software" and "All rights reserved".     *
 ******************************************************************************
 *  File                : hdulibstm32f7xxhalrcc.c
 *
 *  Description         : This file provides firmware functions to manage the
 *                        functionalities of the Reset and Clock Control (RCC) peripheral.
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
 *      1.2           Shilpa A R    02-Sep-2017          100028
 *      1.3           Rona B.S      16-Oct-2017          100083
 *
 * Additional References : None
 *
 ******************************************************************************
 */

/* Includes */
#include "hdulibstm32f7xxhalrcc.h"         /* Header files for RCC HAL driver*/
#include "hdulibstm32f7xxhal.h"            /* Header files for HAL driver*/
#include "hdulibbasictypes.h"              /* Contains basic data types*/
#include "hdulibstm32f7xxhalrccex.h"       /* Header files for RCC EX HAL driver*/
#include "hdulibstm32f7xxhalflash.h"       /* Header files for FLASH HAL driver*/
#include "hdulibstm32f746xx.h"             /* CMSIS Cortex-M7 Device Peripheral Access Layer */
#include "hdulibstm32f7xxhalgpio.h"        /* Header files for GPIO HAL driver*/
#include "hdulibstm32f7xxhaldef.h"         /*Contains the HAL defination module */
#include "hdulibstm32f7xxhalrccex.h"       /* Header files for RCC EX HAL module*/
#include "hdulibstm32f7xxhalflash.h"       /* Header file of FLASH HAL module. */
#include "hdulibstm32f7xxhalconf.h"        /* provides HAL configurations. */
#include "hdulibcmsisgcc.h"      /*CMSIS Cortex-M7 Core Function/Instruction Header File*/

#define MCO1_CLK_ENABLE   __HAL_RCC_GPIOA_CLK_ENABLE()
#define MCO1_GPIO_PORT        GPIOA
#define MCO1_PIN              GPIO_PIN_8

#define MCO2_CLK_ENABLE   __HAL_RCC_GPIOC_CLK_ENABLE()
#define MCO2_GPIO_PORT         GPIOC
#define MCO2_PIN               GPIO_PIN_9

/*
 * Function                :  HalRccOscConfig
 *
 * Description             :  This function Initializes the RCC Oscillators according to the
 *                            specified parameters in the T_RCC_OSC_INIT.
 *
 * Formal parameter(s)     :  T_RCC_OSC_INIT  *rcc_osc_init_struct - IN pointer to a structure
 *                            that contains the configuration information for the RCC Oscillators.
 *
 * Return Value            :  T_HAL_STATUS - HAL status
 *
 * Assumption              :  None
 *
 */
T_HAL_STATUS HalRccOscConfig(T_RCC_OSC_INIT  *rcc_osc_init_struct)
{
  T_UINT32 tick_start = ZERO;

  /* HSE Configuration */
  if( RCC_OSCILLATORTYPE_HSE == ((rcc_osc_init_struct->OscillatorType) & RCC_OSCILLATORTYPE_HSE))
  {
    /* When the HSE is used as system clock or clock source for PLL, It can not be disabled */
    if((__HAL_RCC_GET_SYSCLK_SOURCE() == RCC_SYSCLKSOURCE_STATUS_HSE)
       || ((__HAL_RCC_GET_SYSCLK_SOURCE() == RCC_SYSCLKSOURCE_STATUS_PLLCLK) &&
        ((RCC->PLLCFGR & RCC_PLLCFGR_PLLSRC) == RCC_PLLCFGR_PLLSRC_HSE)))
    {
     if((__HAL_RCC_GET_FLAG(RCC_FLAG_HSERDY) != RESET) &&
         ( RCC_HSE_OFF == rcc_osc_init_struct->HSEState))
      {
        /* hdulibstm32f7xxhalrcc-HalRccOscConfig-DB-LLR-001 */
        return HAL_ERROR;
      }
     else
      {
           ;/* Does nothing */
      }
    }
    else
    {
       /* hdulibstm32f7xxhalrcc-HalRccOscConfig-DB-LLR-002 */
      /* Set the new HSE configuration */
      __HAL_RCC_HSE_CONFIG(rcc_osc_init_struct->HSEState);

      /* Check the HSE State */
      if(rcc_osc_init_struct->HSEState != RCC_HSE_OFF)
      {
         /* hdulibstm32f7xxhalrcc-HalRccOscConfig-DB-LLR-003 */
        /* Get Start Tick*/
        tick_start = HALGetTick();

        /* Wait till HSE is ready */
        while(RESET == __HAL_RCC_GET_FLAG(RCC_FLAG_HSERDY) )
        {
          if((HALGetTick() - tick_start ) > HSE_TIMEOUT_VALUE)
          {
            /* hdulibstm32f7xxhalrcc-HalRccOscConfig-DB-LLR-004 */
            return HAL_TIMEOUT;
          }
          else
          {
              ;/* Does nothing */
          }
        }
      }
      else
      {
        /* hdulibstm32f7xxhalrcc-HalRccOscConfig-DB-LLR-005 */
        /* Get Start Tick*/
        tick_start = HALGetTick();

        /* Wait till HSE is bypassed or disabled */
        while(__HAL_RCC_GET_FLAG(RCC_FLAG_HSERDY) != RESET)
        {
          if((HALGetTick() - tick_start ) > HSE_TIMEOUT_VALUE)
          {
            /* hdulibstm32f7xxhalrcc-HalRccOscConfig-DB-LLR-006 */
            return HAL_TIMEOUT;
          }
          else
           {
              ;/* Does nothing */
           }
        }
      }
    }
  }
  else
  {
   ;
  }

  /* HSI Configuration */
  if(RCC_OSCILLATORTYPE_HSI == ((rcc_osc_init_struct->OscillatorType) & RCC_OSCILLATORTYPE_HSI))
  {

    /*Check if HSI is used as system clock or as PLL source when PLL is selected as system clock*/
    if((RCC_SYSCLKSOURCE_STATUS_HSI == __HAL_RCC_GET_SYSCLK_SOURCE())
       || ((RCC_SYSCLKSOURCE_STATUS_PLLCLK == __HAL_RCC_GET_SYSCLK_SOURCE()) &&
            ( RCC_PLLCFGR_PLLSRC_HSI == (RCC->PLLCFGR & RCC_PLLCFGR_PLLSRC) )))
    {
      /* When HSI is used as system clock it will not disabled */
      if((__HAL_RCC_GET_FLAG(RCC_FLAG_HSIRDY) != RESET) &&
         (rcc_osc_init_struct->HSIState != RCC_HSI_ON))
      {
        /*  hdulibstm32f7xxhalrcc-HalRccOscConfig-DB-LLR-007 */
        return HAL_ERROR;
      }
      /* Otherwise, just the calibration is allowed */
      else
      {
        /* Adjusts the Internal High Speed oscillator (HSI) calibration value.*/
        __HAL_RCC_HSI_CALIBVALUE_ADJUST(rcc_osc_init_struct->HSICalibrationValue);
      }
    }
    else
    {
      /* Check the HSI State */
      if((rcc_osc_init_struct->HSIState)!= RCC_HSI_OFF)
      {
        /*  hdulibstm32f7xxhalrcc-HalRccOscConfig-DB-LLR-008 */
        /* Enable the Internal High Speed oscillator (HSI). */
        __HAL_RCC_HSI_ENABLE();

        /* Get Start Tick*/
        tick_start = HALGetTick();

        /* Wait till HSI is ready */
        while(RESET == __HAL_RCC_GET_FLAG(RCC_FLAG_HSIRDY))
        {
          if((HALGetTick() - tick_start ) > HSI_TIMEOUT_VALUE)
          {
            /* hdulibstm32f7xxhalrcc-HalRccOscConfig-DB-LLR-009 */
            return HAL_TIMEOUT;
          }
        else
           {
              ;/* Does nothing */
           }
        }
        /* hdulibstm32f7xxhalrcc-HalRccOscConfig-DB-LLR-010 */
        /* Adjusts the Internal High Speed oscillator (HSI) calibration value.*/
        __HAL_RCC_HSI_CALIBVALUE_ADJUST(rcc_osc_init_struct->HSICalibrationValue);
      }
      else
      {
        /* hdulibstm32f7xxhalrcc-HalRccOscConfig-DB-LLR-011 */
        /* Disable the Internal High Speed oscillator (HSI). */
        __HAL_RCC_HSI_DISABLE();

        /* Get Start Tick*/
        tick_start = HALGetTick();

        /* Wait till HSI is disabled  */
        while(__HAL_RCC_GET_FLAG(RCC_FLAG_HSIRDY) != RESET)
        {
          if((HALGetTick() - tick_start ) > HSI_TIMEOUT_VALUE)
          {
            /* hdulibstm32f7xxhalrcc-HalRccOscConfig-DB-LLR-012 */
            return HAL_TIMEOUT;
          }
           else
           {
              ;/* Does nothing */
           }
        }
      }
    }
  }
  /*  LSI Configuration */
  if(RCC_OSCILLATORTYPE_LSI == ((rcc_osc_init_struct->OscillatorType) & RCC_OSCILLATORTYPE_LSI))
  {

    /* Check the LSI State */
    if((rcc_osc_init_struct->LSIState)!= RCC_LSI_OFF)
    {
      /* hdulibstm32f7xxhalrcc-HalRccOscConfig-DB-LLR-013 */
      /* Enable the Internal Low Speed oscillator (LSI). */
      __HAL_RCC_LSI_ENABLE();

      /* Get Start Tick*/
      tick_start = HALGetTick();

      /* Wait till LSI is ready */
      while(RESET == __HAL_RCC_GET_FLAG(RCC_FLAG_LSIRDY))
      {
        if((HALGetTick() - tick_start ) > LSI_TIMEOUT_VALUE)
        {
          /* hdulibstm32f7xxhalrcc-HalRccOscConfig-DB-LLR-014 */
          return HAL_TIMEOUT;
        }
          else
          {
           ;/* Does nothing */
          }
      }
    }
    else
    {
      /* hdulibstm32f7xxhalrcc-HalRccOscConfig-DB-LLR-015 */
      /* Disable the Internal Low Speed oscillator (LSI). */
      __HAL_RCC_LSI_DISABLE();

      /* Get Start Tick*/
      tick_start = HALGetTick();

      /* Wait till LSI is disabled */
      while(__HAL_RCC_GET_FLAG(RCC_FLAG_LSIRDY) != RESET)
      {
        if((HALGetTick() - tick_start ) > LSI_TIMEOUT_VALUE)
        {
           /* hdulibstm32f7xxhalrcc-HalRccOscConfig-DB-LLR-016 */
          return HAL_TIMEOUT;
        }
          else
          {
           ;/* Does nothing */
          }
      }
    }
  }
  /* LSE Configuration */
  if(RCC_OSCILLATORTYPE_LSE == ((rcc_osc_init_struct->OscillatorType) & RCC_OSCILLATORTYPE_LSE))
  {
     /* hdulibstm32f7xxhalrcc-HalRccOscConfig-DB-LLR-017 */
    /* Enable Power Clock*/
    __HAL_RCC_PWR_CLK_ENABLE();

    /* Enable write access to Backup domain */
    PWR->CR1 |= PWR_CR1_DBP;

    /* Get Start Tick*/
    tick_start = HALGetTick();

    /* Wait for Backup domain Write protection disable */
    while(RESET == (PWR->CR1 & PWR_CR1_DBP))
    {
      if((HALGetTick() - tick_start ) > RCC_DBP_TIMEOUT_VALUE)
      {
        /* hdulibstm32f7xxhalrcc-HalRccOscConfig-DB-LLR-018 */
        return HAL_TIMEOUT;
      }
     else
     {
        ;/* Does nothing */
     }
    }

    /* hdulibstm32f7xxhalrcc-HalRccOscConfig-DB-LLR-019 */
    /* Set the new LSE configuration */
    __HAL_RCC_LSE_CONFIG(rcc_osc_init_struct->LSEState);
    /* Check the LSE State */
    if((rcc_osc_init_struct->LSEState) != RCC_LSE_OFF)
    {
       /* hdulibstm32f7xxhalrcc-HalRccOscConfig-DB-LLR-020 */
      /* Get Start Tick*/
      tick_start = HALGetTick();

      /* Wait till LSE is ready */
      while(__HAL_RCC_GET_FLAG(RCC_FLAG_LSERDY) == RESET)
      {
        if((HALGetTick() - tick_start ) > RCC_LSE_TIMEOUT_VALUE)
        {
           /* hdulibstm32f7xxhalrcc-HalRccOscConfig-DB-LLR-021 */
          return HAL_TIMEOUT;
        }
        else
        {
         ;/* DOes nothing */
        }
      }
    }
    else
    {
       /* hdulibstm32f7xxhalrcc-HalRccOscConfig-DB-LLR-022 */
      /* Get Start Tick*/
      tick_start = HALGetTick();

      /* Wait till LSE is ready */
      while(__HAL_RCC_GET_FLAG(RCC_FLAG_LSERDY) != RESET)
      {
        if((HALGetTick() - tick_start ) > RCC_LSE_TIMEOUT_VALUE)
        {
          /* hdulibstm32f7xxhalrcc-HalRccOscConfig-DB-LLR-023 */
          return HAL_TIMEOUT;
        }
        else
        {
         ;/* DOes nothing */
      }
    }
  }
  }
  else
  {
     ;/* Does nothing */
  }
  if ((rcc_osc_init_struct->PLL.PLLState) != RCC_PLL_NONE)
  {
    /* Check if the PLL is used as system clock or not */
    if(__HAL_RCC_GET_SYSCLK_SOURCE() != RCC_SYSCLKSOURCE_STATUS_PLLCLK)
    {
      if(RCC_PLL_ON == (rcc_osc_init_struct->PLL.PLLState))
      {
        /* hdulibstm32f7xxhalrcc-HalRccOscConfig-DB-LLR-024 */
        /* Disable the main PLL. */
        __HAL_RCC_PLL_DISABLE();

        /* Get Start Tick*/
        tick_start = HALGetTick();

        /* Wait till PLL is ready */
        while(__HAL_RCC_GET_FLAG(RCC_FLAG_PLLRDY) != RESET)
        {
          if((HALGetTick() - tick_start ) > PLL_TIMEOUT_VALUE)
          {
            /* hdulibstm32f7xxhalrcc-HalRccOscConfig-DB-LLR-025 */
            return HAL_TIMEOUT;
          }
          else
          {
           ;/* Does nothing */
          }
        }

        /* hdulibstm32f7xxhalrcc-HalRccOscConfig-DB-LLR-026 */
        /* Configure the main PLL clock source, multiplication and division factors. */
        __HAL_RCC_PLL_CONFIG(rcc_osc_init_struct->PLL.PLLSource,
                             rcc_osc_init_struct->PLL.PLLM,
                             rcc_osc_init_struct->PLL.PLLN,
                             rcc_osc_init_struct->PLL.PLLP,
                             rcc_osc_init_struct->PLL.PLLQ);

         /* hdulibstm32f7xxhalrcc-HalRccOscConfig-DB-LLR-027 */
        /* Enable the main PLL. */
        __HAL_RCC_PLL_ENABLE();

        /* Get Start Tick*/
        tick_start = HALGetTick();

        /* Wait till PLL is ready */
        while(RESET == __HAL_RCC_GET_FLAG(RCC_FLAG_PLLRDY))
        {
          if((HALGetTick() - tick_start ) > PLL_TIMEOUT_VALUE)
          {
            /* hdulibstm32f7xxhalrcc-HalRccOscConfig-DB-LLR-028 */
            return HAL_TIMEOUT;
          }
          else
          {
           ;/* DOes nothing */
          }
        }
      }
      else
      {
        /* hdulibstm32f7xxhalrcc-HalRccOscConfig-DB-LLR-029 */
        /* Disable the main PLL. */
        __HAL_RCC_PLL_DISABLE();

        /* Get Start Tick*/
        tick_start = HALGetTick();

        /* Wait till PLL is ready */
        while(__HAL_RCC_GET_FLAG(RCC_FLAG_PLLRDY) != RESET)
        {
          if((HALGetTick() - tick_start ) > PLL_TIMEOUT_VALUE)
          {
            /* hdulibstm32f7xxhalrcc-HalRccOscConfig-DB-LLR-030 */
            return HAL_TIMEOUT;
          }
          else
          {
           ;/* DOes nothing */
          }
        }
      }
    }
    else
    {
      /* hdulibstm32f7xxhalrcc-HalRccOscConfig-DB-LLR-031 */
      return HAL_ERROR;
    }
  }
  else
  {
     ;/* does nothing */
  }
  /* hdulibstm32f7xxhalrcc-HalRccOscConfig-DB-LLR-032 */
  return HAL_OK;
}

/*
 * Function                :  HalRccClockConfig
 *
 * Description             :  Initializes the CPU, AHB and APB busses clocks according to the
 *                            specified parameters in the rcc_clk_init_struct.
 *
 * Formal parameter(s)     :  T_RCC_CLK_INIT  *rcc_clk_init_struct - IN pointer to an
 *                            T_RCC_OSC_INIT structure that contains the configuration information
 *                            for the RCC peripheral.
 *                            T_UINT32 f_latency - IN FLASH Latency, this parameter depend on
 *                            device selected
 *
 * Return Value            :  T_HAL_STATUS - HAL status
 *
 * Assumption              :  None
 *
 */

T_HAL_STATUS HalRccClockConfig(T_RCC_CLK_INIT  *rcc_clk_init_struct, T_UINT32 f_latency)
{
  T_UINT32 tick_start = ZERO;

  /*
   * To correctly read data from FLASH memory, the number of wait states (LATENCY)
   * must be correctly programmed according to the frequency of the CPU clock
   * (HCLK) and the supply voltage of the device.
   */

  /* Increasing the CPU frequency */
  if(f_latency > (FLASH->ACR & FLASH_ACR_LATENCY))
  {
     /* hdulibstm32f7xxhalrcc-HalRccClockConfig-DB-LLR-001 */
    /* Program the new number of wait states to the LATENCY bits in the FLASH_ACR register */
    __HAL_FLASH_SET_LATENCY(f_latency);

    /*
     * Check that the new number of wait states is taken into account to access the Flash
     * memory by reading the FLASH_ACR register
     */
    if((FLASH->ACR & FLASH_ACR_LATENCY) != f_latency)
    {
      /* hdulibstm32f7xxhalrcc-HalRccClockConfig-DB-LLR-002 */
      return HAL_ERROR;
    }
    else
   {
      ;/* Does nothing */
   }
  }
  else
  {
     ;/* Does nothing */
  }

  /* HCLK Configuration */
  if(RCC_CLOCKTYPE_HCLK == ((rcc_clk_init_struct->ClockType) & RCC_CLOCKTYPE_HCLK))
  {
    /* hdulibstm32f7xxhalrcc-HalRccClockConfig-DB-LLR-003 */
    MODIFY_REG(RCC->CFGR, RCC_CFGR_HPRE, rcc_clk_init_struct->AHBCLKDivider);
  }
  else
  {
     ;/* Does nothing */
  }

  /* SYSCLK Configuration */
  if(RCC_CLOCKTYPE_SYSCLK == ((rcc_clk_init_struct->ClockType) & RCC_CLOCKTYPE_SYSCLK))
  {
    /* HSE is selected as System Clock Source */
    if(RCC_SYSCLKSOURCE_HSE == rcc_clk_init_struct->SYSCLKSource)
    {
      /* Check the HSE ready flag */
      if(__HAL_RCC_GET_FLAG(RCC_FLAG_HSERDY) == RESET)
      {
        /* hdulibstm32f7xxhalrcc-HalRccClockConfig-DB-LLR-004 */
        return HAL_ERROR;
      }
      else
      {
       ;
      }
    }
    /* PLL is selected as System Clock Source */
    else if(RCC_SYSCLKSOURCE_PLLCLK == rcc_clk_init_struct->SYSCLKSource)
    {
      /* Check the PLL ready flag */
      if(__HAL_RCC_GET_FLAG(RCC_FLAG_PLLRDY) == RESET)
      {
         /* hdulibstm32f7xxhalrcc-HalRccClockConfig-DB-LLR-005 */
        return HAL_ERROR;
      }
      else
      {
       ;
      }
    }
    /* HSI is selected as System Clock Source */
    else
    {
      /* Check the HSI ready flag */
      if(__HAL_RCC_GET_FLAG(RCC_FLAG_HSIRDY) == RESET)
      {
         /* hdulibstm32f7xxhalrcc-HalRccClockConfig-DB-LLR-006 */
        return HAL_ERROR;
      }
      else
      {
       ;
      }
    }

    /* hdulibstm32f7xxhalrcc-HalRccClockConfig-DB-LLR-007 */
    __HAL_RCC_SYSCLK_CONFIG(rcc_clk_init_struct->SYSCLKSource);
    /* Get Start Tick*/
    tick_start = HALGetTick();

    if(RCC_SYSCLKSOURCE_HSE == rcc_clk_init_struct->SYSCLKSource)
    {
      while (__HAL_RCC_GET_SYSCLK_SOURCE() != RCC_SYSCLKSOURCE_STATUS_HSE)
      {
        if((HALGetTick() - tick_start ) > CLOCKSWITCH_TIMEOUT_VALUE)
        {
          /* hdulibstm32f7xxhalrcc-HalRccClockConfig-DB-LLR-008 */
          return HAL_TIMEOUT;
        }
        else
        {
          ;
        }
      }
    }
    else if(RCC_SYSCLKSOURCE_PLLCLK == rcc_clk_init_struct->SYSCLKSource)
    {
      while (__HAL_RCC_GET_SYSCLK_SOURCE() != RCC_SYSCLKSOURCE_STATUS_PLLCLK)
      {
        if((HALGetTick() - tick_start ) > CLOCKSWITCH_TIMEOUT_VALUE)
        {
           /* hdulibstm32f7xxhalrcc-HalRccClockConfig-DB-LLR-009 */
          return HAL_TIMEOUT;
        }
        else
        {
          ;
        }
      }
    }
    else
    {
      while(__HAL_RCC_GET_SYSCLK_SOURCE() != RCC_SYSCLKSOURCE_STATUS_HSI)
      {
        if((HALGetTick() - tick_start ) > CLOCKSWITCH_TIMEOUT_VALUE)
        {
           /* hdulibstm32f7xxhalrcc-HalRccClockConfig-DB-LLR-010 */
          return HAL_TIMEOUT;
        }
        else
        {
          ;
        }
      }
    }
  }
  else
  {
     ;/* Does nothing */
   }

  /* Decreasing the number of wait states because of lower CPU frequency */
  if(f_latency < (FLASH->ACR & FLASH_ACR_LATENCY))
  {
    /* hdulibstm32f7xxhalrcc-HalRccClockConfig-DB-LLR-011 */
    /* Program the new number of wait states to the LATENCY bits in the FLASH_ACR register */
    __HAL_FLASH_SET_LATENCY(f_latency);

    /*
     * Check that the new number of wait states is taken into account to access the Flash
     * memory by reading the FLASH_ACR register
     */
    if((FLASH->ACR & FLASH_ACR_LATENCY) != f_latency)
    {
      /* hdulibstm32f7xxhalrcc-HalRccClockConfig-DB-LLR-012 */
      return HAL_ERROR;
    }
    else
    {
     ;
    }
  }

  /* PCLK1 Configuration */
  if(RCC_CLOCKTYPE_PCLK1 == ((rcc_clk_init_struct->ClockType) & RCC_CLOCKTYPE_PCLK1) )
  {
    /* hdulibstm32f7xxhalrcc-HalRccClockConfig-DB-LLR-013 */
    MODIFY_REG(RCC->CFGR, RCC_CFGR_PPRE1, rcc_clk_init_struct->APB1CLKDivider);
  }
  else
  {
    ;
  }

  /* PCLK2 Configuration */
  if(RCC_CLOCKTYPE_PCLK2 == ((rcc_clk_init_struct->ClockType) & RCC_CLOCKTYPE_PCLK2))
  {
    /* hdulibstm32f7xxhalrcc-HalRccClockConfig-DB-LLR-014 */
    MODIFY_REG(RCC->CFGR, RCC_CFGR_PPRE2, ((rcc_clk_init_struct->APB2CLKDivider) << THREE));
  }
  else
  {
   ;/* Does nothing */
  }

  /* hdulibstm32f7xxhalrcc-HalRccClockConfig-DB-LLR-015 */
  /* Update the System_core_clock global variable */
  System_core_clock = HalRccGetSysClockFreq() >> Ahb_presc_table[(RCC->CFGR & RCC_CFGR_HPRE)>>
                                                POSITION_VAL(RCC_CFGR_HPRE)];

  /* hdulibstm32f7xxhalrcc-HalRccClockConfig-DB-LLR-016 */
  /* Configure the source of time base considering new system clocks settings*/
  HALInitTick (TICK_INT_PRIORITY);

  /* hdulibstm32f7xxhalrcc-HalRccClockConfig-DB-LLR-017 */
  return HAL_OK;
}

/*
 * Function                :  HalRccGetSysClockFreq
 *
 * Description             :  This function Returns the SYSCLK frequency
 *
 * Formal parameter(s)     :  None
 *
 * Return Value            :  T_UINT32 - SYSCLK frequency
 *
 * Assumption              :  None
 *
 */
T_UINT32 HalRccGetSysClockFreq(void)
{
  T_UINT32 pll_m = ZERO,
           pll_vco = ZERO,
           pll_p = ZERO;
  T_UINT32 sys_clock_freq = ZERO;

  /* Get SYSCLK source */
  switch (RCC->CFGR & RCC_CFGR_SWS)
  {
    case RCC_SYSCLKSOURCE_STATUS_HSI:  /* HSI used as system clock source */
    {
       /* hdulibstm32f7xxhalrcc-HalRccGetSysClockFreq-DB-LLR-001 */
      sys_clock_freq = HSI_VALUE;
       break;
    }
    case RCC_SYSCLKSOURCE_STATUS_HSE:  /* HSE used as system clock  source */
    {
      /* hdulibstm32f7xxhalrcc-HalRccGetSysClockFreq-DB-LLR-002 */
      sys_clock_freq = HSE_VALUE;
      break;
    }
    case RCC_SYSCLKSOURCE_STATUS_PLLCLK:  /* PLL used as system clock  source */
    {
      /* hdulibstm32f7xxhalrcc-HalRccGetSysClockFreq-DB-LLR-003 */
      pll_m = RCC->PLLCFGR & RCC_PLLCFGR_PLLM;

      if (__HAL_RCC_GET_PLL_OSCSOURCE() != RCC_PLLCFGR_PLLSRC_HSI)
      {
        /* hdulibstm32f7xxhalrcc-HalRccGetSysClockFreq-DB-LLR-004 */
        /* HSE used as PLL clock source */
        pll_vco = ((HSE_VALUE / pll_m) * ((RCC->PLLCFGR & RCC_PLLCFGR_PLLN)
                  >> POSITION_VAL(RCC_PLLCFGR_PLLN)));
      }
      else
      {
        /* hdulibstm32f7xxhalrcc-HalRccGetSysClockFreq-DB-LLR-005 */
        /* HSI used as PLL clock source */
        pll_vco = ((HSI_VALUE / pll_m) * ((RCC->PLLCFGR & RCC_PLLCFGR_PLLN)
                     >> POSITION_VAL(RCC_PLLCFGR_PLLN)));
      }

      /* hdulibstm32f7xxhalrcc-HalRccGetSysClockFreq-DB-LLR-006 */
      pll_p = ((((RCC->PLLCFGR & RCC_PLLCFGR_PLLP) >> POSITION_VAL(RCC_PLLCFGR_PLLP))
               + ONE ) * TWO);

      sys_clock_freq = pll_vco/pll_p;

      break;
    }
    default:
    {
      /* hdulibstm32f7xxhalrcc-HalRccGetSysClockFreq-DB-LLR-007 */
      sys_clock_freq = HSI_VALUE;
      break;
    }
  }
  /* hdulibstm32f7xxhalrcc-HalRccGetSysClockFreq-DB-LLR-008 */
  return sys_clock_freq;
}

