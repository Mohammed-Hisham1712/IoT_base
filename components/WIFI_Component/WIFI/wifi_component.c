#include "wifi_component_private.h"
#include "wifi_ap_private.h"
#include "wifi_sta_private.h"
#include "types.h"

#include "esp_event.h"
#include "esp_wifi.h"
#include "esp_err.h"
#include "esp_log.h"
#include "tcpip_adapter.h"

#include <stdint.h>
#include <string.h>
#include <stddef.h>

/* ************Callbacks**********************/

static void wifi_component_wifi_event_cb
                    (void* args, esp_event_base_t event_base, int32_t event_id, void* data);
static void wifi_component_ip_event_cb
                    (void* args, esp_event_base_t event_base, int32_t event_id, void* data);
/********************************************/


/**************Static functions**************/

static void wifi_component_run(void* args);
/*******************************************/


/***************Global variables************/

static wifi_component_ctrl_t wifi_component_ctrl;
/*******************************************/

/*************Function definitions**********/

static void wifi_component_wifi_event_cb
                    (void* args, esp_event_base_t event_base, int32_t event_id, void* pdata)
{
    (void) args;
    (void) event_base;

    switch(event_id)
    {
        case WIFI_EVENT_SCAN_DONE:
            wifi_sta_scan_done_event((wifi_event_sta_scan_done_t*) pdata);
            break;
        case WIFI_EVENT_STA_START:
            wifi_sta_started_event();
            break;
        case WIFI_EVENT_STA_STOP:
            break;
        case WIFI_EVENT_STA_CONNECTED:
            wifi_sta_connected_event((wifi_event_sta_connected_t*) pdata);
            break;
        case WIFI_EVENT_STA_DISCONNECTED:
            wifi_sta_disconnected_event((wifi_event_sta_disconnected_t*) pdata);
            break;
        case WIFI_EVENT_AP_START:
            wifi_ap_started_event();
            break;
        case WIFI_EVENT_AP_STOP:
            wifi_ap_stopped_event();
            break;
        case WIFI_EVENT_AP_STACONNECTED:
            wifi_ap_sta_connected_event((wifi_event_ap_staconnected_t*) pdata);
            break;
        case WIFI_EVENT_AP_STADISCONNECTED:
            wifi_ap_sta_disconnected_event((wifi_event_ap_staconnected_t*) pdata);
            break;
    }
}

static void wifi_component_ip_event_cb
                    (void* args, esp_event_base_t event_base, int32_t event_id, void* pdata)
{
    (void) event_base;
    (void) args;

    switch (event_id)
    {
        case IP_EVENT_STA_GOT_IP:
            wifi_sta_got_ip_event((ip_event_got_ip_t*) pdata);
            break;
    
    default:
        break;
    }
}

static void wifi_component_run(void* args)
{
    wifi_component_ctrl_t* l_ctrl;
    wifi_ap_desc_t ap_desc;

    (void) args;
    l_ctrl = &wifi_component_ctrl;

    while(1)
    {
        switch(l_ctrl->state)
        {
            case WIFI_COMPONENT_STATE_INIT:
                wifi_ap_set_ssid(&ap_desc, "GHOST", sizeof("GHOST"));
                wifi_ap_set_passphrase(&ap_desc, "01002282066", sizeof("01002282066"));
                wifi_sta_init(&ap_desc);
                wifi_ap_init();
                l_ctrl->state = WIFI_COMPONENT_STATE_STA;
                break;
            case WIFI_COMPONENT_STATE_AP:
                wifi_ap_start();
                wifi_ap_prov_start();
                break;
            case WIFI_COMPONENT_STATE_STA:
                wifi_sta_run();
                break;
            default:
                break;
                /* TODO: assert */
        }

        vTaskDelay(500 / portTICK_PERIOD_MS);
    }
}

error_t wifi_component_init(void)
{
    wifi_init_config_t wifi_init = WIFI_INIT_CONFIG_DEFAULT();

    memset(&wifi_component_ctrl, 0, sizeof(wifi_component_ctrl_t));

    tcpip_adapter_init();

    ESP_ERROR_CHECK(esp_event_loop_create_default());
    ESP_ERROR_CHECK(esp_event_handler_register(WIFI_EVENT, ESP_EVENT_ANY_ID, 
                                                        wifi_component_wifi_event_cb, NULL));
    ESP_ERROR_CHECK(esp_event_handler_register(IP_EVENT, ESP_EVENT_ANY_ID, 
                                                        wifi_component_ip_event_cb, NULL));
    
    ESP_ERROR_CHECK(esp_wifi_init(&wifi_init));

    wifi_component_ctrl.state = WIFI_COMPONENT_STATE_INIT;

    xTaskCreate(wifi_component_run, "WIFI_COMP_TSK", WIFI_COMPONENT_STACK_SIZE,
                                                        NULL, WIFI_COMPONENT_TSK_PRI, NULL);
    return RET_OK;
}