#include <FreeRTOS.h>
#include <task.h>
#include <string.h>
#include <queue.h>
#include "espressif/esp_common.h"
#include "jsmn.h"

#include "queues.h"

#include "handle_aws_message.h"
#include "wifi.h"

extern QueueHandle_t aws_subscribe_queue;
#define GPIO_LED 2
#define GPIO_LED_RED 4
#define GPIO_LED_GREEN 5
#define GPIO_LED_BLUE 15
#define GPIO_LED_YELLOW 13

#define OFF 0
#define ON 1
#define BLINK 2
#define MAX_JSON_TOKENS 16

#define MAX_VALUE_SIZE 16


/* Define a type point to be a struct with integer members x, y */
typedef struct {
  int red;
  int green;
  int blue;
  int yellow;
} LedStatus;

static LedStatus current_status = {
  OFF /* red */,
  OFF /* green */,
  BLINK /* blue */,
  OFF /* yellow */
};

static int red = 0;
static int green = 0;
static int blue = 2;
static int yellow = 0;

static int extract_led_status(char *v) {
  char *s;
  int i = strtol(v, &s, 10);
  if (i == OFF || i == ON || i == BLINK) {
    return i;
  }
  return OFF;
}

static int jsoneq(const char *json, jsmntok_t *tok, const char *s) {
  if (tok->type == JSMN_STRING && (int) strlen(s) == tok->end - tok->start &&
      strncmp(json + tok->start, s, tok->end - tok->start) == 0) {
    return 0;
  }
  return -1;
}

void extractValue(const char *json, jsmntok_t *token, char* value) {
  int token_size = token->end - token->start;
  if ((token_size - 1) > sizeof(value)) {
    value[0] = '\0';
    return;
  }
#ifdef DEBUG
  printf("Extract value from token of size %d\r\n", token_size);
#endif
  if (value) {
    strncpy(value, json + token->start, token_size);
    value[token_size] = '\0';
#ifdef DEBUG
    printf("- Token: %.*s\n", token_size, json + token->start);
#endif
  }
#ifdef DEBUG
  printf("Returning extracted value %s \r\n", value);
#endif
}

void parse_json_message(char *msg) {
  int i;
  jsmntok_t tokens[MAX_JSON_TOKENS]; /* We expect no more than 64 tokens */
  jsmn_parser json_parser;
  jsmn_init(&json_parser);

#ifdef DEBUG
  printf("Initialized the JSON parser ");
#endif

  int r = jsmn_parse(&json_parser, msg, strlen(msg),
      tokens, sizeof(tokens)/sizeof(tokens[0]));
  if (r < 0) {
    printf("Failed to parse JSON: %d\n", r);
    return;
  } else {
#ifdef DEBUG
    printf("Message parsed. No tokens = %d\n", r);
#endif
  }

  /* Assume the top-level element is an object */
  if (r < 1 || tokens[0].type != JSMN_OBJECT) {
    printf("Object expected\n");
    return;
  }
  /* Loop over all keys of the root object */
  char v[MAX_VALUE_SIZE];
  for (i = 1; i < r; i++) {
    v[0] = '\0';
    if (jsoneq(msg, &(tokens[i]), "red") == 0) {
      extractValue(msg, &tokens[i+1], v);
#ifdef DEBUG
      printf ("red = %s\n ", v);
#endif
      current_status.red = extract_led_status(v);
      i++;
    } else if (jsoneq(msg, &(tokens[i]), "green") == 0) {
      extractValue(msg, &tokens[i+1], v);
#ifdef DEBUG
      printf ("green = %s\n ", v);
#endif
      current_status.green = extract_led_status(v);
      i++;
    } else if (jsoneq(msg, &(tokens[i]), "blue") == 0) {
      extractValue(msg, &tokens[i+1], v);
#ifdef DEBUG
      printf ("blue = %s\n ", v);
#endif
      current_status.blue = extract_led_status(v);
      i++;
    } else if (jsoneq(msg, &(tokens[i]), "yellow") == 0) {
      extractValue(msg, &tokens[i+1], v);
#ifdef DEBUG
      printf ("yellow = %s\n ", v);
#endif
      current_status.yellow = extract_led_status(v);
      i++;
    }
    else {
      printf("Unexpected key: %.*s\n", tokens[i].end-tokens[i].start,
        msg + tokens[i].start);
	  }
  }
  printf ("Parsed Status > red = %d, green = %d, blue = %d, yellow = %d",
      current_status.red, current_status.green, current_status.blue, current_status.yellow);
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
  set_gpio_value(GPIO_LED_BLUE, current_status.blue);
  set_gpio_value(GPIO_LED_YELLOW, current_status.yellow);
  set_gpio_value(GPIO_LED_RED, current_status.red);
  set_gpio_value(GPIO_LED_GREEN, current_status.green);
}

void handle_aws_message(char *payload) {
  int len = strlen(payload);
#ifdef DEBUG
  printf("Processing payload %s", payload);
#endif  
  parse_json_message(payload);
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
  char msg[SUBSCRIBE_QUEUE_ITEM_SIZE];
  while(1) {
    if (xQueueReceive(aws_subscribe_queue, (void *) msg, 0) == pdTRUE) {
      handle_aws_message((char *) msg);
    }
    update_gpios();
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }

}
