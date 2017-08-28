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
  TEMPERATURE = 0;
  BODYHEAT = 1;
  HEARTRATE = 2;
  HUMIDITY = 3;
  for(int i = 0 ; i < 3 ; i++)sensor_val[i] = 255;
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
  IsDataChanged = false;
  Serial.println("Escape Sun Ble Manager Peripheral setup finish!");
}

void BleManager::setIntSensorValue(int index, int value){
  // INDEX
  // 0 : Temp
  // 1 : Body temp
  // 2 : Heart
  // 3 : Humidity
  if(index >= 0 && index <= 3){
    sensor_val[index] = value;
    IsDataChanged = true;
  }
}

void BleManager::initInLoop(
    BLEDevice _central,
    BLECharacteristic sensorData
  ){
  if(IsDataChanged){
    IsDataChanged = false;
    _central = BLE.central();
    const unsigned char values[] = {
      (const unsigned char)(sensor_val[0]),
      (const unsigned char)(sensor_val[1]),
      (const unsigned char)(sensor_val[2]),
      (const unsigned char)(sensor_val[3])
    };
    sensorData.setValue(values,4);
    Serial.println("---------------> Sensor Data Updated!"); 
  }
  
}

