                /*-----------------------------*/
                /*          File Data:         */
                /*-----------------------------*/
/*--------------------------------------------------------------
* File Usage :      
----------------------------------------------------------------
* Creators : 
----------------------------------------------------------------
* History : 
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
#ifndef PIN_DRIVEN_HANDLER_PUBLIC_H
#define PIN_DRIVEN_HANDLER_PUBLIC_H

/*---------------------------------------------------------------*/
        /*-----------------------------------------*/
        /*          1-Section 1:  Includes         */
        /*-----------------------------------------*/
/*---------------------------------------------------------------*/
#include "types.h"
#include "pin_driven_handler_cfg.h"
#include "gpio_hal_config.h"
/*---------------------------------------------------------------*/
        /*-------------------------------------------*/
        /*          2-Section 2:  definitions        */
        /*-------------------------------------------*/
/*---------------------------------------------------------------*/
#define LEVEL_LWO       (0)
#define LEVEL_HIGH      (1)
/*---------------------------------------------------------------*/
        /*--------------------------------------------------*/
        /*          3-Section 3:  public data type          */
        /*--------------------------------------------------*/
/*---------------------------------------------------------------*/
typedef enum 
{
        PIN_DRIVEN_1 ,
	PIN_DRIVEN_2 ,
	PIN_DRIVEN_3 ,
	PIN_DRIVEN_4 ,
	PIN_DRIVEN_5 ,
	PIN_DRIVEN_6 ,
	PIN_DRIVEN_7 ,
	PIN_DRIVEN_8 ,
	PIN_DRIVEN_MAX ,
}PIN_DRIVEN_NUM ;

typedef enum 
{
	PIN_DRIVEN_OFF = LEVEL_LWO,
	PIN_DRIVEN_ON  = LEVEL_HIGH,
	PIN_DRIVEN_UNDEFINED
}PIN_DRIVEN_STATE ;
typedef struct  
{
	PIN_DRIVEN_NUM 		pin_num ; 
	PIN_DRIVEN_STATE	pin_state ;	 
}PIN_DRIVEN_CTRL;

/*---------------------------------------------------------------*/
        /*-------------------------------------------------*/
        /*          4-Section 4:  public functions         */
        /*-------------------------------------------------*/
/*---------------------------------------------------------------*/
/**
 * @brief used to init specific pin 
 * 
 * @param PIN_DRIVEN_NUM : pin number 
 * 
 * @return error_t : init state ( error if failed )
*/
error_t pin_driven_init_pin ( PIN_DRIVEN_NUM c_pin_num) ;
/**
 * @brief used to init all pins 
 * 
 * @return error_t : init state ( error if failed )
*/
error_t pin_driven_init	( void ) ;
/**
 * @brief used to set pin to on or off 
 * 
 * @param PIN_DRIVEN_NUM   : pin number 
 * @param PIN_DRIVEN_STATE : pin state on or off
 * 
 * @return error_t : set state result( error if failed )
*/
error_t pin_driven_set_state ( PIN_DRIVEN_NUM c_pin_num, PIN_DRIVEN_STATE c_pin_state) ;
error_t pin_driven_set_state_dummy( PIN_DRIVEN_NUM c_pin_num, PIN_DRIVEN_STATE c_pin_state) ;
/**
 * @brief used to init specific pin 
 * 
 * @param PIN_DRIVEN_NUM : pin number 
 * 
 * @return error_t : init state ( error if failed )
*/
PIN_DRIVEN_STATE pin_driven_get_state (PIN_DRIVEN_NUM c_pin_num) ;
/**
 * @brief used to init specific pin 
 * 
 * @param PIN_DRIVEN_NUM : pin number 
 * 
 * @return error_t : init state ( error if failed )
*/
error_t pin_driven_toggle (PIN_DRIVEN_NUM c_pin_num ) ; 
error_t pin_driven_toggle_dummy(PIN_DRIVEN_NUM c_pin_num ) ; 
/**
 * @brief used to init specific pin 
 * 
 * @param PIN_DRIVEN_NUM : pin number 
 * 
 * @return error_t : init state ( error if failed )
*/
void pin_driven_run_handler ( void ) ;

BOOL pin_driven_handler_mqtt_update(PIN_DRIVEN_NUM c_pin_num, PIN_DRIVEN_STATE c_state);

BOOL pin_driven_handler_mqtt_get_state(PIN_DRIVEN_NUM c_pin_num, PIN_DRIVEN_STATE *c_state);
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

