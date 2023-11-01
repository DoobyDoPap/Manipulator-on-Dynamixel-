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

void init_uart()
{

const uart_port_t uart_num = UART_NUM_2;
uart_config_t dynamixel_config = {
        .baud_rate = 9600,
        .data_bits = UART_DATA_8_BITS,
        .parity    = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        
    };
    
    uart_param_config(DYNAMIXEL_UART_NUM, &dynamixel_config);
    uart_set_pin(DYNAMIXEL_UART_NUM, 17, 16, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);
    uart_driver_install(DYNAMIXEL_UART_NUM, 1024, 0, 0, NULL, 0);
}
 
 // Enable Dynamixel Torque
uint8_t enable_torque_command[] = {0xFF, 0xFF, 1, 0x05, 0x03, 24, 0x01, 0x00};
send_to_dynamixel(enable_torque_command, sizeof(enable_torque_command));
  
  // Calculate the position value for 30 degrees
uint16_t goal_position = (uint16_t)((30.0 / 300.0) * (DXL_MAXIMUM_POSITION_VALUE - DXL_MINIMUM_POSITION_VALUE)) + DXL_MINIMUM_POSITION_VALUE;

// Set Goal Position
uint8_t set_position_command[] = {0xFF, 0xFF, DXL_ID, 0x07, 0x03, 30, goal_position & 0xFF, (goal_position >> 8) & 0xFF, 0x00};
uart_write_bytes(DYNAMIXEL_UART_NUM, (const char *)set_position_command, sizeof(set_position_command));

    do {
    // Read present position
    uint8_t read_position_command[] = {0xFF, 0xFF, 1, 0x04, 0x02, 36, 0x02};
    send_to_dynamixel(read_position_command, sizeof(read_position_command));
    receive_from_dynamixel((uint8_t *)&current_position, sizeof(current_position));
    
    // Convert the received data to little-endian if needed
    current_position = (current_position >> 8) | (current_position << 8);

} 
while (abs(goal_position - current_position) > DXL_MOVING_STATUS_THRESHOLD);

   
    
 
    
 
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
  

    
















