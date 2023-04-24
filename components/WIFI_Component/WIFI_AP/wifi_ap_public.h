#ifndef __WIFI_AP_PUBLIC_H__

#define __WIFI_AP_PUBLIC_H__

#include "types.h"

#define WIFI_AP_SSID_MAX_LENGTH         (CONFIG_WIFI_AP_SSID_MAX_LENGTH + 1)
#define WIFI_AP_MAX_PASSPHRASE_LENGTH   (CONFIG_WIFI_AP_MAX_PASSPHRASE_LENGTH + 1)

typedef enum
{
    WIFI_AP_STATE_NONE = 0,
    WIFI_AP_STATE_INIT,
    WIFI_AP_STATE_STARTED,
    WIFI_AP_STATE_STOPPED,
    WIFI_AP_STATE_MAX,
} wifi_ap_state_t;

typedef struct
{
    char     ap_ssid[WIFI_AP_SSID_MAX_LENGTH];
    char     ap_passphrase[WIFI_AP_MAX_PASSPHRASE_LENGTH];
    uint16_t ap_ssid_len;           /* Length including NULL terminator */
    uint16_t ap_passphrase_len;     /* Length including NULL terminator */
    uint8_t  ap_bssid[6];           /* MAC address of AP */
} wifi_ap_desc_t;

/**
 * @brief Return current AP state
 * 
 * @return wifi_ap_state_t 
 */
wifi_ap_state_t wifi_ap_get_state(void);

/**
 * @brief Get SSID of ESP Access Point including null character
 * 
 * @param p_ssid Pointer to allocated memory to store the SSID
 * @param size Size of allocated memory. Must be at least the size of AP SSID
 * @return error_t 
 *                  RET_OK: SSID is copied into p_ssid successfully
 *                  RET_FAILED: Either p_ssid is NULL or size is insufficient
 */
error_t wifi_ap_get_own_ssid(char* p_ssid, uint16_t size);

/**
 * @brief Get Passphrase of ESP Access Point including null character
 * 
 * @param p_passphrase Pointer to allocated memory to store the Passphrase
 * @param size Size of allocated memory. Must be at least the size of AP Passphrase
 * @return error_t 
 *                  RET_OK: Passphrase is copied into p_passphrase successfully
 *                  RET_FAILED: Either p_passphrase is NULL or size is insufficient
 */
error_t wifi_ap_get_own_passphrase(char* p_passphrase, uint16_t size);

/**
 * @brief Get length of ESP AP SSID including NULL terminator
 * 
 * @return uint16_t Size of AP SSID
 */
uint16_t wifi_ap_get_own_ssid_len(void);

/**
 * @brief Get length of ESP AP passphrase including NULL terminator
 * 
 * @return uint16_t Size of AP passphrase
 */
uint16_t wifi_ap_get_own_passphrase_len(void);

/**
 * @brief Set SSID for an AP pointed to by p_desc.
 * 
 * @param p_desc Pointer to a structure describing the AP
 * @param ssid A null terminated string.
 * @param len Length of ssid including null character
 * @return error_t 
 */
error_t wifi_ap_set_ssid(wifi_ap_desc_t* p_desc, const char* ssid, uint16_t len);

/**
 * @brief Set passphrase for an AP pointed to by p_desc.
 * 
 * @param p_desc Pointer to a structure describing the AP
 * @param passphrase A null terminated string.
 * @param len Length of passphrase including null character
 * @return error_t 
 */
error_t wifi_ap_set_passphrase(wifi_ap_desc_t* p_desc, const char* passphrase, uint16_t len);

/**
 * @brief Set BSSID for an AP pointed to by p_desc
 * 
 * @param p_desc Pointer to a structure describing the AP
 * @param mac Pointer to an array holding the BSSID
 * @return error_t 
 */
error_t wifi_ap_set_bssid(wifi_ap_desc_t* p_desc, uint8_t* mac);

#endif