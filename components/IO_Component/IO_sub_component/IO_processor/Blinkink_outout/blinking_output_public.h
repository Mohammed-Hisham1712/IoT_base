                /*-----------------------------*/
                /*          File Data:         */
                /*-----------------------------*/
/*--------------------------------------------------------------
* File Usage : 
----------------------------------------------------------------
* Creators : 1-Mahmoud Eid

----------------------------------------------------------------
* History : Creation | 11/5/2023
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
#ifndef BLINKING_OUTPUT_PUBLIC_H
#define BLINKING_OUTPUT_PUBLIC_H

/*---------------------------------------------------------------*/
        /*-----------------------------------------*/
        /*          1-Section 1:  Includes         */
        /*-----------------------------------------*/
/*---------------------------------------------------------------*/
#include "types.h"
/*---------------------------------------------------------------*/
        /*-------------------------------------------*/
        /*          2-Section 2:  definitions        */
        /*-------------------------------------------*/
/*---------------------------------------------------------------*/
typedef enum
{
    BLINK_PIN_1,
    BLINK_PIN_2,
    BLINK_PIN_3,
    BLINK_PIN_4,
    BLINK_PIN_5,
    BLINK_PIN_6,
}blink_pin_t;
typedef enum
{
    NOT_BLINKING,
    BLINKING,
}blink_state_t;
/*---------------------------------------------------------------*/
        /*--------------------------------------------------*/
        /*          3-Section 3:  public data type          */
        /*--------------------------------------------------*/
/*---------------------------------------------------------------*/
/* public functions for custom blinking */
BOOL blink_output_get_state(blink_pin_t c_pin, blink_state_t * p_state);
BOOL blink_output_set_state(blink_pin_t c_pin, blink_state_t  p_state);
BOOL blink_output_set_blink_time(blink_pin_t c_pin, uint16_t blink_time);
BOOL blink_output_set_blink_on_time(blink_pin_t c_pin, uint16_t blink_on_time);
BOOL blink_output_set_blink_off_time(blink_pin_t c_pin, uint16_t blink_off_time);
BOOL blink_output_get_blink_on_time(blink_pin_t c_pin, uint16_t *blink_time);
BOOL blink_output_get_blink_off_time(blink_pin_t c_pin, uint16_t *blink_time);
/* public functions for general blinking */
BOOL blink_output_start_fast_blink(blink_pin_t c_pin);
BOOL blink_output_start_slow_blink(blink_pin_t c_pin);
BOOL blink_output_stop_blinking(blink_pin_t c_pin);
BOOL blink_output_start_blinking(blink_pin_t c_pin);
/* Run functions */
BOOL blink_output_init();
void blink_output_run();
/*---------------------------------------------------------------*/
        /*-------------------------------------------------*/
        /*          4-Section 4:  public functions         */
        /*-------------------------------------------------*/
/*---------------------------------------------------------------*/

/* external component interface apis (connected to component managers apis)*/

#endif  /*  guard end*/

