#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "system_init.h"
#include "freertos_tasks.h"

QueueHandle_t button_queue = NULL;
/**
 * @function: button_isr_handler
 * @brief: button GPIO isr handler
 * @param: (void*) should be gpio number
 * @return: None
 * @note: GPIO 36 and GPIO 39 should not be used(will fix in next hardware board)
 */
void IRAM_ATTR button_isr_handler(void* arg)
{
  button_behavior_t button_behavior;
  button_behavior.button_number = (int) arg;
  button_behavior.button_status = gpio_get_level(button_behavior.button_number);
  xQueueSendFromISR(button_queue, &button_behavior, NULL);
}

/**
 * @function: button_behavior_task
 * @brief: button behavior
 * @param: (void*) should be button_behavior struct
 * @return: None
 * @note: GPIO 36 and GPIO 39 should not be used(will fix in next hardware board)
 */
void button_behavior_task(void *pvParameter)
{
}

