/*
 ******************************************************************************
 * License Information  :  Howell Instruments, Inc.                           *
 *                         "Licensed Software" and "All rights reserved".     *
 ******************************************************************************
 *  File                : hdudispfarinc825perph2.c
 *
 *  Description         : This file defines the implementation of ARINC825 routines
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
 *      1.1           Vinay H       25-Jul-2017             100064
 *      1.2           Vinay H       09-Oct-2017             100064
 *      1.3           Shruthi M N   13-Oct-2017             100083
 *      1.4           Shruthi M N   30-Oct-2017             100104
 *      1.5           Rona B S      12-Sep-2020             100276 
 *
 * Additional References : None
 *
 ******************************************************************************
 */

#include "hdudispfresource.h"   /* provides central location to use On Chip Peripherals*/
#include "hdulibstm32f7xxhalcan.h"   /* Header file of HAL CAN module. */
#include "hdulibstm32f7xxhalconf.h"  /* provides HAL configurations. */
#include "hdudispfarinc825.h"   /* Define the structure for an ARINC 825 Message. */
#include "hdudispfa825def.h"    /* Arinc 825 functions and structures */
#include "hdulibstm32f7xx.h"   /* Cortex-M7 Device System Source File for STM32F7xx devices.*/
#include "hdulibbasictypes.h"  /* Standard basic data type definitions */
#include "hdudispfucos.h"       /* defines the implementation of uC/OS routines  */
#include "hdulibstm32f746xx.h" /* CMSIS STM32F7xx Device Peripheral Access Layer file*/

#define PRESCLR_FOUR    4U
#define BANK_NO_14      14U

/* Counting sem to signal A825 input processing.      */
T_OS_EVENT *Sem_a8252_commtask = (T_OS_EVENT *)NULL;

/* Define transmit queues for the four main A825 channels.   */

static T_CANTXQUEUE Noc_tx_queue =
{
   0,
   Noc_tx_queue.TxBuf,
   Noc_tx_queue.TxBuf,
   {
     {
        0,0,0,0,0,
        {
         0,0,0,0,0,0,0,0
        }
      }
   }
};

static T_CANTXQUEUE Nsc_tx_queue =
{
   0,
   Nsc_tx_queue.TxBuf,
   Nsc_tx_queue.TxBuf,
   {
     {
        0,0,0,0,0,
        {
         0,0,0,0,0,0,0,0
        }
      }
   }
};


/* Define receive queues for the four main A825 channels.    */

static T_CANRXQUEUE Noc_rx_queue =
{
   0,
   Noc_rx_queue.RxBuf,
   Noc_rx_queue.RxBuf,
   {
     {
        0,0,0,0,0,
        {
         0,0,0,0,0,0,0,0
        },
        0,0
     }
   }
};

static T_CANRXQUEUE Nsc_rx_queue =
{
   0,
   Nsc_rx_queue.RxBuf,
   Nsc_rx_queue.RxBuf,
   {
     {
        0,0,0,0,0,
        {
         0,0,0,0,0,0,0,0
        },
        0,0
     }
   }
};

/* Handle for the can channel. */
static T_CAN_HANDLE    Can_handle = {0};

/* Single message for use by the handle. */
static T_CAN_TX_MSG_TYPE        Tx_message = {0};
static T_CAN_RX_MSG_TYPE        Rx_message = {0};


/*Static functions*/
static void CanItConfig(T_CAN* can_x, T_UINT32 can_it, T_FUNCTIONAL_STATE new_state);
static T_UINT8 U8MailBoxAvail(T_CAN_HANDLE* h_can);
static T_A825_RECRESULT RxQueueRemove(T_A825_MESSAGE *ps_destination, T_CANRXQUEUE  *ps_which_q);
static T_A825_RECRESULT RxQueueInsert(T_CAN_RX_MSG_TYPE *ps_new_mess, T_CANRXQUEUE *ps_which_q);
static T_A825_XMITRESULT TxQueueInsert(T_CAN_TX_MSG_TYPE *ps_new_mess, T_CANTXQUEUE   *ps_which_q);
static T_UINT32 BuildBroadcastExtId(T_A825_MESSAGE *ps_xm);
static T_UINT32 BuildPeerToPeerExtId(T_A825_MESSAGE *ps_xm);
static T_UINT8 XmitFromBuff(T_CANTXQUEUE *ps_which_q);


