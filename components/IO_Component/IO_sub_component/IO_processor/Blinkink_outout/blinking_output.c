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
#include "types.h"
#include "debug_uart.h"
#include "pin_driven_handler_public.h"


#include "blinking_output_cfg.h"
#include "blinking_output_private.h"
#include "blinking_output_public.h"

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
blink_pin_ctrl_t g_blink_ctrl;

PIN_DRIVEN_NUM default_blink_pin_table[]=
{
    #ifdef CONFIG_BLINKING_OUTPUT_1
    BLINK_PIN_1_NUM,
    #endif
     #ifdef CONFIG_BLINKING_OUTPUT_2
    BLINK_PIN_2_NUM,
    #endif
     #ifdef CONFIG_BLINKING_OUTPUT_3
    BLINK_PIN_3_NUM,
    #endif
     #ifdef CONFIG_BLINKING_OUTPUT_4
    BLINK_PIN_4_NUM,
    #endif
     #ifdef CONFIG_BLINKING_OUTPUT_5
    BLINK_PIN_5_NUM,
    #endif
     #ifdef CONFIG_BLINKING_OUTPUT_6
    BLINK_PIN_6_NUM,
    #endif
};
/*---------------------------------------------------------------*/
/*-------------------------------------------------------------*/
/*          4-Section 4: Private functions implementations     */
/*-------------------------------------------------------------*/
/*---------------------------------------------------------------*/
BOOL run_pin_blink_routine(blink_pin_t c_pin)
{
    #ifdef DEBUG_run_pin_blink_routine
    debug("\r\n run state of pin num %d",c_pin);
    #endif
    /* check blink state */
    if(g_blink_ctrl.blink_pin[c_pin].blink_flags.blink_on_off == PIN_DRIVEN_ON )
    {
        /*if blink is on */
        #ifdef DEBUG_run_pin_blink_routine
        debug("\r\n pin num %d is on",c_pin);
        #endif
        /* turn on bin */
        pin_driven_set_state_dummy(g_blink_ctrl.blink_pin[c_pin].blink_pin_num,PIN_DRIVEN_ON);
        /* if on timer started */
        if(!g_blink_ctrl.blink_pin[c_pin].timer.timer_state)
        {   
            /*NO start on timer */
            timer_start(&g_blink_ctrl.blink_pin[c_pin].timer);
            #ifdef DEBUG_run_pin_blink_routine
            debug("\r\n pin num %d start on timer",c_pin);
            #endif
        }
        else 
        {
            if(g_blink_ctrl.blink_pin[c_pin].timer.timer_val >= g_blink_ctrl.blink_pin[c_pin].blink_on_time )
            {
                #ifdef DEBUG_run_pin_blink_routine
                debug("\r\n pin num %d end of on timer",c_pin);
                #endif
                timer_reset(&g_blink_ctrl.blink_pin[c_pin].timer); 
                g_blink_ctrl.blink_pin[c_pin].blink_flags.blink_on_off=PIN_DRIVEN_OFF;
            }
            else 
            {
                timer_update(&g_blink_ctrl.blink_pin[c_pin].timer);
            }
        }

    }
    else 
    {
        #ifdef DEBUG_run_pin_blink_routine
        debug("\r\n pin num %d is off",c_pin);
        #endif
        pin_driven_set_state_dummy(g_blink_ctrl.blink_pin[c_pin].blink_pin_num,PIN_DRIVEN_OFF);
        /* if on timer started */
        if(!g_blink_ctrl.blink_pin[c_pin].timer.timer_state)
        {   
            /*NO start on timer */
            timer_start(&g_blink_ctrl.blink_pin[c_pin].timer);
            #ifdef DEBUG_run_pin_blink_routine
            debug("\r\n pin num %d start on off",c_pin);
            #endif
        }
        else 
        {
            if(g_blink_ctrl.blink_pin[c_pin].timer.timer_val >= g_blink_ctrl.blink_pin[c_pin].blink_off_time )
            {
                timer_reset(&g_blink_ctrl.blink_pin[c_pin].timer);
                g_blink_ctrl.blink_pin[c_pin].blink_flags.blink_on_off=PIN_DRIVEN_ON;
                #ifdef DEBUG_run_pin_blink_routine
                debug("\r\n pin num %d end of off period",c_pin);
                #endif
            }
            else 
            {
                #ifdef DEBUG_run_pin_blink_routine
                debug("\r\n update blink timer %d",c_pin);
                #endif
                timer_update(&g_blink_ctrl.blink_pin[c_pin].timer);
            }
        }
    }
    return TRUE;
}

BOOL reset_blink_bin(blink_pin_t c_pin)
{
    pin_driven_set_state(g_blink_ctrl.blink_pin[c_pin].blink_pin_num,PIN_DRIVEN_OFF);
    timer_reset(&g_blink_ctrl.blink_pin[c_pin].timer);
    g_blink_ctrl.blink_pin[c_pin].blink_flags.blink_on_off=1; 
    return TRUE;
}


