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
#include <string.h>               
#include <stdio.h>              
#include "debug_uart.h"               
#include "NV_access_public.h"               
#include "NV_fast_access_cfg.h"              
#include "NV_fast_access_private.h"              
#include "NV_fast_access_public.h"              
              
#include  "fast_system_param.h"              
              
              
nv_fast_ctrl_t fast_ctrl;               
/*---------------------------------------------------------------*/              
        /*-------------------------------------------*/              
        /*          2-Section 2:  definitions        */              
        /*-------------------------------------------*/              
/*---------------------------------------------------------------*/              
              
/*---------------------------------------------------------------*/               
        /*--------------------------------------------------*/               
        /*          3-Section 3:  private functions          */              
        /*--------------------------------------------------*/              
/*---------------------------------------------------------------*/              
BOOL nv_fast_access_partitions_scan(void)               
{              
    #if DEBUG_nv_fast_access_partitions_scan              
        debug("\r\n Scanning function of NV fast %d\r\n",1);              
        print_partitions_keys();              
    #endif              
    system_param_fast_t buffer;               
    int8_t current_partition_key;              
    int8_t next_partition_key;              
               
    fast_ctrl.current_partition_num = fast_partition_1 ;               
              
              
    while(fast_ctrl.current_partition_num <= fast_partition_5)              
    {              
        #if DEBUG_nv_fast_access_partitions_scan              
        debug("\r\n scan partition num :%d \r\n" , fast_ctrl.current_partition_num );              
        #endif              
        if (fast_ctrl.current_partition_num == fast_partition_5 )              
        {              
            fast_ctrl.next_partition_num = 1 ;              
        }              
        else               
        {              
            fast_ctrl.next_partition_num = fast_ctrl.current_partition_num + 1 ;              
        }              
        NV_access_read_data(fast_ctrl.current_partition_num,              
                            (void*)&buffer,sizeof(system_param_fast_t)) ;              
        current_partition_key = buffer.partition_counter ;              
              
        #if DEBUG_nv_fast_access_partitions_scan              
        debug("\r\n current key is :%d \r\n" , current_partition_key);              
        #endif              
              
        NV_access_read_data(fast_ctrl.next_partition_num,              
                            (void*)&buffer,sizeof(system_param_fast_t)) ;              
              
        next_partition_key = buffer.partition_counter ;              
        #if DEBUG_nv_fast_access_partitions_scan              
        debug("\r\n next key is :%d \r\n" , next_partition_key);              
        #endif              
        if(current_partition_key == 3 )              
        {              
            #if DEBUG_nv_fast_access_partitions_scan              
                debug("\r\n current key is %d \r\n",3);                             
            #endif              
            if(next_partition_key == 1 )              
            {              
                #if DEBUG_nv_fast_access_partitions_scan              
                    debug("\r\n next key is %d right and go for next \r\n",1);              
                #endif              
                /* this is right go to next*/              
                fast_ctrl.current_partition_num ++ ;              
            }              
            else               
            {              
                #if DEBUG_nv_fast_access_partitions_scan              
                    debug("\r\n next key NOT %d Wrong stop here \r\n",1);              
                #endif              
                /* this is wrong stay on that*/              
                //increase_partition_position();              
                break ;              
            }              
        }              
        else               
        {              
            if(next_partition_key == current_partition_key +1)              
            {              
                #if DEBUG_nv_fast_access_partitions_scan              
                    debug("\r\n next key = current + %d go for next \r\n",1);              
                #endif              
                /* this is right go to next*/              
                fast_ctrl.current_partition_num ++ ;              
            }              
            else               
            {             
                #if DEBUG_nv_fast_access_partitions_scan              
                    debug("\r\n NEXT != CURRENT + %d STOP HERE \r\n",1);              
                #endif              
                /* this is wrong stay on that*/              
                //increase_partition_position();               
                break;              
            }              
        }              
                      
    }               
    #if DEBUG_nv_fast_access_partitions_scan              
            debug("\r\n END CURENT PART %d\r\n",(int)fast_ctrl.current_partition_num);              
            debug("\r\n END NEXT PART %d\r\n",(int)fast_ctrl.next_partition_num);              
    #endif              
    return TRUE;              
}              
void increase_partition_position(void)              
{              
    #if DEBUG_increase_partition_position              
        debug("\r\n call increase partition num -%d\r\n",0);              
    #endif              
    if(fast_ctrl.current_partition_num == fast_ctrl.next_partition_num)              
    {              
        #if DEBUG_increase_partition_position              
            debug("\r\n current num = next num error -%d\r\n",0);              
        #endif              
        /* set error */              
              
        /* recalculate values*/              
            // nv_fast_access_partitions_scan();              
    }              
    else              
    {               
        if (fast_ctrl.current_partition_num == fast_partition_5 )              
        {              
            #if DEBUG_increase_partition_position              
                    debug("\r\n curent partition is = %d let it to be 1 \r\n",5);              
            #endif              
            fast_ctrl.current_partition_num = fast_partition_1 ;              
        }              
        else               
        {              
            #if DEBUG_increase_partition_position              
                    debug("\r\n curent partition != %d increase 1 \r\n",5);              
            #endif              
            fast_ctrl.current_partition_num ++;              
        }              
        if(fast_ctrl.next_partition_num == fast_partition_5 )              
        {              
            #if DEBUG_increase_partition_position              
                    debug("\r\n next partition = %d let it to be 1 \r\n",5);              
            #endif              
            fast_ctrl.next_partition_num = fast_partition_1;              
        }              
        else               
        {              
            #if DEBUG_increase_partition_position               
                debug("\r\n next partition != %d increase 1 \r\n",5);               
            #endif               
            fast_ctrl.next_partition_num ++;               
        }               
        #if DEBUG_increase_partition_position               
            debug("\r\n current partition is %d\r\n",fast_ctrl.current_partition_num);               
            debug("\r\n next partition is %d\r\n",fast_ctrl.next_partition_num);               
        #endif               
    }               
}               
              
