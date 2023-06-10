#include "wifi_prov_handlers.h"

#include "wifi_component_private.h"
#include "wifi_config.pb-c.h"

#include "esp_err.h"
#include "esp_log.h"

#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>

#define WIFI_PROV_TAG            "WIFI_PROV"

#if CONFIG_WIFI_COMPONENT_LOGE_ENABLED
#define WIFI_PROV_LOGE_FORMAT        "[LINE:%d] [%s]"
#define WIFI_PROV_LOGE(__msg)        ESP_LOGE(WIFI_PROV_TAG, WIFI_PROV_LOGE_FORMAT,\
                                                                         __LINE__, __msg)
#else
#define WIFI_PROV_LOGE(_msg)
#endif

#define WIFI_CONFIG_RESP_OK        "WIFI CONFIG OK!"
#define WIFI_CONFIG_RESP_FAILED    "WIFI CONFIG FAILED!"

error_t wifi_prov_prepare_status_resp(uint8_t** outbuf, ssize_t* outlen, 
                                                                StatusRespType status)
{
    StatusResp resp = STATUS_RESP__INIT;
    size_t resp_size;
    error_t l_ret;

    l_ret = RET_FAILED;

    if(outbuf && outlen)
    {
        resp.status = status;
        resp_size = status_resp__get_packed_size(&resp);
        ESP_LOGD(WIFI_PROV_TAG, "Resp. size = %d\n", resp_size);
        *outbuf = (uint8_t*) malloc(resp_size);
        
        if(*outbuf)
        {
            *outlen = resp_size;
            status_resp__pack(&resp, *outbuf);
            l_ret = RET_OK;
        }
        else
        {
            *outlen = 0;
            WIFI_PROV_LOGE("Cannot allocate memory for response");
        }
    }

    return l_ret;
}

error_t wifi_config_prepare_get_sta_status_resp(uint8_t** outbuf, ssize_t* outlen)
{
    WifiConfigGetStatusResp resp = WIFI_CONFIG_GET_STATUS_RESP__INIT;
    wifi_sta_status_t sta_status;
    size_t resp_size;
    error_t l_ret;

    sta_status = WIFI_STA_STATUS_INVALID;
    l_ret = RET_FAILED;

    if(outbuf && outlen)
    {
        if(wifi_component_get_sta_status(&sta_status) == RET_OK)
        {
            resp.status = STATUS_RESP_TYPE__StatusRespOk;

            switch(sta_status)
            {
                case WIFI_STA_STATUS_OFFLINE:
                    resp.sta_status = WIFI_CONFIG_GET_STATUS_TYPE__GetStatusTypeOffline;
                    ESP_LOGD(WIFI_PROV_TAG, "Sta. status = Offline");
                    break;
                case WIFI_STA_STATUS_ASSOCIATED:
                    resp.sta_status = 
                                WIFI_CONFIG_GET_STATUS_TYPE__GetStatusTypeAssociated;
                    ESP_LOGD(WIFI_PROV_TAG, "Sta. status = Associated");
                    break;
                case WIFI_STA_STATUS_GOT_IP:
                    resp.sta_status = WIFI_CONFIG_GET_STATUS_TYPE__GetStatusTypeGotIP;
                    ESP_LOGD(WIFI_PROV_TAG, "Sta. status = Got IP");
                    break;
                case WIFI_STA_STATUS_ONLINE:
                    resp.sta_status = WIFI_CONFIG_GET_STATUS_TYPE__GetStatusTypeOnline;
                    ESP_LOGD(WIFI_PROV_TAG, "Sta. status = Online");
                    break;
                default:
                    resp.status = STATUS_RESP_TYPE__StatusRespFailed;
                    resp.sta_status = WIFI_CONFIG_GET_STATUS_TYPE__GetStatusTypeNone;
                    WIFI_PROV_LOGE("Sta. state is invalid");
                    break;
            }
        }
        else
        {
            resp.status = STATUS_RESP_TYPE__StatusRespFailed;
            resp.sta_status = WIFI_CONFIG_GET_STATUS_TYPE__GetStatusTypeNone;
            WIFI_PROV_LOGE("Couldn't obtain station status");
        }

        resp_size = wifi_config_get_status_resp__get_packed_size(&resp);
        ESP_LOGD(WIFI_PROV_TAG, "Resp. size = %d\n", resp_size);

        *outbuf = (uint8_t*) malloc(resp_size);
        if(*outbuf)
        {
            wifi_config_get_status_resp__pack(&resp, *outbuf);
            *outlen = resp_size;
            l_ret = RET_OK;
        }
        else
        {
            *outlen = 0;
            WIFI_PROV_LOGE("Cannot allocate memory for response");
        }
    }

    return l_ret;
}

