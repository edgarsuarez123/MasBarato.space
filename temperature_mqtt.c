#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/adc.h"
#include "esp_system.h"
#include "mqtt_client.h"

#define TEMP_SENSOR_PIN ADC1_CHANNEL_XX 

void app_main() {
  float voltage, temperature;
  uint16_t rawValue;
  char data[10];
  
  adc1_config_width(ADC_WIDTH_BIT_12); // Configure ADC width to 12 bits
  adc1_config_channel_atten(TEMP_SENSOR_PIN, ADC_ATTEN_DB_0); // Configure ADC attenuation to 0 dB
  
  mqtt_app_start(); // Start MQTT client
  
  while(1) { // Loop forever
    rawValue = adc1_get_raw(TEMP_SENSOR_PIN); // Read raw value from ADC
    voltage = (float)rawValue * 3.3 / 4095.0; // Convert raw value to voltage (assuming 3.3V reference voltage)
    temperature = (voltage - 0.75) / 0.01; // Convert voltage to temperature (assuming LMT84 sensor)
    sprintf(data, "%.2f", temperature); // Convert temperature to string format
    
    mqtt_client_publish("temperatura", data, strlen(data), 0, false); // Publish temperature to MQTT broker
    
    printf("Temperatura leida: %s\n", data); // Print published temperature
    
    vTaskDelay(pdMS_TO_TICKS(1000)); // Wait for 1 second
  }
}