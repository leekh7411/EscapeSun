#include "checkHeat.h"

#define TEMP 			0
#define BODY 			1
#define HEART			2
#define HUMI 	3

#define BODY_TEMP_MAX	50
#define BODY_TEMP_MIN	30

#define TEMP_MAX		50

#define TEMP_MIN		10
#define HEART_MAX		200
#define HEART_MIN		40

checkHeat::checkHeat()
{
	currentMillis = millis();
	previousMillis = currentMillis-30000;
	boo = 0;
	bodyTemp= 0;
	temp = 0;
	heart = 0;
	bodyTempDegree = 0;
	tempDegree = 0;
	heartDegree = 0;
	count = 0;
	buzzer = Bboobboo();
}

void checkHeat::init(BleManager *Manager){
  manager = Manager;
}

void checkHeat::deBoo(){
	previousMillis = millis();
	boo = 0;
	buzzer.turnOff();
}


void checkHeat::sendCall(int zeroMotion)
{

	count = tempDegree + bodyTempDegree + heartDegree;
	
	if(zeroMotion)
		count++;
		
	Serial.print("count : ");
	Serial.println(count);
	
	if(count >= 5){
		boo = 1;
		long currentMillis = millis();
		long laterMillis;
		buzzer.turnOn();
		int buttonState;    

    while(1) {
    	laterMillis = millis();
    	bool flag;
    	if(laterMillis-currentMillis > 30000) {

    			Serial.println("time 30 over");
    			if(!flag){
    				// send messeage
    				//manager->setIntSensorValue(, int(119));
    			}
    			deBoo();
    			delay(1500);
    			buzzer.turnOn();
    	}

      buttonState = digitalRead(13);    
      if(buttonState == LOW){         
         deBoo();
         break;
      } 
    }


	}
}

void checkHeat::isLongPress(){
      int buttonState = digitalRead(13);    
      if(buttonState == LOW){
      	long currentMillis = millis();
		long laterMillis = millis();         
      	while(laterMillis-currentMillis < 5000){
      		laterMillis = millis();
      		if(buttonState == HIGH){
      			return;
      		}
      	}
      	// send message to smartphone hi:
      	//manager->setIntSensorValue(, int(119));
      } 
}
void checkHeat::checkBodyTemp(float bodyTemperature)
{
	Serial.print("bodytemp= " );
	Serial.println(bodyTemperature);
	if(bodyTemperature < 38){
		bodyTempDegree = 0;
	}
	else if(bodyTemperature < 39){
		bodyTempDegree = 1;
	}
	else if(bodyTemperature < 40){
		bodyTempDegree = 3;
	}
	else{
		bodyTempDegree = 5;
	}
}

void checkHeat::checkTemp(int temperature)
{
  Serial.print("temp= " );
	Serial.println(temperature);
	if(temperature >= 30 && temperature < 34 ){
		tempDegree = 1;
	}
	else if(temperature >= 34 && temperature < 39){
		tempDegree = 2;
	}
	else if(temperature >= 39){
		tempDegree = 3;
	}
	else{
		tempDegree = 0;
	}
}

void checkHeat::checkHeart(int heartRate)			// 정상 성인: 60 ~ 80
{										// 정상 노인: 70 ~ 80
	Serial.print("pulse!!= " );// 정상 어린이: 90 ~ 140
	Serial.println(heartRate);
	if(heartRate < 100){                   
		heartDegree = 0;
	}
	else{								// 분당 100회 이상일 때
		heartDegree = 2;
	}
}

void checkHeat::checkMedian(){
	infraredTemp = InfraredTemperature();
	mTemp.temp_est(); 
	for(int i = 0; i < MEDIAN_MAX_SIZE; i++){
		bodyTemp = infraredTemp.getObjectTempC();
		temp = mTemp.getTemp();
		humidity = mTemp.getHumi();
		heart  = pulse.updateHeartRate();	
		if(heart == -1){					
			heart = pulse.getHeartRate();
		}
		if(bodyTemp > BODY_TEMP_MAX || bodyTemp < BODY_TEMP_MIN 
			|| temp < TEMP_MIN || temp > TEMP_MAX 
			|| heart < HEART_MIN || heart > HEART_MAX ){
			i--;
			Serial.print(bodyTemp);
			Serial.print(" ");
			Serial.print(BODY_TEMP_MAX);
			Serial.print(" ");
			Serial.println(BODY_TEMP_MIN);
			
			Serial.print(temp);
			Serial.print(" ");
			Serial.print(TEMP_MAX);
			Serial.print(" ");
			Serial.println(TEMP_MIN);
			
			Serial.print(heart);
			Serial.print(" ");
			Serial.print(HEART_MAX);
			Serial.print(" ");
			Serial.println(HEART_MIN);
			Serial.println();

			Serial.print(humidity);
			Serial.print(" ");
			Serial.println();
			
			delay(100);
			
			continue;
		}
		median[HEART].add(heart);
		median[TEMP].add(temp);
		median[BODY].add(bodyTemp);
		median[HUMI].add(humidity);
	}

	manager->setIntSensorValue(manager->TEMPERATURE, int(median[manager->TEMPERATURE].getAverage(median[manager->TEMPERATURE].getMedian())));
	manager->setIntSensorValue(manager->BODYHEAT, int(median[manager->BODYHEAT].getAverage(median[manager->BODYHEAT].getMedian())));
	manager->setIntSensorValue(manager->HEARTRATE, int(median[manager->HEARTRATE].getAverage(median[manager->HEARTRATE].getMedian())));
	manager->setIntSensorValue(manager->HUMIDITY, int(median[manager->HUMIDITY].getAverage(median[manager->HUMIDITY].getMedian())));
	
	checkBodyTemp(median[BODY].getAverage(median[BODY].getMedian()));
	checkTemp(median[TEMP].getAverage(median[TEMP].getMedian()));
	checkHeart(median[HEART].getAverage(median[HEART].getMedian()));
	
	for(int i = 0; i < MEDIAN_SIZE; i++){
		median[i].clear();
	}
}

void checkHeat::allcheck(){
	currentMillis = millis();	
	checkMedian();
	
	Serial.print("curTime!!= " );
	Serial.println(currentMillis);
	
	Serial.print("prevTime!!= " );
	Serial.println(previousMillis);
	
	// if(boo == 0 && (currentMillis - previousMillis) >= 30000){ // 그리고 시간값까지
		// SendCall();
	// }
}
