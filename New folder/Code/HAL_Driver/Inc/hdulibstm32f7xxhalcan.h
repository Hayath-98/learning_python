/*
 ******************************************************************************
 * License Information  :  Howell Instruments, Inc.                           *
 *                         "Licensed Software" and "All rights reserved".     *
 ******************************************************************************
 *  File                : hdulibstm32f7xxhalcan.h
 *
 *  Description         : Header file of HAL CAN module.
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
 * <Version No.>     <Author>          <Date>         <Problem Report No.>
 *
 *      1.1          Rona B.S        12-Sep-2017          100064
 *      1.2          Divya G P       09-Oct-2017          100064
 *      1.3          Shruthi M N     16-Oct-2017          100083
 *      1.4          Shruthi M N     30-Oct-2017          100104
 *
 * Additional References : None
 *
 ******************************************************************************
 */

/* Define to prevent recursive inclusion */
#ifndef _HDULIBSTM32F7XXHALDCAN_H_
#define _HDULIBSTM32F7XXHALDCAN_H_

/* Includes*/
#include "hdulibstm32f7xxhaldma.h"  /* Header files for DMA HAL driver*/
#include "hdulibstm32f7xxhaldef.h"  /*Contains the HAL definition module */

typedef enum
{
  HAL_CAN_STATE_RESET             = 0x00U,  /* CAN not yet initialized or disabled */
  HAL_CAN_STATE_READY             = 0x01U,  /* CAN initialized and ready for use   */
  HAL_CAN_STATE_BUSY              = 0x02U,  /* CAN process is ongoing              */
  HAL_CAN_STATE_BUSY_TX           = 0x12U,  /* CAN process is ongoing              */
  HAL_CAN_STATE_BUSY_RX           = 0x22U,  /* CAN process is ongoing              */
  HAL_CAN_STATE_BUSY_TX_RX        = 0x32U,  /* CAN process is ongoing              */
  HAL_CAN_STATE_TIMEOUT           = 0x03U,  /* Timeout state                       */
  HAL_CAN_STATE_ERROR             = 0x04U   /* CAN error state                     */
}T_HAL_CAN_STATE_TYPE;

typedef struct
{
  T_UINT32 Prescaler;  /*
                        * Specifies the length of a time quantum.
                        * This parameter must be a number between Min_Data = 1
                        * and Max_Data = 1024
                        */

  T_UINT32 Mode;       /*
                        * Specifies the CAN operating mode.
                        */

  T_UINT32 SJW;        /*
                        * Specifies the maximum number of time quanta
                        * the CAN hardware is allowed to lengthen or
                        * shorten a bit to perform resynchronization.
                        * This parameter can be a value of CAN_synchronisation_jump_width
                        */

  T_UINT32 BS1;        /*
                        *  Specifies the number of time quanta in Bit Segment 1.
                        *  This parameter can be a value of CAN_time_quantum_in_bit_segment_1
                        */

  T_UINT32 BS2;        /*
                        *  Specifies the number of time quanta in Bit Segment 2.
                        *  This parameter can be a value of CAN_time_quantum_in_bit_segment_2
                        */

  T_UINT32 TTCM;       /*
                        *  Enable or disable the time triggered communication mode.
                        *  This parameter can be set to ENABLE or DISABLE.
                        */

  T_UINT32 ABOM;       /*
                        *  Enable or disable the automatic bus-off management.
                        *  This parameter can be set to ENABLE or DISABLE
                        */

  T_UINT32 AWUM;       /*
                        *  Enable or disable the automatic wake-up mode.
                        *  This parameter can be set to ENABLE or DISABLE
                        */

  T_UINT32 NART;       /*
                        *  Enable or disable the non-automatic retransmission mode.
                        *  This parameter can be set to ENABLE or DISABLE
                        */

  T_UINT32 RFLM;       /*
                        *  Enable or disable the receive FIFO Locked mode.
                        *  This parameter can be set to ENABLE or DISABLE
                        */

  T_UINT32 TXFP;       /*
                        *  Enable or disable the transmit FIFO priority.
                        *  This parameter can be set to ENABLE or DISABLE
                        */
}T_CAN_INIT_TYPE;


