#ifndef __GPIO_HAL_CONFIG_H__
#define __GPIO_HAL_CONFIG_H__

/*
* Author: Mohammed Hisham
* Date: March 24th, 2023
* 
* For more information regarding ESP8266 GPIO pins see the following links
* https://lastminuteengineers.com/esp8266-pinout-reference/
* 
*/

#include "driver/gpio.h"

#define ESP8266_PIN(pin)    (ESP8266_##pin)

#define ESP8266_PIN_0       GPIO_NUM_4
#define ESP8266_PIN_1       GPIO_NUM_5
#define ESP8266_PIN_2       GPIO_NUM_12
#define ESP8266_PIN_3       GPIO_NUM_13
#define ESP8266_PIN_4       GPIO_NUM_14
#define ESP8266_PIN_MAX     GPIO_NUM_MAX

typedef enum
{
    PIN_0 = 0,
    PIN_1,
    PIN_2,
    PIN_3,
    PIN_4,
    PIN_MAX
}gpio_hal_pin_t;

#endif