/*
 ******************************************************************************
 * License Information  :  Howell Instruments, Inc.                           *
 *                         "Licensed Software" and "All rights reserved".     *
 ******************************************************************************
 *  File                : hdudispfdemo.c
 *
 *  Description         : This file creates the demo task, reads the data from PDI and
 *                        and creates the data(A429) to be transmitted
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
 *  Author(s)           : Shilpa A R
 *
 *  Version History     :
 * <Version No.>     <Author>          <Date>         <Problem Report No.>
 *
 *      1.1          Shilpa A R      23-Mar-2018             100196
 *      1.2          Rona B.S        30-Mar-2018             100196
 *      1.3          Shruthi M N     05-Apr-2018             100205
 *      1.4          Chaithra J      21-Jun-2020             100259
 *      1.5          Rona B S        29-Jun-2020             100259
 *      1.6          Dhanalakshmi    05-Aug-2020             100270
 *      1.7          Rona B S        28-Sep-2020             100284 
 *      1.8          Dhanalakshmi    16-Apr-2021             100339
 *      1.9          Dhanalakshmi    24-Apr-2021             100344
 *
 * Additional References : None
 *
 ******************************************************************************
 */
#include "hdudispfdemo.h"  /* Provides demo declarations */
#include "hdudispfa429.h"    /* defines the drivers and labels of the a429 */
#include "hdudispfpdidata.h" /* provides pdi declarations */
#include "hdudispfpara.h"    /* prototype for builds faults, message and system information  */
#include "hdudispfdauprofile.h" /* defines the constants for ARINC 825  Message Traffic.*/
#include "hdudispfcbit.h"    /* contains prototypes for CBIT test. */
#include "hdudispfglobalsettings.h" /* Routines to read and write data to NVRAM  */
#include "hdudispfarinc825.h"   /* for max Payload size definition */
#include "hdudispfa825def.h" /*Definitions for arinc 825 communication*/
#include "hdulibbasictypes.h"   /* Define standard types and common macros */

#define EXTRACT_1ST_BYTE 0x00000FF

#define EXTRACT_2BYTE    0x0000FFFF
#define HEX_7F           0x7F
#define DATA_MULTIPLIER  0.001f
#define DATA_OFFSET      0.01f
#define CLEAR_SYS_INFO 0x83FFU
#define ACT_DELAY_WAIT 20U
#define ACT_DELAY      22U
#define NUM_OF_SEQ     35U

/*   Sem to signal task execution.                              */
T_OS_EVENT *Sem_demo_task = ZERO;
/*   Allocate stack for the Demo task.            */
T_OS_STK Demo_task_stk[DEMO_TASK_STK_SIZE] = {ZERO};
T_BOOL Demo_active = FALSE;


static T_A429_DEMO_STRUCT A429_demo_data[2][256]= {ZERO};

static void DoDemo(void);
static void DemoTask(void *pData);


/*
 * Function                :  A429DemoInit
 *
 * Description             :  This function reads the configuration data w.r.t A429 from PDI.
 *
 * Formal parameter(s)     :  None.
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */

