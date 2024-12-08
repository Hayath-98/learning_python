/*
 ******************************************************************************
 * License Information  :  Howell Instruments, Inc.                           *
 *                         "Licensed Software" and "All rights reserved".     *
 ******************************************************************************
 *  File                : hdudispfdauprofile.h
 *
 *  Description         : This file contains defines the constants for ARINC 825
 *                        Message Traffic.
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
 *  Author(s)           : Rona B.S
 *
 *  Version History     :
 *
 * <Version No.>     <Author>          <Date>         <Problem Report No.>
 *
 *      1.1          Rona B.S        11-Sep-2017             100064
 *      1.2          Rona B.S        10-Oct-2017             100064
 *      1.3          Shruthi M N     13-Oct-2017             100083
 *      1.4          Vinay H         23-Mar-2018             100196
 *      1.5          Dhanalakshmi D  21-Jun-2020             100259
 *      1.6          Rona B S        01-Jul-2020             100259
 *      1.7          Dhanalakshmi    05-Aug-2020             100270
 *      1.8          Dhanalakshmi    20-Mar-2021             100331
 *      1.9          Dhanalakshmi    20-Mar-2021             100331
 *
 * Additional References : None
 *
 *****************************************************************************
 */

#ifndef _HDUDISPFDAUPROFILE_H_
#define _HDUDISPFDAUPROFILE_H_


/* Define the Profile ID and Profile Sub-ID for use in NIS response. */
#define PROFILE_ID         1
#define PROFILE_SUB_ID     0

/* This FID is predefined by ARINC 825 */
#define  MULTICAST_FID     0

/*
 * This is the Functional ID for the Howell DAU.As Per ARINC 825 this FID
 * is reserved for the System Integrator.
 */
#define  HOWELL_DAU_FID 42

/*
 *  Following are the "Server" IDs that provide a unique identifier for
 *  each of the nodes that can be included in the network.  The id's are
 *  used when   performing peer to peer communications.
 *
 */

typedef enum
{
   MULTICAST_SID = 0,   /* Predefined by A825.                */
   GATEWAY_SID,         /* The system gateway/master node.    */
   ANALOG_SID,          /* The "main" data acquisition node.  */
   DIU_SID,             /* The discrete interface node.       */
   DAC_SID,             /* The DAC (Analog Out) node.         */
   LOGGER_SID,          /* The data logger (monitor) node.    */
   CONFIG_SID,          /* The config/bridge node.            */
   EISDSPLY_SID,        /* Engine information display node.   */
   EISDSPLYGATEWAY_SID  /* Gateway for xxx -> A825 conversion.*/
}  T_VAL_SID;             /* ENUM Server ID.                    */

/* These are the Node Service Codes (used on the node service channel). */
typedef enum
{
  /* A825 Predefined Node Service Codes. */
  NSC_IDS, NSC_NSS, NSC_DUS, NSC_DDS,
  NSC_BCS, NSC_NVS, NSC_NIS, NSC_SCS,

  /* User defined codes begin here.            */
  NSC_SET_RCI = 49152,    /* Set on side modules to a specific RCI. */
  NSC_SET_DOUT1,          /* Set discrete outputs 1-24.             */
  NSC_SET_DOUT2,          /* Set discrete outputs 25-48.            */
  NSC_GET_CM_RCI,         /* CM to transmit its RCI, OP, VAL        */
  NSC_EXCITE_SWITCH,      /* Excitation ON or OFF                   */
  NSC_CHIP_BURN,          /* Chip Burn off                          */

  NSC_CLEAR_MEM,
  NSC_SEND_A429,
  NSC_PULL_MEM,
  NSC_PUSH_MEM,

  NSC_SWITCH_SCREEN,
  NSC_TIMER_START,
  NSC_TIMER_STOP,
  NSC_TIMER_RESET,
  NSC_SET_EIU,
  NSC_COOL_TIMER_STATE,
  NSC_PULL_RESEND,
  NSC_SYS_RESET,
  NSC_CALIBRATION = 49176,
  NSC_FUEL_FLOW_STATE
} T_NSC_CODE;


