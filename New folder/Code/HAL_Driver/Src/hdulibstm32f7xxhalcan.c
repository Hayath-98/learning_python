/*
 ******************************************************************************
 * License Information  :  Howell Instruments, Inc.                           *
 *                         "Licensed Software" and "All rights reserved".     *
 ******************************************************************************
 *  File                : hdulibstm32f7xxhalcan.c
 *
 *  Description         : This file provides firmware functions to manage the following
 *                        functionalities of the Controller Area Network (CAN) peripheral:
 *                        1. Initialization and de-initialization functions
 *                        2. IO operation functions
 *                        3. Peripheral Control functions
 *                        4. Peripheral State and Error functions
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
 *      1.1          Rona B.S          12-Sep-2017            100064
 *      1.2          Divya G P         09-Oct-2017            100064
 *      1.3          Shruthi M N       30-Oct-2017            100104
 *      1.4          Rona B.S          12-Sep-2020            100276  
 *
 * Additional References : None
 *
 ******************************************************************************
 */

/*Includes*/
#include "hdulibstm32f746xx.h" /* CMSIS STM32F7xx Device Peripheral Access Layer file*/
#include "hdulibstm32f7xxhalcan.h" /* Defines CAN specification */
#include "hdulibstm32f7xxhalconf.h" /* contains HAL common defines,enum,macro and structures */
#include "hdulibstm32f7xxhal.h" /* Header files for HAL driver*/
#include "hdulibstm32f7xx.h" /* CMSIS STM32F7xx Device Peripheral Access Layer file*/
#include "hdulibbasictypes.h" /* Define standard data types */
#include "hdulibstm32f7xxhaldef.h"     /*Contains the HAL definition module */
#include "hdulibcorecm7.h"    /* Cortex-M7 processor and core peripherals */

#define CAN_TIMEOUT_VALUE  10U
#define HEX_7FF            0x000007FFU
#define HEX_1FFFFFFF       0x1FFFFFFFU
#define HEX_FFFFFFF0       0xFFFFFFF0U
#define HEX_FFFF           0x0000FFFFU

/*
 * Function                : HalCanInit
 *
 * Description             : The function initializes the CAN peripheral according to the specified
 *                           parameters in the T_CAN_HANDLE.
 *
 * Formal parameter(s)     : T_CAN_HANDLE* h_can -INOUT pointer to a T_CAN_HANDLE structure
 *                           that contains the configuration information for the specified CAN.
 *
 * Return Value            : T_HAL_STATUS - HAL status
 *
 * Assumption              : None
 *
 */

