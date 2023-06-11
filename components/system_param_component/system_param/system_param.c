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
#include "NV_slow_access_public.h" 
#include "NV_fast_access_public.h" 
#include "system_param_defintions.h" 
#include "system_param_cfg.h" 
#include "system_param_private.h" 
#include "system_param_public.h" 
#include "system_include.h" 
#include "FreeRTOS.h" 
#include "task.h" 
 
 
/*---------------------------------------------------------------*/ 
        /*-------------------------------------------*/ 
        /*          2-Section 2: Global vars         */ 
        /*-------------------------------------------*/ 
/*---------------------------------------------------------------*/ 
TaskHandle_t system_param_task_handle; 
/*---------------------------------------------------------------*/ 
        /*--------------------------------------------------*/ 
        /*          3-Section 3:            */ 
        /*--------------------------------------------------*/ 
/*---------------------------------------------------------------*/ 
 
/** 
 *  
*/ 
BOOL check_data_size(int8_t partition,int32_t offset, int32_t size) 
{ 
    BOOL result ; 
    switch (partition) 
    { 
    case FAST_PARTITION: 
        if(offset+size <= sizeof(system_param_fast_t)) 
        { 
            result = TRUE ; 
        } 
        else  
        { 
            result = FALSE ; 
        } 
        break; 
    case SLOW_PARTITION: 
        if(offset+size <= sizeof(system_param_slow_t)) 
        { 
            result = TRUE ; 
        } 
        else  
        { 
            result = FALSE ; 
        } 
        break; 
    default: 
        result = FALSE; 
        break; 
    } 
    return result; 
} 
 
 
/*---------------------------------------------------------------*/ 
        /*-------------------------------------------------*/ 
        /*          4-Section 4:public functions          */ 
        /*-------------------------------------------------*/ 
/*---------------------------------------------------------------*/ 
BOOL system_param_read(int8_t partition,int32_t offset, int32_t size, void * buffer) 
{ 
    BOOL result; 
    result = check_data_size(partition,offset,size); 
    if(result) 
    {
        switch (partition) 
        { 
        case FAST_PARTITION: 
            result = nv_fast_access_read(offset,size,buffer); 
            break; 
        case SLOW_PARTITION: 
            result = nv_slow_access_read(offset,size,buffer); 
            break; 
        default: 
            result = FALSE; 
            break; 
        } 
    } 
    else  
    { 
        result = FALSE; 
    } 
  
    return result;  
  
}
BOOL system_param_write(int8_t partition,int32_t offset, int32_t size, void * buffer)  
{  
    BOOL result;  
    result = check_data_size(partition,offset,size);  
    if(result)  
    {  
        switch (partition)  
        {  
        case FAST_PARTITION:  
            result = nv_fast_access_write(offset,size,buffer);  
            break;  
        case SLOW_PARTITION:  
            result = nv_slow_access_write(offset,size,buffer);  
            break;  
        default:  
            result = FALSE;  
            break;  
        }  
    }  
    else   
    {  
        result = FALSE;  
    }  
  
    return result;  
}  
BOOL system_param_init()  
{  
    BOOL result;  
    BaseType_t system_param_task_init_res;  
    result = nv_fast_access_init();  
    result &= nv_slow_access_init();  
  
    system_param_task_init_res = xTaskCreate(system_param_task,  
                                            "System param task",  
                                            CONFIG_SYSTEM_PARAM_TASK_STACK_DEPTH,  
                                            NULL,  
                                            CONFIG_SYSTEM_PARAM_TASK_PRIORITY,  
                                            &system_param_task_handle);  
    if(system_param_task_init_res != pdPASS )  
    {  
          
    }  
      
    return result;  
}  
BOOL system_param_first_run_check()  
{  
    BOOL result;  
    result = nv_fast_access_check_first_run();  
    result |= nv_slow_access_check_first_run();  
    return result;  
}  
BOOL system_param_first_run_init()  
{  
    BOOL result;  
    result = nv_fast_access_first_run();  
    result |= nv_slow_access_first_run();  
    return result;  
}  
  
void system_param_task(void * args)  
{  
    for(;;)  
    {  
        nv_fast_run_task();  
        nv_slow_run_task();  
        vTaskDelay(CONFIG_SYSTEM_PARAM_TASK_PERIOD/ portTICK_PERIOD_MS);  
    }  
      
}  
  
  


