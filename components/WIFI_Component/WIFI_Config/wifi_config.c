#include "wifi_config_private.h"
#include "wifi_config.pb-c.h"

#include "esp_err.h"
#include "esp_log.h"

#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>

#define WIFI_CONFIG_TAG            "WIFI CONFIG"

#ifdef CONFIG_WIFI_COMPONENT_LOGE_ENABLED
#define WIFI_CONFIG_LOGE_FORMAT        "[LINE:%d] [Endpoint: %s] [%s]"
#define WIFI_CONFIG_LOGE(__ep, __msg) \
                    ESP_LOGE(WIFI_CONFIG_TAG, WIFI_CONFIG_LOGE_FORMAT, __LINE__, __ep, __msg)
#else
#define WIFI_CONFIG_LOGE(__ep, __msg)
#endif

#define WIFI_CONFIG_RESP_OK        "WIFI CONFIG OK!"
#define WIFI_CONFIG_RESP_FAILED    "WIFI CONFIG FAILED!"

esp_err_t wifi_config_ap_set_info_req_handler(uint32_t session_id,
                                                        const uint8_t* inbuf, ssize_t inlen,
                                                        uint8_t** outbuf, ssize_t* outlen,
                                                        void* pdata)
{
    WifiConfigApSetInfoReq* p_wifi_ap_info;
    wifi_ap_desc_t ap_desc; 
    char* resp;
    uint16_t resp_len;
    uint16_t len;
    esp_err_t l_ret;

    (void) session_id;
    l_ret = ESP_FAIL;

    ESP_LOGD(WIFI_CONFIG_TAG, "Endpoint: %s", WIFI_CONFIG_AP_INFO_EP);

    if(inbuf && (inlen > 0))
    {
        p_wifi_ap_info = wifi_config_ap_set_info_req__unpack(NULL, inlen, inbuf);
    }
    else
    {
        p_wifi_ap_info = NULL;
        WIFI_CONFIG_LOGE(WIFI_CONFIG_AP_INFO_EP, "No input data");
    }

    if(p_wifi_ap_info && pdata)
    {
        len = strlen(p_wifi_ap_info->ssid);
        ESP_LOGD(WIFI_CONFIG_TAG, "SSID length: %d\r\n", len);

        if(wifi_ap_set_ssid(&ap_desc, p_wifi_ap_info->ssid, len + 1) != RET_OK)
        {
            WIFI_CONFIG_LOGE(WIFI_CONFIG_AP_INFO_EP, "Failed to copy SSID");
            goto wifi_config_ap_end;
        }

        len = strlen(p_wifi_ap_info->passphrase);
        ESP_LOGD(WIFI_CONFIG_TAG, "Passphrase length: %d\r\n", len);
        
        if(wifi_ap_set_passphrase(&ap_desc, p_wifi_ap_info->passphrase, len + 1) != RET_OK)
        {
            WIFI_CONFIG_LOGE(WIFI_CONFIG_AP_INFO_EP, "Failed to copy passphrase");
            goto wifi_config_ap_end;
        }
        
        ESP_LOGD(WIFI_CONFIG_TAG, "\n\rSSID: %s\n\rPassphrase: %s\n\r", 
                                        ap_desc.ap_ssid, ap_desc.ap_passphrase);
        
        l_ret = ESP_OK;
    }

wifi_config_ap_end:

    if(l_ret == ESP_OK)
    {   
        memcpy(pdata, &ap_desc, sizeof(wifi_ap_desc_t));

        if(outbuf && outlen)
        {
            /* Prepare response */
            resp_len = sizeof(WIFI_CONFIG_RESP_OK);
            resp = (char*) malloc(resp_len);    /* Memory freed outside */

            if(resp)
            {
                memcpy(resp, WIFI_CONFIG_RESP_OK, resp_len);
                *outlen = resp_len;
                *outbuf = (uint8_t*) resp;
            }
            else
            {
                *outlen = 0;
                *outbuf = NULL;
                WIFI_CONFIG_LOGE(WIFI_CONFIG_AP_INFO_EP, "Failed to allocate response mem.");
            }
        }
    }
    else
    {
        if(outbuf && outlen)
        {
            /* Prepare response */
            resp_len = sizeof(WIFI_CONFIG_RESP_FAILED);
            resp = (char*) malloc(resp_len);    /* Memory freed outside */

            if(resp)
            {
                memcpy(resp, WIFI_CONFIG_RESP_FAILED, resp_len);
                *outlen = resp_len;
                *outbuf = (uint8_t*) resp;
            }
            else
            {
                *outlen = 0;
                *outbuf = NULL;
                WIFI_CONFIG_LOGE(WIFI_CONFIG_AP_INFO_EP, "Failed to allocate response mem.");
            }
        }
    }

    if(p_wifi_ap_info)
    {
        wifi_config_ap_set_info_req__free_unpacked(p_wifi_ap_info, NULL);
    }

    return l_ret;
}