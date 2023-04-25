#include "data_presentation.h"
#include "protobuffer.h"

#include "types.h"

#include <stdint.h>
#include <stddef.h>

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
            layer->buffer.p_protobuf = NULL;
            l_ret = RET_OK;
        }
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
            l_ret = protobuffer_item_read(layer->item_id, layer->buffer.p_protobuf);
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
            l_ret = protobuffer_item_write(layer->item_id, layer->buffer.p_protobuf);
        }
    }

    return l_ret;
}