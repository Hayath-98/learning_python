/*
 ******************************************************************************
 * License Information  :  Howell Instruments, Inc.                           *
 *                         "Licensed Software" and "All rights reserved".     *
 ******************************************************************************
 *  File                : hdudispfpbs.c
 *
 *  Description         : This file provide application interface to the push button Switches.
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
 *      1.1          Shilpa A R       13-Sep-2017             100064
 *      1.2          Shruthi M N      15-Oct-2017             100083
 *      1.3          Shruthi M N      30-Oct-2017             100104
 *      1.4          Shruthi M N,
 *                   Divya G P         04-Nov-2017            100133,100156
 *      1.5          Rona B S	      29-Jun-2020             100259
 *
 * Additional References : None
 *
 ******************************************************************************
 */

#include "hdudispfpbs.h"        /* Consistency check.  */
#include "hdudispfpolygon1.h" /* implements the polygon fill.*/
#include "hdudispfstandard.h"   /* Need TRUE, FALSE, etc.     */
#include "hdudispftimer.h"      /* Need timer for debounce.   */
#include "hdulibstm32f7xxhalrccex.h" /* Defines RCC configurations */
#include "hdudispfucos.h"       /* Need _enable, _disable.    */
#include "hdulibstm32f7xxhalgpio.h" /* Defines GPIO configurations */
#include "hdulibstm32f7xxhal.h" /* Header files for HAL driver*/
#include "hdulibstm32hallegacy.h" /*definition for the STM32Cube HAL constants*/
#include "hdulibbasictypes.h" /* Define standard data types */
#include "hdudispfgrapp.h"           /* routines for all graph */

#define DEBOUNCE     10U   /* Debounce switch for 10 mS. */
#define CHA_MASK     0x01U
#define CHB_MASK     0x02U

#define REPEAT_MASK     (0)   /* Default to nothing repeats. */
#define RESET_9_AND_10  0x300U
#define RESET_1_AND_2   0x03U
#define RESET_5         0x10U
#define RESET_8         0x80U
#define RESET_11_TO_16  0xFC00U
#define RESET_3_TO_8    0xFCU
#define MAX_16_BIT      0xFFFFU
#define RESET_1_TO_13   0x1FFFU
 /* Updated as per PR100083*/
#define RESET_TMR_VAL   -5000

T_PBS   Switches = {0};     /* Results of pbs get.*/

static T_UINT16 New_switches = ZERO;    /* Value of most recent raw pbs. */

static T_UINT16 Switch_mask = (PBS1_M|PBS2_M|PBS3_M|PBS4_M|PBS5_M|PBS6_M|PBS7_M|PBS8_M|
                                             PBS9_M|PBS10_M|PBS11_M|PBS12_M|PBS13_M);

static T_UINT16   Old_switches = 0;          /* Value of last raw pbs.          */
static T_INT32    Sw_timer = 0;              /* Timer for debounce, repeat, etc.*/
/* Updated as per PR100083*/
static T_INT32    Sw_timer_b1=0;
static T_INT8     Switches_used = FALSE;     /* Flag for last valid sw's used.  */
/* Updated as per PR100083*/
static T_INT8     Switches_used_b1 = FALSE;
static T_INT8     Switches_fetched = FALSE;  /* Flag for last sw's used by app. */
static T_UINT16   Good_switches = 0;         /* Value to be returned to app.    */

static T_UINT8    U8_last_encoder_left = 0;       /* Value of last encoder reading.   */
static T_INT8     S8_position_l = 0;   /* Value of most recent raw pbs.   */
static T_UINT8    U8_last_encoder_right = 0;        /* Value of last encoder reading.  */
static T_INT8     S8_position_r = 0;  /* Change in encoder reading.      */

static T_INT8     S8_activity  =  0;    /* Used to support menu timeout.*/
/* Updated as per PR100083*/
T_BOOL Long_press=FALSE;
/* Function prototype */
static void BspSwitchesInit(void);
static void EncoderDriverL(void);
static void EncoderDriverR(void);

