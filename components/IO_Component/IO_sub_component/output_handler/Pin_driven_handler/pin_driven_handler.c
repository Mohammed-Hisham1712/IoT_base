                /*-----------------------------*/
                /*          File Data:         */
                /*-----------------------------*/
/*--------------------------------------------------------------
* File Usage : This File is used to control This output state of 
               pin driven output.
               IO processor module decide state of the pin.
               Then this sub module execute the state.
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
#include "IO_component_param.h"

#include "pin_driven_handler_cfg.h"
#include "pin_driven_handler_public.h"
#include "pin_driven_handler_private.h"
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
PIN_DRIVEN_CTRL g_pin_driven_ctrl[PIN_DRIVEN_MAX_PIN_NUM] ;
/* default pin defintions */
PIN_DRIVEN_NUM g_pin_driven_default_pin[PIN_DRIVEN_MAX] =
            {
#if PIN_DRIVEN_MAX_PIN_NUM >=1  
                PIN_DRIVEN_PIN_1,
#endif
#if PIN_DRIVEN_MAX_PIN_NUM >=2 
                PIN_DRIVEN_PIN_2,
#endif
#if PIN_DRIVEN_MAX_PIN_NUM >=3 
                PIN_DRIVEN_PIN_3,
#endif
#if PIN_DRIVEN_MAX_PIN_NUM >=4 
                PIN_DRIVEN_PIN_4,
#endif
#if PIN_DRIVEN_MAX_PIN_NUM >=5 
                PIN_DRIVEN_PIN_5,
#endif
 #if PIN_DRIVEN_MAX_PIN_NUM >=6 
                PIN_DRIVEN_PIN_6,
#endif
#if PIN_DRIVEN_MAX_PIN_NUM >=7 
                PIN_DRIVEN_PIN_7,
#endif
            };

IO_pin_driven_param_t g_pin_driven_param;

/*---------------------------------------------------------------*/
/*-------------------------------------------------------------*/
/*          4-Section 4: Private functions implementations     */
/*-------------------------------------------------------------*/
/*---------------------------------------------------------------*/

/*---------------------------------------------------------------*/
/*--------------------------------------------------------*/
/*          5-Section 5: public functions implementations */
/*--------------------------------------------------------*/
/*---------------------------------------------------------------*/
/**
 * @brief used to init specific pin 
 * 
 * @param PIN_DRIVEN_NUM : pin number 
 * 
 * @return error_t : init state ( error if failed )
*/
error_t pin_driven_init_pin ( PIN_DRIVEN_NUM c_pin_num) 
{
    gpio_hal_config_t l_pin_config ; 
    l_pin_config.mode = GPIO_HAL_MODE_OUTPUT_PP ;
    l_pin_config.pull = GPIO_HAL_PULL_NONE ; 

    if ( g_pin_driven_default_pin[c_pin_num] != NON )
    {   
        g_pin_driven_ctrl[c_pin_num].pin_num = g_pin_driven_default_pin[c_pin_num] ; 
        // g_pin_driven_ctrl[c_pin_num].pin_state = PIN_DRIVEN_OFF ;
        gpio_hal_config ( g_pin_driven_ctrl[c_pin_num].pin_num , &l_pin_config) ;
    }
    else 
    {
        /* set error try to init un defined pin*/
    }
    
    return TRUE;

}
/**
 * @brief used to init all pins 
 * 
 * @return error_t : init state ( error if failed )
*/
error_t pin_driven_init	( void ) 
{
    PIN_DRIVEN_NUM l_pin_driven_num  ; 
    pin_driven_handler_param_read();
    for ( l_pin_driven_num = PIN_DRIVEN_1 ; l_pin_driven_num < PIN_DRIVEN_MAX_PIN_NUM ; l_pin_driven_num ++ )
    {
        pin_driven_init_pin ( l_pin_driven_num ) ;
    }
    return TRUE ;
}
/**
 * @brief used to set pin to on or off 
 * 
 * @param PIN_DRIVEN_NUM   : pin number 
 * @param PIN_DRIVEN_STATE : pin state on or off
 * 
 * @return error_t : set state result( error if failed )
*/
error_t pin_driven_set_state ( PIN_DRIVEN_NUM c_pin_num, PIN_DRIVEN_STATE c_pin_state) 
{
    if ( c_pin_num < PIN_DRIVEN_MAX_PIN_NUM )
    {
        g_pin_driven_ctrl[c_pin_num].pin_state = c_pin_state ; 
        pin_driven_handler_param_update(c_pin_num);
    }
    else 
    {
        /* set error and return error */
    }
    return TRUE ;
}
/**
 * @brief used to init specific pin 
 * 
 * @param PIN_DRIVEN_NUM : pin number 
 * 
 * @return error_t : init state ( error if failed )
*/
PIN_DRIVEN_STATE pin_driven_get_state (PIN_DRIVEN_NUM c_pin_num) 
{
    PIN_DRIVEN_STATE ret_state ; 
    if ( c_pin_num < PIN_DRIVEN_MAX_PIN_NUM )
    {
        ret_state = g_pin_driven_ctrl[c_pin_num].pin_state ;
    }
    else 
    {
        ret_state = NON ;
    }
    return ret_state ;
}
/**
 * @brief used to init specific pin 
 * 
 * @param PIN_DRIVEN_NUM : pin number 
 * 
 * @return error_t : init state ( error if failed )
*/
error_t pin_driven_toggle (PIN_DRIVEN_NUM c_pin_num ) 
{
    if(c_pin_num < PIN_DRIVEN_MAX_PIN_NUM )
    {
        if ( g_pin_driven_ctrl[c_pin_num].pin_state == PIN_DRIVEN_ON )
        {
            g_pin_driven_ctrl[c_pin_num].pin_state = PIN_DRIVEN_OFF ;
        }
        else 
        {
            g_pin_driven_ctrl[c_pin_num].pin_state = PIN_DRIVEN_ON ;
        }
        pin_driven_handler_param_update(c_pin_num);
    }
    else 
    {
        /* set error */
    }
    return TRUE ;

}
/**
 * @brief used to init specific pin 
 * 
 * @param PIN_DRIVEN_NUM : pin number 
 * 
 * @return error_t : init state ( error if failed )
*/
void pin_driven_run_handler ( void ) 
{
    PIN_DRIVEN_NUM l_pin_driven_num  ; 

    for ( l_pin_driven_num = PIN_DRIVEN_1 ; l_pin_driven_num < PIN_DRIVEN_MAX_PIN_NUM ; l_pin_driven_num ++ )
    {
        if ( g_pin_driven_ctrl[l_pin_driven_num].pin_num != NON )
        {
            /* write */
            gpio_hal_write(g_pin_driven_ctrl[l_pin_driven_num].pin_num , 
                           g_pin_driven_ctrl[l_pin_driven_num].pin_state) ;
            // debug("write gpio num %d with value %d\r\n",g_pin_driven_ctrl[l_pin_driven_num].pin_num ,
            //                                     g_pin_driven_ctrl[l_pin_driven_num].pin_state );
        }
    }
    

}


