#include <reg52.h>

#include "GPIO.h"

void GPIOInit()
{
	P0 = 0xff;
	P1 = 0xff;
	P2 = 0xff;
	P3 = 0xff;
}