/*
 * Function                :  CanItConfig
 *
 * Description             :  This function enables or disables a specific interrupt on a can
 *                            controller.
 *
 * Formal parameter(s)     :  T_CAN* can_x - INOUT - Pointer to CAN peripheral
 *                            T_UINT32 can_it - IN - specifies the CAN interrupt sources
 *                             to be enabled or disabled.
 *                            T_FUNCTIONAL_STATE new_state - IN new state of the CAN interrupts.
 *                            This parameter can be: ENABLE or DISABLE.
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */
static void CanItConfig(T_CAN* can_x, T_UINT32 can_it,  T_FUNCTIONAL_STATE new_state)
{
  if (new_state != DISABLE)
  {
    /* hdudispfarinc825perph2-CANITConfig-DB-LLR-001 */
    /* Enable the selected CANx interrupt */
    can_x->IER |= can_it;
  }
  else
  {
     /* hdudispfarinc825perph2-CANITConfig-DB-LLR-002 */
    /* Disable the selected CANx interrupt */
    can_x->IER &= ~can_it;
  }
}

/*
 * Function                :  U8MailBoxAvail
 *
 * Description             :  This function sees if there is a mail box available.
 *
 * Formal parameter(s)     :  T_CAN_HANDLE* h_can -IN - Pointer to CAN handle Structure
 *
 * Return Value            :  T_UINT8 - returns mail box status
 *
 * Assumption              :  None
 *
 */

static T_UINT8 U8MailBoxAvail(T_CAN_HANDLE* h_can)
{
   /* hdudispfarinc825perph2-U8MailBoxAvail-DB-LLR-001 */
   return (T_UINT8)(((CAN_TSR_TME0 == (h_can->Instance->TSR&CAN_TSR_TME0)) || \
   (CAN_TSR_TME1 == (h_can->Instance->TSR&CAN_TSR_TME1)) || \
    (CAN_TSR_TME2 == (h_can->Instance->TSR&CAN_TSR_TME2))));
}

/*
 * Function                :  RxQueueRemove
 *
 * Description             :  This function Retrieve a message from the specified receive queue
 *                              and decompose the CAN message into an ARINC 825 message.
 *
 * Formal parameter(s)     :  T_A825_MESSAGE *ps_destination - OUT retrieved message
 *                            T_CANRXQUEUE   *ps_which_q - INOUT The receive queue to retrieve from
 *
 * Return Value            :  T_A825_RECRESULT - Returns the state
 *
 * Assumption              :  None
 *
 */

