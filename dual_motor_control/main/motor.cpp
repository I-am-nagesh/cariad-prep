#include "motor.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

static const char *TAG = "MOTOR";

#define MOTOR1_PWM GPIO_NUM_25
#define MOTOR2_PWM GPIO_NUM_26
#define MOTOR1_DIR1 GPIO_NUM_27
#define MOTOR1_DIR2 GPIO_NUM_14
#define MOTOR2_DIR1 GPIO_NUM_12
#define MOTOR2_DIR2 GPIO_NUM_13

void motor_init()
{
    gpio_set_direction(MOTOR1_DIR1, GPIO_MODE_OUTPUT);
    gpio_set_direction(MOTOR1_DIR2, GPIO_MODE_OUTPUT);
    gpio_set_direction(MOTOR2_DIR1, GPIO_MODE_OUTPUT);
    gpio_set_direction(MOTOR2_DIR2, GPIO_MODE_OUTPUT);

    gpio_set_level(MOTOR1_DIR1, 1);
    gpio_set_level(MOTOR1_DIR2, 0);
    gpio_set_level(MOTOR2_DIR1, 1);
    gpio_set_level(MOTOR2_DIR2, 0);

    ledc_timer_config_t timer_conf = {
        .speed_mode = LEDC_LOW_SPEED_MODE,
        .duty_resolution = LEDC_TIMER_8_BIT,
        .timer_num = LEDC_TIMER_0,
        .freq_hz = 5000,
        .clk_cfg = LEDC_AUTO_CLK};
    ledc_timer_config(&timer_conf);

    ledc_channel_config_t motor1_ch = {
        .gpio_num = MOTOR1_PWM,
        .speed_mode = LEDC_LOW_SPEED_MODE,
        .channel = LEDC_CHANNEL_0,
        .timer_sel = LEDC_TIMER_0,
        .duty = 0,
        .hpoint = 0};
    ledc_channel_config(&motor1_ch);

    ledc_channel_config_t motor2_ch = {
        .gpio_num = MOTOR2_PWM,
        .speed_mode = LEDC_LOW_SPEED_MODE,
        .channel = LEDC_CHANNEL_1,
        .timer_sel = LEDC_TIMER_0,
        .duty = 0,
        .hpoint = 0};
    ledc_channel_config(&motor2_ch);
}

void motor1_set_speed(uint32_t duty)
{
    ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, duty);
    ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0);
}

void motor2_set_speed(uint32_t duty)
{
    ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_1, duty);
    ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_1);
}

void motor1_task(void *pvParameter)
{
    while (true)
    {
        motor1_set_speed(100); 
        ESP_LOGI(TAG, "Motor 1 running at speed 100");
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}

void motor2_task(void *pvParameter)
{
    while (true)
    {
        motor2_set_speed(200); 
        ESP_LOGI(TAG, "Motor 2 running at speed 200");
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}
