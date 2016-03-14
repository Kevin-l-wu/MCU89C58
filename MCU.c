#include <reg52.h>
#include <stdio.h>
#include <string.h>

#include "Common.h"
#include "Uart.h"
#include "Digitron.h"

#include "Message.h"
#include "Error.h"
#include "Framework.h"

#define COMMONDSIZE 20

/*********************** Global Variable ***********************/

char isTimer0Continue = 0;
int gTimer0DelayMs = 0;

SoftArray* gCommondSoftArray = NULL;

/***************************************************************/

static void HandleMessage()
{
	uint i = 0;	
	MESSAGE message = {MessageTypeNone, MessageEventPrintNone};
#if DEBUGON
	PrintString("Handle Message\n");
#endif		
	GetMessage(&message);
	
	if(message.type == MessageTypePrint)
	{
		for(i = 0; i < gCommondSoftArray->actuaLength; i++)
		{
			if(gCommondSoftArray->date[i].event == message.event)
			{
				gCommondSoftArray->date[i].func();
				
				break;
			}
		}
		
		if(i == gCommondSoftArray->actuaLength) 			//No event match
		{
			PrintString("Invalid Event\n");
		}
	}

#if DEBUGON
	PrintString("Handle Message Complete\n");
#endif
}

static void ModuleInit()
{	
	MessageInit();
	
	UartInit();
	DigitronInit();
}

int main()
{	
	char command[COMMONDSIZE] = {'\0'};
	uint j = 0;
	MESSAGE message;
	MCUSTATUS mcuStatus = McuStatusSuccess;

	ModuleInit();

	mcuStatus = CreatCommondSoftArray(&gCommondSoftArray);
	ErrorCheck(mcuStatus);
	CommondInsall(&gCommondSoftArray);
	ErrorCheck(mcuStatus);

	PrintString("Begain Diags Test\n");

	while(1)
	{
		PrintString("-----------------------------------------------------\n");
		PrintString(":-) ");
		ReceiverString(&command, COMMONDSIZE);
		PrintString(command);
		
		CleanString(command);
		PrintString(command);
		
		for(j = 0; j < gCommondSoftArray->actuaLength; j++)
		{	
			if(strcmp(gCommondSoftArray->date[j].cmd, command) == 0)
			{	
				message.type = MessageTypePrint;
				message.event = gCommondSoftArray->date[j].event;
				SendMessage(&message);
	
				break;
			}
		}
		
		if(j == gCommondSoftArray->actuaLength) 			//No commond match
		{
			PrintString("Invalid input\n");
		}
		
		memset(command, '\0', sizeof(command));
		HandleMessage();
	}
	
	return 0;
}

void timer0() interrupt 1
{	
	if(gTimer0DelayMs > 0) 
	{
		TH0 = (65536-50000)/256;
		TL0 = (65536-50000)%256;
		
		TF0 = 0;
		EA = 1;
		ET0 = 1;
		TR0 = 1;
		
		gTimer0DelayMs--;
		isTimer0Continue = 1;
	}
	else
	{
		isTimer0Continue = 0;
		EA = 1;
		ET0 = 1;
		TR0 = 1;
	}
}
