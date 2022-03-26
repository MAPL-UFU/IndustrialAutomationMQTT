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

using namespace std;

static void mqtt_event_handler(void *handler_args, esp_event_base_t base, int32_t event_id, void *event_data)
{
    ESP_LOGD(PROGRAM_TAG, "Event dispatched from event loop base=%s, event_id=%d", base, event_id);
    esp_mqtt_event_handle_t event = (esp_mqtt_event_handle_t)event_data;
    esp_mqtt_client_handle_t client = event->client;
    int msg_id;
    switch (event_id) {
    case MQTT_EVENT_CONNECTED:{
        ESP_LOGI(PROGRAM_TAG, "MQTT_EVENT_CONNECTED");
        msg_id = esp_mqtt_client_subscribe(client, "teste", 0);
        msg_id = esp_mqtt_client_publish(client, "teste_pub", "ESP_Connected", 0, 0, 0);
        ESP_LOGI(PROGRAM_TAG, "sent subscribe successful, msg_id=%d", msg_id);
    }break;

    case MQTT_EVENT_DISCONNECTED:{
        ESP_LOGI(PROGRAM_TAG, "MQTT_EVENT_DISCONNECTED");
    }break;

    case MQTT_EVENT_SUBSCRIBED:{
        ESP_LOGI(PROGRAM_TAG, "MQTT_EVENT_SUBSCRIBED, msg_id=%d", event->msg_id);
    }break;
    
    case MQTT_EVENT_UNSUBSCRIBED:{
        ESP_LOGI(PROGRAM_TAG, "MQTT_EVENT_UNSUBSCRIBED, msg_id=%d", event->msg_id);
    }break;
    
    case MQTT_EVENT_ERROR:{
        ESP_LOGI(PROGRAM_TAG, "MQTT_EVENT_ERROR");
    }break;

    case MQTT_EVENT_DATA:{
        ESP_LOGI(PROGRAM_TAG, "MQTT_EVENT_DATA");    
        string str(event->data, event->data_len);
        cout<<str<<endl;
    }break;
    
    //case EVENT_ID_SEND_INTEGER:
    //    msg_id = esp_mqtt_client_publish(client, "teste_pub", event_data, 0, 0, 0);
    //    ESP_LOGI(PROGRAM_TAG, "MQTT_SEND_INTEGER", event->event_id);
    //    break;
    //
    //case EVENT_ID_SEND_STRING:
    //    msg_id = esp_mqtt_client_publish(client, "teste_pub", event_data, 0, 0, 0);
    //    ESP_LOGI(PROGRAM_TAG, "MQTT_SEND_STRING", event->event_id);
    //    break;
    //
    default:{
        ESP_LOGI(PROGRAM_TAG, "Other event id:%d", event->event_id);
    }break;
    
    }
}

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

    cout<<"MQTT_IP_ADRESS: "<<CONFIG_MQTT_IP_ADRESS<<endl;
    cout<<"MQTT_IP_PORT: "<<CONFIG_MQTT_IP_PORT<<endl;
    esp_mqtt_client_handle_t client = esp_mqtt_client_init(&mqtt_cfg);
    /* The last argument may be used to pass data to the event handler, in this example mqtt_event_handler */
    esp_mqtt_client_register_event(client, (esp_mqtt_event_id_t)MQTT_EVENT_ANY, mqtt_event_handler, NULL);
    esp_mqtt_client_start(client);

    ESP_ERROR_CHECK(esp_event_post_to(*event_loop , MAIN_EVENT, 22, NULL,0,0));

}
