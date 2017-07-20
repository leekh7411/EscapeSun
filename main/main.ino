#include <pulse.h>

PulseSensor pulse;
int ledPin = 13;

void setup() {
  // put your setup code here, to run once:
  pinMode(13, OUTPUT);
  Serial.begin(9600);
}

const int delayMsec = 60;

void loop()
{
  static int beatMsec = 0;
  int heartRateBPM = 0;
  
  if (pulse.heartbeatDetected(delayMsec)) {
    heartRateBPM = 60000 / beatMsec;
 
    // Print msec/beat and instantaneous heart rate in BPM
    Serial.print(beatMsec);
    Serial.print(", ");
    Serial.println(heartRateBPM);
    
    beatMsec = 0;
  }
  // Note: I assume the sleep delay is way longer than the
  // number of cycles used to run the code hence the error
  // is negligible for math.
  delay(delayMsec);
  beatMsec += delayMsec;
}
