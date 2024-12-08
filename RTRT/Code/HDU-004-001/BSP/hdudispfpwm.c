/*
 ******************************************************************************
 * License Information  :  Howell Instruments, Inc.                           *
 *                         "Licensed Software" and "All rights reserved".     *
 ******************************************************************************
 *  File                : hdudispfpwm.c
 *
 *  Description         : This file maintains the pulse width modulation channels which
 *                         control display and bezel backlight brightness.
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
 *      1.1           Shilpa A R       13-Sep-2017             100064
 *      1.2           Akshatha H       10-Oct-2017             100064
 *      1.3           Shruthi M N      15-Oct-2017             100083
 *      1.4           Shruthi M N      30-Oct-2017             100104
 *      1.5           Divya G P        09-Nov-2017             100164
 *      1.6            Rona B S        05-Jul-2020             100259
 *      1.7          Dhanalakshmi      12-Sep-2020             100276  
 *
 * Additional References : None
 *
 ******************************************************************************
 */

#include "hdudispfglobalsettings.h" /* defines global settings functionalities */
#include "hdudispfpolygon1.h" /* implements the polygon fill.*/
#include "hdudispfpwm.h" /*maintains the pulse width modulation channels*/
#include "hdudispfstmadc.h" /*declares the internal ADC and polls for conversion*/
#include "hdudispftimer.h" /* Defines the timer functionalities */
#include "hdulibstm32f7xxhalrccex.h" /* Defines RCC configurations */
#include "hdulibstm32f7xxhaltim.h"/* Defines Timer configurations */
#include "hdulibstm32f7xxhalgpio.h" /* Defines GPIO configurations */
#include "hdulibstm32f7xxhal.h" /* Header files for HAL driver*/
#include "hdudispflookup.h" /*defines the lookup tables*/
#include "hdudispfparams.h"/*tags for various parameters and parameter units.*/
#include "hdulibstm32hallegacy.h"/*definition for the STM32Cube HAL constants*/
#include "hdudispfpanel.h"   /* Contains functions prototypes of panel.*/

/* counter */
static T_INT32 S32_present_pcnt1 = 100;

 /* Updated as per PR100083*/
static  T_INT32 Photo_adc[] =
{
   2,
   20, 2048, 4096
};

 /* Updated as per PR100083*/
static  T_INT32 Photo_read[] =
{
   2,
   15, 10000
};

const T_LOOKUP_TABLE Photo_table =
{
   Photo_adc,
   Photo_read
};
/* PWM CODE FOR TIMER 12 CH 1 and TIMER 2 CH 1.  (Display Back Light primary). */

/* Timer handle for timer #2 */
static T_TIM_HANDLE   Tim2_handle = {ZERO};

/* Timer handle for timer #3 */
static T_TIM_HANDLE   Tim3_handle = {ZERO};

/* Timer handle for timer #5 */
static T_TIM_HANDLE   Tim5_handle = {ZERO};

/* Timer Output Compare Configuration Structure declaration */
static T_TIM_OC_INIT  S_pwm_config = {ZERO};

/* Port pin definition.       */
static T_GPIO_INIT   Gpio_init_struct = {ZERO};

/* mSec timer for back light dimming.  */
static T_INT32 S32_back_light_timer = ZERO;

/* Private function prototypes */
static void ErrorHandler(void);

/*
 *Note: Initial duty cycles should be minimum (0.1%).  If these numbers
 *          are changed, revisit PwmLcdBackLightPcnt below.
 */
/* TIMER #2 CONSTANTS.*/
/* Bring the input down to approximately 2.5 MHz. */
#define TIM2_PRESCALER  (T_INT16)(216/5)
/* Set the period for 10000 = 100 %. */
#define TIM2_PERIOD     10000U
/* Set the initial pulse width to 0%.  */
#define TIM2_INIT_DC    0U
#define POINT_FIVE_PERCNT  50U

/* TIMER #5 CONSTANTS.*/
#define TIM5_PERIOD     5000U
#define TIM5_INIT_DC    500U

#define ZERO           0U
#define DELAY_DSTB    -200

#define DEC_64         64U
#define DEC_500        500U
#define DEC_100K       100000U

