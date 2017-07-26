#include "checkHeat.h"
#include "Bboobboo.h"
#include "tempFunction.h"
#include "InfraredTemperature.h"
checkHeat::checkHeat()
{
     	   bodyTemp= 0;
   	   Temp = 0;
   	   Heart = 0;
}


void checkHeat::SendCall()
{
	if( (bodyTemp+Temp+Heart) >=5){
		//블루투스 사용해서 폰으로 전화를 한다.
	}
	else{
		// 계속 검사를 한다.
	}
}


void checkHeat::checkBodyTemp()
{
	InfraredTemperature infraredTemp;
	infraredTemp = InfraredTemperature();
	bodyTemp = infraredTemp.getObjectTempC();
        Serial.print("bodytemp= " );
	Serial.println(bodyTemp);
}

void checkHeat::checkTemp()
{
	temp_func m_temp;
        m_temp.temp_est(); 
	Temp = m_temp.getTemp();
        Serial.print("temp= " );
	Serial.println(Temp);
}

void checkHeat::checkHeart()
{
	PulseSensor pulse;
	Heart  = pulse.updateHeartRate();
 	if(Heart == -1){
    		Heart = pulse.getHeartRate();
 	 }
        Serial.print("pulse!!= " );
	Serial.println(Heart);
}
