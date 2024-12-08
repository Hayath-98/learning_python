/*
 ******************************************************************************
 * License Information  :  Howell Instruments, Inc.                           *
 *                         "Licensed Software" and "All rights reserved".     *
 ******************************************************************************
 *  File                : H108E-132.ld
 *
 *  Description         : This is the Linker Definition file for HDU Boot Software.
 *
 *  Compiler            : GNU gcc(GNU Tools for ARM Embedded Processors) version 5.4.1 20160919
 *
 *  Compiler options    : As per section 10.3.3 of Software Development Plan (HDU-001-002).
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
 * <Version No.>     <Author>          <Date>         <Problem Report No.>
 *
 *      1.1          Shilpa A R       31-Aug-2017             -
 *      1.2          Rajalakshmi S    01-Sep-2017          100028
 *
 * Additional References : None
 *
 ******************************************************************************
 */

/* Entry Point */
ENTRY(ResetHandler)

/* Highest address of the user mode stack */
_estack = 0x20050000;    /* end of 320KB RAM */

/* Generate a link error if heap and stack don't fit into RAM */
_Min_Heap_Size = 0x200;      /* required amount of heap  */
_Min_Stack_Size = 0x400; /* required amount of stack */

/* Specify the memory areas */

MEMORY
{
FLASH_BOOT (rx)      : ORIGIN = 0x8000000, LENGTH = 0XFFEC
FLASH_APP (rx)		 : ORIGIN = 0x8080000, LENGTH = 512K
RAM (xrw)            : ORIGIN = 0x20000000, LENGTH = 256K
FLASH2 (rx)          : ORIGIN = 0x800FFEC, LENGTH = 0X014
}

/* Define output sections */
SECTIONS
{

   .id_storage :
   {
	 start_id_storage = .;
	 *(.id_storage*)
	 end_id_storage = .;
	} > FLASH2
    
  /* The startup code goes first into FLASH_BOOT */
  .isr_vector :
  {
    . = ALIGN(4);
    KEEP(*(.isr_vector)) /* Startup code */
    . = ALIGN(4);
  } >FLASH_BOOT

  /* The program code and other data goes into FLASH_BOOT */
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
  } >FLASH_BOOT

  /* Constant data goes into FLASH_BOOT */
  .rodata :
  {
    . = ALIGN(4);
    *(.rodata)         /* .rodata sections (constants, strings, etc.) */
    *(.rodata*)        /* .rodata* sections (constants, strings, etc.) */
    . = ALIGN(4);
  } >FLASH_BOOT

  .ARM.extab   : { *(.ARM.extab* .gnu.linkonce.armextab.*) } >FLASH_BOOT
  .ARM : {
    __exidx_start = .;
    *(.ARM.exidx*)
    __exidx_end = .;
  } >FLASH_BOOT

  .preinit_array     :
  {
    PROVIDE_HIDDEN (__preinit_array_start = .);  /*not to eliminate __preinit_array_start section*/
    KEEP (*(.preinit_array*))
    PROVIDE_HIDDEN (__preinit_array_end = .);
  } >FLASH_BOOT
  
  .init_array :
  {
    PROVIDE_HIDDEN (__init_array_start = .);	 /*not to eliminate __init_array_start section*/
    KEEP (*(SORT(.init_array.*)))
    KEEP (*(.init_array*))
    PROVIDE_HIDDEN (__init_array_end = .);
  } >FLASH_BOOT
  .fini_array :
  {
    PROVIDE_HIDDEN (__fini_array_start = .);	/*not to eliminate __finiinit_array_start section*/
    KEEP (*(SORT(.fini_array.*)))
    KEEP (*(.fini_array*))
    PROVIDE_HIDDEN (__fini_array_end = .);
  } >FLASH_BOOT

  /* used by the startup to initialize data */
  _sidata = LOADADDR(.data);

  /* Initialized data sections goes into RAM, load LMA copy after code */
  .data : 
  {
    . = ALIGN(4);
    _sdata = .;        /* create a global symbol at data start */
    *(.data)           /* .data sections */
    *(.data*)          /* .data* sections */

    . = ALIGN(4);
    _edata = .;        /* define a global symbol at data end */
  } >RAM AT> FLASH_BOOT

  
  /* Uninitialized data section */
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

  

  /* Remove information from the standard libraries */
  /DISCARD/ :
  {
    libc.a ( * )
    libm.a ( * )
    libgcc.a ( * )
  }

  .ARM.attributes 0 : { *(.ARM.attributes) }
}


