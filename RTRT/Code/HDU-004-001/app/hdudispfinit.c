/*
 ******************************************************************************
 * License Information  :  Howell Instruments, Inc.                           *
 *                         "Licensed Software" and "All rights reserved".     *
 ******************************************************************************
 *  File                : hdudispfinit.c
 *
 *  Description         : Creates and schedules the init task
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
 *      1.1          Vinay H         24-Jul-2017             100064
 *      1.2          Shruthi M N     13-Oct-2017             100083
 *      1.3          Shruthi M N     30-Oct-2017             100104
 *      1.4          Shruthi M N     04-Nov-2017             100113,100147,100156
 *      1.5          Shilpa A R      23-Mar-2018             100196
 *      1.6          Gururaj C       21-Jun-2020             100259
 *      1.7          Rona  B S       29-Jun-2020             100259
 *      1.8          Dhanalakshmi    20-Mar-2021             100331
 *      1.9          Dhanalakshmi    20-Mar-2021             100331
 *
 * Additional References : None
 *
 ******************************************************************************
 */

#include "hdudispfdemo.h"     /* Contains prototype for demo */
#include "hdudispfa429.h"       /* defines the drivers and labels of the a429 */
#include "hdudispfapp.h"        /* contains Engine Information System application */
#include "hdudispfinit.h"       /* Contains functions prototypes of initialization function.*/
#include "hdudispfpoller.h"     /* Engine Information System poller. */
#include "hdudispfresource.h"   /* provides central location to use On Chip Peripherals*/
#include "hdudispfucos.h"       /* uC/OS routines for the real-time kernel */
#include "hdudispfforeground.h" /* contains the routines for foreground layer of the display */
#include "hdudispfarinc825.h"   /* Define the structure for an ARINC 825 Message. */
#include "hdudispfa825comm.h"   /* Routines for arinc 825 communication */
#include "hdudispfrtd.h"        /* Provide mapping for all A825 incoming parameters */
#include "hdudispfbspled.h"    /* contains LED init and and toggling functions */
#include "hdulibbasictypes.h" /* Contains basic header definations */
/* updated as per PR 100083 */
#include "hdudispfdauprofile.h" /* defines the constants for ARINC 825  Message Traffic.*/
#include "hdudispfglobalsettings.h" /* Contains prototype to read and write data to NVRAM*/
#include "hdudispfwdog.h"            /* Watch dog timer declarations */
#include "hdudispfcbit.h"      /* contains prototypes for CBIT test. */
#include "hdudispflmsscu.h"  /* SCU rtd processing and error codes  */

T_OS_STK Init_task_stk[INIT_TASK_STK_SIZE] = {0};
static T_OS_EVENT *Sem_init_task = {0};
T_BOOL Init_b_done = FALSE;

#define STK_DEF_VAL 0xdeaddead

/* updated as per PR 100083 */
/* A429 data format for EIU selection */
#define A429_DATA_FORMAT_EIU_SEL     0x7DU

/*Static functions*/
static void InitTask();

/*
 *
 * Function                : InitTask
 *
 * Description             : InitTask function calls other initialization tasks such as app task
 *                           and poller task, initializes and toggles the LED
 *
 * Formal parameter(s)     : None
 *
 * Return Value            : None
 *
 * Assumption              : None
 *
 */

