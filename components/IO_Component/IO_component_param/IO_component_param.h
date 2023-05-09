#ifndef IO_COMPONENT_PARAM_H
#define IO_COMPONENT_PARAM_H

#define CONFIG_PRESSED_TO_PIN_HANDLER 1
#define CONFIG_IO_COMPONENT_INCLUDED  1

#include "types.h"
/*******************************************************
 *          INPUT HANDLER STRUCTS
 * ****************************************************/


/*******************************************************
 *          OUTPUT HANDLER STRUCTS
 * ****************************************************/
#ifdef CONFIG_PRESSED_TO_PIN_HANDLER
typedef struct 
{
    int8_t  pin_param_state
}pressed_to_pin_param_t;
#endif  

/*******************************************************
 *          IO PROCESSOR HANDLER STRUCTS
 * ****************************************************/


/*******************************************************
 *          IO PARAM STRUCT
 * ****************************************************/
#ifdef CONFIG_IO_COMPONENT_INCLUDED
typedef struct 
{

#ifdef CONFIG_PRESSED_TO_PIN_HANDLER
    pressed_to_pin_param_t pressed_to_pin_param;
#endif


}IO_component_param_t;
#endif  

/*******************************************************
 *          public APIs
 * ****************************************************/

BOOL IO_comp_param_read(int32_t offset, int32_t size, void * buffer);
BOOL IO_comp_param_write(int32_t offset, int32_t size, void * buffer);
BOOL IO_comp_param_init();
BOOL IO_comp_param_first_run();
BOOL IO_comp_param_check_crc();



#endif