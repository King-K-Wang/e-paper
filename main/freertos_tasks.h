#pragma once

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

/**
 * @function: led_init_behavior_task
 * @brief: When system is initializing, led breathe function
 * @param: (void*) should be NULL
 * @return: None
 * @note: Create and delete the task in system init function
 */
void led_init_behavior_task(void *pvParameter);
void button_behavior_task(void *pvParameter);

