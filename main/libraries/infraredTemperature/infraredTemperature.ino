/***************************************************
  This is a library example for the MLX90614 Temp Sensor

  Designed specifically to work with the MLX90614 sensors in the
  adafruit shop
  ----> https://www.adafruit.com/products/1748
  ----> https://www.adafruit.com/products/1749

  These sensors use I2C to communicate, 2 pins are required to
  interface1
  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.
  BSD license, all text above must be included in any redistribution
 ****************************************************/

#include "InfraredTemperature.h"

InfraredTemperature infraredTemp;
 
void setup() {
  Serial.begin(9600);
  Serial.println("Adafruit MLX90614 test");

  infraredTemp = InfraredTemperature();
}

void loop() {

  infraredTemp.checkTemp();
  
}
