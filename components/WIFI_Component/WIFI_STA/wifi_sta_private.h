#ifndef __WIFI_STA_PRIVATE_H__

#define __WIFI_STA_PRIVATE_H__

#include "wifi_sta_public.h"
#include "wifi_ap_public.h"


/**
 * @brief Handle WIFI scan done event
 * 
 * @param p_scan 
 * @return error_t 
 */
error_t wifi_sta_scan_done_event(wifi_sta_ctrl_t* p_wifi_sta, 
                                        wifi_event_sta_scan_done_t* p_scan);
/**
 * @brief Handle WIFI station started event
 * 
 * @return error_t 
 */
error_t wifi_sta_started_event(wifi_sta_ctrl_t* p_wifi_sta);

/**
 * @brief Handle WIFI station connected event
 * 
 * @param p_ap 
 * @return error_t 
 */
error_t wifi_sta_connected_event(wifi_sta_ctrl_t* p_wifi_sta, 
                                            wifi_event_sta_connected_t* p_ap);

/**
 * @brief 
 * 
 * @param p_disc_event 
 * @return error_t 
 */
error_t wifi_sta_disconnected_event(wifi_sta_ctrl_t* p_wifi_sta, 
                                            wifi_event_sta_disconnected_t* p_disc_event);
/**
 * @brief 
 * 
 * @param p_ip 
 * @return error_t 
 */
error_t wifi_sta_got_ip_event(wifi_sta_ctrl_t* p_wifi_sta, 
                                            ip_event_got_ip_t* p_ip);

/**
 * @brief Start WIFI scan
 * 
 * @param scan_type Type of scan to conduct
 * @param p_scan_target If scan_type is not WIFI_STA_SCAN_ALL_APS, this parameter must be a
 *                          non NULL value
 * @return error_t 
 */
error_t wifi_sta_start_scan(wifi_sta_ctrl_t* p_wifi_sta, 
                                wifi_sta_scan_type_t scan_type, wifi_ap_desc_t* p_scan_target);

/**
 * @brief 
 * 
 * @param p_scan 
 * @return error_t 
 */
error_t wifi_sta_print_scan(const wifi_sta_scan_t* p_scan);

/**
 * @brief 
 * 
 * @return error_t 
 */
error_t wifi_sta_init(wifi_sta_ctrl_t* p_wifi_sta, wifi_ap_desc_t* target_ap);

/**
 * @brief 
 * 
 * @param p_wifi_sta 
 * @return error_t 
 */
error_t wifi_sta_deinit(wifi_sta_ctrl_t* p_wifi_sta);

#endif