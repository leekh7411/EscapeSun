
#ifndef checkHeat_h
#define checkHeat_h

#include "Bboobboo.h"
#include "tempFunction.h"
#include "InfraredTemperature.h"
#include "pulse.h"

class checkHeat
{

private:
    int BodyTempdegree;
    int Tempdegree;
    int Heartdegree;
    int bodyTemp;
    int Temp;
    int Heart;
    InfraredTemperature infraredTemp;
    temp_func m_temp;
    PulseSensor pulse;
public:
    checkHeat();
    void SendCall();
    void checkBodyTemp();
    void checkTemp();
    void checkHeart();
    void Allcheck();


};


#endif