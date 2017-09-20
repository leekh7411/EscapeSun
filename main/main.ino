#include "pulse.h"
#include "InfraredTemperature.h"
#include "Bboobboo.h"
#include "checkHeat.h"
#include "movement.h"
#include "BleManager.h"
#include "StepDetection.h"
#include "TimeCheck.h"
#include <CurieBLE.h>

/*Bluetooth Low Energy*/
// Main Service UUID
BLEService escSunService("19B10000-E8F2-537E-4F6C-D104768A1214"); 
BLECharCharacteristic switch0("19B10001-E8F2-537E-4F6C-D104768A1214", BLERead | BLEWrite);
BLEIntCharacteristic distanceData("19B10002-E8F2-537E-4F6C-D104768A1214", BLERead | BLEWrite);
BLEIntCharacteristic emergency("19B10003-E8F2-537E-4F6C-D104768A1214", BLERead | BLEWrite);
BLEIntCharacteristic limit_distance("19B10011-E8F2-537E-4F6C-D104768A1214", BLERead | BLEWrite);
BLEIntCharacteristic limit_heart_rate("19B10012-E8F2-537E-4F6C-D104768A1214", BLERead | BLEWrite);
BLEIntCharacteristic limit_humidity("19B10013-E8F2-537E-4F6C-D104768A1214", BLERead | BLEWrite);
BLECharacteristic sensorData("19B10006-E8F2-537E-4F6C-D104768A1214",BLERead | BLENotify, 4);
BLEDevice central;
PulseSensor pulse;
Movement movement;
InfraredTemperature infraredTemp;
Bboobboo buzzer;
checkHeat checkheat;
BleManager blemanager;
StepDetection stepdetection;
TimeCheck currentTime;
int buttonPin = 13;

void setup() {
  // put your setup code here, to run once:
  pinMode(buttonPin, INPUT);
  Serial.begin(9600);
  blemanager = BleManager(escSunService,switch0,sensorData,distanceData,emergency,limit_distance,limit_heart_rate,limit_humidity);
   stepdetection  = StepDetection();
  stepdetection.init();
  checkheat.init(&blemanager);
  //movement.init();
  infraredTemp = InfraredTemperature();
  buzzer = Bboobboo();
  currentTime.init();
}
 

// 심박 수 측정을 위한 delay, loop()에서 전체적인 delay의 틀
const int delayMsec = 100;
// 심박 수를 마지막으로 측정한 시간
long previousMillis = 0;

// 온도 체크 딜레이
int tempDelay = 0;
int tempHumidDelay = 0;
void loop()
{  

  if (!stepdetection.stepEventsEnabeled) {
     
    stepdetection.updateStepCount();
  }
  //  currentTime.resetTime();  
  delay(1000);
  //  Serial.print("초 : ");
  //  Serial.println(currentTime.Secondtime());
  //  Serial.print("분 : ");
  //  Serial.println(currentTime.Minutetime());
 // blemanager.initInLoop(central,sensorData,distance,switch0,emergency,limit_distance,limit_heart_rate,limit_humidity);
//  Serial.println(blemanager.getLimitDistance());
  /*
  blemanager.initInLoop(central,sensorData,distance,switch0,emergency,limit_distance,limit_heart_rate,limit_humidity);
  Serial.println(blemanager.getLimitDistance());

    if (!stepdetection.stepEventsEnabeled) {
      stepdetection.updateStepCount();
    }
    //currentTime.resetTime();  
    //stepdetection.movement();
    //Serial.print("초 : ");
    //Serial.println(currentTime.Secondtime());
    //Serial.print("분 : ");
    //Serial.println(currentTime.Minutetime());
    blemanager.initInLoop(central,sensorData,distanceData,switch0,emergency,limit_distance,limit_heart_rate,limit_humidity);

  //Serial.println("in loop");
  long currentMillis = millis();
  // if 200ms have passed, check the heart rate measurement:
  if (currentMillis - previousMillis >= 200) {
    previousMillis = currentMillis;
  }

  
  // Note: I assume the sleep delay is way longer than the
  // number of cycles used to run the code hence the error
  // is negligible for math.

  if(tempDelay > 2000){
    
    if(isZeroMotion == true)  // 모션이 없을 때
      Serial.println("------zero motion detected!-------");
    if(isZeroMotion == false) // 모션이 감지됨...
      Serial.println("======motion detected======");
    
    tempDelay = 0;
  }
 
  if(tempHumidDelay > 1000){
      checkheat.allcheck();
      checkheat.sendCall(isZeroMotion);
      tempHumidDelay = 0;
    }
    
   
  delay(delayMsec);
  */
 // tempHumidDelay += delayMsec;
  //tempDelay += delayMsec;
  
}

