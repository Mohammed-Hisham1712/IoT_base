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

#define ESP8266_PIN_0       GPIO_NUM_0
#define ESP8266_PIN_1       GPIO_NUM_1
#define ESP8266_PIN_2       GPIO_NUM_2
#define ESP8266_PIN_3       GPIO_NUM_3
#define ESP8266_PIN_4       GPIO_NUM_4
#define ESP8266_PIN_5       GPIO_NUM_5
#define ESP8266_PIN_6       GPIO_NUM_6
#define ESP8266_PIN_7       GPIO_NUM_7
#define ESP8266_PIN_8       GPIO_NUM_8
#define ESP8266_PIN_9       GPIO_NUM_9
#define ESP8266_PIN_10      GPIO_NUM_10
#define ESP8266_PIN_11      GPIO_NUM_11
#define ESP8266_PIN_12      GPIO_NUM_12
#define ESP8266_PIN_13      GPIO_NUM_13
#define ESP8266_PIN_14      GPIO_NUM_14
#define ESP8266_PIN_15      GPIO_NUM_15
#define ESP8266_PIN_16      GPIO_NUM_16

#define ESP8266_PIN_MAX     GPIO_NUM_MAX

/* PIN 6 to 11 can not be used as GPIO pin*/
typedef enum
{
    PIN_0 = 0,
    PIN_1,
    PIN_2,
    PIN_3,
    PIN_4,
    PIN_5,
    PIN_6=12,
    PIN_7,
    PIN_8,
    PIN_9,
    PIN_10,
    /*
    PIN_11,
    PIN_12 = 12 ,
    PIN_13,
    PIN_14,
    PIN_15,
    PIN_16,
    */
    PIN_MAX
}gpio_hal_pin_t;

#endif