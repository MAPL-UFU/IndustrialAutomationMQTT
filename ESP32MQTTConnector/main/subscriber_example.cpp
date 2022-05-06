//this tag is used for onli not class methods
//avoiding the use of static methods
#pragma once
#define PROGRAM_TAG "ESP32_CLOUD_CONNECTOR"

#include <iostream>
#include <string>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "freertos/queue.h"


#include "esp_log.h"
#include "esp_event.h"

#include "mqtt_connector.cpp"
#include "serial_connector.cpp"
#include "CustomEventHandler.hpp"

using namespace std;

void vTaskLocalControl(void *pvParameters){
    CustomEventHandler* context = (CustomEventHandler*)pvParameters;
    cout<<("Task Local Control");
    context->subscribeTo("lem/valve",[](string pay){
        cout<<"Received: "<<pay<<endl;
        cout<<("Valvula Acionada no local control")<<endl;
    });
    while(1){
        if(context->isMQTTConnected()){
            cout<<"MQTT Connected"<<endl;
            context->subscribeTo("lem/valve",[](string pay){
                cout<<"Received: "<<pay<<endl;
                cout<<("Valvula Acionada no local control")<<endl;
            });
            break;
        }
        vTaskDelay(5000 / portTICK_PERIOD_MS);
    }
    while(1){
        cout<<"Waiting Data..."<<endl;
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
};

void sub_main(){
    esp_log_level_set("*", ESP_LOG_INFO);
    ESP_LOGI(PROGRAM_TAG, "Main Task In itializing");
 
    esp_event_loop_args_t loop_args = { 
        .queue_size = 10 , 
        .task_name = "main_event_loop",
        .task_priority = tskIDLE_PRIORITY,
        .task_stack_size = 4096,
        .task_core_id = tskNO_AFFINITY
    };

    esp_event_loop_handle_t* loop_handle_pointer = new esp_event_loop_handle_t(); 
    esp_event_loop_create(&loop_args,loop_handle_pointer); // using a dedicated task

    CustomEventHandler* custom_event_handler = new CustomEventHandler();
    startMQTT(custom_event_handler,loop_handle_pointer);                       
    startSerial(custom_event_handler,loop_handle_pointer);

    xTaskCreatePinnedToCore(vTaskLocalControl,
                            "vTaskLocalControl", 
                            2048, 
                            custom_event_handler, 
                            0, 
                            NULL, 
                            tskNO_AFFINITY); 
}