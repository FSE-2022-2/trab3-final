#include <stdio.h>
#include <string.h>
#include "nvs_flash.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_http_client.h"
#include "esp_log.h"
#include "freertos/semphr.h"

#include "wifi.h"
#include "mqtt.h"
#include "dht_sensor.h"
#include "dht11.h"
#include "hall_ky003.h"
#include "rgb_led.h"
#include "button_ky004.h"
#include "laser_ky008.h"
#include "buzzer_ky012.h"

/*
gpio:
2 - button in
4 - dht22 in
18 - hall in
21 - blue out pwm
22 - green out pwm
23 - red out pwm
13 - buzz out pwm
12 - laser out pwm
*/
#define BUTTON_GPIO 2
#define DHT11_GPIO 4
#define HALL_GPIO 18
#define BLUE_GPIO 21
#define GREEN_GPIO 22
#define RED_GPIO 23
#define BUZZ_GPIO 13
#define LASER_GPIO 12


SemaphoreHandle_t conexaoWifiSemaphore;
SemaphoreHandle_t conexaoMQTTSemaphore;

void conectadoWifi(void * params)
{
  while(true)
  {
    if(xSemaphoreTake(conexaoWifiSemaphore, portMAX_DELAY))
    {
      // Processamento Internet
      mqtt_start();
    }
  }
}

void app_main(void)
{
    // Inicializa o NVS
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
      ESP_ERROR_CHECK(nvs_flash_erase());
      ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);
    
    conexaoWifiSemaphore = xSemaphoreCreateBinary();
    conexaoMQTTSemaphore = xSemaphoreCreateBinary();
    wifi_start();
    xTaskCreate(&conectadoWifi,  "Conexão ao MQTT", 4096, NULL, 1, NULL);
    xTaskCreate(&teste_hall, "Teste Hall", 4096, (void*)HALL_GPIO, 1, NULL);
    xTaskCreate(&teste_button, "Teste Button", 4096, (void*)BUTTON_GPIO, 1, NULL);
    xTaskCreate(&teste_laser, "Teste Laser", 4096, (void*)LASER_GPIO, 1, NULL);
    xTaskCreate(&teste_buzzer, "Teste Buzzer", 4096, (void*)BUZZER_GPIO, 1, NULL);
    //led
    xTaskCreate(&blink_rgb_led, "Touch sensor", 4096, NULL, 1, NULL);
    //temp 
    dht_config(DHT11_GPIO);
}
