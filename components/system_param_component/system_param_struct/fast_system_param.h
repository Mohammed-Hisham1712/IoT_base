 #ifndef NV_FAST_PARAM_STRUCT                                            
 #define NV_FAST_PARAM_STRUCT                                            
                                            
#include "types.h"                                            
#include "IO_component_param.h"                                            
                                            
                                            
typedef struct                                             
{                                            
    uint32_t first_run_key_1;                                            
    uint32_t first_run_key_2;                                            
    int32_t partition_counter;                                            
    int32_t test_data_2;                                            
    float   test_data_3;                                            
    char x[152];                                            
    float z[15];                                            
    int32_t test_data_1;                                            
    IO_component_param_t IO_comp_param;                                            
                                            
}system_param_fast_t;                                            
                                            
                                            
 #endif                                            
                                            
                                             