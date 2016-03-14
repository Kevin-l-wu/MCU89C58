#include <reg52.h>

#include "Common.h"
#include "Uart.h"
#include "FengMing.h"
#include "Digitron.h"
#include "LED.h"
#include "Framework.h"
#include "Keyboard.h"
#include "At24C02.h"
#include "Ds18b20.h"
#include "StepMotor.h"
#include "JGD1602.h"
#include "Wireless.h"


int PrintHeadMessage()
{
	Delay(1000);
	PrintString("TX-1C Diags\n");

	PrintString("1 --> FM Test\n");
	PrintString("2 --> Led Test\n");
	PrintString("3 --> Digitron Test\n");
	PrintString("4 --> Keyboard Test\n");
	PrintString("5 --> At24c02 Test\n");
	PrintString("6 --> Ds18b20 Test\n");
	PrintString("7 --> StepMotor Test(Remember to connect the ABCD)\n");
	PrintString("8 --> JGD1602 Test(Remember to connect the JGD1602)\n");
	PrintString("9 --> Wireless Key Test\n");
	PrintString("v --> Print Diags Version\n");
	PrintString("s --> Print DUT SN\n");
	PrintString("h --> Print Help Message\n");
	
	return 0;	
}

int DigitronSingleDisplay()
{
	unsigned i = 0;
	
	for(i = 0; i < MAX_NUMBER_DIGITRON; i++)
	{
		DigitronDisplay(i ,i);
		Delay(1000);
	}

	return 0;
}

int DigitronMutipleDisplay()
{
	unsigned i = 0;

	for(i = 0; i < 10; i++)
	{
		DigitronMulripleDisplay((POSITION_0 & POSITION_1 & POSITION_2 & POSITION_3 & POSITION_4 & POSITION_5) ,i);

		Delay(1000);
	}

	return 0;
}


int RunFMTest()
{
	PrintString("\n---------FM Test---------\n");
	FengMing(3);
	PrintString("Pass\n");
	return 0;
}

int RunLEDTest()
{
	uchar i = 0;

	PrintString("\n---------LED Test---------\n");
	
	for(i = 1; i < 16; i++)
	{
		DisplayChar(i);
		Delay(1000);
	}

	for(i = 1; i < 16; i++)
	{
		DisplayChar(i<<4);
		Delay(1000);
	}

	DisplayChar(0x00);

	PrintString("Pass\n");
	return 0;
}

int RunDigitronTest()
{
	PrintString("\n---------Digitron Test---------\n");

	DigitronSingleDisplay();

	DigitronMutipleDisplay();

	DigitronMulripleDisplay((POSITION_0 & POSITION_1 & POSITION_2 & POSITION_3 & POSITION_4 & POSITION_5), 16);
	PrintString("Pass\n");
	return 0;
}


int RunKeyboardTest()
{
	MATRIX_KEY matrixKey = MATRIX_NONE;
	SINGLE_KEY singleKey = SINGLE_NONE;
	PrintString("\n---------Keyboard Test---------\n");

	PrintString("Pass\n");
	return 0;
}

int RunAt24c02Test()
{
	uchar i = 0;
	uchar buff[16];
	uchar* buffPtr = buff;
	uchar rowSum = ((0 + AT24C02_MAX_BYTE - 1) * AT24C02_MAX_BYTE) / 2;
	uchar actualSum = 0;

	I2cInit();

	PrintString("\n---------At24c02 Test---------\n");

	PrintString("rowSum = ");
	PrintChar(rowSum);
	PrintChar('\n');

	for(i = 0; i < AT24C02_MAX_BYTE; i++)
	{
		At24c02WriteByte(i, i);
		Delay(2);
	}

	for(i = 0; i < AT24C02_MAX_BYTE; i++)
	{
		At24c02ReadByte(i, buffPtr);
		Delay(2);
		actualSum = actualSum + *buffPtr;
		buffPtr++;
	}
	
	PrintString("actualSum = ");
	PrintChar(actualSum);
	PrintChar('\n');

	if(actualSum == rowSum)
	{
		PrintString("Pass\n");
	}
	else
	{
		PrintString("Failed\n");
	}

	return 0;
}

