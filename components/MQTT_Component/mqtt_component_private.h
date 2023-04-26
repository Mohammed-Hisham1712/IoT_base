#ifndef __MQTT_COMPONENT_PRIVATE_H__

#define __MQTT_COMPONENT_PRIVATE_H__

#include "mqtt_component_public.h"
#include "mqtt_interface.h"
#include "data_presentation.h"
#include "mqtt_client.h"

#include "types.h"

#include <stdint.h>

#define MQTT_COMPONENT_CLIENT_ID_SIZE       32
#define MQTT_COMPONENT_HOST_IP_SIZE         16
#define MQTT_COMPONENT_MAX_PAYLOAD_SIZE     192
#define MQTT_COMPONENT_MAX_TOPIC_SIZE       128
           


typedef struct 
{
    mqtt_component_credentials_t credentials;
} mqtt_component_param_t;

typedef struct
{
    char client_id[MQTT_COMPONENT_CLIENT_ID_SIZE];
    char broker_addr[MQTT_COMPONENT_HOST_IP_SIZE];
    char inbound_topic[MQTT_COMPONENT_MAX_TOPIC_SIZE];
    char outbound_topic[MQTT_COMPONENT_MAX_TOPIC_SIZE];
    uint8_t outbound_payload[MQTT_COMPONENT_MAX_PAYLOAD_SIZE];
    uint8_t inbound_payload[MQTT_COMPONENT_MAX_PAYLOAD_SIZE];
    mqtt_interface_msg_desc_t msg_desc;
    data_presentation_layer_t presentation_layer;
    uint16_t broker_port;
    esp_mqtt_client_handle_t client_handle;
} mqtt_component_ctrl_t;


/**
 * @brief 
 * 
 * @param p_status_desc 
 * @return error_t 
 */
error_t mqtt_component_publish(const mqtt_interface_status_msg_desc_t* p_status_desc);


#endif