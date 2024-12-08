/*
 ******************************************************************************
 * License Information  :  Howell Instruments, Inc.                           *
 *                         "Licensed Software" and "All rights reserved".     *
 ******************************************************************************
 *  File                : hdudispfarmmath.h
 *
 *  Description         : Contains CMSIS DSP Library routines.
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
 *      1.1          Vinay H         19-Jul-2017             100064
 *      1.2          Rona B.S        10-Oct-2017             100064
 *      1.3          Shruthi M N     15-Oct-2017             100083
 *      1.4          Rona B S        02-Jul-2020             100259
 *
 * Additional References : None
 *
 ******************************************************************************
 */

#ifndef _HDUDISPFARMMATH_H_
#define _HDUDISPFARMMATH_H_

#define __CMSIS_GENERIC         /* disable NVIC and Systick functions */

#include "hdulibbasictypes.h"   /* Standard basic data type definitions */
#include "hdulibcorecm7.h"      /* Cortex-M7 processor and core peripherals */

#undef  __CMSIS_GENERIC         /* enable NVIC and Systick functions */

/* Macros required for reciprocal calculation in Normalized LMS */
#define DELTA_Q31          (0x100U)
#define DELTA_Q15          0x5U
#define INDEX_MASK         0x0000003FU
#define HEX_2000           0x2000U
#define HEX_8000           0x8000U

/*Macros required for SINE and COSINE Fast math approximations */
#define FAST_MATH_TABLE_SIZE  512U
#define FAST_MATH_Q31_SHIFT   (32 - 10)
#define FAST_MATH_Q15_SHIFT   (16 - 10)
#define CONTROLLER_Q31_SHIFT  (32 - 9)
#define TABLE_SIZE  256U
#define TABLE_SPACING_Q31     0x400000U
#define TABLE_SPACING_Q15     0x80U

/* Macros required for SINE and COSINE Controller functions */
/* 1.31(q31) Fixed value of 2/360 */
/* -1 to +1 is divided into 360 values so total spacing is (2/360) */
#define INPUT_SPACING         0xB60B61U

/* Macro for Unaligned Support */
#define ALIGN4

#define BIT_1_TO_8         0x000000FFUL
#define BIT_9_TO_16        0x0000FF00UL
#define BIT_17_TO_24       0x00FF0000UL
/* Updated as per PR100083*/
#define BIT_25_TO_32       0xFF000000UL
#define BIT_1_TO_31        0x7FFFFFFFUL
#define BIT_1_TO_15        0x7FFFUL
#define BIT_32             0x80000000LL

/*8-bit fractional data type in 1.7 format. */
typedef T_INT8 T_Q7;

/* 16-bit fractional data type in 1.15 format. */
typedef T_INT16 T_Q15;

/* 32-bit fractional data type in 1.31 format. */
typedef T_INT32 T_Q31;

/* 64-bit fractional data type in 1.63 format. */
typedef T_INT64 T_Q63;

/* 32-bit floating-point type definition. */
typedef float T_FLOAT32;

/* 64-bit floating-point type definition. */
typedef double T_FLOAT64;

/*definition to read/write two 16 bit values. */
#define __SIMD32_TYPE T_INT32
#define CMSIS_UNUSED __attribute__((unused))


#define __SIMD32(addr)  (*(__SIMD32_TYPE **) & (addr))
#define __SIMD32_CONST(addr)  ((__SIMD32_TYPE *)(addr))
#define _SIMD32_OFFSET(addr)  (*(__SIMD32_TYPE *)  (addr))
#define __SIMD64(addr)  (*(T_INT64 **) & (addr))

/*Instance structure for the floating-point CFFT/CIFFT function. */

typedef struct
{
  T_UINT16 fftLen;                   /**< length of the FFT. */
  const T_FLOAT32 *pTwiddle;         /**< points to the Twiddle factor table. */
  const T_UINT16 *pBitRevTable;      /**< points to the bit reversal table. */
  T_UINT16 bitRevLength;             /**< bit reversal table length. */
}  T_ARM_CFFT_INSTANCE_F32;

/* Instance structure for the fixed-point CFFT/CIFFT function. */

typedef struct
{
  T_UINT16 fftLen;                   /**< length of the FFT. */
  const T_Q31 *pTwiddle;             /**< points to the Twiddle factor table. */
  const T_UINT16 *pBitRevTable;      /**< points to the bit reversal table. */
  T_UINT16 bitRevLength;             /**< bit reversal table length. */
} T_ARM_CFFT_INSTANCE_Q31;


/*  Instance structure for the fixed-point CFFT/CIFFT function. */
typedef struct
{
  T_UINT16 fftLen;                   /**< length of the FFT. */
  const T_Q15 *pTwiddle;             /**< points to the Twiddle factor table. */
  const T_UINT16 *pBitRevTable;      /**< points to the bit reversal table. */
  T_UINT16 bitRevLength;             /**< bit reversal table length. */
} T_ARM_CFFT_INSTANCE_Q15;

/*
 * Fast approximation to the trigonometric cosine function for Q15 data.
 * param[in] - x Scaled input value in radians.
 * return - cos(x).
 */
extern T_Q15 ArmCosQ15(T_Q15 x);

/*
 * Fast approximation to the trigonometric sine function for Q15 data.
 * param[in] - x Scaled input value in radians.
 * return - sin(x).
 */
extern T_Q15 ArmSinQ15(T_Q15 x);

#define LOW_OPTIMIZATION_ENTER __attribute__(( optimize("-O1") ))
#define LOW_OPTIMIZATION_EXIT
#define IAR_ONLY_LOW_OPTIMIZATION_ENTER
#define IAR_ONLY_LOW_OPTIMIZATION_EXIT

#endif /* _ARM_MATH_H */
