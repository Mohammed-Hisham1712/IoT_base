#include "wifi_diagnostics.h"
#include "timer.h"
#include "types.h"

#include "lwip/ip4_addr.h"
#include "ping/ping_sock.h"
#include "esp_log.h"

#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

#define WIFI_DIAG_TAG       "WIFI_DIAG"


static void wifi_diagnostics_ping_success(esp_ping_handle_t hdl, void* args)
{
    ip_addr_t recv_addr;
    uint32_t elapsed_time;
    uint32_t recv_len;
    uint16_t seqno;
    uint8_t ttl;
    
    esp_ping_get_profile(hdl, ESP_PING_PROF_SEQNO, &seqno, sizeof(seqno));
    esp_ping_get_profile(hdl, ESP_PING_PROF_TTL, &ttl, sizeof(ttl));
    esp_ping_get_profile(hdl, ESP_PING_PROF_IPADDR, &recv_addr, sizeof(recv_addr));
    esp_ping_get_profile(hdl, ESP_PING_PROF_SIZE, &recv_len, sizeof(recv_len));
    esp_ping_get_profile(hdl, ESP_PING_PROF_TIMEGAP, &elapsed_time, sizeof(elapsed_time));

    printf("%d bytes received from (%s): icmp_seq=%d ttl=%d time=%dms\n",
            recv_len, ip4addr_ntoa(&recv_addr.u_addr.ip4), seqno, ttl, elapsed_time);
}

static void wifi_diagnostics_ping_timeout(esp_ping_handle_t hdl, void* args)
{
    ip_addr_t recv_addr;
    uint16_t seqno;

    esp_ping_get_profile(hdl, ESP_PING_PROF_SEQNO, &seqno, sizeof(seqno));
    esp_ping_get_profile(hdl, ESP_PING_PROF_IPADDR, &recv_addr, sizeof(recv_addr));

    printf("From (%s) icmp_seq=%d timeout\n", 
                        ip4addr_ntoa(&recv_addr.u_addr.ip4), seqno);
}

static void wifi_diagnostics_ping_end(esp_ping_handle_t hdl, void* args)
{
    uint32_t transmitted;
    uint32_t received;
    uint32_t total_time;
    float lost;

    esp_ping_get_profile(hdl, ESP_PING_PROF_REQUEST, &transmitted, sizeof(transmitted));
    esp_ping_get_profile(hdl, ESP_PING_PROF_REPLY, &received, sizeof(received));
    esp_ping_get_profile(hdl, ESP_PING_PROF_DURATION, &total_time, sizeof(total_time));

    if(transmitted)
    {
        lost = (transmitted - received) / transmitted * 100.0f;
        printf("%d packets transmitted, %d received, %d%% packets loss, time %dms\n",
            transmitted, received, (uint32_t) (lost), total_time);
    }
    else
    {
        ESP_LOGE(WIFI_DIAG_TAG, "No ICMP packets transmitted");
    }

    esp_ping_delete_session(hdl);
}

error_t wifi_diagnostics_run(void)
{
    ip4_addr_t  ip4_addr;
    ip_addr_t   target_addr;
    esp_ping_config_t ping_config = ESP_PING_DEFAULT_CONFIG();
    esp_ping_callbacks_t ping_cbs;
    esp_ping_handle_t ping_handle;

    ip4addr_aton("8.8.8.8", &ip4_addr);
    memcpy(&target_addr.u_addr.ip4, &ip4_addr, sizeof(ip4_addr_t));

    ping_config.count = 5;
    memcpy(&ping_config.target_addr, &target_addr, sizeof(ip_addr_t));

    ping_cbs.cb_args = NULL;
    ping_cbs.on_ping_success = &wifi_diagnostics_ping_success;
    ping_cbs.on_ping_timeout = &wifi_diagnostics_ping_timeout;
    ping_cbs.on_ping_end = &wifi_diagnostics_ping_end;

    if(esp_ping_new_session(&ping_config, &ping_cbs, &ping_handle) != ESP_OK)
    {
        ESP_LOGE(WIFI_DIAG_TAG, "Couldn't create a ping session");

        return RET_FAILED;
    }

    if(esp_ping_start(ping_handle) != ESP_OK)
    {
        ESP_LOGE(WIFI_DIAG_TAG, "Couldn't start ping session");

        return RET_FAILED;
    }

    return RET_OK;
}
