#ifndef __MQTT_COMPONENT_PUBLIC_H__

#define __MQTT_COMPONENT_PUBLIC_H__

#include "types.h"

#include <stdint.h>

typedef struct
{
    const char* username;
    const char* passwd;
    uint8_t username_len;
    uint8_t passwd_len;
} mqtt_component_credentials_t;

/**
 * @brief 
 * 
 * @param username 
 * @param size 
 * @return error_t 
 */
error_t mqtt_component_get_own_username(char* username, uint16_t size);

/**
 * @brief Construct a new mqtt_component get own passwd object
 * 
 * @param passwd 
 * @param size 
 * @return error_t
 */
error_t mqtt_component_get_own_passwd(char* passwd, uint16_t size);

/**
 * @brief 
 * 
 * @param p_cred 
 * @return error_t 
 */
error_t mqtt_component_get_own_credentials(mqtt_component_credentials_t* p_cred);

/**
 * @brief 
 * 
 * @param p_cred 
 * @return error_t 
 */
error_t mqtt_component_set_own_credentials(const mqtt_component_credentials_t* p_cred);

/**
 * @brief 
 * 
 * @return error_t 
 */
error_t mqtt_component_init(void);

#endif