/***
 * this is a class for unificating the event handling for example
 *
 **/
#pragma once
#include "MQTTEventHandler.hpp"


class CustomEventHandler : public MQTTEventHandler
{
    private:
        inline static const char* CLASS_TAG = "CustomEventHandler";
    public:
        void register_events(void*){};
        std::string getClassTag();
};
