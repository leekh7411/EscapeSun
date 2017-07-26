
#include "InfraredTemperature.h"


InfraredTemperature::InfraredTemperature()
{
    mlx = Adafruit_MLX90614();
    mlx.begin();
}

float InfraredTemperature::getAmbientTempC()
{
   ambientTempC = mlx.readAmbientTempC();
   return ambientTempC;
}

float InfraredTemperature::getObjectTempC()
{
   objectTempC = mlx.readObjectTempC();
   return objectTempC;
}

void InfraredTemperature::printTempC()
{
  Serial.print("Ambient = ");
  Serial.print(ambientTempC);

  Serial.print("*C\tObject = ");
  Serial.print(objectTempC);

  Serial.println("*C");
  //delay(1000);
}

void InfraredTemperature::checkTemp()
{
  getAmbientTempC();
  getObjectTempC();
  printTempC();
}

