//this tag is used for onli not class methods
//avoiding the use of static methods
#define PROGRAM_TAG "ESP32_CLOUD_CONNECTOR"

#include <iostream>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "freertos/queue.h"


#include "esp_log.h"
#include "esp_event.h"

#include "mqtt_connector.cpp"
//#include "serial_connector.cpp"

using namespace std;

void main_event_handler(void* handler_arg, esp_event_base_t base, int32_t id, void* event_data)
{
    cout<<"main_event_handler"<<endl;
}

void main_init(){
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
    //esp_event_handler_register_with(*loop_handle_pointer, CUSTOM_EVENT_BASE, EVENT_SEND_SERIAL_STRING_ID, main_event_handler, NULL);

    startMQTT(loop_handle_pointer); // Start MQTT, this use event loop in a specific task                        
/*
    xTaskCreatePinnedToCore(vTaskSerial,
                            "vTaskSerial", 
                            2048, 
                            loop_handle_pointer, 
                            0, 
                            NULL, 
                            tskNO_AFFINITY);                 
*/

    //ESP_ERROR_CHECK(esp_event_post_to(*loop_handle_pointer , CUSTOM_EVENT_BASE, EVENT_SEND_SERIAL_STRING_ID, NULL,0,0));
}

extern "C" void app_main(void)
{
    main_init();
}
