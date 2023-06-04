#include "wifi_diagnostics.h"
#include "wifi_component_public.h"
#include "timer.h"
#include "types.h"

#include "lwip/ip4_addr.h"
#include "ping/ping_sock.h"
#include "esp_log.h"
#include "esp_event.h"
#include "freertos/task.h"

#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

#define WIFI_DIAG_TAG       "WIFI_DIAG"

typedef struct
{
    esp_ping_handle_t   ping_handle;
    millis_timer_t      diag_timer;
    uint8_t             ping_started;
} wifi_diag_t;

static wifi_diag_host_t diag_hosts[] = 
{
    {.ip = "8.8.8.8"}
};

static wifi_diag_t wifi_diag;

ESP_EVENT_DECLARE_BASE(WIFI_COMP_EVENT);

static void wifi_diagnostics_ping_success(esp_ping_handle_t hdl, void* args)
{
    wifi_diag_host_t* p_host;
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

    if(args && seqno <= 4)
    {
        p_host = (wifi_diag_host_t*) args;
        p_host->diag.rtt[seqno - 1] = elapsed_time;
    }
}

static void wifi_diagnostics_ping_timeout(esp_ping_handle_t hdl, void* args)
{
    wifi_diag_host_t* p_host;
    ip_addr_t recv_addr;
    uint16_t seqno;

    esp_ping_get_profile(hdl, ESP_PING_PROF_SEQNO, &seqno, sizeof(seqno));
    esp_ping_get_profile(hdl, ESP_PING_PROF_IPADDR, &recv_addr, sizeof(recv_addr));

    printf("From (%s) icmp_seq=%d timeout\n", 
                        ip4addr_ntoa(&recv_addr.u_addr.ip4), seqno);
    
    if(args && seqno <= WIFI_DIAG_PING_REQ_COUNT)
    {
        p_host = (wifi_diag_host_t*) args;
        p_host->diag.rtt[seqno - 1] = 0;
    }
}

static void wifi_diagnostics_ping_end(esp_ping_handle_t hdl, void* args)
{
    wifi_diag_host_t* p_host;
    uint32_t transmitted;
    uint32_t received;
    uint32_t total_time;
    float lost;
    uint8_t count;

    count = 0;

    esp_ping_get_profile(hdl, ESP_PING_PROF_REQUEST, &transmitted, sizeof(transmitted));
    esp_ping_get_profile(hdl, ESP_PING_PROF_REPLY, &received, sizeof(received));
    esp_ping_get_profile(hdl, ESP_PING_PROF_DURATION, &total_time, sizeof(total_time));

    if(transmitted)
    {
        lost = (float)(transmitted - received) / transmitted * 100.0f;
        printf("%d packets transmitted, %d received, %d%% packets loss, time %dms\n",
            transmitted, received, (uint32_t) (lost), total_time);
    }
    else
    {
        ESP_LOGE(WIFI_DIAG_TAG, "No ICMP packets transmitted");
        return;
    }

    if(args)
    {
        p_host = (wifi_diag_host_t*) args;

        p_host->diag.loss_rate = (uint8_t) lost;

        for(uint8_t indx = 0; indx < WIFI_DIAG_PING_REQ_COUNT; indx++)
        {
            if(p_host->diag.rtt[indx])
            {
                p_host->diag.avg_rtt += p_host->diag.rtt[indx];
                count++;
            }
        }

        if(count)
        {
            p_host->diag.avg_rtt /= count;
        }
        else
        {
            p_host->diag.avg_rtt = 0;
        }

        if(received > 0)
        {
            p_host->retries = 0;
            p_host->timeout = p_host->diag.avg_rtt * 2;
            
            if(p_host->diag.state != WIFI_DIAG_STATE_REACHABLE)
            {
                p_host->diag.state = WIFI_DIAG_STATE_REACHABLE;
                ESP_LOGD(WIFI_DIAG_TAG, "Network is up!");

                esp_event_post(WIFI_COMP_EVENT, WIFI_COMP_EVENT_INTERNET_UP,
                                                        NULL, 0, portMAX_DELAY);
            }
        }
        else
        {
            if(++p_host->retries < WIFI_DIAG_MAX_RETRIES)
            {
                p_host->timeout *= 2;
                if(p_host->timeout > WIFI_DIAG_MAX_TIMEOUT_MS)
                {
                    p_host->timeout = WIFI_DIAG_MAX_TIMEOUT_MS;
                }
                
                ESP_LOGD(WIFI_DIAG_TAG, "Timeout increased to %dms\n", p_host->timeout);
            }
            else if(p_host->diag.state == WIFI_DIAG_STATE_REACHABLE)
            {
                p_host->diag.state = WIFI_DIAG_STATE_UNREACHABLE;
                p_host->retries = WIFI_DIAG_MAX_RETRIES;
                p_host->timeout = WIFI_DIAG_MAX_TIMEOUT_MS;

                ESP_LOGD(WIFI_DIAG_TAG, "Network is down");

                esp_event_post(WIFI_COMP_EVENT, WIFI_COMP_EVENT_INTERNET_DOWN,
                                                            NULL, 0, portMAX_DELAY);
            }
        }

        printf("rtt avg = %d ms\n", p_host->diag.avg_rtt);
    }

    esp_ping_delete_session(hdl);

    wifi_diag.ping_started = 0;
}

