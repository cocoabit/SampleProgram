#ifndef COCOABIT_h
#define COCOABIT_h
#include<Arduino.h>
class CocoaBit_lib
{
public:
	void pwmWrite(int pin,int value);

};
extern CocoaBit_lib CocoaBit;
#endif