/*
 * Function                :  PwmInit
 *
 * Description             :  This function configures the three PWM(pulse width modulation)
 *                                         channels that drive back lights.
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
   /*TIMER #2 INIIT  BLPWM  */
   /* Enable Timer 2 Clock.   */
   /*hdudispfpwm-PwmInit-DB-LLR-001*/
   __HAL_RCC_TIM2_CLK_ENABLE();

   /* Configure TIM2  */
   /*hdudispfpwm-PwmInit-DB-LLR-002*/
   Tim2_handle.Instance           = TIM2;
   Tim2_handle.Init.Prescaler  = TIM2_PRESCALER;
   Tim2_handle.Init.Period        = TIM2_PERIOD;
   Tim2_handle.Init.ClockDivision = ZERO;
   Tim2_handle.Init.CounterMode      = TIM_COUNTERMODE_UP;

   /*hdudispfpwm-PwmInit-DB-LLR-003*/
   if(HalTimPwmInit(&Tim2_handle) != HAL_OK)
   {
      /* Initialization Error */
      ErrorHandler();
   }
   else
   {
      ;/* Does nothing */
   }

   /*hdudispfpwm-PwmInit-DB-LLR-004*/
   /* Configure PWM channel1 (BLC PWM) */
   /* Common configuration for all channels */
   S_pwm_config.OCMode      = TIM_OCMODE_PWM1;
   S_pwm_config.OCFastMode  = TIM_OCFAST_DISABLE;
   S_pwm_config.OCPolarity  = TIM_OCPOLARITY_HIGH;
   S_pwm_config.OCNPolarity = TIM_OCNPOLARITY_LOW;
   S_pwm_config.Pulse       = TIM2_INIT_DC;

   /*hdudispfpwm-PwmInit-DB-LLR-005*/
   if(HAL_OK != HalTimPwmConfigChannel(&Tim2_handle, &S_pwm_config, TIM_CHANNEL_3))
   {
      /* Configuration Error */
      ErrorHandler();
   }
   else
   {
      ;/* Does nothing */
   }

   /*hdudispfpwm-PwmInit-DB-LLR-006*/
   /* Start PWM signals generation */
   /* Start channel 1 */
   if(HAL_OK != HalTimPwmStart(&Tim2_handle, TIM_CHANNEL_3))
   {
      /* Starting Error */
      ErrorHandler();
   }
   else
   {
      ;/* Does nothing */
   }

   /*hdudispfpwm-PwmInit-DB-LLR-007*/
   /*  Configure the IO port to support PWM.  */
   /*  Enable Port A clock. */
   __HAL_RCC_GPIOA_CLK_ENABLE();

   /*hdudispfpwm-PwmInit-DB-LLR-008*/
   Gpio_init_struct.Mode =  GPIO_MODE_AF_PP;
   Gpio_init_struct.Pull =  GPIO_PULLUP;
   Gpio_init_struct.Speed = GPIO_SPEED_HIGH;
   Gpio_init_struct.Alternate = GPIO_AF1_TIM2;
   Gpio_init_struct.Pin = GPIO_PIN_2;
   HalGpioInit(GPIOA, &Gpio_init_struct);

   /*hdudispfpwm-PwmInit-DB-LLR-009*/
   /* TIMER #3 INIT   */
   /* Enable Timer 3 Clock.   */
   __HAL_RCC_TIM3_CLK_ENABLE();

   /*hdudispfpwm-PwmInit-DB-LLR-010*/
   /* Configure TIM3  */
   Tim3_handle.Instance            = TIM3;
   Tim3_handle.Init.Prescaler = TIM2_PRESCALER;
   Tim3_handle.Init.Period       = TIM2_PERIOD;
   Tim3_handle.Init.ClockDivision   = ZERO;
   Tim3_handle.Init.CounterMode     = TIM_COUNTERMODE_UP;

   /*hdudispfpwm-PwmInit-DB-LLR-011*/
   if(HAL_OK != HalTimPwmInit(&Tim3_handle))
   {
      /* Initialization Error */
      ErrorHandler();
   }
   else
   {
      ;/* Does nothing */
   }

   /*hdudispfpwm-PwmInit-DB-LLR-012*/
   /* Configure PWM channel1 (Bezel PWM) */
   /* Common configuration for all channels */
   S_pwm_config.OCMode      = TIM_OCMODE_PWM1;
   S_pwm_config.OCFastMode  = TIM_OCFAST_DISABLE;
   S_pwm_config.OCPolarity  = TIM_OCPOLARITY_HIGH;
   S_pwm_config.OCNPolarity = TIM_OCNPOLARITY_LOW;
   S_pwm_config.Pulse       = TIM2_INIT_DC;

   /*hdudispfpwm-PwmInit-DB-LLR-013*/
   if(HAL_OK != HalTimPwmConfigChannel(&Tim3_handle, &S_pwm_config, TIM_CHANNEL_1))
   {
      /* Configuration Error */
      ErrorHandler();
   }
   else
   {
      ;/* Does nothing */
   }

   /*hdudispfpwm-PwmInit-DB-LLR-014*/
   /* Start PWM signals generation */
   /* Start channel 1 */
   if(HAL_OK != HalTimPwmStart(&Tim3_handle, TIM_CHANNEL_1))
   {
      /* Starting Error */
      ErrorHandler();
   }
   else
   {
      ;/* Does nothing */
   }

   /*hdudispfpwm-PwmInit-DB-LLR-015*/
   /* Configure the IO port to support PWM.  */
   Gpio_init_struct.Mode = GPIO_MODE_AF_PP;
   Gpio_init_struct.Pull = GPIO_PULLUP;
   Gpio_init_struct.Speed = GPIO_SPEED_HIGH;
   Gpio_init_struct.Alternate = GPIO_AF2_TIM3;
   Gpio_init_struct.Pin = GPIO_PIN_6;
   HalGpioInit(GPIOA, &Gpio_init_struct);

   /*hdudispfpwm-PwmInit-DB-LLR-016*/
   /*  TIMER #5 INIT   */
   /*  Enable Timer 5 Clock.   */
   __HAL_RCC_TIM5_CLK_ENABLE();

   /*hdudispfpwm-PwmInit-DB-LLR-017*/
   /* Configure TIM5  */
   Tim5_handle.Instance            = TIM5;
   Tim5_handle.Init.Prescaler = ZERO;
   Tim5_handle.Init.Period       = TIM5_PERIOD;
   Tim5_handle.Init.ClockDivision   = ZERO;
   Tim5_handle.Init.CounterMode     = TIM_COUNTERMODE_UP;

   /*hdudispfpwm-PwmInit-DB-LLR-018*/
   if(HAL_OK != HalTimPwmInit(&Tim5_handle))
   {
      /* Initialization Error */
      ErrorHandler();
   }
   else
   {
      ;/* Does nothing */
   }

   /*hdudispfpwm-PwmInit-DB-LLR-019*/
   /* Common configuration for all channels */
   S_pwm_config.OCMode      = TIM_OCMODE_PWM1;
   S_pwm_config.OCFastMode  = TIM_OCFAST_ENABLE;
   S_pwm_config.OCPolarity  = TIM_OCPOLARITY_LOW;
   S_pwm_config.Pulse       = TIM5_INIT_DC;

   /*hdudispfpwm-PwmInit-DB-LLR-020*/
   if(HAL_OK != HalTimPwmConfigChannel(&Tim5_handle, &S_pwm_config, TIM_CHANNEL_4))
   {
      /* Configuration Error */
      ErrorHandler();
   }
   else
   {
      ;/* Does nothing */
   }

   /*hdudispfpwm-PwmInit-DB-LLR-021*/
   /* Start PWM signals generation */
   /* Start channel 1 */
   if(HAL_OK != HalTimPwmStart(&Tim5_handle, TIM_CHANNEL_4))
   {
      /* Starting Error */
      ErrorHandler();
   }
   else
   {
      ;/* Does nothing */
   }

   /*hdudispfpwm-PwmInit-DB-LLR-022*/
   /* Configure the IO port to support PWM.  */
   Gpio_init_struct.Mode = GPIO_MODE_AF_PP;
   Gpio_init_struct.Pull = GPIO_PULLDOWN;
   Gpio_init_struct.Speed = GPIO_SPEED_HIGH;
   Gpio_init_struct.Alternate = GPIO_AF2_TIM5;
   Gpio_init_struct.Pin = GPIO_PIN_3;
   HalGpioInit(GPIOA, &Gpio_init_struct);

   /* Init the mSec back light dimming timer.*/
   TimerInstall((T_UINT32 *)&S32_back_light_timer);

   /* Delay for 0.2 sec for display to stabilize.*/
   S32_back_light_timer = DELAY_DSTB;
}

