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
1-Section 1:  Includes 
2-Section 2:  definitions
3-Section 3:  private data type 
4-Section 4:  private functions declaration
5-Section 5:
6-Section 6"
---------------------------------------------------------------*/

/*--------------Guard-----------*/
#ifndef PRESSED_TO_PIN_DRIVEN_PRIVATE_H
#define PRESSED_TO_PIN_DRIVEN_PRIVATE_H

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
void process_on_off_switch_type ( uint8_t switch_num ) ;
void process_reset_switch_type ( uint8_t switch_num ) ;
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

