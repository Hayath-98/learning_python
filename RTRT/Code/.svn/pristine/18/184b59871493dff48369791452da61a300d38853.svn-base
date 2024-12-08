/*
 ******************************************************************************
 * License Information  :  Howell Instruments, Inc.                           *
 *                         "Licensed Software" and "All rights reserved".     *
 ******************************************************************************
 *  File                : hdudispfcas.c
 *
 *  Description         : This file defines the functions to display CAS messages.
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
 *      1.1          Rona B.S        11-Sep-2017             100064
 *      1.2          Rona B.S        10-Oct-2017             100064
 *      1.3          Shruthi M N     15-Oct-2017             100083
 *      1.4          Shruthi M N     30-Oct-2017             100104
 *      1.5          Shruthi M N,
 *                   Divya G P       03-Nov-2017             100108,100156
 *      1.6          Shilpa A R      09-Nov-2017             100164
 *      1.7          Chaithra J      21-Jun-2020             100259
 *      1.8          Rona B.S        29-Jun-2020             100259
 *      1.9          Dhanalakshmi    12-Sep-2020             100276
 *      1.10         Rona B S        29-Sep-2020             100284
 *
 * Additional References : None
 *
 *****************************************************************************
 */

#include "hdudispfcas.h"   /* common defines and functions prototypes for CAS */
#include "hdudispffonts.h"  /*Contains different font information*/
#include "hdudispfpara.h"  /* prototype for builds faults, message and system information  */
#include "hdulibbasictypes.h" /* Standard basic data type definitions */
#include "hdudispfrterror.h" /* Prototype for Rterr definations*/

#define NUM_ROWS  7
#define NUM_COLS  2
#define MAX_CAS_MSG_DISP 35

#define MAX_ITEMS (NUM_ROWS*NUM_COLS)
/* Updated as per PR 100083 */
#define FLASH_TIME1  999000
#define FLASH_TIME2  9999000

T_UINT16 U16_cas_words[MAX_FLAG_WORDS]= {ZERO};
T_UINT16 U16_cas_new_words [MAX_FLAG_WORDS]= {ZERO};
T_UINT16 U16_cas_new_shadow[MAX_FLAG_WORDS]= {ZERO};
T_UINT16 U16_cas_old_shadow[MAX_FLAG_WORDS]= {ZERO};

/*
 * Function                :  CasSetCasWord
 *
 * Description             :  This function is used to set the CAS words.
 *
 * Formal parameter(s)     :  T_UINT8 u8_index - IN Indicates the index.
 *                            T_UINT16 u16_cas_word - IN CAS data.
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */

void CasSetCasWord(T_UINT8 u8_index, T_UINT16 u16_cas_word)
{
   /* hdudispfcas-CasSetCasWord-DB-LLR-001 */
   U16_cas_words[u8_index % MAX_FLAG_WORDS] = u16_cas_word;
}


/*
 * Function                :  CasInit
 *
 * Description             :  This function installs the flash timer for
 *                            each possible CAS message.
 *
 * Formal parameter(s)     :  None
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */

void CasInit(void)
{
   T_UINT16 u16_index  = ZERO;

   for(u16_index = ZERO; u16_index<MAX_CAS_MESSAGES; u16_index++)
   {
      /* hdudispfcas-CasInit-DB-LLR-001 */
       TimerInstall(&(All_cas_messages[u16_index].Flash_timer));
   }
}

/*
 * Function                :  FormulateNewCas
 *
 * Description             :  This function eliminates the old CAS messages
 *                            from the new list.
 *
 * Formal parameter(s)     :  None
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */

static void FormulateNewCas(void)
{
   /* Updated as per PR 100083 */
   T_UINT16 u16_word_cntr  = ZERO;
   T_UINT16 u16_mask       = ZERO;

   /* hdudispfcas-FormulateNewCas -DB-LLR-001 */
   /* For each CAS Word.  */
   for(u16_word_cntr=ZERO; u16_word_cntr < MAX_FLAG_WORDS; u16_word_cntr++)
   {
      /* For each message in the word.  */
      for(u16_mask =THREE; u16_mask; u16_mask = (T_UINT16)(u16_mask<<TWO))
      {
         /* If the message is present.  */
         if((U16_cas_new_words[u16_word_cntr] & u16_mask) != ZERO)
         {
            /* If the message was present before.  */
            if((U16_cas_old_shadow[u16_word_cntr] & u16_mask) != ZERO)
            {
               /* Eliminate it from the new list.  */
               U16_cas_new_words[u16_word_cntr] &= (T_UINT16)(~u16_mask);
            }
            else
            {
              ; /*Do nothing */
            }
         }
         else
         {
           ; /*Do nothing */
         }
      }
   }
}

