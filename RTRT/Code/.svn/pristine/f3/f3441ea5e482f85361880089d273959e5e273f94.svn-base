/*
 ******************************************************************************
 * License Information  :  Howell Instruments, Inc.                           *
 *                         "Licensed Software" and "All rights reserved".     *
 ******************************************************************************
 *  File                : hdudispftextbox.h
 *
 *  Description         : Contains routines for text box draw and updates
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
 *  Portability         : None
 *
 *  Author(s)           : Vinay H
 *
 *  Version History     :
 * <Version No.>     <Author>          <Date>         <Problem Report No.>
 *
 *      1.1          Vinay H         18-Jul-2017             100064
 *      1.2          Shilpa A R      10-Oct-2017             100064
 *      1.3          Gururaj C       21-Jun-2020             100259
 *      1.4          Rona B S        02-Jul-2020             100259
 *      1.5          Dhanalakshmi    12-Sep-2020             100276 
 *
 * Additional References : None
 *
 ******************************************************************************
 */

#ifndef _HDUDISPFTEXTBOX_H_
#define _HDUDISPFTEXTBOX_H_

#include "hdulibbasictypes.h"  /*Contains different font information*/
#include "hdudispfwidgets.h"   /* Contains routines for widget params */
#include "hdudispfbfcfont.h"   /* BitFontCreator (Pro & Grayscale) font header */

#define SIZEOF(x) (sizeof(x)-1)

typedef enum
{
   TEXT_BOX = 0,
   BB_RIGHT,
   BB_BOTTOM,
   LIST_BOX,
   SELECT_BOX,
   BB_CENTER
}  T_ETBOXTYPE;

typedef struct sTextBox *T_PSTEXTBOX;

typedef struct
{
   T_ETBOXTYPE eTBoxType;
   T_INT16        s16ULX;         /* X coordinate of text box center. */
   T_INT16        s16ULY;         /* Y coordinate of text box center. */
   T_INT16        s16PixWidth;    /* Width of text box in characters. */
   T_INT16        s16PixHeight;   /* Height of text box in characters. */
   T_ETXFONT      eTXFont;        /* The font to use in the text box. */
   T_EPENCOLOR eFontColor;        /* The color of the text of the text box. */
   T_EPENCOLOR eBackGroundColor;  /* The color of the background of the text box. */
   T_INT16        s16Margin;      /* Text to frame in Pixels. */
   T_CHAR           *(*fill)(void); /* Function returns a pointer to the text to fill with. */
   T_INT16        s16FrameWidth;  /* The width of the frame in pixels. */
   T_EPENCOLOR eFrameColor;       /* The color of the frame. */
   T_CHAR           *pcTitle;     /* Title for List Box. */
   /* Run time. */
   T_PSTEXTBOX psTextBox;         /* Pointer to the run time structure. */
}  T_STEXTBOXDATA;

typedef struct sTextBox
{
   T_STEXTBOXDATA *pT_STEXTBOXDATA;

   T_INT16              s16LeftMargin;     /* Margin between text box and frame. */
   T_INT16              s16RightMargin;
   T_INT16              s16ToptMargin;
   T_INT16              s16BottomMargin;
   T_INT16              s16DrawX;          /* Cursor location. */
   T_INT16              s16DrawY;
   T_BFC_FONT           *psFont;
   T_INT16              s16FontWidth;
   T_INT16              s16FontHeight;
   T_STATE              eState;    /* Display the text box if "ON". */
   T_BOOL          bFlashing;      /* Force alternation between the text and background colors. */
} T_STEXTBOX;


typedef struct sTextBoxPdi *T_PSTEXTBOXPDI;

typedef struct
{
   T_PARAM_READING      *psParam;   /* Parameter driving the number. */
   T_UINT16   cross_val;
   T_ETBOXTYPE eTBoxType;
   T_INT16        s16ULX;         /* X coordinate of text box center. */
   T_INT16        s16ULY;         /* Y coordinate of text box center. */
   T_INT16        s16PixWidth;    /* Width of text box in characters. */
   T_INT16        s16PixHeight;   /* Height of text box in characters. */
   T_ETXFONT      eTXFont;        /* The font to use in the text box. */
   T_EPENCOLOR eFontColor;        /* The color of the text of the text box. */
   T_EPENCOLOR eBackGroundColor;  /* The color of the background of the text box. */
   T_EPENCOLOR eFlashColor;       /* The color of the background of the text box during flash */
   T_INT16        s16Margin;      /* Text to frame in Pixels. */
   T_CHAR           *(*fill)(void); /* Function returns a pointer to the text to fill with. */
   T_INT16        s16FrameWidth;  /* The width of the frame in pixels. */
   T_EPENCOLOR eFrameColor;       /* The color of the frame. */
   T_CHAR           *pcTitle;     /* Title for List Box. */
   T_SDISREGION      *psDisRegion;  /* Region used for RED X */
   /* Run time. */
   T_PSTEXTBOXPDI psTextBox;         /* Pointer to the run time structure. */
}  T_STEXTBOXPDIDATA;

typedef struct sTextBoxPdi
{
 T_STEXTBOXPDIDATA *pT_STEXTBOXPDIDATA;

   T_INT16              s16LeftMargin;     /* Margin between text box and frame. */
   T_INT16              s16RightMargin;
   T_INT16              s16ToptMargin;
   T_INT16              s16BottomMargin;
   T_INT16              s16DrawX;          /* Cursor location. */
   T_INT16              s16DrawY;
   T_BFC_FONT           *psFont;
   T_INT16              s16FontWidth;
   T_INT16              s16FontHeight;
   T_STATE              eState;    /* Display the text box if "ON". */
   T_BOOL          bFlashing;      /* Force alternation between the text and background colors. */
   T_SPOLY              *psPolyRedX;             /* Polygon to "Red X" the region. */
} T_STEXTBOXPDI;

extern void TextBoxInit(T_STEXTBOXDATA *ps_text_box_data); /* Initialize a text box. */
extern void TextBoxOn(T_STEXTBOXDATA *ps_this_box);        /* Turn a text box on. */
extern void TextBoxOff(T_STEXTBOXDATA *ps_this_box);       /* Turn a text box off. */
extern void TextBoxDraw(void);                             /* Draws the first "ON" text box. */
extern void TextBoxFlash(T_STEXTBOXDATA *ps_this_box);
extern void TextBoxNoFlash(T_STEXTBOXDATA *ps_this_box);
extern void TextBoxClear(T_STEXTBOXPDIDATA *ps_this_box);
extern void TextBoxPdiAllocate(T_STEXTBOXPDIDATA *ps_this_box);
extern void TextBoxPdiDraw(void);
extern T_UINT16 StrLen( T_CHAR *str);

#endif /* _HDUDISPFTEXTBOX_H_ */