#define  MY_RCI   0

/* Initialize a Normal Op Channel message to its default values.       */
#define INIT_NOC_MESSAGE(x)  \
{        \
   x.lcc = NOC;                        /* Normal Opp Channel.          */ \
   x.sID.BID.sfid = HOWELL_DAU_FID;    /* Functional ID is Howell DAU. */ \
   x.sID.BID.rsd     = 0;              /* RDS = 0 for all broadcast.   */ \
   x.sID.BID.lcl     = 1;              /* Message is local to seg.     */ \
   x.sID.BID.pvt     = 1;              /* Message is private.          */ \
   x.sID.BID.doc     = 0;              /* Default Data Object code.    */ \
   x.sID.BID.rci     = MY_RCI;         /* Supply Redundancy Code.      */ \
   x.u8PaySize       = 0;              /* Default 0 bytes of payload.  */ \
}

/* Initialize a Node Service Channel message to its default values.*/
#define INIT_NSC_REQUEST(x)  \
{        \
   x.lcc = NSC;                          /* Node Service Channel.*/     \
   x.sID.PID.cfid = HOWELL_DAU_FID;      /* Client FID is Howell DAU.*/ \
   x.sID.PID.smt = 1;                    /* Request Message Type.*/     \
   x.sID.PID.lcl = 1;                    /* Message is local to seg.*/  \
   x.sID.PID.pvt = 1;                    /* Message is private.*/       \
   x.sID.PID.sfid = HOWELL_DAU_FID;      /* Server functional ID.*/       \
   x.sID.PID.sid = MULTICAST_SID;        /* Server Identifier (Node ID).*/\
   x.sID.PID.rci = MY_RCI;               /* Default Redundancy Code.*/    \
   x.u8PaySize = 2;                      /* Default 2 bytes of payload.*/ \
}

#define MAX_GENERIC_TRIGGER_DOCS       50
#define MAX_APP_SPECIFIC_TRIGGER_DOCS  50
#define MAX_GENERIC_PACKED_DOCS        200

#define  GENERIC_TRIGGER_DOC_START   0

#define  APPLIC_TRIGGER_DOC_START   GENERIC_TRIGGER_DOC_START +\
                                                         MAX_GENERIC_TRIGGER_DOCS

#define  GENERIC_PACKED_DOC_START   APPLIC_TRIGGER_DOC_START +\
                                                         MAX_APP_SPECIFIC_TRIGGER_DOCS

#define  APPLIC_PACKED_DOC_START    GENERIC_PACKED_DOC_START +\
                                                         MAX_GENERIC_PACKED_DOCS

