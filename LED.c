#include <reg52.h>

#include "Common.h"
#include "Uart.h"
#include "LED.h"

sbit diola = P2^5;

int DisplayChar(uchar destChar)
{
	diola = 1;
	P1 = (destChar ^ 0xff);
	diola = 0;
	
	return 0;	
}

void RunLEDTest()
{
	uchar i = 0;

	PrintString("\n---------LED Test---------\n");
	
	for(i = 1; i < 16; i++)
	{
		DisplayChar(i);
		Delay(1000);
	}

	for(i = 1; i < 16; i++)
	{
		DisplayChar(i<<4);
		Delay(1000);
	}

	DisplayChar(0x00);

	PrintString("Pass\n");
}

