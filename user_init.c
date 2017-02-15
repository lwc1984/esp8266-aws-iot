/*
 * Derived from examples/mqtt_client/mqtt_client.c - added TLS1.2 support and some minor modifications.
 */
#include "espressif/esp_common.h"
#include "esp/uart.h"

#include <string.h>

#include <FreeRTOS.h>
#include <task.h>
#include <queue.h>
#include <ssid_config.h>

#include "aws_iot.h"
#include "handle_aws_message.h"
#include "wifi.h"
#include "queues.h"
#include "beat.h"


void user_init(void) {
  uart_set_baud(0, 115200);
  printf("SDK version: %s, free heap %u\n", sdk_system_get_sdk_version(),
        xPortGetFreeHeapSize());

  init_queues();
  configure_wifi(WIFI_SSID, WIFI_PASS);
  init_handle_aws_message_task();
  init_beat_task();

  xTaskCreate(&wifi_task, "wifi_task", 256, NULL, 2, NULL);
  xTaskCreate(&beat_task, "beat_task", 256, NULL, 2, NULL);
  xTaskCreate(&aws_iot_task, "aws_iot_task", 2048, NULL, 2, NULL);
  xTaskCreate(&handle_aws_message_task, "handle_aws_message_task", 256, NULL, 2, NULL);
}
