#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/ledc.h"
#include "esp_err.h"

#include "laser_ky008.h"

static unsigned char is_laser_on = 0;  
static unsigned char valor_pwm = 0;  

void switch_laser(){
  is_laser_on = !is_laser_on;
  return;
}

void handle_intensity(int intensity){
  valor_pwm = intensity * 255 / 100;
}


int get_valor_laser()
{
  // pwm range = 0..254
  if (is_laser_on)
  {
    return valor_pwm;
  } 
  return 0;
}
static int valor_anterior = 0;

void teste_laser(void *pvParameter)
{
  int pino = (int)pvParameter;
  // Configuração do Timer
  ledc_timer_config_t timer_config = {
      .speed_mode = LEDC_LOW_SPEED_MODE,
      .duty_resolution = LEDC_TIMER_8_BIT,
      .timer_num = LEDC_TIMER_1,
      .freq_hz = 80,
      .clk_cfg = LEDC_AUTO_CLK};
  ledc_timer_config(&timer_config);

  // Configuração do Canal
  ledc_channel_config_t channel_config = {
      .gpio_num = pino,
      .speed_mode = LEDC_LOW_SPEED_MODE,
      .channel = LEDC_CHANNEL_2,
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
      ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_2, valor);
      ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_2);
      vTaskDelay(10 / portTICK_PERIOD_MS);
      valor_anterior = valor;
    }
    vTaskDelay(200 / portTICK_PERIOD_MS);
  }
}