error_t wifi_diagnostics_ping_host(wifi_diag_host_t* p_host)
{
    ip4_addr_t  ip4_addr;
    ip_addr_t   target_addr;
    esp_ping_config_t ping_config = ESP_PING_DEFAULT_CONFIG();
    esp_ping_callbacks_t ping_cbs;

    if(!p_host)
    {
        return RET_FAILED;
    }

    memset(&target_addr, 0, sizeof(ip_addr_t));
    ip4addr_aton(p_host->ip, &ip4_addr);
    memcpy(&target_addr.u_addr.ip4, &ip4_addr, sizeof(ip4_addr_t));

    ping_config.count = WIFI_DIAG_PING_REQ_COUNT;
    if(p_host->timeout > 0)
    {
        ping_config.timeout_ms = p_host->timeout;
    }
    else
    {
        ping_config.timeout_ms = WIFI_DIAG_MAX_TIMEOUT_MS / 2;
    }

    memcpy(&ping_config.target_addr, &target_addr, sizeof(ip_addr_t));

    ping_cbs.cb_args = p_host;
    ping_cbs.on_ping_success = &wifi_diagnostics_ping_success;
    ping_cbs.on_ping_timeout = &wifi_diagnostics_ping_timeout;
    ping_cbs.on_ping_end = &wifi_diagnostics_ping_end;

    if(esp_ping_new_session(&ping_config, &ping_cbs, &wifi_diag.ping_handle) != ESP_OK)
    {
        ESP_LOGE(WIFI_DIAG_TAG, "Couldn't create a ping session");

        return RET_FAILED;
    }

    if(esp_ping_start(wifi_diag.ping_handle) != ESP_OK)
    {
        ESP_LOGE(WIFI_DIAG_TAG, "Couldn't start ping session");

        return RET_FAILED;
    }

    wifi_diag.ping_started = 1;

    return RET_OK;
}

void wifi_diagnostics_init(void)
{
    diag_hosts[0].retries = 0;
    diag_hosts[0].timeout = 0;

    memset(&diag_hosts[0].diag, 0, sizeof(wifi_diag_stats_t)); 
    
    memset(&wifi_diag, 0, sizeof(wifi_diag_t));
}

error_t wifi_diagnostics_run(void)
{
    if(timer_is_started(&wifi_diag.diag_timer))
    {
        if(timer_elapsed(&wifi_diag.diag_timer) >= 15000 && !wifi_diag.ping_started)
        {
            ESP_LOGD(WIFI_DIAG_TAG, "Pinging host %s\n", diag_hosts[0].ip);
            wifi_diagnostics_ping_host(&diag_hosts[0]);

            timer_start(&wifi_diag.diag_timer);
        }
    }
    else
    {
        timer_start(&wifi_diag.diag_timer);
    }

    return RET_OK;
}