static T_A825_RECRESULT RxQueueRemove(T_A825_MESSAGE *ps_destination, T_CANRXQUEUE   *ps_which_q)
{
   T_CAN_RX_MSG_TYPE   can_message = {0};
   T_A825_MESSAGE   arinc_message = {0};
   T_UINT8           u8_ctr = {0};

   if(ZERO == ps_which_q->RxCntr)
   {
      /* hdudispfarinc825perph2-RxQueueRemove-DB-LLR-001 */
      return(A825_RX_QUEUE_EMPTY);
   }
   else
   {
      ;/*Do nothing*/
   }

   /* hdudispfarinc825perph2-RxQueueRemove-DB-LLR-002 */
   /* Disable the Can ReceiverTransmit Interrupt. */
   CanItConfig(CAN2, CAN_IT_FMP0, DISABLE);

   /* hdudispfarinc825perph2-RxQueueRemove-DB-LLR-003 */
   can_message = *(ps_which_q->RxHead);

   /* hdudispfarinc825perph2-RxQueueRemove-DB-LLR-004 */
   /* Adjust the head and check for a wrap.*/
   ps_which_q->RxCntr = (T_UINT16)(ps_which_q->RxCntr - ONE);
   ps_which_q->RxHead += ONE;

   if(ps_which_q->RxHead == &(ps_which_q->RxBuf[CAN_R_Q_SIZE]))
   {
      /* hdudispfarinc825perph2-RxQueueRemove-DB-LLR-005 */
      ps_which_q->RxHead = ps_which_q->RxBuf;
   }
   else
   {
      ;/*Do nothing*/
   }

   /* hdudispfarinc825perph2-RxQueueRemove-DB-LLR-006 */
   /* Enable the Can Receiver Interrupt.              */
   CanItConfig(CAN2, CAN_IT_FMP0, ENABLE);

   /* hdudispfarinc825perph2-RxQueueRemove-DB-LLR-007 */
   /* TRANSLATE CAN MESSAGE TO A825 MESSAGE HERE.  */
   arinc_message.lcc = (can_message.ExtId>>LCC_LOC) & LCC_MSK;

   /* If this is a broadcast message.                    */
   if(NOC == arinc_message.lcc)
   {
      /* hdudispfarinc825perph2-RxQueueRemove-DB-LLR-008 */
      arinc_message.sID.BID.rci = (can_message.ExtId>>RCI_LOC) & RCI_MSK;
      arinc_message.sID.BID.doc = (can_message.ExtId>>DOC_LOC) & DOC_MSK;
      arinc_message.sID.BID.pvt = (can_message.ExtId>>PVT_LOC) & PVT_MSK;
      arinc_message.sID.BID.lcl = (can_message.ExtId>>LCL_LOC) & LCL_MSK;
      arinc_message.sID.BID.rsd = (can_message.ExtId>>RSD_LOC) & RSD_MSK;
      arinc_message.sID.BID.sfid = (can_message.ExtId>>SRC_FID_LOC) & SRC_FID_MSK;
   }
   /* Else this is a peer to peer message.            */
   else
   {
      /* hdudispfarinc825perph2-RxQueueRemove-DB-LLR-009 */
      arinc_message.sID.PID.rci = (can_message.ExtId>>RCI_LOC) & RCI_MSK;
      arinc_message.sID.PID.pvt = (can_message.ExtId>>PVT_LOC) & PVT_MSK;
      arinc_message.sID.PID.lcl = (can_message.ExtId>>LCL_LOC) & LCL_MSK;
      arinc_message.sID.PID.sfid = (can_message.ExtId>>SER_FID_LOC) & SER_FID_MSK;
      arinc_message.sID.PID.cfid = (can_message.ExtId>>CFID_LOC) & CFID_MSK;
      arinc_message.sID.PID.smt = (can_message.ExtId>>SMT_LOC) & SMT_MSK;
      arinc_message.sID.PID.sid = (can_message.ExtId>>SID_LOC) & SID_MSK;
   }

   /* hdudispfarinc825perph2-RxQueueRemove-DB-LLR-010 */
   arinc_message.u8PaySize = (T_UINT8)can_message.DLC;
   if(arinc_message.u8PaySize > PAYLOAD_SIZE)
   {
      /* hdudispfarinc825perph2-RxQueueRemove-DB-LLR-011 */
      arinc_message.u8PaySize = PAYLOAD_SIZE;
   }
   else
   {
      ;/*Do nothing*/
   }

   /* Copy the payload.                         */
   for(u8_ctr = 0; u8_ctr < arinc_message.u8PaySize; u8_ctr++)
   {
      /* hdudispfarinc825perph2-RxQueueRemove-DB-LLR-012 */
      arinc_message.u8PayLoad[u8_ctr] = can_message.Data[u8_ctr];
   }

   /* hdudispfarinc825perph2-RxQueueRemove-DB-LLR-013 */
   *ps_destination = arinc_message;

   return(A825_RX_OK);
}


/*
 * Function                :  A8252GetMessage
 *
 * Description             :  This function retrieves a message from the specified
 *                              communication channel.
 *
 * Formal parameter(s)     :  T_LCC_TYPE e_channel - IN channel type
 *                            T_A825_MESSAGE *ps_destination - IN destination message
 *
 * Return Value            :  T_A825_RECRESULT - Returns the state
 *
 * Assumption              :  None
 *
 */

