#include "comp_mang_def.h"                         
#include "debug_uart.h"                         
                         
component_manager_node_t * Node[LAST_MODULE] ;                         
                         
                         
BOOL component_manager_attach_node( components_id_t  c_module_id , component_manager_node_t * node  )                         
{                         
    char ret  ;                         
    if ( c_module_id < LAST_MODULE )                         
    {                         
        Node[c_module_id] = node ;                         
        ret = TRUE ;                         
    }                         
    else                          
    {                         
        /* set error log */                         
    	ret = FALSE ;                         
    }                         
    return ret ;                         
}                         
                         
                         
                         
BOOL component_manager_set(components_id_t c_module_id , set_id_t c_set_id , void * cp_data )                         
{                         
    BOOL ret;                         
    if ( ( c_module_id < LAST_MODULE ) && (Node[c_module_id] != 0) )                         
    {                         
        Node[c_module_id]->set(c_set_id , cp_data) ;                         
        ret = TRUE ;                         
    }                         
    else                          
    {                            
        /* set error log */                         
        ret = FALSE;                         
    }                           
    return ret;                         
}                         
                         
                         
                         
                         
BOOL component_manager_request(components_id_t c_module_id , request_id_t c_request_id , ARGS * args )                         
{                         
    BOOL ret;                         
    if ( ( c_module_id < LAST_MODULE ) && (Node[c_module_id] != 0) )                         
    {                         
        Node[c_module_id]->request(c_request_id , args) ;                         
        ret = TRUE;                         
    }                         
    else                          
    {                         
        /* set error log */                         
        ret = FALSE;                         
    }                         
    return ret;                         
}                         
                         
                         
                         
                         
                         
BOOL component_manager_get(components_id_t c_module_id , get_id_t c_get_id , void * cp_data){                         
                         
    BOOL ret;                         
    if ( ( c_module_id < LAST_MODULE ) && (Node[c_module_id] != 0) )                         
    {                         
        Node[c_module_id]->get(c_get_id , cp_data) ;                         
        ret = TRUE;                         
    }                         
    else                          
    {                         
        /* set error log */                         
        ret = FALSE;                         
    }                         
    return ret;                         
}                         
