#include <driver/adc.h>

#include "timeout.h"

#define DEBUG 3

// global varialbles
short currentMeasurements[90][5]; // array for storing current values
unsigned long timeOfMeasurements[90][2];

void getAnalogData( void * pvParameters  ){
    
    adc1_config_width(ADC_WIDTH_12Bit);
    adc1_config_channel_atten(ADC1_CHANNEL_0,ADC_ATTEN_11db);
    adc1_config_channel_atten(ADC1_CHANNEL_1,ADC_ATTEN_11db);
    adc1_config_channel_atten(ADC1_CHANNEL_2,ADC_ATTEN_11db);
    adc1_config_channel_atten(ADC1_CHANNEL_3,ADC_ATTEN_11db);    
    adc1_config_channel_atten(ADC1_CHANNEL_4,ADC_ATTEN_11db);

    short iteration = 0;

    while(true) {
      timeOfMeasurements[iteration][0] = micros();
      
      currentMeasurements[iteration][0] = adc1_get_voltage(ADC1_CHANNEL_0);
      currentMeasurements[iteration][1] = adc1_get_voltage(ADC1_CHANNEL_1);
      currentMeasurements[iteration][2] = adc1_get_voltage(ADC1_CHANNEL_2);
      currentMeasurements[iteration][3] = adc1_get_voltage(ADC1_CHANNEL_3);
      currentMeasurements[iteration][4] = adc1_get_voltage(ADC1_CHANNEL_4);

      timeOfMeasurements[iteration][1] = micros();
      
      iteration++; 
      if (iteration>89) 
      {
        iteration=0;
        delay(1); //to avoid watch dog error, to be solved later
      }
    }
}

void setup() {
  // starting serial
  Serial.begin(115200);
  #if DEBUG >= 3 
    Serial.print("Serial started (115200)"); 
  #endif

  xTaskCreatePinnedToCore(
   getAnalogData,          /* pvTaskCode */
   "getAnalogData",            /* pcName */
   1000,                   /* usStackDepth */
   NULL,                   /* pvParameters */
   1,                      /* uxPriority */
   NULL,                 /* pxCreatedTask */
   0);
  
}

void loop() {

}
