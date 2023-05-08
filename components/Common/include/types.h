#ifndef __TYPES_H__

#define __TYPES_H__

#include <stdint.h>
#include "stddef.h"
enum
{
    RET_FAILED = -1,
    RET_OK
};

enum
{
    FALSE = 0,
    TRUE
};

typedef int32_t error_t;
typedef uint8_t BOOL;

typedef int32_t get_id_t;
typedef int32_t set_id_t;
typedef int32_t request_id_t;



#define NON         (-1)
#define UNDEFINED   (-1)

#endif