#include <stdio.h>
#include <string.h> 
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/uart.h"
#include "driver/gpio.h"  


#define DYNAMIXEL_UART_NUM    UART_NUM_2
#define BAUD_RATE               9600
#define DYNAMIXEL_TX_PIN        17
#define DYNAMIXEL_RX_PIN        16    
#define DYNAMIXEL_ID             1


void app_main(){ 
    const uart_port_t uart_num = UART_NUM_2;
uart_config_t dynamixel_config = {
        .baud_rate = 9600,
        .data_bits = UART_DATA_8_BITS,
        .parity    = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        
    };  

    uart_param_config(DYNAMIXEL_UART_NUM, &dynamixel_config);
    uart_set_pin(DYNAMIXEL_UART_NUM, DYNAMIXEL_TX_PIN, DYNAMIXEL_RX_PIN, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);
    uart_driver_install(DYNAMIXEL_UART_NUM, 1024, 0, 0, NULL, 0); 
    ESP_ERROR_CHECK(uart_set_mode(uart_num, UART_MODE_RS485_HALF_DUPLEX)); 


    char* test_str = "rotate by 30 ";
    uart_write_bytes(uart_num, (const char*)test_str, strlen(test_str),DYNAMIXEL_ID); 
 
    uint8_t data[128];
    int length ; 
    length = uart_read_bytes(uart_num, data, length, DYNAMIXEL_ID, 100);  

      
}
