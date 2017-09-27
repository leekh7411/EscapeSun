
#ifndef bboobboo_h
#define bboobboo_h

#include "Arduino.h"
#include "TimeCheck.h"
#define BUZZER_PIN_NUMER 8
#define BUTTON_PIN_NUMBER 13

class Bboobboo
{

private:
    int pinNum;
    bool IsBzOn;
    TimeCheck userButtonTimer;
    TimeCheck bzTimer;
    bool bzOnOffFlag;
    bool IsEmergencyButtonOn;
public:
    Bboobboo();
    void turnOnGapTime(int time_gap);
    void turnOn();
    void turnOff();
    bool checkButtonOff();
    bool userEmergencyCheck();
};


#endif // Bboobboo_h
