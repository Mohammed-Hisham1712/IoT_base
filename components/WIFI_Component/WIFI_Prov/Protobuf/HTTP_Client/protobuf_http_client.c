#include "protobuf_http_client.h"
#include "../wifi_config.pb-c.h"

#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

#define HTTP_PORT   80
#define HTTP_POST_FORMAT \
"POST /%s HTTP/1.1\r\n\
Host: %s\r\n\
Content-Type: text/plain\r\n\
Content-Length: %d\r\n\
\r\n"

#define HTTP_POST_RESP  \
"HTTP/1.1 200 OK\r\n\
Content-Type: text/html\r\n\
Content-Length: %d\r\n"

#define HTTP_SERVER_IP  "192.168.4.1"

#define HTTP_WIFI_CONFIG_AP_CONFIG_ENDPOINT     "wifi_config_ap_set_info_req"
#define HTTP_WIFI_CONFIG_CMD_ENDPOINT           "wifi_config_cmd_req"


#define ERROR(msg)  (fprintf(stderr, "ERROR: [Line %d] %s\n\r", __LINE__, msg))

int protobuf_process_resp(request_type_t req, uint8_t* inbuf, uint16_t inlen)
{
    int ret;

    switch(req)
    {
        case HTTP_REQ_WIFI_CONFIG_AP_INFO:
            ret = protobuf_process_status_resp(inbuf, inlen);
            break;
        case HTTP_REQ_WIFI_CONFIG_CMD:
            ret = protobuf_process_sta_get_status_resp(inbuf, inlen);
            break;
        default:
            ret = -1;
            break;
    }

    return ret;
}

int protobuf_process_sta_get_status_resp(uint8_t* inbuf, uint16_t inlen)
{
    WifiConfigGetStatusResp* resp;

    if(inbuf && (inlen > 0))
    {
        resp = wifi_config_get_status_resp__unpack(NULL, inlen, inbuf);

        if(resp)
        {
            if(resp->status == STATUS_RESP_TYPE__StatusRespOk)
            {
                puts("[STATUS]: OK");

                switch(resp->sta_status)
                {
                    case WIFI_CONFIG_GET_STATUS_TYPE__GetStatusTypeOffline:
                        puts("WIFI STA is Offline");
                        break;
                    case WIFI_CONFIG_GET_STATUS_TYPE__GetStatusTypeAssociated:
                        puts("WIFI STA is associated to an AP");
                        break;
                    case WIFI_CONFIG_GET_STATUS_TYPE__GetStatusTypeGotIP:
                        puts("WIFI STA got an IP address");
                        break;
                    case WIFI_CONFIG_GET_STATUS_TYPE__GetStatusTypeOnline:
                        puts("WIFI STA is Online");
                        break;
                    default:
                        puts("WIFI STA status unkown");
                        break;
                }
            }
            else
            {
                puts("[STATUS]: FAILED");
            }

            wifi_config_get_status_resp__free_unpacked(resp, NULL);
            
            return 0;
        }
    }

    return -1;
}

int protobuf_process_status_resp(uint8_t* inbuf, uint16_t inlen)
{
    StatusResp* resp;

    if(inbuf && (inlen > 0))
    {
        resp = status_resp__unpack(NULL, inlen, inbuf);
        if(resp)
        {
            switch(resp->status)
            {
                case STATUS_RESP_TYPE__StatusRespOk:
                    puts("[STATUS]: OK");
                    break;
                case STATUS_RESP_TYPE__StatusRespFailed:
                    puts("[status]: FAILED");
                    break;
                default:
                    return -1;
            }

            status_resp__free_unpacked(resp, NULL);

            return 0;
        }
    }

    return -1;
}

int protobuf_ap_set_info_req_prepare(wifi_ap_desc_t* p_desc, 
                                                uint8_t** outbuf, uint16_t* outlen)
{
    WifiConfigApSetInfoReq wifi_config_req = WIFI_CONFIG_AP_SET_INFO_REQ__INIT;
    uint16_t len;

    if(p_desc && outbuf && outlen)
    {
        wifi_config_req.ssid = p_desc->ap_ssid;
        wifi_config_req.passphrase = p_desc->ap_passphrase;

        len = wifi_config_ap_set_info_req__get_packed_size(&wifi_config_req);

        *outbuf = (uint8_t*) malloc(len);
        if(*outbuf == NULL)
        {
            ERROR("Cannot allocate memory");
            return -1;
        }

        if(wifi_config_ap_set_info_req__pack(&wifi_config_req, *outbuf) != len)
        {
            ERROR("Failed to pack message");
            return -1;
        }

        *outlen = len;

        puts("Data packed for HTTP request");

        return 0;
    }

    return -1;
}

