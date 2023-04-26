#include "mqtt_interface.h"

#include "data_presentation_public.h"
#include "types.h"

#include <stdint.h>
#include <stddef.h>
#include <string.h>

mqtt_interface_status_msg_desc_t mqtt_status_message_desc[] = 
{
    {
        "led_state",
        DATA_PRESENTATION_LED_STATE_ID,
        MQTT_INTERFACE_PUBL_TYPE_PERIODIC,
        0
    }
};

#define MQTT_STATUS_MESSAGE_DESC_SIZE \
           (sizeof(mqtt_status_message_desc) / sizeof(mqtt_interface_status_msg_desc_t))


mqtt_interface_set_msg_desc_t mqtt_set_message_desc[] = 
{
    {
        "led_state",
        DATA_PRESENTATION_LED_STATE_ID
    }
};

#define MQTT_SET_MESSAGE_DESC_SIZE \
             (sizeof(mqtt_set_message_desc) / sizeof(mqtt_interface_set_msg_desc_t))

mqtt_interface_get_msg_desc_t mqtt_get_message_desc[] =
{
    {
        "led_state",
        DATA_PRESENTATION_LED_STATE_ID
    }
};

#define MQTT_GET_MESSAGE_DESC_SIZE \
              (sizeof(mqtt_get_message_desc) / sizeof(mqtt_interface_get_msg_desc_t))


static const char* mqtt_interface_msg_types[MQTT_INTERFACE_MESSAGE_TYPE_MAX] = 
{
    "status",
    "set",
    "get",
    "cmd"
};


error_t mqtt_interface_construct_topic(char* ch_buf, uint32_t buf_len, const char* username, 
                            const char* client_id, const char* sub_topic, uint8_t msg_type)
{
    /*
        Construct a whole topic from different components.
        Topics be like. username/client-Id/msg_type/sup_topic
    */

    const char* msg_type_str;
    char* l_buf;
    uint8_t copy_len;
    error_t l_ret;

    l_buf = ch_buf;
    msg_type_str = NULL;
    copy_len = 0;
    l_ret = RET_FAILED;

    if(msg_type < MQTT_INTERFACE_MESSAGE_TYPE_MAX)
    {
        msg_type_str = mqtt_interface_msg_types[msg_type];
    }

    if(ch_buf && (buf_len > 0))
    {
        if(username && client_id && sub_topic && msg_type_str)
        {   
            /* Copy username into buffer. Includes '/' in calculation */
            copy_len = strlen(username);
            if(buf_len >= copy_len + 1)
            {
                memcpy(l_buf, username, copy_len);
                l_buf += copy_len;
                *l_buf = '/';
                ++l_buf;
                buf_len -= (copy_len + 1);
            }
            else
            {
                return RET_FAILED;
            }

            /* Copy client-id into buffer. Includes '/' in calculation */
            copy_len = strlen(client_id);
            if(buf_len >= copy_len + 1)
            {
                memcpy(l_buf, client_id, copy_len);
                l_buf += copy_len;
                *l_buf = '/';
                ++l_buf;
                buf_len -= (copy_len + 1);
            }
            else
            {
                return RET_FAILED;
            }

            /* Copy message-type into buffer. Includes '/' in calculation */
            copy_len = strlen(msg_type_str);
            if(buf_len >= copy_len + 1)
            {
                memcpy(l_buf, msg_type_str, copy_len);
                l_buf += copy_len;
                *l_buf = '/';
                ++l_buf;
                buf_len -= (copy_len + 1);
            }
            else
            {
                return RET_FAILED;
            }

            /* Copy sub-topic into buffer. Include '\0' in calculation */
            copy_len = strlen(sub_topic);
            if(buf_len >= copy_len + 1)
            {
                memcpy(l_buf, sub_topic, copy_len);
                l_buf += copy_len;
                *l_buf = '\0';
            }
            else
            {
                return RET_FAILED;
            }

            l_ret = RET_OK;
        }
    }

    return l_ret;
}

