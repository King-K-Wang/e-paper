#pragma once

#include "esp_err.h"
#include "led_indicator.h"

#define LEDC_LEDR 4
#define LEDC_LEDG 9
#define LEDC_LEDB 10

esp_err_t system_init(void);

/**
 * @funcion: ledc_init
 * @brief: Initialize RGB LED
 * @param: INPUT - NULL
 * @return: OUTPUT - led_indicator_handle_t Handle of LED indicator
 *                                          NULL if create failed
 */
led_indicator_handle_t ledc_init(void);
esp_err_t button_init(void);

