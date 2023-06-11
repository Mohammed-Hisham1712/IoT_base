#ifndef IO_COMPONENT_INTERFACE_H
#define IO_COMPONENT_INTERFACE_H

// #include "comp_mang.h"
#include "comp_mang_def.h"

typedef enum
{
    d,
}IO_COMPONENT_SET_ID;

typedef enum
{
    ds,
}IO_COMPONENT_GET_ID;

typedef enum
{
/*===============================================*/
    /* Blinking requests */
    SET_BLINK_ON_TIME,
    SET_BLINK_OFF_TIME,
    SET_BLINK_STATE,
    SET_BLINK_TIME,
    GET_BLINK_STATE,
    GET_BLINK_ON_TIME,
    GET_BLINK_OFF_TIME,
    START_FAST_BLINKING,
    START_SLOW_BLINKING,
    START_BLINKING,
    STOP_BLINKING,

/*===========================================*/
    /* PIN DRIVEN OUTPUT */
    PIN_DRIVEN_SET_STATE,
    PIN_DRIVEN_SET_STATE_DUMMY,
    PIN_DRIVEN_GET_STATE,
    PIN_DRIVEN_TOGGLE,
    PIN_DRIVEN_TOGGLE_DUMMY,
    PIN_DRIVEN_MQTT_UPDATE,
    PIN_DRIVEN_MQTT_GET_STATE,
/*===========================================*/
    /* PRESSED TO RESET HANDLER */
    ATTACH_RESET_CALL_BACK,


}IO_COMPONENT_EXECUTE_ID;

/*==============================================================================*/
    /* Blinking requests */
EXECUTE_PROTO(IO_COMPONENT,SET_BLINK_ON_TIME,BOOL *, uint8_t * , uint16_t *);
EXECUTE_PROTO(IO_COMPONENT,SET_BLINK_OFF_TIME,BOOL *, uint8_t * , uint16_t *);
EXECUTE_PROTO(IO_COMPONENT,SET_BLINK_STATE,BOOL *, uint8_t * , uint8_t *);

EXECUTE_PROTO(IO_COMPONENT,GET_BLINK_ON_TIME,BOOL *, uint8_t * , uint16_t *);
EXECUTE_PROTO(IO_COMPONENT,GET_BLINK_OFF_TIME,BOOL *, uint8_t * , uint16_t *);
EXECUTE_PROTO(IO_COMPONENT,GET_BLINK_STATE,BOOL *, uint8_t * , uint8_t *);

EXECUTE_PROTO(IO_COMPONENT,START_FAST_BLINKING,BOOL *, uint8_t *);
EXECUTE_PROTO(IO_COMPONENT,START_SLOW_BLINKING,BOOL *, uint8_t *);
EXECUTE_PROTO(IO_COMPONENT,START_BLINKING,BOOL *, uint8_t *);
EXECUTE_PROTO(IO_COMPONENT,STOP_BLINKING,BOOL *, uint8_t *);

/*==============================================================================*/
    /* PIN DRIVEN OUTPUT */
EXECUTE_PROTO(IO_COMPONENT,PIN_DRIVEN_SET_STATE,error_t *,uint8_t *,uint8_t *);
EXECUTE_PROTO(IO_COMPONENT,PIN_DRIVEN_SET_STATE_DUMMY,error_t *,uint8_t*,uint8_t*);
EXECUTE_PROTO(IO_COMPONENT,PIN_DRIVEN_GET_STATE,uint8_t *,uint8_t*);
EXECUTE_PROTO(IO_COMPONENT,PIN_DRIVEN_TOGGLE,error_t *,uint8_t*);
EXECUTE_PROTO(IO_COMPONENT,PIN_DRIVEN_TOGGLE_DUMMY,error_t *,uint8_t*);
EXECUTE_PROTO(IO_COMPONENT,PIN_DRIVEN_MQTT_UPDATE,BOOL *,uint8_t*,uint8_t*);
EXECUTE_PROTO(IO_COMPONENT,PIN_DRIVEN_MQTT_GET_STATE,BOOL *,uint8_t*,uint8_t*);
/*==============================================================================*/
/*==============================================================================*/
    /* PRESSED TO RESET HANDLER */
EXECUTE_PROTO(IO_COMPONENT,ATTACH_RESET_CALL_BACK,BOOL *,void *);

/*==============================================================================*/
    /*  */
void IO_component_itf_init(void);

#endif