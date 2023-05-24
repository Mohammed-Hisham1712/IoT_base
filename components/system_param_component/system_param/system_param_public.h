                /*-----------------------------*/
                /*          File Data:         */
                /*-----------------------------*/
/*--------------------------------------------------------------
* File Usage :      
----------------------------------------------------------------
* Creators : 
----------------------------------------------------------------
* History : 
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
#ifndef SYSTEM_PARAM_PUBLIC_H
#define SYSTEM_PARAM_PUBLIC_H

/*---------------------------------------------------------------*/
        /*-----------------------------------------*/
        /*          1-Section 1:  Includes         */
        /*-----------------------------------------*/
/*---------------------------------------------------------------*/
#include "types.h"
#include "system_param_defintions.h"

/*---------------------------------------------------------------*/
        /*-------------------------------------------*/
        /*          2-Section 2:          */
        /*-------------------------------------------*/
/*---------------------------------------------------------------*/
#define offset_of(struct,data)  ((int32_t)(&(((struct*)0)->data)))  

/*---------------------------------------------------------------*/
        /*--------------------------------------------------*/
        /*          3-Section 3:            */
        /*--------------------------------------------------*/
/*---------------------------------------------------------------*/


/*---------------------------------------------------------------*/
        /*-------------------------------------------------*/
        /*          4-Section 4:          */
        /*-------------------------------------------------*/
/*---------------------------------------------------------------*/
BOOL system_param_read(int8_t partition,int32_t offset, int32_t size, void * buffer);
BOOL system_param_write(int8_t partition,int32_t offset, int32_t size, void * buffer);
BOOL system_param_init();
BOOL system_param_first_run_check();
BOOL system_param_first_run_init();
void system_param_task(void);
#endif  /*  guard end*/