/*
 * Function                :  BspSwitchesInit
 *
 * Description             :  Initializes the switches.
 *
 * Formal parameter(s)     :  None
 *
 * Return Value            :  None
 *
 * Assumption              :  None
 *
 */
static void BspSwitchesInit(void)
{
   T_GPIO_INIT   gpio_init_struct = {ZERO};

   /*hdudispfpbs-BspSwitchesInit-DB-LLR-001*/
   __HAL_RCC_GPIOB_CLK_ENABLE();

   /*hdudispfpbs-BspSwitchesInit-DB-LLR-002*/
   __HAL_RCC_GPIOC_CLK_ENABLE();

   /*hdudispfpbs-BspSwitchesInit-DB-LLR-003*/
   gpio_init_struct.Mode = GPIO_MODE_INPUT;
   gpio_init_struct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_4|GPIO_PIN_7|GPIO_PIN_10
                       |GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15;
   gpio_init_struct.Speed = GPIO_SPEED_FAST;
   gpio_init_struct.Pull = GPIO_PULLUP;
   HalGpioInit(GPIOB, &gpio_init_struct);

   /*hdudispfpbs-BspSwitchesInit-DB-LLR-004*/
   gpio_init_struct.Pin = GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7;
   HalGpioInit(GPIOC, &gpio_init_struct);

}

/*
 * Function                : EncoderDriverL
 *
 * Description             : Maintains the shaft encoder position.
 *
 * Formal parameter(s)     : None
 *
 * Return Value            : None
 *
 * Assumption              : None
 *
 */

static void EncoderDriverL(void)
{
   T_UINT16    extract_value = ZERO;
   T_UINT16    new_encoder_val = ZERO;

   /*hdudispfpbs-EncoderDriverL-DB-LLR-001*/
   extract_value = (T_UINT16)GPIOA->IDR;
   extract_value &= RESET_9_AND_10;

   extract_value >>= EIGHT;

   new_encoder_val = U8_last_encoder_left;
   U8_last_encoder_left = (T_UINT8)extract_value;

   new_encoder_val ^= extract_value;

   /* If no change, just exit.*/
   if(ZERO == new_encoder_val)
   {
      return;
   }
   else
   {
      ;/*Do nothing*/
   }

   /* If Channel A did not change.*/
   if(ZERO == (new_encoder_val & CHA_MASK))
   {
      /* If Channel A did not change and is low*/
      if(ZERO == (extract_value & CHA_MASK))
      {
         if(ZERO != (extract_value & CHB_MASK))
         {
            /*hdudispfpbs-EncoderDriverL-DB-LLR-002*/
            S8_position_l = (T_INT8)(S8_position_l - (T_INT8)ONE);
         }
         else
         {
            /*hdudispfpbs-EncoderDriverL-DB-LLR-003*/
            S8_position_l = (T_INT8)(S8_position_l + (T_INT8)ONE);
         }
      }
      else
      {
         if(ZERO != (extract_value & CHB_MASK))
         {
            /*hdudispfpbs-EncoderDriverL-DB-LLR-004*/
            S8_position_l = (T_INT8)(S8_position_l + (T_INT8)ONE);
         }
         else
         {
            /*hdudispfpbs-EncoderDriverL-DB-LLR-005*/
            S8_position_l = (T_INT8)(S8_position_l - (T_INT8)ONE);
         }
      }

   }

   /* If channel B did not change.*/
   else
   {
      /* If Channel B did not change and is low*/
      if(ZERO == (extract_value & CHB_MASK) )
      {
         if(ZERO != (extract_value & CHA_MASK))
         {
            /*hdudispfpbs-EncoderDriverL-DB-LLR-006*/
            S8_position_l = (T_INT8)(S8_position_l + (T_INT8)ONE);
         }
         else
         {
            /*hdudispfpbs-EncoderDriverL-DB-LLR-007*/
            S8_position_l = (T_INT8)(S8_position_l - (T_INT8)ONE);
         }
      }
      else
      {
         if(ZERO != (extract_value & CHA_MASK))
         {
           /*hdudispfpbs-EncoderDriverL-DB-LLR-008*/
            S8_position_l = (T_INT8)(S8_position_l - (T_INT8)ONE);
         }
         else
         {
           /*hdudispfpbs-EncoderDriverL-DB-LLR-009*/
            S8_position_l = (T_INT8)(S8_position_l + (T_INT8)ONE);
         }
      }
   }
}