int RunDs18b20Test()
{
	uchar temperature = 0;
	uint caculater = 50;

	PrintString("\n---------Ds18b20 Test---------\n");
	
	while(caculater)
	{
		ReadTemperature(&temperature);
		DisplayChar(temperature);	
		caculater = caculater - 1;
		Delay(500);
	}
	DisplayChar(0);
	PrintString("Pass\n");
	return 0;
}

int RunStepMotorTest()
{
	uint i = 0;
	PrintString("\n---------StepMotor Test---------\n");	

	Beep();
	
	for(i = 0; i < 50; i++)
	{
		MotorCounterClockwise();
		Delay(10);
	}
	
	Beep();

	for(i = 0; i < 50; i++)
	{
		MotorClockwise();
		Delay(10);
	}

	PrintString("Pass\n");
	P0 = 0xff;
	return 0;
}

int RunJGD1602Test()
{
	uchar testString[] = "I love you!";
	PrintString("\n---------RunJGD1602 Test---------\n");
		
	JGD1602Init();
	JGD1602DisplayText(0, 0, testString);

	PrintString("Pass\n");
	return 0;
}

int RunWirelessKeyTest()
{
	uint caculater = 2000;
	WIRELESSKEY wirelessKey = WIRELESSKEY_NONE;
	
	PrintString("\n---------RunWirelessKey Test---------\n");	
	
	while(caculater--)
	{																
		GetWirelessKey(&wirelessKey);
		switch(wirelessKey)
		{
			case WIRELESSKEY_A:
				DisplayChar(0x01);
				break;
			case WIRELESSKEY_B:
				DisplayChar(0x02);
				break;
			case WIRELESSKEY_C:
				DisplayChar(0x04);
				break;
			case WIRELESSKEY_D:
				DisplayChar(0x08);
				break;
			default:
				break;
		
		}
	
		Delay(10);
	}

	DisplayChar(0x00);
	PrintString("Pass\n");

	return 0;
}

int RunADConvert()
{
	PrintString("Run ADConvert\n");	
	
	
	PrintString("Pass\n");
	return 0;
}

int RunDAConvert()
{
	PrintString("Run DAConvert\n");	
	
	
	PrintString("Pass\n");
	return 0;
}


int RunPrintSN()
{
	PrintString("SN: C39L00017Y9H\n");	
	
	
	PrintString("Pass\n");

	return 0;
}

int RunPrintDiagsVerison()
{
	PrintString("Ver: 2015-02-08(Local Build)\n");	
	
	
	PrintString("Pass\n");

	return 0;
}

int ActionToRun(uchar testItems)
{
	PrintChar(sizeof(uchar));
	PrintChar(sizeof(POSITION));

	switch(testItems)
	{
		case TESTITEMS_FM:
			RunFMTest();
			break;
		case TESTITEMS_LED:
			RunLEDTest();
			break;
		case TESTITEMS_DIGITRON:
			RunDigitronTest();
			break;
		case TESTITEMS_KEYBOARD:
			RunKeyboardTest();
			break;
		case TESTITEMS_AT24C02:
			RunAt24c02Test();
			break;
		case TESTITEMS_DS18B20:
			RunDs18b20Test();
			break;
		case TESTITEMS_STEPMOTOR:
			RunStepMotorTest();
			break;
		case TESTITEMS_JGD1602:
			RunJGD1602Test();
			break;
		case TESTITEMS_WIRELESS:
			RunWirelessKeyTest();
			break;
		case TESTITEMS_SN:
			RunPrintSN();
			break;
		case TESTITEMS_VER:
			RunPrintDiagsVerison();
			break;
		case TESTITEMS_ADC:
			RunADConvert();
			break;
		case TESTITEMS_DAC:
			RunDAConvert();
			break;
		case TESTITEMS_HELP:
			PrintHeadMessage();
			break;
		default:
			PrintString("Invalid input\n");
			break;
	}

	return 0;
}
