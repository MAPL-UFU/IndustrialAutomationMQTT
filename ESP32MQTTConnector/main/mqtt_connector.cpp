#pragma once
#include "esp_wifi.h"
#include "esp_system.h"
#include "nvs_flash.h"
#include "esp_event.h"
#include "esp_netif.h"
#include "protocol_examples_common.h"

#include "lwip/sockets.h"
#include "lwip/dns.h"
#include "lwip/netdb.h"

#include "wifi_lib.cpp"
#include "MQTTEventHandler.hpp"

void startMQTT( MQTTEventHandler* mqtt_controller, esp_event_loop_handle_t* event_loop)
{
    ESP_ERROR_CHECK(nvs_flash_init());
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());

    //ESP_ERROR_CHECK(example_connect());
    ESP_ERROR_CHECK(initialise_wifi());

    const esp_mqtt_client_config_t mqtt_cfg={
        .event_loop_handle = *event_loop,
        .host = CONFIG_MQTT_IP_ADRESS,
        .port = CONFIG_MQTT_IP_PORT
    };

    esp_mqtt_client_handle_t client = esp_mqtt_client_init(&mqtt_cfg);
    mqtt_controller->register_mqtt_events(client);
    esp_mqtt_client_start(client);
}
