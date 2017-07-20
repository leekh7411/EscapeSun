#include "pulse.h"

bool PulseSensor::heartbeatDetected(int delay){
  static int maxValue = 0;
  static bool isPeak = false;
  int rawValue;
  bool result = false;
    
  rawValue = analogRead(0);
  // Separated because analogRead() may not return an int
  rawValue *= (1000/delay);
//  HBDEBUG(Serial.print(isPeak); Serial.print("p, "));
//  HBDEBUG(Serial.print(rawValue); Serial.print("r, "));
//  HBDEBUG(Serial.print(maxValue); Serial.print("m, "));
 
  // If sensor shifts, then max is out of whack.
  // Just reset max to a new baseline.
  if (rawValue * 4L < maxValue) {
    maxValue = rawValue * 0.8;
    // HBDEBUG(Serial.print("RESET, "));
  }
  
  // Detect new peak
  if (rawValue > maxValue - (1000/delay)) {
    // Only change peak if we find a higher one.
    if (rawValue > maxValue) {
      maxValue = rawValue;
    }
    // Only return true once per peak.
    if (isPeak == false) {
      result = true;
      // Serial.print(result);
      // Serial.print(",  *");
    }
    isPeak = true;
  } else if (rawValue < maxValue - (3000/delay)) {
    isPeak = false;
    // Decay max value to adjust to sensor shifting
    // Note that it may take a few seconds to re-detect
    // the signal when sensor is pushed on meatier part
    // of the finger. Another way would be to track how
    // long since last beat, and if over 1sec, reset
    // maxValue, or to use derivatives to remove DC bias.
    maxValue-=(1000/delay);
 }
//  HBDEBUG(Serial.print("\n"));
  return result;
}