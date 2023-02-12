#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "esp_log.h"
#include "driver/gpio.h"

#define HALL_KY003 4

void teste_hall()
{
  // Configuração dos pinos dos LEDs 
  gpio_pad_select_gpio(HALL_KY003);
  // Configura os pinos dos LEDs como Output
  gpio_set_direction(HALL_KY003, GPIO_MODE_INPUT);

  int leitura = gpio_get_level(HALL_KY003);
  if (leitura != 1)
  {
    leitura = gpio_get_level(HALL_KY003);
    while(leitura != 1)
    {
      printf("distância: %d\n", leitura);
      vTaskDelay(100 / portTICK_PERIOD_MS);
    }
  } 

}