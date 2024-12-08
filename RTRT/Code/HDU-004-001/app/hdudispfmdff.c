/*
 ******************************************************************************
 * License Information  :  Howell Instruments, Inc.                           *
 *                         "Licensed Software" and "All rights reserved".     *
 ******************************************************************************
 *  File                : hdudispfmdff.c
 *
 *  Description         : This file extracts all the required data from the PDI
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
 *  Author(s)           : Dhanalakshmi D
 *
 *  Version History     :
 * <Version No.>     <Author>               <Date>            <Problem Report No.>
 *
 *      1.1           Dhanalakshmi     20-Mar-2021             100331
 *      1.2           Dhanalakshmi     20-Mar-2021             100331
 *      1.3           Dhanalakshmi     19-Apr-2021             100339
 *      1.4           Dhanalakshmi     24-Apr-2021             100344
 *      1.5           Dhanalakshmi     13-May-2021             100350
 *
 * Additional References : None
 *
 ******************************************************************************
 */

#include "hdudispfmdff.h"      /*  Description contains Fuel flow functionalities */
#include "hdudispfgrapp.h"     /* routines for all graph */
#include "hdudispfmenu.h"      /* contains prototype for menu module*/
#include "hdudispfa429.h"      /* Routines for arinc 429 */
#include "hdudispftext.h"      /*  Routines which maintain text display and updates */
#include "hdudispfparams.h"    /* provides the tags for various parameters and parameter units.*/
#include "hdudispffonts.h"     /* contains prototype of Fonts */
#include "hdulibbasictypes.h"  /* Standard basic data type definitions */


/*
 * Function                :  SetFuelFlowData
 *
 * Description             :  This function stores all the system information words read
 *                             from label 244
 *
 * Formal parameter(s)     :  T_UINT8 a429_tag - IN system information index
 *                            T_FLOAT data     - IN label 244 data
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */

void SetFuelFlowData(T_UINT8 a429_tag, T_FLOAT data)
{
	/*hdudispfmdff-SetFuelFlowData-DB-LLR-001*/
    Fuel_flow_data  = (T_FLOAT)data;
    Ff_a429_tag = (T_UINT8) a429_tag;
}

/*
 * Function                :  SetCMUFuelFlowEnable
 *
 * Description             :  This function stores the fuel flow enable/disable flag
 *
 * Formal parameter(s)     :  T_UINT8 ff_enable_flag - Fuel flow enable flag from DAU
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */

void SetCMUFuelFlowEnable(T_UINT8 ff_enable_flag)
{
	/*hdudispfmdff-SetCMUFuelFlowEnable-DB-LLR-001*/
	  /* CMU fuel flow enable/disable bit from DAU - label 273 id-3, bit-25*/
	 Cmu_fuel_flow = ff_enable_flag;
}


/*
 * Function                : AppFuelFlowDraw
 *
 * Description             : The function displays CAS messages, exceedences ,
 *                           Cool down timer and Manual timer
 *
 * Formal parameter(s)     : None
 *
 * Return Value            : None
 *
 * Assumption              : None
 *
 */
void AppFuelFlowDraw(void)
{

   T_CHAR value[4] ="000";
   T_CHAR ff_redx[5] = "XXXX";

  /*hdudispfmdff-AppFuelFlowDraw-DB-LLR-001*/
  if(PARAM_OK == Parameters[Ff_a429_tag].reading.stat)
     {
        FloatToString((T_FLOAT)Fuel_flow_data, value, (T_UINT8)THREE);
        MemCpy(&Ff_text[3],&value,3);
        TextDispString((T_INT8 *)&Ff_text,
								90,
								346,
								E_NORMAL_FONT,
								WHITE,
								TX_NO_FLASH,
								V_NORMAL,
								ALIGN_CENTER
							   );
     }
	 /*hdudispfmdff-AppFuelFlowDraw-DB-LLR-002*/
  else
          {
              if(NCD == Parameters[Ff_a429_tag].reading.stat)
              {
                 MemCpy(&ff_redx[0],"NCD ",4);
              }
			  /*hdudispfmdff-AppFuelFlowDraw-DB-LLR-003*/
              MemCpy(&Ff_text[3],"    ",4);
              TextDispString((T_INT8 *)&Ff_text,
								90,
								346,
								E_NORMAL_FONT,
								WHITE,
								TX_NO_FLASH,
								V_NORMAL,
								ALIGN_CENTER
							   );
              TextDispString((T_INT8 *)&ff_redx,
								75,
								346,
								E_NORMAL_FONT,
								RED,
								TX_NO_FLASH,
								V_NORMAL,
								ALIGN_CENTER
							   );
          }
}




