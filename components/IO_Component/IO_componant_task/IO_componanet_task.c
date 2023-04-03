
#include "IO_component_task.h"
#include "input_handler_task.h"
#include "input_handler_task.h"
#include "IO_processor_task.h"
#include "output_handler_task.h"

void IO_component_task_init()
{
    
    input_handler_task_init();
    IO_processor_task_init();
    output_handler_task_init();
}


void IO_component_task_run()
{
    input_handler_task_run();
    IO_processor_task_run();
    output_handler_task_run();
}

