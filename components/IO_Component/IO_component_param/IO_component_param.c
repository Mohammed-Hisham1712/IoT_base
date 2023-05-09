#include "IO_component_param.h"
#include "system_param_itf.h"


BOOL IO_comp_param_read(int32_t offset, int32_t size, void * buffer)
{
    BOOL ret ;
    int8_t  partition = IO_COMP_PARTITION ;
    int32_t offset = offset_of(IO_COMP_STRUCT,IO_comp_param) ;
    int32_t data_size= sizeof(IO_component_param_t);
    IO_component_param_t IO_comp_param;

    /* Check data validation */

    /* read data from NV memory */
    EXECUTE(SYSTEM_PARAM,
            SYSTEM_PARAM_READ, 
            &ret,
            &partition,
            &offset,
            &data_size,
            buffer);

    /* Save new data to the memory */

    /* write data to NV memory */
    

}
BOOL IO_comp_param_write(int32_t offset, int32_t size, void * buffer)
{

}
BOOL IO_comp_param_init()
{

}
BOOL IO_comp_param_first_run()
{

}
BOOL IO_comp_param_check_crc()
{

}

