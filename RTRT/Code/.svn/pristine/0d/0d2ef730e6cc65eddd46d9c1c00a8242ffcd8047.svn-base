/*
 ******************************************************************************
 * License Information  :  Howell Instruments, Inc.                           *
 *                         "Licensed Software" and "All rights reserved".     *
 ******************************************************************************
 *  File                : hdudispfrounddial.c
 *
 *  Description         : The file contains routines to draw and update the round dial
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
 *      1.1          Vinay H         14-Sep-2017             100064
 *      1.2          Shilpa A R      10-Oct-2017             100064
 *      1.3          Shruthi M N     15-Oct-2017             100083
 *      1.4          Shruthi M N     30-Oct-2017             100104
 *      1.5          Shruthi M N     07-Nov-2017             100161
 *      1.6          Gururaj C       21-Jun-2020             100259
 *      1.7          Rona B S        02-Jul-2020             100259
 *      1.8          Dhanalakshmi    12-Sep-2020             100276 
 *
 * Additional References : None
 *
 ******************************************************************************
 */

#include "hdudispffonts.h"        /*Contains different font configuration information*/
#include "hdudispfpolygon1.h"      /*implements the "scan line" method polygon fill.*/
#include "hdudispfrterror.h"        /* Provides stub routine for run time errors.*/
#include "hdudispftext.h"         /*  Routines which maintain text display and updates */
#include "hdudispfrounddial.h"    /* routines which draws and updates the round dial */
#include "hdudispfbinascii.h"   /*Utility routines to convert binary to ascii base 10.*/
#include "hdudispfpdidata.h" /* provides pdi declarations */

/* Statically allocate pool of round dials.  */
static T_ROUNDDIAL A_round_dial[MAX_ROUND_DIALS] = {0};
static T_UINT16   U16_round_dials_installed = 0;
#define ASSC_LABEL_INDX 5U
#define THOUSAND     1000U


/*
 * Function                : RoundDialAllocat
 *
 * Description             : Allocate a single round dial.
 *
 * Formal parameter(s)     : T_ROUNDDIALDEF *round_dial_def - OUT round dial definition.
 *
 * Return Value            : None
 *
 * Assumption              : None
 *
 */
