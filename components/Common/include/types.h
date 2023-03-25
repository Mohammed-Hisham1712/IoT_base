#ifndef __TYPES_H__

#define __TYPES_H__

#include <stdint.h>

#ifndef FAILED
#define FAILED -1
#endif

#ifndef OK
#define OK      0
#endif

enum
{
    FALSE = 0,
    TRUE
};

typedef int32_t error_t;
typedef uint8_t BOOL;

#endif