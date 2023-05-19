#ifndef SYSTEM_PARAM_INTERFACE_H
#define SYSTEM_PARAM_INTERFACE_H

// #include "comp_mang.h"
#include "comp_mang_def.h"
#include "system_param_defintions.h"
#include "system_param_public.h"

typedef enum
{
    NO_SET,
}SYSTEM_PARAM_SET_ID;

typedef enum
{
    NO_GET,
}SYSTEM_PARAM_GET_ID;

typedef enum
{
    SYSTEM_PARAM_READ,
    SYSTEM_PARAM_WRITE,
    SYSTEM_PARAM_FIRST_RUN,
    SYSTEM_PARAM_CHECK_FIRST_RUN,
    SYSTEM_PARAM_INIT
}SYSTEM_PARAM_REQUEST_ID;


EXECUTE_PROTO(SYSTEM_PARAM,SYSTEM_PARAM_READ,BOOL*,int8_t*,int32_t*, int32_t*,void *);
EXECUTE_PROTO(SYSTEM_PARAM,SYSTEM_PARAM_WRITE,BOOL*,int8_t*,int32_t*, int32_t*,void *);
EXECUTE_PROTO(SYSTEM_PARAM,SYSTEM_PARAM_INIT,BOOL*,void *);
EXECUTE_PROTO(SYSTEM_PARAM,SYSTEM_PARAM_FIRST_RUN,BOOL*,void *);
EXECUTE_PROTO(SYSTEM_PARAM,SYSTEM_PARAM_CHECK_FIRST_RUN,BOOL*, void *);


void system_param_module_itf_init(void);

#endif