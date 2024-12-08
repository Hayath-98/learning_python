/*
 ******************************************************************************
 * License Information  :  Howell Instruments, Inc.                           *
 *                         "Licensed Software" and "All rights reserved".     *
 ******************************************************************************
 *  File                : hdulibstm32f7xxhalrccex.c
 *
 *  Description         : This file provides firmware functions to manage functionalities
 *                        of RCC extension peripheral
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
 *      1.2           Rona B.S      02-Sep-2017          100028
 *      1.3           Divya G P     09-Oct-2017          100064
 *
 * Additional References : None
 *
 ******************************************************************************
 */

/* Includes*/
#include "hdulibstm32f7xxhal.h"           /* Header file of HAL module.*/
#include "hdulibbasictypes.h"             /* Contains all the basic data types.*/
#include "hdulibstm32f7xxhalrccex.h"      /* Header file of RCC EX HAL module.*/
#include "hdulibstm32f7xxhalrcc.h"        /* Header file of RCC HAL module.*/
#include "hdulibstm32f746xx.h"            /* CMSIS Cortex-M7 Device Peripheral Access Layer */
#include "hdulibstm32f7xxhaldef.h"        /*Contains the HAL defination module */
#include "hdulibstm32f7xx.h"              /* CMSIS STM32F7xx Peripheral Access Layer Header File.*/
#include "hdulibcmsisgcc.h"               /*CMSIS Cortex-M7 Core Function/Instruction Header File*/


#define PLLI2S_TIMEOUT_VALUE    100U /* Timeout value fixed to 100 ms  */
#define PLLSAI_TIMEOUT_VALUE    100U /* Timeout value fixed to 100 ms  */

/*
 * Function                :  HalRccExPeriphCLKConfig
 *
 * Description             :  This function enters an infinite loop, preserving
 *                            the system state for examination by a debugger.
 *                            This function gets called when the processor receives an
 *                            unexpected interrupt
 *
 * Formal parameter(s)     :  T_RCC_PERIPH_CLK  *periph_clk_init - IN  pointer to
 *                            structure that contains the configuration information for the
 *                            Extended Peripherals
 *
 * Return Value            :  T_HAL_STATUS - HAL status
 *
 * Assumption              :  None
 *
 */

