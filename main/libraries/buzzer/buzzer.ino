
#include "Bboobboo.h"

 Bboobboo buzzer;
 
void setup() {
   // put your setup code here, to run once:
   buzzer = Bboobboo();
}

void loop() {
  // put your main code here, to run repeatedly:
   buzzer.turnOn();
   buzzer.turnOff();
   
/*
     tone(buzzerPin, 2000);
     delay(500);
     
     tone(buzzerPin, 500);
     delay(500); 
*/
}

