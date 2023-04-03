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
1-Section 1:  Includes 
2-Section 2:  definitions
3-Section 3:  public data type 
4-Section 4:  public functions
5-Section 5:
6-Section 6"
---------------------------------------------------------------*/

/*--------------Guard-----------*/
#ifndef PRESSED_TO_PIN_DRIVEN_PUBLIC_H
#define PRESSED_TO_PIN_DRIVEN_PUBLIC_H

/*---------------------------------------------------------------*/
        /*-----------------------------------------*/
        /*          1-Section 1:  Includes         */
        /*-----------------------------------------*/
/*---------------------------------------------------------------*/
#include "types.h"
#include "pin_driven_handler_cfg.h"
#include "gpio_hal_config.h"
#include "pressed_input_public.h"
#include "pin_driven_handler_public.h"
/*---------------------------------------------------------------*/
        /*-------------------------------------------*/
        /*          2-Section 2:  definitions        */
        /*-------------------------------------------*/
/*---------------------------------------------------------------*/

/*---------------------------------------------------------------*/
        /*--------------------------------------------------*/
        /*          3-Section 3:  public data type          */
        /*--------------------------------------------------*/
/*---------------------------------------------------------------*/
typedef enum 
{
        PRESSED_TO_PIN1,
        PRESSED_TO_PIN2,
        PRESSED_TO_PIN3,
        PRESSED_TO_PIN4,
        PRESSED_TO_PIN5,
        PRESSED_TO_PIN6,
        PRESSED_TO_PIN7,
        PRESSED_TO_PIN8,
        PRESSED_TO_PIN_MAX
}PRESSED_TO_PIN_NUM;

typedef enum
{
        ON_OFF_SWITCH,
        RESET_SWITCH,
        NOT_USED,
}SWITCH_CTRL_TYPE;

typedef struct 
{
	PRESSED_SWITCH_NUM  pressed_switch_num ;
	PIN_DRIVEN_NUM	pin_driven_num ; 
	PRESSED_SWITCH_STATE pressed_switch_state ;
	PIN_DRIVEN_STATE pin_driven_state ;
        SWITCH_CTRL_TYPE switch_ctrl_type ;
}PRESSED_TO_PIN_CTRL;

typedef struct 
{
	PRESSED_SWITCH_NUM  pressed_switch_num ;
	PIN_DRIVEN_NUM	pin_driven_num ;
        SWITCH_CTRL_TYPE switch_ctrl_type ; 
}PRESSED_PIN_DEFAULT;

/*---------------------------------------------------------------*/
        /*-------------------------------------------------*/
        /*          4-Section 4:  public functions         */
        /*-------------------------------------------------*/
/*---------------------------------------------------------------*/
void pressed_switch_to_pin_driven_init ( void ) ;
void pressed_switch_to_pin_driven_run	( void ) ;

/*---------------------------------------------------------------*/
            /*------------------------------*/
            /*          5-Section5:         */
            /*------------------------------*/
/*---------------------------------------------------------------*/

/*---------------------------------------------------------------*/
            /*------------------------------*/
            /*          6-Section6:         */
            /*------------------------------*/
/*---------------------------------------------------------------*/

/*---------------------------------------------------------------*/
            /*------------------------------*/
            /*          7-Section7:         */
            /*------------------------------*/
/*---------------------------------------------------------------*/

#endif  /*  guard end*/

