/*
 ******************************************************************************
 * License Information  :  Howell Instruments, Inc.                           *
 *                         "Licensed Software" and "All rights reserved".     *
 ******************************************************************************
 *  File                : hdudispfnumbox.c
 *
 *  Description         : This file contains the routines which maintain the
 *                                  "Real Time" Number box of the foreground display.
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
 *      1.1          Vinay H         18-Jul-2017             100064
 *      1.2          Shilpa A R      09-Oct-2017             100064
 *      1.3          Shruthi M N     15-Oct-2017             100083
 *      1.4          Shruthi M N     30-Oct-2017             100104
 *      1.5          Rona B S        04-Nov-2017             100146
 *      1.6          Shruthi M N     07-Nov-2017             100161
 *      1.7          Chaithra J      21-Jun-2020             100259
 *      1.8          Rona B S        02-Jul-2020             100259
 *      1.9          Dhanalakshmi    12-Sep-2020             100276 
 *      1.10         Dhanalakshmi    28-Sep-2020             100285  
 *
 * Additional References : None
 *
 ******************************************************************************
 */
#include "hdudispfpolygon1.h"  /*provides routines for "scan line" method polygon fill.*/
#include "hdudispfrterror.h"        /*provides stub routine for run time errors.*/
#include "hdudispftext.h"     /*  Routines which maintain text display and updates */
#include "hdudispfconfig.h"     /* contains page and color config information */
#include "hdudispfnumbox.h"     /*Numbox routines*/
#include "hdulibbasictypes.h"   /* Standard basic data type definitions */
#include "hdudispfpdidata.h" /* provides pdi declarations */
#include "hdudispffonts.h"   /*Decalarations for font functionality */

/* Statically allocate pool of number boxes.    */
static T_SNUMBOX As_num_box[MAX_NUMBOX] = {0};
static T_UINT16   U16_num_box_installed = 0;

/*
 *
 * Function                : NumboxAllocat
 *
 * Description             : The function allocates number box structure for
 *                           the new strings to be displayed.
 *
 * Formal parameter(s)     : T_SNUMBOXDEF *ps_num_box_def - OUT Pointer to the number box structure
 *
 * Return Value            : None
 *
 * Assumption              : None
 *
 */
void NumboxAllocat(T_SNUMBOXDEF *ps_num_box_def)
{
   T_PSNUMBOX ps_num_box = {0};

   static T_CHAR param_message[] = "Too many number boxes.";
   T_CHAR file_name[] = __FILE__;

   /*hdudispfnumbox-NumboxAllocat-DB-LLR-001*/
   /* Trap for over allocated. */
   if(MAX_NUMBOX == U16_num_box_installed)
   {
      RterrWidget((T_CHAR *)&file_name,__LINE__, (T_CHAR *) &param_message);
      ps_num_box_def->psNumBox = (T_PSNUMBOX *)ZERO;
      return;
   }
   else
   {
      ;/*Do Nothing*/
   }
   /*hdudispfnumbox-NumboxAllocat-DB-LLR-002*/
   if(((T_ETXFONT)E_TINY_FONT != ps_num_box_def->eFont) &&
	  ((T_ETXFONT)E_SMALL_FONT != ps_num_box_def->eFont) &&
	  ((T_ETXFONT)E_NORMAL_FONT != ps_num_box_def->eFont) &&
	  ((T_ETXFONT)E_LARGE_FONT != ps_num_box_def->eFont) &&
	  ((T_ETXFONT)E_BEZEL_FONT != ps_num_box_def->eFont))
   {
	   ps_num_box_def->eFont = (T_ETXFONT)E_NO_FONT;
   }
    else
	{
	   ;  /* Do nothing */
	}

   if(ZERO == ps_num_box_def->u16Format)
   {
	   ps_num_box_def->u16Format = NB_DFT_FORMAT ;
   }
   else
   {
	   ;
   }
   /* Allocate object. */
   ps_num_box = &(As_num_box[U16_num_box_installed]);

   /* Link owner to object. */
   ps_num_box->psNumBoxDef = ps_num_box_def;

   /* Link object to  ,Link owner to object. */
   ps_num_box_def->psNumBox = (T_PSNUMBOX *)ps_num_box;

   /* Updated as per PR100083*/
   /* Initialize the digital reading. */
   ps_num_box->sWidgetParm.s32DisDig = ps_num_box_def->psParam->r;
   ps_num_box->sWidgetParm.s32Dig = ps_num_box_def->psParam->r;

   /* Initialize the scaler reading. */
   ps_num_box->sWidgetParm.s32Scaler = ps_num_box_def->psParam->r;
   ps_num_box->sWidgetParm.s32ScalerStep = ((T_INT32)ZERO);

   /*hdudispfnumbox-NumboxAllocat-DB-LLR-003*/
   if(BinasGetWidth(ps_num_box_def->u16Format)&&(ps_num_box_def->eFont))
   {
      /* Initialize the ascii reading. */
      BinasByteFormatInfoBE(&(ps_num_box->sWidgetParm.s32DisDig), ps_num_box_def->u16Format,
                                       (T_INT8* )ps_num_box->acDigText);

      /* Initialize the digital display. */
      TextAllocat((T_PTEXT *)&(ps_num_box->sWidgetParm.pText)
            ,(T_UINT8 *)ps_num_box->acDigText
            ,(T_UINT16)(ps_num_box_def->sCenter.u16X0)/MAG_FACTOR
            ,(T_UINT16)(ps_num_box_def->sCenter.u16Y0)/MAG_FACTOR
            ,ALIGN_CENTER
            ,ps_num_box_def->eFont
            ,WHITE
            ,V_NORMAL
            ,TX_NO_FLASH
               );
   }
   else
   {
      ;/*Do nothing*/
   }
   /*hdudispfnumbox-NumboxAllocat-DB-LLR-004*/
   /* Inc Number Boxes Installed. */
  U16_num_box_installed =(T_UINT16) (U16_num_box_installed + ONE);
}

