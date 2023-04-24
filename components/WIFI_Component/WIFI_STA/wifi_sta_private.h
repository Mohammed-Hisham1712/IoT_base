#ifndef __WIFI_STA_PRIVATE_H__

#define __WIFI_STA_PRIVATE_H__

#include "wifi_sta_public.h"
#include "wifi_ap_public.h"

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
    WIFI_STA_STATE_CONNECTING,
    WIFI_STA_STATE_ASSOCIATED,
    WIFI_STA_STATE_CONNECTED,
    WIFI_STA_STATE_DISCONNECTED,
    WIFI_STA_STATE_STOPPED,
    WIFI_STA_STATE_MAX
} wifi_sta_state_t;

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
    wifi_ap_desc_t target_ap_desc;    
} wifi_sta_param_t;

typedef struct
{
    wifi_sta_state_t state;
    wifi_sta_scan_t last_scan;
    wifi_sta_ip_info_t ip_info;
} wifi_sta_ctrl_t;

/**
 * @brief Handle WIFI scan done event
 * 
 * @param p_scan 
 * @return error_t 
 */
error_t wifi_sta_scan_done_event(wifi_event_sta_scan_done_t* p_scan);
/**
 * @brief Handle WIFI station started event
 * 
 * @return error_t 
 */
error_t wifi_sta_started_event(void);

/**
 * @brief Handle WIFI station connected event
 * 
 * @param p_ap 
 * @return error_t 
 */
error_t wifi_sta_connected_event(wifi_event_sta_connected_t* p_ap);

/**
 * @brief 
 * 
 * @param p_disc_event 
 * @return error_t 
 */
error_t wifi_sta_disconnected_event(wifi_event_sta_disconnected_t* p_disc_event);
/**
 * @brief 
 * 
 * @param p_ip 
 * @return error_t 
 */
error_t wifi_sta_got_ip_event(ip_event_got_ip_t* p_ip);

/**
 * @brief Start WIFI scan
 * 
 * @param scan_type Type of scan to conduct
 * @param p_scan_target If scan_type is not WIFI_STA_SCAN_ALL_APS, this parameter must be a
 *                          non NULL value
 * @return error_t 
 */
error_t wifi_sta_start_scan(wifi_sta_scan_type_t scan_type, wifi_ap_desc_t* p_scan_target);

/**
 * @brief 
 * 
 * @param p_scan 
 * @return error_t 
 */
error_t wifi_sta_print_scan(const wifi_sta_scan_t* p_scan);

#endif