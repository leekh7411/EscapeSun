#ifndef _MOVEMENT_H
#define _MOVEMENT_H

#include "Arduino.h"
#include "CurieIMU.h"

class Movement{
private:
	int axRaw, ayRaw, azRaw;
	float ax, ay, az;

public:
	void init();
	void getAcc();
};

// motion이 없을 때 true
extern bool isZeroMotion;

#endif