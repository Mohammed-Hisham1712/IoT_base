#ifndef __MQTT_COMPONENT_PUBLIC_H__

#define __MQTT_COMPONENT_PUBLIC_H__

#include "types.h"

#include <stdint.h>

#define MQTT_COMPONENT_MAX_USERNAME_SIZE    32
#define MQTT_COMPONENT_MAX_PASSWORD_SIZE    32

typedef struct
{
    char username[MQTT_COMPONENT_MAX_USERNAME_SIZE];
    char passwd[MQTT_COMPONENT_MAX_PASSWORD_SIZE];
    uint8_t username_len;   /* Length of username including null character*/
    uint8_t passwd_len;     /* Length of passwd including null character */
} mqtt_component_credentials_t;

/**
 * @brief Get MQTT authentication username
 * 
 * @param username  Pointer to a buffer to copy username into
 * @param size      Size of the given buffer. Must be big enough to 
 *                  include the username + null character
 * @return error_t 
 */
error_t mqtt_component_get_own_username(char* username, uint16_t size);

/**
 * @brief Get MQTT authentication password
 * 
 * @param passwd    Pointer to a buffer to copy passwd into
 * @param size      Size of the give buffer. Must be big enough to include 
 *                  the passwd + null character
 * @return error_t
 */
error_t mqtt_component_get_own_passwd(char* passwd, uint16_t size);

/**
 * @brief Get a copy of MQTT authentication credentials (useranem & password)
 * 
 * @param p_cred Pointer to buffer to copy credentials into
 * @return error_t 
 */
error_t mqtt_component_get_own_credentials(mqtt_component_credentials_t* p_cred);

/**
 * @brief Set MQTT authentication credentials (useranem & password)
 * 
 * @param p_cred    Pointer to buffer. The contents of this buffer is copied to MQTT
 *                  local storage.
 * @return error_t 
 */
error_t mqtt_component_set_own_credentials(const mqtt_component_credentials_t* p_cred);

/**
 * @brief 
 * 
 * @return error_t 
 */
error_t mqtt_component_init(void);

/**
 * @brief 
 * 
 * @return error_t 
 */
error_t mqtt_component_start(void);

#endif