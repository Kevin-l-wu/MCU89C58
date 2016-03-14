#include <stdio.h>
#include <string.h>

#include "Common.h"
#include "Uart.h"
#include "SingleChip.h"
#include "LED.h"
#include "FengMing.h"
#include "Digitron.h"
#include "Ds18b20.h"
#include "ADConvert.h"
#include "DAConvert.h"
#include "ADConvert.h"
#include "At24c02.h"
#include "JGD1602.h"

#include "Message.h"
#include "Error.h"
#include "Framework.h"

static void PrintHelp();

COMMANDSLIST Commondlist[] = {
	
	{"ver", 		"Print the diags version", 	MessageEventPrintVersion, 	PrintVersion	},
	{"sn", 			"Print the DUT SN", 		MessageEventPrintSN, 		PrintSN			},
	{"help", 		"Print help message", 		MessageEventPrintHelp, 		PrintHelp		},
	{"led", 		"Led Test", 				MessageEventLedTest, 		RunLEDTest		},
	{"fengming", 	"Feng Ming Test", 			MessageEventFengMingTest, 	RunFMTest		},
	{"digitron", 	"Digitron Test", 			MessageEventDigitronTest, 	RunDigitronTest	},
	{"ds18b20", 	"Ds18b20 Test", 			MessageEventDs18b20Test, 	RunDs18b20Test	},
	{"adconvert", 	"ADConvert Test", 			MessageEventADConvertTest, 	RunADConvert	},
	{"daconvert", 	"DAConvert Test", 			MessageEventDAConvertTest, 	RunDAConvert	},
	{"at24c02", 	"At24c02 Test", 			MessageEventAt24c02Test, 	RunAt24c02Test	},
	{"jdg1602", 	"JDG1602 Test", 			MessageEventJDG1602Test, 	RunJDG1602Test	}
};

COMMANDSLIST commandList[COMMANDLISTLENGTH];
SoftArray softArrayTemp;

static void PrintHelp()
{
	uint i = 0;
	PrintString("\nPrint the info of the commonds\n\n");
	
	for(i = 0; i < sizeof(Commondlist)/sizeof(Commondlist[0]); i++)
	{
		PrintString(Commondlist[i].cmd);
		PrintString(" : ");
		PrintString(Commondlist[i].info);
		PrintString("\n");
	}
}

static MCUSTATUS InsertCommondItemToCommondList(SoftArray** gCommondSoftArray, COMMANDSLIST* commondItem)
{
	MCUSTATUS mcuStatusRet = McuStatusSuccess;
	
#if DEBUGON
	PrintString("Insert Commond Item to CommondList\n");
#endif
	if(gCommondSoftArray != NULL && commondItem != NULL)
	{
		(*gCommondSoftArray)->date[(*gCommondSoftArray)->actuaLength].cmd = commondItem->cmd;
		(*gCommondSoftArray)->date[(*gCommondSoftArray)->actuaLength].info = commondItem->info;
		(*gCommondSoftArray)->date[(*gCommondSoftArray)->actuaLength].event = commondItem->event;
		(*gCommondSoftArray)->date[(*gCommondSoftArray)->actuaLength].func = commondItem->func;
		((*gCommondSoftArray)->actuaLength)++;
#if DEBUGON	
		PrintString("Insert One Commond Tiem Success\n");
#endif
	}
	else
	{
		mcuStatusRet = McuStatusInvalidParameter;
	}

	return mcuStatusRet;
}

static MCUSTATUS CommondItemInstall(SoftArray** gCommondSoftArray, COMMANDSLIST* commondItem)
{
	MCUSTATUS mcuStatusRet = McuStatusSuccess;

	if(gCommondSoftArray != NULL && commondItem != NULL)
	{
#if DEBUGON		
		PrintString("Commond Install\n");
#endif
		if((*gCommondSoftArray)->actuaLength < (*gCommondSoftArray)->capacity)
		{
			InsertCommondItemToCommondList(gCommondSoftArray, commondItem);
		}
		else
		{
			PrintString("The commond list if full, please rejust the capacity of the commond list\n");
			mcuStatusRet = McuStatusMemeryShortage;
		}
#if DEBUGON	
		PrintString("Commond Install Complete\n");
#endif
	}
	else
	{
		mcuStatusRet = McuStatusInvalidParameter;
	}

	return mcuStatusRet;
}


MCUSTATUS CreatCommondSoftArray(SoftArray** gCommondSoftArray)
{
	MCUSTATUS mcuStatusRet = McuStatusSuccess;

	if(gCommondSoftArray != NULL)
	{
#if DEBUGON	 
		PrintString("Creat the SoftArray\n");		
#endif
		softArrayTemp.capacity = COMMANDLISTLENGTH;
		softArrayTemp.actuaLength = 0;
		softArrayTemp.date = commandList;
		
		*gCommondSoftArray = &softArrayTemp;	
	}
	else
	{
		mcuStatusRet = McuStatusInvalidParameter;
	}

	return mcuStatusRet;
}

MCUSTATUS CommondInsall(SoftArray** gCommondSoftArray)
{
	MCUSTATUS mcuStatusRet = McuStatusSuccess;
	unsigned i = 0;

	if(gCommondSoftArray != NULL)
	{
#if DEBUGON
		PrintString("Test Commond Install\n");
#endif	
		for(i = 0; i < sizeof(Commondlist)/sizeof(Commondlist[0]); i++)
		{
			CommondItemInstall(gCommondSoftArray, &Commondlist[i]);
		}
#if DEBUGON
		PrintString("Print Commond Install Complete\n");
#endif
	}
	else
	{
		mcuStatusRet = McuStatusInvalidParameter;
	}

	return mcuStatusRet;
}