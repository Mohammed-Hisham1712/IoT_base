#ifndef IO_COMPONENT_PARAM_H
#define IO_COMPONENT_PARAM_H



#include "types.h"
/*******************************************************
 *          INPUT HANDLER STRUCTS
 * ****************************************************/
typedef struct IO_PIN_DRIVEN_HANDLER
{
    int16_t  pin_param_state ;
}IO_pin_driven_param_t;


/*******************************************************
 *          OUTPUT HANDLER STRUCTS
 * ****************************************************/


/*******************************************************
 *          IO PROCESSOR HANDLER STRUCTS
 * ****************************************************/


/*******************************************************
 *          IO PARAM STRUCT
 * ****************************************************/
typedef struct 
{



    IO_pin_driven_param_t pin_driven_param;

}IO_component_param_t;

/*******************************************************
 *          public APIs
 * ****************************************************/

BOOL IO_comp_param_read(int32_t offset, int32_t size, void * buffer);
BOOL IO_comp_param_write(int32_t offset, int32_t size, void * buffer);
BOOL IO_comp_param_init();
BOOL IO_comp_param_first_run();
BOOL IO_comp_param_check_crc();



#endif