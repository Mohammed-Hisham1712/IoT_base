#ifndef __WIFI_PROV_HANDLERS_H__

#define __WIFI_PROV_HANDLERS_H__

#include "esp_err.h"

#include <stdint.h>

esp_err_t wifi_config_ap_set_info_req_handler(uint32_t session_id,
                                                        const uint8_t* inbuf, ssize_t inlen,
                                                        uint8_t** outbuf, ssize_t* outlen,
                                                        void* pdata);

esp_err_t wifi_config_cmd_req_handler(uint32_t session_id,
                                                    const uint8_t* inbuf, ssize_t inlen,
                                                    uint8_t** outbuf, ssize_t* outlen,
                                                    void* pdata);

#endif