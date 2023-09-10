#include <stdio.h>
#include <string.h> 
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/uart.h"
#include "driver/gpio.h"  



#define BAUD_RATE               9600
#define DYNAMIXEL_TX_PIN        GPIO_NUM_17 
#define DYNAMIXEL_RX_PIN        GPIO_NUM_16   
#define DYNAMIXEL_ID             1  
#define GPIO_BIT_MASK          1ULL<<GPIO_NUM_33
static const gpio_num_t gpio_set_pin = GPIO_NUM_33;    
 



void app_main(){ 
     const uart_port_t DYNAMIXEL_UART_NUM = UART_NUM_2;
uart_config_t dynamixel_config = {
        .baud_rate = 9600,
        .data_bits = UART_DATA_8_BITS,
        .parity    = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        
    }; 
    
    uart_param_config(DYNAMIXEL_UART_NUM, &dynamixel_config);
    uart_set_pin(DYNAMIXEL_UART_NUM, DYNAMIXEL_TX_PIN,  DYNAMIXEL_RX_PIN, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE); 
    ESP_ERROR_CHECK(uart_set_mode(DYNAMIXEL_UART_NUM, UART_MODE_RS485_HALF_DUPLEX));
    uart_driver_install(DYNAMIXEL_UART_NUM, 1024, 0, 0, NULL, 0);   

    gpio_config_t io_conf;
	io_conf.intr_type = GPIO_INTR_DISABLE;
	io_conf.mode = GPIO_MODE_INPUT;
	io_conf.pin_bit_mask = GPIO_BIT_MASK; 
	io_conf.pull_up_en = GPIO_PULLUP_ENABLE; 
	io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
	gpio_config(&io_conf); 
	
	
     
      
     
     while(1) {   
          
          gpio_set_level(gpio_set_pin,0); 
          uint8_t send_command[]= {0XFF ,0XFF ,  0X01 , 0X05 ,0X03  , 0X08 ,   0X1E ,   0x00};   
          uart_write_bytes(DYNAMIXEL_TX_PIN, (const char*)send_command,100);  
         
    
    
     vTaskDelay(1000 / portTICK_PERIOD_MS);  
     
      gpio_set_direction(gpio_set_pin,GPIO_MODE_OUTPUT); 
      gpio_set_level(gpio_set_pin,1); 
     uint8_t recieve_commmand[]={}; 
     int length=0; 
     length=uart_read_bytes(DYNAMIXEL_RX_PIN,recieve_commmand,length,100);  
     
      
     
     vTaskDelay(1000 / portTICK_PERIOD_MS);
      }
} 