void RoundDialAllocat(T_ROUNDDIALDEF *round_dial_def)
{
   T_SPTRSPEC  *ps_ptr_src = {0};
   T_SPTRSPEC  *ps_ptr_dest = {0};
   T_PARAM_STAT   e_temp_stat = PARAM_OK;
    /* Updated as per PR100083*/
   T_UINT8 u8_i=0;
   T_UINT8 num_dec=0;
   T_INT32 reading=0;
   T_PROUNDDIAL round_dial = &(A_round_dial[U16_round_dials_installed]);

   static T_CHAR param_message[] = "Too many round dials.";
   T_CHAR file_name[] = __FILE__;

   /* Check for over allocated. */
   if(MAX_ROUND_DIALS == U16_round_dials_installed)
   {
     /*hdudispfrounddial-RoundDialAllocat-DB-LLR-001*/
      RterrWidget((T_CHAR *)&file_name,__LINE__, (T_CHAR *) &param_message);
      round_dial_def->pRoundDial = (T_PROUNDDIAL)ZERO;
      return;
   }
   else
   {
     /*hdudispfrounddial-RoundDialAllocat-DB-LLR-002*/
      /* Link the owner to object. */
      round_dial_def->pRoundDial = round_dial;
   }
   if(((T_ETXFONT)E_TINY_FONT != round_dial_def->eFont) &&
	  ((T_ETXFONT)E_SMALL_FONT != round_dial_def->eFont) &&
	  ((T_ETXFONT)E_NORMAL_FONT != round_dial_def->eFont) &&
	  ((T_ETXFONT)E_LARGE_FONT != round_dial_def->eFont) &&
	  ((T_ETXFONT)E_BEZEL_FONT != round_dial_def->eFont))
   {
	   round_dial_def->eFont = (T_ETXFONT)E_NO_FONT;
   }
   else 
   { 
        ; /* Do nothing */
   }
   

   /*hdudispfrounddial-RoundDialAllocat-DB-LLR-003*/
   /* Link object to owner. */
   round_dial->round_dial_def = round_dial_def;
   /* Red X not yet defined. */
   round_dial->psPolyRedX = (T_SPOLY *)ZERO;

    /* Updated as per PR100083*/
   num_dec = (round_dial->round_dial_def->u16Format>>FOUR & SEVEN);
   reading= (T_INT32)(((round_dial_def->psParam->fread*THOUSAND*
                  (T_FLOAT)CalculatePower((T_FLOAT)TEN,(T_INT32)num_dec))+FIVE)/TEN);
   /* Initialize the digital reading. */
   round_dial->sWidgetParm.s32DisDig = reading;
   round_dial->sWidgetParm.s32Dig = reading;
   /* Initialize the scaler reading. */
   round_dial->sWidgetParm.s32Scaler = reading;
   round_dial->sWidgetParm.s32ScalerStep = ZERO;

   /* Install all pointers. */
   ps_ptr_src = round_dial_def->asPtrSpec;
   ps_ptr_dest = round_dial->asPtrSpec;

   /* Make a copy of all pointers used. */
   while(ps_ptr_src->s32PtrShape)
   {
     /*hdudispfrounddial-RoundDialAllocat-DB-LLR-004*/
      ps_ptr_src->psShape = PolygonsPsPolyInit(ps_ptr_src->s32PtrShape,
                  round_dial_def->ptr_scale[u8_i].u16X0,
        MAG(round_dial_def->ptr_scale_offset[u8_i].u16X0),round_dial_def->ptr_scale[u8_i].u16Y0,
            MAG(round_dial_def->ptr_scale_offset[u8_i].u16Y0),\
			(T_INT16)round_dial_def->rotAngle[u8_i]);
      ps_ptr_dest->psShape = PolygonsPsDuplicate(ps_ptr_src->psShape);
      ps_ptr_dest->ePenColor = ps_ptr_src->ePenColor;
      ps_ptr_src++;
      ps_ptr_dest++;
      u8_i++;
   }
   /*hdudispfrounddial-RoundDialAllocat-DB-LLR-005*/
    /* Updated as per PR100083*/
   round_dial->sAngle = LookupTableLookup(round_dial_def->psGeometry,
                        round_dial->sWidgetParm.s32Scaler, &e_temp_stat);

   /* Delimit the pointer handle array. */
   ps_ptr_dest->psShape = (T_SPOLY *)ZERO;

   /* If the digital display has a width and the font is defined. */
   if(BinasGetWidth(round_dial_def->u16Format)&&(round_dial_def->eFont))
   {
        /*hdudispfrounddial-RoundDialAllocat-DB-LLR-006*/
         /* Initialize the ascii reading. */
        /* Updated as per PR100083*/
         BinasByteFormatInfoBE (&(round_dial->sWidgetParm.s32DisDig), round_dial_def->u16Format,
                               (T_INT8*) round_dial->acDigText);

         /* Initialize the digital display. */
         TextAllocat( (T_PTEXT *) &(round_dial->sWidgetParm.pText),
               (T_UINT8 *) round_dial->acDigText,
               (T_UINT16)((round_dial_def->sDigCenterOffset.u16X0
               +round_dial_def->sUpperLeft.u16X0)/(T_UINT8)MAG_FACTOR),
               (T_UINT16)((round_dial_def->sDigCenterOffset.u16Y0
               +round_dial_def->sUpperLeft.u16Y0)/(T_UINT8)MAG_FACTOR),
               ALIGN_CENTER,
               round_dial_def->eFont,
               WHITE,
               V_NORMAL,
               TX_NO_FLASH
               );
   }
   /* If no digital display. */
   else
   {
     /*hdudispfrounddial-RoundDialAllocat-DB-LLR-007*/
      round_dial->sWidgetParm.pText = (T_PTEXT *)ZERO;
   }
   /*hdudispfrounddial-RoundDialAllocat-DB-LLR-008*/
   /* Inc Round Dials installed. */
   U16_round_dials_installed = (T_UINT16)(U16_round_dials_installed + ONE);
}

