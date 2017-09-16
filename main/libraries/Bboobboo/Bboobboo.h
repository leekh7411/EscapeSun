
#ifndef bboobboo_h
#define bboobboo_h

#include "Arduino.h"

#define BUZZER_PIN_NUMER 8


class Bboobboo
{

private:
    int pinNum;

public:
    Bboobboo();

    void turnOn();
    void turnOff();

};


#endif // Bboobboo_h
