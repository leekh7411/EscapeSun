
#include "Bboobboo.h"

Bboobboo::Bboobboo()
{
    this->pinNum = BUZZER_PIN_NUMER;
    pinMode(pinNum, OUTPUT);
}


void Bboobboo::turnOn()
{
   digitalWrite(pinNum, HIGH);   
   delay(1000);
}


void Bboobboo::turnOff()
{
   digitalWrite(pinNum, LOW);  
   delay(1000);
}
