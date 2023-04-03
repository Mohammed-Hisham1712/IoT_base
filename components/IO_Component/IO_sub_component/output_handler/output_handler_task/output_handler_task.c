                /*-----------------------------*/
                /*          File Data:         */
                /*-----------------------------*/
/*--------------------------------------------------------------
* File Usage : This file used to run all output sub components 
               init and run functions.
               for example :
                if pin driven output is included in the project
                 this file will be responsible to 1- run pin_driven_init()
                                                  2- run pin_driven_run()
               and the same process for all output modules 
               PWM output
               Dimming output
               motor output
              So this file might be considered as the manager of all 
              output modules
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
    pin_driven_init();
}
void output_handler_task_run ( void )
{
   pin_driven_run_handler(); 
}



