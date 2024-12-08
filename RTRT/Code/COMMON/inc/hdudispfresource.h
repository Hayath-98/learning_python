/*
 ******************************************************************************
 * License Information  :  Howell Instruments, Inc.                           *
 *                         "Licensed Software" and "All rights reserved".     *
 ******************************************************************************
 *  File                : hdudispfresource.h
 *
 *  Description         : This file provides a central location to document the use of
 *                  the On Chip Peripherals.
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
 *      1.1           Shilpa A R       11-Sep-2017             100064
 *      1.2           Rona B S         10-Oct-2017             100064
 *      1.3           Vinay H          23-Mar-2018             100196
 *      1.4           Rona B S   	   29-Jun-2020             100259 
 *      1.5           Dhanalakshmi     05-Aug-2020             100270 
 *
 * Additional References : None
 *
 ******************************************************************************
 */

#ifndef _HDUDISPFRESOURCE_H_
#define _HDUDISPFRESOURCE_H_

#include "hdulibstm32f7xxhalrccex.h"  /* Header files for RCC EX HAL module*/
#include "hdulibstm32f7xxhalconf.h"   /* provides HAL configurations. */
#include "hdulibstm32f7xxhalgpio.h"  /* Header files for GPIO HAL driver*/
#include "hdudispfconfig.h"  /* contains page and color config information */
#include "hdudispfpdidata.h" /* Extract the data from NOR flash */

/**********************************/
/* Panel Selection. */
/**********************************/
/* Panel on the F7 Discovery. */
#define RK043FN48H   0
/* Panel on the Prototype EIS. */
#define AA065VD51    1
/* Panel on the Prototype #2 EIS. */
#define AA07MC52     3
/* Panel on the Prototype DPI. */
#define KD035HVFMA035   4

#define AA104SL12     5

#define AA104XD12     6

/********** Select Panel   ********/

#define PANEL  AA104XD12


/*-------------------   Define interrupt priorities.  -------------------*/

#define CAN1_RX_PRIORITY   1
#define CAN2_RX_PRIORITY   2
#define CAN1_TX_PRIORITY   4
#define CAN2_TX_PRIORITY   5

/*------------------------ Allocate a825 resources  -----------------*/
#define  HAS_A825_1
#define HAS_A825_2

#define CAN1_CLK_ENABLE()               __HAL_RCC_CAN1_CLK_ENABLE()
#define CAN1_GPIO_CLK_ENABLE()          __HAL_RCC_GPIOB_CLK_ENABLE()

#define CAN1_FORCE_RESET()              __HAL_RCC_CAN1_FORCE_RESET()
#define CAN1_RELEASE_RESET()            __HAL_RCC_CAN1_RELEASE_RESET()

/* Definition for USARTx Pins */
#define CAN1_TX_PIN                    GPIO_PIN_9
#define CAN1_TX_GPIO_PORT              GPIOB
#define CAN1_TX_AF                     GPIO_AF9_CAN1
#define CAN1_RX_PIN                    GPIO_PIN_8
#define CAN1_RX_GPIO_PORT              GPIOB
#define CAN1_RX_AF                     GPIO_AF9_CAN1

#define CAN2_CLK_ENABLE()               __HAL_RCC_CAN2_CLK_ENABLE()
#define CAN2_GPIO_CLK_ENABLE()          __HAL_RCC_GPIOB_CLK_ENABLE()

#define CAN2_FORCE_RESET()              __HAL_RCC_CAN2_FORCE_RESET()
#define CAN2_RELEASE_RESET()            __HAL_RCC_CAN2_RELEASE_RESET()

/* Definition for USARTx Pins */
#define CAN2_TX_PIN                    GPIO_PIN_6
#define CAN2_TX_GPIO_PORT              GPIOB
#define CAN2_TX_AF                     GPIO_AF9_CAN2
#define CAN2_RX_PIN                    GPIO_PIN_5
#define CAN2_RX_GPIO_PORT              GPIOB
#define CAN2_RX_AF                     GPIO_AF9_CAN2

/*------------------------ Allocate LED resources. --------------------*/
#define LED1_PORT                               GPIOB
#define  LED1_CLK_ENABLE()                   __HAL_RCC_GPIOB_CLK_ENABLE()
#define LED1_PIN                                GPIO_PIN_2

/*--------------------- A825COMM  TASK ----------------------------------------*/

#define A825_1_COMM_TASK_PRIO    1
#define A825_2_COMM_TASK_PRIO    2
#define A825COMM_TASK_STK_SIZE   1024

/*-------------------- POLLER  TASK -------------------------------------------*/
#define POLLER_TASK_PRIO            3
#define POLLER_TASK_STK_SIZE     1024
#define POLLER_TASK_TICKS           1

/*-------------------- DEMO  TASK --------------------------------------*/
#define DEMO_TASK_PRIO            6
#define DEMO_TASK_STK_SIZE     1024
#define DEMO_TASK_TICKS           1

/*--------------------- APP TASK -------------------------------------------*/

#define APP_TASK_PRIO                  5
#define APP_TASK_STK_SIZE           1024

/*-------------------- INIT TASK -------------------------------------------*/
#define INIT_TASK_PRIO              9
#define INIT_TASK_STK_SIZE       1024
#define INIT_TASK_TICKS             500
/*-------------------- CBIT TASK -------------------------------------------*/
#define CBIT_TASK_PRIO                          20U
#define CBIT_TASK_STK_SIZE                      1024U
#define CBIT_TASK_TICKS                         600U

#endif /*_HDUDISPFRESOURCE_H_*/
