#include "freertos_tasks.h"
#include "driver/ledc.h"
#include "system_init.h"

/**
 * @function: led_init_behavior_task
 * @brief: When system is initializing, led breathe function
 * @param: (void*) should be NULL
 * @return: None
 * @note: Create and delete the task in system init function
 */
void led_init_behavior_task(void *pvParameter)
{
  ESP_ERROR_CHECK(ledc_fade_func_install(0));
  for (;;) {
    for (uint8_t led_channel = 0; led_channel < LED_CHANNELS; led_channel++) {
      ESP_ERROR_CHECK(ledc_set_fade_time_and_start(LEDC_LOW_SPEED_MODE, led_channel, LED_TIMER_FREQUENCY, LED_INIT_BREATH_TIME_MS, LEDC_FADE_NO_WAIT));
      vTaskDelay(LED_INIT_BREATH_TIME_MS / portTICK_PERIOD_MS);
      ESP_ERROR_CHECK(ledc_set_fade_time_and_start(LEDC_LOW_SPEED_MODE, led_channel, 0, LED_INIT_BREATH_TIME_MS, LEDC_FADE_NO_WAIT));
      vTaskDelay(LED_INIT_BREATH_TIME_MS / portTICK_PERIOD_MS);
    }
  }
}

