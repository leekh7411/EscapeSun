#ifndef __TIMECHECK_H
#define __TIMECHECK_H

typedef class TimeCheck{
public:
	unsigned long prev_time;
	unsigned long current_time ;
	TimeCheck();
	void init();
	long Secondtime();
	long Minutetime();
	void resetTime();
	long ModulerSecondtime();

}TimeCheck;

#endif