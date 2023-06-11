
#include "IO_component_task.h"
#include "input_handler_task.h"
#include "input_handler_task.h"
#include "IO_processor_task.h"
#include "output_handler_task.h"
#include "system_param_config.h"
#include "FreeRTOS.h"
#include "task.h"

TaskHandle_t IO_component_task_handle;

void IO_component_task_init()
{
    BaseType_t IO_component_task_create_result;

    input_handler_task_init();
    IO_processor_task_init();
    output_handler_task_init();

    IO_component_task_create_result = xTaskCreate(IO_component_task_run,
                                    "IO_component_task",
                                    CONFIG_IO_COMPONENT_TASK_STACK_DEPTH,
                                    NULL,
                                    CONFIG_IO_COMPONENT_TASK_PERIORITY,
                                    &IO_component_task_handle);
    
    if(IO_component_task_create_result != pdPASS )
    {
        configASSERT(IO_component_task_create_result);
    }
    
    
}


void IO_component_task_run()
{
    for(;;)
    {
        input_handler_task_run();
        IO_processor_task_run();
        output_handler_task_run();
        vTaskDelay(CONFIG_IO_COMPONENT_TASK_PERIOD/portTICK_PERIOD_MS ) ;
    }

    
}

