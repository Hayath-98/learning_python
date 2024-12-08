/*
 ******************************************************************************
 * License Information  :  Howell Instruments, Inc.                           *
 *                         "Licensed Software" and "All rights reserved".     *
 ******************************************************************************
 *  File                : hdulibcmsisgcc.h
 *
 *  Description         : CMSIS Cortex-M7 Core Function/Instruction Header File
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
 *      1.2          Rona B.S        02-Sep-2017            100028
 *      1.3          Shilpa A R      07-Nov-2017            100161
 *      1.4          Rona B.S        12-Sep-2020            100276 
 *
 * Additional References : None
 *
 ******************************************************************************
 */

#ifndef _HDULIBCMSISGCC_H_
#define _HDULIBCMSISGCC_H_

#include "hdulibcorecm7.h"    /* Cortex-M7 processor and core peripherals */
#include "hdulibbasictypes.h" /* Define standard types */

#define __ASM            __asm             /* asm keyword for GNU Compiler */
#define __INLINE         inline            /* inline keyword for GNU Compiler */
#define __STATIC_INLINE  static inline
#define __CORTEX_M                (0x07U)
#define THREE_HUNDRED               300

/* ###########################  Core Function Access  ########################### */

/*Enable IRQ Interrupts */
/*
 * Enables IRQ interrupts by clearing the I-bit in the CPSR.
 * Can only be executed in Privileged modes.
 */
__attribute__( ( always_inline ) ) __STATIC_INLINE void __enable_irq(void)
{
  __ASM volatile ("cpsie i" : : : "memory");
}

/*Disable IRQ Interrupts */
/*
 *Disables IRQ interrupts by setting the I-bit in the CPSR.
 * Can only be executed in Privileged modes.
 */
__attribute__( ( always_inline ) ) __STATIC_INLINE void __disable_irq(void)
{
  __ASM volatile ("cpsid i" : : : "memory");
}

/*
 * \brief   Get Control Register
 * \details Returns the content of the Control Register.
 * \return  Control Register value
 */
__attribute__( ( always_inline ) ) __STATIC_INLINE T_UINT32 __get_CONTROL(void)
{
  T_UINT32 result = ZERO;

  __ASM volatile ("MRS %0, control" : "=r" (result) );
  return(result);
}

/*
 * \brief   Set Control Register
 * \details Writes the given value to the Control Register.
 * \param [in]    control - Set the value to Control Register
 */
__attribute__( ( always_inline ) ) __STATIC_INLINE void __set_CONTROL(T_UINT32 control)
{
  __ASM volatile ("MSR control, %0" : : "r" (control) : "memory");
}


/*
 * \brief   Get IPSR Register
 * \details Returns the content of the IPSR Register.
 * \return               IPSR Register value
 */
__attribute__( ( always_inline ) ) __STATIC_INLINE T_UINT32 __get_IPSR(void)
{
  T_UINT32 result = ZERO;

  __ASM volatile ("MRS %0, ipsr" : "=r" (result) );
  return(result);
}

/*
 * \brief   Get APSR Register
 * \details Returns the content of the APSR Register.
 * \return               APSR Register value
 */
__attribute__( ( always_inline ) ) __STATIC_INLINE T_UINT32 __get_APSR(void)
{
  T_UINT32 result = ZERO;

  __ASM volatile ("MRS %0, apsr" : "=r" (result) );
  return(result);
}

/*
 * \brief   Get xPSR Register
 * \details Returns the content of the xPSR Register.
 *   \return               xPSR Register value
 */
__attribute__( ( always_inline ) ) __STATIC_INLINE T_UINT32 __get_xPSR(void)
{
  T_UINT32 result = ZERO;

  __ASM volatile ("MRS %0, xpsr" : "=r" (result) );
  return(result);
}

/*
 * \brief   Get Process Stack Pointer
 * \details Returns the current value of the Process Stack Pointer (PSP).
 * \return               PSP Register value
 */
