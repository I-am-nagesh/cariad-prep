#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_wifi.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "esp_event.h"
#include <string.h>
#include "esp_netif.h"

#include "freertos/semphr.h"

#define WIFI_SSID "Redmi"
#define WIFI_PASS "12345555"

static const char *TAG = "WIFI_TASK";

// declaring semaphore handle that defined in main.cpp
extern SemaphoreHandle_t wifi_semaphore;

extern "C" void wifi_task(void *pvParameter)
{

    nvs_flash_init();
    esp_netif_init();
    esp_event_loop_create_default();
    // esp_netif_create_default_wifi_sta();
     esp_netif_t *netif = esp_netif_create_default_wifi_sta();

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

    bool connected = false;

    while (true)
    {
        wifi_ap_record_t ap_info;

        esp_netif_ip_info_t ip_info;

        bool wifi_ok = (esp_wifi_sta_get_ap_info(&ap_info) == ESP_OK);
        bool ip_ok = (esp_netif_get_ip_info(netif, &ip_info) == ESP_OK) &&
                     (ip_info.ip.addr != 0);
          if (wifi_ok && ip_ok)
        {
            // connected
            if (!connected)
            {
                // semaphore given to main.cpp to notify that wifi is connected
                xSemaphoreGive(wifi_semaphore);
                connected = true;
                ESP_LOGI(TAG, "Connected to AP SSID: %s, RSSI: %d", ap_info.ssid, ap_info.rssi);
            }
        }
        else
        {

            // disconnected
            if (connected)
            {
                xSemaphoreTake(wifi_semaphore, 0); // blocking LED blinkding
                connected = false;
                ESP_LOGI(TAG, "Not connected to any AP");
            }
            esp_wifi_connect();
        }
        vTaskDelay(pdMS_TO_TICKS(5000));
    }
}