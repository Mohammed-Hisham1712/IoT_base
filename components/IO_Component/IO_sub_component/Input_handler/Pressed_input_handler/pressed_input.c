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
/* common file includes */
#include "debug_uart.h"

#include "types.h"
/* othe modules includes */
/* module itself file include */
#include "pressed_input_cfg.h"
#include "pressed_input_private.h"
#include "pressed_input_public.h"
/*---------------------------------------------------------------*/

/*---------------------------------------------------------------*/
/*----------------------------------------*/
/*          2-Section2: defintions        */
/*----------------------------------------*/
/*---------------------------------------------------------------*/

/*----------------------------------------------------*/
/*          3-Section 3: Global Variables definitions */
/*----------------------------------------------------*/
/*---------------------------------------------------------------*/

/* global array to hold all config of all switches*/
PRESSED_SWITCH_CTRL g_pressed_switch_ctrl[PRESSED_SWITCH_MAX_NUMBER] ;

/* default pin configurations for switches */
gpio_hal_pin_t g_default_presses_pin[SWITCH_MAX] = 
                    {
#if PRESSED_SWITCH_MAX_NUMBER >= 1
                        PRESSED_SWITCH_1_PIN ,
#endif
#if PRESSED_SWITCH_MAX_NUMBER >= 2
                        PRESSED_SWITCH_2_PIN ,
#endif
#if PRESSED_SWITCH_MAX_NUMBER >= 3
                        PRESSED_SWITCH_3_PIN ,
#endif
#if PRESSED_SWITCH_MAX_NUMBER >= 4
                        PRESSED_SWITCH_4_PIN ,
#endif
#if PRESSED_SWITCH_MAX_NUMBER >= 5
                        PRESSED_SWITCH_5_PIN ,
#endif
#if PRESSED_SWITCH_MAX_NUMBER >= 6
                        PRESSED_SWITCH_6_PIN ,
#endif
#if PRESSED_SWITCH_MAX_NUMBER >= 7
                        PRESSED_SWITCH_7_PIN ,
#endif

                    };
