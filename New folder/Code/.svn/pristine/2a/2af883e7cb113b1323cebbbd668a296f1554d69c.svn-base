/*
 ******************************************************************************
 * License Information  :  Howell Instruments, Inc.                           *
 *                         "Licensed Software" and "All rights reserved".     *
 ******************************************************************************
 *  File                : hdudispfbspnor.h
 *
 *  Description         : This file contains the common defines and functions prototypes for
 *                        hdudispfbspnor.c
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
 *
 * Additional References : None
 *
 *****************************************************************************
 */

#ifndef _HDUDISPFBSPNOR_H_
#define _HDUDISPFBSPNOR_H_

/* Includes*/
#include "hdulibstm32f7xxhal.h"   /* Header files for HAL driver*/
#include "hdulibstm32f7xxhalfmc.h" /* Header files for fmc driver*/
#include "hdulibstm32f7xxhalnor.h" /* provides a generic firmware to drive NOR memories */
#include "hdulibbasictypes.h"  /* Standard basic data type definitions */

#define   NOR_STATUS_OK             ((T_UINT8)0x00)
#define   NOR_STATUS_ERROR          ((T_UINT8)0x01)
#define   NOR_MEMORY_WIDTH          FMC_NORSRAM_MEM_BUS_WIDTH_16
#define   NOR_BURSTACCESS           FMC_BURST_ACCESS_MODE_DISABLE
#define   NOR_WRITEBURST            FMC_WRITE_BURST_DISABLE
#define   CONTINUOUSCLOCK_FEATURE   FMC_CONTINUOUS_CLOCK_SYNC_ASYNC

T_UINT8 BspNorInit(void);
void    BspNorMspInit();

#endif /* _HDUDISPFBSPNOR_H_ */

