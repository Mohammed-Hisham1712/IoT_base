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
1-Section 1:   
2-Section 2:
3-Section 3:
4-Section 4:
5-Section 5:
6-Section 6"
---------------------------------------------------------------*/

/*--------------Guard-----------*/
#ifndef BLINKING_OUTPUT_CFG_H
#define BLINKING_OUTPUT_CFG_H

#include "system_include.h"
/*---------------------------------------------------------------*/
            /*------------------------------*/
            /*          1-Section1:         */
            /*------------------------------*/
/*---------------------------------------------------------------*/
#if CONFIG_NUMBER_OF_BLINKING_OUTPUT
#define MAX_NUM_OF_BLINK_PINS   (CONFIG_NUMBER_OF_BLINKING_OUTPUT)
#endif

#ifdef CONFIG_BLINKING_OUTPUT_1
#define BLINK_PIN_1_NUM   (CONFIG_BLINKING_OUTPUT_1)
#endif    

#ifdef CONFIG_BLINKING_OUTPUT_2
#define BLINK_PIN_2_NUM   (CONFIG_BLINKING_OUTPUT_2)
#endif    

#ifdef CONFIG_BLINKING_OUTPUT_3
#define BLINK_PIN_3_NUM   (CONFIG_BLINKING_OUTPUT_3)
#endif    



#ifdef CONFIG_BLINKING_OUTPUT_4
#define BLINK_PIN_4_NUM   (CONFIG_BLINKING_OUTPUT_4)
#endif    


#ifdef CONFIG_BLINKING_OUTPUT_5
#define BLINK_PIN_5_NUM   (CONFIG_BLINKING_OUTPUT_5)
#endif    

#ifdef CONFIG_BLINKING_OUTPUT_6
#define BLINK_PIN_6_NUM   (CONFIG_BLINKING_OUTPUT_6)
#endif    

#define FAST_BLINK_ON_TIME      (100)
#define FAST_BLINK_OFF_TIME     (100)

#define SLOW_BLINK_ON_TIME      (1000)
#define SLOW_BLINK_OFF_TIME     (1000)


#define BLINK_DEBUG_GENERAL     (1)

#define  DEBUG_blink_output_get_state   BLINK_DEBUG_GENERAL && 0
#define  DEBUG_blink_output_set_state   BLINK_DEBUG_GENERAL && 0
#define  DEBUG_blink_output_set_blink_time   BLINK_DEBUG_GENERAL && 0
#define  DEBUG_blink_output_set_blink_on_time   BLINK_DEBUG_GENERAL && 0
#define  DEBUG_blink_output_set_blink_off_time   BLINK_DEBUG_GENERAL && 0
#define  DEBUG_blink_output_get_blink_on_time   BLINK_DEBUG_GENERAL && 0
#define  DEBUG_blink_output_get_blink_off_time   BLINK_DEBUG_GENERAL && 0
#define  DEBUG_blink_output_init   BLINK_DEBUG_GENERAL && 0
#define  DEBUG_blink_output_run   BLINK_DEBUG_GENERAL && 0
/* private functions*/
#define  DEBUG_run_pin_blink_routine   BLINK_DEBUG_GENERAL && 0


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