T_A825_RECRESULT A8252GetMessage(T_LCC_TYPE e_channel, T_A825_MESSAGE *ps_destination)
{
   T_A825_RECRESULT result = A825_RX_NOT_IMPLEMENTED;

   switch(e_channel)
   {
      case NOC:
      {
         /* hdudispfarinc825perph2-A8252GetMessage-DB-LLR-001 */
         result = RxQueueRemove(ps_destination, &Noc_rx_queue);
         break;
      }
      case NSC:
      {
         /* hdudispfarinc825perph2-A8252GetMessage-DB-LLR-002 */
         result = RxQueueRemove(ps_destination, &Nsc_rx_queue);
         break;
      }
      default:
      {
         /* hdudispfarinc825perph2-A8252GetMessage-DB-LLR-003 */
         result = A825_RX_BAD_CHANNEL;
         break;
      }
   }

   /* hdudispfarinc825perph2-A8252GetMessage-DB-LLR-004 */
   return(result);
}


/*
 * Function                :  RxQueueInsert
 *
 * Description             :  This function Inserts a CAN message into the selected queue.
 *
 * Formal parameter(s)     :  T_CAN_RX_MSG_TYPE *ps_new_mess - IN The new message to insert.
 *                            T_CANRXQUEUE *ps_which_q - INOUT The queue to place the message in.
 *
 * Return Value            :  T_A825_RECRESULT - Returns the state
 *
 * Assumption              :  None
 *
 */

static T_A825_RECRESULT RxQueueInsert(T_CAN_RX_MSG_TYPE *ps_new_mess, T_CANRXQUEUE *ps_which_q)
{
   /* Check for buffer overflow.     */
   if(CAN_R_Q_SIZE == ps_which_q->RxCntr)
   {
      /* hdudispfarinc825perph2-RxQueueInsert-DB-LLR-001 */
      return(A825_RX_OVERFLOW);
   }
   else
   {
      ;/*Do nothing*/
   }
   /* hdudispfarinc825perph2-RxQueueInsert-DB-LLR-002 */
   /* Insert the new message.            */
   *(ps_which_q->RxTail) = *ps_new_mess;

   /* hdudispfarinc825perph2-RxQueueInsert-DB-LLR-003 */
   /* Adjust the tail and check for a wrap.*/
   ps_which_q->RxCntr = (T_UINT16)(ps_which_q->RxCntr + ONE);
   ps_which_q->RxTail += ONE;

   if(ps_which_q->RxTail == &(ps_which_q->RxBuf[CAN_R_Q_SIZE]))
   {
      /* hdudispfarinc825perph2-RxQueueInsert-DB-LLR-004 */
      ps_which_q->RxTail = ps_which_q->RxBuf;
   }
   else
   {
      ;/*Do nothing*/
   }

   /* hdudispfarinc825perph2-RxQueueInsert-DB-LLR-005 */
   return(A825_RX_OK);
}

/*
 * Function                :  Can2Rx0IrqHandler
 *
 * Description             :  This function is called directly from the interrupt service
 *                            routine to buffer incoming messages for later processing.
 *                            The LCC must conform to one of the Two main A825 channels
 *                            or the message will be discarded.
 *
 * Formal parameter(s)     :  None
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */

