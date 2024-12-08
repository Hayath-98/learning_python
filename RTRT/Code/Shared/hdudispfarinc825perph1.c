/*
 ******************************************************************************
 * License Information  :  Howell Instruments, Inc.                           *
 *                         "Licensed Software" and "All rights reserved".     *
 ******************************************************************************
 *  File                : hdudispfarinc825perph1.c
 *
 *  Description         : This file provides routines to implement the arinc825 functionality.
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
 *      1.1           Shilpa A R     25-Jul-2017             100064
 *      1.2           Vinay H        09-Oct-2017             100064
 *      1.3           Shilpa A R     23-Oct-2017             100083
 *      1.4           Shruthi M N    30-Oct-2017             100104
 *      1.5           Shilpa A R     04-Nov-2017             100156
 *      1.6           Vinay H        08-Nov-2017             100164
 *      1.7           Vinay H        23-Mar-2018             100196
 *      1.8           Rona B.S       28-Mar-2018             100196
 *
 * Additional References : None
 *
 ******************************************************************************
 */
#include "hdudispfresource.h"   /* provides central location to use On Chip Peripherals*/
#include "hdulibstm32f746xx.h"  /* CMSIS Cortex-M7 Device Peripheral Access Layer */
#include "hdulibstm32f7xxhalcan.h"    /* Header file of HAL CAN module. */
#include "hdulibstm32f7xxhalgpio.h"  /* Header files for GPIO HAL driver*/
#include "hdudispfarinc825.h"   /* Define the structure for an ARINC 825 Message. */
#include "hdudispfa825def.h" /* Arinc 825 functions and structures */
#include "hdulibstm32f7xx.h"    /* Cortex-M7 Device System Source File for STM32F7xx devices.*/
#include "hdulibbasictypes.h"  /* Standard basic data type definitions */
#include "hdulibstm32f7xxhalcortex.h" /* Header file of CORTEX HAL module */
#include "hdulibstmcorecomm.h"   /* Header files for Core Communication*/
#include "hdudispfucos.h"        /* uC/OS routines for the real-time kernel */
#include "hdulibstm32hallegacy.h" /* definition for the STM32Cube HAL */

#define PRESCLR_FOUR 4U
#define BANK_NO_14    14U

/* Counting sem to signal A825 input processing.      */
T_OS_EVENT *Sem_a8251_commtask = NULL;

/* Define transmit queues for the four main A825 channels (CAN1 and CAN2).       */

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



/* Define receive queues for the four main A825 channels.                        */

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

/* Handle for the CAN channel. */
static T_CAN_HANDLE   Can_handle = {0};

/* Single message for transmission and reception type. */
static T_CAN_TX_MSG_TYPE    Tx_message = {0};
static T_CAN_RX_MSG_TYPE    Rx_message = {0};

static void CANITConfig(T_CAN* can_x, T_UINT32 can_it, T_FUNCTIONAL_STATE new_state);
static T_UINT8 U8MailBoxAvail(T_CAN_HANDLE* h_can);
static T_A825_RECRESULT RxQueueRemove(T_A825_MESSAGE *ps_destination, T_CANRXQUEUE  *ps_which_q);
static T_A825_RECRESULT RxQueueInsert(T_CAN_RX_MSG_TYPE *ps_new_mess, T_CANRXQUEUE *ps_which_q);
static T_A825_XMITRESULT TxQueueInsert(T_CAN_TX_MSG_TYPE *ps_new_mess, T_CANTXQUEUE   *ps_which_q);
static T_UINT32 BuildBroadcastExtId(T_A825_MESSAGE *ps_xm);
static T_UINT32 BuildPeerToPeerExtId(T_A825_MESSAGE *ps_xm);
static T_UINT8 XmitFromBuff(T_CANTXQUEUE *ps_which_q);
static void CAN1Config(void);

/*    HELPER ROUTINES FOR PORT FROM STDPERIF TO HAL */

/*
 * Function                :  CANITConfig
 *
 * Description             :  This function enables or disables a specific interrupt
 *                            on a CAN controller.
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

static void CANITConfig(T_CAN* can_x, T_UINT32 can_it,  T_FUNCTIONAL_STATE new_state)
{
  if (new_state != DISABLE)
  {
    /* hdudispfarinc825perph1-CANITConfig-DB-LLR-001 */
    /* Enable the selected can_x interrupt */
    can_x->IER |= can_it;
  }
  else
  {
     /* hdudispfarinc825perph1-CANITConfig-DB-LLR-002 */
    /* Disable the selected can_x interrupt */
    can_x->IER &= ~can_it;
  }
}

