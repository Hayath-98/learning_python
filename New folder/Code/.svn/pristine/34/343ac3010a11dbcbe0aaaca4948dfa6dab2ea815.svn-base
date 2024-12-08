/*
 ******************************************************************************
 * License Information  :  Howell Instruments, Inc.                           *
 *                         "Licensed Software" and "All rights reserved".     *
 ******************************************************************************
 *  File                : hdulibcorecm7.h
 *
 *  Description         : CMSIS Cortex-M7 Core Peripheral Access Layer Header File
 *
 *  Compiler            : GNU gcc(GNU Tools for ARM Embedded Processors) version 5.4.1 20160919
 *
 *
 *  Compiler options    : As per section 10.3.1 of Software Development Plan (HDU-001-002).
 *
 *  Pragma              : None
 *
 *  H/W platform        : ARM Cortex-M7 (STM32F767)
 *
 *  Portability         : None
 *
 *  Author(s)           : Ajay J G
 *
 *  Version History     :
 *
 * <Version No.>     <Author>          <Date>         <Problem Report No.>
 *
 *      1.1          Ajay J G        03-Aug-2017             -
 *      1.2          Rona B.S        02-Sep-2017         100028
 *
 * Additional References : None
 *
 ******************************************************************************
 */

#ifndef _HDULIBCORECM7_H_
#define _HDULIBCORECM7_H_

#include "hdulibstmcorecomm.h"   /* Header files for Core Communication*/
#include "hdulibbasictypes.h"         /* Define standard types */

/*******************************************************************************/
/*                 CMSIS definitions                                           */
/******************************************************************************/

/*  CMSIS CM7 definitions */
#define __CM7_CMSIS_VERSION_MAIN  (0x04U)       /* [31:16] CMSIS HAL main version */
#define __CM7_CMSIS_VERSION_SUB   (0x1EU)       /* [15:0]  CMSIS HAL sub version */
/* CMSIS HAL version number */
#define __CM7_CMSIS_VERSION       ((__CM7_CMSIS_VERSION_MAIN << 16U) | \
                                    __CM7_CMSIS_VERSION_SUB           )

#define EXTRACT_BIT4_12            0x00000FF0UL
#define HEX_220                    0x220UL
#define HEX_20                     0x020UL
#define HEX_FF                     0xFFUL
#define HEX_1F                     0x1FUL
#define HEX_5FA                    0x5FAUL


#if   defined ( __CC_ARM )
  #define __ASM            __asm             /* asm keyword for ARM Compiler */
  #define __INLINE         __inline          /* inline keyword for ARM Compiler */
  #define __STATIC_INLINE  static __inline

#elif defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)
  #define __ASM            __asm             /* asm keyword for ARM Compiler */
  #define __INLINE         __inline          /* inline keyword for ARM Compiler */
  #define __STATIC_INLINE  static __inline

#elif defined ( __GNUC__ )
  #define __ASM            __asm             /* asm keyword for GNU Compiler */
  #define __INLINE         inline            /* inline keyword for GNU Compiler */
  #define __STATIC_INLINE  static inline

#elif defined ( __ICCARM__ )
  #define __ASM            __asm             /* asm keyword for IAR Compiler */
  /* inline keyword for IAR Compiler. Only available in High optimization mode! */
  #define __INLINE         inline
  #define __STATIC_INLINE  static inline

#elif defined ( __TMS470__ )
  #define __ASM            __asm            /* asm keyword for TI CCS Compiler */
  #define __STATIC_INLINE  static inline

#elif defined ( __TASKING__ )
  #define __ASM            __asm          /* asm keyword for TASKING Compiler */
  #define __INLINE         inline         /* inline keyword for TASKING Compiler */
  #define __STATIC_INLINE  static inline

#elif defined ( __CSMC__ )
  #define __ASM            _asm          /* asm keyword for COSMIC Compiler */
  /* inline keyword for COSMIC Compiler. Use -pc99 on compile line */
  #define __INLINE         inline
  #define __STATIC_INLINE  static inline

#else
  #error Unknown compiler
#endif /*__CC_ARM*/

/*
 * __FPU_USED indicates whether an FPU is used or not.
 * For this, __FPU_PRESENT has to be checked prior to making use of
 * FPU specific registers and functions.
 */
#if defined ( __CC_ARM )
  #if defined __TARGET_FPU_VFP
    #if (__FPU_PRESENT == ONE)
      #define __FPU_USED       1U
    #else
     #error "Compiler generates FPU instructions for a device \
             without an FPU (check __FPU_PRESENT)"
     #define __FPU_USED       0U
    #endif
  #else
    #define __FPU_USED         0U
  #endif

#elif defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)
  #if defined __ARM_PCS_VFP
    #if (__FPU_PRESENT == ONE)
      #define __FPU_USED       1U
    #else
      #warning "Compiler generates FPU instructions for a device \
                without an FPU (check __FPU_PRESENT)"
      #define __FPU_USED       0U
    #endif
  #else
    #define __FPU_USED         0U
  #endif

#elif defined ( __GNUC__ )
  #if defined (__VFP_FP__) && !defined(__SOFTFP__)
    #if (__FPU_PRESENT == ONE)
      #define __FPU_USED       1U
    #else
     #error "Compiler generates FPU instructions for a device without \
             an FPU (check __FPU_PRESENT)"
     #define __FPU_USED       0U
    #endif
  #else
    #define __FPU_USED         0U
  #endif

#elif defined ( __ICCARM__ )
  #if defined __ARMVFP__
    #if (__FPU_PRESENT == ONE)
      #define __FPU_USED       1U
    #else
     #error "Compiler generates FPU instructions for a device \
             without an FPU (check __FPU_PRESENT)"
      #define __FPU_USED       0U
    #endif
  #else
    #define __FPU_USED         0U
  #endif

#elif defined ( __TMS470__ )
  #if defined __TI_VFP_SUPPORT__
    #if (__FPU_PRESENT == ONE)
      #define __FPU_USED       1U
    #else
     #error "Compiler generates FPU instructions for a device \
             without an FPU (check __FPU_PRESENT)"
      #define __FPU_USED       0U
    #endif
  #else
    #define __FPU_USED         0U
  #endif

#elif defined ( __TASKING__ )
  #if defined __FPU_VFP__
    #if (__FPU_PRESENT == ONE)
      #define __FPU_USED       1U
    #else
     #error "Compiler generates FPU instructions for a device \
              without an FPU (check __FPU_PRESENT)"
      #define __FPU_USED       0U
    #endif
  #else
    #define __FPU_USED         0U
  #endif

#elif defined ( __CSMC__ )
  #if ( __CSMC__ & 0x400U)
    #if (__FPU_PRESENT == ONE)
      #define __FPU_USED       1U
    #else
     #error "Compiler generates FPU instructions for a device \
              without an FPU (check __FPU_PRESENT)"
      #define __FPU_USED       0U
    #endif
  #else
    #define __FPU_USED         0U
  #endif

#endif /*( __CC_ARM )*/

/* IO definitions (access restrictions to peripheral registers) */

/*
 * \defgroup CMSIS_glob_defs CMSIS Global Defines
 * <strong>IO Type Qualifiers</strong> are used
 * \li to specify the access to peripheral variables.
 * \li for automatic generation of peripheral register debug information.
 */

#define   __I     volatile const       /* Defines 'read only' permissions */
#define     __O     volatile           /* Defines 'write only' permissions */
#define     __IO    volatile           /* Defines 'read / write' permissions */

/* following defines should be used for structure members */
#define     __IM     volatile const      /* Defines 'read only' structure member permissions */
#define     __OM     volatile            /* Defines 'write only' structure member permissions */
#define     __IOM    volatile            /* Defines 'read / write' structure member permissions */
#define __STATIC_INLINE  static inline
#define __ASM            __asm

/*
 ******************************************************************************
 *                 Register Abstraction
 * Core Register contains:
 * - Core Register
 * - Core NVIC Register
 * - Core SCB Register
 * - Core SysTick Register
 * - Core Debug Register
 * - Core MPU Register
 * - Core FPU Register
 *****************************************************************************
 */
/*
 * \defgroup CMSIS_core_register Defines and Type Definitions
 * \brief Type definitions and defines for Cortex-M processor based devices.
 */

/* brief  Union type to access the Application Program Status Register (APSR). */
typedef union
{
  struct
  {
    T_UINT32 _reserved0:16;     /* bit:  0..15  Reserved */
    T_UINT32 GE:4;            /* bit: 16..19  Greater than or Equal flags */
    T_UINT32 _reserved1:7;    /* bit: 20..26  Reserved */
    T_UINT32 Q:1;             /* bit:     27  Saturation condition flag */
    T_UINT32 V:1;             /* bit:     28  Overflow condition code flag */
    T_UINT32 C:1;             /* bit:     29  Carry condition code flag */
    T_UINT32 Z:1;             /* bit:     30  Zero condition code flag */
    T_UINT32 N:1;             /* bit:     31  Negative condition code flag */
  } T_BIT;                    /* Structure used for bit  access */
  T_UINT32 w;                 /* Type      used for word access */
} T_APSR;

/* APSR Register Definitions */
#define APSR_N_POS                         31U       /* APSR: N Position */
#define APSR_N_MSK                         (1UL << APSR_N_POS)      /* APSR: N Mask */

#define APSR_Z_POS                         30U       /* APSR: Z Position */
#define APSR_Z_MSK                         (1UL << APSR_Z_POS)      /* APSR: Z Mask */

#define APSR_C_POS                         29U       /* APSR: C Position */
#define APSR_C_MSK                         (1UL << APSR_C_POS)      /* APSR: C Mask */

#define APSR_V_POS                         28U       /* APSR: V Position */
#define APSR_V_MSK                         (1UL << APSR_V_POS)      /* APSR: V Mask */

#define APSR_Q_POS                         27U       /* APSR: Q Position */
#define APSR_Q_MSK                         (1UL << APSR_Q_POS)      /* APSR: Q Mask */

#define APSR_GE_POS                        16U       /* APSR: GE Position */
#define APSR_GE_MSK                        (0xFUL << APSR_GE_POS)   /* APSR: GE Mask */

/* brief  Union type to access the Interrupt Program Status Register (IPSR). */
typedef union
{
  struct
  {
    T_UINT32 ISR:9;        /* bit:  0.. 8  Exception number */
    T_UINT32 _reserved0:23;/* bit:  9..31  Reserved */
  } T_BIT;                 /* Structure used for bit  access */
  T_UINT32 w;              /* Type      used for word access */
} T_IPSR;

/* IPSR Register Definitions */
#define IPSR_ISR_POS                        0U           /* IPSR: ISR Position */
#define IPSR_ISR_MSK                       (0x1FFUL)   /* IPSR: ISR Mask */

/* brief  Union type to access the Special-Purpose Program Status Registers (XPSR). */
typedef union
{
  struct
  {
    T_UINT32 ISR:9;        /* bit:  0.. 8  Exception number */
    T_UINT32 _reserved0:7; /* bit:  9..15  Reserved */
    T_UINT32 GE:4;         /* bit: 16..19  Greater than or Equal flags */
    T_UINT32 _reserved1:4; /* bit: 20..23  Reserved */
    T_UINT32 T:1;          /* bit:     24  Thumb bit        (read 0) */
    T_UINT32 IT:2;         /* bit: 25..26  saved IT state   (read 0) */
    T_UINT32 Q:1;          /* bit:     27  Saturation condition flag */
    T_UINT32 V:1;          /* bit:     28  Overflow condition code flag */
    T_UINT32 C:1;          /* bit:     29  Carry condition code flag */
    T_UINT32 Z:1;          /* bit:     30  Zero condition code flag */
    T_UINT32 N:1;          /* bit:     31  Negative condition code flag */
  } T_BIT;                 /* Structure used for bit  access */
  T_UINT32 w;               /* Type      used for word access */
} T_XPSR;

/* XPSR Register Definitions */
#define XPSR_N_POS                         31U         /* XPSR: N Position */
#define XPSR_N_MSK                         (1UL << XPSR_N_POS)        /* XPSR: N Mask */

#define XPSR_Z_POS                         30U         /* XPSR: Z Position */
#define XPSR_Z_MSK                         (1UL << XPSR_Z_POS)        /* XPSR: Z Mask */

#define XPSR_C_POS                         29U         /* XPSR: C Position */
#define XPSR_C_MSK                         (1UL << XPSR_C_POS)        /* XPSR: C Mask */

#define XPSR_V_POS                         28U         /* XPSR: V Position */
#define XPSR_V_MSK                         (1UL << XPSR_V_POS)        /* XPSR: V Mask */

#define XPSR_Q_POS                         27U         /* XPSR: Q Position */
#define XPSR_Q_MSK                         (1UL << XPSR_Q_POS)        /* XPSR: Q Mask */

#define XPSR_IT_POS                        25U         /* XPSR: IT Position */
#define XPSR_IT_MSK                        (3UL << XPSR_IT_POS)       /* XPSR: IT Mask */

#define XPSR_T_POS                         24U         /* XPSR: T Position */
#define XPSR_T_MSK                         (1UL << XPSR_T_POS)        /* XPSR: T Mask */

#define XPSR_GE_POS                        16U         /* XPSR: GE Position */
#define XPSR_GE_MSK                        (0xFUL << XPSR_GE_POS)     /* XPSR: GE Mask */

#define XPSR_ISR_POS                        0U         /* XPSR: ISR Position */
#define XPSR_ISR_MSK                       (0x1FFUL)   /* XPSR: ISR Mask */

/* brief  Union type to access the Control Registers (CONTROL). */
typedef union
{
  struct
  {
    T_UINT32 nPRIV:1;         /* bit:      0  Execution privilege in Thread mode */
    T_UINT32 SPSEL:1;         /* bit:      1  Stack to be used */
    T_UINT32 FPCA:1;          /* bit:      2  FP extension active flag */
    T_UINT32 _reserved0:29;     /* bit:  3..31  Reserved */
  } T_BIT;                    /* Structure used for bit  access */
  T_UINT32 w;                 /* Type      used for word access */
} T_CONTROL;

/* CONTROL Register Definitions */
#define CONTROL_FPCA_POS                    2U        /* CONTROL: FPCA Position */
#define CONTROL_FPCA_MSK                   (1UL << CONTROL_FPCA_POS)     /* CONTROL: FPCA Mask */

#define CONTROL_SPSEL_POS                   1U        /* CONTROL: SPSEL Position */
#define CONTROL_SPSEL_MSK                  (1UL << CONTROL_SPSEL_POS) /* CONTROL: SPSEL Mask */

#define CONTROL_NPRIV_POS                   0U        /* CONTROL: nPRIV Position */
#define CONTROL_NPRIV_MSK                  (1UL)/* CONTROL: nPRIV Mask */

/*
 * \ingroup    CMSIS_core_register
 * \defgroup   CMSIS_NVIC  Nested Vectored Interrupt Controller (NVIC)
 * \brief      Type definitions for the NVIC Registers
 */

/* brief  Structure type to access the Nested Vectored Interrupt Controller (NVIC).*/
typedef struct
{
  __IOM T_UINT32 ISER[8U];               /* Offset: 0x000 (R/W)  Interrupt Set Enable Register */
        T_UINT32 RESERVED0[24U];
  __IOM T_UINT32 ICER[8U];               /* Offset: 0x080 (R/W)  Interrupt Clear Enable Register */
        T_UINT32 RSERVED1[24U];
  __IOM T_UINT32 ISPR[8U];               /* Offset: 0x100 (R/W)  Interrupt Set Pending Register */
        T_UINT32 RESERVED2[24U];
  __IOM T_UINT32 ICPR[8U];               /* Offset: 0x180 (R/W)  Interrupt Clear Pending Register*/
        T_UINT32 RESERVED3[24U];
  __IOM T_UINT32 IABR[8U];               /* Offset: 0x200 (R/W)  Interrupt Active bit Register */
        T_UINT32 RESERVED4[56U];
  /* Offset: 0x300 (R/W)  Interrupt Priority Register (8Bit wide) */
  __IOM T_UINT8  IP[240U];
        T_UINT32 RESERVED5[644U];
  __OM  T_UINT32 STIR;               /* Offset: 0xE00 ( /W)  Software Trigger Interrupt Register */
}  T_NVIC;

/* Software Triggered Interrupt Register Definitions */
#define NVIC_STIR_INTID_POS                 0U        /* STIR: INTLINESNUM Position */

/* STIR: INTLINESNUM Mask */
#define NVIC_STIR_INTID_MSK                (0x1FFUL)

/*
 * \ingroup  CMSIS_core_register
 * \defgroup CMSIS_SCB     System Control Block (SCB)
 * \brief    Type definitions for the System Control Block Registers
 */