esp_err_t wifi_config_cmd_req_handler(uint32_t session_id,
                                                    const uint8_t* inbuf, ssize_t inlen,
                                                    uint8_t** outbuf, ssize_t* outlen,
                                                    void* pdata)
{
    WifiConfigCmdReq* p_wifi_cmd_req;
    StatusRespType l_status;
    uint8_t resp_sent;

    (void) session_id;
    l_status = STATUS_RESP_TYPE__StatusRespFailed;
    resp_sent = 0;

    if(inbuf && (inlen > 0))
    {
        p_wifi_cmd_req = wifi_config_cmd_req__unpack(NULL, inlen, inbuf);
    }
    else
    {
        p_wifi_cmd_req = NULL;
        WIFI_PROV_LOGE("No input data");
    }

    if(p_wifi_cmd_req)
    {
        switch(p_wifi_cmd_req->cmd)
        {
            case WIFI_CONFIG_CMD_TYPE__CmdTypeApplyConfig:
                if(wifi_component_apply_config() == RET_OK)
                {
                    l_status = STATUS_RESP_TYPE__StatusRespOk;
                }
            break;
            case WIFI_CONFIG_CMD_TYPE__CmdTypeResetConfig:
                if(wifi_component_reset_config() == RET_OK)
                {
                    l_status = STATUS_RESP_TYPE__StatusRespOk;
                }
            break;
            case WIFI_CONFIG_CMD_TYPE__CmdTypeGetStatus:
                if(wifi_config_prepare_get_sta_status_resp(outbuf, outlen) == RET_OK)
                {
                    resp_sent = 1;
                }
            break;
            default:;
        }
    }

    if(p_wifi_cmd_req)
    {
        wifi_config_cmd_req__free_unpacked(p_wifi_cmd_req, NULL);
    }

    if(!resp_sent && wifi_prov_prepare_status_resp(outbuf, outlen, l_status) != RET_OK)
    {
        return ESP_FAIL;
    }

    return ESP_OK;
}

esp_err_t wifi_config_ap_set_info_req_handler(uint32_t session_id,
                                                        const uint8_t* inbuf, ssize_t inlen,
                                                        uint8_t** outbuf, ssize_t* outlen,
                                                        void* pdata)
{
    WifiConfigApSetInfoReq* p_wifi_ap_info;
    wifi_ap_desc_t ap_desc; 
    uint16_t len;
    StatusRespType l_status;

    (void) session_id;
    l_status = STATUS_RESP_TYPE__StatusRespFailed;

    if(inbuf && (inlen > 0))
    {
        p_wifi_ap_info = wifi_config_ap_set_info_req__unpack(NULL, inlen, inbuf);
    }
    else
    {
        p_wifi_ap_info = NULL;
        WIFI_PROV_LOGE("No input data");
    }

    if(p_wifi_ap_info)
    {
        len = strlen(p_wifi_ap_info->ssid);
        ESP_LOGD(WIFI_PROV_TAG, "SSID length: %d\r\n", len);

        if(wifi_ap_set_ssid(&ap_desc, p_wifi_ap_info->ssid, len + 1) != RET_OK)
        {
            WIFI_PROV_LOGE("Failed to copy SSID");
            goto wifi_config_ap_end;
        }

        len = strlen(p_wifi_ap_info->passphrase);
        ESP_LOGD(WIFI_PROV_TAG, "Passphrase length: %d\r\n", len);
        
        if(wifi_ap_set_passphrase(&ap_desc, p_wifi_ap_info->passphrase, len + 1) != RET_OK)
        {
            WIFI_PROV_LOGE("Failed to copy passphrase");
            goto wifi_config_ap_end;
        }
        
        ESP_LOGD(WIFI_PROV_TAG, "\n\rSSID: %s\n\rPassphrase: %s\n\r", 
                                        ap_desc.ap_ssid, ap_desc.ap_passphrase);
        
        memset(ap_desc.ap_bssid, 0, sizeof(ap_desc.ap_bssid));
        if(wifi_component_set_target_ap(&ap_desc) == RET_OK)
        {
            l_status = STATUS_RESP_TYPE__StatusRespOk;
        }
    }

wifi_config_ap_end:

    if(p_wifi_ap_info)
    {
        wifi_config_ap_set_info_req__free_unpacked(p_wifi_ap_info, NULL);
    }

    if(wifi_prov_prepare_status_resp(outbuf, outlen, l_status) != RET_OK)
    {
        WIFI_PROV_LOGE("Couldn't prepare response");   
        return ESP_FAIL;
    }

    return ESP_OK;
}