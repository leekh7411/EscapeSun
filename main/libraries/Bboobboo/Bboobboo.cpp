
#include "Bboobboo.h"

#include "arduino.h"
Bboobboo::Bboobboo()
{
    this->pinNum = BUZZER_PIN_NUMER;
    pinMode(pinNum, OUTPUT);
    IsBzOn = false;
    IsEmergencyButtonOn = false;
	userButtonTimer.init();
	bzTimer.init();
	bzOnOffFlag = false;
}


void Bboobboo::turnOn()
{
	IsBzOn = true;
   	digitalWrite(pinNum, HIGH);
   	delay(1000);
}

void Bboobboo::turnOnGapTime(int time_gap){
	if(bzTimer.Milistime()>time_gap){
		bzOnOffFlag = !bzOnOffFlag;
		bzTimer.resetTime();
		if(bzOnOffFlag)Bboobboo::turnOn();
		else Bboobboo::turnOff();
		Serial.println("turn on/off the bz");
	}
}


void Bboobboo::turnOff()
{
	IsBzOn = false;
  	digitalWrite(pinNum, LOW);  
}

bool Bboobboo::checkButtonOff(){
	if(IsBzOn){
		int buttonState = digitalRead(BUTTON_PIN_NUMBER);    
		if(buttonState == LOW){
			turnOff();
			return true;
		}else{
			return false;
		}
	}else{
		return false;
	}   
}

