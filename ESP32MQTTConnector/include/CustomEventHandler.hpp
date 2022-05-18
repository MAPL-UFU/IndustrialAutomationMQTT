/***
 * this is a class for unificating the event handling for example
 *
 **/
#pragma once
#include "MQTTEventHandler.hpp"
#include "SerialEventHandler.hpp"


class CustomEventHandler : public MQTTEventHandler, public SerialEventHandler
{
    private:
        inline static const char* CLASS_TAG = "CustomEventHandler";
    public:
        void register_events(void*){};
        std::string getClassTag();
};
