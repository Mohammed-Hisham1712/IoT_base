#ifndef __WIFI_COMPONENT_H__

#define __WIFI_COMPONENT_H__

#include "wifi_component_public.h"
#include "wifi_ap_private.h"
#include "wifi_sta_private.h"
#include "wifi_component_param.h"
#include "types.h"

#define WIFI_COMPONENT_STACK_SIZE       CONFIG_WIFI_COMPONENT_STACK_SIZE
#define WIFI_COMPONENT_TSK_PRI          CONFIG_WIFI_COMPONENT_TSK_PRI

#define WIFI_COMPONENT_TARGET_AP_SET        0x0001
#define WIFI_COMPONENT_TARGET_AP_CHANGED    0x0002
#define WIFI_COMPONENT_TARGET_AP_DELETED    0x0004

typedef enum
{
    WIFI_COMPONENT_STATE_NONE,
    WIFI_COMPONENT_STATE_INIT,
    WIFI_COMPONENT_STATE_AP,
    WIFI_COMPONENT_STATE_STA,
    WIFI_COMPONENT_STATE_APSTA,
    WIFI_COMPONENT_STATE_MAX
} wifi_component_state_t;

typedef enum
{
    WIFI_COMPONENT_TRANS_TO_AP,
    WIFI_COMPONENT_TRANS_TO_STA,
    WIFI_COMPONENT_TRANS_TO_APSTA,
    WIFI_COMPONENT_TRANS_MAX
} wifi_component_trans_t;

typedef struct 
{
    wifi_ap_ctrl_t          ap_ctrl;
    wifi_sta_ctrl_t         sta_ctrl;
    wifi_component_state_t  state;
    wifi_component_param_t  param;
    uint16_t                control_status;
} wifi_component_ctrl_t;

/**
 * @brief 
 * 
 * @param p_ap_desc 
 * @return error_t 
 */
error_t wifi_component_set_target_ap(wifi_ap_desc_t* p_ap_desc);

/**
 * @brief 
 * 
 * @param state 
 * @return error_t 
 */
error_t wifi_component_apply_config(void);

/**
 * @brief 
 * 
 * @return error_t 
 */
error_t wifi_component_reset_config(void);

/**
 * @brief 
 * 
 * @param status 
 * @return error_t 
 */
error_t wifi_component_get_sta_status(wifi_sta_status_t* status);

#endif