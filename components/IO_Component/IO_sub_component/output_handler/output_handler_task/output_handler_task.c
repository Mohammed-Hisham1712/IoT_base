                /*-----------------------------*/
                /*          File Data:         */
                /*-----------------------------*/
/*--------------------------------------------------------------
* File Usage : output handler Task is responsible for init all output
               elements Like pin driven output and any
               future input modules.
               and also responsible for running its handler functions
               for example: if pin driven input is used in the system to 
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
#include "pin_driven_handler_public.h"
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

void output_handler_task_init( void )
{
    /*==================================================
            PIN DRIVEN OUTPUT TASK
    ====================================================*/
    #ifdef CONFIG_PIN_DRIVEN_OUTPUT_HANDLER
        pin_driven_init();
    #endif
    /*==================================================*/



}
void output_handler_task_run ( void )
{
    /*==================================================
            PIN DRIVEN OUTPUT TASK
    ====================================================*/
    #ifdef CONFIG_PIN_DRIVEN_OUTPUT_HANDLER
        pin_driven_run_handler();
    #endif
    /*==================================================*/
    
}