/* brief  Structure type to access the System Control Block (SCB). */
typedef struct
{
  __IM  T_UINT32 CPUID;          /* Offset: 0x000 (R/ )  CPUID Base Register */
  __IOM T_UINT32 ICSR;           /* Offset: 0x004 (R/W)  Interrupt Control and State Register */
  __IOM T_UINT32 VTOR;           /* Offset: 0x008 (R/W)  Vector Table Offset Register */
  /* Offset: 0x00C (R/W)  Application Interrupt and Reset Control Register */
  __IOM T_UINT32 AIRCR;
  __IOM T_UINT32 SCR;            /* Offset: 0x010 (R/W)  System Control Register */
  __IOM T_UINT32 CCR;            /* Offset: 0x014 (R/W)  Configuration Control Register */
  /* Offset: 0x018 (R/W)  System Handlers Priority Registers (4-7, 8-11, 12-15) */
  __IOM T_UINT8  SHPR[12U];
  __IOM T_UINT32 SHCSR;        /* Offset: 0x024 (R/W)  System Handler Control and State Register */
  __IOM T_UINT32 CFSR;           /* Offset: 0x028 (R/W)  Configurable Fault Status Register */
  __IOM T_UINT32 HFSR;           /* Offset: 0x02C (R/W)  HardFault Status Register */
  __IOM T_UINT32 DFSR;           /* Offset: 0x030 (R/W)  Debug Fault Status Register */
  __IOM T_UINT32 MMFAR;          /* Offset: 0x034 (R/W)  MemManage Fault Address Register */
  __IOM T_UINT32 BFAR;           /* Offset: 0x038 (R/W)  BusFault Address Register */
  __IOM T_UINT32 AFSR;           /* Offset: 0x03C (R/W)  Auxiliary Fault Status Register */
  __IM  T_UINT32 ID_PFR[2U];     /* Offset: 0x040 (R/ )  Processor Feature Register */
  __IM  T_UINT32 ID_DFR;         /* Offset: 0x048 (R/ )  Debug Feature Register */
  __IM  T_UINT32 ID_AFR;         /* Offset: 0x04C (R/ )  Auxiliary Feature Register */
  __IM  T_UINT32 ID_MFR[4U];     /* Offset: 0x050 (R/ )  Memory Model Feature Register */
  __IM  T_UINT32 ID_ISAR[5U];    /* Offset: 0x060 (R/ )  Instruction Set Attributes Register */
        T_UINT32 RESERVED0[1U];
  __IM  T_UINT32 CLIDR;          /* Offset: 0x078 (R/ )  Cache Level ID register */
  __IM  T_UINT32 CTR;            /* Offset: 0x07C (R/ )  Cache Type register */
  __IM  T_UINT32 CCSIDR;         /* Offset: 0x080 (R/ )  Cache Size ID Register */
  __IOM T_UINT32 CSSELR;         /* Offset: 0x084 (R/W)  Cache Size Selection Register */
  __IOM T_UINT32 CPACR;          /* Offset: 0x088 (R/W)  Coprocessor Access Control Register */
        T_UINT32 RESERVED3[93U];
  __OM  T_UINT32 STIR;           /* Offset: 0x200 ( /W)  Software Triggered Interrupt Register */
        T_UINT32 RESERVED4[15U];
  __IM  T_UINT32 MVFR0;          /* Offset: 0x240 (R/ )  Media and VFP Feature Register 0 */
  __IM  T_UINT32 MVFR1;          /* Offset: 0x244 (R/ )  Media and VFP Feature Register 1 */
  __IM  T_UINT32 MVFR2;          /* Offset: 0x248 (R/ )  Media and VFP Feature Register 1 */
        T_UINT32 RESERVED5[1U];
  __OM  T_UINT32 ICIALLU;        /* Offset: 0x250 ( /W)  I-Cache Invalidate All to PoU */
        T_UINT32 RESERVED6[1U];
  __OM  T_UINT32 ICIMVAU;        /* Offset: 0x258 ( /W)  I-Cache Invalidate by MVA to PoU */
  __OM  T_UINT32 DCIMVAC;        /* Offset: 0x25C ( /W)  D-Cache Invalidate by MVA to PoC */
  __OM  T_UINT32 DCISW;          /* Offset: 0x260 ( /W)  D-Cache Invalidate by Set-way */
  __OM  T_UINT32 DCCMVAU;        /* Offset: 0x264 ( /W)  D-Cache Clean by MVA to PoU */
  __OM  T_UINT32 DCCMVAC;        /* Offset: 0x268 ( /W)  D-Cache Clean by MVA to PoC */
  __OM  T_UINT32 DCCSW;          /* Offset: 0x26C ( /W)  D-Cache Clean by Set-way */
  __OM  T_UINT32 DCCIMVAC;    /* Offset: 0x270 ( /W)  D-Cache Clean and Invalidate by MVA to PoC */
  __OM  T_UINT32 DCCISW;         /* Offset: 0x274 ( /W)  D-Cache Clean and Invalidate by Set-way */
        T_UINT32 RESERVED7[6U];
  /* Offset: 0x290 (R/W)  Instruction Tightly-Coupled Memory Control Register */
  __IOM T_UINT32 ITCMCR;
  /* Offset: 0x294 (R/W)  Data Tightly-Coupled Memory Control Registers */
  __IOM T_UINT32 DTCMCR;
  __IOM T_UINT32 AHBPCR;         /* Offset: 0x298 (R/W)  AHBP Control Register */
  __IOM T_UINT32 CACR;           /* Offset: 0x29C (R/W)  L1 Cache Control Register */
  __IOM T_UINT32 AHBSCR;         /* Offset: 0x2A0 (R/W)  AHB Slave Control Register */
        T_UINT32 RESERVED8[1U];
  __IOM T_UINT32 ABFSR;          /* Offset: 0x2A8 (R/W)  Auxiliary Bus Fault Status Register */
} T_SCB;

/* SCB CPUID Register Definitions */
#define SCB_CPUID_IMPLEMENTER_POS          24U     /* SCB CPUID: IMPLEMENTER Position */
/* SCB CPUID: IMPLEMENTER Mask */
#define SCB_CPUID_IMPLEMENTER_MSK          (0xFFUL << SCB_CPUID_IMPLEMENTER_POS)

#define SCB_CPUID_VARIANT_POS              20U     /* SCB CPUID: VARIANT Position */
/* SCB CPUID: VARIANT Mask */
#define SCB_CPUID_VARIANT_MSK              (0xFUL << SCB_CPUID_VARIANT_POS)

#define SCB_CPUID_ARCHITECTURE_POS         16U     /* SCB CPUID: ARCHITECTURE Position */
/* SCB CPUID: ARCHITECTURE Mask */
#define SCB_CPUID_ARCHITECTURE_MSK         (0xFUL << SCB_CPUID_ARCHITECTURE_POS)

#define SCB_CPUID_PARTNO_POS                4U     /* SCB CPUID: PARTNO Position */
/* SCB CPUID: PARTNO Mask */
#define SCB_CPUID_PARTNO_MSK               (0xFFFUL << SCB_CPUID_PARTNO_POS)

#define SCB_CPUID_REVISION_POS              0U     /* SCB CPUID: REVISION Position */
/* SCB CPUID: REVISION Mask */
#define SCB_CPUID_REVISION_MSK             (0xFUL)

/* SCB Interrupt Control State Register Definitions */
#define SCB_ICSR_NMIPENDSET_POS            31U     /* SCB ICSR: NMIPENDSET Position */
/* SCB ICSR: NMIPENDSET Mask */
#define SCB_ICSR_NMIPENDSET_MSK            (1UL << SCB_ICSR_NMIPENDSET_POS)

#define SCB_ICSR_PENDSVSET_POS             28U     /* SCB ICSR: PENDSVSET Position */
#define SCB_ICSR_PENDSVSET_MSK             (1UL << SCB_ICSR_PENDSVSET_POS)

#define SCB_ICSR_PENDSVCLR_POS             27U     /* SCB ICSR: PENDSVCLR Position */
/* SCB ICSR: PENDSVCLR Mask */
#define SCB_ICSR_PENDSVCLR_MSK             (1UL << SCB_ICSR_PENDSVCLR_POS)

#define SCB_ICSR_PENDSTSET_POS             26U     /* SCB ICSR: PENDSTSET Position */
/* SCB ICSR: PENDSTSET Mask */
#define SCB_ICSR_PENDSTSET_MSK             (1UL << SCB_ICSR_PENDSTSET_POS)

#define SCB_ICSR_PENDSTCLR_POS             25U     /* SCB ICSR: PENDSTCLR Position */
/* SCB ICSR: PENDSTCLR Mask */
#define SCB_ICSR_PENDSTCLR_MSK             (1UL << SCB_ICSR_PENDSTCLR_POS)

#define SCB_ICSR_ISRPREEMPT_POS            23U     /* SCB ICSR: ISRPREEMPT Position */
/* SCB ICSR: ISRPREEMPT Mask */
#define SCB_ICSR_ISRPREEMPT_MSK            (1UL << SCB_ICSR_ISRPREEMPT_POS)

#define SCB_ICSR_ISRPENDING_POS            22U     /* SCB ICSR: ISRPENDING Position */
/* SCB ICSR: ISRPENDING Mask */
#define SCB_ICSR_ISRPENDING_MSK            (1UL << SCB_ICSR_ISRPENDING_POS)

#define SCB_ICSR_VECTPENDING_POS           12U     /* SCB ICSR: VECTPENDING Position */
 /* SCB ICSR: VECTPENDING Mask */
#define SCB_ICSR_VECTPENDING_MSK           (0x1FFUL << SCB_ICSR_VECTPENDING_POS)

#define SCB_ICSR_RETTOBASE_POS             11U     /* SCB ICSR: RETTOBASE Position */
/* SCB ICSR: RETTOBASE Mask */
#define SCB_ICSR_RETTOBASE_MSK             (1UL << SCB_ICSR_RETTOBASE_POS)

#define SCB_ICSR_VECTACTIVE_POS             0U     /* SCB ICSR: VECTACTIVE Position */
/* SCB ICSR: VECTACTIVE Mask */
#define SCB_ICSR_VECTACTIVE_MSK            (0x1FFUL)

/* SCB Vector Table Offset Register Definitions */
#define SCB_VTOR_TBLOFF_POS                 7U     /* SCB VTOR: TBLOFF Position */
/* SCB VTOR: TBLOFF Mask */
#define SCB_VTOR_TBLOFF_MSK                (0x1FFFFFFUL << SCB_VTOR_TBLOFF_POS)

/* SCB Application Interrupt and Reset Control Register Definitions */
#define SCB_AIRCR_VECTKEY_POS              16U     /* SCB AIRCR: VECTKEY Position */
/* SCB AIRCR: VECTKEY Mask */
#define SCB_AIRCR_VECTKEY_MSK              (0xFFFFUL << SCB_AIRCR_VECTKEY_POS)

#define SCB_AIRCR_VECTKEYSTAT_POS          16U     /* SCB AIRCR: VECTKEYSTAT Position */
/* SCB AIRCR: VECTKEYSTAT Mask */
#define SCB_AIRCR_VECTKEYSTAT_MSK          (0xFFFFUL << SCB_AIRCR_VECTKEYSTAT_POS)

#define SCB_AIRCR_ENDIANESS_POS            15U     /* SCB AIRCR: ENDIANESS Position */
/* SCB AIRCR: ENDIANESS Mask */
#define SCB_AIRCR_ENDIANESS_MSK            (1UL << SCB_AIRCR_ENDIANESS_POS)

#define SCB_AIRCR_PRIGROUP_POS              8U     /* SCB AIRCR: PRIGROUP Position */
/* SCB AIRCR: PRIGROUP Mask */
#define SCB_AIRCR_PRIGROUP_MSK             (7UL << SCB_AIRCR_PRIGROUP_POS)

#define SCB_AIRCR_SYSRESETREQ_POS           2U     /* SCB AIRCR: SYSRESETREQ Position */
/* SCB AIRCR: SYSRESETREQ Mask */
#define SCB_AIRCR_SYSRESETREQ_MSK          (1UL << SCB_AIRCR_SYSRESETREQ_POS)

#define SCB_AIRCR_VECTCLRACTIVE_POS         1U     /* SCB AIRCR: VECTCLRACTIVE Position */
/* SCB AIRCR: VECTCLRACTIVE Mask */
#define SCB_AIRCR_VECTCLRACTIVE_MSK        (1UL << SCB_AIRCR_VECTCLRACTIVE_POS)

#define SCB_AIRCR_VECTRESET_POS             0U     /* SCB AIRCR: VECTRESET Position */
/* SCB AIRCR: VECTRESET Mask */
#define SCB_AIRCR_VECTRESET_MSK            (1UL)  /*<< SCB_AIRCR_VECTRESET_POS*/

/* SCB System Control Register Definitions */
#define SCB_SCR_SEVONPEND_POS               4U     /* SCB SCR: SEVONPEND Position */
/* SCB SCR: SEVONPEND Mask */
#define SCB_SCR_SEVONPEND_MSK              (1UL << SCB_SCR_SEVONPEND_POS)

#define SCB_SCR_SLEEPDEEP_POS               2U     /* SCB SCR: SLEEPDEEP Position */
/* SCB SCR: SLEEPDEEP Mask */
#define SCB_SCR_SLEEPDEEP_MSK              (1UL << SCB_SCR_SLEEPDEEP_POS)

#define SCB_SCR_SLEEPONEXIT_POS             1U     /* SCB SCR: SLEEPONEXIT Position */
/* SCB SCR: SLEEPONEXIT Mask */
#define SCB_SCR_SLEEPONEXIT_MSK            (1UL << SCB_SCR_SLEEPONEXIT_POS)

/* SCB Configuration Control Register Definitions */
/* SCB CCR: Branch prediction enable bit Position */
#define SCB_CCR_BP_POS                      18U
/* SCB CCR: Branch prediction enable bit Mask */
#define SCB_CCR_BP_MSK                     (1UL << SCB_CCR_BP_POS)

#define SCB_CCR_IC_POS                      17U /* SCB CCR: Instruction cache enable bit Position*/
/* SCB CCR: Instruction cache enable bit Mask */
#define SCB_CCR_IC_MSK                     (1UL << SCB_CCR_IC_POS)

#define SCB_CCR_DC_POS                      16U    /* SCB CCR: Cache enable bit Position */
/* SCB CCR: Cache enable bit Mask */
#define SCB_CCR_DC_MSK                     (1UL << SCB_CCR_DC_POS)

#define SCB_CCR_STKALIGN_POS                9U     /* SCB CCR: STKALIGN Position */
/* SCB CCR: STKALIGN Mask */
#define SCB_CCR_STKALIGN_MSK               (1UL << SCB_CCR_STKALIGN_POS)

#define SCB_CCR_BFHFNMIGN_POS               8U     /* SCB CCR: BFHFNMIGN Position */
/* SCB CCR: BFHFNMIGN Mask */
#define SCB_CCR_BFHFNMIGN_MSK              (1UL << SCB_CCR_BFHFNMIGN_POS)

#define SCB_CCR_DIV_0_TRP_POS               4U     /* SCB CCR: DIV_0_TRP Position */
/* SCB CCR: DIV_0_TRP Mask */
#define SCB_CCR_DIV_0_TRP_MSK              (1UL << SCB_CCR_DIV_0_TRP_POS)

#define SCB_CCR_UNALIGN_TRP_POS             3U     /* SCB CCR: UNALIGN_TRP Position */
/* SCB CCR: UNALIGN_TRP Mask */
#define SCB_CCR_UNALIGN_TRP_MSK            (1UL << SCB_CCR_UNALIGN_TRP_POS)

#define SCB_CCR_USERSETMPEND_POS            1U     /* SCB CCR: USERSETMPEND Position */
/* SCB CCR: USERSETMPEND Mask */
#define SCB_CCR_USERSETMPEND_MSK           (1UL << SCB_CCR_USERSETMPEND_POS)

#define SCB_CCR_NONBASETHRDENA_POS          0U     /* SCB CCR: NONBASETHRDENA Position */
/* SCB CCR: NONBASETHRDENA Mask */
#define SCB_CCR_NONBASETHRDENA_MSK         (1UL)

/* SCB System Handler Control and State Register Definitions */
#define SCB_SHCSR_USGFAULTENA_POS          18U     /* SCB SHCSR: USGFAULTENA Position */
/* SCB SHCSR: USGFAULTENA Mask */
#define SCB_SHCSR_USGFAULTENA_MSK          (1UL << SCB_SHCSR_USGFAULTENA_POS)

#define SCB_SHCSR_BUSFAULTENA_POS          17U     /* SCB SHCSR: BUSFAULTENA Position */
/* SCB SHCSR: BUSFAULTENA Mask */
#define SCB_SHCSR_BUSFAULTENA_MSK          (1UL << SCB_SHCSR_BUSFAULTENA_POS)

#define SCB_SHCSR_MEMFAULTENA_POS          16U     /* SCB SHCSR: MEMFAULTENA Position */
/* SCB SHCSR: MEMFAULTENA Mask */
#define SCB_SHCSR_MEMFAULTENA_MSK          (1UL << SCB_SHCSR_MEMFAULTENA_POS)

#define SCB_SHCSR_SVCALLPENDED_POS         15U     /* SCB SHCSR: SVCALLPENDED Position */
/* SCB SHCSR: SVCALLPENDED Mask */
#define SCB_SHCSR_SVCALLPENDED_MSK         (1UL << SCB_SHCSR_SVCALLPENDED_POS)

#define SCB_SHCSR_BUSFAULTPENDED_POS       14U     /* SCB SHCSR: BUSFAULTPENDED Position */
/* SCB SHCSR: BUSFAULTPENDED Mask */
#define SCB_SHCSR_BUSFAULTPENDED_MSK       (1UL << SCB_SHCSR_BUSFAULTPENDED_POS)

#define SCB_SHCSR_MEMFAULTPENDED_POS       13U     /* SCB SHCSR: MEMFAULTPENDED Position */
/* SCB SHCSR: MEMFAULTPENDED Mask */
#define SCB_SHCSR_MEMFAULTPENDED_MSK       (1UL << SCB_SHCSR_MEMFAULTPENDED_POS)

#define SCB_SHCSR_USGFAULTPENDED_POS       12U     /* SCB SHCSR: USGFAULTPENDED Position */
/* SCB SHCSR: USGFAULTPENDED Mask */
#define SCB_SHCSR_USGFAULTPENDED_MSK       (1UL << SCB_SHCSR_USGFAULTPENDED_POS)