/*
 *
 * Function                : EncoderDriverR
 *
 * Description             : Maintain the shaft encoder position.
 *
 * Formal parameter(s)     : None
 *
 * Return Value            : None
 *
 * Assumption              : None
 *
 */
static void EncoderDriverR(void)
{
   T_UINT16    extract_value = ZERO;
   T_UINT16    new_encoder_val = ZERO;

   /*hdudispfpbs-EncoderDriverR-DB-LLR-001*/
   extract_value = (T_UINT16)GPIOA->IDR;
   extract_value &= THREE;
   new_encoder_val = U8_last_encoder_right;
   U8_last_encoder_right = (T_UINT8)extract_value;

   new_encoder_val ^= extract_value;

   /* If no change, just exit.*/
   if(ZERO == new_encoder_val)
   {
      return;
   }
   else
   {
      ;/* Does nothing */
   }

   /* If Channel A did not change.*/
   if(ZERO == (new_encoder_val & CHA_MASK))
   {
      /* If Channel A did not change and is low*/
      if(ZERO == (extract_value & CHA_MASK))
      {
         if(ZERO != (extract_value & CHB_MASK))
         {
            /*hdudispfpbs-EncoderDriverR-DB-LLR-002*/
            S8_position_r = (T_INT8)(S8_position_r - (T_INT8)ONE);
         }
         else
         {
            /*hdudispfpbs-EncoderDriverR-DB-LLR-003*/
            S8_position_r = (T_INT8)(S8_position_r + (T_INT8)ONE);
         }
      }
      else
      {
         if(ZERO != (extract_value & CHB_MASK))
         {
            /*hdudispfpbs-EncoderDriverR-DB-LLR-004*/
            S8_position_r = (T_INT8)(S8_position_r + (T_INT8)ONE);
         }
         else
         {
            /*hdudispfpbs-EncoderDriverR-DB-LLR-005*/
            S8_position_r = (T_INT8)(S8_position_r - (T_INT8)ONE);
         }
      }

   }

   /* If channel B did not change.*/
   else
   {
      /* If Channel B did not change and is low*/
      if(ZERO == (extract_value & CHB_MASK))
      {
         if(ZERO != (extract_value & CHA_MASK))
         {
            /*hdudispfpbs-EncoderDriverR-DB-LLR-006*/
            S8_position_r = (T_INT8)(S8_position_r + (T_INT8)ONE);
         }
         else
         {
            /*hdudispfpbs-EncoderDriverR-DB-LLR-007*/
            S8_position_r = (T_INT8)(S8_position_r - (T_INT8)ONE);
         }
      }
      else
      {
         if(ZERO != (extract_value & CHA_MASK))
         {
            /*hdudispfpbs-EncoderDriverR-DB-LLR-008*/
            S8_position_r = (T_INT8)(S8_position_r - (T_INT8)ONE);
         }
         else
         {
            /*hdudispfpbs-EncoderDriverR-DB-LLR-009*/
            S8_position_r = (T_INT8)(S8_position_r + (T_INT8)ONE);
         }
      }
   }
}

/*
 *
 * Function                : HwPbsGet
 *
 * Description             : This function reads the switch closures from the hardware ports.
 *
 * Formal parameter(s)     : None
 *
 * Return Value            : T_UINT16 - A bit field structure with the raw pbs readings
 *
 * Assumption              : None
 *
 */

