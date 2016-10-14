#include "CocoaBit.h"

void CocoaBit_lib::pwmWrite(int pin, int value)
{
	analogWriteFreq(4000);

	analogWrite(pin, value*10);
}
CocoaBit_lib CocoaBit;