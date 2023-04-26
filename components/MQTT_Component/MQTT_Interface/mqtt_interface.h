#ifndef __MQTT_INTERFACE_H__

#define __MQTT_INTERFACE_H__

#include "types.h"

#include <stdint.h>

#define MQTT_INTERFACE_PUBL_TYPE_PERIODIC     0x01
#define MQTT_INTERFACE_PUBL_TYPE_ON_EVENT     0x02
#define MQTT_INTERFACE_PUBL_TYPE_PERIODIC_OR_UPDATE \
                    (MQTT_INTERFACE_PUBL_TYPE_PERIODIC | MQTT_INTERFACE_PUBL_TYPE_ON_EVENT)

typedef int (*mqtt_interface_command_msg_cb_t) (void* args);

enum
{
    MQTT_INTERFACE_MESSAGE_TYPE_STATUS,
    MQTT_INTERFACE_MESSAGE_TYPE_SET,
    MQTT_INTERFACE_MESSAGE_TYPE_GET,
    MQTT_INTERFACE_MESSAGE_TYPE_CMD,
    MQTT_INTERFACE_MESSAGE_TYPE_MAX
};

typedef struct
{
    const char* topic;
    uint16_t data_id;
    uint16_t publ_type;
    uint8_t  publ_period;   
} mqtt_interface_status_msg_desc_t;

typedef struct
{
    const char* topic;
    uint16_t data_id;
} mqtt_interface_set_msg_desc_t;

typedef struct
{
    const char* topic;
    uint16_t data_id;
} mqtt_interface_get_msg_desc_t;

typedef struct
{
    const char* topic;
    mqtt_interface_command_msg_cb_t cmd_callback;    
} mqtt_interface_cmd_msg_desc_t;

typedef struct
{
    const mqtt_interface_status_msg_desc_t* status_msg_desc;
    const mqtt_interface_set_msg_desc_t*   set_msg_desc;
    const mqtt_interface_get_msg_desc_t*   get_msg_desc;
    const mqtt_interface_cmd_msg_desc_t*   cmd_msg_desc;
    uint8_t status_msg_desc_size;
    uint8_t set_msg_desc_size;
    uint8_t get_msg_desc_size;
    uint8_t cmd_msg_desc_size;
} mqtt_interface_msg_desc_t;


/**
 * @brief 
 * 
 * @param p_msg 
 * @return error_t 
 */
error_t mqtt_interface_get_msg_desc(mqtt_interface_msg_desc_t* p_desc);

/**
 * @brief 
 * 
 * @param ch_buf
 * @param buf_len
 * @param username 
 * @param client_id 
 * @param sub_topic 
 * @param msg_type 
 * @return error_t 
 */
error_t mqtt_interface_construct_topic(char* ch_buf, uint32_t buf_len, const char* username, 
                            const char* client_id, const char* sub_topic, uint8_t msg_type);

/**
 * @brief 
 * 
 * @param ch_buf 
 * @param buf_len 
 * @param p_username 
 * @param p_client_id 
 * @param p_sub_topic 
 * @param p_msg_type 
 * @return error_t 
 */
error_t mqtt_interface_dissect_topic(char* ch_buf, uint32_t buf_len, 
                                            char** p_username, char** p_client_id, 
                                            char** p_sub_topic, uint8_t* p_msg_type);

/**
 * @brief 
 * 
 * @param sub_topic 
 * @return mqtt_interface_status_msg_desc_t* 
 */
const mqtt_interface_status_msg_desc_t* mqtt_interface_get_msg_status_desc
                                                            (const char* sub_topic);

/**
 * @brief 
 * 
 * @param item_id 
 * @return mqtt_interface_status_msg_desc_t* 
 */
const mqtt_interface_status_msg_desc_t* mqtt_interface_get_msg_status_desc_by_id
                                                                    (uint16_t item_id);

/**
 * @brief 
 * 
 * @param sub_topic 
 * @return mqtt_interface_set_msg_desc_t* 
 */
const mqtt_interface_set_msg_desc_t* mqtt_interface_get_msg_set_desc(const char* sub_topic);

/**
 * @brief 
 * 
 * @param sub_topic 
 * @return mqtt_interface_get_msg_desc_t* 
 */
const mqtt_interface_get_msg_desc_t* mqtt_interface_get_msg_get_desc(const char* sub_topic);


#endif