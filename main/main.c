/* Hello World Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "gpio_hal_itf.h"

#define TEST_PIN    PIN_4

void app_main()
{
    #if 1
    gpio_hal_level_t pin_level;

    gpio_hal_init();

    gpio_hal_config_t pin_config = {
        .mode = GPIO_HAL_MODE_OUTPUT_PP,
        .pull = GPIO_HAL_PULL_NONE };

    gpio_hal_config(TEST_PIN, &pin_config);

    pin_level = GPIO_HAL_LEVEL_HIGH;

    while (1)
    {
        gpio_hal_write(TEST_PIN, pin_level);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        pin_level = (pin_level == GPIO_HAL_LEVEL_HIGH) ? 
                                        GPIO_HAL_LEVEL_LOW : GPIO_HAL_LEVEL_HIGH;
    }
    #else
    while(1)
    {
        printf("Hello, world!\n\r");
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
    #endif
}
