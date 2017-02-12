
#include <FreeRTOS.h>
#include <ssid_config.h>

#include "espressif/esp_common.h"
#include <espressif/esp_sta.h>
#include <espressif/esp_wifi.h>

#ifndef INC_WIFI_H
#define INC_WIFI_H


void configure_wifi(const char *ssid, const char *passwd);

void wifi_task(void *pvParameters);

int is_wifi_alive();

// Initializes all the queue declared in this header file.
// Returns 0 on successful initialization. -1 for error.
int init_queues(void);

#endif