typedef struct
{
  T_UINT32 FilterIdHigh;        /*
                                 * Specifies the filter identification number (MSBs for a 32-bit
                                 * configuration, first one for a 16-bit configuration).
                                 * This parameter must be a number between Min_Data = 0x0000
                                 * and Max_Data = 0xFFFF
                                 */

  T_UINT32 FilterIdLow;         /*
                                 * Specifies the filter identification number (LSBs for a 32-bit
                                 * configuration, second one for a 16-bit configuration).
                                 * This parameter must be a number between Min_Data = 0x0000
                                 * and Max_Data = 0xFFFF
                                 */

  T_UINT32 FilterMaskIdHigh;    /*
                                 * Specifies the filter mask number or identification number,
                                 * according to the mode (MSBs for a 32-bit configuration,
                                 * first one for a 16-bit configuration).
                                 * This parameter must be a number between Min_Data = 0x0000
                                 * and Max_Data = 0xFFFF
                                 */


  T_UINT32 FilterMaskIdLow;     /*
                                 * Specifies the filter mask number or identification number,
                                 * according to the mode (LSBs for a 32-bit configuration,
                                 * second one for a 16-bit configuration).
                                 * This parameter must be a number between Min_Data = 0x0000
                                 * and Max_Data = 0xFFFF
                                 */

  T_UINT32 FilterFIFOAssignment;/*
                                 * Specifies the FIFO (0 or 1) which will be assigned
                                 * to the filter.
                                 */

  T_UINT32 FilterNumber;        /*
                                 * Specifies the filter which will be initialized.
                                 * This parameter must be a number between Min_Data = 0
                                 * and Max_Data = 27
                                 */

  T_UINT32 FilterMode;          /*
                                 * Specifies the filter mode to be initialized.
                                 */

  T_UINT32 FilterScale;         /*
                                 * Specifies the filter scale.
                                 */

  T_UINT32 FilterActivation;    /*
                                 * Enable or disable the filter.
                                 * This parameter can be set to ENABLE or DISABLE.
                                 */

  T_UINT32 BankNumber;          /*
                                 * Select the start slave bank filter.
                                 * This parameter must be a number between Min_Data = 0
                                 * and Max_Data = 28
                                 */

}T_CAN_FILTER_CONF_TYPE;


typedef struct
{
  T_UINT32 StdId;    /*
                      *  Specifies the standard identifier.
                      *  This parameter must be a number between Min_Data = 0
                      *  and Max_Data = 0x7FF
                      */

  T_UINT32 ExtId;    /*
                      *  Specifies the extended identifier.
                      *  This parameter must be a number between Min_Data = 0
                      *  and Max_Data = 0x1FFFFFFF
                      */

  T_UINT32 IDE;      /*
                      *  Specifies the type of identifier for the message
                      *  that will be transmitted.
                      */

  T_UINT32 RTR;      /*
                      *  Specifies the type of frame for the message that will be transmitted.
                      */

  T_UINT32 DLC;      /*
                      *  Specifies the length of the frame that will be transmitted.
                      *  This parameter must be a number between Min_Data = 0 and Max_Data = 8
                      */

  T_UINT8 Data[8];   /*
                      *  Contains the data to be transmitted.
                      *  This parameter must be a number between Min_Data = 0 and Max_Data = 0xFF
                      */

}T_CAN_TX_MSG_TYPE;

typedef struct
{
  T_UINT32 StdId;      /*
                        * Specifies the standard identifier.
                        * This parameter must be a number between Min_Data = 0
                        * and Max_Data = 0x7FF
                        */

  T_UINT32 ExtId;      /*
                        * Specifies the extended identifier.
                        * This parameter must be a number between Min_Data = 0 and
                        * Max_Data = 0x1FFFFFFF
                        */

  T_UINT32 IDE;        /*
                        * Specifies the type of identifier for the message that will be received.
                        */

  T_UINT32 RTR;        /*
                        * Specifies the type of frame for the received message.
                        */

  T_UINT32 DLC;        /*
                        * Specifies the length of the frame that will be received.
                        * This parameter must be a number between Min_Data = 0 and Max_Data = 8
                        */

  T_UINT8 Data[8];     /*
                        * Contains the data to be received.
                        * This parameter must be a number between Min_Data = 0
                        * and Max_Data = 0xFF
                        */

  T_UINT32 FMI;        /*
                        * Specifies the index of the filter the message stored in
                        * the mailbox passes through. This parameter must be a number between
                        * Min_Data = 0 and Max_Data = 0xFF.
                        */

  T_UINT32 FIFONumber; /*
                        * Specifies the receive FIFO number.
                        * This parameter can be CAN_FIFO0 or CAN_FIFO1
                        */

}T_CAN_RX_MSG_TYPE;

typedef struct
{
  T_CAN                 *Instance;  /* Register base address          */

  T_CAN_INIT_TYPE       Init;       /* CAN required parameters        */

  T_CAN_TX_MSG_TYPE*    pTxMsg;     /* Pointer to transmit structure  */

  T_CAN_RX_MSG_TYPE*    pRxMsg;     /* Pointer to reception structure */

  T_HAL_CAN_STATE_TYPE    State;      /* CAN communication state        */

  T_HAL_LOCK            Lock;       /* CAN locking object             */

  T_UINT32              ErrorCode;  /* CAN Error code                 */

}T_CAN_HANDLE;


/* No error*/
#define  HAL_CAN_ERROR_NONE         0x00U

/* CAN initialization failed */
#define  CAN_INITSTATUS_FAILED      ((T_UINT8)0x00U)

/* CAN initialization OK */
#define  CAN_INITSTATUS_SUCCESS     ((T_UINT8)0x01U)

/* Normal mode   */
#define  CAN_MODE_NORMAL            ((T_UINT32)0x00000000U)

/* Loopback mode */
#define  CAN_MODE_LOOPBACK          ((T_UINT32)CAN_BTR_LBKM)