/*
 * Function                :  ErrorHandler
 *
 * Description             :  This function Handles the error.
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
   /*hdudispfpwm-ErrorHandler-DB-LLR-001*/
   while (TRUE)
   {
      ;/*Do nothing*/
   }
}

/*
 * Function                :  PwmLcdBackLightPcnt
 *
 * Description             :  This function controls the PWM duty cycles of
 *                                         Timer #2 Channel 3 Drives "BCL PWM" on PA2.
 *                                         Timer #5  Channel 4 Drives "BLC APWM" on PA3.
 *
 * Formal parameter(s)     :  T_UINT32 u32_pcnt_onx1000 - INOUT  desired duty percent x 1000
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */

void PwmLcdBackLightPcnt(T_UINT32 u32_pcnt_onx1000)
{
   static T_INT32 s32_target_pcnt = 100;
   T_INT32  s32_temp = ZERO;
   T_UINT16 u16_timer2_duty = ZERO;
   T_UINT16 u16_timer12_duty = ZERO;

   /* Limit target value to [0.05% to 100%] */
   if(u32_pcnt_onx1000 > DEC_100K)
   {
      /*hdudispfpwm-PwmLcdBackLightPcnt-DB-LLR-001*/
      u32_pcnt_onx1000 = DEC_100K;
   }
   else if(u32_pcnt_onx1000 < POINT_FIVE_PERCNT)
   {
      /*hdudispfpwm-PwmLcdBackLightPcnt-DB-LLR-002*/
      u32_pcnt_onx1000 = POINT_FIVE_PERCNT;
   }
   else
   {
      ;/* Does nothing */
   }

   /*hdudispfpwm-PwmLcdBackLightPcnt-DB-LLR-003*/
   s32_target_pcnt = (T_INT32) u32_pcnt_onx1000;

   /* Step from present to target in 1/64 increments. */
   /* Updated as per PR 100083 */
   if(((T_INT32)ZERO) != (s32_temp = ABS(s32_target_pcnt-S32_present_pcnt1)))
   {
      /* Cover the case where Target and Present are close.*/
     /* Updated as per PR 100083 */
      if(s32_temp < ((T_INT32)DEC_64))
      {
         if((s32_target_pcnt-S32_present_pcnt1) > (T_INT32)ZERO)
         {
            /*hdudispfpwm-PwmLcdBackLightPcnt-DB-LLR-004*/
            s32_temp = ONE;
         }
         else
         {
            /*hdudispfpwm-PwmLcdBackLightPcnt-DB-LLR-005*/
            s32_temp = MINUS_ONE;
         }
      }
      else
      {
         /*hdudispfpwm-PwmLcdBackLightPcnt-DB-LLR-006*/
         s32_temp = ((s32_target_pcnt - S32_present_pcnt1) >> SIX );
      }
   }
   else
   {
      /* Does nothing */
   }

   /*hdudispfpwm-PwmLcdBackLightPcnt-DB-LLR-007*/
   S32_present_pcnt1 += s32_temp;

   /*hdudispfpwm-PwmLcdBackLightPcnt-DB-LLR-008*/
   /* Updated as per PR 100083 */
   if(S32_present_pcnt1 > ((T_INT32)TIM2_PERIOD))
   {
      u16_timer12_duty = TIM2_PERIOD;
      u16_timer2_duty = (T_UINT16)(((T_INT32)TIM5_PERIOD * S32_present_pcnt1)/(T_INT32)DEC_100K);
   }
   else
   {
      u16_timer2_duty = DEC_500;
      u16_timer12_duty = (T_UINT16)S32_present_pcnt1;
   }
   
   
   /*hdudispfpwm-PwmLcdBackLightPcnt-DB-LLR-009*/
   if (ONE == Back_light )
   {
	   TIM2->CCR3 = u16_timer12_duty;
	   TIM5->CCR4 = u16_timer2_duty;
   }
   else
   {
	   TIM2->CCR3 = ZERO;
	   TIM5->CCR4 = ZERO;
   }


}

