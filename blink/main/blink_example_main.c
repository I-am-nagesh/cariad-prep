// Include FreeRTOS headers for multitasking and timing
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

// Include GPIO driver to control pins
#include "driver/gpio.h"

// Include ESP logging library for serial monitor output
#define LOG_LOCAL_LEVEL ESP_LOG_INFO
#include "esp_log.h"

// Define the GPIO pin number connected to the LED
// Most ESP32 DevKit boards have the onboard LED on GPIO 2
#define LED_PIN 2  

// Entry point for the application
void app_main(void)
{
    // Reset the GPIO pin to its default state before configuring
    gpio_reset_pin(LED_PIN);

    // Set the pin direction as output so we can drive HIGH/LOW signals
    gpio_set_direction(LED_PIN, GPIO_MODE_OUTPUT);

    // Infinite loop (FreeRTOS task runs forever)
    while (true)
    {
        // Turn LED ON by setting GPIO level HIGH (3.3V)
        gpio_set_level(LED_PIN, 1);

        // Log message to serial monitor for debugging
        ESP_LOGI("BLINK", "LED ON");

        // Delay the task for 500 milliseconds (non-blocking delay)
        // 'pdMS_TO_TICKS' converts milliseconds to FreeRTOS tick units
        vTaskDelay(pdMS_TO_TICKS(500));

        // Turn LED OFF by setting GPIO level LOW (0V)
        gpio_set_level(LED_PIN, 0);

        // Log message to serial monitor for debugging
        ESP_LOGI("BLINK", "LED OFF");

        // Delay again for 500 ms before next toggle
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}