void Can2Rx0IrqHandler(void)
{
   T_UINT32       lcc_val = 0;
   T_A825_RECRESULT result = {0};

   /* hdudispfarinc825perph2-Can2Rx0IrqHandler-DB-LLR-001 */
   /* Tell uCOS that we are entering the ISR */
   OsIntEnter();

   /* hdudispfarinc825perph2-Can2Rx0IrqHandler-DB-LLR-002 */
   /* Retrieve the can message.                 */
   HalCanReceive(&Can_handle, CAN_FIFO0, 0);

   /* hdudispfarinc825perph2-Can2Rx0IrqHandler-DB-LLR-003 */
   /* Determine which logical comm channel.  */
   lcc_val = ((Rx_message.ExtId) >> LCC_LOC) & LCC_MSK;

   switch(lcc_val)
   {
      case NOC:
      {
         /* hdudispfarinc825perph2-Can2Rx0IrqHandler-DB-LLR-004 */
         result = RxQueueInsert(&Rx_message, &Noc_rx_queue);
         if(A825_RX_OK == result)
         {
            OsSemPost(Sem_a8252_commtask);
         }
         else
         {
            ;/*Do nothing*/
         }
         break;
      }
      case NSC:
      {
         /* hdudispfarinc825perph2-Can2Rx0IrqHandler-DB-LLR-005 */
         result = RxQueueInsert(&Rx_message, &Nsc_rx_queue);
         if(A825_RX_OK == result )
         {
            OsSemPost(Sem_a8252_commtask);
         }
         else
         {
            ;/*Do nothing*/
         }
         break;
      }
      default:
      {
         break;
      }
   }

   /* hdudispfarinc825perph2-Can2Rx0IrqHandler-DB-LLR-007 */
   /* Tell uCOS that we are leaving the ISR */
   OsIntExit();
}

/*
 * Function                :  TxQueueInsert
 *
 * Description             :  This function Inserts a CAN message into the selected queue.
 *
 * Formal parameter(s)     :  T_CAN_TX_MSG_TYPE *ps_new_mess - IN The new message to insert.
 *                             T_CANTXQUEUE *ps_which_q - INOUT The queue to place the message in.
 *
 * Return Value            :  T_A825_XMITRESULT - State
 *
 * Assumption              :  None
 *
 */

static T_A825_XMITRESULT TxQueueInsert(T_CAN_TX_MSG_TYPE *ps_new_mess, T_CANTXQUEUE   *ps_which_q)
{
   /* hdudispfarinc825perph2-TxQueueInsert-DB-LLR-001 */
   /* Disable the Can Transmit Interrupt.   */
   CanItConfig(CAN2, CAN_IT_TME, DISABLE);

   /* Check for buffer overflow.             */
   if(CAN_X_Q_SIZE == ps_which_q->TxCntr)
   {
      /* hdudispfarinc825perph2-TxQueueInsert-DB-LLR-002 */
      /* Enable the Can Transmit Interrupt. */
      CanItConfig(CAN2, CAN_IT_TME, ENABLE);
            return(A825_XM_OVERFLOW);
      }
   else
   {
      ;/*Do nothing*/
   }

   /* hdudispfarinc825perph2-TxQueueInsert-DB-LLR-003 */
   /* Insert the new message.               */
   *(ps_which_q->TxTail) = *ps_new_mess;

   /* hdudispfarinc825perph2-TxQueueInsert-DB-LLR-004 */
   /* Adjust the tail and check for a wrap. */
   ps_which_q->TxCntr = (T_UINT16)(ps_which_q->TxCntr + ONE);
   ps_which_q->TxTail += ONE;

   if(ps_which_q->TxTail == &(ps_which_q->TxBuf[CAN_X_Q_SIZE]))
   {
      /* hdudispfarinc825perph2-TxQueueInsert-DB-LLR-005 */
      ps_which_q->TxTail = ps_which_q->TxBuf;
   }
   else
   {
      ;/*Do nothing*/
   }
   /* hdudispfarinc825perph2-TxQueueInsert-DB-LLR-006 */
   /* Enable the Can Transmit Interrypt.   */
    CanItConfig(CAN2, CAN_IT_TME, ENABLE);

   /* hdudispfarinc825perph2-TxQueueInsert-DB-LLR-007 */
   /* Check for immediate transmit.        */
   Can2TxIrqHandler();

   return(A825_XM_OK);
}

/*
 * Function                :  BuildBroadcastExtId
 *
 * Description             :  This function builds the 29 bit CAN identifier for an ARINC 825
 *                             broadcast type message.
 *
 * Formal parameter(s)     :  T_A825_MESSAGE *ps_xm - IN Pointer to an ARINC 825 message.
 *
 * Return Value            :  T_UINT32 29 bit CAN identifier
 *
 * Assumption              :  None
 *
 */

