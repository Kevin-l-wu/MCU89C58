#include <reg52.h>

#include "Common.h"
#include "Uart.h"
#include "FengMing.h"

sbit FENGMING = P2^3;


static void FengMing(uint times)
{	
	Timer0DelayMs(times);
	
	while(IsTimer0Timeout())
	{
		FENGMING = 0;
		Delay(500);
		
		FENGMING = 1;
		Delay(500);
	}
}

void RunFMTest()
{
	PrintString("\n---------FM Test---------\n");
	FengMing(1200);
	PrintString("Pass\n");
}

