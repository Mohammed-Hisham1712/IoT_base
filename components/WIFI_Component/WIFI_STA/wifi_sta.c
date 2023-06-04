#include "wifi_sta_private.h"
#include "wifi_diagnostics.h"
#include "wifi_component_public.h"
#include "timer.h"
#include "types.h"

#include "esp_wifi_types.h"
#include "esp_wifi.h"
#include "esp_err.h"
#include "esp_log.h"
#include "rom/ets_sys.h"
#include "esp_event.h"
#include "freertos/task.h"

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

ESP_EVENT_DECLARE_BASE(WIFI_COMP_EVENT);

error_t wifi_sta_get_status(wifi_sta_ctrl_t* p_wifi_sta, wifi_sta_status_t* status)
{
    if(!p_wifi_sta || !status)
    {
        return RET_FAILED;
    }

    if(p_wifi_sta->state <= WIFI_STA_STATE_INIT || 
                            p_wifi_sta->state >= WIFI_STA_STATE_MAX)
    {
        return RET_FAILED;
    }

    *status = p_wifi_sta->status;

    return RET_OK;
}

error_t wifi_sta_scan_done_event(wifi_sta_ctrl_t* p_wifi_sta, 
                                    wifi_event_sta_scan_done_t* p_scan)
{
    wifi_ap_record_t ap_records[WIFI_STA_SCAN_LENGTH];
    wifi_sta_scan_t* p_sta_scan;
    wifi_sta_scan_entry_t* p_entry;
    uint8_t ssid_len;

    if(!p_scan || !p_wifi_sta)
    {
        return RET_FAILED;
    }

    p_sta_scan = &p_wifi_sta->last_scan;

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

error_t wifi_sta_started_event(wifi_sta_ctrl_t* p_wifi_sta)
{
    if(p_wifi_sta)
    {
        p_wifi_sta->state = WIFI_STA_STATE_STARTED;
        p_wifi_sta->phase = WIFI_STA_PHASE_DONE;
        p_wifi_sta->status = WIFI_STA_STATUS_OFFLINE;

        ESP_LOGD(WIFI_STA_TAG, "Station started");

        return RET_OK;
    }

    return RET_FAILED;
}

error_t wifi_sta_connected_event(wifi_sta_ctrl_t* p_wifi_sta, 
                                        wifi_event_sta_connected_t* p_ap)
{
    if(p_wifi_sta)
    {
        if(p_wifi_sta->state == WIFI_STA_STATE_CONNECT)
        {
            p_wifi_sta->phase = WIFI_STA_PHASE_DONE;
            p_wifi_sta->status = WIFI_STA_STATUS_ASSOCIATED;

            wifi_ap_set_bssid(&p_wifi_sta->target_ap_desc, p_ap->bssid);
            ESP_LOGD(WIFI_STA_TAG, "Station associated with AP["MACSTR"]", 
                                    MAC2STR(p_wifi_sta->target_ap_desc.ap_bssid));

            esp_event_post(WIFI_COMP_EVENT, WIFI_COMP_EVENT_STA_CONNECTED, 
                                                            NULL, 0, portMAX_DELAY);

            return RET_OK;
        }
    }

    return RET_FAILED;
}

error_t wifi_sta_disconnected_event(wifi_sta_ctrl_t* p_wifi_sta, 
                                        wifi_event_sta_disconnected_t* p_disc_event)
{
    if(!p_wifi_sta)
    {
        return RET_FAILED;
    }

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

        p_wifi_sta->state = WIFI_STA_STATE_DISCONNECT;
        p_wifi_sta->status = WIFI_STA_STATUS_OFFLINE;

        esp_event_post(WIFI_COMP_EVENT, WIFI_COMP_EVENT_STA_DISCONNECTED, 
                                                            NULL, 0, portMAX_DELAY);
        return RET_OK;
    }

    return RET_FAILED;
}

error_t wifi_sta_got_ip_event(wifi_sta_ctrl_t* p_wifi_sta, ip_event_got_ip_t* p_ip)
{
    char ipstr[16];

    if(p_wifi_sta)
    {
        if(p_wifi_sta->state == WIFI_STA_STATE_CONNECT)
        {
            p_wifi_sta->status = WIFI_STA_STATUS_GOT_IP;

            memcpy(&p_wifi_sta->ip_info.ip.s_addr, &p_ip->ip_info.ip.addr, sizeof(uint32_t));
            memcpy(&p_wifi_sta->ip_info.gw.s_addr, &p_ip->ip_info.gw.addr, sizeof(uint32_t));
            memcpy(&p_wifi_sta->ip_info.netmask.s_addr, &p_ip->ip_info.netmask.addr, 
                                                                            sizeof(uint32_t));
            inet_ntoa_r(p_wifi_sta->ip_info.ip.s_addr, ipstr, sizeof(ipstr));
            ESP_LOGD(WIFI_STA_TAG, "Station got IP: %s", ipstr);
            
            if(p_ip->ip_changed)
            {
                esp_event_post(WIFI_COMP_EVENT, WIFI_COMP_EVENT_STA_IP_CHANGED, 
                                                            NULL, 0, portMAX_DELAY);
            }

            return RET_OK;
        }
    }

    return RET_FAILED;
}

