/*
 ******************************************************************************
 * License Information  :  Howell Instruments, Inc.                           *
 *                         "Licensed Software" and "All rights reserved".     *
 ******************************************************************************
 *  File                : hdudispbpwm.c
 *
 *  Description         : This file maintains the pulse width modulation channels which
 *                                  control display and bezel backlight brightness.
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
 * <Version No.>     <Author>          <Date>         <Problem Report No.>
 *
 *      1.1          Ajay J G        02-Aug-2017             -
 *      1.2          Divya G P       02-Sep-2017       100028
 *
 * Additional References : None
 *
 ******************************************************************************
 */
#include "hdulibstm32f7xxhal.h"    /* Header files for HAL driver*/
#include "hdulibbasictypes.h"            /* Basic data types.*/
#include "hdulibstm32f7xxhaltim.h"    /* Header files for TIM driver*/
#include "hdulibstm32f7xxhalgpio.h"    /* Header files for Gpio driver*/
#include "hdulibstm32f7xxhalrccex.h"   /* Header files for RCC EX HAL module*/
#include "hdulibstm32hallegacy.h"  /* Aliases definition for the STM32Cube HAL constants*/
#include "hdudispbpanel.h"                /* Contains functions prototypes of hdudispbpanel*/

/* Timer handle for timer #2 */
static  T_TIM_HANDLE     Tim2_handle = {ZERO};

/* Timer handle for timer #3 */
static T_TIM_HANDLE      Tim3_handle = {ZERO};

/* Timer handle for timer #5 */
static T_TIM_HANDLE      Tim5_handle = {ZERO};

/* Timer Output Compare Configuration Structure declaration */
static T_TIM_OC_INIT  S_pwm_config = {ZERO};

/* Port pin definition.       */
static T_GPIO_INIT   Gpio_init_struct = {ZERO};

/* Private function prototypes */
static void ErrorHandler(void);

/* Bring the input down to approximately 2.5 MHz.*/
#define TIM2_PRESCALER  (T_INT16)(216/5)
/* Set the period for 10000 = 100 %.*/
#define TIM2_PERIOD  10000
/* Set the initial pulse width to 0%.*/
#define TIM2_INIT_DC 0

#define TIM5_PERIOD     5000
#define TIM5_INIT_DC    500
T_INT32  S32_present_pcnt = ONE_HUNDRED;

/*
 * Function                :  PwmLcdBackLightPcnt
 *
 * Description             :  This function controls the PWM duty cycles of
 *                            Timer #2 Channel 3 Drives "BCL PWM" on PA2.
 *                            Timer #5  Channel 4 Drives "BLC APWM" on PA3.
 *
 * Formal parameter(s)     :  T_UINT32 u32_pcnt_onx1000 - IN The desired duty percent x 1000.
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */
void PwmLcdBackLightPcnt(T_UINT32 u32_pcnt_onx1000)
{
   T_INT32 u16_timer2_duty = ZERO;
   T_INT32 u16_timer12_duty = ZERO;

   /*hdudispbpwm-PwmLcdBackLightPcnt-DB-LLR-001*/
   /* set S32_present_pcnt to u32_pcnt_onx1000 */
   S32_present_pcnt = (T_INT32)u32_pcnt_onx1000;

   if(S32_present_pcnt > TIM2_PERIOD)
   {
      /*hdudispbpwm-PwmLcdBackLightPcnt-DB-LLR-002*/
      /* Set timer 12 to TIM2_PERIOD */
      u16_timer12_duty = TIM2_PERIOD;
      /* Set timer 2 to TIM5_PERIOD * S32_present_pcnt/ONE_LAKH */
      u16_timer2_duty = (TIM5_PERIOD * S32_present_pcnt/ONE_LAKH);
   }
   else
   {
      /*hdudispbpwm-PwmLcdBackLightPcnt-DB-LLR-003*/
      /* Set timer 2 to TIM5_INIT_DC */
      u16_timer2_duty = TIM5_INIT_DC;
      /* Set timer 12 to S32_present_pcnt */
      u16_timer12_duty = S32_present_pcnt;
   }
   /*hdudispbpwm-PwmLcdBackLightPcnt-DB-LLR-004*/
   /* Set CCR3 of TIM2 to timer 12 */
   TIM2->CCR3 = (T_UINT32)u16_timer12_duty;
   /* Set CCR4 of TIM5 to timer 2 */
   TIM5->CCR4  = (T_UINT32) u16_timer2_duty;
}