T_HAL_STATUS HalCanInit(T_CAN_HANDLE* h_can)
{
  T_UINT32 init_status = CAN_INITSTATUS_FAILED;
  T_UINT32 tick_start = ZERO;

   /* Check CAN handle */
   if(NULL == h_can)
   {
      /*hdulibstm32f7xxhalcan-HalCanInit-DB-LLR-001*/
      return HAL_ERROR;
   }
   else
   {
      ; /* Do nothing */
   }

   if(HAL_CAN_STATE_RESET == h_can->State)
   {
      /*hdulibstm32f7xxhalcan-HalCanInit-DB-LLR-002*/
      /* Allocate lock resource and initialize it */
      h_can->Lock = HAL_UNLOCKED;

      /* Init the low level hardware */
      HalCanMspInit(h_can);
   }
   else
   {
      ; /* Do nothing */
   }

   /*hdulibstm32f7xxhalcan-HalCanInit-DB-LLR-003*/
   /* Initialize the CAN state*/
   h_can->State = HAL_CAN_STATE_BUSY;

   /* Exit from sleep mode */
   h_can->Instance->MCR &= (~(T_UINT32)CAN_MCR_SLEEP);

   /* Request initialisation */
   h_can->Instance->MCR |= CAN_MCR_INRQ ;

   /* Get tick */
   tick_start = HALGetTick();

   /* Wait the acknowledge */
   while(CAN_MSR_INAK != (h_can->Instance->MSR & CAN_MSR_INAK))
   {
      if((HALGetTick() - tick_start ) > CAN_TIMEOUT_VALUE)
      {
         /*hdulibstm32f7xxhalcan-HalCanInit-DB-LLR-004*/
         h_can->State= HAL_CAN_STATE_TIMEOUT;

         /* Process unlocked */
         __HAL_UNLOCK(h_can);

         return HAL_TIMEOUT;
      }
      else
      {
         ; /* Do nothing */
      }
   }

   /* Check acknowledge */
   if (CAN_MSR_INAK == (h_can->Instance->MSR & CAN_MSR_INAK))
   {
      /* Set the time triggered communication mode */
      if (ENABLE == h_can->Init.TTCM)
      {
         /*hdulibstm32f7xxhalcan-HalCanInit-DB-LLR-005*/
         h_can->Instance->MCR |= CAN_MCR_TTCM;
      }
      else
      {
         /*hdulibstm32f7xxhalcan-HalCanInit-DB-LLR-006*/
         h_can->Instance->MCR &= ~(T_UINT32)CAN_MCR_TTCM;
      }

      /* Set the automatic bus-off management */
      if (ENABLE == h_can->Init.ABOM)
      {
         /*hdulibstm32f7xxhalcan-HalCanInit-DB-LLR-007*/
         h_can->Instance->MCR |= CAN_MCR_ABOM;
      }
      else
      {
         /*hdulibstm32f7xxhalcan-HalCanInit-DB-LLR-008*/
         h_can->Instance->MCR &= ~(T_UINT32)CAN_MCR_ABOM;
      }

      /* Set the automatic wake-up mode */
      if (ENABLE == h_can->Init.AWUM)
      {
         /*hdulibstm32f7xxhalcan-HalCanInit-DB-LLR-009*/
         h_can->Instance->MCR |= CAN_MCR_AWUM;
      }
      else
      {
         /*hdulibstm32f7xxhalcan-HalCanInit-DB-LLR-010*/
         h_can->Instance->MCR &= ~(T_UINT32)CAN_MCR_AWUM;
      }

      /* Set the no automatic retransmission */
      if (ENABLE == h_can->Init.NART)
      {
         /*hdulibstm32f7xxhalcan-HalCanInit-DB-LLR-011*/
         h_can->Instance->MCR |= CAN_MCR_NART;
      }
      else
      {
         /*hdulibstm32f7xxhalcan-HalCanInit-DB-LLR-012*/
         h_can->Instance->MCR &= ~(T_UINT32)CAN_MCR_NART;
      }

      /* Set the receive FIFO locked mode */
      if (ENABLE == h_can->Init.RFLM)
      {
         /*hdulibstm32f7xxhalcan-HalCanInit-DB-LLR-013*/
         h_can->Instance->MCR |= CAN_MCR_RFLM;
      }
      else
      {
         /*hdulibstm32f7xxhalcan-HalCanInit-DB-LLR-014*/
         h_can->Instance->MCR &= ~(T_UINT32)CAN_MCR_RFLM;
      }

      /* Set the transmit FIFO priority */
      if (ENABLE == h_can->Init.TXFP)
      {
         /*hdulibstm32f7xxhalcan-HalCanInit-DB-LLR-015*/
         h_can->Instance->MCR |= CAN_MCR_TXFP;
      }
      else
      {
         /*hdulibstm32f7xxhalcan-HalCanInit-DB-LLR-016*/
         h_can->Instance->MCR &= ~(T_UINT32)CAN_MCR_TXFP;
      }
      /*hdulibstm32f7xxhalcan-HalCanInit-DB-LLR-017*/
      /* Set the bit timing register */
      h_can->Instance->BTR = (T_UINT32)((T_UINT32)h_can->Init.Mode) | \
                                     ((T_UINT32)h_can->Init.SJW) | \
                                     ((T_UINT32)h_can->Init.BS1) | \
                                     ((T_UINT32)h_can->Init.BS2) | \
                                     ((T_UINT32)h_can->Init.Prescaler - ONE);

      /* Request leave initialisation */
      h_can->Instance->MCR &= ~(T_UINT32)CAN_MCR_INRQ;

      /* Get tick */
      tick_start = HALGetTick();

      /* Wait the acknowledge */
      while(CAN_MSR_INAK == (h_can->Instance->MSR & CAN_MSR_INAK))
      {
         if((HALGetTick() - tick_start ) > CAN_TIMEOUT_VALUE)
         {
            /*hdulibstm32f7xxhalcan-HalCanInit-DB-LLR-018*/
            h_can->State= HAL_CAN_STATE_TIMEOUT;

            /* Process unlocked */
            __HAL_UNLOCK(h_can);

            return HAL_TIMEOUT;
         }
         else
         {
            ; /* Do nothing */
         }
      }

      /* Check acknowledged */
      if (CAN_MSR_INAK != (h_can->Instance->MSR & CAN_MSR_INAK))
      {
         /*hdulibstm32f7xxhalcan-HalCanInit-DB-LLR-021*/
         init_status = CAN_INITSTATUS_SUCCESS;
      }
      else
      {
         ; /* Do nothing */
      }
   }

   if(CAN_INITSTATUS_SUCCESS == init_status)
   {
      /*hdulibstm32f7xxhalcan-HalCanInit-DB-LLR-019*/
      /* Set CAN error code to none */
      h_can->ErrorCode = HAL_CAN_ERROR_NONE;

      /* Initialize the CAN state */
      h_can->State = HAL_CAN_STATE_READY;

      /* Return function status */
      return HAL_OK;
   }
   else
   {
      /*hdulibstm32f7xxhalcan-HalCanInit-DB-LLR-020*/
      /* Initialize the CAN state */
      h_can->State = HAL_CAN_STATE_ERROR;

      /* Return function status */
      return HAL_ERROR;
   }
}

