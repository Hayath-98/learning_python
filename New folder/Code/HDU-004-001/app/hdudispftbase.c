/*
 ******************************************************************************
 * License Information  :  Howell Instruments, Inc.                           *
 *                         "Licensed Software" and "All rights reserved".     *
 ******************************************************************************
 *  File                : hdudispftbase.c
 *
 *  Description         : The file provides tbase functionalities
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
 * <Version No.>     <Author>          <Date>         <Problem Report No.>
 *
 *      1.1          Shilpa A R      13-Sep-2017             100064
 *      1.2          Shruthi M N     30-Oct-2017             100104
 *      1.3          Rona B S        23-Mar-2018             100196
 *
 * Additional References : None
 *
 ******************************************************************************
 */

#include "hdudispfdemo.h"     /* contains prototypes of DEMO code. */
#include "hdudispfa429.h" /* provides a429 functionalities */
#include "hdudispfinit.h"/*create and schedule init task*/
#include "hdudispfpoller.h"/*declarations for engine information system poller.*/
#include "hdudispfresource.h"/* provides resources */
#include "hdudispftbase.h" /* provides tbase functionalites */
#include "hdudispfucos.h"/* provides ucos functionalities */
#include "hdulibbasictypes.h" /* provides basic datatypes */
#include "hdudispfcbit.h"      /* contains prototypes for CBIT test. */

#define IDLE_100PCNT 2105U
#define CTR_RESET    40U
#define DEC_100      100U

volatile T_UINT16 U16_pcnt_idle = 0;
static T_ULONG Ul_temp_os_idle_ctr = 0;

/*
 * Function                : HalSystickCallback
 *
 * Description             : The function enter and exits interrupt service routine,
 *                           update time tick, signal poller and init task,
 *                           calculate CPU idle time
 *
 * Formal parameter(s)     : None
 *
 * Return Value            : None
 *
 * Assumption              : None
 *
 */

void HalSystickCallback(void)
{
   /*hdudispftbase-HalSystickCallback-DB-LLR-001*/
   static T_UINT16 u16_ctr = DEC_100;

   /*hdudispftbase-HalSystickCallback-DB-LLR-002*/
   /* Make uCos calls if initialization has completed. */
   if (FALSE != Init_b_done)
   {
      /* Tell uCOS that we are entering the ISR */
      OsIntEnter();

      /* Update time tick */
      OsTimeTick();

      PollerSignalTask();

      InitSignalTask();
      CbitSignalTask();
      DemoSignalTask();

      u16_ctr =(T_UINT16)( u16_ctr - ONE);

      /*   Recalculate percent CPU idle 10 times per second.  */
      if(ZERO == u16_ctr)
      {
        Ul_temp_os_idle_ctr =  Os_idle_ctr;
        Ul_temp_os_idle_ctr *= DEC_100;
        U16_pcnt_idle = (T_UINT16)(Ul_temp_os_idle_ctr/IDLE_100PCNT);
        Os_idle_ctr = ZERO;
        u16_ctr = CTR_RESET;
      }
      else
      {
        ;/*Do nothing*/
      }

      /* Tell uCOS that we are leaving the ISR */
      OsIntExit();
   }
   else
   {
      /*hdudispftbase-HalSystickCallback-DB-LLR-003*/
      ;/*Do nothing*/
   }
}