#if DEBUG_nv_fast_access_partitions_scan               
void print_partitions_keys(void)               
{              
    system_param_fast_t buffer;              
    for (int i = 1 ; i<= 5 ; i++ )              
    {               
        NV_access_read_data(i,              
                        (void *)&buffer , sizeof(system_param_fast_t)) ;              
        debug("\r\npartition num %d key is %d\r\n",i,(int)buffer.partition_counter);              
    }              
                  
               
}             
#endif              
/*---------------------------------------------------------------*/              
        /*-------------------------------------------------*/              
        /*          4-Section 4:  public functions         */              
        /*-------------------------------------------------*/              
/*---------------------------------------------------------------*/               
              
BOOL nv_fast_access_read(int32_t offset, int32_t size, void * buffer)              
{              
    // system_param_fast_t fast_sys_param;              
    int8_t *param_ptr = (int8_t*) &fast_ctrl.fast_sys_param;              
    #if DEBUG_nv_fast_access_read              
        debug("\r\nread from partition %d\r\n",fast_ctrl.current_partition_num);              
    #endif              
    // NV_access_read_data(fast_ctrl.current_partition_num,              
    //                     (void *)&fast_sys_param , sizeof(system_param_fast_t)) ;               
    memcpy((void *)buffer,(void *)(param_ptr+offset), size );              
              
    return TRUE;              
}              
BOOL nv_fast_access_write(int32_t offset, int32_t size, void * buffer)              
{              
    #if DEBUG_nv_fast_access_write             
        debug("\r\n data to store is %d\r\n",* ((int*)buffer));              
    #endif              
    // system_param_fast_t fast_sys_param;              
    int8_t *param_ptr = (int8_t*) &fast_ctrl.fast_sys_param;              
    /* get key of the current partition */              
    // NV_access_read_data(fast_ctrl.current_partition_num,              
    //                     (void *)param_ptr, sizeof(system_param_fast_t)) ;              
              
    #if DEBUG_nv_fast_access_write              
        debug("\r\n read data is %d\r\n",fast_sys_param.test_data_1);              
    #endif              
    /* write data with new key to next partition */              
    memcpy((void *)(param_ptr+offset), buffer , size ) ;              
    #if DEBUG_nv_fast_access_write              
        debug("\r\n data after memcpy %d\r\n",fast_sys_param.test_data_1);              
    #endif              
    fast_ctrl.nv_fast_save_data_flag = TRUE;              
              
    return TRUE;              
}              
BOOL nv_fast_access_init()              
{              
    #if DEBUG_nv_fast_access_init              
        debug("\r\nthis is init process of nv fast access -%d\r\n",0);              
    #endif               
    system_param_fast_t buffer;              
    /* read data of the first partition */              
    NV_access_read_data(fast_partition_1,(void *)&buffer , sizeof(system_param_fast_t)) ;              
    #if DEBUG_nv_fast_access_init              
        debug("\r\n Key one is %d\r\n",buffer.first_run_key_1);              
        debug("\r\n Key two is %d\r\n",buffer.first_run_key_2);              
    #endif              
    if(!(buffer.first_run_key_1 == NV_FAST_KEY1 && buffer.first_run_key_2 == NV_FAST_KEY2) )              
    {              
        #if DEBUG_nv_fast_access_init              
        debug("\r\n this is the first run of nv fast -%d\r\n",0);              
        #endif              
        /* this is the first run of NV memory*/              
        nv_fast_access_first_run();              
    }              
    else               
    {              
        #if DEBUG_nv_fast_access_init              
        debug("\r\n Run normal not first run -%d\r\n",0);              
        #endif              
        nv_fast_access_partitions_scan();              
        NV_access_read_data(fast_ctrl.current_partition_num,              
                        (void *)&fast_ctrl.fast_sys_param , sizeof(system_param_fast_t)) ;               
    }              
    return TRUE;              
}              
BOOL nv_fast_access_first_run()              
{              
    system_param_fast_t buffer;              
              
    memset(&buffer,0,sizeof(system_param_fast_t));              
    buffer.first_run_key_1 = NV_FAST_KEY1;              
    buffer.first_run_key_2 = NV_FAST_KEY2;              
    buffer.partition_counter = 3 ;              
    nv_fast_partitions partition_count  ;              
              
    #if DEBUG_nv_fast_access_first_run              
        debug("\r\n call from first run of nv fast -%d\r\n",0);              
    #endif              
    for(partition_count = fast_partition_5; partition_count >= fast_partition_1; partition_count--)              
    {              
        #if DEBUG_nv_fast_access_first_run              
        debug("\r\n Init fast partition num :%d \r\n" , partition_count );              
        #endif              
        if( partition_count == fast_partition_1 )              
        {               
           buffer.partition_counter = 1 ;               
        }              
        else               
        {              
            /* do nothing */               
        }              
        NV_access_write_data(partition_count,(void *)&buffer,sizeof(system_param_fast_t));              
        #if DEBUG_nv_fast_access_first_run              
            system_param_fast_t sys_param;              
            NV_access_read_data(partition_count,(void *)&sys_param,sizeof(system_param_fast_t));              
            debug("\r\n saved key 1 :%d \r\n", (int)sys_param.first_run_key_1 ) ;              
            debug("\r\n saved key 2 :%d \r\n", (int)sys_param.first_run_key_2 ) ;              
            debug("\r\n saved param num :%d \r\n", (int)sys_param.partition_counter ) ;              
        #endif             
    }              
    return TRUE;              
}              
              
