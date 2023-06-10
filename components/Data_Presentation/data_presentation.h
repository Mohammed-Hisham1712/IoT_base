#ifndef __DATA_PRESENTATION_H__

#define __DATA_PRESENTATION_H__

#include "data_presentation_public.h"

#include "types.h"
#include "protobuffer.h"

#include <stdint.h>

enum
{
    DATA_PRESENTATION_RAW,
    DATA_PRESENTATION_PROTOBUF,
};

typedef struct
{
    uint8_t protocol;
    uint16_t item_id;
    union
    {
        protobuffer_data_t protobuf;
    } layer_data;
    
} data_presentation_layer_t;


/**
 * @brief 
 * 
 * @param layer
 * @param protocol 
 * @return error_t 
 */
error_t data_presentation_init(data_presentation_layer_t* layer, uint8_t protocol);

/**
 * @brief 
 * 
 * @param layer 
 * @param pbuffer 
 * @param size 
 * @return error_t 
 */
error_t data_presentation_protobuf_layer_init(data_presentation_layer_t* layer, 
                                            void* p_read_buffer, void* p_write_buffer,
                                            uint16_t read_buffer_size);

/**
 * @brief 
 * 
 * @param layer 
 * @return error_t 
 */
error_t data_presentation_item_read(data_presentation_layer_t* layer);

/**
 * @brief 
 * 
 * @param layer 
 * @return error_t 
 */
error_t data_presentation_item_write(data_presentation_layer_t* layer);

#endif