static T_UINT16 HwPbsGet(void)
{
   T_UINT16    u16_pbs = ZERO ;
   T_UINT16    temp_var = ZERO;

   /*hdudispfpbs-HwPbsGet-DB-LLR-001*/

   temp_var = (T_UINT16)GPIOB->IDR;
   temp_var &= RESET_1_AND_2;
   u16_pbs |= temp_var;

   temp_var = (T_UINT16)GPIOB->IDR;
   temp_var &= RESET_5;
   temp_var >>= TWO;
   u16_pbs |= temp_var;

   temp_var = (T_UINT16)GPIOB->IDR;
   temp_var &= RESET_8;
   temp_var >>= FOUR;
   u16_pbs |= temp_var;

   temp_var = (T_UINT16)GPIOB->IDR;
   temp_var &= RESET_11_TO_16;
   temp_var >>= SIX;
   u16_pbs |= temp_var;

   temp_var = (T_UINT16)GPIOC->IDR;
   temp_var &= RESET_3_TO_8;
   temp_var = (T_UINT16)(temp_var << EIGHT);
   u16_pbs |= temp_var;

   u16_pbs ^= MAX_16_BIT;
   u16_pbs &= RESET_1_TO_13;

   return (u16_pbs);
}

/*
 *
 * Function                : PbsDriver
 *
 * Description             : Called from the discrete task to scan the push button Switches.
 *
 * Formal parameter(s)     : None
 *
 * Return Value            : None
 *
 * Assumption              : None
 *
 */

void PbsDriver(void)
{
   static T_INT8 first_press = TRUE;
   static T_BOOL first_in=TRUE;

   /*hdudispfpbs-PbsDriver-DB-LLR-001*/
   EncoderDriverL();

   /*hdudispfpbs-PbsDriver-DB-LLR-002*/
   EncoderDriverR();

   /*hdudispfpbs-PbsDriver-DB-LLR-003*/
   New_switches = (HwPbsGet() & Switch_mask);

   /*hdudispfpbs-PbsDriver-DB-LLR-004*/
   if (ZERO == New_switches)
   {
      Old_switches = ZERO;
      Splash_b1_press=ZERO;
      return;
   }
   else
   {
      ;/*Do nothing*/
   }

   /*hdudispfpbs-PbsDriver-DB-LLR-005*/
   if (ZERO == Switches_fetched)
   {
      return;
   }
   else
   {
      ;/*Do nothing*/
   }

   /*hdudispfpbs-PbsDriver-DB-LLR-006*/
   if (New_switches != Old_switches)
   {
      Sw_timer = (T_INT32)-DEBOUNCE;
      Switches_used = FALSE;
      first_press = TRUE;
      Old_switches = New_switches;
      /* Updated as per PR100083*/
      if((New_switches & PBS1_M) != ZERO)
      {
         Sw_timer_b1 = RESET_TMR_VAL;
      }

   }
   else
   {
      ;/*Do nothing*/
   }
   /* Updated for PR100133 */
   /*hdudispfpbs-PbsDriver-DB-LLR-012*/
   if(TRUE==first_in && ONE!=Splash_done && ZERO!=Splash_b1_press)
   {
       if(ZERO!=New_switches)
       {
           Splash_b1_press=ONE;
       }
       else
       {
           Splash_b1_press=ZERO;
       }
       first_in=FALSE;
   }
   else
   {
       ;
   }

   if(ONE==Splash_b1_press)
   {
       if(ZERO==New_switches)
       {
           Splash_b1_press=ZERO;
       }
       else
       {
           ;
       }
   }
   else
   {
	   ;
   }
   /* Updated as per PR100083*/
   if (Sw_timer >= (T_INT32)ZERO)
   {
      /*hdudispfpbs-PbsDriver-DB-LLR-008*/
      /* Updated as per PR100083*/
      if ( ((T_INT8)ZERO) != first_press)
      {
         first_press = FALSE;
         Sw_timer = -DELAY_UNTIL_REPEAT;
      }
      else
      {
         /*hdudispfpbs-PbsDriver-DB-LLR-009*/

         Sw_timer = -REP_RATE;
      }

      /*hdudispfpbs-PbsDriver-DB-LLR-010*/
      if (ZERO == Switches_used)
      {
         Good_switches = New_switches;
         Switches_used = TRUE;
         Switches_fetched = FALSE;
      }
      else
      {
         ;/*Do nothing*/
      }
   }
   else
   {
      ;/*Do nothing*/
   }
    /* Updated as per PR100083*/
   if(Sw_timer_b1>= (T_INT32)ZERO)
   {
         /*hdudispfpbs-PbsDriver-DB-LLR-011*/
      if (((New_switches & PBS1_M) & Switch_mask) != ZERO)
      {
       Switches_used_b1=FALSE;
      }
      else
      {
         Switches_used_b1=TRUE;
      }

      if(FALSE==Switches_used_b1)
      {
       Long_press=TRUE;
       Switches_used_b1=TRUE;
      }
      else
      {
       Long_press=FALSE;
      }
   }
   else
   {
    /* Do nothing */
   }

}