BOOL nv_fast_access_check_first_run(void)              
{               
    BOOL result;              
    system_param_fast_t buffer;              
    /* read data of the first partition */              
    NV_access_read_data(fast_partition_1,(void *)&buffer , sizeof(system_param_fast_t));              
    if(!(buffer.first_run_key_1 == NV_FAST_KEY1 && buffer.first_run_key_2 == NV_FAST_KEY2) )              
    {              
        #if DEBUG_nv_fast_access_check_first_run              
            debug("\r\n this is the first run of nv fast -%d\r\n",0);              
        #endif              
        result = TRUE;              
    }              
    else               
    {              
        result = FALSE ;              
    }              
    return result;              
}              
              
void nv_fast_run_task( void )              
{              
    int8_t *param_ptr = (int8_t*) &fast_ctrl.fast_sys_param;              
    if(fast_ctrl.nv_fast_save_data_flag)              
    {              
        if (fast_ctrl.fast_sys_param.partition_counter == 3 )              
        {              
            fast_ctrl.fast_sys_param.partition_counter = 1 ;              
        }              
        else               
        {              
            fast_ctrl.fast_sys_param.partition_counter ++ ;              
        }              
        increase_partition_position();              
        NV_access_write_data(fast_ctrl.current_partition_num,              
                        (void *)param_ptr , sizeof(system_param_fast_t));              
        fast_ctrl.nv_fast_save_data_flag= FALSE;              
    }              
    else               
    {              
                      
    }              
}              
              
