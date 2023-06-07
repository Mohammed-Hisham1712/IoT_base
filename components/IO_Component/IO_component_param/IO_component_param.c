#include "IO_component_param.h"
#include "system_param_itf.h"
#include <string.h>
#include "IO_component_param_cfg.h"

#ifdef IO_COMP_PARAM_CONFIG_DEBUG
#include "debug_uart.h"
#endif

BOOL IO_comp_param_read(int32_t c_offset, int32_t size, void * buffer)
{
    BOOL ret ;
    int8_t  partition = IO_COMP_PARTITION ;
    int32_t l_offset = offset_of(IO_COMP_STRUCT,IO_comp_param) ;
    int32_t data_size= sizeof(IO_component_param_t);
    IO_component_param_t IO_comp_param;

    /* Check data validation */
#if debug_IO_comp_param_read
debug("begin of io param write %d",1);
#endif
    if( ( c_offset+size ) <= sizeof(IO_component_param_t) ) 
    {
        #if debug_IO_comp_param_read
        debug("trey to read io param %d",1);
        #endif
        /* read data from NV memory */
        EXECUTE(SYSTEM_PARAM,
                SYSTEM_PARAM_READ, 
                &ret,
                &partition,
                &l_offset,
                &data_size,
                &IO_comp_param);

        /* Save new data to the memory */
        if(ret)
        {
            #if debug_IO_comp_param_read
            debug("read success and copy data %d",1);
            #endif
            memcpy(buffer,((int8_t*)&IO_comp_param)+c_offset,size);
        }
        else 
        {
            #if debug_IO_comp_param_read
            debug("read failed %d",1);
            #endif
        }
    }
    else 
    {
        #if debug_IO_comp_param_read
        debug("wrong data to write %d",1);
        #endif
        ret = FALSE ;
    }
    return TRUE;
}
BOOL IO_comp_param_write(int32_t c_offset, int32_t size, void * buffer)
{
    BOOL ret ;
    int8_t  partition = IO_COMP_PARTITION ;
    int32_t l_offset = offset_of(IO_COMP_STRUCT,IO_comp_param) ;
    int32_t data_size= sizeof(IO_component_param_t);
    IO_component_param_t IO_comp_param;
    #if debug_IO_comp_param_write
    debug("\r\nenter io param write %d",1);
    #endif
    /* Check data validation */
    if( ( c_offset+size ) <= sizeof(IO_component_param_t) ) 
    {
        #if debug_IO_comp_param_write
        debug("\r\ntry to write data %d",1);
        #endif
        /* read data from NV memory */
        EXECUTE(SYSTEM_PARAM,
                SYSTEM_PARAM_READ, 
                &ret,
                &partition,
                &l_offset,
                &data_size,
                &IO_comp_param);

        /* Save new data to the memory */
        if(ret)
        {
            #if debug_IO_comp_param_write
            debug("\r\nread success copy write data %d",1);
            #endif
            memcpy(((int8_t*)&IO_comp_param)+c_offset,buffer,size);
        }
        if(ret)
        {
            /* write data to NV memory */
            EXECUTE(SYSTEM_PARAM,
                    SYSTEM_PARAM_WRITE, 
                    &ret,
                    &partition,
                    &l_offset,
                    &data_size,
                    &IO_comp_param);
        }
        if(ret)
        {
            #if debug_IO_comp_param_write
            debug("\r\nwrite success to io param  %d",1);
            #endif
        }
        else 
        {
            #if debug_IO_comp_param_write
            debug("\r\nwrite data failed %d",1);
            #endif
        }
    }
    else 
    {
        #if debug_IO_comp_param_write
        debug("\r\nwrong data to write %d",1);
        #endif
        ret = FALSE ;
    }
    return ret;
}
BOOL IO_comp_param_init()
{
    return TRUE;
}   
BOOL IO_comp_param_first_run()
{
    return TRUE;

}
BOOL IO_comp_param_check_crc()
{
    return TRUE;

}

