#include "system_init.h"
#include "esp_log.h"
#include "driver/ledc.h"
#include "driver/gpio.h"
#include "freertos_tasks.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

esp_err_t system_init(void)
{
  static const char *TAG = "System Init";

  ESP_ERROR_CHECK(ledc_init());

  TaskHandle_t led_init_behavior_task_handle;
  BaseType_t led_init_behavior_task_return = xTaskCreate(led_init_behavior_task, "led init status", 1024, NULL, 16, &led_init_behavior_task_handle);

  if (led_init_behavior_task_return == pdPASS) {
    ESP_LOGI(TAG, "LED Breathing");
  } else {
    ESP_LOGW(TAG, "LED Task Create Fail");
  }

  ESP_ERROR_CHECK(button_init());
  vTaskDelete(led_init_behavior_task_handle);

  return ESP_OK;
}

esp_err_t ledc_init(void)
{
  // Parameters of ledc_timer_config function
  ledc_timer_config_t ledc_timer = {
    .speed_mode = LEDC_LOW_SPEED_MODE,
    .duty_resolution = LEDC_TIMER_10_BIT,
    .timer_num = LEDC_TIMER_0,
    .freq_hz = LED_TIMER_FREQUENCY,
    .clk_cfg = LEDC_USE_APB_CLK,
    .deconfigure = false,
  };
  // Apply LEDC PWM timer configuration
  ESP_ERROR_CHECK(ledc_timer_config(&ledc_timer));

  // Parameters of ledc_channel_config function
  ledc_channel_config_t ledc_channel[LED_CHANNELS] = {
    {
      .gpio_num = LED_LEDR,
      .speed_mode = ledc_timer.speed_mode,
      .channel = LEDC_CHANNEL_0,
      .intr_type = LEDC_INTR_DISABLE,
      .timer_sel = ledc_timer.timer_num,
      .duty = 0,
      .hpoint = 0,
      .flags.output_invert = 1,
    },
    {
      .gpio_num = LED_LEDG,
      .speed_mode = ledc_timer.speed_mode,
      .channel = LEDC_CHANNEL_1,
      .intr_type = LEDC_INTR_DISABLE,
      .timer_sel = ledc_timer.timer_num,
      .duty = 0,
      .hpoint = 0,
      .flags.output_invert = 1,
    },
    {
      .gpio_num = LED_LEDB,
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
  for (uint8_t channels = 0; channels < LED_CHANNELS; channels++) {
    ESP_ERROR_CHECK(ledc_channel_config(&ledc_channel[channels]));
  }

  return ESP_OK;
}

esp_err_t button_init(void)
{
  // Parameters of gpio_config function
  gpio_config_t button_config;
  button_config.pin_bit_mask = (1ULL << BUTTON_UP) | (1ULL << BUTTON_MID) | (1ULL << BUTTON_DOWN);
  button_config.mode = GPIO_MODE_INPUT;
  button_config.pull_up_en = GPIO_PULLUP_DISABLE;
  button_config.pull_down_en = GPIO_PULLDOWN_ENABLE;
  button_config.intr_type = GPIO_INTR_ANYEDGE;
  // Apply button gpio config
  gpio_config(&button_config);
  
  // Turn on ISR service
  ESP_ERROR_CHECK(gpio_install_isr_service(ESP_INTR_FLAG_EDGE));
  // Add ISR handler
  ESP_ERROR_CHECK(gpio_isr_handler_add(BUTTON_UP, button_isr_handler, (void*)BUTTON_UP));
  ESP_ERROR_CHECK(gpio_isr_handler_add(BUTTON_MID, button_isr_handler, (void*)BUTTON_MID));
  ESP_ERROR_CHECK(gpio_isr_handler_add(BUTTON_DOWN, button_isr_handler, (void*)BUTTON_DOWN));

  return ESP_OK;
}

