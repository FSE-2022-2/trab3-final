#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "esp_log.h"
#include "driver/gpio.h"


void handle_botao(){
    if(msg != 0){

    }
}

void teste_laser(void * pvParameter)
{
  const int LASER_KY008 = *((int*)pvParameter);
  // Configuração dos pinos dos LEDs 
  gpio_pad_select_gpio(LASER_KY008);
  // Configura os pinos dos LEDs como Output
  gpio_set_direction(LASER_KY008, GPIO_MODE_OUTPUT);

    leitura = gpio_get_level(LASER_KY008, );
    while(leitura != 1)
    {
      printf("distância: %d\n", leitura);
      vTaskDelay(100 / portTICK_PERIOD_MS);
    }

}