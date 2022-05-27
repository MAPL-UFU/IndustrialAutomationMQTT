#pragma once

#include "driver/uart.h"
#include "driver/gpio.h"

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "freertos/queue.h"

#include "esp_event.h"
#include "esp_log.h"
#include "SerialEventHandler.hpp"

#define ECHO_TEST_TXD (GPIO_NUM_4)
#define ECHO_TEST_RXD (GPIO_NUM_2)
#define ECHO_TEST_RTS (UART_PIN_NO_CHANGE) //flow control disabled
#define ECHO_TEST_CTS (UART_PIN_NO_CHANGE)

#define BUF_SIZE (1024)

#define ECHO_UART_PORT_NUM      2
#define ECHO_UART_BAUD_RATE     9600


void install_serial(){
    uart_config_t uart_config = {
        .baud_rate = ECHO_UART_BAUD_RATE,
        .data_bits = UART_DATA_8_BITS,
        .parity    = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE
    };
    int intr_alloc_flags = 0;

#if CONFIG_UART_ISR_IN_IRAM
    intr_alloc_flags = ESP_INTR_FLAG_IRAM;
#endif

    if (!uart_is_driver_installed(ECHO_UART_PORT_NUM)){
        ESP_ERROR_CHECK(uart_driver_install(ECHO_UART_PORT_NUM, BUF_SIZE * 2, 0, 0, NULL, intr_alloc_flags));
    }
    ESP_ERROR_CHECK(uart_param_config(ECHO_UART_PORT_NUM, &uart_config));
    ESP_ERROR_CHECK(uart_set_pin(ECHO_UART_PORT_NUM, ECHO_TEST_TXD, ECHO_TEST_RXD, ECHO_TEST_RTS, ECHO_TEST_CTS));
}

void startSerial(SerialEventHandler* serial_handler,esp_event_loop_handle_t* event_loop)
{
    //install_serial();  //config serial pins
    serial_handler->register_serial_events(*event_loop);

/*    
    while(1){
        char str[] = "Hello world!\n";
        uart_write_bytes(ECHO_UART_PORT_NUM, str, strlen(str));
        printf(str);
        esp_event_post_to(*event_loop, MAIN_EVENT, EVENT_ID_SEND_INTEGER, NULL,0,0);
        vTaskDelay(1000*30 / portTICK_PERIOD_MS);
    }
*/
}