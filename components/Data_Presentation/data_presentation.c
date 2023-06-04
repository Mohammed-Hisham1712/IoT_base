#include "data_presentation.h"
#include "protobuffer.h"
#include "types.h"

#include "esp_log.h"

#include <stdint.h>
#include <stddef.h>

#define DATA_PRESENTATION_TAG   "DATA_PRESENTATION"


error_t data_presentation_init(data_presentation_layer_t* layer, uint8_t protocol)
{
    error_t l_ret;

    l_ret = RET_FAILED;

    if(layer)
    {
        layer->item_id = DATA_PRESENTATION_ITEM_NONE;

        if(protocol == DATA_PRESENTATION_RAW)
        {
            layer->protocol = DATA_PRESENTATION_RAW;
            l_ret = RET_OK;
        }
        else if(protocol == DATA_PRESENTATION_PROTOBUF)
        {
            layer->protocol = DATA_PRESENTATION_PROTOBUF;
            layer->layer_data.protobuf.p_read_buffer = NULL;
            layer->layer_data.protobuf.p_write_buffer = NULL;
            layer->layer_data.protobuf.read_buffer_size = 0;
            layer->layer_data.protobuf.read_count = 0;
            layer->layer_data.protobuf.write_count = 0;
            l_ret = RET_OK;
        }
    }

    return l_ret;
}

error_t data_presentation_protobuf_layer_init(data_presentation_layer_t* layer, 
                                            void* p_read_buffer, void* p_write_buffer,
                                            uint16_t read_buffer_size)
{
    error_t l_ret;

    l_ret = RET_FAILED;

    if(layer)
    {
        data_presentation_init(layer, DATA_PRESENTATION_PROTOBUF);

        layer->layer_data.protobuf.p_read_buffer = p_read_buffer;
        layer->layer_data.protobuf.p_write_buffer = p_write_buffer;
        layer->layer_data.protobuf.read_buffer_size = read_buffer_size;

        l_ret = RET_OK;
    }

    return l_ret;
}

error_t data_presentation_item_read(data_presentation_layer_t* layer)
{
    error_t l_ret;

    l_ret = RET_FAILED;

    if(layer)
    {
        if(layer->protocol == DATA_PRESENTATION_RAW)
        {
            l_ret = RET_OK;
        }
        else if(layer->protocol == DATA_PRESENTATION_PROTOBUF)
        {
            ESP_LOGD(DATA_PRESENTATION_TAG, "Reading item [%d] from protobuf", layer->item_id);
            
            l_ret = protobuffer_item_read(layer->item_id, &layer->layer_data.protobuf);
        }
    }

    return l_ret;
}

error_t data_presentation_item_write(data_presentation_layer_t* layer)
{
    error_t l_ret;

    l_ret = RET_FAILED;

    if(layer)
    {
        if(layer->protocol == DATA_PRESENTATION_RAW)
        {
            l_ret = RET_OK;
        }
        else if(layer->protocol == DATA_PRESENTATION_PROTOBUF)
        {
            l_ret = protobuffer_item_write(layer->item_id, &layer->layer_data.protobuf);
        }
    }

    return l_ret;
}