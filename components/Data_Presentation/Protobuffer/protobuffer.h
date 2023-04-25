#ifndef __PROTOBUFFER_H__

#define __PROTOBUFFER_H__

#include "types.h"

#include "stdint.h"

typedef struct protobuffer_data_t protobuffer_data_t;

typedef error_t (*protobuffer_read_handler_t) (protobuffer_data_t* p_proto_data);
typedef error_t (*protobuffer_write_handler_t) (protobuffer_data_t* p_proto_data);

struct protobuffer_data_t
{
    void* pdata;
    uint16_t len;
};

typedef struct
{
    uint16_t item_id;
    protobuffer_read_handler_t read_item;
    protobuffer_write_handler_t write_item;
} protobuffer_item_desc_t;

/**
 * @brief 
 * 
 * @param item_id 
 * @param p_proto_data 
 * @return error_t 
 */
error_t protobuffer_item_read(uint16_t item_id, protobuffer_data_t* p_proto_data);

/**
 * @brief 
 * 
 * @param item_id 
 * @param p_proto_data 
 * @return error_t 
 */
error_t protobuffer_item_write(uint16_t item_id, protobuffer_data_t* p_proto_data);

/**
 * @brief 
 * 
 * @param item_id 
 * @return uint16_t 
 */
int32_t protobuffer_get_index_by_id(uint16_t item_id);

/**
 * @brief 
 * 
 * @param item_id 
 * @return protobuffer_item_desc_t* 
 */
protobuffer_item_desc_t* protobuffer_get_desc_by_id(uint16_t item_id);

#endif