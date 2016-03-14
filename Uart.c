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
	/*���ò�����9600*/	
	TMOD = 0x20;
	TH1 = 0xfd;		//װ��ֵ
	TL1 = 0xfd;	
	TR1 = 1;		//������ʱ��1
	
	SCON = 0x50;

	EA = 0;			//ȫ���ж�
	ES = 0;			//�����ж�
}
int PrintChar(uchar destChar)
{
	ES = 0;			//�رմ����ж�
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
		ES = 0;	//�رմ����ж�
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
