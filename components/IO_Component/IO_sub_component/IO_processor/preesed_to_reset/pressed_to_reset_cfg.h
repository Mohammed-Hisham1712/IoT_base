                /*-----------------------------*/
                /*          File Data:         */
                /*-----------------------------*/
/*--------------------------------------------------------------
* File Usage : 
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

/*--------------Guard-----------*/
#ifndef PRESSED_TO_RESET_CFG_H
#define PRESSED_TO_RESET_CFG_H

#include "system_include.h"

/*---------------------------------------------------------------*/
            /*------------------------------*/
            /*          1-Section1:         */
            /*------------------------------*/
/*---------------------------------------------------------------*/
#ifdef CONFIG_NUMBER_OF_PRESSED_RESET
#define MAX_NUM_OF_RESET_SWITCH     CONFIG_NUMBER_OF_PRESSED_RESET
#else
#define MAX_NUM_OF_RESET_SWITCH     (0)
#endif

#ifdef CONFIG_PRESSED_RESET_1_NUM
#define PRESSED_TO_RESET_SWITCH_1         CONFIG_PRESSED_RESET_1_NUM
#define PRESSED_TO_RESET_SWITCH_1_TABLE   CONFIG_PRESSED_RESET_1_TABLE_INDEX
#endif

#ifdef CONFIG_PRESSED_RESET_2_NUM
#define PRESSED_TO_RESET_SWITCH_2   CONFIG_PRESSED_RESET_2_NUM
#define PRESSED_TO_RESET_SWITCH_2_TABLE   CONFIG_PRESSED_RESET_2_TABLE_INDEX

#endif

#ifdef CONFIG_PRESSED_RESET_3_NUM
#define PRESSED_TO_RESET_SWITCH_3   CONFIG_PRESSED_RESET_3_NUM
#define PRESSED_TO_RESET_SWITCH_3_TABLE   CONFIG_PRESSED_RESET_3_TABLE_INDEX

#endif

#ifdef CONFIG_PRESSED_RESET_4_NUM
#define PRESSED_TO_RESET_SWITCH_4   CONFIG_PRESSED_RESET_4_NUM
#define PRESSED_TO_RESET_SWITCH_4_TABLE   CONFIG_PRESSED_RESET_4_TABLE_INDEX

#endif

#ifdef CONFIG_PRESSED_RESET_5_NUM
#define PRESSED_TO_RESET_SWITCH_5   CONFIG_PRESSED_RESET_5_NUM
#define PRESSED_TO_RESET_SWITCH_5_TABLE   CONFIG_PRESSED_RESET_5_TABLE_INDEX

#endif

#ifdef CONFIG_PRESSED_RESET_6_NUM
#define PRESSED_TO_RESET_SWITCH_6   CONFIG_PRESSED_RESET_6_NUM
#define PRESSED_TO_RESET_SWITCH_6_TABLE   CONFIG_PRESSED_RESET_6_TABLE_INDEX
#endif

#ifdef CONFIG_END_OF_RESET_TIMER
#define END_OF_RESET_TIMER   CONFIG_END_OF_RESET_TIMER
#else 
#define END_OF_RESET_TIMER   (1000)
#endif

#ifdef CONFIG_MAX_NUM_OF_CALL_BACK
#define NUM_OF_CALL_BACKS  CONFIG_MAX_NUM_OF_CALL_BACK
#else 
#define NUM_OF_CALL_BACKS   (10)
#endif

/*---------------------------------------------------------------*/
            /*------------------------------*/
            /*          2-Section2:         */
            /*------------------------------*/
/*---------------------------------------------------------------*/
#define PRESSED_TO_RESET_DEBUG  (0)

#define DEBUG_press_to_reset_init               (PRESSED_TO_RESET_DEBUG&&(0))
#define DEBUG_press_to_reset_run                (PRESSED_TO_RESET_DEBUG&&(0))
#define DEBUG_reset_switch_update_state         (PRESSED_TO_RESET_DEBUG&&(0))
#define DEBUG_process_idle_state                (PRESSED_TO_RESET_DEBUG&&(0))
#define DEBUG_process_in_reset_state            (PRESSED_TO_RESET_DEBUG&&(0))
#define DEBUG_process_end_of_reset_state        (PRESSED_TO_RESET_DEBUG&&(0))
#define DEBUG_process_execute_reset_sequence    (PRESSED_TO_RESET_DEBUG&&(1))
#define DEBUG_in_reset_process_pressed_state    (PRESSED_TO_RESET_DEBUG&&(0))
#define DEBUG_in_reset_process_released_state   (PRESSED_TO_RESET_DEBUG&&(0))
#define DEBUG_in_reset_process_transition_state (PRESSED_TO_RESET_DEBUG&&(0))
#define DEBUG_check_seq                         (PRESSED_TO_RESET_DEBUG&&(1))
#define DEBUG_set_reset_switch_to_idle          (PRESSED_TO_RESET_DEBUG&&(0))
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

