#include "CocoaBit.h"

void CocoaBit_lib::pwmWrite(int pin, int value)
{
	analogWriteFreq(4000);
	analogWriteRange(99)
	analogWrite(pin, value);
}
CocoaBit_lib CocoaBit;