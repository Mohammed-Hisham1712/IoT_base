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
1-Section 1:   
2-Section 2:
3-Section 3:
4-Section 4:
5-Section 5:
6-Section 6"
---------------------------------------------------------------*/

/*--------------Guard-----------*/
#ifndef PRESSED_SWITCH_CONFIG_H
#define PRESSED_SWITCH_CONFIG_H

/*---------------------------------------------------------------*/
            /*------------------------------*/
            /*          1-Section1:         */
            /*------------------------------*/
/*---------------------------------------------------------------*/

#include "system_param_config.h"

/*---------------------------------------------------------------*/
            /*------------------------------*/
            /*          2-Section2: defintions        */
            /*------------------------------*/
/*---------------------------------------------------------------*/
#ifdef CONFIG_NUMBER_OF_PRESSED_INPUT_HANDLER
#define PRESSED_SWITCH_MAX_NUMBER     (CONFIG_NUMBER_OF_PRESSED_INPUT_HANDLER)
#else 
#define PRESSED_SWITCH_MAX_NUMBER     (0)
#endif

#ifdef CONFIG_PRESSED_INPUT_HANDLER_1_PIN
#define PRESSED_SWITCH_1_PIN     (CONFIG_PRESSED_INPUT_HANDLER_1_PIN)
#else 
#define PRESSED_SWITCH_1_PIN     (UNDEFINED)
#endif

#ifdef CONFIG_PRESSED_INPUT_HANDLER_2_PIN
#define PRESSED_SWITCH_2_PIN     (CONFIG_PRESSED_INPUT_HANDLER_2_PIN)
#else 
#define PRESSED_SWITCH_2_PIN     (UNDEFINED)
#endif
#ifdef CONFIG_PRESSED_INPUT_HANDLER_3_PIN
#define PRESSED_SWITCH_3_PIN     (CONFIG_PRESSED_INPUT_HANDLER_3_PIN)
#else 
#define PRESSED_SWITCH_3_PIN     (UNDEFINED)
#endif
#ifdef CONFIG_PRESSED_INPUT_HANDLER_4_PIN
#define PRESSED_SWITCH_4_PIN     (CONFIG_PRESSED_INPUT_HANDLER_4_PIN)
#else 
#define PRESSED_SWITCH_4_PIN     (UNDEFINED)
#endif

#ifdef CONFIG_PRESSED_INPUT_HANDLER_5_PIN
#define PRESSED_SWITCH_5_PIN     (CONFIG_PRESSED_INPUT_HANDLER_5_PIN)
#else 
#define PRESSED_SWITCH_5_PIN     (UNDEFINED)
#endif
#ifdef CONFIG_PRESSED_INPUT_HANDLER_6_PIN
#define PRESSED_SWITCH_6_PIN     (CONFIG_PRESSED_INPUT_HANDLER_6_PIN)
#else 
#define PRESSED_SWITCH_6_PIN     (UNDEFINED)
#endif

// #define PRESSED_SWITCH_1_PIN          (PIN_5) 
// #define PRESSED_SWITCH_2_PIN          (PIN_2)
// #define PRESSED_SWITCH_3_PIN          (PIN_8)
// #define PRESSED_SWITCH_4_PIN          (PIN_9)
// #define PRESSED_SWITCH_5_PIN          (PIN_10)
// #define PRESSED_SWITCH_6_PIN          (PIN_11)
// #define PRESSED_SWITCH_7_PIN          (PIN_1)



#endif  /*  guard end*/

