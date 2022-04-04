#pragma once
#include "mqtt_client.h"

class EventHandler
{
    public:
        virtual void register_events(void*)=0;
        void log(std::string);
        virtual std::string getClassTag()=0;
};

