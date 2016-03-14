#include<reg52.h>
#include <string.h>

#include "Common.h"
#include "Uart.h"
#include "JGD1602.h"

sbit EN = P3^4;				//使能管脚
sbit DC = P3^5;				//数据、命令选择端（H、L）
sbit RW = P3^6;				//读写选择端

void PreInit()
{
	EN = 0;
	DC = 1;
	RW = 1;
	P0 = 0xff;   			//这里P0为与LCD D0~D7相连的I/O口
}

void WaitNotBusy()
{
	P0 = 0xff;
	DC = 0;
	RW = 1;
	EN = 1;

	while(P0 & 0x80);   	//P0和10000000相与，D7位若不为0，停在此处

	EN = 0;
}

void JGD1602WriteByte(uchar destChar, bit isData)
{
	WaitNotBusy();

	P0 = destChar;  
	DC = isData;			//其中isData = 0,写指令；isData = 1，写数据.
	
	RW = 0;
	EN = 1;
	EN = 0;
}

void JGD1602Init()    		//完全按照要求初始化流程来，中间省略了一步写指令38H
{
	PreInit();
	
	Delay(15);
	
	JGD1602WriteByte(0x38, 0);
	Delay(5);
	JGD1602WriteByte(0x38, 0);
	JGD1602WriteByte(0x08, 0);
	JGD1602WriteByte(0x01, 0);
	JGD1602WriteByte(0x06, 0);
//	JGD1602WriteByte(0x0c, 0);
	JGD1602WriteByte(0x0e, 0);
}


void JGD1602DisplayByte(uchar row, uchar colum, uchar destChar) 
{         
	if(row)    
	{        
		colum += 0x40;   				//第二行起始地址加上列数为字符显示地址
	}

	colum += 0x80;      				//设置数据指针位置
	JGD1602WriteByte(colum, 0);  
	JGD1602WriteByte(destChar, 1);   	//写入数据
}

void JGD1602DisplayText(uchar row, uchar colum, uchar destString[])    //row，colum同上字符显示，destString[]字符串数组 
{      
	uchar index = 0;

	while(destString[index] != '\0')
	{
		JGD1602DisplayByte(row, colum, destString[index]);
		colum++;
		index++;
		if(colum >= 16)
		{
			JGD1602WriteByte(0x07, 0);	
		}

		Delay(1000);
	}
}

void RunJDG1602Test()
{
	PrintString("\n---------At24c02 Test---------\n");

	JGD1602Init();

	JGD1602DisplayText(0, 0, "Qian Qian,");

	JGD1602DisplayText(1, 0, "Love you forever");

}