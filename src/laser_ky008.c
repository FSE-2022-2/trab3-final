#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/ledc.h"
#include "esp_err.h"

#include "laser_ky008.h"

int get_valor_laser()
{
  // pwm range = 0..254
  
  return 254;
}
int valor_anterior = 0;

void laser_teste(void *pvParameter)
{
  int pino = (int)pvParameter;
  // Configuração do Timer
  ledc_timer_config_t timer_config = {
      .speed_mode = LEDC_LOW_SPEED_MODE,
      .duty_resolution = LEDC_TIMER_8_BIT,
      .timer_num = LEDC_TIMER_1,
      .freq_hz = 1000,
      .clk_cfg = LEDC_AUTO_CLK};
  ledc_timer_config(&timer_config);

  // Configuração do Canal
  ledc_channel_config_t channel_config = {
      .gpio_num = pino,
      .speed_mode = LEDC_LOW_SPEED_MODE,
      .channel = LEDC_CHANNEL_1,
      .timer_sel = LEDC_TIMER_1,
      .duty = valor_anterior,
      .hpoint = 0};
  ledc_channel_config(&channel_config);

  // Utilizando o PWM

  while (true)
  {
    int valor = get_valor_laser();
    if (valor != valor_anterior)
    {
      ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_1, valor);
      ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_1);
      vTaskDelay(10 / portTICK_PERIOD_MS);
      valor_anterior = valor;
    }
    vTaskDelay(200 / portTICK_PERIOD_MS);
  }
}