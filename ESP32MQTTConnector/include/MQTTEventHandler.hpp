#pragma once
#include <map>
#include <string>
#include <functional>
#include "mqtt_client.h"
#include "EventHandler.hpp"

class MQTTEventHandler : public EventHandler
{
    private:
        inline static const char* CLASS_TAG = "MQTTEventHandler";
        bool is_mqtt_connected=false;
        esp_mqtt_client* client;
        std::map<std::string, std::function<void(std::string)>> on_message_callbacks;
    public:
        void register_events(void*){};
        void register_mqtt_events(esp_mqtt_client*);
        std::string getClassTag();

        static void onEventConnected(void*, esp_event_base_t, int32_t, void*);
        static void onEventDisconnected(void*, esp_event_base_t, int32_t, void*);
        static void onEventSubscribed(void*, esp_event_base_t, int32_t, void*);
        static void onEventUnsubscribed(void*, esp_event_base_t, int32_t, void*);
        static void onEventError(void*, esp_event_base_t, int32_t, void*);
        static void onEventData(void*, esp_event_base_t, int32_t, void*);

        bool isMQTTConnected(){ return is_mqtt_connected; };
        void postData(std::string topic, std::string data);
        void subscribeTo(std::string topic, std::function<void(std::string)>);
};