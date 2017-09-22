#include "BleManager.h"
BleManager::BleManager(){
  // Default Constructor
}
BleManager::BleManager(
    BLEService escSunService,
    BLECharCharacteristic switch0,
    BLECharacteristic sensorData,
    BLEIntCharacteristic distance,
    BLEIntCharacteristic emergency,
    BLEIntCharacteristic limit_distance,
    BLEIntCharacteristic limit_heart_rate,
    BLEIntCharacteristic limit_humidity
  ){
  MAX = 10; cnt = 0; 
  TEMPERATURE = 0;
  BODYHEAT = 1;
  HEARTRATE = 2;
  HUMIDITY = 3;
  for(int i = 0 ; i < SENSOR_VAL_NUM ; i++)sensor_val[i] = 0;
  BLE.begin(); // BLE object init in 'CurieBLE.h' library
  BLE.setLocalName("SUN"); // Ble's Tag name
  BLE.setAdvertisedService(escSunService); // set the Service
  escSunService.addCharacteristic(switch0); // add Characteristic in the Service
  escSunService.addCharacteristic(sensorData);
  escSunService.addCharacteristic(distance);
  escSunService.addCharacteristic(emergency);
  escSunService.addCharacteristic(limit_heart_rate);
  escSunService.addCharacteristic(limit_humidity);
  escSunService.addCharacteristic(limit_distance);
  BLE.addService(escSunService);
  switch0.setValue(0);
  distance.setValue(0);
  emergency.setValue(0);
  limit_distance.setValue(0);
  limit_heart_rate.setValue(0);
  limit_humidity.setValue(0);
  const unsigned char values[] = {
    (const unsigned char)sensor_val[0],
    (const unsigned char)sensor_val[1],
    (const unsigned char)sensor_val[2],
    (const unsigned char)sensor_val[3]
  };
  sensorData.setValue(values,SENSOR_VAL_NUM);
  BLE.advertise();
  IsDataChanged = false;
  mode = 0;
  limit_distance_value = 0;
  limit_heart_rate_value = 0;
  limit_humidity_value = 0;
  distance_val = 0;
  IsDataChanged = false;
  IsEmergencyChanged = false;
  Serial.println("Escape Sun Ble Manager Peripheral setup finish!");
}

void BleManager::setIntSensorValue(int index, int value){
  // INDEX
  // 0 : Temp
  // 1 : Body temp
  // 2 : Heart
  // 3 : Humidity
  if(index >= 0 && index < SENSOR_VAL_NUM){
    sensor_val[index] = value;
    IsDataChanged = true;
  }
}

void BleManager::initInLoop(
    BLEDevice _central,
    BLECharacteristic sensorData,
    BLEIntCharacteristic distance,
    BLECharCharacteristic mode_switch,
    BLEIntCharacteristic emergency,
    BLEIntCharacteristic limit_distance,
    BLEIntCharacteristic limit_heart_rate,
    BLEIntCharacteristic limit_humidity
  ){

  // this is a testing module ++++++++++++++++++++++++++++++++++++++++++++++++++
  if(sensorData.written()){
    /*
    Serial.println("Read Sensor BLE value");
    const byte* data = sensorData.value(); 
    Serial.println((int)data[0]);
    Serial.println((int)data[1]);
    Serial.println((int)data[2]);
    Serial.println((int)data[3]);
    */
    Serial.println("----> Debugging --> Sensor written!");
    const unsigned char byte* data = sensorData.value();
    for(int i = 0 ; i < SENSOR_VAL_NUM ; i++){
      sensor_val[i] = (const unsigned char)data[i];
      IsDataChanged = true;
    }
  }// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

  if(IsDataChanged){
    IsDataChanged = false;
    _central = BLE.central();
    const unsigned char values[] = {
      (const unsigned char)(sensor_val[0]),
      (const unsigned char)(sensor_val[1]),
      (const unsigned char)(sensor_val[2]),
      (const unsigned char)(sensor_val[3])
    };
    sensorData.setValue(values,SENSOR_VAL_NUM);
    Serial.println("---------------> Sensor Data Updated!");

  }


  if(IsEmergencyChanged){
    IsEmergencyChanged = false;
    emergency.setValue(EMERGENCY_MODE);
  }

  if(IsDistanceChanged){
    IsDistanceChanged = false;
    distance.setValue(distance_val);
  }

  if(mode_switch.written()){
    mode = (int)mode_switch.value();
    if(mode < 0 || mode > 15){
      // Error?
    }else{
      int temp = mode;
      int idx = 0;
      while(idx <= 3){
        function_switch[idx] = temp % 2;
        idx++;
        temp = (int)(temp/2);
      }
    }
  }

  if(limit_distance.written()){
    limit_distance_value = limit_distance.value();
    //Serial.print("distance_value changed : ");
    //Serial.println(limit_distance_value);
  }
  if(limit_heart_rate.written()){
    limit_heart_rate_value = limit_heart_rate.value();
    //Serial.print("heart_rate_value changed : ");
    //Serial.println(limit_heart_rate_value);
  }
  if(limit_humidity.written()){
    limit_humidity_value = limit_humidity.value();
    //Serial.print("humidity_value changed : ");
    //Serial.println(limit_humidity_value);
  }

}

