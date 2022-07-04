#pragma once
#include "esp_wifi.h"
#include "esp_system.h"
#include "nvs_flash.h"
#include "esp_event.h"
#include "esp_netif.h"

#include "lwip/sockets.h"
#include "lwip/dns.h"
#include "lwip/netdb.h"

#include "mqtt_client.h"
#include "MQTTEventHandler.hpp"
#include "WifiEventHandler.hpp"

extern const uint8_t client_cert_pem_start[] asm("_binary_actuator_certificate_pem_crt_start");
extern const uint8_t client_cert_pem_end[] asm("_binary_actuator_certificate_pem_crt_end");
extern const uint8_t client_key_pem_start[] asm("_binary_actuator_private_pem_key_start");
extern const uint8_t client_key_pem_end[] asm("_binary_actuator_private_pem_key_end");
extern const uint8_t server_cert_pem_start[] asm("_binary_amazon_root_pem_start");
extern const uint8_t server_cert_pem_end[] asm("_binary_amazon_root_pem_end");

void startMQTT( MQTTEventHandler* mqtt_controller, esp_event_loop_handle_t* event_loop)
{
    ESP_ERROR_CHECK(nvs_flash_init());
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());


    WifiEventHandler* wifi_controller = new WifiEventHandler();
    wifi_controller->initialise_wifi();


    const esp_mqtt_client_config_t mqtt_cfg={
        .event_loop_handle = *event_loop,
        .host = CONFIG_MQTT_IP_ADRESS,
        .port = CONFIG_MQTT_IP_PORT,
        .username = "mapl-iot",
        .password = "NgJlVBYOkeNK2GIw"
        //.client_id = "AActuator", 
        //.cert_pem = (const char *)server_cert_pem_start,
        //.client_cert_pem = (const char *)client_cert_pem_start,
        //.client_key_pem = (const char *)client_key_pem_start,
        //.transport = MQTT_TRANSPORT_OVER_SSL,
        //.protocol_ver = MQTT_PROTOCOL_V_3_1_1
    };

    esp_mqtt_client_handle_t client = esp_mqtt_client_init(&mqtt_cfg);
    mqtt_controller->register_mqtt_events(client);
    esp_mqtt_client_start(client);
}
