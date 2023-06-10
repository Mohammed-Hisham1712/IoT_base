#ifndef __WIFI_COMPONENT_PARAM_H__

#define __WIFI_COMPONENT_PARAM_H__

#include "wifi_ap_public.h"
#include "types.h"

#include <stdint.h>

typedef struct
{
    uint8_t         ap_provisioned;
    wifi_ap_desc_t  target_ap_desc;
} wifi_component_param_t;

/**
 * @brief 
 * 
 * @param offset 
 * @param size 
 * @param p_buffer 
 * @return error_t 
 */
error_t wifi_param_read(uint16_t offset, uint16_t size, void* p_buffer);

/**
 * @brief 
 * 
 * @param offset 
 * @param size 
 * @param p_buffer 
 * @return error_t 
 */
error_t wifi_param_write(uint16_t offset, uint16_t size, void* p_buffer);

/**
 * @brief 
 * 
 * @param p_param 
 * @return error_t 
 */
error_t wifi_param_load(wifi_component_param_t* p_param);

/**
 * @brief 
 * 
 * @param p_param 
 * @return error_t 
 */
error_t wifi_param_store(wifi_component_param_t* p_param);

#endif