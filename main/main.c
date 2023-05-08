/* Hello World Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "gpio_hal_itf.h"
// #include "system_param_itf.h"   
#include "IO_component_task.h"
#include "debug_uart.h"
// #include "NV_fast_access_public.h"
// #include "system_param_public.h"


// ((int16_t)(((a*)0)->b))
// #define offset_of(a,b)  ((int32_t)(&(((a*)0)->b)))  

int32_t buffer ;
int data = 150 ;
void app_main()
{
    BOOL ret;
    uart_init() ;
    vTaskDelay(10 / portTICK_PERIOD_MS);
    // EXECUTE(SYSTEM_PARAM,SYSTEM_PARAM_INIT,&ret);
    // debug("\r\nthe result of system param init %d\r\n",ret);
    // system_param_init();
    // nv_fast_access_init();
    // nv_fast_access_write(offset_of(system_param_fast_t,test_data_1),sizeof(data),&data);
    // nv_fast_access_read(offset_of(system_param_fast_t,test_data_1),sizeof(data),&data);
    // BOOL resu = system_param_first_run_check();
    // if( resu == TRUE )
    // {
    //     debug("\r\nthis is system first run %d\r\n",0);
    //     system_param_first_run_init();
    // }
    // else 
    // {
    //     debug("\r\nNOT FIRST RUN  %d\r\n",0);
    // }
    // IO_component_task_init() ;
    while(1)
    {
        // EXECUTE(SYSTEM_PARAM,SYSTEM_PARAM_READ, &FAST_PARTITION,
        //                                         &(offset_of(ystem_param_fast_t,test_data_2))
        //                                         &sizeof(data),&data);
        // system_param_read(FAST_PARTITION,offset_of(system_param_fast_t,test_data_2),sizeof(data),&data);
        // // // nv_fast_access_read(offset_of(system_param_fast_t,test_data_3),sizeof(data),&data);
        // debug("\r\nread data 2 is=%d\r\n",data);
        data++;
        // EXECUTE(SYSTEM_PARAM,SYSTEM_PARAM_WRITE, &FAST_PARTITION,
        //                                         &(offset_of(ystem_param_fast_t,test_data_2))
        //                                         &sizeof(data),&data);
        // system_param_write(FAST_PARTITION,offset_of(system_param_fast_t,test_data_2),sizeof(data),&data);
        // nv_fast_access_write(offset_of(system_param_fast_t,test_data_3),sizeof(data),&data);
        // nv_slow_access_read(offset_of(system_param_slow_t,test_data_1),sizeof(data),&data);
        // debug("\r\nread data 1 is=%d\r\n",data);
        // data++;
        // nv_slow_access_write(offset_of(system_param_slow_t,test_data_1),sizeof(data),&data);
        // IO_component_task_run();
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
    
    
}

// void init_partitions(int part) 
// {
//     system_param_t param ; 
//     param.param1 =0xABCDDCBA ; 
//     param.param2 =0xABCDDCBA ;
//     param.param3 =0 ; 
//     param.param4 =0 ;
//     param.param5 =0; 
//     for ( int i = 0 ; i <= 9 ; i ++ )
//     {
//         param.param6[i] = 0 ; 
//     }
//     for ( int i = 0 ; i <= 5 ; i ++ )
//     {
//         param.param7[i] = 0  ; 
//     }
//     NV_access_write_data(part,(void *)&param,sizeof(system_param_t));
// }


// void write_partitions(int part) 
// {
//     system_param_t param ; 
//     NV_access_read_data(part,(void *)&param,sizeof(system_param_t));
//     // param.param1 ++ ; 
//     // param.param2 += 1.4 ;
//     param.param3 ++ ; 
//     param.param4 += 1.6 ;
//     param.param5 += 2; 
//     for ( int i = 0 ; i <= 9 ; i ++ )
//     {
//         param.param6[i] += i + 1 ; 
//     }
//     for ( int i = 0 ; i <= 5 ; i ++ )
//     {
//         param.param7[i] += i + 1  ; 
//         //param.param7[i] += i  ; 
//     }
//     NV_access_write_data(part,(void *)&param,sizeof(system_param_t));
// }
// void read_partitions(int part) 
// {
//     system_param_t param ; 
//     char sign ;
//     int num1;
//     int num2;
//     NV_access_read_data(part,(void *)&param,sizeof(system_param_t));
//     debug("param1 = %d \r\n",param.param1);
//     num1 = param.param2 ;
//     num2 = ( (param.param2 - num1 )* 10000 ) ;
//     debug("param2 = %d.%d \r\n",num1,num2);
//     debug("param3 = %d \r\n",param.param3);
//     num1 = param.param4 ;
//     num2 = ( (param.param4 - num1 )* 10000 ) ;
//     debug("param4 = %d.%d \r\n",num1,num2);
//     debug("param5 = %ld \r\n",param.param5);
//     for ( int i = 0 ; i <= 9 ; i ++ )
//     {
//         num1 = param.param6[i] ;
//         num2 = ( (param.param6[i] - num1 )* 10000 ) ;
//         debug("param6[%d] = %d.%d\r\n",i,num1,num2);
//     }
//     for ( int i = 0 ; i <= 5 ; i ++ )
//     {
//         debug("param7[%d] = %d\r\n",i,param.param7[i]);
//     }
// }


/* nv access code */

    // uart_send("start partisions init");
    // NV_access_init_partition(  ) ;
    // vTaskDelay(2000 / portTICK_PERIOD_MS);
    // NV_access_read_data(3,(void *) &param , sizeof(param) ) ;
    // if (param.param1 != 0xABCDDCBA && param.param2 != 0xABCDDCBA )
    // {
    //     uart_send("\r\ninit partition 0 \r\n") ;
    //     init_partitions(3);
    // }
    // else 
    // {
    //     uart_send("\r\n run normal \r\n") ;

    //     read_partitions(3);
    //     write_partitions(3);
    //     read_partitions(3);
    // }

// typedef struct system_param
// {
//     int     param1;
//     int     param2;
//     char    param3;
//     double  param4;
//     long    param5; 
//     float   param6[10]; 
//     int     param7[6];
// }system_param_t;

// system_param_t param ;
// void init_partitions(int part) ;

// void write_partitions(int part) ;
// void read_partitions(int part) ;
