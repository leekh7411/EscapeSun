
#ifndef bboobboo_h
#define bboobboo_h

#include "Arduino.h"

#define BUZZER_PIN_NUMER 8
#define BUTTON_PIN_NUMBER 13

class Bboobboo
{

private:
    int pinNum;
    bool IsBzOn;
public:
    Bboobboo();

    void turnOn();
    void turnOff();
    bool checkButtonOff();

};


#endif // Bboobboo_h