/*
 *
 * Function                : NumboxUpdate
 *
 * Description             : Update all numboxes
 *
 * Formal parameter(s)     : None
 *
 * Return Value            : None
 *
 * Assumption              : None
 *
 */
void NumboxUpdate(void)
{
   T_UINT16    u16_num_cntr = 0;
   T_PSNUMBOX  ps_num_box = {0};
   T_UINT16    u16_field_width = 0;
   /* Updated as per PR100083*/
   T_UINT16    num_dec=0;

   /*hdudispfnumbox-NumboxUpdate-DB-LLR-001*/
   /* Update readings used for digital and analog  updates. */
   for (u16_num_cntr=0; u16_num_cntr<U16_num_box_installed; u16_num_cntr++)
   {
      ps_num_box = &As_num_box[u16_num_cntr];
      /* Updated as per PR100083*/
      num_dec = (ps_num_box->psNumBoxDef->u16Format>>FOUR & SEVEN);
      /* Updated as per PR100146 */

         if(ps_num_box->psNumBoxDef->psParam->fread < 0)
         {
            /*Updated as per PR 100161*/
            ps_num_box->psNumBoxDef->psParam->r =
            		(T_INT32)(((ps_num_box->psNumBoxDef->psParam->fread
                     * TEN * (T_FLOAT)CalculatePower((T_FLOAT)TEN,(T_INT32)num_dec))-FIVE)/TEN);
         }
         else
         {
             /*Updated as per PR 100161*/
             ps_num_box->psNumBoxDef->psParam->r =
            		 (T_INT32)(((ps_num_box->psNumBoxDef->psParam->fread
                     * TEN * (T_FLOAT)CalculatePower((T_FLOAT)TEN,(T_INT32)num_dec))+FIVE)/TEN);
    	 }

      WidgetsUpdateRT(ps_num_box->psNumBoxDef->psParam,  &(ps_num_box->sWidgetParm));
   }

   for (u16_num_cntr=0; u16_num_cntr<U16_num_box_installed; u16_num_cntr++)
   {
      /*hdudispfnumbox-NumboxUpdate-DB-LLR-002*/
      ps_num_box = &As_num_box[u16_num_cntr];

      /*hdudispfnumbox-NumboxUpdate-DB-LLR-003*/
      if(ps_num_box->psNumBoxDef->psParam->stat < PARAM_BAD)
      {
         if(ps_num_box->sWidgetParm.pText != NULL)
         {
            WidgetsNumUpdate(ps_num_box->psNumBoxDef->psParam
               ,&(ps_num_box->sWidgetParm),
                (T_CHAR *)ps_num_box->acDigText
               ,ps_num_box->psNumBoxDef->u16Format, ps_num_box->psNumBoxDef->ePenColor
            );

         }
         else
         {
            ;/*Do nothing*/
         }
      }

      /* If the driving parameter is invalid. */
      else
      {
         /*hdudispfnumbox-NumboxUpdate-DB-LLR-004*/
         if(ps_num_box->sWidgetParm.pText != NULL)
         {
            /* Replace all characters with a red x */
            u16_field_width = BinasGetWidth (ps_num_box->psNumBoxDef->u16Format);
            ps_num_box->acDigText[u16_field_width] = ZERO;
            while(u16_field_width != ZERO)
            {
               ps_num_box->acDigText[u16_field_width-1] = RED_X;
               u16_field_width = (T_UINT16)(u16_field_width- ONE);
            }
               TextUpdate((T_PTEXT)ps_num_box->sWidgetParm.pText,BLACK, TX_NO_FLASH, V_NORMAL);
         }
         else
         {
            ;/*Do nothing*/
         }
      }
   }
}

