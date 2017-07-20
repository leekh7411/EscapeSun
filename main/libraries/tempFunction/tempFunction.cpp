#include "DHT11.h" 
#include "tempFunction.h"

void temp_func::temp_est()
{
  int err;    // result code
  float temp_tmp, humi_tmp;   // tempera  ture, humidity

  if((err=dht11.read(humi_tmp, temp_tmp))==0)
  {
	humi = humi_tmp;
	temp = temp_tmp;
  }
  else
  {
    Serial.println();
    Serial.print("Error No :");
    Serial.print(err);
    Serial.println();    
  }
}


float temp_func::getHumi()
{

	return humi;

}

float temp_func::getTemp(){

	return temp;

}

