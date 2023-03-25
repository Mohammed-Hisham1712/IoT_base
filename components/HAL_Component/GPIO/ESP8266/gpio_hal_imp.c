#include "gpio_hal_itf.h"

#include "driver/gpio.h"
#include "esp_log.h"

#define GPIO_HAL_RET_CHECK(ret)     (((ret) == ESP_OK) ? TRUE : FALSE)

#define GPIO_TAG                "GPIO"
#define GPIO_LOGD_FORMAT        "[LINE:%d] [PIN_%d]"

#define GPIO_LOGD(pin_num)      ESP_LOGD(GPIO_TAG, GPIO_LOGD_FORMAT, __LINE__, (pin_num))

const gpio_num_t ESP_GPIO_PINS[PIN_MAX] = {
    ESP8266_PIN(PIN_0),
    ESP8266_PIN(PIN_1),
    ESP8266_PIN(PIN_2),
    ESP8266_PIN(PIN_3),
    ESP8266_PIN(PIN_4),
};

error_t gpio_hal_init(void)
{
    gpio_install_isr_service(0);

    return RET_OK;
}

error_t gpio_hal_config(gpio_hal_pin_t pin_num, const gpio_hal_config_t* p_config)
{
    BOOL l_ret = TRUE;
    gpio_num_t l_pin;

    if(!p_config || !GPIO_HAL_IS_PIN(pin_num))
    {
        GPIO_LOGD(pin_num);
        return RET_FAILED;
    }

    if(!GPIO_HAL_IS_MODE(p_config->mode) || !GPIO_HAL_IS_PULL(p_config->pull))
    {
        GPIO_LOGD(pin_num);
        return RET_FAILED;
    }

    l_pin = ESP_GPIO_PINS[pin_num];

    switch(p_config->mode)
    {
        case GPIO_HAL_MODE_INPUT:
            l_ret &= GPIO_HAL_RET_CHECK(gpio_set_direction(l_pin, GPIO_MODE_INPUT));
            l_ret &= GPIO_HAL_RET_CHECK(gpio_set_intr_type(l_pin, GPIO_INTR_DISABLE));
            break;
        case GPIO_HAL_MODE_OUTPUT_PP:
            l_ret &= GPIO_HAL_RET_CHECK(gpio_set_direction(l_pin, GPIO_MODE_OUTPUT));
            l_ret &= GPIO_HAL_RET_CHECK(gpio_set_intr_type(l_pin, GPIO_INTR_DISABLE));
            break;
        case GPIO_HAL_MODE_OUTPUT_OD:
            l_ret &= GPIO_HAL_RET_CHECK(gpio_set_direction(l_pin, GPIO_MODE_OUTPUT_OD));
            l_ret &= GPIO_HAL_RET_CHECK(gpio_set_intr_type(l_pin, GPIO_INTR_DISABLE));
            break;
        case GPIO_HAL_MODE_IT_RISING:
            l_ret &= GPIO_HAL_RET_CHECK(gpio_set_direction(l_pin, GPIO_MODE_INPUT));
            l_ret &= GPIO_HAL_RET_CHECK(gpio_set_intr_type(l_pin, GPIO_INTR_POSEDGE));
            break;
        case GPIO_HAL_MODE_IT_FALLING:
            l_ret &= GPIO_HAL_RET_CHECK(gpio_set_direction(l_pin, GPIO_MODE_INPUT));
            l_ret &= GPIO_HAL_RET_CHECK(gpio_set_intr_type(l_pin, GPIO_INTR_NEGEDGE));
            break;
        case GPIO_HAL_MODE_IT_RISING_FALLING:
            l_ret &= GPIO_HAL_RET_CHECK(gpio_set_direction(l_pin, GPIO_MODE_INPUT));
            l_ret &= GPIO_HAL_RET_CHECK(gpio_set_intr_type(l_pin, GPIO_INTR_ANYEDGE));
            break;
    }

    switch (p_config->pull)
    {
        case GPIO_HAL_PULL_NONE:
            l_ret &= GPIO_HAL_RET_CHECK(gpio_set_pull_mode(l_pin, GPIO_FLOATING));
            break;
        case GPIO_HAL_PULL_UP:
            l_ret &= GPIO_HAL_RET_CHECK(gpio_set_pull_mode(l_pin, GPIO_PULLUP_ONLY));
            break;
        case GPIO_HAL_PULL_DOWN:
            l_ret &= GPIO_HAL_RET_CHECK(gpio_set_pull_mode(l_pin, GPIO_PULLDOWN_ONLY));
            break;
    }

    if(!l_ret)
    {
        GPIO_LOGD(pin_num);
        return RET_FAILED;
    }

    return RET_OK;
}

error_t gpio_hal_write(gpio_hal_pin_t pin_num, gpio_hal_level_t level)
{

    if(!GPIO_HAL_IS_PIN(pin_num))
    {
        GPIO_LOGD(pin_num);
        return RET_FAILED;
    }
    
    if(gpio_set_level(ESP_GPIO_PINS[pin_num], (uint8_t) level) != ESP_OK)
    {
        return RET_FAILED;
    }

    return RET_OK;
}

gpio_hal_level_t gpio_hal_read(gpio_hal_pin_t pin_num)
{
    return gpio_get_level(ESP_GPIO_PINS[pin_num]) ? 
                            GPIO_HAL_LEVEL_HIGH : GPIO_HAL_LEVEL_LOW;
}

error_t gpio_hal_register_callback(gpio_hal_pin_t pin_num, gpio_hal_callback_t cb)
{
    if(!GPIO_HAL_IS_PIN(pin_num) || !cb)
    {
        GPIO_LOGD(pin_num);
        return RET_FAILED;
    }

    if(gpio_isr_handler_add(ESP_GPIO_PINS[pin_num], (void*) cb, (void*) NULL) != ESP_OK)
    {
        GPIO_LOGD(pin_num);
        return RET_FAILED;
    }
    
    return RET_OK;
}