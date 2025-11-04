#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "motor.h"

extern "C" void app_main()
{
    motor_init();

    xTaskCreate(&motor1_task, "motor1_task", 2048, nullptr, 5, nullptr);
    xTaskCreate(&motor2_task, "motor2_task", 2048, nullptr, 5, nullptr);
}
