#pragma once

ESP_EVENT_DEFINE_BASE(MAIN_EVENT);

enum {    
    EVENT_ID_SEND_INTEGER=500,
    EVENT_ID_SEND_STRING
};

class EventHandler
{
    private:
        /* data */
    public:
        EventHandler(/* args */);
        ~EventHandler();

        
};