void timer_update(blink_timer_t * cp_timer)
{
    cp_timer->timer_val += CONFIG_IO_COMPONENT_TASK_PERIOD;
}
void timer_reset(blink_timer_t * cp_timer)
{
    cp_timer->timer_val = 0 ;
    cp_timer->timer_state =FALSE;
}
void timer_start(blink_timer_t * cp_timer)
{
    cp_timer->timer_val = 0 ; 
    cp_timer->timer_state =TRUE;
}
/*---------------------------------------------------------------*/
/*--------------------------------------------------------*/
/*          5-Section 5: public functions implementations */
/*--------------------------------------------------------*/
/*---------------------------------------------------------------*/
BOOL blink_output_get_state(blink_pin_t c_pin, blink_state_t * p_state)
{
    BOOL ret;
    if( c_pin <MAX_NUM_OF_BLINK_PINS )
    {
        *p_state = g_blink_ctrl.blink_pin[c_pin].blink_flags.blink_state;
        ret = TRUE ;
    }
    else 
    {
        ret = FALSE;
    }
    return ret;
}
BOOL blink_output_set_state(blink_pin_t c_pin, blink_state_t  p_state)
{
    BOOL ret;
    if( c_pin <MAX_NUM_OF_BLINK_PINS )
    {
        g_blink_ctrl.blink_pin[c_pin].blink_flags.blink_state = p_state ;
        if(p_state == NOT_BLINKING )
        {
            reset_blink_bin(c_pin);
        }
        ret = TRUE ;
    }
    else 
    {
        ret = FALSE;
    }
    return ret;
}
BOOL blink_output_set_blink_time(blink_pin_t c_pin, uint16_t blink_time)
{
    return TRUE;
}
BOOL blink_output_set_blink_on_time(blink_pin_t c_pin, uint16_t blink_on_time)
{
    BOOL ret;
    if( c_pin <MAX_NUM_OF_BLINK_PINS )
    {
        g_blink_ctrl.blink_pin[c_pin].blink_on_time = blink_on_time ;
        ret = TRUE ;
    }
    else 
    {
        ret = FALSE;
    }
    return ret;
}
BOOL blink_output_set_blink_off_time(blink_pin_t c_pin, uint16_t blink_off_time)
{
    BOOL ret;
    if( c_pin <MAX_NUM_OF_BLINK_PINS )
    {
        g_blink_ctrl.blink_pin[c_pin].blink_off_time = blink_off_time ;
        ret = TRUE ;
    }
    else 
    {
        ret = FALSE;
    }
    return ret;
}
BOOL blink_output_get_blink_on_time(blink_pin_t c_pin, uint16_t *blink_time)
{
    BOOL ret;
    if( c_pin <MAX_NUM_OF_BLINK_PINS )
    {
        *blink_time = g_blink_ctrl.blink_pin[c_pin].blink_on_time;
        ret = TRUE ;
    }
    else 
    {
        ret = FALSE;
    }
    return ret;
}
BOOL blink_output_get_blink_off_time(blink_pin_t c_pin, uint16_t *blink_time)
{
    BOOL ret;
    if( c_pin <MAX_NUM_OF_BLINK_PINS )
    {
        *blink_time = g_blink_ctrl.blink_pin[c_pin].blink_off_time;
        ret = TRUE ;
    }
    else 
    {
        ret = FALSE;
    }
    return ret;
}
BOOL blink_output_init()
{
    uint8_t pin_counter;
    /* run over all blinking pins */
    
    for(pin_counter = BLINK_PIN_1; pin_counter<MAX_NUM_OF_BLINK_PINS; pin_counter++)
    {
        
        g_blink_ctrl.blink_pin[pin_counter].blink_pin_num = default_blink_pin_table[pin_counter];
        reset_blink_bin(pin_counter);
    }
    return TRUE;
}
void blink_output_run()
{
    #if DEBUG_blink_output_run
    debug("\r\nstarting of blink run %d",0)
    #endif
    uint8_t pin_counter;
    /* run over all blinking pins */
    for(pin_counter = BLINK_PIN_1; pin_counter<MAX_NUM_OF_BLINK_PINS; pin_counter++)
    {   
        #if DEBUG_blink_output_run
        debug("\r\nrun blink pin num%d",pin_counter)
        #endif
        /* check blink state if on or off */
        if(g_blink_ctrl.blink_pin[pin_counter].blink_flags.blink_state == BLINKING)
        {
            #if DEBUG_blink_output_run
            debug("\r\npin num%d is blinking",pin_counter)
            #endif
            /* if blink on start blink task for this pin */
            run_pin_blink_routine(pin_counter);
        }
        else 
        {
            #if DEBUG_blink_output_run
            debug("\r\npin num%d is not",pin_counter)
            #endif
            /* if off make sure that this pin is off */
            reset_blink_bin(pin_counter);
        }
    
    }  
    #if DEBUG_blink_output_run
    debug("\r\nend of blink run %d",0)
    #endif
}


BOOL blink_output_start_fast_blink(blink_pin_t c_pin)
{
    blink_output_set_blink_on_time(c_pin,FAST_BLINK_ON_TIME);
    blink_output_set_blink_off_time(c_pin,FAST_BLINK_OFF_TIME);
    blink_output_set_state(c_pin,BLINKING);
    return TRUE;
}
BOOL blink_output_start_slow_blink(blink_pin_t c_pin)
{
    blink_output_set_blink_on_time(c_pin,SLOW_BLINK_ON_TIME);
    blink_output_set_blink_off_time(c_pin,SLOW_BLINK_OFF_TIME);
    blink_output_set_state(c_pin,BLINKING);
    return TRUE;
}
BOOL blink_output_stop_blinking(blink_pin_t c_pin)
{
    blink_output_set_state(c_pin,NOT_BLINKING);
    return TRUE;
}
BOOL blink_output_start_blinking(blink_pin_t c_pin)
{
    blink_output_set_state(c_pin,BLINKING);
    return TRUE;
}

