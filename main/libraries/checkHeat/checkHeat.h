#ifndef checkHeat_h
#define checkHeat_h
#include "Bboobboo.h"
#include "tempFunction.h"
#include "InfraredTemperature.h"
#include "pulse.h"
#include "RunningMedian.h"
#include "BleManager.h"
#include "TimeCheck.h"
#include "StepDetection.h"
#define TEMPERATURE_STACK_SIZE 3
#define BODY_HEAT_STACK_SIZE 4
#define HEART_RATE_STACK_SIZE 7
#define HUMIDITY_STACK_SIZE 3
#define MEDIAN_SIZE		4
#define SENSOR_CHECK_TIME 10
class checkHeat
{
private:
    BleManager *manager;
    long currentMillis;
    long previousMillis;
    int boo;
    int bodyTempDegree;
    int tempDegree;
    int heartDegree;
    int humidityDegree;
    float bodyTemp;

    float humidity;
    int temp;
    int heart;
	int count;
    Bboobboo buzzer;
    InfraredTemperature infraredTemp;
    temp_func mTemp;
    PulseSensor pulse;
	RunningMedian median[MEDIAN_SIZE] = {RunningMedian(MEDIAN_MAX_SIZE), RunningMedian(MEDIAN_MAX_SIZE), RunningMedian(MEDIAN_MAX_SIZE), RunningMedian(MEDIAN_MAX_SIZE)};
	
    // Temperature Score Lable
    int Temperature_Score_Stack[TEMPERATURE_STACK_SIZE] = {0,0,0};
    TimeCheck Temperature_Time;
    int Temperature_Score;

    // BodyHeat Score Lable
    int BodyHeat_Score_Stack[BODY_HEAT_STACK_SIZE] = {0,0,0,0};
    TimeCheck BodyHeat_Time;
    int BodyHeat_Score;

    // HeartBeat Score Lable
    int HeartRate_Score_Stack[HEART_RATE_STACK_SIZE] = {0,0,0,0,0,0,0};
    TimeCheck HeartRate_Time;
    int HeartRate_Score;

    // Humidity Score Lable
    int Humidity_Score_Stack[HUMIDITY_STACK_SIZE] = {0,0,0};
    TimeCheck Humidity_Time;
    int Humidity_Score;

    TimeCheck Movement_Time;
    int Movement_Score;
public:
    void init(BleManager *Manager);
    checkHeat();
    void sendCall(int zeroMotion);
    void checkBodyTemp(float);
    void checkTemp(int);
    void checkHeart(int);
    void checkHumidity(int);
    int checkMovement(StepDetection stepdetect);
    void allcheck();
    void deBoo();
	void checkMedian();
    void isLongPress();
    // Temperature Score Functions
    void SetCurrentTemperatureScore();
    void TemperatureScoreStackPop(int idx);
    bool heatCramps(); //열경련 and 열실신 
    bool heatExhaustion();
    bool heatStroke();
    void heatAllcheck(StepDetection stepdetect);
};


#endif