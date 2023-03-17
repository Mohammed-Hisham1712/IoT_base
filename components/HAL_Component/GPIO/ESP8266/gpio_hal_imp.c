#include "gpio_hal_itf.h"

#include "gpio.h"

#define GPIO_HAL_RET_CHECK(ret)     (((ret) == ESP_OK) ? TRUE : FALSE)

error_t gpio_hal_init(void)
{
    /* Do nothing*/
    return OK;
}

error_t gpio_hal_config(gpio_hal_pin_t pin_num, const gpio_hal_config_t* p_config)
{
    BOOL l_ret = TRUE;

    if(!p_config)
    {
        return FAILED;
    }

    if(!GPIO_HAL_IS_MODE(p_config->mode) || !GPIO_HAL_IS_PULL(p_config->pull))
    {
        return FAILED;
    }

    switch(p_config->mode)
    {
        case GPIO_HAL_MODE_INPUT:
            l_ret &= GPIO_HAL_RET_CHECK(gpio_set_direction(pin_num, GPIO_MODE_INPUT));
            break;
        case GPIO_HAL_MODE_OUTPUT_PP:
            l_ret &= GPIO_HAL_RET_CHECK(gpio_set_direction(pin_num, GPIO_MODE_OUTPUT));
            break;
        case GPIO_HAL_MODE_OUTPUT_OD:
            l_ret &= GPIO_HAL_RET_CHECK(gpio_set_direction(pin_num, GPIO_MODE_OUTPUT_OD));
            break;
    }

    switch (p_config->pull)
    {
        case GPIO_HAL_PULL_NONE:
            l_ret &= GPIO_HAL_RET_CHECK(gpio_set_pull_mode(pin_num, GPIO_FLOATING));
            break;
        case GPIO_HAL_PULL_UP:
            l_ret &= GPIO_HAL_RET_CHECK(gpio_set_pull_mode(pin_num, GPIO_PULLUP_ONLY));
            break;
        case GPIO_HAL_PULL_DOWN:
            l_ret &= GPIO_HAL_RET_CHECK(gpio_set_pull_mode(pin_num, GPIO_PULLDOWN_ONLY));
            break;
    }

    if(!l_ret)
    {
        return FAILED;
    }

    return OK;
}

error_t gpio_hal_write(gpio_hal_pin_t pin_num, gpio_hal_level_t level)
{
    if(gpio_set_level(pin_num, (uint8_t) level) != ESP_OK)
    {
        return FAILED;
    }

    return OK;
}

gpio_hal_level_t gpio_hal_read(gpio_hal_pin_t pin_num)
{
    return gpio_get_level(pin_num) ? GPIO_HAL_LEVEL_HIGH : GPIO_HAL_LEVEL_LOW;
}