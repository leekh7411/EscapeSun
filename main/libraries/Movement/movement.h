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

extern bool isZeroMotion;

#endif