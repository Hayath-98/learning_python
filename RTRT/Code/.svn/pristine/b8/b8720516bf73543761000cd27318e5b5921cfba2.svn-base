/*
 ******************************************************************************
 * License Information  :  Howell Instruments, Inc.                           *
 *                         "Licensed Software" and "All rights reserved".     *
 ******************************************************************************
 *  File                : hdudispftimer.c
 *
 *  Description         : This file is used to allocate storage for pointers to Timers,
 *                        install pointers in that storage, and increment the Timers
 *                        pointed to by those pointers.
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
 *      1.1          Vinay H         14-Sep-2017             100064
 *      1.2          Shilpa A R      09-Oct-2017             100064
 *
 * Additional References : None
 *
 ******************************************************************************
 */

#include "hdudispfrterror.h"         /* Provides stub routine for run time errors.*/
#include "hdudispftimer.h"         /* Consistency Check*/
#include "hdudispfucos.h"          /* Need OS_ENTER_CRITICAL and OS_EXIT_CRITICAL. */
#include "hdulibbasictypes.h"    /* Contains basic header definations */

#define NUMBER_OF_TIMERS 200U    /* Number of available timers.*/

volatile T_TIMER *Timers [NUMBER_OF_TIMERS + 1] = {ZERO};
static T_INT16    First_call = TRUE;

/* FUNCTIONS   */

/**********************************************************************************/
/*                           Function Definition                                  */
/**********************************************************************************/
/*
 *
 * Function                : TimerInstall
 *
 * Description             : This routine receives a pointer to an unsigned integer
 *                           and then increments that timer each time timer_isr is called.
 *
 * Formal parameter(s)     : volatile T_TIMER *timer -OUT pointer to the timer to install.
 *
 * Return Value            : None
 *
 * Assumption              : None
 *
 */

void TimerInstall (volatile T_TIMER *timer)
{
   volatile T_TIMER  **timer_ptr = (void *)ZERO;
   T_UINT16          index = ZERO;

   static T_CHAR param_message[] = "Too many Timers.";
   T_CHAR file_name[] = __FILE__;

   /*hdudispftimer-TimerInstall-DB-LLR-001*/
   OS_ENTER_CRITICAL();

   /*hdudispftimer-TimerInstall-DB-LLR-002*/
   if (First_call != ZERO)
   {
      Timers[0] = (T_TIMER *)ZERO;
      First_call = FALSE;
   }
   else
   {
      ; /*Do nothing*/
   }
   /*hdudispftimer-TimerInstall-DB-LLR-003*/
   OS_EXIT_CRITICAL();

   for (timer_ptr = Timers, index = ZERO; index < NUMBER_OF_TIMERS; index++, timer_ptr++)
   {
      /*hdudispftimer-TimerInstall-DB-LLR-004*/
      OS_ENTER_CRITICAL();

      /*hdudispftimer-TimerInstall-DB-LLR-005*/
      if ((T_TIMER *)ZERO == *timer_ptr)
      {
         *(timer) = ZERO;
         *(timer_ptr + ONE) = (T_TIMER *)ZERO;
         *timer_ptr = timer;
         OS_EXIT_CRITICAL();

         return;
      }
      else
      {
         ;/*Do nothing*/
      }
      /*hdudispftimer-TimerInstall-DB-LLR-006*/
      OS_EXIT_CRITICAL();
   }
   /*hdudispftimer-TimerInstall-DB-LLR-007*/
   RterrWidget((T_CHAR *)&file_name,__LINE__, (T_CHAR *) &param_message);
}

/*
 *
 * Function                : TimerDriver
 *
 * Description             : Increments all installed Timers.
 *
 * Formal parameter(s)     : None
 *
 * Return Value            : None
 *
 * Assumption              : None
 *
 */

void TimerDriver(void)
{
   volatile T_TIMER **timer_ptr = {ZERO};

   /*hdudispftimer-TimerDriver-DB-LLR-001*/
   if(First_call != ZERO)
   {
      return;
   }
   else
   {
      ;/* Do nothing*/
   }
   /*hdudispftimer-TimerDriver-DB-LLR-002*/
   for (timer_ptr = Timers; *timer_ptr != (T_TIMER *)ZERO; **timer_ptr+=ONE,timer_ptr++);
   {
      ;
   }
}

/*
 *
 * Function                : TimerReset
 *
 * Description             : Resets the given timer.
 *
 * Formal parameter(s)     : volatile T_TIMER *timer - OUT pointer to the timer to reset.
 *
 * Return Value            : None
 *
 * Assumption              : None
 *
 */

void TimerReset(volatile T_TIMER *timer)
{
   /*hdudispftimer-TimerReset-DB-LLR-001*/
   OS_ENTER_CRITICAL();

   /*hdudispftimer-TimerReset-DB-LLR-002*/
   *timer = ZERO;

   /*hdudispftimer-TimerReset-DB-LLR-003*/
   OS_EXIT_CRITICAL();
}

/*
 *
 * Function                : TimerPreset
 *
 * Description             : Sets the given timer 0.
 *
 * Formal parameter(s)     : volatile T_TIMER *timer -OUT pointer to the timer to reset.
 *                           T_INT32 s32_set_val  -IN Value to be set to
 *
 * Return Value            : None
 *
 * Assumption              : None
 *
 */

void TimerPreset(volatile T_TIMER *timer, T_INT32 s32_set_val)
{
   /*hdudispftimer-TimerPreset-DB-LLR-001*/
   OS_ENTER_CRITICAL();

   /*hdudispftimer-TimerPreset-DB-LLR-002*/
   *timer = (T_TIMER)s32_set_val;

   /*hdudispftimer-TimerPreset-DB-LLR-003*/
   OS_EXIT_CRITICAL();
}

