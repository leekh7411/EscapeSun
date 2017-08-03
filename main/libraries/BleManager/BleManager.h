#ifndef __BLEMANAGER_H
#define __BLEMANAGER_H

#include "Arduino.h"
#include <CurieBLE.h>

class BleManager{
private:
// Main Service UUID
BLEService* escSunService;
// Char characteristic  
BLECharCharacteristic* switchCharacteristic;
// Integer characteristic
BLEIntCharacteristic* sensorCharacteristic;
BLEDevice central;
public:
	BleManager(); // This have to initialize in Setup()!
	void initInLoop(); 
	void setIntSensorValue(int value); // set the value in the integer characteristic

};
 

#endif