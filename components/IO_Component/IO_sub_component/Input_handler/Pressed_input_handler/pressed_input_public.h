                
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
1-Section 1:  Includes 
2-Section 2:  definitions
3-Section 3:  public data type 
4-Section 4:  public functions
5-Section 5:
6-Section 6"
---------------------------------------------------------------*/

/*--------------Guard-----------*/
#ifndef PRESSED_SWITCH_PUBLIC_H
#define PRESSED_SWITCH_PUBLIC_H

/*---------------------------------------------------------------*/
        /*-----------------------------------------*/
        /*          1-Section 1:  Includes         */
        /*-----------------------------------------*/
/*---------------------------------------------------------------*/
#include "types.h"
/*---------------------------------------------------------------*/
        /*-------------------------------------------*/
        /*          2-Section 2:  definitions        */
        /*-------------------------------------------*/
/*---------------------------------------------------------------*/
#define LEVEL_LOW       (0)
#define LEVEL_HIGH      (1)
/*---------------------------------------------------------------*/
        /*--------------------------------------------------*/
        /*          3-Section 3:  public data type          */
        /*--------------------------------------------------*/
/*---------------------------------------------------------------*/
typedef enum 
{
    PRESSED_SWITCH_1  ,
    PRESSED_SWITCH_2  ,
    PRESSED_SWITCH_3  ,
    PRESSED_SWITCH_4  ,
    PRESSED_SWITCH_5  ,
    PRESSED_SWITCH_6  ,
    PRESSED_SWITCH_7  ,
    SWITCH_MAX ,

}PRESSED_SWITCH_NUM ;
typedef enum 
{
    RELEASED = LEVEL_LOW,
    PRESSED  = LEVEL_HIGH ,
    PRE_PRESSED,
    PRE_RELEASED ,
}PRESSED_SWITCH_STATE ;
/*---------------------------------------------------------------*/
        /*-------------------------------------------------*/
        /*          4-Section 4:  public functions         */
        /*-------------------------------------------------*/
/*---------------------------------------------------------------*/
/**
 * @brief 
*/
error_t pressed_switch_init( PRESSED_SWITCH_NUM c_pressed_switch_num ) ;
/**
 * @brief
*/
error_t pressed_switch_init_all ( void ) ; 
/**
 * @brief
*/
PRESSED_SWITCH_STATE pressed_switch_get_state ( PRESSED_SWITCH_NUM c_pressed_switch_num ) ; 
/**
 * @brief
*/
void pressed_switch_run_handler ( void ) ;
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