void A429DemoInit()
{
   T_UINT16 u16_i=ZERO;
   T_UINT16 port1_indx=0;
   T_UINT16 port2_indx=0;
   T_UINT16 u16_j=0;

   for(u16_i=ZERO;u16_i<A429_settings_cnt;u16_i++)
   {
      if(ONE == A429_cfg_data[u16_i].A429_port)
      {

         if(BNR==A429_cfg_data[u16_i].A429_type)
         {
             /* hdudispfdemo-A429DemoInit-DB-LLR-001 */
            A429_demo_data[0][port1_indx].A429_data.label=
                  A429_cfg_data[u16_i].A429_label;
            A429_demo_data[0][port1_indx].A429_data.sdi=
                  A429_cfg_data[u16_i].A429_sdi;
            A429_demo_data[0][port1_indx].A429_data.type=
                  A429_cfg_data[u16_i].A429_type;
            A429_demo_data[0][port1_indx].A429_data.sig_bits=
                  (T_UINT8)A429_cfg_data[u16_i].label_data.A429_bnr_data.A429_bnr_bits;
            A429_demo_data[0][port1_indx].A429_data.start_bit=
                  (T_UINT8)A429_cfg_data[u16_i].label_data.A429_bnr_data.A429_bnr_start_bit;
            A429_demo_data[0][port1_indx].A429_data.min_val=
                  A429_cfg_data[u16_i].label_data.A429_bnr_data.A429_bnr_min;
            A429_demo_data[0][port1_indx].A429_data.max_val=
                  A429_cfg_data[u16_i].label_data.A429_bnr_data.A429_bnr_max;
            A429_demo_data[0][port1_indx].A429_data.scale_factor=
                  A429_cfg_data[u16_i].label_data.A429_bnr_data.A429_bnr_scale_fact;
            A429_demo_data[0][port1_indx].A429_data.offset=
                  A429_cfg_data[u16_i].label_data.A429_bnr_data.A429_bnr_offset;
            A429_demo_data[0][port1_indx].A429_data.timeout=
                  (T_UINT16)A429_cfg_data[u16_i].label_data.A429_bnr_data.A429_bnr_timeout;
            A429_demo_data[0][port1_indx].data =
                    (T_FLOAT)(A429_demo_data[0][port1_indx].A429_data.max_val/TWO);
            port1_indx++;
         }
         else if(DDW==A429_cfg_data[u16_i].A429_type)
         {
            if((Cas_cnt!=ZERO) && (A429_cfg_data[u16_i].A429_label==Cas_msg[0].label))
            {
               for(u16_j=ZERO;u16_j<CAU_WARN_MAX_ID;u16_j++)
               {
                  /*
                   * Caution/warning label is received with 6 IDs.
                   * Hence same label is stored in 6 continuous indices of Parameters
                   */
                   /* hdudispfdemo-A429DemoInit-DB-LLR-002 */
                  A429_demo_data[0][port1_indx].A429_data.label=
                        A429_cfg_data[u16_i].A429_label;
                  A429_demo_data[0][port1_indx].A429_data.sdi=
                        A429_cfg_data[u16_i].A429_sdi;
                  A429_demo_data[0][port1_indx].A429_data.type=
                        A429_cfg_data[u16_i].A429_type;
                  A429_demo_data[0][port1_indx].A429_data.sig_bits=DDW_SIG_BIT;
                  A429_demo_data[0][port1_indx].A429_data.start_bit=ONE;
                  A429_demo_data[0][port1_indx].A429_data.min_val=ONE;
                  A429_demo_data[0][port1_indx].A429_data.max_val=ONE;
                  A429_demo_data[0][port1_indx].A429_data.scale_factor=ONE;
                  A429_demo_data[0][port1_indx].A429_data.timeout=
                  (T_UINT16)A429_cfg_data[u16_i].label_data.A429_ddw_timeout;
                  port1_indx++;
               }
            }
            else
            {
                /* hdudispfdemo-A429DemoInit-DB-LLR-003 */
               A429_demo_data[0][port1_indx].A429_data.label=
                     A429_cfg_data[u16_i].A429_label;
               A429_demo_data[0][port1_indx].A429_data.sdi=
                     A429_cfg_data[u16_i].A429_sdi;
               A429_demo_data[0][port1_indx].A429_data.type=
                     A429_cfg_data[u16_i].A429_type;
               A429_demo_data[0][port1_indx].A429_data.sig_bits=DDW_SIG_BIT;
               A429_demo_data[0][port1_indx].A429_data.start_bit=ONE;
               A429_demo_data[0][port1_indx].A429_data.min_val=ONE;
               A429_demo_data[0][port1_indx].A429_data.max_val=ONE;
               A429_demo_data[0][port1_indx].A429_data.scale_factor=ONE;
               A429_demo_data[0][port1_indx].A429_data.timeout=
                     (T_UINT16)A429_cfg_data[u16_i].label_data.A429_ddw_timeout;

               port1_indx++;
            }

         }
         else
         {
            ;/* Do Nothing */
         }
      }
      else if (TWO == A429_cfg_data[u16_i].A429_port)
      {
         if(BNR==A429_cfg_data[u16_i].A429_type)
         {
             /* hdudispfdemo-A429DemoInit-DB-LLR-004 */
            A429_demo_data[1][port2_indx].A429_data.label=
                  A429_cfg_data[u16_i].A429_label;
            A429_demo_data[1][port2_indx].A429_data.sdi=
                  A429_cfg_data[u16_i].A429_sdi;
            A429_demo_data[1][port2_indx].A429_data.type=
                  A429_cfg_data[u16_i].A429_type;
            A429_demo_data[1][port2_indx].A429_data.sig_bits=
                  (T_UINT8)A429_cfg_data[u16_i].label_data.A429_bnr_data.A429_bnr_bits;
            A429_demo_data[1][port2_indx].A429_data.start_bit=
                  (T_UINT8)A429_cfg_data[u16_i].label_data.A429_bnr_data.A429_bnr_start_bit;
            A429_demo_data[1][port2_indx].A429_data.min_val=
                  A429_cfg_data[u16_i].label_data.A429_bnr_data.A429_bnr_min;
            A429_demo_data[1][port2_indx].A429_data.max_val=
                  A429_cfg_data[u16_i].label_data.A429_bnr_data.A429_bnr_max;
            A429_demo_data[1][port2_indx].A429_data.scale_factor=
                  A429_cfg_data[u16_i].label_data.A429_bnr_data.A429_bnr_scale_fact;
            A429_demo_data[1][port2_indx].A429_data.offset=
                  A429_cfg_data[u16_i].label_data.A429_bnr_data.A429_bnr_offset;
            A429_demo_data[1][port2_indx].A429_data.timeout=
                  (T_UINT16)A429_cfg_data[u16_i].label_data.A429_bnr_data.A429_bnr_timeout;
            A429_demo_data[1][port2_indx].data =
                    (T_FLOAT)(A429_demo_data[1][port2_indx].A429_data.max_val/TWO);
            port2_indx++;
         }
         else if(DDW==A429_cfg_data[u16_i].A429_type)
         {
            if((Cas_cnt!=ZERO) && (A429_cfg_data[u16_i].A429_label==Cas_msg[0].label))
            {
               /* hdudispfdemo-A429DemoInit-DB-LLR-005 */
               Cas_label_start_idx=(T_UINT16)(port2_indx+1);
               for(u16_j=ZERO;u16_j<CAU_WARN_MAX_ID;u16_j++)
               {
                  /*
                   * Caution/warning label is received with 6 IDs.
                   * Hence same label is stored in 6 continuous indices of Parameters
                   */
                  A429_demo_data[1][port2_indx].A429_data.label=
                        A429_cfg_data[u16_i].A429_label;
                  A429_demo_data[1][port2_indx].A429_data.sdi=
                        A429_cfg_data[u16_i].A429_sdi;
                  A429_demo_data[1][port2_indx].A429_data.type=
                        A429_cfg_data[u16_i].A429_type;
                  A429_demo_data[1][port2_indx].A429_data.sig_bits=DDW_SIG_BIT;
                  A429_demo_data[1][port2_indx].A429_data.start_bit=ONE;
                  A429_demo_data[1][port2_indx].A429_data.min_val=ONE;
                  A429_demo_data[1][port2_indx].A429_data.max_val=ONE;
                  A429_demo_data[1][port2_indx].A429_data.scale_factor=ONE;
                  A429_demo_data[1][port2_indx].A429_data.timeout=
                       (T_UINT16)A429_cfg_data[u16_i].label_data.A429_ddw_timeout;
                  port2_indx++;
               }
            }
            else
            {
               /* hdudispfdemo-A429DemoInit-DB-LLR-006 */
               A429_demo_data[1][port2_indx].A429_data.label=
                     A429_cfg_data[u16_i].A429_label;
               A429_demo_data[1][port2_indx].A429_data.sdi=
                     A429_cfg_data[u16_i].A429_sdi;
               A429_demo_data[1][port2_indx].A429_data.type=
                     A429_cfg_data[u16_i].A429_type;
               A429_demo_data[1][port2_indx].A429_data.sig_bits=DDW_SIG_BIT;
               A429_demo_data[1][port2_indx].A429_data.start_bit=ONE;
               A429_demo_data[1][port2_indx].A429_data.min_val=ONE;
               A429_demo_data[1][port2_indx].A429_data.max_val=ONE;
               A429_demo_data[1][port2_indx].A429_data.scale_factor=ONE;
               A429_demo_data[1][port2_indx].A429_data.timeout=
                     (T_UINT16)A429_cfg_data[u16_i].label_data.A429_ddw_timeout;
               port2_indx++;
            }
         }
         else
         {
            ;/* Do nothing */
         }
      }
      else
      {
         ; /* Do nothing */
      }
   }

}

