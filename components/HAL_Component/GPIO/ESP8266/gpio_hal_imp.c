#include "gpio_hal_itf.h"

#include "driver/gpio.h"
#include "esp_log.h"
#include "esp8266/pin_mux_register.h"
#define GPIO_HAL_RET_CHECK(ret)     (((ret) == ESP_OK) ? TRUE : FALSE)

#define GPIO_TAG                "GPIO"
#define GPIO_LOGD_FORMAT        "[LINE:%d] [PIN_%d]"

#define GPIO_LOGD(pin_num)      ESP_LOGD(GPIO_TAG, GPIO_LOGD_FORMAT, __LINE__, (pin_num))

const gpio_num_t ESP_GPIO_PINS[PIN_MAX][3] = 
{
    {ESP8266_PIN(PIN_0),PERIPHS_IO_MUX_GPIO0_U,FUNC_GPIO0},
    {ESP8266_PIN(PIN_1),PERIPHS_IO_MUX_U0TXD_U,FUNC_GPIO1},
    {ESP8266_PIN(PIN_2),PERIPHS_IO_MUX_GPIO2_U,FUNC_GPIO2},
    {ESP8266_PIN(PIN_3),PERIPHS_IO_MUX_U0RXD_U,FUNC_GPIO3},
    {ESP8266_PIN(PIN_4),PERIPHS_IO_MUX_GPIO4_U,FUNC_GPIO4},
    {ESP8266_PIN(PIN_5),PERIPHS_IO_MUX_GPIO5_U,FUNC_GPIO5},
    /*
    * Pins from 6 to 11 cannot be used as normal GPIO as they are
    * connected to external flash memory 
    * when I tried to change the configurations the system halted.
    * */
    {ESP8266_PIN(PIN_6),PERIPHS_IO_MUX_SD_CLK_U,FUNC_GPIO6},
    {ESP8266_PIN(PIN_7),PERIPHS_IO_MUX_SD_DATA0_U,FUNC_GPIO7},
    {ESP8266_PIN(PIN_8),PERIPHS_IO_MUX_SD_DATA1_U,FUNC_GPIO8},
    {ESP8266_PIN(PIN_9),PERIPHS_IO_MUX_SD_DATA2_U,FUNC_GPIO9},
    {ESP8266_PIN(PIN_10),PERIPHS_IO_MUX_SD_DATA3_U,FUNC_GPIO10},
    {ESP8266_PIN(PIN_11),PERIPHS_IO_MUX_SD_CMD_U,FUNC_GPIO11},
    
    {ESP8266_PIN(PIN_12),PERIPHS_IO_MUX_MTDI_U,FUNC_GPIO12},
    {ESP8266_PIN(PIN_13),PERIPHS_IO_MUX_MTCK_U,FUNC_GPIO13},
    {ESP8266_PIN(PIN_14),PERIPHS_IO_MUX_MTMS_U,FUNC_GPIO14},
    {ESP8266_PIN(PIN_15),PERIPHS_IO_MUX_MTDO_U,FUNC_GPIO15},
    {ESP8266_PIN(PIN_16),0,0},
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

    l_pin = ESP_GPIO_PINS[pin_num][0];

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
    if ( pin_num != 16 )
    {
        GPIO_LOGD(pin_num);
        GPIO_LOGD(ESP_GPIO_PINS[pin_num][1]) ;
        GPIO_LOGD(ESP_GPIO_PINS[pin_num][2]) ;
        PIN_FUNC_SELECT(ESP_GPIO_PINS[pin_num][1], ESP_GPIO_PINS[pin_num][2]);
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
    
    if(gpio_set_level(ESP_GPIO_PINS[pin_num][0], (uint8_t) level) != ESP_OK)
    {
        return RET_FAILED;
    }

    return RET_OK;
}

gpio_hal_level_t gpio_hal_read(gpio_hal_pin_t pin_num)
{
    return gpio_get_level(ESP_GPIO_PINS[pin_num][0]) ? 
                            GPIO_HAL_LEVEL_HIGH : GPIO_HAL_LEVEL_LOW;
}

error_t gpio_hal_register_callback(gpio_hal_pin_t pin_num, gpio_hal_callback_t cb)
{
    if(!GPIO_HAL_IS_PIN(pin_num) || !cb)
    {
        GPIO_LOGD(pin_num);
        return RET_FAILED;
    }

    if(gpio_isr_handler_add(ESP_GPIO_PINS[pin_num][0], (void*) cb, (void*) NULL) != ESP_OK)
    {
        GPIO_LOGD(pin_num);
        return RET_FAILED;
    }
    
    return RET_OK;
}