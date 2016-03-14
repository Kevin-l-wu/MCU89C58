#include <reg52.h>

#include "Common.h"
#include "At24C02.h"
#include "Uart.h"
#include "LED.h"


sbit SDA = P2^0;
sbit SCL = P2^1;

static void Delay2us()
{
	;;
}

void I2cInit()
{
	SCL = 1;
	Delay2us();
	SDA = 1;
	Delay2us();
}

static void I2cStart()
{
	SDA = 1;
	Delay2us();
	SCL = 1;
	Delay2us();
	SDA = 0;
	Delay2us();
}

static void I2cStop()
{
	SDA = 0;
	Delay2us();
	SCL = 1;
	Delay2us();
	SDA = 1;
	Delay2us();
}

static void I2cRespons()
{	
	uchar i;
	SCL = 1;
	Delay2us();

	while((SDA == 1) && (i < 255))
	{
		i++;
	}

	SCL = 0;
	Delay2us();
}



int I2cReadByte(uchar* destChar)
{
	uchar i, k;
		
	SCL = 0;
	Delay2us();
	SDA = 1;

	for(i = 0; i < 8; i++)
	{
		SCL = 1;
		Delay2us();
		k = (k << 1) | SDA;
		SCL = 0;
		Delay2us();
	}
	Delay2us();
	*destChar = k;
	DisplayChar(*destChar);
	
	return 0;
}



int I2cWriteByte(uchar destChar)
{
	uchar i = 0, temp = destChar;
	
	for(i = 0; i < 8; i++)
	{
		temp = temp << 1;
		SCL = 0;
		Delay2us();
		SDA = CY;
		Delay2us();
		SCL = 1;
		Delay2us();
	}
	
	SCL = 0;
	Delay2us();
	SDA = 1;
	Delay2us();
	
	return 0;
}

int At24c02ReadByte(uchar address, uchar* destChar)
{

	I2cStart();
	I2cWriteByte(0xa0);
	I2cRespons();
	I2cWriteByte(address);
	I2cRespons();

	I2cStart();
	I2cWriteByte(0xa1);
	I2cRespons();
	
	I2cReadByte(destChar);
	I2cStop();

	return 0;
}

int At24c02WriteByte(uchar address, uchar destChar)
{
	I2cStart();

	I2cWriteByte(0xa0);
	I2cRespons();

	I2cWriteByte(address);
	I2cRespons();

	I2cWriteByte(destChar);
	I2cStop();

	return 0;
}
/*
int At24c02Read(unsigned address, unsigned length, char* destChar)
{

}

int At24c02Write(unsigned address, char* destChar, unsigned length)
{


}
*/