/*
 * Function                :  PwmLcdBezelLightPcnt
 *
 * Description             :  This function controls the PWM duty cycle for the display.
 *                                        Timer #2 Channel 3 Drives "BCL PWM" on PA2.
 *                                        Timer #3 Channel 1 Drives "Bezel PWM" on PA6.
 *                                        Timer #5  Channel 4 Drives "BLC APWM" on PA3.
 *
 * Formal parameter(s)     :  T_UINT16 u16_pcnt_onx100 - IN desired duty percent x 100
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */

void PwmLcdBezelLightPcnt(T_UINT16 u16_pcnt_onx100)
{
   static T_INT16 s16_target_pcnt = ZERO;
   static T_INT16 s16_present_pcnt = ZERO;

   T_INT16  s16_temp = ZERO;

   /* Limit target value to 100%.      */
   if(u16_pcnt_onx100 > TIM2_PERIOD)
   {
      /* hdudispfpwm-PwmLcdBezelLightPcnt-DB-LLR-001*/
      u16_pcnt_onx100 = TIM2_PERIOD;
   }
   else
   {
      /* Does nothing */
   }
   /* hdudispfpwm-PwmLcdBezelLightPcnt-DB-LLR-002*/
   s16_target_pcnt = (T_INT16)u16_pcnt_onx100;

   /* Step from present to target in 1/64 increments. */
   /* Updated as per PR 100083 */
   if(((T_INT16)ZERO) != (s16_temp = (T_INT16)(ABS(s16_target_pcnt-s16_present_pcnt))))
   {
      /* Cover the case where Target and Present are close.*/
      if(s16_temp < ((T_INT16)THIRTY_TWO))
      {
         if((s16_target_pcnt-s16_present_pcnt) > ((T_INT16)ZERO))
         {
          /* hdudispfpwm-PwmLcdBezelLightPcnt-DB-LLR-003*/
            s16_temp = ONE;
         }
         else
         {
          /* hdudispfpwm-PwmLcdBezelLightPcnt-DB-LLR-004*/
            s16_temp = MINUS_ONE;
         }

      }
      else
      {
         /* hdudispfpwm-PwmLcdBezelLightPcnt-DB-LLR-005*/
         s16_temp = (T_INT16)((s16_target_pcnt - s16_present_pcnt) >> FIVE);
      }
   }
   /* hdudispfpwm-PwmLcdBezelLightPcnt-DB-LLR-006*/
   s16_present_pcnt = (T_INT16) (s16_present_pcnt + s16_temp);
   /* hdudispfpwm-PwmLcdBezelLightPcnt-DB-LLR-007*/
   TIM3->CCR1 = (T_UINT32)s16_present_pcnt;
}

