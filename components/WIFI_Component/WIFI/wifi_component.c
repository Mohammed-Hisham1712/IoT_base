#include "wifi_component_private.h"
#include "wifi_ap_private.h"
#include "wifi_sta_private.h"
#include "types.h"

#include "esp_event.h"
#include "esp_wifi.h"
#include "esp_err.h"
#include "esp_log.h"
#include "tcpip_adapter.h"
#include "esp_netif.h"

#include <stdint.h>
#include <string.h>
#include <stddef.h>

#define WIFI_COMP_TAG      "WIFI_COMP"

#if CONFIG_WIFI_COMPONENT_LOGE_ENABLED
#define WIFI_COMP_LOGE_FORMAT        "[LINE:%d] [%s]"
#define WIFI_COMP_LOGE(__msg)        ESP_LOGE(WIFI_COMP_TAG, WIFI_COMP_LOGE_FORMAT, \
                                                                        __LINE__, __msg)
#else
#define WIFI_COMP_LOGE(_msg)
#endif

ESP_EVENT_DEFINE_BASE(WIFI_COMP_EVENT);

/* ************Callbacks**********************/

static void wifi_component_wifi_event_cb
                    (void* args, esp_event_base_t event_base, int32_t event_id, void* data);
static void wifi_component_ip_event_cb
                    (void* args, esp_event_base_t event_base, int32_t event_id, void* data);
/********************************************/


/**************Static functions**************/

static void wifi_component_run(void* args);
static error_t wifi_component_trans_to(wifi_component_trans_t trans);

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
            wifi_sta_scan_done_event(&wifi_component_ctrl.sta_ctrl, 
                                            (wifi_event_sta_scan_done_t*) pdata);
            break;
        case WIFI_EVENT_STA_START:
            wifi_sta_started_event(&wifi_component_ctrl.sta_ctrl);
            break;
        case WIFI_EVENT_STA_STOP:
            break;
        case WIFI_EVENT_STA_CONNECTED:
            wifi_sta_connected_event(&wifi_component_ctrl.sta_ctrl, 
                                            (wifi_event_sta_connected_t*) pdata);
            break;
        case WIFI_EVENT_STA_DISCONNECTED:
            wifi_sta_disconnected_event(&wifi_component_ctrl.sta_ctrl,
                                            (wifi_event_sta_disconnected_t*) pdata);
            break;
        case WIFI_EVENT_AP_START:
            wifi_ap_started_event(&wifi_component_ctrl.ap_ctrl);
            break;
        case WIFI_EVENT_AP_STOP:
            wifi_ap_stopped_event(&wifi_component_ctrl.ap_ctrl);
            break;
        case WIFI_EVENT_AP_STACONNECTED:
            wifi_ap_sta_connected_event(&wifi_component_ctrl.ap_ctrl, 
                                                (wifi_event_ap_staconnected_t*) pdata);
            break;
        case WIFI_EVENT_AP_STADISCONNECTED:
            wifi_ap_sta_disconnected_event(&wifi_component_ctrl.ap_ctrl, 
                                                (wifi_event_ap_staconnected_t*) pdata);
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
            wifi_sta_got_ip_event(&wifi_component_ctrl.sta_ctrl, (ip_event_got_ip_t*) pdata);
            break;
    
    default:
        break;
    }
}

static error_t wifi_component_trans_to(wifi_component_trans_t trans)
{
    if(esp_wifi_stop() != ESP_OK)
    {
        return RET_FAILED;
    }

    switch(trans)
    {
        case WIFI_COMPONENT_TRANS_TO_AP:
            if(esp_wifi_set_mode(WIFI_MODE_AP) != ESP_OK)
            {
                return RET_FAILED;
            }
            
            wifi_sta_deinit(&wifi_component_ctrl.sta_ctrl);
            wifi_ap_init(&wifi_component_ctrl.ap_ctrl);

            break;
        case WIFI_COMPONENT_TRANS_TO_STA:
            if(esp_wifi_set_mode(WIFI_MODE_STA) != ESP_OK)
            {
                return RET_FAILED;
            }

            wifi_ap_deinit(&wifi_component_ctrl.ap_ctrl);
            wifi_sta_init(&wifi_component_ctrl.sta_ctrl, 
                                        &wifi_component_ctrl.param.target_ap_desc);
            break;
        case WIFI_COMPONENT_TRANS_TO_APSTA:
            if(esp_wifi_set_mode(WIFI_MODE_APSTA) != ESP_OK)
            {
                return RET_FAILED;
            }

            wifi_ap_init(&wifi_component_ctrl.ap_ctrl);
            wifi_sta_init(&wifi_component_ctrl.sta_ctrl, 
                                        &wifi_component_ctrl.param.target_ap_desc);
            break;
        default:
            return RET_FAILED;
    }

    if(esp_wifi_start() != ESP_OK)
    {
        return RET_FAILED;
    }

    return RET_OK;
}