BOOL pin_driven_handler_mqtt_update(PIN_DRIVEN_NUM c_pin_num,PIN_DRIVEN_STATE c_state )
{
    BOOL ret ;
    if(c_pin_num < PIN_DRIVEN_MAX_PIN_NUM )
    {
        pin_driven_set_state(c_pin_num,c_state);
    }
    else 
    {
        ret = FALSE;
    }
    return ret;
}

BOOL pin_driven_handler_mqtt_get_state(PIN_DRIVEN_NUM c_pin_num,PIN_DRIVEN_STATE *c_state)
{
    BOOL ret ;
    if(c_pin_num < PIN_DRIVEN_MAX_PIN_NUM )
    {
        * c_state = pin_driven_get_state(c_pin_num);
    }
    else 
    {
        ret = FALSE;
    }
    return ret;
}

BOOL pin_driven_handler_param_read(void)
{
    PIN_DRIVEN_NUM l_pin_driven_num;
    IO_comp_param_read(offsetof(IO_component_param_t,pin_driven_param),
                       sizeof(IO_pin_driven_param_t),
                       &g_pin_driven_param);
    // debug("read pin driven param is %d ",l_pin_driven_num);
    for ( l_pin_driven_num = PIN_DRIVEN_1 ; l_pin_driven_num < PIN_DRIVEN_MAX_PIN_NUM ; l_pin_driven_num ++ )
    {
        if ( g_pin_driven_ctrl[l_pin_driven_num].pin_num != NON )
        {
            
            g_pin_driven_ctrl[l_pin_driven_num].pin_state = 
                    (g_pin_driven_param.pin_param_state & (1 << l_pin_driven_num ) );
            // debug("\r\nthe default value of pin driven num %d is %d ",
            //         l_pin_driven_num,
            //         g_pin_driven_ctrl[l_pin_driven_num].pin_state);
        }
    }
    return TRUE ;                 
}
BOOL pin_driven_handler_param_update(PIN_DRIVEN_NUM l_pin_driven_num)
{
    BOOL ret ;
    if(l_pin_driven_num < PIN_DRIVEN_MAX_PIN_NUM )
    {
        if(g_pin_driven_ctrl[l_pin_driven_num].pin_state)
        {
            g_pin_driven_param.pin_param_state |= (1<<l_pin_driven_num);
        }
        else 
        {
            g_pin_driven_param.pin_param_state &= ~(1<<l_pin_driven_num);
        }
        ret = IO_comp_param_write(offsetof(IO_component_param_t,pin_driven_param),
                       sizeof(IO_pin_driven_param_t),
                       &g_pin_driven_param);
    }
    else 
    {
        ret = FALSE ;
    }
    return ret ;
}


