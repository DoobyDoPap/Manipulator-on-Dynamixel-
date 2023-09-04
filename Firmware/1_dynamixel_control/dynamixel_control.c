#include <stdio.h>
#include <string.h> 
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/uart.h"
#include "driver/gpio.h"

#define UART_NUM    UART_NUM_2
#define BAUD_RATE   57600


void app_main(void)
{

const uart_port_t uart_num = UART_NUM_2;
uart_config_t uart_config = {
        .baud_rate = 9600,
        .data_bits = UART_DATA_8_BITS,
        .parity    = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_CTS_RTS,
        .rx_flow_ctrl_thresh = 122,
    };
    
    ESP_ERROR_CHECK(uart_param_config(UART_NUM_2, &uart_config));
    ESP_ERROR_CHECK(uart_set_pin(UART_NUM_2, 17, 16, 18, 19));
    ESP_ERROR_CHECK(uart_set_mode(uart_num, UART_MODE_RS485_HALF_DUPLEX));
    const int uart_buffer_size = (1024*2);
    QueueHandle_t uart_queue;
    ESP_ERROR_CHECK(uart_driver_install(UART_NUM_2, uart_buffer_size, uart_buffer_size, 10, &uart_queue, 0));

 while (1) {
        
        float target_degrees = 30.0;
        controlDynamixelMX64(DYNAMIXEL_UART_PORT, target_degrees);

        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}
    
