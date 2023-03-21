/* Hello World Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_spi_flash.h"

#include "gpio_hal_itf.h"

void app_main()
{
    gpio_hal_level_t pin_level;

    gpio_hal_init();

    gpio_hal_config_t pin_config = {
        .mode = GPIO_HAL_MODE_OUTPUT_PP,
        .pull = GPIO_HAL_PULL_NONE };

    gpio_hal_config(PIN_16, &pin_config);

    pin_level = GPIO_HAL_LEVEL_HIGH;

    while (1)
    {
        gpio_hal_write(PIN_16, pin_level);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        pin_level = (pin_level == GPIO_HAL_LEVEL_HIGH) ? 
                                        GPIO_HAL_LEVEL_LOW : GPIO_HAL_LEVEL_HIGH;
    }
}
