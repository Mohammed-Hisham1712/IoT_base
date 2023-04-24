#ifndef __PROTOBUF_HTTP_CLIENT_H__

#define __PROTOBUF_HTTP_CLIENT_H__

#include <stdint.h>

#define WIFI_AP_SSID_MAX_LENGTH         32
#define WIFI_AP_MAX_PASSPHRASE_LENGTH   32

typedef enum
{
    HTTP_REQ_AP_INFO,
    HTTP_REQ_INVALID
} http_request_t;

typedef struct
{
    const char* endpoint;
    const char* host;
    uint8_t*    data;
    uint16_t    data_len;
} http_post_t;

typedef struct
{
    char ap_ssid[WIFI_AP_SSID_MAX_LENGTH];
    char ap_passphrase[WIFI_AP_MAX_PASSPHRASE_LENGTH];
    uint16_t ap_ssid_len;       /* Length including NULL terminator */
    uint16_t ap_passphrase_len;  /* Length including NULL terminator */
} wifi_ap_desc_t;


#endif