/*
 ******************************************************************************
 * License Information  :  Howell Instruments, Inc.                           *
 *                         "Licensed Software" and "All rights reserved".     *
 ******************************************************************************
 *  File                : hdudispfa825comm1.c
 *
 *  Description         : This file implements the arinc 825 communications portion of
 *                         the application.
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
 * <Version No.>      <Author>          <Date>         <Problem Report No.>
 *
 *      1.1           Vinay H       24-Jul-2017             100064
 *      1.2           Vinay H       09-Oct-2017             100064
 *      1.3           Shruthi M N   13-Oct-2017             100083
 *      1.4           Shruthi M N   04-Nov-2017             100147
 *
 * Additional References : None
 *
 ******************************************************************************
 */

#include "hdudispfapp.h"        /* contains Engine Information System application */
#include "hdudispfcbit.h"       /* contains prototypes for CBIT test. */
#include "hdudispfdauprofile.h" /* defines the constants for ARINC 825  Message Traffic.*/
#include "hdudispfresource.h"   /* provides central location to use On Chip Peripherals*/
#include "hdudispfucos.h"       /* defines the implementation of uC/OS routines  */
#include "hdudispfarinc825.h"   /* Define the structure for an ARINC 825 Message. */
#include "hdudispfa825comm.h"   /* Routines for arinc 825 communication */
#include "hdulibbasictypes.h" /* Standard basic data type definitions */
#include "hdudispfoscpu.h"    /* defines the OS configurations  */
#include "hdudispfarinc825.h"   /* defines  ARINC 825 Message configurations  */

#define MY_SID EISDSPLY_SID      /* Server ID for this node.         */

/* Stack for the a825comm task.  */
T_OS_STK A825_comm1_task_stk[A825COMM_TASK_STK_SIZE]=
{
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,
   STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL,STK_VAL
};

/*
 * This counter increments if a message is received that
 * is not handled by this node.  This is an indication
 * that the filters were not set up properly.
 */
static T_UINT32 U32_a825_filter_errors = ZERO;

/* Updated as per PR100083*/
T_UINT32 Can1_msg_cntr=ZERO;

/*Static functions*/
static void A825CommTask1(void *p_data);

/*
 * Function                :  A825CommTask1
 *
 * Description             :  This task is signaled from the ARINC 825 receiver routine
 *                            to process the received message.  The task will only handle
 *                            messages that it is designed to handle.  All others will
 *                            be discarded.
 *
 * Formal parameter(s)     :  void *p_data -IN Pointer to the data
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */

static void A825CommTask1(void *p_data)
{
   T_UINT8  u8_err = 0;
   T_A825_MESSAGE s_mess = {0};

   /*hdudispfa825comm1-A825CommTask1-DB-LLR-008*/
   p_data=(T_UINT8*)p_data+0;

   /*hdudispfa825comm1-A825CommTask1-DB-LLR-001*/
   while (TRUE)
   {
     /*hdudispfa825comm1-A825CommTask1-DB-LLR-002*/
      /* Wait for a message to arrive. */
      OsSemPend(Sem_a8251_commtask, 0, &u8_err);

      /*Updated as per PR100083*/
      Can1_msg_cntr=ZERO;
/*------------------ Process Normal Operating Channel.   -----------------*/
      if(A8251GetMessage(NOC, &s_mess) != A825_RX_QUEUE_EMPTY)
      {
         /* By design, only respond to NOC messages */
         if(HOWELL_DAU_FID == s_mess.sID.BID.sfid)
         {
           /*hdudispfa825comm1-A825CommTask1-DB-LLR-004*/
            U32_a825_filter_errors += AppU32NOC(&s_mess, A825_1);
         }
         else
         {
           /*hdudispfa825comm1-A825CommTask1-DB-LLR-005*/
            U32_a825_filter_errors += 1;
         }
      }

/*-----------------  Process Node Service Channel.   -----------------------*/
      else if(A8251GetMessage(NSC, &s_mess) != A825_RX_QUEUE_EMPTY)
      {
         /*Updated as per PR100083*/
		 /*Updated as per PR100147*/
         if(((EISDSPLYGATEWAY_SID == s_mess.sID.PID.sid )
               || (MULTICAST_SID == s_mess.sID.PID.sid)
               || (MY_SID == s_mess.sID.PID.sid))&& (ZERO==s_mess.sID.PID.smt))
         {
           /*hdudispfa825comm1-A825CommTask1-DB-LLR-006*/
            /* Service a Node Service Request.  */
            U32_a825_filter_errors += AppU32NSC(&s_mess, A825_1);
         }
         else
         {
           /*hdudispfa825comm1-A825CommTask1-DB-LLR-007*/
            U32_a825_filter_errors += 1;
         }
      }
      else
      {
         ;/*Do nothing*/
      }
   }
}

/*
 * Function                :  A825CommInit1
 *
 * Description             :  Initialize the task to handle commands coming across the
 *                               arinc 825 bus.
 *
 * Formal parameter(s)     :  None
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */

void A825CommInit1(void)
{
   /*hdudispfa825comm1-A825CommInit1-DB-LLR-002*/
   /* Create the application task.  */
   OsTaskCreate(A825CommTask1, (void *)NULL,
                        &A825_comm1_task_stk[A825COMM_TASK_STK_SIZE], A825_1_COMM_TASK_PRIO);
}
