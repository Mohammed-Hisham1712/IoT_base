#ifndef __WIFI_AP_PRIVATE_H__

#define __WIFI_AP_PRIVATE_H__

#include "wifi_ap_public.h"
#include "wifi_config_private.h"

#include "esp_wifi_types.h"
#include "protocomm.h"

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

typedef struct 
{
    const char* endpoint;
    wifi_config_endpoint_handler_t handler;
    void* pdata;
} wifi_ap_config_desc_t;

typedef struct
{
    uint8_t sta_connected;  /* 1: Station connected, 0: No stations connected */
    uint8_t sta_mac[6];     /* MAC address of station, AA:BB:CC:DD:EE:FF */
} wifi_ap_connected_sta_t;


typedef struct
{
    wifi_ap_connected_sta_t sta_info;
    wifi_ap_state_t ap_state;
    protocomm_t* p_protocomm;
} wifi_ap_ctrl_t;

error_t wifi_ap_init(void);
error_t wifi_ap_start(void);
error_t wifi_ap_prov_start(void);

/* WIFI AP Callback functions */

error_t wifi_ap_started_event(void);
error_t wifi_ap_stopped_event(void);
error_t wifi_ap_sta_connected_event(wifi_event_ap_staconnected_t* p_sta);
error_t wifi_ap_sta_disconnected_event(wifi_event_ap_staconnected_t* p_sta);

#endif