#include "mqtt_component_private.h"
#include "mqtt_interface.h"
#include "data_presentation.h"
#include "types.h"

#include "esp_err.h"
#include "esp_log.h"
#include "esp_event.h"
#include "mqtt_client.h"


#include <stdint.h>
#include <stddef.h>

#define MQTT_COMP_TAG           "MQTT_COMP"

static mqtt_component_param_t  mqtt_component_param;
static mqtt_component_ctrl_t   mqtt_component_ctrl;

static error_t mqtt_component_status_msg_process(void);
static error_t mqtt_component_subscribe(void);
static error_t mqtt_component_process_received(void);
static error_t mqtt_component_data_received(const char* topic, uint16_t topic_len,
                                                const char* data, uint16_t data_len);
static void mqtt_component_run(void* args);


static void mqtt_component_mqtt_event_cb
                    (void* args, esp_event_base_t event_base, int32_t event_id, void* pdata)
{
    esp_mqtt_event_handle_t event_data;

    (void) args;
    event_data = (esp_mqtt_event_handle_t) pdata;

    switch(event_id)
    {
        case MQTT_EVENT_BEFORE_CONNECT:
            ESP_LOGD(MQTT_COMP_TAG, "MQTT connecting.....");
        break;
        case MQTT_EVENT_CONNECTED:
            ESP_LOGD(MQTT_COMP_TAG, "MQTT connected!");
        break;
        case MQTT_EVENT_DISCONNECTED:
            ESP_LOGD(MQTT_COMP_TAG, "MQTT disconnected!");
        break;
        case MQTT_EVENT_SUBSCRIBED:
        break;
        case MQTT_EVENT_UNSUBSCRIBED:   
        break;
        case MQTT_EVENT_PUBLISHED:
        break;
        case MQTT_EVENT_DATA:
            mqtt_component_data_received(event_data->topic, event_data->topic_len,
                                            event_data->data, event_data->data_len);
        break;
        case MQTT_EVENT_ERROR:
        break;
        default:
        break;
    }
}

error_t mqtt_component_get_own_username(char* username, uint16_t size)
{
    mqtt_component_credentials_t* l_p_cred;

    l_p_cred = &mqtt_component_param.credentials;

    if(username && (size >= l_p_cred->username_len))
    {
        memcpy(username, l_p_cred->username, l_p_cred->username_len);

        return RET_OK;
    }

    return RET_FAILED;
}

error_t mqtt_component_get_own_passwd(char* passwd, uint16_t size)
{
    mqtt_component_credentials_t* l_p_cred;

    l_p_cred = &mqtt_component_param.credentials;

    if(passwd && (size >= l_p_cred->passwd_len))
    {
        memcpy(passwd, l_p_cred->passwd, l_p_cred->passwd_len);

        return RET_OK;
    }

    return RET_FAILED;
}

error_t mqtt_component_get_own_credentials(mqtt_component_credentials_t* p_cred)
{
    if(p_cred)
    {
        memcpy(p_cred, &mqtt_component_param.credentials, 
                                    sizeof(mqtt_component_credentials_t));
        return RET_OK;
    }

    return RET_FAILED;
}

error_t mqtt_component_set_own_credentials(const mqtt_component_credentials_t* p_cred)
{
    if(p_cred)
    {
        memcpy(&mqtt_component_param.credentials, p_cred, 
                                    sizeof(mqtt_component_credentials_t));
        return RET_OK;                                    
    }

    return RET_FAILED;
}

error_t mqtt_component_init(void)
{
    memset(&mqtt_component_ctrl, 0, sizeof(mqtt_component_ctrl_t));
    memset(&mqtt_component_param, 0, sizeof(mqtt_component_param_t));

    mqtt_interface_get_msg_desc(&mqtt_component_ctrl.msg_desc);
    data_presentation_protobuf_layer_init(&mqtt_component_ctrl.presentation_layer, 
                                                mqtt_component_ctrl.outbound_payload,
                                                mqtt_component_ctrl.inbound_payload,
                                                sizeof(mqtt_component_ctrl.outbound_payload));
    
    /* The following lines of code are for development purposes only
        and should be deleted once development is doen in MQTT */

    mqtt_component_param.credentials.username_len = sizeof("Mohammed1712");
    memcpy(mqtt_component_param.credentials.username, "Mohammed1712", 
                                        mqtt_component_param.credentials.username_len);
    mqtt_component_param.credentials.passwd_len = sizeof("12345678");
    memcpy(mqtt_component_param.credentials.passwd, "12345678",
                                        mqtt_component_param.credentials.passwd_len);
    memcpy(mqtt_component_ctrl.client_id, "ESP8266", sizeof("ESP8266"));
    memcpy(mqtt_component_ctrl.broker_addr, "192.168.1.100", sizeof("192.168.1.100"));
    mqtt_component_ctrl.broker_port = 1883;

    return RET_OK;
}

