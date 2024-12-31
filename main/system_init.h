#pragma once

#include "esp_err.h"

#define LED_TIMER_FREQUENCY 1024
#define LED_CHANNELS 3
#define LED_LEDR 4
#define LED_LEDG 9
#define LED_LEDB 10

#define LED_INIT_BREATH_TIME_MS 1500

#define BUTTON_UP 36
#define BUTTON_MID 37
#define BUTTON_DOWN 38

esp_err_t system_init(void);
esp_err_t ledc_init(void);
esp_err_t button_init(void);

typedef struct {
  int button_number;
  int button_status;
} button_behavior_t;

void button_isr_handler(void* arg);

