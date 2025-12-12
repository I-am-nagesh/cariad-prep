#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/twai.h"
#include "esp_log.h"

#define TX_PIN 4
#define RX_PIN 5

static const char* TAG = "RECEIVER";

extern "C" void app_main(void)
{
    // config TWAI (CAN) Driver
    twai_general_config_t g_config = TWAI_GENERAL_CONFIG_DEFAULT((gpio_num_t)TX_PIN, (gpio_num_t)RX_PIN, TWAI_MODE_NORMAL);
    twai_timing_config_t t_config = TWAI_TIMING_CONFIG_25KBITS();
    twai_filter_config_t f_config = TWAI_FILTER_CONFIG_ACCEPT_ALL();

    // install and start TWAI driver
    if (twai_driver_install(&g_config, &t_config, &f_config) != ESP_OK) {
        ESP_LOGE(TAG, "Failed to install driver");
        return;
    }
    twai_start();
    ESP_LOGI(TAG, "--- CAN Receiver Listening ---");

    while (true) {
        uint32_t alerts;
        twai_read_alerts(&alerts, pdMS_TO_TICKS(100)); 

        if (alerts & TWAI_ALERT_RX_DATA) {
            twai_message_t message;
            if (twai_receive(&message, 0) == ESP_OK) {
                printf("Received ID: 0x%lx | Data: %d\n", message.identifier, message.data[0]);
            }
        }
        
        if (alerts & TWAI_ALERT_BUS_ERROR) {
            printf("Signal Error (Noise/Voltage)\n");
        }
        
        if (alerts & TWAI_ALERT_BUS_OFF) {
            printf("BUS DIED (Bus Off). Restarting...\n");
            twai_initiate_recovery();
            twai_start();
        }
    }
}