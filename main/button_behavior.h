#pragma once

#include "driver/gpio.h"

#define BUTTON_UP 36
#define BUTTON_MID 37
#define BUTTON_DOWN 38

void button_up_handler(void *arg);
void button_mid_handler(void *arg);
void button_down_handler(void *arg);