/*
 * Function                :  U8MailBoxAvail
 *
 * Description             :  This function checks for available mail box.
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
   /* hdudispfarinc825perph1-U8MailBoxAvail-DB-LLR-001 */
   return (T_UINT8)(((CAN_TSR_TME0 == (h_can->Instance->TSR&CAN_TSR_TME0)) || \
   (CAN_TSR_TME1 == (h_can->Instance->TSR&CAN_TSR_TME1)) || \
   (CAN_TSR_TME2 == (h_can->Instance->TSR&CAN_TSR_TME2))));
}

/* ARINC 825 RECEIVE ROUTINES */

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

static T_A825_RECRESULT RxQueueRemove(T_A825_MESSAGE *ps_destination, T_CANRXQUEUE  *ps_which_q)
{
   T_CAN_RX_MSG_TYPE   can_message = {0};
   T_A825_MESSAGE arinc_message = {0};
   T_UINT8        u8_ctr = 0;

   if(ZERO == ps_which_q->RxCntr)
   {
      /* hdudispfarinc825perph1-RxQueueRemove-DB-LLR-001 */
      return(A825_RX_QUEUE_EMPTY);
   }
   else
   {
      /* Does nothing  */
   }

    /* hdudispfarinc825perph1-RxQueueRemove-DB-LLR-002 */
    /* Disable the CAN ReceiverTransmit Interrupt. */
    CANITConfig(CAN1, CAN_IT_FMP0, DISABLE);

   /* hdudispfarinc825perph1-RxQueueRemove-DB-LLR-003 */
   can_message = *(ps_which_q->RxHead);

   /* hdudispfarinc825perph1-RxQueueRemove-DB-LLR-004 */
   /* Adjust the head and check for a wrap.           */
   ps_which_q->RxCntr = (T_UINT16)( ps_which_q->RxCntr - ONE);
   ps_which_q->RxHead += ONE;

   if(ps_which_q->RxHead == &(ps_which_q->RxBuf[CAN_R_Q_SIZE]))
   {
      /* hdudispfarinc825perph1-RxQueueRemove-DB-LLR-005 */
      ps_which_q->RxHead = ps_which_q->RxBuf;
   }
   else
   {
      /* Does nothing  */
   }

   /* hdudispfarinc825perph1-RxQueueRemove-DB-LLR-006 */
   /* Enable the CAN Receiver Interrupt.              */
    CANITConfig(CAN1, CAN_IT_FMP0, ENABLE);

   /* hdudispfarinc825perph1-RxQueueRemove-DB-LLR-007 */
   /* TRANSLATE CAN MESSAGE TO A825 MESSAGE HERE.  */
   arinc_message.lcc = (can_message.ExtId>>LCC_LOC) & LCC_MSK;

   /* If this is a broadcast message.                    */
   if(NOC == arinc_message.lcc)
   {
      /* hdudispfarinc825perph1-RxQueueRemove-DB-LLR-008 */
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
      /* hdudispfarinc825perph1-RxQueueRemove-DB-LLR-009 */
      arinc_message.sID.PID.rci = (can_message.ExtId>>RCI_LOC) & RCI_MSK;
      arinc_message.sID.PID.pvt = (can_message.ExtId>>PVT_LOC) & PVT_MSK;
      arinc_message.sID.PID.lcl = (can_message.ExtId>>LCL_LOC) & LCL_MSK;
      arinc_message.sID.PID.sfid = (can_message.ExtId>>SER_FID_LOC) & SER_FID_MSK;
      arinc_message.sID.PID.cfid = (can_message.ExtId>>CFID_LOC) & CFID_MSK;
      arinc_message.sID.PID.smt = (can_message.ExtId>>SMT_LOC) & SMT_MSK;
      arinc_message.sID.PID.sid = (can_message.ExtId>>SID_LOC) & SID_MSK;
   }

   /* hdudispfarinc825perph1-RxQueueRemove-DB-LLR-010 */
   arinc_message.u8PaySize = (T_UINT8)can_message.DLC;
   if(arinc_message.u8PaySize > PAYLOAD_SIZE)
   {
      /* hdudispfarinc825perph1-RxQueueRemove-DB-LLR-011 */
      arinc_message.u8PaySize = PAYLOAD_SIZE;
   }
   else
   {
      /* Does nothing  */
   }

   /* Copy the payload.                         */
   for(u8_ctr = ZERO; u8_ctr < arinc_message.u8PaySize; u8_ctr++)
   {
      /* hdudispfarinc825perph1-RxQueueRemove-DB-LLR-012 */
      arinc_message.u8PayLoad[u8_ctr] = can_message.Data[u8_ctr];
   }

   /* hdudispfarinc825perph1-RxQueueRemove-DB-LLR-013 */
   *ps_destination = arinc_message;

   return(A825_RX_OK);
}

