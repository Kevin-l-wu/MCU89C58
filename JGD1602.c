#include<reg52.h>
#include <string.h>

#include "Common.h"
#include "Uart.h"
#include "JGD1602.h"

sbit EN = P3^4;				//ʹ�ܹܽ�
sbit DC = P3^5;				//���ݡ�����ѡ��ˣ�H��L��
sbit RW = P3^6;				//��дѡ���

void PreInit()
{
	EN = 0;
	DC = 1;
	RW = 1;
	P0 = 0xff;   			//����P0Ϊ��LCD D0~D7������I/O��
}

void WaitNotBusy()
{
	P0 = 0xff;
	DC = 0;
	RW = 1;
	EN = 1;

	while(P0 & 0x80);   	//P0��10000000���룬D7λ����Ϊ0��ͣ�ڴ˴�

	EN = 0;
}

void JGD1602WriteByte(uchar destChar, bit isData)
{
	WaitNotBusy();

	P0 = destChar;  
	DC = isData;			//����isData = 0,дָ�isData = 1��д����.
	
	RW = 0;
	EN = 1;
	EN = 0;
}

void JGD1602Init()    		//��ȫ����Ҫ���ʼ�����������м�ʡ����һ��дָ��38H
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
		colum += 0x40;   				//�ڶ�����ʼ��ַ��������Ϊ�ַ���ʾ��ַ
	}

	colum += 0x80;      				//��������ָ��λ��
	JGD1602WriteByte(colum, 0);  
	JGD1602WriteByte(destChar, 1);   	//д������
}

void JGD1602DisplayText(uchar row, uchar colum, uchar destString[])    //row��columͬ���ַ���ʾ��destString[]�ַ������� 
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