/*
 * Function                :  ResetNewTimers
 *
 * Description             :  This function resets the flash timer for each new
 *                            CAS message.
 *
 * Formal parameter(s)     :  None
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */

static void ResetNewTimers(void)
{
   /* Updated as per PR 100083 */
   T_UINT16 u16_word_cntr = ZERO;
   T_UINT16 u16_index     = ZERO;
   T_UINT16 u16_mask      = ZERO;

   /*    hdudispfcas-ResetNewTimers-DB-LLR-001 */
   for(u16_word_cntr=0; u16_word_cntr<MAX_FLAG_WORDS; u16_word_cntr++)
   {
      /* For each message in the word.  */
      for(u16_mask = THREE; u16_mask != ZERO ; u16_mask = (T_UINT16)(u16_mask<<TWO))
      {
         /* If the message is present.  */
         if((U16_cas_new_words[u16_word_cntr] & u16_mask) != ZERO)
         {
            TimerReset(&(All_cas_messages[u16_index].Flash_timer));
         }
         else
         {
          ; /* Do nothing */
         }
         u16_index = (T_UINT16)(u16_index + ONE);
      }
   }
}

/*
 * Function                :  SetCasStatus
 *
 * Description             :  This function sets the CAS status.
 *
 * Formal parameter(s)     :  None
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */

void SetCasStatus(void)
{
   T_UINT16 u16_word_cntr  = ZERO;
   T_UINT16 u16_index      = ZERO;
   T_UINT16 u16_mask       = ZERO;
   T_UINT8  u8_shift_count = ZERO;
   T_UINT16 u16_stat_val   = ZERO;

   /* For each CAS Word.  */
   for(u16_word_cntr = ZERO; u16_word_cntr < MAX_FLAG_WORDS; u16_word_cntr++)
   {
      /* For each message in the word.  */
      for(u16_mask = THREE, u8_shift_count = ZERO; u16_mask; u16_mask = (T_UINT16)(u16_mask<<TWO),
                                         u8_shift_count = (T_UINT8)(u8_shift_count + TWO))
      {
       /*   hdudispfcas-SetCasStatus-DB-LLR-001 */
         u16_stat_val = U16_cas_new_shadow[u16_word_cntr] & u16_mask;
         u16_stat_val = (T_UINT16)(u16_stat_val >>u8_shift_count);
       /* Updated as per PR100108 */
         if(u16_stat_val<THREE)
         {
          All_cas_messages[u16_index].u8Stat = (T_UINT8)u16_stat_val;
         }
       else
       {
       ;
       }
         u16_index = (T_UINT16)(u16_index + ONE);
      }
   }
}

/*
 * Function                :  CasUpdate
 *
 * Description             :  This function is used to Update the CAS words.
 *
 * Formal parameter(s)     :  None
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */

void CasUpdate(void)
{
   T_INT16  s16_cntr   = ZERO;
   T_UINT16 *pu16_src  = ZERO;
   T_UINT16 *pu16_dest = ZERO;

   /* Make a copy of the most recent CAS words.  */
   for(s16_cntr = ZERO, pu16_src = U16_cas_words, pu16_dest = U16_cas_new_words;\
       s16_cntr<MAX_FLAG_WORDS;s16_cntr++)
   {
      /* hdudispfcas-CasUpdate-DB-LLR-001 */
      *(pu16_dest++) = *(pu16_src++);
   }
   for(s16_cntr=ZERO, pu16_src = U16_cas_new_words, pu16_dest = U16_cas_new_shadow;\
       s16_cntr<MAX_FLAG_WORDS;s16_cntr++)
   {
      /* hdudispfcas-CasUpdate-DB-LLR-002 */
      *(pu16_dest++) = *(pu16_src++);
   }

   /* hdudispfcas-CasUpdate-DB-LLR-003 */
   /*Make New Cas Words contain only those messages that are new.*/
   FormulateNewCas();

   /* hdudispfcas-CasUpdate-DB-LLR-004 */
   /*Reset the timers for all the new words.*/
   ResetNewTimers();

   /*hdudispfcas-CasUpdate-DB-LLR-005 */
   /*Copy Status to the CAS list.*/
   SetCasStatus();

   /*Update Old Shadow with New Shadow.*/
   for(s16_cntr=ZERO, pu16_src = U16_cas_new_shadow, pu16_dest = U16_cas_old_shadow; \
       s16_cntr<MAX_FLAG_WORDS;s16_cntr++)
   {
      /* hdudispfcas-CasUpdate-DB-LLR-006 */
      *(pu16_dest++) = *(pu16_src++);
   }

   SetCasStatus();
}