/*
 * Function                :  PwmBackLightDriver
 *
 * Description             :  This function updates the duty cycle of the LCD back light
 *
 * Formal parameter(s)     :  None
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */

void PwmBackLightDriver(void)
{
   T_UINT32 u32_pcnt_onx1000 = ZERO;
   T_PARAM_STAT stat = ZERO;

   /*hdudispfpwm-PwmBackLightDriver-DB-LLR-001*/
   /* Only adjust the back light 100 timer per second.   */
   /* Updated as per PR 100083 */
   if(S32_back_light_timer < ((T_INT32)ZERO))
   {
      return;
   }
   else
   {
      ; /* Does nothing */
   }

   /*hdudispfpwm-PwmBackLightDriver-DB-LLR-002*/
   S32_back_light_timer -= (T_INT32)TEN;

   if(EBRIGHTNESS_MANUAL == Brightness_mode)
   {
      /*hdudispfpwm-PwmBackLightDriver-DB-LLR-003*/
      u32_pcnt_onx1000 = ((T_UINT32)Manual_brightness)*TEN;
   }
   else
   {
      /*hdudispfpwm-PwmBackLightDriver-DB-LLR-004*/
      u32_pcnt_onx1000 = (T_UINT32)LookupTableLookup(&Photo_table,
         (T_INT32)S16_adc_reading[0], &stat);
      u32_pcnt_onx1000 = u32_pcnt_onx1000 * ((T_UINT32)Auto_brightness);
      u32_pcnt_onx1000 /= TEN;
   }
   /*hdudispfpwm-PwmBackLightDriver-DB-LLR-005*/
   PwmLcdBackLightPcnt(u32_pcnt_onx1000);

   PwmLcdBezelLightPcnt((T_UINT16)(u32_pcnt_onx1000/TEN));
}

