#include <cstdio>
#include <functional>
#include <iostream>
#include <string>
#include <map>

#include "mqtt_client.h"
#include "esp_event.h"
#include "MQTTEventHandler.hpp"
#include "esp_log.h"

using namespace std;

string MQTTEventHandler::getClassTag(){
    string tag(MQTTEventHandler::CLASS_TAG);
    return tag;
}

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
    context->is_mqtt_connected = true;
}

void MQTTEventHandler::onEventDisconnected(void *handler_args, esp_event_base_t base, int32_t event_id, void *event_data){
    MQTTEventHandler* context = (MQTTEventHandler*)handler_args;
    context->log("ESP MQTT Disconnected");
    context->is_mqtt_connected = false;
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
    if (context->on_message_callbacks.find(topic) != context->on_message_callbacks.end())
    {
        context->on_message_callbacks[topic](payload);
    }
}

void MQTTEventHandler::postData(string topic, string data){
    if(this->is_mqtt_connected){
        esp_mqtt_client_publish(this->client, topic.c_str(), data.c_str(), data.length(), 0, 0);
    }
}

void MQTTEventHandler::subscribeTo(string topic, function<void(string)> callback){
    if(this->is_mqtt_connected){
        esp_mqtt_client_subscribe(this->client, topic.c_str(), 0);
        this->on_message_callbacks[topic] = callback;
    }else{
        this->log("MQTT not connected");
    }
}




