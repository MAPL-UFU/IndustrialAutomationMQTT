#pragma once
#include <string.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_wifi.h"
#include "esp_wpa2.h"
#include "esp_event.h"
#include "esp_log.h"
#include "esp_system.h"
#include "esp_netif.h"

#define EXAMPLE_WIFI_SSID CONFIG_EXAMPLE_WIFI_SSID

#define EXAMPLE_EAP_ID CONFIG_EXAMPLE_EAP_ID
#define EXAMPLE_EAP_USERNAME CONFIG_EXAMPLE_EAP_USERNAME
#define EXAMPLE_EAP_PASSWORD CONFIG_EXAMPLE_EAP_PASSWORD

static SemaphoreHandle_t s_semph_get_ip_addrs = NULL;

static esp_netif_t *sta_netif = NULL;

static const char *TAG = "WiFi Enterprise Client";

esp_eap_ttls_phase2_types TTLS_PHASE2_METHOD = (esp_eap_ttls_phase2_types)CONFIG_EXAMPLE_EAP_METHOD_TTLS_PHASE_2;

static void event_handler(void* arg, esp_event_base_t event_base,
                                int32_t event_id, void* event_data)
{
    if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_START) {
        esp_wifi_connect();
    } else if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_DISCONNECTED) {
        esp_wifi_connect();
    } else if (event_id == IP_EVENT_STA_GOT_IP) {
        xSemaphoreGive(s_semph_get_ip_addrs);
    }
}

static int initialise_wifi(void)
{   
    s_semph_get_ip_addrs = xSemaphoreCreateBinary();
    if (s_semph_get_ip_addrs != NULL) {
        wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
        ESP_ERROR_CHECK(esp_netif_init());

        sta_netif = esp_netif_create_default_wifi_sta();
        assert(sta_netif);

        ESP_ERROR_CHECK( esp_wifi_init(&cfg) );
        ESP_ERROR_CHECK( esp_event_handler_register(WIFI_EVENT, ESP_EVENT_ANY_ID, &event_handler, NULL) );
        ESP_ERROR_CHECK( esp_event_handler_register(IP_EVENT, IP_EVENT_STA_GOT_IP, &event_handler, NULL) );
        ESP_ERROR_CHECK( esp_wifi_set_storage(WIFI_STORAGE_RAM) );

        // C++ 17 não aceita nested Initializer  
        wifi_sta_config_t sta_config = {
                {.ssid = EXAMPLE_WIFI_SSID}
        };
        wifi_config_t wifi_config = {
            .sta = sta_config
        };
        ESP_LOGI(TAG, "Setting WiFi configuration SSID %s...", wifi_config.sta.ssid);
        ESP_ERROR_CHECK( esp_wifi_set_mode(WIFI_MODE_STA) );
        ESP_ERROR_CHECK( esp_wifi_set_config(WIFI_IF_STA, &wifi_config) );
        ESP_ERROR_CHECK( esp_wifi_sta_wpa2_ent_set_identity((uint8_t *)EXAMPLE_EAP_ID, strlen(EXAMPLE_EAP_ID)) );

        ESP_ERROR_CHECK( esp_wifi_sta_wpa2_ent_set_username((uint8_t *)EXAMPLE_EAP_USERNAME, strlen(EXAMPLE_EAP_USERNAME)) );
        ESP_ERROR_CHECK( esp_wifi_sta_wpa2_ent_set_password((uint8_t *)EXAMPLE_EAP_PASSWORD, strlen(EXAMPLE_EAP_PASSWORD)) );

        ESP_ERROR_CHECK( esp_wifi_sta_wpa2_ent_set_ttls_phase2_method(TTLS_PHASE2_METHOD) );

        ESP_ERROR_CHECK( esp_wifi_sta_wpa2_ent_enable() );
        ESP_ERROR_CHECK( esp_wifi_start() );

        if (xSemaphoreTake(s_semph_get_ip_addrs, 60000 / portTICK_PERIOD_MS) == pdTRUE) {
            ESP_LOGI(TAG, "Got IP address.");
            vSemaphoreDelete(s_semph_get_ip_addrs);
            return 0;
        } else {
            ESP_LOGE(TAG, "Failed to get IP address");
            return -1;
        }
    } else {
        ESP_LOGE(TAG, "Failed to create semaphore");
        return -1;
    }
}
    