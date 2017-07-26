#include "movement.h"

bool isZeroMotion = false;

static void eventCallback();

float convertRawAcceleration(int raw){
	return (raw * 2.0) / 32768.0;
}

void Movement::init(){
	/* Initialise the IMU */
  	CurieIMU.begin();
  	CurieIMU.attachInterrupt(eventCallback);

  /* Enable Zero Motion Detection */
  	CurieIMU.setDetectionThreshold(CURIE_IMU_ZERO_MOTION, 50);  // 50mg
  	CurieIMU.setDetectionDuration(CURIE_IMU_ZERO_MOTION, 2);    // 2s
  	CurieIMU.interrupts(CURIE_IMU_ZERO_MOTION);

  /* Enable Motion Detection */
  	CurieIMU.setDetectionThreshold(CURIE_IMU_MOTION, 20);      // 20mg
  	CurieIMU.setDetectionDuration(CURIE_IMU_MOTION, 10);       // trigger times of consecutive slope data points
  	CurieIMU.interrupts(CURIE_IMU_MOTION);
}

void Movement::getAcc(){
	CurieIMU.readAccelerometer(axRaw, ayRaw, azRaw);

	ax = convertRawAcceleration(axRaw);
	ay = convertRawAcceleration(ayRaw);
	az = convertRawAcceleration(azRaw);

	Serial.print("x, y, z : ");
	Serial.print(ax);
	Serial.print("\t");
	Serial.print(ay);
	Serial.print("\t");
	Serial.print(az);
	Serial.println();
}

static void eventCallback(void){
	if(CurieIMU.getInterruptStatus(CURIE_IMU_ZERO_MOTION)){
	  	Serial.println("zero motion detected...");
		isZeroMotion = true;
	}
	if(CurieIMU.getInterruptStatus(CURIE_IMU_MOTION)){
		Serial.println("motion detected!");
		isZeroMotion = false;
	}
}