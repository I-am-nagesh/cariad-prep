#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_wifi.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "esp_event.h"
#include <string.h>
#include "esp_netif.h"

#define WIFI_SSID "Redmi"
#define WIFI_PASS "12345555"

static const char *TAG = "WIFI_TASK";

extern "C" void wifi_task(void *pvParameter)
{

    nvs_flash_init();
    esp_netif_init();
    esp_event_loop_create_default();
    esp_netif_create_default_wifi_sta();

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    esp_wifi_init(&cfg);

    wifi_config_t wifi_config = {};
   strncpy((char *)wifi_config.sta.ssid, WIFI_SSID, sizeof(wifi_config.sta.ssid));
strncpy((char *)wifi_config.sta.password, WIFI_PASS, sizeof(wifi_config.sta.password));


    esp_wifi_set_mode(WIFI_MODE_STA);
    esp_wifi_set_config(WIFI_IF_STA, &wifi_config);

    esp_wifi_start();

    ESP_LOGI(TAG, "Connecting to WiFi SSID: %s", WIFI_SSID);

    esp_wifi_connect();

    while (true)
    {
        wifi_ap_record_t ap_info;
        if (esp_wifi_sta_get_ap_info(&ap_info) == ESP_OK)
        {
            ESP_LOGI(TAG, "Connected to AP SSID: %s, RSSI: %d", ap_info.ssid, ap_info.rssi);
        }
        else
        {
            ESP_LOGI(TAG, "Not connected to any AP");
            esp_wifi_connect();
        }
        vTaskDelay(pdMS_TO_TICKS(5000));
    }
}