#define SCB_SHCSR_SYSTICKACT_POS           11U     /* SCB SHCSR: SYSTICKACT Position */
/* SCB SHCSR: SYSTICKACT Mask */
#define SCB_SHCSR_SYSTICKACT_MSK           (1UL << SCB_SHCSR_SYSTICKACT_POS)

#define SCB_SHCSR_PENDSVACT_POS            10U     /* SCB SHCSR: PENDSVACT Position */
/* SCB SHCSR: PENDSVACT Mask */
#define SCB_SHCSR_PENDSVACT_MSK            (1UL << SCB_SHCSR_PENDSVACT_POS)

#define SCB_SHCSR_MONITORACT_POS            8U     /* SCB SHCSR: MONITORACT Position */
/* SCB SHCSR: MONITORACT Mask */
#define SCB_SHCSR_MONITORACT_MSK           (1UL << SCB_SHCSR_MONITORACT_POS)

#define SCB_SHCSR_SVCALLACT_POS             7U     /* SCB SHCSR: SVCALLACT Position */
/* SCB SHCSR: SVCALLACT Mask */
#define SCB_SHCSR_SVCALLACT_MSK            (1UL << SCB_SHCSR_SVCALLACT_POS)

#define SCB_SHCSR_USGFAULTACT_POS           3U     /* SCB SHCSR: USGFAULTACT Position */
/* SCB SHCSR: USGFAULTACT Mask */
#define SCB_SHCSR_USGFAULTACT_MSK          (1UL << SCB_SHCSR_USGFAULTACT_POS)

#define SCB_SHCSR_BUSFAULTACT_POS           1U     /* SCB SHCSR: BUSFAULTACT Position */
/* SCB SHCSR: BUSFAULTACT Mask */
#define SCB_SHCSR_BUSFAULTACT_MSK          (1UL << SCB_SHCSR_BUSFAULTACT_POS)

#define SCB_SHCSR_MEMFAULTACT_POS           0U     /* SCB SHCSR: MEMFAULTACT Position */
/* SCB SHCSR: MEMFAULTACT Mask */
#define SCB_SHCSR_MEMFAULTACT_MSK          (1UL)

/* SCB Configurable Fault Status Register Definitions */
/* SCB CFSR: Usage Fault Status Register Position */
#define SCB_CFSR_USGFAULTSR_POS            16U
/* SCB CFSR: Usage Fault Status Register Mask */
#define SCB_CFSR_USGFAULTSR_MSK            (0xFFFFUL << SCB_CFSR_USGFAULTSR_POS)

#define SCB_CFSR_BUSFAULTSR_POS             8U  /* SCB CFSR: Bus Fault Status Register Position */
/* SCB CFSR: Bus Fault Status Register Mask */
#define SCB_CFSR_BUSFAULTSR_MSK            (0xFFUL << SCB_CFSR_BUSFAULTSR_POS)

/* SCB CFSR: Memory Manage Fault Status Register Position */
#define SCB_CFSR_MEMFAULTSR_POS             0U
/* SCB CFSR: Memory Manage Fault Status Register Mask */
#define SCB_CFSR_MEMFAULTSR_MSK            (0xFFUL)

/* SCB Hard Fault Status Register Definitions */
#define SCB_HFSR_DEBUGEVT_POS              31U     /* SCB HFSR: DEBUGEVT Position */
/* SCB HFSR: DEBUGEVT Mask */
#define SCB_HFSR_DEBUGEVT_MSK              (1UL << SCB_HFSR_DEBUGEVT_POS)

#define SCB_HFSR_FORCED_POS                30U     /* SCB HFSR: FORCED Position */
/* SCB HFSR: FORCED Mask */
#define SCB_HFSR_FORCED_MSK                (1UL << SCB_HFSR_FORCED_POS)

#define SCB_HFSR_VECTTBL_POS                1U     /* SCB HFSR: VECTTBL Position */
/* SCB HFSR: VECTTBL Mask */
#define SCB_HFSR_VECTTBL_MSK               (1UL << SCB_HFSR_VECTTBL_POS)

/* SCB Debug Fault Status Register Definitions */
#define SCB_DFSR_EXTERNAL_POS               4U     /* SCB DFSR: EXTERNAL Position */
 /* SCB DFSR: EXTERNAL Mask */
#define SCB_DFSR_EXTERNAL_MSK              (1UL << SCB_DFSR_EXTERNAL_POS)

#define SCB_DFSR_VCATCH_POS                 3U     /* SCB DFSR: VCATCH Position */
/* SCB DFSR: VCATCH Mask */
#define SCB_DFSR_VCATCH_MSK                (1UL << SCB_DFSR_VCATCH_POS)

#define SCB_DFSR_DWTTRAP_POS                2U     /* SCB DFSR: DWTTRAP Position */
/* SCB DFSR: DWTTRAP Mask */
#define SCB_DFSR_DWTTRAP_MSK               (1UL << SCB_DFSR_DWTTRAP_POS)

#define SCB_DFSR_BKPT_POS                   1U     /* SCB DFSR: BKPT Position */
/* SCB DFSR: BKPT Mask */
#define SCB_DFSR_BKPT_MSK                  (1UL << SCB_DFSR_BKPT_POS)

#define SCB_DFSR_HALTED_POS                 0U     /* SCB DFSR: HALTED Position */
/* SCB DFSR: HALTED Mask */
#define SCB_DFSR_HALTED_MSK                (1UL)

/* SCB Cache Level ID Register Definitions */
#define SCB_CLIDR_LOUU_POS                 27U     /* SCB CLIDR: LoUU Position */
/* SCB CLIDR: LoUU Mask */
#define SCB_CLIDR_LOUU_MSK                 (7UL << SCB_CLIDR_LOUU_POS)

#define SCB_CLIDR_LOC_POS                  24U     /* SCB CLIDR: LoC Position */
/* SCB CLIDR: LoC Mask */
#define SCB_CLIDR_LOC_MSK                  (7UL << SCB_CLIDR_LOC_POS)

/* SCB Cache Type Register Definitions */
#define SCB_CTR_FORMAT_POS                 29U     /* SCB CTR: Format Position */
/* SCB CTR: Format Mask */
#define SCB_CTR_FORMAT_MSK                 (7UL << SCB_CTR_FORMAT_POS)

#define SCB_CTR_CWG_POS                    24U     /* SCB CTR: CWG Position */
/* SCB CTR: CWG Mask */
#define SCB_CTR_CWG_MSK                    (0xFUL << SCB_CTR_CWG_POS)

#define SCB_CTR_ERG_POS                    20U     /* SCB CTR: ERG Position */
/* SCB CTR: ERG Mask */
#define SCB_CTR_ERG_MSK                    (0xFUL << SCB_CTR_ERG_POS)

#define SCB_CTR_DMINLINE_POS               16U     /* SCB CTR: DminLine Position */
/* SCB CTR: DminLine Mask */
#define SCB_CTR_DMINLINE_MSK               (0xFUL << SCB_CTR_DMINLINE_POS)

#define SCB_CTR_IMINLINE_POS                0U     /* SCB CTR: ImInLine Position */
/* SCB CTR: ImInLine Mask */
#define SCB_CTR_IMINLINE_MSK               (0xFUL) /*<< SCB_CTR_IMINLINE_POS*/

/* SCB Cache Size ID Register Definitions */
#define SCB_CCSIDR_WT_POS                  31U     /* SCB CCSIDR: WT Position */
/* SCB CCSIDR: WT Mask */
#define SCB_CCSIDR_WT_MSK                  (1UL << SCB_CCSIDR_WT_POS)

#define SCB_CCSIDR_WB_POS                  30U     /* SCB CCSIDR: WB Position */
/* SCB CCSIDR: WB Mask */
#define SCB_CCSIDR_WB_MSK                  (1UL << SCB_CCSIDR_WB_POS)

#define SCB_CCSIDR_RA_POS                  29U     /* SCB CCSIDR: RA Position */
/* SCB CCSIDR: RA Mask */
#define SCB_CCSIDR_RA_MSK                  (1UL << SCB_CCSIDR_RA_POS)

#define SCB_CCSIDR_WA_POS                  28U     /* SCB CCSIDR: WA Position */
/* SCB CCSIDR: WA Mask */
#define SCB_CCSIDR_WA_MSK                  (1UL << SCB_CCSIDR_WA_POS)

#define SCB_CCSIDR_NUMSETS_POS             13U     /* SCB CCSIDR: NumSets Position */
/* SCB CCSIDR: NumSets Mask */
#define SCB_CCSIDR_NUMSETS_MSK             (0x7FFFUL << SCB_CCSIDR_NUMSETS_POS)

#define SCB_CCSIDR_ASSOCIATIVITY_POS        3U     /* SCB CCSIDR: Associativity Position */
/* SCB CCSIDR: Associativity Mask */
#define SCB_CCSIDR_ASSOCIATIVITY_MSK       (0x3FFUL << SCB_CCSIDR_ASSOCIATIVITY_POS)

#define SCB_CCSIDR_LINESIZE_POS             0U     /* SCB CCSIDR: LineSize Position */
 /* SCB CCSIDR: LineSize Mask */
#define SCB_CCSIDR_LINESIZE_MSK            (7UL) /*<< SCB_CCSIDR_LINESIZE_POS*/

/* SCB Cache Size Selection Register Definitions */
#define SCB_CSSELR_LEVEL_POS                1U     /* SCB CSSELR: Level Position */
/* SCB CSSELR: Level Mask */
#define SCB_CSSELR_LEVEL_MSK               (7UL << SCB_CSSELR_LEVEL_POS)

#define SCB_CSSELR_IND_POS                  0U     /* SCB CSSELR: InD Position */
/* SCB CSSELR: InD Mask */
#define SCB_CSSELR_IND_MSK                 (1UL) /*<< SCB_CSSELR_IND_POS*/

/* SCB Software Triggered Interrupt Register Definitions */
#define SCB_STIR_INTID_POS                  0U     /* SCB STIR: INTID Position */
/* SCB STIR: INTID Mask */
#define SCB_STIR_INTID_MSK                 (0x1FFUL) /*<< SCB_STIR_INTID_POS*/

/* SCB D-Cache Invalidate by Set-way Register Definitions */
#define SCB_DCISW_WAY_POS                  30U     /* SCB DCISW: Way Position */
/* SCB DCISW: Way Mask */
#define SCB_DCISW_WAY_MSK                  (3UL << SCB_DCISW_WAY_POS)

#define SCB_DCISW_SET_POS                   5U     /* SCB DCISW: Set Position */
 /* SCB DCISW: Set Mask */
#define SCB_DCISW_SET_MSK                  (0x1FFUL << SCB_DCISW_SET_POS)

/* SCB D-Cache Clean by Set-way Register Definitions */
#define SCB_DCCSW_WAY_POS                  30U     /* SCB DCCSW: Way Position */
#define SCB_DCCSW_WAY_MSK                  (3UL << SCB_DCCSW_WAY_POS)   /* SCB DCCSW: Way Mask */

#define SCB_DCCSW_SET_POS                   5U     /* SCB DCCSW: Set Position */
#define SCB_DCCSW_SET_MSK                  (0x1FFUL << SCB_DCCSW_SET_POS) /* SCB DCCSW: Set Mask */

/* SCB D-Cache Clean and Invalidate by Set-way Register Definitions */
#define SCB_DCCISW_WAY_POS                 30U     /* SCB DCCISW: Way Position */
#define SCB_DCCISW_WAY_MSK                 (3UL << SCB_DCCISW_WAY_POS)   /* SCB DCCISW: Way Mask */

#define SCB_DCCISW_SET_POS                  5U     /* SCB DCCISW: Set Position */
/* SCB DCCISW: Set Mask */
#define SCB_DCCISW_SET_MSK                 (0x1FFUL << SCB_DCCISW_SET_POS)

/* Instruction Tightly-Coupled Memory Control Register Definitions */
#define SCB_ITCMCR_SZ_POS                   3U     /* SCB ITCMCR: SZ Position */
#define SCB_ITCMCR_SZ_MSK                  (0xFUL << SCB_ITCMCR_SZ_POS)   /* SCB ITCMCR: SZ Mask */

#define SCB_ITCMCR_RETEN_POS                2U     /* SCB ITCMCR: RETEN Position */
#define SCB_ITCMCR_RETEN_MSK               (1UL << SCB_ITCMCR_RETEN_POS) /* SCB ITCMCR:RETEN Mask*/

#define SCB_ITCMCR_RMW_POS                  1U     /* SCB ITCMCR: RMW Position */
#define SCB_ITCMCR_RMW_MSK                 (1UL << SCB_ITCMCR_RMW_POS)  /* SCB ITCMCR:RMW Mask*/

#define SCB_ITCMCR_EN_POS                   0U     /* SCB ITCMCR: EN Position */
#define SCB_ITCMCR_EN_MSK                  (1UL)  /* SCB ITCMCR: EN Mask*/

/* Data Tightly-Coupled Memory Control Register Definitions */
#define SCB_DTCMCR_SZ_POS                   3U     /* SCB DTCMCR: SZ Position */
#define SCB_DTCMCR_SZ_MSK                  (0xFUL << SCB_DTCMCR_SZ_POS) /* SCB DTCMCR: SZ Mask*/

#define SCB_DTCMCR_RETEN_POS                2U     /* SCB DTCMCR: RETEN Position */
#define SCB_DTCMCR_RETEN_MSK               (1UL << SCB_DTCMCR_RETEN_POS) /* SCB DTCMCR:RETEN Mask*/

#define SCB_DTCMCR_RMW_POS                  1U     /* SCB DTCMCR: RMW Position */
#define SCB_DTCMCR_RMW_MSK                 (1UL << SCB_DTCMCR_RMW_POS)     /* SCB DTCMCR:RMW Mask*/

#define SCB_DTCMCR_EN_POS                   0U     /* SCB DTCMCR: EN Position */
#define SCB_DTCMCR_EN_MSK                  (1UL)  /* SCB DTCMCR: EN Mask*/

/* AHBP Control Register Definitions */
#define SCB_AHBPCR_SZ_POS                   1U     /* SCB AHBPCR: SZ Position */
#define SCB_AHBPCR_SZ_MSK                  (7UL << SCB_AHBPCR_SZ_POS)      /* SCB AHBPCR: SZ Mask*/

#define SCB_AHBPCR_EN_POS                   0U     /* SCB AHBPCR: EN Position */
#define SCB_AHBPCR_EN_MSK                  (1UL)  /* SCB AHBPCR: EN Mask*/

/* L1 Cache Control Register Definitions */
#define SCB_CACR_FORCEWT_POS                2U     /* SCB CACR: FORCEWT Position */
#define SCB_CACR_FORCEWT_MSK               (1UL << SCB_CACR_FORCEWT_POS)  /* SCB CACR:FORCEWT Mask*/

#define SCB_CACR_ECCEN_POS                  1U     /* SCB CACR: ECCEN Position */
#define SCB_CACR_ECCEN_MSK                 (1UL << SCB_CACR_ECCEN_POS)     /* SCB CACR:ECCEN Mask*/

#define SCB_CACR_SIWT_POS                   0U     /* SCB CACR: SIWT Position */
#define SCB_CACR_SIWT_MSK                  (1UL)  /* SCB CACR:SIWT Mask*/

/* AHBS Control Register Definitions */
#define SCB_AHBSCR_INITCOUNT_POS           11U     /* SCB AHBSCR: INITCOUNT Position */
/* SCB AHBSCR: INITCOUNT Mask */
#define SCB_AHBSCR_INITCOUNT_MSK           (0x1FUL << SCB_AHBPCR_INITCOUNT_POS)

#define SCB_AHBSCR_TPRI_POS                 2U     /* SCB AHBSCR: TPRI Position */
/* SCB AHBSCR: TPRI Mask */
#define SCB_AHBSCR_TPRI_MSK                (0x1FFUL << SCB_AHBPCR_TPRI_POS)

#define SCB_AHBSCR_CTL_POS                  0U     /* SCB AHBSCR: CTL Position*/
/* SCB AHBSCR: CTL Mask */
#define SCB_AHBSCR_CTL_MSK                 (3UL)

/* Auxiliary Bus Fault Status Register Definitions */
#define SCB_ABFSR_AXIMTYPE_POS              8U     /* SCB ABFSR: AXIMTYPE Position*/
/* SCB ABFSR: AXIMTYPE Mask */
#define SCB_ABFSR_AXIMTYPE_MSK             (3UL << SCB_ABFSR_AXIMTYPE_POS)

#define SCB_ABFSR_EPPB_POS                  4U     /* SCB ABFSR: EPPB Position*/
#define SCB_ABFSR_EPPB_MSK                 (1UL << SCB_ABFSR_EPPB_POS)  /* SCB ABFSR: EPPB Mask */

#define SCB_ABFSR_AXIM_POS                  3U      /*SCB ABFSR: AXIM Position*/
#define SCB_ABFSR_AXIM_MSK                 (1UL << SCB_ABFSR_AXIM_POS)  /* SCB ABFSR: AXIM Mask */

#define SCB_ABFSR_AHBP_POS                  2U      /*SCB ABFSR: AHBP Position*/
#define SCB_ABFSR_AHBP_MSK                 (1UL << SCB_ABFSR_AHBP_POS)  /* SCB ABFSR: AHBP Mask */

#define SCB_ABFSR_DTCM_POS                  1U      /*SCB ABFSR: DTCM Position*/
#define SCB_ABFSR_DTCM_MSK                 (1UL << SCB_ABFSR_DTCM_POS)  /* SCB ABFSR: DTCM Mask */

