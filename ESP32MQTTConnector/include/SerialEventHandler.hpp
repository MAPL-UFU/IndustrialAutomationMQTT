#pragma once
#include "esp_event.h"
#include "EventHandler.hpp"

enum {    
    EVENT_SEND_SERIAL_INTEGER_ID=500,
    EVENT_SEND_SERIAL_STRING_ID,
    EVENT_RECEIVE_SERIAL_INTEGER_ID,
    EVENT_RECEIVE_SERIAL_STRING_ID
};

class SerialEventHandler : public EventHandler
{
    private:
        inline static const char* CLASS_TAG = "SerialEventHandler";
        esp_event_loop_handle_t loop;
    public:
        void register_events(void*){};
        void register_serial_events(esp_event_loop_handle_t);
        std::string getClassTag();

        static void onEventSerialIntegerSended(void*, esp_event_base_t, int32_t, void*);
        static void onEventSerialStringSended(void*, esp_event_base_t, int32_t, void*);
        static void onEventSerialIntegerReceived(void*, esp_event_base_t, int32_t, void*);
        static void onEventSerialStringReceived(void*, esp_event_base_t, int32_t, void*);
};