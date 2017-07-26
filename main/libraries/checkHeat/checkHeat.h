
#ifndef checkHeat_h
#define checkHeat_h

class checkHeat
{

private:
    int bodyTemp;
    int Temp;
    int Heart;

public:
    checkHeat();
    void SendCall();
    void checkBodyTemp();
    void checkTemp();
    void checkHeart();


};


#endif