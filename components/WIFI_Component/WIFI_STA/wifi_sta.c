#include "wifi_sta_private.h"
#include "types.h"

#include "esp_wifi_types.h"
#include "esp_wifi.h"
#include "esp_err.h"
#include "esp_log.h"
#include "rom/ets_sys.h"

#include <stdint.h>
#include <stddef.h>
#include <string.h>

#define WIFI_STA_TAG                "WIFI_STA"

#if CONFIG_WIFI_COMPONENT_LOGE_ENABLED
#define WIFI_STA_LOGE_FORMAT        "[LINE:%d] [%s]"
#define WIFI_STA_LOGE(__msg)        ESP_LOGE(WIFI_STA_TAG, WIFI_STA_LOGE_FORMAT, \
                                                                        __LINE__, __msg)
#else
#define WIFI_STA_LOGE(_msg)
#endif

static wifi_sta_ctrl_t wifi_sta_ctrl;
static wifi_sta_param_t wifi_sta_param;

error_t wifi_sta_scan_done_event(wifi_event_sta_scan_done_t* p_scan)
{
    wifi_ap_record_t ap_records[WIFI_STA_SCAN_LENGTH];
    wifi_sta_scan_t* p_sta_scan = &wifi_sta_ctrl.last_scan;
    wifi_sta_scan_entry_t* p_entry;
    uint8_t ssid_len;

    if(!p_scan)
    {
        return RET_FAILED;
    }

    if(p_scan->status == 0)
    {
        ESP_LOGD(WIFI_STA_TAG, "Scan done!");

        esp_wifi_scan_get_ap_num(&p_sta_scan->n_entries);
        if(p_sta_scan->n_entries > WIFI_STA_SCAN_LENGTH)
        {
            p_sta_scan->n_entries = WIFI_STA_SCAN_LENGTH;
            ESP_LOGD(WIFI_STA_TAG, "Not enough space for all scan entries");
        }

        if(esp_wifi_scan_get_ap_records(&p_sta_scan->n_entries, ap_records) != ESP_OK)
        {
            p_sta_scan->state = WIFI_STA_SCAN_STATE_FAILED;
            WIFI_STA_LOGE("Cannot retrieve scan record");
            return RET_FAILED;
        }
        
        ESP_LOGD(WIFI_STA_TAG, "Scan found %d APs", p_sta_scan->n_entries);

        for(uint16_t i = 0; i < p_sta_scan->n_entries; i++)
        {
            p_entry = &p_sta_scan->entries[i];

            ssid_len = strlen((const char*) ap_records[i].ssid) + 1;  /* Length including null char */
            ssid_len = (ssid_len > WIFI_AP_SSID_MAX_LENGTH) ? WIFI_AP_SSID_MAX_LENGTH : ssid_len;
            memcpy(p_entry->ssid, ap_records[i].ssid, ssid_len);
            p_entry->ssid[ssid_len - 1] = '\0';

            memcpy(p_entry->bssid, ap_records[i].bssid, sizeof(p_entry->bssid));

            p_entry->channel = ap_records[i].primary;
            p_entry->rssi = ap_records[i].rssi;
            p_entry->authmode = ap_records[i].authmode;
            p_entry->cipher = ap_records[i].pairwise_cipher;
        }

        p_sta_scan->state = WIFI_STA_SCAN_STATE_DONE;

        return RET_OK;
    }

    p_sta_scan->state = WIFI_STA_SCAN_STATE_FAILED;

    return RET_FAILED;
}

error_t wifi_sta_started_event(void)
{
    if(wifi_sta_ctrl.state == WIFI_STA_STATE_INIT)
    {
        wifi_sta_ctrl.state = WIFI_STA_STATE_STARTED;

        ESP_LOGD(WIFI_STA_TAG, "Station started");

        return RET_OK;
    }

    return RET_FAILED;
}

error_t wifi_sta_connected_event(wifi_event_sta_connected_t* p_ap)
{
    if(wifi_sta_ctrl.state == WIFI_STA_STATE_CONNECTING)
    {
        wifi_sta_ctrl.state = WIFI_STA_STATE_ASSOCIATED;

        wifi_ap_set_bssid(&wifi_sta_param.target_ap_desc, p_ap->bssid);
        ESP_LOGD(WIFI_STA_TAG, "Station associated with AP["MACSTR"]", 
                                        MAC2STR(wifi_sta_param.target_ap_desc.ap_bssid));

        return RET_OK;
    }

    return RET_FAILED;
}

