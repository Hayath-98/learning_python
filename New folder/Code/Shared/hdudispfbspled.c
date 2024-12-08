/*
 ******************************************************************************
 * License Information  :  Howell Instruments, Inc.                           *
 *                         "Licensed Software" and "All rights reserved".     *
 ******************************************************************************
 *  File                : hdudispfbspled.c
 *
 *  Description         : This file contains Engine Information System application
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
 *      1.1           Shilpa A R          24-Jul-2017             100064
 *      1.2           Vinay H             09-Oct-2017             100064
 *      1.3           Rona B.S            11-Oct-2017             100064
 *
 * Additional References : None
 *
 ******************************************************************************
 */
#include "hdudispfresource.h"  /* provides central location to use On Chip Peripherals*/
#include "hdulibstm32f7xxhalconf.h"  /* provides HAL configurations. */
#include "hdudispfbspled.h"  /* contains LED init and and toggling functions */
#include "hdulibstm32hallegacy.h" /* definition for the STM32Cube HAL */
#include "hdulibstm32f7xxhalgpio.h" /* Defines GPIO configurations */

/*
 * Function                :  BSPLEDInit
 *
 * Description             :  This function initializes the  BSP LED  based on
 *                             the input Led number.
 *
 * Formal parameter(s)     :  T_ELED_NUM e_led_num - IN Input Led Number
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */

void  BSPLEDInit(T_ELED_NUM e_led_num)
{
   T_GPIO_INIT   led1_gpio_initstruct = {0};
   if( LED1 == e_led_num)
   {
      /*hdudispfbspled-BSPLEDInit-DB-LLR-001*/
      LED1_CLK_ENABLE();
      led1_gpio_initstruct.Pin = LED1_PIN;
      led1_gpio_initstruct.Mode = GPIO_MODE_OUTPUT_PP;
      led1_gpio_initstruct.Speed = GPIO_SPEED_FAST;
      led1_gpio_initstruct.Pull = GPIO_NOPULL;
      HalGpioInit(LED1_PORT, &led1_gpio_initstruct);
   }
   else
   {
      ; /*Does nothing*/
   }
}

/*
 * Function                :  BSPLEDToggle
 *
 * Description             :  This function function toggles the BSP LED based on input
 *                             LED number.
 *
 * Formal parameter(s)     :  T_ELED_NUM e_led_num - IN Input Led Number
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */
void  BSPLEDToggle(T_ELED_NUM e_led_num)
{
   if(LED1 == e_led_num)
   {
      /*hdudispfbspled-BSPLEDToggle-DB-LLR-001*/
      HALGpioTogglePin(LED1_PORT, LED1_PIN);
   }
   else
   {
      ; /*Does nothing*/
   }
}
