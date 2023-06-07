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
1-Section 1:  Includes 
2-Section 2:  definitions
3-Section 3:  private data type 
4-Section 4:  private functions declaration
5-Section 5:
6-Section 6"
---------------------------------------------------------------*/

/*--------------Guard-----------*/
#ifndef PRESSED_TO_RESET_PRIVATE_H
#define PRESSED_TO_RESET_PRIVATE_H

#include "system_include.h"
#include "pressed_input_public.h"
/*---------------------------------------------------------------*/
        /*-----------------------------------------*/
        /*          1-Section 1:  Includes         */
        /*-----------------------------------------*/
/*---------------------------------------------------------------*/

/*---------------------------------------------------------------*/
        /*-------------------------------------------*/
        /*          2-Section 2:  definitions        */
        /*-------------------------------------------*/
/*---------------------------------------------------------------*/

typedef enum
{
    reset_switch_1,
    reset_switch_2,
    reset_switch_3,
    reset_switch_4,
    reset_switch_5,
    reset_switch_6,
}reset_switch_t;

typedef enum
{
    BIGGER_SEQ,
    IN_BETWEEN,
}seq_type_t;

typedef enum
{
    IDLE,
    IN_RESET_PROCESS,
    END_OF_RESET,
}reset_state_t;

typedef enum
{
    WRONG_SEQ,
    RIGHT_SEQ,
}seq_check_res_t;

typedef enum
{
    TIMER_STARTED,
    TIMER_PAUSED,
}timer_state_t;

typedef struct 
{
    uint32_t    timer_val;
    BOOL        timer_state;
}reset_timer_t;

typedef struct 
{
    PRESSED_SWITCH_STATE state;
    uint32_t             min_value;
    uint32_t             max_value;
    seq_type_t           seq_type;
}reset_table_element_t;

typedef struct 
{
    reset_table_element_t * reset_table;
    uint8_t                 reset_table_size;
}reset_table_info_t;


typedef struct 
{
    reset_timer_t           timer;
    PRESSED_SWITCH_NUM      pressed_switch;
    reset_table_element_t * table_index;
    uint8_t                 table_element; 
    uint8_t                 reset_table_size; 
    reset_state_t           reset_state;
    seq_check_res_t         seq_check_res;
}reset_switch_ctrl_t;

typedef struct 
{
    uint8_t not_used_yet;
}reset_ctrl_t;


/*---------------------------------------------------------------*/
        /*--------------------------------------------------*/
        /*          3-Section 3:  private data type          */
        /*--------------------------------------------------*/
/*---------------------------------------------------------------*/

/*---------------------------------------------------------------*/
        /*-------------------------------------------------*/
        /*          4-Section 4:  private functions         */
        /*-------------------------------------------------*/
/*---------------------------------------------------------------*/
void reset_timer_start(reset_timer_t * timer);
void reset_timer_stop(reset_timer_t * timer );

void reset_timer_update(reset_timer_t * timer );

void reset_timer_restart(reset_timer_t * timer);


BOOL reset_switch_update_state(reset_switch_t c_reset_num);

BOOL process_idle_state(reset_switch_t c_reset_num , PRESSED_SWITCH_STATE c_pressed_state);
BOOL process_in_reset_state(reset_switch_t c_reset_num , PRESSED_SWITCH_STATE c_pressed_state);
BOOL process_end_of_reset_state(reset_switch_t c_reset_num , PRESSED_SWITCH_STATE c_pressed_state);
BOOL process_execute_reset_sequence(reset_switch_t c_reset_num );
BOOL in_reset_process_pressed_state(reset_switch_t c_reset_num );

BOOL in_reset_process_released_state(reset_switch_t c_reset_num );
BOOL in_reset_process_transition_state(reset_switch_t c_reset_num );

BOOL check_seq(reset_switch_t c_reset_num , reset_switch_ctrl_t *reset_switch , reset_table_element_t *table_element);


void set_reset_switch_to_idle(reset_switch_t c_reset_num);


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

