#include <FreeRTOS.h>
#include <task.h>
#include <queue.h>

#include "beat.h"
#include "wifi.h"

extern QueueHandle_t aws_publish_queue;

void beat_task(void *pvParameters) {
  char msg[16];
  int count = 0;

  while (1) {
    if (!is_wifi_alive()) {
      vTaskDelay(1000 / portTICK_PERIOD_MS);
      continue;
    }

    printf("Schedule to publish\r\n");

    snprintf(msg, sizeof(msg), "%d", count);
    if (xQueueSend(aws_publish_queue, (void *) msg, 0) == pdFALSE) {
      printf("Publish queue overflow\r\n");
    }

    vTaskDelay(10000 / portTICK_PERIOD_MS);
  }
}
