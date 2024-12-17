#include "system_init.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "led_indicator.h"
#include "led_behavior.h"

static const char *TAG_LED = "RGB LED";

enum {
  LED_INIT = 0,
  LED_INIT_DONE,
  LED_BLINK_MAX,
};

blink_step_t const *led_blink_mode[] = {
  [LED_INIT] = ledc_red_blink_fast,
  [LED_INIT_DONE] = ledc_green_breathe,
  [LED_BLINK_MAX] = NULL,
};

esp_err_t system_init(void)
{
  /* 初始化LED */
  led_indicator_handle_t led_indicator_handle = ledc_init();
  if(NULL == led_indicator_handle) {
    ESP_LOGW(TAG_LED, "handle get NULL");
  } else {
    ESP_LOGI(TAG_LED, "handle get succeed");
  }
  /* 初始化中红灯100毫秒间隔快闪 */
  ESP_ERROR_CHECK(led_indicator_start(led_indicator_handle, LED_INIT));

  /* 初始化按键 */
  ESP_ERROR_CHECK(button_init());

  /* 初始化结束绿灯呼吸2秒 */
  ESP_ERROR_CHECK(led_indicator_stop(led_indicator_handle, LED_INIT));
  ESP_ERROR_CHECK(led_indicator_start(led_indicator_handle, LED_INIT_DONE));

  return ESP_OK;
}

led_indicator_handle_t ledc_init(void)
{
  led_indicator_rgb_config_t rgb_config = {
    .is_active_level_high = false,
    .timer_inited = false,
    .timer_num = LEDC_TIMER_0,
    .red_gpio_num = LEDC_LEDR,
    .green_gpio_num = LEDC_LEDG,
    .blue_gpio_num = LEDC_LEDB,
    .red_channel = LEDC_CHANNEL_0,
    .green_channel = LEDC_CHANNEL_1,
    .blue_channel = LEDC_CHANNEL_2,
  };
  led_indicator_config_t led_config = {
    .mode = LED_RGB_MODE,
    .led_indicator_rgb_config = &rgb_config,
    .blink_lists = led_blink_mode,
    .blink_list_num = LED_BLINK_MAX,
  };
  led_indicator_handle_t led_handle = led_indicator_create(&led_config);
  if(NULL == led_handle) {
    ESP_LOGW(TAG_LED, "create failed");
    return NULL;
  } else {
    ESP_LOGI(TAG_LED, "create succeed");
  }

  return led_handle;
}

esp_err_t button_init(void)
{
  vTaskDelay(5000 / portTICK_PERIOD_MS);
  return ESP_OK;
}

