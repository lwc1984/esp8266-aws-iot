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
#define GPIO_LED_RED 4
#define GPIO_LED_GREEN 5
#define GPIO_LED_BLUE 15
#define GPIO_LED_YELLOW 13

static int red = 0;
static int green = 0;
static int blue = 2;
static int yellow = 0;

static const int OFF = 0;
static const int ON = 1;

int getIntValue(char value) {
  switch(value) {
    case '2':
      return 2;
    case '1':
      return 1;
    default:
      return 0;
  }
}


void update_rgb_values(char color, char value) {
  int intValue = getIntValue(value);
  if (color == 'r') {
    red = intValue;
  } else if (color == 'g') {
    green = intValue;
  } else if (color == 'b') {
    blue = intValue;
  } else if (color == 'y') {
    yellow = intValue;
  }
  printf ("red = %d, green = %d, blue = %d, yellow = %d", red, green, blue, yellow);
}

int toggle(int value) {
  if (value == 0) {
    return 1;
  } else {
    return 0;
  }
}

void set_gpio_value(int gpio, int value) {
  int current_value = 0;
  switch(value) {
    case 2:
        current_value = gpio_read(gpio);
        gpio_write(gpio, toggle(current_value));
        break;
    case 1:
        gpio_write(gpio, ON);
        break;
    default:
        gpio_write(gpio, OFF);
  }

}

void update_gpios() {
  set_gpio_value(GPIO_LED_BLUE, blue);
  set_gpio_value(GPIO_LED_YELLOW, yellow);
  set_gpio_value(GPIO_LED_RED, red);
  set_gpio_value(GPIO_LED_GREEN, green);
}

void handle_aws_message(char *payload) {
  int len = sizeof(payload);
  printf("Processing payload %s", payload);
  int i = 0;
  if (len > 0 && len % 2 == 0) {
    for (i = 0 ; i < len - 1; i+=2) {
      char color = payload[i];
      char value = payload[i + 1];
      update_rgb_values(color, value);
    }
  }
}


void init_handle_aws_message_task() {
  gpio_enable(GPIO_LED, GPIO_OUTPUT);
  gpio_enable(GPIO_LED_BLUE, GPIO_OUTPUT);
  gpio_enable(GPIO_LED_YELLOW, GPIO_OUTPUT);
  gpio_enable(GPIO_LED_RED, GPIO_OUTPUT);
  gpio_enable(GPIO_LED_GREEN, GPIO_OUTPUT);
  gpio_write(GPIO_LED, 0);
  gpio_write(GPIO_LED_BLUE, 1);
  gpio_write(GPIO_LED_YELLOW, 1);
  gpio_write(GPIO_LED_RED, 1);
  gpio_write(GPIO_LED_GREEN, 1);
}

void handle_aws_message_task(void *pvParameters) {
  char msg[64];
  while(1) {
    if (xQueueReceive(aws_subscribe_queue, (void *) msg, 0) == pdTRUE) {
      handle_aws_message((char *) msg);
    }
    update_gpios();
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }

}
