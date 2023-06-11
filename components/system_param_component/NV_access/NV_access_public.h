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
---------------------------------------------------------------*/ 
 
/*--------------Guard-----------*/ 
#ifndef NV_ACCESS_PUBLIC_H
#define NV_ACCESS_PUBLIC_H  

/*---------------------------------------------------------------*/ 
        /*-----------------------------------------*/ 
        /*          1-Section 1:  Includes         */ 
        /*-----------------------------------------*/ 
/*---------------------------------------------------------------*/ 
#include "types.h" 
#include "nvs.h" 
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
BOOL NV_access_write_data(int32_t partition_ID, void * buffer, size_t length); 
BOOL NV_access_read_data(int32_t partition_ID, void * buffer,size_t length);  
BOOL NV_access_check_partition_validation(int32_t partition_ID); 
error_t NV_access_init_partition( void ); 
  
  
   
#endif  /*  guard end*/ 
 