/*
 * Function                : HalCanConfigFilter
 *
 * Description             : The function configures the CAN reception filter according
 *                           to the specified parameters in the T_CAN_FILTER_CONF_TYPE.
 *
 * Formal parameter(s)     : T_CAN_HANDLE* h_can -INOUT pointer to a T_CAN_HANDLE structure
 *                           that contains the configuration information for the specified CAN.
 *                           T_CAN_FILTER_CONF_TYPE* filter_config -IN pointer to
 *                           a T_CAN_FILTER_CONF_TYPE structure that contains the filter
 *                           configuration information.
 *
 * Return Value            : T_HAL_STATUS - HAL status
 *
 * Assumption              : None
 *
 */

T_HAL_STATUS HalCanConfigFilter(T_CAN_HANDLE* h_can, T_CAN_FILTER_CONF_TYPE* filter_config)
{
   T_UINT32 filter_nbr_bit_pos = ZERO;
   T_CAN *can_ip = h_can->Instance;
   /*hdulibstm32f7xxhalcan-HalCanConfigFilter-DB-LLR-001*/
   filter_nbr_bit_pos = ((T_UINT32)ONE) << filter_config->FilterNumber;

   can_ip = CAN1;

   /*hdulibstm32f7xxhalcan-HalCanConfigFilter-DB-LLR-002*/
   /* Initialisation mode for the filter */
   can_ip->FMR |= (T_UINT32)CAN_FMR_FINIT;

   /*hdulibstm32f7xxhalcan-HalCanConfigFilter-DB-LLR-003*/
   /* Select the start slave bank */
   can_ip->FMR &= ~((T_UINT32)CAN_FMR_CAN2SB);
   can_ip->FMR |= (T_UINT32)(filter_config->BankNumber << EIGHT);

   /*hdulibstm32f7xxhalcan-HalCanConfigFilter-DB-LLR-004*/
   /* Filter Deactivation */
   can_ip->FA1R &= ~(T_UINT32)filter_nbr_bit_pos;

   /* Filter Scale */
   if (CAN_FILTERSCALE_16BIT == filter_config->FilterScale)
   {
      /*hdulibstm32f7xxhalcan-HalCanConfigFilter-DB-LLR-005*/
      /* 16-bit scale for the filter */
      can_ip->FS1R &= ~(T_UINT32)filter_nbr_bit_pos;

      /* First 16-bit identifier and First 16-bit mask */
      /* Or First 16-bit identifier and Second 16-bit identifier */
      can_ip->sFilterRegister[filter_config->FilterNumber].FR1 =
      ((HEX_FFFF & (T_UINT32)filter_config->FilterMaskIdLow) << SIXTEEN) |
      (HEX_FFFF & (T_UINT32)filter_config->FilterIdLow);

      /* Second 16-bit identifier and Second 16-bit mask */
      /* Or Third 16-bit identifier and Fourth 16-bit identifier */
      can_ip->sFilterRegister[filter_config->FilterNumber].FR2 =
      ((HEX_FFFF & (T_UINT32)filter_config->FilterMaskIdHigh) << SIXTEEN) |
      (HEX_FFFF & (T_UINT32)filter_config->FilterIdHigh);
   }
   else
   {
      ; /*Do nothing */
   }

   if (CAN_FILTERSCALE_32BIT == filter_config->FilterScale)
   {
      /*hdulibstm32f7xxhalcan-HalCanConfigFilter-DB-LLR-006*/
      /* 32-bit scale for the filter */
      can_ip->FS1R |= filter_nbr_bit_pos;

      /* 32-bit identifier or First 32-bit identifier */
      can_ip->sFilterRegister[filter_config->FilterNumber].FR1 =
      ((HEX_FFFF & (T_UINT32)filter_config->FilterIdHigh) << SIXTEEN) |
      (HEX_FFFF & (T_UINT32)filter_config->FilterIdLow);

      /* 32-bit mask or Second 32-bit identifier */
      can_ip->sFilterRegister[filter_config->FilterNumber].FR2 =
      ((HEX_FFFF & (T_UINT32)filter_config->FilterMaskIdHigh) << SIXTEEN) |
      (HEX_FFFF & (T_UINT32)filter_config->FilterMaskIdLow);
   }
   else
   {
      ; /*Do nothing */
   }

   /* Filter Mode */
   if (CAN_FILTERMODE_IDMASK == filter_config->FilterMode)
   {
      /*hdulibstm32f7xxhalcan-HalCanConfigFilter-DB-LLR-007*/
      /*Id/Mask mode for the filter*/
      can_ip->FM1R &= ~(T_UINT32)filter_nbr_bit_pos;
   }
   else /* CAN_FilterInitStruct->CAN_FilterMode == CAN_FilterMode_IdList */
   {
      /*hdulibstm32f7xxhalcan-HalCanConfigFilter-DB-LLR-008*/
      /*Identifier list mode for the filter*/
      can_ip->FM1R |= (T_UINT32)filter_nbr_bit_pos;
   }

   /* Filter FIFO assignment */
   if (CAN_FILTER_FIFO0 == filter_config->FilterFIFOAssignment)
   {
      /*hdulibstm32f7xxhalcan-HalCanConfigFilter-DB-LLR-009*/
      /* FIFO 0 assignation for the filter */
      can_ip->FFA1R &= ~(T_UINT32)filter_nbr_bit_pos;
   }
   else
   {
      ; /*Do nothing */
   }

   if (CAN_FILTER_FIFO1 == filter_config->FilterFIFOAssignment)
   {
      /*hdulibstm32f7xxhalcan-HalCanConfigFilter-DB-LLR-010*/
      /* FIFO 1 assignation for the filter */
      can_ip->FFA1R |= (T_UINT32)filter_nbr_bit_pos;
   }
   else
   {
      ; /*Do nothing */
   }

   /* Filter activation */
   if (ENABLE == filter_config->FilterActivation)
   {
      /*hdulibstm32f7xxhalcan-HalCanConfigFilter-DB-LLR-011*/
      can_ip->FA1R |= filter_nbr_bit_pos;
   }
   else
   {
      ; /*Do nothing */
   }
   /*hdulibstm32f7xxhalcan-HalCanConfigFilter-DB-LLR-012*/
   /* Leave the initialisation mode for the filter */
   can_ip->FMR &= ~((T_UINT32)CAN_FMR_FINIT);

   /* Return function status */
   return HAL_OK;
}

