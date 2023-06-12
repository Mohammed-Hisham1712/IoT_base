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
#ifndef NV_SLOW_ACCESS_PUBLIC_H 
#define NV_SLOW_ACCESS_PUBLIC_H 
 
/*---------------------------------------------------------------*/ 
        /*-----------------------------------------*/ 
        /*          1-Section 1:  Includes         */ 
        /*-----------------------------------------*/ 
/*---------------------------------------------------------------*/ 
#include "types.h" 
#include "slow_system_param.h" 
/*---------------------------------------------------------------*/ 
        /*-------------------------------------------*/ 
        /*          2-Section 2:  definitions        */ 
        /*-------------------------------------------*/ 
/*---------------------------------------------------------------*/ 
 
/*---------------------------------------------------------------*/ 
        /*--------------------------------------------------*/ 
        /*          3-Section 3:  public data type          */ 
        /*--------------------------------------------------*/ 
/*---------------------------------------------------------------*/ 
 
 
/*---------------------------------------------------------------*/ 
        /*-------------------------------------------------*/ 
        /*          4-Section 4:  public functions         */ 
        /*-------------------------------------------------*/ 
/*---------------------------------------------------------------*/ 
BOOL nv_slow_access_read(int32_t offset, int32_t size, void * buffer); 
BOOL nv_slow_access_write(int32_t offset, int32_t size, void * buffer); 
BOOL nv_slow_access_init(); 
BOOL nv_slow_access_first_run(); 
BOOL nv_slow_access_check_first_run(void); 
void nv_slow_run_task( void ) ; 
#endif  /*  guard end*/ 