/*
 * Function                :  PwmInit
 *
 * Description             :  Configure the three PWM modulation channels that drive
 *                            back lights.
 *                            Timer #2 Channel 3 Drives "BCL PWM" on PA2.
 *                            Timer #3 Channel 1 Drives "Bezel PWM" on PA6.
 *                            Timer #5  Channel 4 Drives "BLC APWM" on PA3.
 *
 *                            The frequency of TIM2 & TIM3 PWM will be set to approximately
 *                            250 Hz (to keep power dissipation down in the switching
 *                            transistor).  The counter reload value will be
 *                            10,000 ( = 100.00%).
 *
 *                            The frequency of TIM5 will be set to approximately 40 KHz
 *                            (per Data Sheet).  TIM2 will perform dimming down to
 *                            10%.  That will reduce current switching by the
 *                            primary PWM reducing stress on the power supply and
 *                            the switching transistor.
 *
 * Formal parameter(s)     :  None
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */
void PwmInit(void)
{
   /*hdudispbpwm-PwmInit-DB-LLR-001*/
   /* Enable Timer 2 Clock.   */
   __HAL_RCC_TIM2_CLK_ENABLE();

   /*hdudispbpwm-PwmInit-DB-LLR-002*/
   /* Configure TIM2  */
   Tim2_handle.Instance           = TIM2;
   Tim2_handle.Init.Prescaler        = TIM2_PRESCALER;
   Tim2_handle.Init.Period        = TIM2_PERIOD;
   Tim2_handle.Init.ClockDivision    =  ZERO;
   Tim2_handle.Init.CounterMode      = TIM_COUNTERMODE_UP;
   if(HalTimPwmInit(&Tim2_handle) != HAL_OK)
   {
      /* Initialization Error */
      ErrorHandler();
   }
   else
   {
      ;
   }
   /*hdudispbpwm-PwmInit-DB-LLR-003*/
   /* Configure PWM channel1 (BLC PWM) */
   /* Common configuration for all channels */
   S_pwm_config.OCMode      = TIM_OCMODE_PWM1;
   S_pwm_config.OCFastMode  = TIM_OCFAST_DISABLE;
   S_pwm_config.OCPolarity  = TIM_OCPOLARITY_HIGH;
   S_pwm_config.OCNPolarity = TIM_OCNPOLARITY_LOW;
   S_pwm_config.Pulse       = TIM2_INIT_DC;
   if(HalTimPwmConfigChannel(&Tim2_handle, &S_pwm_config, TIM_CHANNEL_3) != HAL_OK)
   {
      /* Configuration Error */
      ErrorHandler();
   }
   else
   {
      ;
   }

   /*hdudispbpwm-PwmInit-DB-LLR-004*/
   /* Start PWM signals generation */
   /* Start channel 1 */
   if(HalTimPwmStart(&Tim2_handle, TIM_CHANNEL_3) != HAL_OK)
   {
      /* Starting Error */
      ErrorHandler();
   }
   else
   {
      ;
   }
   /*hdudispbpwm-PwmInit-DB-LLR-005*/
   /*  Configure the IO port to support PWM.  */

   /*  Enable Port A clock. */
   __HAL_RCC_GPIOA_CLK_ENABLE();

   Gpio_init_struct.Mode =  GPIO_MODE_AF_PP;
   Gpio_init_struct.Pull =  GPIO_PULLUP;
   Gpio_init_struct.Speed = GPIO_SPEED_HIGH;
   Gpio_init_struct.Alternate = GPIO_AF1_TIM2;
   Gpio_init_struct.Pin = GPIO_PIN_2;
   HalGpioInit(GPIOA, &Gpio_init_struct);

   /*hdudispbpwm-PwmInit-DB-LLR-006*/
   /* Enable Timer 3 Clock.   */
   __HAL_RCC_TIM3_CLK_ENABLE();

   /*hdudispbpwm-PwmInit-DB-LLR-007*/
   /* Configure TIM2  */
   Tim3_handle.Instance          = TIM3;
   Tim3_handle.Init.Prescaler    = TIM2_PRESCALER;
   Tim3_handle.Init.Period       = TIM2_PERIOD;
   Tim3_handle.Init.ClockDivision   = ZERO;
   Tim3_handle.Init.CounterMode     = TIM_COUNTERMODE_UP;
   if(HalTimPwmInit(&Tim3_handle) != HAL_OK)
   {
      /* Initialization Error */
      ErrorHandler();
   }
   else
   {
      ;
   }
   /*hdudispbpwm-PwmInit-DB-LLR-008*/
   /* Configure PWM channel1 (BLC PWM) */
   /* Common configuration for all channels */
   S_pwm_config.OCMode      = TIM_OCMODE_PWM1;
   S_pwm_config.OCFastMode  = TIM_OCFAST_DISABLE;
   S_pwm_config.OCPolarity  = TIM_OCPOLARITY_HIGH;
   S_pwm_config.OCNPolarity = TIM_OCNPOLARITY_LOW;
   S_pwm_config.Pulse       = TIM2_INIT_DC;
   if(HalTimPwmConfigChannel(&Tim3_handle, &S_pwm_config, TIM_CHANNEL_1) != HAL_OK)
   {
      /* Configuration Error */
      ErrorHandler();
   }
   else
   {
      ; /* Do nothing */
   }

   /*hdudispbpwm-PwmInit-DB-LLR-009*/
   /* Start PWM signals generation */
   /* Start channel 1 */
   if(HalTimPwmStart(&Tim3_handle, TIM_CHANNEL_1) != HAL_OK)
   {
      /* Starting Error */
      ErrorHandler();
   }
   else
   {
      ; /* Do nothing */
   }

   /*hdudispbpwm-PwmInit-DB-LLR-010*/
   /* Configure the IO port to support PWM.  */
   Gpio_init_struct.Mode = GPIO_MODE_AF_PP;
   Gpio_init_struct.Pull = GPIO_PULLUP;
   Gpio_init_struct.Speed = GPIO_SPEED_HIGH;
   Gpio_init_struct.Alternate = GPIO_AF2_TIM3;
   Gpio_init_struct.Pin = GPIO_PIN_6;
   HalGpioInit(GPIOA, &Gpio_init_struct);

   /*hdudispbpwm-PwmInit-DB-LLR-011*/
   /* Enable Timer 5 Clock.   */
   __HAL_RCC_TIM5_CLK_ENABLE();

   /*hdudispbpwm-PwmInit-DB-LLR-012*/
   /* Configure TIM5  */
   Tim5_handle.Instance          = TIM5;
   Tim5_handle.Init.Prescaler       = ZERO;
   Tim5_handle.Init.Period       = TIM5_PERIOD;
   Tim5_handle.Init.ClockDivision   = ZERO;
   Tim5_handle.Init.CounterMode     = TIM_COUNTERMODE_UP;
   if(HalTimPwmInit(&Tim5_handle) != HAL_OK)
   {
      /* Initialization Error */
      ErrorHandler();
   }
   else
   {
      ; /* Do nothing */
   }

   /*hdudispbpwm-PwmInit-DB-LLR-013*/
   /* Common configuration for all channels */
   S_pwm_config.OCMode      = TIM_OCMODE_PWM1;
   S_pwm_config.OCFastMode  = TIM_OCFAST_ENABLE;
   S_pwm_config.OCPolarity  = TIM_OCPOLARITY_LOW;
   S_pwm_config.Pulse       = TIM5_INIT_DC;
   if(HalTimPwmConfigChannel(&Tim5_handle, &S_pwm_config, TIM_CHANNEL_4) != HAL_OK)
   {
      /* Configuration Error */
      ErrorHandler();
   }
   else
   {
      ; /* Do nothing */
   }

   /*hdudispbpwm-PwmInit-DB-LLR-014*/
   /* Start PWM signals generation */
   /* Start channel 1 */
   if(HalTimPwmStart(&Tim5_handle, TIM_CHANNEL_4) != HAL_OK)
   {
       /* Starting Error */
       ErrorHandler();
   }
   else
   {
      ; /* Do nothing */
   }

   /*hdudispbpwm-PwmInit-DB-LLR-015*/
   /* Configure the IO port to support PWM.  */
   Gpio_init_struct.Mode = GPIO_MODE_AF_PP;
   Gpio_init_struct.Pull = GPIO_PULLDOWN;
   Gpio_init_struct.Speed = GPIO_SPEED_HIGH;
   Gpio_init_struct.Alternate = GPIO_AF2_TIM5;
   Gpio_init_struct.Pin = GPIO_PIN_3;
   HalGpioInit(GPIOA, &Gpio_init_struct);

   /*hdudispbpwm-PwmInit-DB-LLR-016*/
   PwmLcdBackLightPcnt(SIXTY_THOUSAND);
}

/*
 * Function                :  ErrorHandler
 *
 * Description             :  This function is used to perform error handling and
 *                            enters infinite loop.
 *
 * Formal parameter(s)     :  None
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */
static void ErrorHandler(void)
{
   /*hdudispbpwm-ErrorHandler-DB-LLR-001*/
   while (ONE)
   {
      ; /* Do nothing*/
   }
}
