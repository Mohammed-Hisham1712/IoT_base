#ifndef __WIFI_AP_PRIVATE_H__

#define __WIFI_AP_PRIVATE_H__

#include "wifi_ap_public.h"
#include "appl_config.h"

#define WIFI_AP_AUTHMODE                WIFI_AUTH_WPA2_PSK
#define WIFI_AP_SSID_HIDDEN             CONFIG_WIFI_AP_SSID_HIDDEN

#define WIFI_AP_NAME_AUTOGEN            CONFIG_WIFI_AP_NAME_AUTOGEN

#if WIFI_AP_NAME_AUTOGEN == 0
#define WIFI_AP_NAME                    "ESP_AP"
#endif

#define WIFI_AP_PASSPHRASE_AUTOGEN  CONFIG_WIFI_AP_PASSPHRASE_AUTOGEN

#if WIFI_AP_PASSPHRASE_AUTOGEN == 0
#define WIFI_AP_PASSPHRASE              "12345678"
#endif

error_t wifi_ap_init(wifi_ap_ctrl_t* p_wifi_ap);
error_t wifi_ap_deinit(wifi_ap_ctrl_t* p_wifi_ap);
error_t wifi_ap_run(wifi_ap_ctrl_t* p_wifi_ap);

/* WIFI AP Callback functions */

error_t wifi_ap_started_event(wifi_ap_ctrl_t* p_wifi_ap);
error_t wifi_ap_stopped_event(wifi_ap_ctrl_t* p_wifi_ap);
error_t wifi_ap_sta_connected_event(wifi_ap_ctrl_t* p_wifi_ap, 
                                            wifi_event_ap_staconnected_t* p_sta);
error_t wifi_ap_sta_disconnected_event(wifi_ap_ctrl_t* p_wifi_ap, 
                                            wifi_event_ap_staconnected_t* p_sta);

#endif