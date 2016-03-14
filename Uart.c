#include <reg52.h>
#include <string.h>

#include "Common.h"
#include "Uart.h"
/*
#include "LED.h"
#include "Digitron.h"
*/


void UartInit()
{
	/*设置波特率9600*/	
	TMOD = 0x20;
	TH1 = 0xfd;		//装初值
	TL1 = 0xfd;	
	TR1 = 1;		//启动定时器1
	
	SCON = 0x50;

	EA = 0;			//全局中断
	ES = 0;			//串行中断
}
int PrintChar(uchar destChar)
{
	ES = 0;			//关闭串行中断
	TI = 0;
	RI = 0;

	SBUF = destChar;
	
	while(!TI);
	Delay(1);

	TI = 0;
	RI = 0;

	return 0;
}


int PrintString(const uchar* destString)
{
	unsigned int stringLength = 0;
	const char* destStringTemp = destString;
	unsigned int i = 0;
	
	if(destString != NULL)
	{
		stringLength = strlen(destString);

		for(i = 0; i < stringLength; i++)
		{
			PrintChar(*destStringTemp);
			destStringTemp++;
		}
	}

	return 0;
}


int ReceiveChar(uchar* destChar)
{
	if(destChar != NULL)
	{
		ES = 0;	//关闭串行中断
		RI = 0;
		TI = 0;
		EA = 0;

		while(!RI);
		
		*destChar = SBUF;

		RI = 0;
	}

	return 0;
}



int ReceiverString(uchar* destString, unsigned int length)
{
	unsigned int i = 0;
	char* destStringTemp = destString;

	for(i = 0; i < length; i++)
	{
		ReceiveChar(destStringTemp);
		if(*destStringTemp == 0x0a)
		{
			break;
		}
		destStringTemp++;
	}
	
	return 0;
}
