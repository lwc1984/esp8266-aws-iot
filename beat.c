#include <FreeRTOS.h>
#include <task.h>
#include <queue.h>
#include "espressif/esp_common.h"

#include "beat.h"
#include "wifi.h"
#include "esp8266.h"
 
extern QueueHandle_t aws_publish_queue;

static QueueHandle_t tsqueue;

const int gpio = 12;   /* gpio 0 usually has "PROGRAM" button attached */
const int active = 1; /* active == 0 for active low */
const gpio_inttype_t int_type = GPIO_INTTYPE_EDGE_POS;

 
void init_beat_task() {
  gpio_enable(gpio, GPIO_INPUT);
  tsqueue = xQueueCreate(2, sizeof(uint32_t));
}

void gpio_intr_handler(uint8_t gpio_num) {
  uint32_t now = xTaskGetTickCountFromISR();
  xQueueSendToBackFromISR(tsqueue, &now, NULL);
}

void send_aws_message() {
  char msg[16];
  int count = 0;

  if (!is_wifi_alive()) {
	printf("Wifi is down\r\n");
	return;
  }

  printf("Schedule to publish\r\n");

  snprintf(msg, sizeof(msg), "%d", count);
  if (xQueueSend(aws_publish_queue, (void *) msg, 0) == pdFALSE) {
  	printf("Publish queue overflow\r\n");
  }
} 

void beat_task(void *pvParameters) {
  printf("Waiting for button press interrupt on gpio %d...\r\n", gpio);
  gpio_set_interrupt(gpio, int_type, gpio_intr_handler);

  uint32_t last = 0;
  while(1) {
  	uint32_t button_ts;
    xQueueReceive(tsqueue, &button_ts, portMAX_DELAY);
    button_ts *= portTICK_PERIOD_MS;
    if(last < button_ts-5000) {
    	printf("Button interrupt fired at %dms\r\n", button_ts);
        last = button_ts;
		send_aws_message();
    }
    vTaskDelay(100 / portTICK_PERIOD_MS);
  }
}


