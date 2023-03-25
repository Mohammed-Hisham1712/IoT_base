/* Hello World Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

#include "gpio_hal_itf.h"

#define LED_PIN     PIN_1
#define BUTTON_BIN  PIN_0 

gpio_hal_level_t led_state;

void button_pressed_callback(void* args)
{
    (void) args;

    led_state = (led_state == GPIO_HAL_LEVEL_HIGH) ? 
                        GPIO_HAL_LEVEL_LOW : GPIO_HAL_LEVEL_HIGH;
    gpio_hal_write(LED_PIN, led_state);
}

void app_main()
{
    gpio_hal_config_t led_config = {
        .mode = GPIO_HAL_MODE_OUTPUT_PP,
        .pull = GPIO_HAL_PULL_NONE };
    
    gpio_hal_config_t button_config = {
        .mode = GPIO_HAL_MODE_IT_FALLING,
        .pull = GPIO_HAL_PULL_UP
    };

    gpio_hal_init();
    gpio_hal_register_callback(BUTTON_BIN, button_pressed_callback);
    gpio_hal_config(LED_PIN, &led_config);
    gpio_hal_config(BUTTON_BIN, &button_config);
    
    gpio_hal_write(20, GPIO_HAL_LEVEL_HIGH);

    while (1)
    {
        ESP_LOGD("MAIN", "%s\n\r", "Hello, world!");
        vTaskDelay(500 / portTICK_PERIOD_MS);
    }
    
}
