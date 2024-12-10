#pragma once

#include "esp_err.h"

#define LEDC_FREQUENCY_1024 1024
#define LEDC_CHANNELS_3 3
#define LEDC_LEDR 4
#define LEDC_LEDG 9
#define LEDC_LEDB 10

esp_err_t system_init(void);
esp_err_t ledc_init(void);

