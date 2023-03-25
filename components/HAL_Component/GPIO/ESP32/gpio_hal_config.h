#ifndef __GPIO_HAL_CONFIG_H__

#define __GPIO_HAL_CONFIG_H__

/*
* Author: Mohammed Hisham
* Date: March 24th, 2023
* 
* For more information regarding ESP32 GPIO ESP32_PINs see the following links
* https://lastminuteengineers.com/esp32-ESP32_PINout-reference/
* https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/peripherals/gpio.html
* 
*/

#include "driver/gpio.h"

#define ESP32_PIN(pin)    (ESP32_##pin)

#define ESP32_PIN_0       GPIO_NUM_4
#define ESP32_PIN_1       GPIO_NUM_13
#define ESP32_PIN_2       GPIO_NUM_14
#define ESP32_PIN_3       GPIO_NUM_16
#define ESP32_PIN_4       GPIO_NUM_17
#define ESP32_PIN_5       GPIO_NUM_18
#define ESP32_PIN_6       GPIO_NUM_19
#define ESP32_PIN_7       GPIO_NUM_21
#define ESP32_PIN_8       GPIO_NUM_22
#define ESP32_PIN_9       GPIO_NUM_23
#define ESP32_PIN_10      GPIO_NUM_25
#define ESP32_PIN_11      GPIO_NUM_26
#define ESP32_PIN_12      GPIO_NUM_27
#define ESP32_PIN_13      GPIO_NUM_32
#define ESP32_PIN_14      GPIO_NUM_33
#define ESP32_PIN_15      GPIO_NUM_34     /* Input Only */
#define ESP32_PIN_16      GPIO_NUM_35     /* Input Only */
#define ESP32_PIN_17      GPIO_NUM_36     /* Input Only */
#define ESP32_PIN_18      GPIO_NUM_39     /* Input Only */
#define ESP32_PIN_MAX     GPIO_NUM_MAX

typedef enum
{
    PIN_0 = 0,
    PIN_1,
    PIN_2,
    PIN_3,
    PIN_4,
    PIN_5,
    PIN_6,
    PIN_7,
    PIN_8,
    PIN_9,
    PIN_10,
    PIN_11,
    PIN_12,
    PIN_13,
    PIN_14,
    PIN_15,
    PIN_16,
    PIN_17,
    PIN_18,
    PIN_MAX,
} gpio_hal_pin_t;

#endif