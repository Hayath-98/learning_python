/*
 ******************************************************************************
 * License Information  :  Howell Instruments, Inc.                           *
 *                         "Licensed Software" and "All rights reserved".     *
 ******************************************************************************
 *  File                : hdudispbboot.c
 *
 *  Description         : This file contains starting address and length of Boot, Maintainance
 *                                  and flight application software.
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
 *      1.2          Divya G P       01-Sep-2017           100028
 *      1.3          Rona B S        29-Jun-2020           100259
 *
 * Additional References : None
 *
 *****************************************************************************
 */

#include "hdudispbboot.h"               /* Contains functions prototypes of hdudispbfonts*/
#include "hdudispbbinascii.h"           /* Contains functions prototypes of hdudispbbinascii.*/
#include "hdudispbcrc.h"                /* Contains functions prototypes of hdudispbcrc*/
#include "hdudispbrterr.h"              /* Contains functions prototypes of hdudispbrterr*/
#include "hdudispbtext.h"               /* Contains functions prototypes of hdudispbtext.*/
#include "hdudispbappdata.h"			/* Contains appdata structure for configuration file*/

#define BOOT_CODE_SIZE         0x0010000U
#define APP_CODE_SIZE          0xC0000U
#define MAINT_CODE_SIZE        0x08040000
#define TOTAL_DISPLAY_CONFIG 6
#define LOADER_CODE_SIZE       0x08018000
#define LOADER_SIZE            0x28000


/* hdudispbboot-DB-LLR-001 */

/* Boot information. */
T_SBOOTFILE Boot_file_boot_code =
{
   SECTOR0BASE,
   BOOT_CODE_SIZE
};

/* Application information. */
T_SBOOTFILE Boot_file_app_code =
{
   FLIGHT_APP_ADDR,
   APP_CODE_SIZE
};

/* Maint information. */
T_SBOOTFILE Boot_file_maint_code =
{
   MAINT_CODE_SIZE,
   MAINT_SIZE
};

/* Loader information. */
T_SBOOTFILE Boot_file_swl_code =
{
   LOADER_CODE_SIZE,
   LOADER_SIZE
};



T_APPDATA_PANEL Rk043fn48h_configs=
{
    480,272,41,13,32,10,2,272
};

T_APPDATA_PANEL Aa065vd51_configs=
{
    640,480,10,30,10,10,2,200
};
T_APPDATA_PANEL Aa07mc52_configs=
{
	800,480,130,30,10,10,10,20
};
T_APPDATA_PANEL Kd035hvfma035_configs=
{
	320,480,130,30,10,10,10,20
};
T_APPDATA_PANEL Aa104sl12_configs=
{
	800,600,10,30,10,10,10,20
};
T_APPDATA_PANEL Aa104xd12_configs=
{
	1024,768,10,30,10,10,10,20
};
T_APPDATA_PANEL *Du_config_files[]=
{
		&Rk043fn48h_configs,
		&Aa065vd51_configs,
		&Aa07mc52_configs,
		&Kd035hvfma035_configs,
		&Aa104sl12_configs,
		&Aa104xd12_configs,
		(T_APPDATA_PANEL*)0/*Delimiter. */
};