T_HAL_STATUS HalRccExPeriphCLKConfig(T_RCC_PERIPH_CLK  *periph_clk_init)
{
  T_UINT32 tick_start = ZERO;
  T_UINT32 tmp_reg0 = ZERO;
  T_UINT32 tmp_reg1 = ZERO;
  T_UINT32 pll_i2s_used = ZERO;
  T_UINT32 pll_sai_used = ZERO;

  /*hdulibstm32f7xxhalrccex-HalRccExPeriphCLKConfig-DB-LLR-001*/
  /* I2S configuration */
  if(((RCC_PERIPHCLK_I2S) == ((periph_clk_init->PeriphClockSelection) & RCC_PERIPHCLK_I2S)))
  {
    /* Configure I2S Clock source */
    __HAL_RCC_I2S_CONFIG(periph_clk_init->I2sClockSelection);

    /* Enable the PLLI2S when it's used as clock source for I2S */
    if(RCC_I2SCLKSOURCE_PLLI2S == periph_clk_init->I2sClockSelection)
    {
      pll_i2s_used = ONE;
    }
    else
    {
      ;/* Does nothing */
    }

  }
  else
  {
   ;
  }

  /*hdulibstm32f7xxhalrccex-HalRccExPeriphCLKConfig-DB-LLR-002*/
  /* SAI1 configuration */
  if( (RCC_PERIPHCLK_SAI1) == ((periph_clk_init->PeriphClockSelection) & RCC_PERIPHCLK_SAI1))
  {
    /* Configure SAI1 Clock source */
    __HAL_RCC_SAI1_CONFIG(periph_clk_init->Sai1ClockSelection);

    /* Enable the PLLI2S when it's used as clock source for SAI */
    if(RCC_SAI1CLKSOURCE_PLLI2S == periph_clk_init->Sai1ClockSelection )
    {
      pll_i2s_used = ONE;
    }
    else
    {
      ;/* Does nothing */
    }

    /* Enable the PLLSAI when it's used as clock source for SAI */
    if(RCC_SAI1CLKSOURCE_PLLSAI == periph_clk_init->Sai1ClockSelection )
    {
      pll_sai_used = ONE;
    }
    else
    {
      ;/* Does nothing */
    }
  }
  else
  {
    ;
  }

  /*hdulibstm32f7xxhalrccex-HalRccExPeriphCLKConfig-DB-LLR-003*/
  /* SAI2 configuration */
  if((RCC_PERIPHCLK_SAI2) == ((periph_clk_init->PeriphClockSelection) & RCC_PERIPHCLK_SAI2))
  {

    /* Configure SAI2 Clock source */
    __HAL_RCC_SAI2_CONFIG(periph_clk_init->Sai2ClockSelection);

    /* Enable the PLLI2S when it's used as clock source for SAI */
    if(RCC_SAI2CLKSOURCE_PLLI2S == periph_clk_init->Sai2ClockSelection )
    {
      pll_i2s_used = ONE;
    }
    else
    {
      ;/* Does nothing */
    }
    /* Enable the PLLSAI when it's used as clock source for SAI */
    if(RCC_SAI2CLKSOURCE_PLLSAI == periph_clk_init->Sai2ClockSelection)
    {
      pll_sai_used = ONE;
    }
    else
    {
      ;/* Does nothing */
    }
  }
  else
  {
   ;
  }

  /*hdulibstm32f7xxhalrccex-HalRccExPeriphCLKConfig-DB-LLR-004*/
  /* SPDIF-RX Configuration */
  if(RCC_PERIPHCLK_SPDIFRX == ((periph_clk_init->PeriphClockSelection) & RCC_PERIPHCLK_SPDIFRX))
  {
      pll_i2s_used = ONE;
  }
  else
  {
   ;/* Does nothing */
  }

  /*hdulibstm32f7xxhalrccex-HalRccExPeriphCLKConfig-DB-LLR-005*/
  /* RTC configuration */
  if( (RCC_PERIPHCLK_RTC) == ((periph_clk_init->PeriphClockSelection) & RCC_PERIPHCLK_RTC))
  {
    /* Enable Power Clock*/
    __HAL_RCC_PWR_CLK_ENABLE();

    /* Enable write access to Backup domain */
    PWR->CR1 |= PWR_CR1_DBP;

    /* Get Start Tick*/
    tick_start = HALGetTick();

    /*hdulibstm32f7xxhalrccex-HalRccExPeriphCLKConfig-DB-LLR-005*/
    /* Wait for Backup domain Write protection disable */
    while(RESET == (PWR->CR1 & PWR_CR1_DBP))
    {
      if((HALGetTick() - tick_start) > RCC_DBP_TIMEOUT_VALUE)
      {
        return HAL_TIMEOUT;
      }
      else
      {
         ;/* Does nothing */
      }
    }

    /* Reset the Backup domain only if the RTC Clock source selection is modified */
    tmp_reg0 = (RCC->BDCR & RCC_BDCR_RTCSEL);

    /*hdulibstm32f7xxhalrccex-HalRccExPeriphCLKConfig-DB-LLR-006*/
    if((tmp_reg0 != ZERO) && (tmp_reg0 != (periph_clk_init->RTCClockSelection & RCC_BDCR_RTCSEL)))
    {
      /* Store the content of BDCR register before the reset of Backup Domain */
      tmp_reg0 = (RCC->BDCR & ~(RCC_BDCR_RTCSEL));

      /* RTC Clock selection can be changed only if the Backup Domain is reset */
      __HAL_RCC_BACKUPRESET_FORCE();
      __HAL_RCC_BACKUPRESET_RELEASE();

      /* Restore the Content of BDCR register */
      RCC->BDCR = tmp_reg0;

      /*hdulibstm32f7xxhalrccex-HalRccExPeriphCLKConfig-DB-LLR-007*/
      /* Wait for LSE reactivation if LSE was enable prior to Backup Domain reset */
      if (HAL_IS_BIT_SET(RCC->BDCR, RCC_BDCR_LSEON) != RESET)
      {
        /* Get Start Tick*/
        tick_start = HALGetTick();

        /* Wait till LSE is ready */
        while(RESET == __HAL_RCC_GET_FLAG(RCC_FLAG_LSERDY))
        {
          if((HALGetTick() - tick_start ) > RCC_LSE_TIMEOUT_VALUE)
          {
            return HAL_TIMEOUT;
          }
          else
          {
           /* Does nothing */
          }
        }
      }
      else
      {
       ;
      }
    }
    else
    {
     ;
    }
    /*hdulibstm32f7xxhalrccex-HalRccExPeriphCLKConfig-DB-LLR-008*/
    __HAL_RCC_RTC_CONFIG(periph_clk_init->RTCClockSelection);
  }
  else
  {
   ;
  }

  /*hdulibstm32f7xxhalrccex-HalRccExPeriphCLKConfig-DB-LLR-009*/
  /* TIM configuration */
  if( (RCC_PERIPHCLK_TIM) == ((periph_clk_init->PeriphClockSelection) & RCC_PERIPHCLK_TIM))
  {
    /* Configure Timer Prescaler */
    __HAL_RCC_TIMCLKPRESCALER(periph_clk_init->TIMPresSelection);
  }
  else
  {
     /* Does nothing */
  }

  /*hdulibstm32f7xxhalrccex-HalRccExPeriphCLKConfig-DB-LLR-010*/
  /* I2C1 Configuration */
  if(RCC_PERIPHCLK_I2C1 == ((periph_clk_init->PeriphClockSelection) & RCC_PERIPHCLK_I2C1))
  {
    /* Configure the I2C1 clock source */
    __HAL_RCC_I2C1_CONFIG(periph_clk_init->I2c1ClockSelection);
  }
  else
  {
     /* Does nothing */
  }

  /*hdulibstm32f7xxhalrccex-HalRccExPeriphCLKConfig-DB-LLR-011*/
  /* I2C2 Configuration */
  if(RCC_PERIPHCLK_I2C2 == ((periph_clk_init->PeriphClockSelection) & RCC_PERIPHCLK_I2C2))
  {
    /* Configure the I2C2 clock source */
    __HAL_RCC_I2C2_CONFIG(periph_clk_init->I2c2ClockSelection);
  }
  else
  {
     /* Does nothing */
  }

  /*hdulibstm32f7xxhalrccex-HalRccExPeriphCLKConfig-DB-LLR-012*/
  /* I2C3 Configuration */
  if(RCC_PERIPHCLK_I2C3 == ((periph_clk_init->PeriphClockSelection) & RCC_PERIPHCLK_I2C3))
  {
    /* Configure the I2C3 clock source */
    __HAL_RCC_I2C3_CONFIG(periph_clk_init->I2c3ClockSelection);
  }
  else
  {
     /* Does nothing */
  }

  /*hdulibstm32f7xxhalrccex-HalRccExPeriphCLKConfig-DB-LLR-013*/
  /* I2C4 Configuration */
  if(RCC_PERIPHCLK_I2C4 == ((periph_clk_init->PeriphClockSelection) & RCC_PERIPHCLK_I2C4))
  {
    /* Configure the I2C4 clock source */
    __HAL_RCC_I2C4_CONFIG(periph_clk_init->I2c4ClockSelection);
  }
  else
  {
     /* Does nothing */
  }

  /*hdulibstm32f7xxhalrccex-HalRccExPeriphCLKConfig-DB-LLR-014*/
  /* USART1 Configuration */
  if(RCC_PERIPHCLK_USART1 == ((periph_clk_init->PeriphClockSelection) & RCC_PERIPHCLK_USART1) )
  {

    /* Configure the USART1 clock source */
    __HAL_RCC_USART1_CONFIG(periph_clk_init->Usart1ClockSelection);
  }
  else
  {
     /* Does nothing */
  }

  /*hdulibstm32f7xxhalrccex-HalRccExPeriphCLKConfig-DB-LLR-015*/
  /* USART2 Configuration */
  if(RCC_PERIPHCLK_USART2 == ((periph_clk_init->PeriphClockSelection) & RCC_PERIPHCLK_USART2) )
  {

    /* Configure the USART2 clock source */
    __HAL_RCC_USART2_CONFIG(periph_clk_init->Usart2ClockSelection);
  }
  else
  {
     /* Does nothing */
  }

  /*hdulibstm32f7xxhalrccex-HalRccExPeriphCLKConfig-DB-LLR-016*/
  /*USART3 Configuration */
  if(RCC_PERIPHCLK_USART3 ==((periph_clk_init->PeriphClockSelection) & RCC_PERIPHCLK_USART3))
  {
    /* Configure the USART3 clock source */
    __HAL_RCC_USART3_CONFIG(periph_clk_init->Usart3ClockSelection);
  }
  else
  {
     /* Does nothing */
  }

  /*hdulibstm32f7xxhalrccex-HalRccExPeriphCLKConfig-DB-LLR-017*/
  /* UART4 Configuration */
  if(RCC_PERIPHCLK_UART4 == ((periph_clk_init->PeriphClockSelection) & RCC_PERIPHCLK_UART4))
  {

    /* Configure the UART4 clock source */
    __HAL_RCC_UART4_CONFIG(periph_clk_init->Uart4ClockSelection);
  }
  else
  {
     /* Does nothing */
  }

  /*hdulibstm32f7xxhalrccex-HalRccExPeriphCLKConfig-DB-LLR-018*/
  /* UART5 Configuration */
  if(RCC_PERIPHCLK_UART5 == ((periph_clk_init->PeriphClockSelection) & RCC_PERIPHCLK_UART5))
  {

    /* Configure the UART5 clock source */
    __HAL_RCC_UART5_CONFIG(periph_clk_init->Uart5ClockSelection);
  }
  else
  {
     /* Does nothing */
  }

  /*hdulibstm32f7xxhalrccex-HalRccExPeriphCLKConfig-DB-LLR-019*/
  /* USART6 Configuration */
  if(RCC_PERIPHCLK_USART6 == ((periph_clk_init->PeriphClockSelection) & RCC_PERIPHCLK_USART6))
  {

    /* Configure the USART6 clock source */
    __HAL_RCC_USART6_CONFIG(periph_clk_init->Usart6ClockSelection);
  }
  else
  {
     /* Does nothing */
  }

  /*hdulibstm32f7xxhalrccex-HalRccExPeriphCLKConfig-DB-LLR-020*/
  /* UART7 Configuration */
  if(RCC_PERIPHCLK_UART7 == ((periph_clk_init->PeriphClockSelection) & RCC_PERIPHCLK_UART7))
  {
    /* Configure the UART7 clock source */
    __HAL_RCC_UART7_CONFIG(periph_clk_init->Uart7ClockSelection);
  }
  else
  {
     /* Does nothing */
  }

  /*hdulibstm32f7xxhalrccex-HalRccExPeriphCLKConfig-DB-LLR-021*/
  /* UART8 Configuration */
  if(RCC_PERIPHCLK_UART8 == ((periph_clk_init->PeriphClockSelection) & RCC_PERIPHCLK_UART8))
  {

    /* Configure the UART8 clock source */
    __HAL_RCC_UART8_CONFIG(periph_clk_init->Uart8ClockSelection);
  }
  else
  {
     /* Does nothing */
  }

  /*hdulibstm32f7xxhalrccex-HalRccExPeriphCLKConfig-DB-LLR-022*/
  /*- CEC Configuration */
  if(RCC_PERIPHCLK_CEC == ((periph_clk_init->PeriphClockSelection) & RCC_PERIPHCLK_CEC))
  {

    /* Configure the CEC clock source */
    __HAL_RCC_CEC_CONFIG(periph_clk_init->CecClockSelection);
  }
  else
  {
     /* Does nothing */
  }

  /*hdulibstm32f7xxhalrccex-HalRccExPeriphCLKConfig-DB-LLR-023*/
  /* CK48 Configuration */
  if(RCC_PERIPHCLK_CLK48 == ((periph_clk_init->PeriphClockSelection) & RCC_PERIPHCLK_CLK48))
  {

    /* Configure the CLK48 source */
    __HAL_RCC_CLK48_CONFIG(periph_clk_init->Clk48ClockSelection);

    /* Enable the PLLSAI when it's used as clock source for CK48 */
    if(RCC_CLK48SOURCE_PLLSAIP == periph_clk_init->Clk48ClockSelection)
    {
      pll_sai_used = ONE;
    }
    else
    {
     /* Does nothing */
    }
  }
  else
  {
     /* Does nothing */
  }

  /*hdulibstm32f7xxhalrccex-HalRccExPeriphCLKConfig-DB-LLR-024*/
  /* LTDC Configuration */
  if(RCC_PERIPHCLK_LTDC == ((periph_clk_init->PeriphClockSelection) & RCC_PERIPHCLK_LTDC))
  {
    pll_sai_used = ONE;
  }
  else
  {
     /* Does nothing */
  }

  /*hdulibstm32f7xxhalrccex-HalRccExPeriphCLKConfig-DB-LLR-025*/
  /* LPTIM1 Configuration */
  if(RCC_PERIPHCLK_LPTIM1 == ((periph_clk_init->PeriphClockSelection) & RCC_PERIPHCLK_LPTIM1))
  {

    /* Configure the LTPIM1 clock source */
    __HAL_RCC_LPTIM1_CONFIG(periph_clk_init->Lptim1ClockSelection);
   }
  else
  {
     /* Does nothing */
  }

  /*hdulibstm32f7xxhalrccex-HalRccExPeriphCLKConfig-DB-LLR-026*/
  /* SDMMC1 Configuration */
  if(RCC_PERIPHCLK_SDMMC1 == ((periph_clk_init->PeriphClockSelection) & RCC_PERIPHCLK_SDMMC1))
  {

    /* Configure the SDMMC1 clock source */
    __HAL_RCC_SDMMC1_CONFIG(periph_clk_init->Sdmmc1ClockSelection);
  }
  else
  {
     /* Does nothing */
  }

  /*hdulibstm32f7xxhalrccex-HalRccExPeriphCLKConfig-DB-LLR-027*/
  /* PLLI2S Configuration */
  if((ONE == pll_i2s_used ) || (RCC_PERIPHCLK_PLLI2S == periph_clk_init->PeriphClockSelection))
  {
    /* Disable the PLLI2S */
    __HAL_RCC_PLLI2S_DISABLE();

    /* Get Start Tick*/
    tick_start = HALGetTick();

    /* Wait till PLLI2S is disabled */
    while(__HAL_RCC_GET_FLAG(RCC_FLAG_PLLI2SRDY)  != RESET)
    {
      if((HALGetTick() - tick_start) > PLLI2S_TIMEOUT_VALUE)
      {
        /* return in case of Timeout detected */
        return HAL_TIMEOUT;
      }
      else
      {
        /* Does nothing */
      }
    }

   /*hdulibstm32f7xxhalrccex-HalRccExPeriphCLKConfig-DB-LLR-028*/
    /* In Case of PLLI2S is selected as source clock for I2 -*/
    if(((RCC_PERIPHCLK_I2S == ((periph_clk_init->PeriphClockSelection) & RCC_PERIPHCLK_I2S))
         && (RCC_I2SCLKSOURCE_PLLI2S == periph_clk_init->I2sClockSelection)))
    {
      /* Read PLLI2SP and PLLI2SQ value from PLLI2SCFGR register */
      tmp_reg0 = ((RCC->PLLI2SCFGR & RCC_PLLI2SCFGR_PLLI2SP) >>
                  POSITION_VAL(RCC_PLLI2SCFGR_PLLI2SP));
      tmp_reg1 = ((RCC->PLLI2SCFGR & RCC_PLLI2SCFGR_PLLI2SQ) >>
                  POSITION_VAL(RCC_PLLI2SCFGR_PLLI2SQ));

      /* Configure the PLLI2S division factors */

      __HAL_RCC_PLLI2S_CONFIG(periph_clk_init->PLLI2S.PLLI2SN , tmp_reg0, tmp_reg1,
                              periph_clk_init->PLLI2S.PLLI2SR);
    }
    else
    {
     /* Does nothing */
    }

    /*hdulibstm32f7xxhalrccex-HalRccExPeriphCLKConfig-DB-LLR-029*/
    /*In Case of PLLI2S is selected as source clock for SAI -*/
    if(((RCC_PERIPHCLK_SAI1 == ((periph_clk_init->PeriphClockSelection) & RCC_PERIPHCLK_SAI1))
         && (RCC_SAI1CLKSOURCE_PLLI2S == periph_clk_init->Sai1ClockSelection)) ||
       ((RCC_PERIPHCLK_SAI2 == ((periph_clk_init->PeriphClockSelection) & RCC_PERIPHCLK_SAI2))
            && (RCC_SAI2CLKSOURCE_PLLI2S == periph_clk_init->Sai2ClockSelection)))
    {

      /*
       * Read PLLI2SP and PLLI2SR values from PLLI2SCFGR register (this value is not
       * needed for SAI configuration)
       */
      tmp_reg0 = ((RCC->PLLI2SCFGR & RCC_PLLI2SCFGR_PLLI2SP) >>
                  POSITION_VAL(RCC_PLLI2SCFGR_PLLI2SP));
      tmp_reg1 = ((RCC->PLLI2SCFGR & RCC_PLLI2SCFGR_PLLI2SR) >>
                  POSITION_VAL(RCC_PLLI2SCFGR_PLLI2SR));

      /* Configure the PLLI2S division factors */

      __HAL_RCC_PLLI2S_CONFIG(periph_clk_init->PLLI2S.PLLI2SN, tmp_reg0,
                              periph_clk_init->PLLI2S.PLLI2SQ, tmp_reg1);

      __HAL_RCC_PLLI2S_CLKDIVQ_CFG(periph_clk_init->PLLI2SDivQ);
    }
    else
    {
     /* Does nothing */
    }

   /*hdulibstm32f7xxhalrccex-HalRccExPeriphCLKConfig-DB-LLR-030*/
    /* In Case of PLLI2S is selected as source clock for SPDIF-RX */
    if(RCC_PERIPHCLK_SPDIFRX == ((periph_clk_init->PeriphClockSelection) & RCC_PERIPHCLK_SPDIFRX))
    {

      tmp_reg0 = ((RCC->PLLI2SCFGR & RCC_PLLI2SCFGR_PLLI2SQ) >>
                  POSITION_VAL(RCC_PLLI2SCFGR_PLLI2SQ));
      tmp_reg1 = ((RCC->PLLI2SCFGR & RCC_PLLI2SCFGR_PLLI2SR) >>
                  POSITION_VAL(RCC_PLLI2SCFGR_PLLI2SR));

      /* Configure the PLLI2S division factors */
      __HAL_RCC_PLLI2S_CONFIG(periph_clk_init->PLLI2S.PLLI2SN , periph_clk_init->PLLI2S.PLLI2SP,
           tmp_reg0, tmp_reg1);
    }
    else
    {
     /* Does nothing */
    }

     /*hdulibstm32f7xxhalrccex-HalRccExPeriphCLKConfig-DB-LLR-031*/
    /*In Case of PLLI2S is just selected */
    if(RCC_PERIPHCLK_PLLI2S == (periph_clk_init->PeriphClockSelection & RCC_PERIPHCLK_PLLI2S))
    {

      /* Configure the PLLI2S division factors */

      __HAL_RCC_PLLI2S_CONFIG(periph_clk_init->PLLI2S.PLLI2SN , periph_clk_init->PLLI2S.PLLI2SP,
           periph_clk_init->PLLI2S.PLLI2SQ, periph_clk_init->PLLI2S.PLLI2SR);
    }
    else
    {
     /* Does nothing */
    }

    /*hdulibstm32f7xxhalrccex-HalRccExPeriphCLKConfig-DB-LLR-032*/
    /* Enable the PLLI2S */
    __HAL_RCC_PLLI2S_ENABLE();

    /* Get Start Tick*/
    tick_start = HALGetTick();

    /* Wait till PLLI2S is ready */
    while(RESET == __HAL_RCC_GET_FLAG(RCC_FLAG_PLLI2SRDY))
    {
      if((HALGetTick() - tick_start) > PLLI2S_TIMEOUT_VALUE)
      {
        /* return in case of Timeout detected */
        return HAL_TIMEOUT;
      }
      else
      {
        /* Does nothing */
      }
    }
  }

  /* PLLSAI Configuration */
  /*
   * PLLSAI is configured when a peripheral will use it as source clock : SAI1, SAI2,
   * LTDC or CK48
   */
  if(ONE == pll_sai_used)
  {
   /*hdulibstm32f7xxhalrccex-HalRccExPeriphCLKConfig-DB-LLR-033*/
   /* Disable PLLSAI Clock */
    __HAL_RCC_PLLSAI_DISABLE();

    /* Get Start Tick*/
    tick_start = HALGetTick();

    /* Wait till PLLSAI is disabled */
    while(__HAL_RCC_PLLSAI_GET_FLAG() != RESET)
    {
      if((HALGetTick() - tick_start) > PLLSAI_TIMEOUT_VALUE)
      {
        /* return in case of Timeout detected */
        return HAL_TIMEOUT;
      }
      else
      {
        /* Does nothing */
      }
    }

    /*hdulibstm32f7xxhalrccex-HalRccExPeriphCLKConfig-DB-LLR-034*/
    /* In Case of PLLSAI is selected as source clock for SAI */
    if(((RCC_PERIPHCLK_SAI1 == ((periph_clk_init->PeriphClockSelection) & RCC_PERIPHCLK_SAI1))
         && (RCC_SAI1CLKSOURCE_PLLSAI == periph_clk_init->Sai1ClockSelection)) ||\
       ((RCC_PERIPHCLK_SAI2 == ((periph_clk_init->PeriphClockSelection) & RCC_PERIPHCLK_SAI2))
            && (RCC_SAI2CLKSOURCE_PLLSAI == periph_clk_init->Sai2ClockSelection)))
    {

      /*
       * Read PLLSAIP value from PLLSAICFGR register (this value is not needed
       * for SAI configuration)
       */
      tmp_reg0 = ((RCC->PLLSAICFGR & RCC_PLLSAICFGR_PLLSAIP) >>
                   POSITION_VAL(RCC_PLLSAICFGR_PLLSAIP));
      tmp_reg1 = ((RCC->PLLSAICFGR & RCC_PLLI2SCFGR_PLLI2SR) >>
                   POSITION_VAL(RCC_PLLSAICFGR_PLLSAIR));

      __HAL_RCC_PLLSAI_CONFIG(periph_clk_init->PLLSAI.PLLSAIN , tmp_reg0,
           periph_clk_init->PLLSAI.PLLSAIQ, tmp_reg1);

      __HAL_RCC_PLLSAI_CLKDIVQ_CFG(periph_clk_init->PLLSAIDivQ);
    }
    else
    {
     /* Does nothing */
    }

    /*hdulibstm32f7xxhalrccex-HalRccExPeriphCLKConfig-DB-LLR-035*/
    /*In Case of PLLSAI is selected as source clock for CLK48 */
    /* In Case of PLLI2S is selected as source clock for CK48 */
    if((RCC_PERIPHCLK_CLK48 == ((periph_clk_init->PeriphClockSelection) & RCC_PERIPHCLK_CLK48))
         && (RCC_CLK48SOURCE_PLLSAIP == periph_clk_init->Clk48ClockSelection))
    {
      /*
       * Read PLLSAIQ and PLLSAIR value from PLLSAICFGR register (this value is not
       * needed for CK48 configuration)
       */
      tmp_reg0 = ((RCC->PLLSAICFGR & RCC_PLLSAICFGR_PLLSAIQ) >>
                  POSITION_VAL(RCC_PLLSAICFGR_PLLSAIQ));
      tmp_reg1 = ((RCC->PLLSAICFGR & RCC_PLLSAICFGR_PLLSAIR) >>
                  POSITION_VAL(RCC_PLLSAICFGR_PLLSAIR));

      /* Configure the PLLSAI division factors */
      /* 48CLK = f(PLLSAI clock output) = f(VCO clock) / PLLSAIP */
      __HAL_RCC_PLLSAI_CONFIG(periph_clk_init->PLLSAI.PLLSAIN , periph_clk_init->PLLSAI.PLLSAIP,
                              tmp_reg0, tmp_reg1);
    }
    else
    {
     /* Does nothing */
    }

    /*hdulibstm32f7xxhalrccex-HalRccExPeriphCLKConfig-DB-LLR-036*/
    /*- LTDC configuration -*/
    if((RCC_PERIPHCLK_LTDC) == ((periph_clk_init->PeriphClockSelection) & RCC_PERIPHCLK_LTDC))
    {
      /*
       * Read PLLSAIP and PLLSAIQ value from PLLSAICFGR register (these value are not
       * needed for LTDC configuration)
       */
      tmp_reg0 = ((RCC->PLLSAICFGR & RCC_PLLSAICFGR_PLLSAIQ) >>
                  POSITION_VAL(RCC_PLLSAICFGR_PLLSAIQ));
      tmp_reg1 = ((RCC->PLLSAICFGR & RCC_PLLSAICFGR_PLLSAIP) >>
                  POSITION_VAL(RCC_PLLSAICFGR_PLLSAIP));

      __HAL_RCC_PLLSAI_CONFIG(periph_clk_init->PLLSAI.PLLSAIN , tmp_reg1, tmp_reg0,
                              periph_clk_init->PLLSAI.PLLSAIR);

      __HAL_RCC_PLLSAI_CLKDIVR_CFG(periph_clk_init->PLLSAIDivR);
    }
    else
    {
     /* Does nothing */
    }
    /*hdulibstm32f7xxhalrccex-HalRccExPeriphCLKConfig-DB-LLR-037*/
    /* Enable PLLSAI Clock */
    __HAL_RCC_PLLSAI_ENABLE();

    /* Get Start Tick*/
    tick_start = HALGetTick();

    /* Wait till PLLSAI is ready */
    while(RESET == __HAL_RCC_PLLSAI_GET_FLAG())
    {
      if((HALGetTick() - tick_start) > PLLSAI_TIMEOUT_VALUE)
      {
        /* return in case of Timeout detected */
        return HAL_TIMEOUT;
      }
      else
      {
       ;
      }
    }
  }
  /*hdulibstm32f7xxhalrccex-HalRccExPeriphCLKConfig-DB-LLR-038*/
  return HAL_OK;
}



