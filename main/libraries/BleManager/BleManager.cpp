#include "BleManager.h"
BleManager::BleManager(){
  // Default Constructor
}
BleManager::BleManager(
    BLEService escSunService,
    BLECharCharacteristic switch0,
    BLECharacteristic sensorData
  ){
  MAX = 10; cnt = 0; 
  for(int i = 0 ; i < 3 ; i++)sensor_val[i] = (i+1) * 50;
  BLE.begin(); // BLE object init in 'CurieBLE.h' library
  BLE.setLocalName("SUN"); // Ble's Tag name
  BLE.setAdvertisedService(escSunService); // set the Service
  
  escSunService.addCharacteristic(switch0); // add Characteristic in the Service
  escSunService.addCharacteristic(sensorData);
  BLE.addService(escSunService);
  switch0.setValue(0);
  
  const unsigned char values[] = {
    (const unsigned char)sensor_val[0],
    (const unsigned char)sensor_val[1],
    (const unsigned char)sensor_val[2],
    (const unsigned char)sensor_val[3]
  };
  sensorData.setValue(values,4);
  BLE.advertise();
  Serial.println("Escape Sun Ble Manager Peripheral setup finish!");
}

void BleManager::setIntSensorValue(int value){

}

void BleManager::initInLoop(
    BLEDevice _central,
    BLECharacteristic sensorData
  ){
  _central = BLE.central();
  cnt++;
  cnt = cnt % MAX;
  const unsigned char values[] = {
    (const unsigned char)(sensor_val[0] + cnt),
    (const unsigned char)(sensor_val[1] + cnt),
    (const unsigned char)(sensor_val[2] + cnt),
    (const unsigned char)(sensor_val[3] + cnt)
  };
  sensorData.setValue(values,4);
}

