#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

extern "C" void wifi_task(void *pvParameter);
extern "C" void led_task(void *pvParameter);

extern "C" void app_main()
{
    xTaskCreate(&wifi_task, "wifi_task", 4096, nullptr, 5, nullptr);
    xTaskCreate(&led_task, "led_task", 2048, nullptr, 5, nullptr);
}