/* 1 time quantum */
#define  CAN_SJW_1TQ                ((T_UINT32)0x00000000U)

/* 6 time quantum  */
#define  CAN_BS1_6TQ                ((T_UINT32)(CAN_BTR_TS1_2 | CAN_BTR_TS1_0))

/* 7 time quantum */
#define  CAN_BS2_7TQ                ((T_UINT32)(CAN_BTR_TS2_2 | CAN_BTR_TS2_1))

/* Identifier mask mode */
#define CAN_FILTERMODE_IDMASK       ((T_UINT8)0x00U)

/* Two 16-bit filters */
#define CAN_FILTERSCALE_16BIT       ((T_UINT8)0x00U)

/* One 32-bit filter  */
#define CAN_FILTERSCALE_32BIT       ((T_UINT8)0x01U)

/* Filter FIFO 0 assignment for filter x */
#define CAN_FILTER_FIFO0            ((T_UINT8)0x00U)

/* Filter FIFO 1 assignment for filter x */
#define CAN_FILTER_FIFO1            ((T_UINT8)0x01U)

/* Standard Id */
#define CAN_ID_STD                  ((T_UINT32)0x00000000U)

/* Extended Id */
#define CAN_ID_EXT                  ((T_UINT32)0x00000004U)

/* Data frame */
#define CAN_RTR_DATA                ((T_UINT32)0x00000000U)

/* Remote frame */
#define CAN_RTR_REMOTE              ((T_UINT32)0x00000002U)

/* CAN FIFO 0 used to receive */
#define CAN_FIFO0                   ((T_UINT8)0x00U)

/* CAN FIFO 1 used to receive */
#define CAN_FIFO1                   ((T_UINT8)0x01U)

/* Transmit mailbox empty interrupt */
#define CAN_IT_TME                  ((T_UINT32)CAN_IER_TMEIE)

 /* FIFO 0 message pending interrupt */
#define CAN_IT_FMP0                 ((T_UINT32)CAN_IER_FMPIE0)

/* Operating Mode Interrupts */
#define CAN_TXMAILBOX_0   ((T_UINT8)0x00U)
#define CAN_TXMAILBOX_1   ((T_UINT8)0x01U)
#define CAN_TXMAILBOX_2   ((T_UINT8)0x02U)

#define __HAL_CAN_MSG_PENDING(__HANDLE__, __FIFONUMBER__) (((__FIFONUMBER__) == CAN_FIFO0)? \
((T_UINT8)((__HANDLE__)->Instance->RF0R&(T_UINT32)0x03)) : \
((T_UINT8)((__HANDLE__)->Instance->RF1R&(T_UINT32)0x03)))

#define __HAL_CAN_TRANSMIT_STATUS(__HANDLE__, __TRANSMITMAILBOX__)\
(((__TRANSMITMAILBOX__) == CAN_TXMAILBOX_0)? ((((__HANDLE__)->Instance->TSR) & \
(CAN_TSR_RQCP0 | CAN_TSR_TXOK0 | CAN_TSR_TME0)) == \
(CAN_TSR_RQCP0 | CAN_TSR_TXOK0 | CAN_TSR_TME0)) :\
 ((__TRANSMITMAILBOX__) == CAN_TXMAILBOX_1)? ((((__HANDLE__)->Instance->TSR) \
 & (CAN_TSR_RQCP1 | CAN_TSR_TXOK1 | CAN_TSR_TME1)) == \
 (CAN_TSR_RQCP1 | CAN_TSR_TXOK1 | CAN_TSR_TME1)) :\
 ((((__HANDLE__)->Instance->TSR) & (CAN_TSR_RQCP2 | CAN_TSR_TXOK2 | CAN_TSR_TME2)) == \
 (CAN_TSR_RQCP2 | CAN_TSR_TXOK2 | CAN_TSR_TME2)))

#define __HAL_CAN_FIFO_RELEASE(__HANDLE__, __FIFONUMBER__) (((__FIFONUMBER__) == CAN_FIFO0)? \
      ((__HANDLE__)->Instance->RF0R = CAN_RF0R_RFOM0) : \
      ((__HANDLE__)->Instance->RF1R = CAN_RF1R_RFOM1))

#define CAN_TXSTATUS_NOMAILBOX      ((T_UINT8)0x04U)

/* Initialization/de-initialization functions*/
extern T_HAL_STATUS HalCanInit(T_CAN_HANDLE* h_can);
extern T_HAL_STATUS HalCanConfigFilter(T_CAN_HANDLE* h_can,
            T_CAN_FILTER_CONF_TYPE* filter_config);
extern T_HAL_STATUS HalCanTransmit(T_CAN_HANDLE* h_can, T_UINT32 time_out);
extern T_HAL_STATUS HalCanReceive(T_CAN_HANDLE* h_can, T_UINT8 fifo_number,
            T_UINT32 time_out);
extern void HalCanMspInit(T_CAN_HANDLE *h_can);

#endif /* _HDULIBSTM32F7XXHALCAN_H_ */

