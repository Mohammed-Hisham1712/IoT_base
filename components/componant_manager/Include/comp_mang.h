#ifndef NERVIOUS_SYSTEM_H 
#define NERVIOUS_SYSTEM_H 
 
#include "comp_mang.h" 
#include "types.h" 
 
 
 
 
 
typedef struct args  
{ 
    void * ret ; 
    void * param_1 ; 
    void * param_2 ; 
    void * param_3 ;  
    void * param_4 ; 
    void * param_5 ; 
    void * param_6 ; 
}ARGS; 
 
typedef void (* function_set_ptr) ( int , void * ) ; 
typedef void (* function_get_ptr) ( int , void * ) ; 
typedef void (* function_request_ptr) ( int , ARGS * ) ; 
 
 
 
typedef struct Componant 
{ 
    function_set_ptr     set ; 
    function_get_ptr     get ; 
    function_request_ptr request ; 
}component_manager_node_t ; 
 
typedef enum  
{ 
    IO_COMPONENT , 
    SYSTEM_PARAM , 
    MQTT_COMPONENT , 
    /* Must be at the last*/ 
    LAST_MODULE  
}components_id_t ; 
 
 
BOOL component_manager_set ( components_id_t , get_id_t , void *  ) ; 
 
BOOL component_manager_get ( components_id_t , set_id_t , void * ) ; 
 
BOOL component_manager_request (  components_id_t , request_id_t , ARGS *   ) ; 
 
BOOL component_manager_attach_node ( components_id_t , component_manager_node_t *node  ) ; 
 
#endif 
 
 
