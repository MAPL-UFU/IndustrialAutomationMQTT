#include <cstdio>
#include <iostream>

#include "mqtt_client.h"
#include "esp_event.h"
#include "SerialEventHandler.hpp"
#include "esp_log.h"

ESP_EVENT_DEFINE_BASE(SERIAL_EVENT_BASE);

using namespace std;

string SerialEventHandler::getClassTag(){
    string tag(SerialEventHandler::CLASS_TAG);
    return tag;
}

void SerialEventHandler::register_serial_events(esp_event_loop_handle_t loop)
{
    this->loop = loop;
    esp_event_handler_register_with(this->loop, 
                                    SERIAL_EVENT_BASE, EVENT_SEND_SERIAL_STRING_ID, 
                                    SerialEventHandler::onEventSerialStringSended, 
                                    this);
    esp_event_handler_register_with(this->loop, 
                                    SERIAL_EVENT_BASE, EVENT_SEND_SERIAL_INTEGER_ID, 
                                    SerialEventHandler::onEventSerialIntegerSended, 
                                    this);
    esp_event_handler_register_with(this->loop,
                                    SERIAL_EVENT_BASE, EVENT_RECEIVE_SERIAL_INTEGER_ID,
                                    SerialEventHandler::onEventSerialIntegerReceived,
                                    this);
    esp_event_handler_register_with(this->loop,
                                    SERIAL_EVENT_BASE, EVENT_RECEIVE_SERIAL_STRING_ID,
                                    SerialEventHandler::onEventSerialStringReceived,
                                    this);
}

void SerialEventHandler::onEventSerialStringSended(void *handler_args, esp_event_base_t base, int32_t event_id, void *event_data){
    SerialEventHandler* context = (SerialEventHandler*)handler_args;
    context->log("ESP Serial String");
}

void SerialEventHandler::onEventSerialIntegerSended(void *handler_args, esp_event_base_t base, int32_t event_id, void *event_data){
    SerialEventHandler* context = (SerialEventHandler*)handler_args;
    context->log("ESP Serial Integer");
}

void SerialEventHandler::onEventSerialIntegerReceived(void *handler_args, esp_event_base_t base, int32_t event_id, void *event_data){
    SerialEventHandler* context = (SerialEventHandler*)handler_args;
    context->log("ESP Serial Integer");
}

void SerialEventHandler::onEventSerialStringReceived(void *handler_args, esp_event_base_t base, int32_t event_id, void *event_data){
    SerialEventHandler* context = (SerialEventHandler*)handler_args;
    context->log("ESP Serial Integer");
}
