#include <reg52.h>


#include "Common.h"
#include "Uart.h"
#include "LED.h"
#include "Ds18b20.h"

sbit DQ = P2^2;


void DelayUs(uint numberUs)
{
	while(numberUs--);
}

void SingleWireInit()
{
	uchar n;
	
	DQ = 1;
	DelayUs(8);
	DQ = 0;
	DelayUs(80);
	DQ = 1;
	DelayUs(8);
	n = DQ;
	
	DelayUs(4);
}

void SingleWireWriteByte(uchar writeData)
{
	uchar i;
	
	for(i = 0; i < 8; i++)
	{
		DQ = 0;
		DQ = writeData & 0x01;
		DelayUs(4);
		DQ = 1;
		writeData >>= 1;
	}
	
	DelayUs(4);
}

uchar SingleWireReadByte()
{
	uchar i, value;
	
	for(i = 0; i < 8; i++)
	{
		DQ = 0;
		value >>= 1;
		DQ = 1;
		
		if(DQ)
		{
			value |= 0x80;
		}
		
		DelayUs(4);
	}
	
	return value;
}

int ReadTemperature(uchar* temperatrue)
{
	uchar a, b;
	
	SingleWireInit();
	SingleWireWriteByte(0xcc);  //跳过ROM
	SingleWireWriteByte(0x44);  //启动温度测量
	DelayUs(300);

	SingleWireInit();
	SingleWireWriteByte(0xcc);
	SingleWireWriteByte(0xbe);

	a = SingleWireReadByte();
	b = SingleWireReadByte();


	b <<= 4;
	b += (a & (0xf0))>>4;

	*temperatrue = b;
	
	return 0;
}

void RunDs18b20Test()
{
	uchar temperature = 0;

	PrintString("\n---------Ds18b20 Test---------\n");
	
	Timer0DelayMs(12000);
	
	while(IsTimer0Timeout())
	{
		ReadTemperature(&temperature);
		DisplayChar(temperature);

	}
	DisplayChar(0);
	PrintString("Pass\n");
}