static T_UINT32 BuildBroadcastExtId(T_A825_MESSAGE *ps_xm)
{
   T_UINT32 ext_id = 0;

   /* hdudispfarinc825perph2-BuildBroadcastExtId-DB-LLR-001 */
   ext_id   = ((T_UINT32)((ps_xm->sID.BID).lcl) << LCL_LOC)
            | ((T_UINT32)((ps_xm->sID.BID).pvt) << PVT_LOC)
            | ((T_UINT32)((ps_xm->sID.BID).doc) << DOC_LOC)
            | ((T_UINT32)((ps_xm->sID.BID).rci) << RCI_LOC)
            | ((T_UINT32)((ps_xm->sID.BID).rsd) << RSD_LOC)
            | ((T_UINT32)((ps_xm->sID.BID).sfid) << SRC_FID_LOC);

   ext_id |= ((T_UINT32)(ps_xm->lcc) << LCC_LOC);

   /* hdudispfarinc825perph2-BuildBroadcastExtId-DB-LLR-002 */
   return(ext_id);
}

/*
 * Function                :  BuildPeerToPeerExtId
 *
 * Description             :  This function builds the 29 bit CAN identifier for an ARINC 825
 *                            peer to peer type message.
 *
 * Formal parameter(s)     :  T_A825_MESSAGE *ps_xm - IN Pointer to an ARINC 825 message.
 *
 * Return Value            :  T_UINT32 -29 bit CAN identifier
 *
 * Assumption              :  None
 *
 */
static T_UINT32 BuildPeerToPeerExtId(T_A825_MESSAGE *ps_xm)
{
   T_UINT32 ext_id = 0;

   /* hdudispfarinc825perph2-BuildPeerToPeerExtId-DB-LLR-001 */
   ext_id   = ((T_UINT32)((ps_xm->sID.PID).cfid) << CFID_LOC)
            | ((T_UINT32)((ps_xm->sID.PID).smt) << SMT_LOC)
            | ((T_UINT32)((ps_xm->sID.PID).lcl) << LCL_LOC)
            | ((T_UINT32)((ps_xm->sID.PID).pvt) << PVT_LOC)
            | ((T_UINT32)((ps_xm->sID.PID).sfid) << SER_FID_LOC)
            | ((T_UINT32)((ps_xm->sID.PID).sid) << SID_LOC)
            | ((T_UINT32)((ps_xm->sID.PID).rci) << RCI_LOC);

   ext_id |= ((T_UINT32)(ps_xm->lcc) << LCC_LOC);

   /* hdudispfarinc825perph2-BuildPeerToPeerExtId-DB-LLR-002 */
   return(ext_id);
}


/*
 * Function                :  A8252Xmit
 *
 * Description             :  This function builds a CAN message from the user supplied ARINC 825
 *                            message Place the newly built CAN message in the queue for that
 *                            message type.
 *
 * Formal parameter(s)     :  T_A825_MESSAGE *ps_xm - IN Pointer to the ARINC 825 message
 *                            to transmit.
 *
 * Return Value            :  T_A825_XMITRESULT - transmit status
 *
 * Assumption              :  None
 *
 */