/*
 * Function                :  A8251GetMessage
 *
 * Description             :  This function Retrieve a message from the specified
 *                            communication channel.
 *
 * Formal parameter(s)     :  T_LCC_TYPE e_channel - IN channel type
 *                            T_A825_MESSAGE *ps_destination - IN destination message
 *
 * Return Value            :  T_A825_RECRESULT - Returns the state
 *
 * Assumption              :  None
 *
 */

T_A825_RECRESULT A8251GetMessage(T_LCC_TYPE e_channel, T_A825_MESSAGE *ps_destination)
{
   T_A825_RECRESULT result = A825_RX_NOT_IMPLEMENTED;

   switch(e_channel)
   {
      case NOC:
      {
         /* hdudispfarinc825perph1-A8251GetMessage-DB-LLR-001 */
         result = RxQueueRemove(ps_destination, &Noc_rx_queue);
         break;
      }
      case NSC:
      {
         /* hdudispfarinc825perph1-A8251GetMessage-DB-LLR-002 */
         result = RxQueueRemove(ps_destination, &Nsc_rx_queue);
         break;
      }
      default:
      {
         /* hdudispfarinc825perph1-A8251GetMessage-DB-LLR-003 */
         result = A825_RX_BAD_CHANNEL;
         break;
      }
   }

   /* hdudispfarinc825perph1-A8251GetMessage-DB-LLR-004 */
   return(result);
}

/*
 * Function                :  RxQueueInsert
 *
 * Description             :  This function inserts a CAN message into the selected queue.
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
   /* Check for buffer overflow.                            */
   if(CAN_R_Q_SIZE == ps_which_q->RxCntr)
   {
      /* hdudispfarinc825perph1-RxQueueInsert-DB-LLR-001 */
      return(A825_RX_OVERFLOW);
   }
   else
   {
      /* Does nothing */
   }

   /* hdudispfarinc825perph1-RxQueueInsert-DB-LLR-002 */
   /* Insert the new message.                               */
   *(ps_which_q->RxTail) = *ps_new_mess;

   /* hdudispfarinc825perph1-RxQueueInsert-DB-LLR-003 */
   /* Adjust the tail and check for a wrap.           */
   ps_which_q->RxCntr = (T_UINT16)( ps_which_q->RxCntr + ONE);
   ps_which_q->RxTail += ONE;

   if(ps_which_q->RxTail == &(ps_which_q->RxBuf[CAN_R_Q_SIZE]))
   {
      /* hdudispfarinc825perph1-RxQueueInsert-DB-LLR-004 */
      ps_which_q->RxTail = ps_which_q->RxBuf;
   }
   else
   {
      /* Does nothing */
   }

   /* hdudispfarinc825perph1-RxQueueInsert-DB-LLR-005 */
   return(A825_RX_OK);
}

