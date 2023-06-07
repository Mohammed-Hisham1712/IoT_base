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
#include "pressed_to_reset_cfg.h"
#include "pressed_to_reset_private.h"
#include  "pressed_to_reset_public.h"

#include "debug_uart.h"
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
uint8_t default_press_to_reset_table_index[MAX_NUM_OF_RESET_SWITCH] = 
{
  #ifdef PRESSED_TO_RESET_SWITCH_1
  PRESSED_TO_RESET_SWITCH_1_TABLE,
  #endif
  #ifdef PRESSED_TO_RESET_SWITCH_2
  PRESSED_TO_RESET_SWITCH_2_TABLE,
  #endif
  #ifdef PRESSED_TO_RESET_SWITCH_3
  PRESSED_TO_RESET_SWITCH_3_TABLE,
  #endif
  #ifdef PRESSED_TO_RESET_SWITCH_4
  PRESSED_TO_RESET_SWITCH_4_TABLE,
  #endif
  #ifdef PRESSED_TO_RESET_SWITCH_5
  PRESSED_TO_RESET_SWITCH_5_TABLE,
  #endif
  #ifdef PRESSED_TO_RESET_SWITCH_6
  PRESSED_TO_RESET_SWITCH_6_TABLE,
  #endif
};

uint8_t default_press_to_reset_switch[MAX_NUM_OF_RESET_SWITCH] =
{
  #ifdef PRESSED_TO_RESET_SWITCH_1
  PRESSED_TO_RESET_SWITCH_1,
  #endif
  #ifdef PRESSED_TO_RESET_SWITCH_2
  PRESSED_TO_RESET_SWITCH_2,
  #endif
  #ifdef PRESSED_TO_RESET_SWITCH_3
  PRESSED_TO_RESET_SWITCH_3,
  #endif
  #ifdef PRESSED_TO_RESET_SWITCH_4
  PRESSED_TO_RESET_SWITCH_4,
  #endif
  #ifdef PRESSED_TO_RESET_SWITCH_5
  PRESSED_TO_RESET_SWITCH_5,
  #endif
  #ifdef PRESSED_TO_RESET_SWITCH_6
  PRESSED_TO_RESET_SWITCH_6,
  #endif
};

reset_table_element_t reset_table_1[] = 
{
  {PRESSED,1000,5000,IN_BETWEEN},
  {RELEASED,1000,5000,IN_BETWEEN},
  {PRESSED,1000,3000,IN_BETWEEN},
  {RELEASED,1000,3000,IN_BETWEEN},
  {PRESSED,1000,3000,IN_BETWEEN},
  {RELEASED,1000,3000,IN_BETWEEN},
  {PRESSED,1000,3000,IN_BETWEEN},
  {RELEASED,1000,3000,IN_BETWEEN},
  {PRESSED,0,5000,BIGGER_SEQ},
} ;

#define RESET_TABLE_1_SIZE  (sizeof(reset_table_1)/sizeof(reset_table_element_t))

reset_table_element_t reset_table_2[] = 
{
  {PRESSED,0,500,IN_BETWEEN},
  {RELEASED,0,500,IN_BETWEEN},
  {PRESSED,0,500,IN_BETWEEN},
  {RELEASED,0,500,IN_BETWEEN},
  {PRESSED,0,500,IN_BETWEEN},
  {RELEASED,0,500,IN_BETWEEN},
  {PRESSED,0,500,IN_BETWEEN},
  {RELEASED,0,500,IN_BETWEEN},
  {PRESSED,0,5000,BIGGER_SEQ},
} ;

#define RESET_TABLE_2_SIZE  (sizeof(reset_table_2)/sizeof(reset_table_element_t))


reset_table_info_t reset_tables_info[] = 
{
  {reset_table_1,RESET_TABLE_1_SIZE},
  {reset_table_2,RESET_TABLE_2_SIZE},
};

#define RESET_TABLES_INFO_SIZE  (sizeof(reset_tables_info)/sizeof(reset_table_info_t ))

reset_switch_ctrl_t g_reset_switch_ctrl[MAX_NUM_OF_RESET_SWITCH];


/*---------------------------------------------------------------*/
/*-------------------------------------------------------------*/
/*          4-Section 4: Private functions implementations     */
/*-------------------------------------------------------------*/
/*---------------------------------------------------------------*/
void reset_timer_start(reset_timer_t * timer)
{
  timer->timer_state = TIMER_STARTED ;
}
void reset_timer_stop(reset_timer_t * timer )
{
  timer->timer_state = TIMER_PAUSED;
  timer->timer_val = 0 ;
}