#define SCB_ABFSR_ITCM_POS                  0U      /*SCB ABFSR: ITCM Position*/
#define SCB_ABFSR_ITCM_MSK                 (1UL ) /* SCB ABFSR:ITCM Mask*/

/*
 * \ingroup  CMSIS_core_register
 * \defgroup CMSIS_SCnSCB System Controls not in SCB (SCnSCB)
 * \brief    Type definitions for the System Control and ID Register not in the SCB
 */

/* brief  Structure type to access the System Control and ID Register not in the SCB. */
typedef struct
{
        T_UINT32 RESERVED0[1U];
  __IM  T_UINT32 ICTR;    /* Offset: 0x004 (R/ )  Interrupt Controller Type Register */
  __IOM T_UINT32 ACTLR;   /* Offset: 0x008 (R/W)  Auxiliary Control Register */
} T_SCNSCB;

/* Interrupt Controller Type Register Definitions */
#define SCNSCB_ICTR_INTLINESNUM_POS         0U      /* ICTR: INTLINESNUM Position */
/* ICTR: INTLINESNUM Mask */
#define SCNSCB_ICTR_INTLINESNUM_MSK        (0xFUL)

/* Auxiliary Control Register Definitions */
#define SCNSCB_ACTLR_DISITMATBFLUSH_POS    12U      /* ACTLR: DISITMATBFLUSH Position */

/* ACTLR: DISITMATBFLUSH Mask */
#define SCNSCB_ACTLR_DISITMATBFLUSH_MSK    (1UL << SCNSCB_ACTLR_DISITMATBFLUSH_POS)

#define SCNSCB_ACTLR_DISRAMODE_POS         11U      /* ACTLR: DISRAMODE Position */
/* ACTLR: DISRAMODE Mask */
#define SCNSCB_ACTLR_DISRAMODE_MSK         (1UL << SCNSCB_ACTLR_DISRAMODE_POS)

#define SCNSCB_ACTLR_FPEXCODIS_POS         10U      /* ACTLR: FPEXCODIS Position */
/* ACTLR: FPEXCODIS Mask */
#define SCNSCB_ACTLR_FPEXCODIS_MSK         (1UL << SCNSCB_ACTLR_FPEXCODIS_POS)

#define SCNSCB_ACTLR_DISFOLD_POS            2U      /* ACTLR: DISFOLD Position */
/* ACTLR: DISFOLD Mask */
#define SCNSCB_ACTLR_DISFOLD_MSK           (1UL << SCNSCB_ACTLR_DISFOLD_POS)

#define SCNSCB_ACTLR_DISMCYCINT_POS         0U      /* ACTLR: DISMCYCINT Position */
/* ACTLR: DISMCYCINT Mask */
#define SCNSCB_ACTLR_DISMCYCINT_MSK        (1UL)

/*
 * \ingroup  CMSIS_core_register
 * \defgroup CMSIS_SysTick     System Tick Timer (SysTick)
 * \brief    Type definitions for the System Timer Registers.
 */

/* brief  Structure type to access the System Timer (SysTick). */
typedef struct
{
  __IOM T_UINT32 CTRL;    /* Offset: 0x000 (R/W)  SysTick Control and Status Register */
  __IOM T_UINT32 LOAD;    /* Offset: 0x004 (R/W)  SysTick Reload Value Register */
  __IOM T_UINT32 VAL;     /* Offset: 0x008 (R/W)  SysTick Current Value Register */
  __IM  T_UINT32 CALIB;   /* Offset: 0x00C (R/ )  SysTick Calibration Register */
} T_SYSTICK;

/* SysTick Control / Status Register Definitions */
#define SYSTICK_CTRL_COUNTFLAG_POS         16U      /*SysTick CTRL: COUNTFLAG Position */
/* SysTick CTRL: COUNTFLAG Mask */
#define SYSTICK_CTRL_COUNTFLAG_MSK         (1UL << SYSTICK_CTRL_COUNTFLAG_POS)

#define SYSTICK_CTRL_CLKSOURCE_POS          2U      /*SysTick CTRL: CLKSOURCE Position */
/* SysTick CTRL: CLKSOURCE Mask */
#define SYSTICK_CTRL_CLKSOURCE_MSK         (1UL << SYSTICK_CTRL_CLKSOURCE_POS)

#define SYSTICK_CTRL_TICKINT_POS            1U      /*SysTick CTRL: TICKINT Position */
/* SysTick CTRL: TICKINT Mask */
#define SYSTICK_CTRL_TICKINT_MSK           (1UL << SYSTICK_CTRL_TICKINT_POS)

#define SYSTICK_CTRL_ENABLE_POS             0U      /*SysTick CTRL: ENABLE Position */
/* SysTick CTRL: ENABLE Mask */
#define SYSTICK_CTRL_ENABLE_MSK            (1UL)

/* SysTick Reload Register Definitions */
#define SYSTICK_LOAD_RELOAD_POS             0U      /*SysTick LOAD: RELOAD Position */
/* SysTick LOAD: RELOAD Mask */
#define SYSTICK_LOAD_RELOAD_MSK            (0xFFFFFFUL)

/* SysTick Current Register Definitions */
#define SYSTICK_VAL_CURRENT_POS             0U      /*SysTick VAL: CURRENT Position */
/* SysTick VAL: CURRENT Mask */
#define SYSTICK_VAL_CURRENT_MSK            (0xFFFFFFUL)

/* SysTick Calibration Register Definitions */
#define SYSTICK_CALIB_NOREF_POS            31U      /*SysTick CALIB: NOREF Position */
/* SysTick CALIB: NOREF Mask */
#define SYSTICK_CALIB_NOREF_MSK            (1UL << SYSTICK_CALIB_NOREF_POS)

#define SYSTICK_CALIB_SKEW_POS             30U      /*SysTick CALIB: SKEW Position */
/* SysTick CALIB: SKEW Mask */
#define SYSTICK_CALIB_SKEW_MSK             (1UL << SYSTICK_CALIB_SKEW_POS)

#define SYSTICK_CALIB_TENMS_POS             0U      /*SysTick CALIB: TENMS Position */
/* SysTick CALIB: TENMS Mask */
#define SYSTICK_CALIB_TENMS_MSK            (0xFFFFFFUL)

/*
 * \ingroup  CMSIS_core_register
 * \defgroup CMSIS_ITM     Instrumentation Trace Macrocell (ITM)
 * \brief    Type definitions for the Instrumentation Trace Macrocell (ITM)
 */

/* brief  Structure type to access the Instrumentation Trace Macrocell Register (ITM). */
typedef struct
{
  __OM  union
  {
    __OM  T_UINT8    u8;  /* Offset: 0x000 ( /W)  ITM Stimulus Port 8-bit */
    __OM  T_UINT16   u16; /* Offset: 0x000 ( /W)  ITM Stimulus Port 16-bit */
    __OM  T_UINT32   u32; /* Offset: 0x000 ( /W)  ITM Stimulus Port 32-bit */
  }  PORT [32U];          /* Offset: 0x000 ( /W)  ITM Stimulus Port Registers */
        T_UINT32 RESERVED0[864U];
  __IOM T_UINT32 TER;     /* Offset: 0xE00 (R/W)  ITM Trace Enable Register */
        T_UINT32 RESERVED1[15U];
  __IOM T_UINT32 TPR;     /* Offset: 0xE40 (R/W)  ITM Trace Privilege Register */
        T_UINT32 RESERVED2[15U];
  __IOM T_UINT32 TCR;     /* Offset: 0xE80 (R/W)  ITM Trace Control Register */
        T_UINT32 RESERVED3[29U];
  __OM  T_UINT32 IWR;     /* Offset: 0xEF8 ( /W)  ITM Integration Write Register */
  __IM  T_UINT32 IRR;     /* Offset: 0xEFC (R/ )  ITM Integration Read Register */
  __IOM T_UINT32 IMCR;    /* Offset: 0xF00 (R/W)  ITM Integration Mode Control Register */
        T_UINT32 RESERVED4[43U];
  __OM  T_UINT32 LAR;     /* Offset: 0xFB0 ( /W)  ITM Lock Access Register */
  __IM  T_UINT32 LSR;     /* Offset: 0xFB4 (R/ )  ITM Lock Status Register */
        T_UINT32 RESERVED5[6U];
  __IM  T_UINT32 PID4;    /* Offset: 0xFD0 (R/ )  ITM Peripheral Identification Register #4 */
  __IM  T_UINT32 PID5;    /* Offset: 0xFD4 (R/ )  ITM Peripheral Identification Register #5 */
  __IM  T_UINT32 PID6;    /* Offset: 0xFD8 (R/ )  ITM Peripheral Identification Register #6 */
  __IM  T_UINT32 PID7;    /* Offset: 0xFDC (R/ )  ITM Peripheral Identification Register #7 */
  __IM  T_UINT32 PID0;    /* Offset: 0xFE0 (R/ )  ITM Peripheral Identification Register #0 */
  __IM  T_UINT32 PID1;    /* Offset: 0xFE4 (R/ )  ITM Peripheral Identification Register #1 */
  __IM  T_UINT32 PID2;    /* Offset: 0xFE8 (R/ )  ITM Peripheral Identification Register #2 */
  __IM  T_UINT32 PID3;    /* Offset: 0xFEC (R/ )  ITM Peripheral Identification Register #3 */
  __IM  T_UINT32 CID0;    /* Offset: 0xFF0 (R/ )  ITM Component  Identification Register #0 */
  __IM  T_UINT32 CID1;    /* Offset: 0xFF4 (R/ )  ITM Component  Identification Register #1 */
  __IM  T_UINT32 CID2;    /* Offset: 0xFF8 (R/ )  ITM Component  Identification Register #2 */
  __IM  T_UINT32 CID3;    /* Offset: 0xFFC (R/ )  ITM Component  Identification Register #3 */
} T_ITM;

/* ITM Trace Privilege Register Definitions */
#define ITM_TPR_PRIVMASK_POS                0U      /*ITM TPR: PRIVMASK Position */
/* ITM TPR: PRIVMASK Mask */
#define ITM_TPR_PRIVMASK_MSK               (0xFUL)

/* ITM Trace Control Register Definitions */
#define ITM_TCR_BUSY_POS                   23U      /*ITM TCR: BUSY Position */
#define ITM_TCR_BUSY_MSK                   (1UL << ITM_TCR_BUSY_POS)       /* ITM TCR: BUSY Mask */

#define ITM_TCR_TRACEBUSID_POS             16U      /*ITM TCR: ATBID Position */
/* ITM TCR: ATBID Mask */
#define ITM_TCR_TRACEBUSID_MSK             (0x7FUL << ITM_TCR_TRACEBUSID_POS)

#define ITM_TCR_GTSFREQ_POS                10U  /*ITM TCR: Global timestamp frequency Position */
/* ITM TCR: Global timestamp frequency Mask */
#define ITM_TCR_GTSFREQ_MSK                (3UL << ITM_TCR_GTSFREQ_POS)

#define ITM_TCR_TSPRESCALE_POS              8U      /*ITM TCR: TSPrescale Position */
/* ITM TCR: TSPrescale Mask */
#define ITM_TCR_TSPRESCALE_MSK             (3UL << ITM_TCR_TSPRESCALE_POS)

#define ITM_TCR_SWOENA_POS                  4U      /*ITM TCR: SWOENA Position */
#define ITM_TCR_SWOENA_MSK                 (1UL << ITM_TCR_SWOENA_POS)   /* ITM TCR: SWOENA Mask */

#define ITM_TCR_DWTENA_POS                  3U      /*ITM TCR: DWTENA Position */
#define ITM_TCR_DWTENA_MSK                 (1UL << ITM_TCR_DWTENA_POS)   /* ITM TCR: DWTENA Mask */

#define ITM_TCR_SYNCENA_POS                 2U      /*ITM TCR: SYNCENA Position */
#define ITM_TCR_SYNCENA_MSK                (1UL << ITM_TCR_SYNCENA_POS)  /* ITM TCR: SYNCENA Mask*/

#define ITM_TCR_TSENA_POS                   1U      /*ITM TCR: TSENA Position */
#define ITM_TCR_TSENA_MSK                  (1UL << ITM_TCR_TSENA_POS)     /* ITM TCR: TSENA Mask */

#define ITM_TCR_ITMENA_POS                  0U      /*ITM TCR: ITM Enable bit Position */
/* ITM TCR: ITM Enable bit Mask */
#define ITM_TCR_ITMENA_MSK                 (1UL)

/* ITM Integration Write Register Definitions */
#define ITM_IWR_ATVALIDM_POS                0U      /*ITM IWR: ATVALIDM Position */
/* ITM IWR: ATVALIDM Mask */
#define ITM_IWR_ATVALIDM_MSK               (1UL)

/* ITM Integration Read Register Definitions */
#define ITM_IRR_ATREADYM_POS                0U      /*ITM IRR: ATREADYM Position */
/* ITM IRR: ATREADYM Mask */
#define ITM_IRR_ATREADYM_MSK               (1UL)

/* ITM Integration Mode Control Register Definitions */
#define ITM_IMCR_INTEGRATION_POS            0U      /*ITM IMCR: INTEGRATION Position */
/* ITM IMCR: INTEGRATION Mask */
#define ITM_IMCR_INTEGRATION_MSK           (1UL)

/* ITM Lock Status Register Definitions */
#define ITM_LSR_BYTEACC_POS                 2U      /*ITM LSR: ByteAcc Position */
#define ITM_LSR_BYTEACC_MSK                (1UL << ITM_LSR_BYTEACC_POS) /* ITM LSR: ByteAcc Mask */

#define ITM_LSR_ACCESS_POS                  1U      /*ITM LSR: Access Position */
#define ITM_LSR_ACCESS_MSK                 (1UL << ITM_LSR_ACCESS_POS)  /* ITM LSR: Access Mask */

#define ITM_LSR_PRESENT_POS                 0U      /*ITM LSR: Present Position */
/* ITM LSR: Present Mask */
#define ITM_LSR_PRESENT_MSK                (1UL)

/*
 * \ingroup  CMSIS_core_register
 * \defgroup CMSIS_DWT     Data Watchpoint and Trace (DWT)
 * \brief    Type definitions for the Data Watchpoint and Trace (DWT)
 */

/* brief  Structure type to access the Data Watchpoint and Trace Register (DWT). */
typedef struct
{
  __IOM T_UINT32 CTRL;     /* Offset: 0x000 (R/W)  Control Register */
  __IOM T_UINT32 CYCCNT;   /* Offset: 0x004 (R/W)  Cycle Count Register */
  __IOM T_UINT32 CPICNT;   /* Offset: 0x008 (R/W)  CPI Count Register */
  __IOM T_UINT32 EXCCNT;   /* Offset: 0x00C (R/W)  Exception Overhead Count Register */
  __IOM T_UINT32 SLEEPCNT; /* Offset: 0x010 (R/W)  Sleep Count Register */
  __IOM T_UINT32 LSUCNT;   /* Offset: 0x014 (R/W)  LSU Count Register */
  __IOM T_UINT32 FOLDCNT;  /* Offset: 0x018 (R/W)  Folded-instruction Count Register */
  __IM  T_UINT32 PCSR;     /* Offset: 0x01C (R/ )  Program Counter Sample Register */
  __IOM T_UINT32 COMP0;    /* Offset: 0x020 (R/W)  Comparator Register 0 */
  __IOM T_UINT32 MASK0;    /* Offset: 0x024 (R/W)  Mask Register 0 */
  __IOM T_UINT32 FUNCTION0; /* Offset: 0x028 (R/W)  Function Register 0 */
        T_UINT32 RESERVED0[1U];
  __IOM T_UINT32 COMP1;    /* Offset: 0x030 (R/W)  Comparator Register 1 */
  __IOM T_UINT32 MASK1;    /* Offset: 0x034 (R/W)  Mask Register 1 */
  __IOM T_UINT32 FUNCTION1; /* Offset: 0x038 (R/W)  Function Register 1 */
        T_UINT32 RESERVED1[1U];
  __IOM T_UINT32 COMP2;    /* Offset: 0x040 (R/W)  Comparator Register 2 */
  __IOM T_UINT32 MASK2;    /* Offset: 0x044 (R/W)  Mask Register 2 */
  __IOM T_UINT32 FUNCTION2; /* Offset: 0x048 (R/W)  Function Register 2 */
        T_UINT32 RESERVED2[1U];
  __IOM T_UINT32 COMP3;     /* Offset: 0x050 (R/W)  Comparator Register 3 */
  __IOM T_UINT32 MASK3;     /* Offset: 0x054 (R/W)  Mask Register 3 */
  __IOM T_UINT32 FUNCTION3; /* Offset: 0x058 (R/W)  Function Register 3 */
        T_UINT32 RESERVED3[981U];
  __OM  T_UINT32 LAR;     /* Offset: 0xFB0 (  W)  Lock Access Register */
  __IM  T_UINT32 LSR;     /* Offset: 0xFB4 (R  )  Lock Status Register */
} T_DWT;

/* DWT Control Register Definitions */
#define DWT_CTRL_NUMCOMP_POS               28U      /* DWT CTRL: NUMCOMP Position */
/* DWT CTRL: NUMCOMP Mask */
#define DWT_CTRL_NUMCOMP_MSK               (0xFUL << DWT_CTRL_NUMCOMP_POS)

