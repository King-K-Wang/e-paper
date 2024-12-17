#pragma once

#include "led_indicator.h"

const blink_step_t ledc_red_blink_fast[] = {
  {LED_BLINK_HSV, SET_HSV(0, 0xC0, 0x0F), 0},
  {LED_BLINK_HOLD, LED_STATE_ON, 100},
  {LED_BLINK_HOLD, LED_STATE_OFF, 100},
  {LED_BLINK_LOOP, 0, 0},
};

const blink_step_t ledc_green_breathe[] = {
  {LED_BLINK_HSV, SET_HSV(0x60, 0xC0, 0x0F), 0},
  {LED_BLINK_HSV_RING, SET_HSV(0x80, 0xA0, 0x60), 500},
  {LED_BLINK_HSV_RING, SET_HSV(0x60, 0xC0, 0x0F), 500},
  {LED_BLINK_HSV_RING, SET_HSV(0x80, 0xA0, 0x60), 500},
  {LED_BLINK_HSV_RING, SET_HSV(0x60, 0xC0, 0x0F), 500},
  {LED_BLINK_STOP, 0, 0},
};

