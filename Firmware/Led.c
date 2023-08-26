include<stdio.h> 
#include"driver/gpio.h"  
#include "freertos/FreeRTOS.h"  
 #include "freertos/task.h" 

 
 
 void main(){   
      
     gpio_set_direction(gpio_12_t , gpio_out); 
     gpio_set_direction(gpio_33_t, gpio_out );
     gpio_set_direction(gpio_25_t, gpio_out );
     gpio_set_direction(gpio_26_t, gpio_out ); 
     gpio_set_direction(gpio_27_t, gpio_out );
     gpio_set_direction(gpio_14_t, gpio_out );
     gpio_set_direction(gpio_13_t, gpio_out );
     gpio_set_direction(gpio_23_t, gpio_out );
    while (1){ 
      gpio_set_level(gpio_12_t, 1); 
      gpio_set_level(gpio_33_t ,1); 
      gpio_set_level(gpio_25_t , 1); 
      gpio_set_level(gpio_26_t , 1); 
      gpio_set_level(gpio_27_t, 1); 
      gpio_set_level(gpio_14_t , 1); 
      gpio_set_level(gpio_13_t, 1); 
      gpio_set_level(gpio_23_t , 1); 
    } 
 
} 
