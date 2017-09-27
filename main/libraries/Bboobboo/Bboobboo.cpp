
#include "Bboobboo.h"

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
		bzOnOffFlag != bzOnOffFlag;
		bzTimer.resetTime();
		if(bzOnOffFlag)Bboobboo::turnOn();
		else Bboobboo::turnOff();
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
			Bboobboo::turnOff();
			return true;
		}else{
			return false;
		}
	}else{
		return false;
	}   
}



bool Bboobboo::userEmergencyCheck(){
	int buttonState = digitalRead(BUTTON_PIN_NUMBER);// Read the button state 
	if(buttonState == LOW){// if button Push
		if(IsEmergencyButtonOn == false){//   when first push
			IsEmergencyButtonOn = true; // -> Init the flag
			userButtonTimer.resetTime();// -> reset the timer
		}else{
			if(userButtonTimer.Secondtime() > 5){ 
				// push time over 5 seconds.. then..
				IsEmergencyButtonOn = false;	
				userButtonTimer.resetTime();
				Bboobboo::turnOff();
				// Send the Emergency Messages
				return true;
			}else{
				// push time under 5 senconds
				// Buzzer (B! B! B! .... ) ON
				Bboobboo::turnOnGapTime(100);// buzzer time gap : 100 ms
			}
		}
	}else{ // if Not push
		if(IsEmergencyButtonOn){ // Before emergency button push timer gone under 5 seconds, detached the button 
			IsEmergencyButtonOn = false;
		}else{
			// default loop
		}
	}
	return false;
}
