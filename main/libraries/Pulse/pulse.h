#ifndef __PULSE_H
#define __PULSE_H

#include "Arduino.h"

typedef class PulseSensor{
public:
	int oldHeartRate;

	PulseSensor();
	int getHeartRate();
	int updateHeartRate();
}PulseSensor;

#endif