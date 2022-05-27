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
#include "driver/gpio.h"


#include "esp_log.h"
#include "esp_event.h"

#include "mqtt_connector.cpp"
#include "serial_connector.cpp"
#include "CustomEventHandler.hpp"

#define GPIO_OUTPUT_IO_0   (gpio_num_t)12
#define GPIO_OUTPUT_PIN_SEL  (1ULL<<GPIO_OUTPUT_IO_0)

void start_gpio(){
    gpio_config_t io_conf = {};
    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.mode = GPIO_MODE_OUTPUT;
    //bit mask of the pins that you want to set,e.g.GPIO18/19
    io_conf.pin_bit_mask = GPIO_OUTPUT_PIN_SEL;
    io_conf.pull_down_en = (gpio_pulldown_t)0;
    io_conf.pull_up_en = (gpio_pullup_t)0;
    gpio_config(&io_conf);
}

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
                if (pay == "Acionado"){
                    gpio_set_level(GPIO_OUTPUT_IO_0, 1);
                }
                if (pay == "Desacionado"){
                    gpio_set_level(GPIO_OUTPUT_IO_0, 0);
                }
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
    start_gpio();
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

    xTaskCreatePinnedToCore(vTaskLocalControl,
                            "vTaskLocalControl", 
                            2048, 
                            custom_event_handler, 
                            0, 
                            NULL, 
                            tskNO_AFFINITY); 
}