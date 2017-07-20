#include "DHT11.h" 
#include "tempFunction.h"
void temp_func::temp_est()
{
  DHT11 dht11(2); 
  int err;    // result code
  float temp, humi;   // tempera  ture, humidity

  if((err=dht11.read(humi, temp))==0)
  {
    Serial.print("temperature:");
    Serial.print(temp);
    Serial.print(" humidity:");
    Serial.print(humi);
    Serial.println();
  }
  else
  {
    Serial.println();
    Serial.print("Error No :");
    Serial.print(err);
    Serial.println();    
  }
  delay(DHT11_RETRY_DELAY); //delay for reread
}

