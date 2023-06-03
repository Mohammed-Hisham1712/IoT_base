#include "wifi_ap_private.h"
#include "wifi_prov_public.h"

#include "esp_wifi_types.h"
#include "esp_wifi.h"
#include "esp_log.h"
#include "esp_err.h"


#include <string.h>
#include <stdint.h>
#include <stddef.h>

#define WIFI_AP_TAG                "WIFI_AP"

#if CONFIG_WIFI_COMPONENT_LOGE_ENABLED
#define WIFI_AP_LOGE_FORMAT        "[LINE:%d] [%s]"
#define WIFI_AP_LOGE(__msg)        ESP_LOGE(WIFI_AP_TAG, WIFI_AP_LOGE_FORMAT, __LINE__, __msg)
#else
#define WIFI_AP_LOGE(_msg)
#endif


wifi_ap_state_t wifi_ap_get_state(wifi_ap_ctrl_t* p_wifi_ap)
{
    if(p_wifi_ap)
    {
        return p_wifi_ap->ap_state;    
    }
    
    return WIFI_AP_STATE_INVALID;
}

error_t wifi_ap_get_own_ssid(wifi_ap_ctrl_t* p_wifi_ap, char* p_ssid, uint16_t size)
{
    wifi_ap_desc_t* p_ap_desc;
    error_t l_ret;

    l_ret = RET_FAILED;

    if(p_wifi_ap && p_ssid)
    {
        p_ap_desc = &p_wifi_ap->ap_desc;

        if(p_ap_desc->ap_ssid_len && (size >= p_ap_desc->ap_ssid_len))
        {
            memcpy(p_ssid, p_ap_desc->ap_ssid, p_ap_desc->ap_ssid_len);
            l_ret = RET_OK;
        }
    }

    return l_ret;
}

error_t wifi_ap_get_own_passphrase(wifi_ap_ctrl_t* p_wifi_ap, char* p_passphrase, uint16_t size)
{
    wifi_ap_desc_t* p_ap_desc;
    error_t l_ret;

    l_ret = RET_FAILED;

    if(p_wifi_ap && p_passphrase)
    {
        p_ap_desc = &p_wifi_ap->ap_desc;

        if(p_ap_desc->ap_passphrase_len && (size >= p_ap_desc->ap_passphrase_len))
        {
            memcpy(p_passphrase, p_ap_desc->ap_passphrase, p_ap_desc->ap_passphrase_len);
            l_ret = RET_OK;
        }
    }

    return l_ret;
}

uint16_t wifi_ap_get_own_ssid_len(wifi_ap_ctrl_t* p_wifi_ap)
{
    if(p_wifi_ap)
    {
        return p_wifi_ap->ap_desc.ap_ssid_len;
    }

    return 0;
}

uint16_t wifi_ap_get_own_passphrase_len(wifi_ap_ctrl_t* p_wifi_ap)
{
    if(p_wifi_ap)
    {
        return p_wifi_ap->ap_desc.ap_passphrase_len;
    }

    return 0;
}

error_t wifi_ap_set_ssid(wifi_ap_desc_t* p_desc, const char* ssid, uint16_t len)
{
    error_t l_ret = RET_FAILED;

    if(p_desc && ssid)
    {
        if((len != 0) && (len <= WIFI_AP_SSID_MAX_LENGTH))
        {
            /* String is null terminated */
            if(ssid[len - 1] == '\0')
            {
                p_desc->ap_ssid_len = len;
                memcpy(p_desc->ap_ssid, ssid, len);

                l_ret = RET_OK;
            }
        }
    }

    return l_ret;
}

error_t wifi_ap_set_passphrase(wifi_ap_desc_t* p_desc, const char* passphrase, uint16_t len)
{
    error_t l_ret = RET_FAILED;

    if(p_desc && passphrase)
    {
        if((len != 0) && (len <= WIFI_AP_MAX_PASSPHRASE_LENGTH))
        {
            /* String is null terminated */
            if(passphrase[len - 1] == '\0')
            {
                p_desc->ap_passphrase_len = len;
                memcpy(p_desc->ap_passphrase, passphrase, len);

                l_ret = RET_OK;
            }
        }
    }

    return l_ret;
}

