#include <cstdio>
#include <functional>
#include <iostream>

#include "mqtt_client.h"
#include "esp_event.h"
#include "event_design.hpp"
#include "esp_log.h"


ESP_EVENT_DEFINE_BASE(CUSTOM_EVENT_BASE);

using namespace std;

void MQTTEventHandler::register_mqtt_events(esp_mqtt_client* client)
{
    this->client = client;
    esp_mqtt_client_register_event(this->client, MQTT_EVENT_CONNECTED, MQTTEventHandler::onEventConnected,this);
    esp_mqtt_client_register_event(this->client, MQTT_EVENT_DISCONNECTED, MQTTEventHandler::onEventDisconnected,this);
    esp_mqtt_client_register_event(this->client, MQTT_EVENT_SUBSCRIBED, MQTTEventHandler::onEventSubscribed,this);
    esp_mqtt_client_register_event(this->client, MQTT_EVENT_UNSUBSCRIBED, MQTTEventHandler::onEventUnsubscribed,this);
    esp_mqtt_client_register_event(this->client, MQTT_EVENT_ERROR, MQTTEventHandler::onEventError,this);
    esp_mqtt_client_register_event(this->client, MQTT_EVENT_DATA, MQTTEventHandler::onEventData,this);
}

void MQTTEventHandler::onEventConnected(void *handler_args, esp_event_base_t base, int32_t event_id, void *event_data){
    MQTTEventHandler* context = (MQTTEventHandler*)handler_args;
    context->log("ESP MQTT Connected");
    esp_mqtt_client_subscribe(context->client, "/teste", 0);
}

void MQTTEventHandler::onEventDisconnected(void *handler_args, esp_event_base_t base, int32_t event_id, void *event_data){
    MQTTEventHandler* context = (MQTTEventHandler*)handler_args;
    context->log("ESP MQTT Disconnected");
}

void MQTTEventHandler::onEventSubscribed(void *handler_args, esp_event_base_t base, int32_t event_id, void *event_data){
    MQTTEventHandler* context = (MQTTEventHandler*)handler_args;
    context->log("ESP MQTT Subscribed");
}

void MQTTEventHandler::onEventUnsubscribed(void *handler_args, esp_event_base_t base, int32_t event_id, void *event_data){
    MQTTEventHandler* context = (MQTTEventHandler*)handler_args;
    context->log("ESP MQTT Unsubscribed");
}

void MQTTEventHandler::onEventError(void *handler_args, esp_event_base_t base, int32_t event_id, void *event_data){
    MQTTEventHandler* context = (MQTTEventHandler*)handler_args;
    context->log("ESP MQTT Error");
}

void MQTTEventHandler::onEventData(void *handler_args, esp_event_base_t base, int32_t event_id, void *event_data){
    MQTTEventHandler* context = (MQTTEventHandler*)handler_args;
    context->log("ESP MQTT Data");

    esp_mqtt_event_handle_t event = (esp_mqtt_event_handle_t)event_data;
    string topic(event->topic, event->topic_len);
    string payload(event->data, event->data_len);
    context->log("Topic: " + topic);
    context->log("Payload: " + payload);
}

void MQTTEventHandler::log(string message){
    if (LOG_LOCAL_LEVEL >= ESP_LOG_INFO) {
        const char* format = "I (%d) %s: %s\n"; 
        printf(format,esp_log_timestamp(),MQTTEventHandler::CLASS_TAG,message.c_str());
    }
}