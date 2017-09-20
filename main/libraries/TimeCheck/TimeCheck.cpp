#include "TimeCheck.h"  
#include "arduino.h"
TimeCheck::TimeCheck(){
}

/*
2017-07-20
심박 수 측정
analog pin 0 사용
*/
void TimeCheck::init(){
  prev_time = 0;
}

long TimeCheck::Secondtime(){
  current_time = millis();
  return (current_time-prev_time)/1000;
}
long TimeCheck::Minutetime(){
  current_time = millis();
  return (current_time-prev_time)/60000;
}
long TimeCheck::ModulerSecondtime(){
  current_time = millis();
  return ((current_time-prev_time)/1000)%60;
}
void TimeCheck::resetTime(){
	prev_time = millis();
}

