/*
 ******************************************************************************
 * License Information  :  Howell Instruments, Inc.                           *
 *                         "Licensed Software" and "All rights reserved".     *
 ******************************************************************************
 *  File                : hdudispbrevno.h
 *
 *  Description         : This file Provides the definition of the software application part number.
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
 *  Version History     :
 * <Version No.>     <Author>          <Date>         <Problem Report No.>
 *
 *      1.1          Rona B.S        22-Aug-2017             -
 *      1.2          Divya G P       02-Sep-2017            100028
 *      1.3          Rona B.S        28-Sep-2017            100064
 *      1.4          Shilpa A R      10-Oct-2017            100064
 *      1.5          Shruthi M N     04-Nov-2017            100156
 *      1.6          Shruthi M N     09-Nov-2017            100164
 *      1.7          Rona B.S        23-Mar-2018            100196
 *      1.8          Rona B.S        05-Jul-2020            100259
 *      1.9          Rona B.S        12-Sep-2020            100276 
 *      1.10         Dhanalakshmi    20-Mar-2021            100331
 *      1.11         Dhanalakshmi   20-Mar-2021             100331
 *
 * Additional References : None
 *
 ******************************************************************************
 */

#ifndef _HDUDISPBREVNO_H_
#define _HDUDISPBREVNO_H_

#include "hdulibbasictypes.h" /*Contains basic data types */

/* Revno is fixed at 16 characters without the null at the end */
/* Length of revision string */
#define REVNO_LEN_BOOT   16U
#define REVNO_ID_STORAGE_DISP_BOOT  __attribute__ ((section(".id_storage")))

/* revision string for indicator software as a whole */
#define BOOT_PART_REV_NUMBER   "H108E-132 -1.11 "

extern T_UINT8 Revno_id[REVNO_LEN_BOOT] REVNO_ID_STORAGE_DISP_BOOT;

#endif