/*
 * Function                :  CasSort
 *
 * Description             :  This function sorts the CAS messages.
 *
 * Formal parameter(s)     :  None
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */

void CasSort (void)
{
   T_UINT16 u1_item_count  = 0;
   T_UINT16 u16_next_count = 0;
   T_CAS_MSG_DEF temp ={0};

   T_CAS_MSG_DEF cas_priority[MAX_CAS_MESSAGES] = {{0}};

   /*Aspen order sort  */
   for(u1_item_count = 0; u1_item_count < Cas_message_count ; u1_item_count++)
   {
      for(u16_next_count = (T_UINT16)(u1_item_count+1); u16_next_count < Cas_message_count ;
           u16_next_count++)
      {
         if(Cas_msg[u1_item_count].Id > Cas_msg[u16_next_count].Id)
         {
            /* hdudispfcas-CasSort-DB-LLR-001 */
            temp = Cas_msg[u1_item_count];
            Cas_msg[u1_item_count] = Cas_msg[u16_next_count];
            Cas_msg[u16_next_count] = temp;
         }
         else
         {
          ; /* Do nothing */
         }
      }
   }

   for(u1_item_count = 0; u1_item_count < Cas_message_count ; u1_item_count++)
   {
      for(u16_next_count = (T_UINT16)(u1_item_count+1); u16_next_count < Cas_message_count ;
                                                             u16_next_count++)
      {
         if(Cas_msg[u1_item_count].Id == Cas_msg[u16_next_count].Id)
         {
            if(Cas_msg[u1_item_count].u8Start > Cas_msg[u16_next_count].u8Start)
            {
               /* hdudispfcas-CasSort-DB-LLR-002 */
               temp = Cas_msg[u1_item_count];
               Cas_msg[u1_item_count] = Cas_msg[u16_next_count];
               Cas_msg[u16_next_count] = temp;
            }
            else
            {
               ; /*Do nothing */
            }
         }
         else
         {
            ; /* Do nothing */
         }
      }
   }

   /*Priority sorting  */
   for(u1_item_count = 0; u1_item_count < Cas_message_count ; u1_item_count++)
   {
      /* hdudispfcas-CasSort-DB-LLR-003 */
      cas_priority[u1_item_count].priority = Cas_msg[u1_item_count].priority;
      cas_priority[u1_item_count].Id = Cas_msg[u1_item_count].Id;
      cas_priority[u1_item_count].u8Start = Cas_msg[u1_item_count].u8Start;
   }

   for(u1_item_count = 0; u1_item_count < Cas_message_count ; u1_item_count++)
   {
      for(u16_next_count = (T_UINT16)(u1_item_count+1); u16_next_count < Cas_message_count ;
                                                          u16_next_count++)
      {
         if(cas_priority[u1_item_count].priority > cas_priority[u16_next_count].priority)
         {
          /*   hdudispfcas-CasSort-DB-LLR-004 */
            temp = cas_priority[u1_item_count];
            cas_priority[u1_item_count] = cas_priority[u16_next_count];
            cas_priority[u16_next_count] = temp;
         }
         else
         {
          ; /* Do nothing */
         }
      }
   }

   /* hdudispfcas-CasSort-DB-LLR-005 */
   for(u1_item_count = 0; u1_item_count < Cas_message_count ; u1_item_count++)
   {
      if(ELEVEN == cas_priority[u1_item_count].u8Start)
      {
         Cas_app_array[u1_item_count] = (cas_priority[u1_item_count].Id * EIGHT) +
                                 (cas_priority[u1_item_count].u8Start-TEN);
      }
      else
      {
         Cas_app_array[u1_item_count] = (cas_priority[u1_item_count].Id * EIGHT) +
                             ((cas_priority[u1_item_count].u8Start-TEN)/TWO)+1;
     }
   }
}

/*
 * Function                :  CasDisplay
 *
 * Description             :  This function displays the CAS messages.
 *
 * Formal parameter(s)     :  None
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */

