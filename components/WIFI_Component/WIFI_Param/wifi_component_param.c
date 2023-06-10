#include "wifi_component_param.h"

#include "system_param_itf.h"
#include "types.h"

#include <stdint.h>
#include <stddef.h>
#include <string.h>



error_t wifi_param_read(uint16_t offset, uint16_t size, void* p_buffer)
{
    wifi_component_param_t l_param;
    int8_t l_partition;
    int32_t l_size;
    int32_t l_offset;
    BOOL l_ret;

    l_partition = WIFI_COMP_PARTITION;
    l_size = sizeof(wifi_component_param_t);
    l_offset = offset_of(WIFI_COMP_STRUCT, wifi_param);
    l_ret = FALSE;

    if(p_buffer && ((offset + size) <= sizeof(wifi_component_param_t)))
    {
        EXECUTE(SYSTEM_PARAM, SYSTEM_PARAM_READ, &l_ret, 
                                &l_partition, &l_offset, &l_size, (void*) &l_param);
        
        if(l_ret)
        {
            memcpy(p_buffer, (void*) ((&l_param) + offset), size);
        }
    }

    return l_ret ? RET_OK : RET_FAILED;
}


error_t wifi_param_write(uint16_t offset, uint16_t size, void* p_buffer)
{
    wifi_component_param_t l_param;
    int8_t l_partition;
    int32_t l_size;
    int32_t l_offset;
    BOOL l_ret;

    l_partition = WIFI_COMP_PARTITION;
    l_size = sizeof(wifi_component_param_t);
    l_offset = offset_of(WIFI_COMP_STRUCT, wifi_param);
    l_ret = FALSE;

    if(p_buffer && ((offset + size) <= sizeof(wifi_component_param_t)))
    {
        EXECUTE(SYSTEM_PARAM, SYSTEM_PARAM_READ, &l_ret,
                                &l_partition, &l_offset, &l_size, (void*) &l_param);

        if(l_ret)
        {
            memcpy((void*) ((&l_param) + offset), p_buffer, size);

            EXECUTE(SYSTEM_PARAM, SYSTEM_PARAM_WRITE, &l_ret,
                                    &l_partition, &l_offset, &l_size, (void*) &l_param);
        }
    }

    return l_ret ? RET_OK : RET_FAILED;
}

error_t wifi_param_load(wifi_component_param_t* p_param)
{
    int8_t l_partition;
    int32_t l_size;
    int32_t l_offset;
    BOOL l_ret;

    l_partition = WIFI_COMP_PARTITION;
    l_size = sizeof(wifi_component_param_t);
    l_offset = offset_of(WIFI_COMP_STRUCT, wifi_param);
    l_ret = FALSE;

    if(p_param)
    {
        EXECUTE(SYSTEM_PARAM, SYSTEM_PARAM_READ, &l_ret,
                                &l_partition, &l_offset, &l_size, (void*) p_param);
    }

    return l_ret ? RET_OK : RET_FAILED;
}

error_t wifi_param_store(wifi_component_param_t* p_param)
{
    int8_t l_partition;
    int32_t l_size;
    int32_t l_offset;
    BOOL l_ret;

    l_partition = WIFI_COMP_PARTITION;
    l_size = sizeof(wifi_component_param_t);
    l_offset = offset_of(WIFI_COMP_STRUCT, wifi_param);
    l_ret = FALSE;

    if(p_param)
    {
        EXECUTE(SYSTEM_PARAM, SYSTEM_PARAM_WRITE, &l_ret,
                                &l_partition, &l_offset, &l_size, (void*) p_param);
    }

    return l_ret ? RET_OK : RET_FAILED;
}