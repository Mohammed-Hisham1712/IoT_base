 #ifndef NV_FAST_PARAM_STRUCT 
 #define NV_FAST_PARAM_STRUCT 

#include "system_include.h"

#if CONFIG_IO_COMPONENT_INCLUDED
#include "IO_component_param.h"
#endif  /* CONFIG_IO_COMPONENT_INCLUDED */ 


typedef struct  
{ 
    uint32_t first_run_key_1; 
    uint32_t first_run_key_2; 
    int32_t partition_counter; 

    #if CONFIG_IO_COMPONENT_INCLUDED
    IO_component_param_t IO_comp_param;
    #endif /* CONFIG_IO_COMPONENT_INCLUDED */ 

    
}system_param_fast_t; 
 
 
 #endif 
 
  