/*
 * Function                :  CAN1Rx0IrqHandler
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

void CAN1Rx0IrqHandler(void)
{
   T_UINT32       lcc_val = ZERO;
   T_A825_RECRESULT  result = A825_RX_OK;

   /* hdudispfarinc825perph1-CAN1Rx0IrqHandler-DB-LLR-001 */
   /* Tell uCOS that we are entering the ISR */
   OsIntEnter();

   /* hdudispfarinc825perph1-CAN1Rx0IrqHandler-DB-LLR-002 */
   /* Retrieve the CAN message.                */
   HalCanReceive(&Can_handle, CAN_FIFO0, ZERO_TIMEOUT);

   /* hdudispfarinc825perph1-CAN1Rx0IrqHandler-DB-LLR-003 */
   /* Determine which logical communication channel.  */
   lcc_val = ((Rx_message.ExtId) >> LCC_LOC) & LCC_MSK;

   switch(lcc_val)
   {
      case NOC:
      {
         /* hdudispfarinc825perph1-CAN1Rx0IrqHandler-DB-LLR-004 */
         result = RxQueueInsert(&Rx_message, &Noc_rx_queue);
         if(A825_RX_OK == result )
         {
            OsSemPost(Sem_a8251_commtask);
         }
         break;
      }
      case NSC:
      {
         /* hdudispfarinc825perph1-CAN1Rx0IrqHandler-DB-LLR-005 */
         result = RxQueueInsert(&Rx_message, &Nsc_rx_queue);
         if(A825_RX_OK == result)
         {
            OsSemPost(Sem_a8251_commtask);
         }
         break;
      }
      default:
      {
         break;
      }
   }

   /* hdudispfarinc825perph1-CAN1Rx0IrqHandler-DB-LLR-007 */
   /* Tell uCOS that we are leaving the ISR */
   OsIntExit();
}

/* Queue Insert Routines */

/*
 * Function                :  TxQueueInsert
 *
 * Description             :  This function inserts a CAN message into the selected queue
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
   /* hdudispfarinc825perph1-TxQueueInsert-DB-LLR-001 */
   /* Disable the CAN Transmit Interrupt.*/
   CANITConfig(CAN1, CAN_IT_TME, DISABLE);

   /* Check for buffer overflow.          */
   if(CAN_X_Q_SIZE == ps_which_q->TxCntr )
   {
      /* hdudispfarinc825perph1-TxQueueInsert-DB-LLR-002 */
      /* Enable the CAN Transmit Interrupt.     */
      CANITConfig(CAN1, CAN_IT_TME, ENABLE);
      return(A825_XM_OVERFLOW);
   }
   else
   {
      /* Does nothing */
   }

   /* hdudispfarinc825perph1-TxQueueInsert-DB-LLR-003 */
   /* Insert the new message.    */
   *(ps_which_q->TxTail) = *ps_new_mess;

   /* hdudispfarinc825perph1-TxQueueInsert-DB-LLR-004 */
   /* Adjust the tail and check for a wrap.  */
   ps_which_q->TxCntr = (T_UINT16)( ps_which_q->TxCntr + ONE);
   ps_which_q->TxTail += ONE;

   if(ps_which_q->TxTail == &(ps_which_q->TxBuf[CAN_X_Q_SIZE]))
   {
      /* hdudispfarinc825perph1-TxQueueInsert-DB-LLR-005 */
      ps_which_q->TxTail = ps_which_q->TxBuf;
   }
   else
   {
      /* Does nothing */
   }

   /* hdudispfarinc825perph1-TxQueueInsert-DB-LLR-006 */
   /* Enable the CAN Transmit Interrupt.  */
    CANITConfig(CAN1, CAN_IT_TME, ENABLE);

   /* hdudispfarinc825perph1-TxQueueInsert-DB-LLR-007 */
   /* Check for immediate transmit. */
   CAN1TxIrqHandler();

   return(A825_XM_OK);
}

/*
 * Function                :  BuildBroadcastExtId
 *
 * Description             :  This function Build the 29 bit CAN identifier for an
 *                            ARINC 825 broadcast type message.
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

   /* hdudispfarinc825perph1-BuildBroadcastExtId-DB-LLR-001 */
   ext_id   = ((T_UINT32)((ps_xm->sID.BID).lcl) << LCL_LOC)
            | ((T_UINT32)((ps_xm->sID.BID).pvt) << PVT_LOC)
            |  ((T_UINT32)((ps_xm->sID.BID).doc) << DOC_LOC)
            | ((T_UINT32)((ps_xm->sID.BID).rci) << RCI_LOC)
            |  ((T_UINT32)((ps_xm->sID.BID).rsd) << RSD_LOC)
            |  ((T_UINT32)((ps_xm->sID.BID).sfid) << SRC_FID_LOC);

   ext_id |= ((T_UINT32)(ps_xm->lcc) << LCC_LOC);

   /* hdudispfarinc825perph1-BuildBroadcastExtId-DB-LLR-002 */
   return(ext_id);
}

