/*
 ******************************************************************************
 * License Information  :  Howell Instruments, Inc.                           *
 *                         "Licensed Software" and "All rights reserved".     *
 ******************************************************************************
 *  File                : hdudispfrevno.c
 *
 *  Description         : This file provides the declaration of the software
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
 *
 * Additional References : None
 *
 ******************************************************************************
 */

#include "hdudispfrevno.h"            /* Revision number ID */
#include "hdulibbasictypes.h"    /* provides basic datatypes */

/*
 *The CSC hdudispfrevno shall define the Top level software configuration number(SCN) and
 * set the HDU Application Software Part Number to REVNO_REVISION_FLIGHT
 */
REVNO_LOCATE_IN_ID_STORAGE T_UINT8 Revno_id[REVNO_LEN_FLIGHT] = { REVNO_REVISION_FLIGHT };

