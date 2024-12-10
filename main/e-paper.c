/* 
 * @filename: e-paper.c
 * @author:   k.wang
 * @brief:    This is main function of e-paper app, including system initialize and startup tasks
 * @version:  1.0
 * @note:     
 */
#include <stdio.h>
#include "system_init.h"
#include "esp_clk_tree.h"
#include "driver/ledc.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define INIT_BREATH_LIGHT 500

void app_main(void)
{
  // 系统初始化
  ESP_ERROR_CHECK(system_init());

  // 初始化成功后依次点亮红、绿、蓝灯
  ESP_ERROR_CHECK(ledc_fade_func_install(0));
  for (uint8_t led_channel = 0; led_channel < LEDC_CHANNELS_3; led_channel++) {
    ESP_ERROR_CHECK(ledc_set_fade_time_and_start(LEDC_LOW_SPEED_MODE, led_channel, LEDC_FREQUENCY_1024, INIT_BREATH_LIGHT, LEDC_FADE_NO_WAIT));
    vTaskDelay(INIT_BREATH_LIGHT/portTICK_PERIOD_MS);
    ESP_ERROR_CHECK(ledc_set_fade_time_and_start(LEDC_LOW_SPEED_MODE, led_channel, 0, INIT_BREATH_LIGHT, LEDC_FADE_NO_WAIT));
    vTaskDelay(INIT_BREATH_LIGHT/portTICK_PERIOD_MS);
  }
}