static void wifi_component_run(void* args)
{
    wifi_component_ctrl_t* l_ctrl;

    (void) args;
    l_ctrl = &wifi_component_ctrl;

    while(1)
    {
        switch(l_ctrl->state)
        {
            case WIFI_COMPONENT_STATE_INIT:
                if(l_ctrl->param.ap_provisioned)
                {
                    l_ctrl->state = WIFI_COMPONENT_STATE_STA;
                    esp_wifi_set_mode(WIFI_MODE_STA);
                    wifi_sta_init(&l_ctrl->sta_ctrl, &l_ctrl->param.target_ap_desc);
                }
                else
                {
                    l_ctrl->state = WIFI_COMPONENT_STATE_AP;
                    esp_wifi_set_mode(WIFI_MODE_AP);
                    wifi_ap_init(&l_ctrl->ap_ctrl);
                }
                esp_wifi_start();
                break;
            case WIFI_COMPONENT_STATE_AP:
                wifi_ap_run(&l_ctrl->ap_ctrl);

                if(l_ctrl->control_status & WIFI_COMPONENT_TARGET_AP_SET)
                {
                    l_ctrl->control_status &= ~WIFI_COMPONENT_TARGET_AP_SET;

                    if(wifi_component_trans_to(WIFI_COMPONENT_TRANS_TO_APSTA) 
                                                                        == RET_OK)
                    {
                        l_ctrl->state = WIFI_COMPONENT_STATE_APSTA;
                        ESP_LOGD(WIFI_COMP_TAG, "Transitioning to APSTA");
                    }
                    else
                    {
                        WIFI_COMP_LOGE("Trans. to APSTA failed");
                    }
                }
                break;
            case WIFI_COMPONENT_STATE_STA:
                wifi_sta_run(&l_ctrl->sta_ctrl);
                break;
            case WIFI_COMPONENT_STATE_APSTA:
                wifi_ap_run(&l_ctrl->ap_ctrl);
                wifi_sta_run(&l_ctrl->sta_ctrl);

                if(l_ctrl->control_status & WIFI_COMPONENT_TARGET_AP_CHANGED)
                {
                    l_ctrl->control_status &= ~WIFI_COMPONENT_TARGET_AP_CHANGED;
                }

                if(l_ctrl->control_status & WIFI_COMPONENT_TARGET_AP_DELETED)
                {
                    l_ctrl->control_status &= ~WIFI_COMPONENT_TARGET_AP_DELETED;

                    if(wifi_component_trans_to(WIFI_COMPONENT_TRANS_TO_AP) == RET_OK)
                    {
                        l_ctrl->state = WIFI_COMPONENT_STATE_AP;
                        ESP_LOGD(WIFI_COMP_TAG, "Transitioning to AP");
                    }
                    else
                    {
                        WIFI_COMP_LOGE("Trans. to AP mode failed");
                    }
                }

                break;
            default:
                break;
                /* TODO: assert */
        }

        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
}

error_t wifi_comp_event_register(wifi_comp_event_t event_id, 
                                                esp_event_handler_t hdl, void* arg)
{
    if(hdl && (event_id < WIFI_COMP_EVENT_MAX))
    {
        if(esp_event_handler_register(WIFI_COMP_EVENT, event_id, hdl, arg) == ESP_OK)
        {
            return RET_OK;
        }
    }

    return RET_FAILED;
}

error_t wifi_comp_event_unregister(wifi_comp_event_t event_id, esp_event_handler_t hdl)
{
    if(hdl && (event_id < WIFI_COMP_EVENT_MAX))
    {
        if(esp_event_handler_unregister(WIFI_COMP_EVENT, event_id, hdl) == ESP_OK)
        {
            return RET_OK;
        }
    }

    return RET_FAILED;
}

error_t wifi_component_init(void)
{
    wifi_init_config_t wifi_init = WIFI_INIT_CONFIG_DEFAULT();

    memset(&wifi_component_ctrl, 0, sizeof(wifi_component_ctrl_t));

    if(wifi_param_load(&wifi_component_ctrl.param) != RET_OK)
    {
        ESP_LOGE(WIFI_COMP_TAG, "Error loading params");
        return RET_FAILED;
    }

    esp_netif_init();
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

error_t wifi_component_set_target_ap(wifi_ap_desc_t* p_ap_desc)
{
    error_t l_ret;

    l_ret = RET_FAILED;

    if(p_ap_desc)
    {
        if((p_ap_desc->ap_ssid_len > 0) && (p_ap_desc->ap_passphrase_len > 0))
        {
            if(wifi_component_ctrl.control_status == 0)
            {
                memcpy(&wifi_component_ctrl.param.target_ap_desc, p_ap_desc, 
                                                            sizeof(wifi_ap_desc_t));
                if(wifi_component_ctrl.param.ap_provisioned == 0)
                {
                    wifi_component_ctrl.param.ap_provisioned = 1;
                    wifi_component_ctrl.control_status |= WIFI_COMPONENT_TARGET_AP_SET;
                }
                else
                {
                    wifi_component_ctrl.control_status |= 
                                                WIFI_COMPONENT_TARGET_AP_CHANGED;
                }

                l_ret = RET_OK;
            }
        }
    }
    
    return l_ret;
}

error_t wifi_component_apply_config(void)
{
    return wifi_param_store(&wifi_component_ctrl.param);
}

error_t wifi_component_reset_config(void)
{
    error_t l_ret;

    l_ret = RET_FAILED;

    if(wifi_component_ctrl.control_status == 0)
    {
        if(wifi_param_load(&wifi_component_ctrl.param) == RET_OK)
        {
            if(wifi_component_ctrl.param.ap_provisioned)
            {
                wifi_component_ctrl.control_status |= WIFI_COMPONENT_TARGET_AP_CHANGED;
            }
            else
            {
                wifi_component_ctrl.control_status |= WIFI_COMPONENT_TARGET_AP_DELETED;
            }

            l_ret = RET_OK;
        }
    }

    return l_ret;
}

error_t wifi_component_get_sta_status(wifi_sta_status_t* status)
{
    return wifi_sta_get_status(&wifi_component_ctrl.sta_ctrl, status);
}