error_t wifi_sta_disconnected_event(wifi_event_sta_disconnected_t* p_disc_event)
{
    if(p_disc_event)
    {
        switch(p_disc_event->reason)
        {
            case WIFI_REASON_NO_AP_FOUND:
                ESP_LOGD(WIFI_STA_TAG, "DISCONNECTED: Cannot find AP");
                break;
            case WIFI_REASON_AUTH_EXPIRE:
                ESP_LOGD(WIFI_STA_TAG, "DISCONNECTED: Auth. expired");
                break;
            case WIFI_REASON_AUTH_FAIL:
                ESP_LOGD(WIFI_STA_TAG, "DISCONNECTED: Auth. failed");
                break;
            case WIFI_REASON_AUTH_LEAVE:
                ESP_LOGD(WIFI_STA_TAG, "DISCONNECTED: Auth. leave");
                break;
            case WIFI_REASON_NOT_AUTHED:
                ESP_LOGD(WIFI_STA_TAG, "DISCONNECTED: Class 2 not authenticated");
                break;
            case WIFI_REASON_ASSOC_EXPIRE:
                ESP_LOGD(WIFI_STA_TAG, "DISCONNECTED: Assoc. expired");
                break;
            case WIFI_REASON_ASSOC_FAIL:
                ESP_LOGD(WIFI_STA_TAG, "DISCONNECTED: Assoc. failed");
                break;
            case WIFI_REASON_ASSOC_TOOMANY:
                ESP_LOGD(WIFI_STA_TAG, "DISCONNECTED: Assoc. too many");
                break;
            case WIFI_REASON_NOT_ASSOCED:
                ESP_LOGD(WIFI_STA_TAG, "DISCONNECTED: Class 3 not associated");
                break;
            case WIFI_REASON_HANDSHAKE_TIMEOUT:
                ESP_LOGD(WIFI_STA_TAG, "DISCONNECTED: EOP handshake timeout");
                break;
            case WIFI_REASON_MIC_FAILURE:
                ESP_LOGD(WIFI_STA_TAG, "DISCONNECTED: MIC failure");
                break;
            case WIFI_REASON_IE_IN_4WAY_DIFFERS:
                ESP_LOGD(WIFI_STA_TAG, "DISCONNECTED: EOP handshake failed");
                break;
            case WIFI_REASON_PAIRWISE_CIPHER_INVALID:
                ESP_LOGD(WIFI_STA_TAG, "DISCONNECTED: Pairwise cipher invalid");
                break;
            case WIFI_REASON_BEACON_TIMEOUT:
                ESP_LOGD(WIFI_STA_TAG, "DISCONNECTED: Beacon timeout");
                break;
            default:
                break;
        }

        wifi_sta_ctrl.state = WIFI_STA_STATE_DISCONNECTED;

        return RET_OK;
    }

    return RET_FAILED;
}

error_t wifi_sta_got_ip_event(ip_event_got_ip_t* p_ip)
{
    char ipstr[16];

    if(wifi_sta_ctrl.state == WIFI_STA_STATE_ASSOCIATED)
    {
        wifi_sta_ctrl.state = WIFI_STA_STATE_CONNECTED;

        memcpy(&wifi_sta_ctrl.ip_info.ip.s_addr, &p_ip->ip_info.ip.addr, sizeof(uint32_t));
        memcpy(&wifi_sta_ctrl.ip_info.gw.s_addr, &p_ip->ip_info.gw.addr, sizeof(uint32_t));
        memcpy(&wifi_sta_ctrl.ip_info.netmask.s_addr, &p_ip->ip_info.netmask.addr, 
                                                                        sizeof(uint32_t));
        inet_ntoa_r(wifi_sta_ctrl.ip_info.ip.s_addr, ipstr, sizeof(ipstr));
        ESP_LOGD(WIFI_STA_TAG, "Station got IP: %s", ipstr);

        return RET_OK;
    }

    return RET_FAILED;
}

