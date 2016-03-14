#include <reg52.h>
#include <string.h>

#include "Common.h"
#include "Uart.h"

void Delay(uint ms)
{
	uint x = 0, y = 0;
	
	for(x = ms; x > 0; x--)
	{
		for(y = 110; y > 0; y--);
	}
}

void Timer0DelayMs(uint ms)
{
	gTimer0DelayMs = ms;
	PrintString("Begain Timer0 Delay\n");


	if(gTimer0DelayMs > 0)
	{
		TMOD = 0xf1 & TMOD;
	
		TH0 = (65536 - 50000) / 256;
		TL0 = (65536 - 50000) % 256;
		
		TF0 = 0;
		EA = 1;
		ET0 = 1;
		TR0 = 1;
		isTimer0Continue = 1;
	}
	else
	{
		isTimer0Continue = 0;
	}
}

int IsTimer0Timeout()
{
	if(isTimer0Continue == 1)
	{
#if DEBUGON
		PrintString("Timer Continue Delay\n");
#endif
		return 1;
	}
	else
	{
#if DEBUGON
		PrintString("Stop Timer0 Delay\n");
#endif
		return 0;
	}
}

/*Delete the last char of the string*/
void CleanString(char* destString)
{
	uint stringLength = 0;
	if(destString != NULL)
	{
		stringLength = strlen(destString);
		destString[stringLength - 2] = '\0';
	}
}


void UcharNumberToAscii(uchar destNumber, uchar* asciiCode)
{
	if(asciiCode != NULL)
	
	*asciiCode = ((destNumber / 100) + 48);		
	*(asciiCode + 1) = (((destNumber / 100) % 10) + 48);
	*(asciiCode + 2) = ((destNumber % 10) + 48);
}

/*
void UintNumberToAscii(uint destNumber, uchar* asciiCode)
{
	if(asciiCode != NULL)
	{
		*asciiCode = ((destNumber / 10000) + 48);		
		*(asciiCode + 1) = (((destNumber / 10000) % 1000) + 48);
		*(asciiCode + 2) = (((destNumber / 1000) % 100) + 48);		
		*(asciiCode + 3) = (((destNumber / 100) % 10) + 48);
		*(asciiCode + 4) = ((destNumber % 10) + 48);
	}
}
*/