T_A825_XMITRESULT A8252Xmit(T_A825_MESSAGE *ps_xm)
{
   T_A825_XMITRESULT  result = A825_XM_NOT_IMPLEMENTED;
   T_UINT32 ext_id = 0;                   /* Used to build the A825 Extended ID. */
   T_UINT8  u8_ctr = 0;                   /* Counter. */
   T_CAN_TX_MSG_TYPE transmit_msg = {0};  /* Message to be transmitted. */
   T_CANTXQUEUE   *temp_tx_queue = {0};   /* Pointer to message Q. */

   /* Locate Q and build the 29 bit ID based on selected channel. */
   if (NOC == ps_xm->lcc)   /* Normal Operation Channel.     */
   {
      /* hdudispfarinc825perph2-A8252Xmit-DB-LLR-001 */
      temp_tx_queue = &Noc_tx_queue;
      ext_id = BuildBroadcastExtId(ps_xm);
   }
   else if (NSC == ps_xm->lcc)   /* Node Service Channel.           */
   {
      /* hdudispfarinc825perph2-A8252Xmit-DB-LLR-002 */
      temp_tx_queue = &Nsc_tx_queue;
      ext_id = BuildPeerToPeerExtId(ps_xm);
   }
   else     /* UNKNOWN Channel Type.*/
   {
      /* hdudispfarinc825perph2-A8252Xmit-DB-LLR-003 */
      return(A825_BAD_CHANNEL);
   }

   /* Check for too many payload bytes.   */
   if(ps_xm->u8PaySize > PAYLOAD_SIZE)
   {
      /* hdudispfarinc825perph2-A8252Xmit-DB-LLR-004 */
      return(A825_BAD_PAYLOAD_SIZE);
   }
   else
   {
      ;/*Do nothing*/
   }

   /* hdudispfarinc825perph2-A8252Xmit-DB-LLR-005 */
   /* Fill in all of the CAN message data.                                  */
   transmit_msg.ExtId = ext_id;              /* Set the extended ID.        */
   transmit_msg.IDE = CAN_ID_EXT;            /* A825 uses extended IDs only.*/
   transmit_msg.RTR = CAN_RTR_DATA;       /* This is *not* a remote frame.  */
   transmit_msg.DLC = ps_xm->u8PaySize;   /* Set the payload size.          */

   /* Copy the payload.                         */
   for(u8_ctr = 0; u8_ctr < ps_xm->u8PaySize; u8_ctr++)
   {
      /*Updated as per PR100083*/
      /* hdudispfarinc825perph2-A8252Xmit-DB-LLR-006 */
      transmit_msg.Data[u8_ctr] = ps_xm->u8PayLoad[u8_ctr];
   }

   /* hdudispfarinc825perph2-A8252Xmit-DB-LLR-007 */
   result = TxQueueInsert(&transmit_msg, temp_tx_queue);

   return(result);
}

/*
 * Function                :  XmitFromBuff
 *
 * Description             :  This function transmits a message from the supplied queue
 *                            if a CAN mailbox is ready.
 *
 * Formal parameter(s)     :  T_CANTXQUEUE *ps_which_q - INOUT The queue to place the message in
 *
 * Return Value            :  T_UINT8 - The number of the mailbox that
 *                                  is used for transmission
 *
 * Assumption              :  None
 *
 */

static T_UINT8 XmitFromBuff(T_CANTXQUEUE *ps_which_q)
{
   if(U8MailBoxAvail(&Can_handle) != ZERO)
   {
      /* hdudispfarinc825perph2-XmitFromBuff-DB-LLR-001 */
      *(Can_handle.pTxMsg) = *(ps_which_q->TxHead);
      HalCanTransmit(&Can_handle, ZERO_TIMEOUT);

      /* hdudispfarinc825perph2-XmitFromBuff-DB-LLR-002 */
      ps_which_q->TxCntr = (T_UINT16)(ps_which_q->TxCntr - ONE);
      ps_which_q->TxHead += ONE;
      if(ps_which_q->TxHead == &(ps_which_q->TxBuf[CAN_X_Q_SIZE]))
      {
         /* hdudispfarinc825perph2-XmitFromBuff-DB-LLR-003 */
         ps_which_q->TxHead = ps_which_q->TxBuf;
      }
      else
      {
         ;/*Do nothing*/
      }
      /* hdudispfarinc825perph2-XmitFromBuff-DB-LLR-004 */
      return(ONE);
   }
   else
   {
      /* hdudispfarinc825perph2-XmitFromBuff-DB-LLR-005 */
      return(ZERO);
   }
}

/*
 * Function                :  Can2TxIrqHandler
 *
 * Description             :  This function checks whether the free mail box is available
 *                            for the immediate message transmission  and disable the selected
 *                            CANx interrupt when transmission queue is empty.
 *
 * Formal parameter(s)     :  None
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */

