 #ifndef NV_SLOW_PARAM_STRUCT 
 #define NV_SLOW_PARAM_STRUCT 
 
#include "types.h" 
 
#include "wifi_component_param.h"


typedef struct  
{ 
    uint32_t first_run_key_1; 
    uint32_t first_run_key_2; 
 
    wifi_component_param_t wifi_param;

}system_param_slow_t; 
 
 
 
 
 #endif 
 
  