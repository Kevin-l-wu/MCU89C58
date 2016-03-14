#include<reg52.h>

#include "Common.h"
#include "Uart.h"
#include "At24c02.h"

sbit SDA = P2^0;
sbit SCL = P2^1;

void Delay2us()
{ 
	;;
}

void I2cInit()
{
	SDA = 1;
	Delay2us();
	SCL = 1;
	Delay2us();
}

void I2cStart()  //开始信号
{	
	SDA = 1;
	Delay2us();
	SCL = 1;
	Delay2us();
	SDA = 0;
	Delay2us();
}

void I2cStop()   //停止
{
	SDA = 0;
	Delay2us();
	SCL = 1;
	Delay2us();
	SDA = 1;
	Delay2us();
}

void I2cRespons()  //应答
{
	uchar i;
	
	SCL = 1;
	Delay2us();
	
	while((SDA==1)&&(i<250))
	{
		i++;
	}
	
	SCL = 0;
	Delay2us();
}



void I2cWriteByte(uchar date)
{
	uchar i,temp;
	temp = date;


	for(i = 0; i < 8; i++)
	{
		temp = temp<<1;
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
}

uchar I2cReadByte()
{
	uchar i, destByte;
	
	SCL = 0;
	Delay2us();
	SDA = 1;
	Delay2us();
	
	for(i = 0; i < 8; i++)
	{
		SCL = 1;
		Delay2us();	
		destByte = (destByte << 1) | SDA;
		SCL = 0;
		Delay2us();	
	}
	
	return destByte;
}

int At24c02WriteByte(uchar address, uchar date)
{
	I2cStart();
	I2cWriteByte(0xa0);
	I2cRespons();
	I2cWriteByte(address);
	I2cRespons();
	I2cWriteByte(date);
	I2cRespons();
	I2cStop();

	return 0;
}

int At24c02ReadByte(uchar address, uchar* destChar)
{
	uchar date;

	I2cStart();
	I2cWriteByte(0xa0);
	I2cRespons();
	I2cWriteByte(address);
	I2cRespons();

	I2cStart();
	I2cWriteByte(0xa1);
	I2cRespons();
	date = I2cReadByte();
	I2cStop();

	*destChar = date;

	return 0;
}

void RunAt24c02Test()
{
	uint i = 0;
	uchar buffer;
	uchar asciiString[6] = {0};
	uchar rowSum = 0;
	uchar actualSum = 0;

	I2cInit();

	PrintString("\n---------At24c02 Test---------\n");

	//Caculate rowSum value
	for(i = 0; i < AT24C02_MAX_BYTE; i++)
	{
		 rowSum = rowSum ^ i;
	}
	PrintString("rowSum = ");
	UcharNumberToAscii(rowSum, asciiString);
	PrintString(asciiString);
	PrintChar('\n');

	//Write date to AT24C02
	for(i = 0; i < AT24C02_MAX_BYTE; i++)
	{
		At24c02WriteByte(i, i);
		Delay(2);
	}

	//Read date and caculate sum
	for(i = 0; i < AT24C02_MAX_BYTE; i++)
	{
		At24c02ReadByte(i, &buffer);
		Delay(2);
		actualSum = actualSum ^ buffer;
	}
	
	PrintString("actualSum = ");
	UcharNumberToAscii(actualSum, asciiString);
	PrintString(asciiString);
	PrintChar('\n');

	if(actualSum == rowSum)
	{
		PrintString("Pass\n");
	}
	else
	{
		PrintString("Failed\n");
	}
}