__attribute__( ( always_inline ) ) __STATIC_INLINE T_UINT32 __get_PSP(void)
{
  register T_UINT32 result = ZERO;

  __ASM volatile ("MRS %0, psp\n"  : "=r" (result) );
  return(result);
}

/*
 * \brief   Set Process Stack Pointer
 * \details Assigns the given value to the Process Stack Pointer (PSP).
 * \param [in]    top_of_proc_stack  Process Stack Pointer value to set
 */
__attribute__( ( always_inline ) ) __STATIC_INLINE void __set_PSP(T_UINT32 top_of_proc_stack)
{
  __ASM volatile ("MSR psp, %0\n" : : "r" (top_of_proc_stack) : "sp");
}

/*
 * \brief   Get Main Stack Pointer
 * \details Returns the current value of the Main Stack Pointer (MSP).
 * \return               MSP Register value
 */
__attribute__( ( always_inline ) ) __STATIC_INLINE T_UINT32 __get_MSP(void)
{
  register T_UINT32 result = ZERO;

  __ASM volatile ("MRS %0, msp\n" : "=r" (result) );
  return(result);
}

/*
 * \brief   Set Main Stack Pointer
 * \details Assigns the given value to the Main Stack Pointer (MSP).
 *   \param [in]    top_of_main_stack  Main Stack Pointer value to set
 */
__attribute__( ( always_inline ) ) __STATIC_INLINE void __set_MSP(T_UINT32 top_of_main_stack)
{
  __ASM volatile ("MSR msp, %0\n" : : "r" (top_of_main_stack) : "sp");
}

/*
 * \brief   Get Priority Mask
 * \details Returns the current state of the priority mask bit from the Priority Mask Register.
 * \return               Priority Mask value
 */
__attribute__( ( always_inline ) ) __STATIC_INLINE T_UINT32 __get_PRIMASK(void)
{
  T_UINT32 result = ZERO;

  __ASM volatile ("MRS %0, primask" : "=r" (result) );
  return(result);
}

/*
 * \brief   Set Priority Mask
 * \details Assigns the given value to the Priority Mask Register.
 * \param [in]    pri_mask  Priority Mask
 */
__attribute__( ( always_inline ) ) __STATIC_INLINE void __set_PRIMASK(T_UINT32 pri_mask)
{
  __ASM volatile ("MSR primask, %0" : : "r" (pri_mask) : "memory");
}


#if       (__CORTEX_M >= THREE)

/*
 * \brief   Enable FIQ
 * \details Enables FIQ interrupts by clearing the F-bit in the CPSR.
 *          Can only be executed in Privileged modes.
 */
__attribute__( ( always_inline ) ) __STATIC_INLINE void __enable_fault_irq(void)
{
  __ASM volatile ("cpsie f" : : : "memory");
}

/*
 * \brief   Disable FIQ
 * \details Disables FIQ interrupts by setting the F-bit in the CPSR.
 *          Can only be executed in Privileged modes.
 */
__attribute__( ( always_inline ) ) __STATIC_INLINE void __disable_fault_irq(void)
{
  __ASM volatile ("cpsid f" : : : "memory");
}

/*
 * \brief   Get Base Priority Mask register
 * \details Returns the current value of the Base Priority Mask register.
 * \return               Base Priority Mask register value
 */
__attribute__( ( always_inline ) ) __STATIC_INLINE T_UINT32 __get_BASEPRI(void)
{
  T_UINT32 result = ZERO;

  __ASM volatile ("MRS %0, basepri" : "=r" (result) );
  return(result);
}

/*
 * \brief   Set Base Priority Mask register
 * \details Assigns the given value to the Base Priority Mask register.
 * \param [in]    value  Base Priority Mask register to set
 */
__attribute__( ( always_inline ) ) __STATIC_INLINE void __set_BASEPRI(T_UINT32 value)
{
  __ASM volatile ("MSR basepri, %0" : : "r" (value) : "memory");
}

