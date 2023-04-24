#include "wifi_ap_private.h"

#include "esp_wifi_types.h"
#include "esp_wifi.h"
#include "esp_log.h"
#include "esp_err.h"
#include "protocomm.h"
#include "protocomm_httpd.h"
#include "protocomm_security0.h"

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

static wifi_ap_ctrl_t wifi_ap_ctrl;
static wifi_ap_desc_t wifi_ap_desc;

static wifi_ap_config_desc_t wifi_config_desc[] = 
{
    {WIFI_CONFIG_AP_INFO_EP, wifi_config_ap_set_info_req_handler, (void*) &wifi_ap_desc}
};

#define WIFI_AP_CONFIG_DESC_SIZE   (sizeof(wifi_config_desc) / sizeof(wifi_ap_config_desc_t))

wifi_ap_state_t wifi_ap_get_state(void)
{
    return wifi_ap_ctrl.ap_state;
}

error_t wifi_ap_get_own_ssid(char* p_ssid, uint16_t size)
{
    error_t l_ret = RET_FAILED;

    if(p_ssid)
    {
        if(wifi_ap_desc.ap_ssid_len && (size >= wifi_ap_desc.ap_ssid_len))
        {
            memcpy(p_ssid, wifi_ap_desc.ap_ssid, wifi_ap_desc.ap_ssid_len);
            l_ret = RET_OK;
        }
    }

    return l_ret;
}

error_t wifi_ap_get_own_passphrase(char* p_passphrase, uint16_t size)
{
    error_t l_ret = RET_FAILED;

    if(p_passphrase)
    {
        if(wifi_ap_desc.ap_passphrase_len && (size >= wifi_ap_desc.ap_passphrase_len))
        {
            memcpy(p_passphrase, wifi_ap_desc.ap_passphrase, wifi_ap_desc.ap_passphrase_len);
            l_ret = RET_OK;
        }
    }

    return l_ret;
}

uint16_t wifi_ap_get_own_ssid_len(void)
{
    return wifi_ap_desc.ap_ssid_len;
}