void reset_timer_update(reset_timer_t * timer )
{
  timer->timer_val += CONFIG_IO_COMPONENT_TASK_PERIOD ;
}

void reset_timer_restart(reset_timer_t * timer)
{
  timer->timer_state = TIMER_STARTED ;
  timer->timer_val = 0 ;
}


BOOL reset_switch_update_state(reset_switch_t c_reset_num)
{
  BOOL ret = TRUE ;
  PRESSED_SWITCH_STATE l_pressed_state ;

  /* read current switch state*/
  l_pressed_state = pressed_switch_get_state(g_reset_switch_ctrl[c_reset_num].pressed_switch);
  /* process state */
  if( c_reset_num < MAX_NUM_OF_RESET_SWITCH )
  {
    switch (g_reset_switch_ctrl[c_reset_num].reset_state)
    {
      case IDLE:
        process_idle_state(c_reset_num,l_pressed_state);
        #if DEBUG_reset_switch_update_state
          debug("\r\n prcess IDLE STATE %d",0);
        #endif  
        break;
      case IN_RESET_PROCESS:
        process_in_reset_state(c_reset_num,l_pressed_state);
        #if DEBUG_reset_switch_update_state
          debug("\r\n prcess in reset STATE %d",0);
        #endif  
        break;
      case END_OF_RESET:
        process_end_of_reset_state(c_reset_num,l_pressed_state);
        #if DEBUG_reset_switch_update_state
          debug("\r\n prcess end of reset STATE %d",0);
        #endif  
        break;
      default:
          /*  error */
        break;
    }
  }
  else 
  {
    #if DEBUG_reset_switch_update_state
          debug("\r\n switch num !< MAX_NUM_OF_RESET_SWITCH %d",c_reset_num);
    #endif  
    ret = FALSE ;
  }
  return ret;
}

BOOL process_idle_state(reset_switch_t c_reset_num , PRESSED_SWITCH_STATE c_pressed_state)
{

  switch (c_pressed_state)
  {
  case PRE_PRESSED:
    g_reset_switch_ctrl[c_reset_num].reset_state = IN_RESET_PROCESS ;
    reset_timer_start(&g_reset_switch_ctrl[c_reset_num].timer);
    #if DEBUG_process_idle_state
        debug("\r\n start in reset process %d",0);
    #endif
    break;
  
  default:
    #if DEBUG_process_idle_state
        debug("\r\n still in pre pressed %d",0);
    #endif
    g_reset_switch_ctrl[c_reset_num].reset_state = IDLE ;
    break;
  }
  return TRUE;
}

BOOL process_in_reset_state(reset_switch_t c_reset_num , PRESSED_SWITCH_STATE c_pressed_state)
{
  switch (c_pressed_state)
  {
  case PRESSED:
    #if DEBUG_process_in_reset_state
        debug("\r\n process pressed state %d",0);
    #endif
    in_reset_process_pressed_state(c_reset_num);  
    break;
  case RELEASED:
    #if DEBUG_process_in_reset_state
        debug("\r\n process released state %d",0);
    #endif
    in_reset_process_released_state(c_reset_num);
    break;
  case PRE_PRESSED:
    #if DEBUG_process_in_reset_state
        debug("\r\n process pre pressed state %d",0);
    #endif
    in_reset_process_transition_state(c_reset_num);
    break;
  case PRE_RELEASED:
    #if DEBUG_process_in_reset_state
        debug("\r\n process pre released state %d",0);
    #endif
    in_reset_process_transition_state(c_reset_num);
    break;
  default:
    set_reset_switch_to_idle(c_reset_num);
    break;
  } 
  return TRUE;
}

BOOL process_end_of_reset_state(reset_switch_t c_reset_num , PRESSED_SWITCH_STATE c_pressed_state)
{
  switch (c_pressed_state)
  {
  case RELEASED:
    #if DEBUG_process_end_of_reset_state
        debug("\r\n wait to set to idle %d",0);
    #endif
    if(g_reset_switch_ctrl[c_reset_num].timer.timer_val < END_OF_RESET_TIMER )
    {
      #if DEBUG_process_end_of_reset_state
        debug("\r\n update timer %d",0);
      #endif
      reset_timer_update(&g_reset_switch_ctrl[c_reset_num].timer);
    }
    else 
    {
      #if DEBUG_process_end_of_reset_state
        debug("\r\n go to idle %d",0);
      #endif
      reset_timer_stop(&g_reset_switch_ctrl[c_reset_num].timer);
      g_reset_switch_ctrl[c_reset_num].table_element = 0 ;
      g_reset_switch_ctrl[c_reset_num].reset_state = IDLE ;
    }
    break;

  default:
    #if DEBUG_process_end_of_reset_state
        debug("\r\n wrong and reset timer %d",0);
    #endif
    reset_timer_restart(&g_reset_switch_ctrl[c_reset_num].timer);
    break;
  } 
  return TRUE;
}

