#include <stdio.h>
#include <cstdlib>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/twai.h"
#include "esp_random.h"
#include "esp_log.h"

#define TX_PIN 4
#define RX_PIN 5

static const char *TAG = "SENDER";

extern "C" void app_main(void)
{
    // config TWAI (CAN) Driver
twai_general_config_t g_config = TWAI_GENERAL_CONFIG_DEFAULT((gpio_num_t)TX_PIN, (gpio_num_t)RX_PIN, TWAI_MODE_NO_ACK);
   twai_timing_config_t t_config = TWAI_TIMING_CONFIG_25KBITS();
    twai_filter_config_t f_config = TWAI_FILTER_CONFIG_ACCEPT_ALL();

    // install and start TWAI driver
    if (twai_driver_install(&g_config, &t_config, &f_config) != ESP_OK)
    {
        ESP_LOGE(TAG, "Failed to install driver");
        return;
    }
    twai_start();
    ESP_LOGI(TAG, "--- CAN Sender Started ---");

    while (true)
    {
        // generatimg random speed
        uint8_t speed = esp_random() % 151;

        // create message
        twai_message_t message;
        message.identifier = 0x10A;
        message.extd = 0;
        message.rtr = 0;
        message.data_length_code = 1;
        message.data[0] = speed;

        // transmit
        if (twai_transmit(&message, pdMS_TO_TICKS(1000)) == ESP_OK)
        {
            printf("Sent Speed: %d km/h\n", speed);
        }
        else 
        {
        uint32_t alerts;
        twai_read_alerts(&alerts, pdMS_TO_TICKS(10));
        
        if (alerts & TWAI_ALERT_BUS_OFF) {
            printf("BUS OFF! Restarting driver...\n");
            twai_initiate_recovery();
            twai_start();
        }
        else {
            printf("Failed to send (Error count increasing...)\n");
        }
    }

        // delay 1 second
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}