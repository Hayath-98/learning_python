/*
 ******************************************************************************
 * License Information  :  Howell Instruments, Inc.                           *
 *                         "Licensed Software" and "All rights reserved".     *
 ******************************************************************************
 *  File                : hdudispfa825def.h
 *
 *  Description         : Definitions for arinc 825 communication
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
 *      1.3           Vinay H       23-Mar-2018             100196
 *
 * Additional References : None
 *
 ******************************************************************************
 */

#ifndef _HDUDISPFA825DEF_H_
#define _HDUDISPFA825DEF_H_

#include "hdulibstm32f7xxhalcan.h" /*Contains CAN prototypes */

/* Define the location of the various bit fields in the 825 Ident Struct */

/* For all Messages.          */
#define  RCI_LOC        0U          /* Redundancy channel identifier.   */
#define RCI_MSK         3U

#define  LCC_LOC        26U         /* Logical communication channel.   */
#define  LCC_MSK        7U

#define  PVT_LOC        16U         /* Private.                         */
#define PVT_MSK         1U

#define  LCL_LOC        17U         /* Local.                           */
#define  LCL_MSK        1U

/* For Broadcast Messages.       */
#define  DOC_LOC        2U          /* Data Object Code.                */
#define  DOC_MSK        0x3FFFU

#define  RSD_LOC        18U         /* Reserved = 0.                    */
#define  RSD_MSK        1U

#define  SRC_FID_LOC    19U         /* Source Function Ident.           */
#define SRC_FID_MSK     0x7FU

/* For Peer to Peer Messages. */
#define SID_LOC         2U          /* Server ID (Node #)               */
#define SID_MSK         0x7FU

#define SER_FID_LOC     9U          /* Server Functional Ident.         */
#define SER_FID_MSK     0x7FU

#define SMT_LOC         18U         /* Service Message Type.            */
#define SMT_MSK         1U

#define CFID_LOC     19U         /* Client Functional Ident.            */
#define CFID_MSK     0x7FU

/* Define Transmit message Queue Size. */
#define CAN_X_Q_SIZE    120U

/*
 * Define Receive message Queue Size.
 * At maximum bus speed, shortest message length, and 100% bus
 * loading, 250 messages will allow 0.016 seconds from empty
 * to full.  Recommend 10 mS max for buffer service.
 */
#define CAN_R_Q_SIZE    160U

/* Queue for the CAN transmitter.  */
typedef  struct
{
   T_UINT16    TxCntr;                    /* Number of messages in the Tx queue.    */
   T_CAN_TX_MSG_TYPE   *TxHead;                /* Next message to remove (transmit).*/
   T_CAN_TX_MSG_TYPE   *TxTail;                /* Next message to insert.           */
   T_CAN_TX_MSG_TYPE   TxBuf[CAN_X_Q_SIZE];    /* Tx buffer.                    */
}T_CANTXQUEUE;

/* Queue for the CAN receiver. */
typedef  struct
{
   T_UINT16    RxCntr;                    /* Number of messages in the Rx queue.    */
   T_CAN_RX_MSG_TYPE   *RxHead;                /* Next message to remove (receive). */
   T_CAN_RX_MSG_TYPE   *RxTail;                /* Next message to insert.           */
   T_CAN_RX_MSG_TYPE   RxBuf[CAN_R_Q_SIZE];/* Rx buffer.          */
}T_CANRXQUEUE;


#endif /* _HDUDISPFA825DEF_H_ */
