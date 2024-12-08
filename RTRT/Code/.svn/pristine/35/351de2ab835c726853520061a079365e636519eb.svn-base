/*
 ******************************************************************************
 * License Information  :  Howell Instruments, Inc.                           *
 *                         "Licensed Software" and "All rights reserved".     *
 ******************************************************************************
 *  File                : hdudispbappdata.h
 *
 *  Description         : This file contains the appdata structure required for 
 *                        configuration file
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
 *  Author(s)           : Rona B.S
 *
 *  Version History     :
 *
 * <Version No.>     <Author>          <Date>         <Problem Report No.>
 *
 *      1.1          Rona B.S        03-Jul-2020             100259
 *
 * Additional References : None
 *
 *****************************************************************************
 */


#ifndef _HDUDISPBAPPDATA_H_
#define _HDUDISPBAPPDATA_H_  



/* PUBLIC-SCOPE SPECIFICATION */

/* .... Constants ..................*/
#ifndef S32_MAX
#define S32_MAX    ((T_INT32)2147483647)
#endif
#ifndef S32_MIN
#define S32_MIN    ((T_INT32)-2147483647 - 1)
#endif



/* Array max values */

/*
 * These are the maximum allowable items in an array, they are usually
 * used in an array size[VALUE+1] so that the array can hold the maximum
 * value of elements and then the size element as well.
 */

/*This is the length of revision string for the Appdata software part number*/
#define REVNO_DATA_LEN 16

#define APPDATA_LOCATE_IN_FLASH __attribute__ ((section(".flash_data")))
#define APPDATA_LOCATE_IN_FLASH_SUBPART \
    __attribute__ ((section(".flash_subpart_data")))

 /* LCD PIXEL WIDTH            */
#define PANEL_WIDTH             ((T_UINT16)Appdata_appdata_boot->PanelStruct.PanelWidth)
 /* LCD PIXEL HEIGHT           */
#define PANEL_HEIGHT            ((T_UINT16)Appdata_appdata_boot->PanelStruct.PanelHeight)
 /* Horizontal synchronization */
#define PANEL_HSYNC             ((T_UINT16)Appdata_appdata_boot->PanelStruct.PanelHSync)
/* Horizontal back porch      */
#define PANEL_HBP               ((T_UINT16)Appdata_appdata_boot->PanelStruct.PanelHBP)
/* Horizontal front porch     */  
#define PANEL_HFP               ((T_UINT16)Appdata_appdata_boot->PanelStruct.PanelHFP)
 /* Vertical synchronization   */
#define PANEL_VSYNC             ((T_UINT16)Appdata_appdata_boot->PanelStruct.PanelVSync)
/* Vertical back porch        */
#define PANEL_VBP               ((T_UINT16)Appdata_appdata_boot->PanelStruct.PanelVbp)
 /* Vertical front porch       */    
#define PANEL_VFP               ((T_UINT16)Appdata_appdata_boot->PanelStruct.PanelVfp)

#define ORIENTATION             (Appdata_appdata_boot->Orientation)    /* Orientation*/
#define SW_FLAG                 (Appdata_appdata_boot->Flag.SoftwareJumpFlag)    /* SW_FLAG_JUMP*/

#define SDRAM_BASE ((T_UINT32)0xC0000000)
 /* *** CAUTION!  Last 1 Meg of 8 Meg is reserved for frame buffer. */
#define SDRAM_SIZE ((T_UINT32)0x700000)    
#define FB_ADDR ((void *)(SDRAM_BASE+SDRAM_SIZE))
#define FB_BG_ADDR ((void *)((SDRAM_BASE+SDRAM_SIZE+(PANEL_HEIGHT*PANEL_WIDTH))))
#define FB_SIZE (PANEL_WIDTH*PANEL_HEIGHT)


    /*  Set the value of the push button switches.  */
#define FONT                  (T_APPDATA_APPDATA_BOOT->Font)   /* FONT to use */
#define DOWN             ((T_INT16)T_APPDATA_APPDATA_BOOT->DownButtonSel)
#define SELECT            ((T_INT16)T_APPDATA_APPDATA_BOOT->SelectButtonSel)
#define UP_BUTTON             ((T_INT16)T_APPDATA_APPDATA_BOOT->UpButtonSel)


