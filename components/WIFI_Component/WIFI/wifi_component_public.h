#ifndef __WIFI_COMPONENT_PUBLIC_H__

#define __WIFI_COMPONENT_PUBLIC_H__

#include "wifi_ap_public.h"
#include "wifi_sta_public.h"
#include  "types.h"

#include "esp_event.h"


typedef enum
{
    WIFI_COMP_EVENT_INTERNET_DOWN,
    WIFI_COMP_EVENT_INTERNET_UP,
    WIFI_COMP_EVENT_STA_DISCONNECTED,
    WIFI_COMP_EVENT_STA_CONNECTED,
    WIFI_COMP_EVENT_STA_IP_CHANGED,
    WIFI_COMP_EVENT_MAX,
} wifi_comp_event_t;

/**
 * @brief 
 * 
 * @param event_id 
 * @param hdl 
 * @param arg
 * @return error_t 
 */
error_t wifi_comp_event_register(wifi_comp_event_t event_id, 
                                                esp_event_handler_t hdl, void* arg);

/**
 * @brief 
 * 
 * @param event_id 
 * @return error_t 
 */
error_t wifi_comp_event_unregister(wifi_comp_event_t event_id, esp_event_handler_t hdl);


/**
 * @brief 
 * 
 * @return error_t 
 */
error_t wifi_component_init(void);

#endif