static void InitTask()
{
   T_UINT8 u8_err = 0;
   /* updated as per PR 100083 */
   static T_UINT8 toggle=0;
   T_A825_MESSAGE   s_mess = {ZERO};

   /* hdudispfinit-InitTask-DB-LLR-009 */
   INIT_NSC_REQUEST(s_mess);
   s_mess.sID.PID.sid    =  MULTICAST_SID;
   s_mess.u8PaySize      = SIX;

   /* hdudispfinit-InitTask-DB-LLR-010 */
   WdogInit();

   /* hdudispfinit-InitTask-DB-LLR-001 */
   /* Prepare to monitor specific A825 parameters. */
   RTDInit();
   WdogKickWatchDog();

   ScuRTDInit();
   WdogKickWatchDog();

   /* hdudispfinit-InitTask-DB-LLR-002 */
   /* Initalize application task*/
   AppInit();
   WdogKickWatchDog();

   /* hdudispfinit-InitTask-DB-LLR-003 */
   /* Initialize the Poller Task.*/
   PollerInit();
   WdogKickWatchDog();

   /* hdudispfinit-InitTask-DB-LLR-004 */
   /* Initilize the Graphic Display Interrupt.*/
   ITInterrupsInit();
   WdogKickWatchDog();

   /* hdudispfinit-InitTask-DB-LLR-005 */
   BSPLEDInit(LED1);
   WdogKickWatchDog();

   /* hdudispfinit-InitTask-DB-LLR-011 */
   DemoInit();
   WdogKickWatchDog();

   /* hdudispfinit-InitTask-DB-LLR-008 */
   CbitInit();
   WdogKickWatchDog();

   /* hdudispfinit-InitTask-DB-LLR-006 */
   /* Allow signaling of all time scheduled tasks.*/
   Init_b_done = TRUE;

   /* hdudispfinit-InitTask-DB-LLR-007 */
   /* Task body */
   while(TRUE)
   {
      OsSemPend(Sem_init_task, 0, &u8_err);
      BSPLEDToggle(LED1);
      WdogKickWatchDog();
      Can1_msg_cntr++;
      /* updated as per PR 100083 */
      toggle = (toggle+ONE) & ONE;

      if(ZERO != toggle)
      {
        s_mess.sID.PID.rci = (T_UCHAR)(Du_position & THREE);
      /* Updated as per PR100156 */
        *((T_UINT32 *)s_mess.u8PayLoad) =   NSC_SEND_A429;
        /* Updated as per PR100113 and PR100147 */
        if ( ONE == Config_data.eng_sdi)
        {
            *((T_UINT32 *)(&(s_mess.u8PayLoad[2]))) = (T_UINT32)(A429_DATA_FORMAT_EIU_SEL
                          |((ZERO & THREE)<<EIGHT)| (( (T_UINT32)Active_eiu) << TEN));
        }
        else
        {
            *((T_UINT32 *)(&(s_mess.u8PayLoad[2]))) = (T_UINT32)(A429_DATA_FORMAT_EIU_SEL
                          |((Du_position & THREE)<<EIGHT)| (( (T_UINT32)Active_eiu) << TEN));
        }
        A8251Xmit(&s_mess);
      }
      else
      {
         ;/* Does nothing */
      }
   }
}

/*
 * Function                : InitSignalTask
 *
 * Description             : InitSignalTask unlocks the init task semaphore
 *
 * Formal parameter(s)     : None
 *
 * Return Value            : None
 *
 * Assumption              : None
 *
 */
void InitSignalTask(void)
{
   static T_UINT16 u16_tick_cntr = ZERO;

   /* hdudispfinit-InitSignalTask-DB-LLR-001 */
   u16_tick_cntr = (T_UINT16)(u16_tick_cntr + ONE);

   if (u16_tick_cntr >= INIT_TASK_TICKS)
   {
      /* hdudispfinit-InitSignalTask-DB-LLR-002 */
      u16_tick_cntr = ZERO;
      OsSemPost(Sem_init_task);
   }
   else
   {
      /* hdudispfinit-InitSignalTask-DB-LLR-003 */
      ;/*Do nothing*/
   }
}

/*
 * Function                : InitInit
 *
 * Description             : This function installs Semaphore into timebase and creates InitTask
 *
 * Formal parameter(s)     : None
 *
 * Return Value            : None
 *
 * Assumption              : None
 *
 */
void InitInit(void)
{
   T_UINT16 u16_ctr = 0;

   /* hdudispfinit-InitInit-DB-LLR-001 */
   /* Initialize semaphore for application task */
   Sem_init_task = OsSemCreate(ZERO);

   /* hdudispfinit-InitInit-DB-LLR-002 */
   /* Initialize the stack for run time checks. */
   for(u16_ctr=0; u16_ctr<INIT_TASK_STK_SIZE; u16_ctr++)
   {
      Init_task_stk[u16_ctr] = STK_DEF_VAL;
   }

   /* create InitTask as the first task to run of RTOS */
   OsTaskCreate(InitTask, (void *)ZERO, &Init_task_stk[INIT_TASK_STK_SIZE], INIT_TASK_PRIO);
}
