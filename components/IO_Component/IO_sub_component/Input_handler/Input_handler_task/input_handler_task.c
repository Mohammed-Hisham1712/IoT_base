                /*-----------------------------*/
                /*          File Data:         */
                /*-----------------------------*/
/*--------------------------------------------------------------
* File Usage : Input handler Task is responsible for init all input
               elements Like pressed input or on off input and any
               future input modules.
               and also responsible for running its handler functions
               for example: if ON-off input is used in the system to 
               be compiled and run. 
               input task will init it and run it also periodically
               and the periodic time is IO_component Task periodic time. 
----------------------------------------------------------------
* Creators : 1- Mahmoud Eid
             2- Mohamed Hisham
----------------------------------------------------------------
* History : Creation | 28/3/2023
----------------------------------------------------------------*/

                /*---------------------------*/
                /*          Content:         */
                /*---------------------------*/
/*-------------------------------------------------------------
1-Section 1: Includes  
2-Section 2: Defintions
3-Section 3: functions Definitions  
---------------------------------------------------------------*/

/*---------------------------------------------------------------*/
    /*----------------------------------------*/
    /*          1-Section 1: Includes         */
    /*----------------------------------------*/
/*---------------------------------------------------------------*/
#include "pressed_input_public.h"
#include "system_include.h"

/*---------------------------------------------------------------*/
    /*-----------------------------------------*/
    /*          2-Section 2: Defintions        */
    /*-----------------------------------------*/
/*---------------------------------------------------------------*/

/*---------------------------------------------------------------*/
    /*------------------------------------------------------*/
    /*          3-Section 3: functions Definitions          */
    /*------------------------------------------------------*/
/*---------------------------------------------------------------*/
void input_handler_task_init(void)
{
    /*==================================================
            PRESSED INPUT TASK
    ====================================================*/
    #ifdef CONFIG_PRESSED_TO_PIN_HANDLER
        pressed_switch_init_all() ;
    #endif
    /*==================================================*/
    
    
}
void input_handler_task_run(void)
{
    /*==================================================
            PRESSED INPUT TASK
    ====================================================*/
    #ifdef CONFIG_PRESSED_TO_PIN_HANDLER
        pressed_switch_run_handler() ;
    #endif
    /*==================================================*/
    
}



