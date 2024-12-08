/*
 ******************************************************************************
 * License Information  :  Howell Instruments, Inc.                           *
 *                         "Licensed Software" and "All rights reserved".     *
 ******************************************************************************
 *  File                : hdudispfwdog.c
 *
 *  Description         : This file provides Routines for accessing the watch dog timer.
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
 *  Author(s)           : Shruthi MN
 *
 *  Version History     :
 * <Version No.>     <Author>          <Date>         <Problem Report No.>
 *
 *      1.1          Shruthi MN       15-Oct-2017             100083
 *
 * Additional References : None
 *
 ******************************************************************************
 */


#include "hdudispfwdog.h"            /* Watch dog timer declarations */

#define WATCHDOG_FREQ_KHZ_SCALE   1000U
#define GET_PRESCALER_4_FOR_WD    4U

T_IWDG_HANDLE_TYPE Wdog_handle ={0};
/*
 * Function                : WdogInit
 *
 * Description             : This function calculates the reload value for the
 *                           independent watchdog timer,initialize the prescaler divider to 64,
 *                           write reload value to the reload register,enable the watchdog
 *                           register and reload watchdog counter
 *
 * Formal parameter(s)     : None
 *
 * Return Value            : None
 *
 * Assumption              : None
 *
 */
void WdogInit(void)
{

   /*hdudispfwdog-WdogInit-DB-LLR-001*/
   /* calculate the reload value for the independent watchdog timer */
   Wdog_handle.Init.Reload =
   (WDOG_TIMEOUT_MS * WDOG_FREQ) / (WATCHDOG_FREQ_KHZ_SCALE *
   (GET_PRESCALER_4_FOR_WD << WDOG_PRESCALER));
   /* The maximun of the reload value is 0x0FFF */

   if (Wdog_handle.Init.Reload > MAX_RELOAD_VALUE)
   {
   /*hdudispfwdog-WdogInit-DB-LLR-002*/
   Wdog_handle.Init.Reload = MAX_RELOAD_VALUE;
   }
   else
   {
   ;
   }

   /*hdudispfwdog-WdogInit-DB-LLR-003*/
   /* Initialize the prescaler divider to 64 */
   Wdog_handle.Init.Prescaler = WDOG_PRESCALER;

   /*hdudispfwdog-WdogInit-DB-LLR-003*/
   Wdog_handle.Init.Window = IWDG_WINR_WIN;

   /*hdudispfwdog-WdogInit-DB-LLR-004*/
   /* Enable watchdog timer */
   HalIwdgInit(&Wdog_handle);

   /*hdudispfwdog-WdogInit-DB-LLR-005*/
   /* Reload watchdog counter */
   HalIwdgRefresh(&Wdog_handle);

}

/*
 * Function                : WdogKickWatchDog
 *
 * Description             : This function reloads watchdog counter
 *
 * Formal parameter(s)     : None
 *
 * Return Value            : None
 *
 * Assumption              : None
 *
 */
void WdogKickWatchDog (void)
{

   /*eiuwdog-WdogKickWatchDog-DB-LLR-001*/
   /* Reload watchdog counter */
   HalIwdgRefresh(&Wdog_handle);

}
