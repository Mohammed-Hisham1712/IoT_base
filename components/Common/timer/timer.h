#ifndef __TIMER_H__

#define __TIMER_H__

#include "types.h"

#include <stdint.h>

typedef struct
{
    uint8_t started;
    int64_t start_milliseconds;
} millis_timer_t;

/**
 * @brief 
 * 
 * @return int64_t 
 */
int64_t timer_get_milliseconds(void);

/**
 * @brief 
 * 
 * @param p_timer 
 * @return error_t 
 */
void timer_start(millis_timer_t* p_timer);

/**
 * @brief 
 * 
 * @param p_timer 
 */
void timer_clear(millis_timer_t* p_timer);

/**
 * @brief 
 * 
 * @param p_timer 
 * @return int64_t 
 */
int64_t timer_elapsed(millis_timer_t* p_timer);

/**
 * @brief 
 * 
 * @param p_timer 
 * @return uint8_t 
 */
uint8_t timer_is_started(millis_timer_t* p_timer);

#endif