/*
 * Function                :  BuildPeerToPeerExtId
 *
 * Description             :  This function Builds the 29 bit CAN identifier for an
 *                               ARINC 825 peer to peer type message.
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

   /* hdudispfarinc825perph1-BuildPeerToPeerExtId-DB-LLR-001 */
   ext_id   = ((T_UINT32)((ps_xm->sID.PID).cfid) << CFID_LOC)
            | ((T_UINT32)((ps_xm->sID.PID).smt) << SMT_LOC)
            |  ((T_UINT32)((ps_xm->sID.PID).lcl) << LCL_LOC)
            | ((T_UINT32)((ps_xm->sID.PID).pvt) << PVT_LOC)
            |  ((T_UINT32)((ps_xm->sID.PID).sfid) << SER_FID_LOC)
            | ((T_UINT32)((ps_xm->sID.PID).sid) << SID_LOC)
            |  ((T_UINT32)((ps_xm->sID.PID).rci) << RCI_LOC);

   ext_id |= ((T_UINT32)(ps_xm->lcc) << LCC_LOC);

   /* hdudispfarinc825perph1-BuildPeerToPeerExtId-DB-LLR-002 */
   return(ext_id);
}

/*
 * Function                :  A8251Xmit
 *
 * Description             :  This function Builds a CAN message from the user supplied
 *                            ARINC 825 message. Place the newly built CAN message in the
 *                            queue for that message type.
 *
 * Formal parameter(s)     :  T_A825_MESSAGE *ps_xm - IN Pointer to the ARINC 825 message
 *                            to transmit.
 *
 * Return Value            :  T_A825_XMITRESULT - transmit status
 *
 * Assumption              :  None
 *
 */

T_A825_XMITRESULT A8251Xmit(T_A825_MESSAGE *ps_xm)
{
   /* Updates as per PR 100156 */
   T_A825_XMITRESULT result   = A825_XM_NOT_IMPLEMENTED;

   T_UINT32    ext_id = 0; /* Used to build the A825 Extended ID. */
   T_UINT8        u8_ctr = 0;       /* Counter.                                        */
   T_CAN_TX_MSG_TYPE    temp_tx_message = {0};   /*    Message to be transmitted. */
   T_CANTXQUEUE   *p_tx_queue = (T_CANTXQUEUE *)NULL;   /* Pointer to message Q.   */

   /* Locate Q and build the 29 bit ID based on selected channel. */
   if (NOC == ps_xm->lcc )  /* Normal Operation Channel.  */
   {
      /* hdudispfarinc825perph1-A8251Xmit-DB-LLR-001 */
      p_tx_queue = &Noc_tx_queue;
      ext_id = BuildBroadcastExtId(ps_xm);
   }
   else if (NSC == ps_xm->lcc)   /* Node Service Channel.   */
   {
      /* hdudispfarinc825perph1-A8251Xmit-DB-LLR-002 */
      p_tx_queue = &Nsc_tx_queue;
      ext_id = BuildPeerToPeerExtId(ps_xm);
   }
   else  /* UNKNOWN Channel Type.      */
   {
      /* hdudispfarinc825perph1-A8251Xmit-DB-LLR-003 */
      return(A825_BAD_CHANNEL);
   }

   /* Check for too many payload bytes.   */
   if(ps_xm->u8PaySize > PAYLOAD_SIZE)
   {
      /* hdudispfarinc825perph1-A8251Xmit-DB-LLR-004 */
      return(A825_BAD_PAYLOAD_SIZE);
   }
   else
   {
      /* Does nothing */
   }

   /* hdudispfarinc825perph1-A8251Xmit-DB-LLR-005 */
   /* Fill in all of the CAN message data.                                     */
   temp_tx_message.ExtId = ext_id;             /* Set the extended ID. */
   temp_tx_message.IDE = CAN_ID_EXT;           /* A825 uses extended IDs only. */
   temp_tx_message.RTR = CAN_RTR_DATA;         /* This is *not* a remote frame. */
   temp_tx_message.DLC = ps_xm->u8PaySize;  /* Set the payload size.   */

   /* Copy the payload.                         */
   for(u8_ctr = 0; u8_ctr < ps_xm->u8PaySize; u8_ctr++)
   {
      /* hdudispfarinc825perph1-A8251Xmit-DB-LLR-006 */
      temp_tx_message.Data[u8_ctr] = ps_xm->u8PayLoad[u8_ctr];
   }

   /* hdudispfarinc825perph1-A8251Xmit-DB-LLR-007 */
   result = TxQueueInsert(&temp_tx_message, p_tx_queue);

   return(result);
}

