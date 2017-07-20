
#ifndef Bboobboo_h
#define Bboobboo_h

#include "Arduino.h"

#define BUZZER_PIN_NUMER 7


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