/*
 * Function                :  DoDemo
 *
 * Description             :  This function builds the A429 message to be transmitted
 *                            and Transmit the A825 message.
 *
 * Formal parameter(s)     :  None.
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */

static void DoDemo(void)
{
   T_A825_MESSAGE tx_msg = {ZERO};

   static T_UINT32 cas_cnt = 0,
           airframe_seq=0;
   T_INT32    *ps32_payload = NULL;
   T_UINT8    channel = 0;
   T_UINT16   label_cnt = 0;
   T_UINT8 demo_label = ZERO,
         cas_label = ZERO,
         exceed_label =ZERO;
   T_UINT8  sdi_val = 0;
   T_FLOAT  data = 0;
   T_INT32 ssm_val = 0;
   T_BOOL update = FALSE,
        transmit = FALSE,
        airframe_trans=FALSE;
   static T_UINT32 transmit_cnt = 0;
   static T_UINT32 u32_time = 20;
   T_UINT32 u32_seconds_data = ZERO;
   static T_BOOL red_value = FALSE;
   T_BOOL update_timer = FALSE;
   T_UINT8 tmr_index = ZERO;
   T_BOOL timer_label_found = FALSE;
   static T_UINT32 timer_cnt = 0;

   /* hdudispfdemo-DoDemo-DB-LLR-001 */
   U16_message_words[1] |= FOUR;

   /*   Init. tx_msg to the defaults for a NSC request.   */
   /* hdudispfdemo-DoDemo-DB-LLR-002 */
   INIT_NOC_MESSAGE(tx_msg);
   tx_msg.u8PaySize      = PAYLOAD_SIZE;

   /* hdudispfdemo-DoDemo-DB-LLR-003 */
   /* extract out Label */
   cas_label = Cas_msg[0].label;
   /*Flip MSB with LSB to read correct octal value */
   cas_label = (T_UINT8)((cas_label & HEX_F0)>>FOUR|(cas_label & HEX_0F)<<FOUR);
   cas_label = (T_UINT8)((cas_label & HEX_CC)>>TWO|(cas_label & HEX_33)<<TWO);
   cas_label = (T_UINT8)((cas_label & HEX_AA)>>ONE|(cas_label & HEX_55)<<ONE);

   /* hdudispfdemo-DoDemo-DB-LLR-004 */
   exceed_label = Exceed_data[0].label;
   exceed_label = (T_UINT8)((exceed_label & HEX_F0)>>FOUR|(exceed_label & HEX_0F)<<FOUR);
   exceed_label = (T_UINT8)((exceed_label & HEX_CC)>>TWO|(exceed_label & HEX_33)<<TWO);
   exceed_label = (T_UINT8)((exceed_label & HEX_AA)>>ONE|(exceed_label & HEX_55)<<ONE);

   /* hdudispfdemo-DoDemo-DB-LLR-005 */
   transmit_cnt++;
   if(transmit_cnt >= FIFTY)
   {
      transmit_cnt = ZERO;
      transmit = TRUE;
   }
   else
   {
      ; /* Do nothing */
   }

   for(channel = 0; channel<MAX_A429_CHANNEL; channel++)
   {
      for(label_cnt = 0; label_cnt<MAX_A429_LABELS; label_cnt++)
      {
        /* hdudispfdemo-DoDemo-DB-LLR-006 */
         tx_msg.sID.BID.doc= (DEMO_DOC_ID+channel) & DOC_MSK;

         ps32_payload = (T_INT32 *)tx_msg.u8PayLoad;

        demo_label = A429_demo_data[channel][label_cnt].A429_data.label;

       /*Flip MSB with LSB to read correct octal value */
       demo_label = (T_UINT8)((demo_label & HEX_F0)>>FOUR|(demo_label & HEX_0F)<<FOUR);
       demo_label = (T_UINT8)((demo_label & HEX_CC)>>TWO|(demo_label & HEX_33)<<TWO);
       demo_label = (T_UINT8)((demo_label & HEX_AA)>>ONE|(demo_label & HEX_55)<<ONE);

       /* Check if sdi's are considered for determining the engines */

       if(ONE == Config_data.eng_sdi)
       {
           sdi_val = A429_demo_data[channel][label_cnt].A429_data.sdi;
       }
       else
       {
           sdi_val = (T_UINT8)(channel+1);
       }

  	   for(tmr_index=0; tmr_index< Timer_cnt; tmr_index++)
  	   {
  		 if((Page_settings.Timer_settings[tmr_index].timer_label ==
  		     A429_demo_data[channel][label_cnt].A429_data.label) &&
  		     (Page_settings.Timer_settings[tmr_index].timer_sdi ==
  		      A429_demo_data[channel][label_cnt].A429_data.sdi))
  		 {
  			timer_label_found = TRUE;
     	   timer_cnt++;
     	   if(ZERO==(timer_cnt % THOUSAND_FIVE_HUNDRED))
     	   {
     		   update_timer = TRUE;
     	   }
		   else
		   {
		      ; 
		   } 
  			break;
  		 }
  		 else
  		 {
  			timer_label_found = FALSE;
  		 }
  	   }

       data =  A429_demo_data[channel][label_cnt].data;

       A429_demo_data[channel][label_cnt].localtimer++;

       if(DDW == A429_demo_data[channel][label_cnt].A429_data.type)
       {

          /* hdudispfdemo-DoDemo-DB-LLR-007 */
          if(A429_demo_data[channel][label_cnt].localtimer > TWO_THOUSAND)
          {
            update = TRUE;
            A429_demo_data[channel][label_cnt].localtimer = 0;
          }
          else
          {
             ;/* Do nothing */
          }
          ssm_val = 0;
          if(TRUE == update)
          {
           /* Value has been incremented by 1.0f because type of 'data' variable is float */
           A429_demo_data[channel][label_cnt].data =
                  A429_demo_data[channel][label_cnt].data + 1.0f;
          }
          else
          {
            ;/* Do nothing */
          }

          /*add ID Detection and rotation */
          if(demo_label == cas_label)
          {
             /* hdudispfdemo-DoDemo-DB-LLR-008 */
            if(data >= (T_FLOAT)MAX_CAS_DATA)
            {
              A429_demo_data[channel][label_cnt].data = 0;
            }
            else
            {
               ;/* Do nothing */
            }
            data = (T_FLOAT)(((T_INT32)data<<TEN)|((T_INT32)cas_cnt<<TWENTY_SIX));
            cas_cnt++;

            if (cas_cnt > MAX_CAS_COUNT)
            {
             cas_cnt = 0;
            }
            else
            {
               ;/* Do nothing */
            }
          }
          /* hdudispfdemo-DoDemo-DB-LLR-009 */
          else if (demo_label == exceed_label)
          {
            if(data >= (T_FLOAT)MAX_EXCEE_DATA)
            {
               A429_demo_data[channel][label_cnt].data = 0;
            }
            else
            {
               ;
            }
            data = (T_FLOAT)((T_INT32)data<<TEN);
          }
          else if(LABEL_0370 == A429_demo_data[channel][label_cnt].A429_data.label)
          {
              data=(T_FLOAT)((T_INT32)airframe_seq << TEN);

              airframe_trans=TRUE;

              if(++airframe_seq > NUM_OF_SEQ)
              {
                  airframe_seq=ZERO;
              }
          }
          else if (LABEL_0360 == A429_demo_data[channel][label_cnt].A429_data.label)
          {
              data=0;
              U16_sys_info_words[1] &=CLEAR_SYS_INFO;
          }
          else if(TRUE == timer_label_found)
		  {
    		  if(FALSE == red_value)
    		  {
        	    data = 137;
        	    u32_seconds_data = TWO;
        	    u32_seconds_data = u32_seconds_data | (u32_time << THREE) ;
        	    //u32_time--;
    		  }
    		  else
    		  {
    			  ; /* Does nothing */
    		  }
    		  if(TRUE == red_value)
    		  {
    		    data = 265;
    		    u32_seconds_data = TWO;
        	    u32_seconds_data = u32_seconds_data | (u32_time << THREE) ;
    		  }
    		  else
    		  {
    			  ; /* Does nothing */
    		  }
    		  A429_demo_data[channel][label_cnt].data = (T_FLOAT)u32_seconds_data;
    		  if (TRUE == update_timer)
    		  {
    		    if((u32_time > ZERO) && (FALSE == red_value))
    		    {
    			   u32_time = u32_time - ONE;
    		    }
    		    else if((ZERO == u32_time) && (FALSE == red_value))
        	    {
        		   red_value = TRUE;
        	    }
        	    else
        	    {
        		   u32_time = u32_time + ONE;
        		   if(u32_time >= MAX_EXCEED_TIME)
        		   {
        			   u32_time = ZERO;
        		   }
        	    }
    		    update_timer = FALSE;
    		  }
    		  else
    		  {
    			  ; /* Do nothing */
    		  }

		  }
          else
          {
            /* hdudispfdemo-DoDemo-DB-LLR-010 */
           if(data >= (T_FLOAT)MAX_A429_DATA_VALUE)
           {
             A429_demo_data[channel][label_cnt].data = 0;
           }
           else
           {
              ;
           }
            data = (T_FLOAT)((T_INT32)data<<TEN);
         }
      }
      else
      {
         /* hdudispfdemo-DoDemo-DB-LLR-011 */
         if(A429_demo_data[channel][label_cnt].localtimer > label_cnt)
         {
           update = TRUE;
           A429_demo_data[channel][label_cnt].localtimer = 0;
         }
         else
         {
            ;
         }

         ssm_val = THREE;
         /* hdudispfdemo-DoDemo-DB-LLR-012 */
         /*
          * The two macros DATA_MULTIPLIER and DATA_OFFSET is used to determine the next value
          * of the parameter in demo mode
          */
         if(TRUE == update)
         {
           if(TRUE == A429_demo_data[channel][label_cnt].FWD)
           {
              A429_demo_data[channel][label_cnt].data =
                  A429_demo_data[channel][label_cnt].data +
                  ((T_FLOAT)A429_data[channel][label_cnt].scale_factor);
           }
           else
           {
             A429_demo_data[channel][label_cnt].data =
                A429_demo_data[channel][label_cnt].data -
                ((T_FLOAT)A429_data[channel][label_cnt].scale_factor);
           }
         }
         else
         {
            ;
         }

         /* hdudispfdemo-DoDemo-DB-LLR-013 */
         if (data >= A429_demo_data[channel][label_cnt].A429_data.max_val)
         {
           A429_demo_data[channel][label_cnt].FWD = FALSE;

         }
         else if(data <= A429_demo_data[channel][label_cnt].A429_data.min_val)
         {
           A429_demo_data[channel][label_cnt].FWD = TRUE;
         }
         else
         {
            ;
         }
         /* hdudispfdemo-DoDemo-DB-LLR-014 */

         data = (T_FLOAT)((T_INT32)(data/A429_data[channel][label_cnt].scale_factor)
               <<((T_UINT32)A429_data[channel][label_cnt].start_bit-1));
         /* To ensure bits 32,31,29 are not set from data values*/
         data =(T_FLOAT)((T_INT32)data & (T_INT32)0x1FFFFFFF);
      }

      /* hdudispfdemo-DoDemo-DB-LLR-015 */
      if((TRUE == update)||(TRUE == transmit)||(TRUE==airframe_trans))
      {
 	     if(TRUE!= timer_label_found)
 	     {
          *ps32_payload = ((T_INT32)demo_label)|(((T_INT32)sdi_val)<<EIGHT)
                  |(((T_INT32)data))| (((T_INT32)ssm_val)<<TWENTY_NINE);
         A8251Xmit(&tx_msg);
         update = FALSE;
         airframe_trans=FALSE;
 	     }
 	     else
 	     {
 	    	 ;
 	     }

      }
      else
      {
         ;/* Do nothing */
      }
	     if(TRUE== timer_label_found)
	     {
        *ps32_payload = ((T_INT32)demo_label)|(((T_INT32)sdi_val)<<EIGHT)
         |(((T_INT32)data<<TEN))| (((T_INT32)ssm_val)<<TWENTY_NINE);
         A8251Xmit(&tx_msg);
        *ps32_payload = ((T_INT32)demo_label)|(((T_INT32)sdi_val)<<EIGHT)
         |(((T_INT32)u32_seconds_data<<TEN))| (((T_INT32)ssm_val)<<TWENTY_NINE);
         A8251Xmit(&tx_msg);
	    }
	    else
	    {
        ; /*Do nothing */
        }
      } /* end of label count for loop */

   } /* end of channel count for loop */
}