/*  Queue Removal Routines */

/*
 * Function                :  XmitFromBuff
 *
 * Description             :  This function transmit a message from the
 *                            supplied queue when  a CAN mailbox is ready.
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
   if(ZERO != U8MailBoxAvail(&Can_handle))
   {
      /* hdudispfarinc825perph1-XmitFromBuff-DB-LLR-001 */
      *(Can_handle.pTxMsg) = *(ps_which_q->TxHead);
      HalCanTransmit(&Can_handle, ZERO_TIMEOUT);

      /* hdudispfarinc825perph1-XmitFromBuff-DB-LLR-002 */
      /* Adjust the tail and check for a wrap.           */
      ps_which_q->TxCntr = (T_UINT16)(ps_which_q->TxCntr - ONE);
      ps_which_q->TxHead += ONE;

      if(ps_which_q->TxHead == &(ps_which_q->TxBuf[CAN_X_Q_SIZE]))
      {
         /* hdudispfarinc825perph1-XmitFromBuff-DB-LLR-003 */
         ps_which_q->TxHead = ps_which_q->TxBuf;
      }
      else
      {
         /* Does nothing */
      }
      /* hdudispfarinc825perph1-XmitFromBuff-DB-LLR-004 */
      return(ONE);
   }
   else
   {
      /* hdudispfarinc825perph1-XmitFromBuff-DB-LLR-005 */
      return(ZERO);
   }
}

/*
 * Function                :  CAN1TxIrqHandler
 *
 * Description             :  This function checks the various transmit buffers.
 *
 * Formal parameter(s)     :  None
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */

void CAN1TxIrqHandler(void)
{
   /* hdudispfarinc825perph1-CAN1TxIrqHandler-DB-LLR-001 */
   while(Noc_tx_queue.TxCntr != ZERO)
   {
      if(ZERO == XmitFromBuff(&Noc_tx_queue))
      {
         /* hdudispfarinc825perph1-CAN1TxIrqHandler-DB-LLR-002 */
         return;
      }
      else
      {
         /* Does nothing */
      }
   }

   /* hdudispfarinc825perph1-CAN1TxIrqHandler-DB-LLR-003 */
   while(Nsc_tx_queue.TxCntr != ZERO)
   {
      if(ZERO == XmitFromBuff(&Nsc_tx_queue))
      {
         /* hdudispfarinc825perph1-CAN1TxIrqHandler-DB-LLR-004 */
         return;
      }
      else
      {
         /* Does nothing */
      }
   }

   /* hdudispfarinc825perph1-CAN1TxIrqHandler-DB-LLR-005 */
   /* If we reach here, all transmit queues are empty.   */
   CANITConfig(CAN1, CAN_IT_TME, DISABLE);
}

/*
 * Function                :  HalCanMspInit
 *
 * Description             :  This function configures the hardware resources used in
 *                            - Peripheral's clock enable
 *                            - Peripheral's GPIO Configuration
 *                            - NVIC configuration for DMA interrupt request enable
 *
 * Formal parameter        : T_CAN_HANDLEdleTypeDef *h_can - IN CAN handle pointer
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */

