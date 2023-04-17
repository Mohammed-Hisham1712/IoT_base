                /*-----------------------------*/
                /*          File Data:         */
                /*-----------------------------*/
/*--------------------------------------------------------------
* File Usage :  pressed input file is used to handle all inputs
                for the system and save it's data.
                it just read the input value
                and based on input last state decide the input
                current state.
                input cases for this file is
                ( Pressed - preReleased, Released , prePressed )
                This file supposed to run periodically every 20 ms

----------------------------------------------------------------
* Creators : 1- Mahmoud Eid
             2- Mohamed Hisham
----------------------------------------------------------------
* History : 1 - Creation   | 20/03/2023
----------------------------------------------------------------*/

                /*---------------------------*/
                /*          Content:         */
                /*---------------------------*/
/*-------------------------------------------------------------
1-Section 1:  Includes 
2-Section 2:  definitions
3-Section 3:  private data type 
4-Section 4:  private functions declaration
---------------------------------------------------------------*/


/*--------------Guard-----------*/
#ifndef PRESSED_SWITCH_PRIVATE_H
#define PRESSED_SWITCH_PRIVATE_H

/*---------------------------------------------------------------*/
        /*-----------------------------------------*/
        /*          1-Section 1:  Includes         */
        /*-----------------------------------------*/
/*---------------------------------------------------------------*/
#include "types.h"
#include "gpio_hal_itf.h"
#include "pressed_input_public.h"
/*---------------------------------------------------------------*/
        /*-------------------------------------------*/
        /*          2-Section 2:  definitions        */
        /*-------------------------------------------*/
/*---------------------------------------------------------------*/


/*---------------------------------------------------------------*/
        /*--------------------------------------------------*/
        /*          3-Section 3:  private data type          */
        /*--------------------------------------------------*/
/*---------------------------------------------------------------*/
typedef enum 
{
    SWITCH_PRESSED  = GPIO_HAL_LEVEL_HIGH, 
    SWITCH_RELEASED = GPIO_HAL_LEVEL_LOW ,
} SWITCH_PRESSED_STATE_T;

typedef struct  
{
    PRESSED_SWITCH_STATE current_state ;
    PRESSED_SWITCH_STATE state ;
    gpio_hal_pin_t switch_pin ;
    
}PRESSED_SWITCH_CTRL;

/*---------------------------------------------------------------*/
        /*-------------------------------------------------*/
        /*          4-Section 4:  private functions         */
        /*-------------------------------------------------*/
/*---------------------------------------------------------------*/
void run_pressed_handler(PRESSED_SWITCH_NUM  c_pressed_switch_num ) ; 
void run_pre_pressed_handler(PRESSED_SWITCH_NUM  c_pressed_switch_num ) ; 
void run_released_handler(PRESSED_SWITCH_NUM  c_pressed_switch_num ) ;
void run_pre_released_handler(PRESSED_SWITCH_NUM  c_pressed_switch_num ) ;



#endif  /*  guard end*/

