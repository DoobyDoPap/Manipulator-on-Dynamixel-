#include<stdio.h> 
#include"driver/gpio.h"  
#include "freertos/FreeRTOS.h"  
 #include "freertos/task.h"  
 

static const gpio_num_t step_pin_m1 = GPIO_NUM_12;
static const gpio_num_t step_pin_m2 = GPIO_NUM_33;
static const gpio_num_t step_pin_m3 = GPIO_NUM_25;
static const gpio_num_t step_pin_m4 = GPIO_NUM_26;
static const gpio_num_t step_pin_m5 = GPIO_NUM_27;
static const gpio_num_t step_pin_m6 = GPIO_NUM_14;
static const gpio_num_t step_pin_m7 = GPIO_NUM_13;
static const gpio_num_t step_pin_m8 = GPIO_NUM_23; 
static const  gpio_mode_t led_mode = GPIO_MODE_OUTPUT; 
 
  
 void app_main(){    
         
        gpio_set_direction( step_pin_m1, led_mode);  
        gpio_set_direction( step_pin_m2, led_mode );   
        gpio_set_direction( step_pin_m3, led_mode);   
        gpio_set_direction( step_pin_m4, led_mode);   
        gpio_set_direction( step_pin_m5, led_mode);   
        gpio_set_direction( step_pin_m6, led_mode);   
        gpio_set_direction( step_pin_m7, led_mode);   
        gpio_set_direction( step_pin_m8, led_mode);    
    
    while (1){ 
  gpio_set_level( step_pin_m1 ,1);  
    
  gpio_set_level( step_pin_m2, 1); 
    
  gpio_set_level( step_pin_m3 , 1); 
    
  gpio_set_level( step_pin_m4,1);  
  
  gpio_set_level( step_pin_m5, 1);  
  
  gpio_set_level( step_pin_m6, 1);  
    
  gpio_set_level( step_pin_m7 , 1); 
    
  gpio_set_level(step_pin_m8 ,1);    
  
  
    vTaskDelay(1000 / portTICK_PERIOD_MS); 
    
   gpio_set_level( step_pin_m1 ,0);  
   gpio_set_level( step_pin_m2 ,0);  
   gpio_set_level( step_pin_m3 ,0);  
   gpio_set_level( step_pin_m4 ,0);  
   gpio_set_level( step_pin_m5 ,0);  
   gpio_set_level( step_pin_m6 ,0);  
   gpio_set_level( step_pin_m7,0);  
   gpio_set_level( step_pin_m8 ,0);  
            
           
     vTaskDelay(1000 / portTICK_PERIOD_MS); 
    
     
    }   
    
 
  
  } 