#define DWT_CTRL_NOTRCPKT_POS              27U      /* DWT CTRL: NOTRCPKT Position */
/* DWT CTRL: NOTRCPKT Mask */
#define DWT_CTRL_NOTRCPKT_MSK              (0x1UL << DWT_CTRL_NOTRCPKT_POS)

#define DWT_CTRL_NOEXTTRIG_POS             26U      /* DWT CTRL: NOEXTTRIG Position */
/* DWT CTRL: NOEXTTRIG Mask */
#define DWT_CTRL_NOEXTTRIG_MSK             (0x1UL << DWT_CTRL_NOEXTTRIG_POS)

#define DWT_CTRL_NOCYCCNT_POS              25U      /* DWT CTRL: NOCYCCNT Position */
/* DWT CTRL: NOCYCCNT Mask */
#define DWT_CTRL_NOCYCCNT_MSK              (0x1UL << DWT_CTRL_NOCYCCNT_POS)

#define DWT_CTRL_NOPRFCNT_POS              24U      /* DWT CTRL: NOPRFCNT Position */
/* DWT CTRL: NOPRFCNT Mask */
#define DWT_CTRL_NOPRFCNT_MSK              (0x1UL << DWT_CTRL_NOPRFCNT_POS)

#define DWT_CTRL_CYCEVTENA_POS             22U      /* DWT CTRL: CYCEVTENA Position */
/* DWT CTRL: CYCEVTENA Mask */
#define DWT_CTRL_CYCEVTENA_MSK             (0x1UL << DWT_CTRL_CYCEVTENA_POS)

#define DWT_CTRL_FOLDEVTENA_POS            21U      /* DWT CTRL: FOLDEVTENA Position */
/* DWT CTRL: FOLDEVTENA Mask */
#define DWT_CTRL_FOLDEVTENA_MSK            (0x1UL << DWT_CTRL_FOLDEVTENA_POS)

#define DWT_CTRL_LSUEVTENA_POS             20U      /* DWT CTRL: LSUEVTENA Position */
/* DWT CTRL: LSUEVTENA Mask */
#define DWT_CTRL_LSUEVTENA_MSK             (0x1UL << DWT_CTRL_LSUEVTENA_POS)

#define DWT_CTRL_SLEEPEVTENA_POS           19U      /* DWT CTRL: SLEEPEVTENA Position */
/* DWT CTRL: SLEEPEVTENA Mask */
#define DWT_CTRL_SLEEPEVTENA_MSK           (0x1UL << DWT_CTRL_SLEEPEVTENA_POS)

#define DWT_CTRL_EXCEVTENA_POS             18U      /* DWT CTRL: EXCEVTENA Position */
/* DWT CTRL: EXCEVTENA Mask */
#define DWT_CTRL_EXCEVTENA_MSK             (0x1UL << DWT_CTRL_EXCEVTENA_POS)

#define DWT_CTRL_CPIEVTENA_POS             17U      /* DWT CTRL: CPIEVTENA Position */
/* DWT CTRL: CPIEVTENA Mask */
#define DWT_CTRL_CPIEVTENA_MSK             (0x1UL << DWT_CTRL_CPIEVTENA_POS)

#define DWT_CTRL_EXCTRCENA_POS             16U      /* DWT CTRL: EXCTRCENA Position */
/* DWT CTRL: EXCTRCENA Mask */
#define DWT_CTRL_EXCTRCENA_MSK             (0x1UL << DWT_CTRL_EXCTRCENA_POS)

#define DWT_CTRL_PCSAMPLENA_POS            12U      /* DWT CTRL: PCSAMPLENA Position */
/* DWT CTRL: PCSAMPLENA Mask */
#define DWT_CTRL_PCSAMPLENA_MSK            (0x1UL << DWT_CTRL_PCSAMPLENA_POS)

#define DWT_CTRL_SYNCTAP_POS               10U      /* DWT CTRL: SYNCTAP Position */
/* DWT CTRL: SYNCTAP Mask */
#define DWT_CTRL_SYNCTAP_MSK               (0x3UL << DWT_CTRL_SYNCTAP_POS)

#define DWT_CTRL_CYCTAP_POS                 9U      /* DWT CTRL: CYCTAP Position */
#define DWT_CTRL_CYCTAP_MSK                (0x1UL << DWT_CTRL_CYCTAP_POS) /* DWT CTRL:CYCTAP Mask*/

#define DWT_CTRL_POSTINIT_POS               5U      /* DWT CTRL: POSTINIT Position */
/* DWT CTRL: POSTINIT Mask */
#define DWT_CTRL_POSTINIT_MSK              (0xFUL << DWT_CTRL_POSTINIT_POS)

#define DWT_CTRL_POSTPRESET_POS             1U      /* DWT CTRL: POSTPRESET Position */
/* DWT CTRL: POSTPRESET Mask */
#define DWT_CTRL_POSTPRESET_MSK            (0xFUL << DWT_CTRL_POSTPRESET_POS)

#define DWT_CTRL_CYCCNTENA_POS              0U      /* DWT CTRL: CYCCNTENA Position */
/* DWT CTRL: CYCCNTENA Mask */
#define DWT_CTRL_CYCCNTENA_MSK             (0x1UL)

/* DWT CPI Count Register Definitions */
#define DWT_CPICNT_CPICNT_POS               0U      /* DWT CPICNT: CPICNT Position */
/* DWT CPICNT: CPICNT Mask */
#define DWT_CPICNT_CPICNT_MSK              (0xFFUL)

/* DWT Exception Overhead Count Register Definitions */
#define DWT_EXCCNT_EXCCNT_POS               0U      /* DWT EXCCNT: EXCCNT Position */
/* DWT EXCCNT: EXCCNT Mask */
#define DWT_EXCCNT_EXCCNT_MSK              (0xFFUL)

/* DWT Sleep Count Register Definitions */
#define DWT_SLEEPCNT_SLEEPCNT_POS           0U      /* DWT SLEEPCNT: SLEEPCNT Position */
/* DWT SLEEPCNT: SLEEPCNT Mask */
#define DWT_SLEEPCNT_SLEEPCNT_MSK          (0xFFUL)

/* DWT LSU Count Register Definitions */
#define DWT_LSUCNT_LSUCNT_POS               0U      /* DWT LSUCNT: LSUCNT Position */
/* DWT LSUCNT: LSUCNT Mask */
#define DWT_LSUCNT_LSUCNT_MSK              (0xFFUL)

/* DWT Folded-instruction Count Register Definitions */
#define DWT_FOLDCNT_FOLDCNT_POS             0U      /* DWT FOLDCNT: FOLDCNT Position */
/* DWT FOLDCNT: FOLDCNT Mask */
#define DWT_FOLDCNT_FOLDCNT_MSK            (0xFFUL)

/* DWT Comparator Mask Register Definitions */
#define DWT_MASK_MASK_POS                   0U      /* DWT MASK: MASK Position */
/* DWT MASK: MASK Mask */
#define DWT_MASK_MASK_MSK                  (0x1FUL)

/* DWT Comparator Function Register Definitions */
#define DWT_FUNCTION_MATCHED_POS           24U      /* DWT FUNCTION: MATCHED Position */
/* DWT FUNCTION: MATCHED Mask */
#define DWT_FUNCTION_MATCHED_MSK           (0x1UL << DWT_FUNCTION_MATCHED_POS)

#define DWT_FUNCTION_DATAVADDR1_POS        16U      /* DWT FUNCTION: DATAVADDR1 Position */
/* DWT FUNCTION: DATAVADDR1 Mask */
#define DWT_FUNCTION_DATAVADDR1_MSK        (0xFUL << DWT_FUNCTION_DATAVADDR1_POS)

#define DWT_FUNCTION_DATAVADDR0_POS        12U      /* DWT FUNCTION: DATAVADDR0 Position */
/* DWT FUNCTION: DATAVADDR0 Mask */
#define DWT_FUNCTION_DATAVADDR0_MSK        (0xFUL << DWT_FUNCTION_DATAVADDR0_POS)

#define DWT_FUNCTION_DATAVSIZE_POS         10U      /* DWT FUNCTION: DATAVSIZE Position */
/* DWT FUNCTION: DATAVSIZE Mask */
#define DWT_FUNCTION_DATAVSIZE_MSK         (0x3UL << DWT_FUNCTION_DATAVSIZE_POS)

#define DWT_FUNCTION_LNK1ENA_POS            9U      /* DWT FUNCTION: LNK1ENA Position */
/* DWT FUNCTION: LNK1ENA Mask */
#define DWT_FUNCTION_LNK1ENA_MSK           (0x1UL << DWT_FUNCTION_LNK1ENA_POS)

#define DWT_FUNCTION_DATAVMATCH_POS         8U      /* DWT FUNCTION: DATAVMATCH Position */
/* DWT FUNCTION: DATAVMATCH Mask */
#define DWT_FUNCTION_DATAVMATCH_MSK        (0x1UL << DWT_FUNCTION_DATAVMATCH_POS)

#define DWT_FUNCTION_CYCMATCH_POS           7U      /* DWT FUNCTION: CYCMATCH Position */
/* DWT FUNCTION: CYCMATCH Mask */
#define DWT_FUNCTION_CYCMATCH_MSK          (0x1UL << DWT_FUNCTION_CYCMATCH_POS)

#define DWT_FUNCTION_EMITRANGE_POS          5U      /* DWT FUNCTION: EMITRANGE Position */
/* DWT FUNCTION: EMITRANGE Mask */
#define DWT_FUNCTION_EMITRANGE_MSK         (0x1UL << DWT_FUNCTION_EMITRANGE_POS)

#define DWT_FUNCTION_FUNCTION_POS           0U      /* DWT FUNCTION: FUNCTION Position */
/* DWT FUNCTION: FUNCTION Mask */
#define DWT_FUNCTION_FUNCTION_MSK          (0xFUL)

/*
 * \ingroup  CMSIS_core_register
 * \defgroup CMSIS_TPI     Trace Port Interface (TPI)
 * \brief    Type definitions for the Trace Port Interface (TPI)
 */

/* brief  Structure type to access the Trace Port Interface Register (TPI). */
typedef struct
{
  __IOM T_UINT32 SSPSR;   /* Offset: 0x000 (R/ )  Supported Parallel Port Size Register */
  __IOM T_UINT32 CSPSR;   /* Offset: 0x004 (R/W)  Current Parallel Port Size Register */
        T_UINT32 RESERVED0[2U];
  __IOM T_UINT32 ACPR;    /* Offset: 0x010 (R/W)  Asynchronous Clock Prescaler Register */
        T_UINT32 RESERVED1[55U];
  __IOM T_UINT32 SPPR;    /* Offset: 0x0F0 (R/W)  Selected Pin Protocol Register */
        T_UINT32 RESERVED2[131U];
  __IM  T_UINT32 FFSR;    /* Offset: 0x300 (R/ )  Formatter and Flush Status Register */
  __IOM T_UINT32 FFCR;    /* Offset: 0x304 (R/W)  Formatter and Flush Control Register */
  __IM  T_UINT32 FSCR;    /* Offset: 0x308 (R/ )  Formatter Synchronization Counter Register */
        T_UINT32 RESERVED3[759U];
  __IM  T_UINT32 TRIGGER;   /* Offset: 0xEE8 (R/ )  TRIGGER */
  __IM  T_UINT32 FIFO0;     /* Offset: 0xEEC (R/ )  Integration ETM Data */
  __IM  T_UINT32 ITATBCTR2; /* Offset: 0xEF0 (R/ )  ITATBCTR2 */
        T_UINT32 RESERVED4[1U];
  __IM  T_UINT32 ITATBCTR0; /* Offset: 0xEF8 (R/ )  ITATBCTR0 */
  __IM  T_UINT32 FIFO1;     /* Offset: 0xEFC (R/ )  Integration ITM Data */
  __IOM T_UINT32 ITCTRL;    /* Offset: 0xF00 (R/W)  Integration Mode Control */
        T_UINT32 RESERVED5[39U];
  __IOM T_UINT32 CLAIMSET; /* Offset: 0xFA0 (R/W)  Claim tag set */
  __IOM T_UINT32 CLAIMCLR; /* Offset: 0xFA4 (R/W)  Claim tag clear */
        T_UINT32 RESERVED7[8U];
  __IM  T_UINT32 DEVID;   /* Offset: 0xFC8 (R/ )  TPIU_DEVID */
  __IM  T_UINT32 DEVTYPE; /* Offset: 0xFCC (R/ )  TPIU_DEVTYPE */
} T_TPI;

/* TPI Asynchronous Clock Prescaler Register Definitions */
#define TPI_ACPR_PRESCALER_POS              0U      /* TPI ACPR: PRESCALER Position */
/* TPI ACPR: PRESCALER Mask */
#define TPI_ACPR_PRESCALER_MSK             (0x1FFFU)

/* TPI Selected Pin Protocol Register Definitions */
#define TPI_SPPR_TXMODE_POS                 0U      /* TPI SPPR: TXMODE Position */
/* TPI SPPR: TXMODE Mask */
#define TPI_SPPR_TXMODE_MSK                (0x3UL)

/* TPI Formatter and Flush Status Register Definitions */
#define TPI_FFSR_FTNONSTOP_POS              3U      /* TPI FFSR: FtNonStop Position */
/* TPI FFSR: FtNonStop Mask */
#define TPI_FFSR_FTNONSTOP_MSK             (0x1UL << TPI_FFSR_FTNONSTOP_POS)

#define TPI_FFSR_TCPRESENT_POS              2U      /* TPI FFSR: TCPresent Position */
/* TPI FFSR: TCPresent Mask */
#define TPI_FFSR_TCPRESENT_MSK             (0x1UL << TPI_FFSR_TCPRESENT_POS)

#define TPI_FFSR_FTSTOPPED_POS              1U      /* TPI FFSR: FtStopped Position */
/* TPI FFSR: FtStopped Mask */
#define TPI_FFSR_FTSTOPPED_MSK             (0x1UL << TPI_FFSR_FTSTOPPED_POS)

#define TPI_FFSR_FLINPROG_POS               0U      /* TPI FFSR: FlInProg Position */
/* TPI FFSR: FlInProg Mask */
#define TPI_FFSR_FLINPROG_MSK              (0x1UL)

/* TPI Formatter and Flush Control Register Definitions */
#define TPI_FFCR_TRIGIN_POS                 8U      /* TPI FFCR: TrigIn Position */
/* TPI FFCR: TrigIn Mask */
#define TPI_FFCR_TRIGIN_MSK                (0x1UL << TPI_FFCR_TRIGIN_POS)

#define TPI_FFCR_ENFCONT_POS                1U      /* TPI FFCR: EnFCont Position */
/* TPI FFCR: EnFCont Mask */
#define TPI_FFCR_ENFCONT_MSK               (0x1UL << TPI_FFCR_ENFCONT_POS)

/* TPI TRIGGER Register Definitions */
#define TPI_TRIGGER_TRIGGER_POS             0U      /* TPI TRIGGER: TRIGGER Position */
/* TPI TRIGGER: TRIGGER Mask */
#define TPI_TRIGGER_TRIGGER_MSK            (0x1UL)

/* TPI Integration ETM Data Register Definitions (FIFO0) */
#define TPI_FIFO0_ITM_ATVALID_POS          29U      /* TPI FIFO0: ITM_ATVALID Position */
/* TPI FIFO0: ITM_ATVALID Mask */
#define TPI_FIFO0_ITM_ATVALID_MSK          (0x3UL << TPI_FIFO0_ITM_ATVALID_POS)

#define TPI_FIFO0_ITM_BYTECOUNT_POS        27U      /* TPI FIFO0: ITM_bytecount Position */
/* TPI FIFO0: ITM_bytecount Mask */
#define TPI_FIFO0_ITM_BYTECOUNT_MSK        (0x3UL << TPI_FIFO0_ITM_BYTECOUNT_POS)

#define TPI_FIFO0_ETM_ATVALID_POS          26U      /* TPI FIFO0: ETM_ATVALID Position */
/* TPI FIFO0: ETM_ATVALID Mask */
#define TPI_FIFO0_ETM_ATVALID_MSK          (0x3UL << TPI_FIFO0_ETM_ATVALID_POS)

#define TPI_FIFO0_ETM_BYTECOUNT_POS        24U      /* TPI FIFO0: ETM_bytecount Position */
/* TPI FIFO0: ETM_bytecount Mask */
#define TPI_FIFO0_ETM_BYTECOUNT_MSK        (0x3UL << TPI_FIFO0_ETM_BYTECOUNT_POS)

#define TPI_FIFO0_ETM2_POS                 16U      /* TPI FIFO0: ETM2 Position */
/* TPI FIFO0: ETM2 Mask */
#define TPI_FIFO0_ETM2_MSK                 (0xFFUL << TPI_FIFO0_ETM2_POS)

#define TPI_FIFO0_ETM1_POS                  8U      /* TPI FIFO0: ETM1 Position */
/* TPI FIFO0: ETM1 Mask */
#define TPI_FIFO0_ETM1_MSK                 (0xFFUL << TPI_FIFO0_ETM1_POS)

#define TPI_FIFO0_ETM0_POS                  0U      /* TPI FIFO0: ETM0 Position */
/* TPI FIFO0: ETM0 Mask */
#define TPI_FIFO0_ETM0_MSK                 (0xFFUL)

/* TPI ITATBCTR2 Register Definitions */
#define TPI_ITATBCTR2_ATREADY_POS           0U      /* TPI ITATBCTR2: ATREADY Position */
/* TPI ITATBCTR2: ATREADY Mask */
#define TPI_ITATBCTR2_ATREADY_MSK          (0x1UL)

