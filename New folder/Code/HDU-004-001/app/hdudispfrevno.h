/*
 ******************************************************************************
 * License Information  :  Howell Instruments, Inc.                           *
 *                         "Licensed Software" and "All rights reserved".     *
 ******************************************************************************
 *  File                : hdudispfrevno.h
 *
 *  Description         : This file Provides the definition of the software
 *                        application part number.
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
 * <Version No.>     <Author>          <Date>         <Problem Report No.>
 *
 *      1.1          Shilpa A R       13-Sep-2017             100064
 *      1.2          Vinay H          10-Oct-2017             100064
 *      1.3          Rona B.S         11-Oct-2017             100064
 *      1.4          Shruthi M N      16-Oct-2017             100083
 *      1.5          Shruthi M N      30-Oct-2017             100104
 *      1.6          Shruthi M N      04-Nov-2017             100156
 *      1.7          Shruthi M N      07-Nov-2017             100161
 *      1.8          Shruthi M N      08-Nov-2017             100164
 *      1.9          Divya G P        09-Nov-2017             100164
 *      1.10         Rona B S         23-Mar-2018             100196
 *      1.11         Rona B S         28-Mar-2018             100196
 *      1.12         Shruthi M N      03-Apr-2018             100205
 *      1.13         Rona B S         16-Apr-2018             100211
 *      1.14         Rona B S         18-Apr-2018             100216
 *      1.15         Dhanalakshmi D   24-Apr-2020             100241
 *      1.16         Dhanalakshmi D   15-May-2020             100247
 *      1.17         Dhanalakshmi D   21-Jun-2020             100259
 *      1.18         Rona B S   	  29-Jun-2020             100259
 *      1.19         Rona B S   	  24-Jul-2020             100259
 *      1.20         Dhanalakshmi     05-Aug-2020             100270
 *      1.21         Rona B S   	  12-Sep-2020             100276
 *      1.22         Rona B S   	  15-Sep-2020             100276
 *      1.23         Rona B S   	  28-Sep-2020             100284 
 *      1.24         Rona B S   	  30-Sep-2020             100284 
 *      1.25         Rona B S         05-Oct-2020             100288   
 *      1.26         Rona B S         09-Oct-2020             100288  
 *      1.27         Dhanalakshmi D   21-Oct-2020             100314
 *      1.28         Dhanalakshmi     20-Mar-2021             100331
 *      1.29         Dhanalakshmi     20-Mar-2021             100331
 *      1.30         Dhanalakshmi     20-Mar-2021             100331
 *      1.31         Dhanalakshmi     03-Apr-2021             100330
 *      1.32         Dhanalakshmi     16-Apr-2021             100339
 *      1.33         Dhanalakshmi     24-Apr-2021             100344
 *      1.34         Dhanalakshmi     13-May-2021             100350
 *      1.35         Chaithra J       04-Mar-2022             100368
 *
 * Additional References : None
 *
 ******************************************************************************
 */

#ifndef _HDUDISPFREVNO_H_
#define _HDUDISPFREVNO_H_

#include "hdulibbasictypes.h" /* provides basic datatypes */

/* Revno is fixed at 16 characters without the null at the end */
/* Length of revision string */
#define REVNO_LEN_FLIGHT   16U
#define REVNO_LOCATE_IN_ID_STORAGE __attribute__((section(".id_storage")))

/* revision string for indicator software as a whole */
#define REVNO_REVISION_FLIGHT "H108E-133 -1.34 "

REVNO_LOCATE_IN_ID_STORAGE
extern T_UINT8 Revno_id[REVNO_LEN_FLIGHT];

#endif /* _HDUDISPFREVNO_H */
