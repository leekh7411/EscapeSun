
#ifndef checkHeat_h
#define checkHeat_h

#include "Bboobboo.h"
#include "tempFunction.h"
#include "InfraredTemperature.h"
#include "pulse.h"

class checkHeat
{

private:
    long currentMillis;
    long previousMillis;
    int boo;
    int BodyTempdegree;
    int Tempdegree;
    int Heartdegree;
    int bodyTemp;
    int Temp;
    int Heart;
    Bboobboo buzzer;
    InfraredTemperature infraredTemp;
    temp_func m_temp;
    PulseSensor pulse;
public:
    checkHeat();
    int SendCall();
    void checkBodyTemp();
    void checkTemp();
    void checkHeart();
    void Allcheck();
    void deBoo();


};


#endif