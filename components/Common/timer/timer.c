#include "timer.h"

#include "esp_timer.h"

#define TIMER_DIVIDER   1000LL

int64_t timer_get_milliseconds(void)
{
    return esp_timer_get_time() / TIMER_DIVIDER;
}

void timer_start(millis_timer_t* p_timer)
{
    p_timer->start_milliseconds = timer_get_milliseconds();
    p_timer->started = 1;
}

void timer_clear(millis_timer_t* p_timer)
{
    p_timer->start_milliseconds = 0;
    p_timer->started = 0;
}

int64_t timer_elapsed(millis_timer_t* p_timer)
{
    int64_t elapsed;
    
    elapsed = 0;

    if(p_timer->started)
    {
        elapsed = timer_get_milliseconds() - p_timer->start_milliseconds;
    }

    return elapsed;
}

uint8_t timer_is_started(millis_timer_t* p_timer)
{
    return p_timer->started;
}