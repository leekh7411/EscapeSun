#include "pulse.h"

PulseSensor::PulseSensor(){
  oldHeartRate = 0;
}

/*
2017-07-20
심박 수 측정
analog pin 0 사용
*/
int PulseSensor::updateHeartRate(){
  /* Read the current voltage level on the A0 analog input pin.
     This is used here to simulate the heart rate's measurement.
  */
  int heartRateMeasurement = analogRead(0);
  int heartRate = map(heartRateMeasurement, 0, 1023, 0, 100);
  if (heartRate != oldHeartRate) {      // if the heart rate has changed
    // Serial.print("Heart Rate is now: "); // print it
    // Serial.println(heartRate);
    oldHeartRate = heartRate;           // save the level for next comparison
    return heartRate;
  }
  return -1;
}

int PulseSensor::getHeartRate(){
  return oldHeartRate;
}