/*
 *
 * Function                : NumboxDraw
 *
 * Description             : The function Draws the number box.
 *
 * Formal parameter(s)     : None
 *
 * Return Value            : None
 *
 * Assumption              : None
 *
 */
void NumboxDraw(void)
{
   T_UINT16 u16_num_box_cntr = 0;
   T_SNUMBOX *ps_num_box = NULL;
   T_SDISREGION ps_dis_region={0};
   T_UINT8 text[4] = "NCD";

   /* Update the angle of each round dial. */
   for (u16_num_box_cntr=0; u16_num_box_cntr < U16_num_box_installed; u16_num_box_cntr++)
   {
      /*hdudispfnumbox-NumboxDraw-DB-LLR-001*/
      ps_num_box = &As_num_box[u16_num_box_cntr];

      /*hdudispfnumbox-NumboxDraw-DB-LLR-002*/
      if(ps_num_box->psNumBoxDef->psParam->stat >= PARAM_BAD)
      {
         if(ps_num_box->psNumBoxDef->psDisRegion != NULL)
         {
          if(ps_num_box->psNumBoxDef->psParam->stat != NCD)
          {
             WidgetsRedX(ps_num_box->psNumBoxDef->psDisRegion,&(ps_num_box->psPolyRedX));
          }
          else
          {
             /*hdudispfnumbox-NumboxDraw-DB-LLR-003*/
             /*To display NCD when state is NCD */
             ps_dis_region.eRegionType=ps_num_box->psNumBoxDef->psDisRegion->eRegionType;
             ps_dis_region.eTXFont=ps_num_box->psNumBoxDef->psDisRegion->eTXFont;
             ps_dis_region.pu8Text=text;
             ps_dis_region.s32Height=ps_num_box->psNumBoxDef->psDisRegion->s32Height;
             ps_dis_region.s32Width=ps_num_box->psNumBoxDef->psDisRegion->s32Width;
             ps_dis_region.sDisLocCtr.u16X0=
             ps_num_box->psNumBoxDef->psDisRegion->sDisLocCtr.u16X0;
             ps_dis_region.sDisLocCtr.u16Y0=
             ps_num_box->psNumBoxDef->psDisRegion->sDisLocCtr.u16Y0;
             ps_dis_region.sDisLocO.u16X0=
             ps_num_box->psNumBoxDef->psDisRegion->sDisLocO.u16X0;
             ps_dis_region.sDisLocO.u16Y0=
             ps_num_box->psNumBoxDef->psDisRegion->sDisLocO.u16Y0;
             WidgetsRedX(&ps_dis_region,&(ps_num_box->psPolyRedX));
          }
         }
         else
         {
            ;/* Do nothing */
         }
      }
      else
      {
         ;/* Do nothing */
      }
   }
}

/*
 *
 * Function                : NumboxClear
 *
 * Description             : De-allocate all pointers.
 *
 * Formal parameter(s)     : None
 *
 * Return Value            : None
 *
 * Assumption              : None
 *
 */
void NumboxClear(void)
{
   /*hdudispfnumbox-NumboxClear-DB-LLR-001*/
   while(U16_num_box_installed)
   {
      As_num_box[U16_num_box_installed - 1].psPolyRedX = (T_SPOLY *)NULL;
    U16_num_box_installed = (T_UINT16)(U16_num_box_installed - ONE);
   }
}