error_t wifi_sta_start_scan(wifi_sta_scan_type_t scan_type, wifi_ap_desc_t* p_scan_target)
{
    wifi_scan_config_t scan_config;

    scan_config.channel = 0;
    scan_config.scan_type = WIFI_SCAN_TYPE_ACTIVE;
    scan_config.scan_time.active.min = 0;
    scan_config.scan_time.active.max = 0;

    if((scan_type != WIFI_STA_SCAN_ALL_APS) && (p_scan_target == NULL))
    {
        return RET_FAILED;
    }

    switch(scan_type)
    {
        case WIFI_STA_SCAN_ALL_APS:;
            scan_config.ssid = NULL;
            scan_config.bssid = NULL;
            scan_config.show_hidden = 0;
            break;
        case WIFI_STA_SCAN_SPECIFIC_SSID_ALL:;
            scan_config.ssid = (uint8_t*) p_scan_target->ap_ssid;
            scan_config.bssid = NULL;
            scan_config.show_hidden = 1;
            break;
        case WIFI_STA_SCAN_SPECIFIC_SSID_FAST:  /* Not supported in ESP8266 */
            break;
        case WIFI_STA_SCAN_SPECIFIC_AP:;
            scan_config.ssid = (uint8_t*) p_scan_target->ap_ssid;
            scan_config.bssid = p_scan_target->ap_bssid;
            scan_config.show_hidden = 1;
            break;
        default:
            return RET_FAILED;
    }

    if(esp_wifi_scan_start(&scan_config, 0) != ESP_OK)
    {
        WIFI_STA_LOGE("Cannot start scan");
        return RET_FAILED;
    }

    wifi_sta_ctrl.last_scan.state = WIFI_STA_SCAN_STATE_ONGOING;

    return RET_OK;
}

error_t wifi_sta_print_scan(const wifi_sta_scan_t* p_scan)
{
    const wifi_sta_scan_entry_t* p_entry;

    if(p_scan && (p_scan->state == WIFI_STA_SCAN_STATE_DONE))
    {
        for(uint16_t i = 0; i < p_scan->n_entries; i++)
        {
            p_entry = &p_scan->entries[i];

            printf("Scan entry: %d\n", i);
            puts("---------------------------");
            printf("ESSID: %s\n", p_entry->ssid);
            printf("BSSID: ["MACSTR"]\n", MAC2STR(p_entry->bssid));
            printf("Channel: %d\n", p_entry->channel);
            printf("RSSI: %d dBm\n", p_entry->rssi);
            printf("Auth. mode: ");

            switch(p_entry->authmode)
            {
                case WIFI_AUTH_OPEN:
                    puts("OPEN");
                    break;
                case WIFI_AUTH_WEP:
                    puts("WEP");
                    break;
                case WIFI_AUTH_WPA_PSK:
                    puts("WPA-PSK");
                    break;
                case WIFI_AUTH_WPA2_PSK:
                    puts("WPA2-PSK");
                    break;
                case WIFI_AUTH_WPA_WPA2_PSK:
                    puts("WPA/WPA2-PSK");
                    break;
                case WIFI_AUTH_WPA2_ENTERPRISE:
                    puts("WPA2-ENTERPRISE");
                    break;
                case WIFI_AUTH_WPA3_PSK:
                    puts("WPA3-PSK");
                    break;
                default:
                    puts("UNKOWN");
                    break;
            }

            printf("Cipher: ");

            switch(p_entry->cipher)
            {
                case WIFI_CIPHER_TYPE_NONE:
                    puts("Unencrypted");
                    break;
                case WIFI_CIPHER_TYPE_WEP40:
                    puts("WEP40");
                    break;
                case WIFI_CIPHER_TYPE_WEP104:
                    puts("WEP104");
                    break;
                case WIFI_CIPHER_TYPE_TKIP:
                    puts("TKIP");
                    break;
                case WIFI_CIPHER_TYPE_CCMP:
                    puts("CCMP");
                    break;
                case WIFI_CIPHER_TYPE_TKIP_CCMP:
                    puts("TKIP-CCMP");
                    break;
                default:
                    puts("UNKOWN");
                    break;
            }
        }

        puts("---------------------------");

        return RET_OK;
    }

    return RET_FAILED;
}