void CasDisplay()
{
   enum CAS_INDEX *message_index    = Cas_app_array;
   T_UINT16 u16_item_count                = 0;
   T_UINT16    u16_display_x = 0;
   T_UINT16    u16_display_y = 0;
   T_CAS_MESSAGE  *cas_message = (T_CAS_MESSAGE *)NULL;
   T_CHAR        message_text[MAX_CAS_LENGTH+3] = {0};  /*Max chars + delimiter + book ends.  */
   T_CHAR        *src_ptr = (T_CHAR *)NULL ;
   T_CHAR        *dest_ptr= (T_CHAR *)NULL;

   T_UINT16 indx1 = 0;

   T_TIMER flash_timer = 0;
   T_ETXFONT cas_font = 0;

   T_UINT16 u16_index = 0;
   T_CHAR file_name3[] = __FILE__;
   T_CHAR cas_err_msg[] = "Too many cas messages";

   /* hdudispfcas-CasDisplay-DB-LLR-001 */
   if((T_UINT16)MAX_CAS_MSG_DISP < (T_UINT16)Cas_message_count)
   {
	  RterrWidget((T_CHAR *)&file_name3, __LINE__, &cas_err_msg[0]);
   }
   else
   {
       	;  /* Do nothing */
   }

   CasSort();
   message_index  = Cas_app_array;
   for(u16_index = 0; u16_index < MAX_CAS_MESSAGES ; u16_index++)
   {
      All_cas_messages[u16_index].ePenColor = BLACK;
   }
   while(*message_index)
   {
      All_cas_messages[(*message_index)-1].ePenColor = CAS_WHITE;
      message_index += 1;
   }

   /* hdudispfcas-CasDisplay-DB-LLR-002 */
   for(u16_item_count = 0; u16_item_count < Cas_message_count ; u16_item_count++)
   {
      if(CAS_ADVISORY == Cas_msg[u16_item_count].type)
      {
         Cas_msg[u16_item_count].ePenColor = CAS_WHITE;
      }
      else if(CAS_CAUTION == Cas_msg[u16_item_count].type)
      {
         Cas_msg[u16_item_count].ePenColor = CAS_AMBER;
      }
      else if(CAS_WARNING == Cas_msg[u16_item_count].type)
      {
         Cas_msg[u16_item_count].ePenColor = CAS_RED;
      }
      else
      {
        ; /* Do nothing */
      }
   }

   u16_item_count = 0;

   /*  hdudispfcas-CasDisplay-DB-LLR-003 */
   for(u16_index = 0; u16_index < MAX_CAS_MESSAGES ; u16_index++)
   {
      if(BLACK != All_cas_messages[u16_index].ePenColor )
      {
          All_cas_messages[u16_index].ePenColor = Cas_msg[u16_item_count].ePenColor;
          for(indx1=0;indx1<MAX_CAS_LENGTH;indx1++)
          {
             All_cas_messages[u16_index].acCASText[indx1] =
                                        Cas_msg[u16_item_count].acCASText[indx1];
          }
          u16_item_count++;
      }
      else
      {
         ;/* Does nothing*/
      }
   }

   /* hdudispfcas-CasDisplay-DB-LLR-004 */
   message_index  = Cas_app_array;
   u16_item_count = 0;
   while(*message_index)
   {
      if ((u16_item_count) >=
    		  (Cas_messages_setting.row * Cas_messages_setting.column))
      {
         return;
      }
      else
      {
         ; /*Do nothing */
      }

      cas_message = &(All_cas_messages[(*message_index)-1]);

      u16_display_x = (T_UINT16)((u16_item_count / Cas_messages_setting.row) *
           (T_UINT16)Cas_messages_setting.columnWidth +
                 (T_UINT16)Cas_messages_setting.sOrigin.u16X0);

      u16_display_y = (T_UINT16)((u16_item_count % Cas_messages_setting.row) *
           (T_UINT16)Cas_messages_setting.rowHeight + (T_UINT16)Cas_messages_setting.sOrigin.u16Y0);

      cas_font = Cas_messages_setting.eFont;

      /* hdudispfcas-CasDisplay-DB-LLR-005 */
      if(ZERO != cas_message->u8Stat)
      {
         dest_ptr = message_text;
         *(dest_ptr++) = LEFT_BE;
         src_ptr = cas_message->acCASText;

         while(*src_ptr)
         {
            *(dest_ptr++) = *(src_ptr++);
         }
         *(dest_ptr++) = RIGHT_BE;
         *dest_ptr = 0;

         /* hdudispfcas-CasDisplay-DB-LLR-006 */
         if(CAS_RED == cas_message->ePenColor )
         {
          flash_timer = Cas_messages_setting.warn_flash_timer;
         }
         else if(CAS_AMBER == cas_message->ePenColor )
         {
          flash_timer = Cas_messages_setting.caut_flash_timer;
         }
         else if(CAS_WHITE == cas_message->ePenColor)
         {
          flash_timer = Cas_messages_setting.adv_flash_timer;
         }
         else
         {
            /* Does nothing */
         }

         if(ZERO == flash_timer)
         {
            if((REV_VID == cas_message->u8Stat) || (CAS_RED==cas_message->ePenColor))
            {
             /* hdudispfcas-CasDisplay-DB-LLR-007 */
                TextDispString((T_INT8*)message_text, u16_display_x, u16_display_y, cas_font,
                                    cas_message->ePenColor, TX_NO_FLASH, V_REVERSE, ALIGN_LEFT);
            }
            else if((CAS_AMBER==cas_message->ePenColor) ||(CAS_WHITE==cas_message->ePenColor))
            {
              /* hdudispfcas-CasDisplay-DB-LLR-008 */
                 TextDispString((T_INT8*)message_text, u16_display_x, u16_display_y, cas_font,
                                      cas_message->ePenColor, TX_NO_FLASH, V_NORMAL, ALIGN_LEFT);
            }
            else
            {
               ; /*Do nothing */
            }
         }
         else if(FLASH_TIME1 == flash_timer)
         {
            if(REV_VID == cas_message->u8Stat || CAS_WHITE==cas_message->ePenColor)
            {
               /* hdudispfcas-CasDisplay-DB-LLR-009 */
               TextDispString((T_INT8*)message_text, u16_display_x, u16_display_y, cas_font,
                             cas_message->ePenColor, TX_FLASH, V_REVERSE, ALIGN_LEFT);
            }
            else if(CAS_AMBER==cas_message->ePenColor)
            {
              /* hdudispfcas-CasDisplay-DB-LLR-010 */
                 TextDispString((T_INT8*)message_text, u16_display_x, u16_display_y, cas_font,
                    cas_message->ePenColor, TX_NO_FLASH, V_NORMAL, ALIGN_LEFT);
            }
            else
            {
               /* hdudispfcas-CasDisplay-DB-LLR-011 */
               TextDispString((T_INT8*)message_text, u16_display_x, u16_display_y, cas_font,
                    cas_message->ePenColor, TX_NO_FLASH, V_REVERSE, ALIGN_LEFT);
            }
         }
         else if(FLASH_TIME2 == flash_timer)
         {
            /* hdudispfcas-CasDisplay-DB-LLR-012 */
            TextDispString((T_INT8*)message_text, u16_display_x, u16_display_y, cas_font,
                            cas_message->ePenColor, TX_FLASH, V_REVERSE, ALIGN_LEFT);
         }
         else
         {
            if (cas_message->Flash_timer < flash_timer)
            {
               /* hdudispfcas-CasDisplay-DB-LLR-013 */
               if((CAS_WHITE==cas_message->ePenColor) || (REV_VID == cas_message->u8Stat))
               {
                  TextDispString((T_INT8*)message_text, u16_display_x, u16_display_y, cas_font,
                             cas_message->ePenColor, TX_FLASH, V_REVERSE, ALIGN_LEFT);
              }
               else if(CAS_AMBER==cas_message->ePenColor)
               {
                  TextDispString((T_INT8*)message_text, u16_display_x, u16_display_y, cas_font,
                                cas_message->ePenColor, TX_NO_FLASH, V_NORMAL, ALIGN_LEFT);
               }
               else if(CAS_RED==cas_message->ePenColor)
               {
                  TextDispString((T_INT8*)message_text, u16_display_x, u16_display_y, cas_font,
                                cas_message->ePenColor, TX_NO_FLASH, V_REVERSE, ALIGN_LEFT);
               }
               else
               {
                  ; /*Do nothing */
               }
            }
            else
            {
               /* hdudispfcas-CasDisplay-DB-LLR-014 */
               TimerPreset(&(cas_message->Flash_timer), (T_INT32)flash_timer);
               if((REV_VID == cas_message->u8Stat)||(CAS_RED==cas_message->ePenColor))
               {
                  TextDispString((T_INT8*)message_text, u16_display_x, u16_display_y, cas_font,
                                cas_message->ePenColor, TX_NO_FLASH, V_REVERSE, ALIGN_LEFT);
               }
               else if((CAS_AMBER==cas_message->ePenColor)||(CAS_WHITE==cas_message->ePenColor))
               {
                  TextDispString((T_INT8*)message_text, u16_display_x, u16_display_y, cas_font,
                                cas_message->ePenColor, TX_NO_FLASH, V_NORMAL, ALIGN_LEFT);
               }
               else
               {
                  ; /*Do nothing */
               }
            }
         }
      /* hdudispfcas-CasDisplay-DB-LLR-015 */
      u16_item_count = (T_UINT16)(u16_item_count + 1);
   }
   else
   {
      ; /*Do nothing */
   }
      message_index += 1;
   }
}

