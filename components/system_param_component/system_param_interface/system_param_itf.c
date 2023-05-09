#include "system_param_itf.h"
#include "system_param_public.h"

void system_param_set(set_id_t id, void * data_ptr);
void system_param_get(get_id_t id, void * data_ptr);
void system_param_execute(request_id_t id, ARGS * arg );


component_manager_node_t system_param_node =
{
    system_param_set,
    system_param_get,
    system_param_execute
};

void system_param_module_itf_init(void)
{
    component_manager_attach_node(SYSTEM_PARAM,& system_param_node);
}

void system_param_set(set_id_t id, void * data_ptr)
{
    switch (id)
    {

    default:
        /* do nothing */
        break;
    }
}
void system_param_get(get_id_t id, void * data_ptr)
{
    switch (id)
    {

    default:
        /* do nothing */
        break;
    }
}
void system_param_execute(request_id_t id, ARGS * arg )
{
    switch (id)
    {
    
    case SYSTEM_PARAM_READ:
        *((BOOL *)arg->ret) = system_param_read(*(int8_t*)arg->param_1,
                                                *(int32_t*)arg->param_2,
                                                *(int32_t*)arg->param_3,
                                                 (void *)arg->param_4);
        break;
    
    case SYSTEM_PARAM_WRITE:
        *((BOOL *)arg->ret) = system_param_write(*(int8_t*)arg->param_1,
                                                *(int32_t*)arg->param_2,
                                                *(int32_t*)arg->param_3,
                                                 (void *)arg->param_4);
        break;
    
    case SYSTEM_PARAM_FIRST_RUN:
        *((BOOL *)arg->ret) = system_param_first_run_init();
        break;
    
    case SYSTEM_PARAM_CHECK_FIRST_RUN:
        *((BOOL *)arg->ret) = system_param_first_run_check();
        break;
    
    case SYSTEM_PARAM_INIT:
        *((BOOL *)arg->ret) = system_param_init();
        break;
    
    default:
        /* do nothing */
        break;
    }
}