#define PBS1_M          ((T_SINT16)0x01)                /*  Mask for PBS1.      */
#define PBS2_M          ((T_SINT16)0x02)                /*  Mask for PBS2.      */
#define PBS3_M          ((T_SINT16)0x04)                /*  Mask for PBS3.      */
#define PBS4_M          ((T_SINT16)0x08)                /*  Mask for PBS4.      */
#define PBS5_M          ((T_SINT16)0x10)                /*  Mask for PBS5.      */
#define PBS6_M          ((T_SINT16)0x20)                /*  Mask for PBS6.      */
#define PBS7_M          ((T_SINT16)0x40)                /*  Mask for PBS7.      */
#define PBS8_M          ((T_SINT16)0x80)                /*  Mask for PBS8.      */
#define PBS9_M          ((T_SINT16)0x100)               /*  Mask for PBS9.      */
#define PBS10_M         ((T_SINT16)0x200)               /*  Mask for PBS10.     */
#define PBS11_M         ((T_SINT16)0x400)               /*  Mask for PBS11.     */
#define PBS12_M         0x800                          /*  Mask for PBS12.     */
#define PBS13_M         0x1000                         /*  Mask for PBS13.     */
#ifndef PACK_THIS
#define PACK_THIS __attribute__ ((packed))
#endif


typedef enum
{
     FONT_NO_FONT,
	 CONSOLAS24, /*  fontConsolas24hAA4 */
	 CONSOLAS22, /*  fontConsolas22hAA4 */
	 CONSOLAS9
} T_ETXFONT_STYLE;

typedef enum
{
    /** No Active Switches */
    LAND_SCAPE = 0,
    /** Display on Top */
    PORTRAIT = 1

} T_PANEL_ORIENTATION;

typedef enum
{
    SOFTWARE_LOADER = 0,
    MAINTENANCE_SW = 1

}T_SW_JUMP_FLAG;

typedef struct
{
	T_UINT16 DownButton;
	T_UINT16 SelectButton;
	T_UINT16 UpButton;

}T_PBS_TYPE;

/*Software Jump Flag Structure */
typedef struct
{
    /*Software Jump Flag */
	T_SW_JUMP_FLAG SoftwareJumpFlag;

}T_APPDATA_SOFTWARE_FLAG;

/*Panel Settings Structure */
typedef struct
{

	/* LCD PIXEL WIDTH */
	T_UINT16 PanelWidth;
	/* LCD PIXEL HEIGHT */
	T_UINT16 PanelHeight;
	/* Horizontal synchronization */
	T_UINT16 PanelHSync;
	/* Horizontal back porch */
	T_UINT16 PanelHBP;
	/* Horizontal front porch */
	T_UINT16 PanelHFP;
	/* Vertical synchronization  */
	T_UINT16 PanelVSync;
	/* Vertical back porch */
	T_UINT16 PanelVbp;
	/* Vertical front porch */
	T_UINT16 PanelVfp;

}T_APPDATA_PANEL;

/*
 * This structure is defined here and is used to reference a memory location
 * loaded by another program 
 */
 
typedef struct TagAPP_DATA
{
/* NOTE: */

/* 
 * All entries in this structure are allocated within blocks
 * that have a size that is a multiple of 4 bytes.    
 */

/*  
 * RULE: All strings must have a zero as a terminating character
 * meaning that if a string has a size of 16 then the value may
 * only be  15 characters long to leave room for the
 * terminating zero 
 */

    /* ALWAYS LEAVE REVNO AS FIRST ITEM */
    /** PART NUMBER of Application Data */
	T_UINT8 RevNo[REVNO_DATA_LEN + 4];

	/*Panel Settings Structure used by PRIM_APP,MAINT,SWL*/
	T_APPDATA_PANEL  PanelStruct;

	/*Software Jump Flag Structure used by BOOT,MAINT,SWL */
	T_APPDATA_SOFTWARE_FLAG  Flag;

    /*Down button for menu selection*/
	T_UINT16 DownButtonSel;
    /*Select button for menu selection*/
	T_UINT16 SelectButtonSel;
    /*Up button for menu selection*/
	T_UINT16 UpButtonSel;
    /*Fonts option*/
    T_ETXFONT_STYLE  Font;
    /*Orientation of the screen*/
    T_PANEL_ORIENTATION Orientation;

} T_APPDATA_APPDATA_BOOT;

/*  GLOBALS     */
extern T_APPDATA_APPDATA_BOOT *Appdata_appdata_boot;

#endif /* _HDUDISPBAPPDATA_H_ */



