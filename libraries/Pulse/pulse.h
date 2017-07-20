#ifndef __PULSE_H
#define __PULSE_H

#include "Arduino.h"

typedef class PulseSensor{
public:
	bool heartbeatDetected(int delay);
}PulseSensor;

#endif