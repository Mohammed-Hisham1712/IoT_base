#ifndef __WIFI_STA_PUBLIC_H__

#define __WIFI_STA_PUBLIC_H__

#include "wifi_ap_public.h"
#include "types.h"

/**
 * @brief 
 * 
 * @return error_t 
 */
error_t wifi_sta_init(const wifi_ap_desc_t* p_ap_desc);

/**
 * @brief 
 * 
 * @param p_ap_desc 
 * @return error_t 
 */
error_t wifi_sta_start(void);

/**
 * @brief 
 * 
 * @return error_t 
 */
error_t wifi_sta_connect(void);

/**
 * @brief 
 * 
 * @return error_t 
 */
error_t wifi_sta_run(void);
#endif