#ifndef __BLEMANAGER_H
#define __BLEMANAGER_H

#include "Arduino.h"
#include <CurieBLE.h>

class BleManager{
private:
	int MAX,cnt;
	int sensor_val[4]; // Datas have to set range in 0 ~ 256 
public:
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
	void setIntSensorValue(int value); // set the value in the integer characteristic

};
 

#endif