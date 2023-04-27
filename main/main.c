#include "mqtt_component_public.h"
#include "wifi_component_public.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

void app_main()
{
    wifi_component_init();
    vTaskDelay(10000 / portTICK_PERIOD_MS);
    mqtt_component_init();
    mqtt_component_start();

    while (1)
    {    
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }    
}
