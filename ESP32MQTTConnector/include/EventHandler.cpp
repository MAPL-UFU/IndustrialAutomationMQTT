#include <cstdio>
#include <iostream>

#include "EventHandler.hpp"
#include "esp_log.h"

using namespace std;

void EventHandler::log(string message){
    if (LOG_LOCAL_LEVEL >= ESP_LOG_INFO) {
        const char* format = "I (%d) %s: %s\n"; 
        printf(format,esp_log_timestamp(),this->getClassTag().c_str(),message.c_str());
    }
}
