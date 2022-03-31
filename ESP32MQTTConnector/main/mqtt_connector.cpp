#include <iostream>
#include <string>

#include "esp_wifi.h"
#include "esp_system.h"
#include "nvs_flash.h"
#include "esp_event.h"
#include "esp_netif.h"
#include "protocol_examples_common.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "freertos/queue.h"

#include "lwip/sockets.h"
#include "lwip/dns.h"
#include "lwip/netdb.h"

#include "esp_log.h"
#include "mqtt_client.h"
#include "event_design.hpp"

void startMQTT(esp_event_loop_handle_t* event_loop)
{
    ESP_ERROR_CHECK(nvs_flash_init());
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());

    ESP_ERROR_CHECK(example_connect());

    const esp_mqtt_client_config_t mqtt_cfg={
        .event_loop_handle = *event_loop,
        .host = CONFIG_MQTT_IP_ADRESS,
        .port = CONFIG_MQTT_IP_PORT
    };

    esp_mqtt_client_handle_t client = esp_mqtt_client_init(&mqtt_cfg);
    /* The last argument may be used to pass data to the event handler, in this example mqtt_event_handler */
    MQTTEventHandler* handler = new MQTTEventHandler();
    handler->register_mqtt_events(client);
    //register_mqtt_events(client);
    //register_custom_events(event_loop);
    esp_mqtt_client_start(client);


}
