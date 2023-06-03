#ifndef __WIFI_CONFIG_PRIVATE_H__

#define __WIFI_CONFIG_PRIVATE_H__

#include "wifi_prov_public.h"
#include "appl_config.h"

#include "esp_err.h"

#include <stdint.h>

#define WIFI_CONFIG_AP_INFO_EP              "wifi_config_ap_set_info_req"
#define WIFI_CONFIG_CMD_EP                  "wifi_config_cmd_req"

typedef esp_err_t (*wifi_config_endpoint_handler_t) (uint32_t session_id, 
                                                        const uint8_t* inbuf, ssize_t inlen,
                                                        uint8_t** outbuf, ssize_t* outlen,
                                                        void* pdata);

typedef struct 
{
    const char* endpoint;
    wifi_config_endpoint_handler_t handler;
} wifi_prov_desc_t;

#endif