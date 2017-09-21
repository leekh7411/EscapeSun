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
	humidityDegree = 0;
	count = 0;
	buzzer = Bboobboo();
	Temperature_Time.init();
	BodyHeat_Time.init();
	HeartRate_Time.init();
	Humidity_Time.init();
	Movement_Time.init();
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
	if(BodyHeat_Time.Secondtime() > SENSOR_CHECK_TIME){
		BodyHeat_Time.resetTime();
		Serial.print("bodytemp= " );
		Serial.println(bodyTemperature);
		if(bodyTemperature < 37){
			bodyTempDegree = 0;
		}
		else if(bodyTemperature < 38){
			bodyTempDegree = 1;
		}
		else if(bodyTemperature < 39){
			bodyTempDegree = 2;
		}
		else if(bodyTemperature < 40){
			bodyTempDegree = 3;
		}
		else{
			bodyTempDegree = 4;
		}

		// Add Score stack
		if(bodyTempDegree > 0)BodyHeat_Score_Stack[bodyTempDegree-1]++;
		
		// Remove Score stack
		for(int i = bodyTempDegree; i < BODY_HEAT_STACK_SIZE ; i++){
			if(BodyHeat_Score_Stack[i] > 0)BodyHeat_Score_Stack[i]--;
		}

		// Caculate Score
		BodyHeat_Score = 0;
		for(int i = 0 ; i < BODY_HEAT_STACK_SIZE; i++){
			BodyHeat_Score += BodyHeat_Score_Stack[i] * (i+1);
		}

		// Print Score
		Serial.print("BodyHeat_Score : ");
		Serial.println(BodyHeat_Score);	
	}
	
}

void checkHeat::checkTemp(int temperature)
{
	if(Temperature_Time.Secondtime() > SENSOR_CHECK_TIME){
		Temperature_Time.resetTime();
		Serial.print("temp= " );
		Serial.println(temperature);
		if(temperature >= 30 && temperature < 34 ){
			tempDegree = 1;
			Temperature_Score_Stack[0]++;	
		}
		else if(temperature >= 34 && temperature < 39){
			tempDegree = 2;
			Temperature_Score_Stack[1]++;	
		}
		else if(temperature >= 39){
			tempDegree = 3;
			Temperature_Score_Stack[2]++;
		}
		else{
			tempDegree = 0;
		}

		for(int i = tempDegree; i < TEMPERATURE_STACK_SIZE ; i++){
			if(Temperature_Score_Stack[i] > 0)Temperature_Score_Stack[i]--;
		}

		Temperature_Score = 0;
		for(int i = 0 ; i < TEMPERATURE_STACK_SIZE ; i++){
			Temperature_Score += (Temperature_Score_Stack[i] * (i+1));
		}
		
		Serial.print("Temperature_Score : ");
		Serial.println(Temperature_Score);
	}
}

void checkHeat::SetCurrentTemperatureScore(){
	Temperature_Score = 0;
	for(int i = 0 ; i < TEMPERATURE_STACK_SIZE ; i++){
		Temperature_Score += (Temperature_Score_Stack[i] * (i+1));
	}
	Serial.print("Temperature_Score : ");
	Serial.println(Temperature_Score);
}
void checkHeat::TemperatureScoreStackPop(int idx){
	for(int i = idx; i < TEMPERATURE_STACK_SIZE ; i++){
		if(Temperature_Score_Stack[i] > 0)Temperature_Score_Stack[i]--;
	}
}

void checkHeat::checkHeart(int heartRate)			
{
	if(HeartRate_Time.Secondtime() > SENSOR_CHECK_TIME){
		HeartRate_Time.resetTime();
		Serial.print("pulse!!= " );
		Serial.println(heartRate);

		if(heartRate < 50){
			heartDegree = 3;
		}else if(50 <= heartRate && heartRate < 60){
			heartDegree = 1;
		}else if(60 <= heartRate && heartRate < 80){
			heartDegree = 0;
		}else if(80 <= heartRate && heartRate < 110){
			heartDegree = 1;
		}else if(110 <= heartRate && heartRate < 130){
			heartDegree = 2;
		}else if(130 <= heartRate && heartRate < 150){
			heartDegree = 3;
		}else{
			heartDegree = 4;
		}

		// Add Score stack
		if(tempDegree){
			if(heartDegree > 0)HeartRate_Score_Stack[heartDegree-1]++;
		}
		// Remove Score stack
		for(int i = heartDegree; i < HEART_RATE_STACK_SIZE ; i++){
			if(HeartRate_Score_Stack[i] > 0)HeartRate_Score_Stack[i]--;
		}

		// Caculate Score
		HeartRate_Score = 0;
		for(int i = 0 ; i < HEART_RATE_STACK_SIZE; i++){
			HeartRate_Score += HeartRate_Score_Stack[i] * (i+1);
		}

		// Print Score
		Serial.print("HeartRate_Score : ");
		Serial.println(HeartRate_Score);	
	}										
	
}

