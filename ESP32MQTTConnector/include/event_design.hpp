#pragma once
#include "mqtt_client.h"

enum {    
    EVENT_SEND_SERIAL_INTEGER_ID=500,
    EVENT_SEND_SERIAL_STRING_ID
};

class EventHandler
{
    public:
        virtual void register_events(void*)=0;
};


class MQTTEventHandler : public EventHandler
{
    private:
        inline static const char* CLASS_TAG = "MQTTEventHandler";
        esp_mqtt_client* client;
    public:
        void register_events(void*){};
        void register_mqtt_events(esp_mqtt_client*);
        void log(std::string);

        static void onEventConnected(void*, esp_event_base_t, int32_t, void*);
        static void onEventDisconnected(void*, esp_event_base_t, int32_t, void*);
        static void onEventSubscribed(void*, esp_event_base_t, int32_t, void*);
        static void onEventUnsubscribed(void*, esp_event_base_t, int32_t, void*);
        static void onEventError(void*, esp_event_base_t, int32_t, void*);
        static void onEventData(void*, esp_event_base_t, int32_t, void*);
};

/*
class CustomEventHandler : public EventHandler
{
    private:
        inline static const char* CLASS_TAG = "CustomEventHandler";
        esp_event_loop_handle_t event_loop;
    public:
        void register_events(void*);
        void register_custom_events(esp_event_loop_handle_t);
        void log(std::string);

        static void onEventSendSerialInteger(void*, esp_event_base_t, int32_t, void*);
        static void onEventSendSerialString(void*, esp_event_base_t, int32_t, void*);
};
*/