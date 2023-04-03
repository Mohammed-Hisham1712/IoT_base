                /*-----------------------------*/
                /*          File Data:         */
                /*-----------------------------*/
/*--------------------------------------------------------------
* File Usage : This file is used to control the pin driven output
               type like Relay or led or on-off Triac according to
               input pressed switch like push button or touch input 
               and according to received data from the server.
               Then it analyze the input and read received data then
               take action to turn on or off the output pin
----------------------------------------------------------------
* Creators : 1-Mahmoud Eid
             2-Mohamed Hisham
----------------------------------------------------------------
* History : Creation | 25/3/2023
----------------------------------------------------------------*/

                /*---------------------------*/
                /*          Content:         */
                /*---------------------------*/
/*-------------------------------------------------------------
1-Section 1: Includes
2-Section 2: defintions
3-Section 3: Global Variables definitions
4-Section 4: Private functions implementations
5-Section 5: public functions implementations
6-Section 6"
---------------------------------------------------------------*/


/*---------------------------------------------------------------*/
/*----------------------------------------*/
/*          1-Section 1: Includes         */
/*----------------------------------------*/
/*---------------------------------------------------------------*/
#include "debug_uart.h"
#include "types.h"
#include "pin_driven_handler_public.h"
#include "pressed_input_public.h"


#include "pressed_to_pin_driven_cfg.h"
#include "pressed_to_pin_driven_private.h"
#include "pressed_to_pin_driven_public.h"
/*---------------------------------------------------------------*/
/*----------------------------------------*/
/*          2-Section2: defintions        */
/*----------------------------------------*/
/*---------------------------------------------------------------*/

/*---------------------------------------------------------------*/

/*----------------------------------------------------*/
/*          3-Section 3: Global Variables definitions */
/*----------------------------------------------------*/
/*---------------------------------------------------------------*/
PRESSED_TO_PIN_CTRL g_pressed_pin_ctrl[PRESS_TO_PIN_MAX_PROCESS] ;
PRESSED_PIN_DEFAULT g_pressed_pin_default[PRESSED_TO_PIN_MAX] = 
    {
          { PRESSED_SWITCH_PROCESS_1 , PIN_DRIVEN_PROCESS_1 , SWITCH_1_TYPE},
          { PRESSED_SWITCH_PROCESS_2 , PIN_DRIVEN_PROCESS_2 , SWITCH_2_TYPE},
          { PRESSED_SWITCH_PROCESS_3 , PIN_DRIVEN_PROCESS_3 , SWITCH_3_TYPE},
          { PRESSED_SWITCH_PROCESS_4 , PIN_DRIVEN_PROCESS_4 , SWITCH_4_TYPE},
          { PRESSED_SWITCH_PROCESS_5 , PIN_DRIVEN_PROCESS_5 , SWITCH_5_TYPE},
          { PRESSED_SWITCH_PROCESS_6 , PIN_DRIVEN_PROCESS_6 , SWITCH_6_TYPE},
    };
/*---------------------------------------------------------------*/
/*-------------------------------------------------------------*/
/*          4-Section 4: Private functions implementations     */
/*-------------------------------------------------------------*/
/*---------------------------------------------------------------*/
void process_on_off_switch_type ( uint8_t c_switch_num ) 
{
  g_pressed_pin_ctrl[c_switch_num].pressed_switch_state = 
                pressed_switch_get_state(g_pressed_pin_ctrl[c_switch_num].pressed_switch_num);
  switch (g_pressed_pin_ctrl[c_switch_num].pressed_switch_state )
  {
  case PRESSED:
      /* Do nothing till now */
    break;
  case RELEASED:
      /* Do nothing till now*/
    break;
  case PRE_PRESSED:
      pin_driven_toggle(g_pressed_pin_ctrl[c_switch_num].pin_driven_num ) ;
      uart_send("switch is pre pressed ");
      uart_send_int(c_switch_num);
    break;
  case PRE_RELEASED:
    
    break;
  
  default:
    break;
  }
}
void process_reset_switch_type ( uint8_t c_switch_num ) 
{
  g_pressed_pin_ctrl[c_switch_num].pressed_switch_state = pressed_switch_get_state(c_switch_num);
  switch (g_pressed_pin_ctrl[c_switch_num].pressed_switch_state )
  {
  case PRESSED:
      /* Start Timer */
    break;
  case RELEASED:
      /* Do nothing till now */
    break;
  case PRE_PRESSED:
      /* Do nothing Till now */
    break;
  case PRE_RELEASED:
      /* Read Timer value */
      /* if Timer value > reset value */
          /* set reset condition */
      /* else */
        /* do nothing*/
      /* reset the counter*/
    
    break;
  
  default:
    break;
  }
}

/*---------------------------------------------------------------*/
/*--------------------------------------------------------*/
/*          5-Section 5: public functions implementations */
/*--------------------------------------------------------*/
/*---------------------------------------------------------------*/
void pressed_switch_to_pin_driven_init ( void ) 
{
    uint16_t l_counter;
    for ( l_counter = 0 ; l_counter < PRESS_TO_PIN_MAX_PROCESS ; l_counter ++ )
    {
      /* init on off switch type*/
      if (g_pressed_pin_default[l_counter].switch_ctrl_type == ON_OFF_SWITCH )
      {
        if ( g_pressed_pin_default[l_counter].pin_driven_num != NON 
          && g_pressed_pin_default[l_counter].pressed_switch_num != NON )
          {
            g_pressed_pin_ctrl[l_counter].pin_driven_num = g_pressed_pin_default[l_counter].pin_driven_num ;
            g_pressed_pin_ctrl[l_counter].pressed_switch_num = g_pressed_pin_default[l_counter].pressed_switch_num ;
            g_pressed_pin_ctrl[l_counter].pin_driven_state = PIN_DRIVEN_OFF ; 
            g_pressed_pin_ctrl[l_counter].pressed_switch_state = RELEASED ;
          }
          else 
          {
            /* ERROR try to init undefined pin (critical error) */
          }
      }
      /* Init reset switch type. */
      else if (g_pressed_pin_default[l_counter].switch_ctrl_type == RESET_SWITCH )
      {
        if ( g_pressed_pin_default[l_counter].pressed_switch_num != NON )
        {
            g_pressed_pin_ctrl[l_counter].pressed_switch_num = g_pressed_pin_default[l_counter].pressed_switch_num ;
            g_pressed_pin_ctrl[l_counter].pin_driven_state = PIN_DRIVEN_OFF ; 
            g_pressed_pin_ctrl[l_counter].pressed_switch_state = RELEASED ;
        }
        else 
        {
          /* ERROR try to init undefined switch (critical error )*/
        }
      }
    }
}
void pressed_switch_to_pin_driven_run	( void ) 
{
  uint8_t counter ; 
  for( counter = 0 ; counter < PRESS_TO_PIN_MAX_PROCESS ; counter ++ )
  {
    if ( g_pressed_pin_ctrl[counter].switch_ctrl_type == ON_OFF_SWITCH )
    {
      process_on_off_switch_type(counter);
      // uart_send("process pressed switch num") ;
      // uart_send_int(counter);
      // uart_wait();
    }
    else if ( g_pressed_pin_ctrl[counter].switch_ctrl_type == RESET_SWITCH )
    {
      process_reset_switch_type(counter);
    }
    else 
    {

    }

  }
}



