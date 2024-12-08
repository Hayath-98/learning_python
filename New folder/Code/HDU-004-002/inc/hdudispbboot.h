/*
 ******************************************************************************
 * License Information  :  Howell Instruments, Inc.                           *
 *                         "Licensed Software" and "All rights reserved".     *
 ******************************************************************************
 *  File                : hdudispbboot.h
 *
 *  Description         : This file contains the common defines and functions prototypes for
 *                        hdudispbboot.c.
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
 *      1.1          Rona B.S        02-Aug-2017             -
 *      1.2          Divya G P       01-Sep-2017      100028
 *      1.3          Rona B.S        21-Jun-2020      100259  
 *      1.4          Rona B S        29-Jun-2020      100259
 *
 * Additional References : None
 *
 *****************************************************************************
 */

#ifndef _HDUDISPBBOOT_H_
#define _HDUDISPBBOOT_H_

#include "hdulibbasictypes.h"    /* Contains basic data types */
#include "hdudispbappdata.h"	 /* Contains appdata structure for configuration file*/

#define MAX_FILE_NAME_LENGTH  13

typedef struct
{
   T_UINT32 u32LoadAddr;   /* Where the file will be loaded. */
   T_UINT32 u32LoadSize;   /* Size of the load image. *** CAUTION  7 Meg Max. */

}  T_SBOOTFILE;

#define SIZE_IN_KB  1024
#define SIZE_IN_MB  (SIZE_IN_KB*SIZE_IN_KB)

#define FLIGHT_APP_ADDR  0x080C0000

/* External Nor defines. */
#define NOR_BASE              0x60000000
#define NOR_SIZE              0x4000000
#define  NOR_SECTOR_SIZE      (128*SIZE_IN_KB)


/* Internal flash memory defines. */
#define SECTOR0BASE 0x08000000
#define SECTOR1BASE 0x08008000
#define SECTOR2BASE 0x08010000
#define SECTOR3BASE 0x08080000
#define SECTOR4BASE 0x08020000
#define SECTOR5BASE 0x08040000
#define SECTOR6BASE 0x08080000
#define SECTOR7BASE 0x080C0000

#define SECTOR0SIZE (32*SIZE_IN_KB)
#define SECTOR1SIZE (32*SIZE_IN_KB)
#define SECTOR2SIZE (32*SIZE_IN_KB)
#define SECTOR3SIZE (32*SIZE_IN_KB)
#define SECTOR4SIZE (128*SIZE_IN_KB)
#define SECTOR5SIZE (256*SIZE_IN_KB)
#define SECTOR6SIZE (256*SIZE_IN_KB)
#define SECTOR7SIZE (256*SIZE_IN_KB)

#define APP_BASE  SECTOR3BASE
#define BOOT_SIZE (SECTOR0SIZE+SECTOR1SIZE+SECTOR2SIZE)
#define APP_SIZE  (SECTOR3SIZE+SECTOR4SIZE+SECTOR5SIZE+SECTOR6SIZE+SECTOR7SIZE)
#define MAINT_SIZE 0x80000U
extern T_SBOOTFILE Boot_file_boot_code;
extern T_SBOOTFILE Boot_file_app_code;
extern T_SBOOTFILE Boot_file_maint_code;
extern T_SBOOTFILE Boot_file_swl_code;
extern T_APPDATA_PANEL  *Du_config_files[];

#endif /* _HDUDISPBBOOT_H_ */