/*
 * \brief   Set Base Priority Mask register with condition
 * \details Assigns the given value to the Base Priority Mask register only if BASEPRI masking is
 *  disabled, or the new value increases the BASEPRI priority level.
 * \param [in]    value  Base Priority Mask register value to set
 */
__attribute__( ( always_inline ) ) __STATIC_INLINE void __set_BASEPRI_MAX(T_UINT32 value)
{
  __ASM volatile ("MSR basepri_max, %0" : : "r" (value) : "memory");
}

/*
 * \brief   Get Fault Mask
 * \details Returns the current value of the Fault Mask register.
 * \return               Fault Mask register value
 */
__attribute__( ( always_inline ) ) __STATIC_INLINE T_UINT32 __get_FAULTMASK(void)
{
  T_UINT32 result = ZERO;

  __ASM volatile ("MRS %0, faultmask" : "=r" (result) );
  return(result);
}

/*
 * \brief   Set Fault Mask
 * \details Assigns the given value to the Fault Mask register.
 * \param [in]    fault_mask  Fault Mask value to set
 */
__attribute__( ( always_inline ) ) __STATIC_INLINE void __set_FAULTMASK(T_UINT32 fault_mask)
{
  __ASM volatile ("MSR faultmask, %0" : : "r" (fault_mask) : "memory");
}

#endif /* (__CORTEX_M >= THREE) */


#if       (__CORTEX_M == FOUR) || (__CORTEX_M == SEVEN)

/*
 * \brief   Get FPSCR
 * \details Returns the current value of the Floating Point Status/Control register.
 * \return               Floating Point Status/Control register value
 */
__attribute__( ( always_inline ) ) __STATIC_INLINE T_UINT32 __get_FPSCR(void)
{
   return(0);
}

#endif /* (__CORTEX_M == FOUR) || (__CORTEX_M == SEVEN) */

/* ##########################  Core Instruction Access  ######################### */

/*
 * \defgroup CMSIS_Core_InstructionInterface CMSIS Core Instruction Interface
 * Access to dedicated instructions
 */

/*
 * Define macros for porting to both thumb1 and thumb2.
 * For thumb1, use low register (r0-r7), specified by constraint "l"
 * Otherwise, use general registers, specified by constraint "r"
 */
#define __CMSIS_GCC_OUT_REG(r) "=r" (r)
#define __CMSIS_GCC_USE_REG(r) "r" (r)

/*
 * \brief   Wait For Interrupt
 * \details Wait For Interrupt is a hint instruction that suspends execution until
 * one of a number of events occurs.
 */
__attribute__((always_inline)) __STATIC_INLINE void __WFI(void)
{
  __ASM volatile ("wfi");
}

/*
 * \brief   Wait For Event
 * \details Wait For Event is a hint instruction that permits the processor to enter
 *   a low-power state until one of a number of events occurs.
 */
__attribute__((always_inline)) __STATIC_INLINE void __WFE(void)
{
  __ASM volatile ("wfe");
}

/*
 * \brief   Send Event
 * \details Send Event is a hint instruction. It causes an event to be signaled to the CPU.
 */
__attribute__((always_inline)) __STATIC_INLINE void __SEV(void)
{
  __ASM volatile ("sev");
}

/*
 * \brief   Data Memory Barrier
 * \details Ensures the apparent order of the explicit memory operations before
 *          and after the instruction, without ensuring their completion.
 */
__attribute__((always_inline)) __STATIC_INLINE void __DMB(void)
{
  __ASM volatile ("dmb 0xF":::"memory");
}

/*
 * \brief   Reverse byte order (32 bit)
 * \details Reverses the byte order in integer value.
 * \param [in]    value  Value to reverse
 * \return               Reversed value
 */
