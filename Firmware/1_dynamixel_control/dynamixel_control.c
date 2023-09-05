#include <stdio.h>
#include <string.h> 
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/uart.h"
#include "driver/gpio.h"

#define UART_NUM    UART_NUM_2
#define BAUD_RATE   9600


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
    
   
    
 while (1) {
        
    ESP_ERROR_CHECK(uart_param_config(UART_NUM_2, &uart_config));
    ESP_ERROR_CHECK(uart_set_pin(UART_NUM_2, 17, 16, 18, 19));
    ESP_ERROR_CHECK(uart_set_mode(uart_num, UART_MODE_RS485_HALF_DUPLEX));
       
       const int uart_buffer_size = (1024*2);
    QueueHandle_t uart_queue;
    ESP_ERROR_CHECK(uart_driver_install(UART_NUM_2, uart_buffer_size, uart_buffer_size, 10, &uart_queue, 0));
      uint8_t dynamixel_command[] = {0xFF, 0xFF, DYNAMIXEL_ID, 0x05, 0x03, 0x1E, 0x00, 0x01, 0xFE};
    
    uart_write_bytes(UART_NUM, (const char *)dynamixel_command, sizeof(dynamixel_command));

    vTaskDelay(pdMS_TO_TICKS(100));

    uint8_t dynamixel_read_command[] = {0xFF, 0xFF, DYNAMIXEL_ID, 0x04, 0x02, 0x24, 0x02, 0xFE};
    
    uart_write_bytes(UART_NUM, (const char *)dynamixel_read_command, sizeof(dynamixel_read_command));

    vTaskDelay(pdMS_TO_TICKS(100));

    uint8_t dynamixel_response[8];
    uart_read_bytes(UART_NUM, dynamixel_response, sizeof(dynamixel_response), 100);

    if (dynamixel_response[0] == 0xFF && dynamixel_response[1] == 0xFF && dynamixel_response[2] == DYNAMIXEL_ID) {
        uint16_t present_position = dynamixel_response[5] << 8 | dynamixel_response[4];
        printf("Dynamixel present position: %d\n", present_position);
    } else {
        printf("Invalid response received from Dynamixel\n");
    }

       
      
       }
}
    
 
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
  

    
















