#ifndef InfraredTemperature_h
#define InfraredTemperature_h

#include <Wire.h>
#include "Adafruit_MLX90614.h"

class InfraredTemperature {
  private:
    Adafruit_MLX90614 mlx; 
    float ambientTempC;
    float objectTempC;

  public:
    InfraredTemperature();
    float getAmbientTempC();
    float getObjectTempC();
    void printTempC();
    void checkTemp();
};

#endif