error_t wifi_ap_set_bssid(wifi_ap_desc_t* p_desc, uint8_t* mac)
{
    error_t l_ret = RET_FAILED;

    if(p_desc && mac)
    {
        memcpy(p_desc->ap_bssid, mac, 6);

        l_ret = RET_OK;
    }

    return l_ret;
}

error_t wifi_ap_started_event(wifi_ap_ctrl_t* p_wifi_ap)
{
    if(p_wifi_ap)
    {
        ESP_LOGD(WIFI_AP_TAG, "AP Started");
        p_wifi_ap->ap_state = WIFI_AP_STATE_STARTED;
        p_wifi_ap->ap_phase = WIFI_AP_PHASE_DONE;

        return RET_OK;
    }

    WIFI_AP_LOGE("Wrong state");

    return RET_FAILED;
}

error_t wifi_ap_stopped_event(wifi_ap_ctrl_t* p_wifi_ap)
{
    if(p_wifi_ap)
    {
        ESP_LOGD(WIFI_AP_TAG, "AP Stopped");
        p_wifi_ap->ap_state = WIFI_AP_STATE_STOPPED;
        p_wifi_ap->ap_phase = WIFI_AP_PHASE_DONE;

        return RET_OK;
    }

    WIFI_AP_LOGE("Wrong state");

    return RET_FAILED;
}

error_t wifi_ap_sta_connected_event(wifi_ap_ctrl_t* p_wifi_ap, 
                                                wifi_event_ap_staconnected_t* p_sta)
{
    wifi_ap_connected_sta_t* p_info;

    /* No stations already connected */
    if(p_wifi_ap && p_sta)
    {
        p_info = &p_wifi_ap->sta_info;

        if(!p_info->sta_connected)
        {
            p_info->sta_connected = 1;
            memcpy(p_info->sta_mac, p_sta->mac, sizeof(p_info->sta_mac));
            ESP_LOGD(WIFI_AP_TAG, "[STA connected] MAC:"MACSTR, MAC2STR(p_info->sta_mac));

            return RET_OK;
        }
    }

    return RET_FAILED;
}

error_t wifi_ap_sta_disconnected_event(wifi_ap_ctrl_t* p_wifi_ap, 
                                                wifi_event_ap_staconnected_t* p_sta)
{
    wifi_ap_connected_sta_t* p_info;

    if(p_wifi_ap && p_sta)
    {
        p_info = &p_wifi_ap->sta_info;

        if(p_info->sta_connected)
        {
            p_info = &p_wifi_ap->sta_info;
            p_info->sta_connected = 0;
            ESP_LOGD(WIFI_AP_TAG, "[STA disconnected] MAC:"MACSTR, MAC2STR(p_info->sta_mac));
            memset(p_info->sta_mac, 0, sizeof(p_info->sta_mac));

            /* TODO: Handle station disconnection */

            return RET_OK;
        }
    }

    return RET_FAILED;
}

error_t wifi_ap_init(wifi_ap_ctrl_t* p_wifi_ap)
{
    wifi_ap_desc_t* p_ap_desc;
    wifi_config_t wifi_ap_config;
    wifi_mode_t mode;
    error_t l_ret;

    l_ret = RET_FAILED;

    if(esp_wifi_get_mode(&mode) != ESP_OK)
    {
        return l_ret;
    }

    if(p_wifi_ap && (mode == WIFI_MODE_AP || mode == WIFI_MODE_APSTA))
    {
        p_ap_desc = &p_wifi_ap->ap_desc;

        memset(p_wifi_ap, 0, sizeof(wifi_ap_ctrl_t));

        #if WIFI_AP_NAME_AUTOGEN

        #else
        memcpy(p_wifi_ap->ap_desc.ap_ssid, WIFI_AP_NAME, sizeof(WIFI_AP_NAME));
        p_wifi_ap->ap_desc.ap_ssid_len = sizeof(WIFI_AP_NAME);
        #endif

        #if WIFI_AP_PASSPHRASE_AUTOGEN

        #else
        memcpy(p_wifi_ap->ap_desc.ap_passphrase, WIFI_AP_PASSPHRASE, sizeof(WIFI_AP_PASSPHRASE));
        p_wifi_ap->ap_desc.ap_passphrase_len = sizeof(WIFI_AP_PASSPHRASE);
        #endif

        memset(&wifi_ap_config, 0, sizeof(wifi_config_t));
        memcpy(wifi_ap_config.ap.ssid, p_ap_desc->ap_ssid, p_ap_desc->ap_ssid_len);
        memcpy(wifi_ap_config.ap.password, p_ap_desc->ap_passphrase, 
                                                                p_ap_desc->ap_passphrase_len);
        wifi_ap_config.ap.ssid_len = 0;
        wifi_ap_config.ap.channel = 0;
        wifi_ap_config.ap.authmode = WIFI_AP_AUTHMODE;
        wifi_ap_config.ap.ssid_hidden = WIFI_AP_SSID_HIDDEN;
        wifi_ap_config.ap.max_connection = 1;

        if(esp_wifi_set_config(WIFI_IF_AP, &wifi_ap_config) != ESP_OK)
        {
            WIFI_AP_LOGE("Cannot set AP configuration");
            return l_ret;
        }
            
        p_wifi_ap->ap_state = WIFI_AP_STATE_INIT;
        p_wifi_ap->ap_phase = WIFI_AP_PHASE_DONE;
        l_ret = RET_OK;

        ESP_LOGD(WIFI_AP_TAG, "WIFI AP init done");
    }

    return l_ret;
}