typedef enum
{
   /*GENERIC TRIGGER DOCs*/

   /* Signal nodes to send acquired data. */
   ACQUIRE = GENERIC_TRIGGER_DOC_START,
   HEART_BEAT,

   /*APPLICATION SPECIFIC TRIGGER DOCs*/

   /* Trigger acquisition of off side excitation voltage.*/
   SEND_OSV =  APPLIC_TRIGGER_DOC_START,

   /*GENERIC PACKED DOCs*/

   /* 192 Discrete Input Channels packed 1 discrete per bit.*/
   DISCI_1_64 = GENERIC_PACKED_DOC_START,
   DISCI_65_128,
   DISCI_129_192,

   /* Discrete outputs 1 thru 24*/
   DISCO_1_32,
   DISCO_33_64,
   DISCO_1_64_STAT,

   /* Low Level Voltage Inputs*/
   LLDCI_1_4,     LLDCI_5_8,     LLDCI_9_12,    LLDCI_13_16,
   LLDCI_17_20,   LLDCI_21_24,   LLDCI_25_28,   LLDCI_29_32,

   /* Two bits of status for each low level channel.*/
   LLDCI_1_32_STAT,

   /* Low Level Voltage Inputs*/
   HLDCI_1_4,     HLDCI_5_8,     HLDCI_9_12,    HLDCI_13_16,
   HLDCI_17_20,   HLDCI_21_24,   HLDCI_25_28,   HLDCI_29_32,

   /* Two bits of status for each high level channel.*/
   HLDCI_1_32_STAT,

   /* Three wire RTD Inputs.*/
   RTDI_1_4, RTDI_5_8, RTDI_9_12, RTDI_13_16,

   /* Two bits of status for each RTD channel.*/
   RTDI_1_16_STAT,

   /* 16 Tach Channels packed 4 per message.\*/
   TACH_1_4, TACH_5_8, TACH_9_12, TACH_13_16,

   /* Two bits of status for each high level channel.*/
   TACH_1_16_STAT,

   /* 8 Fuel Flow Channels packed 4 per message.*/
   FF_1_4, FF_5_8,

   /* Two bits of status for each Fuel Flow channel.*/
   FF_1_8_STAT,

   /* 8 RMS to DC Channels packed 4 per message.*/
   RMS_1_4, RMS_5_8,

   /* Two bits of status for each RMS to DC channel.*/
   RMS_1_8_STAT,

   /* 4 Reference Junction Channels packed 4 per message.*/
   REFJ_1_4,

   /* Two bits of status for each REFJ channel.*/
   REFJ_1_4_STAT,

   /* Chip Detector Status.*/
   CHIP_DETC_1_8,

   /* Synchro channel labels.*/
   SYNCHRO_1_4, SYNCHRO_5_8, SYNCHRO_9_12, SYNCHRO_13_16,
   SYNCHRO_17_20, SYNCHRO_21_24, SYNCHRO_25_28, SYNCHRO_29_32,

   /* Two bits of status for each SYNCHOR channel.*/
   SYNCHRO_1_32_STAT,

   /* ARINC429 channel labels.*/
   A429_1_4, A429_5_8, A429_9_12, A429_13_16,
   A429_17_20, A429_21_24, A429_25_28, A429_29_32,

   /* Two bits of status for each ARINC429 channel*/
   A429_1_32_STAT,

   /* Raw transmission of A429*/
   A429_CHAN_1,
   A429_CHAN_2,

   /* Display F4 Application SOftware PN and CRC */
   DIS_COMAPP_REVNO1,
   DIS_COMAPP_REVNO2,
   DIS_COMAPP_CRC,

   /* Display F4 Bootloader SOftware PN and CRC */
   DIS_COMBOOT_REVNO1,
   DIS_COMBOOT_REVNO2,
   DIS_COMBOOT_CRC,

   /* Display F4 Maint SOftware PN and CRC */
   DIS_COMMAINT_REVNO1,
   DIS_COMMAINT_REVNO2,
   DIS_COMMAINT_CRC,
   F4_PBIT_ERR =172,
   F4_CBIT_ERR =173,
   DIS_PEAK_ID,
   DIS_PEAK_DATA,
   DIS_PEAK_DUR,

   /* Display F4 Software Loader PN and CRC */
   DIS_COMSL_REVNO1,
   DIS_COMSL_REVNO2,
   DIS_COMSL_CRC,

   /* Display Fault log */
   DIS_FAULT_LOG, /* Flight no, fault type, error code, WOG */
   DIS_FAULT_TIMESTAMP, /* duration of fault */
   DIS_FAULT_PARAM_WOG, /* status of WOG during fault */
   DIS_FAULT_PARAM_TRQ, /* value of TRQ during fault */
   DIS_FAULT_PARAM_N2, /* value of N2 during fault */
   DIS_FAULT_PARAM_EOP, /* value of EOP during fault */
   DIS_FAULT_PARAM_TOT, /* value of TOT during fault */
   DIS_FAULT_PARAM_BUSV /* value of BUSV during fault */

}  T_VAL_DOC; /* Data Object Codes.   */

#endif /*_HDUDISPFDAUPROFILE_H*/
