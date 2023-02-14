#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/ledc.h"
#include "esp_err.h"

#include "buzzer_ky012.h"

static unsigned char is_buzzer_on = 0;  

void switch_buzzer(){
    is_buzzer_on = !is_buzzer_on;
    return;
}

int handle_alarm_buzzer()
{
  if(is_buzzer_on){
    return 1;
  }
  return 0;
}

void teste_buzzer(void *pvParameter)
{
  int pino = (int)pvParameter;
  // Configuração do Timer
  ledc_timer_config_t timer_config = {
      .speed_mode = LEDC_LOW_SPEED_MODE,
      .duty_resolution = LEDC_TIMER_8_BIT,
      .timer_num = LEDC_TIMER_2,
      .freq_hz = 1000,
      .clk_cfg = LEDC_AUTO_CLK};
  ledc_timer_config(&timer_config);

  // Configuração do Canal
  ledc_channel_config_t channel_config = {
      .gpio_num = pino,
      .speed_mode = LEDC_LOW_SPEED_MODE,
      .channel = LEDC_CHANNEL_3,
      .timer_sel = LEDC_TIMER_2,
      .duty = 0,
      .hpoint = 0};
  ledc_channel_config(&channel_config);

  // Utilizando o PWM

  while (true)
  {
    if (handle_alarm_buzzer())
    {
        for(int i = 0; i < 255; i++)
        {
            ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_3, i);
            ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_3);
            vTaskDelay(10 / portTICK_PERIOD_MS);
        }

        for(int i = 255; i > 0; i--)
        {
            ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_3, i);
            ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_3);
            vTaskDelay(10 / portTICK_PERIOD_MS);
        }
        ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_3, 0);
        ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_3);
    }
    vTaskDelay(200 / portTICK_PERIOD_MS);
  }
}