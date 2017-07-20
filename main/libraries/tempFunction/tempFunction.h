#ifndef tempFunction_h
#define tempFunction_h
#include "DHT11.h" 
class temp_func
{ 
public:
	float temp;
	float humi;
	DHT11 dht11 = DHT11(2);
public:
	temp_func()
	{

	}
	~temp_func()
	{
	}


public:
	void temp_est();
	float getTemp();
	float getHumi();
};

#endif