#ifndef __WIFI_STA_PUBLIC_H__

#define __WIFI_STA_PUBLIC_H__

#include "wifi_ap_public.h"
#include "appl_config.h"
#include "types.h"

#include "esp_wifi_types.h"
#include "tcpip_adapter.h"
#include "lwip/inet.h"

#ifdef  CONFIG_WIFI_STA_SCAN_LENGTH
#define WIFI_STA_SCAN_LENGTH    CONFIG_WIFI_STA_SCAN_LENGTH
#else
#define WIFI_STA_SCAN_LENGTH    20
#endif

typedef enum
{
    WIFI_STA_STATE_NONE = 0,
    WIFI_STA_STATE_INIT,
    WIFI_STA_STATE_STARTED,
    WIFI_STA_STATE_CONNECT,
    WIFI_STA_STATE_DISCONNECT,
    WIFI_STA_STATE_STOPPED,
    WIFI_STA_STATE_MAX
} wifi_sta_state_t;

typedef enum
{
    WIFI_STA_PHASE_WAITING,
    WIFI_STA_PHASE_IN_PROGRESS,
    WIFI_STA_PHASE_DONE,
    WIFI_STA_PHASE_INVALID
} wifi_sta_phase_t;

typedef enum
{
    WIFI_STA_STATUS_OFFLINE,
    WIFI_STA_STATUS_ASSOCIATED,
    WIFI_STA_STATUS_GOT_IP,
    WIFI_STA_STATUS_ONLINE,
    WIFI_STA_STATUS_INVALID
} wifi_sta_status_t;

typedef enum
{
    WIFI_STA_SCAN_ALL_APS,              /* All APs on all channels */
    WIFI_STA_SCAN_SPECIFIC_SSID_FAST,   /* All APs with ESSID, stop when first AP is found */
    WIFI_STA_SCAN_SPECIFIC_SSID_ALL,    /* All APs with ESSID on all channels */
    WIFI_STA_SCAN_SPECIFIC_AP,          /* AP's ESSID and BSSID are specified */
    WIFI_STA_SCAN_TYPE_INV              /* Invalid scan type */
} wifi_sta_scan_type_t;

typedef enum
{
    WIFI_STA_SCAN_STATE_INVALID,
    WIFI_STA_SCAN_STATE_ONGOING,
    WIFI_STA_SCAN_STATE_DONE,
    WIFI_STA_SCAN_STATE_FAILED
} wifi_sta_scan_state_t;

typedef struct
{
    char ssid[WIFI_AP_SSID_MAX_LENGTH];
    uint8_t bssid[6];
    uint8_t channel;
    uint8_t rssi;
    wifi_auth_mode_t authmode;
    wifi_cipher_type_t cipher;
} wifi_sta_scan_entry_t;

typedef struct
{
    wifi_sta_scan_entry_t entries[WIFI_STA_SCAN_LENGTH];
    wifi_sta_scan_type_t type;
    wifi_sta_scan_state_t state;
    uint16_t n_entries;
} wifi_sta_scan_t;

typedef struct
{
    struct in_addr ip;      /* Same struct in_addr as used with sockets API */
    struct in_addr gw;
    struct in_addr netmask;
} wifi_sta_ip_info_t;

typedef struct
{
    wifi_sta_state_t    state;
    wifi_sta_phase_t    phase;
    wifi_sta_status_t   status;
    wifi_sta_scan_t     last_scan;
    wifi_sta_ip_info_t  ip_info;
    wifi_ap_desc_t      target_ap_desc;
} wifi_sta_ctrl_t;


/**
 * @brief 
 * 
 * @param p_wifi_sta 
 * @param status 
 * @return error_t 
 */
error_t wifi_sta_get_status(wifi_sta_ctrl_t* p_wifi_sta, wifi_sta_status_t* status);

/**
 * @brief 
 * 
 * @return error_t 
 */
error_t wifi_sta_run(wifi_sta_ctrl_t* p_wifi_sta);

#endif