void HalCanMspInit(T_CAN_HANDLE *h_can)
{
   T_GPIO_INIT  gpio_init_struct ={0};

  if(CAN1 == h_can->Instance)
  {
      /* hdudispfarinc825perph1-HalCanMspInit-DB-LLR-001 */
      /*##-1- Enable peripherals and GPIO Clocks */
      /* CAN1 Periph clock enable */
      CAN1_CLK_ENABLE();
      /* Enable GPIO clock */
      CAN1_GPIO_CLK_ENABLE();

      /* hdudispfarinc825perph1-HalCanMspInit-DB-LLR-002 */
      /*##-2- Configure peripheral GPIO */
      /* CAN1 TX GPIO pin configuration */
      gpio_init_struct.Pin = CAN1_TX_PIN;
      gpio_init_struct.Mode = GPIO_MODE_AF_PP;
      gpio_init_struct.Speed = GPIO_SPEED_HIGH;
      gpio_init_struct.Pull = GPIO_PULLUP;
      gpio_init_struct.Alternate =  CAN1_TX_AF;

      HalGpioInit(CAN1_TX_GPIO_PORT, &gpio_init_struct);

      /* hdudispfarinc825perph1-HalCanMspInit-DB-LLR-003 */
      /* CAN1 RX GPIO pin configuration */
      gpio_init_struct.Pin = CAN1_RX_PIN;
      gpio_init_struct.Mode = GPIO_MODE_AF_PP;
      gpio_init_struct.Speed = GPIO_SPEED_HIGH;
      gpio_init_struct.Pull = GPIO_PULLUP;
      gpio_init_struct.Alternate =  CAN1_RX_AF;

      HalGpioInit(CAN1_RX_GPIO_PORT, &gpio_init_struct);

      /* hdudispfarinc825perph1-HalCanMspInit-DB-LLR-004 */
      /*##-3- Configure the NVIC */
      /* NVIC configuration for CAN1 Reception complete interrupt */
      HalNvicSetPriority(CAN1_RX0_IRQN, CAN1_RX_PRIORITY, 0);
      HalNvicSetPriority(CAN1_TX_IRQN, CAN1_TX_PRIORITY, 0);
      HalNvicEnableIrq(CAN1_RX0_IRQN);
      HalNvicEnableIrq(CAN1_TX_IRQN);
  }
  else if (CAN2 == h_can->Instance)
  {
      /* hdudispfarinc825perph1-HalCanMspInit-DB-LLR-005 */
      /*##-1- Enable peripherals and GPIO Clocks */
      /* CAN2 Periph clock enable */
      CAN2_CLK_ENABLE();
      /* Enable GPIO clock */
      CAN2_GPIO_CLK_ENABLE();

      /* hdudispfarinc825perph1-HalCanMspInit-DB-LLR-006 */
      /*##-2- Configure peripheral GPIO */
      /* CAN2 TX GPIO pin configuration */
      gpio_init_struct.Pin = CAN2_TX_PIN;
      gpio_init_struct.Mode = GPIO_MODE_AF_PP;
      gpio_init_struct.Speed = GPIO_SPEED_HIGH;
      gpio_init_struct.Pull = GPIO_PULLUP;
      gpio_init_struct.Alternate =  CAN2_TX_AF;

      HalGpioInit(CAN2_TX_GPIO_PORT, &gpio_init_struct);

      /* hdudispfarinc825perph1-HalCanMspInit-DB-LLR-007 */
      /* CAN2 RX GPIO pin configuration */
      gpio_init_struct.Pin = CAN2_RX_PIN;
      gpio_init_struct.Mode = GPIO_MODE_AF_PP;
      gpio_init_struct.Speed = GPIO_SPEED_HIGH;
      gpio_init_struct.Pull = GPIO_PULLUP;
      gpio_init_struct.Alternate =  CAN2_RX_AF;

      HalGpioInit(CAN2_RX_GPIO_PORT, &gpio_init_struct);

      /* hdudispfarinc825perph1-HalCanMspInit-DB-LLR-008 */
      /*##-3- Configure the NVIC */
      /* NVIC configuration for CAN2 Reception complete interrupt */
      HalNvicSetPriority(CAN2_RX0_IRQN, CAN2_RX_PRIORITY, 0);
      HalNvicSetPriority(CAN2_TX_IRQN, CAN2_TX_PRIORITY, 0);
      HalNvicEnableIrq(CAN2_RX0_IRQN);
      HalNvicEnableIrq(CAN2_TX_IRQN);
  }
  else
  {
     /* Does nothing */
  }
}

/*
 * Function                :  CAN1Config
 *
 * Description             :  This function configures the CAN
 *
 * Formal parameter(s)     :  None
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */

