#include "IO_comp_interface.h"
#include "system_include.h"

#include "debug_uart.h"

#if CONFIG_BLINKING_OUTPUT
#include "blinking_output_public.h"
#endif

#if CONFIG_PIN_DRIVEN_OUTPUT_HANDLER
#include "pin_driven_handler_public.h"
#endif

#if CONFIG_PRESSED_TO_RESET_HANDLER
#include "pressed_to_reset_public.h"
#endif


void io_comp_set(set_id_t id, void * data_ptr);
void io_comp_get(get_id_t id, void * data_ptr);
void io_comp_execute(request_id_t id, ARGS * arg );


component_manager_node_t IO_COM_node =
{
    io_comp_set,
    io_comp_get,
    io_comp_execute
};


void io_comp_set(set_id_t id, void * data_ptr)
{
    switch (id)
    {

    default:
        /* do nothing */
        break;
    }
}
void io_comp_get(get_id_t id, void * data_ptr)
{
    switch (id)
    {

    default:
        /* do nothing */
        break;
    }
}
void io_comp_execute(request_id_t id, ARGS * arg )
{
    debug("\n\rCalling IO set on time%d",0);
    switch (id)
    {

/*============================================================================================================================*/
    #if CONFIG_BLINKING_OUTPUT
    case SET_BLINK_ON_TIME:
        *((BOOL*)arg->ret) = blink_output_set_blink_on_time(*(blink_pin_t*)arg->param_1,*(uint16_t*)arg->param_2);
        break;
    case SET_BLINK_OFF_TIME:
        *(BOOL*)arg->ret = blink_output_set_blink_off_time(*(blink_pin_t*)arg->param_1,*(uint16_t*)arg->param_2);
        break;
    case SET_BLINK_STATE:
        *(BOOL*)arg->ret = blink_output_set_state(*(blink_pin_t*)arg->param_1,*(blink_state_t*)arg->param_2);
        break;
    case SET_BLINK_TIME:
        /* not implemented yet so do nothing*/
        break;
    case GET_BLINK_STATE:
        *(BOOL*)arg->ret = blink_output_get_state(*(blink_pin_t*)arg->param_1,(blink_state_t*)arg->param_2);
        break;
    case GET_BLINK_ON_TIME:
        *(BOOL*)arg->ret = blink_output_get_blink_on_time(*(blink_pin_t*)arg->param_1,(uint16_t*)arg->param_2);
        break;
    case GET_BLINK_OFF_TIME:
        *(BOOL*)arg->ret = blink_output_get_blink_off_time(*(blink_pin_t*)arg->param_1,(uint16_t*)arg->param_2);
        break;
    case START_FAST_BLINKING:
        *(BOOL*)arg->ret = blink_output_start_fast_blink(*(blink_pin_t*)arg->param_1);
        break;
    case START_SLOW_BLINKING:
        *(BOOL*)arg->ret = blink_output_start_slow_blink(*(blink_pin_t*)arg->param_1);
        break;
    case START_BLINKING:
        *(BOOL*)arg->ret = blink_output_start_blinking(*(blink_pin_t*)arg->param_1);
        break;
    case STOP_BLINKING:
        *(BOOL*)arg->ret = blink_output_stop_blinking(*(blink_pin_t*)arg->param_1);
        break;
    #endif /* END OF BLINKING OUTPUT INCLUDE*/
/*============================================================================================================================*/    
    #if CONFIG_PIN_DRIVEN_OUTPUT_HANDLER
    case PIN_DRIVEN_MQTT_GET_STATE:
        *(BOOL*)arg->ret = pin_driven_handler_mqtt_get_state(*(PIN_DRIVEN_NUM*)arg->param_1,(PIN_DRIVEN_STATE*)arg->param_2);
        break;
    case PIN_DRIVEN_MQTT_UPDATE:
        *(BOOL*)arg->ret= pin_driven_handler_mqtt_update(*(PIN_DRIVEN_NUM*)arg->param_1,*(PIN_DRIVEN_STATE*)arg->param_2);
        break;
    case PIN_DRIVEN_TOGGLE_DUMMY:
        *(error_t*)arg->ret= pin_driven_toggle_dummy(*(PIN_DRIVEN_NUM*)arg->param_1);
        break;
    case PIN_DRIVEN_TOGGLE:
        *(error_t*)arg->ret= pin_driven_toggle(*(PIN_DRIVEN_NUM*)arg->param_1);
        break;
    case PIN_DRIVEN_GET_STATE:
        *(PIN_DRIVEN_STATE *)arg->ret= pin_driven_get_state(*(PIN_DRIVEN_NUM*)arg->param_1);
        break;
    case PIN_DRIVEN_SET_STATE: 
        *(error_t*)arg->ret= pin_driven_set_state(*(PIN_DRIVEN_NUM*)arg->param_1,*(PIN_DRIVEN_STATE*)arg->param_2);
        break;
    case PIN_DRIVEN_SET_STATE_DUMMY:
        *(error_t*)arg->ret= pin_driven_set_state_dummy(*(PIN_DRIVEN_NUM*)arg->param_1,*(PIN_DRIVEN_STATE*)arg->param_2);
        break;
    #endif /* END OF PIN DRIVEN OUTPUT HANDLER*/
/*============================================================================================================================*/    
/*============================================================================================================================*/    
    #if CONFIG_PRESSED_TO_RESET_HANDLER
    case ATTACH_RESET_CALL_BACK:
    *(BOOL*)arg->ret = press_to_reset_attach_reset_call_back((reset_call_back)arg->param_1);
    #endif /* END OF PIN DRIVEN OUTPUT HANDLER*/
/*============================================================================================================================*/    

    default:
        /* do nothing */
        break;
    }
}

void IO_component_itf_init(void)
{
    component_manager_attach_node(IO_COMPONENT,& IO_COM_node);

}