error_t wifi_sta_start_scan(wifi_sta_ctrl_t* p_wifi_sta, 
                                wifi_sta_scan_type_t scan_type, wifi_ap_desc_t* p_scan_target)
{
    wifi_scan_config_t scan_config;

    scan_config.channel = 0;
    scan_config.scan_type = WIFI_SCAN_TYPE_ACTIVE;
    scan_config.scan_time.active.min = 0;
    scan_config.scan_time.active.max = 0;

    if(!p_wifi_sta || ((scan_type != WIFI_STA_SCAN_ALL_APS) && (p_scan_target == NULL)))
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

    p_wifi_sta->last_scan.state = WIFI_STA_SCAN_STATE_ONGOING;

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

error_t wifi_sta_init(wifi_sta_ctrl_t* p_wifi_sta, wifi_ap_desc_t* p_target_ap)
{
    wifi_config_t wifi_sta_config;
    wifi_mode_t mode;
    error_t l_ret;

    l_ret = RET_FAILED;

    if(esp_wifi_get_mode(&mode) != ESP_OK)
    {
        return l_ret;
    }

    if(p_wifi_sta && p_target_ap && (mode == WIFI_MODE_STA || mode == WIFI_MODE_APSTA))
    {
        memset(p_wifi_sta, 0, sizeof(wifi_sta_ctrl_t));

        p_wifi_sta->state = WIFI_STA_STATE_INIT;
        p_wifi_sta->status = WIFI_STA_STATUS_OFFLINE;

        memcpy(&p_wifi_sta->target_ap_desc, p_target_ap, sizeof(wifi_ap_desc_t));

        memset(&wifi_sta_config, 0, sizeof(wifi_config_t));
        memcpy(wifi_sta_config.sta.ssid, p_target_ap->ap_ssid, p_target_ap->ap_ssid_len);
        memcpy(wifi_sta_config.sta.password, p_target_ap->ap_passphrase, 
                                                    p_target_ap->ap_passphrase_len);

        wifi_sta_config.sta.scan_method = WIFI_ALL_CHANNEL_SCAN;    
        wifi_sta_config.sta.bssid_set = 0;
        wifi_sta_config.sta.channel = 0;
        wifi_sta_config.sta.sort_method = WIFI_CONNECT_AP_BY_SIGNAL;
        wifi_sta_config.sta.threshold.rssi = 0;
        wifi_sta_config.sta.threshold.authmode = WIFI_AUTH_WPA2_PSK;

        if(esp_wifi_set_config(WIFI_IF_STA, &wifi_sta_config) != ESP_OK)
        {
            WIFI_STA_LOGE("Cannot set sta configuration");
            return RET_FAILED;
        }
        
        p_wifi_sta->phase = WIFI_STA_PHASE_DONE;
        l_ret = RET_OK;

        ESP_LOGD(WIFI_STA_TAG, "Init done");
        wifi_diagnostics_init();
    }

    return RET_FAILED;
}

error_t wifi_sta_deinit(wifi_sta_ctrl_t* p_wifi_sta)
{
    if(p_wifi_sta)
    {
        memset(p_wifi_sta, 0, sizeof(wifi_sta_ctrl_t));
        
        return RET_OK;
    }

    return RET_FAILED;
}

error_t wifi_sta_run(wifi_sta_ctrl_t* p_wifi_sta)
{
    wifi_ap_desc_t* p_target_ap;


    if(p_wifi_sta)
    {
        p_target_ap = &p_wifi_sta->target_ap_desc;
    }
    else
    {
        return RET_FAILED;
    }

    switch(p_wifi_sta->state)
    {
        case WIFI_STA_STATE_INIT:
            break;
        case WIFI_STA_STATE_STARTED:
            if(p_wifi_sta->phase == WIFI_STA_PHASE_DONE)
            {
                p_wifi_sta->state = WIFI_STA_STATE_CONNECT;
                p_wifi_sta->phase = WIFI_STA_PHASE_IN_PROGRESS;

                if(esp_wifi_connect() != ESP_OK)
                {
                    return RET_FAILED;
                }
            }
            else if(p_wifi_sta->phase == WIFI_STA_PHASE_IN_PROGRESS)
            {

            }
            else
            {
                return RET_FAILED;
            }
            break;
        case WIFI_STA_STATE_CONNECT:
            if(p_wifi_sta->phase == WIFI_STA_PHASE_DONE)
            {
                if(p_wifi_sta->status == WIFI_STA_STATUS_GOT_IP)
                {
                    wifi_diagnostics_run();
                }
            }
            else if(p_wifi_sta->phase == WIFI_STA_PHASE_IN_PROGRESS)
            {

            }
            else
            {
                return RET_FAILED;
            }
            break;
        case WIFI_STA_STATE_DISCONNECT:
            p_wifi_sta->state = WIFI_STA_STATE_CONNECT;
            p_wifi_sta->phase = WIFI_STA_PHASE_IN_PROGRESS;

            ESP_LOGD(WIFI_STA_TAG, "Reconnecting....");

            if(esp_wifi_connect() != ESP_OK)
            {
                return RET_FAILED;
            }
            break;
        default:
            return RET_FAILED;
    }

    return RET_OK;
}
