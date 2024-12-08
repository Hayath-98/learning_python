/*
 ******************************************************************************
 * License Information  :  Howell Instruments, Inc.                           *
 *                         "Licensed Software" and "All rights reserved".     *
 ******************************************************************************
 *  File                : H108E-133.ld
 *
 *  Description         : This is the Linker Definition file for Display flight software.                 
 *
 *  Compiler            : GNU gcc(GNU Tools for ARM Embedded Processors) version 5.4.1 20160919
 *
 *  Compiler options    : As per section 10.3.3 of Software Development Plan (HDU-001-002).
 *
 *  Pragma              : None
 *
 *  H/W platform        : ARM Cortex-M4 (STM32F767)
 *
 *  Portability         : None
 *
 *  Author(s)           : Shilpa A R
 *
 *  Version History     :
 * <Version No.>     <Author>             <Date>         <Problem Report No.>
 *      1.1          Shilpa A R         31-Aug-2017            -
 *      1.2          Vinay H            09-Oct-2017          100064 
 *      1.3          Rona B.S           24-Jul-2020          100259 
 *      1.4          Rona B.S           05-Aug-2020          100270 
 *      1.5          Dhanalakshmi D     09-Oct-2020          100288 
 *
 * Additional References           : None
 *
 ******************************************************************************
 */

/* Entry Point */
ENTRY(ResetHandler)

/* Highest address of the user mode stack */
_estack = 0x2007D000;    /* end of RAM */

_Min_Heap_Size = 0;      /* required amount of heap  */
_Min_Stack_Size = 0x800; /* required amount of stack */

/* Memories definition */
MEMORY
{
  RAM (xrw)    : ORIGIN = 0x20000000, LENGTH = 496K
  RAM2(xrw)    : ORIGIN = 0x2007C000, LENGTH = 4K 
  ROM (rx)     : ORIGIN = 0x80C0000, LENGTH = 0xBFFEC
  ROM2 (rx)    : ORIGIN = 0x0817FFEC, LENGTH = 0X014
  SDRAM(XRW)   : ORIGIN = 0xC0000000, LENGTH = 24M  
  SDRAM2(XRW)   : ORIGIN =0xC1800000, LENGTH = 8M
}

/* Sections */
SECTIONS
{
  /* The startup code into ROM memory */
  .isr_vector :
  {
    . = ALIGN(4);
    KEEP(*(.isr_vector)) /* Startup code */
    . = ALIGN(4);
  } >ROM

  /* The program code and other data into ROM memory */
  .text :
  {
    . = ALIGN(4);
    *(.text)           /* .text sections (code) */
    *(.text*)          /* .text* sections (code) */
    *(.glue_7)         /* glue arm to thumb code */
    *(.glue_7t)        /* glue thumb to arm code */
    *(.eh_frame)

    KEEP (*(.init))
    KEEP (*(.fini))

    . = ALIGN(4);
    _etext = .;        /* define a global symbols at end of code */
  } >ROM

  /* Constant data into ROM memory*/
  .rodata :
  {
    . = ALIGN(4);
    *(.rodata)         /* .rodata sections (constants, strings, etc.) */
    *(.rodata*)        /* .rodata* sections (constants, strings, etc.) */
    . = ALIGN(4);
       _erodata = .;        /* define a global symbols at end of const */
  } >ROM

  .ARM.extab   : { 
   . = ALIGN(4);
   *(.ARM.extab* .gnu.linkonce.armextab.*)
   . = ALIGN(4);
  } >ROM
  
  .ARM : {
    . = ALIGN(4);
    __exidx_start = .;
    *(.ARM.exidx*)
    __exidx_end = .;
    . = ALIGN(4);
  } >ROM

  .preinit_array     :
  {
    . = ALIGN(4);
    PROVIDE_HIDDEN (__preinit_array_start = .);
    KEEP (*(.preinit_array*))
    PROVIDE_HIDDEN (__preinit_array_end = .);
    . = ALIGN(4);
  } >ROM
  
  .init_array :
  {
    . = ALIGN(4);
    PROVIDE_HIDDEN (__init_array_start = .);
    KEEP (*(SORT(.init_array.*)))
    KEEP (*(.init_array*))
    PROVIDE_HIDDEN (__init_array_end = .);
    . = ALIGN(4);
  } >ROM
  
  .fini_array :
  {
    . = ALIGN(4);
    PROVIDE_HIDDEN (__fini_array_start = .);
    KEEP (*(SORT(.fini_array.*)))
    KEEP (*(.fini_array*))
    PROVIDE_HIDDEN (__fini_array_end = .);
    . = ALIGN(4);
  } >ROM

  /* Used by the startup to initialize data */
  _sidata = LOADADDR(.data);

  /* Initialized data sections into RAM memory */
  .data : 
  {
    . = ALIGN(4);
    _sdata = .;        /* create a global symbol at data start */
    *(.data)           /* .data sections */
    *(.data*)          /* .data* sections */

    . = ALIGN(4);
    _edata = .;        /* define a global symbol at data end */
  } >RAM AT> ROM

  
  /* Uninitialized data section into RAM memory */
  . = ALIGN(4);
  .bss :
  {
    /* This is used by the startup in order to initialize the .bss secion */
    _sbss = .;         /* define a global symbol at bss start */
    __bss_start__ = _sbss;
    *(.bss)
    *(.bss*)
    *(COMMON)

    . = ALIGN(4);
    _ebss = .;         /* define a global symbol at bss end */
    __bss_end__ = _ebss;
  } >RAM
  
  
  .ram_test(NOLOAD) :
    {
        _ram_test_start = .;
        *(.ram_test*)
        . = ALIGN(4);
        _ram_test_end = .;
    } > RAM2
    
    .sdram_test(NOLOAD) :
    {
        _sdram_test_start = .;
        *(.sdram_test*)
        . = ALIGN(4);
        _sdram_test_end = .;
    } > SDRAM
    
    .sdram_var(NOLOAD) :
    {
        _sdram_var_start = .;
        *(.sdram_var*)
        . = ALIGN(4);
        _sdram_var_end = .;
    } > SDRAM2

  /* User_heap_stack section, used to check that there is enough RAM left */
  ._user_heap_stack :
  {
    . = ALIGN(8);
    PROVIDE ( end = . );
    PROVIDE ( _end = . );
    . = . + _Min_Heap_Size;
    . = . + _Min_Stack_Size;
    . = ALIGN(8);
  } >RAM

     .id_storage :
   {
      start_id_storage = .;
      *(.id_storage*)
      end_id_storage = .;
   } >ROM2

  /* Remove information from the compiler libraries */
  /DISCARD/ :
  {
    libc.a ( * )
    libm.a ( * )
    libgcc.a ( * )
  }

  .ARM.attributes 0 : { *(.ARM.attributes) }
}
