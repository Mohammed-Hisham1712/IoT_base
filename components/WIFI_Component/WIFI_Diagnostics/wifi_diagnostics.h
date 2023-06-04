#ifndef __WIFI_DIAGNOSTICS_H__

#define __WIFI_DIAGNOSTICS_H__

#include "types.h"

#include <stdint.h>

#define WIFI_DIAG_PING_REQ_COUNT        5
#define WIFI_DIAG_MAX_TIMEOUT_MS        2000
#define WIFI_DIAG_MAX_RETRIES           4

#define WIFI_DIAG_STATE_REACHABLE       0
#define WIFI_DIAG_STATE_UNREACHABLE     1


typedef struct
{
    uint16_t    rtt[WIFI_DIAG_PING_REQ_COUNT];
    uint16_t    avg_rtt;
    uint16_t    mdev_rtt;
    uint8_t     loss_rate;
    uint8_t     state;
} wifi_diag_stats_t;

typedef struct
{
    const char          ip[16];
    wifi_diag_stats_t   diag;
    uint16_t            timeout;
    uint8_t             retries;
} wifi_diag_host_t;


/**
 * @brief 
 * 
 */
void wifi_diagnostics_init(void);

/**
 * @brief 
 * 
 * @return error_t 
 */
error_t wifi_diagnostics_run(void);

#endif