/*
 * Function                : HalCanTransmit
 *
 * Description             : The function initiates and transmits a CAN frame message.
 *
 * Formal parameter(s)     : T_CAN_HANDLE* h_can -INOUT pointer to a T_CAN_HANDLE structure
 *                           that contains the configuration information for the specified CAN.
 *                           T_UINT32 time_out -IN Specify time_out value
 *
 * Return Value            : T_HAL_STATUS - HAL status
 *
 * Assumption              : None
 *
 */

T_HAL_STATUS HalCanTransmit(T_CAN_HANDLE* h_can, T_UINT32 time_out)
{
  T_UINT32  transmit_mailbox = CAN_TXSTATUS_NOMAILBOX;
  T_UINT32  tick_start = ZERO;

   if((CAN_TSR_TME0 == (h_can->Instance->TSR&CAN_TSR_TME0)) || \
      (CAN_TSR_TME1 == (h_can->Instance->TSR&CAN_TSR_TME1)) || \
      (CAN_TSR_TME2 == (h_can->Instance->TSR&CAN_TSR_TME2)))
   {

      /* Select one empty transmit mailbox */
      if (CAN_TSR_TME0 == (h_can->Instance->TSR&CAN_TSR_TME0))
      {
         /*hdulibstm32f7xxhalcan-HalCanTransmit-DB-LLR-001*/
         transmit_mailbox = CAN_TXMAILBOX_0;
      }
      else if (CAN_TSR_TME1 == (h_can->Instance->TSR&CAN_TSR_TME1))
      {
         /*hdulibstm32f7xxhalcan-HalCanTransmit-DB-LLR-002*/
         transmit_mailbox = CAN_TXMAILBOX_1;
      }
      else
      {
         /*hdulibstm32f7xxhalcan-HalCanTransmit-DB-LLR-003*/
         transmit_mailbox = CAN_TXMAILBOX_2;
      }
      /*hdulibstm32f7xxhalcan-HalCanTransmit-DB-LLR-004*/
      /* Set up the Id */
      h_can->Instance->sTxMailBox[transmit_mailbox].TIR &= CAN_TI0R_TXRQ;

      if (CAN_ID_STD == h_can->pTxMsg->IDE)
      {
         /*hdulibstm32f7xxhalcan-HalCanTransmit-DB-LLR-005*/
         h_can->Instance->sTxMailBox[transmit_mailbox].TIR |=
                                                         ((h_can->pTxMsg->StdId << TWENTY_ONE) |
                                                         h_can->pTxMsg->RTR);
      }
      else
      {
         /*hdulibstm32f7xxhalcan-HalCanTransmit-DB-LLR-006*/
         h_can->Instance->sTxMailBox[transmit_mailbox].TIR |=((h_can->pTxMsg->ExtId << THREE) | \
                                                             h_can->pTxMsg->IDE | \
                                                             h_can->pTxMsg->RTR);
      }
      /*hdulibstm32f7xxhalcan-HalCanTransmit-DB-LLR-007*/
      /* Set up the DLC */
      h_can->pTxMsg->DLC &= FIFTEEN;
      h_can->Instance->sTxMailBox[transmit_mailbox].TDTR &= (T_UINT32)HEX_FFFFFFF0;
      h_can->Instance->sTxMailBox[transmit_mailbox].TDTR |= h_can->pTxMsg->DLC;

      /*hdulibstm32f7xxhalcan-HalCanTransmit-DB-LLR-008*/
      /* Set up the data field */
      h_can->Instance->sTxMailBox[transmit_mailbox].TDLR =
                                             (((T_UINT32)h_can->pTxMsg->Data[3] << TWENTY_FOUR) |
                                             ((T_UINT32)h_can->pTxMsg->Data[2] << SIXTEEN) |
                                             ((T_UINT32)h_can->pTxMsg->Data[1] << EIGHT) |
                                             ((T_UINT32)h_can->pTxMsg->Data[0]));

      h_can->Instance->sTxMailBox[transmit_mailbox].TDHR =
                                             (((T_UINT32)h_can->pTxMsg->Data[7] << TWENTY_FOUR) |
                                             ((T_UINT32)h_can->pTxMsg->Data[6] << SIXTEEN) |
                                             ((T_UINT32)h_can->pTxMsg->Data[5] << EIGHT) |
                                             ((T_UINT32)h_can->pTxMsg->Data[4]));
      /*hdulibstm32f7xxhalcan-HalCanTransmit-DB-LLR-009*/
      /* Request transmission */
      h_can->Instance->sTxMailBox[transmit_mailbox].TIR |= CAN_TI0R_TXRQ;

      /* Get tick */
      tick_start = HALGetTick();

      /* Check End of transmission flag */
      while(ZERO == (__HAL_CAN_TRANSMIT_STATUS(h_can, transmit_mailbox)))
      {
         /* Check for the time_out */
         if(HAL_MAX_DELAY != time_out)
         {
            if((ZERO == time_out )||((HALGetTick() - tick_start ) > time_out))
            {
               /*hdulibstm32f7xxhalcan-HalCanTransmit-DB-LLR-010*/
               h_can->State = HAL_CAN_STATE_TIMEOUT;

               /* Process unlocked */
               __HAL_UNLOCK(h_can);

               return HAL_TIMEOUT;
            }
            else
            {
               ; /* Do nothing */
            }
         }
         else
         {
            ; /* Do nothing */
         }
      }
   /*hdulibstm32f7xxhalcan-HalCanTransmit-DB-LLR-011*/
   /* Return function status */
   return HAL_OK;
   }
   else
   {
      /*hdulibstm32f7xxhalcan-HalCanTransmit-DB-LLR-012*/
      /* Return function status */
      return HAL_ERROR;
   }
}

