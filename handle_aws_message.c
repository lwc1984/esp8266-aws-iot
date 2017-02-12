#include <FreeRTOS.h>
#include <task.h>
#include <string.h>
#include <queue.h>
#include "espressif/esp_common.h"

#include "queues.h"

#include "handle_aws_message.h"
#include "wifi.h"

extern QueueHandle_t aws_subscribe_queue;
#define GPIO_LED 2

void handle_aws_message(char *payload) {
  if (!strncmp(payload, "on", 2)) {
  	printf("Turning on LED\r\n");
    gpio_write(GPIO_LED, 0);
  } else if (!strncmp(payload, "off", 3)) {
  	printf("Turning off LED\r\n");
    gpio_write(GPIO_LED, 1);
  }
}

void init_handle_aws_message_task() {
  gpio_enable(GPIO_LED, GPIO_OUTPUT);
  gpio_write(GPIO_LED, 1);
}

void handle_aws_message_task(void *pvParameters) {
  char msg[64];
  while(1) {
    if (xQueueReceive(aws_subscribe_queue, (void *) msg, 0) == pdTRUE) {
      handle_aws_message((char *) msg);
    }

    vTaskDelay(10000 / portTICK_PERIOD_MS);
  }

}
