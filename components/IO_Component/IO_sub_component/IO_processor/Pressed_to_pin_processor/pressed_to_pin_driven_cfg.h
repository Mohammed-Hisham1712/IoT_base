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
1-Section 1:   
2-Section 2:
3-Section 3:
4-Section 4:
5-Section 5:
6-Section 6"
---------------------------------------------------------------*/
#include "gpio_hal_config.h"
#include "types.h"
#include "pressed_input_public.h"
#include "pin_driven_handler_private.h"
#include "pin_driven_handler_public.h"
#include "system_param_config.h"
/*--------------Guard-----------*/
#ifndef PRESSED_TO_PIN_DRIVEN_CFG_H
#define PRESSED_TO_PIN_DRIVEN_CFG_H

/*---------------------------------------------------------------*/
            /*------------------------------*/
            /*          1-Section1:         */
            /*------------------------------*/
/*---------------------------------------------------------------*/
#ifdef CONFIG_NUMBER_OF_PRESSED_TO_PIN_DRIVEN_OUTPUT
#define PRESS_TO_PIN_MAX_PROCESS    (CONFIG_NUMBER_OF_PRESSED_TO_PIN_DRIVEN_OUTPUT)
#else
#define PRESS_TO_PIN_MAX_PROCESS    ( 0 )
#endif
/*================================================================================*/
#ifdef CONFIG_PRESSED_TO_PIN_SWITCH_1_NUM
#define PRESSED_SWITCH_PROCESS_1    (CONFIG_PRESSED_TO_PIN_SWITCH_1_NUM)   
#define PIN_DRIVEN_PROCESS_1        (CONFIG_PRESSED_TO_PIN_PIN_1_NUM)

#else
#define PRESSED_SWITCH_PROCESS_1    (UNDEFINED)  
#define PIN_DRIVEN_PROCESS_1        (UNDEFINED)
#endif
/*================================================================================*/
#ifdef CONFIG_PRESSED_TO_PIN_SWITCH_2_NUM
#define PRESSED_SWITCH_PROCESS_2    (CONFIG_PRESSED_TO_PIN_SWITCH_2_NUM)   
#define PIN_DRIVEN_PROCESS_2        (CONFIG_PRESSED_TO_PIN_PIN_2_NUM)

#else
#define PRESSED_SWITCH_PROCESS_2   (UNDEFINED)  
#define PIN_DRIVEN_PROCESS_2        (UNDEFINED)
#endif
/*================================================================================*/
#ifdef CONFIG_PRESSED_TO_PIN_SWITCH_3_NUM
#define PRESSED_SWITCH_PROCESS_3   (CONFIG_PRESSED_TO_PIN_SWITCH_3_NUM)   
#define PIN_DRIVEN_PROCESS_3        (CONFIG_PRESSED_TO_PIN_PIN_3_NUM)

#else
#define PRESSED_SWITCH_PROCESS_3   (UNDEFINED)  
#define PIN_DRIVEN_PROCESS_3       (UNDEFINED)
#endif
/*================================================================================*/
#ifdef CONFIG_PRESSED_TO_PIN_SWITCH_4_NUM
#define PRESSED_SWITCH_PROCESS_4    (CONFIG_PRESSED_TO_PIN_SWITCH_4_NUM)   
#define PIN_DRIVEN_PROCESS_4        (CONFIG_PRESSED_TO_PIN_PIN_4_NUM)

#else
#define PRESSED_SWITCH_PROCESS_4   (UNDEFINED)  
#define PIN_DRIVEN_PROCESS_4        (UNDEFINED)
#endif
/*================================================================================*/
#ifdef CONFIG_PRESSED_TO_PIN_SWITCH_5_NUM
#define PRESSED_SWITCH_PROCESS_5    (CONFIG_PRESSED_TO_PIN_SWITCH_5_NUM)   
#define PIN_DRIVEN_PROCESS_5        (CONFIG_PRESSED_TO_PIN_PIN_5_NUM)

#else
#define PRESSED_SWITCH_PROCESS_5   (UNDEFINED)  
#define PIN_DRIVEN_PROCESS_5        (UNDEFINED)
#endif
/*================================================================================*/
#ifdef CONFIG_PRESSED_TO_PIN_SWITCH_6_NUM
#define PRESSED_SWITCH_PROCESS_6    (CONFIG_PRESSED_TO_PIN_SWITCH_6_NUM)   
#define PIN_DRIVEN_PROCESS_6        (CONFIG_PRESSED_TO_PIN_PIN_6_NUM)

#else
#define PRESSED_SWITCH_PROCESS_6   (UNDEFINED)  
#define PIN_DRIVEN_PROCESS_6        (UNDEFINED)
#endif
/*================================================================================*/
// #define PRESSED_SWITCH_PROCESS_1    (PRESSED_SWITCH_1)
// #define PRESSED_SWITCH_PROCESS_2    (PRESSED_SWITCH_1)
// #define PRESSED_SWITCH_PROCESS_3    (PRESSED_SWITCH_1)
// #define PRESSED_SWITCH_PROCESS_4    (PRESSED_SWITCH_1)
// #define PRESSED_SWITCH_PROCESS_5    (PRESSED_SWITCH_1)
// #define PRESSED_SWITCH_PROCESS_6    (PRESSED_SWITCH_1)


// #define PIN_DRIVEN_PROCESS_1    (PIN_DRIVEN_1)
// #define PIN_DRIVEN_PROCESS_2    (PIN_DRIVEN_2)
// #define PIN_DRIVEN_PROCESS_3    (PIN_DRIVEN_3)
// #define PIN_DRIVEN_PROCESS_4    (PIN_DRIVEN_4)
// #define PIN_DRIVEN_PROCESS_5    (PIN_DRIVEN_5)
// #define PIN_DRIVEN_PROCESS_6    (PIN_DRIVEN_6)


#define SWITCH_1_TYPE   (ON_OFF_SWITCH)
#define SWITCH_2_TYPE   (ON_OFF_SWITCH)
#define SWITCH_3_TYPE   (ON_OFF_SWITCH)
#define SWITCH_4_TYPE   (ON_OFF_SWITCH)
#define SWITCH_5_TYPE   (ON_OFF_SWITCH)
#define SWITCH_6_TYPE   (ON_OFF_SWITCH)

/*---------------------------------------------------------------*/
            /*------------------------------*/
            /*          2-Section2:         */
            /*------------------------------*/
/*---------------------------------------------------------------*/

/*---------------------------------------------------------------*/
            /*------------------------------*/
            /*          3-Section3:         */
            /*------------------------------*/
/*---------------------------------------------------------------*/

/*---------------------------------------------------------------*/
            /*------------------------------*/
            /*          4-Section4:         */
            /*------------------------------*/
/*---------------------------------------------------------------*/

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

