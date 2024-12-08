/*
 ******************************************************************************
 * License Information  :  Howell Instruments, Inc.                           *
 *                         "Licensed Software" and "All rights reserved".     *
 ******************************************************************************
 *  File                : hdulibstm32f7xx.h
 *
 *  Description         : CMSIS STM32F7xx Device Peripheral Access Layer Header File.
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
 *  Author(s)           : Vinay H
 *
 *  Version History     :
 * <Version No.>     <Author>          <Date>         <Problem Report No.>
 *
 *      1.1          Vinay H         25-Jul-2017             -
 *      1.2          Rona B.S        02-Sep-2017            100028  
 *      1.3          Shilpa A R      07-Nov-2017            100161
 *      1.4          Rona B.S        12-Sep-2020            100276
 *
 * Additional References : None
 *
 ******************************************************************************
 */

#ifndef _HDULIBSTM32F7XX_H_
#define _HDULIBSTM32F7XX_H_

#if !defined  (STM32F7)
#define STM32F7
#endif

#if !defined (STM32F756xx) && !defined (STM32F746xx) && !defined (STM32F745xx) && \
   !defined (STM32F767xx) && !defined (STM32F769xx) && !defined (STM32F777xx) && \
   !defined (STM32F779xx) && !defined (STM32F722xx) && !defined (STM32F723xx) && \
   !defined (STM32F732xx) && !defined (STM32F733xx)
#if 0
  /* #define STM32F756XX */   /*!< STM32F756VG, STM32F756ZG, STM32F756ZG, STM32F756IG, STM32F756BG,
                                   STM32F756NG Devices */
  /* #define STM32F746XX */   /*!< STM32F746VE, STM32F746VG, STM32F746ZE, STM32F746ZG, STM32F746IE,
                        STM32F746IG, STM32F746BE, STM32F746BG, STM32F746NE, STM32F746NG Devices */
  /* #define STM32F745XX */   /*!< STM32F745VE, STM32F745VG, STM32F745ZG, STM32F745ZE, STM32F745IE,
                                    STM32F745IG Devices */
  /* #define STM32F765XX */   /*!< STM32F765BI, STM32F765BG, STM32F765NI, STM32F765NG, STM32F765II,
                      STM32F765IG, STM32F765ZI, STM32F765ZG, STM32F765VI, STM32F765VG Devices */
#endif
   /*
    * STM32F767BG, STM32F767BI, STM32F767IG, STM32F767II, STM32F767NG, STM32F767NI,
    * STM32F767VG, STM32F767VI, STM32F767ZG, STM32F767ZI Devices
    */
   #define STM32F767xx

#if 0
  /* #define STM32F769XX */   /*!< STM32F769AG, STM32F769AI, STM32F769BG, STM32F769BI, STM32F769IG,
                                    STM32F769II,STM32F769NG, STM32F769NI, STM32F768AI Devices */
  /* #define STM32F777XX */   /*!< STM32F777VI, STM32F777ZI, STM32F777II, STM32F777BI, STM32F777NI
                                 Devices */
  /* #define STM32F779XX */   /*!< STM32F779II, STM32F779BI, STM32F779NI, STM32F779AI, STM32F778AI
                                 Devices */
  /* #define STM32F722XX */   /*!< STM32F722IE, STM32F722ZE, STM32F722VE, STM32F722RE, STM32F722IC,
                                    STM32F722ZC,STM32F722VC, STM32F722RC Devices */
  /* #define STM32F723XX */   /*!< STM32F723IE, STM32F723ZE, STM32F723VE, STM32F723IC, STM32F723ZC,
                                 STM32F723VC Devices */
  /* #define STM32F732XX */   /*!< STM32F732IE, STM32F732ZE, STM32F732VE, STM32F732RE Devices */
  /* #define STM32F733XX */   /*!< STM32F733IE, STM32F733ZE, STM32F733VE Devices */
#endif

#endif


#if !defined  (USE_HAL_DRIVER)
/*
 * @brief Comment the line below if you will not use the peripherals drivers.
 * In this case, these drivers will not be included and the application code will
 * be based on direct access to peripherals registers
 */
  /*#define USE_HAL_DRIVER */
#endif /* USE_HAL_DRIVER */

#define __STM32F7_CMSIS_VERSION_MAIN   (0x01) /* [31:24] main version */
#define __STM32F7_CMSIS_VERSION_SUB1   (0x01) /* [23:16] sub1 version */
#define __STM32F7_CMSIS_VERSION_SUB2   (0x02) /* [15:8]  sub2 version */
#define __STM32F7_CMSIS_VERSION_RC     (0x00) /* [7:0]  release candidate */
#define __STM32F7_CMSIS_VERSION        ((__STM32F7_CMSIS_VERSION_MAIN << 24)\
                                       |(__STM32F7_CMSIS_VERSION_SUB1 << 16)\
                                       |(__STM32F7_CMSIS_VERSION_SUB2 << 8 )\
                                       |(__STM32F7_CMSIS_VERSION))

typedef enum
{
  RESET = 0,
  SET = !RESET
} T_FLAG_STATUS, T_IT_STATUS;

typedef enum
{
  DISABLE = 0,
  ENABLE = !DISABLE
} T_FUNCTIONAL_STATE;

#define IS_FUNCTIONAL_STATE(STATE) (((STATE) == DISABLE) || ((STATE) == ENABLE))

typedef enum
{
  ERROR = 0,
  SUCCESS = !ERROR
} T_ERROR_STATUS;


#define SET_BIT(REG, BIT)     ((REG) |= (BIT))

#define CLEAR_BIT(REG, BIT)   ((REG) &= ~(BIT))

#define READ_BIT(REG, BIT)    ((REG) & (BIT))

#define CLEAR_REG(REG)        ((REG) = (0x0))

#define WRITE_REG(REG, VAL)   ((REG) = (VAL))

#define READ_REG(REG)         ((REG))

#define MODIFY_REG(REG, CLEARMASK, SETMASK)  (WRITE_REG((REG), (((READ_REG(REG)) \
         & (~(CLEARMASK))) | (SETMASK))))

/*Updated as per PR100161*/
#define POSITION_VAL(VAL)     (COUNT_LEADING_ZEROS(__RBIT(VAL))) /*Counts leading zeros*/


#endif /* __HDULIBSTM32F7XX_H */
