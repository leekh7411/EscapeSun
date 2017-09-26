
#include "Bboobboo.h"

Bboobboo::Bboobboo()
{
    this->pinNum = BUZZER_PIN_NUMER;
    pinMode(pinNum, OUTPUT);
    IsBzOn = false;
}


void Bboobboo::turnOn()
{
	IsBzOn = true;
   digitalWrite(pinNum, HIGH);
   delay(1000);
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
