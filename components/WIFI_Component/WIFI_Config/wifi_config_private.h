#ifndef __WIFI_CONFIG_PRIVATE_H__

#define __WIFI_CONFIG_PRIVATE_H__

#include "wifi_config_public.h"
#include "wifi_ap_public.h"

#include "esp_err.h"

#include <stdint.h>

#define WIFI_CONFIG_AP_INFO_EP      "ap_set_info_req"

typedef esp_err_t (*wifi_config_endpoint_handler_t) (uint32_t session_id, 
                                                        const uint8_t* inbuf, ssize_t inlen,
                                                        uint8_t** outbuf, ssize_t* outlen,
                                                        void* pdata);

esp_err_t wifi_config_ap_set_info_req_handler(uint32_t session_id,
                                                        const uint8_t* inbuf, ssize_t inlen,
                                                        uint8_t** outbuf, ssize_t* outlen,
                                                        void* pdata);
#endif