error_t wifi_ap_deinit(wifi_ap_ctrl_t* p_wifi_ap)
{
    if(p_wifi_ap)
    {
        memset(p_wifi_ap, 0, sizeof(wifi_ap_ctrl_t));

        return RET_OK;
    }

    return RET_FAILED;
}

error_t wifi_ap_run(wifi_ap_ctrl_t* p_wifi_ap)
{
    wifi_ap_desc_t* p_ap_desc;
    error_t l_ret;

    p_ap_desc = &p_wifi_ap->ap_desc;
    l_ret = RET_FAILED;

    switch(p_wifi_ap->ap_state)
    {
        case WIFI_AP_STATE_INIT:
            break;
        case WIFI_AP_STATE_STARTED:
            if(p_wifi_ap->ap_phase == WIFI_AP_PHASE_DONE)
            {
                p_wifi_ap->ap_state = WIFI_AP_STATE_PROVISIONING;
                p_wifi_ap->ap_phase = WIFI_AP_PHASE_WAITING;

                if(wifi_prov_start() != RET_OK)
                {
                    return l_ret;
                }
            }
            else if(p_wifi_ap->ap_phase == WIFI_AP_PHASE_IN_PROGRESS)
            {

            }
            else
            {
                return l_ret;
            }
            break;
        
        case WIFI_AP_STATE_PROVISIONING:
            if(p_wifi_ap->ap_phase == WIFI_AP_PHASE_WAITING)
            {
                if(p_wifi_ap->sta_info.sta_connected)
                {
                    ESP_LOGD(WIFI_AP_TAG, "HTTP provisioning started");
                    p_wifi_ap->ap_phase = WIFI_AP_PHASE_IN_PROGRESS;
                }
            }
            else if(p_wifi_ap->ap_phase == WIFI_AP_PHASE_IN_PROGRESS)
            {
                if(!p_wifi_ap->sta_info.sta_connected)
                {
                    ESP_LOGD(WIFI_AP_TAG, "HTTP provisioning done");
                    p_wifi_ap->ap_phase = WIFI_AP_PHASE_DONE;
                }
            }
            else if(p_wifi_ap->ap_phase == WIFI_AP_PHASE_DONE)
            {
                p_wifi_ap->ap_state = WIFI_AP_STATE_STOPPED;
                p_wifi_ap->ap_phase = WIFI_AP_PHASE_IN_PROGRESS;

                if(esp_wifi_stop() != ESP_OK)
                {
                    WIFI_AP_LOGE("Cannot stop WIFI AP");
                    return l_ret;
                }
            }
            else
            {
                return l_ret;
            }
            break;
        case WIFI_AP_STATE_STOPPED:
            if(p_wifi_ap->ap_phase == WIFI_AP_PHASE_DONE)
            {
                p_wifi_ap->ap_state = WIFI_AP_STATE_NONE;
            }
            else if(p_wifi_ap->ap_phase == WIFI_AP_PHASE_IN_PROGRESS)
            {

            }
            else
            {
                return l_ret;
            }
            break;
        default:
            return l_ret;
    }

    return l_ret;
}