BOOL process_execute_reset_sequence(reset_switch_t c_reset_num )
{
    #if DEBUG_process_execute_reset_sequence
        debug("\r\n execute reset sequence now %d",0);
    #endif
    return TRUE;
}

BOOL in_reset_process_pressed_state(reset_switch_t c_reset_num )
{
  BOOL ret ;
  reset_switch_ctrl_t *reset_switch = & g_reset_switch_ctrl[c_reset_num];
  reset_table_element_t *table_element ;
  if(reset_switch->table_element < reset_switch->reset_table_size )
  {
    #if DEBUG_in_reset_process_pressed_state
        debug("\r\n table element < table size correct %d",0);
    #endif
    table_element = & reset_switch->table_index[reset_switch->table_element];
    if( table_element->state == PRESSED )
    { 
      #if DEBUG_in_reset_process_pressed_state
        debug("\r\n table element is pressed correct and continue %d",0);
      #endif
      check_seq(c_reset_num,reset_switch,table_element);
    }
    else 
    {
      #if DEBUG_in_reset_process_pressed_state
        debug("\r\n table element is not pressed wrong and break %d",0);
      #endif
      set_reset_switch_to_idle(c_reset_num);
    }
  }
  else 
  {
    #if DEBUG_in_reset_process_pressed_state
        debug("\r\n table element > table size wrong and break %d",0);
    #endif
    set_reset_switch_to_idle(c_reset_num);
  }
  return TRUE ;
}

BOOL in_reset_process_released_state(reset_switch_t c_reset_num )
{
  BOOL ret ;
  reset_switch_ctrl_t *reset_switch = & g_reset_switch_ctrl[c_reset_num];
  reset_table_element_t *table_element ;
  if(reset_switch->table_element < reset_switch->reset_table_size )
  {
    #if DEBUG_in_reset_process_released_state
        debug("\r\n table element < table size correct %d",0);
    #endif
    table_element = & reset_switch->table_index[reset_switch->table_element];
    if( table_element->state == RELEASED )
    {
      #if DEBUG_in_reset_process_released_state
        debug("\r\n table element is released correct and continue %d",0);
      #endif
      check_seq(c_reset_num,reset_switch,table_element);
    }
    else 
    {
      #if DEBUG_in_reset_process_released_state
        debug("\r\n table element is not released wrong and break %d",0);
      #endif
      set_reset_switch_to_idle(c_reset_num);
    }
  }
  else 
  {
    #if DEBUG_in_reset_process_released_state
        debug("\r\n table element > table size wrong and break %d",0);
    #endif
    set_reset_switch_to_idle(c_reset_num);
  }
  return TRUE ;
}

BOOL in_reset_process_transition_state(reset_switch_t c_reset_num )
{
  reset_switch_ctrl_t *reset_switch = & g_reset_switch_ctrl[c_reset_num];
  if(reset_switch->seq_check_res == RIGHT_SEQ )
  {
    #if DEBUG_in_reset_process_transition_state
        debug("\r\n right seq type increase to next element %d",0);
    #endif
    reset_switch->table_element ++ ;
    reset_timer_restart(&g_reset_switch_ctrl[c_reset_num].timer);
  }
  else 
  {
    #if DEBUG_in_reset_process_transition_state
        debug("\r\n wrong seq restart reset %d",0);
    #endif
    set_reset_switch_to_idle(c_reset_num);
  }
  return TRUE;
}


