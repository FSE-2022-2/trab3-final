#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "esp_log.h"
#include "driver/gpio.h"
#include "mqtt.h"
#include "hall_ky003.h"
#include "json_util.h"
#include "cJSON.h"

void teste_hall(void * pvParameter)
{
  const int HALL_KY003 = *((int*)pvParameter);
  // Configuração dos pinos dos LEDs 
  // gpio_pad_select_gpio(HALL_KY003);
  esp_rom_gpio_pad_select_gpio(HALL_KY003);
  // Configura os pinos dos LEDs como Output
  gpio_set_direction(HALL_KY003, GPIO_MODE_INPUT);

  int leitura = gpio_get_level(HALL_KY003);
  if (leitura != 1)
  {
    leitura = gpio_get_level(HALL_KY003);
    while(leitura != 1)
    {
      printf("distância: %d\n", leitura);
      fflush(stdout);
      char mensagem[50];
      sprintf(mensagem, "{\"distancia\": %d}", leitura);
      mqtt_envia_mensagem("v1/devices/me/telemetry", mensagem);
      vTaskDelay(5000 / portTICK_PERIOD_MS);
    }
  } 

}