error_t mqtt_component_start(void)
{
    esp_mqtt_client_config_t mqtt_client_config;

    memset(&mqtt_client_config, 0, sizeof(esp_mqtt_client_config_t));

    mqtt_client_config.host = mqtt_component_ctrl.broker_addr;
    mqtt_client_config.port = mqtt_component_ctrl.broker_port;
    mqtt_client_config.client_id = mqtt_component_ctrl.client_id;
    mqtt_client_config.username = mqtt_component_param.credentials.username;
    mqtt_client_config.password = mqtt_component_param.credentials.passwd;
    mqtt_client_config.disable_auto_reconnect = 1;
    mqtt_client_config.protocol_ver = MQTT_PROTOCOL_V_3_1_1;

    mqtt_component_ctrl.client_handle = esp_mqtt_client_init(&mqtt_client_config);
    if(mqtt_component_ctrl.client_handle == NULL)
    {
        return RET_FAILED;
    }

    if(esp_mqtt_client_register_event(mqtt_component_ctrl.client_handle, ESP_EVENT_ANY_ID,
                                            mqtt_component_mqtt_event_cb, NULL) != ESP_OK)
    {
        return RET_FAILED;
    }

    if(esp_mqtt_client_start(mqtt_component_ctrl.client_handle) != ESP_OK)
    {
        return RET_FAILED;
    }

    if(mqtt_component_subscribe() != RET_OK)
    {
        return RET_FAILED;
    }

    xTaskCreate(mqtt_component_run, "MQTT_COMP_TSK", MQTT_COMPONENT_TASK_STACK_SIZE, NULL,
                                                        MQTT_COMPONENT_TASK_PRI, NULL);
    return RET_OK;
}

static error_t mqtt_component_status_msg_process(void)
{
    const mqtt_interface_status_msg_desc_t* p_status_msg_desc;
    uint8_t status_msg_desc_size;
    error_t l_ret;

    p_status_msg_desc = mqtt_component_ctrl.msg_desc.status_msg_desc;
    status_msg_desc_size = mqtt_component_ctrl.msg_desc.status_msg_desc_size;
    l_ret = RET_FAILED;

    if(p_status_msg_desc)
    {
        for(uint8_t i = 0; i < status_msg_desc_size; i++)
        {
            if(p_status_msg_desc->publ_type & MQTT_INTERFACE_PUBL_TYPE_PERIODIC)
            {
                mqtt_component_publish(p_status_msg_desc);
            }

            if(p_status_msg_desc->publ_type & MQTT_INTERFACE_PUBL_TYPE_ON_EVENT)
            {
                
            }
        }

        l_ret = RET_OK;
    }

    return l_ret;
}

error_t mqtt_component_publish(const mqtt_interface_status_msg_desc_t* p_status_desc)
{
    data_presentation_layer_t* p_layer;
    error_t l_ret;

    p_layer = &mqtt_component_ctrl.presentation_layer;
    l_ret = RET_FAILED;

    if(p_status_desc->data_id != DATA_PRESENTATION_ITEM_NONE)
    {
        p_layer->item_id = p_status_desc->data_id;

        if(data_presentation_item_read(p_layer) == RET_OK)
        {
            if(mqtt_interface_construct_topic(mqtt_component_ctrl.outbound_topic, 
                                    sizeof(mqtt_component_ctrl.outbound_topic), NULL,
                                    mqtt_component_ctrl.client_id, p_status_desc->topic,
                                    MQTT_INTERFACE_MESSAGE_TYPE_STATUS) != RET_OK)
            {
                return RET_FAILED;
            }

            if(esp_mqtt_client_publish(mqtt_component_ctrl.client_handle, 
                                        (const char*) mqtt_component_ctrl.outbound_topic,
                                        (const char*) mqtt_component_ctrl.outbound_payload,
                                        p_layer->layer_data.protobuf.read_count,
                                        0, 1) < 0)
            {
                return RET_FAILED;
            }

            l_ret = RET_OK;
        }
    }

    return l_ret;
}

