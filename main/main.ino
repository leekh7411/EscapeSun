//#include <pulse.h>
#include "pulse.h"
#include "InfraredTemperature.h"
#include "Bboobboo.h"
#include "tempFunction.h"

PulseSensor pulse;
InfraredTemperature infraredTemp;
Bboobboo buzzer;

temp_func m_temp;
int ledPin = 13;

void setup() {
  // put your setup code here, to run once:
  pinMode(13, OUTPUT);
  Serial.begin(9600);

  infraredTemp = InfraredTemperature();
  buzzer = Bboobboo();
}
 

//심박 수 측정을 위한 delay, loop()에서 전체적인 delay의 틀
const int delayMsec = 60;

// 온도 체크 딜레이
int tempDelay = 0;
int tempHumidDelay = 0;
void loop()
{
  static int beatMsec = 0;
  int heartRateBPM = 0;
  
  if (pulse.heartbeatDetected(delayMsec)) {
    heartRateBPM = 60000 / beatMsec;
 
    // Print msec/beat and instantaneous heart rate in BPM
    Serial.print(beatMsec);
    Serial.print(", ");
    Serial.println(heartRateBPM);
    
    beatMsec = 0;
  }
  // Note: I assume the sleep delay is way longer than the
  // number of cycles used to run the code hence the error
  // is negligible for math.

  if(tempDelay > 2000){
    infraredTemp.checkTemp();
    
    buzzer.turnOn();
    buzzer.turnOff();
    
    tempDelay = 0;
  }
    if(tempHumidDelay > 1000){
    m_temp.temp_est();
   
    tempHumidDelay = 0;
  } 
  delay(delayMsec);
  tempHumidDelay += delayMsec;
  tempDelay += delayMsec;
  beatMsec += delayMsec;
}