/*
 *
 * Function                : DemoTask
 *
 * Description             : Function reads A429 and CAN data from PDI, activates the DEMO
 *                           functionality.
 *
 * Formal parameter(s)     : *p_data - IN pointer to null data(not used)
 *
 * Return Value            : None
 *
 * Assumption              : None
 *
 */

static void DemoTask(void *p_data)
{
   T_UINT8 u8_err = 0;
   static T_UINT32 act_delay = 0;
   static T_BOOL firstin = TRUE;

   p_data =(T_UINT8 *)p_data + ZERO;

  /*hdudispfdemo-DemoTask-DB-LLR-001*/
   while (TRUE)
    {
      OsSemPend(Sem_demo_task, 0, &u8_err);

      if((Demo_mode>0) && (Demo_mode_activate>0))
      {
         if(act_delay > ACT_DELAY_WAIT)
         {
            act_delay = ACT_DELAY;

            if( FALSE !=firstin)
            {
               firstin = FALSE;
               CAN1DemoConfig();
               A429DemoInit();
            }
            else
            {
               ; /* Do nothing */
            }

            Demo_active = TRUE;
            DoDemo();
         }
         else
         {
            act_delay++;
         }
      }

   }
}

/*
 *
 * Function                : DemoSignalTask
 *
 * Description             : This function is used to signal the Demo task.
 *
 * Formal parameter(s)     : None
 *
 * Return Value            : None
 *
 * Assumption              : None
 *
 */