/* TPI Integration ITM Data Register Definitions (FIFO1) */
#define TPI_FIFO1_ITM_ATVALID_POS          29U      /* TPI FIFO1: ITM_ATVALID Position */
/* TPI FIFO1: ITM_ATVALID Mask */
#define TPI_FIFO1_ITM_ATVALID_MSK          (0x3UL << TPI_FIFO1_ITM_ATVALID_POS)

#define TPI_FIFO1_ITM_BYTECOUNT_POS        27U      /* TPI FIFO1: ITM_bytecount Position */
/* TPI FIFO1: ITM_bytecount Mask */
#define TPI_FIFO1_ITM_BYTECOUNT_MSK        (0x3UL << TPI_FIFO1_ITM_BYTECOUNT_POS)

#define TPI_FIFO1_ETM_ATVALID_POS          26U      /* TPI FIFO1: ETM_ATVALID Position */
/* TPI FIFO1: ETM_ATVALID Mask */
#define TPI_FIFO1_ETM_ATVALID_MSK          (0x3UL << TPI_FIFO1_ETM_ATVALID_POS)

#define TPI_FIFO1_ETM_BYTECOUNT_POS        24U      /* TPI FIFO1: ETM_bytecount Position */
/* TPI FIFO1: ETM_bytecount Mask */
#define TPI_FIFO1_ETM_BYTECOUNT_MSK        (0x3UL << TPI_FIFO1_ETM_BYTECOUNT_POS)

#define TPI_FIFO1_ITM2_POS                 16U      /* TPI FIFO1: ITM2 Position */
/* TPI FIFO1: ITM2 Mask */
#define TPI_FIFO1_ITM2_MSK                 (0xFFUL << TPI_FIFO1_ITM2_POS)

#define TPI_FIFO1_ITM1_POS                  8U      /* TPI FIFO1: ITM1 Position */
/* TPI FIFO1: ITM1 Mask */
#define TPI_FIFO1_ITM1_MSK                 (0xFFUL << TPI_FIFO1_ITM1_POS)

#define TPI_FIFO1_ITM0_POS                  0U      /* TPI FIFO1: ITM0 Position */
/* TPI FIFO1: ITM0 Mask */
#define TPI_FIFO1_ITM0_MSK                 (0xFFUL)

/* TPI ITATBCTR0 Register Definitions */
#define TPI_ITATBCTR0_ATREADY_POS           0U      /* TPI ITATBCTR0: ATREADY Position */
/* TPI ITATBCTR0: ATREADY Mask */
#define TPI_ITATBCTR0_ATREADY_MSK          (0x1UL)

/* TPI Integration Mode Control Register Definitions */
#define TPI_ITCTRL_MODE_POS                 0U      /* TPI ITCTRL: Mode Position */
/* TPI ITCTRL: Mode Mask */
#define TPI_ITCTRL_MODE_MSK                (0x1UL)

/* TPI DEVID Register Definitions */
#define TPI_DEVID_NRZVALID_POS             11U      /* TPI DEVID: NRZVALID Position */
/* TPI DEVID: NRZVALID Mask */
#define TPI_DEVID_NRZVALID_MSK             (0x1UL << TPI_DEVID_NRZVALID_POS)

#define TPI_DEVID_MANCVALID_POS            10U      /* TPI DEVID: MANCVALID Position */
/* TPI DEVID: MANCVALID Mask */
#define TPI_DEVID_MANCVALID_MSK            (0x1UL << TPI_DEVID_MANCVALID_POS)

#define TPI_DEVID_PTINVALID_POS             9U      /* TPI DEVID: PTINVALID Position */
/* TPI DEVID: PTINVALID Mask */
#define TPI_DEVID_PTINVALID_MSK            (0x1UL << TPI_DEVID_PTINVALID_POS)

#define TPI_DEVID_MINBUFSZ_POS              6U      /* TPI DEVID: MinBufSz Position */
/* TPI DEVID: MinBufSz Mask */
#define TPI_DEVID_MINBUFSZ_MSK             (0x7UL << TPI_DEVID_MINBUFSZ_POS)

#define TPI_DEVID_ASYNCLKIN_POS             5U      /* TPI DEVID: AsynClkIn Position */
/* TPI DEVID: AsynClkIn Mask */
#define TPI_DEVID_ASYNCLKIN_MSK            (0x1UL << TPI_DEVID_ASYNCLKIN_POS)

#define TPI_DEVID_NRTRACEINPUT_POS          0U      /* TPI DEVID: NrTraceInput Position */
/* TPI DEVID: NrTraceInput Mask */
#define TPI_DEVID_NRTRACEINPUT_MSK         (0x1FUL)

/* TPI DEVTYPE Register Definitions */
#define TPI_DEVTYPE_MAJORTYPE_POS           4U      /* TPI DEVTYPE: MajorType Position */
/* TPI DEVTYPE: MajorType Mask */
#define TPI_DEVTYPE_MAJORTYPE_MSK          (0xFUL << TPI_DEVTYPE_MAJORTYPE_POS)

#define TPI_DEVTYPE_SUBTYPE_POS             0U      /* TPI DEVTYPE: SubType Position */
/* TPI DEVTYPE: SubType Mask */
#define TPI_DEVTYPE_SUBTYPE_MSK            (0xFUL)

#if (__MPU_PRESENT == ONE)
/*
 * \ingroup  CMSIS_core_register
 * \defgroup CMSIS_MPU     Memory Protection Unit (MPU)
 * \brief    Type definitions for the Memory Protection Unit (MPU)
 */

/* brief  Structure type to access the Memory Protection Unit (MPU).*/
typedef struct
{
  __IM  T_UINT32 TYPE;    /* Offset: 0x000 (R/ )  MPU Type Register */
  __IOM T_UINT32 CTRL;    /* Offset: 0x004 (R/W)  MPU Control Register */
  __IOM T_UINT32 RNR;     /* Offset: 0x008 (R/W)  MPU Region RNRber Register */
  __IOM T_UINT32 RBAR;    /* Offset: 0x00C (R/W)  MPU Region Base Address Register */
  __IOM T_UINT32 RASR;    /* Offset: 0x010 (R/W)  MPU Region Attribute and Size Register */
  __IOM T_UINT32 RBAR_A1; /* Offset: 0x014 (R/W)  MPU Alias 1 Region Base Address Register */
  __IOM T_UINT32 RASR_A1; /* Offset: 0x018 (R/W)  MPU Alias 1 Region Attribute and Size Register */
  __IOM T_UINT32 RBAR_A2; /* Offset: 0x01C (R/W)  MPU Alias 2 Region Base Address Register */
  __IOM T_UINT32 RASR_A2; /* Offset: 0x020 (R/W)  MPU Alias 2 Region Attribute and Size Register */
  __IOM T_UINT32 RBAR_A3; /* Offset: 0x024 (R/W)  MPU Alias 3 Region Base Address Register */
  __IOM T_UINT32 RASR_A3; /* Offset: 0x028 (R/W)  MPU Alias 3 Region Attribute and Size Register */
} T_MPU;

/* MPU Type Register Definitions */
#define MPU_TYPE_IREGION_POS               16U      /*MPU TYPE: IREGION Position */
/* MPU TYPE: IREGION Mask */
#define MPU_TYPE_IREGION_MSK               (0xFFUL << MPU_TYPE_IREGION_POS)

#define MPU_TYPE_DREGION_POS                8U      /*MPU TYPE: DREGION Position */
/* MPU TYPE: DREGION Mask */
#define MPU_TYPE_DREGION_MSK               (0xFFUL << MPU_TYPE_DREGION_POS)

#define MPU_TYPE_SEPARATE_POS               0U      /*MPU TYPE: SEPARATE Position */
/* MPU TYPE: SEPARATE Mask */
#define MPU_TYPE_SEPARATE_MSK              (1UL)

/* MPU Control Register Definitions */
#define MPU_CTRL_PRIVDEFENA_POS             2U      /*MPU CTRL: PRIVDEFENA Position */
/* MPU CTRL: PRIVDEFENA Mask */
#define MPU_CTRL_PRIVDEFENA_MSK            (1UL << MPU_CTRL_PRIVDEFENA_POS)

#define MPU_CTRL_HFNMIENA_POS               1U      /*MPU CTRL: HFNMIENA Position */
/* MPU CTRL: HFNMIENA Mask */
#define MPU_CTRL_HFNMIENA_MSK              (1UL << MPU_CTRL_HFNMIENA_POS)

#define MPU_CTRL_ENABLE_POS                 0U      /*MPU CTRL: ENABLE Position */
/* MPU CTRL: ENABLE Mask */
#define MPU_CTRL_ENABLE_MSK                (1UL)

/* MPU Region Number Register Definitions */
#define MPU_RNR_REGION_POS                  0U      /*MPU RNR: REGION Position */
/* MPU RNR: REGION Mask */
#define MPU_RNR_REGION_MSK                 (0xFFUL)

/* MPU Region Base Address Register Definitions */
#define MPU_RBAR_ADDR_POS                   5U      /*MPU RBAR: ADDR Position */
/* MPU RBAR: ADDR Mask */
#define MPU_RBAR_ADDR_MSK                  (0x7FFFFFFUL << MPU_RBAR_ADDR_POS)

#define MPU_RBAR_VALID_POS                  4U      /*MPU RBAR: VALID Position */
/* MPU RBAR: VALID Mask */
#define MPU_RBAR_VALID_MSK                 (1UL << MPU_RBAR_VALID_POS)

#define MPU_RBAR_REGION_POS                 0U      /*MPU RBAR: REGION Position */
/* MPU RBAR: REGION Mask */
#define MPU_RBAR_REGION_MSK                (0xFUL)

/* MPU Region Attribute and Size Register Definitions */
#define MPU_RASR_ATTRS_POS                 16U  /*MPU RASR: MPU Region Attribute field Position */
/* MPU RASR: MPU Region Attribute field Mask */
#define MPU_RASR_ATTRS_MSK                 (0xFFFFUL << MPU_RASR_ATTRS_POS)

#define MPU_RASR_XN_POS                    28U      /*MPU RASR: ATTRS.XN Position */
/* MPU RASR: ATTRS.XN Mask */
#define MPU_RASR_XN_MSK                    (1UL << MPU_RASR_XN_POS)

#define MPU_RASR_AP_POS                    24U      /*MPU RASR: ATTRS.AP Position */
/* MPU RASR: ATTRS.AP Mask */
#define MPU_RASR_AP_MSK                    (0x7UL << MPU_RASR_AP_POS)

#define MPU_RASR_TEX_POS                   19U      /*MPU RASR: ATTRS.TEX Position */
/* MPU RASR: ATTRS.TEX Mask */
#define MPU_RASR_TEX_MSK                   (0x7UL << MPU_RASR_TEX_POS)

#define MPU_RASR_S_POS                     18U      /*MPU RASR: ATTRS.S Position */
#define MPU_RASR_S_MSK                     (1UL << MPU_RASR_S_POS) /* MPU RASR: ATTRS.S Mask */

#define MPU_RASR_C_POS                     17U      /*MPU RASR: ATTRS.C Position */
#define MPU_RASR_C_MSK                     (1UL << MPU_RASR_C_POS) /* MPU RASR: ATTRS.C Mask */

#define MPU_RASR_B_POS                     16U      /*MPU RASR: ATTRS.B Position */
#define MPU_RASR_B_MSK                     (1UL << MPU_RASR_B_POS) /* MPU RASR: ATTRS.B Mask */

#define MPU_RASR_SRD_POS                    8U      /*MPU RASR: Sub-Region Disable Position */
/* MPU RASR: Sub-Region Disable Mask */
#define MPU_RASR_SRD_MSK                   (0xFFUL << MPU_RASR_SRD_POS)

#define MPU_RASR_SIZE_POS                   1U      /*MPU RASR: Region Size Field Position */
/* MPU RASR: Region Size Field Mask */
#define MPU_RASR_SIZE_MSK                  (0x1FUL << MPU_RASR_SIZE_POS)

#define MPU_RASR_ENABLE_POS                 0U      /*MPU RASR: Region enable bit Position */
/* MPU RASR: Region enable bit Disable Mask */
#define MPU_RASR_ENABLE_MSK                (1UL)

#endif /*__MPU_PRESENT == ONE*/

#if (__FPU_PRESENT == ONE)
/*
 * \ingroup  CMSIS_core_register
 * \defgroup CMSIS_FPU     Floating Point Unit (FPU)
 * \brief    Type definitions for the Floating Point Unit (FPU)
 */

/* brief  Structure type to access the Floating Point Unit (FPU). */
typedef struct
{
        T_UINT32 RESERVED0[1U];
  __IOM T_UINT32 FPCCR;   /* Offset: 0x004 (R/W)  Floating-Point Context Control Register */
  __IOM T_UINT32 FPCAR;   /* Offset: 0x008 (R/W)  Floating-Point Context Address Register */
  __IOM T_UINT32 FPDSCR;  /* Offset: 0x00C (R/W)  Floating-Point Default Status Control Register */
  __IM  T_UINT32 MVFR0;   /* Offset: 0x010 (R/ )  Media and FP Feature Register 0 */
  __IM  T_UINT32 MVFR1;   /* Offset: 0x014 (R/ )  Media and FP Feature Register 1 */
  __IM  T_UINT32 MVFR2;   /* Offset: 0x018 (R/ )  Media and FP Feature Register 2 */
} T_FPU;

/* Floating-Point Context Control Register Definitions */
#define FPU_FPCCR_ASPEN_POS                31U      /*FPCCR: ASPEN bit Position */
#define FPU_FPCCR_ASPEN_MSK                (1UL << FPU_FPCCR_ASPEN_POS) /* FPCCR: ASPEN bit Mask */

#define FPU_FPCCR_LSPEN_POS                30U      /*FPCCR: LSPEN Position */
#define FPU_FPCCR_LSPEN_MSK                (1UL << FPU_FPCCR_LSPEN_POS) /* FPCCR: LSPEN bit Mask */

#define FPU_FPCCR_MONRDY_POS                8U      /*FPCCR: MONRDY Position */
#define FPU_FPCCR_MONRDY_MSK               (1UL << FPU_FPCCR_MONRDY_POS) /* FPCCR:MONRDY bit Mask*/

#define FPU_FPCCR_BFRDY_POS                 6U      /*FPCCR: BFRDY Position */
#define FPU_FPCCR_BFRDY_MSK                (1UL << FPU_FPCCR_BFRDY_POS) /* FPCCR: BFRDY bit Mask */

#define FPU_FPCCR_MMRDY_POS                 5U      /*FPCCR: MMRDY Position */
#define FPU_FPCCR_MMRDY_MSK                (1UL << FPU_FPCCR_MMRDY_POS) /* FPCCR: MMRDY bit Mask */

#define FPU_FPCCR_HFRDY_POS                 4U      /*FPCCR: HFRDY Position */
#define FPU_FPCCR_HFRDY_MSK                (1UL << FPU_FPCCR_HFRDY_POS) /* FPCCR: HFRDY bit Mask */

#define FPU_FPCCR_THREAD_POS                3U      /*FPCCR: processor mode bit Position */
/* FPCCR: processor mode active bit Mask */
#define FPU_FPCCR_THREAD_MSK               (1UL << FPU_FPCCR_THREAD_POS)

#define FPU_FPCCR_USER_POS                  1U      /*FPCCR: privilege level bit Position */
/* FPCCR: privilege level bit Mask */
#define FPU_FPCCR_USER_MSK                 (1UL << FPU_FPCCR_USER_POS)

/*FPCCR: Lazy state preservation active bit Position */
#define FPU_FPCCR_LSPACT_POS                0U
/* FPCCR: Lazy state preservation active bit Mask */
#define FPU_FPCCR_LSPACT_MSK               (1UL)

/* Floating-Point Context Address Register Definitions */
#define FPU_FPCAR_ADDRESS_POS               3U      /*FPCAR: ADDRESS bit Position */
/* FPCAR: ADDRESS bit Mask */
#define FPU_FPCAR_ADDRESS_MSK              (0x1FFFFFFFUL << FPU_FPCAR_ADDRESS_POS)

/* Floating-Point Default Status Control Register Definitions */
#define FPU_FPDSCR_AHP_POS                 26U      /*FPDSCR: AHP bit Position */
#define FPU_FPDSCR_AHP_MSK                 (1UL << FPU_FPDSCR_AHP_POS)     /* FPDSCR:AHP bit Mask*/

#define FPU_FPDSCR_DN_POS                  25U      /*FPDSCR: DN bit Position */
#define FPU_FPDSCR_DN_MSK                  (1UL << FPU_FPDSCR_DN_POS)      /* FPDSCR: DN bit Mask*/

#define FPU_FPDSCR_FZ_POS                  24U      /*FPDSCR: FZ bit Position */
#define FPU_FPDSCR_FZ_MSK                  (1UL << FPU_FPDSCR_FZ_POS)      /* FPDSCR: FZ bit Mask*/

#define FPU_FPDSCR_RMODE_POS               22U      /*FPDSCR: RMode bit Position */
/* FPDSCR: RMode bit Mask */
#define FPU_FPDSCR_RMODE_MSK               (3UL << FPU_FPDSCR_RMODE_POS)

/* Media and FP Feature Register 0 Definitions */
#define FPU_MVFR0_FP_ROUNDING_MODES_POS    28U      /*MVFR0: FP rounding modes bits Position */
/* MVFR0: FP rounding modes bits Mask */
#define FPU_MVFR0_FP_ROUNDING_MODES_MSK    (0xFUL << FPU_MVFR0_FP_ROUNDING_MODES_POS)

