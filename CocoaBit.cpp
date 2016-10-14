#include "CocoaBit.h"

void CocoaBit_lib::pwmWrite(int pin, int value)
{	
	analogWriteFreq(4000);
	analogWriteRange(990);
	if (value > 99)value = 99;
	if (0 > value)value = 0;
	analogWrite(pin, value*10);
}
CocoaBit_lib CocoaBit;