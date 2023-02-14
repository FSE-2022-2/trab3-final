#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "esp_log.h"
#include "driver/gpio.h"

#include "button_ky004.h"


xQueueHandle filaDeInterrupcao;

static void IRAM_ATTR gpio_isr_handler(void *args)
{
  int pino = (int)args;
  xQueueSendFromISR(filaDeInterrupcao, &pino, NULL);
}

void trataInterrupcaoBotao(void *params)
{
  int pino;
  int contador = 0;

  while(true)
  {
    if(xQueueReceive(filaDeInterrupcao, &pino, portMAX_DELAY))
    {
      // De-bouncing
      int estado = gpio_get_level(pino);
      if(estado == 1)
      {
        gpio_isr_handler_remove(pino);
        while(gpio_get_level(pino) == estado)
        {
          vTaskDelay(50 / portTICK_PERIOD_MS);
        }

        // Habilitar novamente a interrupção
        vTaskDelay(50 / portTICK_PERIOD_MS);
        gpio_isr_handler_add(pino, gpio_isr_handler, (void *) pino);
      }

    }
  }
}

void teste_button(void* pvParameter)
{
    const int BUTTON_KY004 = (int) pvParameter;

  // Configuração do pino do Botão
  gpio_pad_select_gpio(BUTTON_KY004);
  // Configura o pino do Botão como Entrada
  gpio_set_direction(BUTTON_KY004, GPIO_MODE_INPUT);
  // Configura o resistor de Pulldown para o botão (por padrão a entrada estará em Zero)
  gpio_pulldown_en(BUTTON_KY004);
  // Desabilita o resistor de Pull-up por segurança.
  gpio_pullup_dis(BUTTON_KY004);

  // Configura pino para interrupção
  gpio_set_intr_type(BUTTON_KY004, GPIO_INTR_POSEDGE);

  filaDeInterrupcao = xQueueCreate(10, sizeof(int));
  xTaskCreate(trataInterrupcaoBotao, "TrataBotao", 2048, NULL, 1, NULL);

  gpio_install_isr_service(0);
  gpio_isr_handler_add(BUTTON_KY004, gpio_isr_handler, (void *) BUTTON_KY004);

}