#define FPU_MVFR0_SHORT_VECTORS_POS        24U      /*MVFR0: Short vectors bits Position */
/* MVFR0: Short vectors bits Mask */
#define FPU_MVFR0_SHORT_VECTORS_MSK        (0xFUL << FPU_MVFR0_SHORT_VECTORS_POS)

#define FPU_MVFR0_SQUARE_ROOT_POS          20U      /*MVFR0: Square root bits Position */
/* MVFR0: Square root bits Mask */
#define FPU_MVFR0_SQUARE_ROOT_MSK          (0xFUL << FPU_MVFR0_SQUARE_ROOT_POS)

#define FPU_MVFR0_DIVIDE_POS               16U      /*MVFR0: Divide bits Position */
/* MVFR0: Divide bits Mask */
#define FPU_MVFR0_DIVIDE_MSK               (0xFUL << FPU_MVFR0_DIVIDE_POS)

#define FPU_MVFR0_FP_EXCEP_TRAPPING_POS    12U      /*MVFR0: FP exception trapping bits Position */

/* MVFR0: FP exception trapping bits Mask */
#define FPU_MVFR0_FP_EXCEP_TRAPPING_MSK    (0xFUL << FPU_MVFR0_FP_EXCEP_TRAPPING_POS)

#define FPU_MVFR0_DOUBLE_PRECISION_POS      8U      /*MVFR0: Double-precision bits Position */
/* MVFR0: Double-precision bits Mask */
#define FPU_MVFR0_DOUBLE_PRECISION_MSK     (0xFUL << FPU_MVFR0_DOUBLE_PRECISION_POS)

#define FPU_MVFR0_SINGLE_PRECISION_POS      4U      /*MVFR0: Single-precision bits Position */
/* MVFR0: Single-precision bits Mask */
#define FPU_MVFR0_SINGLE_PRECISION_MSK     (0xFUL << FPU_MVFR0_SINGLE_PRECISION_POS)

#define FPU_MVFR0_A_SIMD_REGISTERS_POS      0U      /*MVFR0: A_SIMD registers bits Position */
/* MVFR0: A_SIMD registers bits Mask */
#define FPU_MVFR0_A_SIMD_REGISTERS_MSK     (0xFUL)

/* Media and FP Feature Register 1 Definitions */
#define FPU_MVFR1_FP_FUSED_MAC_POS         28U      /*MVFR1: FP fused MAC bits Position */
/* MVFR1: FP fused MAC bits Mask */
#define FPU_MVFR1_FP_FUSED_MAC_MSK         (0xFUL << FPU_MVFR1_FP_FUSED_MAC_POS)

#define FPU_MVFR1_FP_HPFP_POS              24U      /*MVFR1: FP HPFP bits Position */
/* MVFR1: FP HPFP bits Mask */
#define FPU_MVFR1_FP_HPFP_MSK              (0xFUL << FPU_MVFR1_FP_HPFP_POS)

#define FPU_MVFR1_D_NAN_MODE_POS            4U      /*MVFR1: D_NaN mode bits Position */
/* MVFR1: D_NaN mode bits Mask */
#define FPU_MVFR1_D_NAN_MODE_MSK           (0xFUL << FPU_MVFR1_D_NAN_MODE_POS)

#define FPU_MVFR1_FTZ_MODE_POS              0U      /*MVFR1: FtZ mode bits Position */
/* MVFR1: FtZ mode bits Mask */
#define FPU_MVFR1_FTZ_MODE_MSK             (0xFUL)

#endif /*__FPU_PRESENT == ONE*/

/*
 * \ingroup  CMSIS_core_register
 * \defgroup CMSIS_CoreDebug       Core Debug Registers (CoreDebug)
 * \brief    Type definitions for the Core Debug Registers
 */

/* brief  Structure type to access the Core Debug Register (CoreDebug).*/
typedef struct
{
  __IOM T_UINT32 DHCSR;   /* Offset: 0x000 (R/W)  Debug Halting Control and Status Register */
  __OM  T_UINT32 DCRSR;   /* Offset: 0x004 ( /W)  Debug Core Register Selector Register */
  __IOM T_UINT32 DCRDR;   /* Offset: 0x008 (R/W)  Debug Core Register Data Register */
  __IOM T_UINT32 DEMCR;   /* Offset: 0x00C (R/W)  Debug Exception and Monitor Control Register */
} T_COREDEBUG;

/* Debug Halting Control and Status Register Definitions */
#define COREDEBUG_DHCSR_DBGKEY_POS         16U      /*CoreDebug DHCSR: DBGKEY Position */
/* CoreDebug DHCSR: DBGKEY Mask */
#define COREDEBUG_DHCSR_DBGKEY_MSK         (0xFFFFUL << COREDEBUG_DHCSR_DBGKEY_POS)

#define COREDEBUG_DHCSR_S_RESET_ST_POS     25U      /*CoreDebug DHCSR: S_RESET_ST Position */
/* CoreDebug DHCSR: S_RESET_ST Mask */
#define COREDEBUG_DHCSR_S_RESET_ST_MSK     (1UL << COREDEBUG_DHCSR_S_RESET_ST_POS)

#define COREDEBUG_DHCSR_S_RETIRE_ST_POS    24U      /*CoreDebug DHCSR: S_RETIRE_ST Position */
/* CoreDebug DHCSR: S_RETIRE_ST Mask */
#define COREDEBUG_DHCSR_S_RETIRE_ST_MSK    (1UL << COREDEBUG_DHCSR_S_RETIRE_ST_POS)

#define COREDEBUG_DHCSR_S_LOCKUP_POS       19U      /*CoreDebug DHCSR: S_LOCKUP Position */
/* CoreDebug DHCSR: S_LOCKUP Mask */
#define COREDEBUG_DHCSR_S_LOCKUP_MSK       (1UL << COREDEBUG_DHCSR_S_LOCKUP_POS)

#define COREDEBUG_DHCSR_S_SLEEP_POS        18U      /*CoreDebug DHCSR: S_SLEEP Position */
/* CoreDebug DHCSR: S_SLEEP Mask */
#define COREDEBUG_DHCSR_S_SLEEP_MSK        (1UL << COREDEBUG_DHCSR_S_SLEEP_POS)

#define COREDEBUG_DHCSR_S_HALT_POS         17U      /*CoreDebug DHCSR: S_HALT Position */
/* CoreDebug DHCSR: S_HALT Mask */
#define COREDEBUG_DHCSR_S_HALT_MSK         (1UL << COREDEBUG_DHCSR_S_HALT_POS)

#define COREDEBUG_DHCSR_S_REGRDY_POS       16U      /*CoreDebug DHCSR: S_REGRDY Position */
/* CoreDebug DHCSR: S_REGRDY Mask */
#define COREDEBUG_DHCSR_S_REGRDY_MSK       (1UL << COREDEBUG_DHCSR_S_REGRDY_POS)

#define COREDEBUG_DHCSR_C_SNAPSTALL_POS     5U      /*CoreDebug DHCSR: C_SNAPSTALL Position */
/* CoreDebug DHCSR: C_SNAPSTALL Mask */
#define COREDEBUG_DHCSR_C_SNAPSTALL_MSK    (1UL << COREDEBUG_DHCSR_C_SNAPSTALL_POS)

#define COREDEBUG_DHCSR_C_MASKINTS_POS      3U      /*CoreDebug DHCSR: C_MASKINTS Position */
/* CoreDebug DHCSR: C_MASKINTS Mask */
#define COREDEBUG_DHCSR_C_MASKINTS_MSK     (1UL << COREDEBUG_DHCSR_C_MASKINTS_POS)

#define COREDEBUG_DHCSR_C_STEP_POS          2U      /*CoreDebug DHCSR: C_STEP Position */
/* CoreDebug DHCSR: C_STEP Mask */
#define COREDEBUG_DHCSR_C_STEP_MSK         (1UL << COREDEBUG_DHCSR_C_STEP_POS)

#define COREDEBUG_DHCSR_C_HALT_POS          1U      /*CoreDebug DHCSR: C_HALT Position */
/* CoreDebug DHCSR: C_HALT Mask */
#define COREDEBUG_DHCSR_C_HALT_MSK         (1UL << COREDEBUG_DHCSR_C_HALT_POS)

#define COREDEBUG_DHCSR_C_DEBUGEN_POS       0U      /*CoreDebug DHCSR: C_DEBUGEN Position */
/* CoreDebug DHCSR: C_DEBUGEN Mask */
#define COREDEBUG_DHCSR_C_DEBUGEN_MSK      (1UL)

/* Debug Core Register Selector Register Definitions */
#define COREDEBUG_DCRSR_REGWNR_POS         16U      /*CoreDebug DCRSR: REGWnR Position */
/* CoreDebug DCRSR: REGWnR Mask */
#define COREDEBUG_DCRSR_REGWNR_MSK         (1UL << COREDEBUG_DCRSR_REGWNR_POS)

#define COREDEBUG_DCRSR_REGSEL_POS          0U      /*CoreDebug DCRSR: REGSEL Position */
/* CoreDebug DCRSR: REGSEL Mask */
#define COREDEBUG_DCRSR_REGSEL_MSK         (0x1FUL)

/* Debug Exception and Monitor Control Register Definitions */
#define COREDEBUG_DEMCR_TRCENA_POS         24U      /*CoreDebug DEMCR: TRCENA Position */
/* CoreDebug DEMCR: TRCENA Mask */
#define COREDEBUG_DEMCR_TRCENA_MSK         (1UL << COREDEBUG_DEMCR_TRCENA_POS)

#define COREDEBUG_DEMCR_MON_REQ_POS        19U      /*CoreDebug DEMCR: MON_REQ Position */
/* CoreDebug DEMCR: MON_REQ Mask */
#define COREDEBUG_DEMCR_MON_REQ_MSK        (1UL << COREDEBUG_DEMCR_MON_REQ_POS)

#define COREDEBUG_DEMCR_MON_STEP_POS       18U      /*CoreDebug DEMCR: MON_STEP Position */
/* CoreDebug DEMCR: MON_STEP Mask */
#define COREDEBUG_DEMCR_MON_STEP_MSK       (1UL << COREDEBUG_DEMCR_MON_STEP_POS)

#define COREDEBUG_DEMCR_MON_PEND_POS       17U      /*CoreDebug DEMCR: MON_PEND Position */
/* CoreDebug DEMCR: MON_PEND Mask */
#define COREDEBUG_DEMCR_MON_PEND_MSK       (1UL << COREDEBUG_DEMCR_MON_PEND_POS)

#define COREDEBUG_DEMCR_MON_EN_POS         16U      /*CoreDebug DEMCR: MON_EN Position */
/* CoreDebug DEMCR: MON_EN Mask */
#define COREDEBUG_DEMCR_MON_EN_MSK         (1UL << COREDEBUG_DEMCR_MON_EN_POS)

#define COREDEBUG_DEMCR_VC_HARDERR_POS     10U      /*CoreDebug DEMCR: VC_HARDERR Position */
/* CoreDebug DEMCR: VC_HARDERR Mask */
#define COREDEBUG_DEMCR_VC_HARDERR_MSK     (1UL << COREDEBUG_DEMCR_VC_HARDERR_POS)

#define COREDEBUG_DEMCR_VC_INTERR_POS       9U      /*CoreDebug DEMCR: VC_INTERR Position */
/* CoreDebug DEMCR: VC_INTERR Mask */
#define COREDEBUG_DEMCR_VC_INTERR_MSK      (1UL << COREDEBUG_DEMCR_VC_INTERR_POS)

#define COREDEBUG_DEMCR_VC_BUSERR_POS       8U      /*CoreDebug DEMCR: VC_BUSERR Position */
/* CoreDebug DEMCR: VC_BUSERR Mask */
#define COREDEBUG_DEMCR_VC_BUSERR_MSK      (1UL << COREDEBUG_DEMCR_VC_BUSERR_POS)

#define COREDEBUG_DEMCR_VC_STATERR_POS      7U      /*CoreDebug DEMCR: VC_STATERR Position */
/* CoreDebug DEMCR: VC_STATERR Mask */
#define COREDEBUG_DEMCR_VC_STATERR_MSK     (1UL << COREDEBUG_DEMCR_VC_STATERR_POS)

#define COREDEBUG_DEMCR_VC_CHKERR_POS       6U      /*CoreDebug DEMCR: VC_CHKERR Position */
#define COREDEBUG_DEMCR_VC_CHKERR_MSK      (1UL << COREDEBUG_DEMCR_VC_CHKERR_POS)

#define COREDEBUG_DEMCR_VC_NOCPERR_POS      5U      /*CoreDebug DEMCR: VC_NOCPERR Position */
/* CoreDebug DEMCR: VC_NOCPERR Mask */
#define COREDEBUG_DEMCR_VC_NOCPERR_MSK     (1UL << COREDEBUG_DEMCR_VC_NOCPERR_POS)

#define COREDEBUG_DEMCR_VC_MMERR_POS        4U      /*CoreDebug DEMCR: VC_MMERR Position */
/* CoreDebug DEMCR: VC_MMERR Mask */
#define COREDEBUG_DEMCR_VC_MMERR_MSK       (1UL << COREDEBUG_DEMCR_VC_MMERR_POS)

#define COREDEBUG_DEMCR_VC_CORERESET_POS    0U      /*CoreDebug DEMCR: VC_CORERESET Position */
/* CoreDebug DEMCR: VC_CORERESET Mask */
#define COREDEBUG_DEMCR_VC_CORERESET_MSK   (1UL)

/*
 * \brief   Mask and shift a bit field value for use in a register bit range.
 * \param[in] field  Name of the register bit field.
 * \param[in] value  Value of the bit field.
 * \return           Masked and shifted value.
 */
#define _VAL2FLD(field, value)    ((value << field ## _POS) & field ## _MSK)

/*
 * \brief     Mask and shift a register value to extract a bit filed value.
 * \param[in] field  Name of the register bit field.
 * \param[in] value  Value of register.
 * \return           Masked and shifted bit field value.
 */
#define _FLD2VAL(field, value)    ((value & field ## _MSK) >> field ## _POS)

/*
 * \ingroup    CMSIS_core_register
 * \defgroup   CMSIS_core_base     Core Definitions
 * \brief      Definitions for base addresses, unions, and structures.
 */

/* Memory mapping of Cortex-M4 Hardware */
#define SCS_BASE            (0xE000E000UL)         /* System Control Space Base Address */
#define ITM_BASE            (0xE0000000UL)         /* ITM Base Address */
#define DWT_BASE            (0xE0001000UL)         /* DWT Base Address */
#define TPI_BASE            (0xE0040000UL)         /* TPI Base Address */
#define COREDEBUG_BASE      (0xE000EDF0UL)         /* Core Debug Base Address */
#define SYSTICK_BASE        (SCS_BASE +  0x0010UL)  /* SysTick Base Address */
#define NVIC_BASE           (SCS_BASE +  0x0100UL)  /* NVIC Base Address */
#define SCB_BASE            (SCS_BASE +  0x0D00UL)  /* System Control Block Base Address */

/* System control Register not in SCB */
#define SCNSCB              ((T_SCNSCB    *)     SCS_BASE      )
#define SCB                 ((T_SCB       *)     SCB_BASE      )  /* SCB configuration struct */
/* SysTick configuration struct */
#define SYSTICK             ((T_SYSTICK   *)     SYSTICK_BASE  )
#define NVIC                ((T_NVIC      *)     NVIC_BASE     )  /* NVIC configuration struct*/
#define ITM                 ((T_ITM       *)     ITM_BASE      )  /* ITM configuration struct */
#define DWT                 ((T_DWT       *)     DWT_BASE      )  /* DWT configuration struct */
#define TPI                 ((T_TPI       *)     TPI_BASE      )  /* TPI configuration struct */
/* Core Debug configuration struct */
#define COREDEBUG           ((T_COREDEBUG *)     COREDEBUG_BASE)

#if (__MPU_PRESENT == ONE)
  #define MPU_BASE          (SCS_BASE +  0x0D90UL)                /* Memory Protection Unit */
  #define MPU               ((T_MPU       *)     MPU_BASE      )  /* Memory Protection Unit */
#endif /*__MPU_PRESENT == ONE*/

#if (__FPU_PRESENT == ONE)
  #define FPU_BASE          (SCS_BASE +  0x0F30UL)                /* Floating Point Unit */
  #define FPU               ((T_FPU       *)     FPU_BASE      )  /* Floating Point Unit */
#endif /*__FPU_PRESENT == ONE*/

/*
 * \brief   Instruction Synchronization Barrier
 * \details Instruction Synchronization Barrier flushes the pipeline in the processor,
 *          so that all instructions following the ISB are fetched from cache or memory,
 *          after the instruction has been completed.
 */
__attribute__((always_inline)) __STATIC_INLINE void __ISB(void)
{
  __ASM volatile ("isb 0xF":::"memory");
}

/*
 * \brief   Data Synchronization Barrier
 * \details Acts as a special kind of Data Memory Barrier.
 *          It completes when all explicit memory accesses before this instruction complete.
 */
__attribute__((always_inline)) __STATIC_INLINE void __DSB(void)
{
  __ASM volatile ("dsb 0xF":::"memory");
}


/*
 * \brief   No Operation
 * \details No Operation does nothing. This instruction can be used for code alignment purposes.
 */
__attribute__((always_inline)) __STATIC_INLINE void __NOP(void)
{
  __ASM volatile ("nop");
}

/*
 ******************************************************************************
 *                Hardware Abstraction Layer
 * Core Function Interface contains:
 * - Core NVIC Functions
 * - Core SysTick Functions
 * - Core Debug Functions
 * - Core Register Access Functions
 *****************************************************************************
 */