/*
 *
 * Function                : RoundDialUpdate
 *
 * Description             : Update all installed dials
 *
 * Formal parameter(s)     : None
 *
 * Return Value            : None
 *
 * Assumption              : None
 *
 */
void RoundDialUpdate(void)
{
   T_UINT16 u16_round_dial_cntr = 0;
   T_SPTRSPEC  *ps_ptr_src = {0};
   T_PARAM_STAT   e_temp_stat = PARAM_OK;
   T_ROUNDDIAL *ps_round_dial = {0};
    /* Updated as per PR100083*/
   T_UINT16 u16_field_width = 0;
    T_UINT16    num_dec=0;
   T_SRECTPOINT   s_rect_point = {0};
   T_FLOAT       decvernpos=0;
   T_INT32       vernscalertemp=ZERO;
   T_INT32 st_angle = 0; /* starting angle of the dial*/
   T_UINT8 pointer = 0; /* Variable to determine the colored filled rd pointer*/
   T_BOOL rd_moving = FALSE; /*TRUE if its a moving round dial*/

   /* Update readings used for digital and analog updates. */
   for (u16_round_dial_cntr=ZERO; u16_round_dial_cntr<U16_round_dials_installed;
                                                             u16_round_dial_cntr++)
   {
     /*hdudispfrounddial-RoundDialUpdate-DB-LLR-001*/
      ps_round_dial = &A_round_dial[u16_round_dial_cntr];
      /* Updated as per PR100083*/
      num_dec = (ps_round_dial->round_dial_def->u16Format>>FOUR & SEVEN);
      ps_round_dial->round_dial_def->psParam->r =
           (T_INT32)(((ps_round_dial->round_dial_def->psParam->fread*
        THOUSAND* (T_FLOAT)CalculatePower((T_FLOAT)TEN,(T_INT32)num_dec))+FIVE)/TEN);
      WidgetsUpdateRT(ps_round_dial->round_dial_def->psParam,  &(ps_round_dial->sWidgetParm));
   }

   /* Update the angle of each round dial. */
   for (u16_round_dial_cntr=ZERO; u16_round_dial_cntr<U16_round_dials_installed;
                                                                u16_round_dial_cntr++)
   {
     /*hdudispfrounddial-RoundDialUpdate-DB-LLR-002*/
      /* Update the angle of each round dial. */
      ps_round_dial = &A_round_dial[u16_round_dial_cntr];

       /* Vernier round dial*/
      if (ONE == ps_round_dial->round_dial_def->vernStatus)
      {
          /*hdudispfrounddial-RoundDialUpdate-DB-LLR-006*/
          /*oneth, tenth vernier*/
          if (ps_round_dial->round_dial_def->vernPos < ONE)
          {
              ps_round_dial->sWidgetParm.s32Scaler =
                     (T_INT32)((ps_round_dial->round_dial_def->psParam->fread *ONE_HUNDRED ));
              decvernpos = ps_round_dial->round_dial_def->vernPos * THOUSAND;

              ps_round_dial->sWidgetParm.s32Scaler =
                      (ps_round_dial->sWidgetParm.s32Scaler %(T_INT32)decvernpos)*(T_INT32) TEN *
                      ((T_INT32)ONE_HUNDRED/ (T_INT32)decvernpos) ;
          }
          else
          {
              /*hdudispfrounddial-RoundDialUpdate-DB-LLR-007*/
              /*ones,twos,hundreds vernier*/
              ps_round_dial->sWidgetParm.s32Scaler =
              (T_INT32)((T_INT32)ps_round_dial->round_dial_def->psParam->fread %
               ((T_INT32)ps_round_dial->round_dial_def->vernPos * (T_INT32)TEN) );

              ps_round_dial->sWidgetParm.s32Scaler = \
			          (ps_round_dial->sWidgetParm.s32Scaler *(T_INT32)TEN *
                      ((T_INT32)TEN/(T_INT32)ps_round_dial->round_dial_def->vernPos));

              if (ONE == (T_INT32)ps_round_dial->round_dial_def->vernPos)
              {
                  vernscalertemp = (T_INT32)(ps_round_dial->round_dial_def->psParam->fread *
                                    ONE_HUNDRED);
                  vernscalertemp = ((T_INT32)vernscalertemp % ONE_HUNDRED);
                  ps_round_dial->sWidgetParm.s32Scaler = ps_round_dial->sWidgetParm.s32Scaler +
                                                         vernscalertemp;
              }
			  else
              {
                  ; /*Do nothing*/
              }
          }
          /*hdudispfrounddial-RoundDialUpdate-DB-LLR-008*/
          if (ps_round_dial->sWidgetParm.s32Scaler < 0)
          {
              ps_round_dial->sWidgetParm.s32Scaler = ps_round_dial->sWidgetParm.s32Scaler * (-1);
          }
		  else
          {
              ; /*Do nothing*/
          }
          /*hdudispfrounddial-RoundDialUpdate-DB-LLR-009*/    
          ps_round_dial->sAngle = LookupTableLookup(ps_round_dial->round_dial_def->psGeometry,
                                        ps_round_dial->sWidgetParm.s32Scaler, &e_temp_stat);
      }
      else
      {
          /*hdudispfrounddial-RoundDialUpdate-DB-LLR-010*/

          ps_round_dial->sAngle = LookupTableLookup(ps_round_dial->round_dial_def->psGeometry,
                                         ps_round_dial->sWidgetParm.s32Scaler, &e_temp_stat);
      }



      if(ps_round_dial->round_dial_def->psParam->stat < PARAM_BAD)
      {
         /* If the dial has a digital display. */
         if(ps_round_dial->sWidgetParm.pText != ZERO)
         {
         /*hdudispfrounddial-RoundDialUpdate-DB-LLR-003*/
            WidgetsNumUpdate(ps_round_dial->round_dial_def->psParam,
               &(ps_round_dial->sWidgetParm),
               ps_round_dial->acDigText,
               ps_round_dial->round_dial_def->u16Format, 0);
         }
         else
         {
            ;/*Do nothing*/
         }

            /* Update all pointers of this dial. */
         for(ps_ptr_src = ps_round_dial->asPtrSpec,pointer = 0;
             ps_ptr_src->psShape != (T_SPOLY *)ZERO; ps_ptr_src++,pointer++)
         {
         /*hdudispfrounddial-RoundDialUpdate-DB-LLR-004*/
            s_rect_point.s32X = (T_INT32)ps_round_dial->round_dial_def->sUpperLeft.u16X0
                        +  (T_INT32)ps_round_dial->round_dial_def->sDialCenterOffset.u16X0;

            s_rect_point.s32Y = (T_INT32)ps_round_dial->round_dial_def->sUpperLeft.u16Y0
                        +  (T_INT32)ps_round_dial->round_dial_def->sDialCenterOffset.u16Y0;

            /*to check whether the pointer is color filed round dial or not*/
            /*hdudispfrounddial-RoundDialUpdate-DB-LLR-011*/

            if (EMOVINGROUNDDIAL==(T_INT32)ps_round_dial->round_dial_def->
                                        asPtrSpec[pointer].s32PtrShape)
            {
                /* to determine Moving round Dial initial Angle*/
                st_angle = LookupTableLookup(ps_round_dial->round_dial_def->psGeometry,
                            0, &e_temp_stat);
                rd_moving = TRUE;
            }
            else
            {
                st_angle = 0;
                rd_moving = FALSE;
            }
         /*hdudispfrounddial-RoundDialUpdate-DB-LLR-012*/
            PolygonsvPolarToRect(ps_ptr_src->psShape,
                                             s_rect_point.s32X,
                                             s_rect_point.s32Y,
                                             ps_round_dial->round_dial_def->usLength,
                                             ps_round_dial->sAngle, st_angle, rd_moving
                                             );
         }
      }
      /* If parameter is invalid. */
      else
      {
       /*hdudispfrounddial-RoundDialUpdate-DB-LLR-005*/
         /* If a digital display is present. */
         if((T_PTEXT *)NULL != ps_round_dial->sWidgetParm.pText)
         {
            /* Replace all characters with a red x */
            u16_field_width = BinasGetWidth (ps_round_dial->round_dial_def->u16Format);
            ps_round_dial->acDigText[u16_field_width] = ZERO;
            while(u16_field_width)
            {
               ps_round_dial->acDigText[u16_field_width-ONE] = RED_X;
               u16_field_width=(T_UINT16)(u16_field_width -ONE);
            }
            TextUpdate((T_PTEXT) ps_round_dial->sWidgetParm.pText,LIGHT_RED, TX_NO_FLASH,V_NORMAL);
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
 * Function                : RoundDialDraw
 *
 * Description             : The function Draws the Round dial
 *
 * Formal parameter(s)     : None
 *
 * Return Value            : None
 *
 * Assumption              : None
 *
 */
void RoundDialDraw(void)
{
   T_UINT16 u16_round_dial_cntr = 0;
   T_UINT16 u16_round_x_cntr = 0;
   T_ROUNDDIAL *ps_round_dial = {0};
   T_SPTRSPEC  *ptr_spec = {0};
    /* Updated as per PR100083*/
   static T_BOOL round_dial_sw_x[30] = {FALSE};
   T_BOOL draw_dial = TRUE;
   T_UINT8 assc_indx=0;
   for (u16_round_dial_cntr=ZERO; u16_round_dial_cntr<U16_round_dials_installed;
                         u16_round_dial_cntr++)
   {
     /*hdudispfrounddial-RoundDialDraw-DB-LLR-001*/
      ps_round_dial = &A_round_dial[u16_round_dial_cntr];
      /* Updated as per PR100083*/
      draw_dial = TRUE;
      /* If the driving parameter is invalid, RedX the region. */
      if(ps_round_dial->round_dial_def->psParam->stat >= PARAM_BAD)
      /* Updated as per PR100083*/
      {
         for(assc_indx=0;assc_indx<ASSC_LABEL_INDX;assc_indx++)
         {
            if(ps_round_dial->round_dial_def->associated_labels[assc_indx]!=0)
            {
               for(u16_round_x_cntr = 0; u16_round_x_cntr<U16_round_dials_installed;
                   u16_round_x_cntr++)
                  {
                     if((ps_round_dial->round_dial_def->associated_labels[assc_indx]
                           == A_round_dial[u16_round_x_cntr].round_dial_def->label)
                           &&(!round_dial_sw_x[u16_round_x_cntr] ))
                     {
                        if(A_round_dial[u16_round_x_cntr].round_dial_def->psParam->stat<PARAM_BAD)
                        {
                           draw_dial = FALSE;
                        }
                        break;
                     }
					 else
                     {
                         ; /*Do nothing*/
                     }
                  }

            }
            else
            {
               break;
            }
         }

         if((T_SDISREGION *)NULL != ps_round_dial->round_dial_def->psDisRegion && TRUE == draw_dial)
         {
         /*hdudispfrounddial-RoundDialDraw-DB-LLR-002*/
            WidgetsRedX(ps_round_dial->round_dial_def->psDisRegion, &(ps_round_dial->psPolyRedX ));
          /* Updated as per PR100083*/
            round_dial_sw_x[u16_round_dial_cntr] = TRUE;
         }
         else
         {
            ;/*Do nothing*/
         }
      }
      /* Else draw the pointer(s). */
      else
      {
       /* Updated as per PR100083*/
         round_dial_sw_x[u16_round_dial_cntr] = FALSE;

       /*hdudispfrounddial-RoundDialDraw-DB-LLR-003*/
         ptr_spec = ps_round_dial->asPtrSpec;
         while(ptr_spec->psShape)
         {
            PolygonDrawPoly(ptr_spec->psShape, ptr_spec->ePenColor);
            ptr_spec++;
         }
      }
   }
}

/*
 *
 * Function                : RoundDialClear
 *
 * Description             : De-allocate Round Dials.
 *
 * Formal parameter(s)     : None
 *
 * Return Value            : None
 *
 * Assumption              : None
 *
 */
void RoundDialClear(void)
{
   /*hdudispfrounddial-RoundDialClear-DB-LLR-001*/
   while(U16_round_dials_installed)
   {
      A_round_dial[U16_round_dials_installed - ONE].psPolyRedX = (T_SPOLY *)ZERO;
      U16_round_dials_installed = (T_UINT16)(U16_round_dials_installed - ONE);
   }
}
