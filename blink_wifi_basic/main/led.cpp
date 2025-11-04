#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"

#include "freertos/semphr.h"

#define LED_PIN GPIO_NUM_2

static const char *TAG = "LED TASK";

// semaphore handle declared in main.cpp
extern SemaphoreHandle_t wifi_semaphore;

extern "C" void led_task(void *pvParameter)
{
    gpio_reset_pin(LED_PIN);
    gpio_set_direction(LED_PIN, GPIO_MODE_OUTPUT);

    while (true)
    {

        // wait until wifi is connected
        if (xSemaphoreTake(wifi_semaphore, pdMS_TO_TICKS(1000)) == pdTRUE)
        {

            // LED blinks indefinitely while connected
            gpio_set_level(LED_PIN, 1);
            ESP_LOGI(TAG, "LED ON (WiFi Connected)");
            vTaskDelay(pdMS_TO_TICKS(500));

            gpio_set_level(LED_PIN, 0);
            ESP_LOGI(TAG, "LED OFF (WiFi Connected)");
            vTaskDelay(pdMS_TO_TICKS(500));

            // give semaphore back for next cycle
            xSemaphoreGive(wifi_semaphore);
        }
        else
        {
            // WiFi not connected, keep LED OFF
            gpio_set_level(LED_PIN, 0);
            ESP_LOGW(TAG, "WiFi not connected. LED stopped.");
            vTaskDelay(pdMS_TO_TICKS(2000));
        }

        // gpio_set_level(LED_PIN, 1);
        // ESP_LOGI(TAG, "LED ON");
        // vTaskDelay(pdMS_TO_TICKS(500));

        // gpio_set_level(LED_PIN, 0);
        // ESP_LOGI(TAG, "LED OFF");
        // vTaskDelay(pdMS_TO_TICKS(500));
    }
}