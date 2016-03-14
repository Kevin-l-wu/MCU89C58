#include <stdio.h>
#include <string.h>

#include "Message.h"
#include "SoftArray.h"
#include "Framework.h"
#include "SingleChip.h"

#define DEFAULTCOMMONDARRAYSIZE 8

SoftArray* gCommondSoftArray = NULL;

static void HandleMessage()
{
	printf("Handle Message\n");
	MESSAGE message = {MessageEventNone, MessageEventPrintNone};
	unsigned i = 0;
	
	GetMessage(&message);
	
	if(message.type == MessageEventPrint)
	{
		for(i = 0; i < gCommondSoftArray->actuaLength; i++)
		{
			if(gCommondSoftArray->data[i].event == message.event)
			{
				gCommondSoftArray->data[i].func();
				break;
			}
		}
		
		if(i == gCommondSoftArray->actuaLength) 			//No event match
		{
			printf("Invalid Event\n");
		}
	}

}

int main()
{	
	char command[10] = {'\0'};
	MESSAGE message;
	MessageInit();
	
	CreatCommondSoftArray(&gCommondSoftArray, DEFAULTCOMMONDARRAYSIZE);
	PrintCommondInsall(&gCommondSoftArray);
	
		
	unsigned i = 0, j = 0;
	
	for(i = 0; i < 5; i++)
	{
		printf(":-)");
		scanf("%s", command);
		printf("Command: %s\n", command);
		
		for(j = 0; j < gCommondSoftArray->actuaLength; j++)
		{	
			if(strcmp(gCommondSoftArray->data[j].cmd, command) == 0)
			{	
				message.type = MessageEventPrint;
				message.event = gCommondSoftArray->data[j].event;
				SendMessage(&message);
			
				break;
			}
		}
		
		if(j == gCommondSoftArray->actuaLength) 			//No commond match
		{
			printf("Invalid input\n");
		}
		
		memset(command, '\0', sizeof(command));
		HandleMessage();
	}
	
	printf("gCommondSoftArray = %p\n", gCommondSoftArray);
	DestroyCommondSoftArray(&gCommondSoftArray);
	
	return 0;
}