/*----------------------------------------------------------*/
/*-------------------------------------------------------------*/
/*          4-Section 4: Private functions implementations     */
/*-------------------------------------------------------------*/
/*---------------------------------------------------------------*/
/**
 * @brief if the previous state of the switch is pressed 
 *        Then if current state is released the state of the switch 
 *        is pre_released 
 *        and if the current state is pressed then the state is pressed.
 * 
 * @param c_pressed_switch_num  : this is the switch number to analyze.
 * 
 * @return void : this function returns nothing and the result is saved at 
 *                g_pressed_switch_ctrl global variable.
*/
void run_pressed_handler ( PRESSED_SWITCH_NUM  c_pressed_switch_num ) 
{
    if ( c_pressed_switch_num < PRESSED_SWITCH_MAX_NUMBER ) 
    {
        if ( g_pressed_switch_ctrl[c_pressed_switch_num].current_state == RELEASED  
          && g_pressed_switch_ctrl[c_pressed_switch_num].state == PRESSED
           )
        {
            g_pressed_switch_ctrl[c_pressed_switch_num].state = PRE_RELEASED; 
        }
        else 
        {   
            g_pressed_switch_ctrl[c_pressed_switch_num].state = PRESSED ; 
        }
    }
    else 
    {
        /* error try ro control un exist button*/
    }
    
}
/**
 * @brief if the previous state of the switch is pre_pressed 
 *        Then if current state is released the state of the switch 
 *        is released 
 *        and if the current state is pressed then the state is pressed.
 * 
 * @param c_pressed_switch_num  : this is the switch number to analyze.
 * 
 * @return void : this function returns nothing and the result is saved at 
 *                g_pressed_switch_ctrl global variable.
*/
void run_pre_pressed_handler (PRESSED_SWITCH_NUM  c_pressed_switch_num ) 
{
    if ( c_pressed_switch_num < PRESSED_SWITCH_MAX_NUMBER ) 
    {
        if ( g_pressed_switch_ctrl[c_pressed_switch_num].current_state == PRESSED  
          && g_pressed_switch_ctrl[c_pressed_switch_num].state == PRE_PRESSED
           )
        {
            g_pressed_switch_ctrl[c_pressed_switch_num].state = PRESSED; 
        }
        else if (g_pressed_switch_ctrl[c_pressed_switch_num].current_state == RELEASED  
             &&  g_pressed_switch_ctrl[c_pressed_switch_num].state == PRE_PRESSED)
        {   
            g_pressed_switch_ctrl[c_pressed_switch_num].state = RELEASED ; 
        }
        else 
        {
            g_pressed_switch_ctrl[c_pressed_switch_num].state = PRE_PRESSED;
        }
    }
    else 
    {
        /* error try ro control un exist button*/
    }
}
/**
 * @brief if the previous state of the switch is released 
 *        Then if current state is pressed the state of the switch 
 *        is pre_pressed 
 *        and if the current state is released then the state is released.
 * 
 * @param c_pressed_switch_num  : this is the switch number to analyze.
 * 
 * @return void : this function returns nothing and the result is saved at 
 *                g_pressed_switch_ctrl global variable.
*/
void run_released_handler ( PRESSED_SWITCH_NUM  c_pressed_switch_num ) 
{
    if ( c_pressed_switch_num < PRESSED_SWITCH_MAX_NUMBER ) 
    {
        if ( g_pressed_switch_ctrl[c_pressed_switch_num].current_state == PRESSED  
          && g_pressed_switch_ctrl[c_pressed_switch_num].state == RELEASED
           )
        {
            g_pressed_switch_ctrl[c_pressed_switch_num].state = PRE_PRESSED; 
        }
        else 
        {   
            g_pressed_switch_ctrl[c_pressed_switch_num].state = RELEASED ; 
        }
    }
    else 
    {
        /* error try ro control un exist button*/
    }
}
/**
 * @brief if the previous state of the switch is pre_released
 *        Then if current state is released the state of the switch 
 *        is released 
 *        and if the current state is pressed then the state is pressed.
 * 
 * @param c_pressed_switch_num  : this is the switch number to analyze.
 * 
 * @return void : this function returns nothing and the result is saved at 
 *                g_pressed_switch_ctrl global variable.
*/
void run_pre_released_handler ( PRESSED_SWITCH_NUM  c_pressed_switch_num ) 
{
    if ( c_pressed_switch_num < PRESSED_SWITCH_MAX_NUMBER ) 
    {
        if ( g_pressed_switch_ctrl[c_pressed_switch_num].current_state == RELEASED  
          && g_pressed_switch_ctrl[c_pressed_switch_num].state == PRE_RELEASED
           )
        {
            g_pressed_switch_ctrl[c_pressed_switch_num].state = RELEASED; 
        }
        else if (g_pressed_switch_ctrl[c_pressed_switch_num].current_state == PRESSED  
             &&  g_pressed_switch_ctrl[c_pressed_switch_num].state == PRE_RELEASED)
        {   
            g_pressed_switch_ctrl[c_pressed_switch_num].state = PRESSED ; 
        }
        else 
        {
            g_pressed_switch_ctrl[c_pressed_switch_num].state = PRE_RELEASED;
        }
    }
    else 
    {
        /* error try ro control un exist button*/
    }
}
/*---------------------------------------------------------------*/
/*--------------------------------------------------------*/
/*          5-Section 5: public functions implementations */
/*--------------------------------------------------------*/
/*---------------------------------------------------------------*/
/**
 * @brief 
*/
error_t pressed_switch_init( PRESSED_SWITCH_NUM c_pressed_switch ) 
{
    gpio_hal_config_t switch_mode ;
    switch_mode.mode = GPIO_HAL_MODE_INPUT ; 
    switch_mode.pull = GPIO_HAL_PULL_DOWN  ;
    
    /* Filling ctrl struct of the choosen switch */
    if ( g_default_presses_pin[c_pressed_switch] != NON  )
    {
        int init_result ;
        /* */
        g_pressed_switch_ctrl[c_pressed_switch].switch_pin = g_default_presses_pin[c_pressed_switch] ;
        g_pressed_switch_ctrl[c_pressed_switch].current_state = RELEASED ;
        g_pressed_switch_ctrl[c_pressed_switch].state = RELEASED ;
        init_result = gpio_hal_config(g_pressed_switch_ctrl[c_pressed_switch].switch_pin , &switch_mode ) ;
        uart_send("init result is = ");
        uart_send_int(init_result);
    }
    else 
    {
        /* error try to init undefined switch pin*/
    }
    /* should be changed to error state */
    return TRUE ;
}
/**
 * @brief
*/
error_t pressed_switch_init_all ( void ) 
{
    PRESSED_SWITCH_NUM counter ; 

    for (counter = PRESSED_SWITCH_1 ; counter < PRESSED_SWITCH_MAX_NUMBER ; counter ++ )
    {
        pressed_switch_init(counter) ;
        uart_send("button init is = ");
        uart_send_int(counter);
    }
    /* should be changed to error state */
    return TRUE ; 
} 
/**
 * @brief
*/
PRESSED_SWITCH_STATE pressed_switch_get_state ( PRESSED_SWITCH_NUM c_pressed_switch_num ) 
{
    if ( c_pressed_switch_num < PRESSED_SWITCH_MAX_NUMBER ) 
    {
        return g_pressed_switch_ctrl[c_pressed_switch_num].state ; 
    }
    else 
    {
        /* error try to read an exist button*/
        return FALSE ;
    }
} 
/**
 * @brief
*/
void pressed_switch_run_handler ( void ) 
{
    PRESSED_SWITCH_NUM counter ; 

    for (counter = PRESSED_SWITCH_1 ; counter < PRESSED_SWITCH_MAX_NUMBER ; counter ++ )
    {
        /* read switch state */
        g_pressed_switch_ctrl[counter].current_state = gpio_hal_read (g_pressed_switch_ctrl[counter].switch_pin);
        // uart_send("button read is = ");
        // uart_send_int(g_pressed_switch_ctrl[counter].current_state) ;
        /* analyze current state of the switch*/
        switch (g_pressed_switch_ctrl[counter].state)
        {
        case PRESSED:
            run_pressed_handler(counter) ;
            // uart_send("button is pressed\r\n");
            break;
        case RELEASED:
            run_released_handler(counter) ;
            // uart_send("button is RELEASED\r\n");
            break;
        case PRE_RELEASED :
            run_pre_released_handler(counter) ;
            uart_send("button is pre released\r\n");
            break ;
        case PRE_PRESSED :
            run_pre_pressed_handler(counter) ;
            uart_send("button is pre pre pressed\r\n");
            break ;
        default:
            /* do nothing*/
            break;
        }
    }
}


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
