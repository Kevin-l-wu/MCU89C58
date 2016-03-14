#include <reg52.h>

#include "Common.h"
#include "Uart.h"
#include "LED.h"
#include "Digitron.h"
#include "ADConvert.h"

sbit ADRD = P3^7;
sbit ADWR = P3^6;
sbit WELA = P2^7;


void GetADCRowValue(uchar* value)
{
	WELA = 1;
	P0 = 0x7f;
	WELA = 1;

	ADWR = 1;
	ADWR = 0;
	ADWR = 1;
	
	Delay(5);
	P1 = 0xff;

	ADRD = 1;
	ADRD = 0;
	*value = P1;
	ADRD = 1;

	Delay(5);
}


void GetADCValue(uchar* value)
{
	uchar sampleNumber = 0;
	uchar rowValue = 0;
	uint sampleSum = 0;

	for(sampleNumber = 0; sampleNumber < SAMPLESUMTIMES;sampleNumber++)
	{
		GetADCRowValue(&rowValue);
		sampleSum += (uint)rowValue;
	}
	
	*value = (uchar)((sampleSum / SAMPLESUMTIMES) % 256);
}

void RunADConvert()
{
	uchar adcValue = 0;
	PrintString("Run ADConvert\n");	
	
	Timer0DelayMs(12000);
	
	while(IsTimer0Timeout())
	{
		 GetADCValue(&adcValue);
		 DisplayChar(adcValue);
		 DigitronMulripleDisplay(POSITION_0, (adcValue >> 4));
		 Delay(20);
		 DigitronMulripleDisplay(POSITION_1, (adcValue & 0x0f));
	}
	
	PrintString("Pass\n");
}
