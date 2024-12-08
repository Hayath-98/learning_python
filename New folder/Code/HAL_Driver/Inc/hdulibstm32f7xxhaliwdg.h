/*
 ******************************************************************************
 * License Information  :  Howell Instruments, Inc.                           *
 *                         "Licensed Software" and "All rights reserved".     *
 ******************************************************************************
 *  File                : hdulibstm32f7xxhaliwdg.h
 *
 *  Description         : This file provides prototypes of Watchdog (IWDG) peripheral.
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
 *      1.1          Shruthi M N       15-Oct-2017             100083
 *      1.2          Shruthi M N       30-Oct-2017             100104
 *
 * Additional References : None
 *
 ******************************************************************************
 */

#ifndef _HDULIBSTM32F7XXHALIWDG_H_
#define _HDULIBSTM32F7XXHALIWDG_H_

#include "hdulibstm32f7xxhaldef.h" /*Contains the HAL defination module */
#include "hdulibstm32f746xx.h"  /* CMSIS Cortex-M7 Device Peripheral Access Layer */

typedef struct
{
   T_UINT32 Prescaler;  /*
                         * Select the prescaler of the IWDG.
                         * This parameter can be a value of @ref IWDG_Prescaler
                         */

   T_UINT32 Reload;     /*
                         * Specifies the IWDG down-counter reload value.
                         * This parameter must be a number between Min_Data = 0
                         * and Max_Data = 0x0FFF
                         */

   T_UINT32 Window;     /*
                         * Specifies the window value to be compared to the down-counter.
                         * This parameter must be a number between Min_Data = 0
                         * and Max_Data = 0x0FFF
                         */

} T_IWDG_INIT_TYPE_DEF;


typedef struct
{
   /*Register base address*/
   T_IWDG                  *Instance;

  /*IWDG required parameters */
  T_IWDG_INIT_TYPE_DEF     Init;

}T_IWDG_HANDLE_TYPE;

#define IWDG_PRESCALER_4                  0x00000000u
#define IWDG_PRESCALER_8                  IWDG_PR_PR_0
#define IWDG_PRESCALER_16                 IWDG_PR_PR_1
#define IWDG_PRESCALER_32                 (IWDG_PR_PR_1 | IWDG_PR_PR_0)
#define IWDG_PRESCALER_64                 IWDG_PR_PR_2
#define IWDG_PRESCALER_128                (IWDG_PR_PR_2 | IWDG_PR_PR_0)
#define IWDG_PRESCALER_256                (IWDG_PR_PR_2 | IWDG_PR_PR_1)
#define IWDG_KEY_RELOAD                   0x0000AAAAu
#define IWDG_KEY_ENABLE                   0x0000CCCCu
#define IWDG_KEY_WRITE_ACCESS_ENABLE      0x00005555u
#define IWDG_KEY_WRITE_ACCESS_DISABLE     0x00000000u
#define IWDG_WINDOW_DISABLE               IWDG_WINR_WIN

#define __HAL_IWDG_START(__HANDLE__)           WRITE_REG((__HANDLE__)->Instance->KR, \
                                               IWDG_KEY_ENABLE)

#define __HAL_IWDG_RELOAD_COUNTER(__HANDLE__)  WRITE_REG((__HANDLE__)->Instance->KR, \
                                               IWDG_KEY_RELOAD)

#define IWDG_ENABLE_WRITE_ACCESS(__HANDLE__)  WRITE_REG((__HANDLE__)->Instance->KR,  \
                                              IWDG_KEY_WRITE_ACCESS_ENABLE)

#define IWDG_DISABLE_WRITE_ACCESS(__HANDLE__) WRITE_REG((__HANDLE__)->Instance->KR, \
                                              IWDG_KEY_WRITE_ACCESS_DISABLE)

#define IS_IWDG_PRESCALER(__PRESCALER__)      (((__PRESCALER__) == IWDG_PRESCALER_4)  || \
                                               ((__PRESCALER__) == IWDG_PRESCALER_8)  || \
                                               ((__PRESCALER__) == IWDG_PRESCALER_16) || \
                                               ((__PRESCALER__) == IWDG_PRESCALER_32) || \
                                               ((__PRESCALER__) == IWDG_PRESCALER_64) || \
                                               ((__PRESCALER__) == IWDG_PRESCALER_128)|| \
                                               ((__PRESCALER__) == IWDG_PRESCALER_256))

#define IS_IWDG_RELOAD(__RELOAD__)            ((__RELOAD__) <= IWDG_RLR_RL)

#define IS_IWDG_WINDOW(__WINDOW__)            ((__WINDOW__) <= IWDG_WINR_WIN)


extern T_HAL_STATUS HalIwdgRefresh(T_IWDG_HANDLE_TYPE *h_iwdg);
extern T_HAL_STATUS HalIwdgInit(T_IWDG_HANDLE_TYPE *h_iwdg);


#endif /* _HDULIBSTM32F7XXHALIWDG_H_ */