BOOL check_seq(reset_switch_t c_reset_num , reset_switch_ctrl_t *reset_switch , reset_table_element_t *table_element)
{
  if(table_element->seq_type == IN_BETWEEN )
  {
    #if DEBUG_check_seq && (1)
        debug("\r\n table seq type is in between %d",0);
    #endif
    if(reset_switch->timer.timer_val < table_element->min_value )
    {
      #if DEBUG_check_seq && (1)
        debug("\r\n timer val is lower than min val %d",reset_switch->timer.timer_val);
      #endif
      reset_switch->seq_check_res = WRONG_SEQ ; 
      reset_timer_update(&reset_switch->timer);
    }
    else if ( reset_switch->timer.timer_val >= table_element->min_value 
            && reset_switch->timer.timer_val < table_element->max_value )
    {
      #if DEBUG_check_seq && (1)
        debug("\r\n timer val is lower than min val and bigger than max val %d",reset_switch->timer.timer_val);
      #endif
      reset_switch->seq_check_res = RIGHT_SEQ ; 
      reset_timer_update(&reset_switch->timer);
    }
    else 
    {
      #if DEBUG_check_seq && (1)
        debug("\r\n timer val is bigger than max val %d",reset_switch->timer.timer_val);
      #endif
      reset_switch->seq_check_res = WRONG_SEQ ;
      set_reset_switch_to_idle(c_reset_num);
    }
  }
  else if (table_element->seq_type == BIGGER_SEQ)
  {
      #if DEBUG_check_seq && (1)
        debug("\r\n seq type is bigger seq %d",reset_switch->timer.timer_val);
      #endif
    if(reset_switch->timer.timer_val < table_element->max_value )
    {
      #if DEBUG_check_seq && (1)
        debug("\r\n timer val smaller than max val %d",reset_switch->timer.timer_val);
      #endif
      reset_switch->seq_check_res = WRONG_SEQ ; 
      reset_timer_update(&reset_switch->timer);
    }
    else 
    {
      #if DEBUG_check_seq && (1)
        debug("\r\n timer val is bigger than max val %d",reset_switch->timer.timer_val);
      #endif
      /* execute reset sequence */
      process_execute_reset_sequence(c_reset_num);
      set_reset_switch_to_idle(c_reset_num);
    }
  }
  else
  {
    set_reset_switch_to_idle(c_reset_num);
  }
  return TRUE;
      
}


void set_reset_switch_to_idle(reset_switch_t c_reset_num)
{
  g_reset_switch_ctrl[c_reset_num].reset_state = END_OF_RESET ;
}



/*---------------------------------------------------------------*/
/*-------------------------------------------------------------*/
/*          4-Section 4: public functions implementations     */
/*-------------------------------------------------------------*/
/*---------------------------------------------------------------*/

BOOL press_to_reset_init(void)
{
  reset_switch_t counter ;

  for (counter= reset_switch_1; counter < MAX_NUM_OF_RESET_SWITCH; counter++)
  {
    g_reset_switch_ctrl[counter].reset_state = IDLE ;

    if(default_press_to_reset_table_index[counter] < RESET_TABLES_INFO_SIZE )
    {
      #if DEBUG_press_to_reset_init
      debug("\r\nright table %d\r\n", counter );
      #endif
      g_reset_switch_ctrl[counter].table_index = reset_tables_info[default_press_to_reset_table_index[counter]].reset_table;
      g_reset_switch_ctrl[counter].reset_table_size = reset_tables_info[default_press_to_reset_table_index[counter]].reset_table_size;
    }
    else
    {
      #if DEBUG_press_to_reset_init
      debug("\r\nwrong table go to default %d\r\n", counter );
      #endif
      g_reset_switch_ctrl[counter].table_index = reset_tables_info[0].reset_table;
      g_reset_switch_ctrl[counter].reset_table_size = reset_tables_info[0].reset_table_size;
    }
    g_reset_switch_ctrl[counter].pressed_switch = default_press_to_reset_switch[counter];
    reset_timer_restart(&g_reset_switch_ctrl[counter].timer);
    g_reset_switch_ctrl[counter].seq_check_res = WRONG_SEQ;

    #if DEBUG_press_to_reset_init
      debug("\r\ninit process of reset switch %d\r\n", counter );
        debug("\r\nreset_switch.table_index = %p", g_reset_switch_ctrl[counter].table_index );
      debug("\r\nreset_switch.reset table size = %d", g_reset_switch_ctrl[counter].reset_table_size );
      debug("\r\nreset table pointer = %p", reset_tables_info[default_press_to_reset_table_index[counter]].reset_table );
      debug("\r\naddress of reset table is %p",reset_table_1);
      debug("\r\n reset switch num is %d",g_reset_switch_ctrl[counter].pressed_switch);
      debug("\r\n reset table 1 size is %d",g_reset_switch_ctrl[counter].reset_table_size);
      debug("\r\n reset table info size is %d\r\n",RESET_TABLES_INFO_SIZE);
    #endif
  }

  return TRUE;
  
}

BOOL press_to_reset_run(void)
{
  reset_switch_t counter ;

  for (counter= reset_switch_1; counter < MAX_NUM_OF_RESET_SWITCH; counter++)
  {
      reset_switch_update_state(counter);
  }
  return TRUE;
}