void DemoSignalTask(void)
{
   static T_UINT16 u16_tick_cntr = 0;

   /*hdudispfdemo-DemoSignalTask-DB-LLR-001*/
   u16_tick_cntr =(T_UINT16)(u16_tick_cntr + ONE);

   /*hdudispfdemo-DemoSignalTask-DB-LLR-002*/
   if (u16_tick_cntr >= DEMO_TASK_TICKS)
   {
      u16_tick_cntr = ZERO;
      OsSemPost(Sem_demo_task);
   }
   else
   {
      ; /* Do nothing */
   }
}

/*
 *
 * Function                : DemoInit
 *
 * Description             : This function is scheduled once per mSec to debounce the
 *                           discrete inputs.
 *
 * Formal parameter(s)     : None
 *
 * Return Value            : None
 *
 * Assumption              : None
 *
 */

void DemoInit(void)
{
   T_UINT16 u16_ctr = 0;

   /*hdudispfdemo-DemoInit-DB-LLR-001*/
   /* Initialize semaphore for application task */
   Sem_demo_task = OsSemCreate(ZERO);

   /*hdudispfdemo-DemoInit-DB-LLR-002*/
   /* Initialize the stack for run time checks*/
   for(u16_ctr=0; u16_ctr < DEMO_TASK_STK_SIZE; u16_ctr++)
   {
      Demo_task_stk[u16_ctr] = STK_VAL;
   }

   /*hdudispfdemo-DemoInit-DB-LLR-003*/
   /* Create InitTask as the first task to run of RTOS */
   OsTaskCreate(DemoTask, NULL, &Demo_task_stk[DEMO_TASK_STK_SIZE], DEMO_TASK_PRIO);
}