/*
 * Function                : HalCanReceive
 *
 * Description             : The function receives a correct CAN frame.
 *
 * Formal parameter(s)     : T_CAN_HANDLE* h_can -INOUT pointer to a T_CAN_HANDLE structure
 *                           that contains the configuration information for the specified CAN.
 *                           T_UINT8 fifo_number -IN  FIFO Number value.
 *                           T_UINT32 time_out -IN Specify time_out value
 *
 * Return Value            : T_HAL_STATUS - HAL status
 *
 * Assumption              : None
 *
 */


T_HAL_STATUS HalCanReceive(T_CAN_HANDLE* h_can, T_UINT8 fifo_number, T_UINT32 time_out)
{

   T_UINT32 tick_start = ZERO;

   if(HAL_CAN_STATE_BUSY_TX == h_can->State)
   {
      /*hdulibstm32f7xxhalcan-HalCanReceive-DB-LLR-001*/
      /* Change CAN state */
      h_can->State = HAL_CAN_STATE_BUSY_TX_RX;
   }
   else
   {
      /*hdulibstm32f7xxhalcan-HalCanReceive-DB-LLR-002*/
      /* Change CAN state */
      h_can->State = HAL_CAN_STATE_BUSY_RX;
   }
   /*hdulibstm32f7xxhalcan-HalCanReceive-DB-LLR-003*/
   /* Get tick */
   tick_start = HALGetTick();

   /* Check pending message */
   while(ZERO == __HAL_CAN_MSG_PENDING(h_can, fifo_number))
   {
      /* Check for the time_out */
      if(time_out != HAL_MAX_DELAY)
      {
         if(( ZERO == time_out)||((HALGetTick() - tick_start ) > time_out))
         {
            /*hdulibstm32f7xxhalcan-HalCanReceive-DB-LLR-004*/
            h_can->State = HAL_CAN_STATE_TIMEOUT;

            /* Process unlocked */
            __HAL_UNLOCK(h_can);

            return HAL_TIMEOUT;
         }
         else
         {
            ; /* Do nothing */
         }
      }
      else
      {
         ; /* Do nothing */
      }
   }
   /*hdulibstm32f7xxhalcan-HalCanReceive-DB-LLR-005*/
   /* Get the Id */
   h_can->pRxMsg->IDE = (T_UINT8)FOUR & h_can->Instance->sFIFOMailBox[fifo_number].RIR;

   if (CAN_ID_STD == h_can->pRxMsg->IDE)
   {
      /*hdulibstm32f7xxhalcan-HalCanReceive-DB-LLR-006*/
      h_can->pRxMsg->StdId = (T_UINT32)HEX_7FF &
                        (h_can->Instance->sFIFOMailBox[fifo_number].RIR >> TWENTY_ONE);
   }
   else
   {
      /*hdulibstm32f7xxhalcan-HalCanReceive-DB-LLR-007*/
      h_can->pRxMsg->ExtId = (T_UINT32)HEX_1FFFFFFF &
                        (h_can->Instance->sFIFOMailBox[fifo_number].RIR >> THREE);
   }
   /*hdulibstm32f7xxhalcan-HalCanReceive-DB-LLR-008*/
   h_can->pRxMsg->RTR = (T_UINT8)TWO & h_can->Instance->sFIFOMailBox[fifo_number].RIR;

   /*hdulibstm32f7xxhalcan-HalCanReceive-DB-LLR-009*/
   /* Get the DLC */
   h_can->pRxMsg->DLC = (T_UINT8)FIFTEEN & h_can->Instance->sFIFOMailBox[fifo_number].RDTR;

   /*hdulibstm32f7xxhalcan-HalCanReceive-DB-LLR-010*/
   /* Get the FMI */
   h_can->pRxMsg->FMI = (T_UINT8)HEX_FF &
                     (h_can->Instance->sFIFOMailBox[fifo_number].RDTR >> EIGHT);

   /*hdulibstm32f7xxhalcan-HalCanReceive-DB-LLR-011*/
   /* Get the data field */
   h_can->pRxMsg->Data[0] = (T_UINT8)HEX_FF &
                           h_can->Instance->sFIFOMailBox[fifo_number].RDLR;

   h_can->pRxMsg->Data[1] = (T_UINT8)HEX_FF &
                           (h_can->Instance->sFIFOMailBox[fifo_number].RDLR >> EIGHT);

   h_can->pRxMsg->Data[2] = (T_UINT8)HEX_FF &
                           (h_can->Instance->sFIFOMailBox[fifo_number].RDLR >> SIXTEEN);

   h_can->pRxMsg->Data[3] = (T_UINT8)(HEX_FF &
                           (h_can->Instance->sFIFOMailBox[fifo_number].RDLR >> TWENTY_FOUR));

   h_can->pRxMsg->Data[4] = (T_UINT8)HEX_FF &
                            h_can->Instance->sFIFOMailBox[fifo_number].RDHR;

   h_can->pRxMsg->Data[5] = (T_UINT8)HEX_FF &
                           (h_can->Instance->sFIFOMailBox[fifo_number].RDHR >> EIGHT);

   h_can->pRxMsg->Data[6] = (T_UINT8)HEX_FF &
                           (h_can->Instance->sFIFOMailBox[fifo_number].RDHR >> SIXTEEN);

   h_can->pRxMsg->Data[7] = (T_UINT8)(HEX_FF &
                           (h_can->Instance->sFIFOMailBox[fifo_number].RDHR >> TWENTY_FOUR));

   /* Release the FIFO */
   if(CAN_FIFO0 == fifo_number)
   {
      /*hdulibstm32f7xxhalcan-HalCanReceive-DB-LLR-012*/
      /* Release FIFO0 */
      __HAL_CAN_FIFO_RELEASE(h_can, CAN_FIFO0);
   }
   else /* fifo_number == CAN_FIFO1 */
   {
      /*hdulibstm32f7xxhalcan-HalCanReceive-DB-LLR-013*/
      /* Release FIFO1 */
      __HAL_CAN_FIFO_RELEASE(h_can, CAN_FIFO1);
   }

   if(HAL_CAN_STATE_BUSY_TX_RX == h_can->State)
   {
      /*hdulibstm32f7xxhalcan-HalCanReceive-DB-LLR-014*/
      /* Change CAN state */
      h_can->State = HAL_CAN_STATE_BUSY_TX;
   }
   else
   {
      /*hdulibstm32f7xxhalcan-HalCanReceive-DB-LLR-015*/
      /* Change CAN state */
      h_can->State = HAL_CAN_STATE_READY;
   }

   /* Process unlocked */
   /*hdulibstm32f7xxhalcan-HalCanReceive-DB-LLR-016*/
   __HAL_UNLOCK(h_can);

   /* Return function status */
   return HAL_OK;
}
