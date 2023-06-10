#ifndef __PROTOBUF_HTTP_CLIENT_H__

#define __PROTOBUF_HTTP_CLIENT_H__

#include <stdint.h>

#define WIFI_AP_SSID_MAX_LENGTH         32
#define WIFI_AP_MAX_PASSPHRASE_LENGTH   32

typedef enum
{
    HTTP_REQ_WIFI_CONFIG_AP_INFO,
    HTTP_REQ_WIFI_CONFIG_CMD,
    HTTP_REQ_INVALID
} request_type_t;

typedef enum
{
    HTTP_RESP_HEADER,
    HTTP_RESP_SEPERATOR,
    HTTP_RESP_DATA,
} http_resp_phase_t;

typedef enum
{
    WIFI_CONFIG_CMD_APPLY_CONFIG,
    WIFI_CONFIG_CMD_RESET_CONFIG,
    WIFI_CONFIG_CMD_GET_STA_STATUS,
    WIFI_CONFIG_CMD_INVALID
} wifi_config_cmd_t;

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

typedef struct
{
    request_type_t req_type;
    union
    {
        wifi_ap_desc_t ap_desc;
        wifi_config_cmd_t wifi_config_cmd;
    } data;
} request_t;

int protobuf_process_status_resp(uint8_t* inbuf, uint16_t inlen);
int protobuf_process_sta_get_status_resp(uint8_t* inbuf, uint16_t inlen);

#endif