uint16_t wifi_ap_get_own_passphrase_len(void)
{
    return wifi_ap_desc.ap_passphrase_len;
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

error_t wifi_ap_started_event(void)
{
    if(wifi_ap_ctrl.ap_state == WIFI_AP_STATE_INIT)
    {
        ESP_LOGD(WIFI_AP_TAG, "AP Started");
        wifi_ap_ctrl.ap_state = WIFI_AP_STATE_STARTED;

        return RET_OK;
    }

    WIFI_AP_LOGE("Wrong state");

    return RET_FAILED;
}

error_t wifi_ap_stopped_event(void)
{
    if(wifi_ap_ctrl.ap_state == WIFI_AP_STATE_STARTED)
    {
        ESP_LOGD(WIFI_AP_TAG, "AP Stopped");
        wifi_ap_ctrl.ap_state = WIFI_AP_STATE_STOPPED;

        return RET_OK;
    }

    WIFI_AP_LOGE("Wrong state");

    return RET_FAILED;
}

error_t wifi_ap_sta_connected_event(wifi_event_ap_staconnected_t* p_sta)
{
    wifi_ap_connected_sta_t* p_info = &wifi_ap_ctrl.sta_info;

    /* No stations already connected */
    if(p_sta && !p_info->sta_connected)
    {
        p_info->sta_connected = 1;
        memcpy(p_info->sta_mac, p_sta->mac, sizeof(p_info->sta_mac));
        ESP_LOGD(WIFI_AP_TAG, "[STA connected] MAC:"MACSTR, MAC2STR(p_info->sta_mac));

        return RET_OK;
    }

    return RET_FAILED;
}

error_t wifi_ap_sta_disconnected_event(wifi_event_ap_staconnected_t* p_sta)
{
    wifi_ap_connected_sta_t* p_info = &wifi_ap_ctrl.sta_info;

    if(p_sta && p_info->sta_connected)
    {
        p_info->sta_connected = 0;
        ESP_LOGD(WIFI_AP_TAG, "[STA disconnected] MAC:"MACSTR, MAC2STR(p_info->sta_mac));
        memset(p_info->sta_mac, 0, sizeof(p_info->sta_mac));

        /* TODO: Handle station disconnection */

        return RET_OK;
    }

    return RET_FAILED;
}

error_t wifi_ap_init(void)
{
    memset(&wifi_ap_desc, 0, sizeof(wifi_ap_desc_t));
    memset(&wifi_ap_ctrl, 0, sizeof(wifi_ap_ctrl_t));

    #if WIFI_AP_NAME_AUTOGEN

    #else
    memcpy(wifi_ap_desc.ap_ssid, WIFI_AP_NAME, sizeof(WIFI_AP_NAME));
    wifi_ap_desc.ap_ssid_len = sizeof(WIFI_AP_NAME);
    #endif

    #if WIFI_AP_PASSPHRASE_AUTOGEN

    #else
    memcpy(wifi_ap_desc.ap_passphrase, WIFI_AP_PASSPHRASE, sizeof(WIFI_AP_PASSPHRASE));
    wifi_ap_desc.ap_passphrase_len = sizeof(WIFI_AP_PASSPHRASE);
    #endif

    wifi_ap_ctrl.ap_state = WIFI_AP_STATE_INIT;

    ESP_LOGD(WIFI_AP_TAG, "WIFI AP init done");

    return RET_OK;
}

error_t wifi_ap_start(void)
{
    error_t l_ret = RET_FAILED;
    wifi_config_t wifi_ap_config;

    if(wifi_ap_ctrl.ap_state == WIFI_AP_STATE_INIT)
    {
        memcpy(wifi_ap_config.ap.ssid, wifi_ap_desc.ap_ssid, wifi_ap_desc.ap_ssid_len);
        memcpy(wifi_ap_config.ap.password, wifi_ap_desc.ap_passphrase, 
                                                            wifi_ap_desc.ap_passphrase_len);
        wifi_ap_config.ap.ssid_len = 0;
        wifi_ap_config.ap.channel = 0;
        wifi_ap_config.ap.authmode = WIFI_AP_AUTHMODE;
        wifi_ap_config.ap.ssid_hidden = WIFI_AP_SSID_HIDDEN;
        wifi_ap_config.ap.max_connection = 1;

        if(esp_wifi_set_mode(WIFI_MODE_AP) != ESP_OK)
        {
            WIFI_AP_LOGE("Cannot set AP mode");
            return l_ret;
        }

        if(esp_wifi_set_config(WIFI_IF_AP, &wifi_ap_config) != ESP_OK)
        {
            WIFI_AP_LOGE("Cannot set AP configuration");
            return l_ret;
        }
        
        if(esp_wifi_start() != ESP_OK)
        {
            WIFI_AP_LOGE("Cannot start WIFI AP");
            return l_ret;
        }

        l_ret = RET_OK;
    }

    return l_ret;
}

error_t wifi_ap_prov_start(void)
{
    wifi_ap_config_desc_t* p_desc;
    protocomm_httpd_config_t httpd_config = {
        .ext_handle_provided = 0,
        .data = {
            .config = PROTOCOMM_HTTPD_DEFAULT_CONFIG()
        }
    };
    error_t l_ret = RET_FAILED;

    wifi_ap_ctrl.p_protocomm = protocomm_new();
    if(wifi_ap_ctrl.p_protocomm)
    {
        if(protocomm_httpd_start(wifi_ap_ctrl.p_protocomm, &httpd_config) != ESP_OK)
        {
            WIFI_AP_LOGE("Cannot start HTTP daemon");

            return l_ret;
        }

        if(protocomm_set_security(wifi_ap_ctrl.p_protocomm, "security_endpoint", 
                                                    &protocomm_security0, NULL) != ESP_OK)
        {
            WIFI_AP_LOGE("Cannot set Security 0");

            return l_ret;
        }

        for(uint8_t i = 0; i < WIFI_AP_CONFIG_DESC_SIZE; i++)
        {
            p_desc = &wifi_config_desc[i];
            if(protocomm_add_endpoint(wifi_ap_ctrl.p_protocomm, p_desc->endpoint, 
                                            (protocomm_req_handler_t) p_desc->handler, 
                                            p_desc->pdata) != ESP_OK)
            {
                WIFI_AP_LOGE(p_desc->endpoint);

                return l_ret;
            }                                            
        }

        l_ret = RET_OK;
    }

    return l_ret;
}
