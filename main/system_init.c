#include "system_init.h"
#include "driver/ledc.h"

esp_err_t system_init(void)
{
  ESP_ERROR_CHECK(ledc_init());

  return ESP_OK;
}

esp_err_t ledc_init(void)
{
  // Parameters of ledc_timer_config function
  ledc_timer_config_t ledc_timer = {
    .speed_mode = LEDC_LOW_SPEED_MODE,
    .duty_resolution = LEDC_TIMER_10_BIT,
    .timer_num = LEDC_TIMER_0,
    .freq_hz = LEDC_FREQUENCY_1024,
    .clk_cfg = LEDC_USE_APB_CLK,
    .deconfigure = false,
  };
  // Apply LEDC PWM timer configuration
  ESP_ERROR_CHECK(ledc_timer_config(&ledc_timer));

  // Parameters of ledc_channel_config function
  ledc_channel_config_t ledc_channel[LEDC_CHANNELS_3] = {
    {
      .gpio_num = LEDC_LEDR,
      .speed_mode = ledc_timer.speed_mode,
      .channel = LEDC_CHANNEL_0,
      .intr_type = LEDC_INTR_DISABLE,
      .timer_sel = ledc_timer.timer_num,
      .duty = 0,
      .hpoint = 0,
      .flags.output_invert = 1,
    },
    {
      .gpio_num = LEDC_LEDG,
      .speed_mode = ledc_timer.speed_mode,
      .channel = LEDC_CHANNEL_1,
      .intr_type = LEDC_INTR_DISABLE,
      .timer_sel = ledc_timer.timer_num,
      .duty = 0,
      .hpoint = 0,
      .flags.output_invert = 1,
    },
    {
      .gpio_num = LEDC_LEDB,
      .speed_mode = ledc_timer.speed_mode,
      .channel = LEDC_CHANNEL_2,
      .intr_type = LEDC_INTR_DISABLE,
      .timer_sel = ledc_timer.timer_num,
      .duty = 0,
      .hpoint = 0,
      .flags.output_invert = 1,
    },
  };
  // Apply LEDC channel
  for (uint8_t channels = 0; channels < LEDC_CHANNELS_3; channels++) {
    ESP_ERROR_CHECK(ledc_channel_config(&ledc_channel[channels]));
  }

  return ESP_OK;
}

