                /*-----------------------------*/
                /*          File Data:         */
                /*-----------------------------*/
/*--------------------------------------------------------------
* File Usage :  

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
1-Section 1:Includes   
2-Section 2:
3-Section 3:
---------------------------------------------------------------*/

/*--------------Guard-----------*/
#ifndef PIN_DRIVEN_HANDLER_CFG_H
#define PIN_DRIVEN_HANDLER_CFG_H

/*---------------------------------------------------------------*/
            /*------------------------------*/
            /*          1-Includes:         */
            /*------------------------------*/
/*---------------------------------------------------------------*/
#ifdef  CONFIG_NUMBER_OF_PIN_DRIVEN_OUTPUT
#define PIN_DRIVEN_MAX_PIN_NUM  CONFIG_NUMBER_OF_PIN_DRIVEN_OUTPUT
#else
#define PIN_DRIVEN_MAX_PIN_NUM      (0)
#endif

#ifdef  CONFIG_PIN_DRIVEN_1_PIN_NUM
#define PIN_DRIVEN_PIN_1    CONFIG_PIN_DRIVEN_1_PIN_NUM
#else   
#define PIN_DRIVEN_PIN_1      (UNDEFINED)
#endif

#ifdef  CONFIG_PIN_DRIVEN_2_PIN_NUM
#define PIN_DRIVEN_PIN_2    CONFIG_PIN_DRIVEN_2_PIN_NUM
#else
#define PIN_DRIVEN_PIN_2      (UNDEFINED)
#endif

#ifdef  CONFIG_PIN_DRIVEN_3_PIN_NUM
#define PIN_DRIVEN_PIN_3    CONFIG_PIN_DRIVEN_3_PIN_NUM
#else
#define PIN_DRIVEN_PIN_3      (UNDEFINED)
#endif

#ifdef  CONFIG_PIN_DRIVEN_4_PIN_NUM
#define PIN_DRIVEN_PIN_4    CONFIG_PIN_DRIVEN_4_PIN_NUM
#else
#define PIN_DRIVEN_PIN_4      (UNDEFINED)
#endif

#ifdef  CONFIG_PIN_DRIVEN_5_PIN_NUM
#define PIN_DRIVEN_PIN_5    CONFIG_PIN_DRIVEN_5_PIN_NUM
#else
#define PIN_DRIVEN_PIN_5      (UNDEFINED)
#endif

#ifdef  CONFIG_PIN_DRIVEN_6_PIN_NUM
#define PIN_DRIVEN_PIN_6    CONFIG_PIN_DRIVEN_6_PIN_NUM
#else
#define PIN_DRIVEN_PIN_6      (UNDEFINED)
#endif

// #define PIN_DRIVEN_MAX_PIN_NUM      (6)
// #define PIN_DRIVEN_PIN_1        (PIN_0) 
// #define PIN_DRIVEN_PIN_2        (PIN_1) 
// #define PIN_DRIVEN_PIN_3        (PIN_2) 
// #define PIN_DRIVEN_PIN_4        (PIN_15) 
// #define PIN_DRIVEN_PIN_5        (PIN_12) 
// #define PIN_DRIVEN_PIN_6        (PIN_16) 
// #define PIN_DRIVEN_PIN_7        (PIN_6) 
/*---------------------------------------------------------------*/
            /*------------------------------*/
            /*          2-Section2:         */
            /*------------------------------*/
/*---------------------------------------------------------------*/

/*---------------------------------------------------------------*/
            /*------------------------------*/
            /*          3-Section3:         */
            /*------------------------------*/
/*---------------------------------------------------------------*/



#endif  /*  guard end*/