void checkHeat::checkHumidity(int humidity){
	if(Humidity_Time.Secondtime() > SENSOR_CHECK_TIME){
		Humidity_Time.resetTime();
		Serial.print("Humidity = ");
		Serial.println(humidity);	
		if(0 <=  humidity && humidity < 60 ){
			humidityDegree = 0;
		}else if(70 <=  humidity && humidity < 90 ){
			humidityDegree = 1;	
		}else if(90 <=  humidity && humidity < 100 ){
			humidityDegree = 2;	
		}else{
			//error!
			humidityDegree = 0;
		}	
		if(tempDegree){
			// Add Score stack
			if(humidityDegree > 0)Humidity_Score_Stack[humidityDegree-1]++;
		}
		// Remove Score stack
		for(int i = humidityDegree; i < HUMIDITY_STACK_SIZE ; i++){
			if(Humidity_Score_Stack[i] > 0)Humidity_Score_Stack[i]--;
		}

		// Caculate Score
		Humidity_Score = 0;
		for(int i = 0 ; i < HUMIDITY_STACK_SIZE; i++){
			Humidity_Score += Humidity_Score_Stack[i] * (i+1);
		}

		// Print Score
		Serial.print("Humidity_Score : ");
		Serial.println(Humidity_Score);	

	}
}

int checkHeat::checkMovement(StepDetection stepdetect){
	Movement_Time.resetTime();
	stepdetect.iammove = false;
	//stepdetect.updateStepCount();
	int movementnum = 0;
	while(Movement_Time.Secondtime() < SENSOR_CHECK_TIME){

		 if(stepdetect.iammove == 1){
		 	//움직임이 있다.
		 	movementnum = 1;
		 }
		delay(1000);
	}
	return movementnum;
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
			/*
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
			*/
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
	checkHumidity(median[HUMI].getAverage(median[HUMI].getMedian()));

	for(int i = 0; i < MEDIAN_SIZE; i++){
		median[i].clear();
	}
}

void checkHeat::allcheck(){
	currentMillis = millis();	
	checkMedian();
	
	/*Serial.print("curTime!!= " );
	Serial.println(currentMillis);
	
	Serial.print("prevTime!!= " );
	Serial.println(previousMillis);
	*/
	// if(boo == 0 && (currentMillis - previousMillis) >= 30000){ // ±×¸®°í ½Ã°£°ª±îÁö
		// SendCall();
	// }
}


bool checkHeat::heatCramps(){
	if(Humidity_Score + Temperature_Score > 600){
		return true;
	}
	return false;
}

bool checkHeat::heatExhaustion(){

	if(bodyTempDegree > 1){
		if(Humidity_Score + Temperature_Score + HeartRate_Score > 1200){
			return true;
		}
	}
	else if(bodyTempDegree == 0){
		if(Humidity_Score + Temperature_Score + HeartRate_Score > 1500){
			return true;
		}
	}
	return false;

}

bool checkHeat::heatStroke(){
	if(bodyTempDegree > 3 ){
		return true;
	}
	else if(bodyTempDegree > 2){
		if(Humidity_Score + Temperature_Score + HeartRate_Score > 900){
			return true;
		}
	}
	return false;
}

void checkHeat::heatAllcheck(StepDetection stepdetect){
	int degree = 0;
	if(heatStroke()){
		degree = 3;
	}
	else if(heatExhaustion()){
		degree = 2;
	}
	else if(heatCramps()){
		degree = 1;
	}

	if(degree == 1){
		// 중증 1 의 경고를 보내준다.
	}
	else if (degree == 2){
		// 중증 2의 경고를 보내준다.
	}
	else if (degree == 3){
		// 중증 3의 경고를 보내준다.
	}

	if(degree != 0 ){
		if (tempDegree  == 0){
			// 그늘이니까 쉬는거로 간주
		}
		else{
			if(checkMovement(stepdetect) == 1){
				//움직임이 있다.
			}
			else{
				//움직임이 없다. 부저를 울린다.
			}
		}
	}

}