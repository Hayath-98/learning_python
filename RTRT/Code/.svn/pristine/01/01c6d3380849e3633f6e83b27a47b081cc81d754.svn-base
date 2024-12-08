/*
 ******************************************************************************
 * License Information  :  Howell Instruments, Inc.                           *
 *                         "Licensed Software" and "All rights reserved".     *
 ******************************************************************************
 *  File                : hdudispfarinc825.h
 *
 *  Description         : This file define the structure for an ARINC 825 Message
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
 *      1.1           Shilpa A R    25-Jul-2017             100064
 *      1.2           Vinay H       09-Oct-2017             100064
 *      1.3           Vinay H       23-Mar-2018             100196
 *
 * Additional References : None
 *
 ******************************************************************************
 */

#ifndef _HDUDISPFARINC825_H_
#define _HDUDISPFARINC825_H_

#include "hdudispfucos.h"       /* defines the implementation of uC/OS routines  */
#include "hdulibbasictypes.h" /* Standard basic data type definitions */

#define ZERO_TIMEOUT 0U
#define PAYLOAD_SIZE 8U

/* Define the structure of the ARINC 825 29 bit identifier for broadcast messages.*/
typedef struct
{
   unsigned sfid  :  7;    /* Source Fucntionial Identifier.                  */
   unsigned rsd   :  1;    /* Reserved = 0 for all One to Many.               */
   unsigned lcl   :  1;    /* local, = 1 if for this network segment only. */
   unsigned pvt   :  1;    /* = 1 if only for a subset of nodes.              */
   unsigned doc   :  14;      /* Data Object Code for the payload.            */
   unsigned rci   :  2;    /* Redundancy Channel ID.                          */
}  T_A825_BROADCAST_ID;

/* Define the structure of the ARINC 825 29 bit identifier for peer to peer messages.*/
typedef struct
{
   unsigned cfid  :  7;    /* Client Fucntional Identifier.                   */
   unsigned smt   :  1;    /* Service message type. 1 = request, 0 = responce.*/
   unsigned lcl   :  1;    /* = 1 if only for a subset of nodes.              */
   unsigned pvt   :  1;    /* Opaque data type.                               */
   unsigned sfid  :  7;    /* Server Functional Identifier.                   */
   unsigned sid   :  7;    /* Server Identifer (Node ID).                     */
   unsigned rci   :  2;    /* Redundancy Channel ID.                          */
}  T_A825_PEER_TO_PEER_ID;

/* Combine ID types.    */
typedef union
{
   T_A825_BROADCAST_ID  BID;
   T_A825_PEER_TO_PEER_ID  PID;
}  T_A825_ID;

/* Type for the Logical Communication Channel. */
typedef enum
{
   EEC = 0,       /* Exception Event Channel.  */
   NOC = 2,       /* Normal Opperating Channel.*/
   NSC   =  4,       /* Node Service Channel.  */
   UDC,           /* User Defined Channel.     */
   TMC,           /* Test and Maint. Channel.  */
   FMC               /* Frame Migration Channel.*/
}T_LCC_TYPE;

/* Type for generic ARINC 825 Message.    */
typedef struct
{
   T_LCC_TYPE              lcc;           /* Logical communication channel.*/
   T_A825_ID                  sID;        /* ID (less LCC).                */
   T_UINT8                 u8PaySize;     /* Number of bytes of payload.   */
   T_UINT8                 u8PayLoad[8];  /* Payload contents.             */
}T_A825_MESSAGE;

/* Return results for A825 transmit routines.   */
typedef enum
{
   A825_XM_OK = 0,
   A825_XM_OVERFLOW,
   A825_BAD_CHANNEL,
   A825_BAD_PAYLOAD_SIZE,
   A825_XM_NOT_IMPLEMENTED
} T_A825_XMITRESULT;

/* Return results for A825 Rec routines.  */
typedef enum
{
   A825_RX_OK = 0,
   A825_RX_OVERFLOW,
   A825_RX_BAD_CHANNEL,
   A825_RX_QUEUE_EMPTY,
   A825_RX_NOT_IMPLEMENTED
} T_A825_RECRESULT;

/* Which Bus to use. */
typedef enum
{
   A825_1,
   A825_2
} T_EA825BUS;

/* Counting sem to signal A825 input processing.   */
extern T_OS_EVENT *Sem_a8251_commtask;
extern T_OS_EVENT *Sem_a8252_commtask;

extern T_A825_RECRESULT A8251GetMessage(T_LCC_TYPE e_channel, T_A825_MESSAGE *ps_destination);
extern T_A825_RECRESULT A8252GetMessage(T_LCC_TYPE e_channel, T_A825_MESSAGE *ps_destination);

/* Build a CAN message from the user supplied ARINC 825 message. */

extern T_A825_XMITRESULT A8251Xmit(T_A825_MESSAGE *ps_xm);
extern T_A825_XMITRESULT A8252Xmit(T_A825_MESSAGE *ps_xm);

/* Perform initialization necessary for ARINC 825 communication. */
void A8251Init(void);
void A8252Init(void);

/* Forward Ref.      */
extern void CAN1TxIrqHandler(void);
extern void Can2TxIrqHandler(void);

/* Forward Ref.      */
extern void CAN1Rx0IrqHandler(void);
extern void Can2Rx0IrqHandler(void);
extern void CAN1DemoConfig(void);

#endif /* _HDUDISPFARINC825_H_ */
