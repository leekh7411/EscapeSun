#include "checkHeat.h"

checkHeat::checkHeat()
{
	   currentMillis = millis();
	   previousMillis = currentMillis-30000;
	   boo = 0;
     	   bodyTemp= 0;
   	   Temp = 0;
   	   Heart = 0;
	   BodyTempdegree = 0;
           Tempdegree = 0;
           Heartdegree = 0;
	   buzzer = Bboobboo();
}


int checkHeat::SendCall()
{
	if( (Tempdegree+ BodyTempdegree+ Heartdegree) >=5){
		boo = 1;
		buzzer.turnOn();
		  
	}
	else{
		  return 0 ;
		// 계속 검사를 한다.
	}
}


void checkHeat::checkBodyTemp()
{
	infraredTemp = InfraredTemperature();
	bodyTemp = infraredTemp.getObjectTempC();
        Serial.print("bodytemp= " );
	Serial.println(bodyTemp);
	if(bodyTemp <38){
		BodyTempdegree = 0;}
	else if(Temp <39){
		BodyTempdegree = 1;}
	else if(Temp <40){
		BodyTempdegree = 3;}
	else{
		BodyTempdegree = 5;}
}

void checkHeat::checkTemp()
{
        m_temp.temp_est(); 
	Temp = m_temp.getTemp();
        Serial.print("temp= " );
	Serial.println(Temp);
	if(Temp >= 30 && Temp <34 ){
		Tempdegree = 1;}
	else if(Temp>=34 && Temp <39){
		Tempdegree = 2;}
	else if(Temp >=39){
		Tempdegree = 3;}
	else{
		Tempdegree = 0;}
}

void checkHeat::checkHeart()
{
	Heart  = pulse.updateHeartRate();
 	if(Heart == -1){
    		Heart = pulse.getHeartRate();
 	 }
        Serial.print("pulse!!= " );
	Serial.println(Heart);
	if(Heart <38){                   //여기는 심박수에 따른 점수
		Heartdegree = 0;}
	else if(Heart <39){
		Heartdegree = 1;}
	else if(Heart <40){
		Heartdegree = 2;}
	else{
		Heartdegree = 3;}
}

void checkHeat::Allcheck(){
	currentMillis = millis();	
	checkBodyTemp();
	checkTemp();
	checkHeart();
        Serial.print("time!!= " );
	Serial.println(currentMillis);
        Serial.print("pretime!!= " );
	Serial.println(previousMillis);
	if(boo == 0 && (currentMillis-previousMillis)>=30000){ // 그리고 시간값까지
		SendCall();
	}
}

void checkHeat::deBoo(){

	previousMillis = millis();
	boo = 0;
	buzzer.turnOff();
}