error_t wifi_sta_init(const wifi_ap_desc_t* p_ap_desc)
{
    memset(&wifi_sta_ctrl, 0, sizeof(wifi_sta_ctrl_t));
    memset(&wifi_sta_param, 0, sizeof(wifi_sta_param_t));

    memcpy(&wifi_sta_param.target_ap_desc, p_ap_desc, sizeof(wifi_ap_desc_t));

    wifi_sta_ctrl.state = WIFI_STA_STATE_INIT;

    ESP_LOGD(WIFI_STA_TAG, "Init done");
    
    return RET_OK;
}

error_t wifi_sta_start(void)
{
    wifi_config_t wifi_sta_config;
    wifi_ap_desc_t* p_ap_desc;

    p_ap_desc = &wifi_sta_param.target_ap_desc;

    if(p_ap_desc && (wifi_sta_ctrl.state == WIFI_STA_STATE_INIT))
    {
        memset(&wifi_sta_config, 0, sizeof(wifi_config_t));
        memcpy(wifi_sta_config.sta.ssid, p_ap_desc->ap_ssid, p_ap_desc->ap_ssid_len);
        memcpy(wifi_sta_config.sta.password, p_ap_desc->ap_passphrase, 
                                                    p_ap_desc->ap_passphrase_len);

        wifi_sta_config.sta.scan_method = WIFI_ALL_CHANNEL_SCAN;    
        wifi_sta_config.sta.bssid_set = 0;
        wifi_sta_config.sta.channel = 0;
        wifi_sta_config.sta.sort_method = WIFI_CONNECT_AP_BY_SIGNAL;
        wifi_sta_config.sta.threshold.rssi = 0;
        wifi_sta_config.sta.threshold.authmode = WIFI_AUTH_WPA2_PSK;

        if(esp_wifi_set_mode(WIFI_MODE_STA) != ESP_OK)
        {
            WIFI_STA_LOGE("Cannot set sta mode");
            return RET_FAILED;
        }

        if(esp_wifi_set_config(WIFI_IF_STA, &wifi_sta_config) != ESP_OK)
        {
            WIFI_STA_LOGE("Cannot set sta configuration");
            return RET_FAILED;
        }

        if(esp_wifi_start() != ESP_OK)
        {
            WIFI_STA_LOGE("Cannot start station");
            return RET_FAILED;
        }

        return RET_OK;
    }

    return RET_FAILED;
}

error_t wifi_sta_connect(void)
{
    if(esp_wifi_connect() != ESP_OK)
    {
        return RET_FAILED;
    }

    return RET_OK;
}

error_t wifi_sta_run(void)
{
    switch(wifi_sta_ctrl.state)
    {
        case WIFI_STA_STATE_INIT:
            wifi_sta_start();
            break;
        case WIFI_STA_STATE_STARTED:
            wifi_sta_ctrl.state = WIFI_STA_STATE_CONNECTING;
            wifi_sta_connect();
            break;
        case WIFI_STA_STATE_CONNECTING:
        case WIFI_STA_STATE_ASSOCIATED:
            break;
        case WIFI_STA_STATE_CONNECTED:
            if(wifi_sta_ctrl.last_scan.state == WIFI_STA_SCAN_STATE_INVALID)
            {
                #if 0
                wifi_sta_start_scan(WIFI_STA_SCAN_SPECIFIC_SSID_ALL, 
                                                        &wifi_sta_param.target_ap_desc);
                #endif
            }
            else if(wifi_sta_ctrl.last_scan.state == WIFI_STA_SCAN_STATE_DONE)
            {
                wifi_sta_print_scan(&wifi_sta_ctrl.last_scan);
                wifi_sta_ctrl.last_scan.state = WIFI_STA_SCAN_STATE_INVALID;
            }
            else
            {
                ESP_LOGD(WIFI_STA_TAG, "Scan state is invalid");
            }
            break;
        case WIFI_STA_STATE_DISCONNECTED:
            ESP_LOGD(WIFI_STA_TAG, "Reconnecting....");
            wifi_sta_ctrl.state = WIFI_STA_STATE_CONNECTING;
            wifi_sta_connect();
            break;
        default:
            break;
    }

    return RET_OK;
}