__attribute__((always_inline)) __STATIC_INLINE T_UINT32 __REV(T_UINT32 value)
{
#if (__GNUC__ > FOUR) || (__GNUC__ == FOUR && __GNUC_MINOR__ >= FIVE)
  return __builtin_bswap32(value);
#else
  T_UINT32 result = ZERO;

  __ASM volatile ("rev %0, %1" : __CMSIS_GCC_OUT_REG (result) : __CMSIS_GCC_USE_REG (value) );
  return(result);
#endif
}

/*
 * \brief   Reverse byte order (16 bit)
 * \details Reverses the byte order in two unsigned short values.
 * \param [in]    value  Value to reverse
 * \return               Reversed value
 */
__attribute__((always_inline)) __STATIC_INLINE T_UINT32 __REV16(T_UINT32 value)
{
  T_UINT32 result = ZERO;

  __ASM volatile ("rev16 %0, %1" : __CMSIS_GCC_OUT_REG (result) : __CMSIS_GCC_USE_REG (value) );
  return(result);
}

/*
 * \brief   Reverse byte order in signed short value
 * \details Reverses the byte order in a signed short value with sign extension to integer.
 * \param [in]    value  Value to reverse
 * \return               Reversed value
 */
__attribute__((always_inline)) __STATIC_INLINE T_INT32 __REVSH(T_INT32 value)
{
  T_INT32 result = ZERO;

  __ASM volatile ("revsh %0, %1" : __CMSIS_GCC_OUT_REG (result) : __CMSIS_GCC_USE_REG (value) );
  return(result);
}

/*
 * \brief   Rotate Right in unsigned value (32 bit)
 * \details Rotate Right (immediate) provides the value of the contents of a register rotated
 * by a variable number of bits.
 * \param [in]    value  Value to rotate
 * \param [in]    value  Number of Bits to rotate
 * \return               Rotated value
 */
__attribute__((always_inline)) __STATIC_INLINE T_UINT32 __ROR(T_UINT32 op1, T_UINT32 op2)
{
  return (op1 >> op2) | (op1 << (THIRTY_TWO - op2));
}

/*
 * \brief   Breakpoint
 * \details Causes the processor to enter Debug state.
 *          Debug tools can use this to investigate system state when the instruction
 * at a particular address is reached.
 * \param [in]    value  is ignored by the processor.
 *                If required, a debugger can use it to store additional information
 *                about the breakpoint.
 */
#define __BKPT(value)                       (__ASM volatile ("bkpt "#value))

/*Updated as per PR100161*/
/*
 * \brief   count the leading zero
 * \param [in]    num  .
 * \return        returns the count of leading zeros .
 */
__attribute__((always_inline)) __STATIC_INLINE T_UINT32 COUNT_LEADING_ZEROS(T_UINT32 num)
{
   T_INT32 index = 0;
   T_UINT32 cal_num = 0;
   T_UINT32 count =0 ;

   for (index = 31; index >= 0; index --)
   {
      cal_num = (num >> index) & 1;
      if (0 == cal_num)
      {
      count = count + 1;
      }
      else
      {
      break;
      }
   }
  return count;
}

/*
 * \brief   Reverse bit order of value
 * \details Reverses the bit order of the given value.
 * \param [in]    value  Value to reverse
 * \return               Reversed value
 */
__attribute__((always_inline)) __STATIC_INLINE T_UINT32 __RBIT(T_UINT32 value)
{
  T_UINT32 result = ZERO;

#if       (__CORTEX_M >= THREE) || (__CORTEX_SC >= THREE_HUNDRED)
   __ASM volatile ("rbit %0, %1" : "=r" (result) : "r" (value) );
#else
  T_INT32 s = FOUR /*sizeof(v)*/ * EIGHT - ONE; /* extra shift needed at end */

  result = value;                      /* r will be reversed bits of v; first get LSB of v */
  for (value >>= ONE; value; value >>= ONE)
  {
    result <<= ONE;
    result |= value & ONE;
    s--;
  }
  result <<= s;                        /* shift when v's highest bits are zero */
#endif
  return(result);
}

#endif
