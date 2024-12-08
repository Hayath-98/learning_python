/*
 ******************************************************************************
 * License Information  :  Howell Instruments, Inc.                           *
 *                         "Licensed Software" and "All rights reserved".     *
 ******************************************************************************
 *  File                : hdulibstm32f7xxhaliwdg.c
 *
 *  Description         : This file provides firmware functions to manage the following
 *                        functionalities of the Independent Watchdog (IWDG) peripheral:
 *                        - Initialization and Start functions
 *                        - IO operation functions
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
 *  Author(s)           : Shruthi MN
 *
 *  Version History     :
 * <Version No.>     <Author>          <Date>         <Problem Report No.>
 *
 *      1.1          Shruthi MN       15-Oct-2017             100083
 *
 * Additional References : None
 *
 ******************************************************************************
 */

#include "hdulibstm32f7xxhal.h" /* Header files for HAL driver*/
#include "hdulibstm32f7xxhaliwdg.h" /* Watchdog routines*/


#define HAL_IWDG_DEFAULT_TIMEOUT        48U

/*
 * Function                : HalIwdgInit
 *
 * Description             : This function initializes the IWDG according to the specified
 *                           parameters in the  IWDG_INIT_TYPE_DEF and start watchdog. Before
 *                           exiting function, watchdog is refreshed in order to have
 *                           correct time base.
 *
 * Formal parameter(s)     : T_IWDG_HANDLE_TYPE *h_iwdg -IN  pointer to a T_IWDG_HANDLE_TYPE
 *                           structure that contains the configuration information for the
 *                           specified IWDG module.
 *
 * Return Value            : HAL status
 *
 * Assumption              : None
 *
 */

T_HAL_STATUS HalIwdgInit(T_IWDG_HANDLE_TYPE *h_iwdg)
{
  T_UINT32 tick_start = 0;

  /*hdulibstm32f7xxhaladc-HalIwdgInit-DB-LLR-001*/
  /* Check the IWDG handle allocation */
  if(NULL == h_iwdg)
  {
    return HAL_ERROR;
  }
  else
  {
   ; /* Do nothing */
  }

  /*hdulibstm32f7xxhaladc-HalIwdgInit-DB-LLR-002*/
  /* Enable IWDG. LSI is turned on automaticaly */
  __HAL_IWDG_START(h_iwdg);

  /*hdulibstm32f7xxhaladc-HalIwdgInit-DB-LLR-003*/
  /* Enable write access to IWDG_PR, IWDG_RLR and IWDG_WINR registers by writing 0x5555 in KR */
  IWDG_ENABLE_WRITE_ACCESS(h_iwdg);

  /* Write to IWDG registers the Prescaler & Reload values to work with */
  h_iwdg->Instance->PR = h_iwdg->Init.Prescaler;
  h_iwdg->Instance->RLR = h_iwdg->Init.Reload;

  /*hdulibstm32f7xxhaladc-HalIwdgInit-DB-LLR-004*/
  /* Check pending flag, if previous update not done, return timeout */
  tick_start = HALGetTick();

  /*hdulibstm32f7xxhaladc-HalIwdgInit-DB-LLR-005*/
  /* Wait for register to be updated */
  while(h_iwdg->Instance->SR != RESET)
  {
    if((HALGetTick() - tick_start ) > HAL_IWDG_DEFAULT_TIMEOUT)
    {
      return HAL_TIMEOUT;
    }
  }

  /*hdulibstm32f7xxhaladc-HalIwdgInit-DB-LLR-006*/
  /* If window parameter is different than current value, modify window register */
  if(h_iwdg->Instance->WINR != h_iwdg->Init.Window)
  {
    /*
     * Write to IWDG WINR the IWDG_Window value to compare with. In any case,
     * even if window feature is disabled, Watchdog will be reloaded by writing
     * windows register
     */
    h_iwdg->Instance->WINR = h_iwdg->Init.Window;
  }
  else
  {
    /* Reload IWDG counter with value defined in the reload register */
    __HAL_IWDG_RELOAD_COUNTER(h_iwdg);
  }

  /*hdulibstm32f7xxhaladc-HalIwdgInit-DB-LLR-007*/
  /* Return function status */
  return HAL_OK;
}


/*
 * Function                : HalIwdgRefresh
 *
 * Description             : Function refreshs the IWDG.
 *
 * Formal parameter(s)     : T_IWDG_HANDLE_TYPE *h_iwdg - IN pointer to a T_IWDG_HANDLE_TYPE
 *                           structure that contains the configuration information
 *                           for the specified IWDG module.
 *
 * Return Value            : HAL status
 *
 * Assumption              : None
 *
 */

T_HAL_STATUS HalIwdgRefresh(T_IWDG_HANDLE_TYPE *h_iwdg)
{
  /*hdulibstm32f7xxhaladc-HalIwdgRefresh-DB-LLR-001*/
  /* Reload IWDG counter with value defined in the reload register */
  __HAL_IWDG_RELOAD_COUNTER(h_iwdg);

  /* Return function status */
  return HAL_OK;
}

