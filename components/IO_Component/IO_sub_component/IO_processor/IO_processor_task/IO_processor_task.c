                /*-----------------------------*/
                /*          File Data:         */
                /*-----------------------------*/
/*--------------------------------------------------------------
* File Usage : IO Processor handler Task is responsible for init all 
               IO Processor elements Like pressed to pin driven 
               processor and for any future extention modules.
               and also responsible for running its handler functions
               for example: if pressed to pin driven is used in the system to 
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
4-Section 4:
5-Section 5:
6-Section 6"
---------------------------------------------------------------*/

/*---------------------------------------------------------------*/
    /*----------------------------------------*/
    /*          1-Section 1: Includes         */
    /*----------------------------------------*/
/*---------------------------------------------------------------*/
#include "system_param_config.h"


#if CONFIG_PRESSED_TO_PIN_HANDLER
    #include "pressed_to_pin_driven_public.h"
#endif
#if CONFIG_PRESSED_TO_RESET_HANDLER
    #include "pressed_to_reset_public.h"
#endif
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
void IO_processor_task_init( void )
{
    /*==================================================
            PRESSED INPUT TO PIN DRIVEN OUTPUT TASK
    ====================================================*/
    #if CONFIG_PRESSED_TO_PIN_HANDLER
        pressed_switch_to_pin_driven_init();
    #endif
    /*==================================================*/
    
        /*==================================================
            PRESSED TO RESET DRIVEN OUTPUT TASK
    ====================================================*/
    #if CONFIG_PRESSED_TO_RESET_HANDLER
        press_to_reset_init();
    #endif
    /*==================================================*/
    
}
void IO_processor_task_run ( void )
{
    /*==================================================
            PRESSED INPUT TO PIN DRIVEN OUTPUT TASK
    ====================================================*/
    #if CONFIG_PRESSED_TO_PIN_HANDLER
        pressed_switch_to_pin_driven_run();
    #endif
    /*==================================================*/
            /*==================================================
            PRESSED TO RESET DRIVEN OUTPUT TASK
    ====================================================*/
    #if CONFIG_PRESSED_TO_RESET_HANDLER
        press_to_reset_run();
    #endif
    /*==================================================*/
    
}



