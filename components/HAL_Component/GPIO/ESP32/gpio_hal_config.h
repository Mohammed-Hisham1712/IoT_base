#ifndef __GPIO_HAL_CONFIG_H__

#define __GPIO_HAL_CONFIG_H__

/*
* Author: Mohammed Hisham
* Date: March 24th, 2023
* 
* For more information regarding ESP32 GPIO pins see the following links
* https://lastminuteengineers.com/esp32-pinout-reference/
* https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/peripherals/gpio.html
* 
*/

#include "driver/gpio.h"

#define PIN_INV     0xFF

#define PIN_0       GPIO_NUM_4
#define PIN_1       GPIO_NUM_13
#define PIN_2       GPIO_NUM_14
#define PIN_3       GPIO_NUM_16
#define PIN_4       GPIO_NUM_17
#define PIN_5       GPIO_NUM_18
#define PIN_6       GPIO_NUM_19
#define PIN_7       GPIO_NUM_21
#define PIN_8       GPIO_NUM_22
#define PIN_9       GPIO_NUM_23
#define PIN_10      GPIO_NUM_25
#define PIN_11      GPIO_NUM_26
#define PIN_12      GPIO_NUM_27
#define PIN_13      GPIO_NUM_32
#define PIN_14      GPIO_NUM_33
#define PIN_15      GPIO_NUM_34     /* Input Only */
#define PIN_16      GPIO_NUM_35     /* Input Only */
#define PIN_17      GPIO_NUM_36     /* Input Only */
#define PIN_18      GPIO_NUM_39     /* Input Only */
#define PIN_MAX     GPIO_NUM_MAX

#endif