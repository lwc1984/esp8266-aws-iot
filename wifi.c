#include "wifi.h"
#include <string.h>
#include <task.h>

static struct sdk_station_config config;
static int __wifi_alive = 0;

void configure_wifi(const char *ssid, const char *passwd) {
  strncpy((char *)config.ssid, ssid, sizeof(config.ssid));
  strncpy((char *)config.password, passwd, sizeof(config.password));
  printf("Setting wifi ssid to %s\n\r", config.ssid);
}

int is_wifi_alive() {
  return __wifi_alive;
}

void wifi_task(void *pvParameters) {
    uint8_t status = 0;
    uint8_t retries = 30;

    printf("%s: Connecting to WiFi\n\r", config.ssid);
    sdk_wifi_set_opmode (STATION_MODE);
    sdk_wifi_station_set_config(&config);

    while (1) {
        __wifi_alive = 0;

        while ((status != STATION_GOT_IP) && (retries)) {
            status = sdk_wifi_station_get_connect_status();
            printf("%s: status = %d\n\r", __func__, status);
            if (status == STATION_WRONG_PASSWORD) {
                printf("WiFi: wrong password\n\r");
                break;
            } else if (status == STATION_NO_AP_FOUND) {
                printf("WiFi: AP not found\n\r");
                break;
            } else if (status == STATION_CONNECT_FAIL) {
                printf("WiFi: connection failed\r\n");
                break;
            }
            vTaskDelay(1000 / portTICK_PERIOD_MS);
            --retries;
        }

        while ((status = sdk_wifi_station_get_connect_status())
                == STATION_GOT_IP) {
            if (__wifi_alive == 0) {
                printf("WiFi: Connected\n\r");
                __wifi_alive = 1;
            }
            vTaskDelay(500 / portTICK_PERIOD_MS);
        }

        __wifi_alive = 0;
        printf("WiFi: disconnected\n\r");
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}
