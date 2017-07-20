#ifndef InfraredTemperature_h
#define InfraredTemperature_h

#include <Wire.h>
#include "Adafruit-MLX90614\Adafruit_MLX90614.h"

class InfraredTemperature {
  private:
    Adafruit_MLX90614 mlx; 
    float ambientTempC;
    float objectTempC;

  public:
    InfraredTemperature();
    void getAmbientTempC();
    void getObjectTempC();
    void printTempC();
    void checkTemp();
};

#endif
