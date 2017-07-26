#include "pulse.h"
#include "InfraredTemperature.h"
#include "Bboobboo.h"
#include "checkHeat.h"

PulseSensor pulse;
InfraredTemperature infraredTemp;
Bboobboo buzzer;
checkHeat checkheat;
int ledPin = 13;

void setup() {
  // put your setup code here, to run once:
  pinMode(13, OUTPUT);
  Serial.begin(9600);

  infraredTemp = InfraredTemperature();
  buzzer = Bboobboo();
}
 

// 심박 수 측정을 위한 delay, loop()에서 전체적인 delay의 틀
const int delayMsec = 60;
// 심박 수를 마지막으로 측정한 시간
long previousMillis = 0;

// 온도 체크 딜레이
int tempDelay = 0;
int tempHumidDelay = 0;
void loop()
{
  Serial.println("a");
  int heartRateBPM = 0;
  
  long currentMillis = millis();
  // if 200ms have passed, check the heart rate measurement:
  if (currentMillis - previousMillis >= 200) {
    previousMillis = currentMillis;
  }

  
  // Note: I assume the sleep delay is way longer than the
  // number of cycles used to run the code hence the error
  // is negligible for math.

  if(tempDelay > 2000){

    buzzer.turnOn();
    buzzer.turnOff();
    
    tempDelay = 0;
  }
  if(tempHumidDelay > 1000){
    checkheat.checkTemp();
    checkheat.checkBodyTemp();
    checkheat.checkHeart();    
    tempHumidDelay = 0;
  } 
  delay(delayMsec);
  tempHumidDelay += delayMsec;
  tempDelay += delayMsec;
}
