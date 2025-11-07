#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

extern "C" void display_task(void *pvParameter);

extern "C" void app_main(void)
{
    xTaskCreate(display_task, "display_task", 4096, nullptr, 5, nullptr);
}