error_t mqtt_interface_dissect_topic(char* ch_buf, uint32_t buf_len, 
                                            char** p_username, char** p_client_id, 
                                            char** p_sub_topic, uint8_t* p_msg_type)
{
    /*
        Dissect topic into its components.
        Topics be like. username/client-Id/msg_type/sup_topic
        Warning: ch_buf is modified such that each '/' encountered is
        replaced with NULL characted.
    */

    char* l_buf;
    char* p_topic_type;
    error_t l_ret;

    l_buf = ch_buf;
    l_ret = RET_FAILED;

    if(ch_buf && (buf_len > 0))
    {
        if(p_username && p_client_id && p_sub_topic && p_msg_type)
        {
            *p_username = l_buf;

            /* Find Client-Id in string topic.
                Update l_buf to find the next '/'
                Put a null character at the end of username */
            *p_client_id = strchr(l_buf, '/');
            if(*p_client_id)
            {
                **p_client_id = '\0';
                *p_client_id += 1;
                l_buf = *p_client_id;
            }
            else
            {
                return RET_FAILED;
            }

            /* Find message type part of the topic.
                Update l_buf to find the next '/'
                Replace '/' with '\0' to terminate client_id */
            p_topic_type = strchr(l_buf, '/');
            if(p_topic_type)
            {
                *p_topic_type = '\0';
                p_topic_type += 1;
                l_buf = p_topic_type;
            }
            else
            {
                return RET_FAILED;
            }

            /* Find sub-topic part of the topic
                Replace '/' with '\0' to terminate msg-type */
            *p_sub_topic = strchr(l_buf, '/');
            if(*p_sub_topic)
            {
                **p_sub_topic = '\0';
                *p_sub_topic += 1;
            }
            else
            {
                return RET_FAILED;
            }

            /* Convert msg-type from string to enum type */
            *p_msg_type = MQTT_INTERFACE_MESSAGE_TYPE_MAX;
            for(uint8_t i = 0; i < MQTT_INTERFACE_MESSAGE_TYPE_MAX; i++)
            {
                if(strcmp(*p_sub_topic, mqtt_interface_msg_types[i]) == 0)
                {
                    *p_msg_type = i;
                    break;
                }
            }

            if(MQTT_INTERFACE_MESSAGE_TYPE_MAX != *p_msg_type)
            {
                l_ret = RET_OK;
            }
        }
    }

    return l_ret;
}

const mqtt_interface_status_msg_desc_t* mqtt_interface_get_msg_status_desc
                                                            (const char* sub_topic)
{
    mqtt_interface_status_msg_desc_t* p_desc;

    p_desc = NULL;

    if(sub_topic)
    {
        for(uint16_t i = 0; i < MQTT_STATUS_MESSAGE_DESC_SIZE; i++)
        {
            if(strcmp(sub_topic, mqtt_status_message_desc[i].topic) == 0)
            {
                p_desc = &mqtt_status_message_desc[i];
                break;
            }
        }
    }

    return p_desc;
}

const mqtt_interface_status_msg_desc_t* mqtt_interface_get_msg_status_desc_by_id
                                                                    (uint16_t item_id)
{
    mqtt_interface_status_msg_desc_t* p_desc;

    p_desc = NULL;

    if(item_id != DATA_PRESENTATION_ITEM_NONE)
    {
        for(uint16_t i = 0; i < MQTT_STATUS_MESSAGE_DESC_SIZE; i++)
        {
            if(item_id == mqtt_status_message_desc[i].data_id)
            {
                p_desc = &mqtt_status_message_desc[i];
                break;
            }
        }
    }

    return p_desc;
}

const mqtt_interface_set_msg_desc_t* mqtt_interface_get_msg_set_desc(const char* sub_topic)
{
    mqtt_interface_set_msg_desc_t* p_desc;

    p_desc = NULL;

    if(sub_topic)
    {
        for(uint16_t i = 0; i < MQTT_SET_MESSAGE_DESC_SIZE; i++)
        {
            if(strcmp(sub_topic, mqtt_set_message_desc[i].topic) == 0)
            {
                p_desc = &mqtt_set_message_desc[i];
                break;
            }
        }
    }

    return p_desc;
}

const mqtt_interface_get_msg_desc_t* mqtt_interface_get_msg_get_desc(const char* sub_topic)
{
    mqtt_interface_get_msg_desc_t* p_desc;

    p_desc = NULL;

    if(sub_topic)
    {
        for(uint16_t i = 0; i < MQTT_GET_MESSAGE_DESC_SIZE; i++)
        {
            if(strcmp(sub_topic, mqtt_get_message_desc[i].topic) == 0)
            {
                p_desc = &mqtt_get_message_desc[i];
                break;
            }
        }
    }

    return p_desc;
}

error_t mqtt_interface_get_msg_desc(mqtt_interface_msg_desc_t* p_desc)
{
    error_t l_ret;

    l_ret = RET_FAILED;

    if(p_desc)
    {
        p_desc->status_msg_desc = mqtt_status_message_desc;
        p_desc->status_msg_desc_size = MQTT_STATUS_MESSAGE_DESC_SIZE;

        p_desc->set_msg_desc = mqtt_set_message_desc;
        p_desc->set_msg_desc_size = MQTT_SET_MESSAGE_DESC_SIZE;

        p_desc->get_msg_desc = mqtt_get_message_desc;
        p_desc->get_msg_desc_size = MQTT_GET_MESSAGE_DESC_SIZE;

        p_desc->cmd_msg_desc = NULL;
        p_desc->cmd_msg_desc_size = 0;

        l_ret = RET_OK;
    }

    return l_ret;
}