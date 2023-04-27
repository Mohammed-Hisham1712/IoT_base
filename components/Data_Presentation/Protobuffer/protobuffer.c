#include "protobuffer.h"

#include "data_presentation.pb-c.h"
#include "data_presentation_public.h"
#include "types.h"

#include "esp_log.h"

#include <stdint.h>
#include <stddef.h>


#define PROTOBUFFER_TAG     "PROTOBUFFER"

/************** PRIVATE FUNCTIONS *******************/

error_t protobuffer_led_state_read(protobuffer_data_t* p_proto_data);
error_t protobuffer_led_state_write(protobuffer_data_t* p_proto_data);



/*************** GLOBAL DATA **********************/

uint8_t led_state;  // Used for testing

static protobuffer_item_desc_t protobuffer_item_desc[] = 
{
    {
        DATA_PRESENTATION_LED_STATE_ID,
        protobuffer_led_state_read,
        protobuffer_led_state_write
    },
};

#define PROTOBUFFER_ITEM_DESC_SIZE \
              (sizeof(protobuffer_item_desc) / sizeof(protobuffer_item_desc_t))




/************* PRIVATE FUNCTIONS ****************/

error_t protobuffer_led_state_read(protobuffer_data_t* p_proto_data)
{
    ProtoBufferLedState protobuffer_led_state;
    size_t packed_size;
    error_t l_ret;

    l_ret = RET_FAILED;

    if(p_proto_data && p_proto_data->p_read_buffer && p_proto_data->read_buffer_size)
    {
        proto_buffer_led_state__init(&protobuffer_led_state);
        
        if(led_state)
        {
            protobuffer_led_state.led_state = LED_STATES__LED_STATE_ON;
        }
        else
        {
            protobuffer_led_state.led_state = LED_STATES__LED_STATE_OFF;
        }

        packed_size = proto_buffer_led_state__get_packed_size(&protobuffer_led_state);

        if(p_proto_data->read_buffer_size >= packed_size)
        {
            if(proto_buffer_led_state__pack(&protobuffer_led_state, 
                                            p_proto_data->p_read_buffer))
            {
                ESP_LOGD(PROTOBUFFER_TAG, "%d bytes read", packed_size);
                p_proto_data->read_count = packed_size;
                l_ret = RET_OK;
            }
        }
    }

    return l_ret;
}

error_t protobuffer_led_state_write(protobuffer_data_t* p_proto_data)
{
    ProtoBufferLedState* p_protobuffer_led_state;
    error_t l_ret;

    p_protobuffer_led_state = NULL;
    l_ret = RET_FAILED;

    if(p_proto_data && p_proto_data->p_write_buffer && p_proto_data->write_count)
    {
        p_protobuffer_led_state = proto_buffer_led_state__unpack(NULL, p_proto_data->write_count, 
                                                                    p_proto_data->p_write_buffer);

        if(p_protobuffer_led_state)
        {
            if(p_protobuffer_led_state->led_state == LED_STATES__LED_STATE_ON)
            {
                led_state = 1;
            }
            else
            {
                led_state = 0;
            }

            proto_buffer_led_state__free_unpacked(p_protobuffer_led_state, NULL);
            
            l_ret = RET_OK;
        }
    }

    return l_ret;
}



/************ PUBLIC FUNCTIONS *******************/

error_t protobuffer_item_write(uint16_t item_id, protobuffer_data_t* p_proto_data)
{
    protobuffer_item_desc_t* p_desc;
    error_t l_ret;

    p_desc = protobuffer_get_desc_by_id(item_id);
    l_ret = RET_FAILED;

    if(p_desc && p_proto_data)
    {
        if(p_desc->write_item)
        {
            l_ret = p_desc->write_item(p_proto_data);
        }
    }

    return l_ret;
}

error_t protobuffer_item_read(uint16_t item_id, protobuffer_data_t* p_proto_data)
{
    protobuffer_item_desc_t* p_desc;
    error_t l_ret;

    p_desc = protobuffer_get_desc_by_id(item_id);
    l_ret = RET_FAILED;

    if(p_desc && p_proto_data)
    {
        if(p_desc->read_item)
        {
            ESP_LOGD(PROTOBUFFER_TAG, "Calling read handler for item [%d]", item_id);

            l_ret = p_desc->read_item(p_proto_data);
        }
    }

    return l_ret;
}

int32_t protobuffer_get_index_by_id(uint16_t item_id)
{
    int32_t indx = -1;

    for(uint16_t i = 0; i < PROTOBUFFER_ITEM_DESC_SIZE; i++)
    {
        if(protobuffer_item_desc[i].item_id == item_id)
        {
            indx = i;
            break;
        }
    }

    return indx;
}

protobuffer_item_desc_t* protobuffer_get_desc_by_id(uint16_t item_id)
{
    protobuffer_item_desc_t* p_desc;

    p_desc = NULL;

    for(uint16_t i = 0; i < PROTOBUFFER_ITEM_DESC_SIZE; i++)
    {
        if(protobuffer_item_desc[i].item_id == item_id)
        {
            p_desc = &protobuffer_item_desc[i];
            break;
        }
    }

    return p_desc;
}