/*
 * Function                :  PwmBackLightStepTo
 *
 * Description             :  This function Eliminate averaging when brightness is adjusted
 *
 * Formal parameter(s)     :  T_INT16 new_auto_brightness - IN holds auto brighness value
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */

void PwmBackLightStepTo(T_INT16 new_auto_brightness)
{
   T_UINT32 u32_pcnt_onx1000 = ZERO;

   if(EBRIGHTNESS_MANUAL == Brightness_mode)
   {
      /*hdudispfpwm-PwmBackLightStepTo-DB-LLR-001*/
      u32_pcnt_onx1000 = ((T_UINT32)Manual_brightness)*TEN;
   }
   else
   {
      /*hdudispfpwm-PwmBackLightStepTo-DB-LLR-002*/
      u32_pcnt_onx1000 = (T_UINT32)((S32_present_pcnt1 * new_auto_brightness)/Auto_brightness);
      Auto_brightness = new_auto_brightness;
   }

   /* Limit target value to [0.05% to 100%]   */
   if(u32_pcnt_onx1000 > DEC_100K)
   {
      /*hdudispfpwm-PwmBackLightStepTo-DB-LLR-003*/
      u32_pcnt_onx1000 = DEC_100K;
   }
   else if(u32_pcnt_onx1000 < POINT_FIVE_PERCNT)
   {
      /*hdudispfpwm-PwmBackLightStepTo-DB-LLR-004*/
      u32_pcnt_onx1000 = POINT_FIVE_PERCNT;
   }
   /*hdudispfpwm-PwmBackLightStepTo-DB-LLR-005*/
   S32_present_pcnt1 = (T_INT32)u32_pcnt_onx1000;
}

/*
 * Function                :  PwmBackLightNewMode
 *
 * Description             :  This function drives the new back light mode.
 *
 * Formal parameter(s)     :  None
 *
 * Return Value            :  T_INT16 new_auto_brightness - IN holds auto brighness value
 *
 * Assumption              :  None
 *
 */
void PwmBackLightNewMode(T_INT16 new_auto_brightness)
{
   T_UINT32 u32_pcnt_onx1000 = ZERO;
   T_PARAM_STAT stat = ZERO;

   if(EBRIGHTNESS_AUTO == Brightness_mode)
   {
      /*hdudispfpwm-PwmBackLightNewMode-DB-LLR-001*/
      u32_pcnt_onx1000 = (T_UINT32)LookupTableLookup(&Photo_table,
         (T_INT32)S16_adc_reading[0], &stat);
      u32_pcnt_onx1000 = (T_UINT32)((T_INT32)u32_pcnt_onx1000 * (T_INT32)new_auto_brightness);
      u32_pcnt_onx1000 /= TEN;

      Auto_brightness = new_auto_brightness;

      /* Limit target value to [0.05% to 100%]     */
      if(u32_pcnt_onx1000 > DEC_100K)
      {
         /*hdudispfpwm-PwmBackLightNewMode-DB-LLR-002*/
         u32_pcnt_onx1000 = DEC_100K;
      }
      else if(u32_pcnt_onx1000 < POINT_FIVE_PERCNT)
      {
         /*hdudispfpwm-PwmBackLightNewMode-DB-LLR-003*/
         u32_pcnt_onx1000 = POINT_FIVE_PERCNT;
      }
   }
   else
   {
      /*hdudispfpwm-PwmBackLightNewMode-DB-LLR-004*/
      u32_pcnt_onx1000 = ((T_UINT32)Manual_brightness)*TEN;
   }
   /*hdudispfpwm-PwmBackLightNewMode-DB-LLR-005*/
   S32_present_pcnt1 = (T_INT32)u32_pcnt_onx1000;
}

/*
 * Function                :  PwmBlink
 *
 * Description             :  This function turns off the back light for 1/10 second.
 *
 * Formal parameter(s)     :  None
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */
void PwmBlink(void)
{
   /*hdudispfpwm-PwmBlink-DB-LLR-001*/
   TIM2->CCR3 = ZERO;
   TIM5->CCR4  = ZERO;
   S32_back_light_timer = (T_INT32)(MINUS_100);
}


