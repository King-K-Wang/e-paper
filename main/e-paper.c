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

  for (;;) {
    vTaskDelay(10000 / portTICK_PERIOD_MS);
  }
}

