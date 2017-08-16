#include "pulse.h"
#include "InfraredTemperature.h"
#include "Bboobboo.h"
#include "checkHeat.h"
#include "movement.h"
#include "BleManager.h"
#include <CurieBLE.h>

/*Bluetooth Low Energy*/
// Main Service UUID
BLEService escSunService("19B10000-E8F2-537E-4F6C-D104768A1214"); 
BLECharCharacteristic switch0("19B10001-E8F2-537E-4F6C-D104768A1214", BLERead | BLEWrite);

BLECharacteristic sensorData("19B10006-E8F2-537E-4F6C-D104768A1214",BLERead | BLENotify, 4);
BLEDevice central;

PulseSensor pulse;
Movement movement;
InfraredTemperature infraredTemp;
Bboobboo buzzer;
checkHeat checkheat;
BleManager blemanager;
int ledPin = 13;

void setup() {
  // put your setup code here, to run once:
  pinMode(13, OUTPUT);
  Serial.begin(9600);
  blemanager = BleManager(escSunService,switch0,sensorData);
  //blemanager = BleManager();
  //BleManagerSetup();
  movement.init();
  infraredTemp = InfraredTemperature();
  buzzer = Bboobboo();
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
  blemanager.initInLoop(central,sensorData);
  
  /*long currentMillis = millis();
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
    if(checkheat.sendCall(isZeroMotion) == 1){

      //여기서부터 시간을 잰다. 30 초 이상 지났을 때 블루투스로 전화를 건다.
      // 버튼을 누르고 나서 다시 여기로 들어올 때
    }

    // 버튼을 누르면 checkHeat::deBoo()를 사용한다.
    tempHumidDelay = 0;
  } 
  delay(delayMsec);
  tempHumidDelay += delayMsec;
  tempDelay += delayMsec;*/
  
}

/*void BleManagerSetup(){
  // Main Service UUID
  //escSunService = new BLEService("19B10000-E8F2-537E-4F6C-D104768A1214");
  // Char characteristic  
  //switchCharacteristic = new BLECharCharacteristic("19B10001-E8F2-537E-4F6C-D104768A1214", BLERead | BLEWrite);
  // Integer characteristic
  //sensorCharacteristic = new BLEIntCharacteristic("19B10002-E8F2-537E-4F6C-D104768A1214", BLERead | BLENotify);
  BLE.begin(); // BLE object init in 'CurieBLE.h' library
  BLE.setLocalName("SUN"); // Ble's Tag name
  BLE.setAdvertisedService(escSunService); // set the Service
  escSunService.addCharacteristic(sensorCharacteristic); // add Characteristic in the Service
  escSunService.addCharacteristic(switchCharacteristic); // add Characteristic in the Service
  BLE.addService(escSunService);
  switchCharacteristic.setValue(0);
  sensorCharacteristic.setValue(100); // first initialize (now random value)
  BLE.advertise();
  Serial.println("Escape Sun Ble Manager Peripheral setup finish!");
}*/
