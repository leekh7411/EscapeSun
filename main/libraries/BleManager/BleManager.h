#ifndef __BLEMANAGER_H
#define __BLEMANAGER_H

#include "Arduino.h"
#include <CurieBLE.h>

class BleManager{
private:
	int MAX,cnt;
	int sensor_val[4]; // Datas have to set range in 0 ~ 256 

public:
	int TEMPERATURE,BODYHEAT,HEARTRATE,HUMIDITY;
	BleManager();
	BleManager(
	  BLEService escSunService,
	   BLECharCharacteristic switch0,
    	  BLECharacteristic sensorData
	); // This have to initialize in Setup()!
	void initInLoop(
	    BLEDevice _central,
    	    BLECharacteristic sensorData
  	); 
	void setIntSensorValue(int index, int value); // set the value in the integer characteristic
};
#endif