/* ##########################   NVIC functions  #################################### */

/*
 * \brief   Set Priority Grouping
 * \details Sets the priority grouping field using the required unlock sequence.
 *          The parameter PriorityGroup is assigned to the field SCB->AIRCR [10:8] PRIGROUP field.
 *          Only values from 0..7 are used.
 *          In case of a conflict between priority grouping and available
 *          priority bits (__NVIC_PRIO_BITS), the smallest possible priority group is set.
 * \param [in]      PriorityGroup  Priority grouping field.
 */
static inline void NVICSetPriorityGrouping(T_UINT32 priority_group)
{
  T_UINT32 reg_value = ZERO;
  T_UINT32 priority_group_tmp = (priority_group & (T_UINT32)SEVEN);

  reg_value  =  SCB->AIRCR;             /*read old register configuration */
  /* clear bits to change */
  reg_value &= ~((T_UINT32)(SCB_AIRCR_VECTKEY_MSK | SCB_AIRCR_PRIGROUP_MSK));
  /* Insert write key and priority group */
  reg_value  =  (reg_value                                   |
                ((T_UINT32)HEX_5FA << SCB_AIRCR_VECTKEY_POS) |
                (priority_group_tmp << EIGHT));
  SCB->AIRCR =  reg_value;
}

/*
 * \brief   Get Priority Grouping
 * \details Reads the priority grouping field from the NVIC Interrupt Controller.
 * \return                Priority grouping field (SCB->AIRCR [10:8] PRIGROUP field).
 */
static inline T_UINT32 NVICGetPriorityGrouping(void)
{
  return ((T_UINT32)((SCB->AIRCR & SCB_AIRCR_PRIGROUP_MSK) >> SCB_AIRCR_PRIGROUP_POS));
}

/*
 * \brief   Enable External Interrupt
 * \details Enables a device-specific interrupt in the NVIC interrupt controller.
 * \param [in]      IRQn  External interrupt number. Value cannot be negative.
 */

/*
 * \brief   Disable External Interrupt
 * \details Disables a device-specific interrupt in the NVIC interrupt controller.
 * \param [in]      IRQn  External interrupt number. Value cannot be negative.
 */
static inline void NVICDisableIRQ(T_IRQN_TYPE IRQn)
{
  NVIC->ICER[(((T_UINT32)(T_INT32)IRQn) >> FIVE)] = (T_UINT32)(ONE << \
         (((T_UINT32)(T_INT32)IRQn) & HEX_1F));
}

/*
 * \brief   Get Pending Interrupt
 * \details Reads the pending register in the NVIC and returns the pending
 * bit for the specified interrupt.
 * \param [in]      IRQn  Interrupt number.
 * \return             0  Interrupt status is not pending.
 * \return             1  Interrupt status is pending.
 */
static inline T_UINT32 NVICGetPendingIRQ(T_IRQN_TYPE IRQn)
{
  return((T_UINT32)(((NVIC->ISPR[(((T_UINT32)(T_INT32)IRQn) >> FIVE)] & \
         (ONE << (((T_UINT32)(T_INT32)IRQn) & HEX_1F))) != ZERO) ? ONE : ZERO));
}

/*
 * \brief   Set Pending Interrupt
 * \details Sets the pending bit of an external interrupt.
 * \param [in]      IRQn  Interrupt number. Value cannot be negative.
 */
static inline void NVICSetPendingIRQ(T_IRQN_TYPE IRQn)
{
  NVIC->ISPR[(((T_UINT32)(T_INT32)IRQn) >> FIVE)] = (T_UINT32)(ONE << \
         (((T_UINT32)(T_INT32)IRQn) & HEX_1F));
}

/*
 * \brief   Set Interrupt Priority
 * \details Sets the priority of an interrupt.
 * \note    The priority cannot be set for every core interrupt.
 * \param [in]      IRQn  Interrupt number.
 * \param [in]  priority  Priority to set.
 */
static inline void NVICSetPriority(T_IRQN_TYPE IRQn, T_UINT32 priority)
{
  if ((T_INT32)(IRQn) < (T_INT32)ZERO)
  {
    SCB->SHPR[(((T_UINT32)(T_INT32)IRQn) & FIFTEEN)-FOUR] = (T_UINT8)((priority << \
               (EIGHT - __NVIC_PRIO_BITS)) & (T_UINT32)HEX_FF);
  }
  else
  {
    NVIC->IP[((T_UINT32)(T_INT32)IRQn)] = (T_UINT8)((priority << \
            (EIGHT - __NVIC_PRIO_BITS)) & (T_UINT32)HEX_FF);
  }
}

/*
 * \brief   Get Interrupt Priority
 * \details Reads the priority of an interrupt.
 *         The interrupt number can be positive to specify an external (device specific) interrupt,
 *          or negative to specify an internal (core) interrupt.
 * \param [in]   IRQn  Interrupt number.
 * \return             Interrupt Priority.
 *                     Value is aligned automatically to the implemented priority bits of
 * the microcontroller.
 */
static inline T_UINT32 NVICGetPriority(T_IRQN_TYPE IRQn)
{

  if ((T_INT32)(IRQn) < (T_INT32)ZERO)
  {
    return(((T_UINT32)SCB->SHPR[(((T_UINT32)(T_INT32)IRQn) & FIFTEEN)-FOUR] >> \
               (EIGHT - __NVIC_PRIO_BITS)));
  }
  else
  {
    return(((T_UINT32)NVIC->IP[((T_UINT32)(T_INT32)IRQn)] >> (EIGHT - __NVIC_PRIO_BITS)));
  }
}

/*
 * \brief   Encode Priority
 * \details Encodes the priority for an interrupt with the given priority group,
 *          preemptive priority value, and subpriority value.
 *          In case of a conflict between priority grouping and available
 *          priority bits (__NVIC_PRIO_BITS), the smallest possible priority group is set.
 * \param [in]     PriorityGroup  Used priority group.
 * \param [in]   PreemptPriority  Preemptive priority value (starting from 0).
 * \param [in]       SubPriority  Subpriority value (starting from 0).
 * \return                        Encoded priority. Value can be used in the function
 * \ref NVIC_SetPriority().
 */
static inline T_UINT32 NVICEncodePriority (T_UINT32 priority_group, T_UINT32 preempt_priority, \
                                             T_UINT32 sub_priority)
{
  T_UINT32 priority_group_tmp = (priority_group & (T_UINT32)SEVEN); /* only values 0..7 are used */
  T_UINT32 preempt_priority_bits = ZERO;
  T_UINT32 subpriority_bits = ZERO;

  preempt_priority_bits = ((SEVEN - priority_group_tmp) > (T_UINT32)(__NVIC_PRIO_BITS)) ? \
                        (T_UINT32)(__NVIC_PRIO_BITS) : (T_UINT32)(SEVEN - priority_group_tmp);
  subpriority_bits     = ((priority_group_tmp + (T_UINT32)(__NVIC_PRIO_BITS)) < (T_UINT32)SEVEN) ? \
                           (T_UINT32)ZERO : (T_UINT32)((priority_group_tmp - SEVEN) + \
                           (T_UINT32)(__NVIC_PRIO_BITS));

  return (
           ((preempt_priority & (T_UINT32)((ONE << (preempt_priority_bits)) - ONE)) << \
            subpriority_bits) |
           ((sub_priority     & (T_UINT32)((ONE << (subpriority_bits    )) - ONE)))
         );
}

/*
 * \brief   Decode Priority
 * \details Decodes an interrupt priority value with a given priority group to
 *          preemptive priority value and subpriority value.
 *          In case of a conflict between priority grouping and available
 *          priority bits (__NVIC_PRIO_BITS) the smallest possible priority group is set.
 * \param [in]         Priority   Priority value, which can be retrieved with the function
 * \ref NVIC_GetPriority().
 * \param [in]     PriorityGroup  Used priority group.
 * \param [out] pPreemptPriority  Preemptive priority value (starting from 0).
 * \param [out]     pSubPriority  Subpriority value (starting from 0).
 */
static inline void NVICDecodePriority (T_UINT32 Priority, T_UINT32 priority_group,
         T_UINT32* const ppreempt_priority, T_UINT32* const psub_priority)
{
  T_UINT32 priority_group_tmp = (priority_group & (T_UINT32)SEVEN); /* only values 0..7 are used */
  T_UINT32 preempt_priority_bits = ZERO;
  T_UINT32 subpriority_bits = ZERO;

  preempt_priority_bits = ((SEVEN - priority_group_tmp) > (T_UINT32)(__NVIC_PRIO_BITS)) ? \
               (T_UINT32)(__NVIC_PRIO_BITS) : (T_UINT32)(SEVEN - priority_group_tmp);

  subpriority_bits  = ((priority_group_tmp + (T_UINT32)(__NVIC_PRIO_BITS)) < (T_UINT32)SEVEN) ? \
         (T_UINT32)ZERO : (T_UINT32)((priority_group_tmp - SEVEN) + (T_UINT32)(__NVIC_PRIO_BITS));

  *ppreempt_priority = (Priority >> subpriority_bits) & (T_UINT32)((ONE << \
            (preempt_priority_bits)) - ONE);

  *psub_priority     = (Priority ) & (T_UINT32)((ONE << (subpriority_bits    )) - ONE);
}

/*
 * \brief   System Reset
 * \details Initiates a system reset request to reset the MCU.
 */
static inline void NVICSystemReset(void)
{
  /*
   * Ensure all outstanding memory accesses included
   * buffered write are completed before reset
   */
  __DSB();
  SCB->AIRCR  = (T_UINT32)((HEX_5FA << SCB_AIRCR_VECTKEY_POS)    |
                           (SCB->AIRCR & SCB_AIRCR_PRIGROUP_MSK) |
                            SCB_AIRCR_SYSRESETREQ_MSK    );
  __DSB();     /*Ensure completion of memory access */

  for(;;)      /*wait until reset */
  {
    __NOP();
  }
}

/* ##########################  FPU functions  #################################### */

/*
 * \brief   get FPU type
 * \details returns the FPU type
 * \returns
 *  - \b  0: No FPU
 *  - \b  1: Single precision FPU
 *  - \b  2: Double + Single precision FPU
 */
static inline T_UINT32 SCBGetFPUType(void)
{
  T_UINT32 mvfr0 = ZERO;

  mvfr0 = SCB->MVFR0;
  if        (HEX_220 == (mvfr0 & EXTRACT_BIT4_12))
  {
    return TWO;           /* Double + Single precision FPU */
  }
  else if (HEX_20 == (mvfr0 & EXTRACT_BIT4_12))
  {
    return ONE;           /* Single precision FPU */
  }
  else
  {
    return ZERO;           /* No FPU */
  }
}

/* ##########################  Cache functions  #################################### */
/*
 * \ingroup  CMSIS_Core_FunctionInterface
 * \defgroup CMSIS_Core_CacheFunctions Cache Functions
 * \brief    Functions that configure Instruction and Data cache.
 */

/* Cache Size ID Register Macros */
#define CCSIDR_WAYS(x)       (((x) & SCB_CCSIDR_ASSOCIATIVITY_MSK) >> SCB_CCSIDR_ASSOCIATIVITY_POS)
#define CCSIDR_SETS(x)       (((x) & SCB_CCSIDR_NUMSETS_MSK ) >> SCB_CCSIDR_NUMSETS_POS )

/*
 * \brief   Enable I-Cache
 * \details Turns on I-Cache
 */
static inline void ScbEnableICache (void)
{
  #if (__ICACHE_PRESENT == ONE)
    __DSB();
    __ISB();
    SCB->ICIALLU = ZERO;      /* invalidate I-Cache */
    SCB->CCR |=  (T_UINT32)SCB_CCR_IC_MSK;  /* enable I-Cache */
    __DSB();
    __ISB();
  #endif
}

/*
 * \brief   Enable D-Cache
 * \details Turns on D-Cache
 */
static inline void ScbEnableDCache (void)
{
  #if (__DCACHE_PRESENT == ONE)
    T_UINT32 ccsidr = ZERO;
    T_UINT32 sets = ZERO;
    T_UINT32 ways = ZERO;

    SCB->CSSELR = (ZERO << ONE) | ZERO;     /* Level 1 data cache */
    __DSB();

    ccsidr = SCB->CCSIDR;

      /*invalidate D-Cache */
    sets = (T_UINT32)(CCSIDR_SETS(ccsidr));
    do
    {
      ways = (T_UINT32)(CCSIDR_WAYS(ccsidr));
      do
      {
        SCB->DCISW = (((sets << SCB_DCISW_SET_POS) & SCB_DCISW_SET_MSK) |
                      ((ways << SCB_DCISW_WAY_POS) & SCB_DCISW_WAY_MSK)  );
        #if defined ( __CC_ARM )
          __schedule_barrier();
        #endif
      } while (ways--);
    } while(sets--);
    __DSB();

    SCB->CCR |=  (T_UINT32)SCB_CCR_DC_MSK;  /* enable D-Cache */

    __DSB();
    __ISB();
  #endif
}

/* #####################    SysTick function  ########################### */
/*
 * \ingroup  CMSIS_Core_FunctionInterface
 * \defgroup CMSIS_Core_SysTickFunctions SysTick Functions
 * \brief    Functions that configure the System.
 */

#if (__VENDOR_SYSTICKCONFIG == ZERO)

/*
 * \brief   System Tick Configuration
 * \details Initializes the System Timer and its interrupt, and starts the System Tick Timer.
 *          Counter is in free running mode to generate periodic interrupts.
 * \param [in]  ticks  Number of ticks between two interrupts.
 * \return          0  Function succeeded.
 * \return          1  Function failed.
 * \note    When the variable <b>__Vendor_SysTickConfig</b> is set to 1, then the
 * function <b>SysTick_Config</b> is not included. In this case, the file <b><i>device</i>.h</b>
 *          must contain a vendor-specific implementation of this function.
 */
static inline T_UINT32 SysTickConfig(T_UINT32 ticks)
{
  if ((ticks - ONE) > SYSTICK_LOAD_RELOAD_MSK)
  {
    return (ONE);             /*Reload value impossible */
  }

  SYSTICK->LOAD  = (T_UINT32)(ticks - ONE);          /* set reload register */
  /* set Priority for Systick Interrupt */
  NVICSetPriority (SYSTICK_IRQN, (ONE << __NVIC_PRIO_BITS) - ONE);
  SYSTICK->VAL   = ZERO;       /*Load the SysTick Counter Value */
  SYSTICK->CTRL  = SYSTICK_CTRL_CLKSOURCE_MSK |
                   SYSTICK_CTRL_TICKINT_MSK   |
                   SYSTICK_CTRL_ENABLE_MSK;          /* Enable SysTick IRQ and SysTick Timer */
  return (ZERO);               /*Function successful */
}

#endif

/* ################### Debug In/Output function ######################## */
/*
 * \ingroup  CMSIS_Core_FunctionInterface
 * \defgroup CMSIS_core_DebugFunctions ITM Functions
 * \brief    Functions that access the ITM debug interface.
 */

extern volatile T_INT32 Itm_rx_buffer;     /* External variable to receive characters. */
/* Value identifying \ref Itm_rx_buffer is ready for next character. */
#define                 ITM_RXBUFFER_EMPTY   0x5AA55AA5U

/*
 * \brief   ITM Send Character
 * \details Transmits a character via the ITM channel 0, and
 *          \li Just returns when no debugger is connected that has booked the output.
 *          \li Is blocking when a debugger is connected, but the previous character
 *             sent has not been transmitted.
 * \param [in]     ch  Character to transmit.
 * \returns            Character to transmit.
 */
static inline T_UINT32 ITMSendChar (T_UINT32 ch)
{
  if (((ITM->TCR & ITM_TCR_ITMENA_MSK) != ZERO) &&      /* ITM enabled */
      ((ITM->TER & ONE               ) != ZERO)   )     /* ITM Port #0 enabled */
  {
    while (ITM->PORT[0U].u32 == ZERO)
    {
      __NOP();
    }
    ITM->PORT[0U].u8 = (T_UINT8)ch;
  }
  return (ch);
}

/*
 * \brief   ITM Receive Character
 * \details Inputs a character via the external variable \ref Itm_rx_buffer.
 * \return             Received character.
 * \return         -1  No character pending.
 */
static inline T_INT32 ITMReceiveChar (void)
{
  T_INT32 charactor = MINUS_ONE;            /* no character available */

  if (Itm_rx_buffer != ITM_RXBUFFER_EMPTY)
  {
    charactor = Itm_rx_buffer;
    Itm_rx_buffer = ITM_RXBUFFER_EMPTY;       /* ready for next character */
  }
  return (charactor);
}

/*
 * \brief   ITM Check Character
 * \details Checks whether a character is pending for reading in the variable \ref Itm_rx_buffer.
 * \return          0  No character available.
 * \return          1  Character available.
 */
static inline T_INT32 ITMCheckChar (void)
{

  if (ITM_RXBUFFER_EMPTY == Itm_rx_buffer)
  {
    return (ZERO);               /* no character available */
  }
  else
  {
    return (ONE);               /*    character available */
  }
}

/*
 * \brief   NVICEnableIRQ
 * \details Sets the priority of an interrupt.
 * \return          None
 */

static inline void NVICEnableIRQ(T_IRQN_TYPE irq_n)
{
  NVIC->ISER[(((T_UINT32)(T_INT32)irq_n) >> FIVE)] = \
            (T_UINT32)(ONE << (((T_UINT32)(T_INT32)irq_n) & HEX_1F));
}

#endif /* _HDULIBCORECM7_H_ */


