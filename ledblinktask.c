#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <driver/gpio.h>
#include "esp_log.h"
#define BG_LED_1 12
#define BG_LED_2 33
#define BG_LED_3 25
#define BG_LED_4 26
#define BG_LED_5 27
#define BG_LED_6 14
#define BG_LED_7 13
#define BG_LED_8 23
void set_led(uint8_t data,const int *pin_out)
{
for(int i=0;i<8;i++)
{
if ((data & 0x80) == 0x80)
            {
                // set gpio value to 1
                gpio_set_level((gpio_num_t)pin_out[i], 1);
            }
            else
            {
                // set gpio value to 0
                gpio_set_level((gpio_num_t)pin_out[i], 0);
            }
            data= data<<1;
            }
            
            }
void app_main(){
static const int pin_out[8] = {BG_LED_1,BG_LED_2,BG_LED_4,BG_LED_4,BG_LED_5,BG_LED_6,BG_LED_7,BG_LED_8};
uint8_t data;
static const char *TAG = "blink_code";
gpio_config_t io_conf;
io_conf.intr_type = GPIO_INTR_DISABLE;
io_conf.mode = GPIO_MODE_OUTPUT;
io_conf.pin_bit_mask = 0;
for (int i = 0; i < 8; i++) {
        io_conf.pin_bit_mask |= (1ULL << led_pins[i]);
    }
io_conf.mode = GPIO_MODE_OUTPUT;
io_conf.pull_up_en =0;
io_conf.pull_down_en = 1;

esp_err_t err = gpio_config(&io_conf);
if(err == ESP_OK){
for(int a=0;a<5;a++){
set_led(0xFF,pin_out);
vTaskDelay(1000 / portTICK_RATE_MS);
set_led(0x00,pin_out);
vTaskDelay(1000 / portTICK_RATE_MS);
}
data = 0x01;
while(1)
{
if(data == 0x00){
data = 0x01;
}
set_led(data,pin_out);
data=data<<1;
vTaskDelay(1000 / portTICK_RATE_MS);
}
}
  else
    {
        ESP_LOGE(TAG, "error: %s", esp_err_to_name(err));
        return;
      }
      }
