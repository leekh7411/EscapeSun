#include "DHT11.h" 
#include "tempFunction.h"
float temp_func::getHumi()
{
  DHT11 dht11(2); 
  int err;    // result code
  float temp, humi;   // tempera  ture, humidity

  if((err=dht11.read(humi, temp))==0)
  {
	return humi;
  }
  else
  {
    Serial.println();
    Serial.print("Error No :");
    Serial.print(err);
    Serial.println();    
  }
}

float temp_func::getTemp(){
 DHT11 dht11(2); 
  int err;    // result code
  float temp, humi;   // tempera  ture, humidity

  if((err=dht11.read(humi, temp))==0)
  {
	return temp;
  }
  else
  {
    Serial.println();
    Serial.print("Error No :");
    Serial.print(err);
    Serial.println();    
  }
}