/*
 *
 * Function                : PbsGet
 *
 * Description             : This routine is called to collect the Switches which have
 *                                         been pressed since the last call to this routine.
 *
 * Formal parameter(s)     : None
 *
 * Return Value            : None
 *
 * Assumption              : None
 *
 */

void PbsGet(void)
{
   T_UINT16 val_app = ZERO;

   /* Fetch the new switch closures.   */

   /*hdudispfpbs-PbsGet-DB-LLR-001*/
   OS_ENTER_CRITICAL();

   /*hdudispfpbs-PbsGet-DB-LLR-002*/
   val_app = Good_switches;
   Switches_fetched = TRUE;
   Good_switches = ZERO;

   /*hdudispfpbs-PbsGet-DB-LLR-003*/
   OS_EXIT_CRITICAL();

   /*hdudispfpbs-PbsGet-DB-LLR-004*/
   /* Set the value of the push button Switches.   */
   Switches.b1 =  (T_CHAR)((val_app & PBS1_M) != ZERO);
   Switches.b2 =  (T_CHAR)((val_app & PBS2_M) != ZERO);
   Switches.b3 =  (T_CHAR)((val_app & PBS3_M) != ZERO);
   Switches.b4 =  (T_CHAR)((val_app & PBS4_M) != ZERO);
   Switches.b5 =  (T_CHAR)((val_app & PBS5_M) != ZERO);
   Switches.b6 =  (T_CHAR)((val_app & PBS6_M) != ZERO);
   Switches.b7 =  (T_CHAR)((val_app & PBS7_M) != ZERO);
   Switches.b8 =  (T_CHAR)((val_app & PBS8_M) != ZERO);
   Switches.c1 =  (T_CHAR)((val_app & PBS9_M) != ZERO);
   Switches.c2 =  (T_CHAR)((val_app & PBS10_M) != ZERO);
   Switches.c3 =  (T_CHAR)((val_app & PBS11_M) != ZERO);

   Switches.sLE.pressed =  (T_CHAR)((val_app & PBS12_M) != ZERO);
   Switches.sLE.twist = ZERO;

   Switches.sRE.pressed =  (T_CHAR)((val_app & PBS13_M) !=ZERO);
   Switches.sRE.twist = ZERO;

   /*hdudispfpbs-PbsGet-DB-LLR-005*/
   OS_ENTER_CRITICAL();

   S8_activity = ZERO;

   /*hdudispfpbs-PbsGet-DB-LLR-006*/
   if(ZERO != S8_position_l)
   {
      S8_activity = ONE;
      Switches.sLE.twist = S8_position_l;
      S8_position_l = ZERO;
   }
   else
   {
      ; /*Does nothing */
   }

   /*hdudispfpbs-PbsGet-DB-LLR-007*/
   if(ZERO != S8_position_r)
   {
      S8_activity = ONE;
      Switches.sRE.twist = S8_position_r;
      S8_position_r = ZERO;
   }
   else
   {
      ;/* Does nothing */
   }

   /*hdudispfpbs-PbsGet-DB-LLR-008*/
   if(ZERO != HwPbsGet())
   {
      S8_activity = ONE;
   }
   else
   {
      ;/* Does nothing */
   }

   /*hdudispfpbs-PbsGet-DB-LLR-009*/
   Switches.activity = S8_activity;

   /*hdudispfpbs-PbsGet-DB-LLR-010*/
   OS_EXIT_CRITICAL();

   /*hdudispfpbs-PbsGet-DB-LLR-011*/
   Switches.pressed =   Switches.b1|Switches.b2|Switches.b3|Switches.b4|
                     Switches.b5|Switches.b6|Switches.b7;
   Switches.pressed |=  Switches.b8|Switches.c1|Switches.c2|Switches.c3|
                     Switches.sLE.pressed|Switches.sRE.pressed;

   /*hdudispfpbs-PbsGet-DB-LLR-012*/
   Switches.pressed = (T_INT8)(Switches.pressed |((T_INT8)(ZERO != Switches.sLE.twist)|
                         (T_INT8)(ZERO != Switches.sRE.twist)));

   /*hdudispfpbs-PbsGet-DB-LLR-013*/
   /* Set the raw Switches to allow checks for switch combos.  */
   Switches.raw = HwPbsGet();
}

