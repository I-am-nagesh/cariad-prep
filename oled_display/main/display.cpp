#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/i2c_master.h"
#include "esp_log.h"
#include "string.h"

// inclusing the font data
#include "font8x5.h"

#define I2C_MASTER_SDA_IO 19
#define I2C_MASTER_SCL_IO 18
#define I2C_MASTER_NUM I2C_NUM_0
#define OLED_ADDR 0x3C

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define SCREEN_PAGES (SCREEN_HEIGHT / 8)

static const char *TAG = "OLED_DISPLAY";

esp_err_t oled_send_command(i2c_master_dev_handle_t dev_handle, uint8_t cmd)
{
    uint8_t write_buf[2] = {0x00, cmd}; // 0x00 for command register
    return i2c_master_transmit(dev_handle, write_buf, sizeof(write_buf), pdMS_TO_TICKS(100));
}

esp_err_t oled_send_data(i2c_master_dev_handle_t dev_handle, uint8_t data)
{
    uint8_t write_buf[2] = {0x40, data}; // 0x40 for data register
    return i2c_master_transmit(dev_handle, write_buf, sizeof(write_buf), pdMS_TO_TICKS(100));
}

void oled_display_init(i2c_master_dev_handle_t dev_handle)
{
    oled_send_command(dev_handle, 0xAE); // Display OFF
    oled_send_command(dev_handle, 0xD5); // Set Display Clock Divide Ratio
    oled_send_command(dev_handle, 0x80); //   Default Ratio
    oled_send_command(dev_handle, 0xA8); // Set MUX Ratio
    oled_send_command(dev_handle, 0x1F); //   128x32 (31)
    oled_send_command(dev_handle, 0xD3); // Set Display Offset
    oled_send_command(dev_handle, 0x00); //   No offset
    oled_send_command(dev_handle, 0x40); // Set Start Line (0)
    oled_send_command(dev_handle, 0x8D); // Charge Pump Setting
    oled_send_command(dev_handle, 0x14); //   Enable Charge Pump
    oled_send_command(dev_handle, 0x20); // Set Memory Addressing Mode
    oled_send_command(dev_handle, 0x00); //   Horizontal Addressing Mode
    oled_send_command(dev_handle, 0xA1); // Set Segment Re-map (col 127 is 0)
    oled_send_command(dev_handle, 0xC8); // Set COM Output Scan Direction (remap)
    oled_send_command(dev_handle, 0xDA); // Set COM Pins
    oled_send_command(dev_handle, 0x02); //   Sequential, 128x32
    oled_send_command(dev_handle, 0x81); // Set Contrast
    oled_send_command(dev_handle, 0xCF); //   Default 0xCF
    oled_send_command(dev_handle, 0xD9); // Set Pre-charge Period
    oled_send_command(dev_handle, 0xF1);
    oled_send_command(dev_handle, 0xDB); // Set VCOMH
    oled_send_command(dev_handle, 0x40);
    oled_send_command(dev_handle, 0xA4); // Output follows RAM
    oled_send_command(dev_handle, 0xA6); // Normal Display
    oled_send_command(dev_handle, 0xAF); // Display ON
    ESP_LOGI(TAG, "OLED Display Initialized");
}

void oled_set_cursor(i2c_master_dev_handle_t dev_handle, uint8_t page, uint8_t col)
{
    oled_send_command(dev_handle, 0xB0 | (page & 0x07)); // Set Page
    oled_send_command(dev_handle, 0x00 | (col & 0x0F));  // Set low nibble of column
    oled_send_command(dev_handle, 0x10 | (col >> 4));    // Set high nibble of column
}

void oled_clear_screen(i2c_master_dev_handle_t dev_handle)
{
    for (uint8_t page = 0; page < SCREEN_PAGES; page++)
    {
        oled_set_cursor(dev_handle, page, 0);
        for (uint8_t col = 0; col < SCREEN_WIDTH; col++)
        {
            oled_send_data(dev_handle, 0x00);
        }
    }
    oled_set_cursor(dev_handle, 0, 0); // Reset cursor to top-left
    ESP_LOGI(TAG, "Screen cleared");
}

void oled_draw_char(i2c_master_dev_handle_t dev_handle, char c)
{
    if (c < 32 || c > 126)
    {            // Only draw printable ASCII
        c = ' '; // Default to space
    }
    // Each char is 5 bytes (columns) from the font table
    for (uint8_t i = 0; i < 5; i++)
    {
        oled_send_data(dev_handle, font8x5[c - 32][i]);
    }
    oled_send_data(dev_handle, 0x00); // 1-pixel space between chars
}

void oled_draw_string(i2c_master_dev_handle_t dev_handle, const char *str)
{
    while (*str)
    {
        oled_draw_char(dev_handle, *str++);
    }
}

extern "C" void display_task(void *pvParameter)
{

    i2c_master_bus_config_t bus_cfg = {
        .i2c_port = I2C_MASTER_NUM,
        .sda_io_num = static_cast<gpio_num_t>(I2C_MASTER_SDA_IO),
        .scl_io_num = static_cast<gpio_num_t>(I2C_MASTER_SCL_IO),
        .clk_source = I2C_CLK_SRC_DEFAULT,
        .glitch_ignore_cnt = 7,
        .intr_priority = 1,
        .trans_queue_depth = 0,
        .flags = {
            .enable_internal_pullup = true,
            .allow_pd = false},
    };

    i2c_master_bus_handle_t bus_handle;
    ESP_ERROR_CHECK(i2c_new_master_bus(&bus_cfg, &bus_handle));
    ESP_LOGI(TAG, "I2C Master Bus Initialized");

    i2c_device_config_t dev_cfg = {
        .dev_addr_length = I2C_ADDR_BIT_LEN_7,
        .device_address = OLED_ADDR,
        .scl_speed_hz = 400000,
        .scl_wait_us = 0,
        .flags = {
            .disable_ack_check = false}};

    i2c_master_dev_handle_t oled_handle;
    ESP_ERROR_CHECK(i2c_master_bus_add_device(bus_handle, &dev_cfg, &oled_handle));
    ESP_LOGI(TAG, "OLED Device Added to Bus");

    oled_display_init(oled_handle);

    oled_clear_screen(oled_handle);

    oled_set_cursor(oled_handle, 0, 0);

    oled_draw_string(oled_handle, "nagesh");

    oled_set_cursor(oled_handle, 2, 0);
    oled_draw_string(oled_handle, "ESP32 C++");

    ESP_LOGI(TAG, "Text displayed. Task will now delete.");

    vTaskDelete(nullptr);
}