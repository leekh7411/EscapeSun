#include "BleManager.h"

BleManager::BleManager(){
  // Main Service UUID
  escSunService = new BLEService("19B10000-E8F2-537E-4F6C-D104768A1214");
  // Char characteristic  
  switchCharacteristic = new BLECharCharacteristic("19B10001-E8F2-537E-4F6C-D104768A1214", BLERead | BLEWrite);
  // Integer characteristic
  sensorCharacteristic = new BLEIntCharacteristic("19B10002-E8F2-537E-4F6C-D104768A1214", BLERead | BLENotify);
  BLE.begin(); // BLE object init in 'CurieBLE.h' library
  BLE.setLocalName("SUN"); // Ble's Tag name
  BLE.setAdvertisedService(*escSunService); // set the Service
  escSunService->addCharacteristic(*sensorCharacteristic); // add Characteristic in the Service
  escSunService->addCharacteristic(*switchCharacteristic); // add Characteristic in the Service
  BLE.addService(*escSunService);
  switchCharacteristic->setValue(0);
  sensorCharacteristic->setValue(100); // first initialize (now random value)
  BLE.advertise();
  Serial.println("Escape Sun Ble Manager Peripheral setup finish!");
}

void BleManager::setIntSensorValue(int value){

}

void BleManager::initInLoop(){
  central = BLE.central();
}