void Can2TxIrqHandler(void)
{
   /* hdudispfarinc825perph2-Can2TxIrqHandler-DB-LLR-001 */
   while(Noc_tx_queue.TxCntr != ZERO)
   {
      if(ZERO == XmitFromBuff(&Noc_tx_queue))
      {
         return;
      }
      else
      {
         ;/*Do nothing*/
      }
   }

   /* hdudispfarinc825perph2-Can2TxIrqHandler-DB-LLR-003 */
   while(Nsc_tx_queue.TxCntr != ZERO)
   {
      if(ZERO == XmitFromBuff(&Nsc_tx_queue))
      {
         return;
      }
      else
      {
         ;/*Do nothing*/
      }
   }

   /* hdudispfarinc825perph2-Can2TxIrqHandler-DB-LLR-005 */
   /* If we reach here, all transmit queues are empty.   */
   CanItConfig(CAN2, CAN_IT_TME, DISABLE);
}

/*
 * Function                :  Can2Config
 *
 * Description             :  This function configures the CAN2.
 *
 * Formal parameter(s)     :  None
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */

static void Can2Config(void)
{
  T_CAN_FILTER_CONF_TYPE  filter_config = {0};

  /*hdudispfarinc825perph2-Can2Config-DB-LLR-001*/
  /*##-1- Configure the CAN peripheral */
  Can_handle.Instance = CAN2;
  Can_handle.pTxMsg = &Tx_message;
  Can_handle.pRxMsg = &Rx_message;

  Can_handle.Init.TTCM = DISABLE;
  Can_handle.Init.ABOM = ENABLE;
  Can_handle.Init.AWUM = DISABLE;
  Can_handle.Init.NART = DISABLE;
  Can_handle.Init.RFLM = DISABLE;
  Can_handle.Init.TXFP = DISABLE;
  Can_handle.Init.Mode = CAN_MODE_NORMAL;
  Can_handle.Init.SJW  = CAN_SJW_1TQ;
  Can_handle.Init.BS1  = CAN_BS1_6TQ;
  Can_handle.Init.BS2  = CAN_BS2_7TQ;
  Can_handle.Init.Prescaler = PRESCLR_FOUR;

  /*hdudispfarinc825perph2-Can2Config-DB-LLR-002*/
  if (HalCanInit(&Can_handle) != HAL_OK)
  {
   while(TRUE)
   {
      /* Does nothing */
   }
  }
  else
  {
   ;/*Do nothing*/
  }

  /*hdudispfarinc825perph2-Can2Config-DB-LLR-003*/
  /*##-2- Configure the CAN Filter */
  filter_config.FilterNumber = BANK_NO_14;
  filter_config.FilterMode = CAN_FILTERMODE_IDMASK;
  filter_config.FilterScale = CAN_FILTERSCALE_32BIT;
  filter_config.FilterIdHigh = ZERO;
  filter_config.FilterIdLow = ZERO;
  filter_config.FilterMaskIdHigh = ZERO;
  filter_config.FilterMaskIdLow = ZERO;
  filter_config.FilterFIFOAssignment = ZERO;
  filter_config.FilterActivation = ENABLE;
  filter_config.BankNumber = BANK_NO_14;

   /*hdudispfarinc825perph2-Can2Config-DB-LLR-004 */
  if (HalCanConfigFilter(&Can_handle, &filter_config) != HAL_OK)
  {
   while(TRUE)
   {
      ;/* Does nothing */
   }
  }
  else
  {
   ;/*Do nothing*/
  }

  /*hdudispfarinc825perph2-Can2Config-DB-LLR-005*/
  /* Enable FIFO 0 message pending Interrupt */
  CanItConfig(CAN2, CAN_IT_FMP0, ENABLE);
}


/*
 * Function                :  A8252Init
 *
 * Description             :  This function Perform initialization necessary for
 *                            ARINC 825 communication.
 *
 * Formal parameter(s)     :  None
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */

void A8252Init(void)
{
   /* hdudispfarinc825perph2-A8252Init-DB-LLR-001 */
   /* Create a Sem to signaling the A825 receiver task.  */
   Sem_a8252_commtask = OsSemCreate(0);

   /* hdudispfarinc825perph2-A8252Init-DB-LLR-002 */
   /* CAN configuration */
   Can2Config();
}
