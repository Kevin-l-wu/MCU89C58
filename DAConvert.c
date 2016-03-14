#include <reg52.h>

#include "Common.h"
#include "Uart.h"
#include "DAConvert.h"


sbit DACS = P3^2;
sbit DAWR = P3^6;
sbit WELA = P2^7;
sbit DULA = P2^6;


void PreSetDAChip()
{
	DACS = 0;
	DAWR = 0;
	DULA = 0;
	WELA = 0;
}


void SendDAConvertValue(uchar value)
{	
	P0 = value;
}

void RunDAConvert()
{
	uchar dacValue = 0;
	
	PrintString("Run DAConvert\n");	
	PreSetDAChip();

	Timer0DelayMs(12000);
	
	while(IsTimer0Timeout())
	{
		for(dacValue = 0; dacValue < 255; dacValue++)
		{	 
			SendDAConvertValue(dacValue);
			Delay(20);
		}
	}
	
	PrintString("Pass\n");
}
