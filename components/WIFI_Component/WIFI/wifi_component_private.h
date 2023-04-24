#ifndef __WIFI_COMPONENT_H__

#define __WIFI_COMPONENT_H__

#include "wifi_component_public.h"
#include "wifi_ap_private.h"
#include "types.h"

#define WIFI_COMPONENT_STACK_SIZE       CONFIG_WIFI_COMPONENT_STACK_SIZE
#define WIFI_COMPONENT_TSK_PRI          CONFIG_WIFI_COMPONENT_TSK_PRI

typedef enum
{
    WIFI_COMPONENT_STATE_NONE,
    WIFI_COMPONENT_STATE_INIT,
    WIFI_COMPONENT_STATE_AP,
    WIFI_COMPONENT_STATE_STA,
    WIFI_COMPONENT_STATE_MAX
} wifi_component_state_t;


typedef struct 
{
    wifi_component_state_t state;
} wifi_component_ctrl_t;

#endif