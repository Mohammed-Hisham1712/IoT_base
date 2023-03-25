#ifndef __GPIO_HAL_ITF_H__

#define __GPIO_HAL_ITF_H__

#include "gpio_hal_config.h"

#include "types.h"

#include <stdint.h>

#define GPIO_HAL_IS_PIN(pin)            ((pin) < PIN_MAX)
#define GPIO_HAL_IS_MODE(mode)          ((mode) < GPIO_HAL_MODE_INVALID)
#define GPIO_HAL_IS_PULL(pull)          ((pull) < GPIO_HAL_PULL_INVALID)

typedef void (*gpio_hal_callback_t) (void*);

typedef enum
{
    GPIO_HAL_MODE_INPUT,
    GPIO_HAL_MODE_OUTPUT_PP,
    GPIO_HAL_MODE_OUTPUT_OD,
    GPIO_HAL_MODE_IT_RISING,
    GPIO_HAL_MODE_IT_FALLING,
    GPIO_HAL_MODE_IT_RISING_FALLING,
    GPIO_HAL_MODE_INVALID
} gpio_hal_mode_t;

typedef enum
{
    GPIO_HAL_PULL_NONE,
    GPIO_HAL_PULL_UP,
    GPIO_HAL_PULL_DOWN,
    GPIO_HAL_PULL_INVALID
} gpio_hal_pull_t;

typedef enum
{
    GPIO_HAL_LEVEL_LOW = 0,
    GPIO_HAL_LEVEL_HIGH,
} gpio_hal_level_t;

typedef struct
{
    uint8_t mode;
    uint8_t pull;
} gpio_hal_config_t;

error_t gpio_hal_init(void);

error_t gpio_hal_config(gpio_hal_pin_t pin_num, const gpio_hal_config_t* p_config);

error_t gpio_hal_write(gpio_hal_pin_t pin_num, gpio_hal_level_t level);

gpio_hal_level_t gpio_hal_read(gpio_hal_pin_t pin_num);

error_t gpio_hal_register_callback(gpio_hal_pin_t pin_num, gpio_hal_callback_t cb);

#endif