/*
 * Function                : PbsClear
 *
 * Description             : This routine Reset all Switches to not pressed.
 *
 * Formal parameter(s)     : None
 *
 * Return Value            : None
 *
 * Assumption              : None
 *
 */

void PbsClear(void)
{

   /*hdudispfpbs-PbsClear-DB-LLR-001*/
   Switches.b1 =  ZERO;
   Switches.b2 =  ZERO;
   Switches.b3 =  ZERO;
   Switches.b4 =  ZERO;
   Switches.b5 =  ZERO;
   Switches.b6 =  ZERO;
   Switches.b7 =  ZERO;
   Switches.b8 =  ZERO;
   Switches.c1 =  ZERO;
   Switches.c2 =  ZERO;
   Switches.c3 =  ZERO;

   Switches.sLE.pressed =  ZERO;
   Switches.sLE.twist = ZERO;

   Switches.sRE.pressed =  ZERO;
   Switches.sRE.twist = ZERO;

   Switches.pressed = ZERO;
   Switches.activity = ZERO;
   Switches.raw = ZERO;
}


/*
 *
 * Function                : PbsInit
 *
 * Description             : Perform necessary initialization for push button Switches.
 *
 * Formal parameter(s)     : None
 *
 * Return Value            : None
 *
 * Assumption              : None
 *
 */

void PbsInit (void)
{
   /*hdudispfpbs-PbsInit-DB-LLR-001*/
   __HAL_RCC_GPIOA_CLK_ENABLE();

   /*hdudispfpbs-PbsInit-DB-LLR-002*/
   __HAL_RCC_GPIOB_CLK_ENABLE();

   /*hdudispfpbs-PbsInit-DB-LLR-003*/
   __HAL_RCC_GPIOC_CLK_ENABLE();

   /*hdudispfpbs-PbsInit-DB-LLR-004*/
   BspSwitchesInit();

   /*hdudispfpbs-PbsInit-DB-LLR-005*/
   TimerInstall((T_TIMER *)(&Sw_timer));

   TimerInstall((T_TIMER *)(&Sw_timer_b1));
   /*hdudispfpbs-PbsInit-DB-LLR-006*/
   EncoderDriverL();

   /*hdudispfpbs-PbsInit-DB-LLR-007*/
   EncoderDriverR();

   /*hdudispfpbs-PbsInit-DB-LLR-008*/
   S8_position_l    =  ZERO;
   S8_position_r    =  ZERO;
}



