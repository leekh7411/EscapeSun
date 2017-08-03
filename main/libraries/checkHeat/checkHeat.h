
#ifndef checkHeat_h
#define checkHeat_h

#include "Bboobboo.h"
#include "tempFunction.h"
#include "InfraredTemperature.h"
#include "pulse.h"
#include "RunningMedian.h"

#define MEDIAN_SIZE		3

class checkHeat
{
private:
    long currentMillis;
    long previousMillis;
    int boo;
    int bodyTempDegree;
    int tempDegree;
    int heartDegree;
    float bodyTemp;
    int temp;
    int heart;
	int count;
    Bboobboo buzzer;
    InfraredTemperature infraredTemp;
    temp_func mTemp;
    PulseSensor pulse;
	RunningMedian median[MEDIAN_SIZE] = {RunningMedian(MEDIAN_MAX_SIZE), RunningMedian(MEDIAN_MAX_SIZE), RunningMedian(MEDIAN_MAX_SIZE)};
	
public:
    checkHeat();
    int sendCall(int zeroMotion);
    void checkBodyTemp(float);
    void checkTemp(int);
    void checkHeart(int);
    void allcheck();
    void deBoo();
	void checkMedian();
};


#endif