static error_t mqtt_component_subscribe(void)
{
    const mqtt_interface_set_msg_desc_t* p_set_msg_desc;
    const mqtt_interface_get_msg_desc_t* p_get_msg_desc;
    const mqtt_interface_cmd_msg_desc_t* p_cmd_msg_desc;

    p_set_msg_desc = mqtt_component_ctrl.msg_desc.set_msg_desc;
    p_get_msg_desc = mqtt_component_ctrl.msg_desc.get_msg_desc;
    p_cmd_msg_desc = mqtt_component_ctrl.msg_desc.cmd_msg_desc;

    /* Subscribe to all 'username/client-id/set/+' messages */
    if(p_set_msg_desc)
    {
        for(uint8_t i = 0; i < mqtt_component_ctrl.msg_desc.set_msg_desc_size; i++)
        {
            if(mqtt_interface_construct_topic(mqtt_component_ctrl.outbound_topic,
                                    sizeof(mqtt_component_ctrl.outbound_topic), NULL,
                                    mqtt_component_ctrl.client_id, p_set_msg_desc->topic,
                                    MQTT_INTERFACE_MESSAGE_TYPE_SET) != RET_OK)
            {
                return RET_FAILED;
            }

            if(esp_mqtt_client_subscribe(mqtt_component_ctrl.client_handle,
                                    mqtt_component_ctrl.outbound_topic, 0) < 0)
            {
                return RET_FAILED;
            }
        }
    }

    /* Subscribe to all 'username/client-id/get/+' messages */
    if(p_get_msg_desc)
    {
        for(uint8_t i = 0; i < mqtt_component_ctrl.msg_desc.get_msg_desc_size; i++)
        {
            if(mqtt_interface_construct_topic(mqtt_component_ctrl.outbound_topic,
                                    sizeof(mqtt_component_ctrl.outbound_topic), NULL,
                                    mqtt_component_ctrl.client_id, p_get_msg_desc->topic,
                                    MQTT_INTERFACE_MESSAGE_TYPE_GET) != RET_OK)
            {
                return RET_FAILED;
            }

            if(esp_mqtt_client_subscribe(mqtt_component_ctrl.client_handle,
                                    mqtt_component_ctrl.outbound_topic, 1) < 0)
            {
                return RET_FAILED;
            }
        }
    }

    /* Subscribe to all 'username/client-id/cmd/+' messages */
    if(p_cmd_msg_desc)
    {
        for(uint8_t i = 0; i < mqtt_component_ctrl.msg_desc.cmd_msg_desc_size; i++)
        {
            if(mqtt_interface_construct_topic(mqtt_component_ctrl.outbound_topic,
                                    sizeof(mqtt_component_ctrl.outbound_topic), NULL,
                                    mqtt_component_ctrl.client_id, p_cmd_msg_desc->topic,
                                    MQTT_INTERFACE_MESSAGE_TYPE_GET) != RET_OK)
            {
                return RET_FAILED;
            }

            if(esp_mqtt_client_subscribe(mqtt_component_ctrl.client_handle,
                                    mqtt_component_ctrl.outbound_topic, 0) < 0)
            {
                return RET_FAILED;
            }
        }
    }

    return RET_OK;
}

static error_t mqtt_component_process_received(void)
{
    char* p_username;
    char* p_client_id;
    char* p_sub_topic;
    uint8_t msg_type;
    const mqtt_interface_status_msg_desc_t* p_status_msg_desc;
    const mqtt_interface_set_msg_desc_t* p_set_msg_desc;
    const mqtt_interface_get_msg_desc_t* p_get_msg_desc;
    error_t l_ret;

    p_username = NULL;
    p_client_id = NULL;
    p_sub_topic = NULL;
    l_ret = RET_FAILED;

    if(mqtt_interface_dissect_topic(mqtt_component_ctrl.inbound_topic, 0, &p_username,
                                                &p_client_id, &p_sub_topic, &msg_type)
                                                                            != RET_OK)
    {
        return RET_FAILED;
    }

    /* TODO: Check username */
    /* TODO: Check client-id */

    switch(msg_type)
    {
        case MQTT_INTERFACE_MESSAGE_TYPE_SET:

            p_set_msg_desc = mqtt_interface_get_msg_set_desc(p_sub_topic);
            if(p_set_msg_desc)
            {
                mqtt_component_ctrl.presentation_layer.item_id = p_set_msg_desc->data_id;
                l_ret = data_presentation_item_write(&mqtt_component_ctrl.presentation_layer);
            }

        break;

        case MQTT_INTERFACE_MESSAGE_TYPE_GET:

            p_get_msg_desc = mqtt_interface_get_msg_get_desc(p_sub_topic);
            if(p_get_msg_desc)
            {
                p_status_msg_desc = 
                        mqtt_interface_get_msg_status_desc_by_id(p_get_msg_desc->data_id);

                if(p_status_msg_desc)
                {
                    l_ret = mqtt_component_publish(p_status_msg_desc);
                }
            }

        break;

        case MQTT_INTERFACE_MESSAGE_TYPE_CMD:
        break;
    }

    return l_ret;
}

static error_t mqtt_component_data_received(const char* topic, uint16_t topic_len,
                                                const char* data, uint16_t data_len)
{
    error_t l_ret;

    l_ret = RET_FAILED;

    if(topic && data)
    {
        if((topic_len <= sizeof(mqtt_component_ctrl.inbound_topic))
                && (data_len <= sizeof(mqtt_component_ctrl.inbound_payload)))
        {
            memcpy(mqtt_component_ctrl.inbound_topic, topic, topic_len);
            memcpy(mqtt_component_ctrl.inbound_payload, data, data_len);

            l_ret = mqtt_component_process_received();
        }
    }

    return l_ret;
}

void mqtt_component_run(void* args)
{
    (void) args;

    while(1)
    {
        if(mqtt_component_status_msg_process() != RET_OK)
        {
            break;
        }

        vTaskDelay(2000 / portTICK_PERIOD_MS);
    }

    vTaskDelete(NULL);
}