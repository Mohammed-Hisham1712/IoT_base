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
  
 
/*---------------------------------------------------------------*/ 
        /*-----------------------------------------*/ 
        /*          1-Section 1:  Includes         */ 
        /*-----------------------------------------*/ 
/*---------------------------------------------------------------*/ 
#include "types.h" 
#include "types.h" 
#include <string.h> 
#include <stdio.h> 
#include "debug_uart.h" 
#include "NV_access_public.h" 
#include "slow_system_param.h"  
#include "NV_slow_access_cfg.h" 
#include "NV_slow_access_private.h" 
#include "NV_slow_access_public.h" 
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
 
static slow_system_ctrl_t slow_system_ctrl; 
/*---------------------------------------------------------------*/ 
        /*-------------------------------------------------*/ 
        /*          4-Section 4:  private functions         */ 
        /*-------------------------------------------------*/ 
/*---------------------------------------------------------------*/ 
BOOL nv_slow_access_read(int32_t offset, int32_t size, void * buffer) 
{ 
    #if DEBUG_nv_slow_access_read 
        debug("\r\nread from slow partition **%d\r\n",SLOW_PARTITION_NUM); 
    #endif 
    // system_param_slow_t slow_sys_param; 
    int8_t * param_ptr = (int8_t*) (&slow_system_ctrl.slow_system_param); 
    // NV_access_read_data(SLOW_PARTITION_NUM, 
    //                    (void *)&slow_sys_param, sizeof(system_param_slow_t)) ;  
    memcpy((void *)buffer,(void *)(param_ptr+offset), size ); 
  
    return TRUE; 
} 
BOOL nv_slow_access_write(int32_t offset, int32_t size, void * buffer) 
{ 
    #if DEBUG_nv_slow_access_write 
        debug("\r\n enter write function %d\r\n",* ((int*)buffer)); 
    #endif 
    // system_param_slow_t slow_sys_param; 
    int8_t * param_ptr = (int8_t*) (&slow_system_ctrl.slow_system_param); 
    // NV_access_read_data(SLOW_PARTITION_NUM, 
    //                     (void *)&slow_sys_param, sizeof(system_param_slow_t)) ; 
 
    #if DEBUG_nv_slow_access_write 
        debug("\r\n read data before store %d\r\n",slow_sys_param.test_data_1); 
    #endif 
    /* write data with new key to next partition */ 
    memcpy((void *)(param_ptr+offset), buffer , size ) ; 
    #if DEBUG_nv_slow_access_write 
        debug("\r\n data after memcpy %d\r\n",slow_sys_param.test_data_1); 
    #endif 
    // NV_access_write_data(SLOW_PARTITION_NUM, 
    //                     (void *)param_ptr , sizeof(system_param_slow_t)); 
    slow_system_ctrl.slow_system_write_flag = TRUE ;   
    return TRUE;        
} 
BOOL nv_slow_access_init() 
{ 
    #if DEBUG_nv_slow_access_init 
        debug("\r\nthis is init process of nv slow access -%d\r\n",0); 
    #endif 
    // system_param_slow_t buffer; 
    /* read data of the first partition */ 
    NV_access_read_data(SLOW_PARTITION_NUM,(void *)&slow_system_ctrl.slow_system_param ,  
                            sizeof(system_param_slow_t)) ; 
    #if DEBUG_nv_slow_access_init 
        debug("\r\n Key one is %d\r\n",buffer.first_run_key_1); 
        debug("\r\n Key two is %d\r\n",buffer.first_run_key_2);  
    #endif 
    if(!(slow_system_ctrl.slow_system_param.first_run_key_1 == NV_SLOW_KEY1 &&  
         slow_system_ctrl.slow_system_param.first_run_key_2 == NV_SLOW_KEY2) ) 
    { 
        #if DEBUG_nv_slow_access_init 
        debug("\r\n this is the first run of nv slow -%d\r\n",0); 
        #endif 
        nv_slow_access_first_run(); 
    } 
    else  
    { 
 
    } 
    return TRUE; 
} 
BOOL nv_slow_access_first_run() 
{ 
    #if DEBUG_nv_slow_access_first_run 
        debug("\r\n call from first run of nv slow -%d\r\n",0); 
    #endif  
    system_param_slow_t buffer;  
    memset(&buffer,0,sizeof(system_param_slow_t)); 
    buffer.first_run_key_1 = NV_SLOW_KEY1; 
    buffer.first_run_key_2 = NV_SLOW_KEY2; 
 
    NV_access_write_data(SLOW_PARTITION_NUM,(void *)&buffer,sizeof(system_param_slow_t)); 
    #if DEBUG_nv_slow_access_first_run 
        system_param_slow_t sys_param; 
        NV_access_read_data(SLOW_PARTITION_NUM,(void *)&sys_param,sizeof(system_param_slow_t)); 
        debug("\r\n saved key 1 :%d \r\n", (int)sys_param.first_run_key_1 ) ; 
        debug("\r\n saved key 2 :%d \r\n", (int)sys_param.first_run_key_2 ) ; 
    #endif 
     
    return TRUE; 
} 
 
BOOL nv_slow_access_check_first_run(void) 
{ 
    BOOL result;  
    system_param_slow_t buffer;  
    /* read data of the first partition */  
    NV_access_read_data(SLOW_PARTITION_NUM,(void *)&buffer , sizeof(system_param_slow_t)); 
    if(!(buffer.first_run_key_1 == NV_SLOW_KEY1 && buffer.first_run_key_2 == NV_SLOW_KEY2) ) 
    { 
        #if DEBUG_nv_slow_access_check_first_run 
            debug("\r\n this is the first run of nv slow -%d\r\n",0); 
        #endif 
        result = TRUE; 
    } 
    else  
    { 
        /* not first run of the system*/ 
        result = FALSE ; 
    } 
    return result; 
}  
void nv_slow_run_task( void ) 
{ 
    if(slow_system_ctrl.slow_system_write_flag) 
    { 
        NV_access_write_data(SLOW_PARTITION_NUM, 
                            (void *)&slow_system_ctrl.slow_system_param,  
                            sizeof(system_param_slow_t)); 
 
        slow_system_ctrl.slow_system_write_flag = FALSE ; 
    } 
    else  
    { 
 
    } 
 
 
} 
 
 
 