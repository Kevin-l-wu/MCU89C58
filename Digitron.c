#include <reg52.h>

#include "Common.h"
#include "Uart.h"
#include "Digitron.h"

sbit DULA = P2^6;
sbit WELA = P2^7;

uchar code gDigitTable[] = {
	DIGIT_0, DIGIT_1, DIGIT_2, DIGIT_3,
	DIGIT_4, DIGIT_5, DIGIT_6, DIGIT_7,
	DIGIT_8, DIGIT_9, DIGIT_A, DIGIT_B,
	DIGIT_C, DIGIT_D, DIGIT_E, DIGIT_F,
	DIGIT_DARK,
};

uchar code gPositionTalbe[] = {
	POSITION_0, POSITION_1, POSITION_2, POSITION_3, POSITION_4, POSITION_5
};

void DigitronInit()
{
	DULA = 1;
	P0 = 0xff;
	DULA=0;

	WELA=1;
	P0 = 0xff;
	WELA=0;	
}


void DigitronDisplay(uchar number, uchar contentNumber)
{
	DULA = 1;
	P0 = gDigitTable[contentNumber];
	DULA=0;
	
	P0=0xff;

	WELA=1;
	P0 = gPositionTalbe[number];
	WELA=0;

	P0=0xff;
}


void DigitronMulripleDisplay(POSITION position, uchar contentNumber)
{
	DULA = 1;
	P0 = gDigitTable[contentNumber];
	DULA=0;
	
	P0=0xff;

	WELA=1;
	P0 = position;
	WELA=0;

	P0=0xff;
}

/***************************************Install Function****************************************/

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
		DigitronMulripleDisplay((POSITION)(POSITION_0 & POSITION_1 & POSITION_2 & POSITION_3 & POSITION_4 & POSITION_5) ,i);

		Delay(1000);
	}

	return 0;
}



/*
int DisplayCharValue(POSITION highFourBitPosition, POSITION lowFourBitPosition, uchar destChar)
{
	uchar highFourBit = (destChar & 0xf0) >> 4;
	uchar lowFourBit = destChar & 0x0f;
	
	DigitronMulripleDisplay(highFourBitPosition, highFourBit);
	Delay(5);
	DigitronMulripleDisplay(lowFourBitPosition, lowFourBit);
	Delay(5);

	return 0;
}
*/
void RunDigitronTest()
{
	PrintString("\n---------Digitron Test---------\n");

	DigitronSingleDisplay();

	DigitronMutipleDisplay();

	DigitronMulripleDisplay((POSITION)(POSITION_0 & POSITION_1 & POSITION_2 & POSITION_3 & POSITION_4 & POSITION_5), 16);
	
	PrintString("Pass\n");
}

