#include "driver/ledc.h"
#include "driver/gpio.h"


void motor_init();
void motor1_set_speed(uint32_t duty);
void motor2_set_speed(uint32_t duty);
void motor1_task(void *pvParameter);
void motor2_task(void *pvParameter);