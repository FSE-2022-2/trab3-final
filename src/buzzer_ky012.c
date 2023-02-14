#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/ledc.h"
#include "esp_err.h"
#include "mqtt.h"


#include "buzzer_ky012.h"

static unsigned char is_buzzer_on = 0;  

void switch_buzzer(){
    is_buzzer_on = !is_buzzer_on;
    return;
}

void teste_buzzer(void *pvParameter)
{
  const int pino = (int) pvParameter;
  // Configuração dos pinos dos LEDs 
  // gpio_pad_select_gpio(pino);
  esp_rom_gpio_pad_select_gpio(pino);
  // Configura os pinos dos LEDs como Output
  gpio_set_direction(pino, GPIO_MODE_OUTPUT);

  while (true)
  {
    
    gpio_set_level(pino, is_buzzer_on);
    printf("musica: %s\n", (is_buzzer_on ? "on" : "off"));  
    fflush(stdout);
    char mensagem[50];
    sprintf(mensagem, "{\"getJingle\": %s}", (is_buzzer_on ? "true" : "false"));
    mqtt_envia_mensagem("v1/devices/me/telemetry", mensagem);
    vTaskDelay(2000 / portTICK_PERIOD_MS);
  }
}