static void CAN1Config(void)
{
  T_CAN_FILTER_CONF_TYPE  s_filter_config = {0};

  /*hdudispfarinc825perph1-CAN1Config-DB-LLR-001*/
  /* Configure the CAN peripheral */
   Can_handle.Instance = CAN1;
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

  /* hdudispfarinc825perph1-CAN1Config-DB-LLR-002 */
  if (HalCanInit(&Can_handle) != HAL_OK)
  {
   while(TRUE)
   {
      ;/* Does nothing */
   }
  }
  else
  {
     /* Does nothing */
  }

  /* hdudispfarinc825perph1-CAN1Config-DB-LLR-003 */
  /* Configure the CAN Filter*/
  s_filter_config.FilterNumber = ZERO;
  s_filter_config.FilterMode = CAN_FILTERMODE_IDMASK;
  s_filter_config.FilterScale = CAN_FILTERSCALE_32BIT;
  s_filter_config.FilterIdHigh = ZERO;
  s_filter_config.FilterIdLow = ZERO;
  s_filter_config.FilterMaskIdHigh = ZERO;
  s_filter_config.FilterMaskIdLow = ZERO;
  s_filter_config.FilterFIFOAssignment = ZERO;
  s_filter_config.FilterActivation = ENABLE;
  s_filter_config.BankNumber = BANK_NO_14;

  /* hdudispfarinc825perph1-CAN1Config-DB-LLR-004 */
  if (HalCanConfigFilter(&Can_handle, &s_filter_config) != HAL_OK)
  {
   while(TRUE)
   {
      ;/* Does nothing */
   }
  }
  else
  {
     /* Does nothing */
  }

  /* hdudispfarinc825perph1-CAN1Config-DB-LLR-005 */
  /* Enable FIFO 0 message pending Interrupt */
  CANITConfig(CAN1, CAN_IT_FMP0, ENABLE);
}

/*
 * Function                :  CAN1DemoConfig
 *
 * Description             :  This function configures the CAN
 *
 * Formal parameter(s)     :  None
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */

void CAN1DemoConfig(void)
{
  T_CAN_FILTER_CONF_TYPE  s_filter_config = {0};

  /*hdudispfarinc825perph1-CAN1DemoConfig-DB-LLR-001*/
  /* Configure the CAN peripheral */
  Can_handle.Instance = CAN1;
  Can_handle.pTxMsg = &Tx_message;
  Can_handle.pRxMsg = &Rx_message;

  Can_handle.Init.TTCM = DISABLE;
  Can_handle.Init.ABOM = ENABLE;
  Can_handle.Init.AWUM = DISABLE;
  Can_handle.Init.NART = DISABLE;
  Can_handle.Init.RFLM = DISABLE;
  Can_handle.Init.TXFP = DISABLE;
  Can_handle.Init.Mode = CAN_MODE_LOOPBACK;
  Can_handle.Init.SJW  = CAN_SJW_1TQ;
  Can_handle.Init.BS1  = CAN_BS1_6TQ;
  Can_handle.Init.BS2  = CAN_BS2_7TQ;
  Can_handle.Init.Prescaler = PRESCLR_FOUR;

  /* hdudispfarinc825perph1-CAN1DemoConfig-DB-LLR-002 */
  if (HalCanInit(&Can_handle) != HAL_OK)
  {
   while(HalCanInit(&Can_handle) != HAL_OK)
   {
      ;/* Does nothing */
   }
  }
  else
  {
     /* Does nothing */
  }

  /* hdudispfarinc825perph1-CAN1DemoConfig-DB-LLR-003 */
  /* Configure the CAN Filter*/
  s_filter_config.FilterNumber = ZERO;
  s_filter_config.FilterMode = CAN_FILTERMODE_IDMASK;
  s_filter_config.FilterScale = CAN_FILTERSCALE_32BIT;
  s_filter_config.FilterIdHigh = ZERO;
  s_filter_config.FilterIdLow = ZERO;
  s_filter_config.FilterMaskIdHigh = ZERO;
  s_filter_config.FilterMaskIdLow = ZERO;
  s_filter_config.FilterFIFOAssignment = ZERO;
  s_filter_config.FilterActivation = ENABLE;
  s_filter_config.BankNumber = BANK_NO_14;

  /* hdudispfarinc825perph1-CAN1DemoConfig-DB-LLR-004 */
  if (HalCanConfigFilter(&Can_handle, &s_filter_config) != HAL_OK)
  {
   while(TRUE)
   {
     ;/* Does nothing */
   }
  }
  else
  {
     /* Does nothing */
  }

  /* hdudispfarinc825perph1-CAN1DemoConfig-DB-LLR-005 */
  /* Enable FIFO 0 message pending Interrupt */
  CANITConfig(CAN1, CAN_IT_FMP0, ENABLE);
}
/*
 * Function                :  A8251Init
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

void A8251Init(void)
{
   /* hdudispfarinc825perph1-A8251Init-DB-LLR-001 */
   /* Create a Sem to signaling the A825 receiver task.  */
   Sem_a8251_commtask = OsSemCreate(ZERO);

   /* hdudispfarinc825perph1-A8251Init-DB-LLR-002 */
   /* CAN configuration */
   CAN1Config();
}

