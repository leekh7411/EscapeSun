#ifndef __STEPDETECTION_H
#define __STEPDETECTION_H
#include "BleManager.h"
#include "CurieIMU.h"

typedef class StepDetection{
public:
	static boolean iammove;
	static boolean IsStepUpdate;
	boolean stepEventsEnabeled;   // whether you're polling or using events
	static long lastStepCount;              // step count on previous polling check
	StepDetection();
	void init();
	static void updateStepCount();
	static void eventCallbacka(void);
	static void movement();
	inline int getLastStepCount(){return (int)lastStepCount;}
	static boolean getStepUpdate();
	//static inline boolean getIsStepCountChanged(){return IsStepCountChanged;}
	//static inline void resetIsStepCountChanged(){IsStepCountChanged = false;}
}StepDetection;

#endif