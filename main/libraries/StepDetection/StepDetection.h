#ifndef __STEPDETECTION_H
#define __STEPDETECTION_H

#include "CurieIMU.h"

typedef class StepDetection{
public:
	boolean stepEventsEnabeled;   // whether you're polling or using events
	static long lastStepCount;              // step count on previous polling check
	StepDetection();
	void init();
	static void updateStepCount();
	static void eventCallbacka(void);
	void movement();

}StepDetection;

#endif