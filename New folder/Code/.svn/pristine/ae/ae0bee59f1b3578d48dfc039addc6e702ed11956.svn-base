/*
 ******************************************************************************
 * License Information  :  Howell Instruments, Inc.                           *
 *                         "Licensed Software" and "All rights reserved".     *
 ******************************************************************************
 *  File                : hdudispfforeground.h
 *
 *  Description         : This file contains the routines which maintain the
 *                          "Real Time" foreground layer of the display.
 *
 *  Compiler            :  GNU gcc(GNU Tools for ARM Embedded Processors) version 5.4.1 20160919
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
 *      1.1           Shilpa A R    24-Jul-2017             100064
 *      1.2           Vinay H       09-Oct-2017             100064
 *      1.3           Shruthi M N   13-Oct-2017             100083
 *      1.4           Shruthi M N   30-Oct-2017             100104
 *      1.5           Chaithra J    21-Jun-2020             100259
 *      1.6           Rona B S      29-Jun-2020             100259
 *
 * Additional References : None
 *
 ******************************************************************************
 */

#ifndef _HDUDISPFFOREGROUND_H_
#define _HDUDISPFFOREGROUND_H_

#include "hdudispfwidgets.h"  /* Contains routines for widget params */
extern T_BOOL Bool_menu_cal;

/*Updated as per PR100083*/
typedef struct
{
   T_SDISREGION disRegion;
   T_SPOLY *poly_red_x;
}T_DIS_REDX;

typedef struct
{
   T_SDISREGION disRegion;
   T_SPOLY *poly_red_x;
}T_CAS_REDX;

/* Sem to signal task execution.    */

extern void  ForegroundInit(void);
extern void ClearForeground(void);
extern void ForegroundLoadBackground(T_UINT16 *pu16Src);
extern void ForegroundClear(void);
extern void ForegroundReDraw1(void);
extern void ForegroundReDraw2(void);
extern void ForegroundReDraw3(void);
/*Updated as per PR100083*/
extern void CasRedxInit(T_CAS_REDX *cas_redx);
extern void DisRedxInit(T_DIS_REDX *dis_redx);
extern T_EFLASHSTATE EGetFlashState(void);

extern void VHadFlash(void);

#endif /* __FOREGROUND_H */