int protobuf_wifi_config_cmd_prepare(wifi_config_cmd_t cmd, 
                                                uint8_t** outbuf, uint16_t* outlen)
{
    WifiConfigCmdReq cmd_req = WIFI_CONFIG_CMD_REQ__INIT;
    uint16_t len;

    if(outbuf && outlen)
    {
        switch (cmd)
        {
            case WIFI_CONFIG_CMD_APPLY_CONFIG:
                cmd_req.cmd = WIFI_CONFIG_CMD_TYPE__CmdTypeApplyConfig;
                break;
            case WIFI_CONFIG_CMD_RESET_CONFIG:
                cmd_req.cmd = WIFI_CONFIG_CMD_TYPE__CmdTypeResetConfig;
                break;
            case WIFI_CONFIG_CMD_GET_STA_STATUS:
                cmd_req.cmd = WIFI_CONFIG_CMD_TYPE__CmdTypeGetStatus;
                break;
            default:
                return -1;
        }

        len = wifi_config_cmd_req__get_packed_size(&cmd_req);
        *outbuf = (uint8_t*) malloc(len);

        if(*outbuf == NULL)
        {
            ERROR("Cannot allocate memory");
            return -1;
        }

        if(wifi_config_cmd_req__pack(&cmd_req, *outbuf) != len)
        {
            ERROR("Failed to pack message");
            return -1;
        }

        *outlen = len;

        puts("Data packed for HTTP request");

        return 0;
    }

    return -1;
}

int http_client_connect(const char* ip_server)
{
    int sock;
    struct sockaddr_in local_addr;
    struct sockaddr_in server_addr;
    struct in_addr in_addr;

    local_addr.sin_family = AF_INET;
    local_addr.sin_addr.s_addr = INADDR_ANY;

    if(ip_server)
    {
        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(HTTP_PORT);
        inet_pton(AF_INET, ip_server, &in_addr);
        memcpy(&server_addr.sin_addr, &in_addr, sizeof(struct in_addr));
    }
    else
    {
        ERROR("Empty IP address");
        return -1;
    }

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock == -1)
    {
        ERROR("Cannot open socket");
        return -1;
    }

    if(bind(sock, (struct sockaddr*) &local_addr, sizeof(local_addr)) == -1)
    {
        ERROR("Cannot bind socket");
        return -1;
    }

    if(connect(sock, (struct sockaddr*) &server_addr, sizeof(server_addr)) == -1)
    {
        ERROR("Cannot connect to HTTP server");
        return -1;
    }

    printf("Connected to HTTP [%s:%d]\r\n", ip_server, HTTP_PORT);

    return sock;
}

int http_client_post(request_type_t req, int sock, const http_post_t* p_post)
{
    char* http_post;
    uint8_t* resp;
    char recv_buf[512];
    char* p_recv_buf;
    uint16_t total_len;
    uint16_t msg_len;
    uint32_t resp_len;
    uint16_t n_recv;
    http_resp_phase_t phase = HTTP_RESP_HEADER;

    if(p_post == NULL)
    {
        return -1;
    }

    if(p_post->data == NULL || p_post->endpoint == NULL || p_post->host == NULL)
    {
        return -1;
    }

    total_len = strlen(p_post->endpoint) + strlen(p_post->host) + 
                p_post->data_len + sizeof(HTTP_POST_FORMAT) + 1; 

    http_post = (char*) malloc(total_len);
    if(http_post == NULL)
    {
        ERROR("Cannot allocate memory");
        return -1;
    }

    msg_len = snprintf(http_post, total_len, HTTP_POST_FORMAT, p_post->endpoint,
                                                    p_post->host, p_post->data_len);
    memcpy(&http_post[msg_len], p_post->data, p_post->data_len);
    msg_len += p_post->data_len;

    if(msg_len >= total_len)
    {
        ERROR("Cannot construct POST message");
        return -1;
    }

    printf("Sending %d bytes\r\n", msg_len);

    if(send(sock, http_post, msg_len, 0) == -1)
    {
        ERROR("Failed to send message");
        return -1;
    }

    puts("Waiting for data.....\n");

    while(1)
    {
        n_recv = recv(sock, recv_buf, sizeof(recv_buf), 0);
        printf("[REV] %d bytes\n", n_recv);

        if(n_recv > 0)
        {
            if(phase == HTTP_RESP_HEADER)
            {
                if(sscanf(recv_buf, HTTP_POST_RESP, &resp_len) < 1)
                {
                    ERROR("Unkown HTTP resp header");
                    break;
                }
                printf("[Resp] %d bytes\n", resp_len);
                phase = HTTP_RESP_SEPERATOR;
            }
            else if(phase == HTTP_RESP_SEPERATOR)
            {
                if(memcmp(recv_buf, "\r\n", sizeof("\r\n") - 1) == 0)
                {
                    phase = HTTP_RESP_DATA;
                    n_recv -= 2;
                    if(n_recv > 0)
                    {
                        p_recv_buf = recv_buf + 2;
                    }
                    else
                    {
                        p_recv_buf = recv_buf;
                    }
                }
                else
                {
                    ERROR("Uknown HTTP resp seperator");
                    break;
                }
            }

            if(phase == HTTP_RESP_DATA && (n_recv == resp_len))
            {
                if(protobuf_process_resp(req, p_recv_buf, resp_len) < 0)
                {
                    ERROR("Cannot process response");
                }
                break;
            }
        }
        else if(n_recv == 0)
        {
            shutdown(sock, SHUT_WR);
            puts("HTTP connection closed");
            break;
        }
        else
        {
            ERROR("Connection terminated");
            break;
        }
    }

    close(sock);
    free(http_post);

    return 0;
}

int process_ap_info(const char* ssid, const char* passphrase, wifi_ap_desc_t* p_desc)
{
    wifi_ap_desc_t ap_desc;
    uint16_t len;

    if(!ssid || !passphrase || !p_desc)
    {
        return -1;
    }

    len = strlen(ssid) + 1;
    if(len <= WIFI_AP_SSID_MAX_LENGTH)
    {
        ap_desc.ap_ssid_len = len;
        memcpy(ap_desc.ap_ssid, ssid, ap_desc.ap_ssid_len);
    }
    else
    {
        ERROR("SSID is too long");
        return -1;
    }

    len = strlen(passphrase) + 1;
    if(len <= WIFI_AP_MAX_PASSPHRASE_LENGTH)
    {
        ap_desc.ap_passphrase_len = len;
        memcpy(ap_desc.ap_passphrase, passphrase, ap_desc.ap_passphrase_len);
    }
    else
    {
        ERROR("Passphrase is too long");
        return -1;
    }

    memcpy(p_desc, &ap_desc, sizeof(wifi_ap_desc_t));

    printf("SSID: %s\n\rPassphrase: %s\n\r", ap_desc.ap_ssid, ap_desc.ap_passphrase);

    return 0;
}

int main(int argc, char* argv[])
{
    int sock;
    char* opt;
    request_t req;
    http_post_t post;

    if(argc > 1)
    {
        if((argv[1][0] == '-') && (argv[1][1] == '-'))
        {
            opt = &argv[1][2];
            
            if(memcmp(opt, "ap", sizeof("ap")) == 0)
            {
                if(argc > 3)
                {
                    req.req_type = HTTP_REQ_WIFI_CONFIG_AP_INFO;
                    if(process_ap_info(argv[2], argv[3], &req.data.ap_desc) < 0)
                    {
                        return -1;
                    }
                }
                else
                {
                    ERROR("Insufficient number of args");
                    return -1;
                }
            }
            else if(memcmp(opt, "sta-status", sizeof("sta-status")) == 0)
            {
                req.req_type = HTTP_REQ_WIFI_CONFIG_CMD;
                req.data.wifi_config_cmd = WIFI_CONFIG_CMD_GET_STA_STATUS;
            }
            else if(memcmp(opt, "ap-reset", sizeof("ap-reset")) == 0)
            {
                req.req_type = HTTP_REQ_WIFI_CONFIG_CMD;
                req.data.wifi_config_cmd = WIFI_CONFIG_CMD_RESET_CONFIG;
            }
            else if(memcmp(opt, "ap-apply", sizeof("ap-apply")) == 0)
            {
                req.req_type = HTTP_REQ_WIFI_CONFIG_CMD;
                req.data.wifi_config_cmd = WIFI_CONFIG_CMD_APPLY_CONFIG;
            }
            else
            {
                ERROR("Wrong argument format");
                return -1;
            }
        }
    }
    else
    {
        ERROR("Insufficient number of args");
        return -1;
    }

    post.host = HTTP_SERVER_IP;

    switch(req.req_type)
    {
        case HTTP_REQ_WIFI_CONFIG_AP_INFO:
            if(protobuf_ap_set_info_req_prepare(&req.data.ap_desc, 
                                                    &post.data, &post.data_len) < 0)
            {
                return -1;
            }
            post.endpoint = HTTP_WIFI_CONFIG_AP_CONFIG_ENDPOINT;
            break;
        case HTTP_REQ_WIFI_CONFIG_CMD:
            if(protobuf_wifi_config_cmd_prepare(req.data.wifi_config_cmd,
                                                    &post.data, &post.data_len) < 0)
            {
                return -1;
            }
            post.endpoint = HTTP_WIFI_CONFIG_CMD_ENDPOINT;
            break;
        default:
            return -1;
    }
    
    if((sock = http_client_connect(post.host)) == -1)
    {
        return -1;
    }
    
    if(http_client_post(req.req_type, sock, &post) < 0)
    {
        return -1;
    }

    free(post.data);

    return 0;
}
